
#ifndef CMP_H
#define CMP_H

#include <stdint.h>
#include <stdbool.h>
#include "device_registers.h"
#include "cmp_driver.h"




 #if defined(__cplusplus)
extern "C" {
#endif

cmp_mode_t CMP_GetFunctionalMode(const CMP_Type* baseAddr);

void CMP_SetFunctionalMode(CMP_Type* baseAddr, cmp_mode_t mode, uint8_t filter_sample_count, uint8_t filter_sample_period);

static inline bool CMP_GetDMATriggerState(const CMP_Type* baseAddr)
{
    return (bool)(((baseAddr->C0) >> (CMP_C0_DMAEN_SHIFT)) & 1U);
}

static inline void CMP_SetDMATriggerState(CMP_Type* baseAddr, bool to_set)
{
    baseAddr->C0 = (baseAddr->C0 & (~(CMP_C0_DMAEN_MASK))) | ((uint32_t)to_set << CMP_C0_DMAEN_SHIFT);
}

static inline cmp_output_trigger_t CMP_GetOutputInterruptTrigger(const CMP_Type* baseAddr)
{
    bool rising_enabled = (bool)(((baseAddr->C0) >> CMP_C0_IER_SHIFT) & 1U);
    bool falling_enabled = (bool)(((baseAddr->C0) >> CMP_C0_IEF_SHIFT) & 1U);
    return (cmp_output_trigger_t) (((uint32_t)rising_enabled << (uint32_t)1U) | ((uint32_t)falling_enabled));
}

static inline void CMP_SetOutputInterruptTrigger(CMP_Type* baseAddr, cmp_output_trigger_t to_set)
{
    uint32_t tmp = baseAddr->C0;
    tmp &= ~(CMP_C0_IER_MASK) & ~(CMP_C0_IEF_MASK);
    tmp |= CMP_C0_IER((uint32_t)to_set>>1) | CMP_C0_IEF((uint32_t)to_set & (uint32_t)0x01);
    baseAddr->C0 = tmp;
}

static inline uint8_t CMP_GetFilterSamplePeriod(const CMP_Type* baseAddr)
{
    uint32_t tmp = baseAddr->C0;
    tmp = (tmp & CMP_C0_FPR_MASK) >> CMP_C0_FPR_SHIFT;
    return ( uint8_t ) (tmp);
}

static inline void CMP_SetFilterSamplePeriod(CMP_Type* baseAddr, uint8_t to_set)
{
    uint32_t tmp = baseAddr->C0;
    baseAddr->C0 &= ~(CMP_C0_FPR_MASK);
    tmp &= ~(CMP_C0_FPR_MASK);
    tmp |= CMP_C0_FPR(to_set);
    baseAddr->C0 = tmp;
}

static inline cmp_power_mode_t CMP_GetPowerMode(const CMP_Type* baseAddr)
{
    return (cmp_power_mode_t)(((baseAddr->C0) >> CMP_C0_PMODE_SHIFT) & 1U);
}

static inline void CMP_SetPowerMode(CMP_Type* baseAddr, cmp_power_mode_t to_set)
{
    (baseAddr->C0) = ((baseAddr->C0) & (~(CMP_C0_PMODE_MASK))) | ((uint32_t)to_set << CMP_C0_PMODE_SHIFT);
}

static inline cmp_inverter_t CMP_GetInverterState(const CMP_Type* baseAddr)
{
    return (cmp_inverter_t)(((baseAddr->C0) >> CMP_C0_INVT_SHIFT) & 1U);
}

static inline void CMP_SetInverterState(CMP_Type* baseAddr, cmp_inverter_t to_set)
{
    (baseAddr->C0) = ((baseAddr->C0) & (~(CMP_C0_INVT_MASK))) | ((uint32_t)to_set << CMP_C0_INVT_SHIFT);
}

static inline cmp_output_select_t CMP_GetComparatorOutputSource(const CMP_Type* baseAddr)
{
    return (cmp_output_select_t)(((baseAddr->C0) >> CMP_C0_COS_SHIFT) & 1U);
}

static inline void CMP_SetComparatorOutputSource(CMP_Type* baseAddr, cmp_output_select_t to_set)
{
    (baseAddr->C0) = ((baseAddr->C0) & (~(CMP_C0_COS_MASK))) | ((uint32_t)to_set << CMP_C0_COS_SHIFT);
}

static inline cmp_output_enable_t CMP_GetOutputPinState(const CMP_Type* baseAddr)
{
    return (cmp_output_enable_t)(((baseAddr->C0) >> CMP_C0_OPE_SHIFT) & 1U);
}

static inline void CMP_SetOutputPinState(CMP_Type* baseAddr, cmp_output_enable_t to_set)
{

    (baseAddr->C0) = ((baseAddr->C0) & (~(CMP_C0_OPE_MASK))) | ((uint32_t)to_set << CMP_C0_OPE_SHIFT);
}

static inline uint8_t CMP_GetFilterSampleCount(const CMP_Type* baseAddr)
{
    uint32_t tmp = baseAddr->C0;
    tmp = (tmp & CMP_C0_FILTER_CNT_MASK) >> CMP_C0_FILTER_CNT_SHIFT;
    return ( uint8_t ) (tmp);
}

static inline void CMP_SetFilterSampleCount(CMP_Type* baseAddr, uint8_t to_set)
{
    uint32_t tmp = baseAddr->C0;
    baseAddr->C0 &= ~(CMP_C0_FILTER_CNT_MASK);
    tmp &= ~(CMP_C0_FILTER_CNT_MASK);
    tmp |= CMP_C0_FILTER_CNT(to_set);
    baseAddr->C0 = tmp;
}

#if FEATURE_CMP_HAS_HARD_BLOCK_OFFSET

static inline cmp_offset_t CMP_GetOffset(const CMP_Type* baseAddr)
{
    return (cmp_offset_t)(((baseAddr->C0) >> CMP_C0_OFFSET_SHIFT) & 1U);
}

static inline void CMP_SetOffset(CMP_Type* baseAddr, cmp_offset_t to_set)
{
    uint32_t tmp = baseAddr->C0;
    tmp &= ~(CMP_C0_OFFSET_MASK);
    tmp |= CMP_C0_OFFSET(to_set);
    baseAddr->C0 = tmp;
}

#endif

static inline cmp_hysteresis_t CMP_GetHysteresis(const CMP_Type* baseAddr)
{
    uint32_t tmp = baseAddr->C0;
    tmp = (tmp & CMP_C0_HYSTCTR_MASK) >> CMP_C0_HYSTCTR_SHIFT;
    return ( cmp_hysteresis_t ) (tmp);
}

static inline void CMP_SetHysteresis(CMP_Type* baseAddr, cmp_hysteresis_t to_set)
{
    uint32_t tmp = baseAddr->C0;
    tmp &= ~(CMP_C0_HYSTCTR_MASK);
    tmp |= CMP_C0_HYSTCTR(to_set);
    baseAddr->C0 = tmp;
}

static inline cmp_port_mux_t CMP_GetPositivePortInput(const CMP_Type* baseAddr)
{
    uint32_t tmp = baseAddr->C1;
    tmp = (tmp & CMP_C1_INPSEL_MASK) >> CMP_C1_INPSEL_SHIFT;
    return ( cmp_port_mux_t ) (tmp);
}

static inline void CMP_SetPositivePortInput(CMP_Type* baseAddr, cmp_port_mux_t to_set)
{
    uint32_t tmp = baseAddr->C1;
    tmp &= ~(CMP_C1_INPSEL_MASK);
    tmp |= CMP_C1_INPSEL(to_set);
    baseAddr->C1 = tmp;
}

static inline cmp_port_mux_t CMP_GetNegativePortInput(const CMP_Type* baseAddr)
{
    uint32_t tmp = baseAddr->C1;
    tmp = (tmp & CMP_C1_INNSEL_MASK) >> CMP_C1_INNSEL_SHIFT;
    return ( cmp_port_mux_t ) (tmp);
}

static inline void CMP_SetNegativePortInput(CMP_Type* baseAddr, cmp_port_mux_t to_set)
{
    uint32_t tmp = baseAddr->C1;
    tmp &= ~(CMP_C1_INNSEL_MASK);
    tmp |= CMP_C1_INNSEL(to_set);
    baseAddr->C1 = tmp;
}

static inline cmp_ch_list_t CMP_GetRoundRobinChannels(const CMP_Type* baseAddr)
{
    uint32_t tmp = baseAddr->C1;
    tmp =  tmp & (uint32_t)CMP_ROUND_ROBIN_CHANNELS_MASK;
    return(cmp_ch_list_t) (tmp >> CMP_ROUND_ROBIN_CHANNELS_SHIFT);
}

static inline void CMP_SetRoundRobinChannels(CMP_Type* baseAddr, cmp_ch_list_t to_set)
{
    uint32_t tmp = baseAddr->C1;
    tmp &= ~(uint32_t)(CMP_ROUND_ROBIN_CHANNELS_MASK);
    tmp |= (uint32_t)to_set << (uint32_t)CMP_ROUND_ROBIN_CHANNELS_SHIFT;
    baseAddr->C1 = tmp;
}

static inline bool CMP_GetDACState(const CMP_Type* baseAddr)
{
    return (bool)(((baseAddr->C1) >> CMP_C1_DACEN_SHIFT) & 1U);
}

static inline void CMP_SetDACState(CMP_Type* baseAddr, bool to_set)
{
    (baseAddr->C1) = ((baseAddr->C1) & (~(CMP_C1_DACEN_MASK))) | ((uint32_t)to_set << CMP_C1_DACEN_SHIFT);
}

static inline cmp_voltage_reference_t CMP_GetVoltageReference(const CMP_Type* baseAddr)
{
    return (cmp_voltage_reference_t)(((baseAddr->C1) >> CMP_C1_VRSEL_SHIFT) & 1U);
}

static inline void CMP_SetVoltageReference(CMP_Type* baseAddr, cmp_voltage_reference_t to_set)
{
    (baseAddr->C1) = ((baseAddr->C1) & (~(CMP_C1_VRSEL_SHIFT))) | ((uint32_t)to_set << CMP_C1_VRSEL_SHIFT);
}

static inline cmp_ch_number_t CMP_GetPlusMUXControl(const CMP_Type* baseAddr)
{
    uint32_t tmp = baseAddr->C1;
    tmp = (tmp & CMP_C1_PSEL_MASK) >> CMP_C1_PSEL_SHIFT;
    return ( cmp_ch_number_t ) (tmp);
}

static inline void CMP_SetPlusMuxControl(CMP_Type* baseAddr, cmp_ch_number_t to_set)
{
    uint32_t tmp = baseAddr->C1;
    tmp &= ~(CMP_C1_PSEL_MASK);
    tmp |= CMP_C1_PSEL(to_set);
    baseAddr->C1 = tmp;
}

static inline cmp_ch_number_t CMP_GetMinusMUXControl(const CMP_Type* baseAddr)
{
    uint32_t tmp = baseAddr->C1;
    tmp = (tmp & CMP_C1_MSEL_MASK) >> CMP_C1_MSEL_SHIFT;
    return ( cmp_ch_number_t ) (tmp);
}

static inline void CMP_SetMinusMUXControl(CMP_Type* baseAddr, cmp_ch_number_t to_set)
{
    uint32_t tmp = baseAddr->C1;
    tmp &= ~(CMP_C1_MSEL_MASK);
    tmp |= CMP_C1_MSEL(to_set);
    baseAddr->C1 = tmp;
}

static inline uint8_t CMP_GetVoltage(const CMP_Type* baseAddr)
{
    uint32_t tmp = baseAddr->C1;
    tmp = (tmp & CMP_C1_VOSEL_MASK) >> CMP_C1_VOSEL_SHIFT;
    return ( uint8_t ) (tmp);
}

static inline void CMP_SetVoltage(CMP_Type* baseAddr, uint8_t to_set)
{
    uint32_t tmp = baseAddr->C1;
    tmp &= ~(CMP_C1_VOSEL_MASK);
    tmp |= CMP_C1_VOSEL(to_set);
    baseAddr->C1 = tmp;
}

static inline bool CMP_GetRoundRobinState(const CMP_Type* baseAddr)
{
    return (bool)(((baseAddr->C2) >> CMP_C2_RRE_SHIFT) & 1U);
}

static inline void CMP_SetRoundRobinState(CMP_Type* baseAddr, bool to_set)
{
    (baseAddr->C2) = ((baseAddr->C2) &(~(CMP_C2_RRE_MASK))) | ((uint32_t)to_set << CMP_C2_RRE_SHIFT);
}

static inline bool CMP_GetRoundRobinInterruptState(const CMP_Type* baseAddr)
{
    return (bool)(((baseAddr->C2) >> CMP_C2_RRIE_SHIFT) & 1U);
}

static inline void CMP_SetRoundRobinInterruptState(CMP_Type* baseAddr, bool to_set)
{
    (baseAddr->C2) = ((baseAddr->C2) & (~(CMP_C2_RRIE_SHIFT))) | ((uint32_t)to_set << CMP_C2_RRIE_SHIFT);
}

static inline cmp_fixed_port_t CMP_GetFixedPort(const CMP_Type* baseAddr)
{
    return (cmp_fixed_port_t)(((baseAddr->C2) >> CMP_C2_FXMP_SHIFT) & 1U);
}

static inline void CMP_SetFixedPort(CMP_Type* baseAddr, cmp_fixed_port_t to_set)
{
    (baseAddr->C2) = ((baseAddr->C2) & (~(CMP_C2_FXMP_MASK))) | ((uint32_t)to_set << CMP_C2_FXMP_SHIFT);
}

static inline cmp_ch_number_t CMP_GetFixedChannel(const CMP_Type* baseAddr)
{
    uint32_t tmp = baseAddr->C2;
    tmp = (tmp & CMP_C2_FXMXCH_MASK) >> CMP_C2_FXMXCH_SHIFT;
    return ( cmp_ch_number_t ) (tmp);
}

static inline void CMP_SetFixedChannel(CMP_Type* baseAddr, cmp_ch_number_t to_set)
{
    uint32_t tmp = baseAddr->C2;
    tmp &= ~(CMP_C2_FXMXCH_MASK);
    tmp |= CMP_C2_FXMXCH(to_set);
    baseAddr->C2 = tmp;
}

static inline uint8_t CMP_GetRoundRobinSamplesNumber(const CMP_Type* baseAddr)
{
    uint32_t tmp = baseAddr->C2;
    tmp = (tmp & CMP_C2_NSAM_MASK) >> CMP_C2_NSAM_SHIFT;
    return ( uint8_t ) (tmp);
}

static inline void CMP_SetRoundRobinSamplesNumber(CMP_Type* baseAddr, uint8_t to_set)
{
    uint32_t tmp = baseAddr->C2;
    tmp &= ~(CMP_C2_NSAM_MASK);
    tmp |= CMP_C2_NSAM(to_set);
    baseAddr->C2 = tmp;
}

#if FEATURE_CMP_HAS_INIT_DELAY

static inline uint8_t CMP_GetInitDelay(const CMP_Type* baseAddr)
{
    uint32_t tmp = baseAddr->C2;
    tmp = (tmp & CMP_C2_INITMOD_MASK) >> CMP_C2_INITMOD_SHIFT;
    return ( uint8_t ) (tmp);
}

static inline void CMP_SetInitDelay(CMP_Type* baseAddr, uint8_t to_set)
{
    uint32_t tmp = baseAddr->C2;
    tmp &= ~(CMP_C2_INITMOD_MASK);
    tmp |= CMP_C2_INITMOD(to_set);
    baseAddr->C2 = tmp;
}

#endif

static inline cmp_ch_list_t CMP_GetLastComparisonResult(const CMP_Type* baseAddr)
{
    uint32_t tmp = baseAddr->C2;
    tmp = (tmp & CMP_C2_ACOn_MASK) >> CMP_C2_ACOn_SHIFT;
    return ( cmp_ch_list_t ) (tmp);
}

static inline void CMP_SetPresetState(CMP_Type* baseAddr, cmp_ch_list_t to_set)
{
    uint32_t tmp = baseAddr->C2;
    tmp &= ~(CMP_C2_ACOn_MASK);
    tmp |= CMP_C2_ACOn(to_set);
    baseAddr->C2 = tmp;
}

#if FEATURE_CMP_DAC_FIX_SELECTION
static inline bool CMP_GetFixedDACState(const CMP_Type* baseAddr)
{
    return (bool)(((baseAddr->C2) >> CMP_C2_FXDACI_SHIFT) & 1U);
}

static inline void CMP_SetFixedDACState(CMP_Type* baseAddr, bool to_set)
{
    (baseAddr->C2) = ((baseAddr->C2) & (~(CMP_C2_FXDACI_MASK))) | ((uint32_t)to_set << CMP_C2_FXDACI_SHIFT);
}

#endif

#if defined(__cplusplus)
}
#endif


#endif 

