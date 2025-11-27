#include "adc.h"
#include "driver/adc.h"
#include <math.h>

#define ADC_VOLT_PIN      ADC1_CHANNEL_0   // GPIO36
#define ADC_RES_PIN       ADC1_CHANNEL_6   // GPIO34
#define ADC_CURR_PIN      ADC1_CHANNEL_4   // GPIO32

void adc_init()
{
    adc1_config_width(ADC_WIDTH_BIT_12);

    adc1_config_channel_atten(ADC_VOLT_PIN, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC_RES_PIN,  ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC_CURR_PIN, ADC_ATTEN_DB_11);
}

float read_voltage()
{
    int raw = adc1_get_raw(ADC_VOLT_PIN);
    float v = raw * 3.3f / 4095.0f;

    v = v * 15.0f * 1.043f;
    return v;
}

float read_current()
{
    int raw = adc1_get_raw(ADC_CURR_PIN);
    float v = raw * 3.3f / 4095.0f;

    return fabs((v - 2.5f) / 0.185f);
}

float read_resistance()
{
    int raw = adc1_get_raw(ADC_RES_PIN);
    float v = raw * 3.3f / 4095.0f;

    float Rref = 10000.0f;
    return (v * Rref) / (3.3f - v);
}
