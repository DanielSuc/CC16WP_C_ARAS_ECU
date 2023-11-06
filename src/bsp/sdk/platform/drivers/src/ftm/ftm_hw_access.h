
#ifndef FTM_HW_ACCESS_H
#define FTM_HW_ACCESS_H

#include <stdbool.h>
#include <stddef.h>
#include "status.h"
#include "device_registers.h"
#include "interrupt_manager.h"
#include "clock_manager.h"
#include "ftm_common.h"





#if defined(__cplusplus)
extern "C" {
#endif

static inline void FTM_DRV_SetHalfCycleValue(FTM_Type * const ftmBase,
                                             uint16_t value)
{
    ((ftmBase)->HCR) = value;
}

static inline void FTM_DRV_SetClockSource(FTM_Type * const ftmBase,
                                          ftm_clock_source_t clock)
{
    FTM_RMW_SC(ftmBase, FTM_SC_CLKS_MASK, FTM_SC_CLKS(clock));
}

static inline void FTM_DRV_SetClockPs(FTM_Type * const ftmBase,
                                      ftm_clock_ps_t ps)
{
    FTM_RMW_SC(ftmBase, FTM_SC_PS_MASK, FTM_SC_PS(ps));
}

static inline uint8_t FTM_DRV_GetClockPs(const FTM_Type * ftmBase)
{
    return (uint8_t)((((ftmBase)->SC) & FTM_SC_PS_MASK) >> FTM_SC_PS_SHIFT);
}

static inline void FTM_DRV_SetTimerOverflowInt(FTM_Type * const ftmBase,
                                               bool state)
{
    FTM_RMW_SC(ftmBase, FTM_SC_TOIE_MASK, FTM_SC_TOIE(state));
}

static inline void FTM_DRV_EnablePwmChannelOutputs(FTM_Type * const ftmBase,
                                                   uint8_t channel)
{
    FTM_RMW_SC(ftmBase, (1UL << (channel + FTM_FEATURE_OUTPUT_CHANNEL_OFFSET)), (1UL << (channel + FTM_FEATURE_OUTPUT_CHANNEL_OFFSET)));
}

static inline void FTM_DRV_DisablePwmChannelOutputs(FTM_Type * const ftmBase,
                                                    uint8_t channel)
{
    uint32_t regValue = ((ftmBase)->SC);
    regValue = regValue & (~(1UL << (channel + FTM_FEATURE_OUTPUT_CHANNEL_OFFSET)));
    ((ftmBase)->SC) = (regValue);
}

static inline void FTM_DRV_ClearTimerOverflow(FTM_Type * const ftmBase)
{
    FTM_RMW_SC(ftmBase, FTM_SC_TOF_MASK, FTM_SC_TOF(0U));
#ifdef ERRATA_E9005
    ftmBase->SC;
#endif
}

static inline bool FTM_DRV_IsOverflowIntEnabled(const FTM_Type * ftmBase)
{
    return ((ftmBase->SC & FTM_SC_TOIE_MASK) >> FTM_SC_TOIE_SHIFT) != 0U;
}

static inline bool FTM_DRV_HasTimerOverflowed(const FTM_Type * ftmBase)
{
    return ((ftmBase->SC & FTM_SC_TOF_MASK) >> FTM_SC_TOF_SHIFT) != 0U;
}

static inline void FTM_DRV_SetCpwms(FTM_Type * const ftmBase,
                                    bool mode)
{
    FTM_RMW_SC(ftmBase, FTM_SC_CPWMS_MASK, FTM_SC_CPWMS(mode));
}

static inline bool FTM_DRV_GetCpwms(const FTM_Type * ftmBase)
{
    return ((ftmBase->SC & FTM_SC_CPWMS_MASK) >> FTM_SC_CPWMS_SHIFT) != 0U;
}

static inline void FTM_DRV_SetReIntEnabledCmd(FTM_Type * const ftmBase,
                                              bool enable)
{
    FTM_RMW_SC(ftmBase, FTM_SC_RIE_MASK, FTM_SC_RIE(enable));
}

static inline bool FTM_DRV_GetReloadFlag(const FTM_Type * ftmBase)
{
    return ((ftmBase->SC & FTM_SC_RF_MASK) >> FTM_SC_RF_SHIFT) != 0U;
}

static inline void FTM_DRV_ClearReloadFlag(FTM_Type * const ftmBase)
{
    FTM_RMW_SC(ftmBase, FTM_SC_RF_MASK, FTM_SC_RF(0U));
#ifdef ERRATA_E9005
    ftmBase->SC;
#endif
}

static inline bool FTM_DRV_IsReloadIntEnabled(const FTM_Type * ftmBase)
{
    return ((ftmBase->SC & FTM_SC_RIE_MASK) >> FTM_SC_RIE_SHIFT) != 0U;
}

static inline uint8_t FTM_DRV_GetClockSource(const FTM_Type * ftmBase)
{
    return (uint8_t)((((ftmBase)->SC) & FTM_SC_CLKS_MASK) >> FTM_SC_CLKS_SHIFT);
}

static inline void FTM_DRV_SetCounter(FTM_Type * const ftmBase,
                                      uint16_t value)
{
    FTM_RMW_CNT(ftmBase, FTM_CNT_COUNT_MASK, FTM_CNT_COUNT(value));
}

static inline void FTM_DRV_SetMod(FTM_Type * const ftmBase,
                                  uint16_t value)
{
    FTM_RMW_MOD(ftmBase, FTM_MOD_MOD_MASK, FTM_MOD_MOD(value));
}

static inline void FTM_DRV_SetCounterInitVal(FTM_Type * const ftmBase,
                                             uint16_t value)
{
    FTM_RMW_CNTIN(ftmBase, FTM_CNTIN_INIT_MASK, FTM_CNTIN_INIT(value));
}

static inline void FTM_DRV_SetChnMSnBAMode(FTM_Type * const ftmBase,
                                           uint8_t channel,
                                           uint8_t selection)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    FTM_RMW_CnSCV_REG(ftmBase, channel, FTM_CnSC_MSA_MASK, FTM_CnSC_MSA((uint32_t)selection & 0x01U));

    FTM_RMW_CnSCV_REG(ftmBase, channel, FTM_CnSC_MSB_MASK, FTM_CnSC_MSB(((uint32_t)selection & 0x02U) >> 1U));
}

