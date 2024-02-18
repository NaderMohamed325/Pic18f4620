/**
 * @file hal_adc.c
 * @brief ADC Module Implementation
 * @author xcite
 * @date February 17, 2024
 */

#include "hal_adc.h"

// Private function declarations
static inline void adc_input_channel_port_configure(adc_channel_select_t channel);
static inline void adc_select_result_format(const adc_config_t* adc);
static inline void adc_select_voltage_ref(const adc_config_t* adc);

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*_ADC_Interrupt_Handler)(void) = NULL;

#endif

/**
 * @brief Initializes the ADC module.
 *
 * @param adc Pointer to the ADC configuration structure.
 * @return Std_ReturnType E_OK if successful, E_NOT_OK if unsuccessful.
 */
Std_ReturnType ADC_Init(const adc_config_t* adc) {
    Std_ReturnType ret = E_OK;

    // Check if the provided ADC configuration pointer is valid
    if (NULL == adc) {
        ret = E_NOT_OK;
    } else {
        // Disable ADC before configuration
        ADC_CONVERTER_DISABLE();

        // Set acquisition time and conversion clock
        ADCON2bits.ACQT = adc->adc_acquisition;
        ADCON2bits.ADCS = adc->adc_conversion_clock;

        // Select ADC channel and configure related port
        ADCON0bits.CHS = adc->adc_channel;
        adc_input_channel_port_configure(adc->adc_channel);

        // Select result format and voltage reference
        adc_select_result_format(adc);
        adc_select_voltage_ref(adc);
        //interrupt features
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ADC_InterruptEnable();
        INTERRUPT_Global_Interrupt_Enable();
        INTERRUPT_Peripheral_Interrupt_Enable();
        ADC_InterruptFlagClear();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        if (INTERRUPT_HIGH_PRIORITY == adc->priority) {
            ADC_HighPrioritySet();
        } else if (INTERRUPT_LOW_PRIORITY == adc->priority) {
            ADC_LowPrioritySet();
        }
#endif

        _ADC_Interrupt_Handler = adc->ADC_Interrupt_Handler;

#endif

        // Enable ADC after configuration
        ADC_CONVERTER_ENABLE();
    }

    return ret;
}

/**
 * @brief Deinitializes the ADC module.
 *
 * @param adc Pointer to the ADC configuration structure.
 * @return Std_ReturnType E_OK if successful, E_NOT_OK if unsuccessful.
 */
Std_ReturnType ADC_Deinit(const adc_config_t* adc) {
    Std_ReturnType ret = E_OK;

    // Check if the provided ADC configuration pointer is valid
    if (NULL == adc) {
        ret = E_NOT_OK;
    } else {
        // Disable ADC
        ADC_CONVERTER_DISABLE();


#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

        ADC_InterruptDisable();






#endif
    }

    return ret;
}

/**
 * @brief Selects the ADC channel for conversion.
 *
 * @param adc Pointer to the ADC configuration structure.
 * @param channel ADC channel to be selected.
 * @return Std_ReturnType E_OK if successful, E_NOT_OK if unsuccessful.
 */
Std_ReturnType ADC_Select_Channel(const adc_config_t* adc, adc_channel_select_t channel) {
    Std_ReturnType ret = E_OK;

    // Check if the provided ADC configuration pointer is valid
    if (NULL == adc) {
        ret = E_NOT_OK;
    } else {
        // Select ADC channel and configure related port
        ADCON0bits.CHS = channel;
        adc_input_channel_port_configure(channel);
    }

    return ret;
}

/**
 * @brief Starts the ADC conversion.
 *
 * @param adc Pointer to the ADC configuration structure.
 * @return Std_ReturnType E_OK if successful, E_NOT_OK if unsuccessful.
 */
Std_ReturnType ADC_Start_Conversion(const adc_config_t* adc) {
    Std_ReturnType ret = E_OK;

    // Check if the provided ADC configuration pointer is valid
    if (NULL == adc) {
        ret = E_NOT_OK;
    } else {
        // Start ADC conversion
        ADC_START_CONVERSION();
    }

    return ret;
}

/**
 * @brief Checks if ADC conversion is complete.
 *
 * @param adc Pointer to the ADC configuration structure.
 * @param conversion_status Pointer to store the conversion status.
 * @return Std_ReturnType E_OK if successful, E_NOT_OK if unsuccessful.
 */
Std_ReturnType ADC_Is_Conversion_Done(const adc_config_t* adc, uint8_t* conversion_status) {
    Std_ReturnType ret = E_OK;

    // Check if the provided ADC configuration and status pointers are valid
    if (NULL == adc || NULL == conversion_status) {
        ret = E_NOT_OK;
    } else {
        // Check ADC conversion status
        *conversion_status = !(uint8) (ADCON0bits.GO_nDONE);
    }

    return ret;
}

/**
 * @brief Gets the result of the last ADC conversion.
 *
 * @param adc Pointer to the ADC configuration structure.
 * @param result Pointer to store the ADC conversion result.
 * @return Std_ReturnType E_OK if successful, E_NOT_OK if unsuccessful.
 */
