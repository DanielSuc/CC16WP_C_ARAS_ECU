
#if !defined(LPI2C_DRIVER_H)
#define LPI2C_DRIVER_H

#include <stddef.h>
#include <stdbool.h>
#include "device_registers.h"
#include "status.h"
#include "edma_driver.h"
#include "osif.h"
#include "callbacks.h"




#define LPI2C_MASTER_CMD_QUEUE_SIZE   5U

typedef enum
{
    LPI2C_STANDARD_MODE      = 0x0U,   
    LPI2C_FAST_MODE          = 0x1U,   
#if(LPI2C_HAS_FAST_PLUS_MODE)
    LPI2C_FASTPLUS_MODE      = 0x2U,   
#endif
#if(LPI2C_HAS_HIGH_SPEED_MODE)
    LPI2C_HIGHSPEED_MODE     = 0x3U,   
#endif
#if(LPI2C_HAS_ULTRA_FAST_MODE)
    LPI2C_ULTRAFAST_MODE     = 0x4U    
#endif
} lpi2c_mode_t;

typedef enum
{
   LPI2C_USING_DMA         = 0,    
   LPI2C_USING_INTERRUPTS  = 1,    
} lpi2c_transfer_type_t;



typedef struct
{
    uint16_t slaveAddress;                      
    bool is10bitAddr;                           
    lpi2c_mode_t operatingMode;                 
    uint32_t baudRate;                          
#if(LPI2C_HAS_HIGH_SPEED_MODE)
    uint32_t baudRateHS;                        
    uint8_t masterCode;                         
#endif
    lpi2c_transfer_type_t transferType;         
    uint8_t dmaChannel;                         
    i2c_master_callback_t masterCallback;     
    void *callbackParam;                        
} lpi2c_master_user_config_t;

typedef struct
{
    uint16_t slaveAddress;                      
    bool is10bitAddr;                           
    lpi2c_mode_t operatingMode;                 
    bool slaveListening;                        
    lpi2c_transfer_type_t transferType;         
    uint8_t dmaChannel;                       
    i2c_slave_callback_t slaveCallback;       
    void *callbackParam;                        
} lpi2c_slave_user_config_t;

typedef struct
{
    uint32_t baudRate;
#if(LPI2C_HAS_HIGH_SPEED_MODE)
    uint32_t baudRateHS;
#endif
} lpi2c_baud_rate_params_t;

typedef enum
{
    LPI2C_MASTER_COMMAND_TRANSMIT         = 0U,  
    LPI2C_MASTER_COMMAND_RECEIVE          = 1U,  
    LPI2C_MASTER_COMMAND_STOP             = 2U,  
    LPI2C_MASTER_COMMAND_RECEIVE_DISCARD  = 3U,  
    LPI2C_MASTER_COMMAND_START            = 4U,  
    LPI2C_MASTER_COMMAND_START_NACK       = 5U,  
    LPI2C_MASTER_COMMAND_START_HS         = 6U,  
    LPI2C_MASTER_COMMAND_START_NACK_HS    = 7U,  
} lpi2c_master_command_t;

typedef struct
{
    lpi2c_master_command_t cmd[LPI2C_MASTER_CMD_QUEUE_SIZE];
    uint8_t data[LPI2C_MASTER_CMD_QUEUE_SIZE];
    uint8_t writeIdx;
    uint8_t readIdx;
} lpi2c_master_cmd_queue_t;

typedef struct
{
    lpi2c_master_cmd_queue_t cmdQueue;      
    uint8_t * rxBuff;                       
    uint32_t rxSize;                        
    const uint8_t * txBuff;                 
    uint32_t txSize;                        
    volatile status_t status;               
    lpi2c_mode_t operatingMode;             
    uint16_t slaveAddress;                  
    volatile bool i2cIdle;                  
#if(LPI2C_HAS_HIGH_SPEED_MODE)
    uint8_t masterCode;                     
    bool highSpeedInProgress;               
    uint32_t baudRateHS;                    
#endif
    bool sendStop;                          
    bool is10bitAddr;                       
    semaphore_t idleSemaphore;              
    bool blocking;                          
    lpi2c_transfer_type_t transferType;     
    uint8_t dmaChannel;                     
    i2c_master_callback_t masterCallback; 
    void *callbackParam;                    
    bool abortedTransfer;                   
    uint32_t baudrate;                      
} lpi2c_master_state_t;

