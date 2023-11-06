
#include "user_api_ai.h"
#include "adc_app.h"


void user_ai_set_measurement_range(enum_adc_pin_name pin, uint8_t range)
{
#if ADC_SECOND_RANGE
    modulhardwarecode_adc_set_measurement_range(pin, range);
#endif
}


uint16_t user_ai_get(enum_adc_pin_name pin)
{
    uint16_t ret_val = 0u;
    hal_io_ai_get_digits(pin, &ret_val);
    return ret_val;
}


uint16_t user_ai_get_mv(enum_adc_pin_name pin)
{
	uint16_t ret_val = 0u;

    if ( (pin > ADC_MAX) || (adc_config_tbl[pin].resolution == 0u) )
    {
        ret_val = 0;
    }
	else
	{
		ret_val = ((user_ai_get(pin) * adc_get_measurement_range(pin)) / adc_config_tbl[pin].resolution);
	}

	return ret_val;
}


uint16_t user_ai_get_cal(enum_adc_pin_name pin)
{
	uint16_t retval = 0u;

	retval = adc_results[pin].result_cal;

    return retval;
}

uint16_t user_ai_get_filtered(enum_adc_pin_name pin)
{
    uint16_t retval = 0u;

    retval = adc_results[pin].result_filtered;

    return retval;
}

