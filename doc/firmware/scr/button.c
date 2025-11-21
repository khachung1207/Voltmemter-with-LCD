#include "button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static gpio_num_t btn_pin;
static int last_state = 1;

void button_init(gpio_num_t pin)
{
    btn_pin = pin;
    gpio_set_direction(btn_pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(btn_pin, GPIO_PULLUP_ONLY);
}

int button_get_pressed()
{
    int now = gpio_get_level(btn_pin);
    int pressed = 0;
    if(last_state == 1 && now == 0)
    {
        pressed = 1;
        vTaskDelay(200 / portTICK_PERIOD_MS); // debounce
    }
    last_state = now;
    return pressed;
}
