#include <Arduino.h>
#include "driver/twai.h"

/* ================= PIN CONFIG ================= */
#define CAN_TX_PIN 14
#define CAN_RX_PIN 13
#define CAN_RS_PIN 38   // Set LOW to enable transceiver (for SN65HVD)

/* ================= SETTINGS ================= */
#define UART_BAUD 921600

/* ================= GLOBAL ================= */
static bool can_ok = false;

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
