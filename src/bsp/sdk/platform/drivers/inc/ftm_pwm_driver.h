
#ifndef FTM_PWM_DRIVER_H
#define FTM_PWM_DRIVER_H

#include "ftm_common.h"


#define FTM_MAX_DUTY_CYCLE      (0x8000U)
#define FTM_DUTY_TO_TICKS_SHIFT (15U)

typedef enum
{
    FTM_PWM_UPDATE_IN_DUTY_CYCLE = 0x00U,     
    FTM_PWM_UPDATE_IN_TICKS      = 0x01U      
} ftm_pwm_update_option_t;

typedef enum
{
    FTM_POLARITY_LOW  = 0x00U,  
    FTM_POLARITY_HIGH = 0x01U   
} ftm_polarity_t;

typedef enum
{
    FTM_MAIN_INVERTED   = 0x01U,  
    FTM_MAIN_DUPLICATED = 0x00U   
} ftm_second_channel_polarity_t;

typedef enum
{
    FTM_FAULT_CONTROL_DISABLED  = 0x00U,    
    FTM_FAULT_CONTROL_MAN_EVEN  = 0x01U,    
    FTM_FAULT_CONTROL_MAN_ALL   = 0x02U,    
    FTM_FAULT_CONTROL_AUTO_ALL  = 0x03U     
} ftm_fault_mode_t;

typedef enum
{
    FTM_LOW_STATE = 0x00U,    
    FTM_HIGH_STATE  = 0x01U   
} ftm_safe_state_polarity_t;

typedef struct
{
    bool faultChannelEnabled;                   
    bool faultFilterEnabled;                    
    ftm_polarity_t ftmFaultPinPolarity;         
} ftm_pwm_ch_fault_param_t;

typedef struct
{
    bool pwmOutputStateOnFault;             
    bool pwmFaultInterrupt;                 
    uint8_t faultFilterValue;               
    ftm_fault_mode_t faultMode;             
    ftm_pwm_ch_fault_param_t ftmFaultChannelParam[FTM_FEATURE_FAULT_CHANNELS]; 
} ftm_pwm_fault_param_t;

typedef struct
{
    uint8_t hwChannelId;                                 
    ftm_polarity_t polarity;                             
    uint16_t uDutyCyclePercent;                          
    bool enableExternalTrigger;                          
    ftm_safe_state_polarity_t safeState;                 
    bool enableSecondChannelOutput;                      
    ftm_second_channel_polarity_t secondChannelPolarity; 
    bool deadTime;                                       
} ftm_independent_ch_param_t;

typedef struct
{
    uint8_t hwChannelId;                                 
    uint16_t firstEdge;                                  
    uint16_t secondEdge;                                 
    bool deadTime;                                       
    bool enableModifiedCombine;                          
    ftm_polarity_t mainChannelPolarity;                  
    bool enableSecondChannelOutput;                      
    ftm_second_channel_polarity_t secondChannelPolarity; 
    bool enableExternalTrigger;                          
    bool enableExternalTriggerOnNextChn;                 
    ftm_safe_state_polarity_t mainChannelSafeState;      
    ftm_safe_state_polarity_t secondChannelSafeState;    
} ftm_combined_ch_param_t;

typedef struct
{
    uint8_t nNumIndependentPwmChannels;                                     
    uint8_t nNumCombinedPwmChannels;                                        
    ftm_config_mode_t mode;                                                 
    uint8_t deadTimeValue;                                                  
    ftm_deadtime_ps_t deadTimePrescaler;                                    
    uint32_t uFrequencyHZ;                                                  
    ftm_independent_ch_param_t * pwmIndependentChannelConfig;               
    ftm_combined_ch_param_t * pwmCombinedChannelConfig;                     
    ftm_pwm_fault_param_t * faultConfig;                                    
} ftm_pwm_param_t;


#if defined(__cplusplus)
extern "C" {
#endif

status_t FTM_DRV_DeinitPwm(uint32_t instance);

status_t FTM_DRV_InitPwm(uint32_t instance,
                         const ftm_pwm_param_t * param);

status_t FTM_DRV_UpdatePwmChannel(uint32_t instance,
                                  uint8_t channel,
                                  ftm_pwm_update_option_t typeOfUpdate,
                                  uint16_t firstEdge,
                                  uint16_t secondEdge,
                                  bool softwareTrigger);

status_t FTM_DRV_FastUpdatePwmChannels(uint32_t instance,
                                       uint8_t numberOfChannels,
                                       const uint8_t * channels,
                                       const uint16_t * duty,
                                       bool softwareTrigger);

status_t FTM_DRV_UpdatePwmPeriod(uint32_t instance,
                                 ftm_pwm_update_option_t typeOfUpdate,
                                 uint32_t newValue,
                                 bool softwareTrigger);

status_t FTM_DRV_ControlChannelOutput(uint32_t instance,
                                      uint8_t channel,
                                      bool enableChannelOutput);

#if FEATURE_FTM_HAS_SUPPORTED_DITHERING
status_t FTM_DRV_UpdatePwmPeriodDither(uint32_t instance,
                                       uint8_t newModFracVal,
                                       bool softwareTrigger);

status_t FTM_DRV_UpdatePwmEdgeChannelDither(uint32_t instance,
                                            uint8_t channel,
                                            uint8_t newMatchFracVal,
                                            bool softwareTrigger);
#endif

#ifdef ERRATA_E10856
void FTM_PWM_DRV_IrqHandler(uint32_t instance,
                            uint32_t chnOutCtrlVal);

#endif 

#if defined(__cplusplus)
}
#endif



#endif 

