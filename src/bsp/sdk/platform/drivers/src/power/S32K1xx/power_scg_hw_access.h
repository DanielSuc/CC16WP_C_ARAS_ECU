
#ifndef POWER_SCG_HW_ACCESS_H
#define POWER_SCG_HW_ACCESS_H

#include "device_registers.h"




#if defined(__cplusplus)
extern "C" {
#endif 

#if FEATURE_HAS_SPLL_CLK
static inline void SCG_SetEnableSPLL(bool enable)
{
    uint32_t regValue = SCG->SPLLCSR;
    regValue &= ~SCG_SPLLCSR_SPLLEN_MASK;
    if (enable == true)
    {
        regValue |= SCG_SPLLCSR_SPLLEN(1U);
    }
    else
    {
        regValue |= SCG_SPLLCSR_SPLLEN(0U);
    }
    SCG->SPLLCSR = regValue;
}

static inline bool SCG_GetEnableSPLL(void)
{
    uint32_t regValue = SCG->SPLLCSR;
    regValue = (regValue & SCG_SPLLCSR_SPLLEN_MASK) >> SCG_SPLLCSR_SPLLEN_SHIFT;

    return (regValue == 0U) ? false : true;
}

static inline bool SCG_GetHsrunSelectSPLL(void)
{
    uint32_t regValue = SCG->HCCR;
    regValue = (regValue & SCG_HCCR_SCS_MASK) >> SCG_HCCR_SCS_SHIFT;

    return (regValue == FEATURE_SCG_SPLL_VALUE) ? true : false;
}

#endif

static inline void SCG_SetEnableFIRC(bool enable)
{
    uint32_t regValue = SCG->FIRCCSR;
    regValue &= ~SCG_FIRCCSR_FIRCEN_MASK;
    if (enable == true)
    {
        regValue |= SCG_FIRCCSR_FIRCEN(1U);
    }
    else
    {
        regValue |= SCG_FIRCCSR_FIRCEN(0U);
    }
    SCG->FIRCCSR = regValue;
}

static inline bool SCG_GetEnableFIRC(void)
{
    uint32_t regValue = SCG->FIRCCSR;
    regValue = (regValue & SCG_FIRCCSR_FIRCEN_MASK) >> SCG_FIRCCSR_FIRCEN_SHIFT;

    return (regValue == 0U) ? false : true;
}

static inline void SCG_SetEnableSOSC(bool enable)
{
    uint32_t regValue = SCG->SOSCCSR;
    regValue &= ~SCG_SOSCCSR_SOSCEN_MASK;
    if (enable == true)
    {
        regValue |= SCG_SOSCCSR_SOSCEN(1U);
    }
    else
    {
        regValue |= SCG_SOSCCSR_SOSCEN(0U);
    }
    SCG->SOSCCSR = regValue;
}

static inline bool SCG_GetEnableSOSC(void)
{
    uint32_t regValue = SCG->SOSCCSR;
    regValue = (regValue & SCG_SOSCCSR_SOSCEN_MASK) >> SCG_SOSCCSR_SOSCEN_SHIFT;

    return (regValue == 0U) ? false : true;
}


#if defined(__cplusplus)
}
#endif 


#endif 

