
#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

#include <stdint.h>
#include <stdbool.h>
#include "device_registers.h"



typedef enum
{
    ADC_CLK_DIVIDE_1 = 0x00U,   
    ADC_CLK_DIVIDE_2 = 0x01U,   
    ADC_CLK_DIVIDE_4 = 0x02U,   
    ADC_CLK_DIVIDE_8 = 0x03U    
} adc_clk_divide_t;

typedef enum
{
    ADC_RESOLUTION_8BIT = 0x00U,    
    ADC_RESOLUTION_12BIT = 0x01U,   
    ADC_RESOLUTION_10BIT = 0x02U    
} adc_resolution_t;

typedef enum
{
    ADC_CLK_ALT_1 = 0x00U,  
    ADC_CLK_ALT_2 = 0x01U,  
    ADC_CLK_ALT_3 = 0x02U,  
    ADC_CLK_ALT_4 = 0x03U   
} adc_input_clock_t;

typedef enum
{
    ADC_TRIGGER_SOFTWARE       = 0x00U,   
    ADC_TRIGGER_HARDWARE       = 0x01U    
} adc_trigger_t;

typedef enum
{
    ADC_PRETRIGGER_SEL_PDB     = 0x00U,   
    ADC_PRETRIGGER_SEL_TRGMUX  = 0x01U,   
    ADC_PRETRIGGER_SEL_SW      = 0x02U    
} adc_pretrigger_sel_t;

typedef enum
{
    ADC_TRIGGER_SEL_PDB        = 0x00U,   
    ADC_TRIGGER_SEL_TRGMUX     = 0x01U    
} adc_trigger_sel_t;

typedef enum
{
    ADC_SW_PRETRIGGER_DISABLED = 0x00U,   
    ADC_SW_PRETRIGGER_0        = 0x04U,   
    ADC_SW_PRETRIGGER_1        = 0x05U,   
    ADC_SW_PRETRIGGER_2        = 0x06U,   
    ADC_SW_PRETRIGGER_3        = 0x07U    
} adc_sw_pretrigger_t;

typedef enum
{
    ADC_VOLTAGEREF_VREF = 0x00U,    
    ADC_VOLTAGEREF_VALT = 0x01U     
} adc_voltage_reference_t;

typedef enum
{
    ADC_AVERAGE_4 = 0x00U,  
    ADC_AVERAGE_8 = 0x01U,  
    ADC_AVERAGE_16 = 0x02U, 
    ADC_AVERAGE_32 = 0x03U  
} adc_average_t;

typedef enum
{
    ADC_INPUTCHAN_EXT0      = 0x00U,              
    ADC_INPUTCHAN_EXT1      = 0x01U,              
#if (FEATURE_ADC_HAS_CHANNEL_2)
    ADC_INPUTCHAN_EXT2      = 0x02U,              
#endif
    ADC_INPUTCHAN_EXT3      = 0x03U,              
    ADC_INPUTCHAN_EXT4      = 0x04U,              
    ADC_INPUTCHAN_EXT5      = 0x05U,              
    ADC_INPUTCHAN_EXT6      = 0x06U,              
    ADC_INPUTCHAN_EXT7      = 0x07U,              
#if (FEATURE_ADC_HAS_CHANNEL_8)
    ADC_INPUTCHAN_EXT8      = 0x08U,              
#endif
    ADC_INPUTCHAN_EXT9      = 0x09U,              
    ADC_INPUTCHAN_EXT10     = 0x0AU,              
    ADC_INPUTCHAN_EXT11     = 0x0BU,              
    ADC_INPUTCHAN_EXT12     = 0x0CU,              
    ADC_INPUTCHAN_EXT13     = 0x0DU,              
    ADC_INPUTCHAN_EXT14     = 0x0EU,              
#if (FEATURE_ADC_MAX_NUM_EXT_CHANS > 15)
    ADC_INPUTCHAN_EXT15     = 0x0FU,              
#if (FEATURE_ADC_MAX_NUM_EXT_CHANS > 16)
    ADC_INPUTCHAN_EXT16     = 0x20U,              
    ADC_INPUTCHAN_EXT17     = 0x21U,              
    ADC_INPUTCHAN_EXT18     = 0x22U,              
    ADC_INPUTCHAN_EXT19     = 0x23U,              
    ADC_INPUTCHAN_EXT20     = 0x24U,              
    ADC_INPUTCHAN_EXT21     = 0x25U,              
    ADC_INPUTCHAN_EXT22     = 0x26U,              
    ADC_INPUTCHAN_EXT23     = 0x27U,              
#if (FEATURE_ADC_MAX_NUM_EXT_CHANS > 24)
    ADC_INPUTCHAN_EXT24     = 0x28U,              
    ADC_INPUTCHAN_EXT25     = 0x29U,              
    ADC_INPUTCHAN_EXT26     = 0x2AU,              
    ADC_INPUTCHAN_EXT27     = 0x2BU,              
    ADC_INPUTCHAN_EXT28     = 0x2CU,              
    ADC_INPUTCHAN_EXT29     = 0x2DU,              
    ADC_INPUTCHAN_EXT30     = 0x2EU,              
    ADC_INPUTCHAN_EXT31     = 0x2FU,              
#endif 
#endif 
#endif

    ADC_INPUTCHAN_DISABLED  = ADC_SC1_ADCH_MASK,  

    ADC_INPUTCHAN_INT0      = 0x15,               
    ADC_INPUTCHAN_INT1      = 0x16,               
    ADC_INPUTCHAN_INT2      = 0x17,               
    ADC_INPUTCHAN_INT3      = 0x1C,               

    ADC_INPUTCHAN_TEMP      = 0x1A,               
    ADC_INPUTCHAN_BANDGAP   = 0x1B,               
    ADC_INPUTCHAN_VREFSH    = 0x1D,               
    ADC_INPUTCHAN_VREFSL    = 0x1E,               

    ADC_INPUTCHAN_SUPPLY_VDD            = 0xF00U,   
    ADC_INPUTCHAN_SUPPLY_VDDA           = 0xF01U,   
    ADC_INPUTCHAN_SUPPLY_VREFH          = 0xF02U,   
    ADC_INPUTCHAN_SUPPLY_VDD_3V         = 0xF03U,   
    ADC_INPUTCHAN_SUPPLY_VDD_FLASH_3V   = 0xF04U,   
    ADC_INPUTCHAN_SUPPLY_VDD_LV         = 0xF05U    
} adc_inputchannel_t;

