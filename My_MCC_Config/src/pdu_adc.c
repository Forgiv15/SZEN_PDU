#include "pdu_adc.h"
#include "config/default/peripheral/adc/plib_adc0.h"

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
    if (!pdu_adc_select_channel(ch))
    {
        return 0U;
    }

    ADC0_ConversionStart();
    while (!ADC0_ConversionStatusGet())
    {
    }
    (void)ADC0_ConversionResultGet();

    ADC0_ConversionStart();
    while (!ADC0_ConversionStatusGet())
    {
    }

    return ADC0_ConversionResultGet();
}

void PDU_ADC_Init(void)
{
    ADC0_Enable();
}

float PDU_ADC_ReadVoltage(pdu_adc_channel_t ch)
{
    uint16_t raw = pdu_adc_read_raw(ch);

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
