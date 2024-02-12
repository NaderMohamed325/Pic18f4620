#include "app.h"


// Global variables
Std_ReturnType ret = E_OK;


// Function prototypes
void Application_initialize(void);

uint8 timer = 0;
void timer_increment(void);
interrupt_INTx_t clock = {
    .Edge = INTERRUPT_RISING_EDGE,
    .Priority = INTERRUPT_HIGH_PRIORITY,
    .Source = INTERRUPT_EXTERNAL_INT0,
    .mcu_pin.direction = GPIO_INPUT,
    .mcu_pin.logic = GPIO_LOW,
    .mcu_pin.pin = PIN0,
    .mcu_pin.port = PORTB_INDEX,
    .External_CallBack = timer_increment,
};

int main(void) {
    // Initialize the application

    Application_initialize();
    while (1) {
        ret = Seven_Segm_Display_Number(&segment, timer/10);
        ret = Seven_Segm_Display_Number(&segment_10, timer%10);
    }

    return 0;
}
// Function to initialize the application

void Application_initialize(void) {
    ecu_layer_initailize();
    ret = Interrupt_INTx_Init(&clock);
}

void timer_increment(void) {
    timer++;
    ret = led_toggle_status(&led);
}