#ifndef HAL_MATH_H
#define HAL_MATH_H

#include "hal_data_types.h"

#define CCITT_MASK 0x1021

#define CRC_MASK CCITT_MASK 



void hal_math_init( void );

uint16_t hal_math_get_16bitcrc( const uint8_t* ptr_buffer, uint16_t u16_start_value, uint32_t u32_byte_count );

uint16_t hal_math_get_ac_16bitcrc( const uint8_t* ptr_buffer, uint16_t u16_start_value, uint32_t u32_byte_count );

#endif 

