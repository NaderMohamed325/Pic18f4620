#include "app.h"

// Global variables
Std_ReturnType ret = E_OK;

// Function prototypes
void Application_initialize(void);
volatile uint16 freq = 0;

// ISR (Interrupt Service Routine) function

void Isr(void) {

}

// Timer0 configuration structure
timer0_t timer = {
    .Timer0_Interrupt_Handler = Isr,
    .timer0_counter_edge = TIMER0_RISING_EDGE_CFG,
    .timer0_register_size = TIMER0_16BIT_REGISTER_MODE,
    .timer0_mode = TIMER0_COUNTER_MODE
};

int main(void) {
    // Initialize the application
    Application_initialize();

    while (1) {
        // Read the current value of Timer0
        Timer0_Read_Value(&timer, &freq);
          Timer0_Write_Value(&timer, 0);
        __delay_ms(1000);
      
    }

    return 0;
}

void Application_initialize(void) {
    // Initialize ECU (Electronic Control Unit) layer
    ecu_layer_initialize();

    // Initialize Timer0
    Timer0_Init(&timer);
}
