#ifndef SFL_SIGNAL_GENERATOR_H
#define SFL_SIGNAL_GENERATOR_H


#include "hal_data_types.h"
#include "sfl_signal_generator_cfg.h"

typedef enum
{
    SG_OK                                     = 0u,             
    SG_ERROR_BASE_MODE_INVALID                    ,             
    SG_ERROR_SETTING_UNDEFINED                    ,             
    SG_ERROR_CONFIG_TABLE                                       

}enum_SG_RETURN_VALUE;

typedef enum
{
    SG_OUTPUT_STATE_OFF                       = 0u,             
    SG_OUTPUT_STATE_ON                                          

}enum_OUTPUT_STATE;

typedef enum
{
    SG_OUTPUT_LOUDNESS_QUIET                  = 0u,             
    SG_OUTPUT_LOUDNESS_LOUD                                     

}enum_OUTPUT_LOUDNESS;

typedef enum
{
    SG_BASE_MODE_CONTINUOUS_OFF               = 0u,             
    SG_BASE_MODE_CONTINUOUS_ON                    ,             
    SG_BASE_MODE_TOGGLE                           ,             
    SG_BASE_MODE_DELAY_ON                         ,             
    SG_BASE_MODE_DELAY_OFF                        ,             
    SG_BASE_MODE_PITCH                            ,             
    SG_BASE_MODE_INVALID                                        

}enum_SG_BASE_MODE;

typedef enum
{
    SG_SIGNAL_PROCESSING_PROCESS_NOT_SET         = 0u,          
    SG_SIGNAL_PROCESSING_PROCESS_IDLE                ,          
    SG_SIGNAL_PROCESSING_PROCESS_IN_PROGRESS                    

}enum_SG_SIGNAL_PROCESSING;


typedef struct
{
    uint16_t                    internalCommand;                
    enum_OUTPUT_STATE           internalOutputState;            
    enum_OUTPUT_STATE           internalToggleState;            
    uint16_t                    internalOutputPitch;            
    enum_OUTPUT_LOUDNESS        internalLoudness;               
    uint16_t                    internalPitch1;                 
    uint16_t                    internalTimePulse;              
    uint16_t                    internalTimeBreak;              
    uint16_t                    internalOnTime;                 
    uint16_t                    internalOnCount;                
    uint16_t                    internalOnPitch;                
    uint32_t                    internalPulseTimer;             
    uint32_t                    internalBreakTimer;             
    uint32_t                    internalOnCommandTimer;         
    uint16_t                    internalSetCommandOnCountValue; 
    enum_SG_SIGNAL_PROCESSING   internalSignalProcessingState;  
    uint16_t                    internalBrightness;             
}struct_SG_HANDLER;


typedef struct
{
    uint16_t Command;                                           
    enum_SG_BASE_MODE BaseMode;                                 
    uint16_t TimePulse;                                         
    uint16_t TimeBreak;                                         
    uint16_t OnTime;                                            
    uint16_t OnCount;                                           
    uint16_t Pitch1;                                            
    uint16_t OnPitch;                                           
    enum_OUTPUT_LOUDNESS Loudness;                              
    uint16_t Brightness;                                        

}struct_SG_CONFIG_TABLE;


enum_SG_RETURN_VALUE sfl_sg_init( struct_SG_HANDLER* ptrSgHandler );

enum_SG_RETURN_VALUE sfl_sg_process_command( uint16_t command,
    struct_SG_HANDLER* ptrSgHandler );

enum_SG_RETURN_VALUE sfl_sg_process_cyclic( struct_SG_HANDLER* ptrSgHandler );

enum_OUTPUT_STATE sfl_sg_get_output_state( struct_SG_HANDLER* ptrSgHandler );

uint32_t sfl_sg_get_pitch( struct_SG_HANDLER* ptrSgHandler );

uint32_t sfl_sg_get_loudness( struct_SG_HANDLER* ptrSgHandler );

uint16_t sfl_sg_get_brightness( struct_SG_HANDLER* ptrSgHandler );

enum_SG_SIGNAL_PROCESSING sfl_sg_get_signal_processing_state( struct_SG_HANDLER* ptrSgHandler );

struct_SG_CONFIG_TABLE* sfl_sg_get_config_table( void );

#endif

