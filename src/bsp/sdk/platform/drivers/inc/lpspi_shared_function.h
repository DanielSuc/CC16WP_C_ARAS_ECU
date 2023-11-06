

#ifndef LPSPI_SHARED_FUNCTION_H
#define LPSPI_SHARED_FUNCTION_H

#include <stdbool.h>
#include "edma_driver.h"
#include "clock_manager.h"
#include "osif.h"
#include "status.h"
#include "callbacks.h"



extern void LPSPI_DRV_MasterIRQHandler(uint32_t instance);

extern void LPSPI_DRV_SlaveIRQHandler(uint32_t instance);

typedef enum
{
    LPSPI_PCS0 = 0U, 
    LPSPI_PCS1 = 1U, 
    LPSPI_PCS2 = 2U, 
    LPSPI_PCS3 = 3U  
} lpspi_which_pcs_t;

typedef enum
{
    LPSPI_ACTIVE_HIGH = 1U, 
    LPSPI_ACTIVE_LOW  = 0U  
} lpspi_signal_polarity_t;

typedef enum
{
    LPSPI_CLOCK_PHASE_1ST_EDGE = 0U, 
    LPSPI_CLOCK_PHASE_2ND_EDGE = 1U  
} lpspi_clock_phase_t;

typedef enum
{
    LPSPI_SCK_ACTIVE_HIGH = 0U, 
    LPSPI_SCK_ACTIVE_LOW  = 1U  
} lpspi_sck_polarity_t;


typedef enum
{
    LPSPI_USING_DMA         = 0,    
    LPSPI_USING_INTERRUPTS,         
} lpspi_transfer_type;

typedef enum
{
    LPSPI_TRANSFER_OK = 0U,    
    LPSPI_TRANSMIT_FAIL,       
    LPSPI_RECEIVE_FAIL         
} transfer_status_t;

typedef struct
{
    uint16_t bitsPerFrame;               
    uint16_t bytesPerFrame;              
    bool isPcsContinuous;                
    bool isBlocking;                     
    uint32_t lpspiSrcClk;                
    volatile bool isTransferInProgress;  
    const uint8_t * txBuff;                      
    uint8_t * rxBuff;                    
    volatile uint16_t txCount;           
    volatile uint16_t rxCount;           
    volatile uint16_t txFrameCnt;        
    volatile uint16_t rxFrameCnt;        
    volatile bool lsb;                   
    uint8_t fifoSize;                    
    uint8_t rxDMAChannel;                
    uint8_t txDMAChannel;                
    lpspi_transfer_type transferType;    
    semaphore_t lpspiSemaphore;          
    transfer_status_t status;            
    spi_callback_t callback;             
    void *callbackParam;                 
    uint32_t dummy;                      
} lpspi_state_t;

extern LPSPI_Type * g_lpspiBase[LPSPI_INSTANCE_COUNT];

extern IRQn_Type g_lpspiIrqId[LPSPI_INSTANCE_COUNT];

extern lpspi_state_t * g_lpspiStatePtr[LPSPI_INSTANCE_COUNT];


void LPSPI_DRV_IRQHandler(uint32_t instance);

void LPSPI_DRV_FillupTxBuffer(uint32_t instance);

void LPSPI_DRV_ReadRXBuffer(uint32_t instance);

void LPSPI_DRV_DisableTEIEInterrupts(uint32_t instance);


#endif 


