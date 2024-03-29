/* 
 * File:   app.h
 * Author: xcite
 *
 * Created on November 14, 2023, 8:33 PM
 */
#ifndef APP_H
#define APP_H

/*----------------INCLUDES-------------------*/
#include "ECU_LAYER/ecu_layer_init.h"
#include "MCAL_LAYER/Interrupt/mcal_external_interrupt.h"
#include "MCAL_LAYER/EEPROM/hal_eeprom.h"
#include "MCAL_LAYER/ADC/hal_adc.h"
#include "MCAL_LAYER/Timer/hal_timer0.h"
#include "MCAL_LAYER/Timer/hal_timer1.h"
#include "MCAL_LAYER/Timer/hal_timer2.h"
#include "MCAL_LAYER/Timer/hal_timer3.h"
/*-----------------MACROS--------------------*/



/*--------------MACROS_FUNCTIONS-----------*/


/*------------DATA_TYPES-------------------*/

/*------------FUNCTIONS_DECLARATION--------*/
void Application_initialize(void);


#endif	/* APP_H */

