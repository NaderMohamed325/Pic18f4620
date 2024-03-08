/* 
 * File:   hal_timer1.h
 * Author: xcite
 *
 * Created on March 3, 2024, 12:03 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/*----------------INCLUDES-------------------*/
#include "../../MCAL_LAYER/Interrupt/mcal_internal_interrupt.h"

/*-----------------MACROS--------------------*/
// Timer modes
#define TIMER1_TIMER_MODE              1    
#define TIMER1_COUNTER_MODE            0    

// Counter modes
#define TIMER1_ASYNC_COUNTER_MODE      1  
#define TIMER1_SYNC_COUNTER_MODE       0   

// Oscillator control
#define TIMER1_OSC_ENABLE              1 
#define TIMER1_OSC_DISABLE             0 

// Read/Write register modes
#define TIMER1_RW_REG_MODE_8BIT        0
#define TIMER1_RW_REG_MODE_16BIT       1


/*--------------MACROS_FUNCTIONS-----------*/

// Macros to turn Timer1 module on/off
#define TIMER1_MODULE_ON()                     (T1CONbits.TMR1ON=1)
#define TIMER1_MODULE_OFF()                    (T1CONbits.TMR1ON=0)

// Macros to select Timer0 mode (Timer/Counter)
#define TIMER1_TIMER_MODE_ENABLE()             (T1CONbits.TMR1CS=0)
#define TIMER1_COUNTER_MODE_ENABLE()           (T1CONbits.TMR1CS=1)

// Macros for counter mode selection
#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()     (T1CONbits.T1SYNC=1)  
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()      (T1CONbits.T1SYNC=0)

// Macros for oscillator control
#define TIMER1_OSC_ON_FUN()                    (T1CONbits.T1OSCEN=1)  
#define TIMER1_OSC_OFF_FUN()                   (T1CONbits.T1OSCEN=0) 

// Macro for selecting prescaler
#define TIMER1_PRESCALER_SELECT(_X_)           (T1CONbits.T1CKPS=_X_)

// Macro for checking system clock status
#define TIMER1_SYSTEM_CLK_STATUS()             (T1CONbits.T1RUN)

// Macros for selecting register mode (8-bit or 16-bit)
#define TIMER1_RW_REG_MODE_16BIT_ENABLE()      (T1CONbits.RD16=1)
#define TIMER1_RW_REG_MODE_8BIT_ENABLE()       (T1CONbits.RD16=0)

/*------------DATA_TYPES-------------------*/
typedef enum {
    TIMER1_PRESCALER_DIV_BY_1 = 0,
    TIMER1_PRESCALER_DIV_BY_2,
    TIMER1_PRESCALER_DIV_BY_4,
    TIMER1_PRESCALER_DIV_BY_8,
} timer1_prescaler_select_t;

typedef struct {
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    // Function pointer for Timer1 interrupt handler
    void (*Timer1_Interrupt_Handler)(void);
    // Interrupt priority configuration
    interrupt_priority_cfg priority;
#endif
    // Timer configuration parameters
    timer1_prescaler_select_t prescaler_value;
    uint16 timer1_preload_value;
    uint8 timer1_mode : 1;
    uint8 counter_mode : 1;
    uint8 timer1_osc_cfg : 1;
    uint8 timer1_rw_reg_mode : 1;
} timer1_t;

/*------------FUNCTIONS_DECLARATION--------*/
// Function to initialize Timer1
Std_ReturnType Timer1_Init(timer1_t const *timer);

// Function to deinitialize Timer1
Std_ReturnType Timer1_DeInit(timer1_t const *timer);

// Function to write a value to Timer1
Std_ReturnType Timer1_Write_Value(timer1_t const *timer, uint16 value);

// Function to read the current value of Timer1
Std_ReturnType Timer1_Read_Value(timer1_t const *timer, uint16 *value);

#endif	/* HAL_TIMER1_H */
