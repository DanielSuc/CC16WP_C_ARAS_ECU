#include <stdbool.h>
#include <stdint.h>

#include "lpuart1.h"
#include "sci_app.h"

#include "hal_io.h"
#include "hal_sci.h"
#include "io_tables.h"

#include "sfl_timer.h"

#include "user_code.h"

#define TIMEOUT 30

void UART_Callback(uint8_t interface, void *driverState, uart_event_t event, void * callbackParam);

void UART_Callback0(void *driverState, uart_event_t event, void * callbackParam);
void UART_Callback1(void *driverState, uart_event_t event, void * callbackParam);
void UART_Callback2(void *driverState, uart_event_t event, void * callbackParam);

uint8_t rx_buffer_8bit[MAX_LPUART_INSTANCES] = {0};
uint8_t tx_buffer_8bit[MAX_LPUART_INSTANCES] = {0};


static struct_hal_sci_handle hal_sci_config[MAX_LPUART_INSTANCES] __attribute__((unused))= {
    { .channel = INST_LPUART0, .baudrate = HAL_SCI_BAUD_115200, .hal_sci_callback_handle = { .rx_callback = (hal_sci_rx_callback_t) UART_Callback0, .tx_callback = (hal_sci_tx_callback_t) UART_Callback0, .error_callback = NULL, } },
    { .channel = INST_LPUART1, .baudrate = HAL_SCI_BAUD_115200, .hal_sci_callback_handle = { .rx_callback = (hal_sci_rx_callback_t) UART_Callback1, .tx_callback = (hal_sci_tx_callback_t) UART_Callback1, .error_callback = NULL, } },
    { .channel = INST_LPUART2, .baudrate = HAL_SCI_BAUD_115200, .hal_sci_callback_handle = { .rx_callback = (hal_sci_rx_callback_t) UART_Callback2, .tx_callback = (hal_sci_tx_callback_t) UART_Callback2, .error_callback = NULL, } },
};

void UART_Callback0(void *driverState, uart_event_t event, void * callbackParam)
{
    UART_Callback(0, driverState, event, callbackParam);
}

void UART_Callback1(void *driverState, uart_event_t event, void * callbackParam)
{
    UART_Callback(1, driverState, event, callbackParam);
}

void UART_Callback2(void *driverState, uart_event_t event, void * callbackParam)
{
    UART_Callback(2, driverState, event, callbackParam);
}

void UART_Callback(uint8_t interface,void *driverState, uart_event_t event, void * callbackParam)
{
    switch (event)
    {
        case UART_EVENT_RX_FULL:
#ifdef SET_SCI_CONTINUOUS_RECEPTION
            user_sci_continuous_receive_callback(hal_sci_config[interface].channel, rx_buffer_8bit[interface]);
            LPUART_DRV_SetRxBuffer(hal_sci_config[interface].channel, &rx_buffer_8bit[interface], 1);
#else
            user_sci_rx_full_callback(hal_sci_config[interface].channel);
#endif
            break;

        case UART_EVENT_TX_EMPTY:
#ifdef SET_SCI_CONTINUOUS_TRANSMISSION
            user_sci_continuous_transmit_callback(hal_sci_config[interface].channel, &tx_buffer_8bit[interface]);
            LPUART_DRV_SetTxBuffer(hal_sci_config[interface].channel, &tx_buffer_8bit[interface], 1);
#else
            user_sci_tx_empty_callback(hal_sci_config[interface].channel);
#endif
            break;

        case UART_EVENT_END_TRANSFER:
            user_sci_transfer_complete_callback(hal_sci_config[interface].channel);
            break;

        default:
            break;
    }
}

enum_HAL_SCI_RETURN_VALUE sci_init(uint8_t interface)
{
    if ( interface > NUMBER_OF_LPUART_INSTANCES)
    {
        return HAL_SCI_ERROR_CHANNEL_INVALID;
    }
    else
    {
        hal_sci_init(&hal_sci_config[interface], hal_sci_config[interface].channel);
        hal_sci_set_callback(&hal_sci_config[interface], hal_sci_config[interface].hal_sci_callback_handle.rx_callback, hal_sci_config[interface].hal_sci_callback_handle.tx_callback, hal_sci_config[interface].hal_sci_callback_handle.error_callback);
#ifdef SET_SCI_CONTINUOUS_RECEPTION
        hal_sci_receive(&hal_sci_config[interface], &rx_buffer_8bit[interface], 1); 
#endif
        return HAL_SCI_OK;
    }
}

enum_HAL_SCI_RETURN_VALUE sci_set_baudrate(uint8_t interface, enum_HAL_SCI_BAUD baudrate)
{
    enum_HAL_SCI_RETURN_VALUE ret_val = HAL_SCI_ERROR_GENERAL;

    if ( interface > NUMBER_OF_LPUART_INSTANCES)
    {
        ret_val = HAL_SCI_ERROR_CHANNEL_INVALID;
    }
    else
    {
        hal_sci_deinit(&hal_sci_config[interface]);
        hal_sci_config[interface].baudrate = baudrate;
        ret_val = hal_sci_set_baudrate(&hal_sci_config[interface], baudrate);
        hal_sci_init(&hal_sci_config[interface], hal_sci_config[interface].channel);
        hal_sci_set_callback(&hal_sci_config[interface], hal_sci_config[interface].hal_sci_callback_handle.rx_callback, hal_sci_config[interface].hal_sci_callback_handle.tx_callback, hal_sci_config[interface].hal_sci_callback_handle.error_callback);
#ifdef SET_SCI_CONTINUOUS_RECEPTION
        hal_sci_receive(&hal_sci_config[interface], &rx_buffer_8bit[interface], 1);
#endif
    }
    return ret_val;
}

