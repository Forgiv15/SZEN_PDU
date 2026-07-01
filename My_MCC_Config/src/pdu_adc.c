/**
 * @file pdu_adc.c
 * @brief PDU ADC — internal 2.048 V reference with oversampling
 *
 * Each relay output has a resistor divider (÷11) feeding the PIC32CM
 * internal ADC.  Oversampling gives 12+n effective bits from the
 * native 12-bit SAR.
 */

#include "pdu_adc.h"
#include "config/default/peripheral/adc/plib_adc0.h"

/* ── Oversampling helpers ──────────────────────────────────────────── */

/*
 * Each 4× oversampling adds 1 effective bit after decimation.
 * Decimation shift = log4(N).
 *
 *   N=  1 → shift 0  (12 bit)
 *   N=  4 → shift 1  (13 bit)
 *   N= 16 → shift 2  (14 bit)
 *   N= 64 → shift 3  (15 bit)
 *   N=256 → shift 4  (16 bit)
 */
#if PDU_ADC_OVERSAMPLE == 1
    #define OVERSAMPLE_SHIFT  0U
#elif PDU_ADC_OVERSAMPLE == 4
    #define OVERSAMPLE_SHIFT  1U
#elif PDU_ADC_OVERSAMPLE == 16
    #define OVERSAMPLE_SHIFT  2U
#elif PDU_ADC_OVERSAMPLE == 64
    #define OVERSAMPLE_SHIFT  3U
#elif PDU_ADC_OVERSAMPLE == 256
    #define OVERSAMPLE_SHIFT  4U
#else
    #error "PDU_ADC_OVERSAMPLE must be a power of 4 (1, 4, 16, 64, 256)"
#endif

/* Samples discarded after mux switch to let the S/H capacitor settle */
#define ADC_SETTLE_DISCARDS   4U

/* Samples discarded after ADC enable (reference start-up) */
#define ADC_WARMUP_SAMPLES    8U

/* Effective max code after decimation:
 *   native_max × sqrt(N)   because sum(N) >> log4(N) = sum / sqrt(N)
 *   = 4095 × (N >> shift)  where N >> shift = sqrt(N)           */
#define ADC_EFFECTIVE_MAX    (PDU_ADC_MAX_COUNTS * \
                              (float)(PDU_ADC_OVERSAMPLE >> OVERSAMPLE_SHIFT))

/* ── Internal state ────────────────────────────────────────────────── */

static bool adc_initialised = false;

/* ── Channel → POSINPUT lookup ─────────────────────────────────────── */

static ADC_POSINPUT adc_posinput_for_channel(pdu_adc_channel_t ch)
{
    switch (ch)
    {
        case PDU_ADC_VSENSE_HYBRID:  return ADC_POSINPUT_AIN9;
        case PDU_ADC_VSENSE_VENT1:   return ADC_POSINPUT_AIN8;
        case PDU_ADC_VSENSE_VENT2:   return ADC_POSINPUT_AIN7;
        case PDU_ADC_VSENSE_IGN:     return ADC_POSINPUT_AIN6;
        case PDU_ADC_VSENSE_FUEL:    return ADC_POSINPUT_AIN5;
        case PDU_ADC_VSENSE_WP1:     return ADC_POSINPUT_AIN3;
        case PDU_ADC_VSENSE_WP2:     return ADC_POSINPUT_AIN4;
        case PDU_ADC_VSENSE_12V:     return ADC_POSINPUT_AIN2;
        default:                     return ADC_POSINPUT_AIN9;
    }
}

/* ── Warm-up discard ───────────────────────────────────────────────── */

static void adc_discard_warmup(void)
{
    uint8_t i;
    for (i = 0U; i < ADC_WARMUP_SAMPLES; i++)
    {
        ADC0_ConversionStart();
        while (!ADC0_ConversionStatusGet()) { }
        (void)ADC0_ConversionResultGet();
    }
}

/* ── Oversampled single-channel read ───────────────────────────────── */

static uint32_t adc_read_oversampled(pdu_adc_channel_t ch)
{
    uint32_t sum = 0U;
    uint16_t sample;
    uint8_t i;

    ADC0_ChannelSelect(adc_posinput_for_channel(ch), ADC_NEGINPUT_GND);

    /* Discard settling samples after mux switch */
    for (i = 0U; i < ADC_SETTLE_DISCARDS; i++)
    {
        ADC0_ConversionStart();
        while (!ADC0_ConversionStatusGet()) { }
        (void)ADC0_ConversionResultGet();
    }

    /* Accumulate oversampled conversions */
    for (i = 0U; i < (uint8_t)PDU_ADC_OVERSAMPLE; i++)
    {
        ADC0_ConversionStart();
        while (!ADC0_ConversionStatusGet()) { }
        sample = ADC0_ConversionResultGet();
        sum += (uint32_t)sample;
    }

    /* Decimate: right-shift by log4(N) to recover the enhanced range */
    return (sum >> OVERSAMPLE_SHIFT);
}

/* ── Public API ────────────────────────────────────────────────────── */

void PDU_ADC_Init(void)
{
    uint32_t supc_vref;

    /* ── Configure SUPC internal VREF to 2.048 V ── */
    supc_vref  = SUPC_REGS->SUPC_VREF;
    supc_vref &= (uint32_t)(~(SUPC_VREF_SEL_Msk |
                               SUPC_VREF_VREFOE_Msk |
                               SUPC_VREF_RUNSTDBY_Msk |
                               SUPC_VREF_ONDEMAND_Msk));
    supc_vref |= SUPC_VREF_SEL_2V048;
    SUPC_REGS->SUPC_VREF = supc_vref;

    /* ── Switch ADC to internal reference ── */
    ADC0_Disable();
    ADC0_REGS->ADC_REFCTRL = (uint8_t)ADC_REFCTRL_REFSEL_INTREF;
    while (0U != ADC0_REGS->ADC_SYNCBUSY) { }

    ADC0_Enable();
    adc_discard_warmup();
    adc_initialised = true;
}

float PDU_ADC_ReadChannelVoltage(pdu_adc_channel_t ch)
{
    uint32_t raw;
    float v_adc;   /* voltage at ADC pin (after divider) */
    float v_out;   /* voltage at relay output (before divider) */

    if (!adc_initialised)
    {
        return 0.0f;
    }

    raw = adc_read_oversampled(ch);

    /* Convert raw decimated code to voltage at ADC input,
     * then multiply by divider ratio to get output voltage. */
    v_adc = ((float)(uint32_t)raw / ADC_EFFECTIVE_MAX) * PDU_ADC_VREF_VOLTS;
    v_out = v_adc * PDU_ADC_DIVIDER_RATIO;

    return v_out;
}
