
#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

#include "device_registers.h"
#include "status.h"

#if ((defined(S32K14x_SERIES)) || (defined(S32MTV_SERIES)) || (defined(S32K11x_SERIES)))
#include "../src/power/S32K1xx/power_manager_S32K1xx.h"
#elif (defined(S32V234_SERIES))
#include "../src/power/S32V234/power_manager_S32V234.h"
#elif (defined(MPC574x_SERIES) || defined(S32R_SERIES))
#include "../src/power/MPC57xx/power_manager_MPC57xx.h"
#else
#error "No valid CPU defined!"
#endif




typedef enum
{
    POWER_MANAGER_POLICY_AGREEMENT,      
    POWER_MANAGER_POLICY_FORCIBLE        
} power_manager_policy_t;

typedef enum
{
    POWER_MANAGER_NOTIFY_RECOVER = 0x00U,  
    POWER_MANAGER_NOTIFY_BEFORE  = 0x01U,  
    POWER_MANAGER_NOTIFY_AFTER   = 0x02U   
} power_manager_notify_t;

typedef enum
{
    POWER_MANAGER_CALLBACK_BEFORE       = 0x01U, 
    POWER_MANAGER_CALLBACK_AFTER        = 0x02U, 
    POWER_MANAGER_CALLBACK_BEFORE_AFTER = 0x03U  
} power_manager_callback_type_t;

typedef void power_manager_callback_data_t;


typedef struct
{
    power_manager_user_config_t * targetPowerConfigPtr; 
    uint8_t targetPowerConfigIndex;    
    power_manager_policy_t policy;     
    power_manager_notify_t notifyType; 
} power_manager_notify_struct_t;

typedef status_t (* power_manager_callback_t)(power_manager_notify_struct_t * notify,
                                              power_manager_callback_data_t * dataPtr);

typedef struct
{
    power_manager_callback_t callbackFunction;
    power_manager_callback_type_t callbackType;
    power_manager_callback_data_t * callbackData;
} power_manager_callback_user_config_t;

typedef struct
{
    power_manager_user_config_t * (*configs)[];             
    uint8_t configsNumber;                                  
    power_manager_callback_user_config_t * (*staticCallbacks)[]; 
    uint8_t staticCallbacksNumber;                          
    uint8_t errorCallbackIndex;                             
    uint8_t currentConfig;                                  
} power_manager_state_t;

extern power_manager_state_t gPowerManagerState;


#if defined(__cplusplus)
extern "C" {
#endif

status_t POWER_SYS_Init(power_manager_user_config_t * (*powerConfigsPtr)[],
                        uint8_t configsNumber,
                        power_manager_callback_user_config_t * (*callbacksPtr)[],
                        uint8_t callbacksNumber);

status_t POWER_SYS_Deinit(void);

status_t POWER_SYS_SetMode(uint8_t powerModeIndex,
                           power_manager_policy_t policy);

status_t POWER_SYS_GetLastMode(uint8_t * powerModeIndexPtr);

status_t POWER_SYS_GetLastModeConfig(power_manager_user_config_t ** powerModePtr);

power_manager_modes_t POWER_SYS_GetCurrentMode(void);

uint8_t POWER_SYS_GetErrorCallbackIndex(void);

power_manager_callback_user_config_t * POWER_SYS_GetErrorCallback(void);

void POWER_SYS_GetDefaultConfig(power_manager_user_config_t * const config);

#if defined(__cplusplus)
}
#endif


#endif 