static inline void FTM_DRV_SetChnEdgeLevel(FTM_Type * const ftmBase,
                                           uint8_t channel,
                                           uint8_t level)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    FTM_RMW_CnSCV_REG(ftmBase, channel, FTM_CnSC_ELSA_MASK, FTM_CnSC_ELSA((uint32_t)level & 0x01U));

    FTM_RMW_CnSCV_REG(ftmBase, channel, FTM_CnSC_ELSB_MASK, FTM_CnSC_ELSB(((uint32_t)level & 0x02U) >> 1U));
}

static inline void FTM_DRV_EnableChnInt(FTM_Type * const ftmBase,
                                        uint8_t channel)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    FTM_RMW_CnSCV_REG(ftmBase, channel, FTM_CnSC_CHIE_MASK, FTM_CnSC_CHIE(1U));
}

static inline void FTM_DRV_DisableChnInt(FTM_Type * const ftmBase,
                                         uint8_t channel)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    FTM_RMW_CnSCV_REG(ftmBase, channel, FTM_CnSC_CHIE_MASK, FTM_CnSC_CHIE(0U));
}

static inline void FTM_DRV_ClearChnEventFlag(FTM_Type * const ftmBase,
                                             uint8_t channel)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    FTM_RMW_CnSCV_REG(ftmBase, channel, FTM_CnSC_CHF_MASK, FTM_CnSC_CHF(0U));
#ifdef ERRATA_E9005
    ftmBase->CONTROLS[channel].CnSC;
#endif
}

static inline void FTM_DRV_SetChnCountVal(FTM_Type * const ftmBase,
                                          uint8_t channel,
                                          uint16_t value)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    ((ftmBase)->CONTROLS[channel].CnV) = value;
}

static inline bool FTM_DRV_IsChnIntEnabled(const FTM_Type * ftmBase,
                                           uint8_t channel)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    return (((ftmBase)->CONTROLS[channel].CnSC) & FTM_CnSC_CHIE_MASK) != 0U;
}

static inline bool FTM_DRV_HasChnEventOccurred(const FTM_Type * ftmBase,
                                               uint8_t channel)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    return (((ftmBase)->CONTROLS[channel].CnSC) & FTM_CnSC_CHF_MASK) != 0U;
}

static inline uint8_t FTM_DRV_GetChnMode(const FTM_Type * ftmBase,
                                         uint8_t channel)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);
    uint8_t retValue;

    retValue = (uint8_t)((((ftmBase)->CONTROLS[channel].CnSC) & FTM_CnSC_MSA_MASK) >> FTM_CnSC_MSA_SHIFT);

    retValue |= (uint8_t)(((((ftmBase)->CONTROLS[channel].CnSC) & FTM_CnSC_MSB_MASK) >> FTM_CnSC_MSB_SHIFT) << 1U);

    return retValue;
}

static inline void FTM_DRV_SetOutmaskReg(FTM_Type * const ftmBase,
                                         uint32_t regVal)
{
    ((ftmBase)->OUTMASK) = regVal;
}

