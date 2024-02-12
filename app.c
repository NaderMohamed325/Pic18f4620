#include "app.h"


// Global variables
Std_ReturnType ret = E_OK;

uint8 p1 = 2;
uint8 p2 = 2;


// Function prototypes
void Application_initialize(void);

void p1_mod_inc(void) {
    if (p1 < 4) {
        p1++;
    }
};

void p1_mod_dec(void) {
    if (p1 > 0) {
        p1--;
    }
};

void p2_mod_inc(void) {
    if (p2 < 4) {
        p2++;
    }
};

void p2_mod_dec(void) {
    if (p2 > 0) {
        p2--;
    }
};


uint8 timer = 0;
void timer_increment(void);
void res(void);
interrupt_INTx_t clock = {
    .Edge = INTERRUPT_RISING_EDGE,
    .Priority = INTERRUPT_HIGH_PRIORITY,
    .Source = INTERRUPT_EXTERNAL_INT1,
    .mcu_pin.direction = GPIO_INPUT,
    .mcu_pin.logic = GPIO_LOW,
    .mcu_pin.pin = PIN0,
    .mcu_pin.port = PORTB_INDEX,
    .External_CallBack = timer_increment,
};
interrupt_INTx_t re = {
    .Edge = INTERRUPT_RISING_EDGE,
    .Priority = INTERRUPT_HIGH_PRIORITY,
    .Source = INTERRUPT_EXTERNAL_INT0,
    .mcu_pin.direction = GPIO_INPUT,
    .mcu_pin.logic = GPIO_LOW,
    .mcu_pin.pin = PIN1,
    .mcu_pin.port = PORTB_INDEX,
    .External_CallBack = res,
};
interrupt_RBx_t p1_up = {
    .External_CallBack_Low = p1_mod_inc,
    .External_CallBack_High = NULL,
    .Priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.direction = GPIO_INPUT,
    .mcu_pin.logic = GPIO_LOW,
    .mcu_pin.pin = PIN4,
    .mcu_pin.port = PORTB_INDEX,
};
interrupt_RBx_t p1_down = {
    .External_CallBack_Low = p1_mod_dec,
    .External_CallBack_High = NULL,
    .Priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.direction = GPIO_INPUT,
    .mcu_pin.logic = GPIO_LOW,
    .mcu_pin.pin = PIN5,
    .mcu_pin.port = PORTB_INDEX,
};
interrupt_RBx_t p2_up = {
    .External_CallBack_Low = p2_mod_inc,
    .External_CallBack_High = NULL,
    .Priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.direction = GPIO_INPUT,
    .mcu_pin.logic = GPIO_LOW,
    .mcu_pin.pin = PIN6,
    .mcu_pin.port = PORTB_INDEX,
};
interrupt_RBx_t p2_down = {
    .External_CallBack_Low = p2_mod_dec,
    .External_CallBack_High = NULL,
    .Priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.direction = GPIO_INPUT,
    .mcu_pin.logic = GPIO_LOW,
    .mcu_pin.pin = PIN7,
    .mcu_pin.port = PORTB_INDEX,
};

int main(void) {
    // Initialize the application

    Application_initialize();
    ret = lcd_4bit_send_char_data_pos(&lcd, p1, 1, '|');
    ret = lcd_4bit_send_char_data_pos(&lcd, p2, 20, '|');
    while (1) {

    }

    return 0;
}
// Function to initialize the application

void Application_initialize(void) {
    ecu_layer_initailize();
    ret = Interrupt_INTx_Init(&clock);
    ret = Interrupt_INTx_Init(&re);
    ret = Interrupt_RBx_Init(&p1_down);
    ret = Interrupt_RBx_Init(&p2_down);
    ret = Interrupt_RBx_Init(&p1_up);
    ret = Interrupt_RBx_Init(&p2_up);

}

void timer_increment(void) {
    timer++;
    ret = Seven_Segm_Display_Number(&segment, timer / 10);
    ret = Seven_Segm_Display_Number(&segment_10, timer % 10);
}

void res(void) {
    Reset();
}

