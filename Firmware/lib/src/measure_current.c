#include "measure_current.h"
#include "adc_read.h"
#include "lcd_i2c.h"
#include <math.h>

void show_current()
{
    int adc_val = read_adc_avg(ADC1_CHANNEL_5, 200);

    float Vadc = (float)adc_val / 4095.0f * 3.3f;

    float OFFSET = 2.50f;
    float current = fabs((Vadc - OFFSET) / 0.185f + 0.15f );

    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("Current:");

    char buf[20];
    sprintf(buf, "%.2fA", current);
    lcd_set_cursor(1, 0);
    lcd_print(buf);
}
