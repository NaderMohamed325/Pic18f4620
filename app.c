#include "app.h"

// Global variables
Std_ReturnType ret = E_OK;

// Function prototypes
void Application_initialize(void);


// ISR (Interrupt Service Routine) function

void Isr(void) {

}



int main(void) {
    // Initialize the application
    Application_initialize();

    while (1) {
      
    }

    return 0;
}

void Application_initialize(void) {
    // Initialize ECU (Electronic Control Unit) layer
    ecu_layer_initialize();

    // Initialize Timer0

}
