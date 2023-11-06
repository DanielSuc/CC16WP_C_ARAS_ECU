
#ifndef LPTMR_DRIVER_H
#define LPTMR_DRIVER_H

#include <stdint.h>
#include <stdbool.h>
#include "status.h"
#include "device_registers.h"



typedef enum {
    LPTMR_PINSELECT_TRGMUX  = 0x00u, 
#if FEATURE_LPTMR_HAS_INPUT_ALT1_SELECTION
    LPTMR_PINSELECT_ALT1    = 0x01u, 
#endif
    LPTMR_PINSELECT_ALT2    = 0x02u, 
    LPTMR_PINSELECT_ALT3    = 0x03u  
} lptmr_pinselect_t;

typedef enum {
    LPTMR_PINPOLARITY_RISING    = 0u, 
    LPTMR_PINPOLARITY_FALLING   = 1u  
} lptmr_pinpolarity_t;

typedef enum {
    LPTMR_WORKMODE_TIMER        = 0u, 
    LPTMR_WORKMODE_PULSECOUNTER = 1u  
} lptmr_workmode_t;

typedef enum {
    LPTMR_PRESCALE_2                        = 0x00u, 
    LPTMR_PRESCALE_4_GLITCHFILTER_2         = 0x01u, 
    LPTMR_PRESCALE_8_GLITCHFILTER_4         = 0x02u, 
    LPTMR_PRESCALE_16_GLITCHFILTER_8        = 0x03u, 
    LPTMR_PRESCALE_32_GLITCHFILTER_16       = 0x04u, 
    LPTMR_PRESCALE_64_GLITCHFILTER_32       = 0x05u, 
    LPTMR_PRESCALE_128_GLITCHFILTER_64      = 0x06u, 
    LPTMR_PRESCALE_256_GLITCHFILTER_128     = 0x07u, 
    LPTMR_PRESCALE_512_GLITCHFILTER_256     = 0x08u, 
    LPTMR_PRESCALE_1024_GLITCHFILTER_512    = 0x09u, 
    LPTMR_PRESCALE_2048_GLITCHFILTER_1024   = 0x0Au, 
    LPTMR_PRESCALE_4096_GLITCHFILTER_2048   = 0x0Bu, 
    LPTMR_PRESCALE_8192_GLITCHFILTER_4096   = 0x0Cu, 
    LPTMR_PRESCALE_16384_GLITCHFILTER_8192  = 0x0Du, 
    LPTMR_PRESCALE_32768_GLITCHFILTER_16384 = 0x0Eu, 
    LPTMR_PRESCALE_65536_GLITCHFILTER_32768 = 0x0Fu  
} lptmr_prescaler_t;

typedef enum {
    LPTMR_CLOCKSOURCE_SIRCDIV2  = 0x00u, 
    LPTMR_CLOCKSOURCE_1KHZ_LPO  = 0x01u, 
    LPTMR_CLOCKSOURCE_RTC       = 0x02u, 
    LPTMR_CLOCKSOURCE_PCC       = 0x03u  
} lptmr_clocksource_t;

typedef enum
{
    LPTMR_COUNTER_UNITS_TICKS           = 0x00U,
    LPTMR_COUNTER_UNITS_MICROSECONDS    = 0x01U
} lptmr_counter_units_t;

typedef struct
{
    bool dmaRequest;                    
    bool interruptEnable;               
    bool freeRun;                       
    lptmr_workmode_t workMode;          
    lptmr_clocksource_t clockSelect;    
    lptmr_prescaler_t prescaler;        
    bool bypassPrescaler;               
    uint32_t compareValue;              
    lptmr_counter_units_t counterUnits; 
    lptmr_pinselect_t pinSelect;        
    lptmr_pinpolarity_t pinPolarity;    
} lptmr_config_t;


#if defined(__cplusplus)
extern "C" {
#endif

void LPTMR_DRV_InitConfigStruct(lptmr_config_t * const config);

void LPTMR_DRV_Init(const uint32_t instance,
                    const lptmr_config_t * const config,
                    const bool startCounter);

void LPTMR_DRV_SetConfig(const uint32_t instance,
                         const lptmr_config_t * const config);

void LPTMR_DRV_GetConfig(const uint32_t instance,
                         lptmr_config_t * const config);

void LPTMR_DRV_Deinit(const uint32_t instance);

status_t LPTMR_DRV_SetCompareValueByCount(const uint32_t instance,
                                          const uint16_t compareValueByCount);

void LPTMR_DRV_GetCompareValueByCount(const uint32_t instance,
                                      uint16_t * const compareValueByCount);

status_t LPTMR_DRV_SetCompareValueByUs(const uint32_t instance,
                                       const uint32_t compareValueUs);

void LPTMR_DRV_GetCompareValueByUs(const uint32_t instance,
                                   uint32_t * const compareValueUs);

bool LPTMR_DRV_GetCompareFlag(const uint32_t instance);

void LPTMR_DRV_ClearCompareFlag(const uint32_t instance);

bool LPTMR_DRV_IsRunning(const uint32_t instance);

void LPTMR_DRV_SetInterrupt(const uint32_t instance,
                            const bool enableInterrupt);

uint16_t LPTMR_DRV_GetCounterValueByCount(const uint32_t instance);

void LPTMR_DRV_StartCounter(const uint32_t instance);

void LPTMR_DRV_StopCounter(const uint32_t instance);

void LPTMR_DRV_SetPinConfiguration(const uint32_t instance,
                                   const lptmr_pinselect_t pinSelect,
                                   const lptmr_pinpolarity_t pinPolarity);

#if defined(__cplusplus)
}
#endif



#endif 

