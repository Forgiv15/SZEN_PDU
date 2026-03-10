#include <Arduino.h>
#include "driver/twai.h"
#include <stdlib.h>
#include <string.h>

/* ================= PIN CONFIG ================= */
#define CAN_TX_PIN 14
#define CAN_RX_PIN 13
#define CAN_RS_PIN 38   // Set LOW to enable transceiver (for SN65HVD)

/* ================= SETTINGS ================= */
#define UART_BAUD 921600

/* ================= GLOBAL ================= */
static bool can_ok = false;
static char serial_line_buffer[128];
static size_t serial_line_length = 0;

static bool parse_hex_byte(const char* token, uint8_t* value)
{
    char* end_ptr = nullptr;
    unsigned long parsed;

    if ((token == nullptr) || (value == nullptr))
    {
        return false;
    }

    parsed = strtoul(token, &end_ptr, 16);
    if ((end_ptr == token) || (*end_ptr != '\0') || (parsed > 0xFFUL))
    {
        return false;
    }

    *value = (uint8_t)parsed;
    return true;
}

static void process_serial_command(char* line)
{
    char* tokens[5] = { nullptr };
    char* save_ptr = nullptr;
    char* token = nullptr;
    char* byte_token = nullptr;
    char* byte_save_ptr = nullptr;
    twai_message_t msg = {};
    unsigned long can_id;
    unsigned long dlc;
    size_t index = 0;

    token = strtok_r(line, ",", &save_ptr);
    while ((token != nullptr) && (index < 5U))
    {
        tokens[index++] = token;
        token = strtok_r(nullptr, ",", &save_ptr);
    }

    if ((index < 4U) || (strcmp(tokens[0], "TX") != 0))
    {
        return;
    }

    msg.extd = (strcmp(tokens[1], "E") == 0) ? 1U : 0U;
    if ((msg.extd == 0U) && (strcmp(tokens[1], "S") != 0))
    {
        Serial.println("TXERR,BAD_TYPE");
        return;
    }

    can_id = strtoul(tokens[2], nullptr, 16);
    dlc = strtoul(tokens[3], nullptr, 10);
    if (dlc > 8UL)
    {
        Serial.println("TXERR,BAD_DLC");
        return;
    }

    msg.identifier = (uint32_t)can_id;
    msg.data_length_code = (uint8_t)dlc;
    msg.rtr = 0U;
    msg.ss = 0U;
    msg.self = 0U;
    msg.dlc_non_comp = 0U;

    if (index >= 5U)
    {
        byte_token = strtok_r(tokens[4], " ", &byte_save_ptr);
        index = 0U;
        while ((byte_token != nullptr) && (index < msg.data_length_code))
        {
            if (!parse_hex_byte(byte_token, &msg.data[index]))
            {
                Serial.println("TXERR,BAD_DATA");
                return;
            }
            index++;
            byte_token = strtok_r(nullptr, " ", &byte_save_ptr);
        }

        if (index != msg.data_length_code)
        {
            Serial.println("TXERR,LEN_MISMATCH");
            return;
        }
    }
    else if (msg.data_length_code != 0U)
    {
        Serial.println("TXERR,NO_DATA");
        return;
    }

    if (twai_transmit(&msg, pdMS_TO_TICKS(20)) == ESP_OK)
    {
        Serial.println("TXOK");
    }
    else
    {
        Serial.println("TXERR,CAN");
    }
}

static void service_serial_tx_commands(void)
{
    while (Serial.available() > 0)
    {
        char ch = (char)Serial.read();

        if ((ch == '\r') || (ch == '\n'))
        {
            if (serial_line_length > 0U)
            {
                serial_line_buffer[serial_line_length] = '\0';
                process_serial_command(serial_line_buffer);
                serial_line_length = 0U;
            }
        }
        else if (serial_line_length < (sizeof(serial_line_buffer) - 1U))
        {
            serial_line_buffer[serial_line_length++] = ch;
        }
        else
        {
            serial_line_length = 0U;
            Serial.println("TXERR,LINE_TOO_LONG");
        }
    }
}

/* ================= SETUP ================= */
void setup()
{
    Serial.begin(UART_BAUD);
    delay(500);

    Serial.println("\nESP32-S3 CAN Bridge Starting...");

    /* Enable transceiver */
    pinMode(CAN_RS_PIN, OUTPUT);
    digitalWrite(CAN_RS_PIN, LOW);   // LOW = normal mode (for SN65HVD)

    /* CAN Configuration */
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(
        (gpio_num_t)CAN_TX_PIN,
        (gpio_num_t)CAN_RX_PIN,
        TWAI_MODE_NORMAL
    );

    g_config.tx_queue_len = 4;
    g_config.rx_queue_len = 32;

    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    esp_err_t err;

    err = twai_driver_install(&g_config, &t_config, &f_config);
    if (err != ESP_OK)
    {
        Serial.printf("Driver install failed: %d\n", err);
        return;
    }

    err = twai_start();
    if (err != ESP_OK)
    {
        Serial.printf("CAN start failed: %d\n", err);
        return;
    }

    can_ok = true;
    Serial.println("CAN Started @500kbps");
}

/* ================= LOOP ================= */
void loop()
{
    service_serial_tx_commands();

    if (!can_ok)
    {
        delay(1000);
        return;
    }

    twai_message_t msg;

    if (twai_receive(&msg, pdMS_TO_TICKS(10)) == ESP_OK)
    {
        uint32_t ts = millis();

        Serial.print(ts);
        Serial.print(",");

        Serial.print(msg.extd ? "E," : "S,");

        if (msg.extd)
            Serial.printf("%08lX,", (unsigned long)(msg.identifier & 0x1FFFFFFF));
        else
            Serial.printf("%03lX,", (unsigned long)(msg.identifier & 0x7FF));

        Serial.print(msg.data_length_code);
        Serial.print(",");

        for (uint8_t i = 0; i < msg.data_length_code; i++)
        {
            Serial.printf("%02X", msg.data[i]);
            if (i < msg.data_length_code - 1)
                Serial.print(" ");
        }

        Serial.println();
    }

    /* Optional: monitor bus state */
    static uint32_t last_status = 0;
    if (millis() - last_status > 1000)
    {
        twai_status_info_t status;
        twai_get_status_info(&status);

        Serial.printf("State:%d RX:%d TX:%d ErrRX:%d ErrTX:%d\n",
                      status.state,
                      status.msgs_to_rx,
                      status.msgs_to_tx,
                      status.rx_error_counter,
                      status.tx_error_counter);

        last_status = millis();
    }
}
