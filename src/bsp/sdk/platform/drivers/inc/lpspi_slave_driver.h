

#ifndef LPSPI_SLAVE_DRIVER_H
#define LPSPI_SLAVE_DRIVER_H

#include "lpspi_shared_function.h"






typedef struct 
{
    lpspi_signal_polarity_t pcsPolarity; 
    uint16_t bitcount;                   
    lpspi_clock_phase_t clkPhase;        
    lpspi_which_pcs_t whichPcs;
    lpspi_sck_polarity_t clkPolarity;    
    bool lsbFirst;                       
    lpspi_transfer_type transferType;    
    uint8_t rxDMAChannel;                
    uint8_t txDMAChannel;                
    spi_callback_t callback;             
    void *callbackParam;                 
} lpspi_slave_config_t;



#if defined(__cplusplus)
extern "C" {
#endif


 void LPSPI_DRV_SlaveGetDefaultConfig(lpspi_slave_config_t * spiConfig);

status_t LPSPI_DRV_SlaveInit(uint32_t instance,
                               lpspi_state_t * lpspiState,
                               const lpspi_slave_config_t * slaveConfig);

status_t LPSPI_DRV_SlaveDeinit(uint32_t instance);

status_t LPSPI_DRV_SlaveTransferBlocking(uint32_t instance,
                                           const uint8_t *sendBuffer,
                                           uint8_t *receiveBuffer,
                                           uint16_t transferByteCount,
                                           uint32_t timeout);

status_t LPSPI_DRV_SlaveTransfer(uint32_t instance,
                                   const uint8_t *sendBuffer,
                                   uint8_t *receiveBuffer,
                                   uint16_t transferByteCount);

status_t LPSPI_DRV_SlaveAbortTransfer(uint32_t instance);

status_t LPSPI_DRV_SlaveGetTransferStatus(uint32_t instance,
                                            uint32_t * bytesRemained);

void LPSPI_DRV_SlaveIRQHandler(uint32_t instance);

#if defined(__cplusplus)
}
#endif




#endif 



