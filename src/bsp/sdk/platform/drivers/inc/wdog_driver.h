

#ifndef WDOG_DRIVER_H
#define WDOG_DRIVER_H

#include "status.h"
#include "interrupt_manager.h"




typedef enum
{
    WDOG_BUS_CLOCK                        = 0x00U, 
    WDOG_LPO_CLOCK                        = 0x01U, 
    WDOG_SOSC_CLOCK                       = 0x02U, 
    WDOG_SIRC_CLOCK                       = 0x03U  
} wdog_clk_source_t;

typedef enum
{
    WDOG_TST_DISABLED                     = 0x00U, 
    WDOG_TST_USER                         = 0x01U, 
    WDOG_TST_LOW                          = 0x02U, 
    WDOG_TST_HIGH                         = 0x03U  
} wdog_test_mode_t;

typedef enum
{
    WDOG_DEBUG_MODE                        = 0x00U, 
    WDOG_WAIT_MODE                         = 0x01U, 
    WDOG_STOP_MODE                         = 0x02U  
} wdog_set_mode_t;

typedef struct
{
    bool wait;  
    bool stop;  
    bool debug; 
} wdog_op_mode_t;

typedef struct
{
    wdog_clk_source_t    clkSource;       
    wdog_op_mode_t       opMode;          
    bool                 updateEnable;    
    bool                 intEnable;       
    bool                 winEnable;       
    uint16_t             windowValue;     
    uint16_t             timeoutValue;    
    bool                 prescalerEnable; 
} wdog_user_config_t;


#if defined(__cplusplus)
extern "C" {
#endif

status_t WDOG_DRV_Init(uint32_t instance,
                       const wdog_user_config_t * userConfigPtr);

status_t WDOG_DRV_Deinit(uint32_t instance);

void WDOG_DRV_GetConfig(uint32_t instance,
                        wdog_user_config_t * const config);

void WDOG_DRV_GetDefaultConfig(wdog_user_config_t * const config);

status_t WDOG_DRV_SetInt(uint32_t instance,
                         bool enable);

void WDOG_DRV_ClearIntFlag(uint32_t instance);

void WDOG_DRV_Trigger(uint32_t instance);

uint16_t WDOG_DRV_GetCounter(uint32_t instance);

status_t WDOG_DRV_SetWindow(uint32_t instance,
                            bool enable,
                            uint16_t windowvalue);

status_t WDOG_DRV_SetMode(uint32_t instance,
                          bool enable,
                          wdog_set_mode_t Setmode);

status_t WDOG_DRV_SetTimeout(uint32_t instance,
                             uint16_t timeout);

status_t WDOG_DRV_SetTestMode(uint32_t instance,
                              wdog_test_mode_t testMode);

wdog_test_mode_t WDOG_DRV_GetTestMode(uint32_t instance);


#if defined(__cplusplus)
}
#endif


#endif 

