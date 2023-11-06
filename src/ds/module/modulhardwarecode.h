#ifndef SRC_MODULHARDWARECODE_H_
#define SRC_MODULHARDWARECODE_H_

/*--------------------------------------------------------------------------*/
/** \file           modulhardwarecode.h
*   \brief          Module specific functions
*   \date           09.10.2023 11:02:57  \author: ApplicsStudio
*   \version        1.00
*   \platform CPU:  S32K  | Compiler: GCC
* --------------------------------------------------------------------------*/
#include <stdint.h>

#include "io_tables.h"

#define AD_FILTER     23u
#define HW_CALIBRATION_SUPPORT 1u
#define ADC_SECOND_RANGE       1u
#define AI_RANGE_16V		   0u
#define AI_RANGE_32V   1u
#define MULTIPLEX_STABILITY_CYCLES 16

typedef struct {
        enum_adc_pin_name   pin;
        uint32_t            vrefh2;
        enum_pin_name       range_switch;
}struct_ADC_VREF_values_t;


uint32_t modulhardwarecode_adc_get_vrefh2(enum_adc_pin_name const pin, uint32_t const default_range);
void modulhardwarecode_adc_set_measurement_range(enum_adc_pin_name const pin, uint8_t const range);

void modulhardwarecode_init(void);
void modulhardwarecode_sleep(void);
void modulhardwarecode_timer(void);
void modulhardwarecode_adc_multiplex(uint8_t multiplex_nr);
void modulhardwarecode_cyclic(void);

#endif // SRC_MODULHARDWARECODE_H_