static inline void FTM_DRV_SetChnOutputPolarityCmd(FTM_Type * const ftmBase,
                                                   uint8_t channel,
                                                   bool polarity)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    if (true != polarity)
    {
        ((ftmBase)->POL) &= ~(1UL << channel);
    }
    else
    {
        ((ftmBase)->POL) |= (1UL << channel);
    }
}

static inline void FTM_DRV_SetChnFaultInputPolarityCmd(FTM_Type * const ftmBase,
                                                       uint8_t fltChannel,
                                                       bool polarity)
{
    DEV_ASSERT(fltChannel < FTM_FEATURE_FAULT_CHANNELS);

    if (true == polarity)
    {
        ((ftmBase)->FLTPOL) &= ~(1UL << fltChannel);
    }
    else
    {
        ((ftmBase)->FLTPOL) |= (1UL << fltChannel);
    }
}

static inline void FTM_DRV_SetFaultInt(FTM_Type * const ftmBase,
                                       bool state)
{
    FTM_RMW_MODE(ftmBase, FTM_MODE_FAULTIE_MASK, FTM_MODE_FAULTIE(state));
}

static inline bool FTM_DRV_IsFaultIntEnabled(const FTM_Type * ftmBase)
{
    return ((ftmBase->MODE & FTM_MODE_FAULTIE_MASK) >> FTM_MODE_FAULTIE_SHIFT) != 0U;
}

static inline void FTM_DRV_ClearFaultsIsr(FTM_Type * const ftmBase)
{
    FTM_RMW_FMS(ftmBase, FTM_FMS_FAULTF0_MASK | FTM_FMS_FAULTF_MASK, FTM_FMS_FAULTF0(0U) | FTM_FMS_FAULTF(0U));
    FTM_RMW_FMS(ftmBase, FTM_FMS_FAULTF1_MASK | FTM_FMS_FAULTF_MASK, FTM_FMS_FAULTF1(0U) | FTM_FMS_FAULTF(0U));
    FTM_RMW_FMS(ftmBase, FTM_FMS_FAULTF2_MASK | FTM_FMS_FAULTF_MASK, FTM_FMS_FAULTF2(0U) | FTM_FMS_FAULTF(0U));
    FTM_RMW_FMS(ftmBase, FTM_FMS_FAULTF3_MASK | FTM_FMS_FAULTF_MASK, FTM_FMS_FAULTF3(0U) | FTM_FMS_FAULTF(0U));
#ifdef ERRATA_E9005
    ftmBase->FMS;
#endif
}

static inline void FTM_DRV_SetFaultControlMode(FTM_Type * const ftmBase,
                                               uint32_t mode)
{
    FTM_RMW_MODE(ftmBase, FTM_MODE_FAULTM_MASK, FTM_MODE_FAULTM(mode));
}

static inline void FTM_DRV_SetInitChnOutputCmd(FTM_Type * const ftmBase,
                                               bool enable)
{
    FTM_RMW_MODE(ftmBase, FTM_MODE_INIT_MASK, FTM_MODE_INIT(enable));
}

static inline bool FTM_DRV_GetDetectedFaultInput(const FTM_Type * ftmBase)
{
    return (ftmBase->FMS & FTM_FMS_FAULTF_MASK) != 0U;
}

static inline void FTM_DRV_SetWriteProtectionCmd(FTM_Type * const ftmBase,
                                                 bool enable)
{
    if (enable)
    {
        ftmBase->FMS = (ftmBase->FMS & ~FTM_FMS_WPEN_MASK) | FTM_FMS_WPEN(1U);
    }
    else
    {
        ftmBase->MODE = (ftmBase->MODE & ~FTM_MODE_WPDIS_MASK) | FTM_MODE_WPDIS(1U);
    }
}

static inline void FTM_DRV_Enable(FTM_Type * const ftmBase,
                                  bool enable)
{
    FTM_RMW_MODE(ftmBase, FTM_MODE_FTMEN_MASK, FTM_MODE_FTMEN(enable));
}

static inline void FTM_DRV_SetPwmSyncMode(FTM_Type * const ftmBase,
                                          bool enable)
{
    FTM_RMW_MODE(ftmBase, FTM_MODE_PWMSYNC_MASK, FTM_MODE_PWMSYNC(enable));
}

static inline void FTM_DRV_SetSoftwareTriggerCmd(FTM_Type * const ftmBase,
                                                 bool enable)
{
    FTM_RMW_SYNC(ftmBase, FTM_SYNC_SWSYNC_MASK, FTM_SYNC_SWSYNC(enable));
}

