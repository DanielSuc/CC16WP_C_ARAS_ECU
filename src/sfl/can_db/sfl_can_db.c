
#include "sfl_db.h"
#include "sfl_can_db.h"
#include "sfl_bl_protocol.h"


uint32_t Save_can_db_test_dp_value = 0;
extern volatile const can_datenpunkt_db_const_typ can_datenpunkt_db_const[];
extern can_block_db_ram_typ can_block_db_ram[];
extern volatile const can_block_db_const_typ can_block_db_const[];
extern can_db_typ can_db;
extern volatile const can_gateway_db_const_typ can_gateway_db_const[];
extern volatile const can_bus_db_const_typ can_bus_db_const[];

static callback_can_msg_receive_t callback_can_msg_receive = NULL_PTR;

void sfl_can_db_rx_fifo_init( const uint8_t bus_id )
{
    sfl_fifo_init( can_fifo_config_actual[bus_id]->rx_fifo_config, can_fifo_config_actual[bus_id]->rx_fifo_size, sizeof(struct_sfl_can_fifo_frame) );
}

void sfl_can_db_tx_fifo_init( const uint8_t bus_id )
{
    sfl_fifo_init( can_fifo_config_actual[bus_id]->tx_fifo_config, can_fifo_config_actual[bus_id]->tx_fifo_size, sizeof(struct_sfl_can_fifo_frame) );
}

void sfl_can_db_tx_fifo_cyclic()
{
    volatile uint8_t interface = 0;

    for( interface = 0; interface < CAN_BUS_MAX; interface++ )
    {
        sfl_can_db_tx_callback( interface );
    }
}

uint32_t sfl_can_db_tx_fifo_get_free( const uint8_t bus_id )
{
    return sfl_fifo_get_free( can_fifo_config_actual[bus_id]->tx_fifo_config );
}

uint32_t sfl_can_db_tx_fifo_get_count( const uint8_t bus_id )
{
    return sfl_fifo_get_count( can_fifo_config_actual[bus_id]->tx_fifo_config );
}

uint32_t sfl_can_db_rx_fifo_get_free( const uint8_t bus_id )
{
    return sfl_fifo_get_free( can_fifo_config_actual[bus_id]->rx_fifo_config );
}

uint32_t sfl_can_db_rx_fifo_get_count( const uint8_t bus_id )
{
    return sfl_fifo_get_count( can_fifo_config_actual[bus_id]->rx_fifo_config );
}

enum_sfl_can_return_value_t sfl_can_db_rx_fifo_remove(const uint8_t bus_id, const uint32_t count)
{
    enum_sfl_can_return_value_t err = SFL_CAN_ERROR_GENERAL;
    enum_SFL_FIFO_ERROR_CODES sfl_fifo_err = SFL_FIFO_ERROR_UNKNOWN;

	sfl_fifo_err = sfl_fifo_remove(can_fifo_config_actual[bus_id]->rx_fifo_config, count);

    if (sfl_fifo_err != SFL_FIFO_ERROR_NONE) 
    {
        err = SFL_CAN_ERROR_FIFO;
    } 
    else 
    {
        err = SFL_CAN_OK;
    }
    return err;
}

void sfl_can_db_tx_callback( const uint8_t instance )
{
    enum_SFL_FIFO_ERROR_CODES sfl_fifo_err = SFL_FIFO_ERROR_UNKNOWN;
    struct_hal_can_handle temp_can_handle;
    temp_can_handle.can_handle_number = instance;
    struct_hal_can_frame_t hal_can_msg;

    hal_sys_disable_all_interrupts();
    sfl_fifo_err = sfl_fifo_get_preview( can_fifo_config_actual[instance]->tx_fifo_config, (uint8_t*) &hal_can_msg, (uint8_t*) can_fifo_config_actual[instance]->ptr_tx_fifo_buffer );
    if( sfl_fifo_err == SFL_FIFO_ERROR_NONE )
    { 
        if( hal_can_send( &temp_can_handle, &hal_can_msg ) == HAL_CAN_OK )
        {
            sfl_fifo_remove( can_fifo_config_actual[instance]->tx_fifo_config, 1 );
        }
    }
    else
    {   
    }
    hal_sys_enable_all_interrupts();
}

uint32_t sfl_can_db_get_value( const uint32_t id )
{
    can_datenpunkt_db_const_typ dp = can_datenpunkt_db_const[id];

    return sfl_db_get_signal_value_from_data_block(can_block_db_ram[dp.nr_can_block].msg.data, dp.pos_bit_0, dp.bit_laenge, dp.data_format, dp.datentyp);
}

