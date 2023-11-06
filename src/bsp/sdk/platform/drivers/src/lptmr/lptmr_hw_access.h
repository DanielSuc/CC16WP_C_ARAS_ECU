
#ifndef LPTMR_HW_ACCESS_H
#define LPTMR_HW_ACCESS_H


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "device_registers.h"
#include "lptmr_driver.h"



#if defined(__cplusplus)
extern "C" {
#endif

void LPTMR_Init(LPTMR_Type* const base);

static inline bool LPTMR_GetDmaRequest(const LPTMR_Type* const base)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->CSR;

    tmp = (tmp & LPTMR_CSR_TDRE_MASK) >> LPTMR_CSR_TDRE_SHIFT;

    return ((tmp == 1u) ? true : false);
}

static inline void LPTMR_SetDmaRequest(LPTMR_Type* const base,
                                       bool enable)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->CSR;
    tmp &= ~(LPTMR_CSR_TDRE_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= LPTMR_CSR_TDRE(enable ? (uint32_t)1u : (uint32_t)0u);
    base->CSR = tmp;
}

static inline bool LPTMR_GetCompareFlag(const LPTMR_Type* const base)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base -> CSR;
    tmp = (tmp & LPTMR_CSR_TCF_MASK) >> LPTMR_CSR_TCF_SHIFT;

    return ((tmp == 1u) ? true : false);
}

static inline void LPTMR_ClearCompareFlag(LPTMR_Type* const base)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->CSR;
    tmp |= (LPTMR_CSR_TCF_MASK);
    base->CSR = tmp;
#ifdef ERRATA_E9005
    (void)base->CSR;
#endif
}

static inline bool LPTMR_GetInterruptEnable(const LPTMR_Type* const base)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->CSR;
    tmp = (tmp & LPTMR_CSR_TIE_MASK) >> LPTMR_CSR_TIE_SHIFT;

    return ((tmp == 1u) ? true : false);
}

static inline void LPTMR_SetInterrupt(LPTMR_Type* const base,
                                      bool enable)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->CSR;
    tmp &= ~(LPTMR_CSR_TIE_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= LPTMR_CSR_TIE(enable ? (uint32_t)1u : (uint32_t)0u);
    base->CSR = tmp;
}

static inline lptmr_pinselect_t LPTMR_GetPinSelect(const LPTMR_Type* const base)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->CSR;
    tmp = (tmp & LPTMR_CSR_TPS_MASK) >> LPTMR_CSR_TPS_SHIFT;
    return (lptmr_pinselect_t)(tmp);
}

static inline void LPTMR_SetPinSelect(LPTMR_Type* const base,
                                      const lptmr_pinselect_t pinsel)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->CSR;
    tmp &= ~(LPTMR_CSR_TPS_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= LPTMR_CSR_TPS(pinsel);
    base->CSR = tmp;
}

static inline lptmr_pinpolarity_t LPTMR_GetPinPolarity(const LPTMR_Type* const base)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->CSR;
    tmp = (tmp & LPTMR_CSR_TPP_MASK) >> LPTMR_CSR_TPP_SHIFT;

    return (lptmr_pinpolarity_t)((tmp == 0u) ? LPTMR_PINPOLARITY_RISING : LPTMR_PINPOLARITY_FALLING);
}

static inline void LPTMR_SetPinPolarity(LPTMR_Type* const base,
                                        const lptmr_pinpolarity_t pol)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->CSR;
    tmp &= ~(LPTMR_CSR_TPP_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= LPTMR_CSR_TPP(pol);
    base->CSR = tmp;
}

static inline bool LPTMR_GetFreeRunning(const LPTMR_Type* const base)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->CSR;
    tmp = (tmp & LPTMR_CSR_TFC_MASK) >> LPTMR_CSR_TFC_SHIFT;

    return ((tmp == 1u) ? true : false);
}

static inline void LPTMR_SetFreeRunning(LPTMR_Type* const base,
                                        const bool enable)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->CSR;
    tmp &= ~(LPTMR_CSR_TFC_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= LPTMR_CSR_TFC(enable ? (uint32_t)1u : (uint32_t)0u);
    base->CSR = tmp;
}

