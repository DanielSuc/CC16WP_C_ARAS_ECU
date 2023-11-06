#ifndef SRC_USER_API_AI_H_
#define SRC_USER_API_AI_H_
#include "hal_data_types.h"
#include "io_tables.h"
#include "adc_app.h"


void user_ai_set_measurement_range(enum_adc_pin_name pin, uint8_t range);


uint16_t user_ai_get(enum_adc_pin_name pin);
#define user_ai_get_digits( pin ) user_ai_get( pin )


uint16_t user_ai_get_mv(enum_adc_pin_name pin);


uint16_t user_ai_get_cal(enum_adc_pin_name pin);

uint16_t user_ai_get_filtered(enum_adc_pin_name pin);


#endif 

