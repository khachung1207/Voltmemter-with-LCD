#ifndef BUTTON_H
#define BUTTON_H

#include "driver/gpio.h"

void button_init(gpio_num_t pin);
int button_get_pressed();

#endif
