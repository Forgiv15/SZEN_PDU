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
 * @brief Initialize CAN0 runtime resources for PDU telemetry
 *
 * Must be called once after CAN0_Initialize().
 */
void PDU_CAN_Init(void);

/**
 * @brief Initialize the PDU subsystem
 * 
 * Initializes ADC, GPIO pins for LEDs, and prepares for eFuse communication.
 */
void PDU_Init(void);

/**
 * @brief Service pending PDU work scheduled by timer/CAN interrupts.
 *
 * Executes fast control reconciliation at 100 Hz and telemetry transmission at
 * 10 Hz without doing blocking PMBus work inside interrupt context.
 */
void PDU_Service(void);

/**
 * @brief Poll all TPS25990 channels and transmit telemetry on CAN
 *
 * Sends aggregated telemetry at 10 Hz on CAN IDs 0x700 and 0x701:
 *  - 0x700: VIN_avg_mV, SumCurrent_dA (0.1A units), TempAvg_c_x10,
 *           err_flags (bit0 overcurrent>60A, bit1 VIN outside 10-15V), flt_bitmap
 *  - 0x701: TempPeak_c_x10, system_flags, debug_active flag
 *
 * When debug mode is armed via control frame debug flag, also sends per-channel
 * debug frames on 0x710-0x791 (efuse, ADC, temp, MCU, error detail, PMBus trace).
 */
void PDU_PollAndSendTelemetry(void);

#endif /* PDU_H */