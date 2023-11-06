
#ifndef FLASH_MX25L6433F_DRIVER_H
#define FLASH_MX25L6433F_DRIVER_H

#include <stddef.h>
#include <stdbool.h>
#include "device_registers.h"
#include "status.h"
#include "quadspi_driver.h"




typedef enum
{
    FLASH_MX25L6433F_PROT_DIR_TOP        = 0x00U,  
    FLASH_MX25L6433F_PROT_DIR_BOTTOM     = 0x01U,  
} flash_mx25l6433f_prot_dir_t;


typedef enum
{
    FLASH_MX25L6433F_DRV_STRENGTH_HIGH       = 0x00U,  
    FLASH_MX25L6433F_DRV_STRENGTH_LOW        = 0x01U,  
} flash_mx25l6433f_drv_strength_t;


typedef enum
{
    FLASH_MX25L6433F_PROT_SIZE_0         = 0x00U,  
    FLASH_MX25L6433F_PROT_SIZE_64K       = 0x01U,  
    FLASH_MX25L6433F_PROT_SIZE_128K      = 0x02U,  
    FLASH_MX25L6433F_PROT_SIZE_256K      = 0x03U,  
    FLASH_MX25L6433F_PROT_SIZE_512K      = 0x04U,  
    FLASH_MX25L6433F_PROT_SIZE_1M        = 0x05U,  
    FLASH_MX25L6433F_PROT_SIZE_2M        = 0x06U,  
    FLASH_MX25L6433F_PROT_SIZE_4M        = 0x07U,  
    FLASH_MX25L6433F_PROT_SIZE_8M        = 0x08U,  
} flash_mx25l6433f_prot_size_t;



typedef struct
{
    bool dmaSupport;                                        
    flash_mx25l6433f_drv_strength_t outputDriverStrength;   
} flash_mx25l6433f_user_config_t;


typedef struct
{
    uint8_t lastCommand;                                    
    uint8_t suspendedCommand;                               
    flash_mx25l6433f_drv_strength_t outputDriverStrength;   
    bool dmaSupport;                                        
} flash_mx25l6433f_state_t;



typedef struct
{
    bool userAreaLock;               
    bool factoryAreaLock;            
} flash_mx25l6433f_secure_lock_t;



#if defined(__cplusplus)
extern "C" {
#endif


status_t FLASH_MX25L6433F_DRV_Init(uint32_t instance,
                                   const flash_mx25l6433f_user_config_t * userConfigPtr,
                                   flash_mx25l6433f_state_t * state);


status_t FLASH_MX25L6433F_DRV_Deinit(uint32_t instance);


status_t FLASH_MX25L6433F_DRV_SetProtection(uint32_t instance, 
                                            flash_mx25l6433f_prot_dir_t direction,
                                            flash_mx25l6433f_prot_size_t size);


status_t FLASH_MX25L6433F_DRV_GetProtection(uint32_t instance, 
                                            flash_mx25l6433f_prot_dir_t * direction,
                                            flash_mx25l6433f_prot_size_t * size);


status_t FLASH_MX25L6433F_DRV_SetSecureLock(uint32_t instance);


status_t FLASH_MX25L6433F_DRV_GetSecureLock(uint32_t instance,  
                                            flash_mx25l6433f_secure_lock_t *lock);


status_t FLASH_MX25L6433F_DRV_Read(uint32_t instance, 
                                   uint32_t address,
                                   uint8_t * data,
                                   uint32_t size);


status_t FLASH_MX25L6433F_DRV_Erase4K(uint32_t instance, uint32_t address);


status_t FLASH_MX25L6433F_DRV_Erase32K(uint32_t instance, uint32_t address);


status_t FLASH_MX25L6433F_DRV_Erase64K(uint32_t instance, uint32_t address);


status_t FLASH_MX25L6433F_DRV_EraseAll(uint32_t instance);


status_t FLASH_MX25L6433F_DRV_EraseVerify(uint32_t instance, uint32_t address, uint32_t size);


status_t FLASH_MX25L6433F_DRV_Program(uint32_t instance,
                                      uint32_t address,
                                      const uint8_t * data,
                                      uint32_t size);


status_t FLASH_MX25L6433F_DRV_ProgramVerify(uint32_t instance, 
                                            uint32_t address,
                                            const uint8_t * data,
                                            uint32_t size);


status_t FLASH_MX25L6433F_DRV_GetStatus(uint32_t instance);


status_t FLASH_MX25L6433F_DRV_Reset(uint32_t instance);


status_t FLASH_MX25L6433F_DRV_EnterOTP(uint32_t instance);


status_t FLASH_MX25L6433F_DRV_ExitOTP(uint32_t instance);


status_t FLASH_MX25L6433F_DRV_EnterDPD(uint32_t instance);


status_t FLASH_MX25L6433F_DRV_ExitDPD(uint32_t instance);


status_t FLASH_MX25L6433F_DRV_Suspend(uint32_t instance);


status_t FLASH_MX25L6433F_DRV_Resume(uint32_t instance);


void FLASH_MX25L6433F_DRV_GetDefaultConfig(flash_mx25l6433f_user_config_t * userConfigPtr);


#if defined(__cplusplus)
}
#endif


#endif 

