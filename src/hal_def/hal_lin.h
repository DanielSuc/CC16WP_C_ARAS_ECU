#ifndef HAL_LIN_H
#define HAL_LIN_H
#include "hal_data_types.h"

#define HAL_LIN_DATA_MAX               8u
#define HAL_LIN_SET_WAKE_UP            1u
#define HAL_LINE_FRAME_SEPARATE_MODE   1u


typedef enum
{
    HAL_LIN_OK                      = 0u,     
    HAL_LIN_ERROR_NO_CHANNEL_LEFT       ,     
    HAL_LIN_ERROR_DATA_LEN_INVALID      ,     
    HAL_LIN_ERROR_DIR_INVALID           ,     
    HAL_LIN_ERROR_CRC_INVALID           ,     
    HAL_LIN_ERROR_NODE_INVALID          ,     
    HAL_LIN_ERROR_RESPONSE_INVALID      ,     
	HAL_LIN_ERROR_OTHER					      

}enum_HAL_LIN_RETURN_VALUE;

typedef enum
{
	HAL_LIN_BREAK_DETECTION_DISABLED 	= 0u,	
	HAL_LIN_BREAK_DETECTION_ENABLED 	= 1u	
}HAL_LIN_BREAK_DETECTION;



typedef void (*hal_lin_tx_callback_t)( uint8_t );
typedef void (*hal_lin_rx_callback_t)( uint8_t, uint8_t, uint8_t );
typedef void (*hal_lin_error_callback_t)( uint8_t, uint8_t );


enum_HAL_LIN_RETURN_VALUE hal_lin_init( uint8_t hw_module, uint32_t baudrate );

void hal_lin_de_init( uint8_t hw_module );

enum_HAL_LIN_RETURN_VALUE hal_lin_set_callback( uint8_t hw_module,
    hal_lin_tx_callback_t const ptr_lin_tx_callback,
    hal_lin_rx_callback_t const ptr_lin_rx_callback,
    hal_lin_error_callback_t const ptr_lin_error_callback );

void hal_lin_write_byte( uint8_t hw_module, uint8_t data, bool blocking );

void hal_lin_set_master_mode( uint8_t hw_module );

void hal_lin_break_detection_enable( uint8_t hw_module, bool enable_interrupt, uint8_t break_length );

void hal_lin_send_break( uint8_t hw_module );

void hal_lin_tx_complete_int_enable( uint8_t hw_module, bool ena );

void hal_lin_rx_int_enable( uint8_t hw_module, bool ena );

#endif 

