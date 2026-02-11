#include "pdu_adc.h"
#include "config/default/peripheral/adc/plib_adc0.h"
// If you use ADC1, also include its header:
#include "config/default/peripheral/adc/plib_adc1.h"

void PDU_ADC_Init(void)
{
    ADC0_Enable();
    ADC1_Enable();
}

float PDU_ADC_ReadVoltage(pdu_adc_channel_t ch)
{
    uint16_t raw = 0;

    switch (ch)
    {
        case PDU_ADC_IMON_HYBRID:
            ADC0_ChannelSelect(ADC_POSINPUT_AIN9, ADC_NEGINPUT_GND);
            break;
        case PDU_ADC_IMON_VENT1:
            ADC0_ChannelSelect(ADC_POSINPUT_AIN8, ADC_NEGINPUT_GND);
            break;
        default:
            return 0.0f;
    }

    ADC0_ConversionStart();
    while (!ADC0_ConversionStatusGet());

    raw = ADC0_ConversionResultGet();

    return ((float)raw / ADC_MAX_COUNTS) * ADC_VREF_VOLTS;
}
