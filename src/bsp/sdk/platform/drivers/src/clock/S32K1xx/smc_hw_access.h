
#if !defined(SMC_HW_ACCESS_H)
#define SMC_HW_ACCESS_H

#include "device_registers.h"
#include <stdbool.h>
#include <stddef.h>




#if defined(__cplusplus)
extern "C" {
#endif 


static inline uint32_t SMC_GetCurrentRunningMode(const SMC_Type* const baseAddr)
{
    return (baseAddr->PMSTAT & SMC_PMSTAT_PMSTAT_MASK) >> SMC_PMSTAT_PMSTAT_SHIFT;    
}


#if defined(__cplusplus)
}
#endif 



#endif 


