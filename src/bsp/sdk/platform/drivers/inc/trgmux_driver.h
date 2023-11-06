
#ifndef TRGMUX_DRIVER_H
#define TRGMUX_DRIVER_H



#include <stdint.h>
#include <stdbool.h>
#include "status.h"
#include "device_registers.h"




typedef enum trgmux_trigger_source_e trgmux_trigger_source_t;

typedef enum trgmux_target_module_e trgmux_target_module_t;

typedef struct
{
    trgmux_trigger_source_t triggerSource; 
    trgmux_target_module_t targetModule;   
    bool lockTargetModuleReg;              
} trgmux_inout_mapping_config_t;

typedef struct
{
    uint8_t numInOutMappingConfigs;                           
    const trgmux_inout_mapping_config_t * inOutMappingConfig; 
} trgmux_user_config_t;


#if defined(__cplusplus)
extern "C" {
#endif


status_t TRGMUX_DRV_Init(const uint32_t instance,
                         const trgmux_user_config_t * const trgmuxUserConfig);

status_t TRGMUX_DRV_Deinit(const uint32_t instance);

status_t TRGMUX_DRV_SetTrigSourceForTargetModule(const uint32_t instance,
                                                 const trgmux_trigger_source_t triggerSource,
                                                 const trgmux_target_module_t targetModule);

trgmux_trigger_source_t TRGMUX_DRV_GetTrigSourceForTargetModule(const uint32_t instance,
                                                                const trgmux_target_module_t targetModule);

void TRGMUX_DRV_SetLockForTargetModule(const uint32_t instance,
                                       const trgmux_target_module_t targetModule);

bool TRGMUX_DRV_GetLockForTargetModule(const uint32_t instance,
                                       const trgmux_target_module_t targetModule);

void TRGMUX_DRV_GenSWTrigger(const uint32_t instance);

#if defined(__cplusplus)
}
#endif


#endif 

