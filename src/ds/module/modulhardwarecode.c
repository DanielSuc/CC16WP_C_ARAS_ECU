/*--------------------------------------------------------------------------*/
/** \file           modulhardwarecode.c
*   \brief          Modulehardwarecode for the CC16WP module and its variants.
*   \date           09.10.2023 11:02:57  \author: ApplicsStudio
*   \version        1.00
*   \platform CPU:  S32K  | Compiler: GCC
* --------------------------------------------------------------------------*/
#include "modulhardwarecode.h"
#include "can_app.h"
#include "sci_app.h"
#include "hal_io.h"
#include "io_tables.h"
#include "hal_tick.h"
#include "sfl_timer.h"
#include "watchdog1.h"
#include "hal_watchdog.h"
#include "user_api_io.h"
#include "lin_db_tables.h"
#include "sfl_can_db_tables_data.h"

const struct_can_pin_list can_pin_list[CAN_HANDLE_MAX_NR] =
{
    // enable,  standby
    { CAN_EN1, CAN_STB1 },
    { CAN_EN2, CAN_STB2 },
    { PIN_MAX, PIN_MAX }
};

struct_ADC_VREF_values_t mgl_adc_vref_values[ADC_MAX + 1] = {
         // name                           // alternate vref value         // range switch
    {   .pin = AI_A_IN0,           .vrefh2 = 32250,     .range_switch = DO_RS0        },
    {   .pin = AI_A_IN1,           .vrefh2 = 32250,     .range_switch = DO_RS1        },
    {   .pin = AI_A_IN2,           .vrefh2 = 32250,     .range_switch = DO_RS2        },
    {   .pin = AI_A_IN3,           .vrefh2 = 32250,     .range_switch = DO_RS3        },
    {   .pin = AI_A_IN4,           .vrefh2 = 32250,     .range_switch = DO_RS4        },
    {   .pin = AI_A_IN5,           .vrefh2 = 32250,     .range_switch = DO_RS5        },
    {   .pin = AI_ID,                   .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_INA_OUT0,  .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_INA_OUT1,  .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_INA_OUT2,  .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_INA_OUT3,  .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_INA_OUT4,  .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_INA_OUT5,  .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_INA_OUT6,  .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_INA_OUT7,  .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_KL30_1,         .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_KL30_2,         .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_OUT0,            .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_OUT1,            .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_OUT2,            .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_OUT3,            .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_OUT4,            .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_OUT5,            .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_OUT6,            .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_OUT7,            .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_SNS1,             .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_SNS2,             .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_SNS3,             .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_SNS4,             .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_VARIANTE,  .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = AI_VREF,             .vrefh2 = 0,              .range_switch = PIN_MAX     },
    {   .pin = ADC_MAX,         .vrefh2 = 0,              .range_switch = PIN_MAX     }
};


uint32_t modulhardwarecode_adc_get_vrefh2(enum_adc_pin_name const pin, uint32_t const default_range)
{
    	uint32_t range = default_range;
    	// check if range of given ADC pin is switched and if yes use that value
    	// Is the given pin inside the ADC pin count?
    if (pin < ADC_MAX)
    	{
        		if (mgl_adc_vref_values[pin].range_switch < PIN_MAX)
        		{
            			// the pin has a range switch
            			if (user_do_readback(mgl_adc_vref_values[pin].range_switch))
            			{
                				// 2nd range is selected
                				range = mgl_adc_vref_values[pin].vrefh2;
            			}
        		}
    	}

    	return range;
}


enum_pin_name modulhardwarecode_adc_get_range_switch(enum_adc_pin_name const pin)
{
    	if (pin < ADC_MAX)
    	{
        		return mgl_adc_vref_values[pin].range_switch;
    	}
    	else
    	{
        		return PIN_MAX;
    	}
}


void modulhardwarecode_adc_set_measurement_range(enum_adc_pin_name const pin, uint8_t const range)
{
    	// Check if pin is valid, has a vref_range_1 value and DO pin for range switch are given
    	if ( (pin < ADC_MAX) &&
           			(mgl_adc_vref_values[pin].vrefh2 != 0) &&
           			(mgl_adc_vref_values[pin].range_switch < PIN_MAX) )
    	{
        		switch (range)
        		{
            		case 0:
            			(void)user_do_set(mgl_adc_vref_values[pin].range_switch, 0);
            			break;

            		case 1:
            			(void)user_do_set(mgl_adc_vref_values[pin].range_switch, 1);
            			break;

            		default:
            			(void)user_do_set(mgl_adc_vref_values[pin].range_switch, 0);
            			break;
        		}
    	}
    	else
    	{
        		// return invalid pin
    	}
}

