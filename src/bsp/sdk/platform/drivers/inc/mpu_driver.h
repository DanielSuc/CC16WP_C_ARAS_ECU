

#ifndef MPU_DRIVER_H
#define MPU_DRIVER_H

#include "status.h"
#include "device_registers.h"


typedef enum
{
    MPU_ERR_TYPE_READ  = 0U,    
    MPU_ERR_TYPE_WRITE = 1U     
} mpu_err_access_type_t;

typedef enum
{
    MPU_INSTRUCTION_ACCESS_IN_USER_MODE       = 0U,    
    MPU_DATA_ACCESS_IN_USER_MODE              = 1U,    
    MPU_INSTRUCTION_ACCESS_IN_SUPERVISOR_MODE = 2U,    
    MPU_DATA_ACCESS_IN_SUPERVISOR_MODE        = 3U     
} mpu_err_attributes_t;

typedef struct
{
    uint8_t                master;                     
    mpu_err_attributes_t   attributes;                 
    mpu_err_access_type_t  accessType;                 
    uint16_t               accessCtr;                  
    uint32_t               addr;                       
#if FEATURE_MPU_HAS_PROCESS_IDENTIFIER
    uint8_t                processorIdentification;    
#endif
} mpu_access_err_info_t;

typedef enum
{
    MPU_SUPERVISOR_RWX_USER_NONE    = 0x00U,    
    MPU_SUPERVISOR_RWX_USER_X       = 0x01U,    
    MPU_SUPERVISOR_RWX_USER_W       = 0x02U,    
    MPU_SUPERVISOR_RWX_USER_WX      = 0x03U,    
    MPU_SUPERVISOR_RWX_USER_R       = 0x04U,    
    MPU_SUPERVISOR_RWX_USER_RX      = 0x05U,    
    MPU_SUPERVISOR_RWX_USER_RW      = 0x06U,    
    MPU_SUPERVISOR_RWX_USER_RWX     = 0x07U,    
    MPU_SUPERVISOR_RX_USER_NONE     = 0x08U,    
    MPU_SUPERVISOR_RX_USER_X        = 0x09U,    
    MPU_SUPERVISOR_RX_USER_W        = 0x0AU,    
    MPU_SUPERVISOR_RX_USER_WX       = 0x0BU,    
    MPU_SUPERVISOR_RX_USER_R        = 0x0CU,    
    MPU_SUPERVISOR_RX_USER_RX       = 0x0DU,    
    MPU_SUPERVISOR_RX_USER_RW       = 0x0EU,    
    MPU_SUPERVISOR_RX_USER_RWX      = 0x0FU,    
    MPU_SUPERVISOR_RW_USER_NONE     = 0x10U,    
    MPU_SUPERVISOR_RW_USER_X        = 0x11U,    
    MPU_SUPERVISOR_RW_USER_W        = 0x12U,    
    MPU_SUPERVISOR_RW_USER_WX       = 0x13U,    
    MPU_SUPERVISOR_RW_USER_R        = 0x14U,    
    MPU_SUPERVISOR_RW_USER_RX       = 0x15U,    
    MPU_SUPERVISOR_RW_USER_RW       = 0x16U,    
    MPU_SUPERVISOR_RW_USER_RWX      = 0x17U,    
    MPU_SUPERVISOR_USER_NONE        = 0x18U,    
    MPU_SUPERVISOR_USER_X           = 0x19U,    
    MPU_SUPERVISOR_USER_W           = 0x1AU,    
    MPU_SUPERVISOR_USER_WX          = 0x1BU,    
    MPU_SUPERVISOR_USER_R           = 0x1CU,    
    MPU_SUPERVISOR_USER_RX          = 0x1DU,    
    MPU_SUPERVISOR_USER_RW          = 0x1EU,    
    MPU_SUPERVISOR_USER_RWX         = 0x1FU,    
    MPU_NONE                        = 0x80U,    
    MPU_W                           = 0xA0U,    
    MPU_R                           = 0xC0U,    
    MPU_RW                          = 0xE0U     
} mpu_access_rights_t;

typedef struct
{
    uint8_t                     masterNum;                  
    mpu_access_rights_t         accessRight;                
#if FEATURE_MPU_HAS_PROCESS_IDENTIFIER
    bool                        processIdentifierEnable;    
#endif
} mpu_master_access_right_t;

typedef struct
{
    uint32_t                            startAddr;            
    uint32_t                            endAddr;              
    const mpu_master_access_right_t     *masterAccRight;      
#if FEATURE_MPU_HAS_PROCESS_IDENTIFIER
    uint8_t                             processIdentifier;    
    uint8_t                             processIdMask;        
#endif 
} mpu_user_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

status_t MPU_DRV_Init(uint32_t instance,
                      uint8_t regionCnt,
                      const mpu_user_config_t * userConfigArr);

void MPU_DRV_Deinit(uint32_t instance);

void MPU_DRV_SetRegionAddr(uint32_t instance,
                           uint8_t regionNum,
                           uint32_t startAddr,
                           uint32_t endAddr);

status_t MPU_DRV_SetRegionConfig(uint32_t instance,
                                 uint8_t regionNum,
                                 const mpu_user_config_t * userConfigPtr);

status_t MPU_DRV_SetMasterAccessRights(uint32_t instance,
                                       uint8_t regionNum,
                                       const mpu_master_access_right_t * accessRightsPtr);

bool MPU_DRV_GetDetailErrorAccessInfo(uint32_t instance,
                                      uint8_t slavePortNum,
                                      mpu_access_err_info_t * errInfoPtr);

mpu_user_config_t MPU_DRV_GetDefaultRegionConfig(mpu_master_access_right_t * masterAccRight);

void MPU_DRV_EnableRegion(uint32_t instance,
                          uint8_t regionNum,
                          bool enable);


#if defined(__cplusplus)
}
#endif


#endif 

