#include "measure_voltage.h"
#include "adc_read.h"
#include "lcd_i2c.h"
#include <stdio.h>

void show_voltage()
{
    int adc_val = read_adc_avg(ADC1_CHANNEL_3, 200);

    float voltage = adc_val * 15.0f * (28205.0f / 27000.0f) * 1.10f / 4096.0f;

    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("Voltage:");

    char buf[20];
    sprintf(buf, "%.2f V", voltage);
    lcd_set_cursor(1, 0);
    lcd_print(buf);
}
