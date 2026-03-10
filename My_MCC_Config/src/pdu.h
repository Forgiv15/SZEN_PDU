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
 * @brief Service 1 ms PDU tasks.
 *
 * Handles fast safety interlock timing that should not wait for the 100 ms
 * telemetry task.
 */
void PDU_Task1ms(void);

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

#endif /* PDU_H */