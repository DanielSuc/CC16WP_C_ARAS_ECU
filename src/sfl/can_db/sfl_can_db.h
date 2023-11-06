#ifndef SFL_CAN_DB_H
#define SFL_CAN_DB_H

#include "sfl_can_db_tables_data.h"



typedef enum
{
    SFL_CAN_OK                        = 0u,   
    SFL_CAN_ERROR_GENERAL                 ,   
    SFL_CAN_ERROR_DLC_INVALID             ,   
    SFL_CAN_ERROR_FIFO                    ,   

} enum_sfl_can_return_value_t;


typedef void (*callback_can_msg_receive_t)( uint8_t, bios_can_msg_typ* );


void sfl_can_db_rx_fifo_init( const uint8_t bus_id );

void sfl_can_db_tx_fifo_init( const uint8_t bus_id );

void sfl_can_db_tx_fifo_cyclic();

uint32_t sfl_can_db_tx_fifo_get_free( const uint8_t bus_id );

uint32_t sfl_can_db_tx_fifo_get_count( const uint8_t bus_id );

uint32_t sfl_can_db_rx_fifo_get_free( const uint8_t bus_id );

uint32_t sfl_can_db_rx_fifo_get_count( const uint8_t bus_id );

enum_sfl_can_return_value_t sfl_can_db_rx_fifo_remove(const uint8_t bus_id, const uint32_t count);

void sfl_can_db_tx_callback( const uint8_t instance );

uint32_t sfl_can_db_get_value( const uint32_t id );

void sfl_can_db_set_value( const uint32_t id, const uint32_t wert_int );

uint32_t sfl_can_db_get_value_on_change( const uint32_t id, uint8_t* const changed );

void sfl_can_db_set_transmit_flag( const uint32_t id );

uint8_t* sfl_can_db_get_block_ptr( const uint32_t id );

uint8_t sfl_can_db_block_received( const uint32_t id, const uint8_t reset );

uint8_t sfl_can_db_test_dp_value( const uint32_t id );

uint8_t sfl_can_db_block_expired(const uint32_t block_id);

uint8_t sfl_can_db_datapoint_expired(const uint32_t dp_id);


uint8_t sfl_bit_weight_32( uint32_t val );

uint8_t sfl_bit_weight_8( uint32_t val );

void sfl_os_can_copy_msg( const bios_can_msg_typ* src, bios_can_msg_typ* const dst );

enum_sfl_can_return_value_t sfl_can_db_rx_wrapper( const uint8_t p_bus_id, const struct_hal_can_frame_t* const ptr_can_msg );
void sfl_can_queue_in_process( void );

enum_SFL_FIFO_ERROR_CODES sfl_can_queue_in_process_bus( const uint8_t bus_id );

enum_sfl_can_return_value_t sfl_can_db_tx_wrapper( const uint8_t p_bus_id, const bios_can_msg_typ* const msg );

uint8_t sfl_can_db_gateway( const uint8_t bus_id, bios_can_msg_typ* const msg );

void sfl_can_input_block_to_db( const uint8_t bus_id, bios_can_msg_typ* const msg );

void sfl_can_process_block_timeouts( void );

void sfl_can_db_output_to_bus( void );

uint8_t sfl_can_db_stop_transmission( const uint8_t can_bus, const uint8_t status );

#define sfl_can_db_transmit_deactivate( status ) sfl_can_db_stop_transmission( (CAN_BUS_MAX), status )

uint8_t sfl_can_db_stop_gateway_for_known_ids( const uint8_t can_bus, const uint8_t status );

uint8_t sfl_can_db_stop_gateway_for_unknown_ids( const uint8_t can_bus, const uint8_t status );

enum_sfl_can_return_value_t sfl_can_send_message( const struct_hal_can_handle* ptr_can_handle, const uint32_t can_id, const uint8_t can_dlc, const uint8_t can_fd, const uint8_t can_fd_brs, const uint8_t* const data_buffer );
void set_callback_can_msg_receive( callback_can_msg_receive_t callback );

#endif


