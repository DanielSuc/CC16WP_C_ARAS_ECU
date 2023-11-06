#ifndef _HAL_I2C_H_
#define _HAL_I2C_H_
#include "hal_data_types.h"


typedef enum
{
    HAL_I2C_OK                      = 0u,       
    HAL_I2C_ERROR_GENERAL               ,       
    HAL_I2C_ERROR_INIT_FAILED           ,       
    HAL_I2C_ERROR_DEINIT_FAILED         ,       
    HAL_I2C_ERROR_NO_CHANNEL_LEFT       ,       
    HAL_I2C_ERROR_WHILE_SENDING         ,       
    HAL_I2C_ERROR_WHILE_RECEIVING       ,       

} enum_HAL_I2C_RETURN_VALUE;


typedef struct
{
        void* i2c_handle_ptr;       
        uint8_t i2c_instance;       
} struct_hal_i2c_handle;

typedef struct
{
        uint8_t* i2c_rx_buffer;     
        uint32_t i2c_rx_size;       
        uint8_t* i2c_tx_buffer;     
        uint32_t i2c_tx_size;       
        uint8_t  i2c_stop_bit;      
        uint32_t timeout_size;      
} struct_hal_i2c_frame;

typedef struct
{
        uint32_t baudrate;
        uint16_t slaveAddress;                      
        bool is10bitAddr;                           
} struct_hal_i2c_master_config;

enum_HAL_I2C_RETURN_VALUE hal_i2c_master_init( struct_hal_i2c_handle* ptr_i2c_handle, uint8_t instance, const struct_hal_i2c_master_config *i2c_config );

enum_HAL_I2C_RETURN_VALUE hal_i2c_master_deinit( struct_hal_i2c_handle* ptr_i2c_handle );

enum_HAL_I2C_RETURN_VALUE hal_i2c_master_send_blocking( struct_hal_i2c_handle* ptr_i2c_handle, struct_hal_i2c_frame* ptr_i2c_frame );

enum_HAL_I2C_RETURN_VALUE hal_i2c_master_receive_blocking( struct_hal_i2c_handle* ptr_i2c_handle, struct_hal_i2c_frame* ptr_i2c_frame );

enum_HAL_I2C_RETURN_VALUE hal_i2c_master_set_slave_address( struct_hal_i2c_handle* ptr_i2c_handle, uint16_t address, bool is10bitAddr );

#endif

