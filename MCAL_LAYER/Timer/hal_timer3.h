/* 
 * File:   hal_timer3.h
 * Author: xcite
 *
 * Created on March 8, 2024, 8:06 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H


/*----------------INCLUDES-------------------*/
#include "../../MCAL_LAYER/Interrupt/mcal_internal_interrupt.h"

/*-----------------MACROS--------------------*/

// Timer modes
#define TIMER3_TIMER_MODE              1    
#define TIMER3_COUNTER_MODE            0    

// Counter modes
#define TIMER3_ASYNC_COUNTER_MODE      1  
#define TIMER3_SYNC_COUNTER_MODE       0   

// Read/Write register modes
#define TIMER3_RW_REG_MODE_8BIT        0
#define TIMER3_RW_REG_MODE_16BIT       1

/*--------------MACROS_FUNCTIONS-----------*/
// Macros to turn Timer3 module on/off
#define TIMER3_MODULE_ON()                     (T3CONbits.TMR3ON=1)
#define TIMER3_MODULE_OFF()                    (T3CONbits.TMR3ON=0)

// Macros to select Timer0 mode (Timer/Counter)
#define TIMER3_TIMER_MODE_ENABLE()             (T3CONbits.TMR3CS=0)
#define TIMER3_COUNTER_MODE_ENABLE()           (T3CONbits.TMR3CS=1)

// Macros for counter mode selection
#define TIMER3_ASYNC_COUNTER_MODE_ENABLE()     (T3CONbits.T3SYNC=1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()      (T3CONbits.T3SYNC=0)

// Macro for selecting prescaler
#define TIMER3_PRESCALER_SELECT(_X_)           (T3CONbits.T3CKPS=_X_)

// Macros for selecting register mode (8-bit or 16-bit)
#define TIMER3_RW_REG_MODE_16BIT_ENABLE()      (T3CONbits.RD16=1)
#define TIMER3_RW_REG_MODE_8BIT_ENABLE()       (T3CONbits.RD16=0)
/*------------DATA_TYPES-------------------*/


typedef enum {
    TIMER3_PRESCALER_DIV_BY_1 = 0,
    TIMER3_PRESCALER_DIV_BY_2,
    TIMER3_PRESCALER_DIV_BY_4,
    TIMER3_PRESCALER_DIV_BY_8,
} timer3_prescaler_select_t;

typedef struct {
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    // Function pointer for Timer3 interrupt handler
    void (*Timer3_Interrupt_Handler)(void);
    // Interrupt priority configuration
    interrupt_priority_cfg priority;
#endif
    // Timer configuration parameters
    timer3_prescaler_select_t prescaler_value;
    uint16 timer3_preload_value;
    uint8 timer3_mode : 1;
    uint8 counter_mode : 1;
    uint8 timer3_rw_reg_mode : 1;
} timer3_t;

/*------------FUNCTIONS_DECLARATION--------*/


// Function to initialize Timer3
Std_ReturnType Timer3_Init(timer3_t const *timer);

// Function to deinitialize Timer3
Std_ReturnType Timer3_DeInit(timer3_t const *timer);

// Function to write a value to Timer3
Std_ReturnType Timer3_Write_Value(timer3_t const *timer, uint16 value);

// Function to read the current value of Timer3
Std_ReturnType Timer3_Read_Value(timer3_t const *timer, uint16 *value);

#endif	/* HAL_TIMER3_H */

