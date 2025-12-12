#include "adc_read.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void adc_init_all()
{
    adc1_config_width(ADC_WIDTH_BIT_12);

    adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_5, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11);
}

int read_adc_avg(adc1_channel_t ch, int samples)
{
    int sum = 0;
    for (int i = 0; i < samples; i++)
    {
        sum += adc1_get_raw(ch);
        vTaskDelay(1);
    }
    return sum / samples;
}
