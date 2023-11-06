#include "ftm_app.h"
#include "pins_port_hw_access.h"
#include "hal_pwm.h"


struct_pwm_vals_def pwm_vals_t[PWM_MAX + 1];


uint32_t change_pin_to_ftm(enum_pin_name pin)
{
	uint32_t ret_val = 0;

	if(pin<NUM_OF_CONFIGURED_PINS)
	{
		PINS_SetMuxModeSel(g_pin_mux_InitConfigArr[pin].base, g_pin_mux_InitConfigArr[pin].pinPortIdx, g_pin_mux_InitConfigArr[pin].mux);
		ret_val=1;
	}
	return ret_val;
}


uint32_t change_pin_to_adc(enum_pin_name pin)
{
	uint32_t ret_val = 0;

	if(pin<NUM_OF_CONFIGURED_PINS)
	{
		PINS_SetMuxModeSel(g_pin_mux_InitConfigArr[pin].base, g_pin_mux_InitConfigArr[pin].pinPortIdx, PORT_PIN_DISABLED);
		ret_val=1;
	}
	return ret_val;
}

void encoder_Callback(ic_event_t event, uint8_t instance, uint8_t channel)
{
	hal_freq_process_encoder(event, instance, channel);
}

void FTM_IRQHandler(uint8_t module)
{
	uint8_t i;

	for (i = 0; i < PWM_MAX; i++)
	{
		if (struct_ftm_config_tbl[i].pwm_instance == module)	
		{
			if (pwm_vals_t[i].dither_promille)
			{
				pwm_vals_t[i].dither_counter++;

				if (pwm_vals_t[i].dither_counter >= (pwm_vals_t[i].dither_counts + 1) / 2)
				{
					pwm_vals_t[i].dither_counter = 0;

					pwm_vals_t[i].dither_stat = ~pwm_vals_t[i].dither_stat + 1; 

					hal_pwm_set_duty(i, (uint16_t)((pwm_vals_t[i].pwm_promille_backup + pwm_vals_t[i].dither_stat * pwm_vals_t[i].dither_promille)));
				}
				else
				{
				}
			}
			else
			{
			}
		}
		else
		{
		}
	}
}


void FTM0_IRQHandler(void)
{
	FTM_IRQHandler(MODULE_0);
	FTM_DRV_ClearStatusFlags(MODULE_0, FTM_TIME_OVER_FLOW_FLAG);
}


void FTM1_IRQHandler(void)
{
	FTM_IRQHandler(MODULE_1);
	FTM_DRV_ClearStatusFlags(MODULE_1, FTM_TIME_OVER_FLOW_FLAG);
}


void FTM2_IRQHandler(void)
{
	FTM_IRQHandler(MODULE_2);
	FTM_DRV_ClearStatusFlags(MODULE_2, FTM_TIME_OVER_FLOW_FLAG);
}


void FTM3_IRQHandler(void)
{
	FTM_IRQHandler(MODULE_3);
	FTM_DRV_ClearStatusFlags(MODULE_3, FTM_TIME_OVER_FLOW_FLAG);
}


void FTM4_IRQHandler(void)
{
	FTM_IRQHandler(MODULE_4);
	FTM_DRV_ClearStatusFlags(MODULE_4, FTM_TIME_OVER_FLOW_FLAG);
}


void FTM5_IRQHandler(void)
{
	FTM_IRQHandler(MODULE_5);
	FTM_DRV_ClearStatusFlags(MODULE_5, FTM_TIME_OVER_FLOW_FLAG);
}


void FTM6_IRQHandler(void)
{
	FTM_IRQHandler(MODULE_6);
	FTM_DRV_ClearStatusFlags(MODULE_6, FTM_TIME_OVER_FLOW_FLAG);
}


void FTM7_IRQHandler(void)
{
	FTM_IRQHandler(MODULE_7);
	FTM_DRV_ClearStatusFlags(MODULE_7, FTM_TIME_OVER_FLOW_FLAG);
}


