#include "user_api_can.h"
#include "user_api_eeprom.h"
#include "sfl_can_db.h"
#include "modulhardwarecode.h"
#include "can_app.h"
#include "sfl_bl_protocol_s32k.h"



extern volatile struct_can_app_error can_error_handle[];

static enum_HAL_CAN_RETURN_VALUE sfl_to_hal_err(enum_sfl_can_return_value_t err);

void user_can_module_rx( void ){
	sfl_can_queue_in_process();
}

void user_can_db_process_tx( void )
{
    sfl_can_db_output_to_bus();
}

enum_HAL_CAN_RETURN_VALUE user_can_msg_send(const uint8_t can_bus, const uint32_t can_id, const enum_CAN_ID_TYPE id_type, const uint8_t can_dlc, const uint8_t data_byte_0, const uint8_t data_byte_1, const uint8_t data_byte_2, const uint8_t data_byte_3, const uint8_t data_byte_4, const uint8_t data_byte_5, const uint8_t data_byte_6, const uint8_t data_byte_7)
{
    enum_HAL_CAN_RETURN_VALUE err = HAL_CAN_ERROR_GENERAL;
    enum_sfl_can_return_value_t sfl_can_err = SFL_CAN_ERROR_GENERAL;

    uint32_t can_id_complete = ( (can_id & ~(1<<31)) | (id_type<<31) );

    uint8_t data_buffer[8] = {0};
    data_buffer[0] = data_byte_0;
    data_buffer[1] = data_byte_1;
    data_buffer[2] = data_byte_2;
    data_buffer[3] = data_byte_3;
    data_buffer[4] = data_byte_4;
    data_buffer[5] = data_byte_5;
    data_buffer[6] = data_byte_6;
    data_buffer[7] = data_byte_7;

    if (NULL != can_handle[can_bus].can_handle_ptr)
    {
        sfl_can_err = sfl_can_send_message(&can_handle[can_bus], can_id_complete, can_dlc, 0, 0, data_buffer);
    }

    err = sfl_to_hal_err(sfl_can_err);

    return err;
}

enum_HAL_CAN_RETURN_VALUE user_can_msg_buffer_send(const uint8_t can_bus, const uint32_t can_id, const enum_CAN_ID_TYPE id_type, const uint8_t can_dlc, uint8_t *const data_buffer)
{
    enum_HAL_CAN_RETURN_VALUE err = HAL_CAN_ERROR_GENERAL;
    enum_sfl_can_return_value_t sfl_can_err = SFL_CAN_ERROR_GENERAL;

    uint32_t temp_id;

    temp_id = ( (can_id & ~(1<<31)) | (id_type<<31) );

    if (NULL != can_handle[can_bus].can_handle_ptr)
    {
        sfl_can_err = sfl_can_send_message( &can_handle[can_bus], temp_id, can_dlc, 0, 0, data_buffer);
    }

    err = sfl_to_hal_err(sfl_can_err);

    return err;
}

enum_HAL_CAN_RETURN_VALUE user_can_fd_msg_buffer_send(uint8_t can_bus, uint32_t can_id, enum_CAN_ID_TYPE id_type, uint8_t can_dlc, uint8_t can_fd_brs, uint8_t *const data_buffer)
{
    enum_HAL_CAN_RETURN_VALUE err = HAL_CAN_ERROR_GENERAL;
    enum_sfl_can_return_value_t sfl_can_err = SFL_CAN_ERROR_GENERAL;

    can_id = ( (can_id & ~(1<<31)) | (id_type<<31) );

    if (NULL != can_handle[can_bus].can_handle_ptr)
    {
        sfl_can_err = sfl_can_send_message( &can_handle[can_bus], can_id, can_dlc, 1, can_fd_brs, data_buffer);
    }

    err = sfl_to_hal_err(sfl_can_err);

    return err;
}

void user_can_db_set_value(const uint32_t id, const uint32_t value_int)
{
    sfl_can_db_set_value(id, value_int);
}

