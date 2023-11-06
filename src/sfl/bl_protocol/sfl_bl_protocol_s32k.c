#include <stdint.h>
#include <stddef.h>

#include "can_db_tables.h"
#include "hal_can.h"
#include "sfl_can_db_tables_data.h"
#include "sfl_bl_protocol_s32k.h"

#include "defines_general.h"
#include "role_types.h"
#include "role_phy_can.h"
#include "role_protocol_bl.h"
#include "role.h"

FILENUM( 22 )

static enum_SFL_BLP_ERROR_CODES sfl_bl_protocol_s32k_transfer_msg_to_protocol( uint32_t msgid, uint8_t len, const uint8_t* ptr_data );
static enum_CODE convert_universal_params_to_flexcan_params( const struct_ROLE_CAN_EXT_BAUD_OUTPUT_PHASE *ptr_inp, flexcan_time_segment_t *ptr_out, uint8_t iphase );

extern volatile const can_bus_db_const_typ can_bus_db_const[];

static flexcan_msgbuff_t mgl_can_msg_rx;
static uint8_t mgl_bl_can_ind = 0;

enum_SFL_BLP_ERROR_CODES sfl_bl_protocol_s32k_init()
{
    enum_SFL_BLP_ERROR_CODES retval = SFL_BLP_ERROR_OPERATION;

#if defined(STANDALONE_APP)
    if (CODE_OK == role_do(ROLE_ID_PROTOCOL_BOOTLOADER, ROLE_INIT, BL_APP_MODE_STANDALONE))
#else
    if( CODE_OK == role_do( ROLE_ID_PROTOCOL_BOOTLOADER, ROLE_INIT, BL_APP_MODE_APP ) )
    #endif 
    {
        retval = SFL_BLP_ERROR_NONE;
    }
    else
    {
    }

    return retval;
}

enum_SFL_BLP_ERROR_CODES sfl_bl_protocol_s32k_is_msg_for_bl( uint32_t idx, flexcan_state_t *flexcanState )
{
    enum_SFL_BLP_ERROR_CODES retval = ( BL_CAN_RX_IDX == idx ? SFL_BLP_ERROR_NONE : SFL_BLP_NON_BLP_IDX );
    if( SFL_BLP_ERROR_NONE == retval )
    {
        (void) sfl_bl_protocol_s32k_transfer_msg_to_protocol( flexcanState->mbs[idx].mb_message->msgId,
            flexcanState->mbs[idx].mb_message->dataLen,
            flexcanState->mbs[idx].mb_message->data );
    }
    else
    {
    }

    return retval;
}

enum_SFL_BLP_ERROR_CODES sfl_bl_protocol_s32k_cyclic()
{
    role_play();
    return SFL_BLP_ERROR_NONE;
}

enum_SFL_BLP_ERROR_CODES sfl_bl_protocol_s32k_process_rx_msg( const struct_hal_can_frame_t* ptr_can_msg )
{
    return sfl_bl_protocol_s32k_transfer_msg_to_protocol( ptr_can_msg->header.can_id, ptr_can_msg->header.can_dlc, ptr_can_msg->data );
}

enum_SFL_BLP_ERROR_CODES sfl_bl_protocol_s32k_rx_tx_init( uint8_t rx_msg_box_num, uint8_t tx_msg_box_num )
{
    enum_SFL_BLP_ERROR_CODES retval = SFL_BLP_ERROR_OPERATION;

    mgl_bl_can_ind = ( *(uint8_t*) EE_READ_PTR( bl_canbus ) );
    ASSERT( mgl_bl_can_ind < 3u );	

    if( mgl_bl_can_ind < CAN_BUS_MAX && TRUE == can_bus_db_const[mgl_bl_can_ind].hw_module_active )
    {
        struct_ROLE_CAN_RX_MB_INFO mb_info = { .mb = rx_msg_box_num, .ptr_msgbuff = &mgl_can_msg_rx };
        if( CODE_OK == role_do( ROLE_ID_PHY_CAN0 + mgl_bl_can_ind, ROLE_CAN_CONFIG_BL_RX_MB, &mb_info ) )
        {
            if( CODE_OK == role_do( ROLE_ID_PHY_CAN0 + mgl_bl_can_ind, ROLE_CAN_CONFIG_BL_TX_MB, (uint32_t) tx_msg_box_num ) )
            {
                retval = SFL_BLP_ERROR_NONE;
            }
            else
            {
            }
        }
        else
        {
        }
    }
    else
    {
    }

    return retval;
}

enum_SFL_BLP_ERROR_CODES sfl_bl_protocol_s32k_set_baudrate( const struct_hal_can_handle* ptr_can_handle, uint8_t baudrate )
{
    enum_SFL_BLP_ERROR_CODES retval = SFL_BLP_ERROR_OPERATION;

    if( mgl_bl_can_ind == ptr_can_handle->can_handle_number )
    {
        if( CODE_OK == EE_WRITE_MAX32(baudrate1, SWAP(INV_16(baudrate))) )
        {
            if( CODE_OK == EE_WRITE_MAX32(baudrate2, SWAP(INV_16(baudrate))) )
            {
                retval = SFL_BLP_ERROR_NONE;
            }
            else
            {
            }
        }
        else
        {
        }
    }
    else
    {
        retval = SFL_BLP_ERROR_PORT;
    }

    return retval;
}

