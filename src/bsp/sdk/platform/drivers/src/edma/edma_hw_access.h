

#ifndef EDMA_HW_ACCESS_H
#define EDMA_HW_ACCESS_H

#include <stdint.h>
#include <stdbool.h>
#include "edma_driver.h"


#ifdef FEATURE_DMA_ENGINE_STALL 
typedef enum {
    EDMA_ENGINE_STALL_0_CYCLES = 0,
    EDMA_ENGINE_STALL_4_CYCLES = 2,
    EDMA_ENGINE_STALL_8_CYCLES = 3
} edma_engine_stall_t;
#endif


#if defined(__cplusplus)
extern "C" {
#endif


void EDMA_Init(DMA_Type * base);

void EDMA_CancelTransfer(DMA_Type * base);

void EDMA_CancelTransferWithError(DMA_Type * base);

static inline void EDMA_SetHaltOnErrorCmd(DMA_Type * base, bool haltOnError)
{
    uint32_t regValTemp;
#ifdef FEATURE_DMA_HWV3
    regValTemp = base->MP_CSR;
    regValTemp &= ~(DMA_MP_CSR_HAE_MASK);
    regValTemp |= DMA_MP_CSR_HAE(haltOnError ? 1UL : 0UL);
    base->MP_CSR = regValTemp;
#else
    regValTemp = base->CR;
    regValTemp &= ~(DMA_CR_HOE_MASK);
    regValTemp |= DMA_CR_HOE(haltOnError ? 1UL : 0UL);
    base->CR = regValTemp;
#endif
}



static inline void EDMA_SetChannelPriority(DMA_Type * base, uint8_t channel, edma_channel_priority_t priority)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif

#ifdef FEATURE_DMA_HWV3
    volatile uint32_t regValTemp;
    regValTemp = base->TCD[channel].CH_PRI;
    regValTemp &= (uint32_t)~(DMA_TCD_CH_PRI_APL_MASK);
    regValTemp |= (uint32_t)DMA_TCD_CH_PRI_APL(priority);
    base->TCD[channel].CH_PRI = regValTemp;
#else
    uint8_t regValTemp;
    uint8_t index = (uint8_t)FEATURE_DMA_CHN_TO_DCHPRI_INDEX(channel);
    regValTemp = base->DCHPRI[index];
    regValTemp &= (uint8_t)~(DMA_DCHPRI_CHPRI_MASK);
    regValTemp |= (uint8_t)DMA_DCHPRI_CHPRI(priority);
    base->DCHPRI[index] = regValTemp;
#endif
}

static inline void EDMA_SetChannelArbitrationMode(DMA_Type * base, edma_arbitration_algorithm_t channelArbitration)
{
    uint32_t regValTemp;
#ifdef FEATURE_DMA_HWV3
    regValTemp = base->MP_CSR;
    regValTemp &= ~(DMA_MP_CSR_ERCA_MASK);
    regValTemp |= DMA_MP_CSR_ERCA(channelArbitration);
    base->MP_CSR = regValTemp;
#else
    regValTemp = base->CR;
    regValTemp &= ~(DMA_CR_ERCA_MASK);
    regValTemp |= DMA_CR_ERCA(channelArbitration);
    base->CR = regValTemp;
#endif
}


static inline edma_arbitration_algorithm_t EDMA_GetChannelArbitrationMode(const DMA_Type * base)
{
    edma_arbitration_algorithm_t retVal;
#ifdef FEATURE_DMA_HWV3
    if (((base->MP_CSR >> DMA_MP_CSR_ERCA_SHIFT) & 1U) != 0U)
#else
    if (((base->CR >> DMA_CR_ERCA_SHIFT) & 1U) != 0U)
#endif
    {
        retVal = EDMA_ARBITRATION_ROUND_ROBIN;
    }
    else
    {
        retVal = EDMA_ARBITRATION_FIXED_PRIORITY;
    }
    return retVal;
}

