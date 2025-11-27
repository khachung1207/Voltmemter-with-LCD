#include "adc_driver.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include <math.h>

#define ADC_VOLT_PIN      ADC1_CHANNEL_0   // GPIO36
#define ADC_RESIST_PIN    ADC1_CHANNEL_6   // GPIO34
#define ADC_CURRENT_PIN   ADC1_CHANNEL_4   // GPIO32

void adc_init()
{
    adc1_config_width(ADC_WIDTH_BIT_12);

    adc1_config_channel_atten(ADC_VOLT_PIN, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC_RESIST_PIN, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC_CURRENT_PIN, ADC_ATTEN_DB_11);
}

float read_voltage()
{
    int raw = adc1_get_raw(ADC_VOLT_PIN);
    float volt = raw * 3.3f / 4095.0f;

    // Nhân hệ số theo công thức bạn cung cấp
    volt = volt * 15.0f * 1.043f;

    return volt;
}

float read_current()
{
    int raw = adc1_get_raw(ADC_CURRENT_PIN);
    float volt = raw * 3.3f / 4095.0f;

    // ACS712 5A: 185 mV/A, offset 2.5V
    float current = fabs((volt - 2.5f) / 0.185f);

    return current;
}

float read_resistance()
{
    int raw = adc1_get_raw(ADC_RESIST_PIN);
    float volt = raw * 3.3f / 4095.0f;

    float Rref = 10000.0f;      // 10K Ohm
    float R = (volt * Rref) / (3.3f - volt);

    return R;
}
