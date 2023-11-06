#ifndef SRC_USER_API_UART_H_
#define SRC_USER_API_UART_H_
#include "hal_sci.h"


enum_HAL_SCI_RETURN_VALUE user_uart_send_buffer_blocking(uint8_t uart_interface, const uint8_t *send_buffer, uint8_t send_length);


enum_HAL_SCI_RETURN_VALUE user_uart_send_buffer(uint8_t uart_interface, const uint8_t *send_buffer, uint8_t send_length);


enum_HAL_SCI_RETURN_VALUE user_uart_send_get_status(uint8_t uart_interface);


uint32_t user_uart_send_get_remaining_bytes( uint8_t uart_interface );


enum_HAL_SCI_RETURN_VALUE user_uart_receive_buffer_blocking( uint8_t uart_interface, uint8_t *recv_buffer, uint8_t recv_length );


enum_HAL_SCI_RETURN_VALUE user_uart_receive_buffer( uint8_t uart_interface, uint8_t *recv_buffer, uint8_t recv_length );


enum_HAL_SCI_RETURN_VALUE user_uart_receive_get_status(uint8_t uart_interface);


uint32_t user_uart_receive_get_remaining_bytes( uint8_t uart_interface );


enum_HAL_SCI_RETURN_VALUE user_uart_set_baudrate(uint8_t uart_interface, enum_HAL_SCI_BAUD baudrate);


enum_HAL_SCI_RETURN_VALUE user_uart_set_config_parameter(uint8_t uart_interface, lpuart_parity_mode_t parity, lpuart_stop_bit_count_t stop_bit, lpuart_bit_count_per_char_t bit_per_char );

#endif 

