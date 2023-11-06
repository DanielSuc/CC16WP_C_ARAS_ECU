
#ifndef APP_FTM_APP_H_
#define APP_FTM_APP_H_

#include "flexTimerCom1.h"


typedef struct {
  uint16_t 	dither_promille;		
  uint16_t 	dither_counts;			
  uint16_t	dither_counter;			
  uint16_t 	pwm_promille_backup;	
  uint16_t 	pwm_frequency_old;		
  int8_t  	dither_stat;			
  uint16_t 	duty_cycle;				
  uint16_t 	pwm_period;				
}struct_pwm_vals_def;

extern struct_pwm_vals_def pwm_vals_t[PWM_MAX + 1];


uint32_t change_pin_to_ftm(enum_pin_name pin);


uint32_t change_pin_to_adc(enum_pin_name pin);

extern void encoder_Callback(ic_event_t event, uint8_t  instance, uint8_t channel);

void FTM_IRQHandler(uint8_t module);


void FTM0_IRQHandler(void);


void FTM1_IRQHandler(void);


void FTM2_IRQHandler(void);


void FTM3_IRQHandler(void);


void FTM4_IRQHandler(void);


void FTM5_IRQHandler(void);


void FTM6_IRQHandler(void);


void FTM7_IRQHandler(void);



#endif 