Std_ReturnType ADC_Get_Conversion_Result(const adc_config_t* adc, uint16_t* result) {
    Std_ReturnType ret = E_OK;

    // Check if the provided ADC configuration and result pointers are valid
    if (NULL == adc || NULL == result) {
        ret = E_NOT_OK;
    } else {
        // Retrieve ADC conversion result based on result format
        if (ADC_RESULT_FORMAT_RIGHT_ENABLED == adc->result_format) {
            *result = (uint16_t) ((ADRESH << 8) + ADRESL);
        } else if (ADC_RESULT_FORMAT_LEFT_ENABLED == adc->result_format) {
            *result = (uint16_t) (((ADRESH << 8) + ADRESL) >> 2);
        } else {
            *result = (uint16_t) ((ADRESH << 8) + ADRESL);
        }
    }

    return ret;
}

/**
 * @brief Gets the result of a specific ADC channel conversion.
 *
 * @param adc Pointer to the ADC configuration structure.
 * @param channel ADC channel for which to get the conversion result.
 * @param result Pointer to store the ADC conversion result.
 * @return Std_ReturnType E_OK if successful, E_NOT_OK if unsuccessful.
 */
Std_ReturnType ADC_Get_Conversion_Blocking(const adc_config_t* adc, adc_channel_select_t channel, uint16_t* result) {
    Std_ReturnType ret = E_OK;
    uint8_t conversion_status;

    // Check if the provided ADC configuration, channel, and result pointers are valid
    if (NULL == adc || NULL == result) {
        ret = E_NOT_OK;
    } else {
        // Select channel, start conversion, and check if conversion is done
        ret &= ADC_Select_Channel(adc, channel);
        ret &= ADC_Start_Conversion(adc);
        ret &= ADC_Is_Conversion_Done(adc, &conversion_status);

        // Wait for conversion to complete
        while (ADCON0bits.GO_nDONE);

        // Get the ADC conversion result
        ret &= ADC_Get_Conversion_Result(adc, result);
    }

    return ret;
}

Std_ReturnType ADC_Get_Conversion_Interrupt(const adc_config_t*adc, adc_channel_select_t channel) {

    Std_ReturnType ret = E_OK;
    uint8_t conversion_status;

    // Check if the provided ADC configuration, channel, and result pointers are valid
    if (NULL == adc) {
        ret = E_NOT_OK;
    } else {
        // Select channel, start conversion, and check if conversion is done
        ret &= ADC_Select_Channel(adc, channel);
        ret &= ADC_Start_Conversion(adc);

    }

    return ret;


}

/**
 * @brief Configures the digital input driver for the specified ADC channel.
 *
 * @param channel ADC channel for which to configure the digital input driver.
 * @return void
 */
static inline void adc_input_channel_port_configure(adc_channel_select_t channel) {
    switch (channel) {
        case ADC_CHANNEL_AN0: SET_BIT(TRISA, _TRISA_RA0_POSN);
            break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN1: SET_BIT(TRISA, _TRISA_RA1_POSN);
            break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN2: SET_BIT(TRISA, _TRISA_RA2_POSN);
            break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN3: SET_BIT(TRISA, _TRISA_RA3_POSN);
            break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN4: SET_BIT(TRISA, _TRISA_RA5_POSN);
            break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN5: SET_BIT(TRISE, _TRISE_RE0_POSN);
            break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN6: SET_BIT(TRISE, _TRISE_RE1_POSN);
            break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN7: SET_BIT(TRISE, _TRISE_RE2_POSN);
            break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN8: SET_BIT(TRISB, _TRISB_RB2_POSN);
            break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN9: SET_BIT(TRISB, _TRISB_RB3_POSN);
            break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN10: SET_BIT(TRISB, _TRISB_RB1_POSN);
            break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN11: SET_BIT(TRISB, _TRISB_RB4_POSN);
            break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN12: SET_BIT(TRISB, _TRISB_RB0_POSN);
            break; /* Disable the digital output driver */
        default: /* Nothing */;
    }
}

/**
 * @brief Selects the result format for the ADC conversion.
 *
 * @param adc Pointer to the ADC configuration structure.
 * @return void
 */
static inline void adc_select_result_format(const adc_config_t* adc) {
    if (adc->result_format) {
        ADC_RESULT_RIGHT_FORMAT();
    } else {
        ADC_RESULT_LEFT_FORMAT();
    }
}

/**
 * @brief Selects the voltage reference for the ADC conversion.
 *
 * @param adc Pointer to the ADC configuration structure.
 * @return void 
 */
static inline void adc_select_voltage_ref(const adc_config_t* adc) {
    if (ADC_VOLTAGE_REFERENCE_ENABLED == adc->voltage_ref) {
        ADC_ENABLE_VOLTAGE_REFERENCE();
    } else if (ADC_VOLTAGE_REFERENCE_DISABLED == adc->voltage_ref) {
        ADC_DISABLE_VOLTAGE_REFERENCE();
    } else {
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
}

void ADC_ISR(void) {
    ADC_InterruptFlagClear();
    if (_ADC_Interrupt_Handler) {
        _ADC_Interrupt_Handler();
    }
}