#if FEATURE_DMA_CHANNEL_GROUP_COUNT > 0x1U
#ifdef FEATURE_DMA_HWV3
void EDMA_SetChannelPriorityGroup(DMA_Type * base, uint8_t channel, edma_group_priority_t channelPriorityGroup);
#else
void EDMA_SetGroupPriority(DMA_Type * base, edma_group_priority_t priority);
#endif

#ifndef FEATURE_DMA_HWV3
static inline void EDMA_SetGroupArbitrationMode(DMA_Type * base, edma_arbitration_algorithm_t groupArbitration)
{
    uint32_t regValTemp;
    regValTemp = base->CR;
    regValTemp &= ~(DMA_CR_ERGA_MASK);
    regValTemp |= DMA_CR_ERGA(groupArbitration);
    base->CR = regValTemp;
}
#endif
#endif

#ifdef FEATURE_DMA_HWV3
static inline void EDMA_SetMinorLoopMappingCmd(DMA_Type * base, uint8_t channel, bool enable)
{
    uint32_t regValTemp;
    regValTemp = base->TCD[channel].NBYTES.MLOFFNO;
    regValTemp &= ~(DMA_TCD_NBYTES_MLOFFNO_SMLOE_MASK);
    regValTemp &= ~(DMA_TCD_NBYTES_MLOFFNO_DMLOE_MASK);
    regValTemp |= DMA_TCD_NBYTES_MLOFFNO_SMLOE(enable ? 1UL : 0UL);
    regValTemp |= DMA_TCD_NBYTES_MLOFFNO_DMLOE(enable ? 1UL : 0UL);
    base->TCD[channel].NBYTES.MLOFFNO = regValTemp;
}
#else
static inline void EDMA_SetMinorLoopMappingCmd(DMA_Type * base, bool enable)
{
    uint32_t regValTemp;
    regValTemp = base->CR;
    regValTemp &= ~(DMA_CR_EMLM_MASK);
    regValTemp |= DMA_CR_EMLM(enable ? 1UL : 0UL);
    base->CR = regValTemp;
}
#endif

void EDMA_SetErrorIntCmd(DMA_Type * base, uint8_t channel, bool enable);

static inline uint32_t EDMA_GetErrorIntStatusFlag(const DMA_Type * base)
{
#ifdef FEATURE_DMA_HWV3
    return ((base->MP_ES & DMA_MP_ES_ERRCHN_MASK) >> DMA_MP_ES_ERRCHN_SHIFT);
#else
    return base->ERR;
#endif
}

static inline void EDMA_ClearErrorIntStatusFlag(DMA_Type * base, uint8_t channel)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
#ifdef FEATURE_DMA_HWV3
    base->TCD[channel].CH_ES |= DMA_TCD_CH_ES_ERR_MASK;
#else
    base->CERR = (uint8_t)channel;
#endif
}

void EDMA_SetDmaRequestCmd(DMA_Type * base, uint8_t channel, bool enable);

static inline void EDMA_ClearDoneStatusFlag(DMA_Type * base, uint8_t channel)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
#ifdef FEATURE_DMA_HWV3
    base->TCD[channel].CH_CSR |= DMA_TCD_CH_CSR_DONE_MASK;
#else
    base->CDNE = (uint8_t)channel;
#endif
}

static inline void EDMA_TriggerChannelStart(DMA_Type * base, uint8_t channel)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
#ifdef FEATURE_DMA_HWV3
    base->TCD[channel].CSR |= DMA_TCD_CSR_START_MASK;
#else
    base->SSRT = (uint8_t)channel;
#endif
}

static inline void EDMA_ClearIntStatusFlag(DMA_Type * base, uint8_t channel)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
#ifdef FEATURE_DMA_HWV3
    base->TCD[channel].CH_INT |= DMA_TCD_CH_INT_INT_MASK;
#else
    base->CINT = (uint8_t)channel;
#endif
}



void EDMA_TCDClearReg(DMA_Type * base, uint8_t channel);

