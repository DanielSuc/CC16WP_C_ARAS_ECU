
#include "user_api_io.h"
#include "io_tables.h"
#include "user_api_pwm.h"
#include "adConvCom1.h"
#include "flexTimerCom1.h"
#include "user_code.h"
#include "adc_app.h"

#ifdef DI_EMULATION_THRESHOLD_HIGH
    #define DI_THRESHOLD_HIGH DI_EMULATION_THRESHOLD_HIGH
#else
    #define DI_THRESHOLD_HIGH 6000u 
#endif

#ifdef DI_EMULATION_THRESHOLD_LOW
    #define DI_THRESHOLD_LOW DI_EMULATION_THRESHOLD_LOW
#else
  #define DI_THRESHOLD_LOW 4000u  
#endif



extern struct_VIRTUAL_PINS_CFG virtual_pin[VIRTUAL_PIN_MAX - PIN_MAX];

void user_do_set(uint16_t pin, uint8_t state)
{
    if( (g_pin_mux_InitConfigArr[pin].mux == PORT_MUX_AS_GPIO) && (pin < PIN_MAX) )
    {
        hal_io_do_set(pin, state);
    }
    else if( (pin >= PIN_MAX) && (pin < VIRTUAL_PIN_MAX) )
    {
		virtual_pin[pin - PIN_MAX].current_val = state;
    }
    else if( io_pin_linker[pin].pwm_pin_name != PWM_MAX)
    {

        if (state == 0)
        {
            user_pwm_output_force(io_pin_linker[pin].pwm_pin_name, 0);
        }
        else
        {
        	user_pwm_output_force(io_pin_linker[pin].pwm_pin_name, 1000);
        }
    }
}


uint8_t user_do_readback(uint16_t pin)
{
	uint8_t state = 0;

    if( (g_pin_mux_InitConfigArr[pin].mux == PORT_MUX_AS_GPIO) && (pin < PIN_MAX) )
    {
        hal_io_do_readback(pin, &state);
    }
    else if (pin >= PIN_MAX)
    {
    	state = virtual_pin[pin - PIN_MAX].current_val;
    }
    else if ( io_pin_linker[pin].pwm_pin_name != PWM_MAX)
    {
        hal_pwm_readback_do(io_pin_linker[pin].pwm_pin_name, &state);
    }

    return state;
}


uint8_t user_di_get(uint16_t pin)
{
    uint8_t state = 0;
    static uint32_t pin_states[(ADC_MAX-1)/32 + 1] = { 0 };

    if( pin < VIRTUAL_PIN_MAX )
    {
    	if(pin<PIN_MAX)
    	{
			if( g_pin_mux_InitConfigArr[pin].mux == PORT_MUX_AS_GPIO )
			{
				hal_io_di_get(pin, &state);

				return state;
			}
    	}


		enum_adc_pin_name adc_pin = io_pin_linker[pin].adc_pin_name;
		if(adc_pin < ADC_MAX)
		{
			uint8_t arr_index = adc_pin / 32;
			uint8_t bit_position = adc_pin % 32;
			state = ( pin_states[arr_index] & (1u << bit_position) ) ? 1 : 0;

			if (user_ai_get_mv(adc_pin) >= DI_THRESHOLD_HIGH)
			{
				pin_states[arr_index] |= (1u << bit_position);
				state = 1;
			}
			else if(user_ai_get_mv(adc_pin) <= DI_THRESHOLD_LOW)
			{
				pin_states[arr_index] &= ~(1u << bit_position);
				state = 0;
			}
		}
		else
		{
			state = 0;
		}

    }
    else
    {
        state = 0;
    }

    return state;
}

