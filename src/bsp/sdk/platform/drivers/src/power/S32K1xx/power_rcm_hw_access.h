
#ifndef POWER_RCM_HW_ACCESS_H
#define POWER_RCM_HW_ACCESS_H

#include "device_registers.h"
#include "power_manager_S32K1xx.h"




#if defined(__cplusplus)
extern "C" {
#endif 


static inline bool RCM_GetSrcStatusCmd(const RCM_Type * const baseAddr,
                         const rcm_source_names_t srcName)
{
    bool retValue;
    uint32_t regValue = (uint32_t)baseAddr->SRS;

    DEV_ASSERT(srcName < RCM_SRC_NAME_MAX);

    switch (srcName)
    {
        case RCM_LOW_VOLT_DETECT:              
            regValue = (regValue & RCM_SRS_LVD_MASK) >> RCM_SRS_LVD_SHIFT;
            break;
        case RCM_LOSS_OF_CLK:                  
            regValue = (regValue & RCM_SRS_LOC_MASK) >> RCM_SRS_LOC_SHIFT;
            break;
        case RCM_LOSS_OF_LOCK:                 
            regValue = (regValue & RCM_SRS_LOL_MASK) >> RCM_SRS_LOL_SHIFT;
            break;
#if FEATURE_RCM_HAS_CMU_LOSS_OF_CLOCK          
        case RCM_CMU_LOC:
            regValue = (regValue & RCM_SRS_CMU_LOC_MASK) >> RCM_SRS_CMU_LOC_SHIFT;
            break;     
#endif
        case RCM_WATCH_DOG:                    
            regValue = (regValue & RCM_SRS_WDOG_MASK) >> RCM_SRS_WDOG_SHIFT;
            break;
        case RCM_EXTERNAL_PIN:                 
            regValue = (regValue & RCM_SRS_PIN_MASK) >> RCM_SRS_PIN_SHIFT;
            break;
        case RCM_POWER_ON:                     
            regValue = (regValue & RCM_SRS_POR_MASK) >> RCM_SRS_POR_SHIFT;
            break;
        case RCM_SJTAG:                        
            regValue = (regValue & RCM_SSRS_SJTAG_MASK) >> RCM_SSRS_SJTAG_SHIFT;
            break;
        case RCM_CORE_LOCKUP:                  
            regValue = (regValue & RCM_SRS_LOCKUP_MASK) >> RCM_SRS_LOCKUP_SHIFT;
            break;
        case RCM_SOFTWARE:                     
            regValue = (regValue & RCM_SRS_SW_MASK) >> RCM_SRS_SW_SHIFT;
            break;
        case RCM_SMDM_AP:                      
            regValue = (regValue & RCM_SSRS_SMDM_AP_MASK) >> RCM_SSRS_SMDM_AP_SHIFT;
            break;
        case RCM_STOP_MODE_ACK_ERR:            
            regValue = (regValue & RCM_SRS_SACKERR_MASK) >> RCM_SRS_SACKERR_SHIFT;
            break;
        default:
            regValue = 0U;
            break;
    }

    retValue = (regValue == 0UL) ? false : true;

    return retValue;
}


#if defined(__cplusplus)
}
#endif 


#endif 

