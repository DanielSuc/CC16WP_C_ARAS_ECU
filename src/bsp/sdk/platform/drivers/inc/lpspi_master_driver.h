

#ifndef LPSPI_MASTER_DRIVER_H
#define LPSPI_MASTER_DRIVER_H

#include "lpspi_shared_function.h"




typedef struct
{
    uint32_t bitsPerSec;                 
    lpspi_which_pcs_t whichPcs;          
    lpspi_signal_polarity_t pcsPolarity; 
    bool isPcsContinuous;                
    uint16_t bitcount;                   
    uint32_t lpspiSrcClk;                
    lpspi_clock_phase_t clkPhase;        
    lpspi_sck_polarity_t clkPolarity;    
    bool lsbFirst;                       
    lpspi_transfer_type transferType;    
    uint8_t rxDMAChannel;                
    uint8_t txDMAChannel;                
    spi_callback_t callback;             
    void *callbackParam;                 
} lpspi_master_config_t;



#if defined(__cplusplus)
extern "C" {
#endif



 void LPSPI_DRV_MasterGetDefaultConfig(lpspi_master_config_t * spiConfig);

status_t LPSPI_DRV_MasterInit(uint32_t instance, lpspi_state_t * lpspiState,
                                    const lpspi_master_config_t * spiConfig);

status_t LPSPI_DRV_MasterDeinit(uint32_t instance);

status_t LPSPI_DRV_MasterSetDelay(uint32_t instance, uint32_t delayBetwenTransfers,
                        uint32_t delaySCKtoPCS, uint32_t delayPCStoSCK);




status_t LPSPI_DRV_MasterConfigureBus(uint32_t instance,
                                            const lpspi_master_config_t * spiConfig,
                                            uint32_t * calculatedBaudRate);

status_t LPSPI_DRV_SetPcs(uint32_t instance, lpspi_which_pcs_t whichPcs, lpspi_signal_polarity_t polarity);



status_t LPSPI_DRV_MasterTransferBlocking(uint32_t instance,
                                                const uint8_t * sendBuffer,
                                                uint8_t * receiveBuffer,
                                                uint16_t transferByteCount,
                                                uint32_t timeout);



status_t LPSPI_DRV_MasterTransfer(uint32_t instance,
                                        const uint8_t * sendBuffer,
                                        uint8_t * receiveBuffer,
                                        uint16_t transferByteCount);

status_t LPSPI_DRV_MasterGetTransferStatus(uint32_t instance, uint32_t * bytesRemained);

status_t LPSPI_DRV_MasterAbortTransfer(uint32_t instance);

void LPSPI_DRV_MasterIRQHandler(uint32_t instance);


#if defined(__cplusplus)
}
#endif



#endif 

