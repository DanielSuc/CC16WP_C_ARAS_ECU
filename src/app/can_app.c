#include "can_app.h"
#include "canCom1.h"
#include "sfl_can_db.h"
#include "sfl_bl_protocol.h"
#include "flexcan_driver.h"
#include <stdbool.h>
#include "io_tables.h"
#include "hal_io.h"
#include "user_code.h"
#include "can_db_tables.h"

#define MAX_CAN_BUS_SUPPORTED 3

#define CAN_RETRANSMISSION_ENABLE   0
#define CAN_RETRANSMISSION_RETRY    1
#define CAN_RETRANSMISSION_DISABLE  2

#define ERR_MASKS (CAN_ESR1_ACKERR_MASK | \
                   CAN_ESR1_STFERR_MASK | \
                   CAN_ESR1_ERROVR_MASK | \
                   CAN_ESR1_FRMERR_MASK | \
                   CAN_ESR1_CRCERR_MASK | \
                   CAN_ESR1_BIT0ERR_MASK | CAN_ESR1_BIT1ERR_MASK)

volatile struct_can_app_error can_error_handle[MAX_CAN_BUS_SUPPORTED];

static void can_error_handle_tx_abort(uint8_t instance);
static void can_error_handle_tx_retry(uint8_t instance);

void CAN_Callback(uint8_t instance, flexcan_event_type_t eventType, uint32_t buffIdx, flexcan_state_t *flexcanState);

void CAN_Callback_Error(uint8_t instance, flexcan_event_type_t eventType, flexcan_state_t *flexcanState);

extern volatile const can_bus_db_const_typ can_bus_db_const[];


void user_can_init(const struct_can_pin_list ptr_can_pin_list[])
{
    static bool once = true;

    uint8_t i;
    if (once)
    {
        once = false;

        sfl_can_db_tables_data_init();          
        sfl_can_db_fifo_init();

        can_db_filter_typ can_db_filter_config[CAN_BUS_MAX];
        ext_get_filter_and_mask(can_db_filter_config);
        sfl_can_db_init(can_db_filter_config);  

        for (uint8_t i = 0; i < CAN_BUS_MAX; i++)       
        {
            sfl_can_db_tables_data_init_baudrate(can_handle[i], can_bus_db_const[i]);
        }
    }


    for (i = 0; i < CAN_BUS_MAX; i++)
    {
        can_handle[i].can_handle_number = can_bus_db_const[i].hw_module_id;

        if (can_bus_db_const[i].hw_module_active == TRUE)
        {
            if( ( ptr_can_pin_list[can_bus_db_const[i].hw_module_id].can_en_pin != PIN_MAX ) &&
                ( ptr_can_pin_list[can_bus_db_const[i].hw_module_id].can_stb_pin != PIN_MAX ) )
            {
                switch (can_bus_db_const[i].hw_module_id)
                {
                case 0:     
                    hal_io_do_set(ptr_can_pin_list[can_bus_db_const[i].hw_module_id].can_en_pin, 1);      
                    hal_io_do_set(ptr_can_pin_list[can_bus_db_const[i].hw_module_id].can_stb_pin, 1);     

                    break;

                case 1:     
                    hal_io_do_set(ptr_can_pin_list[can_bus_db_const[i].hw_module_id].can_en_pin, 1);      
                    hal_io_do_set(ptr_can_pin_list[can_bus_db_const[i].hw_module_id].can_stb_pin, 1);     

                    break;
                case 2:     
                    hal_io_do_set(ptr_can_pin_list[can_bus_db_const[i].hw_module_id].can_en_pin, 1);      
                    hal_io_do_set(ptr_can_pin_list[can_bus_db_const[i].hw_module_id].can_stb_pin, 1);     

                    break;
                default:
                    break;
                }
            }
            else
            {
            }

            can_handle[i].rx_cb_function = (hal_can_rx_callback_function_type) CAN_Callback;
            hal_can_set_receive_callback(&can_handle[i], NULL);        

            can_handle[i].err_cb_function = (hal_can_err_callback_function_type) CAN_Callback_Error;
            hal_can_set_error_callback(&can_handle[i], NULL);          
        }
    }
}