void sfl_can_db_set_value( const uint32_t id, const uint32_t wert_int )
{
    can_datenpunkt_db_const_typ dp = can_datenpunkt_db_const[id];

    sfl_db_put_signal_value_to_data_block( wert_int, can_block_db_ram[dp.nr_can_block].msg.data, dp.pos_bit_0, dp.bit_laenge, dp.data_format );
}

uint32_t sfl_can_db_get_value_on_change( const uint32_t id, uint8_t* const changed )
{
    uint32_t u_long, last;
    uint8_t i = 0;

    can_datenpunkt_db_const_typ dp = can_datenpunkt_db_const[id];
    u_long = sfl_db_get_signal_value_from_data_block(can_block_db_ram[dp.nr_can_block].msg.data, dp.pos_bit_0, dp.bit_laenge, dp.data_format, ULONG);
    last = sfl_db_get_signal_value_from_data_block(can_block_db_ram[dp.nr_can_block].last_data, dp.pos_bit_0, dp.bit_laenge, dp.data_format, ULONG);
    *changed = (u_long != last);

    if( *changed )
    {
        while( i < 8 )
        {
            can_block_db_ram[dp.nr_can_block].last_data[i] = can_block_db_ram[dp.nr_can_block].msg.data[i];
            ++i;
        }
    }
    return u_long;
}

void sfl_can_db_set_transmit_flag( const uint32_t id )
{
    can_datenpunkt_db_const_typ dp = can_datenpunkt_db_const[id];

    if( can_block_db_const[dp.nr_can_block].tx == 1 )
    {
        can_block_db_ram[dp.nr_can_block].transmit = 1;
    }
}

uint8_t* sfl_can_db_get_block_ptr( const uint32_t id )
{
    return can_block_db_ram[id].msg.data;
}

uint8_t sfl_can_db_block_received( const uint32_t id, const uint8_t reset )
{   
    uint8_t retval = can_block_db_ram[id].received;

    if( reset )
    {
        can_block_db_ram[id].received = 0;
    }
    return retval;
}

uint8_t sfl_can_db_test_dp_value( const uint32_t id )
{
    uint8_t ret = 0;    
    uint32_t u_long;

    can_datenpunkt_db_const_typ dp = can_datenpunkt_db_const[id];

    if( sfl_can_db_block_received( dp.nr_can_block, 1 ) == 1 )
    {
        u_long = sfl_db_get_signal_value_from_data_block(can_block_db_ram[dp.nr_can_block].msg.data, dp.pos_bit_0, dp.bit_laenge, dp.data_format, dp.datentyp);

        if( u_long != Save_can_db_test_dp_value )
        {
            ret = 2;
        }
        else
        {
            ret = 1;
        }
        Save_can_db_test_dp_value = u_long;
    }
    return ret;
}

uint8_t sfl_can_db_block_expired(const uint32_t block_id)
{
    if ( (block_id < dyn_CAN_BLOCK_MAX) && can_block_db_const[block_id].timeout_ms > 0)
    {
        return can_block_db_ram[block_id].expired;
    }
    else
    {
        return 0;
    }
}

uint8_t sfl_can_db_datapoint_expired(const uint32_t dp_id)
{
    uint8_t block_id = can_datenpunkt_db_const[dp_id].nr_can_block;
    return sfl_can_db_block_expired(block_id);
}

uint8_t sfl_bit_weight_32( uint32_t val )
{
    uint8_t i = 32, retval = 0;

    while( i-- > 0 )
    {
        if( val & 1 )
        {
            ++retval;
        }
        val = val >> 1;
    }
    return retval;
}

uint8_t sfl_bit_weight_8( uint32_t val )
{
    uint8_t i = 8, retval = 0;

    while( i-- > 0 )
    {
        if( val & 1 )
        {
            ++retval;
        }

        val = val >> 1;
    }
    return retval;
}

void sfl_os_can_copy_msg( const bios_can_msg_typ* const src, bios_can_msg_typ* const dst )
{

    dst->id = src->id;
    dst->id_ext = src->id_ext;
    dst->remote_tx = src->remote_tx;
    dst->len = src->len;
    dst->prty = src->prty;
    dst->can_fd = src->can_fd;
    dst->can_fd_brs = src->can_fd_brs;

    memcpy( &dst->data, &src->data, src->len );
}

