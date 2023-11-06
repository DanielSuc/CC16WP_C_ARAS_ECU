#ifndef HAL_SCI_H
#define HAL_SCI_H

#include "hal_data_types.h"
#include "lpuart_driver.h"

#define VAL_MAX_BUF                                 15u

typedef enum
{
    HAL_SCI_BAUD_600             = 600u,    
    HAL_SCI_BAUD_1200            = 1200u,   
    HAL_SCI_BAUD_2400            = 2400u,   
    HAL_SCI_BAUD_4800            = 4800u,   
    HAL_SCI_BAUD_9600            = 9600u,   
    HAL_SCI_BAUD_14400           = 14400u,  
    HAL_SCI_BAUD_19200           = 19200u,  
    HAL_SCI_BAUD_28800           = 28800u,  
    HAL_SCI_BAUD_38400           = 38400u,  
    HAL_SCI_BAUD_56000           = 56000u,  
    HAL_SCI_BAUD_57600           = 57600u,  
    HAL_SCI_BAUD_115200          = 115200u, 
    HAL_SCI_BAUD_128000          = 128000u, 
    HAL_SCI_BAUD_250000          = 250000u, 
    HAL_SCI_BAUD_256000          = 256000u  
} enum_HAL_SCI_BAUD;



typedef enum
{
    HAL_SCI_OK                      = 0u,     
    HAL_SCI_ERROR_GENERAL               ,     
    HAL_SCI_ERROR_INIT_FAILED           ,     
    HAL_SCI_ERROR_DEINIT_FAILED         ,     
    HAL_SCI_ERROR_CHANNEL_INVALID       ,     
    HAL_SCI_ERROR_NO_CHANNEL_LEFT       ,     
    HAL_SCI_ERROR_SET_CALLBACK          ,     
    HAL_SCI_ERROR_SET_BAUDRATE          ,     
    HAL_SCI_ERROR_NOT_IMPLEMENTED             

} enum_HAL_SCI_RETURN_VALUE;

typedef void (*hal_sci_rx_callback_t)(void * callbackParam);

typedef void (*hal_sci_tx_callback_t)(void * callbackParam);
typedef void (*hal_sci_error_callback_t)(uint8_t);

typedef struct
{
    hal_sci_rx_callback_t rx_callback;          
    hal_sci_tx_callback_t tx_callback;          
    hal_sci_error_callback_t error_callback;    

}struct_hal_sci_callback_handle;

typedef struct
{
    void* ptr_handle;                                       
    uint8_t channel;                                        
    uint32_t baudrate;                                      
    struct_hal_sci_callback_handle hal_sci_callback_handle; 

}struct_hal_sci_handle;


enum_HAL_SCI_RETURN_VALUE hal_sci_init( struct_hal_sci_handle* ptr_sci_handle, uint8_t sci_channel );

enum_HAL_SCI_RETURN_VALUE hal_sci_deinit( struct_hal_sci_handle* ptr_sci_handle );

enum_HAL_SCI_RETURN_VALUE hal_sci_send_byte( struct_hal_sci_handle* ptr_sci_handle, uint8_t val );

enum_HAL_SCI_RETURN_VALUE hal_sci_receive_byte( struct_hal_sci_handle* ptr_sci_handle, uint8_t *ptr_val );

enum_HAL_SCI_RETURN_VALUE hal_sci_send_string( struct_hal_sci_handle* ptr_sci_handle, const uint8_t* ptr_str );

enum_HAL_SCI_RETURN_VALUE hal_sci_send_string_block( struct_hal_sci_handle* ptr_sci_handle, const uint8_t* ptr_str, uint32_t timeout );

enum_HAL_SCI_RETURN_VALUE hal_sci_send( struct_hal_sci_handle* ptr_sci_handle, const uint8_t* ptr_data, uint16_t len );

enum_HAL_SCI_RETURN_VALUE hal_sci_send_block( struct_hal_sci_handle* ptr_sci_handle, const uint8_t* ptr_data, uint16_t len,
    uint32_t timeout );

enum_HAL_SCI_RETURN_VALUE hal_sci_receive( struct_hal_sci_handle* ptr_sci_handle, uint8_t* ptr_data, uint16_t len );

enum_HAL_SCI_RETURN_VALUE hal_sci_receive_block( struct_hal_sci_handle* ptr_sci_handle, uint8_t* ptr_data, uint16_t len, uint32_t timeout );

enum_HAL_SCI_RETURN_VALUE hal_sci_send_status( struct_hal_sci_handle* ptr_sci_handle, uint32_t *bytes_remaining );

enum_HAL_SCI_RETURN_VALUE hal_sci_receive_status( struct_hal_sci_handle* ptr_sci_handle, uint32_t *bytes_remaining );

enum_HAL_SCI_RETURN_VALUE hal_sci_send_fix_point_val( struct_hal_sci_handle* ptr_sci_handle, uint32_t val, uint8_t fix_point );

enum_HAL_SCI_RETURN_VALUE hal_sci_set_callback(struct_hal_sci_handle*    ptr_sci_handle,
                                               hal_sci_rx_callback_t     ptr_hal_sci_rx_callback,
                                               hal_sci_tx_callback_t     ptr_hal_sci_tx_callback,
                                               hal_sci_error_callback_t  ptr_hal_sci_error_callback);

enum_HAL_SCI_RETURN_VALUE hal_sci_set_baudrate( struct_hal_sci_handle* ptr_sci_handle, uint32_t baudrate );
#endif

