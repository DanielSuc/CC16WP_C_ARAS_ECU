
#ifndef SRC_APP_sci_APP_H_
#define SRC_APP_sci_APP_H_

#include "hal_sci.h"


typedef enum
{
    SCI_INTERFACE_0          = 0u,
    SCI_INTERFACE_1              ,
    SCI_INTERFACE_2              ,

} enum_lpuart_interface;

enum_HAL_SCI_RETURN_VALUE sci_init(uint8_t interface);


enum_HAL_SCI_RETURN_VALUE sci_set_baudrate(uint8_t interface, enum_HAL_SCI_BAUD baudrate);

enum_HAL_SCI_RETURN_VALUE sci_set_config_parameter(uint8_t interface, lpuart_parity_mode_t parity, lpuart_stop_bit_count_t stop_bit, lpuart_bit_count_per_char_t bit_per_char );


enum_HAL_SCI_RETURN_VALUE sci_sleep(uint8_t interface);


enum_HAL_SCI_RETURN_VALUE sci_deinit(uint8_t interface);


enum_HAL_SCI_RETURN_VALUE sci_tx_blocking(uint8_t interface, const uint8_t* send_buffer, uint8_t send_length);


enum_HAL_SCI_RETURN_VALUE sci_tx(uint8_t interface, const uint8_t* send_buffer, uint8_t send_length);


enum_HAL_SCI_RETURN_VALUE sci_rx_blocking(uint8_t interface, uint8_t* recv_buffer, uint8_t recv_length);


enum_HAL_SCI_RETURN_VALUE sci_rx(uint8_t interface, uint8_t* recv_buffer, uint8_t recv_length);


enum_HAL_SCI_RETURN_VALUE sci_tx_status( uint8_t interface );


enum_HAL_SCI_RETURN_VALUE sci_rx_status( uint8_t interface );


uint32_t sci_tx_get_remaining_bytes( uint8_t interface );


uint32_t sci_rx_get_remaining_bytes( uint8_t interface );


#endif 

