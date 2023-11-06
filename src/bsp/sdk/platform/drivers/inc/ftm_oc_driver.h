
#ifndef FTM_OC_DRIVER_H
#define FTM_OC_DRIVER_H

#include "ftm_common.h"



typedef enum
{
    FTM_DISABLE_OUTPUT  = 0x00U,    
    FTM_TOGGLE_ON_MATCH = 0x01U,    
    FTM_CLEAR_ON_MATCH  = 0x02U,    
    FTM_SET_ON_MATCH    = 0x03U     
} ftm_output_compare_mode_t;

typedef enum
{
    FTM_RELATIVE_VALUE = 0x00U,     
    FTM_ABSOLUTE_VALUE = 0x01U      
} ftm_output_compare_update_t;

typedef struct
{
    uint8_t hwChannelId;                        
    ftm_output_compare_mode_t chMode;           
    uint16_t comparedValue;                     
    bool enableExternalTrigger;                 
} ftm_output_cmp_ch_param_t;

typedef struct
{
    uint8_t nNumOutputChannels;                             
    ftm_config_mode_t mode;                                 
    uint16_t maxCountValue;                                 
    ftm_output_cmp_ch_param_t * outputChannelConfig;        
} ftm_output_cmp_param_t;


#if defined(__cplusplus)
extern "C" {
#endif

status_t FTM_DRV_InitOutputCompare(uint32_t instance,
                                   const ftm_output_cmp_param_t * param);

status_t FTM_DRV_DeinitOutputCompare(uint32_t instance,
                                     const ftm_output_cmp_param_t * param);

status_t FTM_DRV_UpdateOutputCompareChannel(uint32_t instance,
                                            uint8_t channel,
                                            uint16_t nextComparematchValue,
                                            ftm_output_compare_update_t update,
                                            bool softwareTrigger);

#if defined(__cplusplus)
}
#endif



#endif 

