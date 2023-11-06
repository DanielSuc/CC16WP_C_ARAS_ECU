
#ifndef FLEXIO_UART_DRIVER_H
#define FLEXIO_UART_DRIVER_H

#include <stddef.h>
#include <stdbool.h>
#include "device_registers.h"
#include "flexio.h"
#include "edma_driver.h"
#include "callbacks.h"




typedef enum
{
    FLEXIO_UART_DIRECTION_TX       = 0x01U,    
    FLEXIO_UART_DIRECTION_RX       = 0x00U,    
} flexio_uart_driver_direction_t;




typedef struct
{
    flexio_driver_type_t driverType;            
    uint32_t baudRate;                          
    uint8_t bitCount;                           
    flexio_uart_driver_direction_t direction;   
    uint8_t dataPin;                            
    uart_callback_t callback;                   
    void *callbackParam;                        
    uint8_t dmaChannel;                         
} flexio_uart_user_config_t;


typedef struct
{
    flexio_common_state_t flexioCommon;        
    uint8_t *rxData;                           
    const uint8_t *txData;                     
    uint32_t remainingBytes;                   
    uint8_t dmaChannel;                        
    uart_callback_t callback;                  
    void *callbackParam;                       
    flexio_uart_driver_direction_t direction;  
    flexio_driver_type_t driverType;           
    status_t status;                           
    bool driverIdle;                           
    semaphore_t idleSemaphore;                 
    bool blocking;                             
    uint8_t bitCount;                          
    uint8_t txFlush;                           
} flexio_uart_state_t;



#if defined(__cplusplus)
extern "C" {
#endif


status_t FLEXIO_UART_DRV_Init(uint32_t instance,
                              const flexio_uart_user_config_t * userConfigPtr,
                              flexio_uart_state_t * state);

status_t FLEXIO_UART_DRV_Deinit(flexio_uart_state_t * state);


status_t FLEXIO_UART_DRV_SetConfig(flexio_uart_state_t *state,
                                   uint32_t baudRate,
                                   uint8_t bitCount);


status_t FLEXIO_UART_DRV_GetBaudRate(flexio_uart_state_t *state, uint32_t *baudRate);


status_t FLEXIO_UART_DRV_SendDataBlocking(flexio_uart_state_t *state,
                                          const uint8_t * txBuff,
                                          uint32_t txSize,
                                          uint32_t timeout);

status_t FLEXIO_UART_DRV_SendData(flexio_uart_state_t *state,
                                  const uint8_t * txBuff,
                                  uint32_t txSize);


status_t FLEXIO_UART_DRV_ReceiveDataBlocking(flexio_uart_state_t *state,
                                             uint8_t * rxBuff,
                                             uint32_t rxSize,
                                             uint32_t timeout);

status_t FLEXIO_UART_DRV_ReceiveData(flexio_uart_state_t *state,
                                     uint8_t * rxBuff,
                                     uint32_t rxSize);



status_t FLEXIO_UART_DRV_GetStatus(flexio_uart_state_t * state,
                                   uint32_t *bytesRemaining);



status_t FLEXIO_UART_DRV_TransferAbort(flexio_uart_state_t * state);


status_t FLEXIO_UART_DRV_SetRxBuffer(flexio_uart_state_t *state,
                                     uint8_t * rxBuff,
                                     uint32_t rxSize);


status_t FLEXIO_UART_DRV_SetTxBuffer(flexio_uart_state_t *state,
                                     const uint8_t * txBuff,
                                     uint32_t txSize);


void FLEXIO_UART_DRV_GetDefaultConfig(flexio_uart_user_config_t * userConfigPtr);


#if defined(__cplusplus)
}
#endif


#endif 

