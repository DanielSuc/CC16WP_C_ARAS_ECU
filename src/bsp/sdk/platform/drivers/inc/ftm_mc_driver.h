
#ifndef FTM_MC_DRIVER_H
#define FTM_MC_DRIVER_H

#include "ftm_common.h"



typedef struct
{
    ftm_config_mode_t mode;                 
    uint16_t initialValue;                  
    uint16_t finalValue;                    
} ftm_timer_param_t;


#if defined(__cplusplus)
extern "C" {
#endif

status_t FTM_DRV_InitCounter(uint32_t instance,
                             const ftm_timer_param_t * timer);

status_t FTM_DRV_CounterStart(uint32_t instance);

status_t FTM_DRV_CounterStop(uint32_t instance);

uint32_t FTM_DRV_CounterRead(uint32_t instance);

void FTM_MC_DRV_GetDefaultConfig(ftm_timer_param_t * const config);

#if defined(__cplusplus)
}
#endif



#endif 

