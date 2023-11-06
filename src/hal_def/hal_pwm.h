#ifndef HAL_PWM_H
#define HAL_PWM_H

#include "hal_data_types.h"
#include "callbacks.h"

#define HAL_PWM_DUTY_MIN                           0u   
#define HAL_PWM_DUTY_MAX                        1000u   
#define HAL_PWM_FREQ_MIN                           0u   
#define HAL_PWM_FREQ_MAX                       30000u   


typedef enum
{
    HAL_PWM_OK                      = 0u,   
    HAL_PWM_ERROR_GENERAL               ,   
    HAL_PWM_ERROR_INIT_FAILED           ,   
    HAL_PWM_ERROR_DEINIT_FAILED         ,   
    HAL_PWM_ERROR_CHANNEL_INVALID       ,   
    HAL_PWM_ERROR_NO_CHANNEL_LEFT       ,   
    HAL_PWM_ERROR_PWM_SOURCE_INVALID    ,   
    HAL_PWM_ERROR_PWM_MASTER            ,   
    HAL_PWM_ERROR_NOT_IMPLEMENTED           

} enum_HAL_PWM_RETURN_VALUE_t;

typedef enum
{
	HAL_PWM_RANGE_1			= 0x00U,	
	HAL_PWM_RANGE_2			= 0x01U,	
	HAL_PWM_RANGE_3			= 0x02U,	
}enum_HAL_PWM_RANGE_t;

typedef enum
{
    HAL_NO_PIN_CONTROL          = 0x00U,       
    HAL_RISING_EDGE             = 0x01U,       
    HAL_FALLING_EDGE            = 0x02U,       
    HAL_BOTH_EDGES              = 0x03U        
} enum_HAL_EDGE_ALIGNMENT_MODE_t;

typedef enum
{
	HAL_ENCODER_STATE_A_LOW_B_LOW = 0,
	HAL_ENCODER_STATE_A_HIGH_B_LOW,
	HAL_ENCODER_STATE_A_HIGH_B_HIGH,
	HAL_ENCODER_STATE_A_LOW_B_HIGH
}enum_encoder_state_t;

typedef enum
{
	HAL_ENCODER_MODE_1X = 0,
	HAL_ENCODER_MODE_2X,
	HAL_ENCODER_MODE_4X,
	HAL_ENCODER_MODE_MAX
}enum_encoder_mode_t;

typedef struct
{
    uint8_t inputChannelA;              
    uint8_t inputChannelAInstance;      
    uint8_t inputChannelB;              
    enum_encoder_state_t state;         
    uint8_t mode;                       
    int32_t counter4X;                  
} hal_encoder_channel_t;




uint32_t get_ftm_setting_ptr(uint32_t pwm_pin_name);

enum_HAL_PWM_RETURN_VALUE_t hal_pwm_init(uint32_t pwm_count);

enum_HAL_PWM_RETURN_VALUE_t hal_pwm_deinit(void);

enum_HAL_PWM_RETURN_VALUE_t hal_freq_init(uint32_t freq_count);

enum_HAL_PWM_RETURN_VALUE_t hal_freq_deinit(void);


enum_HAL_PWM_RETURN_VALUE_t hal_freq_get_duty(uint16_t pin, uint16_t* const ptr_duty);

enum_HAL_PWM_RETURN_VALUE_t hal_pwm_set_duty(uint16_t pin, uint16_t duty);

enum_HAL_PWM_RETURN_VALUE_t hal_pwm_readback_duty(uint16_t pin, uint16_t* const ptr_duty);


enum_HAL_PWM_RETURN_VALUE_t hal_pwm_force_output(uint16_t pin, uint16_t forced_output_value);

enum_HAL_PWM_RETURN_VALUE_t hal_pwm_update_now(uint16_t pin, uint8_t enable);

enum_HAL_PWM_RETURN_VALUE_t hal_pwm_readback_do(uint16_t pin, uint8_t* ptr_state);

enum_HAL_PWM_RETURN_VALUE_t hal_pwm_readback_freq(uint16_t pin, uint32_t* const ptr_freq);

enum_HAL_PWM_RETURN_VALUE_t hal_pwm_set_freq_global(uint32_t freq);

enum_HAL_PWM_RETURN_VALUE_t hal_pwm_set_freq(uint16_t pin, uint32_t freq);

enum_HAL_PWM_RETURN_VALUE_t hal_freq_get_freq(uint16_t pin, uint32_t* const ptr_freq);

enum_HAL_PWM_RETURN_VALUE_t hal_pwm_process_cyclic(void);

enum_HAL_PWM_RETURN_VALUE_t hal_freq_config_freq_measurment( uint8_t instance, enum_HAL_PWM_RANGE_t range );

enum_HAL_PWM_RETURN_VALUE_t hal_freq_edge_counting(uint16_t pin, uint32_t* ptr_edge, uint16_t* const t_measure);

enum_HAL_PWM_RETURN_VALUE_t hal_freq_init_ftm_edge(uint16_t pin, enum_HAL_EDGE_ALIGNMENT_MODE_t edge_select );

enum_HAL_PWM_RETURN_VALUE_t hal_freq_get_edge_counter_value(uint16_t pin, uint32_t* value);

enum_HAL_PWM_RETURN_VALUE_t hal_freq_set_edge_counter_value(uint16_t pin, uint32_t value);

enum_HAL_PWM_RETURN_VALUE_t hal_freq_init_encoder(uint8_t instance, uint8_t channelA, uint8_t channelB, uint8_t mode);

enum_HAL_PWM_RETURN_VALUE_t hal_freq_process_encoder(ic_event_t event, uint8_t  instance, uint8_t channel);

enum_HAL_PWM_RETURN_VALUE_t hal_freq_get_encoder_value(uint8_t instance, int32_t *value);

enum_HAL_PWM_RETURN_VALUE_t hal_freq_set_encoder(uint8_t instance, int32_t value);


#endif

