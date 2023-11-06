


#include "user_api_pwm.h"
#include "graph_support.h"
#include "sfl_math.h"
#include "adc_app.h"
#include "user_api_ai.h"
#include "ftm_app.h"
#include "sfl_ramp_generator.h"


pi_regulator_info_t regulator_data = {0, 0, 0};
pi_regulator_data_t mgl_pi_controller_data[PWM_MAX];
sfl_ramp_generator_control_t mgl_pwm_duty_ramp_control[PWM_MAX];
sfl_ramp_generator_control_t mgl_pwm_freq_ramp_control[PWM_MAX];


#if CONTROLLER_WITH_PRECONTROL
pi_controller_t mgl_pi_controller_vals[PWM_MAX];
#endif

#if CONTROLLER_WITH_PRECONTROL
uint16_t stromvalue1, stromvalue2, stromvalue3, step_regulator, stromvalue4; 
#endif



uint32_t user_pwm_set_pwm(uint16_t pin, uint16_t freq, uint16_t duty)
{
    uint8_t ret_val;

    ret_val = hal_pwm_set_freq(pin, freq);

    if(!ret_val)
    {
        ret_val = hal_pwm_set_duty(pin, duty);
    }
    else
    {
    }

    return (uint32_t) ret_val;
}

uint32_t user_pwm_set_pwm_ramped(uint16_t pin, uint16_t freq, uint16_t duty, uint16_t ramp_time)
{
	uint32_t ret_val = PWM_RAMP_FINISHED;
	int32_t new_duty, new_freq;
	uint32_t elapsedTime = 0;

	if(freq > HAL_PWM_FREQ_MAX) freq = HAL_PWM_FREQ_MAX;

	if(duty > HAL_PWM_DUTY_MAX) duty = HAL_PWM_DUTY_MAX;

	if(pin < PWM_MAX)
	{
		if((mgl_pwm_duty_ramp_control[pin].ramp_time == ramp_time) && (mgl_pwm_duty_ramp_control[pin].ramp_value_end == duty) && (mgl_pwm_freq_ramp_control[pin].ramp_value_end == freq))
		{
			user_set_timestamp(&elapsedTime, PRECISION_1MS);
			elapsedTime -= mgl_pwm_duty_ramp_control[pin].ramp_time_start;

			new_duty = sfl_ramp_generator(&mgl_pwm_duty_ramp_control[pin], elapsedTime);
			new_freq = sfl_ramp_generator(&mgl_pwm_freq_ramp_control[pin], elapsedTime);

			if( mgl_pwm_duty_ramp_control[pin].ramping || mgl_pwm_freq_ramp_control[pin].ramping)
			{
				ret_val = PWM_RAMP_IN_PROGRESS;
			}
		}
		else
		{
			uint16_t last_duty;
			uint32_t last_freq;

			hal_pwm_readback_duty(pin, &last_duty);
			hal_pwm_readback_freq(pin, &last_freq);

			if(last_duty > HAL_PWM_DUTY_MAX) last_duty = HAL_PWM_DUTY_MAX;
			mgl_pwm_duty_ramp_control[pin].ramp_value_start = last_duty;
			mgl_pwm_duty_ramp_control[pin].ramp_time = ramp_time;

			if(last_freq > 2000) last_freq = 2000; 
			mgl_pwm_freq_ramp_control[pin].ramp_value_start = last_freq;
			mgl_pwm_freq_ramp_control[pin].ramp_time = ramp_time;

			mgl_pwm_duty_ramp_control[pin].ramp_value_end = duty;
			mgl_pwm_freq_ramp_control[pin].ramp_value_end = freq;

			user_set_timestamp(&mgl_pwm_duty_ramp_control[pin].ramp_time_start, PRECISION_1MS);
			user_set_timestamp(&mgl_pwm_freq_ramp_control[pin].ramp_time_start, PRECISION_1MS);

			mgl_pwm_duty_ramp_control[pin].ramping = true;
			mgl_pwm_freq_ramp_control[pin].ramping = true;
			ret_val = PWM_RAMP_IN_PROGRESS;

			new_duty = sfl_ramp_generator(&mgl_pwm_duty_ramp_control[pin], elapsedTime);
			new_freq = sfl_ramp_generator(&mgl_pwm_freq_ramp_control[pin], elapsedTime);
		}

		if(new_duty > HAL_PWM_DUTY_MAX)
		{
			new_duty = HAL_PWM_DUTY_MAX;
		}
		else if(new_duty < HAL_PWM_DUTY_MIN)
		{
			new_duty = HAL_PWM_DUTY_MIN;
		}

		if(new_freq > HAL_PWM_FREQ_MAX)
		{
			new_freq = HAL_PWM_FREQ_MAX;
		}
		else if(new_freq < HAL_PWM_FREQ_MIN)
		{
			new_freq = HAL_PWM_FREQ_MIN;
		}

		user_pwm_set_pwm(pin, (uint16_t)new_freq, (uint16_t)new_duty);
	}
	else
	{
		ret_val = PWM_RAMP_CHANNEL_INVALID;
	}

	return ret_val;
}

