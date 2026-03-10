#include "pdu_adc.h"
#include "config/default/peripheral/adc/plib_adc0.h"

#define PDU_ADC_SETTLE_DISCARDS  6U
#define PDU_ADC_AVERAGE_SAMPLES  8U
#define PDU_ADC_ENABLE_WARMUP_SAMPLES  6U

static pdu_adc_reference_t pdu_adc_reference = PDU_ADC_REF_EXTERNAL;

static void pdu_adc_discard_warmup_samples(void)
{
    uint8_t sample;

    for (sample = 0U; sample < PDU_ADC_ENABLE_WARMUP_SAMPLES; sample++)
    {
        ADC0_ConversionStart();
        while (!ADC0_ConversionStatusGet())
        {
        }
        (void)ADC0_ConversionResultGet();
    }
}

static bool pdu_adc_select_channel(pdu_adc_channel_t ch)
{
    ADC_POSINPUT input;

    switch (ch)
    {
        case PDU_ADC_IMON_HYBRID:
            input = ADC_POSINPUT_AIN9;
            break;
        case PDU_ADC_IMON_VENT1:
            input = ADC_POSINPUT_AIN8;
            break;
        case PDU_ADC_IMON_VENT2:
            input = ADC_POSINPUT_AIN7;
            break;
        case PDU_ADC_IMON_IGN:
            input = ADC_POSINPUT_AIN6;
            break;
        case PDU_ADC_IMON_FUEL:
            input = ADC_POSINPUT_AIN5;
            break;
        case PDU_ADC_IMON_WP1:
            input = ADC_POSINPUT_AIN3;
            break;
        case PDU_ADC_IMON_WP2:
            input = ADC_POSINPUT_AIN4;
            break;
        case PDU_ADC_IMON_12V:
            input = ADC_POSINPUT_AIN2;
            break;
        case PDU_ADC_NONFUSE_SHUNT:
            input = ADC_POSINPUT_AIN10;
            break;
        default:
            return false;
    }

    ADC0_ChannelSelect(input, ADC_NEGINPUT_GND);
    return true;
}

static uint16_t pdu_adc_read_raw(pdu_adc_channel_t ch)
{
    uint32_t sum = 0U;
    uint8_t sample;

    if (!pdu_adc_select_channel(ch))
    {
        return 0U;
    }

    /*
     * The input mux is switched between channels. Discard a few samples so the
     * mux and sample capacitor settle, then average multiple conversions.
     */
    for (sample = 0U; sample < PDU_ADC_SETTLE_DISCARDS; sample++)
    {
        ADC0_ConversionStart();
        while (!ADC0_ConversionStatusGet())
        {
        }
        (void)ADC0_ConversionResultGet();
    }

    for (sample = 0U; sample < PDU_ADC_AVERAGE_SAMPLES; sample++)
    {
        ADC0_ConversionStart();
        while (!ADC0_ConversionStatusGet())
        {
        }
        sum += ADC0_ConversionResultGet();
    }

    return (uint16_t)((sum + (PDU_ADC_AVERAGE_SAMPLES / 2U)) / PDU_ADC_AVERAGE_SAMPLES);
}

void PDU_ADC_Init(void)
{
    (void)PDU_ADC_SetReference(PDU_ADC_REF_EXTERNAL);
}

bool PDU_ADC_SetReference(pdu_adc_reference_t reference)
{
    uint8_t refsel;
    uint32_t supc_vref;

    switch (reference)
    {
        case PDU_ADC_REF_EXTERNAL:
            refsel = (uint8_t)ADC_REFCTRL_REFSEL_VREFA;
            break;
        case PDU_ADC_REF_INTERNAL:
            refsel = (uint8_t)ADC_REFCTRL_REFSEL_INTREF;
            break;
        default:
            return false;
    }

    supc_vref = SUPC_REGS->SUPC_VREF;
    supc_vref &= ~(SUPC_VREF_SEL_Msk | SUPC_VREF_VREFOE_Msk | SUPC_VREF_RUNSTDBY_Msk | SUPC_VREF_ONDEMAND_Msk);
    if (reference == PDU_ADC_REF_INTERNAL)
    {
        supc_vref |= SUPC_VREF_SEL_2V048;
    }
    SUPC_REGS->SUPC_VREF = supc_vref;

    ADC0_Disable();
    ADC0_REGS->ADC_REFCTRL = refsel;
    while (0U != ADC0_REGS->ADC_SYNCBUSY)
    {
    }

    ADC0_Enable();
    pdu_adc_discard_warmup_samples();
    pdu_adc_reference = reference;
    return true;
}

pdu_adc_reference_t PDU_ADC_GetReference(void)
{
    return pdu_adc_reference;
}

float PDU_ADC_ReadVoltage(pdu_adc_channel_t ch)
{
    uint16_t raw = pdu_adc_read_raw(ch);
    (void)ch;
    return ((float)raw / ADC_MAX_COUNTS) * ADC_VREF_VOLTS;
}

float PDU_ADC_ReadImonCurrent(pdu_adc_channel_t ch, float r_imon_ohms)
{
    float voltage = PDU_ADC_ReadVoltage(ch);

    if (r_imon_ohms <= 0.0f)
    {
        return 0.0f;
    }

    return voltage / (PDU_ADC_IMON_GAIN_A_PER_A * r_imon_ohms);
}

float PDU_ADC_ReadNonfuseCurrent(void)
{
    float voltage = PDU_ADC_ReadVoltage(PDU_ADC_NONFUSE_SHUNT);
    return voltage / PDU_ADC_SHUNT_GAIN_V_PER_A;
}
