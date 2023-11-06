#ifndef _CAN_APP_H_
#define _CAN_APP_H_
#include "hal_can.h"
#include "flexcan_hw_access.h"
#include "sfl_can_db_tables_data.h"


typedef struct
{
    uint32_t time_from_start_to_error;
    uint32_t last_can_error;
} struct_can_app_error;

typedef struct {
    uint16_t can_en_pin;      
    uint16_t can_stb_pin;     
} struct_can_pin_list;


void user_can_init(const struct_can_pin_list ptr_can_pin_list[]);


uint32_t user_can_fd_calculate_baudrate(uint32_t arb_baud, uint32_t arb_sample_pt, uint32_t data_baud, uint32_t data_sample_pt, hal_can_time_segment* arb_phase, hal_can_time_segment* data_phase );

void user_can_set_baudrate(uint8_t interface, uint8_t can_fd_en, enum_HAL_CAN_BAUDRATE baudrate, hal_can_time_segment arb_phase, hal_can_time_segment data_phase);

void ext_get_filter_and_mask(can_db_filter_typ filter[]);

#endif


