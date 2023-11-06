#ifndef SFL_TIMER_H
#define SFL_TIMER_H

#include "hal_tick.h"

typedef enum
{
    SFL_TIMER_ERR_OK									=0u,    
	SFL_TIMER_ERR_PRECISION_INVALID,						    
	SFL_TIMER_ERR_OVERFLOW,                                     

    SFL_TIMER_ERR_GENERAL
} enum_SFL_TIMER_ERR;


void sfl_timer_init( void );

void sfl_timer_deinit( void );

enum_SFL_TIMER_ERR sfl_timer_set_timestamp( uint32_t* timestamp, enum_HAL_PRECISION precision );

enum_SFL_TIMER_ERR sfl_timer_get_time_elapsed( uint32_t* time_elapsed, uint32_t timestamp_t0, enum_HAL_PRECISION precision );

enum_SFL_TIMER_ERR sfl_timer_time_elapsed( uint8_t* elapsed, uint32_t timestamp_t0, uint32_t span, enum_HAL_PRECISION precision );

enum_SFL_TIMER_ERR sfl_timer_wait( uint32_t wait_time, enum_HAL_PRECISION precision );

enum_SFL_TIMER_ERR sfl_timer_get_roundtrip_time( uint32_t* roundtrip_time, enum_HAL_PRECISION precision );

#endif

