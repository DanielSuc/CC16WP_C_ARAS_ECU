#ifndef HAL_SYS_H
#define HAL_SYS_H

#include "hal_data_types.h"

#define HAL_SYS_APP_HEADER_VERSION                  (1u)            
#define HAL_SYS_APP_HEADER_KEY                      (0x12345678u)   
#define HAL_SYS_BOOTLOADER_ACCESS_KEY               (0x4D525321u)   
#define HAL_SYS_BOOTLOADER_APP_START_KEY            (0x07412807u)   
#define HAL_SYS_BOOTLOADER_ACCESS_KEY_UPDATE        (0x1AF7356B)    

typedef enum
{
    HAL_SYS_RESET_TYPE_NONE = 0,                                    
    HAL_SYS_RESET_TYPE_START_APP,                                   
    HAL_SYS_RESET_TYPE_SOFTRESET_APP,                               
    HAL_SYS_RESET_TYPE_SOFTRESET_BL,                                
    HAL_SYS_RESET_TYPE_SOFTRESET_BL_UPDATE_FROM_COPY,               
    HAL_SYS_RESET_TYPE_HARDRESET_WD,                                
    HAL_SYS_RESET_TYPE_HARDRESET_CPU,                               

}enum_HAL_SYS_RESET;

typedef struct
{
    uint32_t header_key;            
    uint32_t header_crc;            
    uint32_t app_header_version;    
    uint32_t application_crc;       
    uint32_t application_length;    
    uint8_t sw_version[32];         

#if HAL_SYS_APP_HEADER_VERSION >= 1
    uint8_t reserve[460];           
    uint8_t signature_key[512];     
#endif

} struct_hal_sys_app_header;

typedef void (*hal_sys_pre_reset_callback_t)( enum_HAL_SYS_RESET );

void hal_sys_init( hal_sys_pre_reset_callback_t callback );

void hal_sys_reset( enum_HAL_SYS_RESET reset_mode );

struct_hal_sys_app_header hal_sys_get_app_header( void );

struct_hal_sys_app_header hal_sys_get_app_update_header( void );

uint32_t hal_sys_get_bl_access_key( void );

void hal_sys_set_bl_access_key( uint32_t bl_access_key );

void hal_sys_disable_all_interrupts( void );

void hal_sys_enable_all_interrupts( void );
#endif

