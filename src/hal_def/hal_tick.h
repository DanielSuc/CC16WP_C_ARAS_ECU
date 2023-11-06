#ifndef HAL_TICK_H
#define HAL_TICK_H

#include "hal_data_types.h"



typedef enum
{
    HAL_TICK_OK                         = 0u,   
    HAL_TICK_ERROR_GENERAL                  ,   
    HAL_TICK_ERROR_INIT_FAILED              ,   
    HAL_TICK_ERROR_DEINIT_FAILED            ,   
    HAL_TICK_ERROR_PRECISION_INVALID        ,   
    HAL_TICK_ERROR_NOT_IMPLEMENTED              

} enum_HAL_TICK_RETURN_VALUE;


typedef enum
{
    HAL_PRECISION_1US                   = 0u,   
    HAL_PRECISION_10US                      ,   
    HAL_PRECISION_100US                     ,   
    HAL_PRECISION_1MS                       ,   
    HAL_PRECISION_10MS                      ,   
    HAL_PRECISION_100MS                     ,   
    HAL_PRECISION_1S                            
} enum_HAL_PRECISION;


typedef struct
{
    uint32_t tick_1us;                          
    uint32_t tick_10us;                         
    uint32_t tick_100us;                        
    uint32_t tick_1ms;                          
    uint32_t tick_10ms;                         
    uint32_t tick_100ms;                        
    uint32_t tick_1s;                           
    enum_HAL_PRECISION precision;               
} struct_hal_tick_handle;

typedef void (*callback_timer_1ms_t)(void);


enum_HAL_TICK_RETURN_VALUE hal_tick_init(void);

enum_HAL_TICK_RETURN_VALUE hal_tick_deinit(void);

enum_HAL_TICK_RETURN_VALUE hal_get_timestamp(uint32_t* timestamp, enum_HAL_PRECISION precision);


void hal_tick_set_tick_next(uint32_t* tick_temp, uint32_t* tick_temp_next, uint32_t* tick_next);

void hal_tick_set_tick(enum_HAL_PRECISION precision);

void set_callback_timer_1ms(callback_timer_1ms_t callback);

void set_callback_timer_lin_1ms(callback_timer_1ms_t callback);

#endif



