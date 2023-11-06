

#ifndef LPIT_DRIVER_H
#define LPIT_DRIVER_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "status.h"


#define MAX_PERIOD_COUNT                    (0xFFFFFFFFU)
#define MAX_PERIOD_COUNT_IN_DUAL_16BIT_MODE (0x1FFFEU)
#define MAX_PERIOD_COUNT_16_BIT (0xFFFFU)

typedef enum
{
    LPIT_PERIODIC_COUNTER      = 0x00U,  
    LPIT_DUAL_PERIODIC_COUNTER = 0x01U,  
    LPIT_TRIGGER_ACCUMULATOR   = 0x02U,  
    LPIT_INPUT_CAPTURE         = 0x03U   
} lpit_timer_modes_t;

typedef enum
{
    LPIT_TRIGGER_SOURCE_EXTERNAL = 0x00U, 
    LPIT_TRIGGER_SOURCE_INTERNAL = 0x01U  
}  lpit_trigger_source_t;

typedef enum
{
    LPIT_PERIOD_UNITS_COUNTS        = 0x00U, 
    LPIT_PERIOD_UNITS_MICROSECONDS  = 0x01U  
} lpit_period_units_t;

typedef struct
{
    bool enableRunInDebug; 
    bool enableRunInDoze;  
} lpit_user_config_t;

typedef struct
{
    lpit_timer_modes_t timerMode;        
    lpit_period_units_t periodUnits;     
    uint32_t period;                     
    lpit_trigger_source_t triggerSource; 
    uint32_t triggerSelect;              
    bool enableReloadOnTrigger;          
    bool enableStopOnInterrupt;          
    bool enableStartOnTrigger;           
    bool chainChannel;                   
    bool isInterruptEnabled;             
} lpit_user_channel_config_t;


#if defined(__cplusplus)
extern "C" {
#endif


void LPIT_DRV_GetDefaultConfig(lpit_user_config_t * const config);

void LPIT_DRV_GetDefaultChanConfig(lpit_user_channel_config_t * const config);

void LPIT_DRV_Init(uint32_t instance,
                   const lpit_user_config_t * userConfig);

void LPIT_DRV_Deinit(uint32_t instance);

status_t LPIT_DRV_InitChannel(uint32_t instance,
                              uint32_t channel,
                              const lpit_user_channel_config_t * userChannelConfig);



void LPIT_DRV_StartTimerChannels(uint32_t instance,
                                 uint32_t mask);

void LPIT_DRV_StopTimerChannels(uint32_t instance,
                                uint32_t mask);



status_t LPIT_DRV_SetTimerPeriodByUs(uint32_t instance,
                                     uint32_t channel,
                                     uint32_t periodUs);

status_t LPIT_DRV_SetTimerPeriodInDual16ModeByUs(uint32_t instance,
                                                 uint32_t channel,
                                                 uint16_t periodHigh,
                                                 uint16_t periodLow);

uint64_t LPIT_DRV_GetTimerPeriodByUs(uint32_t instance,
                                     uint32_t channel);

uint64_t LPIT_DRV_GetCurrentTimerUs(uint32_t instance,
                                    uint32_t channel);

void LPIT_DRV_SetTimerPeriodByCount(uint32_t instance,
                                    uint32_t channel,
                                    uint32_t count);

void LPIT_DRV_SetTimerPeriodInDual16ModeByCount(uint32_t instance,
                                                uint32_t channel,
                                                uint16_t periodHigh,
                                                uint16_t periodLow);

uint32_t LPIT_DRV_GetTimerPeriodByCount(uint32_t instance,
                                        uint32_t channel);

uint32_t LPIT_DRV_GetCurrentTimerCount(uint32_t instance,
                                       uint32_t channel);


void LPIT_DRV_EnableTimerChannelInterrupt(uint32_t instance,
                                          uint32_t mask);

void LPIT_DRV_DisableTimerChannelInterrupt(uint32_t instance,
                                           uint32_t mask);

uint32_t LPIT_DRV_GetInterruptFlagTimerChannels(uint32_t instance,
                                                uint32_t mask);

void LPIT_DRV_ClearInterruptFlagTimerChannels(uint32_t instance,
                                              uint32_t mask);


#if defined(__cplusplus)
}
#endif


#endif 

