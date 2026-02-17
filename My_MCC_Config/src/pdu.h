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

#endif /* PDU_H */
