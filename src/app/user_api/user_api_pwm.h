#ifndef SRC_USER_API_PWM_H_
#define SRC_USER_API_PWM_H_
#include <stdint.h>
#include "hal_pwm.h"
#include "io_tables.h"

typedef struct
{
    uint32_t current_value;
    uint32_t duty_out_before;
    uint32_t duty_out_after;
} pi_regulator_info_t;

typedef struct
{
    uint32_t current_value;
    uint32_t flag0;
    uint32_t flag1;
} pi_regulator_data_t;

typedef enum{
	PWM_RAMP_FINISHED = 0,
	PWM_RAMP_IN_PROGRESS,
	PWM_RAMP_CHANNEL_INVALID
}enum_pwm_ramp_status_t;

#if CONTROLLER_WITH_PRECONTROL
typedef struct {
  uint8_t pre_control;
  uint8_t cycles;
  uint8_t controller_status;
  uint16_t old_soll;
  uint16_t  snapshot_current;
  int16_t difference_current;
  uint16_t max_current_slope;
  uint16_t last_current_slope;
  uint16_t old_current_value;
  uint32_t lower_border;
  uint16_t duty_adaption;
}pi_controller_t;
#endif




uint32_t user_pwm_set_pwm(uint16_t pin, uint16_t freq, uint16_t duty);
#define user_set_pwm( pin, freq, duty ) user_pwm_set_pwm( pin, freq, duty )


uint32_t user_pwm_set_pwm_ramped(uint16_t pin, uint16_t freq, uint16_t duty, uint16_t ramp_time);

uint32_t user_pwm_set_pwm_immediate(uint16_t pin, uint16_t freq, uint16_t duty);


uint32_t user_pwm_set_duty(uint16_t pin, uint16_t duty);
#define user_set_pwm_duty( pin, duty ) user_pwm_set_duty( pin, duty )

uint32_t user_pwm_set_duty_ramped(uint16_t pin, uint16_t duty, uint16_t ramp_time);


uint32_t user_pwm_output_force(uint16_t pin, uint16_t forced_output_value);


uint32_t user_pwm_set_dither(uint16_t pin, uint16_t duty, uint16_t freq, uint16_t dither_duty, uint16_t dither_freq);


uint32_t  user_pwm_set_global_freq(uint16_t freq);
#define user_set_pwm_freq_global( freq ) user_pwm_set_global_freq( freq )

uint32_t user_pwm_set_freq(uint16_t pin, uint16_t freq);
#define user_set_pwm_freq( pin, freq ) user_pwm_set_freq( pin, freq )

uint32_t user_freq_get_measured_freq(uint16_t pin);
#define user_get_measured_freq( pin ) user_freq_get_measured_freq( pin )

uint32_t user_freq_get_measured_freq_high_res(uint16_t pin);


uint32_t user_freq_get_measured_duty(uint16_t pin);
#define user_get_measured_duty( pin ) user_freq_get_measured_duty( pin )

uint32_t user_freq_get_measured_duty_high_res(uint16_t pin);


uint32_t user_freq_get_measured_edge_count(uint16_t pin);
#define user_get_measured_edge_count( pin ) user_freq_get_measured_edge_count( pin )

uint32_t user_freq_init_encoder(uint8_t instance, uint8_t channelA, uint8_t channelB, uint8_t mode);

uint32_t user_freq_get_encoder_value(uint8_t instance, int32_t *value);

uint32_t user_freq_set_encoder_value(uint8_t instance, int32_t value);

uint32_t user_pwm_current_control(enum_pwm_pin_name pin, uint32_t set_value, uint32_t kp, uint32_t ki);

void PI_Controller_Discrete(enum_pwm_pin_name pin, uint32_t soll, uint32_t ist, uint32_t kp, uint32_t ki, uint32_t minOut, uint32_t maxOut, uint32_t *out, uint32_t *flag0, uint32_t *flag1);

void PI_Controller_Discrete_with_precontrol(enum_pwm_pin_name pin, uint32_t soll, uint32_t ist, uint32_t kp, uint32_t ki, uint32_t minOut, uint32_t maxOut, uint32_t *out, uint32_t *flag0, uint32_t *flag1);



#endif 

