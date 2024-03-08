#include "hal_timer0.h"

// Declare a pointer to a function for Timer0 interrupt handling
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*Timer0_Interrupt_Handler)(void) = NULL;
#endif

// Inline function to configure Timer0 prescaler
static inline void Timer0_Prescaler_Config(timer0_t const *timer);
static inline void Timer0_Mode_Config(timer0_t const *timer);
static inline void Timer0_Reg_Size_Config(timer0_t const *timer);
static uint16 pre_work_out = 0;

/**
 * @brief   Initialize Timer0 module.
 * @details This function initializes the Timer0 module based on the provided configuration.
 * @param   timer: Pointer to the Timer0 configuration structure.
 * @return  Returns E_OK if initialization is successful, otherwise returns E_NOT_OK.
 */
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
        TMR0H = (timer->timer0_preload_value) >> 8;
        TMR0L = (uint8) (timer->timer0_preload_value);
        pre_work_out = timer->timer0_preload_value;

        // Enable Timer0 interrupt and configure interrupt settings
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptEnable();
        TIMER0_InterruptFlagClear();
        Timer0_Interrupt_Handler = timer->Timer0_Interrupt_Handler;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        // Configure interrupt priority levels
        INTERRUPT_PRIORITY_LEVELS_ENABLE();
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

/**
 * @brief   Deinitialize Timer0 module.
 * @details This function deinitializes the Timer0 module based on the provided configuration.
 * @param   timer: Pointer to the Timer0 configuration structure.
 * @return  Returns E_OK if deinitialization is successful, otherwise returns E_NOT_OK.
 */
Std_ReturnType Timer0_DeInit(timer0_t const *timer) {
    Std_ReturnType ret = E_OK;

    // Check if the input pointer is NULL
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        TIMER0_MODULE_OFF();
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptDisable();
#endif
    }

    return ret;
}

/**
 * @brief   Write a value to Timer0.
 * @details This function writes a 16-bit value to Timer0 registers.
 * @param   timer: Pointer to the Timer0 configuration structure.
 * @param   value: The value to be written to Timer0.
 * @return  Returns E_OK if writing is successful, otherwise returns E_NOT_OK.
 */
Std_ReturnType Timer0_Write_Value(timer0_t const *timer, uint16 value) {
    Std_ReturnType ret = E_OK;

    // Check if the input pointer is NULL
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        // Write the value to Timer0 registers
        TMR0H = (value) >> 8;
        TMR0L = (uint8) (value);
    }

    return ret;
}

/**
 * @brief   Read the value from Timer0.
 * @details This function reads a 16-bit value from Timer0 registers.
 * @param   timer: Pointer to the Timer0 configuration structure.
 * @param   value: Pointer to store the read value.
 * @return  Returns E_OK if reading is successful, otherwise returns E_NOT_OK.
 */
Std_ReturnType Timer0_Read_Value(timer0_t const *timer, uint16 *value) {
     Std_ReturnType ret = E_NOT_OK;
    uint8 l_tmr0l = 0, l_tmr0h = 0;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        l_tmr0l = TMR0L;
        l_tmr0h = TMR0H;
        *value = (uint16)((l_tmr0h << 8) + l_tmr0l);
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief   Timer0 Interrupt Service Routine (ISR).
 * @details This ISR is called when Timer0 interrupt occurs.
 */
void TIMER0_ISR(void) {
    // Clear Timer0 interrupt flag
    TIMER0_InterruptFlagClear();
    TMR0H = (pre_work_out) >> 8;
    TMR0L = (uint8) (pre_work_out);
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

// Inline function to configure Timer0 mode

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

// Inline function to configure Timer0 register size

static inline void Timer0_Reg_Size_Config(timer0_t const *timer) {
    if (TIMER0_8BIT_REGISTER_MODE == timer->timer0_register_size) {
        TIMER0_8BIT_REGISTER_MODE_ENABLE();
    } else if (TIMER0_16BIT_REGISTER_MODE == timer->timer0_register_size) {
        TIMER0_16BIT_REGISTER_MODE_ENABLE();
    }
}
