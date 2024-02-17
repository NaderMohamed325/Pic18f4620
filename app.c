#include "app.h"

// Global variables
volatile Std_ReturnType ret = E_OK;

// Function prototypes
void Application_initialize(void);
Led_t led = {
    .led_status = LED_OFF,
    .pin_index = PIN1,
    .port_index = PORTC_INDEX,
};
button_t b = {
    .button_active = BUTTON_ACTVE_HIGH,
    .button_state = BUTTON_RELEASED,
    .pin_config.direction = GPIO_INPUT,
    .pin_config.logic = GPIO_LOW,
    .pin_config.pin = PIN0,
    .pin_config.port = PORTC_INDEX,
};

void f(void) {
    ret = led_toggle_status(&led);
}

interrupt_RBx_t r = {
    .Priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.pin = PIN7,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.logic = GPIO_LOW,
    .mcu_pin.direction = GPIO_INPUT,
    .External_CallBack_High = f,
    .External_CallBack_Low = NULL,
};
volatile button_state_t s = BUTTON_RELEASED;

int main(void) {
    // Initialize the application
    Application_initialize();

    while (1) {
        ret = button_read_state(&b, &s);
    }
 
    return 0;
}

void Application_initialize(void) {
    ecu_layer_initialize();
    ret = led_intialize(&led);
    ret = Interrupt_RBx_Init(&r);
    ret = button_intialize(&b);
}
