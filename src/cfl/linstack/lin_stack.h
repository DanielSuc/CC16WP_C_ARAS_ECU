#ifndef _LIN_STACK_H_
#define _LIN_STACK_H_



#include "hal_data_types.h"
#include "bit_access_macros.h"
#include "lin_db_tables.h"
#include "hal_lin.h"
#include "lin_diagnose.h"

#define MRS_LIN_STACK_SW_VERSION  "V0.1.0"

#define LIN_SLEEP_TIMEOUT	4000u

#if 0
typedef enum
{
    LIN30 = 0u, 
    LIN31 ,
    LIN32 ,
    LIN33 ,
    LIN34 ,
    LIN35 ,
    LIN25 ,
    LIN_MAX
}enum_LIN_UNIT;
#endif

typedef enum
{
    LIN_HANDLE_IDLE = 0,									
    LIN_HANDLE_HEADER_TRANSMISSION_ENABLED,					
    LIN_HANDLE_HEADER_RECEPTION,							
    LIN_HANDLE_RESPONSE_TRANSMISSION_ENABLED,				
    LIN_HANDLE_RESPONSE_RECEPTION_ENABLED,					
    LIN_HANDLE_MASTER_REQUEST_FRAME_TRANSMISSION_ENABLED	
} enum_lin_handle_state_types;

#if 0
typedef struct
{
    uint8_t trasmitted_header_id; 
    enum_lin_handle_state_types handle_state;
    uint32_t error_timestamp;
    struct_hal_lin_handle lin_handle;
}struct_lin_dyn_data;
#endif


#ifndef NULL_PTR
#define NULL_PTR ((void*)0)
#endif

#ifndef MRS_FAR
#define MRS_FAR	
#endif

#define LIN_WAKE_SIGNAL     (uint8_t)0xF0    
#define LIN_SYNC_SIGNAL     (uint8_t)0x55    

#define LIN_STATE_ERROR     (uint8_t)0x00
#define LIN_STATE_SUCCESS   (uint8_t)0x01

#define LIN_FRAME_LEN_MAX	((uint8_t)0x08)


typedef enum
{
    LIN_TX_FRAME_START_INTERRUPT = 0,
    LIN_TX_FRAME_START_IDLE
} enum_lin_tx_frame_start_types;

typedef enum
{
    LIN_HEADER_NO_ACK = 0u,               
    LIN_HEADER_ACK = 1u                
} enum_header_received_callback;

typedef enum_header_received_callback (*lin_header_received_callback_t)( const uint8_t lin_module, const uint8_t rx_header_id, const uint8_t frame_index );

typedef void (*lin_frame_received_callback_t)( const uint8_t lin_module, const struct_lin_rx_msg_type, const uint8_t frame_index );

typedef void (*lin_schedule_complete_callback_t)( const uint8_t lin_module, const uint8_t lin_schedule_table_index );

typedef void (*lin_frame_transmission_complete_callback_t)( const uint8_t lin_module, const uint8_t tx_header_id, const uint8_t frame_index );


extern lin_header_received_callback_t ext_lin_stack_header_received_cb_handler;
extern lin_frame_received_callback_t ext_lin_stack_frame_received_cb_handler;
extern lin_schedule_complete_callback_t ext_lin_stack_schedule_complete_cb_handler;
extern lin_frame_transmission_complete_callback_t ext_lin_stack_frame_transmission_complete_cb_handler;

void lin_init( void );

void lin_set_callback( lin_header_received_callback_t const ptr_lin_header_received_callback,
    lin_frame_received_callback_t const ptr_lin_frame_received_callback,
    lin_schedule_complete_callback_t const ptr_lin_schedule_complete_callback,
    lin_frame_transmission_complete_callback_t const ptr_lin_frame_transmission_complete_callback );

void lin_error_callback( uint8_t module, uint8_t lin_status );

void lin_module_disable( uint8_t lin_module );

void lin_send_wakeup( uint8_t lin_module );

void lin_send_go_to_sleep( uint8_t lin_module );

void lin_rx_frame_handling( uint8_t module, uint8_t data, uint8_t break_received );

void lin_ms_timer_handling( void );

uint8_t lin_crc_check( uint8_t lin_id_with_parity, uint8_t lin_length, uint8_t* lin_data_ptr, uint8_t lin_crc_to_check, uint8_t lin_crc_type );

uint8_t lin_crc_check_universal( uint8_t lin_id_with_parity, uint8_t lin_length, uint8_t* lin_data_ptr, uint8_t lin_crc_to_check );

uint8_t lin_calculate_crc_value( uint8_t lin_frame_index );

void lin_tx_frame_handling( uint8_t module );

uint32_t lin_db_get_value( uint32_t datapoint_id );

void lin_db_set_value( uint32_t datapoint_id, uint32_t set_value );

void lin_schedule_handling( uint8_t lin_schedule_table_index, uint8_t lin_st_active );

void lin_schedule_handling_reset( uint8_t lin_schedule_table_index );

void lin_queue_in_process( void );

void lin_gateway_handling( uint8_t lin_module_in, uint8_t frame_id );

void lin_gateway_req_data_process( uint8_t frame_dest_index, uint8_t frame_src_index );

void lin_gateway_resp_data_process( uint8_t frame_dest_index, uint8_t frame_src_index );

uint8_t lin_check_for_received_response_frame( uint8_t frame_index );

#define lin_check_for_received_header(x)		lin_check_for_received_response_frame(x)

uint8_t lin_check_for_received_request_frame( uint8_t frame_index );

uint8_t lin_check_for_received_frame( uint8_t lin_module, uint8_t frame_index, uint8_t reset );

bool lin_check_for_received_frame_reworked( enum_lin_dp_id frame_index, bool reset );

void lin_clear_response_frame_flag( uint8_t frame_index );

#define lin_enable_frame_transmission(x) 	lin_clear_response_frame_flag(x)

void lin_clear_request_frame_flag( uint8_t frame_index );

uint8_t lin_ma_check_frame_resp_timeout( uint8_t frame_index );

void lin_header_received_ack( uint16_t frame_index );

uint16_t lin_get_lin_frame_index( uint8_t lin_module, uint8_t lin_id );

#endif