typedef struct
{
    status_t status;                  
    volatile bool isTransferInProgress;     
    uint32_t txSize;                        
    uint32_t rxSize;                        
    const uint8_t * txBuff;                 
    uint8_t * rxBuff;                       
    lpi2c_mode_t operatingMode;             
    bool slaveListening;                    
    bool is10bitAddress;                    
    uint8_t repeatedStarts;                 
    bool txUnderrunWarning;                 
    semaphore_t idleSemaphore;              
    bool blocking;                          
    lpi2c_transfer_type_t transferType;     
    uint8_t dmaChannel;                                     
    i2c_slave_callback_t slaveCallback;   
    void *callbackParam;                    
} lpi2c_slave_state_t;


#if defined(__cplusplus)
extern "C" {
#endif


status_t LPI2C_DRV_MasterInit(uint32_t instance,
                                    const lpi2c_master_user_config_t * userConfigPtr,
                                    lpi2c_master_state_t * master);


status_t LPI2C_DRV_MasterDeinit(uint32_t instance);


void LPI2C_DRV_MasterGetBaudRate(uint32_t instance, lpi2c_baud_rate_params_t *baudRate);


status_t LPI2C_DRV_MasterSetBaudRate(uint32_t instance,
                                const lpi2c_mode_t operatingMode,
                                const lpi2c_baud_rate_params_t baudRate);


void LPI2C_DRV_MasterSetSlaveAddr(uint32_t instance, const uint16_t address, const bool is10bitAddr);


status_t LPI2C_DRV_MasterSendData(uint32_t instance,
                                            const uint8_t * txBuff,
                                            uint32_t txSize,
                                            bool sendStop);


status_t LPI2C_DRV_MasterSendDataBlocking(uint32_t instance,
                                    const uint8_t * txBuff,
                                    uint32_t txSize,
                                    bool sendStop,
                                    uint32_t timeout);


status_t LPI2C_DRV_MasterAbortTransferData(uint32_t instance);


status_t LPI2C_DRV_MasterReceiveData(uint32_t  instance,
                                               uint8_t * rxBuff,
                                               uint32_t rxSize,
                                               bool sendStop);


status_t LPI2C_DRV_MasterReceiveDataBlocking(uint32_t instance,
                                       uint8_t * rxBuff,
                                       uint32_t rxSize,
                                       bool sendStop,
                                       uint32_t timeout);


status_t LPI2C_DRV_MasterGetTransferStatus(uint32_t instance, uint32_t *bytesRemaining);


void LPI2C_DRV_MasterIRQHandler(uint32_t instance);


status_t LPI2C_DRV_SlaveInit(uint32_t instance,
                               const lpi2c_slave_user_config_t * userConfigPtr,
                               lpi2c_slave_state_t * slave);


status_t LPI2C_DRV_SlaveDeinit(uint32_t instance);


status_t LPI2C_DRV_SlaveSetTxBuffer(uint32_t instance,
                                            const uint8_t * txBuff,
                                            uint32_t txSize);


status_t LPI2C_DRV_SlaveSetRxBuffer(uint32_t instance,
                                            uint8_t * rxBuff,
                                            uint32_t  rxSize);


status_t LPI2C_DRV_SlaveSendData(uint32_t instance,
                                   const uint8_t * txBuff,
                                   uint32_t txSize);


status_t LPI2C_DRV_SlaveSendDataBlocking(uint32_t    instance,
                                           const uint8_t *  txBuff,
                                           uint32_t txSize,
                                           uint32_t timeout);


status_t LPI2C_DRV_SlaveReceiveData(uint32_t   instance,
                                       uint8_t * rxBuff,
                                       uint32_t  rxSize);


status_t LPI2C_DRV_SlaveReceiveDataBlocking(uint32_t instance,
                                                uint8_t  * rxBuff,
                                                uint32_t rxSize,
                                                uint32_t timeout);


status_t LPI2C_DRV_SlaveGetTransferStatus(uint32_t instance,
                                            uint32_t *bytesRemaining);


status_t LPI2C_DRV_SlaveAbortTransferData(uint32_t instance);


void LPI2C_DRV_SlaveIRQHandler(uint32_t instance);

void LPI2C_DRV_MasterGetDefaultConfig(lpi2c_master_user_config_t * config);

void LPI2C_DRV_SlaveGetDefaultConfig(lpi2c_slave_user_config_t *config);

#if defined(S32K11x_SERIES)
void LPI2C_DRV_ModuleIRQHandler(uint32_t instance);
#endif

#if defined(__cplusplus)
}
#endif


#endif 

