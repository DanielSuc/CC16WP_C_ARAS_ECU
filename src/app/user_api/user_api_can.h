#ifndef SRC_USER_API_CAN_H_
#define SRC_USER_API_CAN_H_
#include <stdint.h>
#include "hal_can.h"
#include "can_db_tables.h"

typedef enum
{
    STANDARD_ID  = 0,   
    EXTENDED_ID         
}enum_CAN_ID_TYPE;

typedef enum
{
    CAN_BUS_OK  = 0,
    CAN_BUS_ERROR,
    CAN_BUS_OFF
}enum_CAN_ERROR_TYPE;

typedef struct
{
    enum_CAN_ERROR_TYPE last_state;         
    uint32_t esr1;                          
    uint32_t time_from_start_to_err_in_ms;  
}struct_error_watermark;

void user_can_module_rx();
#define user_can_db_clear_rx_buff() user_can_module_rx()

void user_can_db_process_tx( void );

enum_HAL_CAN_RETURN_VALUE user_can_msg_send(const uint8_t can_bus, const uint32_t can_id, const enum_CAN_ID_TYPE id_type, const uint8_t can_dlc, const uint8_t data_byte_0, const uint8_t data_byte_1, const uint8_t data_byte_2, const uint8_t data_byte_3, const uint8_t data_byte_4, const uint8_t data_byte_5, const uint8_t data_byte_6, const uint8_t data_byte_7);
#define user_can_send_msg( can_bus,can_id,id_type,can_dlc,data_byte_0,data_byte_1,data_byte_2,data_byte_3,data_byte_4,data_byte_5,data_byte_6,data_byte_7 ) user_can_msg_send( can_bus,can_id,id_type,can_dlc,data_byte_0,data_byte_1,data_byte_2,data_byte_3,data_byte_4,data_byte_5,data_byte_6,data_byte_7 )


enum_HAL_CAN_RETURN_VALUE user_can_msg_buffer_send(const uint8_t can_bus, const uint32_t can_id, const enum_CAN_ID_TYPE id_type, const uint8_t can_dlc, uint8_t *const data_buffer);
#define user_can_send_msg_buffer( can_bus,can_id,id_type,can_dlc,data_buffer ) user_can_msg_buffer_send( can_bus,can_id,id_type,can_dlc,data_buffer )

enum_HAL_CAN_RETURN_VALUE user_can_fd_msg_buffer_send(uint8_t can_bus, uint32_t can_id, enum_CAN_ID_TYPE id_type, uint8_t can_dlc, uint8_t can_fd_brs, uint8_t *const data_buffer);

void user_can_db_set_value(const uint32_t id, const uint32_t value_int);
#define user_can_db_set_signal_value( id,value_int ) user_can_db_set_value( id,value_int )


uint32_t user_can_db_get_value(const uint32_t id);
#define user_can_db_get_signal_value( id ) user_can_db_get_value( id )


uint8_t user_can_db_block_received(const uint32_t can_block_id, const uint8_t reset);


uint8_t user_can_db_test_dp_value(const uint32_t can_dp_id);


uint8_t user_can_db_block_expired(uint8_t block_id);


uint8_t user_can_db_datapoint_expired(uint8_t dp_id);

void user_can_db_send_dp(const uint32_t can_dp_id);
#define user_can_db_set_transmit_flag(...) user_can_db_send_dp(__VA_ARGS__)

uint8_t user_can_db_get_value_on_change(const uint32_t can_dp_id, uint32_t* const buffer_dp_value);

uint8_t user_can_db_stop_transmission(const uint8_t can_bus, const uint8_t status);


uint8_t user_can_db_transmit_deactivate( const uint8_t status );


uint8_t user_can_db_stop_gateway_for_known_ids( const uint8_t can_bus, const uint8_t status );


uint8_t user_can_db_stop_gateway_for_unknown_ids(const uint8_t can_bus, const uint8_t status);


void user_can_get_error(const uint8_t can_bus, struct_error_watermark* const watermark);

uint8_t user_can_set_bl_baudrate(uint8_t const baudrate);


#endif 


