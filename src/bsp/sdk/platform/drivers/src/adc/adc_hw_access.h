
#ifndef ADC_HW_ACCESS_H
#define ADC_HW_ACCESS_H

#include <stdint.h>
#include <stdbool.h>
#include "device_registers.h"
#include "adc_driver.h"





#if defined (__cplusplus)
extern "C" {
#endif


static inline bool ADC_GetConvActiveFlag(const ADC_Type * const baseAddr)
{
    uint32_t tmp = (uint32_t)baseAddr->SC2;
    tmp = (tmp & ADC_SC2_ADACT_MASK) >> ADC_SC2_ADACT_SHIFT;

    return (tmp != 0u) ? true : false;
}

static inline adc_clk_divide_t ADC_GetClockDivide(const ADC_Type * const baseAddr)
{
    uint32_t tmp = baseAddr->CFG1;
    tmp = (tmp & ADC_CFG1_ADIV_MASK) >> ADC_CFG1_ADIV_SHIFT;

    return (adc_clk_divide_t)(tmp);
}

static inline void ADC_SetClockDivide(ADC_Type * const baseAddr,
                                      const adc_clk_divide_t clockDivide)
{
    uint32_t tmp = baseAddr->CFG1;
    tmp &= ~(ADC_CFG1_ADIV_MASK);
    tmp |= ADC_CFG1_ADIV(clockDivide);
    baseAddr->CFG1 = tmp;
}

static inline uint8_t ADC_GetSampleTime(const ADC_Type * const baseAddr)
{
    uint32_t tmp = baseAddr->CFG2;
    tmp = (tmp & ADC_CFG2_SMPLTS_MASK) >> ADC_CFG2_SMPLTS_SHIFT;

    return (uint8_t)(tmp);
}

static inline void ADC_SetSampleTime(ADC_Type * const baseAddr,
                                     uint8_t sampletime)
{
    uint8_t rsampletime = (uint8_t)((sampletime > 0U) ? sampletime : 1U);
    uint32_t tmp = baseAddr->CFG2;
    tmp &= ~(ADC_CFG2_SMPLTS_MASK);
    tmp |= ADC_CFG2_SMPLTS(rsampletime);
    baseAddr->CFG2 = tmp;
}

static inline adc_resolution_t ADC_GetResolution(const ADC_Type * const baseAddr)
{
    uint32_t tmp = baseAddr->CFG1;
    tmp = (tmp & ADC_CFG1_MODE_MASK) >> ADC_CFG1_MODE_SHIFT;
    adc_resolution_t retValue;
    switch (tmp)
    {
        case 0x00U:
            retValue = ADC_RESOLUTION_8BIT;
            break;
        case 0x01U:
            retValue = ADC_RESOLUTION_12BIT;
            break;
        case 0x02U:
            retValue = ADC_RESOLUTION_10BIT;
            break;
        default:
            retValue = ADC_RESOLUTION_8BIT;
            break;
    }

    return retValue;
}

static inline void ADC_SetResolution(ADC_Type * const baseAddr,
                                     const adc_resolution_t resolution)
{
    uint32_t tmp = baseAddr->CFG1;
    tmp &= ~(ADC_CFG1_MODE_MASK);
    tmp |= ADC_CFG1_MODE(resolution);
    baseAddr->CFG1 = tmp;
}

static inline adc_input_clock_t ADC_GetInputClock(const ADC_Type * const baseAddr)
{
    uint32_t tmp = baseAddr->CFG1;
    tmp = (tmp & ADC_CFG1_ADICLK_MASK) >> ADC_CFG1_ADICLK_SHIFT;

    return (adc_input_clock_t)(tmp);
}

static inline void ADC_SetInputClock(ADC_Type * const baseAddr,
                                     const adc_input_clock_t inputClock)
{
    uint32_t tmp = baseAddr->CFG1;
    tmp &= ~(ADC_CFG1_ADICLK_MASK);
    tmp |= ADC_CFG1_ADICLK(inputClock);
    baseAddr->CFG1 = tmp;
}

static inline adc_trigger_t ADC_GetTriggerMode(const ADC_Type * const baseAddr)
{
    uint32_t tmp = baseAddr->SC2;
    tmp = (tmp & ADC_SC2_ADTRG_MASK) >> ADC_SC2_ADTRG_SHIFT;

    return (adc_trigger_t)(tmp);
}

static inline void ADC_SetTriggerMode(ADC_Type * const baseAddr,
                                      const adc_trigger_t trigger)
{
    uint32_t tmp = baseAddr->SC2;
    tmp &= ~(ADC_SC2_ADTRG_MASK);
    tmp |= ADC_SC2_ADTRG(trigger);
    baseAddr->SC2 = tmp;
}

static inline adc_pretrigger_sel_t ADC_GetPretriggerSelect(const uint32_t instance)
{
    const SIM_Type * const sim_base          = SIM;
    uint32_t currentVal                      = 0U;
    adc_pretrigger_sel_t returnVal           = ADC_PRETRIGGER_SEL_PDB;
    uint32_t mask[ADC_INSTANCE_COUNT] = {0U};
    uint32_t shift[ADC_INSTANCE_COUNT] = {0U};
#if (ADC_INSTANCE_COUNT == 1u)
    mask[0]  = SIM_ADCOPT_ADC0PRETRGSEL_MASK;
    shift[0] = SIM_ADCOPT_ADC0PRETRGSEL_SHIFT;
#elif (ADC_INSTANCE_COUNT == 2u)
    mask[0]  = SIM_ADCOPT_ADC0PRETRGSEL_MASK;
    mask[1]  = SIM_ADCOPT_ADC1PRETRGSEL_MASK;
    shift[0] = SIM_ADCOPT_ADC0PRETRGSEL_SHIFT;
    shift[1] = SIM_ADCOPT_ADC1PRETRGSEL_SHIFT;
#else
#error "Maximum supported value for ADC_INSTANCE_COUNT is 2."
#endif
    currentVal = (sim_base->ADCOPT & mask[instance]) >> shift[instance];
    switch(currentVal)
    {
        case ADC_PRETRIGGER_SEL_PDB:
            returnVal = ADC_PRETRIGGER_SEL_PDB;     break;
        case ADC_PRETRIGGER_SEL_TRGMUX:
            returnVal = ADC_PRETRIGGER_SEL_TRGMUX;  break;
        case ADC_PRETRIGGER_SEL_SW:
            returnVal = ADC_PRETRIGGER_SEL_SW;      break;
        default:
            DEV_ASSERT(false);                      break;
    }

    return returnVal;
}

static inline void ADC_SetPretriggerSelect(const uint32_t instance,
                                           const adc_pretrigger_sel_t pretriggerSel)
{
    SIM_Type * const simBase = SIM;
    uint32_t mask[ADC_INSTANCE_COUNT] = {0U};
#if (ADC_INSTANCE_COUNT == 1u)
    mask[0] = SIM_ADCOPT_ADC0PRETRGSEL_MASK;
#elif (ADC_INSTANCE_COUNT == 2u)
    mask[0] = SIM_ADCOPT_ADC0PRETRGSEL_MASK;
    mask[1] = SIM_ADCOPT_ADC1PRETRGSEL_MASK;
#else
#error "Maximum supported value for ADC_INSTANCE_COUNT is 2."
#endif
    uint32_t intermVal = 0U;

    intermVal = simBase->ADCOPT & (~ mask[instance]);

    switch(instance)
    {
    case 0:
        intermVal |= SIM_ADCOPT_ADC0PRETRGSEL(pretriggerSel);
        break;
    case 1:
        intermVal |= SIM_ADCOPT_ADC1PRETRGSEL(pretriggerSel);
        break;
    default:
        DEV_ASSERT(false);
        break;
    }

    simBase->ADCOPT = intermVal;
}

static inline adc_trigger_sel_t ADC_GetTriggerSelect(const uint32_t instance)
{
    const SIM_Type * const sim_base          = SIM;
    uint32_t currentVal                      = 0U;
    adc_trigger_sel_t returnVal              = ADC_TRIGGER_SEL_PDB;
    uint32_t mask[ADC_INSTANCE_COUNT] = {0U};
    uint32_t shift[ADC_INSTANCE_COUNT] = {0U};
#if (ADC_INSTANCE_COUNT == 1u)
    mask[0]  = SIM_ADCOPT_ADC0TRGSEL_MASK;
    shift[0] = SIM_ADCOPT_ADC0TRGSEL_SHIFT;
#elif (ADC_INSTANCE_COUNT == 2u)
    mask[0]  = SIM_ADCOPT_ADC0TRGSEL_MASK;
    mask[1]  = SIM_ADCOPT_ADC1TRGSEL_MASK;
    shift[0] = SIM_ADCOPT_ADC0TRGSEL_SHIFT;
    shift[1] = SIM_ADCOPT_ADC1TRGSEL_SHIFT;
#else
#error "Maximum supported value for ADC_INSTANCE_COUNT is 2."
#endif
    currentVal = (sim_base->ADCOPT & mask[instance]) >> shift[instance];
    switch(currentVal)
    {
    case ADC_TRIGGER_SEL_PDB:
        returnVal = ADC_TRIGGER_SEL_PDB;    break;
    case ADC_TRIGGER_SEL_TRGMUX:
        returnVal = ADC_TRIGGER_SEL_TRGMUX; break;
    default:
        DEV_ASSERT(false);                  break;
    }

    return returnVal;
}

static inline void ADC_SetTriggerSelect(const uint32_t instance,
                                        const adc_trigger_sel_t triggerSel)
{
    SIM_Type * const simBase = SIM;
    uint32_t mask[ADC_INSTANCE_COUNT] = {0U};
#if (ADC_INSTANCE_COUNT == 1u)
    mask[0] = SIM_ADCOPT_ADC0TRGSEL_MASK;
#elif (ADC_INSTANCE_COUNT == 2u)
    mask[0] = SIM_ADCOPT_ADC0TRGSEL_MASK;
    mask[1] = SIM_ADCOPT_ADC1TRGSEL_MASK;
#else
#error "Maximum supported value for ADC_INSTANCE_COUNT is 2."
#endif
    uint32_t intermVal = 0U;

    intermVal = simBase->ADCOPT & (~ mask[instance]);

    switch(instance)
    {
    case 0:
        intermVal |= SIM_ADCOPT_ADC0TRGSEL(triggerSel);
        break;
    case 1:
        intermVal |= SIM_ADCOPT_ADC1TRGSEL(triggerSel);
        break;
    default:
        DEV_ASSERT(false);
        break;
    }

    simBase->ADCOPT = intermVal;
}

static inline bool ADC_GetDMAEnableFlag(const ADC_Type * const baseAddr)
{
    uint32_t tmp = (uint32_t)baseAddr->SC2;
    tmp = (tmp & ADC_SC2_DMAEN_MASK) >> ADC_SC2_DMAEN_SHIFT;

    return (tmp != 0u) ? true : false;
}

static inline void ADC_SetDMAEnableFlag(ADC_Type * const baseAddr,
                                        const bool state)
{
    uint32_t tmp = (uint32_t)baseAddr->SC2;
    tmp &= (uint32_t)(~(ADC_SC2_DMAEN_MASK));
    tmp |= ADC_SC2_DMAEN(state ? (uint32_t)1u : (uint32_t)0u);
    baseAddr->SC2 = (uint32_t)tmp;
}

static inline adc_voltage_reference_t ADC_GetVoltageReference(const ADC_Type * const baseAddr)
{
    uint32_t tmp = baseAddr->SC2;
    tmp = (tmp & ADC_SC2_REFSEL_MASK) >> ADC_SC2_REFSEL_SHIFT;

    return (adc_voltage_reference_t)(tmp);
}

static inline void ADC_SetVoltageReference(ADC_Type * const baseAddr,
                                           const adc_voltage_reference_t voltageRef)
{
    uint32_t tmp = baseAddr->SC2;
    tmp &= ~(ADC_SC2_REFSEL_MASK);
    tmp |= ADC_SC2_REFSEL(voltageRef);
    baseAddr->SC2 = tmp;
}

static inline bool ADC_GetContinuousConvFlag(const ADC_Type * const baseAddr)
{
    uint32_t tmp = (uint32_t)baseAddr->SC3;
    tmp = (tmp & ADC_SC3_ADCO_MASK) >> ADC_SC3_ADCO_SHIFT;

    return (tmp != 0u) ? true : false;
}

static inline void ADC_SetContinuousConvFlag(ADC_Type * const baseAddr,
                                             const bool state)
{
    uint32_t tmp = (uint32_t)baseAddr->SC3;
    tmp &= ~(ADC_SC3_ADCO_MASK);
    tmp |= ADC_SC3_ADCO(state ? (uint32_t)1u : (uint32_t)0u);
    baseAddr->SC3 = (uint32_t)tmp;
}

static inline void ADC_SetSupplyMonitoringEnableFlag(SIM_Type * const baseAddr,
                                                  const bool state)
{
    if(state == true)
    {
        baseAddr->CHIPCTL |= SIM_CHIPCTL_ADC_SUPPLYEN_MASK;
    }
    else
    {
        baseAddr->CHIPCTL &= ~SIM_CHIPCTL_ADC_SUPPLYEN_MASK;
    }
}



static inline bool ADC_GetHwCompareEnableFlag(const ADC_Type * const baseAddr)
{
    uint32_t tmp = (uint32_t)baseAddr->SC2;
    tmp = (tmp & ADC_SC2_ACFE_MASK) >> ADC_SC2_ACFE_SHIFT;

    return (tmp != 0u) ? true : false;
}

static inline void ADC_SetHwCompareEnableFlag(ADC_Type * const baseAddr,
                                              const bool state)
{
    uint32_t tmp = (uint32_t)baseAddr->SC2;
    tmp &= (uint32_t)(~(ADC_SC2_ACFE_MASK));
    tmp |= ADC_SC2_ACFE(state ? (uint32_t)1u : (uint32_t)0u);
    baseAddr->SC2 = (uint32_t)tmp;
}

static inline bool ADC_GetHwCompareGtEnableFlag(const ADC_Type * const baseAddr)
{
    uint32_t tmp = (uint32_t)baseAddr->SC2;
    tmp = (tmp & ADC_SC2_ACFGT_MASK) >> ADC_SC2_ACFGT_SHIFT;

    return (tmp != 0u) ? true : false;
}

static inline void ADC_SetHwCompareGtEnableFlag(ADC_Type * const baseAddr,
                                                const bool state)
{
    uint32_t tmp = (uint32_t)baseAddr->SC2;
    tmp &= (uint32_t)(~(ADC_SC2_ACFGT_MASK));
    tmp |= ADC_SC2_ACFGT(state ? (uint32_t)1u : (uint32_t)0u);
    baseAddr->SC2 = (uint32_t)tmp;
}

static inline bool ADC_GetHwCompareRangeEnableFlag(const ADC_Type * const baseAddr)
{
    uint32_t tmp = (uint32_t)baseAddr->SC2;
    tmp = (tmp & ADC_SC2_ACREN_MASK) >> ADC_SC2_ACREN_SHIFT;

    return (tmp != 0u) ? true : false;
}

static inline void ADC_SetHwCompareRangeEnableFlag(ADC_Type * const baseAddr,
                                                   const bool state)
{
    uint32_t tmp = (uint32_t)baseAddr->SC2;
    tmp &= (uint32_t)(~(ADC_SC2_ACREN_MASK));
    tmp |= ADC_SC2_ACREN(state ? (uint32_t)1u : (uint32_t)0u);
    baseAddr->SC2 = (uint32_t)tmp;
}

static inline uint16_t ADC_GetHwCompareComp1Value(const ADC_Type * const baseAddr)
{
    return (uint16_t)baseAddr->CV[0U];
}

static inline void ADC_SetHwCompareComp1Value(ADC_Type * const baseAddr,
                                              const uint16_t value)
{
    baseAddr->CV[0U] = ADC_CV_CV(value);
}

static inline uint16_t ADC_GetHwCompareComp2Value(const ADC_Type * const baseAddr)
{
    return (uint16_t)baseAddr->CV[1U];
}

static inline void ADC_SetHwCompareComp2Value(ADC_Type * const baseAddr,
                                              const uint16_t value)
{
    baseAddr->CV[1U] = ADC_CV_CV(value);
}



static inline bool ADC_GetHwAverageEnableFlag(const ADC_Type * const baseAddr)
{
    uint32_t tmp = (uint32_t)baseAddr->SC3;
    tmp = (tmp & ADC_SC3_AVGE_MASK) >> ADC_SC3_AVGE_SHIFT;

    return (tmp != 0u) ? true : false;
}

static inline void ADC_SetHwAverageEnableFlag(ADC_Type * const baseAddr,
                                              const bool state)
{
    uint32_t tmp = baseAddr->SC3;
    tmp &= ~(ADC_SC3_AVGE_MASK);
    tmp |= ADC_SC3_AVGE(state ? (uint32_t)1u : (uint32_t)0u);
    baseAddr->SC3 = tmp;
}

static inline adc_average_t ADC_GetHwAverageMode(const ADC_Type * const baseAddr)
{
    uint32_t tmp = baseAddr->SC3;
    tmp = (tmp & ADC_SC3_AVGS_MASK) >> ADC_SC3_AVGS_SHIFT;

    return (adc_average_t)(tmp);
}

static inline void ADC_SetHwAverageMode(ADC_Type * const baseAddr,
                                        const adc_average_t averageMode)
{
    uint32_t tmp = baseAddr->SC3;
    tmp &= ~(ADC_SC3_AVGS_MASK);
    tmp |= ADC_SC3_AVGS(averageMode);
    baseAddr->SC3 = tmp;
}



static inline bool ADC_GetCalibrationActiveFlag(const ADC_Type * const baseAddr)
{
    uint32_t tmp = (uint32_t)baseAddr->SC3;
    tmp = (tmp & ADC_SC3_CAL_MASK) >> ADC_SC3_CAL_SHIFT;

    return (tmp != 0u) ? true : false;
}

static inline void ADC_SetCalibrationActiveFlag(ADC_Type * const baseAddr,
                                                const bool state)
{
    uint32_t tmp = baseAddr->SC3;
    tmp &= ~(ADC_SC3_CAL_MASK);
    tmp |= ADC_SC3_CAL(state ? (uint32_t)1u : (uint32_t)0u);
    baseAddr->SC3 = tmp;
}

static inline uint16_t ADC_GetUserGainValue(const ADC_Type * const baseAddr)
{
    uint32_t tmp = baseAddr->UG;
    tmp = (tmp & ADC_UG_UG_MASK) >> ADC_UG_UG_SHIFT;

    return (uint16_t)tmp;
}

static inline void ADC_SetUserGainValue(ADC_Type * const baseAddr,
                                        const uint16_t value)
{
    uint16_t clp0 = (uint16_t)baseAddr->CLP0;
    uint16_t clp1 = (uint16_t)baseAddr->CLP1;
    uint16_t clp2 = (uint16_t)baseAddr->CLP2;
    uint16_t clp3 = (uint16_t)baseAddr->CLP3;
    uint16_t clps = (uint16_t)baseAddr->CLPS;
    uint16_t sum = (uint16_t)(value + clp0 + clp1 + clp2 + clp3 + clps);
    uint16_t temp = (uint16_t)(sum & 0xF800U);
    if (temp != 0x0000U)
    {
        temp = 0xFFFFU;
    }

    baseAddr->UG = (uint32_t)value;
    baseAddr->G = (uint32_t)temp;
}

static inline uint16_t ADC_GetUserOffsetValue(const ADC_Type * const baseAddr)
{
    uint32_t tmp = baseAddr->USR_OFS;
    tmp = (tmp & ADC_USR_OFS_USR_OFS_MASK) >> ADC_USR_OFS_USR_OFS_SHIFT;

    return (uint16_t)tmp;
}

static inline void ADC_SetUserOffsetValue(ADC_Type * const baseAddr,
                                          const uint16_t value)
{
    baseAddr->USR_OFS = ADC_USR_OFS_USR_OFS(value);
}



static inline bool ADC_GetChanInterruptEnableFlag(const ADC_Type * const baseAddr,
                                                  const uint8_t chanIndex)
{

#if FEATURE_ADC_HAS_EXTRA_NUM_REGS

    uint32_t tmp = (uint32_t)baseAddr->aSC1[chanIndex];
    tmp = (tmp & ADC_aSC1_AIEN_MASK) >> ADC_aSC1_AIEN_SHIFT;
#else

    uint32_t tmp = (uint32_t)baseAddr->SC1[chanIndex];
    tmp = (tmp & ADC_SC1_AIEN_MASK) >> ADC_SC1_AIEN_SHIFT;
#endif 

    return (tmp != 0u) ? true : false;
}

static inline adc_inputchannel_t ADC_GetInputChannel(const ADC_Type * const baseAddr,
                                                     const uint8_t chanIndex)
{
#if FEATURE_ADC_HAS_EXTRA_NUM_REGS
    uint32_t tmp = baseAddr->aSC1[chanIndex];
    tmp = (tmp & ADC_aSC1_ADCH_MASK) >> ADC_aSC1_ADCH_SHIFT;
#else
    uint32_t tmp = baseAddr->SC1[chanIndex];
    tmp = (tmp & ADC_SC1_ADCH_MASK) >> ADC_SC1_ADCH_SHIFT;
#endif 

    uint32_t supplyen = (uint32_t)SIM->CHIPCTL;
    supplyen = (supplyen & SIM_CHIPCTL_ADC_SUPPLYEN_MASK) >> SIM_CHIPCTL_ADC_SUPPLYEN_SHIFT;
    if((tmp == (uint32_t)ADC_INPUTCHAN_INT0) && (supplyen != 0UL))
    {
        tmp = (uint32_t)SIM->CHIPCTL;
        tmp = (tmp & SIM_CHIPCTL_ADC_SUPPLY_MASK) >> SIM_CHIPCTL_ADC_SUPPLY_SHIFT;
        tmp = tmp + (uint32_t)ADC_INPUTCHAN_SUPPLY_VDD;
    }
    return (adc_inputchannel_t)(tmp);
}

static inline void ADC_SetInputChannel(ADC_Type * const baseAddr,
                                       const uint8_t chanIndex,
                                       const adc_inputchannel_t inputChan,
                                       const bool state)
{
    adc_inputchannel_t inputChanDemapped;

    if((inputChan >= ADC_INPUTCHAN_SUPPLY_VDD) && (inputChan <= ADC_INPUTCHAN_SUPPLY_VDD_LV))
    {
        const uint32_t supplyMonitorIdx = (uint32_t)inputChan - (uint32_t)ADC_INPUTCHAN_SUPPLY_VDD; 

        SIM_Type * const simBase = SIM;
        DEV_ASSERT((simBase ->CHIPCTL & SIM_CHIPCTL_ADC_SUPPLYEN_MASK) != 0UL);
        simBase->CHIPCTL &= ~SIM_CHIPCTL_ADC_SUPPLY_MASK;
        simBase->CHIPCTL |= SIM_CHIPCTL_ADC_SUPPLY(supplyMonitorIdx);

        inputChanDemapped = ADC_INPUTCHAN_INT0; 
    }
    else
    {
        inputChanDemapped = inputChan;
    }

#if FEATURE_ADC_HAS_EXTRA_NUM_REGS
    uint32_t tmp = baseAddr->aSC1[chanIndex];
    tmp &= ~(ADC_aSC1_ADCH_MASK);
    tmp |= ADC_aSC1_ADCH(inputChanDemapped);
    tmp &= ~(ADC_aSC1_AIEN_MASK);
    tmp |= ADC_aSC1_AIEN(state ? (uint32_t)1u : (uint32_t)0u);
    baseAddr->aSC1[chanIndex] = tmp;
#else
    uint32_t tmp = baseAddr->SC1[chanIndex];
    tmp &= ~(ADC_SC1_ADCH_MASK);
    tmp |= ADC_SC1_ADCH(inputChanDemapped);
    tmp &= ~(ADC_SC1_AIEN_MASK);
    tmp |= ADC_SC1_AIEN(state ? (uint32_t)1u : (uint32_t)0u);
    baseAddr->SC1[chanIndex] = tmp;
#endif 

}



static inline void ADC_ClearLatchTriggers(ADC_Type * const baseAddr)
{
    baseAddr->CFG1 |= ADC_CFG1_CLRLTRG(0x01u);
}

static inline uint32_t ADC_GetTriggerLatchFlags(const ADC_Type * const baseAddr)
{
    uint32_t tmp = baseAddr->SC2;
    tmp = (tmp & ADC_SC2_TRGSTLAT_MASK) >> ADC_SC2_TRGSTLAT_SHIFT;

    return tmp;
}


#if defined (__cplusplus)
}
#endif


#endif 

