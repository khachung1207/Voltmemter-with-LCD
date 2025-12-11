#include "lcd_i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define I2C_PORT I2C_NUM_0
#define SDA_PIN 21
#define SCL_PIN 22
#define LCD_ADDR 0x27     

#define LCD_BACKLIGHT 0x08
#define ENABLE 0x04
#define RS 0x01

void i2c_master_init()
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = SDA_PIN,
        .scl_io_num = SCL_PIN,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000
    };
    i2c_param_config(I2C_PORT, &conf);
    i2c_driver_install(I2C_PORT, conf.mode, 0, 0, 0);
}

static void lcd_write_4bits(uint8_t data)
{
    uint8_t d1 = data | LCD_BACKLIGHT | ENABLE;
    uint8_t d2 = data | LCD_BACKLIGHT;

    i2c_master_write_to_device(I2C_PORT, LCD_ADDR, &d1, 1, 1000 / portTICK_PERIOD_MS);
    esp_rom_delay_us(50);

    i2c_master_write_to_device(I2C_PORT, LCD_ADDR, &d2, 1, 1000 / portTICK_PERIOD_MS);
    esp_rom_delay_us(50);
}

static void lcd_send(uint8_t value, uint8_t mode)
{
    uint8_t high = (value & 0xF0) | mode;
    uint8_t low  = ((value << 4) & 0xF0) | mode;

    lcd_write_4bits(high);
    lcd_write_4bits(low);
}

void lcd_clear()
{
    lcd_send(0x01, 0);
    vTaskDelay(3 / portTICK_PERIOD_MS);
}

void lcd_set_cursor(int row, int col)
{
    uint8_t addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_send(addr, 0);
}

void lcd_print(const char *s)
{
    while (*s)
        lcd_send(*s++, RS);
}

void lcd_init()
{
    vTaskDelay(50 / portTICK_PERIOD_MS);

    lcd_write_4bits(0x30);
    esp_rom_delay_us(4500);

    lcd_write_4bits(0x30);
    esp_rom_delay_us(4500);

    lcd_write_4bits(0x20);   // 4-bit mode
    esp_rom_delay_us(150);

    lcd_send(0x28, 0); // 4-bit 2-line
    lcd_send(0x0C, 0); // display ON
    lcd_send(0x06, 0); // entry mode
    lcd_clear();
}
