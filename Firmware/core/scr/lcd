#include "lcd.h"
#include "i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LCD_ADDR  0x27

static void lcd_send_cmd(uint8_t cmd)
{
    uint8_t data[2] = {0x80, cmd};
    i2c_write_bytes(LCD_ADDR, data, 2);
}

static void lcd_send_data(uint8_t data)
{
    uint8_t packet[2] = {0x40, data};
    i2c_write_bytes(LCD_ADDR, packet, 2);
}

void lcd_init()
{
    i2c_init();
    vTaskDelay(50 / portTICK_PERIOD_MS);

    lcd_send_cmd(0x33);
    lcd_send_cmd(0x32);
    lcd_send_cmd(0x28);
    lcd_send_cmd(0x0C);
    lcd_send_cmd(0x06);
    lcd_clear();
}

void lcd_clear()
{
    lcd_send_cmd(0x01);
    vTaskDelay(2 / portTICK_PERIOD_MS);
}

void lcd_set_cursor(int col, int row)
{
    uint8_t cmd = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_send_cmd(cmd);
}

void lcd_print(const char *str)
{
    while (*str)
    {
        lcd_send_data((uint8_t)*str);
        str++;
    }
}