#ifdef FEATURE_DMA_ENGINE_STALL
static inline void EDMA_TCDSetEngineStall(DMA_Type * base, uint8_t channel, edma_engine_stall_t cycles)
{
#ifdef DEV_ERROR_DETECT
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif    
    uint16_t regValTemp;
    regValTemp = base->TCD[channel].CSR;
    regValTemp &= ~(DMA_TCD_CSR_BWC_MASK);    
    regValTemp |= DMA_TCD_CSR_BWC(cycles);
    base->TCD[channel].CSR = regValTemp;
}
#endif

static inline void EDMA_TCDSetSrcAddr(DMA_Type * base, uint8_t channel, uint32_t address)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    base->TCD[channel].SADDR = address;
}

static inline void EDMA_TCDSetSrcOffset(DMA_Type * base, uint8_t channel, int16_t offset)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    base->TCD[channel].SOFF = (uint16_t)offset;
}

void EDMA_TCDSetAttribute(
                DMA_Type * base, uint8_t channel,
                edma_modulo_t srcModulo, edma_modulo_t destModulo,
                edma_transfer_size_t srcTransferSize, edma_transfer_size_t destTransferSize);

static inline void EDMA_TCDSetSrcTransferSize(DMA_Type * base, uint8_t channel, edma_transfer_size_t size)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    uint16_t regValTemp;
    regValTemp = base->TCD[channel].ATTR;
    regValTemp &= (uint16_t)(~(DMA_TCD_ATTR_SSIZE_MASK));
    regValTemp |= (uint16_t)(DMA_TCD_ATTR_SSIZE((uint16_t)size));
    base->TCD[channel].ATTR = regValTemp;
}

static inline void EDMA_TCDSetDestTransferSize(DMA_Type * base, uint8_t channel, edma_transfer_size_t size)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    uint16_t regValTemp;
    regValTemp = base->TCD[channel].ATTR;
    regValTemp &= (uint16_t)(~(DMA_TCD_ATTR_DSIZE_MASK));
    regValTemp |= (uint16_t)(DMA_TCD_ATTR_DSIZE((uint16_t)size));
    base->TCD[channel].ATTR = regValTemp;
}

void EDMA_TCDSetNbytes(DMA_Type * base, uint8_t channel, uint32_t nbytes);

static inline void EDMA_TCDSetSrcMinorLoopOffsetCmd(DMA_Type * base, uint8_t channel, bool enable)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
#ifdef FEATURE_DMA_HWV3
    uint32_t smloe = (base->TCD[channel].NBYTES.MLOFFNO & DMA_TCD_NBYTES_MLOFFNO_SMLOE_MASK) >> DMA_TCD_NBYTES_MLOFFNO_SMLOE_SHIFT;
    uint32_t dmloe = (base->TCD[channel].NBYTES.MLOFFNO & DMA_TCD_NBYTES_MLOFFNO_DMLOE_MASK) >> DMA_TCD_NBYTES_MLOFFNO_DMLOE_SHIFT;
    if ((smloe != 0UL) || (dmloe != 0UL))
    {
        uint32_t regValTemp;
        regValTemp = base->TCD[channel].NBYTES.MLOFFYES;
        regValTemp &= ~(DMA_TCD_NBYTES_MLOFFYES_SMLOE_MASK);
        regValTemp |= DMA_TCD_NBYTES_MLOFFYES_SMLOE(enable ? 1UL : 0UL);
        base->TCD[channel].NBYTES.MLOFFYES = regValTemp;
    }
#else
    if (((base->CR >> DMA_CR_EMLM_SHIFT) & 1U) != 0U)
    {
        uint32_t regValTemp;
        regValTemp = base->TCD[channel].NBYTES.MLOFFYES;
        regValTemp &= ~(DMA_TCD_NBYTES_MLOFFYES_SMLOE_MASK);
        regValTemp |= DMA_TCD_NBYTES_MLOFFYES_SMLOE(enable ? 1UL : 0UL);
        base->TCD[channel].NBYTES.MLOFFYES = regValTemp;
    }
#endif
}

