/**
 * @file pdu.h
 * @brief Power Distribution Unit (PDU) control and monitoring interface
 * 
 * Provides initialization and self-test functionality for the PDU
 * with 8 TPS25990 eFuses.
 */

#ifndef PDU_H
#define PDU_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief PDU operation result codes
 */
typedef enum
{
    PDU_OK = 0,     /**< Operation successful */
    PDU_FAULT       /**< Operation failed or fault detected */
} pdu_result_t;

/**
 * @brief Number of eFuses in the system
 */
#define PDU_NUM_EFUSES  8U

/**
 * @brief Initialize CAN1 runtime resources for PDU telemetry
 *
 * Must be called once after CAN1_Initialize().
 */
void PDU_CAN_Init(void);

/**
 * @brief Initialize the PDU subsystem
 * 
 * Initializes ADC, GPIO pins for LEDs, and prepares for eFuse communication.
 */
void PDU_Init(void);

/**
 * @brief Run all PDU self-checks and update status LEDs
 * 
 * Performs:
 * - Voltage check (all eFuses >11V) - Green LED
 * - Power calculation check - Blue LED  
 * - FET driver check - Red LED
 * 
 * LED states: ON = all OK, BLINK = fault detected
 */
void PDU_RunChecks(void);

/**
 * @brief Poll all TPS25990 channels and transmit telemetry on CAN
 *
 * Sends one 8-byte frame per eFuse on CAN IDs 0x500-0x507:
 * - bytes 0-1: VOUT in mV (uint16)
 * - bytes 2-3: IOUT in mA (uint16)
 * - bytes 4-5: PIN in 10mW units (uint16)
 * - bytes 6-7: STATUS_WORD (uint16)
 */
void PDU_PollAndSendTelemetry(void);

/**
 * @brief Send one independent CAN heartbeat frame on ID 0x520
 *
 * Returns true if frame was queued for transmission.
 */
bool PDU_CANSendHeartbeat(void);

/**
 * @brief Send MCU telemetry frame with independent CAN test signal
 *
 * Sends CAN ID 0x520 with a reserved-byte test pattern that toggles
 * between 0 and 255 on each call. This frame is independent of eFuse polling.
 */
void PDU_SendMcuTelemetryTest(void);

#endif /* PDU_H */