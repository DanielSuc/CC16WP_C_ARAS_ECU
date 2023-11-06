
#ifndef SFL_BL_PROTOCOL_S32K_H__
#define SFL_BL_PROTOCOL_S32K_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#include "flexcan_driver.h"

#define BL_CAN_RX_IDX   (0u) 
#define BL_CAN_TX_IDX   (6u) 

typedef enum
{
    SFL_BLP_ERROR_NONE = 0u,                
    SFL_BLP_ERROR_OPERATION,                
    SFL_BLP_ERROR_PORT,                     
    SFL_BLP_NON_BLP_IDX,					
} enum_SFL_BLP_ERROR_CODES;

enum_SFL_BLP_ERROR_CODES sfl_bl_protocol_s32k_init();

enum_SFL_BLP_ERROR_CODES sfl_bl_protocol_s32k_is_msg_for_bl( uint32_t idx, flexcan_state_t *flexcanState );

enum_SFL_BLP_ERROR_CODES sfl_bl_protocol_s32k_cyclic();

enum_SFL_BLP_ERROR_CODES sfl_bl_protocol_s32k_process_rx_msg( const struct_hal_can_frame_t* ptr_can_msg );

enum_SFL_BLP_ERROR_CODES sfl_bl_protocol_s32k_rx_tx_init( uint8_t rx_msg_box_num, uint8_t tx_msg_box_num );

enum_SFL_BLP_ERROR_CODES sfl_bl_protocol_s32k_set_baudrate( const struct_hal_can_handle* ptr_can_handle, uint8_t baudrate );

enum_SFL_BLP_ERROR_CODES sfl_bl_protocol_s32k_get_baudrate( void );

enum_SFL_BLP_ERROR_CODES sfl_bl_protocol_s32k_calc_baudrate_params( uint32_t can_clock_hz, uint32_t arbitr_baud_hz, uint32_t data_baud_hz,
																	uint8_t  arbitr_sample_pnt_percent, uint8_t  data_sample_pnt_percent,
																	flexcan_time_segment_t * ptr_arbitr_tseg, flexcan_time_segment_t * ptr_data_tseg);

#ifdef __cplusplus
}
#endif

#endif 

