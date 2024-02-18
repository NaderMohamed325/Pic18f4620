/* 
 * File:   hal_adc.h
 * Author: xcite
 *
 * Created on February 17, 2024, 11:58 AM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/*----------------INCLUDES-------------------*/
#include "hal_adc_cfg.h"
#include "../GPIO/hal_gpio.h"
#include "../mcal_std_types.h"
#include "../../MCAL_LAYER/Interrupt/mcal_internal_interrupt.h"

/*-----------------MACROS--------------------*/
#define ADC_AN0_ANALOG_FUNCTIONALITY  0X0E  /**< Macro to define analog functionality for AN0. */
#define ADC_AN1_ANALOG_FUNCTIONALITY  0X0D  /**< Macro to define analog functionality for AN1. */
#define ADC_AN2_ANALOG_FUNCTIONALITY  0X0C  /**< Macro to define analog functionality for AN2. */
#define ADC_AN3_ANALOG_FUNCTIONALITY  0X0B  /**< Macro to define analog functionality for AN3. */
#define ADC_AN4_ANALOG_FUNCTIONALITY  0X0A  /**< Macro to define analog functionality for AN4. */
#define ADC_AN5_ANALOG_FUNCTIONALITY  0X09  /**< Macro to define analog functionality for AN5. */
#define ADC_AN6_ANALOG_FUNCTIONALITY  0X08  /**< Macro to define analog functionality for AN6. */
#define ADC_AN7_ANALOG_FUNCTIONALITY  0X07  /**< Macro to define analog functionality for AN7. */
#define ADC_AN8_ANALOG_FUNCTIONALITY  0X06  /**< Macro to define analog functionality for AN8. */
#define ADC_AN9_ANALOG_FUNCTIONALITY  0X05  /**< Macro to define analog functionality for AN9. */
#define ADC_AN10_ANALOG_FUNCTIONALITY 0X04  /**< Macro to define analog functionality for AN10. */
#define ADC_AN11_ANALOG_FUNCTIONALITY 0X03  /**< Macro to define analog functionality for AN11. */
#define ADC_AN12_ANALOG_FUNCTIONALITY 0X02  /**< Macro to define analog functionality for AN12. */
#define ADC_ALL_ANALOG_FUNCTIONALITY   0X00 /**< Macro to define analog functionality for all channels. */
#define ADC_ALL_DIGITAL_FUNCTIONALITY  0X0F /**< Macro to define digital functionality for all channels. */


#define ADC_RESULT_FORMAT_RIGHT_ENABLED    0X01U
#define ADC_RESULT_FORMAT_LEFT_ENABLED     0X00


#define ADC_VOLTAGE_REFERENCE_ENABLED    0X01U
#define ADC_VOLTAGE_REFERENCE_DISABLED    0X00


#define ADC_CONVERSION_COMPLETED     0X01
#define ADC_CONVERSION_NOT_COMPLETED 0X00

/*--------------MACROS_FUNCTIONS-----------*/

#define ADC_CONVERSION_STATUS()  (ADCON0bits.GO_nDONE)      /**< Macro to check the conversion status. */
#define ADC_START_CONVERSION()   (ADCON0bits.GO_nDONE=1) 


#define ADC_CONVERTER_ENABLE()   (ADCON0bits.ADON = 1)      /**< Macro to enable the ADC converter. */
#define ADC_CONVERTER_DISABLE()  (ADCON0bits.ADON = 0)      /**< Macro to disable the ADC converter. */

#define ADC_ENABLE_VOLTAGE_REFERENCE()    do{ADCON1bits.VCFG1 = 1; \
                                             ADCON1bits.VCFG0 = 1; \
                                             } while(0)
/**< Macro to enable the voltage reference for the ADC. */

#define ADC_DISABLE_VOLTAGE_REFERENCE()   do{ADCON1bits.VCFG1 = 0; \
                                             ADCON1bits.VCFG0 = 0; \
                                             } while(0)
/**< Macro to disable the voltage reference for the ADC. */

#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG) (ADCON1bits.PCFG=_CONFIG)

#define ADC_RESULT_RIGHT_FORMAT()     (ADCON2bits.ADFM=1)
#define ADC_RESULT_LEFT_FORMAT()      (ADCON2bits.ADFM=0)

/*------------DATA_TYPES-------------------*/
typedef enum {
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12,
    ADC_CHANNEL_AN13,
} adc_channel_select_t;

/**< Enumeration for ADC channel selection. */
typedef enum {
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD,
} adc_acquisition_time_t;

typedef enum {
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64,
} adc_conversion_clock_t;

typedef struct {
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*ADC_Interrupt_Handler) (void);
#endif
    adc_acquisition_time_t adc_acquisition;
    adc_conversion_clock_t adc_conversion_clock;
    adc_channel_select_t adc_channel;
    interrupt_priority_cfg priority;
    uint8 voltage_ref : 1;
    uint8 result_format : 1;
    uint8 reserved_bits : 6;
} adc_config_t;


/*------------FUNCTIONS_DECLARATION--------*/
Std_ReturnType ADC_Init(const adc_config_t*adc);
Std_ReturnType ADC_Denit(const adc_config_t*adc);
Std_ReturnType ADC_Select_Channel(const adc_config_t*adc, adc_channel_select_t channel);
Std_ReturnType ADC_Start_Conversion(const adc_config_t*adc);
Std_ReturnType ADC_Is_Conversion_Done(const adc_config_t*adc, uint8 *conversion_status);
Std_ReturnType ADC_Get_Conversion_Result(const adc_config_t*adc, uint16 *result);
Std_ReturnType ADC_Get_Conversion_Blocking(const adc_config_t*adc, adc_channel_select_t channel, uint16 *result);




#endif	/* HAL_ADC_H */
