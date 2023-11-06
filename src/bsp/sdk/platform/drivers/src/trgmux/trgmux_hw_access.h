
#ifndef TRGMUX_HW_ACCESS_H
#define TRGMUX_HW_ACCESS_H


#include "trgmux_driver.h"




#if defined(__cplusplus)
extern "C" {
#endif

status_t TRGMUX_Init(TRGMUX_Type * const base);

void TRGMUX_SetTrigSourceForTargetModule(TRGMUX_Type * const base,
                                         const trgmux_trigger_source_t triggerSource,
                                         const trgmux_target_module_t targetModule);

trgmux_trigger_source_t TRGMUX_GetTrigSourceForTargetModule(const TRGMUX_Type * const base,
                                                            const trgmux_target_module_t targetModule);

void TRGMUX_SetLockForTargetModule(TRGMUX_Type * const base,
                                   const trgmux_target_module_t targetModule);

bool TRGMUX_GetLockForTargetModule(const TRGMUX_Type * const base,
                                   const trgmux_target_module_t targetModule);

#if defined(__cplusplus)
}
#endif


#endif 

