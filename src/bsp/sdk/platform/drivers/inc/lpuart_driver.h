
#ifndef LPUART_DRIVER_H__
#define LPUART_DRIVER_H__

#include <stddef.h>
#include "device_registers.h"
#include "status.h"
#include "interrupt_manager.h"
#include "osif.h"
#if FEATURE_LPUART_HAS_DMA_ENABLE
#include "edma_driver.h"
#endif
#include "callbacks.h"




typedef enum
{
    LPUART_USING_DMA         = 0,    
    LPUART_USING_INTERRUPTS          
} lpuart_transfer_type_t;

typedef enum
{
    LPUART_8_BITS_PER_CHAR  = 0x0U, 
    LPUART_9_BITS_PER_CHAR  = 0x1U, 
    LPUART_10_BITS_PER_CHAR = 0x2U  
} lpuart_bit_count_per_char_t;

typedef enum
{
    LPUART_PARITY_DISABLED = 0x0U, 
    LPUART_PARITY_EVEN     = 0x2U, 
    LPUART_PARITY_ODD      = 0x3U  
} lpuart_parity_mode_t;

typedef enum
{
    LPUART_ONE_STOP_BIT = 0x0U, 
    LPUART_TWO_STOP_BIT = 0x1U  
} lpuart_stop_bit_count_t;

typedef struct
{
    const uint8_t * txBuff;              
    uint8_t * rxBuff;                    
    volatile uint32_t txSize;            
    volatile uint32_t rxSize;            
    volatile bool isTxBusy;              
    volatile bool isRxBusy;              
    volatile bool isTxBlocking;          
    volatile bool isRxBlocking;          
    lpuart_bit_count_per_char_t bitCountPerChar; 
    uart_callback_t rxCallback;          
    void * rxCallbackParam;              
    uart_callback_t txCallback;          
    void * txCallbackParam;              
    lpuart_transfer_type_t transferType; 
#if FEATURE_LPUART_HAS_DMA_ENABLE
    uint8_t rxDMAChannel;                
    uint8_t txDMAChannel;                
#endif
    semaphore_t rxComplete;              
    semaphore_t txComplete;              
    volatile status_t transmitStatus;    
    volatile status_t receiveStatus;     
} lpuart_state_t;

typedef struct
{
    uint32_t baudRate;                           
    lpuart_parity_mode_t parityMode;             
    lpuart_stop_bit_count_t stopBitCount;        
    lpuart_bit_count_per_char_t bitCountPerChar; 
    lpuart_transfer_type_t transferType;         
    uint8_t rxDMAChannel;                        
    uint8_t txDMAChannel;                        
} lpuart_user_config_t;


#if defined(__cplusplus)
extern "C" {
#endif


void LPUART_DRV_GetDefaultConfig(lpuart_user_config_t * lpuartUserConfig);

status_t LPUART_DRV_Init(uint32_t instance, lpuart_state_t * lpuartStatePtr,
                         const lpuart_user_config_t * lpuartUserConfig);

status_t LPUART_DRV_Deinit(uint32_t instance);

uart_callback_t LPUART_DRV_InstallRxCallback(uint32_t instance,
                                             uart_callback_t function,
                                             void * callbackParam);

uart_callback_t LPUART_DRV_InstallTxCallback(uint32_t instance,
                                             uart_callback_t function,
                                             void * callbackParam);

status_t LPUART_DRV_SendDataBlocking(uint32_t instance,
                                     const uint8_t * txBuff,
                                     uint32_t txSize,
                                     uint32_t timeout);

status_t LPUART_DRV_SendDataPolling(uint32_t instance, const uint8_t *txBuff, uint32_t txSize);

status_t LPUART_DRV_SendData(uint32_t instance,
                             const uint8_t * txBuff,
                             uint32_t txSize);

status_t LPUART_DRV_GetTransmitStatus(uint32_t instance, uint32_t * bytesRemaining);

status_t LPUART_DRV_AbortSendingData(uint32_t instance);

status_t LPUART_DRV_ReceiveDataBlocking(uint32_t instance,
                                        uint8_t * rxBuff,
                                        uint32_t rxSize,
                                        uint32_t timeout);

status_t LPUART_DRV_ReceiveDataPolling(uint32_t instance, uint8_t *rxBuff, uint32_t rxSize);

status_t LPUART_DRV_ReceiveData(uint32_t instance,
                                uint8_t * rxBuff,
                                uint32_t rxSize);

status_t LPUART_DRV_GetReceiveStatus(uint32_t instance, uint32_t * bytesRemaining);

status_t LPUART_DRV_AbortReceivingData(uint32_t instance);

status_t LPUART_DRV_SetBaudRate(uint32_t instance, uint32_t desiredBaudRate);

void LPUART_DRV_GetBaudRate(uint32_t instance, uint32_t * configuredBaudRate);

status_t LPUART_DRV_SetTxBuffer(uint32_t instance,
                                const uint8_t * txBuff,
                                uint32_t txSize);

status_t LPUART_DRV_SetRxBuffer(uint32_t instance,
                                uint8_t * rxBuff,
                                uint32_t rxSize);


#if defined(__cplusplus)
}
#endif


#endif 

