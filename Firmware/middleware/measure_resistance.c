#include "measure_resistance.h"
#include "adc_read.h"
#include "lcd_i2c.h"
#include <stdio.h>

void show_resistance()
{
    int adc_val = read_adc_avg(ADC1_CHANNEL_7, 100);
    float Vout = (float)adc_val / 4095.0f * 3.3f;

    float Rref = 10000.0f;
    float Rx = Rref * (Vout / (3.3f - Vout))+200 ;

    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("Resistance:");

    char buf[20];
    sprintf(buf, "%.1f ohm", Rx);
    lcd_set_cursor(1, 0);
    lcd_print(buf);
}
