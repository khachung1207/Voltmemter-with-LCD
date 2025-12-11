idf_component_register(
    SRCS 
        "main.c"
        "adc_read.c"
        "lcd_i2c.c"
        "measure_voltage.c"
        "measure_current.c"
        "measure_resistance.c"
    INCLUDE_DIRS "../include"
)