uint32_t user_can_db_get_value(const uint32_t id)
{
    return sfl_can_db_get_value(id);
}

uint8_t user_can_db_block_received(const uint32_t can_block_id, const uint8_t reset)
{
    return sfl_can_db_block_received( can_block_id, reset );
}

uint8_t user_can_db_test_dp_value(const uint32_t can_dp_id)
{
    return sfl_can_db_test_dp_value( can_dp_id );
}

uint8_t user_can_db_block_expired(uint8_t block_id)
{
    return sfl_can_db_block_expired( block_id );
}

uint8_t user_can_db_datapoint_expired(uint8_t dp_id)
{
    return sfl_can_db_datapoint_expired( dp_id );
}

void user_can_db_send_dp(const uint32_t can_dp_id)
{
    sfl_can_db_set_transmit_flag( can_dp_id );
}

uint8_t user_can_db_get_value_on_change(const uint32_t can_dp_id, uint32_t* const buffer_dp_value)
{
    uint8_t changed = 0;
    uint8_t ret_val;

    *buffer_dp_value = sfl_can_db_get_value_on_change(can_dp_id, &changed);

    if (!changed)
    {
        ret_val = 0;
    }
    else
    {
        ret_val = 1;
    }

    return ret_val;
}

uint8_t user_can_db_transmit_deactivate( const uint8_t status )
{
    return sfl_can_db_transmit_deactivate( status );
}

uint8_t user_can_db_stop_transmission(const uint8_t can_bus, const uint8_t status)
{
    return sfl_can_db_stop_transmission( can_bus, status );
}

uint8_t user_can_db_stop_gateway_for_known_ids( const uint8_t can_bus, const uint8_t status )
{
    return sfl_can_db_stop_gateway_for_known_ids( can_bus, status );

}

uint8_t user_can_db_stop_gateway_for_unknown_ids(const uint8_t can_bus, const uint8_t status)
{
    return sfl_can_db_stop_gateway_for_unknown_ids( can_bus, status );
}

void user_can_get_error(uint8_t can_bus, struct_error_watermark* const watermark)
{

    const uint32_t esr1 = can_error_handle[can_bus].last_can_error;
    const uint32_t err_masks = (CAN_ESR1_ERRINT_MASK | CAN_ESR1_RXWRN_MASK | CAN_ESR1_TXWRN_MASK);

    watermark->esr1 = esr1;
    watermark->time_from_start_to_err_in_ms = can_error_handle[can_bus].time_from_start_to_error;

    if(esr1 & CAN_ESR1_BOFFINT_MASK )
    {
        watermark->last_state = CAN_BUS_OFF;
    }
    else if ( esr1 & err_masks )
    {
        watermark->last_state = CAN_BUS_ERROR;
    }
    else
    {
        watermark->last_state = CAN_BUS_OK;
    }
}

uint8_t user_can_set_bl_baudrate(uint8_t const baudrate)
{
    static uint8_t ret;
    uint16_t interface = user_eeprom_read_bl_can_bus(); 

    if ( (baudrate > HAL_CAN_BAUD_INVALID) && (baudrate < HAL_CAN_BAUD_MAX) )
    {
        hal_can_set_baudrate(&can_handle[interface], baudrate);
    	uint8_t tmp_baudrate = sfl_can_db_tables_convert_baud(baudrate,  1);
        ret = sfl_bl_protocol_s32k_set_baudrate(&can_handle[interface], tmp_baudrate);
    }
    else
    {
        ret = HAL_CAN_BAUD_INVALID;
    }
    return ret;
}

static enum_HAL_CAN_RETURN_VALUE sfl_to_hal_err(enum_sfl_can_return_value_t err)
{
    if (err != SFL_CAN_OK) 
    {
        if (err == SFL_CAN_ERROR_DLC_INVALID) 
        {
            return HAL_CAN_ERROR_DLC_INVALID;
        } 
        else 
        {
            return HAL_CAN_ERROR_WHILE_WRITING;
        }
    } 
    else 
    {
        return HAL_CAN_OK;
    }
}














