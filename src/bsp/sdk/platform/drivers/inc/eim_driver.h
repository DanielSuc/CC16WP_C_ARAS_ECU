

#ifndef EIM_DRIVER_H
#define EIM_DRIVER_H

#include <stddef.h>
#include "device_registers.h"




#define EIM_CHECKBITMASK_DEFAULT    (0x01U)
#define EIM_DATAMASK_DEFAULT        (0x00U)

typedef struct
{
    uint8_t channel;      
    uint8_t checkBitMask; 
    uint32_t dataMask;    
#if defined(FEATURE_EIM_DATAMASK1)
    uint32_t dataMask1;   
#endif
    bool enable;          
} eim_user_channel_config_t;


#if defined(__cplusplus)
extern "C"
{
#endif

void EIM_DRV_Init(uint32_t instance,
                  uint8_t channelCnt,
                  const eim_user_channel_config_t *channelConfigArr);

void EIM_DRV_Deinit(uint32_t instance);

void EIM_DRV_ConfigChannel(uint32_t instance,
                           const eim_user_channel_config_t *userChannelConfig);

void EIM_DRV_GetChannelConfig(uint32_t instance,
                              uint8_t channel,
                              eim_user_channel_config_t *channelConfig);

void EIM_DRV_GetDefaultConfig(uint8_t channel,
                              eim_user_channel_config_t *channelConfig);


#if defined(__cplusplus)
}
#endif


#endif 