enum_sfl_can_return_value_t sfl_can_db_rx_wrapper( const uint8_t p_bus_id, const struct_hal_can_frame_t* const ptr_can_msg )
{
    enum_SFL_FIFO_ERROR_CODES retval;
    enum_sfl_can_return_value_t err = SFL_CAN_ERROR_GENERAL;

    retval = sfl_fifo_put( can_fifo_config_actual[p_bus_id]->rx_fifo_config, (uint8_t*) ptr_can_msg, (uint8_t*) can_fifo_config_actual[p_bus_id]->ptr_rx_fifo_buffer);
    if(retval != SFL_FIFO_ERROR_NONE) 
    {
        err = SFL_CAN_ERROR_FIFO;
    } 
    else 
    {
        err = SFL_CAN_OK;
    }
    return err;
}

void sfl_can_queue_in_process( void )
{
    uint8_t instance = 0;

    for( instance = 0; instance < can_db.BUS_MAX; instance++ )
    {
        sfl_can_queue_in_process_bus( instance );
    }

    sfl_can_process_block_timeouts();
}

enum_SFL_FIFO_ERROR_CODES sfl_can_queue_in_process_bus( const uint8_t bus_id )
{
    enum_SFL_FIFO_ERROR_CODES retval = SFL_FIFO_ERROR_UNKNOWN;
    bios_can_msg_typ temp_can_msg_typ;
    struct_sfl_can_fifo_frame temp_can_msg;

    for( uint16_t i = 0; i < can_fifo_config_actual[bus_id]->rx_fifo_config->max; i++)
    {
		retval = sfl_fifo_get( can_fifo_config_actual[bus_id]->rx_fifo_config, (uint8_t*) &temp_can_msg, (uint8_t*) can_fifo_config_actual[bus_id]->ptr_rx_fifo_buffer );
		if( retval == SFL_FIFO_ERROR_NONE )
		{
			temp_can_msg_typ.id = temp_can_msg.header.can_id & 0x7FFFFFFF;
			temp_can_msg_typ.id_ext = ( ( temp_can_msg.header.can_id >> 31 ) & 0x1 );
			temp_can_msg_typ.len = hal_can_dlc_to_len( temp_can_msg.header.can_dlc );
			temp_can_msg_typ.can_fd = temp_can_msg.header.can_fd;
			temp_can_msg_typ.can_fd_brs = temp_can_msg.header.can_fd_brs;
			memcpy( temp_can_msg_typ.data, temp_can_msg.data, temp_can_msg_typ.len );
			sfl_can_input_block_to_db( bus_id, &temp_can_msg_typ );
		}
		else if( retval == SFL_FIFO_ERROR_EMPTY )
		{
			break;
		}
		else
		{
		}
    }

    return retval;
}

enum_sfl_can_return_value_t sfl_can_db_tx_wrapper( const uint8_t p_bus_id, const bios_can_msg_typ* const msg )
{
    struct_sfl_can_fifo_frame l_can_msg;
    enum_SFL_FIFO_ERROR_CODES retval;
    enum_sfl_can_return_value_t err = SFL_CAN_ERROR_GENERAL;

    l_can_msg.header.can_id = msg->id | ( (uint32_t) msg->id_ext << 31 );
    l_can_msg.header.can_dlc = hal_can_len_to_dlc( msg->len );
    l_can_msg.header.can_fd = msg->can_fd;
    l_can_msg.header.can_fd_brs = msg->can_fd_brs;

    memcpy( l_can_msg.data, msg->data, msg->len );

    retval = sfl_fifo_put( can_fifo_config_actual[p_bus_id]->tx_fifo_config, (uint8_t*) &l_can_msg, (uint8_t*) can_fifo_config_actual[p_bus_id]->ptr_tx_fifo_buffer);
    if ( retval != SFL_FIFO_ERROR_NONE ) 
    {   
        err = SFL_CAN_ERROR_FIFO;
    } 
    else 
    {
        err = SFL_CAN_OK;
    }
    return err;
}

uint8_t sfl_can_db_gateway( const uint8_t bus_id, bios_can_msg_typ* const msg )
{
    uint8_t i; 
    enum_sfl_can_return_value_t error = SFL_CAN_OK;

    for( i = 0; i < CAN_GATEWAY_DB_MAX; ++i )
    {
        if( bus_id == can_gateway_db_const[i].bus_id_in )
        {

            error = sfl_can_db_tx_wrapper( can_bus_db_const[can_gateway_db_const[i].bus_id_out].hw_module_id, msg );

            if( error != SFL_CAN_OK )
            {
            }
        }
    }

    return ( error != SFL_CAN_OK );
}

