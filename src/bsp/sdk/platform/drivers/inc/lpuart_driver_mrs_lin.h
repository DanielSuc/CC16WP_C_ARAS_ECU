

#ifndef LPUART_DRIVER_MRS_LIN_H__
#define LPUART_DRIVER_MRS_LIN_H__

#include <stddef.h>
#include <stdbool.h>
#include "device_registers.h"
#include "status.h"
#include "interrupt_manager.h"
#include "lpuart_hw_access.h"
#include "hal_data_types.h" 

typedef enum
{
    LIN_MRS_DRV_OK                      = 0u,     
    LIN_MRS_DRV_ERROR_NO_CHANNEL_LEFT       ,     
    LIN_MRS_DRV_ERROR_DATA_LEN_INVALID      ,     
    LIN_MRS_DRV_ERROR_DIR_INVALID           ,     
    LIN_MRS_DRV_ERROR_CRC_INVALID           ,     
    LIN_MRS_DRV_ERROR_NODE_INVALID          ,     
    LIN_MRS_DRV_ERROR_RESPONSE_INVALID      ,     
	LIN_MRS_DRV_ERROR_OTHER					      

}enum_LIN_MRS_DRV_RETVAL;


typedef void (*lin_tx_callback_t)(uint8_t);
typedef void (*lin_rx_callback_t)(uint8_t, uint8_t, uint8_t);
typedef void (*lin_error_callback_t)(uint8_t, uint8_t);


status_t LIN_MRS_DRV_Init(uint8_t module, uint32_t baudrate);


void LIN_MRS_DRV_De_Init(uint8_t hw_module);


void LIN_MRS_DRV_SetBaudRate(uint8_t module, uint32_t desiredBaudRate);


void LIN_MRS_DRV_IRQHandler(uint32_t module); 




uint8_t LIN_MRS_DRV_SetCallbacks( uint8_t module,
								  lin_tx_callback_t 	const ptr_lin_tx_callback,
								  lin_rx_callback_t 	const ptr_lin_rx_callback,
								  lin_error_callback_t 	const ptr_lin_error_callback);


LPUART_Type *const LIN_MRS_DRV_GetUartBase(uint8_t module);


void LIN_MRS_DRV_SetBreakCharDetectLength(LPUART_Type *const base, lpuart_break_char_length_t length); 


void LIN_MRS_DRV_QueueBreakField(LPUART_Type *const base);  


void LIN_MRS_DRV_SetMasterMode(uint8_t hw_module);


bool LIN_MRS_DRV_LinIsActive(uint8_t hw_module); 



#if defined(__cplusplus)
}
#endif



#endif 

