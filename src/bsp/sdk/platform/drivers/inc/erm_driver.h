
#ifndef ERM_DRIVER_H
#define ERM_DRIVER_H


#include "device_registers.h"
#include "status.h"


typedef enum
{
    ERM_EVENT_NONE              = 0U,   
    ERM_EVENT_SINGLE_BIT        = 1U,   
    ERM_EVENT_NON_CORRECTABLE   = 2U    
} erm_ecc_event_t;

typedef struct
{
    bool enableSingleCorrection;    
    bool enableNonCorrectable;      
} erm_interrupt_config_t;

typedef struct
{
    uint8_t channel;                                
    const erm_interrupt_config_t * interruptCfg;    
} erm_user_config_t;


#if defined(__cplusplus)
extern "C" {
#endif

void ERM_DRV_Init(uint32_t instance,
                  uint8_t channelCnt,
                  const erm_user_config_t * userConfigArr);

void ERM_DRV_Deinit(uint32_t instance);

void ERM_DRV_SetInterruptConfig(uint32_t instance,
                                uint8_t channel,
                                erm_interrupt_config_t interruptCfg);

void ERM_DRV_GetInterruptConfig(uint32_t instance,
                                uint8_t channel,
                                erm_interrupt_config_t * const interruptPtr);

void ERM_DRV_ClearEvent(uint32_t instance,
                        uint8_t channel,
                        erm_ecc_event_t eccEvent);

erm_ecc_event_t ERM_DRV_GetErrorDetail(uint32_t instance,
                                       uint8_t channel,
                                       uint32_t * addressPtr);


#if defined(__cplusplus)
}
#endif


#endif 