void user_can_set_baudrate(uint8_t interface, uint8_t can_fd_en, enum_HAL_CAN_BAUDRATE baudrate, hal_can_time_segment arb_phase, hal_can_time_segment data_phase)
{
    can_handle[interface].can_ext_baudrate.jumpwidth   = arb_phase.jumpwidth;
    can_handle[interface].can_ext_baudrate.phase_seg1  = arb_phase.phase_seg1;
    can_handle[interface].can_ext_baudrate.phase_seg2  = arb_phase.phase_seg2;
    can_handle[interface].can_ext_baudrate.pre_divider = arb_phase.pre_divider;
    can_handle[interface].can_ext_baudrate.prop_seg    = arb_phase.prop_seg;

    can_handle[interface].can_fd_ext_baudrate.jumpwidth   = data_phase.jumpwidth;
    can_handle[interface].can_fd_ext_baudrate.phase_seg1  = data_phase.phase_seg1;
    can_handle[interface].can_fd_ext_baudrate.phase_seg2  = data_phase.phase_seg2;
    can_handle[interface].can_fd_ext_baudrate.pre_divider = data_phase.pre_divider;
    can_handle[interface].can_fd_ext_baudrate.prop_seg    = data_phase.prop_seg;

    if( can_fd_en != 0)
    { 
        can_handle[interface].can_baudrate = HAL_CAN_FD_BAUD_EXT;
        can_handle[interface].can_fd_data_baudrate = HAL_CAN_FD_BAUD_EXT;
    }
    else
    { 
        if ( ( baudrate > HAL_CAN_BAUD_INVALID) && ( baudrate < HAL_CAN_BAUD_EXT) )
        {
            can_handle[interface].can_baudrate = baudrate;
            can_handle[interface].can_fd_data_baudrate = HAL_CAN_BAUD_INVALID;
        }
        else
        {
            can_handle[interface].can_baudrate = HAL_CAN_BAUD_EXT;
            can_handle[interface].can_fd_data_baudrate = HAL_CAN_BAUD_INVALID;
        }

    }

    hal_can_set_baudrate(&can_handle[interface], can_handle[interface].can_baudrate );
    hal_can_set_fd_data_baudrate(&can_handle[interface], can_handle[interface].can_fd_data_baudrate);
}


uint32_t user_can_fd_calculate_baudrate(uint32_t arb_baud, uint32_t arb_sample_pt, uint32_t data_baud, uint32_t data_sample_pt, hal_can_time_segment* arb_phase, hal_can_time_segment* data_phase )
{
    struct_ROLE_CAN_EXT_BAUD_DEMO io;
    uint32_t error = 0;

    struct_hal_can_handle local_can_handle;
    local_can_handle.is_can_fd = true;

    io.inp.arbitr_baud    = arb_baud;        
    io.inp.data_baud      = data_baud;       
    io.inp.can_clock      = 80000000u;       
    io.inp.arbitr_smp     = arb_sample_pt;   
    io.inp.data_smp       = data_sample_pt;  

    error = calculate_can_baudrate(&io);

    error = set_can_baudrate_timing(&local_can_handle.can_ext_baudrate, &io.out.phase[0], CAN_FD_FRAME_PHASE_ARBITRATION);

    error = set_can_baudrate_timing(&local_can_handle.can_fd_ext_baudrate, &io.out.phase[1], CAN_FD_FRAME_PHASE_DATA);

    if (error == 0 )
    {
        arb_phase->jumpwidth    = local_can_handle.can_ext_baudrate.jumpwidth;
        arb_phase->phase_seg1   = local_can_handle.can_ext_baudrate.phase_seg1;
        arb_phase->phase_seg2   = local_can_handle.can_ext_baudrate.phase_seg2;
        arb_phase->pre_divider  = local_can_handle.can_ext_baudrate.pre_divider;
        arb_phase->prop_seg     = local_can_handle.can_ext_baudrate.prop_seg;

        data_phase->jumpwidth   = local_can_handle.can_fd_ext_baudrate.jumpwidth;
        data_phase->phase_seg1  = local_can_handle.can_fd_ext_baudrate.phase_seg1;
        data_phase->phase_seg2  = local_can_handle.can_fd_ext_baudrate.phase_seg2;
        data_phase->pre_divider = local_can_handle.can_fd_ext_baudrate.pre_divider;
        data_phase->prop_seg    = local_can_handle.can_fd_ext_baudrate.prop_seg;


        if( ( ( arb_phase->jumpwidth == 0 ) &&
            ( arb_phase->phase_seg1 == 0 ) &&
            ( arb_phase->phase_seg2 == 0 ) &&
            ( arb_phase->pre_divider == 0 ) &&
            ( arb_phase->prop_seg == 0 ) &&
            ( data_phase->jumpwidth == 0 ) &&
            ( data_phase->phase_seg1 == 0 ) &&
            ( data_phase->phase_seg2 == 0 ) &&
            ( data_phase->pre_divider == 0 ) &&
            ( data_phase->prop_seg == 0 ) ) )
        {
            error = 1;
        }
    }

    return error;

}