void sfl_can_input_block_to_db( const uint8_t bus_id, bios_can_msg_typ* const msg )
{
    uint8_t i;
    uint32_t tmp_mask;
    enum_sfl_can_return_value_t send_error = SFL_CAN_ERROR_GENERAL;

    for( i = 0; i < dyn_CAN_BLOCK_MAX; i++ )
    {
        if( bus_id == can_block_db_const[i].bus_id && can_block_db_const[i].tx == 0 && msg->id_ext == can_block_db_const[i].can_id_ext )
        {
            tmp_mask = ~can_block_db_const[i].can_id_mask;

            if( ( msg->id == can_block_db_const[i].can_id ) || ( can_block_db_const[i].can_id_mask && ( ( msg->id & tmp_mask ) == ( can_block_db_const[i].can_id & tmp_mask ) ) ) )
            {
                if (!can_block_db_const[i].mux_length || (sfl_db_get_signal_value_from_data_block(&msg->data[0], can_block_db_const[i].mux_start, can_block_db_const[i].mux_length, DF_INTEL, ULONG) == can_block_db_const[i].mux_val))
                {
                    if( ( can_db.sa_active && msg->id_ext && ( can_block_db_const[i].can_id & 0xFF00 ) == can_db.sa_db_rx && ( msg->id & 0xFF00 ) != can_db.sa_val_rx ) == FALSE )
                    {
                        if( ( NONE ) != can_block_db_const[i].can_bus_gw )
                        {
                            if( ( FALSE ) == can_block_db_ram[i].stop_gw_known_ids )
                            {
                                send_error = sfl_can_db_tx_wrapper( can_block_db_const[i].can_bus_gw, msg );
                                if( send_error != SFL_CAN_OK )
                                {
                                }
                                else
                                {
                                }
                            }
                        }
                        else
                        {
                            sfl_timer_set_timestamp( &can_block_db_ram[i].time_stamp_read, HAL_PRECISION_1MS );
                            can_block_db_ram[i].received = 1;
                            can_block_db_ram[i].expired = 0;
                            can_block_db_ram[i].failsafe = 0;
                        }
                        sfl_os_can_copy_msg( msg, &( can_block_db_ram[i].msg ) );
                        break;
                    }
                }
            }
        }

    }

    if( ( ( IS_GW_INPUT ) == can_bus_db_const[bus_id].gw_input ) && ( ( dyn_CAN_BLOCK_MAX ) == i ) )
    {
        if( ( FALSE ) == ext_sfl_can_stop_gw_unknown_ids[bus_id] )
        {
            (void) sfl_can_db_gateway( bus_id, msg );
        }
        else
        {
        }
    }

    if( callback_can_msg_receive != NULL_PTR )
    {
        callback_can_msg_receive( bus_id, msg );
    }
}

void sfl_can_process_block_timeouts( void )
{
    uint32_t elapsed_time;
    uint8_t i;

    for (i = 0; i < dyn_CAN_BLOCK_MAX; i++)
    {
        if (can_block_db_const[i].timeout_ms > 0 && can_block_db_const[i].tx == 0 && can_block_db_ram[i].expired == 0)
        {
            sfl_timer_get_time_elapsed(&elapsed_time, can_block_db_ram[i].time_stamp_read, HAL_PRECISION_1MS);

            if (elapsed_time >= can_block_db_const[i].timeout_ms)
            {
                can_block_db_ram[i].expired = 1;
                can_block_db_ram[i].failsafe = 1;
                can_block_db_ram[i].received = 0;

                for (uint8_t dp_id = 0; dp_id < dyn_CAN_DP_MAX; dp_id++)
                {
                    can_datenpunkt_db_const_typ dp = can_datenpunkt_db_const[dp_id];
                    if (dp.nr_can_block == i)
                    {
                        sfl_db_put_signal_value_to_data_block(dp.init_value, can_block_db_ram[i].msg.data, dp.pos_bit_0, dp.bit_laenge, dp.data_format);
                    }
                }
            }
        }
    }
}


