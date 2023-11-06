
#ifndef FLEXIO_I2C_DRIVER_H
#define FLEXIO_I2C_DRIVER_H

#include <stddef.h>
#include <stdbool.h>
#include "device_registers.h"
#include "flexio.h"
#include "edma_driver.h"
#include "callbacks.h"






#define FLEXIO_I2C_MAX_SIZE   (((uint32_t)((0xFFU - 1U) / 18U)) - 1U)

#define FLEXIO_I2C_DMA_TX_CHAIN_LENGTH      (1U)
#define FLEXIO_I2C_DMA_RX_CHAIN_LENGTH      (5U)
#define FLEXIO_I2C_DMA_BUF_SIZE   (STCD_SIZE(FLEXIO_I2C_DMA_TX_CHAIN_LENGTH + FLEXIO_I2C_DMA_RX_CHAIN_LENGTH + 1U))



typedef struct
{
    uint16_t slaveAddress;              
    flexio_driver_type_t driverType;    
    uint32_t baudRate;                  
    uint8_t sdaPin;                     
    uint8_t sclPin;                     
    i2c_master_callback_t callback;         
    void *callbackParam;                
    uint8_t rxDMAChannel;               
    uint8_t txDMAChannel;               
} flexio_i2c_master_user_config_t;


typedef struct
{
    flexio_common_state_t flexioCommon;    
    const uint8_t *txData;                 
    uint8_t *rxData;                       
    uint32_t txRemainingBytes;             
    uint32_t rxRemainingBytes;             
    uint8_t rxDMAChannel;                  
    uint8_t txDMAChannel;                  
    i2c_master_callback_t callback;        
    void *callbackParam;                   
    uint16_t slaveAddress;                 
    flexio_driver_type_t driverType;       
    status_t status;                       
    bool receive;                          
    bool addrReceived;                     
    bool driverIdle;                       
    semaphore_t idleSemaphore;             
    bool blocking;                         
    bool sendStop;                         
    uint8_t sdaPin;                        
    uint8_t sclPin;                        
    uint8_t dummyDmaIdle;                  
    uint8_t dummyDmaStop;                  
    uint8_t dummyDmaReceive;               
    uint8_t dmaReceiveTxStop0;             
    uint8_t dmaReceiveTxStop1;             
    uint8_t dmaReceiveRxStop1;             
    uint8_t stcd[FLEXIO_I2C_DMA_BUF_SIZE]; 
} flexio_i2c_master_state_t;



#if defined(__cplusplus)
extern "C" {
#endif

status_t FLEXIO_I2C_DRV_MasterInit(uint32_t instance,
                                   const flexio_i2c_master_user_config_t * userConfigPtr,
                                   flexio_i2c_master_state_t * master);


status_t FLEXIO_I2C_DRV_MasterDeinit(flexio_i2c_master_state_t * master);


status_t FLEXIO_I2C_DRV_MasterSetBaudRate(flexio_i2c_master_state_t * master, uint32_t baudRate);


status_t FLEXIO_I2C_DRV_MasterGetBaudRate(flexio_i2c_master_state_t * master, uint32_t *baudRate);


status_t FLEXIO_I2C_DRV_MasterSetSlaveAddr(flexio_i2c_master_state_t * master, const uint16_t address);


status_t FLEXIO_I2C_DRV_MasterSendData(flexio_i2c_master_state_t * master,
                                       const uint8_t * txBuff,
                                       uint32_t txSize,
                                       bool sendStop);



status_t FLEXIO_I2C_DRV_MasterSendDataBlocking(flexio_i2c_master_state_t * master,
                                               const uint8_t * txBuff,
                                               uint32_t txSize,
                                               bool sendStop,
                                               uint32_t timeout);


status_t FLEXIO_I2C_DRV_MasterReceiveData(flexio_i2c_master_state_t * master,
                                          uint8_t * rxBuff,
                                          uint32_t rxSize,
                                          bool sendStop);


status_t FLEXIO_I2C_DRV_MasterReceiveDataBlocking(flexio_i2c_master_state_t * master,
                                                  uint8_t * rxBuff,
                                                  uint32_t rxSize,
                                                  bool sendStop,
                                                  uint32_t timeout);


status_t FLEXIO_I2C_DRV_MasterTransferAbort(flexio_i2c_master_state_t * master);


status_t FLEXIO_I2C_DRV_MasterGetStatus(flexio_i2c_master_state_t * master, uint32_t *bytesRemaining);


void FLEXIO_I2C_DRV_GetDefaultConfig(flexio_i2c_master_user_config_t * userConfigPtr);


#if defined(__cplusplus)
}
#endif


#endif 