static inline void FTM_DRV_SetHardwareSyncTriggerSrc(FTM_Type * const ftmBase,
                                                     uint8_t trigger_num,
                                                     bool enable)
{
    DEV_ASSERT(trigger_num < 3U);

    if (enable)
    {
        ((ftmBase)->SYNC) |= ((uint32_t)(FTM_SYNC_TRIG0_MASK) << trigger_num);
    }
    else
    {
        ((ftmBase)->SYNC) &= ~((uint32_t)(FTM_SYNC_TRIG0_MASK) << trigger_num);
    }
}

static inline void FTM_DRV_SetOutmaskPwmSyncModeCmd(FTM_Type * const ftmBase,
                                                    bool enable)
{
    FTM_RMW_SYNC(ftmBase, FTM_SYNC_SYNCHOM_MASK, FTM_SYNC_SYNCHOM(enable));
}

static inline void FTM_DRV_SetMaxLoadingCmd(FTM_Type * const ftmBase,
                                            bool enable)
{
    FTM_RMW_SYNC(ftmBase, FTM_SYNC_CNTMAX_MASK, FTM_SYNC_CNTMAX(enable));
}

static inline void FTM_DRV_SetMinLoadingCmd(FTM_Type * const ftmBase,
                                            bool enable)
{
    FTM_RMW_SYNC(ftmBase, FTM_SYNC_CNTMIN_MASK, FTM_SYNC_CNTMIN(enable));
}

static inline void FTM_DRV_SetDualChnMofCombineCmd(FTM_Type * const ftmBase,
                                                   uint8_t chnlPairNum,
                                                   bool enable)
{
    DEV_ASSERT(chnlPairNum < (FEATURE_FTM_CHANNEL_COUNT >> 1U));

    if (enable)
    {
        ((ftmBase)->COMBINE) |= ((uint32_t)FTM_COMBINE_MCOMBINE0_MASK << (chnlPairNum * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH));
    }
    else
    {
        ((ftmBase)->COMBINE) &= ~((uint32_t)FTM_COMBINE_MCOMBINE0_MASK << (chnlPairNum * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH));
    }
}

static inline void FTM_DRV_SetDualChnFaultCmd(FTM_Type * const ftmBase,
                                              uint8_t chnlPairNum,
                                              bool enable)
{
    DEV_ASSERT(chnlPairNum < (FEATURE_FTM_CHANNEL_COUNT >> 1U));

    if (enable)
    {
        ((ftmBase)->COMBINE) |= ((uint32_t)FTM_COMBINE_FAULTEN0_MASK << (chnlPairNum * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH));
    }
    else
    {
        ((ftmBase)->COMBINE) &= ~((uint32_t)FTM_COMBINE_FAULTEN0_MASK << (chnlPairNum * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH));
    }
}

static inline void FTM_DRV_SetDualChnPwmSyncCmd(FTM_Type * const ftmBase,
                                                uint8_t chnlPairNum,
                                                bool enable)
{
    DEV_ASSERT(chnlPairNum < (FEATURE_FTM_CHANNEL_COUNT >> 1U));

    if (enable)
    {
        ((ftmBase)->COMBINE) |= ((uint32_t)FTM_COMBINE_SYNCEN0_MASK << (chnlPairNum * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH));
    }
    else
    {
        ((ftmBase)->COMBINE) &= ~((uint32_t)FTM_COMBINE_SYNCEN0_MASK << (chnlPairNum * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH));
    }
}

static inline void FTM_DRV_SetDualChnDeadtimeCmd(FTM_Type * const ftmBase,
                                                 uint8_t chnlPairNum,
                                                 bool enable)
{
    DEV_ASSERT(chnlPairNum < FEATURE_FTM_CHANNEL_COUNT);

    if (enable)
    {
        ((ftmBase)->COMBINE) |= ((uint32_t)FTM_COMBINE_DTEN0_MASK << (chnlPairNum * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH));
    }
    else
    {
        ((ftmBase)->COMBINE) &= ~((uint32_t)FTM_COMBINE_DTEN0_MASK << (chnlPairNum * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH));
    }
}

static inline void FTM_DRV_SetDualChnDecapCmd(FTM_Type * const ftmBase,
                                              uint8_t chnlPairNum,
                                              bool enable)
{
    DEV_ASSERT(chnlPairNum < (FEATURE_FTM_CHANNEL_COUNT >> 1U));

    if (enable)
    {
        ((ftmBase)->COMBINE) |= ((uint32_t)FTM_COMBINE_DECAP0_MASK << (chnlPairNum * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH));
    }
    else
    {
        ((ftmBase)->COMBINE) &= ~((uint32_t)FTM_COMBINE_DECAP0_MASK << (chnlPairNum * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH));
    }
}

