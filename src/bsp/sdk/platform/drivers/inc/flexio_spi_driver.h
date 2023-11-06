
#ifndef FLEXIO_SPI_DRIVER_H
#define FLEXIO_SPI_DRIVER_H

#include <stddef.h>
#include <stdbool.h>
#include "device_registers.h"
#include "flexio.h"
#include "edma_driver.h"
#include "callbacks.h"




typedef enum
{
    FLEXIO_SPI_TRANSFER_MSB_FIRST        = 0U,  
    FLEXIO_SPI_TRANSFER_LSB_FIRST        = 1U,  
} flexio_spi_transfer_bit_order_t;

typedef enum
{
    FLEXIO_SPI_TRANSFER_1BYTE            = 1U,  
    FLEXIO_SPI_TRANSFER_2BYTE            = 2U,  
    FLEXIO_SPI_TRANSFER_4BYTE            = 4U,  
} flexio_spi_transfer_size_t;




typedef struct
{
    uint32_t baudRate;         
    flexio_driver_type_t driverType; 
    flexio_spi_transfer_bit_order_t bitOrder; 
    flexio_spi_transfer_size_t transferSize;  
    uint8_t clockPolarity;     
    uint8_t clockPhase;        
    uint8_t mosiPin;           
    uint8_t misoPin;           
    uint8_t sckPin;            
    uint8_t ssPin;             
    spi_callback_t callback;       
    void *callbackParam;       
    uint8_t rxDMAChannel;      
    uint8_t txDMAChannel;      
} flexio_spi_master_user_config_t;

typedef struct
{
    flexio_driver_type_t driverType; 
    flexio_spi_transfer_bit_order_t bitOrder; 
    flexio_spi_transfer_size_t transferSize;  
    uint8_t clockPolarity;     
    uint8_t clockPhase;        
    uint8_t mosiPin;           
    uint8_t misoPin;           
    uint8_t sckPin;            
    uint8_t ssPin;             
    spi_callback_t callback;       
    void *callbackParam;       
    uint8_t rxDMAChannel;      
    uint8_t txDMAChannel;      
} flexio_spi_slave_user_config_t;


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
    flexio_driver_type_t driverType;           
    flexio_spi_transfer_bit_order_t bitOrder;  
    flexio_spi_transfer_size_t transferSize;   
    status_t status;                           
    bool driverIdle;                           
    semaphore_t idleSemaphore;                 
    bool blocking;                             
    bool master;                               
    spi_callback_t callback;                   
    void *callbackParam;                       
} flexio_spi_master_state_t;

typedef flexio_spi_master_state_t flexio_spi_slave_state_t;




#if defined(__cplusplus)
extern "C" {
#endif

status_t FLEXIO_SPI_DRV_MasterInit(uint32_t instance,
                                   const flexio_spi_master_user_config_t * userConfigPtr,
                                   flexio_spi_master_state_t * master);


status_t FLEXIO_SPI_DRV_MasterDeinit(flexio_spi_master_state_t *master);


status_t FLEXIO_SPI_DRV_MasterSetBaudRate(flexio_spi_master_state_t *master, uint32_t baudRate);


status_t FLEXIO_SPI_DRV_MasterGetBaudRate(flexio_spi_master_state_t *master, uint32_t *baudRate);


status_t FLEXIO_SPI_DRV_MasterTransfer(flexio_spi_master_state_t *master,
                                       const uint8_t *txData,
                                       uint8_t *rxData,
                                       uint32_t dataSize);


status_t FLEXIO_SPI_DRV_MasterTransferBlocking(flexio_spi_master_state_t *master,
                                               const uint8_t *txData,
                                               uint8_t *rxData,
                                               uint32_t dataSize,
                                               uint32_t timeout);



status_t FLEXIO_SPI_DRV_MasterTransferAbort(flexio_spi_master_state_t *master);


status_t FLEXIO_SPI_DRV_MasterGetStatus(flexio_spi_master_state_t *master, uint32_t *bytesRemaining);


status_t FLEXIO_SPI_DRV_SlaveInit(uint32_t instance,
                                  const flexio_spi_slave_user_config_t * userConfigPtr,
                                  flexio_spi_slave_state_t * slave);

status_t FLEXIO_SPI_DRV_SlaveDeinit(flexio_spi_slave_state_t *slave);


status_t FLEXIO_SPI_DRV_SlaveTransfer(flexio_spi_slave_state_t *slave,
                                                    const uint8_t *txData,
                                                    uint8_t *rxData,
                                                    uint32_t dataSize);


status_t FLEXIO_SPI_DRV_SlaveTransferBlocking(flexio_spi_slave_state_t *slave,
                                                            const uint8_t *txData,
                                                            uint8_t *rxData,
                                                            uint32_t dataSize,
                                                            uint32_t timeout);


status_t FLEXIO_SPI_DRV_SlaveTransferAbort(flexio_spi_slave_state_t *slave);


status_t FLEXIO_SPI_DRV_SlaveGetStatus(flexio_spi_slave_state_t *slave, uint32_t *bytesRemaining);


void FLEXIO_SPI_DRV_MasterGetDefaultConfig(flexio_spi_master_user_config_t * userConfigPtr);


void FLEXIO_SPI_DRV_SlaveGetDefaultConfig(flexio_spi_slave_user_config_t * userConfigPtr);


#if defined(__cplusplus)
}
#endif


#endif 

