#include "main.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

int lcdState = 0;

void app_main() {
    lcd_init();
    button_init();

    while (1) {
        if (button_read()) {
            lcdState++;
            if (lcdState > 2) lcdState = 0;
            vTaskDelay(150 / portTICK_PERIOD_MS);
        }

        lcd_clear();

        if (lcdState == 0) {
            char text[20];
            float v = read_voltage();
            lcd_set_cursor(0,0);
            lcd_print("Voltage:");
            sprintf(text, "%.2f V", v);
            lcd_set_cursor(0,1);
            lcd_print(text);
        }

        else if (lcdState == 1) {
            char text[20];
            float c = read_current();
            lcd_set_cursor(0,0);
            lcd_print("Current:");
            sprintf(text, "%.2f A", c);
            lcd_set_cursor(0,1);
            lcd_print(text);
        }

        else {
            char text[20];
            float r = read_resistance();
            lcd_set_cursor(0,0);
            lcd_print("Res:");
            sprintf(text, "%.2f Ohm", r);
            lcd_set_cursor(0,1);
            lcd_print(text);
        }

        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}
