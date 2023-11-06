
#ifndef POWER_SMC_HW_ACCESS_H
#define POWER_SMC_HW_ACCESS_H

#include "status.h"
#include "device_registers.h"
#include "power_manager_S32K1xx.h"




#if defined(__cplusplus)
extern "C" {
#endif 


status_t SMC_SetPowerMode(SMC_Type * const baseAddr,
                          const smc_power_mode_config_t * const powerModeConfig);

void SMC_SetProtectionMode(SMC_Type * const baseAddr,
                           const smc_power_mode_protection_config_t * const protectConfig);

static inline void SMC_SetRunModeControl(SMC_Type * const baseAddr,
                                         const smc_run_mode_t runMode)
{
    uint32_t regValue = baseAddr->PMCTRL;
    regValue &= ~(SMC_PMCTRL_RUNM_MASK);
    regValue |= SMC_PMCTRL_RUNM(runMode);
    baseAddr->PMCTRL = regValue;
}

static inline void SMC_SetStopModeControl(SMC_Type * const baseAddr,
                                          const smc_stop_mode_t stopMode)
{
    uint32_t regValue = baseAddr->PMCTRL;
    regValue &= ~(SMC_PMCTRL_STOPM_MASK);
    regValue |= SMC_PMCTRL_STOPM(stopMode);
    baseAddr->PMCTRL = regValue;
}

#if FEATURE_SMC_HAS_STOPO
static inline void SMC_SetStopOption(SMC_Type * const baseAddr,
                                     const smc_stop_option_t option)
{
    uint32_t regValue = baseAddr->STOPCTRL;
    regValue &= ~(SMC_STOPCTRL_STOPO_MASK);
    regValue |= SMC_STOPCTRL_STOPO(option);
    baseAddr->STOPCTRL = regValue;
}

#endif 

#if FEATURE_SMC_HAS_PSTOPO

#error "Unimplemented"

#endif

static inline power_mode_stat_t SMC_GetPowerModeStatus(const SMC_Type * const baseAddr)
{
    power_mode_stat_t retValue;
    uint32_t regValue = baseAddr->PMSTAT;
    regValue = (regValue & SMC_PMSTAT_PMSTAT_MASK) >> SMC_PMSTAT_PMSTAT_SHIFT;

    switch (regValue)
    {
        case 1UL:
            retValue = STAT_RUN;
            break;
        case 2UL:
            retValue = STAT_STOP;
            break;
        case 4UL:
            retValue = STAT_VLPR;
            break;
#if FEATURE_SMC_HAS_WAIT_VLPW
        case 8UL:
            retValue = STAT_VLPW;
            break;
#endif
        case 16UL:
            retValue = STAT_VLPS;
            break;
#if FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE
        case 128UL:
            retValue = STAT_HSRUN;
            break;
#endif
        case 255UL:
        default:
            retValue = STAT_INVALID;
            break;
    }

    return retValue;
}


#if defined(__cplusplus)
}
#endif 


#endif 

