#include "app.h"

// Global variables
Std_ReturnType ret = E_OK;

// Function prototypes
void Application_initialize(void);


// ISR (Interrupt Service Routine) function
volatile uint16 val = 0;
Led_t led = {
    .led_status = LED_OFF,
    .pin_index = PIN0,
    .port_index = PORTC_INDEX,
};

void Isr(void) {
    led_toggle_status(&led);
}



timer1_t timer1 = {
    .Timer1_Interrupt_Handler = Isr,
    .prescaler_value = TIMER1_PRESCALER_DIV_BY_8,
    .timer1_mode = TIMER1_TIMER_MODE,
    .timer1_osc_cfg = TIMER1_OSC_DISABLE,
    .timer1_preload_value = 3036,
    .timer1_rw_reg_mode = TIMER1_RW_REG_MODE_16BIT,
};

int main(void) {

    Application_initialize();

    while (1) {


    }

    return 0;
}

void Application_initialize(void) {
    // Initialize ECU (Electronic Control Unit) layer
    ecu_layer_initialize();
    Timer1_Init(&timer1);
    led_intialize(&led);
}
