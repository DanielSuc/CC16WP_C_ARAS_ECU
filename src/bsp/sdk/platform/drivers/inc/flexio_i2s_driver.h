
#ifndef FLEXIO_I2S_DRIVER_H
#define FLEXIO_I2S_DRIVER_H

#include <stddef.h>
#include <stdbool.h>
#include "device_registers.h"
#include "flexio.h"
#include "edma_driver.h"
#include "callbacks.h"







typedef struct
{
    flexio_driver_type_t driverType;        
    uint32_t baudRate;                      
    uint8_t bitsWidth;                      
    uint8_t txPin;                          
    uint8_t rxPin;                          
    uint8_t sckPin;                         
    uint8_t wsPin;                          
    i2s_callback_t callback;                
    void *callbackParam;                     
    uint8_t rxDMAChannel;                    
    uint8_t txDMAChannel;                    
} flexio_i2s_master_user_config_t;


typedef struct
{
    flexio_driver_type_t driverType;        
    uint8_t bitsWidth;                      
    uint8_t txPin;                          
    uint8_t rxPin;                          
    uint8_t sckPin;                         
    uint8_t wsPin;                          
    i2s_callback_t callback;                
    void *callbackParam;                    
    uint8_t rxDMAChannel;                   
    uint8_t txDMAChannel;                   
} flexio_i2s_slave_user_config_t;


typedef struct
{
    flexio_common_state_t flexioCommon;    
    const uint8_t *txData;                 
    uint8_t *rxData;                       
    uint32_t txRemainingBytes;             
    uint32_t rxRemainingBytes;             
    uint32_t dummyDmaData;                 
    uint8_t rxDMAChannel;                  
    uint8_t txDMAChannel;                  
    uint8_t bitsWidth;                     
    uint8_t byteWidth;                     
    bool master;                           
    flexio_driver_type_t driverType;       
    status_t status;                       
    bool driverIdle;                       
    semaphore_t idleSemaphore;             
    bool blocking;                         
    i2s_callback_t callback;               
    void *callbackParam;                   
} flexio_i2s_master_state_t;

typedef flexio_i2s_master_state_t flexio_i2s_slave_state_t;



#if defined(__cplusplus)
extern "C" {
#endif

status_t FLEXIO_I2S_DRV_MasterInit(uint32_t instance,
                                   const flexio_i2s_master_user_config_t * userConfigPtr,
                                   flexio_i2s_master_state_t * master);


status_t FLEXIO_I2S_DRV_MasterDeinit(flexio_i2s_master_state_t * master);


status_t FLEXIO_I2S_DRV_MasterSetConfig(flexio_i2s_master_state_t * master,
                                        uint32_t baudRate,
                                        uint8_t bitsWidth);


status_t FLEXIO_I2S_DRV_MasterGetBaudRate(flexio_i2s_master_state_t * master, uint32_t *baudRate);


status_t FLEXIO_I2S_DRV_MasterSendData(flexio_i2s_master_state_t * master,
                                       const uint8_t * txBuff,
                                       uint32_t txSize);



status_t FLEXIO_I2S_DRV_MasterSendDataBlocking(flexio_i2s_master_state_t * master,
                                               const uint8_t * txBuff,
                                               uint32_t txSize,
                                               uint32_t timeout);


status_t FLEXIO_I2S_DRV_MasterReceiveData(flexio_i2s_master_state_t * master,
                                          uint8_t * rxBuff,
                                          uint32_t rxSize);


status_t FLEXIO_I2S_DRV_MasterReceiveDataBlocking(flexio_i2s_master_state_t * master,
                                                  uint8_t * rxBuff,
                                                  uint32_t rxSize,
                                                  uint32_t timeout);


status_t FLEXIO_I2S_DRV_MasterTransferAbort(flexio_i2s_master_state_t * master);


status_t FLEXIO_I2S_DRV_MasterGetStatus(flexio_i2s_master_state_t * master, uint32_t *bytesRemaining);


status_t FLEXIO_I2S_DRV_MasterSetRxBuffer(flexio_i2s_master_state_t *master,
                                          uint8_t * rxBuff,
                                          uint32_t rxSize);


status_t FLEXIO_I2S_DRV_MasterSetTxBuffer(flexio_i2s_master_state_t *master,
                                          const uint8_t * txBuff,
                                          uint32_t txSize);


status_t FLEXIO_I2S_DRV_SlaveInit(uint32_t instance,
                                  const flexio_i2s_slave_user_config_t * userConfigPtr,
                                  flexio_i2s_slave_state_t * slave);


status_t FLEXIO_I2S_DRV_SlaveDeinit(flexio_i2s_slave_state_t * slave);


status_t FLEXIO_I2S_DRV_SlaveSetConfig(flexio_i2s_slave_state_t * slave,
                                       uint8_t bitsWidth);


status_t FLEXIO_I2S_DRV_SlaveSendData(flexio_i2s_slave_state_t * slave,
                                                    const uint8_t * txBuff,
                                                    uint32_t txSize);


status_t FLEXIO_I2S_DRV_SlaveSendDataBlocking(flexio_i2s_slave_state_t * slave,
                                                            const uint8_t * txBuff,
                                                            uint32_t txSize,
                                                            uint32_t timeout);

status_t FLEXIO_I2S_DRV_SlaveReceiveData(flexio_i2s_slave_state_t * slave,
                                                       uint8_t * rxBuff,
                                                       uint32_t rxSize);


status_t FLEXIO_I2S_DRV_SlaveReceiveDataBlocking(flexio_i2s_slave_state_t * slave,
                                                               uint8_t * rxBuff,
                                                               uint32_t rxSize,
                                                               uint32_t timeout);


status_t FLEXIO_I2S_DRV_SlaveTransferAbort(flexio_i2s_slave_state_t * slave);


status_t FLEXIO_I2S_DRV_SlaveGetStatus(flexio_i2s_slave_state_t * slave, uint32_t *bytesRemaining);


status_t FLEXIO_I2S_DRV_SlaveSetRxBuffer(flexio_i2s_slave_state_t *slave,
                                                       uint8_t * rxBuff,
                                                       uint32_t rxSize);


status_t FLEXIO_I2S_DRV_SlaveSetTxBuffer(flexio_i2s_slave_state_t *slave,
                                                       const uint8_t * txBuff,
                                                       uint32_t txSize);


void FLEXIO_I2S_DRV_MasterGetDefaultConfig(flexio_i2s_master_user_config_t * userConfigPtr);


void FLEXIO_I2S_DRV_SlaveGetDefaultConfig(flexio_i2s_slave_user_config_t * userConfigPtr);


#if defined(__cplusplus)
}
#endif


#endif 