enum_SFL_BLP_ERROR_CODES sfl_bl_protocol_s32k_get_baudrate()
{
    uint8_t EEPROM_baudrate1;
    uint8_t EEPROM_baudrate2;

    EEPROM_baudrate1 = SWAP((*(uint16_t*)EE_READ_PTR(baudrate1)));
    EEPROM_baudrate2 = SWAP((*(uint16_t*)EE_READ_PTR(baudrate2)));

    if( EEPROM_baudrate1 == EEPROM_baudrate2 )
    {
        return EEPROM_baudrate1;
    }
    else
    {
        return BIOS_CAN_125KBIT;
    }
}

enum_SFL_BLP_ERROR_CODES sfl_bl_protocol_s32k_calc_baudrate_params( uint32_t can_clock_hz, uint32_t arbitr_baud_hz, uint32_t data_baud_hz,
    uint8_t arbitr_sample_pnt_percent, uint8_t data_sample_pnt_percent,
    flexcan_time_segment_t * ptr_arbitr_tseg, flexcan_time_segment_t * ptr_data_tseg )
{
#if 0
    struct_EE_CAN_EXT can_ext;
    can_ext.baud.inp.can_clock = 80000000u;
    can_ext.baud.inp.arbitr_baud = 500000u;
    can_ext.baud.inp.data_baud = 1000000u;
    can_ext.baud.inp.arbitr_smp = 75u;
    can_ext.baud.inp.data_smp = 75u;


#endif 

    struct_ROLE_CAN_EXT_BAUD baud;
    baud.inp.can_clock = can_clock_hz;
    baud.inp.arbitr_baud = arbitr_baud_hz;
    baud.inp.data_baud = data_baud_hz;
    baud.inp.arbitr_smp = arbitr_sample_pnt_percent;
    baud.inp.data_smp = data_sample_pnt_percent;

    enum_CODE retval = role_do( ROLE_ID_PHY_CAN0, ROLE_CAN_CALC_EXT_BAUD_PARAMS, &baud );
    if( CODE_OK == retval )
    {
        retval = convert_universal_params_to_flexcan_params( &baud.out.phase[CAN_FRAME_PHASE_ARBITRATION], ptr_arbitr_tseg, CAN_FRAME_PHASE_ARBITRATION );
        if( CODE_OK == retval )
        {
            retval = convert_universal_params_to_flexcan_params( &baud.out.phase[CAN_FRAME_PHASE_DATA], ptr_data_tseg, CAN_FRAME_PHASE_DATA );
        }
        else
        {
        }
    }
    else
    {
    }

    return ( CODE_OK == retval ? SFL_BLP_ERROR_NONE : SFL_BLP_ERROR_OPERATION );
}


static enum_SFL_BLP_ERROR_CODES sfl_bl_protocol_s32k_transfer_msg_to_protocol( uint32_t msgid, uint8_t len, const uint8_t* ptr_data )
{
    enum_SFL_BLP_ERROR_CODES retval = SFL_BLP_ERROR_OPERATION;

    uint8_t i = 0;
    mgl_can_msg_rx.msgId = msgid & 0x7FFFFFFF;
    mgl_can_msg_rx.dataLen = len;
    for( i = 0; i < len; i++ )
    {
        mgl_can_msg_rx.data[i] = ptr_data[i];
    }

    if( CODE_OK == role_do( ROLE_ID_PHY_CAN0 + mgl_bl_can_ind, ROLE_CAN_SIGNAL_RX_MSG, ROLE_PARAM_NONE ) )
    {
        retval = SFL_BLP_ERROR_NONE;
    }
    else
    {
    }

    return retval;
}

static enum_CODE convert_universal_params_to_flexcan_params( const struct_ROLE_CAN_EXT_BAUD_OUTPUT_PHASE *ptr_inp, flexcan_time_segment_t *ptr_out, uint8_t iphase )
{
    struct_ROLE_CAN_FLEXCAN_PARAMS flex;       
    struct_ROLE_CAN_PARAM_CONVERTABLE conv;
    conv.ptr_inp = ptr_inp;
    conv.ptr_out = &flex;
    conv.iphase = iphase;

    enum_CODE retval = role_do( ROLE_ID_PHY_CAN0, ROLE_CAN_EXT_EE_PARAM_TO_FLEXCAN, &conv ); 
    if( CODE_OK == retval )
    {
        ptr_out->propSeg = flex.propSeg;
        ptr_out->phaseSeg1 = flex.phaseSeg1;
        ptr_out->phaseSeg2 = flex.phaseSeg2;
        ptr_out->preDivider = flex.preDivider;
        ptr_out->rJumpwidth = flex.rJumpwidth;
    }
    else
    {
    }
    return retval;
}


