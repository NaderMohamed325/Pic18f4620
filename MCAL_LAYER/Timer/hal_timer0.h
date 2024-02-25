/* 
 * File:   hal_timer0.h
 * Author: xcite
 *
 * Created on 25/2/2024, 01:54 
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/*----------------INCLUDES-------------------*/
#include "../../MCAL_LAYER/Interrupt/mcal_internal_interrupt.h"

/*-----------------MACROS--------------------*/

// Configuration macros for enabling/disabling Timer0 prescaler
#define TIMER0_PRESCALER_ENABLE_CFG    1
#define TIMER0_PRESCALER_DISABLE_CFG   0

// Configuration macros for rising/falling edge configuration
#define TIMER0_RISING_EDGE_CFG         1
#define TIMER0_FALLING_EDGE_CFG        0

// Configuration macros for Timer0 mode (Timer/Counter), and register size (8-bit/16-bit)
#define TIMER0_TIMER_MODE              1    
#define TIMER0_COUNTER_MODE            0    
#define TIMER0_8BIT_REGISTER_MODE      1
#define TIMER0_16BIT_REGISTER_MODE     0

/*--------------MACROS_FUNCTIONS-----------*/

// Macros to enable/disable Timer0 prescaler
#define TIMER0_PRESCALER_ENABLE()        (T0CONbits.PSA=0)
#define TIMER0_PRESCALER_DISABLE()       (T0CONbits.PSA=1)

// Macros to enable rising/falling edge configuration for Timer0
#define TIMER0_RISING_EDGE_ENABLE()      (T0CONbits.T0SE=0)
#define TIMER0_FALLING_EDGE_ENABLE()     (T0CONbits.T0SE=1)

// Macros to select Timer0 mode (Timer/Counter)
#define TIMER0_TIMER_MODE_ENABLE()       (T0CONbits.T0CS=0)
#define TIMER0_COUNTER_MODE_ENABLE()     (T0CONbits.T0CS=1)

// Macros to select Timer0 register size (8-bit/16-bit)
#define TIMER0_8BIT_REGISTER_MODE_ENABLE()  (T0CONbits.T08BIT=1)
#define TIMER0_16BIT_REGISTER_MODE_ENABLE() (T0CONbits.T08BIT=0)

// Macros to turn Timer0 module on/off
#define TIMER0_MODULE_ON()                   (T0CONbits.TMR0ON=1)
#define TIMER0_MODULE_OFF()                  (T0CONbits.TMR0ON=0)

/*------------DATA_TYPES-------------------*/

// Enum to specify Timer0 prescaler values

typedef enum {
    TIMER0_PRESCALER_DIV_BY_2 = 0,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256,
} timer0_prescaler_select_t;

// Structure to hold Timer0 configuration settings

typedef struct {
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*Timer0_Interrupt_Handler)(void);
    interrupt_priority_cfg priority;
#endif
    timer0_prescaler_select_t prescaler_value;
    uint16 timer0_preload_value;
    uint8 prescaler_enable : 1;
    uint8 timer0_counter_edge : 1;
    uint8 timer0_mode : 1;
    uint8 timer0_register_size : 1;
    uint8 _reserved : 4;
} timer0_t;

/*------------FUNCTIONS_DECLARATION--------*/
Std_ReturnType Timer0_Init(timer0_t const *timer);
Std_ReturnType Timer0_DeInit(timer0_t const *timer);
Std_ReturnType Timer0_Write_Value(timer0_t const *timer, uint16 value);
Std_ReturnType Timer0_Read_Value(timer0_t const *timer, uint16 *value);

#endif	/* HAL_TIMER0_H */
