

#ifndef EWM_HW_ACCESS_H
#define EWM_HW_ACCESS_H

#include "ewm_driver.h"





#if defined(__cplusplus)
extern "C" {
#endif

static inline void EWM_Refresh(EWM_Type * const base)
{
    base->SERV = FEATURE_EWM_KEY_FIRST_BYTE;
    base->SERV = FEATURE_EWM_KEY_SECOND_BYTE;
}

static inline bool EWM_IsEnabled(const EWM_Type * const base)
{
    return ((base->CTRL & EWM_CTRL_EWMEN_MASK) >> EWM_CTRL_EWMEN_SHIFT) != 0U;
}

static inline void EWM_SetControl(EWM_Type * const base, uint8_t value)
{
    base->CTRL = value;
}

static inline uint8_t EWM_GetControl(const EWM_Type * const base)
{
    return base->CTRL;
}

static inline void EWM_SetCompareLow(EWM_Type * const base, uint8_t value)
{
    base->CMPL = value;
}


static inline void EWM_SetCompareHigh(EWM_Type * const base, uint8_t value)
{
    base->CMPH = value;
}


static inline void EWM_SetPrescaler(EWM_Type * const base, uint8_t value)
{
    base->CLKPRESCALER = value;
}



#if defined(__cplusplus)
}
#endif


#endif 

