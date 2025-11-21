#ifndef LCD_H
#define LCD_H

#include "i2c_lcd1602.h"

i2c_lcd1602_info_t* lcd_init_driver();
void lcd_clear();
void lcd_print_voltage(float v);
void lcd_print_current(float c);
void lcd_print_resistance(float r);

#endif