uint32_t user_pwm_set_pwm_immediate(uint16_t pin, uint16_t freq, uint16_t duty)
{
    uint8_t ret_val;

    hal_pwm_update_now(pin, 1);
    ret_val = hal_pwm_set_freq(pin, freq);
    hal_pwm_update_now(pin, 0);

    if(!ret_val)
    {
        ret_val = hal_pwm_set_duty(pin, duty);
    }
    else
    {
    }

    return (uint32_t) ret_val;
}

uint32_t user_pwm_set_duty(uint16_t pin, uint16_t duty)
{
    return (uint32_t) hal_pwm_set_duty(pin, duty);
}

uint32_t user_pwm_set_duty_ramped(uint16_t pin, uint16_t duty, uint16_t ramp_time)
{
	uint32_t ret_val = PWM_RAMP_FINISHED;
	int32_t new_duty;
	uint32_t elapsedTime = 0;

	if(pin < PWM_MAX)
	{
		if((mgl_pwm_duty_ramp_control[pin].ramp_time == ramp_time) && (mgl_pwm_duty_ramp_control[pin].ramp_value_end == duty))
		{
			user_set_timestamp(&elapsedTime, PRECISION_1MS);
			elapsedTime -= mgl_pwm_duty_ramp_control[pin].ramp_time_start;

			new_duty = sfl_ramp_generator(&mgl_pwm_duty_ramp_control[pin], elapsedTime);

			if( mgl_pwm_duty_ramp_control[pin].ramping )
			{
				ret_val = PWM_RAMP_IN_PROGRESS;
			}
		}
		else
		{
			uint16_t last_duty;
			hal_pwm_readback_duty(pin, &last_duty);
			if(last_duty > HAL_PWM_DUTY_MAX) last_duty = HAL_PWM_DUTY_MAX;
			mgl_pwm_duty_ramp_control[pin].ramp_value_start = last_duty;
			mgl_pwm_duty_ramp_control[pin].ramp_time = ramp_time;

			if(duty > HAL_PWM_DUTY_MAX) duty = HAL_PWM_DUTY_MAX;
			mgl_pwm_duty_ramp_control[pin].ramp_value_end = duty;

			user_set_timestamp(&mgl_pwm_duty_ramp_control[pin].ramp_time_start, PRECISION_1MS);

			mgl_pwm_duty_ramp_control[pin].ramping = true;
			ret_val = PWM_RAMP_IN_PROGRESS;

			new_duty = sfl_ramp_generator(&mgl_pwm_duty_ramp_control[pin], elapsedTime);
		}

		if(new_duty > HAL_PWM_DUTY_MAX)
		{
			new_duty = HAL_PWM_DUTY_MAX;
		}
		else if(new_duty < HAL_PWM_DUTY_MIN)
		{
			new_duty = HAL_PWM_DUTY_MIN;
		}

		user_pwm_set_duty(pin, (uint16_t)new_duty);
	}
	else
	{
		ret_val = PWM_RAMP_CHANNEL_INVALID;
	}

	return ret_val;
}