static inline void FTM_DRV_SetDualEdgeCaptureCmd(FTM_Type * const ftmBase,
                                                 uint8_t chnlPairNum,
                                                 bool enable)
{
    DEV_ASSERT(chnlPairNum < (FEATURE_FTM_CHANNEL_COUNT >> 1U));

    if (enable)
    {
        ((ftmBase)->COMBINE) |= ((uint32_t)FTM_COMBINE_DECAPEN0_MASK << (chnlPairNum * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH));
    }
    else
    {
        ((ftmBase)->COMBINE) &= ~((uint32_t)FTM_COMBINE_DECAPEN0_MASK << (chnlPairNum * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH));
    }
}

static inline bool FTM_DRV_GetDualEdgeCaptureBit(const FTM_Type * ftmBase,
                                                 uint8_t chnlPairNum)
{
    DEV_ASSERT(chnlPairNum < (FEATURE_FTM_CHANNEL_COUNT >> 1U));

    return (((ftmBase)->COMBINE) & ((uint32_t)FTM_COMBINE_DECAPEN0_MASK << (chnlPairNum * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH))) != 0U;
}

static inline void FTM_DRV_SetDualChnCompCmd(FTM_Type * const ftmBase,
                                             uint8_t chnlPairNum,
                                             bool polarity)
{
    DEV_ASSERT(chnlPairNum < (FEATURE_FTM_CHANNEL_COUNT >> 1U));

    if (polarity == true)
    {
        ((ftmBase)->COMBINE) |= (FTM_COMBINE_COMP0_MASK << ((uint32_t)(chnlPairNum) * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH));
    }
    else
    {
        ((ftmBase)->COMBINE) &= ~(FTM_COMBINE_COMP0_MASK << ((uint32_t)(chnlPairNum) * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH));
    }
}

static inline void FTM_DRV_SetDualChnCombineCmd(FTM_Type * const ftmBase,
                                                uint8_t chnlPairNum,
                                                bool enable)
{
    DEV_ASSERT(chnlPairNum < (FEATURE_FTM_CHANNEL_COUNT >> 1U));

    if (enable)
    {
        ((ftmBase)->COMBINE) |= (FTM_COMBINE_COMBINE0_MASK << ((uint32_t)(chnlPairNum) * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH));
    }
    else
    {
        ((ftmBase)->COMBINE) &= ~(FTM_COMBINE_COMBINE0_MASK << ((uint32_t)(chnlPairNum) * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH));
    }
}

static inline bool FTM_DRV_GetDualChnCombineCmd(const FTM_Type * ftmBase,
                                                uint8_t chnlPairNum)
{
    DEV_ASSERT(chnlPairNum < (FEATURE_FTM_CHANNEL_COUNT >> 1U));

    return (((ftmBase)->COMBINE) & (FTM_COMBINE_COMBINE0_MASK << ((uint32_t)(chnlPairNum) * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH))) != 0U;
}

static inline bool FTM_DRV_GetDualChnMofCombineCmd(const FTM_Type * ftmBase,
                                                   uint8_t chnlPairNum)
{
    DEV_ASSERT(chnlPairNum < (FEATURE_FTM_CHANNEL_COUNT >> 1U));

    return (((ftmBase)->COMBINE) & (FTM_COMBINE_MCOMBINE0_MASK << ((uint32_t)(chnlPairNum) * FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH))) != 0U;
}

static inline void FTM_DRV_SetExtDeadtimeValue(FTM_Type * const ftmBase,
                                               uint8_t value)
{
    DEV_ASSERT(value < 16U);

    FTM_RMW_DEADTIME(ftmBase, FTM_DEADTIME_DTVALEX_MASK, FTM_DEADTIME_DTVALEX(value));
}

static inline void FTM_DRV_SetDeadtimePrescale(FTM_Type * const ftmBase,
                                               ftm_deadtime_ps_t divider)
{
    FTM_RMW_DEADTIME(ftmBase, FTM_DEADTIME_DTPS_MASK, FTM_DEADTIME_DTPS((uint8_t)divider));
}

static inline void FTM_DRV_SetDeadtimeCount(FTM_Type * const ftmBase,
                                            uint8_t count)
{
    DEV_ASSERT(count < 64U);

    FTM_RMW_DEADTIME(ftmBase, FTM_DEADTIME_DTVAL_MASK, FTM_DEADTIME_DTVAL(count));
}

static inline void FTM_DRV_SetInitTriggerCmd(FTM_Type * const ftmBase,
                                             bool enable)
{
    ftmBase->EXTTRIG = (ftmBase->EXTTRIG & ~FTM_EXTTRIG_INITTRIGEN_MASK) | FTM_EXTTRIG_INITTRIGEN(enable);
}

static inline bool FTM_DRV_IsChnTriggerGenerated(const FTM_Type * ftmBase)
{
    return (ftmBase->EXTTRIG & FTM_EXTTRIG_TRIGF_MASK) != 0U;
}

