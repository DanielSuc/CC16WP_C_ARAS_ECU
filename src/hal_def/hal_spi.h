#ifndef HAL_SPI_H
#define HAL_SPI_H
#include "hal_data_types.h"



#define CS_ENABLE(ptr_spi_handle)               \
    if ( ptr_spi_handle->cs_control != NULL )   \
        ptr_spi_handle->cs_control(1);

#define CS_DISABLE(ptr_spi_handle)              \
    if ( ptr_spi_handle->cs_control != NULL )   \
        ptr_spi_handle->cs_control(0);

typedef enum
{
    HAL_SPI_OK                      = 0u,     
    HAL_SPI_ERROR_GENERAL               ,     
    HAL_SPI_ERROR_BUSY                  ,     
    HAL_SPI_ERROR_INVALID_PARAM	        ,     
    HAL_SPI_ERROR_INIT_FAILED           ,     
    HAL_SPI_ERROR_CONFIG_FAILED         ,     
    HAL_SPI_ERROR_DEINIT_FAILED         ,     
    HAL_SPI_ERROR_CHANNEL_INVALID       ,     
    HAL_SPI_ERROR_NO_CHANNEL_LEFT       ,     
    HAL_SPI_ERROR_SET_CALLBACK          ,     
    HAL_SPI_ERROR_SET_BAUDRATE          ,     
    HAL_SPI_ERROR_TX_DATA               ,     
    HAL_SPI_ERROR_RX_DATA               ,     
    HAL_SPI_ERROR_WHILE_READING         ,     
    HAL_SPI_ERROR_WHILE_WRITING         ,     
    HAL_SPI_ERROR_WHILE_TRANSFER        ,     
    HAL_SPI_ERROR_NOT_IMPLEMENTED             

} enum_HAL_SPI_RETURN_VALUE;


typedef struct
{
        void* ptr_handle;
        uint8_t channel;
        void (*cs_control)(int active); 
} struct_hal_spi_handle;

typedef struct
{
        uint8_t* ptr_tx_data;
        uint8_t* ptr_rx_data;
        uint16_t size;
} struct_hal_spi_frame;

typedef struct
{
        uint32_t spi_baudrate;
        uint8_t  spi_which_pcs;
        uint8_t  spi_pcs_polarity;
        bool     spi_pcs_contiuous_mode;
        uint8_t  spi_clock_phase;
        uint8_t  spi_clock_polarity;
        bool     spi_lsb_first;
        void     (*spi_cs_control)(int active); 
} struct_hal_spi_master_config;

typedef struct
{
        uint8_t  spi_which_pcs;
        uint8_t  spi_pcs_polarity;
        uint8_t  spi_clock_phase;
        uint8_t  spi_clock_polarity;
        bool     spi_lsb_first;
} struct_hal_spi_slave_config;


enum_HAL_SPI_RETURN_VALUE hal_spi_master_init( struct_hal_spi_handle* ptr_spi_handle, uint8_t spi_channel, const struct_hal_spi_master_config* ptr_spi_config );

enum_HAL_SPI_RETURN_VALUE hal_spi_slave_init( struct_hal_spi_handle* ptr_spi_handle, uint8_t spi_channel, const struct_hal_spi_slave_config* ptr_spi_config );

enum_HAL_SPI_RETURN_VALUE hal_spi_master_deinit( struct_hal_spi_handle* ptr_spi_handle );

enum_HAL_SPI_RETURN_VALUE hal_spi_slave_deinit( struct_hal_spi_handle* ptr_spi_handle );

enum_HAL_SPI_RETURN_VALUE hal_spi_master_send( struct_hal_spi_handle* ptr_spi_handle, uint8_t *ptr_tx_data, uint8_t size );

enum_HAL_SPI_RETURN_VALUE hal_spi_master_send_blocking( struct_hal_spi_handle* ptr_spi_handle, uint8_t *ptr_tx_data, uint8_t size,
    uint32_t timeout );

#ifdef HAL_SPI_SLAVE_EXTENDED_FUNCTIONS_ENABLE
enum_HAL_SPI_RETURN_VALUE hal_spi_slave_send(struct_hal_spi_handle* ptr_spi_handle, uint8_t *ptr_tx_data, uint8_t size);
#endif 

#ifdef HAL_SPI_SLAVE_EXTENDED_FUNCTIONS_ENABLE
enum_HAL_SPI_RETURN_VALUE hal_spi_slave_send_blocking(struct_hal_spi_handle* ptr_spi_handle, uint8_t *ptr_tx_data, uint8_t size,
    uint32_t timeout);
#endif 

enum_HAL_SPI_RETURN_VALUE hal_spi_master_receive( struct_hal_spi_handle* ptr_spi_handle, uint8_t *ptr_rx_data, uint8_t size );

enum_HAL_SPI_RETURN_VALUE hal_spi_master_receive_blocking( struct_hal_spi_handle* ptr_spi_handle, uint8_t *ptr_rx_data, uint8_t size,
    uint32_t timeout );

#ifdef HAL_SPI_SLAVE_EXTENDED_FUNCTIONS_ENABLE
enum_HAL_SPI_RETURN_VALUE hal_spi_slave_receive(struct_hal_spi_handle* ptr_spi_handle, uint8_t *ptr_rx_data, uint8_t size);
#endif 

#ifdef HAL_SPI_SLAVE_EXTENDED_FUNCTIONS_ENABLE
enum_HAL_SPI_RETURN_VALUE hal_spi_slave_receive_blocking(struct_hal_spi_handle* ptr_spi_handle, uint8_t *ptr_rx_data, uint8_t size,
    uint32_t timeout);
#endif 

enum_HAL_SPI_RETURN_VALUE hal_spi_master_transfer( struct_hal_spi_handle* ptr_spi_handle, struct_hal_spi_frame* ptr_spi_frame );

enum_HAL_SPI_RETURN_VALUE hal_spi_master_transfer_blocking( struct_hal_spi_handle* ptr_spi_handle, struct_hal_spi_frame* ptr_spi_frame, uint32_t timeout );

enum_HAL_SPI_RETURN_VALUE hal_spi_slave_transfer( struct_hal_spi_handle* ptr_spi_handle, struct_hal_spi_frame* ptr_spi_frame );

enum_HAL_SPI_RETURN_VALUE hal_spi_slave_transfer_blocking( struct_hal_spi_handle* ptr_spi_handle, struct_hal_spi_frame* ptr_spi_frame,
    uint32_t timeout );

enum_HAL_SPI_RETURN_VALUE hal_spi_master_get_transfer_status( struct_hal_spi_handle* ptr_spi_handle );

enum_HAL_SPI_RETURN_VALUE hal_spi_slave_get_transfer_status( struct_hal_spi_handle* ptr_spi_handle );

enum_HAL_SPI_RETURN_VALUE hal_spi_master_set_delay( struct_hal_spi_handle* ptr_spi_handle, uint32_t delay_CS_to_SCK, uint32_t delay_SCK_to_CS, uint32_t delay_betwen_transfers );

#endif