uint32_t user_pwm_output_force(uint16_t pin, uint16_t forced_output_value)
{
    return (uint32_t) hal_pwm_force_output(pin, forced_output_value);
}

uint32_t user_pwm_set_dither(uint16_t pin, uint16_t duty, uint16_t freq, uint16_t dither_duty, uint16_t dither_freq)
{
	uint32_t ret_val = 0;

    if (pin < PWM_MAX)
    {
        if (dither_duty > duty )
        {
            dither_duty = duty;
        }
        else if (dither_duty > 1000 - duty)
        {
            dither_duty = 1000 - duty;
        }
        else
        {
        }

        if (dither_freq < 10)
        {
        	dither_freq = 10;
        }
        else if (dither_freq > freq / 2)
        {
            dither_freq = freq / 2;
        }
        else
        {
        }

        pwm_vals_t[pin].dither_promille = dither_duty;
        pwm_vals_t[pin].dither_counts = freq / dither_freq;
        pwm_vals_t[pin].pwm_promille_backup = duty;  

        if (freq != pwm_vals_t[pin].pwm_frequency_old && freq)
        {
        	ret_val = user_set_pwm_freq(pin, freq);
            pwm_vals_t[pin].pwm_period = (1000 + freq / 2) / freq;   
        }

        if (dither_duty == 0)
        {
            pwm_vals_t[pin].duty_cycle = duty;
        }
        ret_val = user_set_pwm_duty(pin, duty);
    }

    return ret_val;
}

uint32_t user_pwm_set_global_freq(uint16_t freq)
{
    return (uint32_t) hal_pwm_set_freq_global( freq );
}

uint32_t user_pwm_set_freq(uint16_t pin, uint16_t freq)
{
    enum_HAL_PWM_RETURN_VALUE_t error = HAL_PWM_ERROR_GENERAL;

    if(freq == 0)
    {
        error = hal_pwm_set_duty(pin, 0);
    }
    else
    {
        error = hal_pwm_set_freq(pin, freq);
    }
    return (uint32_t) error;
}

uint32_t user_freq_get_measured_freq(uint16_t pin)
{
    return (user_freq_get_measured_freq_high_res(pin)+500)/1000;
}

uint32_t user_freq_get_measured_freq_high_res(uint16_t pin)
{
    uint32_t freq;
    hal_freq_get_freq(pin, &freq);
    return freq;
}

uint32_t user_freq_get_measured_duty(uint16_t pin)
{
    return user_freq_get_measured_duty_high_res(pin)/10;
}

uint32_t user_freq_get_measured_duty_high_res(uint16_t pin)
{
    uint16_t duty;
    hal_freq_get_duty(pin, &duty);
    return (uint32_t) duty;
}

uint32_t user_freq_get_measured_edge_count(uint16_t pin)
{
	uint32_t edges;
    hal_freq_get_edge_counter_value(pin, &edges);
    return edges;
}

uint32_t user_freq_init_encoder(uint8_t instance, uint8_t channelA, uint8_t channelB, uint8_t mode)
{
	if ( ( ( channelA > PWM_MAX ) && ( channelA < FREQ_MAX) ) || ( ( channelB > PWM_MAX ) && ( channelB < FREQ_MAX) ) )
	{
		return hal_freq_init_encoder(instance,  channelA,  channelB,  mode);

	}
	else
	{
		return HAL_CAN_ERROR_CHANNEL_INVALID;
	}
}


uint32_t user_freq_get_encoder_value(uint8_t instance, int32_t *value)
{
    return hal_freq_get_encoder_value(instance, value);
}

uint32_t user_freq_set_encoder_value( uint8_t instance, int32_t value)
{
    return hal_freq_set_encoder(instance, value);
}