void modulhardwarecode_init(void)
{
	// Watchdog
    hal_watchdog_mask(WDT_SIGNAL_MAIN_LOOP_BIT);
    hal_watchdog_start(HAL_WATCHDOG_EXTERNAL, WD);

    user_can_init( can_pin_list);

    sci_init( SCI_INTERFACE_2 );

    // shift_reg_init
    hal_io_do_set(DO_SHIFT_MR, 1);   	// Master Reset - has to be high while operating
    hal_io_do_set(DO_SHIFT_ST_CP, 1);	// Values of shift register are copied into the Storage/Latch Register ("Output").
    hal_io_do_set(DO_SHIFT_OE, 0);   	// Output Enable - has to be low while operating

    // Enable LIN transceiver (if present on HW) unconditionally - this is required for proper sleep handling (see KSB-941)
    hal_io_do_set(LIN_EN, 1);
}

void modulhardwarecode_sleep(void)
{
    // go-to-sleep mode for CAN tranceiver
    hal_io_do_set(CAN_STB1, 0);     // disable CAN1 standby pin
    hal_io_do_set(CAN_STB2, 0);     // disable CAN2 standby pin

    // wait untill CAN tranceivers are in sleep mode
    sfl_timer_wait(2, HAL_PRECISION_1MS);  // Wait 2ms

    // disable CAN tranceiver
    hal_io_do_set(CAN_EN1, 0);      // disable CAN1 enable pin
    hal_io_do_set(CAN_EN2, 0);      // disable CAN2 enable pin

    hal_io_do_set(LIN_EN, 0);       // disable LIN transceiver
    hal_io_do_set(DO_POWER, 0);     // disable selbsthaltung

    // wait until 5V DCDC is off
    sfl_timer_wait(200, HAL_PRECISION_1MS);  // Wait 200ms


    // recovery after timeout, because module didn't go to sleep
    hal_io_do_set(DO_POWER, 1);     // re-enable selbsthaltung
    hal_io_do_set(CAN_EN1, 1);      // enable CAN1 transceiver
    hal_io_do_set(CAN_STB1, 1);     // enable CAN1 standby pin
    hal_io_do_set(CAN_EN2, 1);      // enable CAN2 transceiver
    hal_io_do_set(CAN_STB2, 1);     // enable CAN2 standby pin
    hal_io_do_set(LIN_EN, 1);       // enable LIN transceiver
}

void modulhardwarecode_timer(void)
{
}

/**
 * Public functions module_adc_multiplex
 */
void modulhardwarecode_adc_multiplex(uint8_t multiplex_nr)
{
    switch (multiplex_nr)
    {
        case 0:
            // Enable HSD1, Disable HSD2
            hal_io_do_set(DO_CS_HSD1, 0);
            hal_io_do_set(DO_CS_HSD2, 1);
            break;
        case 1:
            // Disable HSD1, Enable HSD2
            hal_io_do_set(DO_CS_HSD1, 1);//0
            hal_io_do_set(DO_CS_HSD2, 0);//1
            break;
        default:
            // Disable HSD1 and HSD2
            hal_io_do_set(DO_CS_HSD1, 1);
            hal_io_do_set(DO_CS_HSD2, 1);
            break;
    }

}

void modulhardwarecode_cyclic(void)
{
    // update shift register

    // Check if a shift register variable was changed
    // Disable store pin
    hal_io_do_set(DO_SHIFT_ST_CP, 0);

    for(uint8_t pin = 0; pin < (VIRTUAL_PIN_MAX - PIN_MAX); pin++)
    {
    	// loop through all pins.
    	// NOTE: the order of the enums/pins must be identical to what it is on the hardware
    	// the number of the enum has an offset of PIN_MAX but in virtual_pin addresses start at 0 to save memory

    	// Set shift(clock) pin to low
    	hal_io_do_set(DO_SHIFT_SH_CP, 0);

    	// Set the data
    	hal_io_do_set(DOX_SHIFT_IN_DS, virtual_pin[pin].current_val);

    	// Set shift(clock) pin to high (Shift register will take over the data)
    	hal_io_do_set(DO_SHIFT_SH_CP, 1);
    }

    // Enable storage pin
    hal_io_do_set(DO_SHIFT_ST_CP, 1);

    // make sure the output is enabled
    hal_io_do_set(DO_SHIFT_OE, 0);   	// Output Enable - has to be low while operating
}

