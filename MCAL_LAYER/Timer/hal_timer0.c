#include "hal_timer0.h"

// Declare a pointer to a function for Timer0 interrupt handling
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*Timer0_Interrupt_Handler)(void) = NULL;
#endif

// Inline function to configure Timer0 prescaler
static inline void Timer0_Prescaler_Config(timer0_t const *timer);
static inline void Timer0_Mode_Config(timer0_t const *timer);
static inline void Timer0_Reg_Size_Config(timer0_t const *timer);



// Function to initialize Timer0

Std_ReturnType Timer0_Init(timer0_t const *timer) {
    Std_ReturnType ret = E_OK;

    // Check if the input pointer is NULL
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        // Turn off Timer0 module
        TIMER0_MODULE_OFF();

        // Configure Timer0 prescaler
        Timer0_Prescaler_Config(timer);
        Timer0_Mode_Config(timer);
        Timer0_Reg_Size_Config(timer);
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        // Enable Timer0 interrupt and global interrupts
        TIMER0_InterruptEnable();
        // Clear Timer0 interrupt flag and set the interrupt handler
        TIMER0_InterruptFlagClear();
        Timer0_Interrupt_Handler = timer->Timer0_Interrupt_Handler;


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        if (INTERRUPT_HIGH_PRIORITY == timer->priority) {
            TIMER0_HighPrioritySet();
            INTERRUPT_Global_Interrupt_High_Enable();
        } else if (INTERRUPT_LOW_PRIORITY == timer->priority) {
            TIMER0_LowPrioritySet();
            INTERRUPT_Global_Interrupt_Low_Enable();
        }
#else
        INTERRUPT_Global_Interrupt_Enable();
        INTERRUPT_Peripheral_Interrupt_Enable();
#endif
#endif

        // Turn on Timer0 module
        TIMER0_MODULE_ON();
    }

    return ret;
}

// Function to deinitialize Timer0

Std_ReturnType Timer0_DeInit(timer0_t const *timer) {
    Std_ReturnType ret = E_OK;

    // Check if the input pointer is NULL
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        // Additional deinitialization steps for Timer0 interrupts, if needed
#endif
    }

    return ret;
}

// Function to write a value to Timer0

Std_ReturnType Timer0_Write_Value(timer0_t const *timer, uint16 value) {
    Std_ReturnType ret = E_OK;

    // Check if the input pointer is NULL
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        // Additional steps for writing a value to Timer0, if needed
    }

    return ret;
}

// Function to read the value from Timer0

Std_ReturnType Timer0_Read_Value(timer0_t const *timer, uint16 *value) {
    Std_ReturnType ret = E_OK;

    // Check if the input pointers are NULL
    if (NULL == timer || NULL == value) {
        ret = E_NOT_OK;
    } else {
        // Additional steps for reading the value from Timer0, if needed
    }

    return ret;
}

// Timer0 Interrupt Service Routine (ISR)

void TIMER0_ISR(void) {
    // Clear Timer0 interrupt flag
    TIMER0_InterruptFlagClear();

    // Check if there is a valid interrupt handler and call it
    if (Timer0_Interrupt_Handler) {
        Timer0_Interrupt_Handler();
    }
}

// Inline function to configure Timer0 prescaler

static inline void Timer0_Prescaler_Config(timer0_t const *timer) {
    // Check if Timer0 prescaler is enabled in the configuration
    if (TIMER0_PRESCALER_ENABLE_CFG == timer->prescaler_enable) {
        // Enable Timer0 prescaler and set the prescaler value
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = timer->prescaler_value;
    } else {
        // Disable Timer0 prescaler
        TIMER0_PRESCALER_DISABLE();
    }
}

static inline void Timer0_Mode_Config(timer0_t const *timer) {

    if (TIMER0_COUNTER_MODE == timer->timer0_mode) {
        TIMER0_COUNTER_MODE_ENABLE();
        if (timer->timer0_counter_edge == TIMER0_RISING_EDGE_CFG) {
            TIMER0_RISING_EDGE_ENABLE();
        } else if (timer->timer0_counter_edge == TIMER0_FALLING_EDGE_CFG) {
            TIMER0_FALLING_EDGE_ENABLE();
        }
    } else if (TIMER0_TIMER_MODE == timer->timer0_mode) {
        TIMER0_TIMER_MODE_ENABLE();
    }
}

static inline void Timer0_Reg_Size_Config(timer0_t const *timer) {
    if (TIMER0_8BIT_REGISTER_MODE == timer->timer0_register_size) {
        TIMER0_8BIT_REGISTER_MODE_ENABLE();
    } else if (TIMER0_16BIT_REGISTER_MODE == timer->timer0_register_size) {
        TIMER0_16BIT_REGISTER_MODE_ENABLE();
    }
}