static inline void FTM_DRV_ClearChnTriggerFlag(FTM_Type * const ftmBase)
{
    FTM_RMW_EXTTRIG_REG(ftmBase, FTM_EXTTRIG_TRIGF_MASK, FTM_EXTTRIG_TRIGF(0UL));
}

static inline void FTM_DRV_SetQuadDecoderCmd(FTM_Type * const ftmBase,
                                             bool enable)
{
    if (enable)
    {
        ((ftmBase)->QDCTRL) |= (1UL << FTM_QDCTRL_QUADEN_SHIFT);
    }
    else
    {
        ((ftmBase)->QDCTRL) &= ~(1UL << FTM_QDCTRL_QUADEN_SHIFT);
    }
}

static inline void FTM_DRV_SetQuadPhaseAFilterCmd(FTM_Type * const ftmBase,
                                                  bool enable)
{
    if (enable)
    {
        ((ftmBase)->QDCTRL) |= (1UL << FTM_QDCTRL_PHAFLTREN_SHIFT);
    }
    else
    {
        ((ftmBase)->QDCTRL) &= ~(1UL << FTM_QDCTRL_PHAFLTREN_SHIFT);
    }
}

static inline void FTM_DRV_SetQuadPhaseAPolarity(FTM_Type * const ftmBase,
                                                 uint8_t mode)
{
    FTM_RMW_QDCTRL(ftmBase, FTM_QDCTRL_PHAPOL_MASK, FTM_QDCTRL_PHAPOL(mode));
}

static inline void FTM_DRV_SetQuadPhaseBPolarity(FTM_Type * const ftmBase,
                                                 uint8_t mode)
{
    FTM_RMW_QDCTRL(ftmBase, FTM_QDCTRL_PHBPOL_MASK, FTM_QDCTRL_PHBPOL(mode));
}

static inline void FTM_DRV_SetQuadMode(FTM_Type * const ftmBase,
                                       uint8_t quadMode)
{
    FTM_RMW_QDCTRL(ftmBase, FTM_QDCTRL_QUADMODE_MASK, FTM_QDCTRL_QUADMODE(quadMode));
}

static inline bool FTM_DRV_GetQuadDir(const FTM_Type * ftmBase)
{
    return (ftmBase->QDCTRL & FTM_QDCTRL_QUADIR_MASK) != 0U;
}

static inline bool FTM_DRV_GetQuadTimerOverflowDir(const FTM_Type * ftmBase)
{
    return (ftmBase->QDCTRL & FTM_QDCTRL_TOFDIR_MASK) != 0U;
}

static inline void FTM_DRV_SetQuadPhaseBFilterCmd(FTM_Type * const ftmBase,
                                                  bool enable)
{
    if (enable)
    {
        ((ftmBase)->QDCTRL) |= (1UL << FTM_QDCTRL_PHBFLTREN_SHIFT);
    }
    else
    {
        ((ftmBase)->QDCTRL) &= ~(1UL << FTM_QDCTRL_PHBFLTREN_SHIFT);
    }
}

static inline void FTM_DRV_SetFaultInputFilterVal(FTM_Type * const ftmBase,
                                                  uint32_t value)
{
    FTM_RMW_FLTCTRL(ftmBase, FTM_FLTCTRL_FFVAL_MASK, FTM_FLTCTRL_FFVAL(value));
}

static inline void FTM_DRV_SetFaultInputFilterCmd(FTM_Type * const ftmBase,
                                                  uint8_t inputNum,
                                                  bool enable)
{
    DEV_ASSERT(inputNum < CHAN4_IDX);

    if (enable)
    {
        ((ftmBase)->FLTCTRL) |=  (1UL << (inputNum + FTM_FLTCTRL_FFLTR0EN_SHIFT));
    }
    else
    {
        ((ftmBase)->FLTCTRL) &=  ~(1UL << (inputNum + FTM_FLTCTRL_FFLTR0EN_SHIFT));
    }
}

static inline void FTM_DRV_ClearFaultControl(FTM_Type * const ftmBase)
{
    ((ftmBase)->FLTCTRL) =  0U;
}

static inline void FTM_DRV_SetFaultInputCmd(FTM_Type * const ftmBase,
                                            uint8_t inputNum,
                                            bool enable)
{
    DEV_ASSERT(inputNum < CHAN4_IDX);

    if (enable)
    {
        ((ftmBase)->FLTCTRL) |=  (1UL << inputNum);
    }
    else
    {
        ((ftmBase)->FLTCTRL) &=  ~(1UL << inputNum);
    }
}

static inline void FTM_DRV_SetPwmFaultBehavior(FTM_Type * const ftmBase,
                                               bool enable)
{
    if (enable)
    {
        ((ftmBase)->FLTCTRL) |=  (1UL << FTM_FLTCTRL_FSTATE_SHIFT);
    }
    else
    {
        ((ftmBase)->FLTCTRL) &=  ~(1UL << FTM_FLTCTRL_FSTATE_SHIFT);
    }
}

