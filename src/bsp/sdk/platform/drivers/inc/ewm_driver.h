

#ifndef EWM_DRIVER_H
#define EWM_DRIVER_H

#include "device_registers.h"
#include "status.h"



typedef enum
{
    EWM_IN_ASSERT_DISABLED      = 0x00U,    
    EWM_IN_ASSERT_ON_LOGIC_ZERO = 0x01U,    
    EWM_IN_ASSERT_ON_LOGIC_ONE  = 0x02U     
} ewm_in_assert_logic_t;

typedef struct
{
    ewm_in_assert_logic_t assertLogic; 
    bool       interruptEnable;        
    uint8_t    prescaler;              
    uint8_t    compareLow;             
    uint8_t    compareHigh;            
} ewm_init_config_t;


#if defined(__cplusplus)
extern "C" {
#endif

status_t EWM_DRV_Init(uint32_t instance, const ewm_init_config_t * config);

void EWM_DRV_GetDefaultConfig(ewm_init_config_t * config);

void EWM_DRV_Refresh(uint32_t instance);

ewm_in_assert_logic_t EWM_DRV_GetInputPinAssertLogic(uint32_t instance);

#if defined(__cplusplus)
}
#endif


#endif 

