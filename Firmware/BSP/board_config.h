#pragma once
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "driver/adc.h"

// ---- BUTTON PIN ----
#define BUTTON_PIN GPIO_NUM_4   // hoặc chân bạn chọn

// ---- I2C PINS ----
#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22

// ---- ADC Channels ----
#define VOLTAGE_ADC_CH   ADC1_CHANNEL_3
#define CURRENT_ADC_CH   ADC1_CHANNEL_5
#define RESIST_ADC_CH    ADC1_CHANNEL_7

// ---- I2C PORT ----
#define I2C_PORT I2C_NUM_0