static inline void EDMA_TCDSetDestMinorLoopOffsetCmd(DMA_Type * base, uint8_t channel, bool enable)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
#ifdef FEATURE_DMA_HWV3
    uint32_t smloe = (base->TCD[channel].NBYTES.MLOFFNO & DMA_TCD_NBYTES_MLOFFNO_SMLOE_MASK) >> DMA_TCD_NBYTES_MLOFFNO_SMLOE_SHIFT;
    uint32_t dmloe = (base->TCD[channel].NBYTES.MLOFFNO & DMA_TCD_NBYTES_MLOFFNO_DMLOE_MASK) >> DMA_TCD_NBYTES_MLOFFNO_DMLOE_SHIFT;
    if ((smloe != 0UL) || (dmloe != 0UL))
    {
        uint32_t regValTemp;
        regValTemp = base->TCD[channel].NBYTES.MLOFFYES;
        regValTemp &= ~(DMA_TCD_NBYTES_MLOFFYES_DMLOE_MASK);
        regValTemp |= DMA_TCD_NBYTES_MLOFFYES_DMLOE(enable ? 1UL : 0UL);
        base->TCD[channel].NBYTES.MLOFFYES = regValTemp;
    }
#else
    if (((base->CR >> DMA_CR_EMLM_SHIFT) & 1U) != 0U)
    {
        uint32_t regValTemp;
        regValTemp = base->TCD[channel].NBYTES.MLOFFYES;
        regValTemp &= ~(DMA_TCD_NBYTES_MLOFFYES_DMLOE_MASK);
        regValTemp |= DMA_TCD_NBYTES_MLOFFYES_DMLOE(enable ? 1UL : 0UL);
        base->TCD[channel].NBYTES.MLOFFYES = regValTemp;
    }
#endif
}

void EDMA_TCDSetMinorLoopOffset(DMA_Type * base, uint8_t channel, int32_t offset);

static inline void EDMA_TCDSetSrcLastAdjust(DMA_Type * base, uint8_t channel, int32_t size)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    base->TCD[channel].SLAST = (uint32_t)size;
}

static inline void EDMA_TCDSetDestAddr(DMA_Type * base, uint8_t channel, uint32_t address)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    base->TCD[channel].DADDR = address;
}

static inline void EDMA_TCDSetDestOffset(DMA_Type * base, uint8_t channel, int16_t offset)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    base->TCD[channel].DOFF = (uint16_t)offset;
}

static inline void EDMA_TCDSetDestLastAdjust(DMA_Type * base, uint8_t channel, int32_t adjust)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    base->TCD[channel].DLASTSGA = (uint32_t)adjust;
}

void EDMA_TCDSetScatterGatherLink(DMA_Type * base, uint8_t channel, uint32_t nextTCDAddr);

static inline void EDMA_TCDSetScatterGatherCmd(DMA_Type * base, uint8_t channel, bool enable)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    uint16_t regValTemp;
    regValTemp = base->TCD[channel].CSR;
    regValTemp &= (uint16_t)~(DMA_TCD_CSR_ESG_MASK);
    regValTemp |= (uint16_t)DMA_TCD_CSR_ESG(enable ? 1UL : 0UL);
    base->TCD[channel].CSR = regValTemp;
}

static inline void EDMA_TCDSetChannelMajorLink(DMA_Type * base, uint8_t channel, uint32_t majorLinkChannel, bool enable)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    uint16_t regValTemp;
    regValTemp = base->TCD[channel].CSR;
    regValTemp &= (uint16_t)~(DMA_TCD_CSR_MAJORLINKCH_MASK);
    regValTemp |= (uint16_t)DMA_TCD_CSR_MAJORLINKCH(majorLinkChannel);
    base->TCD[channel].CSR = regValTemp;
    regValTemp = base->TCD[channel].CSR;
    regValTemp &= (uint16_t)~(DMA_TCD_CSR_MAJORELINK_MASK);
    regValTemp |= (uint16_t)DMA_TCD_CSR_MAJORELINK(enable ? 1UL : 0UL);
    base->TCD[channel].CSR = regValTemp;
}

