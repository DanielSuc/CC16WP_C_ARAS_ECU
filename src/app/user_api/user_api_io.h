#ifndef SRC_USER_API_IO_H_
#define SRC_USER_API_IO_H_
#include <stdint.h>
#include "hal_io.h"
#include "io_tables.h"


void user_do_set(uint16_t pin, uint8_t state);
#define user_io_set_do(pin ,state) user_do_set(pin ,state)

uint8_t user_do_readback(uint16_t pin);
#define user_io_readback_do(pin) user_do_readback(pin)

uint8_t user_di_get(uint16_t pin);
#define user_io_get_di(pin) user_di_get(pin)

enum_adc_pin_name user_di_find_adc_pin(uint16_t pin);

#endif 

