#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "i2c_lcd1602.h"

#define I2C_MASTER_SDA 21
#define I2C_MASTER_SCL 22
#define I2C_PORT I2C_NUM_0
#define I2C_FREQ 100000

// LCD I2C address
#define LCD_ADDR 0x27

// ADC pins (ADC1 channel)
#define ADC_VOLTAGE_CH ADC1_CHANNEL_0   // GPIO36
#define ADC_RES_CH     ADC1_CHANNEL_6   // GPIO34
#define ACS712_CH      ADC1_CHANNEL_4   // GPIO32

#define BUTTON_PIN 16

static i2c_lcd1602_info_t* lcd;

static const float VCC = 3.3;
static const float Rref = 10000.0;

int lcd_state = 0;

void i2c_init()
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA,
        .scl_io_num = I2C_MASTER_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_FREQ
    };
    i2c_param_config(I2C_PORT, &conf);
    i2c_driver_install(I2C_PORT, conf.mode, 0, 0, 0);
}

void adc_init_all()
{
    adc1_config_width(ADC_WIDTH_BIT_12);

    adc1_config_channel_atten(ADC_VOLTAGE_CH, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC_RES_CH, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ACS712_CH, ADC_ATTEN_DB_11);
}

// ------------------------- Voltage ------------------------------ //
void show_voltage()
{
    int total = 0;
    for(int i = 0; i < 200; i++) total += adc1_get_raw(ADC_VOLTAGE_CH);
    float adc = total / 200.0;

    float voltage = adc * 3.3 / 4095.0;

    i2c_lcd1602_clear(lcd);
    i2c_lcd1602_move_cursor(lcd, 0, 0);
    i2c_lcd1602_printf(lcd, "Voltage: %.2fV", voltage);
}

// ------------------------- Current (ACS712) ------------------------------ //
void show_current()
{
    int total = 0;
    for(int i = 0; i < 200; i++) total += adc1_get_raw(ACS712_CH);

    float adc = total / 200.0;
    float voltage = adc * 3.3 / 4095.0;

    float current = fabs((voltage - 2.5) / 0.185) - 0.36;  // hiệu chỉnh

    i2c_lcd1602_clear(lcd);
    i2c_lcd1602_move_cursor(lcd, 0, 0);
    i2c_lcd1602_printf(lcd, "Current: %.2fmA", current);
}

// ------------------------- Resistance ------------------------------ //
void show_resistance()
{
    int total = 0;
    for(int i = 0; i < 100; i++) total += adc1_get_raw(ADC_RES_CH);

    float adc = total / 100.0;
    float Vout = adc * VCC / 4095.0;

    float Rx = Rref * ((Vout / (VCC - Vout)) * 1.1);

    i2c_lcd1602_clear(lcd);
    i2c_lcd1602_move_cursor(lcd, 0, 0);
    i2c_lcd1602_printf(lcd, "Resistance:");
    i2c_lcd1602_move_cursor(lcd, 0, 1);
    i2c_lcd1602_printf(lcd, "%.1f ohm", Rx);
}

// ================================================================= //

void app_main()
{
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);

    i2c_init();
    adc_init_all();

    lcd = i2c_lcd1602_init(I2C_PORT, LCD_ADDR, 16, 2);

    int last = 1;

    while (1)
    {
        int now = gpio_get_level(BUTTON_PIN);

        if(last == 1 && now == 0)
        {
            lcd_state++;
            if(lcd_state > 2) lcd_state = 0;
            vTaskDelay(200 / portTICK_PERIOD_MS);
        }

        last = now;

        if(lcd_state == 0) show_voltage();
        else if(lcd_state == 1) show_current();
        else if(lcd_state == 2) show_resistance();

        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}
