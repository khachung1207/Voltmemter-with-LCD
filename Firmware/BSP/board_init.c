#include "board_config.h"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "adc_read.h"

// Khởi tạo I2C
void board_init_i2c()
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_SDA_PIN,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_SCL_PIN,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000
    };
    i2c_param_config(I2C_PORT, &conf);
    i2c_driver_install(I2C_PORT, I2C_MODE_MASTER, 0, 0, 0);
}

// Khởi tạo nút nhấn
void board_init_button()
{
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);
}

// Khởi tạo ADC
void board_init_adc()
{
    adc_init_all();
}

// Hàm khởi tạo toàn board
void board_init()
{
    board_init_i2c();
    board_init_button();
    board_init_adc();
}