static inline void FTM_DRV_SetInvctrlReg(FTM_Type * const ftmBase,
                                         uint32_t regVal)
{
    ((ftmBase)->INVCTRL) = regVal;
}

static inline void FTM_DRV_SetAllChnSoftwareCtrlCmd(FTM_Type * const ftmBase,
                                                    uint8_t channelsMask)
{
    uint32_t mask = FTM_SWOCTRL_CH0OC_MASK | FTM_SWOCTRL_CH1OC_MASK | FTM_SWOCTRL_CH2OC_MASK |
                    FTM_SWOCTRL_CH3OC_MASK | FTM_SWOCTRL_CH4OC_MASK | FTM_SWOCTRL_CH5OC_MASK |
                    FTM_SWOCTRL_CH6OC_MASK | FTM_SWOCTRL_CH7OC_MASK;
    ((ftmBase)->SWOCTRL) = (((ftmBase)->SWOCTRL) & (~(mask))) | channelsMask;
}

static inline void FTM_DRV_SetAllChnSoftwareCtrlVal(FTM_Type * const ftmBase,
                                                    uint8_t channelsValues)
{
    uint32_t mask = FTM_SWOCTRL_CH0OCV_MASK | FTM_SWOCTRL_CH1OCV_MASK | FTM_SWOCTRL_CH2OCV_MASK |
                        FTM_SWOCTRL_CH3OCV_MASK | FTM_SWOCTRL_CH4OCV_MASK | FTM_SWOCTRL_CH5OCV_MASK |
                        FTM_SWOCTRL_CH6OCV_MASK | FTM_SWOCTRL_CH7OCV_MASK;
   ((ftmBase)->SWOCTRL) = (((ftmBase)->SWOCTRL) & (~(mask))) | ((uint32_t)channelsValues << FTM_SWOCTRL_CH0OCV_SHIFT);
}

static inline void FTM_DRV_SoftwareOutputControl(FTM_Type * const ftmBase,
                                                 uint16_t value)
{
   ((ftmBase)->SWOCTRL) = value;
}

static inline void FTM_DRV_SetBdmMode(FTM_Type * const ftmBase,
                                      ftm_bdm_mode_t val)
{
    FTM_RMW_CONF(ftmBase, FTM_CONF_BDMMODE_MASK, FTM_CONF_BDMMODE(val));
}

static inline void FTM_DRV_SetSwoctrlHardwareSyncModeCmd(FTM_Type * const ftmBase,
                                                         bool enable)
{
    ftmBase->SYNCONF = (ftmBase->SYNCONF & ~FTM_SYNCONF_HWSOC_MASK) | FTM_SYNCONF_HWSOC(enable);
}

static inline void FTM_DRV_SetInvctrlHardwareSyncModeCmd(FTM_Type * const ftmBase,
                                                         bool enable)
{
    ftmBase->SYNCONF = (ftmBase->SYNCONF & ~FTM_SYNCONF_HWINVC_MASK) | FTM_SYNCONF_HWINVC(enable);
}

static inline void FTM_DRV_SetOutmaskHardwareSyncModeCmd(FTM_Type * const ftmBase,
                                                         bool enable)
{
    ftmBase->SYNCONF = (ftmBase->SYNCONF & ~FTM_SYNCONF_HWOM_MASK) | FTM_SYNCONF_HWOM(enable);
}

static inline void FTM_DRV_SetModCntinCvHardwareSyncModeCmd(FTM_Type * const ftmBase,
                                                            bool enable)
{
    ftmBase->SYNCONF = (ftmBase->SYNCONF & ~FTM_SYNCONF_HWWRBUF_MASK) | FTM_SYNCONF_HWWRBUF(enable);
}

static inline void FTM_DRV_SetCounterHardwareSyncModeCmd(FTM_Type * const ftmBase,
                                                         bool enable)
{
    ftmBase->SYNCONF = (ftmBase->SYNCONF & ~FTM_SYNCONF_HWRSTCNT_MASK) | FTM_SYNCONF_HWRSTCNT(enable);
}

static inline void FTM_DRV_SetSwoctrlSoftwareSyncModeCmd(FTM_Type * const ftmBase,
                                                         bool enable)
{
    ftmBase->SYNCONF = (ftmBase->SYNCONF & ~FTM_SYNCONF_SWSOC_MASK) | FTM_SYNCONF_SWSOC(enable);
}

