/* 
 * File:   mcal_internal_interrupt.h
 * Author: xcite
 *
 * Created on February 1, 2024, 8:24 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H
/*----------------INCLUDES-------------------*/
#include "mcal_interrupt_cfg.h"
#include "../ADC/hal_adc.h"
/*-----------------MACROS--------------------*/



/*--------------MACROS_FUNCTIONS-----------*/
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

#define ADC_InterruptDisable()         (PIE1bits.ADIE = 0)
/* This routine sets the interrupt enable for the ADC Module */
#define ADC_InterruptEnable()          (PIE1bits.ADIE = 1)
/* This routine clears the interrupt flag for the ADC Module */
#define ADC_InterruptFlagClear()       (PIR1bits.ADIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE   == INTERRUPT_FEATURE_ENABLE

/* This routine set the ADC Module Interrupt Priority to be High priority */
#define ADC_HighPrioritySet()          (IPR1bits.ADIP = 1)
/* This routine set the ADC Module Interrupt Priority to be Low priority */
#define ADC_LowPrioritySet()           (IPR1bits.ADIP = 0)

#endif



/*------------DATA_TYPES-------------------*/



/*------------FUNCTIONS_DECLARATION--------*/


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

#endif