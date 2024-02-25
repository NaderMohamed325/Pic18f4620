#include "app.h"

// Global variables
Std_ReturnType ret = E_OK;

// Function prototypes
void Application_initialize(void);

int main(void) {
    // Initialize the application
    Application_initialize();

    while (1) {
      
    }

    return 0;
}

void Application_initialize(void) {
    ecu_layer_initialize();

}