void sfl_can_db_output_to_bus( void )
{

    uint16_t d, flag_senden;
    uint8_t dlc, t_elapsed;

    for( uint32_t counter = 0; counter < dyn_CAN_BLOCK_MAX; ( counter )++ )
    {
        if( can_block_db_const[counter].tx && !can_block_db_ram[counter].transmit_stop )
        {
            flag_senden = 0;
            dlc = hal_can_dlc_to_len( can_block_db_const[counter].msg_len_dlc );

            if( can_block_db_ram[counter].transmit == 1 )
            {
                if( sfl_timer_time_elapsed( &t_elapsed, can_block_db_ram[counter].time_stamp_transmit, 10, HAL_PRECISION_1MS ) == SFL_TIMER_ERR_OK && t_elapsed == TRUE )
                {
                    sfl_timer_set_timestamp( &can_block_db_ram[counter].time_stamp_transmit, HAL_PRECISION_1MS );
                    flag_senden = 1; 
                }
            }
            if( can_block_db_const[counter].zykluszeit_ms_max || flag_senden == 1 ) 
            {
                if( sfl_timer_time_elapsed( &t_elapsed, can_block_db_ram[counter].time_stamp_write, can_block_db_const[counter].zykluszeit_ms_max, HAL_PRECISION_1MS )
                    == SFL_TIMER_ERR_OK && t_elapsed == TRUE )
                {
                    flag_senden = 1; 
                }
                else if( sfl_timer_time_elapsed( &t_elapsed, can_block_db_ram[counter].time_stamp_write, can_block_db_const[counter].zykluszeit_ms_min, HAL_PRECISION_1MS )
                    == SFL_TIMER_ERR_OK && t_elapsed == TRUE )
                {
                    for( d = 0; d < dlc; d++ )
                        if( can_block_db_ram[counter].msg.data[d] != can_block_db_ram[counter].last_data[d] )
                            break;
                    if( d < dlc )
                        flag_senden = 1;  
                }

                if( flag_senden )
                {
                    can_block_db_ram[counter].msg.id = can_block_db_const[counter].can_id;

                    if( can_db.sa_active && can_block_db_const[counter].can_id_ext && ( can_block_db_const[counter].can_id & 0xFF ) == can_db.sa_db )
                    {
                        can_block_db_ram[counter].msg.id = ( can_block_db_ram[counter].msg.id & 0xFFFFFF00 ) | can_db.sa_val;
                    }

                    can_block_db_ram[counter].msg.id_ext = can_block_db_const[counter].can_id_ext % 2;  
                    can_block_db_ram[counter].msg.len = dlc;

                    if( can_bus_db_const[can_block_db_const[counter].bus_id].can_fd_capability )
                    {
                        if( (can_block_db_const[counter].can_id_ext == 2) || (can_block_db_const[counter].can_id_ext == 3) ) 
                        {
                            can_block_db_ram[counter].msg.can_fd = TRUE;
                            can_block_db_ram[counter].msg.can_fd_brs = can_block_db_const[counter].can_fd_brs;
                        }
                        else
                        {
                        }
                    }
                    else
                    {
                    }


                    enum_sfl_can_return_value_t debug_err = sfl_can_db_tx_wrapper( can_block_db_const[counter].bus_id, &can_block_db_ram[counter].msg );
                    if( debug_err == SFL_CAN_OK )
                    {
                        can_block_db_ram[counter].transmit = 0; 
                        for( d = 0; d < dlc; d++ )
                        {
                            can_block_db_ram[counter].last_data[d] = can_block_db_ram[counter].msg.data[d];
                        }

                        sfl_timer_set_timestamp( &can_block_db_ram[counter].time_stamp_write, HAL_PRECISION_1MS );
                    }
                    else
                    {
                    }
                }
            }
        }
    }

    sfl_can_db_tx_fifo_cyclic();
}

uint8_t sfl_can_db_stop_transmission( const uint8_t can_bus, const uint8_t status )
{
    uint8_t idx;
    uint8_t local_tx_status;
    uint8_t ret_err;

    local_tx_status = 0xFFu;
    ret_err = ( FALSE );

    if( can_bus > ( dyn_CAN_BUS_MAX ) )
    {
        ret_err = ( TRUE );
    }
    else
    {
        for( idx = 0u; idx < ( dyn_CAN_BLOCK_MAX ); idx++ )
        {
            if( 0u != can_block_db_const[idx].tx )
            {
                if( can_bus == ( dyn_CAN_BUS_MAX ) )
                {
                    local_tx_status = (uint8_t) status;
                }
                else
                {
                    if( can_bus == can_block_db_const[idx].bus_id )
                    {
                        local_tx_status = status;
                    }
                    else
                    {
                    }
                }
            }
            else
            {
            }

            if( 0xFFu != local_tx_status )
            {
                can_block_db_ram[idx].transmit_stop = local_tx_status;
            }
            else
            {
            }

            local_tx_status = 0xFFu;
        }
    }

    return ret_err;
}

