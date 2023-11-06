
#ifndef SAI_DRIVER_H_
#define SAI_DRIVER_H_

#include <stddef.h>
#include <stdbool.h>
#include "device_registers.h"
#include "clock_manager.h"
#include "interrupt_manager.h"
#include "edma_driver.h"
#include "osif.h"


#define SAI_CHANNEL_0 0x1
#define SAI_CHANNEL_1 0x2
#define SAI_CHANNEL_2 0x4
#define SAI_CHANNEL_3 0x8

typedef struct
{
    uint32_t count;
    uint8_t *data;
} sai_xfer_state_t;

typedef enum
{
    SAI_RX_COMPLETE         = 0x00U, 
    SAI_TX_COMPLETE         = 0x01U, 
    SAI_ERROR               = 0x03U, 
    SAI_FRAME_START         = 0x05U, 
    SAI_RUN_ERROR           = 0x06U, 
    SAI_SYNC_ERROR          = 0x07U, 
} sai_report_type_t;

typedef void (*sai_transfer_callback_t)(sai_report_type_t event, void *userData);

typedef enum
{
    SAI_INTERRUPT = 0U,     
    SAI_DMA                 
} sai_transfer_type_t;

typedef enum
{
    SAI_MUX_DISABLED = 0U,  
    SAI_MUX_LINE = 1U,      
    SAI_MUX_MEM = 2U        
} sai_mux_mode_t;

typedef struct
{
    sai_xfer_state_t ChnState[SAI_MAX_CHANNEL_COUNT];   
    volatile status_t status;
    uint8_t DmaChannel[SAI_MAX_CHANNEL_COUNT];          
    uint8_t ElementSize;                                
    bool Blocking;
    sai_transfer_type_t XferType;
    semaphore_t Sema;
    sai_mux_mode_t mux;                                 
    uint8_t ChannelCount;                               
    uint8_t NextChn;                                    
    sai_transfer_callback_t Callback;
    void* callbackParam;
    uint32_t cr4;                                   
} sai_state_t;

typedef enum
{
    SAI_ASYNC        = 0U,         
    SAI_SYNC_WITH_OTHER = 1U,      
#ifdef FEATURE_SAI_SYNC_WITH_OTHER_INST
    SAI_SYNC_WITH_SAI2_SAME = 2U,  
    SAI_SYNC_WITH_SAI2_OTHER = 3U  
#endif 
} sai_sync_mode_t;

typedef enum
{
#ifdef FEATURE_SAI_MSEL_BUS_CLK
    SAI_BUS_CLK = 0U,       
#endif
#ifdef FEATURE_SAI_MSEL_MCLK_PIN
    SAI_EXTERNAL_CLK = 1U,   
#endif
#ifdef FEATURE_SAI_MSEL_FCD
    SAI_FCD_CLK = 1U,
#endif
#ifdef FEATURE_SAI_MSEL_SOSC_CLK
    SAI_SOSC_CLK = 2U,       
#endif
#ifdef FEATURE_SAI_MSEL_OTHER_MCLK_PIN
    SAI_EXTERNAL_CLK_1 = 2U, 
    SAI_EXTERNAL_CLK_2 = 3U, 
#endif
} sai_master_clk_source_t;

#ifdef FEATURE_SAI_MSEL_FCD
typedef enum
{
    SAI_FCD_PLL = 0U,     
    SAI_FCD_FXOSC = 2U,   
    SAI_FCD_MCLK = 3U,    
} sai_fcd_clock_source_t;
#endif 

#ifdef FEATURE_SAI_HAS_CHMOD
typedef enum
{
    SAI_MASK_TRISTATE = 0U,     
    SAI_MASK_ZERO = 1U          
} sai_mask_mode_t;
#endif 

typedef struct
{
    sai_sync_mode_t SyncMode;               
    sai_master_clk_source_t MasterClkSrc;   
    bool BitClkNegPolar;                    
    bool BitClkInternal;                    
    uint16_t BitClkDiv;                     
    uint8_t ChannelEnable;                  
    uint8_t FrameSize;                      
    uint8_t SyncWidth;                      
#ifdef FEATURE_SAI_HAS_CHMOD
    sai_mask_mode_t MaskMode;               
#endif
    bool MsbFirst;                          
    bool SyncEarly;                         
    bool SyncNegPolar;                      
    bool SyncInternal;                      
    uint8_t Word0Width;                     
    uint8_t WordNWidth;                     
    uint8_t FirstBitIndex;                  
    uint32_t BitClkFreq;                    
    bool RunErrorReport;                    
    bool SyncErrorReport;                   
    bool FrameStartReport;                  
    sai_mux_mode_t MuxMode;                 
    sai_transfer_type_t TransferType;       
    uint8_t DmaChannel[SAI_MAX_CHANNEL_COUNT];   
    uint8_t ElementSize;                    
    uint8_t ChannelCount;                   
    sai_transfer_callback_t callback;       
    void* callbackParam;                    

} sai_user_config_t;

#if defined(__cplusplus)
extern "C" {
#endif


#ifdef FEATURE_SAI_MSEL_FCD
void SAI_DRV_FCDInit(uint32_t instNum,
                     sai_fcd_clock_source_t fcdSource,
                     uint32_t freqDivisor,
                     bool MclkBypassFcd);

void SAI_DRV_GetFCDFreq(uint32_t instNum, uint32_t* freq);
#endif 

void SAI_DRV_SetMaster(uint32_t instNum,
                       bool tx);


void SAI_DRV_TxInit(uint32_t instNum,
                   const sai_user_config_t* saiUserConfig,
                   sai_state_t* StateAlloc);

void SAI_DRV_RxInit(uint32_t instNum,
                    const sai_user_config_t* saiUserConfig,
                    sai_state_t* StateAlloc);

void SAI_DRV_TxDeinit(uint32_t instNum);

void SAI_DRV_RxDeinit(uint32_t instNum);

uint32_t SAI_DRV_TxGetBitClockFreq(uint32_t instNum);

uint32_t SAI_DRV_RxGetBitClockFreq(uint32_t instNum);

uint32_t SAI_DRV_TxGetBitClockDiv(uint32_t instNum);

uint32_t SAI_DRV_RxGetBitClockDiv(uint32_t instNum);

void SAI_DRV_TxSetNextMaskWords(uint32_t instNum, uint16_t Words);

void SAI_DRV_RxSetNextMaskWords(uint32_t instNum, uint16_t Words);

status_t SAI_DRV_SendBlocking(uint32_t instNum,
                              const uint8_t* data[],
                              uint32_t count,
                              uint32_t timeout);

void SAI_DRV_Send(uint32_t instNum,
                  const uint8_t* data[],
                  uint32_t count);

status_t SAI_DRV_GetSendingStatus(uint32_t instNum,
                                  uint32_t *countRemain);

void SAI_DRV_AbortSending(uint32_t instNum);

status_t SAI_DRV_ReceiveBlocking(uint32_t instNum,
                                 uint8_t* data[],
                                 uint32_t count,
                                 uint32_t timeout);

void SAI_DRV_Receive(uint32_t instNum,
                     uint8_t* data[],
                     uint32_t count);

status_t SAI_DRV_GetReceivingStatus(uint32_t instNum,
                                    uint32_t *countRemain);

void SAI_DRV_AbortReceiving(uint32_t instNum);


void SAI_DRV_GetDefaultConfig(sai_user_config_t* uc);

#if defined(__cplusplus)
}
#endif

#endif 

