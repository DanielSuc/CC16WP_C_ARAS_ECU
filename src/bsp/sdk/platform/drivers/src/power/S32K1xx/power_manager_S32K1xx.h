
#ifndef POWER_MANAGER_S32K1XX_H
#define POWER_MANAGER_S32K1XX_H


#include "device_registers.h"
#include "status.h"


typedef enum
{
#if FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE
    POWER_MANAGER_HSRUN,            
#endif
    POWER_MANAGER_RUN,              
    POWER_MANAGER_VLPR,             
#if FEATURE_SMC_HAS_WAIT_VLPW
    POWER_MANAGER_WAIT,             
    POWER_MANAGER_VLPW,             
#endif
#if FEATURE_SMC_HAS_PSTOPO
    POWER_MANAGER_PSTOP1,           
    POWER_MANAGER_PSTOP2,           
#endif
#if FEATURE_SMC_HAS_STOPO
    POWER_MANAGER_STOP1,           
    POWER_MANAGER_STOP2,           
#endif
    POWER_MANAGER_VLPS,             
    POWER_MANAGER_MAX
} power_manager_modes_t;

typedef struct
{
    power_manager_modes_t powerMode;
    bool sleepOnExitValue;
} power_manager_user_config_t;

typedef enum
{
    STAT_RUN     = 0x01,              
    STAT_STOP    = 0x02,              
    STAT_VLPR    = 0x04,              
    STAT_VLPW    = 0x08,              
    STAT_VLPS    = 0x10,              
    STAT_HSRUN   = 0x80,              
    STAT_INVALID = 0xFF               
} power_mode_stat_t;

typedef enum
{
    SMC_RUN,                                
    SMC_RESERVED_RUN, SMC_VLPR,             
    SMC_HSRUN                               
} smc_run_mode_t;

typedef enum
{
    SMC_STOP            = 0U,    
    SMC_RESERVED_STOP1  = 1U,    
    SMC_VLPS            = 2U     
} smc_stop_mode_t;

typedef enum
{
    SMC_STOP_RESERVED = 0x00,               
    SMC_STOP1         = 0x01,               
    SMC_STOP2         = 0x02                
} smc_stop_option_t;

typedef struct
{
    bool vlpProt;            
#if FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE
    bool hsrunProt;          
#endif
} smc_power_mode_protection_config_t;

typedef struct
{
    power_manager_modes_t powerModeName;    
#if FEATURE_SMC_HAS_STOPO
    smc_stop_option_t stopOptionValue;      
#endif
#if FEATURE_SMC_HAS_PSTOPO
    bool pStopOption;                       
    smc_stop_option_t pStopOptionValue;     
#endif
} smc_power_mode_config_t;

typedef enum
{
    RCM_LOW_VOLT_DETECT      = 1U,             
    RCM_LOSS_OF_CLK          = 2U,       
    RCM_LOSS_OF_LOCK         = 3U,       
#if FEATURE_RCM_HAS_CMU_LOSS_OF_CLOCK
    RCM_CMU_LOC              = 4U,        
#endif
    RCM_WATCH_DOG            = 5U,        
    RCM_EXTERNAL_PIN         = 6U,       
    RCM_POWER_ON             = 7U,       
    RCM_SJTAG                = 8U,       
    RCM_CORE_LOCKUP          = 9U,       
    RCM_SOFTWARE             = 10U,       
    RCM_SMDM_AP              = 11U,       
    RCM_STOP_MODE_ACK_ERR    = 13U,       
    RCM_SRC_NAME_MAX
} rcm_source_names_t;

#if defined(__cplusplus)
extern "C" {
#endif

status_t POWER_SYS_DoInit(void);

status_t POWER_SYS_DoDeinit(void);

status_t POWER_SYS_DoSetMode(const power_manager_user_config_t * const configPtr);

bool POWER_SYS_GetResetSrcStatusCmd(const RCM_Type * const baseAddr , const rcm_source_names_t srcName);

static inline void POWER_SYS_DoGetDefaultConfig(power_manager_user_config_t * const defaultConfig)
{
    defaultConfig->powerMode = POWER_MANAGER_RUN;    
    defaultConfig->sleepOnExitValue = false;         
}

#if defined(__cplusplus)
}
#endif


#endif 

