#include "adc_measure.h"
#include "driver/adc.h"
#include <math.h>

#define ADC_VOLTAGE_CH ADC1_CHANNEL_0
#define ADC_RES_CH     ADC1_CHANNEL_6
#define ACS712_CH      ADC1_CHANNEL_4

static const float VCC = 3.3;
static const float Rref = 10000.0;

void adc_init_all()
{
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC_VOLTAGE_CH, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC_RES_CH, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ACS712_CH, ADC_ATTEN_DB_11);
}

float read_voltage()
{
    int total = 0;
    for(int i=0;i<200;i++) total += adc1_get_raw(ADC_VOLTAGE_CH);
    float adc = total / 200.0;
    return adc * VCC / 4095.0;
}

float read_current()
{
    int total = 0;
    for(int i=0;i<200;i++) total += adc1_get_raw(ACS712_CH);
    float adc = total / 200.0;
    float voltage = adc * VCC / 4095.0;
    return fabs((voltage - 2.5)/0.185) - 0.36;
}

float read_resistance()
{
    int total = 0;
    for(int i=0;i<100;i++) total += adc1_get_raw(ADC_RES_CH);
    float adc = total / 100.0;
    float Vout = adc * VCC / 4095.0;
    return Rref * ((Vout/(VCC-Vout))*1.1);
}
