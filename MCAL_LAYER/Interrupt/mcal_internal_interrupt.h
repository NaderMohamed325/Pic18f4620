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

/*-----------------MACROS--------------------*/


#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the ADC Module */
#define ADC_InterruptDisable()         (PIE1bits.ADIE = 0)
/* This routine sets the interrupt enable for the ADC Module */
#define ADC_InterruptEnable()          (PIE1bits.ADIE = 1)
/* This routine clears the interrupt flag for the ADC Module */
#define ADC_InterruptFlagClear()       (PIR1bits.ADIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* This routine set the ADC Module Interrupt Priority to be High priority */
#define ADC_HighPrioritySet()          (IPR1bits.ADIP = 1)
/* This routine set the ADC Module Interrupt Priority to be Low priority */
#define ADC_LowPrioritySet()           (IPR1bits.ADIP = 0)
#endif
#endif

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the TIMER0 Module */
#define TIMER0_InterruptDisable()         (INTCONbits.TMR0IE = 0)
/* This routine sets the interrupt enable for the TIMER0 Module */
#define TIMER0_InterruptEnable()          (INTCONbits.TMR0IE = 1)
/* This routine clears the interrupt flag for the TIMER0 Module */
#define TIMER0_InterruptFlagClear()       (INTCONbits.TMR0IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* This routine set the TIMER0 Module Interrupt Priority to be High priority */
#define TIMER0_HighPrioritySet()          (INTCON2bits.TMR0IP = 1)
/* This routine set the TIMER0 Module Interrupt Priority to be Low priority */
#define TIMER0_LowPrioritySet()           (INTCON2bits.TMR0IP = 0)
#endif
#endif

#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the TIMER1 Module */
#define TIMER1_InterruptDisable()         (PIE1bits.TMR1IE = 0)
/* This routine sets the interrupt enable for the TIMER1 Module */
#define TIMER1_InterruptEnable()          (PIE1bits.TMR1IE = 1)
/* This routine clears the interrupt flag for the TIMER1 Module */
#define TIMER1_InterruptFlagClear()       (PIR1bits.TMR1IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* This routine set the TIMER1 Module Interrupt Priority to be High priority */
#define TIMER1_HighPrioritySet()          (PIR1bits.TMR1IP = 1)
/* This routine set the TIMER1 Module Interrupt Priority to be Low priority */
#define TIMER1_LowPrioritySet()           (PIR1bits.TMR1IP = 0)
#endif
#endif



#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the TIMER2 Module */
#define TIMER2_InterruptDisable()         (PIE1bits.TMR2IE= 0)
/* This routine sets the interrupt enable for the TIMER2 Module */
#define TIMER2_InterruptEnable()          (PIE1bits.TMR2IE= 1)
/* This routine clears the interrupt flag for the TIMER2 Module */
#define TIMER2_InterruptFlagClear()       (PIR1bits.TMR2IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* This routine set the TIMER2 Module Interrupt Priority to be High priority */
#define TIMER2_HighPrioritySet()          (IPR1bits.TMR2IP= 1)
/* This routine set the TIMER2 Module Interrupt Priority to be Low priority */
#define TIMER2_LowPrioritySet()           (IPR1bits.TMR2IP= 0)
#endif
#endif

#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the TIMER3 Module */
#define TIMER3_InterruptDisable()         (PIE2bits.TMR3IE= 0)
/* This routine sets the interrupt enable for the TIMER2 Module */
#define TIMER3_InterruptEnable()          (PIE2bits.TMR3IE= 1)
/* This routine clears the interrupt flag for the TIMER3 Module */
#define TIMER3_InterruptFlagClear()       (PIR2bits.TMR3IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* This routine set the TIMER3 Module Interrupt Priority to be High priority */
#define TIMER3_HighPrioritySet()          (IPR2bits.TMR3IP= 1)
/* This routine set the TIMER3 Module Interrupt Priority to be Low priority */
#define TIMER3_LowPrioritySet()           (IPR2bits.TMR3IP= 0)
#endif
#endif








/*------------DATA_TYPES-------------------*/



/*------------FUNCTIONS_DECLARATION--------*/


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

