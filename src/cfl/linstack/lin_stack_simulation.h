#ifndef INCLUDE_GUARD_LIN_STACK_SIMULATION_H_
#define INCLUDE_GUARD_LIN_STACK_SIMULATION_H_

#include "hal_data_types.h"
#include "lin_db_tables.h"
#include "sfl_db.h"






uint16_t lin_get_number_of_wakeup_messages_sent( void );
void lin_reset_number_of_wakeup_messages_sent( void );
void lin_simulation_receive_value( uint32_t datapoint_id, uint32_t set_value );
void lin_simulation_receive_value_64( uint32_t datapoint_id, uint64_t set_value );
void lin_simulation_receive_frame_request( uint8_t frame_index );

#endif 

