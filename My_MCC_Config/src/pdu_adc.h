/**
 * @file pdu_adc.h
 * @brief PDU ADC interface — voltage sensing via internal 2.048 V reference
 *
 * Each relay output channel has a resistor divider (÷11) feeding the
 * PIC32CM internal ADC.  Oversampling is used to achieve 14–16 effective
 * bits from the native 12-bit SAR.
 */

#ifndef PDU_ADC_H
#define PDU_ADC_H

#include <stdbool.h>

/** Internal voltage reference (SUPC VREF = 2.048 V) */
#define PDU_ADC_VREF_VOLTS       2.048f

/** Native 12-bit ADC full-scale count */
#define PDU_ADC_MAX_COUNTS       4095.0f

/**
 * Oversampling factor — must be a power of 4 (1, 4, 16, 64, 256…).
 * Each 4× adds 1 effective bit:  16× → 14-bit, 64× → 15-bit, 256× → 16-bit.
 */
#define PDU_ADC_OVERSAMPLE       64U

/** Resistor-divider ratio  (Rtop + Rbot) / Rbot  = 11 : 1 */
#define PDU_ADC_DIVIDER_RATIO    11.0f

/**
 * @brief ADC input channels for per-output voltage sensing
 */
typedef enum
{
    PDU_ADC_VSENSE_HYBRID = 0,  /**< Hybrid   — AIN9  */
    PDU_ADC_VSENSE_VENT1,       /**< Vent1    — AIN8  */
    PDU_ADC_VSENSE_VENT2,       /**< Vent2    — AIN7  */
    PDU_ADC_VSENSE_IGN,         /**< IGN/INJ  — AIN6  */
    PDU_ADC_VSENSE_FUEL,        /**< Fuel     — AIN5  */
    PDU_ADC_VSENSE_WP1,         /**< WP1      — AIN3  */
    PDU_ADC_VSENSE_WP2,         /**< WP2      — AIN4  */
    PDU_ADC_VSENSE_12V          /**< 12V      — AIN2  */
} pdu_adc_channel_t;

/* ── API ───────────────────────────────────────────────────────────── */

/**
 * @brief Initialise the ADC peripheral with internal 2.048 V reference.
 */
void PDU_ADC_Init(void);

/**
 * @brief Read the actual output voltage on one channel (volts).
 *
 * Performs oversampled conversion, applies the resistor-divider
 * scale factor, and returns the voltage at the relay output.
 *
 * @param ch   Channel to read
 * @return     Output voltage in volts (e.g. 12.34f)
 */
float PDU_ADC_ReadChannelVoltage(pdu_adc_channel_t ch);

#endif /* PDU_ADC_H */