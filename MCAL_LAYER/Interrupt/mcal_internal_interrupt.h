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

/* Macros for Timer0 Interrupt Control */
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

// Disable Timer0 Interrupt
#define TIMER0_InterruptDisable()         (PIE1bits.TMR0IE = 0)
// Enable Timer0 Interrupt
#define TIMER0_InterruptEnable()          (PIE1bits.TMR0IE = 1)
// Clear Timer0 Interrupt Flag
#define TIMER0_InterruptFlagClear()       (PIR1bits.TMR0IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

// Set Timer0 Interrupt Priority to High
#define TIMER0_HighPrioritySet()          (IPR1bits.TMR0IP = 1)
// Set Timer0 Interrupt Priority to Low
#define TIMER0_LowPrioritySet()           (IPR1bits.TMR0IP = 0)

#endif
#endif

/* Macros for ADC Interrupt Control */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

// Disable ADC Interrupt
#define ADC_InterruptDisable()         (PIE1bits.ADIE = 0)
// Enable ADC Interrupt
#define ADC_InterruptEnable()          (PIE1bits.ADIE = 1)
// Clear ADC Interrupt Flag
#define ADC_InterruptFlagClear()       (PIR1bits.ADIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

// Set ADC Interrupt Priority to High
#define ADC_HighPrioritySet()          (IPR1bits.ADIP = 1)
// Set ADC Interrupt Priority to Low
#define ADC_LowPrioritySet()           (IPR1bits.ADIP = 0)

#endif

#endif

/*------------DATA_TYPES-------------------*/

// Data types can be added here if needed

/*------------FUNCTIONS_DECLARATION--------*/

// Function declarations can be added here if needed

#endif	/* MCAL_INTERNAL_INTERRUPT_H */
