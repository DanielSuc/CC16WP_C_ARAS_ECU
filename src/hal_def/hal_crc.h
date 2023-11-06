#ifndef HAL_CRC_H
#define HAL_CRC_H


#include "hal_data_types.h"


typedef enum
{
    HAL_CRC_OK                      = 0u,       
    HAL_CRC_ERROR_NO_CHANNEL_LEFT       ,       
    HAL_CRC_ERROR_WHILE_INITIALIZING    ,       
} enum_HAL_CRC_RETURN_VALUE;


typedef struct
{
    void* ptr_handle;       
    uint8_t channel;        
    const void* ptr_data;   
    uint32_t size;          
    uint32_t crc;           
} struct_hal_crc_handle;


enum_HAL_CRC_RETURN_VALUE hal_crc_init( struct_hal_crc_handle* ptr_crc_handle, uint8_t channel );

uint32_t hal_crc_calculate_crc( struct_hal_crc_handle* ptr_crc_handle, const void* ptr_data, uint32_t size );

#endif


