/* 
 * File:   hal_timer2.h
 * Author: xcite
 *
 * Created on March 8, 2024, 8:04 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/*----------------INCLUDES-------------------*/
#include "../../MCAL_LAYER/Interrupt/mcal_internal_interrupt.h"

/*-----------------MACROS--------------------*/



/*--------------MACROS_FUNCTIONS-----------*/

// Macro for selecting prescaler and postscaler
#define TIMER2_PRESCALER_SELECT(_X_)           (T2CONbits.T2CKPS=_X_)
#define TIMER2_POSTSCALER_SELECT(_X_)          (T2CONbits.TOUTPS=_X_)



// Macros to turn Timer1 module on/off
#define TIMER2_MODULE_ON()                     (T2CONbits.TMR2ON=1)
#define TIMER2_MODULE_OFF()                    (T2CONbits.TMR2ON=1)

/*------------DATA_TYPES-------------------*/
typedef enum {
    TIMER2_POST_SCALER_DIV_BY_1 = 0,
    TIMER2_POST_SCALER_DIV_BY_2,
    TIMER2_POST_SCALER_DIV_BY_3,
    TIMER2_POST_SCALER_DIV_BY_4,
    TIMER2_POST_SCALER_DIV_BY_5,
    TIMER2_POST_SCALER_DIV_BY_6,
    TIMER2_POST_SCALER_DIV_BY_7,
    TIMER2_POST_SCALER_DIV_BY_8,
    TIMER2_POST_SCALER_DIV_BY_9,
    TIMER2_POST_SCALER_DIV_BY_10,
    TIMER2_POST_SCALER_DIV_BY_11,
    TIMER2_POST_SCALER_DIV_BY_12,
    TIMER2_POST_SCALER_DIV_BY_13,
    TIMER2_POST_SCALER_DIV_BY_14,
    TIMER2_POST_SCALER_DIV_BY_15,
    TIMER2_POST_SCALER_DIV_BY_16,
} timer2_post_scaler_t;

typedef enum {
    TIMER2_PRE_SCALER_DIV_BY_1 = 0,
    TIMER2_PRE_SCALER_DIV_BY_4,
    TIMER2_PRE_SCALER_DIV_BY_16,
} timer2_pre_scaler_t;

typedef struct {
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    // Function pointer for Timer2 interrupt handler
    void (*Timer2_Interrupt_Handler)(void);
    // Interrupt priority configuration
    interrupt_priority_cfg priority;
#endif
    uint8 timer2_preload_value;
    timer2_pre_scaler_t timer2_prescaler_value;
    timer2_post_scaler_t timer2_postscaler_value;

} timer2_t;


/*------------FUNCTIONS_DECLARATION--------*/

// Function to initialize Timer2
Std_ReturnType Timer2_Init(timer2_t const *timer);

// Function to deinitialize Timer2
Std_ReturnType Timer2_DeInit(timer2_t const *timer);

// Function to write a value to Timer2
Std_ReturnType Timer2_Write_Value(timer2_t const *timer, uint8 value);

// Function to read the current value of Timer2
Std_ReturnType Timer2_Read_Value(timer2_t const *timer, uint8 *value);


#endif	/* HAL_TIMER2_H */