uint32_t user_pwm_current_control(enum_pwm_pin_name pin, uint32_t set_value, uint32_t kp, uint32_t ki)
{
    uint32_t duty_out;

	mgl_pi_controller_data[pin].current_value = adc_results[struct_ftm_config_tbl[pin].adc_pin_name].result_filtered;

    PI_Controller_Discrete(pin, set_value, mgl_pi_controller_data[pin].current_value, kp, ki, 0u, 1000u, &duty_out, &mgl_pi_controller_data[pin].flag0, &mgl_pi_controller_data[pin].flag1);

    hal_pwm_set_duty(pin, duty_out);

    return duty_out;
}

void PI_Controller_Discrete(enum_pwm_pin_name pin, uint32_t soll, uint32_t ist, uint32_t kp, uint32_t ki, uint32_t minOut, uint32_t maxOut, uint32_t *out,
        uint32_t *flag0, uint32_t *flag1)
{
    if ( soll == 0 )
    {
        *flag0 = 0;
        *flag1 = 0;
        *out = 0;
    }
    else
    {
        int rtAdd;
        int rtSub;

        rtSub = (int)soll - (int)ist;
        rtAdd = (((int)ki + (int)kp) * rtSub / 1000 + (int)*flag1) - (int)ki * (int)*flag0 / 1000;

        if ( rtAdd > (int) maxOut )
        {
            rtAdd = (uint32_t) maxOut;
        }
        else if ( rtAdd < (int) minOut )
        {
            rtAdd = (uint32_t) minOut;
        }
        else
        {
        }

        *flag1 = (int)rtAdd;
        *flag0 = rtSub;

        *out = (uint32_t)rtAdd;
    }
}

