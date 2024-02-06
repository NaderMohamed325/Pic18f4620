#include "app.h"


// Global variables
Std_ReturnType ret = E_OK;


// Function prototypes
void Application_initialize(void);
void reset() {
    // Perform a software reset by jumping to the reset vector
    asm("goto 0x00");
}

Led_t led0 = {
    .led_status = LED_OFF,
    .port_index = PORTC_INDEX,
    .pin_index = PIN0,
};
Led_t led1 = {
    .led_status = LED_ON,
    .port_index = PORTC_INDEX,
    .pin_index = PIN1,
};
Led_t led2 = {
    .led_status = LED_OFF,
    .port_index = PORTC_INDEX,
    .pin_index = PIN2,
};
Led_t led3 = {
    .led_status = LED_OFF,
    .port_index = PORTC_INDEX,
    .pin_index = PIN3,
};

void High(void) {
    ret=led_toggle_status(&led0);

};

void Low(void) {
 ret=led_toggle_status(&led1);

};
interrupt_RBx_t rb = {
    .External_CallBack_High = High,
    .External_CallBack_Low = Low,
    .Priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.direction = GPIO_INPUT,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = PIN4,
};
//nader 

int main(void) {
    // Initialize the application
    ret = led_intialize(&led0);
    ret = led_intialize(&led1);
    ret = led_intialize(&led2);
    ret = Interrupt_RBx_Init(&rb);
    Application_initialize();
    while (1) {

    }

    return 0;
}
// Function to initialize the application

void Application_initialize(void) {
    ecu_layer_initailize();
}
