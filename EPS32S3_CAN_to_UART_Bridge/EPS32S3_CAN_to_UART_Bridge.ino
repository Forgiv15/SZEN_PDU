#include <Arduino.h>
#include "driver/twai.h"

/* =========================
   PIN DEFINITIONS
   ========================= */
#define CAN_TX_PIN 14
#define CAN_RX_PIN 13
#define CAN_RS_PIN 38   // Not used

/* =========================
   UART SETTINGS
   ========================= */
#define UART_BAUD 921600

/* =========================
   CAN SETTINGS
   ========================= */
#define CAN_BAUD_RATE TWAI_TIMING_CONFIG_500KBITS()

/* =========================
   Setup
   ========================= */
void setup()
{
    Serial.begin(UART_BAUD);
    delay(1000);

    Serial.println("ESP32-S3 CAN Bridge Starting...");

    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(
        (gpio_num_t)CAN_TX_PIN,
        (gpio_num_t)CAN_RX_PIN,
        TWAI_MODE_NORMAL
    );

    twai_timing_config_t t_config = CAN_BAUD_RATE;
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK)
    {
        Serial.println("CAN Driver Install Failed!");
        while (1);
    }

    if (twai_start() != ESP_OK)
    {
        Serial.println("CAN Start Failed!");
        while (1);
    }

    Serial.println("CAN Initialized at 500kbps");
}

/* =========================
   Loop
   ========================= */
void loop()
{
    twai_message_t message;

    if (twai_receive(&message, pdMS_TO_TICKS(100)) == ESP_OK)
    {
        uint32_t timestamp = millis();

        Serial.print(timestamp);
        Serial.print(",");

        if (message.extd)
        {
            Serial.print("E,");
        }
        else
        {
            Serial.print("S,");
        }

        Serial.print(message.identifier, HEX);
        Serial.print(",");

        Serial.print(message.data_length_code);
        Serial.print(",");

        for (int i = 0; i < message.data_length_code; i++)
        {
            if (message.data[i] < 0x10)
                Serial.print("0");

            Serial.print(message.data[i], HEX);

            if (i < message.data_length_code - 1)
                Serial.print(" ");
        }

        Serial.println();
    }
}
