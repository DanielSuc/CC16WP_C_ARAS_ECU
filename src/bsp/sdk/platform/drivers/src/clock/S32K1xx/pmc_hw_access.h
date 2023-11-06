
#if !defined(PMC_HW_ACCESS_H)
#define PMC_HW_ACCESS_H

#include "device_registers.h"
#include <stdbool.h>
#include <stddef.h>




#if defined(__cplusplus)
extern "C" {
#endif 


static inline void PMC_SetLpoMode(PMC_Type* const baseAddr, const bool enable)
{
    uint8_t regValue = baseAddr->REGSC;
    regValue &= (uint8_t)(~(PMC_REGSC_LPODIS_MASK));
    regValue |= (uint8_t)PMC_REGSC_LPODIS(enable?0U:1U);
    baseAddr->REGSC = regValue;
}

static inline bool PMC_GetLpoMode(const PMC_Type * const baseAddr)
{
    uint8_t regValue = baseAddr->REGSC;
    regValue = (uint8_t)((regValue & PMC_REGSC_LPODIS_MASK) >> PMC_REGSC_LPODIS_SHIFT);
    return (regValue == 0U) ? true : false;
}


static inline void PMC_SetLpoTrimValue(PMC_Type* const baseAddr, const int8_t decimalValue)
{
    int8_t decValue = decimalValue;
    uint8_t lpotrim, trimval, regValue;

    if (decValue < 0)
    {
        lpotrim = ((uint8_t)1U) << (PMC_LPOTRIM_LPOTRIM_WIDTH);
        decValue = (int8_t)(decValue + (int8_t)(lpotrim));
    }
    trimval = (uint8_t)decValue;

    DEV_ASSERT(trimval <= (1U << PMC_LPOTRIM_LPOTRIM_WIDTH));

    regValue = baseAddr->LPOTRIM;
    regValue &= (uint8_t)(~(PMC_LPOTRIM_LPOTRIM_MASK));
    regValue |= (uint8_t)PMC_LPOTRIM_LPOTRIM(trimval);
    baseAddr->LPOTRIM = regValue;
}


#if defined(__cplusplus)
}
#endif 



#endif 


