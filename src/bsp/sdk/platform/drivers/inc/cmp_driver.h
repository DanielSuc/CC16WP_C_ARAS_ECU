
#ifndef CMP_DRIVER_H
#define CMP_DRIVER_H

#include "status.h"
#include "device_registers.h"

#define CMP_INPUT_FLAGS_MASK 0xFF0000
#define CMP_INPUT_FLAGS_SHIFT 16U
#define CMP_ROUND_ROBIN_CHANNELS_MASK 0xFF0000
#define CMP_ROUND_ROBIN_CHANNELS_SHIFT 16U

typedef enum
{
    CMP_LOW_SPEED   = 0U,   
    CMP_HIGH_SPEED  = 1U    
} cmp_power_mode_t;

typedef enum
{
    CMP_VIN1 = 0U,  
    CMP_VIN2 = 1U   
} cmp_voltage_reference_t;

typedef enum
{
    CMP_DAC = CMP_DAC_SOURCE,   
    CMP_MUX = CMP_MUX_SOURCE    
} cmp_port_mux_t;

typedef enum
{
    CMP_NORMAL = 0U,    
    CMP_INVERT = 1U     
} cmp_inverter_t;

typedef enum
{
    CMP_COUT  = 0U,     
    CMP_COUTA = 1U      
} cmp_output_select_t;

typedef enum
{
    CMP_UNAVAILABLE  = 0U,  
    CMP_AVAILABLE    = 1U   
} cmp_output_enable_t;

#if FEATURE_CMP_HAS_HARD_BLOCK_OFFSET
typedef enum
{
    CMP_LEVEL_OFFSET_0 = 0U,
    CMP_LEVEL_OFFSET_1 = 1U
} cmp_offset_t;
#endif

typedef enum
{
    CMP_LEVEL_HYS_0 = 0U,
    CMP_LEVEL_HYS_1 = 1U,
    CMP_LEVEL_HYS_2 = 2U,
    CMP_LEVEL_HYS_3 = 3U
} cmp_hysteresis_t;

typedef enum
{
    CMP_PLUS_FIXED      = 0U,   
    CMP_MINUS_FIXED     = 1U    
} cmp_fixed_port_t;

typedef enum
{
    CMP_NO_EVENT            = 0U,   
    CMP_FALLING_EDGE        = 1U,   
    CMP_RISING_EDGE         = 2U,   
    CMP_BOTH_EDGES          = 3U    
} cmp_output_trigger_t;

typedef enum
{
    CMP_DISABLED                        = 0U,
    CMP_CONTINUOUS                      = 1U,
    CMP_SAMPLED_NONFILTRED_INT_CLK      = 2U,
    CMP_SAMPLED_NONFILTRED_EXT_CLK      = 3U,
    CMP_SAMPLED_FILTRED_INT_CLK         = 4U,
    CMP_SAMPLED_FILTRED_EXT_CLK         = 5U,
    CMP_WINDOWED                        = 6U,
    CMP_WINDOWED_RESAMPLED              = 7U,
    CMP_WINDOWED_FILTRED                = 8U
} cmp_mode_t;

typedef  uint8_t cmp_ch_list_t;

typedef  uint8_t cmp_ch_number_t;

typedef struct
{
    bool                    dmaTriggerState;        
    cmp_output_trigger_t    outputInterruptTrigger; 
    cmp_mode_t              mode;                    
    uint8_t                 filterSamplePeriod;     
    uint8_t                 filterSampleCount;      
    cmp_power_mode_t        powerMode;              
    cmp_inverter_t          inverterState;          
    cmp_output_enable_t     pinState;               
    cmp_output_select_t     outputSelect;                
#if FEATURE_CMP_HAS_HARD_BLOCK_OFFSET
    cmp_offset_t            offsetLevel;            
#endif
    cmp_hysteresis_t        hysteresisLevel;        
}cmp_comparator_t;

typedef struct
{
    cmp_port_mux_t      positivePortMux;    
    cmp_port_mux_t      negativePortMux;    

    cmp_ch_number_t     positiveInputMux;   
    cmp_ch_number_t     negativeInputMux;   
}cmp_anmux_t;

typedef struct
{
    cmp_voltage_reference_t     voltageReferenceSource;       
    uint8_t                     voltage;                    
    bool                        state;                      

#if FEATURE_CMP_DAC_FIX_SELECTION
    bool						fixRefInputMux;				
#endif
}cmp_dac_t;

typedef struct
{
    bool                roundRobinState;            
    bool                roundRobinInterruptState;   
    cmp_fixed_port_t    fixedPort;                  
    cmp_ch_number_t     fixedChannel;               
    uint8_t             samples;                    
#if FEATURE_CMP_HAS_INIT_DELAY
    uint8_t             initializationDelay;        
#endif
    cmp_ch_list_t       roundRobinChannelsState;    
    cmp_ch_list_t       programedState;             
}cmp_trigger_mode_t;

typedef struct
{
    cmp_comparator_t        comparator;
    cmp_anmux_t             mux;
    cmp_dac_t               dac;
    cmp_trigger_mode_t      triggerMode;
}cmp_module_t;



#if defined(__cplusplus)
extern "C" {
#endif

status_t CMP_DRV_Reset(const uint32_t instance);

status_t CMP_DRV_GetInitConfigAll(cmp_module_t* config);

status_t CMP_DRV_GetDefaultConfig(cmp_module_t* const config);

status_t CMP_DRV_Init(const uint32_t instance, const cmp_module_t* const config);

status_t CMP_DRV_GetConfigAll(const uint32_t instance, cmp_module_t* const config);

status_t CMP_DRV_GetInitConfigDAC(cmp_dac_t* config);

status_t CMP_DRV_ConfigDAC(const uint32_t instance, const cmp_dac_t* config);

status_t CMP_DRV_GetDACConfig(const uint32_t instance, cmp_dac_t* const config);

status_t CMP_DRV_GetInitConfigMUX(cmp_anmux_t* config);

status_t CMP_DRV_ConfigMUX(const uint32_t instance, const cmp_anmux_t* config);

status_t CMP_DRV_GetMUXConfig(const uint32_t instance, cmp_anmux_t* const config);

status_t CMP_DRV_GetInitTriggerMode(cmp_trigger_mode_t* config);

status_t CMP_DRV_ConfigTriggerMode(const uint32_t instance, const cmp_trigger_mode_t* config);

status_t CMP_DRV_GetTriggerModeConfig(const uint32_t instance, cmp_trigger_mode_t* const config);

status_t CMP_DRV_GetOutputFlags(const uint32_t instance, cmp_output_trigger_t *flags);

status_t CMP_DRV_ClearOutputFlags(const uint32_t instance);

status_t CMP_DRV_GetInputFlags(const uint32_t instance, cmp_ch_list_t *flags);

status_t CMP_DRV_ClearInputFlags(const uint32_t instance);

status_t CMP_DRV_GetInitConfigComparator(cmp_comparator_t* config);

status_t CMP_DRV_ConfigComparator(const uint32_t instance, const cmp_comparator_t *config);

status_t CMP_DRV_GetComparatorConfig(const uint32_t instance, cmp_comparator_t *config);


#if defined(__cplusplus)
}
#endif


#endif 


