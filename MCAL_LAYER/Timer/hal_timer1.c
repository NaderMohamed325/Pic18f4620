#include "hal_timer1.h"

// Declare a pointer to a function for Timer1 interrupt handling
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*Timer1_Interrupt_Handler)(void) = NULL;
#endif

// Function to configure Timer1 mode based on the provided timer configuration
static inline void Timer1_Mode_Config(timer1_t const *timer);

// Variable to store the preload value for pre-calculation
static uint16 pre_work_out = 0;

// Function to initialize Timer1

Std_ReturnType Timer1_Init(timer1_t const *timer) {
    // Store the preload value for pre-calculation
    pre_work_out = timer->timer1_preload_value;
    Std_ReturnType ret = E_NOT_OK;

    // Check if the timer configuration is not NULL
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        // Turn off Timer1 module
        TIMER1_MODULE_OFF();

        // Configure Timer1 mode based on the provided timer configuration
        Timer1_Mode_Config(timer);

        // Select Timer1 prescaler
        TIMER1_PRESCALER_SELECT(timer->prescaler_value);

        // Set the high and low bytes of the preload value
        TMR1H = (timer->timer1_preload_value) >> 8;
        TMR1L = (uint8) (timer->timer1_preload_value);

#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        // Enable Timer1 interrupt and configure interrupt handling
        TIMER1_InterruptEnable();
        TIMER1_InterruptFlagClear();
        Timer1_Interrupt_Handler = timer->Timer1_Interrupt_Handler;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        // Configure interrupt priority levels
        INTERRUPT_PRIORITY_LEVELS_ENABLE();
        if (INTERRUPT_HIGH_PRIORITY == timer->priority) {
            TIMER1_HighPrioritySet();
            INTERRUPT_Global_Interrupt_High_Enable();
        } else if (INTERRUPT_LOW_PRIORITY == timer->priority) {
            TIMER1_LowPrioritySet();
            INTERRUPT_Global_Interrupt_Low_Enable();
        }
#else
        // Enable global and peripheral interrupts
        INTERRUPT_Global_Interrupt_Enable();
        INTERRUPT_Peripheral_Interrupt_Enable();
#endif
#endif
        // Turn on Timer1 module
        TIMER1_MODULE_ON();
        ret = E_OK;
    }
    return ret;
}

// Function to deinitialize Timer1

Std_ReturnType Timer1_DeInit(timer1_t const *timer) {
    Std_ReturnType ret = E_NOT_OK;

    // Check if the timer configuration is not NULL
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        // Perform deinitialization steps (if any)
        TIMER1_MODULE_OFF();
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER1_InterruptDisable();
#endif
        ret = E_OK;
    }
    return ret;
}

// Function to write a value to Timer1

Std_ReturnType Timer1_Write_Value(timer1_t const *timer, uint16 value) {
    Std_ReturnType ret = E_NOT_OK;

    // Check if the timer configuration is not NULL
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {

        // Write the value to Timer0 registers
        TMR1H = (value) >> 8;
        TMR1L = (uint8) (value);
        ret = E_OK;
    }
    return ret;
}

// Function to read the current value of Timer1

Std_ReturnType Timer1_Read_Value(timer1_t const *timer, uint16 *value) {
    Std_ReturnType ret = E_NOT_OK;
 uint8 l_tmr1l = 0, l_tmr1h = 0;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        l_tmr1l = TMR1L;
        l_tmr1h = TMR1H;
        *value = (uint16)((l_tmr1h << 8) + l_tmr1l);
        ret = E_OK;
    }
    return ret;
}

// Function to configure Timer1 mode based on the provided timer configuration

static inline void Timer1_Mode_Config(timer1_t const *timer) {
    // Check if Timer1 is in counter mode
    if (TIMER1_COUNTER_MODE == timer->timer1_mode) {
        TIMER1_COUNTER_MODE_ENABLE();

        // Check if Timer1 is in asynchronous or synchronous counter mode
        if (TIMER1_ASYNC_COUNTER_MODE == timer->counter_mode) {
            TIMER1_ASYNC_COUNTER_MODE_ENABLE();
        } else if (TIMER1_SYNC_COUNTER_MODE == timer->counter_mode) {
            TIMER1_SYNC_COUNTER_MODE_ENABLE();
        }

    } else if (TIMER1_TIMER_MODE == timer->timer1_mode) {
        // Timer1 is in timer mode
        TIMER1_TIMER_MODE_ENABLE();
    }
}
/**
 * @brief   Timer1 Interrupt Service Routine (ISR).
 * @details This ISR is called when Timer1 interrupt occurs.
 */
void TIMER1_ISR(void) {
    // Clear Timer1 interrupt flag
    TIMER1_InterruptFlagClear();
    TMR1H = (pre_work_out) >> 8;
    TMR1L = (uint8) (pre_work_out);
    // Check if there is a valid interrupt handler and call it
    if (Timer1_Interrupt_Handler) {
        Timer1_Interrupt_Handler();
    }
}
