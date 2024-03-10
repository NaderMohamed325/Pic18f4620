/* 
 * File:   hal_timer3.c
 * Author: xcite
 *
 * Created on March 8, 2024, 8:04 PM
 */
#include "hal_timer3.h"



// Declare a pointer to a function for Timer1 interrupt handling
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*Timer3_Interrupt_Handler)(void) = NULL;
#endif

// Function to configure Timer1 mode based on the provided timer configuration
static inline void Timer3_Mode_Config(timer3_t const *timer);

// Variable to store the preload value for pre-calculation
static uint16 pre_work_out = 0;


// Function to initialize Timer3

Std_ReturnType Timer3_Init(timer3_t const *timer) {
    Std_ReturnType ret = E_NOT_OK;

    // Check if the timer configuration is not NULL
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        // Turn off Timer1 module
        TIMER3_MODULE_OFF();

        // Configure Timer1 mode based on the provided timer configuration
        Timer3_Mode_Config(timer);

        // Select Timer1 prescaler
        TIMER3_PRESCALER_SELECT(timer->prescaler_value);

        // Set the high and low bytes of the preload value
        TMR3H = (timer->timer3_preload_value) >> 8;
        TMR3L = (uint8) (timer->timer3_preload_value);

#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        // Enable Timer3 interrupt and configure interrupt handling
        TIMER3_InterruptEnable();
        TIMER3_InterruptFlagClear();
        Timer3_Interrupt_Handler = timer->Timer3_Interrupt_Handler;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        // Configure interrupt priority levels
        INTERRUPT_PRIORITY_LEVELS_ENABLE();
        if (INTERRUPT_HIGH_PRIORITY == timer->priority) {
            TIMER3_HighPrioritySet();
            INTERRUPT_Global_Interrupt_High_Enable();
        } else if (INTERRUPT_LOW_PRIORITY == timer->priority) {
            TIMER3_LowPrioritySet();
            INTERRUPT_Global_Interrupt_Low_Enable();
        }
#else
        // Enable global and peripheral interrupts
        INTERRUPT_Global_Interrupt_Enable();
        INTERRUPT_Peripheral_Interrupt_Enable();
#endif
#endif
        // Turn on Timer3 module
        TIMER3_MODULE_ON();

        ret = E_OK;
    }
    return ret;
}

// Function to deinitialize Timer3

Std_ReturnType Timer3_DeInit(timer3_t const *timer) {
    Std_ReturnType ret = E_NOT_OK;
    // Check if the timer configuration is not NULL
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        // Perform deinitialization steps (if any)
        TIMER3_MODULE_OFF();
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptDisable();
#endif

        ret = E_OK;
    }
    return ret;
}

// Function to write a value to Timer3

Std_ReturnType Timer3_Write_Value(timer3_t const *timer, uint16 value) {
    Std_ReturnType ret = E_NOT_OK;
    // Check if the timer configuration is not NULL
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
  // Write the value to Timer3 registers
        TMR3H = (value) >> 8;
        TMR3L = (uint8) (value);
        ret = E_OK;
    }
    return ret;
}

// Function to read the current value of Timer3

Std_ReturnType Timer3_Read_Value(timer3_t const *timer, uint16 *value) {
      Std_ReturnType ret = E_NOT_OK;
 uint8 l_tmr3l = 0, l_tmr3h = 0;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        l_tmr3l = TMR3L;
        l_tmr3h = TMR3H;
        *value = (uint16)((l_tmr3h << 8) + l_tmr3l);
        ret = E_OK;
    }
    return ret;
}

static inline void Timer3_Mode_Config(timer3_t const *timer) {
 // Check if Timer3 is in counter mode
    if (TIMER3_COUNTER_MODE == timer->timer3_mode) {
        TIMER3_COUNTER_MODE_ENABLE();

        // Check if Timer3 is in asynchronous or synchronous counter mode
        if (TIMER3_ASYNC_COUNTER_MODE == timer->counter_mode) {
            TIMER3_ASYNC_COUNTER_MODE_ENABLE();
        } else if (TIMER3_SYNC_COUNTER_MODE == timer->counter_mode) {
            TIMER3_SYNC_COUNTER_MODE_ENABLE();
        }

    } else if (TIMER3_TIMER_MODE == timer->timer3_mode) {
        // Timer3 is in timer mode
        TIMER3_TIMER_MODE_ENABLE();
    }
}
/**
 * @brief   Timer3 Interrupt Service Routine (ISR).
 * @details This ISR is called when Timer1 interrupt occurs.
 */
void TIMER3_ISR(void) {
    // Clear Timer1 interrupt flag
    TIMER3_InterruptFlagClear();
    TMR3H = (pre_work_out) >> 8;
    TMR3L = (uint8) (pre_work_out);
    // Check if there is a valid interrupt handler and call it
    if (Timer3_Interrupt_Handler) {
        Timer3_Interrupt_Handler();
    }
}
