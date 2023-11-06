
#ifndef RTC_HW_ACCESS_H
#define RTC_HW_ACCESS_H
#include <stdbool.h>
#include "device_registers.h"
#include "status.h"
#include "rtc_driver.h"





#if defined(__cplusplus)
extern "C" {
#endif



status_t RTC_Enable(RTC_Type * const base);

status_t RTC_Disable(RTC_Type * const base);

status_t RTC_ConfigureRegisterLock(RTC_Type * const base, rtc_lock_register_select_t registerToConfig);

bool RTC_IsRegisterLocked(const RTC_Type * const base, rtc_lock_register_select_t reg);


status_t RTC_ConfigureClockOut(RTC_Type * const base, rtc_clk_out_config_t config);


static inline uint32_t RTC_GetTimeSecondsRegister(const RTC_Type * const base)
{
    uint32_t tmp = base->TSR;
    tmp = (tmp & RTC_TSR_TSR_MASK) >> RTC_TSR_TSR_SHIFT;
    return (uint32_t) (tmp);
}

status_t RTC_SetTimeSecondsRegister(RTC_Type * const base, uint32_t seconds);


static inline uint32_t RTC_GetTimeAlarmRegister(const RTC_Type * const base)
{
    uint32_t tmp = base->TAR;
    tmp = (tmp & RTC_TAR_TAR_MASK) >> RTC_TAR_TAR_SHIFT;
    return (uint32_t) (tmp);
}

static inline void RTC_SetTimeAlarmRegister(RTC_Type * const base, uint32_t seconds)
{
    base->TAR = seconds;
}


static inline void RTC_SetTimeCompensation(RTC_Type * const base,
                                               int8_t  compensationValue,
                                               uint8_t compensationInterval)
{
    uint32_t tmp = base->TCR;
    tmp &= ~(RTC_TCR_TCR_MASK | RTC_TCR_CIR_MASK);
    tmp |= RTC_TCR_TCR(compensationValue);
    tmp |= RTC_TCR_CIR(compensationInterval);
    base->TCR = tmp;
}

static inline void RTC_GetCurrentTimeCompensation(const RTC_Type * const base,
                                                      int8_t  * compensationValue,
                                                      uint8_t * compensationInterval)
{
    uint32_t tmp = base->TCR;
    (*compensationValue)    = (int8_t)((tmp & RTC_TCR_TCV_MASK) >> RTC_TCR_TCV_SHIFT);
    (*compensationInterval) = (uint8_t)((tmp & RTC_TCR_CIC_MASK) >> RTC_TCR_CIC_SHIFT);
}


static inline void RTC_SetLPOSelect(RTC_Type * const base, rtc_clk_select_t clk_select)
{
    uint32_t tmp = base->CR;
    tmp &= ~(RTC_CR_LPOS_MASK);
    tmp |= RTC_CR_LPOS(clk_select);
    base->CR = tmp;
}

static inline void RTC_SetUpdateMode(RTC_Type * const base, bool updateEnable)
{
    uint32_t tmp = base->CR;
    tmp &= ~(RTC_CR_UM_MASK);
    tmp |= RTC_CR_UM((updateEnable ? 1UL : 0UL));
    base->CR = tmp;
}

static inline bool RTC_GetUpdateMode(const RTC_Type * const base)
{
    uint32_t tmp = base->CR;
    tmp = (tmp & RTC_CR_UM_MASK) >> RTC_CR_UM_SHIFT;
    return ((tmp == 1U) ? true : false);
}

static inline void RTC_SetNonSupervisorAccess(RTC_Type * const base, bool enable)
{
    uint32_t tmp = base->CR;
    tmp &= ~(RTC_CR_SUP_MASK);
    tmp |= RTC_CR_SUP(enable ? 1UL : 0UL);
    base->CR = tmp;
}

static inline void RTC_SoftwareReset(RTC_Type * const base)
{
	base->CR |= RTC_CR_SWR(1);
	base->CR &= ~RTC_CR_SWR(1);
}


static inline void RTC_SetTimeCounterEnable(RTC_Type * const base, bool enable)
{
    uint32_t tmp = base->SR;
    tmp &= ~(RTC_SR_TCE_MASK);
    tmp |= RTC_SR_TCE(enable ? 1UL : 0UL);
    base->SR = tmp;
}

static inline bool RTC_GetTimeCounterEnable(const RTC_Type * const base)
{
    uint32_t tmp = base->SR;
    tmp = (tmp & RTC_SR_TCE_MASK) >> RTC_SR_TCE_SHIFT;
    return ((tmp == 1U) ? true : false);
}

static inline bool RTC_GetTimeAlarmFlag(const RTC_Type * const base)
{
    uint32_t tmp = base->SR;
    tmp = (tmp & RTC_SR_TAF_MASK) >> RTC_SR_TAF_SHIFT;
    return ((tmp == 1U) ? true : false);
}

static inline bool RTC_GetTimeOverflowFlag(const RTC_Type * const base)
{
    uint32_t tmp = base->SR;
    tmp = (tmp & RTC_SR_TOF_MASK) >> RTC_SR_TOF_SHIFT;
    return ((tmp == 1U) ? true : false);
}

static inline bool RTC_GetTimeInvalidFlag(const RTC_Type * const base)
{
    uint32_t tmp = base->SR;
    tmp = (tmp & RTC_SR_TIF_MASK) >> RTC_SR_TIF_SHIFT;
    return ((tmp == 1U) ? true : false);
}


static inline void RTC_LockRegisterLock(RTC_Type * const base)
{
    uint32_t tmp = base->LR;
    tmp &= ~(RTC_LR_LRL_MASK);
    base->LR = tmp;
}

static inline bool RTC_GetLockRegisterLock(const RTC_Type * const base)
{
    uint32_t tmp = base->LR;
    tmp = (tmp & RTC_LR_LRL_MASK) >> RTC_LR_LRL_SHIFT;
    return ((tmp == 1U) ? false : true);
}

static inline void RTC_StatusRegisterLock(RTC_Type * const base)
{
    uint32_t tmp = base->LR;
    tmp &= ~(RTC_LR_SRL_MASK);
    base->LR = tmp;
}

static inline bool RTC_GetStatusRegisterLock(const RTC_Type * const base)
{
    uint32_t tmp = base->LR;
    tmp = (tmp & RTC_LR_SRL_MASK) >> RTC_LR_SRL_SHIFT;
    return ((tmp == 1U) ? false : true);
}

static inline bool RTC_GetControlRegisterLock(const RTC_Type * const base)
{
    uint32_t tmp = base->LR;
    tmp = (tmp & RTC_LR_CRL_MASK) >> RTC_LR_CRL_SHIFT;
    return ((tmp == 1U) ? false : true);
}

static inline void RTC_ControlRegisterLock(RTC_Type * const base)
{
    uint32_t tmp = base->LR;
    tmp &= ~(RTC_LR_CRL_MASK);
    base->LR = tmp;
}

static inline bool RTC_GetTimeCompensationLock(const RTC_Type * const base)
{
    uint32_t tmp = base->LR;
    tmp = (tmp & RTC_LR_TCL_MASK) >> RTC_LR_TCL_SHIFT;
    return ((tmp == 1U) ? false : true);
}

static inline void RTC_TimeCompensationLock(RTC_Type * const base)
{
    uint32_t tmp = base->LR;
    tmp &= ~(RTC_LR_TCL_MASK);
    base->LR = tmp;
}


static inline void RTC_SetTimeSecondsIntConf(RTC_Type * const base, rtc_second_int_cfg_t intCfg)
{
    uint32_t tmp = base->IER;
    tmp &= ~(RTC_IER_TSIC_MASK);
    tmp |= RTC_IER_TSIC((uint8_t)intCfg);
    base->IER = tmp;
}

static inline void RTC_SetTimeSecondsIntEnable(RTC_Type * const base, bool enable)
{
    uint32_t tmp = base->IER;
    tmp &= ~(RTC_IER_TSIE_MASK);
    tmp |= RTC_IER_TSIE(enable ? 1UL : 0UL);
    base->IER = tmp;
}

static inline void RTC_SetTimeAlarmIntEnable(RTC_Type * const base, bool enable)
{
    uint32_t tmp = base->IER;
    tmp &= ~(RTC_IER_TAIE_MASK);
    tmp |= RTC_IER_TAIE(enable ? 1UL : 0UL);
    base->IER = tmp;
}

static inline void RTC_SetTimeOverflowIntEnable(RTC_Type * const base, bool enable)
{
    uint32_t tmp = base->IER;
    tmp &= ~(RTC_IER_TOIE_MASK);
    tmp |= RTC_IER_TOIE(enable ? 1UL : 0UL);
    base->IER = tmp;
}

static inline void RTC_SetTimeInvalidIntEnable(RTC_Type * const base, bool enable)
{
    uint32_t tmp = base->IER;
    tmp &= ~(RTC_IER_TIIE_MASK);
    tmp |= RTC_IER_TIIE(enable ? 1UL : 0UL);
    base->IER = tmp;
}


#if defined(__cplusplus)
}
#endif


#endif 

