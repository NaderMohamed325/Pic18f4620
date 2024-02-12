
/* 
 * File:   ecu_layer_init.c
 * Author: xcite
 *
 * Created on January 6, 2024, 1:13 AM
 */
#include "ecu_layer_init.h"
/*
Led_t led = {
    .led_status = LED_OFF,
    .pin_index = PIN4,
    .port_index = PORTC_INDEX,
};*/
lcd_4bit_mode lcd = {
    .lcd_en.direction = GPIO_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .lcd_en.pin = PIN0,
    .lcd_en.port = PORTD_INDEX,

    .lcd_rs.direction = GPIO_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_rs.pin = PIN1,
    .lcd_rs.port = PORTD_INDEX,

    .lcd_data[0].direction = GPIO_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[0].pin = PIN2,
    .lcd_data[0].port = PORTD_INDEX,

    .lcd_data[1].direction = GPIO_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[1].pin = PIN3,
    .lcd_data[1].port = PORTD_INDEX,

    .lcd_data[2].direction = GPIO_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[2].pin = PIN4,
    .lcd_data[2].port = PORTD_INDEX,

    .lcd_data[3].direction = GPIO_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW,
    .lcd_data[3].pin = PIN5,
    .lcd_data[3].port = PORTD_INDEX,
};
Seven_Segment_t segment_10 = {
    .Seg_Type = SEVEN_SEG_TYPE_CATHOD,
    .segment_pins[0].direction = GPIO_OUTPUT,
    .segment_pins[0].logic = GPIO_LOW,
    .segment_pins[0].pin = PIN0,
    .segment_pins[0].port = PORTC_INDEX,


    .segment_pins[1].direction = GPIO_OUTPUT,
    .segment_pins[1].logic = GPIO_LOW,
    .segment_pins[1].pin = PIN1,
    .segment_pins[1].port = PORTC_INDEX,

    .segment_pins[2].direction = GPIO_OUTPUT,
    .segment_pins[2].logic = GPIO_LOW,
    .segment_pins[2].pin = PIN2,
    .segment_pins[2].port = PORTC_INDEX,


    .segment_pins[3].direction = GPIO_OUTPUT,
    .segment_pins[3].logic = GPIO_LOW,
    .segment_pins[3].pin = PIN3,
    .segment_pins[3].port = PORTC_INDEX,
};
Seven_Segment_t segment = {
    .Seg_Type = SEVEN_SEG_TYPE_CATHOD,
    .segment_pins[0].direction = GPIO_OUTPUT,
    .segment_pins[0].logic = GPIO_LOW,
    .segment_pins[0].pin = PIN0,
    .segment_pins[0].port = PORTA_INDEX,


    .segment_pins[1].direction = GPIO_OUTPUT,
    .segment_pins[1].logic = GPIO_LOW,
    .segment_pins[1].pin = PIN1,
    .segment_pins[1].port = PORTA_INDEX,

    .segment_pins[2].direction = GPIO_OUTPUT,
    .segment_pins[2].logic = GPIO_LOW,
    .segment_pins[2].pin = PIN2,
    .segment_pins[2].port = PORTA_INDEX,


    .segment_pins[3].direction = GPIO_OUTPUT,
    .segment_pins[3].logic = GPIO_LOW,
    .segment_pins[3].pin = PIN3,
    .segment_pins[3].port = PORTA_INDEX,
};

void ecu_layer_initailize(void) {
    Std_ReturnType ret = E_OK;

    ret = Seven_Segm_initailize(&segment);
    ret = Seven_Segm_initailize(&segment_10);
    //ret = led_intialize(&led);
    ret = lcd_4bit_initailize(&lcd);
    
}