#if CONTROLLER_WITH_PRECONTROL
void PI_Controller_Discrete_with_precontrol(enum_pwm_pin_name pin, uint32_t soll, uint32_t ist, uint32_t kp, uint32_t ki, uint32_t minOut, uint32_t maxOut, uint32_t *out, uint32_t *flag0, uint32_t *flag1)
{

    uint32_t ausgang;

    mgl_pi_controller_vals[pin].snapshot_current = user_ai_get_cal(AI_INA_OUT1);

    if ( (mgl_pi_controller_vals[pin].snapshot_current - mgl_pi_controller_vals[pin].old_current_value) < 0 ) 
    {
        stromvalue2 = 0;
        mgl_pi_controller_vals[pin].last_current_slope = 0;
    }
    else
    {
        stromvalue2 = mgl_pi_controller_vals[pin].snapshot_current - mgl_pi_controller_vals[pin].old_current_value; 
        mgl_pi_controller_vals[pin].last_current_slope = mgl_pi_controller_vals[pin].snapshot_current - mgl_pi_controller_vals[pin].old_current_value; 
    }

    if ( mgl_pi_controller_vals[pin].last_current_slope > mgl_pi_controller_vals[pin].max_current_slope )
    {
        mgl_pi_controller_vals[pin].max_current_slope = mgl_pi_controller_vals[pin].last_current_slope; 
    }

    stromvalue3 = mgl_pi_controller_vals[pin].max_current_slope; 
    mgl_pi_controller_vals[pin].lower_border = ((mgl_pi_controller_vals[pin].max_current_slope * 100) * (75)) / 10000; 

    if ( (soll - mgl_pi_controller_vals[pin].old_soll) >= mgl_pi_controller_vals[pin].max_current_slope + 50 ) 
    {
        mgl_pi_controller_vals[pin].pre_control = 0;
        step_regulator = 0;
        mgl_pi_controller_vals[pin].cycles = (soll - mgl_pi_controller_vals[pin].old_soll) / 50; 
        mgl_pi_controller_vals[pin].controller_status = 0;
    }

    stromvalue2 = mgl_pi_controller_vals[pin].cycles;

    if ( soll == 0 )
    {
        *flag0 = 0;
        *flag1 = 0;
        ausgang = 0;
        *out = ausgang;
        step_regulator = 0; 
        mgl_pi_controller_vals[pin].pre_control = 0;
        mgl_pi_controller_vals[pin].cycles = 0;
    }
    else
    {

        int delay1_PI = (int) *flag0;
        int delay2_PI = (int) *flag1;

        int rtAdd;
        int rtSub;

        mgl_pi_controller_vals[pin].difference_current = soll - mgl_pi_controller_vals[pin].snapshot_current;

        if ( (mgl_pi_controller_vals[pin].difference_current - 51) < 0 )
        {
            mgl_pi_controller_vals[pin].pre_control = mgl_pi_controller_vals[pin].cycles;
        }

        if ( 0 )
        { 
            step_regulator++; 

            if ( mgl_pi_controller_vals[pin].difference_current >= mgl_pi_controller_vals[pin].max_current_slope
                    || (mgl_pi_controller_vals[pin].controller_status & 0x10) )
            {
                ausgang = 1000;
                mgl_pi_controller_vals[pin].controller_status |= 0x01; 

                if ( mgl_pi_controller_vals[pin].controller_status & 0x02 )
                {
                    mgl_pi_controller_vals[pin].controller_status |= 0x10;
                }

                if ( mgl_pi_controller_vals[pin].controller_status & 0x04 )
                {
                    mgl_pi_controller_vals[pin].controller_status |= 0x08;
                }
            } 
            else if ( (mgl_pi_controller_vals[pin].difference_current < mgl_pi_controller_vals[pin].max_current_slope
                    && mgl_pi_controller_vals[pin].difference_current >= mgl_pi_controller_vals[pin].lower_border)
                    || (mgl_pi_controller_vals[pin].controller_status & 0x08) )
            {
                ausgang = 750 - mgl_pi_controller_vals[pin].duty_adaption;
                mgl_pi_controller_vals[pin].controller_status |= 0x02;

                if ( mgl_pi_controller_vals[pin].controller_status & 0x04 )
                {
                    mgl_pi_controller_vals[pin].controller_status |= 0x08;
                }
            }
            else
            {
                ausgang = 500 - mgl_pi_controller_vals[pin].duty_adaption;
                mgl_pi_controller_vals[pin].controller_status |= 0x04;
            }

            mgl_pi_controller_vals[pin].pre_control++;

            *out = ausgang;
            rtSub = (int) soll - (int) ist;

            delay1_PI = rtSub;

            *flag0 = delay1_PI;
            *flag1 = ausgang - 0; 
        }
        else
        { 
            step_regulator = 255;

            if ( (mgl_pi_controller_vals[pin].snapshot_current > soll) && !(mgl_pi_controller_vals[pin].controller_status & 0x80)
                    && ((int) (soll - mgl_pi_controller_vals[pin].old_soll) >= 0) )
            {
                mgl_pi_controller_vals[pin].duty_adaption += 20;
                stromvalue4 = mgl_pi_controller_vals[pin].duty_adaption;
            }

            mgl_pi_controller_vals[pin].controller_status |= 0x80;

            rtSub = (int) soll - (int) ist;
            rtAdd = (((int) ki + (int) kp) * rtSub / 1000 + delay2_PI) - (int) kp * delay1_PI / 1000;

            if ( rtAdd > (int) maxOut )
            {
                rtAdd = (uint32_t) maxOut;
            }
            else if ( rtAdd < (int) minOut )
            {
                rtAdd = (uint32_t) minOut;
            }
            else
            {
            }

            ausgang = (uint32_t) rtAdd;

            delay2_PI = (int) rtAdd;
            delay1_PI = rtSub;

            *flag0 = delay1_PI;
            *flag1 = delay2_PI;

        }

        *out = ausgang;

    }

    mgl_pi_controller_vals[pin].old_soll = soll; 
    mgl_pi_controller_vals[pin].old_current_value = user_ai_get_cal(AI_INA_OUT1);

}
#endif

