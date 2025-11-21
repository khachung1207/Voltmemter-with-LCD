#include "lcd.h"
#include "driver/i2c.h"

static i2c_lcd1602_info_t* lcd;

i2c_lcd1602_info_t* lcd_init_driver()
{
    lcd = i2c_lcd1602_init(0, 0x27, 16, 2);
    return lcd;
}

void lcd_clear() {
    i2c_lcd1602_clear(lcd);
}

void lcd_print_voltage(float v) {
    i2c_lcd1602_clear(lcd);
    i2c_lcd1602_move_cursor(lcd,0,0);
    i2c_lcd1602_printf(lcd,"Voltage: %.2fV", v);
}

void lcd_print_current(float c) {
    i2c_lcd1602_clear(lcd);
    i2c_lcd1602_move_cursor(lcd,0,0);
    i2c_lcd1602_printf(lcd,"Current: %.2fmA", c);
}

void lcd_print_resistance(float r) {
    i2c_lcd1602_clear(lcd);
    i2c_lcd1602_move_cursor(lcd,0,0);
    i2c_lcd1602_printf(lcd,"Resistance:");
    i2c_lcd1602_move_cursor(lcd,0,1);
    i2c_lcd1602_printf(lcd,"%.1f ohm", r);
}
