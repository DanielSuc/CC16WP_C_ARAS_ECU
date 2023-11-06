#ifndef HAL_IO_H
#define HAL_IO_H





#include "hal_data_types.h"
#include "pins_driver.h"




typedef enum
{
    HAL_IO_OK                       = 0u,   
    HAL_IO_ERROR_GENERAL                ,   
    HAL_IO_ERROR_INIT_FAILED            ,   
    HAL_IO_ERROR_DEINIT_FAILED          ,   
    HAL_IO_ERROR_CHANNEL_INVALID        ,   
    HAL_IO_ERROR_NO_CHANNEL_LEFT        ,   
    HAL_IO_ERROR_NO_DO                  ,   
    HAL_IO_ERROR_NO_DI                  ,   
    HAL_IO_ERROR_NOT_IMPLEMENTED        ,   
	HAL_IO_ERROR_SET_PIN				,	
	HAL_IO_ERROR_SET_DIRECTION			,	
    HAL_IO_ERROR_ADC_MAX_NOT_DEFINED        

} enum_HAL_IO_RETURN_VALUE;


typedef enum
{
    PORT_A = 0,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E,
    PORT_MAX
} enum_port_name;


enum_HAL_IO_RETURN_VALUE hal_io_init( const uint16_t num_pins );

void hal_io_get_pin_count( uint16_t * const num_pins );

enum_HAL_IO_RETURN_VALUE hal_io_init_pin( pin_settings_config_t const * const ptr_pin, const uint16_t pin_ind );

enum_HAL_IO_RETURN_VALUE hal_io_deinit( void );

enum_HAL_IO_RETURN_VALUE hal_io_di_get( const uint16_t pin, uint8_t * const ptr_state );

enum_HAL_IO_RETURN_VALUE hal_io_do_readback( const uint16_t pin, uint8_t * const ptr_state );

enum_HAL_IO_RETURN_VALUE hal_io_do_set( const uint16_t pin, const uint8_t state );

enum_HAL_IO_RETURN_VALUE hal_io_do_toggle( const uint16_t pin );

enum_HAL_IO_RETURN_VALUE hal_io_ai_get_digits( const uint16_t pin, uint16_t * const ptr_val );

enum_HAL_IO_RETURN_VALUE hal_io_ai_get_mV( const uint16_t pin, uint16_t * const ptr_val );

enum_HAL_IO_RETURN_VALUE hal_io_ao_set_digits( const uint16_t pin, const uint16_t val );

enum_HAL_IO_RETURN_VALUE hal_io_ao_set_mV( const uint16_t pin, const uint16_t val );

enum_HAL_IO_RETURN_VALUE hal_io_pin_set_direction( const uint16_t pin, const uint8_t direction );

enum_HAL_IO_RETURN_VALUE hal_io_port_set_direction( const uint16_t port, const uint32_t pins_direction );

enum_HAL_IO_RETURN_VALUE hal_io_do_port_write( const uint16_t port, const uint32_t data );

enum_HAL_IO_RETURN_VALUE hal_io_di_port_read( const uint16_t port, uint32_t * const ptr_state );

#endif