void CAN_Callback(uint8_t instance, flexcan_event_type_t eventType, uint32_t buffIdx, flexcan_state_t *flexcanState)
{
    struct_hal_can_frame_t can_msg_receive;
    can_handle[instance].can_handle_mb_idx = buffIdx;

    uint32_t err1 = FLEXCAN_DRV_GetErrorStatus(instance);

    if ( (err1 & ERR_MASKS) )
    {
        can_error_handle[instance].last_can_error = err1;
        hal_get_timestamp((uint32_t*)&can_error_handle[instance].time_from_start_to_error, HAL_PRECISION_1MS);
    }
    else
    {
        can_error_handle[instance].last_can_error = 0u;
        hal_get_timestamp((uint32_t*)&can_error_handle[instance].time_from_start_to_error, HAL_PRECISION_1MS);        
    }

    switch (eventType)
    {
        case FLEXCAN_EVENT_TX_COMPLETE:
            sfl_can_db_tx_callback(instance);
            break;
        case FLEXCAN_EVENT_RXFIFO_COMPLETE:
            break;
        case FLEXCAN_EVENT_RX_COMPLETE:
        	if ( SFL_BLP_NON_BLP_IDX == sfl_bl_protocol_s32k_is_msg_for_bl(buffIdx, flexcanState) ) 
        	{
                hal_can_receive(&can_handle[instance], &can_msg_receive);     
                sfl_can_db_rx_wrapper(instance,&can_msg_receive);   
                (void)sfl_bl_protocol_s32k_process_rx_msg(&can_msg_receive);
			}
			else
			{
			}
            break;
        default:
            break;
    }
}

