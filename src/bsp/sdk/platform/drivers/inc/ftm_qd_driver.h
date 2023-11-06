
#ifndef FTM_QD_DRIVER_H
#define FTM_QD_DRIVER_H

#include "ftm_common.h"


typedef enum
{
    FTM_QUAD_PHASE_ENCODE   = 0x00U,    
    FTM_QUAD_COUNT_AND_DIR  = 0x01U     
} ftm_quad_decode_mode_t;

typedef enum
{
    FTM_QUAD_PHASE_NORMAL = 0x00U,  
    FTM_QUAD_PHASE_INVERT = 0x01U   
} ftm_quad_phase_polarity_t;

typedef struct
{
    bool phaseInputFilter;                          
    uint8_t phaseFilterVal;                         
    ftm_quad_phase_polarity_t phasePolarity;        
} ftm_phase_params_t;

typedef struct
{
    ftm_quad_decode_mode_t mode;        
    uint16_t initialVal;                
    uint16_t maxVal;                    
    ftm_phase_params_t phaseAConfig;    
    ftm_phase_params_t phaseBConfig;    
} ftm_quad_decode_config_t;

typedef struct
{
    uint16_t counter;           
    bool overflowFlag;          
    bool overflowDirection;     
    bool counterDirection;      
} ftm_quad_decoder_state_t;


#if defined(__cplusplus)
extern "C" {
#endif

status_t FTM_DRV_QuadDecodeStart(uint32_t instance,
                                 const ftm_quad_decode_config_t * config);

status_t FTM_DRV_QuadDecodeStop(uint32_t instance);

ftm_quad_decoder_state_t FTM_DRV_QuadGetState(uint32_t instance);

void FTM_QD_DRV_GetDefaultConfig(ftm_quad_decode_config_t * const config);

#if defined(__cplusplus)
}
#endif



#endif 

