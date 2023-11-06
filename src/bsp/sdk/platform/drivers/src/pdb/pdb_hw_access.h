
#ifndef PDB_HW_ACCESS_H
#define PDB_HW_ACCESS_H

#include <stddef.h>
#include "pdb_driver.h"





#if defined(__cplusplus)
extern "C" {
#endif


void PDB_Init(PDB_Type * const base);

void PDB_ConfigTimer(PDB_Type * const base,
                     const pdb_timer_config_t * const configPtr);

static inline void PDB_SetSoftTriggerCmd(PDB_Type * const base)
{
    DEV_ASSERT(base != NULL);
    REG_BIT_SET32(&(base->SC), PDB_SC_SWTRIG_MASK);
}

static inline void PDB_Enable(PDB_Type * const base)
{
    DEV_ASSERT(base != NULL);
    REG_BIT_SET32(&(base->SC), PDB_SC_PDBEN_MASK);
}

static inline void PDB_Disable(PDB_Type * const base)
{
    DEV_ASSERT(base != NULL);
    REG_BIT_CLEAR32(&(base->SC), PDB_SC_PDBEN_MASK);
}

static inline bool PDB_GetTimerIntFlag(PDB_Type const * const base)
{
    DEV_ASSERT(base != NULL);

    return 1U == ((base->SC & PDB_SC_PDBIF_MASK) >> PDB_SC_PDBIF_SHIFT);
}

static inline void PDB_ClearTimerIntFlag(PDB_Type * const base)
{
    DEV_ASSERT(base != NULL);
    volatile uint32_t dummy_read;
    REG_BIT_CLEAR32(&(base->SC), PDB_SC_PDBIF_MASK);

    dummy_read = REG_READ32(&(base->SC));
    (void)dummy_read;
}

static inline void PDB_SetLoadValuesCmd(PDB_Type * const base)
{
    DEV_ASSERT(base != NULL);
    REG_BIT_SET32(&(base->SC), PDB_SC_LDOK_MASK);
}

static inline void PDB_SetTimerModulusValue(PDB_Type * const base,
                                            uint16_t value)
{
    DEV_ASSERT(base != NULL);
    REG_RMW32(&(base->MOD), PDB_MOD_MOD_MASK, PDB_MOD_MOD(value));
}

static inline uint32_t PDB_GetTimerValue(PDB_Type const * const base)
{
    DEV_ASSERT(base != NULL);

    return ((base->CNT & PDB_CNT_CNT_MASK) >> PDB_CNT_CNT_SHIFT);
}

static inline void PDB_SetValueForTimerInterrupt(PDB_Type * const base,
                                                 uint16_t value)
{
    DEV_ASSERT(base != NULL);
    REG_RMW32(&(base->IDLY), PDB_IDLY_IDLY_MASK, PDB_IDLY_IDLY(value));
}

void PDB_SetAdcPreTriggerBackToBackEnable(PDB_Type * const base,
                                          uint32_t chn,
                                          uint32_t preChnMask,
                                          bool enable);

void PDB_SetAdcPreTriggerOutputEnable(PDB_Type * const base,
                                      uint32_t chn,
                                      uint32_t preChnMask,
                                      bool enable);

void PDB_SetAdcPreTriggerEnable(PDB_Type * const base,
                                uint32_t chn,
                                uint32_t preChnMask,
                                bool enable);

static inline uint32_t PDB_GetAdcPreTriggerFlags(PDB_Type const * const base,
                                                 uint32_t chn,
                                                 uint32_t preChnMask)
{
    DEV_ASSERT(base != NULL);
    DEV_ASSERT(chn < PDB_CH_COUNT);

    return preChnMask & ((base->CH[chn].S & PDB_S_CF_MASK) >> PDB_S_CF_SHIFT);
}

void PDB_ClearAdcPreTriggerFlags(PDB_Type * const base,
                                 uint32_t chn,
                                 uint32_t preChnMask);

static inline uint32_t PDB_GetAdcPreTriggerSeqErrFlags(PDB_Type const * const base,
                                                       uint32_t chn,
                                                       uint32_t preChnMask)
{
    DEV_ASSERT(base != NULL);
    DEV_ASSERT(chn < PDB_CH_COUNT);

    return (preChnMask & ((base->CH[chn].S & PDB_S_ERR_MASK) >> PDB_S_ERR_SHIFT));
}

void PDB_ClearAdcPreTriggerSeqErrFlags(PDB_Type * const base,
                                       uint32_t chn,
                                       uint32_t preChnMask);

static inline void PDB_SetAdcPreTriggerDelayValue(PDB_Type * const base,
                                    uint32_t chn,
                                    uint32_t preChn,
                                    uint32_t value)
{
    DEV_ASSERT(base != NULL);
    DEV_ASSERT(chn < PDB_CH_COUNT);
    DEV_ASSERT(preChn < PDB_DLY_COUNT);

    base->CH[chn].DLY[preChn] = PDB_DLY_DLY(value);
}

void PDB_SetCmpPulseOutEnable(PDB_Type * const base,
                              uint32_t pulseChnMask,
                              bool enable);

static inline void PDB_SetCmpPulseOutDelayForHigh(PDB_Type * const base,
                                                  uint32_t pulseChn,
                                                  uint32_t value)
{
    DEV_ASSERT(base != NULL);
    DEV_ASSERT(pulseChn < PDB_POnDLY_COUNT);
    base->POnDLY[pulseChn].ACCESS16BIT.DLY1 = (uint16_t)PDB_POnDLY_ACCESS16BIT_DLY1_DLY1(value);
}

static inline void PDB_SetCmpPulseOutDelayForLow(PDB_Type * const base,
                                                 uint32_t pulseChn,
                                                 uint32_t value)
{
    DEV_ASSERT(base != NULL);
    DEV_ASSERT(pulseChn < PDB_POnDLY_COUNT);
    base->POnDLY[pulseChn].ACCESS16BIT.DLY2 = (uint16_t)PDB_POnDLY_ACCESS16BIT_DLY2_DLY2(value);
}

#if FEATURE_PDB_HAS_INSTANCE_BACKTOBACK
static inline void PDB_SIM_EnableBackToBack(void)
{
    SIM->CHIPCTL |= SIM_CHIPCTL_PDB_BB_SEL(1u);
}

static inline void PDB_SIM_DisableBackToBack(void)
{
    SIM->CHIPCTL &= ~SIM_CHIPCTL_PDB_BB_SEL(1u);
}
#endif 

#if defined(__cplusplus)
}
#endif


#endif 


