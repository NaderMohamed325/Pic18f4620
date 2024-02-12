#include "app.h"

// Global variables
Std_ReturnType ret = E_OK;


// Function prototypes
void Application_initialize(void);


int main(void) {
    // Initialize the application
    Application_initialize();
 

    while (1) {
        // Your main application logic here
    }

    return 0;
}

// Function to initialize the application

void Application_initialize(void) {
    ecu_layer_initialize();


}


