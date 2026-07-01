/**
 * @file pdu.h
 * @brief Power Distribution Unit (PDU) — Relay-based (Dumb PDU) variant
 *
 * Controls 8 relay channels via GPIO with CAN-bus command input and
 * per-channel voltage telemetry from the PIC32CM internal ADC.
 *
 * No PMBus, no TPS25990 eFuses, no I2C — pure GPIO + ADC + CAN.
 */

#ifndef PDU_H
#define PDU_H

#include <stdint.h>
#include <stdbool.h>

/** Number of relay output channels */
#define PDU_NUM_CHANNELS  8U

/**
 * @brief Initialize CAN0 message RAM for PDU telemetry.
 * Must be called once after CAN0_Initialize().
 */
void PDU_CAN_Init(void);

/**
 * @brief Initialize the PDU subsystem.
 *
 * Configures ADC (internal 2.048 V reference, oversampling),
 * enables all GPIO output drivers, registers CAN / timer / EIC
 * callbacks, and forces safety-off state if any interlock is active.
 */
void PDU_Init(void);

/**
 * @brief Service pending PDU work scheduled by interrupts.
 *
 * Runs control reconciliation at 100 Hz and telemetry
 * transmission at 20 Hz.  Must be called from the main loop.
 */
void PDU_Service(void);

/**
 * @brief Poll ADC channels and transmit telemetry on CAN0.
 *
 * Always sent (20 Hz):
 *  - 0x700  Summary:  VIN_avg_mV(u16), system_flags(u8),
 *                     control_state(u8), requested_mask(u8),
 *                     applied_mask(u8), ecu_mask(u8), dash_mask(u8)
 *  - 0x701  Voltages ch0-3:  ch0_mV…ch3_mV  (4 × uint16)
 *  - 0x702  Voltages ch4-7:  ch4_mV…ch7_mV  (4 × uint16)
 *  - 0x085  Input8 raw state (1 byte)
 *
 * Debug mode only (debug flag set via 0x200 frame):
 *  - 0x740  MCU debug telemetry
 *  - 0x703  ECU raw debug
 */
void PDU_PollAndSendTelemetry(void);

#endif /* PDU_H */