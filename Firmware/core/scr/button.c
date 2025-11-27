#include "button_driver.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUTTON_PIN     16

void button_init()
{
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);
}

int button_read()
{
    static int last = 1;
    int current = gpio_get_level(BUTTON_PIN);

    // Active LOW
    if (current == 0 && last == 1)
    {
        last = 0;
        vTaskDelay(20 / portTICK_PERIOD_MS);
        return 1;
    }

    if (current == 1)
    {
        last = 1;
    }

    return 0;
}
