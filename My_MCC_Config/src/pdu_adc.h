/**
 * @file pdu_adc.h
 * @brief PDU ADC interface for IMON current monitoring
 * 
 * Provides ADC reading functionality for the TPS25990 IMON pins.
 */

#ifndef PDU_ADC_H
#define PDU_ADC_H

#include <stdint.h>
#include <stdbool.h>

/* External reference voltage for ADC */
#define ADC_VREF_VOLTS      2.048f
#define ADC_MAX_COUNTS      4095.0f   /* 12-bit ADC */

/**
 * @brief ADC channels for IMON pins mapping to eFuse channels
 */
typedef enum
{
    PDU_ADC_IMON_HYBRID = 0,
    PDU_ADC_IMON_VENT1,
    PDU_ADC_IMON_VENT2,
    PDU_ADC_IMON_IGN,
    PDU_ADC_IMON_FUEL,
    PDU_ADC_IMON_WP1,
    PDU_ADC_IMON_WP2,
    PDU_ADC_IMON_12V
} pdu_adc_channel_t;

/**
 * @brief Initialize ADC peripherals for IMON reading
 */
void PDU_ADC_Init(void);

/**
 * @brief Read voltage from an IMON ADC channel
 * 
 * @param ch ADC channel to read
 * @return float Voltage in volts
 */
float PDU_ADC_ReadVoltage(pdu_adc_channel_t ch);

#endif /* PDU_ADC_H */