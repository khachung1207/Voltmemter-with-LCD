#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "driver/i2c.h"
#include "esp_rom_sys.h"

void lcd_init();
void lcd_clear();
void lcd_set_cursor(int row, int col);
void lcd_print(const char *str);

void i2c_master_init();

#endif
