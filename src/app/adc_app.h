#ifndef __ADC_APP_H_
#define __ADC_APP_H_

#include "pdbCom1.h"
#include "adConvCom1.h"
#include "hal_io.h"
#include "pins_driver.h"
#include "io_tables.h" 
#include "modulhardwarecode.h"



typedef struct
 {
    uint16_t a_data[AD_FILTER];
    uint8_t index_next_value;
    uint16_t amount_of_values;
 } floating_avg_data_t;       

typedef struct
{
    uint32_t current_value;
    uint16_t amount_values;
} floating_avg_values_data_t;

typedef struct
{
        uint16_t result_raw;
        uint16_t result_digit;      
        uint16_t result_unit;     
        uint16_t result_cal;      
        uint16_t result_filtered; 
}struct_adc_results_t;


extern struct_adc_results_t adc_results[ADC_MAX];


void ADC_init(void);
void ADC1_IRQHandler(void);
void ADC2_IRQHandler(void);

void adc_processing(uint8_t *multiplex_group, bool hw_calibration_support);
uint16_t adc_get_module_type();

uint16_t get_mean_analog_value(enum_adc_pin_name analog_pin, uint8_t AmountValues);

uint16_t get_mean_analog_value_exact(enum_adc_pin_name analog_pin);

uint32_t adc_get_measurement_range(enum_adc_pin_name const pin);

void adc_copy_results_from_interrupt(uint8_t adc_instance, uint8_t* adc_done_flag, uint32_t* adc_counter, IRQn_Type adc_interrupt );


void add_to_float_avg(floating_avg_data_t *float_avg_data, uint16_t new_value);

uint16_t adc_calc_float_avg(floating_avg_data_t *float_avg_data);

#endif

