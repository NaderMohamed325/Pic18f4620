#include "app.h"

// Global variables
Std_ReturnType ret = E_OK;

// Function prototypes
void Application_initialize(void);
uint16 re_1, re_2, re_3, re_4;
adc_config_t adc_1 = {
    .ADC_Interrupt_Handler = NULL,
    .adc_acquisition = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN0,
    .adc_conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_FORMAT_RIGHT_ENABLED  ,
    .voltage_ref = ADC_VOLTAGE_REFERENCE_DISABLED
};
adc_config_t adc_2 = {
    .ADC_Interrupt_Handler = NULL,
    .adc_acquisition = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN1,
    .adc_conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_FORMAT_RIGHT_ENABLED  ,
    .voltage_ref = ADC_VOLTAGE_REFERENCE_DISABLED
};
adc_config_t adc_3 = {
    .ADC_Interrupt_Handler = NULL,
    .adc_acquisition = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN2,
    .adc_conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_FORMAT_RIGHT_ENABLED  ,
    .voltage_ref = ADC_VOLTAGE_REFERENCE_DISABLED
};
adc_config_t adc_4 = {
    .ADC_Interrupt_Handler = NULL,
    .adc_acquisition = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN3,
    .adc_conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_FORMAT_RIGHT_ENABLED  ,
    .voltage_ref = ADC_VOLTAGE_REFERENCE_DISABLED
};

int main(void) {
    // Initialize the application
    Application_initialize();

    while (1) {
        ret = ADC_Get_Conversion_Blocking(&adc_1, ADC_CHANNEL_AN0, &re_1);
        ret = ADC_Get_Conversion_Blocking(&adc_2, ADC_CHANNEL_AN1, &re_2);
        ret = ADC_Get_Conversion_Blocking(&adc_3, ADC_CHANNEL_AN2, &re_3);
        ret = ADC_Get_Conversion_Blocking(&adc_4, ADC_CHANNEL_AN3, &re_4);
    }

    return 0;
}

void Application_initialize(void) {
    ecu_layer_initialize();
    ret = ADC_Init(&adc_1);
    ret = ADC_Init(&adc_2);
    ret = ADC_Init(&adc_3);
    ret = ADC_Init(&adc_4);
}