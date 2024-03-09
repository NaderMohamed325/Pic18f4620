/* 
 * File:   hal_timer2.c
 * Author: xcite
 *
 * Created on March 8, 2024, 8:04 PM
 */


#include "hal_timer2.h"


#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*Timer2_Interrupt_Handler)(void) = NULL;
#endif

// Function to initialize Timer2
uint8 pre = 0;

Std_ReturnType Timer2_Init(timer2_t const *timer) {
    Std_ReturnType ret = E_NOT_OK;

    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        TIMER2_MODULE_OFF();
        TIMER2_PRESCALER_SELECT(timer->timer2_prescaler_value);
        TIMER2_POSTSCALER_SELECT(timer->timer2_postscaler_value);
        TMR2 = timer->timer2_preload_value;
        pre = timer->timer2_preload_value;
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        // Enable Timer2 interrupt and configure interrupt handling
        TIMER2_InterruptEnable();
        TIMER2_InterruptFlagClear();
        Timer2_Interrupt_Handler = timer->Timer2_Interrupt_Handler;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        // Configure interrupt priority levels
        INTERRUPT_PRIORITY_LEVELS_ENABLE();
        if (INTERRUPT_HIGH_PRIORITY == timer->priority) {
            TIMER2_HighPrioritySet();
            INTERRUPT_Global_Interrupt_High_Enable();
        } else if (INTERRUPT_LOW_PRIORITY == timer->priority) {
            TIMER2_LowPrioritySet();
            INTERRUPT_Global_Interrupt_Low_Enable();
        }
#else
        // Enable global and peripheral interrupts
        INTERRUPT_Global_Interrupt_Enable();
        INTERRUPT_Peripheral_Interrupt_Enable();
#endif
#endif
        TIMER2_MODULE_ON();
        ret = E_OK;
    }
    return ret;
}

// Function to deinitialize Timer2

Std_ReturnType Timer2_DeInit(timer2_t const *timer) {
    Std_ReturnType ret = E_NOT_OK;

    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        // Perform deinitialization steps (if any)
        TIMER2_MODULE_OFF();
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptDisable();
#endif
        ret = E_OK;
    }
    return ret;
}

// Function to write a value to Timer2

Std_ReturnType Timer2_Write_Value(timer2_t const *timer, uint8 value) {
    Std_ReturnType ret = E_NOT_OK;

    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        TMR2 = value;
        ret = E_OK;
    }
    return ret;
}

// Function to read the current value of Timer2

Std_ReturnType Timer2_Read_Value(timer2_t const *timer, uint8 *value) {
    Std_ReturnType ret = E_NOT_OK;

    if (NULL == timer || NULL == value) {
        ret = E_NOT_OK;
    } else {
        *value = TMR2;
        ret = E_OK;
    }
    return ret;


}

/**
 * @brief   Timer1 Interrupt Service Routine (ISR).
 * @details This ISR is called when Timer1 interrupt occurs.
 */
void TIMER2_ISR(void) {
    // Clear Timer2 interrupt flag
    TIMER2_InterruptFlagClear();
    TMR2 = pre;
    // Check if there is a valid interrupt handler and call it
    if (Timer2_Interrupt_Handler) {
        Timer2_Interrupt_Handler();
    }
}
