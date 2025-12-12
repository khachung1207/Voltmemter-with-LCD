#ifndef ADC_READ_H
#define ADC_READ_H

#include "driver/adc.h"

void adc_init_all();
int read_adc_avg(adc1_channel_t ch, int samples);

#endif