uint8_t sfl_can_db_stop_gateway_for_known_ids( const uint8_t can_bus, const uint8_t status )
{
    uint8_t idx;
    uint8_t local_gw_status;
    uint8_t ret_err;

    local_gw_status = 0xFFu;
    ret_err = ( FALSE );

    if( can_bus > ( dyn_CAN_BUS_MAX ) )
    {
        ret_err = ( TRUE );
    }
    else
    {
        for( idx = 0u; idx < ( dyn_CAN_BLOCK_MAX ); idx++ )
        {
            if( ( NONE ) != can_block_db_const[idx].can_bus_gw )
            {
                if( can_bus == ( dyn_CAN_BUS_MAX ) )
                {
                    local_gw_status = status;
                }
                else
                {
                    if( can_bus == can_block_db_const[idx].bus_id )
                    {
                        local_gw_status = status;
                    }
                    else
                    {
                    }
                }
            }
            else
            {
            }

            if( 0xFFu != local_gw_status )
            {
                can_block_db_ram[idx].stop_gw_known_ids = local_gw_status;
            }
            else
            {
            }

            local_gw_status = 0xFFu;
        }
    }

    return ret_err;
}

uint8_t sfl_can_db_stop_gateway_for_unknown_ids( const uint8_t can_bus, const uint8_t status )
{
    uint8_t idx;
    uint8_t local_gw_status;
    uint8_t ret_err;

    local_gw_status = 0xFFu;
    ret_err = ( FALSE );

    if( can_bus > ( dyn_CAN_BUS_MAX ) )
    {
        ret_err = ( TRUE );
    }
    else
    {
        for( idx = 0u; idx < ( dyn_CAN_BUS_MAX ); idx++ )
        {
            if( can_bus == ( dyn_CAN_BUS_MAX ) )
            {
                local_gw_status = status;
            }
            else
            {
                if( can_bus == idx )
                {
                    local_gw_status = status;
                }
                else
                {
                }
            }

            if( 0xFFu != local_gw_status )
            {
                ext_sfl_can_stop_gw_unknown_ids[idx] = local_gw_status;
            }
            else
            {
            }

            local_gw_status = 0xFFu;
        }
    }

    return ret_err;
}

enum_sfl_can_return_value_t sfl_can_send_message( const struct_hal_can_handle* ptr_can_handle, const uint32_t can_id, const uint8_t can_dlc, const uint8_t can_fd, const uint8_t can_fd_brs, const uint8_t* const data_buffer )
{
    bios_can_msg_typ can_tx_msg;
    enum_sfl_can_return_value_t ret_val = SFL_CAN_ERROR_GENERAL;

    can_tx_msg.id = can_id;
    can_tx_msg.id_ext = ( ( can_id >> 31 ) & 0x1 ); 
    can_tx_msg.len = hal_can_dlc_to_len( can_dlc );
    can_tx_msg.can_fd = can_fd;
    can_tx_msg.can_fd_brs = can_fd_brs;

    memset( can_tx_msg.data, 0, sizeof( can_tx_msg.data ) / sizeof(uint8_t) );
    memcpy( can_tx_msg.data, data_buffer, can_tx_msg.len );

    uint8_t sfl_max_payload_size = 0;
    if( !can_fd )
    {
        sfl_max_payload_size = SFL_CAN_CLASSIC_PAYLOAD_SIZE;
    }
    else
    {
        sfl_max_payload_size = SFL_CAN_FD_PAYLOAD_SIZE;
    }

    if( can_tx_msg.len <= sfl_max_payload_size )
    {
        ret_val = sfl_can_db_tx_wrapper( ptr_can_handle->can_handle_number, &can_tx_msg );
    }
    else
    {
        ret_val = SFL_CAN_ERROR_DLC_INVALID;
    }

    return ret_val;
}

void set_callback_can_msg_receive( callback_can_msg_receive_t callback )
{
    callback_can_msg_receive = callback;
}