typedef struct
{
    adc_clk_divide_t clockDivide;        
    uint8_t sampleTime;                  
    adc_resolution_t resolution;         
    adc_input_clock_t inputClock;        
    adc_trigger_t trigger;               
    adc_pretrigger_sel_t pretriggerSel;  
    adc_trigger_sel_t triggerSel;        
    bool dmaEnable;                      
    adc_voltage_reference_t voltageRef;  
    bool continuousConvEnable;           
    bool supplyMonitoringEnable;         
} adc_converter_config_t;

typedef struct
{
    bool compareEnable;              
    bool compareGreaterThanEnable;   
    bool compareRangeFuncEnable;     
    uint16_t compVal1;               
    uint16_t compVal2;               
} adc_compare_config_t;

typedef struct
{
    bool hwAvgEnable;        
    adc_average_t hwAverage; 
} adc_average_config_t;

typedef struct
{
    bool interruptEnable;       
    adc_inputchannel_t channel; 
} adc_chan_config_t;

typedef struct
{
    uint16_t userGain;    
    uint16_t userOffset;  
} adc_calibration_t;

typedef enum
{
    ADC_LATCH_CLEAR_WAIT, 
    ADC_LATCH_CLEAR_FORCE 
} adc_latch_clear_t;


#if defined (__cplusplus)
extern "C" {
#endif


void ADC_DRV_InitConverterStruct(adc_converter_config_t * const config);

void ADC_DRV_ConfigConverter(const uint32_t instance,
                             const adc_converter_config_t * const config);

void ADC_DRV_GetConverterConfig(const uint32_t instance,
                                adc_converter_config_t * const config);



void ADC_DRV_InitHwCompareStruct(adc_compare_config_t * const config);

void ADC_DRV_ConfigHwCompare(const uint32_t instance,
                             const adc_compare_config_t * const config);

void ADC_DRV_GetHwCompareConfig(const uint32_t instance,
                                adc_compare_config_t * const config);


void ADC_DRV_InitHwAverageStruct(adc_average_config_t * const config);

void ADC_DRV_ConfigHwAverage(const uint32_t instance,
                             const adc_average_config_t * const config);

void ADC_DRV_GetHwAverageConfig(const uint32_t instance,
                                adc_average_config_t * const config);



void ADC_DRV_InitChanStruct(adc_chan_config_t * const config);

void ADC_DRV_ConfigChan(const uint32_t instance,
                        const uint8_t chanIndex,
                        const adc_chan_config_t * const config);

void ADC_DRV_GetChanConfig(const uint32_t instance,
                           const uint8_t chanIndex,
                           adc_chan_config_t * const config);

void ADC_DRV_SetSwPretrigger(const uint32_t instance,
                             const adc_sw_pretrigger_t swPretrigger);


void ADC_DRV_Reset(const uint32_t instance);

void ADC_DRV_WaitConvDone(const uint32_t instance);

bool ADC_DRV_GetConvCompleteFlag(const uint32_t instance,
                                 const uint8_t chanIndex);


void ADC_DRV_GetChanResult(const uint32_t instance,
                           const uint8_t chanIndex,
                           uint16_t * const result);



void ADC_DRV_AutoCalibration(const uint32_t instance);

void ADC_DRV_InitUserCalibrationStruct(adc_calibration_t * const config);

void ADC_DRV_ConfigUserCalibration(const uint32_t instance,
                                   const adc_calibration_t * const config);

void ADC_DRV_GetUserCalibration(const uint32_t instance,
                                adc_calibration_t * const config);



IRQn_Type ADC_DRV_GetInterruptNumber(const uint32_t instance);



void ADC_DRV_ClearLatchedTriggers(const uint32_t instance,
                                  const adc_latch_clear_t clearMode);

void ADC_DRV_ClearTriggerErrors(const uint32_t instance);

uint32_t ADC_DRV_GetTriggerErrorFlags(const uint32_t instance);


#if defined (__cplusplus)
}
#endif


#endif 