static inline void FTM_DRV_SetInvctrlSoftwareSyncModeCmd(FTM_Type * const ftmBase,
                                                         bool enable)
{
    ftmBase->SYNCONF = (ftmBase->SYNCONF & ~FTM_SYNCONF_SWINVC_MASK) | FTM_SYNCONF_SWINVC(enable);
}

static inline void FTM_DRV_SetOutmaskSoftwareSyncModeCmd(FTM_Type * const ftmBase,
                                                         bool enable)
{
    ftmBase->SYNCONF = (ftmBase->SYNCONF & ~FTM_SYNCONF_SWOM_MASK) | FTM_SYNCONF_SWOM(enable);
}

static inline void FTM_DRV_SetModCntinCvSoftwareSyncModeCmd(FTM_Type * const ftmBase,
                                                            bool enable)
{
    ftmBase->SYNCONF = (ftmBase->SYNCONF & ~FTM_SYNCONF_SWWRBUF_MASK) | FTM_SYNCONF_SWWRBUF(enable);
}

static inline void FTM_DRV_SetHwTriggerSyncModeCmd(FTM_Type * const ftmBase,
                                                   bool enable)
{
    ftmBase->SYNCONF = (ftmBase->SYNCONF & ~FTM_SYNCONF_HWTRIGMODE_MASK) | FTM_SYNCONF_HWTRIGMODE(enable);
}

static inline void FTM_DRV_SetCounterSoftwareSyncModeCmd(FTM_Type * const ftmBase,
                                                         ftm_pwm_sync_mode_t update_mode)
{
    ftmBase->SYNCONF = (ftmBase->SYNCONF & ~FTM_SYNCONF_SWRSTCNT_MASK) | FTM_SYNCONF_SWRSTCNT(update_mode);
}

static inline void FTM_DRV_SetPwmSyncModeCmd(FTM_Type * const ftmBase,
                                             bool mode)
{
    ftmBase->SYNCONF = (ftmBase->SYNCONF & ~FTM_SYNCONF_SYNCMODE_MASK) | FTM_SYNCONF_SYNCMODE(mode);
}

static inline void FTM_DRV_SetSwoctrlPwmSyncModeCmd(FTM_Type * const ftmBase,
                                                    ftm_reg_update_t mode)
{
    ftmBase->SYNCONF = (ftmBase->SYNCONF & ~FTM_SYNCONF_SWOC_MASK) | FTM_SYNCONF_SWOC(mode);
}

static inline void FTM_DRV_SetInvctrlPwmSyncModeCmd(FTM_Type * const ftmBase,
                                                    ftm_reg_update_t mode)
{
    ftmBase->SYNCONF = (ftmBase->SYNCONF & ~FTM_SYNCONF_INVC_MASK) | FTM_SYNCONF_INVC(mode);
}

static inline void FTM_DRV_SetCntinPwmSyncModeCmd(FTM_Type * const ftmBase,
                                                  ftm_reg_update_t mode)
{
    ftmBase->SYNCONF = (ftmBase->SYNCONF & ~FTM_SYNCONF_CNTINC_MASK) | FTM_SYNCONF_CNTINC(mode);
}

#if FEATURE_FTM_HAS_SUPPORTED_DITHERING
static inline void FTM_DRV_SetModFracVal(FTM_Type * const ftmBase,
                                         uint8_t value)
{
    FTM_RMW_MOD_MIRROR(ftmBase, FTM_MOD_MIRROR_FRACMOD_MASK, FTM_MOD_MIRROR_FRACMOD(value));
}

static inline void FTM_DRV_SetChnMatchFracVal(FTM_Type * const ftmBase,
                                              uint8_t channel,
                                              uint8_t value)
{
    FTM_RMW_CnV_MIRROR(ftmBase, channel, FTM_CV_MIRROR_FRACVAL_MASK, FTM_CV_MIRROR_FRACVAL(value));
}
#endif

static inline void FTM_DRV_SyncBit(SIM_Type * const simBase,
                                   uint32_t instance,
                                   bool enable)
{
    uint32_t instTemp = instance;

    if (instTemp > 3U)
    {
        instTemp = instance + 7U;
    }

    if (true == enable)
    {
        simBase->FTMOPT1 |= (1U << instTemp);
    }
    else
    {
        simBase->FTMOPT1 &= ~(1U << instTemp);
    }
}

void FTM_DRV_Reset(FTM_Type * const ftmBase);

void FTM_DRV_InitModule(FTM_Type * const ftmBase,
                        ftm_clock_ps_t ftmClockPrescaler);

void FTM_DRV_SetChnTriggerCmd(FTM_Type * const ftmBase,
                              uint8_t channel,
                              bool enable);

void FTM_DRV_SetChnInputCaptureFilter(FTM_Type * const ftmBase,
                                      uint8_t channel,
                                      uint8_t value);

#if defined(__cplusplus)
}
#endif



#endif 


