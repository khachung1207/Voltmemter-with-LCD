#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include "lcd_i2c.h"
#include "adc_read.h"

#include "measure_voltage.h"
#include "measure_current.h"
#include "measure_resistance.h"

// ⭐ ĐỔI CHÂN BUTTON TỪ GPIO3 → GPIO4
#define BUTTON_PIN GPIO_NUM_4

int lcd_state = 0;
int last_btn = 1;

void app_main()
{
    i2c_master_init();
    lcd_init();
    adc_init_all();
 
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);

    while (1)
    {
        int btn = gpio_get_level(BUTTON_PIN);

        if (btn == 0 && last_btn == 1)
        {
            lcd_state++;
            if (lcd_state > 2) lcd_state = 0;
            vTaskDelay(200 / portTICK_PERIOD_MS);   // debounce
        }

        last_btn = btn;

        switch (lcd_state)
        {
            case 0: show_voltage(); break;
            case 1: show_current(); break;
            case 2: show_resistance(); break;
        }

        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
