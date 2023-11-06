
#ifndef PDB_DRIVER_H
#define PDB_DRIVER_H

#include <stdint.h>
#include <stdbool.h>
#include "clock_manager.h"



typedef enum
{
    PDB_LOAD_VAL_IMMEDIATELY                        = 0U,
    PDB_LOAD_VAL_AT_MODULO_COUNTER                  = 1U,
    PDB_LOAD_VAL_AT_NEXT_TRIGGER                    = 2U,
    PDB_LOAD_VAL_AT_MODULO_COUNTER_OR_NEXT_TRIGGER  = 3U
} pdb_load_value_mode_t;

typedef enum
{
    PDB_CLK_PREDIV_BY_1   = 0U, 
    PDB_CLK_PREDIV_BY_2   = 1U, 
    PDB_CLK_PREDIV_BY_4   = 2U, 
    PDB_CLK_PREDIV_BY_8   = 3U, 
    PDB_CLK_PREDIV_BY_16  = 4U, 
    PDB_CLK_PREDIV_BY_32  = 5U, 
    PDB_CLK_PREDIV_BY_64  = 6U, 
    PDB_CLK_PREDIV_BY_128 = 7U  
} pdb_clk_prescaler_div_t;

typedef enum
{
    PDB_TRIGGER_IN0         = 0U,    
    PDB_SOFTWARE_TRIGGER    = 15U    
} pdb_trigger_src_t;

typedef enum
{
    PDB_CLK_PREMULT_FACT_AS_1  = 0U, 
    PDB_CLK_PREMULT_FACT_AS_10 = 1U, 
    PDB_CLK_PREMULT_FACT_AS_20 = 2U, 
    PDB_CLK_PREMULT_FACT_AS_40 = 3U  
} pdb_clk_prescaler_mult_factor_t;

typedef struct
{
    pdb_load_value_mode_t           loadValueMode;            
    bool                            seqErrIntEnable;          
    pdb_clk_prescaler_div_t         clkPreDiv;                
    pdb_clk_prescaler_mult_factor_t clkPreMultFactor;         
    pdb_trigger_src_t               triggerInput;             
    bool                            continuousModeEnable;     
    bool                            dmaEnable;                
    bool                            intEnable;                
    bool                            instanceBackToBackEnable; 
} pdb_timer_config_t;

typedef struct
{
    uint32_t adcPreTriggerIdx;       
    bool preTriggerEnable;           
    bool preTriggerOutputEnable;     
    bool preTriggerBackToBackEnable; 
} pdb_adc_pretrigger_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

void PDB_DRV_Init(const uint32_t instance,
                  const pdb_timer_config_t * userConfigPtr);

void PDB_DRV_Deinit(const uint32_t instance);

void PDB_DRV_GetDefaultConfig(pdb_timer_config_t * const config);

void PDB_DRV_Enable(const uint32_t instance);

void PDB_DRV_Disable(const uint32_t instance);

void PDB_DRV_SoftTriggerCmd(const uint32_t instance);

uint32_t PDB_DRV_GetTimerValue(const uint32_t instance);

bool PDB_DRV_GetTimerIntFlag(const uint32_t instance);

void PDB_DRV_ClearTimerIntFlag(const uint32_t instance);

void PDB_DRV_LoadValuesCmd(const uint32_t instance);

void PDB_DRV_SetTimerModulusValue(const uint32_t instance,
                                  const uint16_t value);

void PDB_DRV_SetValueForTimerInterrupt(const uint32_t instance,
                                       const uint16_t value);

void PDB_DRV_ConfigAdcPreTrigger(const uint32_t instance,
                                 const uint32_t chn,
                                 const pdb_adc_pretrigger_config_t * configPtr);

uint32_t PDB_DRV_GetAdcPreTriggerFlags(const uint32_t instance,
                                       const uint32_t chn,
                                       const uint32_t preChnMask);

void PDB_DRV_ClearAdcPreTriggerFlags(const uint32_t instance,
                                     const uint32_t chn,
                                     const uint32_t preChnMask);

uint32_t PDB_DRV_GetAdcPreTriggerSeqErrFlags(const uint32_t instance,
                                             const uint32_t chn,
                                             const uint32_t preChnMask);

void PDB_DRV_ClearAdcPreTriggerSeqErrFlags(const uint32_t instance,
                                           const uint32_t chn,
                                           const uint32_t preChnMask);

void PDB_DRV_SetAdcPreTriggerDelayValue(const uint32_t instance,
                                        const uint32_t chn,
                                        const uint32_t preChn,
                                        const uint32_t value);

void PDB_DRV_SetCmpPulseOutEnable(const uint32_t instance,
                                  const uint32_t pulseChnMask,
                                  bool enable);

void PDB_DRV_SetCmpPulseOutDelayForHigh(const uint32_t instance,
                                        const uint32_t pulseChn,
                                        const uint32_t value);

void PDB_DRV_SetCmpPulseOutDelayForLow(const uint32_t instance,
                                       const uint32_t pulseChn,
                                       const uint32_t value);

#if defined(__cplusplus)
}
#endif


#endif 

