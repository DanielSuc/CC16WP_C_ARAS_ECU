#ifndef HAL_WATCHDOG_H
#define HAL_WATCHDOG_H


#include "hal_data_types.h"

#define WATCHDOG_DEAD_SIGNAL_ITER_MAX	3u

#define WATCHDOG_KICK_REQUEST			( ((wdog_reg_t)1u) << (sizeof(wdog_reg_t)*8u-1) )


typedef enum
{
    HAL_WATCHDOG_OK                 = 0u,   
	HAL_WATCHDOG_NOT_INITIALIZED        ,   
	HAL_WATCHDOG_NOT_KICKED             ,   
	HAL_WATCHDOG_INVALID_SIGNAL             

} enum_HAL_WATCHDOG_RETURN_VALUE;


typedef enum
{
    HAL_WATCHDOG_INTERNAL           = 0u,   
    HAL_WATCHDOG_EXTERNAL               ,   
} enum_HAL_WATCHDOG_TYPE;

typedef uint32_t wdog_reg_t;

typedef struct
{
	wdog_reg_t reg;							
	wdog_reg_t mask;						
	enum_HAL_WATCHDOG_TYPE wdt_type;	    
} struct_watchdog_t;



enum_HAL_WATCHDOG_RETURN_VALUE hal_watchdog_start( enum_HAL_WATCHDOG_TYPE wdog_type, uint16_t pin );

enum_HAL_WATCHDOG_RETURN_VALUE hal_watchdog_mask( wdog_reg_t mask_bit );

enum_HAL_WATCHDOG_RETURN_VALUE hal_watchdog_unmask( wdog_reg_t mask_bit );

enum_HAL_WATCHDOG_RETURN_VALUE hal_watchdog_signal( wdog_reg_t signal_bit );

#endif