enum_HAL_SCI_RETURN_VALUE sci_set_config_parameter(uint8_t interface, lpuart_parity_mode_t parity, lpuart_stop_bit_count_t stop_bit, lpuart_bit_count_per_char_t bit_per_char )
{
    if ( interface > NUMBER_OF_LPUART_INSTANCES)
    {
        return HAL_SCI_ERROR_CHANNEL_INVALID;
    }
    else
    {
        struct_lpuart_config[interface].lpuart_init_config_struct->parityMode = parity;
        struct_lpuart_config[interface].lpuart_init_config_struct->stopBitCount = stop_bit;
        struct_lpuart_config[interface].lpuart_init_config_struct->bitCountPerChar = bit_per_char;

#if 0
        hal_sci_config->ptr_handle = &struct_lpuart_config[interface];
#endif

        sci_deinit(interface);

        sci_init(interface);
        return HAL_SCI_OK;
    }
}

enum_HAL_SCI_RETURN_VALUE sci_sleep(uint8_t interface)
{
    return sci_deinit(interface);
}

enum_HAL_SCI_RETURN_VALUE sci_deinit(uint8_t interface)
{
    if ( interface > NUMBER_OF_LPUART_INSTANCES)
    {
        return HAL_SCI_ERROR_CHANNEL_INVALID;
    }
    else
    {
        return hal_sci_deinit(&hal_sci_config[interface]);
    }
}


enum_HAL_SCI_RETURN_VALUE sci_tx_blocking(uint8_t interface, const uint8_t* send_buffer, uint8_t send_length)
{
    if ( interface > NUMBER_OF_LPUART_INSTANCES)
    {
        return HAL_SCI_ERROR_CHANNEL_INVALID;
    }
    else
    {
        return hal_sci_send_block(&hal_sci_config[interface], send_buffer, send_length, TIMEOUT);
    }
}

enum_HAL_SCI_RETURN_VALUE sci_tx(uint8_t interface, const uint8_t* send_buffer, uint8_t send_length)
{
    if ( interface > NUMBER_OF_LPUART_INSTANCES)
    {
        return HAL_SCI_ERROR_CHANNEL_INVALID;
    }
    else
    {
        return hal_sci_send(&hal_sci_config[interface], send_buffer, send_length);
    }
}

enum_HAL_SCI_RETURN_VALUE sci_rx_blocking(uint8_t interface, uint8_t* recv_buffer, uint8_t recv_length)
{
    if ( interface > NUMBER_OF_LPUART_INSTANCES)
    {
        return HAL_SCI_ERROR_CHANNEL_INVALID;
    }
    else
    {
        return hal_sci_receive_block(&hal_sci_config[interface], (uint8_t*)recv_buffer, recv_length, TIMEOUT);
    }
}

enum_HAL_SCI_RETURN_VALUE sci_rx(uint8_t interface, uint8_t* recv_buffer, uint8_t recv_length)
{
    if ( interface > NUMBER_OF_LPUART_INSTANCES)
    {
        return HAL_SCI_ERROR_CHANNEL_INVALID;
    }
    else
    {
        return hal_sci_receive(&hal_sci_config[interface], (uint8_t*)recv_buffer, recv_length);
    }
}

enum_HAL_SCI_RETURN_VALUE sci_tx_status( uint8_t interface)
{
    if ( interface > NUMBER_OF_LPUART_INSTANCES)
    {
        return HAL_SCI_ERROR_CHANNEL_INVALID;
    }
    else
    {
        return hal_sci_send_status( &hal_sci_config[interface], NULL );
    }
}

enum_HAL_SCI_RETURN_VALUE sci_rx_status( uint8_t interface )
{
    if ( interface > NUMBER_OF_LPUART_INSTANCES)
    {
        return HAL_SCI_ERROR_CHANNEL_INVALID;
    }
    else
    {
        return hal_sci_receive_status( &hal_sci_config[interface], NULL );
    }
}

uint32_t sci_tx_get_remaining_bytes( uint8_t interface )
{
    uint32_t bytes_remaining = ( (uint32_t) - 1);

    if ( interface > NUMBER_OF_LPUART_INSTANCES)
    {
        return HAL_SCI_ERROR_CHANNEL_INVALID;
    }
    else
    {
        (void) hal_sci_send_status( &hal_sci_config[interface], &bytes_remaining );
    }

    return bytes_remaining;
}

uint32_t sci_rx_get_remaining_bytes( uint8_t interface )
{
    uint32_t bytes_remaining = ( (uint32_t) - 1);

    if ( interface > NUMBER_OF_LPUART_INSTANCES)
    {
        return HAL_SCI_ERROR_CHANNEL_INVALID;
    }
    else
    {
        (void) hal_sci_receive_status( &hal_sci_config[interface], &bytes_remaining );
    }

    return bytes_remaining;
}

__attribute__ ((weak)) void user_sci_rx_full_callback(uint8_t instance)
 {

 }

__attribute__ ((weak)) void user_sci_continuous_transmit_callback(uint8_t instance, uint8_t *buff)
 {

 }

__attribute__ ((weak)) void user_sci_tx_empty_callback(uint8_t instance)
 {

 }

__attribute__ ((weak)) void user_sci_transfer_complete_callback(uint8_t instance)
 {

 }