static inline void EDMA_TCDSetDisableDmaRequestAfterTCDDoneCmd(DMA_Type * base, uint8_t channel, bool disable)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    uint16_t regValTemp;
    regValTemp = base->TCD[channel].CSR;
    regValTemp &= (uint16_t)~(DMA_TCD_CSR_DREQ_MASK);
    regValTemp |= (uint16_t)DMA_TCD_CSR_DREQ(disable ? 1UL : 0UL);
    base->TCD[channel].CSR = regValTemp;
}

static inline void EDMA_TCDSetMajorHalfCompleteIntCmd(DMA_Type * base, uint8_t channel, bool enable)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    uint16_t regValTemp;
    regValTemp = base->TCD[channel].CSR;
    regValTemp &= (uint16_t)~(DMA_TCD_CSR_INTHALF_MASK);
    regValTemp |= (uint16_t)DMA_TCD_CSR_INTHALF(enable ? 1UL : 0UL);
    base->TCD[channel].CSR = regValTemp;
}

static inline void EDMA_TCDSetMajorCompleteIntCmd(DMA_Type * base, uint8_t channel, bool enable)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    uint16_t regValTemp;
    regValTemp = base->TCD[channel].CSR;
    regValTemp &= (uint16_t)~(DMA_TCD_CSR_INTMAJOR_MASK);
    regValTemp |= (uint16_t)DMA_TCD_CSR_INTMAJOR(enable ? 1UL : 0UL);
    base->TCD[channel].CSR = regValTemp;
}

void EDMA_TCDSetChannelMinorLink(DMA_Type * base, uint8_t channel, uint32_t linkChannel, bool enable);

void EDMA_TCDSetMajorCount(DMA_Type * base, uint8_t channel, uint32_t count);

uint32_t EDMA_TCDGetCurrentMajorCount(const DMA_Type * base, uint8_t channel);

#ifdef FEATURE_DMAMUX_AVAILABLE
void DMAMUX_Init(DMAMUX_Type * base);
#endif

#ifdef FEATURE_DMAMUX_AVAILABLE
static inline void DMAMUX_SetChannelCmd(DMAMUX_Type * base, uint8_t channel, bool enable)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMAMUX_CHANNELS);
#endif
    uint32_t regIndex = FEATURE_DMAMUX_CHN_REG_INDEX(channel);
    uint8_t regValTemp = base->CHCFG[regIndex];
    regValTemp &= (uint8_t)~(DMAMUX_CHCFG_ENBL_MASK);
    regValTemp |= (uint8_t)DMAMUX_CHCFG_ENBL(enable ? 1U : 0U);
    base->CHCFG[regIndex] = regValTemp;
}
#endif

#ifdef FEATURE_DMAMUX_AVAILABLE
#ifdef FEATURE_DMAMUX_HAS_TRIG
static inline void DMAMUX_SetChannelTrigger(DMAMUX_Type * base, uint8_t channel, bool enable)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMAMUX_CHANNELS);
#endif
    uint32_t regIndex = FEATURE_DMAMUX_CHN_REG_INDEX(channel);
    uint8_t regValTemp;
    regValTemp = base->CHCFG[regIndex];
    regValTemp &= (uint8_t)~(DMAMUX_CHCFG_TRIG_MASK);
    regValTemp |= (uint8_t)DMAMUX_CHCFG_TRIG(enable ? 1U : 0U);
    base->CHCFG[regIndex] = regValTemp;
}
#endif
#endif

#ifdef FEATURE_DMAMUX_AVAILABLE
static inline void DMAMUX_SetChannelSource(DMAMUX_Type * base, uint8_t channel, uint8_t source)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMAMUX_CHANNELS);
#endif
    uint32_t regIndex = FEATURE_DMAMUX_CHN_REG_INDEX(channel);
    uint8_t regValTemp;
    regValTemp = base->CHCFG[regIndex];
    regValTemp &= (uint8_t)~(DMAMUX_CHCFG_SOURCE_MASK);
    regValTemp |= (uint8_t)DMAMUX_CHCFG_SOURCE(source);
    base->CHCFG[regIndex] = regValTemp;
}
#endif

DMA_Type * EDMA_DRV_GetDmaRegBaseAddr(uint32_t instance);

#if defined(__cplusplus)
}
#endif

#endif 