static inline lptmr_workmode_t LPTMR_GetWorkMode(const LPTMR_Type* const base)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->CSR;
    tmp = (tmp & LPTMR_CSR_TMS_MASK) >> LPTMR_CSR_TMS_SHIFT;

    return (lptmr_workmode_t)((tmp == 0u) ? LPTMR_WORKMODE_TIMER : LPTMR_WORKMODE_PULSECOUNTER);
}

static inline void LPTMR_SetWorkMode(LPTMR_Type* const base,
                                     const lptmr_workmode_t mode)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->CSR;
    tmp &= ~(LPTMR_CSR_TMS_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= LPTMR_CSR_TMS(mode);
    base->CSR = tmp;
}

static inline bool LPTMR_GetEnable(const LPTMR_Type* const base)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->CSR;
    tmp = (tmp & LPTMR_CSR_TEN_MASK) >> LPTMR_CSR_TEN_SHIFT;

    return ((tmp == 1u) ? true : false);
}

static inline void LPTMR_Enable(LPTMR_Type* const base)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->CSR;
    tmp &= ~(LPTMR_CSR_TEN_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= LPTMR_CSR_TEN(1u);
    base->CSR = tmp;
}

static inline void LPTMR_Disable(LPTMR_Type* const base)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->CSR;
    tmp &= ~(LPTMR_CSR_TEN_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= LPTMR_CSR_TEN(0u);
    base->CSR = tmp;
}

static inline lptmr_prescaler_t LPTMR_GetPrescaler(const LPTMR_Type* const base)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->PSR;
    tmp = (tmp & LPTMR_PSR_PRESCALE_MASK) >> LPTMR_PSR_PRESCALE_SHIFT;
    return (lptmr_prescaler_t)(tmp);
}

static inline void LPTMR_SetPrescaler(LPTMR_Type* const base,
                                      const lptmr_prescaler_t presc)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->PSR;
    tmp &= ~(LPTMR_PSR_PRESCALE_MASK);
    tmp |= LPTMR_PSR_PRESCALE(presc);
    base->PSR = tmp;
}

static inline bool LPTMR_GetBypass(const LPTMR_Type* const base)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->PSR;
    tmp = (tmp & LPTMR_PSR_PBYP_MASK) >> LPTMR_PSR_PBYP_SHIFT;

    return ((tmp == 1u) ? true : false);
}

static inline void LPTMR_SetBypass(LPTMR_Type* const base,
                                   const bool enable)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->PSR;
    tmp &= ~(LPTMR_PSR_PBYP_MASK);
    tmp |= LPTMR_PSR_PBYP(enable ? (uint32_t)1u : (uint32_t)0u);
    base->PSR = tmp;
}

static inline lptmr_clocksource_t LPTMR_GetClockSelect(const LPTMR_Type* const base)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->PSR;
    tmp = (tmp & LPTMR_PSR_PCS_MASK) >> LPTMR_PSR_PCS_SHIFT;
    return (lptmr_clocksource_t)(tmp);
}

static inline void LPTMR_SetClockSelect(LPTMR_Type* const base,
                                        const lptmr_clocksource_t clocksel)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->PSR;
    tmp &= ~(LPTMR_PSR_PCS_MASK);
    tmp |= LPTMR_PSR_PCS(clocksel);
    base->PSR = tmp;
}

static inline uint16_t LPTMR_GetCompareValue(const LPTMR_Type* const base)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->CMR;
    tmp = (tmp & LPTMR_CMR_COMPARE_MASK) >> LPTMR_CMR_COMPARE_SHIFT;
    return (uint16_t)(tmp);
}

static inline void LPTMR_SetCompareValue(LPTMR_Type* const base,
                                         const uint16_t compval)
{
    DEV_ASSERT(base != NULL);

    uint32_t tmp = base->CMR;
    tmp &= ~(LPTMR_CMR_COMPARE_MASK);
    tmp |= LPTMR_CMR_COMPARE(compval);
    base->CMR = tmp;
}

static inline uint16_t LPTMR_GetCounterValue(LPTMR_Type* const base)
{
    DEV_ASSERT(base != NULL);

    base->CNR = LPTMR_CNR_COUNTER(0u);
    uint16_t cnr = (uint16_t)base->CNR;
    return cnr;
}

#if defined(__cplusplus)
}
#endif

#endif 

