#ifndef PDU_ADC_H
#define PDU_ADC_H

//#include <stdint.h>
#include <stdbool.h>

/* External reference voltage */
#define ADC_VREF_VOLTS 2.048f
#define ADC_MAX_COUNTS 4095.0f   /* 12-bit ADC */

/* ADC channels for IMON pins (example – adjust to MCC) */
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

void  PDU_ADC_Init(void);
float PDU_ADC_ReadVoltage(pdu_adc_channel_t ch);

#endif /* PDU_ADC_H */