void CAN_Callback_Error(uint8_t instance, flexcan_event_type_t eventType, flexcan_state_t *flexcanState)
{
    uint8_t can_retransmission_mode = CAN_RETRANSMISSION_DISABLE; 

#ifdef SET_CAN_RETRANSMISSION_ENABLE
    can_retransmission_mode = CAN_RETRANSMISSION_ENABLE;
#endif

#ifdef SET_CAN_RETRANSMISSION_DISABLE
    can_retransmission_mode = CAN_RETRANSMISSION_DISABLE;
#endif

#ifdef SET_CAN_RETRANSMISSION_RETRY
    can_retransmission_mode = CAN_RETRANSMISSION_RETRY;
#endif

    if (FLEXCAN_EVENT_ERROR == eventType)
    {
        uint32_t err1 = FLEXCAN_DRV_GetErrorStatus(instance);

    	if ( (err1 & ERR_MASKS) )
    	{
    	    can_error_handle[instance].last_can_error = err1;
    	    hal_get_timestamp((uint32_t*)&can_error_handle[instance].time_from_start_to_error, HAL_PRECISION_1MS);

    		if (err1 & CAN_ESR1_TX_MASK)
    		{
                switch(can_retransmission_mode) {
                    case CAN_RETRANSMISSION_ENABLE:
                    break;

                    case CAN_RETRANSMISSION_RETRY:
                        can_error_handle_tx_retry(instance);
                    break;

                    case CAN_RETRANSMISSION_DISABLE:
                        can_error_handle_tx_abort(instance);
                    break;

                    default:
                    break;
                }
    		}

    		if (err1 & CAN_ESR1_RX_MASK)
    		{
        		for ( uint32_t mb_idx = 0u; mb_idx < 3u; ++mb_idx )
        	    {
        		    if (STATUS_SUCCESS != FLEXCAN_DRV_GetTransferStatus(instance, mb_idx))
        	        {
						FLEXCAN_DRV_AbortTransfer(instance, mb_idx);
						sfl_can_rx_int_enable(instance, mb_idx);
        	        }
        		    else
        		    {
        		    }
        	    }
    		}

            CAN_Type * const canBase[] = CAN_BASE_PTRS;
            FLEXCAN_ClearErrIntStatusFlag(canBase[instance]);

            if (CAN_ESR1_ERROVR_MASK == (err1 & CAN_ESR1_ERROVR_MASK))
			{
        		canBase[instance]->ESR1 |= CAN_ESR1_ERROVR_MASK;
			}
        	else
        	{
        	}
    	}
    	else
    	{
    	}
    }
}

void ext_get_filter_and_mask(can_db_filter_typ filter[])
{
    uint8_t bus_id = 0;


    switch(CAN_BUS_MAX){
#ifdef CAN2_FILTER_A
        case(3):
            bus_id = CAN_BUS_2;
            filter[bus_id].filter[0] = CAN2_FILTER_A;
            filter[bus_id].filter[1] = CAN2_FILTER_B;
            filter[bus_id].mask[0] = CAN2_MASK_A;
            filter[bus_id].mask[1] = CAN2_MASK_B;
            filter[bus_id].mask_division = CAN2_MASK_DIVISION;
#endif
#ifdef CAN1_FILTER_A
        case(2):
            bus_id = CAN_BUS_1;
            filter[bus_id].filter[0] = CAN1_FILTER_A;
            filter[bus_id].filter[1] = CAN1_FILTER_B;
            filter[bus_id].mask[0] = CAN1_MASK_A;
            filter[bus_id].mask[1] = CAN1_MASK_B;
            filter[bus_id].mask_division = CAN1_MASK_DIVISION;
#endif
        case(1):
            bus_id = CAN_BUS_0;
            filter[bus_id].filter[0] = CAN0_FILTER_A;
            filter[bus_id].filter[1] = CAN0_FILTER_B;
            filter[bus_id].mask[0] = CAN0_MASK_A;
            filter[bus_id].mask[1] = CAN0_MASK_B;
            filter[bus_id].mask_division = CAN0_MASK_DIVISION;
            break;

        default:
            filter = NULL;
            break;
    }

}

static void can_error_handle_tx_abort(uint8_t instance)
{
    for(uint32_t mb_idx = 4u; mb_idx < struct_can_config_tbl[instance].can_init_config_struct->max_num_mb; ++mb_idx )
    {
        if (STATUS_SUCCESS != FLEXCAN_DRV_GetTransferStatus(instance, mb_idx))
        {
            FLEXCAN_DRV_AbortTransfer(instance, mb_idx);
        }
        else
        {
        }
    }
}

static void can_error_handle_tx_retry(uint8_t instance)
{
    static uint32_t cnt = 0;
    uint32_t retry = 0;

    #ifdef SET_CAN_RETRANSMISSION_RETRY
    retry = SET_CAN_RETRANSMISSION_RETRY;
    #endif

    if(cnt >= retry) {
       can_error_handle_tx_abort(instance);
       cnt = 0;
    } else {
        cnt++;
    }
}

