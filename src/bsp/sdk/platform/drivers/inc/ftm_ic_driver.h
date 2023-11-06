
#ifndef FTM_IC_DRIVER_H
#define FTM_IC_DRIVER_H

#include "ftm_common.h"



typedef enum
{
    FTM_EDGE_DETECT         = 0U,    
    FTM_SIGNAL_MEASUREMENT  = 1U,    
    FTM_NO_OPERATION        = 2U     
} ftm_input_op_mode_t;

typedef enum
{
    FTM_NO_MEASUREMENT                  = 0x00U,    
    FTM_RISING_EDGE_PERIOD_MEASUREMENT  = 0x01U,    
    FTM_FALLING_EDGE_PERIOD_MEASUREMENT = 0x02U,    
    FTM_PERIOD_ON_MEASUREMENT           = 0x03U,    
    FTM_PERIOD_OFF_MEASUREMENT          = 0x04U     
} ftm_signal_measurement_mode_t;

typedef enum
{
    FTM_NO_PIN_CONTROL          = 0x00U,       
    FTM_RISING_EDGE             = 0x01U,       
    FTM_FALLING_EDGE            = 0x02U,       
    FTM_BOTH_EDGES              = 0x03U        
} ftm_edge_alignment_mode_t;

typedef enum
{
    FTM_DISABLE_OPERATION           = 0x00U, 
    FTM_TIMESTAMP_RISING_EDGE       = 0x01U, 
    FTM_TIMESTAMP_FALLING_EDGE      = 0x02U, 
    FTM_TIMESTAMP_BOTH_EDGES        = 0x03U, 
    FTM_MEASURE_RISING_EDGE_PERIOD  = 0x04U, 
    FTM_MEASURE_FALLING_EDGE_PERIOD = 0x05U, 
    FTM_MEASURE_PULSE_HIGH          = 0x06U, 
    FTM_MEASURE_PULSE_LOW           = 0x07U  
} ftm_ic_op_mode_t;

typedef struct
{
    uint8_t hwChannelId;                                
    ftm_input_op_mode_t inputMode;                      
    ftm_edge_alignment_mode_t edgeAlignement;           
    ftm_signal_measurement_mode_t measurementType;      
    uint16_t filterValue;                               
    bool filterEn;                                      
    bool continuousModeEn;                              
    void * channelsCallbacksParams;                     
    ic_callback_t channelsCallbacks;                    
} ftm_input_ch_param_t;

typedef struct
{
    uint8_t nNumChannels;                    
    uint16_t nMaxCountValue;                 
    ftm_input_ch_param_t * inputChConfig;    
} ftm_input_param_t;


#if defined(__cplusplus)
extern "C" {
#endif

status_t FTM_DRV_InitInputCapture(uint32_t instance,
                                  const ftm_input_param_t * param);

status_t FTM_DRV_DeinitInputCapture(uint32_t instance,
                                    const ftm_input_param_t * param);

uint16_t FTM_DRV_GetInputCaptureMeasurement(uint32_t instance,
                                            uint8_t channel);

status_t FTM_DRV_StartNewSignalMeasurement(uint32_t instance,
                                           uint8_t channel);
status_t FTM_IC_DRV_SetChannelMode(uint32_t instance,
                                   uint8_t channel,
                                   ftm_ic_op_mode_t inputMode,
                                   bool enableContinuousCapture);

#if defined(__cplusplus)
}
#endif



#endif 

