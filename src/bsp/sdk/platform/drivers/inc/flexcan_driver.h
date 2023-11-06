
#ifndef FLEXCAN_DRIVER_H
#define FLEXCAN_DRIVER_H

#include "device_registers.h"
#include "osif.h"
#if FEATURE_CAN_HAS_DMA_ENABLE
#include "edma_driver.h"
#endif



typedef enum {
    FLEXCAN_RXFIFO_USING_INTERRUPTS,    
#if FEATURE_CAN_HAS_DMA_ENABLE
    FLEXCAN_RXFIFO_USING_DMA            
#endif
} flexcan_rxfifo_transfer_type_t;

typedef enum {
    FLEXCAN_EVENT_RX_COMPLETE,     
    FLEXCAN_EVENT_RXFIFO_COMPLETE, 
    FLEXCAN_EVENT_RXFIFO_WARNING,  
    FLEXCAN_EVENT_RXFIFO_OVERFLOW, 
    FLEXCAN_EVENT_TX_COMPLETE,     
#if FEATURE_CAN_HAS_WAKE_UP_IRQ
    FLEXCAN_EVENT_WAKEUP_TIMEOUT,  
    FLEXCAN_EVENT_WAKEUP_MATCH,    
    FLEXCAN_EVENT_SELF_WAKEUP,     
#endif 
#if FEATURE_CAN_HAS_DMA_ENABLE
	FLEXCAN_EVENT_DMA_COMPLETE,	  
	FLEXCAN_EVENT_DMA_ERROR,	  
#endif 
    FLEXCAN_EVENT_ERROR
} flexcan_event_type_t;

typedef enum {
    FLEXCAN_MB_IDLE,      
    FLEXCAN_MB_RX_BUSY,   
    FLEXCAN_MB_TX_BUSY,   
#if FEATURE_CAN_HAS_DMA_ENABLE
	FLEXCAN_MB_DMA_ERROR 
#endif
} flexcan_mb_state_t;

typedef enum {
    FLEXCAN_MSG_ID_STD,         
    FLEXCAN_MSG_ID_EXT          
} flexcan_msgbuff_id_type_t;

#if FEATURE_CAN_HAS_PE_CLKSRC_SELECT
typedef enum {
    FLEXCAN_CLK_SOURCE_OSC    = 0U,  
    FLEXCAN_CLK_SOURCE_PERIPH = 1U   
} flexcan_clk_source_t;
#endif

typedef struct {
    uint32_t cs;                        
    uint32_t msgId;                     
    uint8_t data[64];                   
    uint8_t dataLen;                    
} flexcan_msgbuff_t;

typedef struct {
    flexcan_msgbuff_t *mb_message;       
    semaphore_t mbSema;                  
    volatile flexcan_mb_state_t state;   
    bool isBlocking;                     
    bool isRemote;                       
} flexcan_mb_handle_t;

typedef struct FlexCANState {
    flexcan_mb_handle_t mbs[FEATURE_CAN_MAX_MB_NUM];           
    void (*callback)(uint8_t instance,
                     flexcan_event_type_t eventType,
                     uint32_t buffIdx,
                     struct FlexCANState *driverState);        
    void *callbackParam;                                       
    void (*error_callback)(uint8_t instance,
                           flexcan_event_type_t eventType,
                           struct FlexCANState *driverState);  
    void *errorCallbackParam;                                  
#if FEATURE_CAN_HAS_DMA_ENABLE
    uint8_t rxFifoDMAChannel;                                  
#endif
    flexcan_rxfifo_transfer_type_t transferType;               
} flexcan_state_t;

typedef struct {
    flexcan_msgbuff_id_type_t msg_id_type;  
    uint32_t data_length;                   
#if FEATURE_CAN_HAS_FD
    bool fd_enable;                         
    uint8_t fd_padding;                     
    bool enable_brs;                        
#endif
    bool is_remote;                         
} flexcan_data_info_t;

typedef enum {
    FLEXCAN_RX_FIFO_ID_FILTERS_8   = 0x0,         
    FLEXCAN_RX_FIFO_ID_FILTERS_16  = 0x1,         
    FLEXCAN_RX_FIFO_ID_FILTERS_24  = 0x2,         
    FLEXCAN_RX_FIFO_ID_FILTERS_32  = 0x3,         
    FLEXCAN_RX_FIFO_ID_FILTERS_40  = 0x4,         
    FLEXCAN_RX_FIFO_ID_FILTERS_48  = 0x5,         
    FLEXCAN_RX_FIFO_ID_FILTERS_56  = 0x6,         
    FLEXCAN_RX_FIFO_ID_FILTERS_64  = 0x7,         
    FLEXCAN_RX_FIFO_ID_FILTERS_72  = 0x8,         
    FLEXCAN_RX_FIFO_ID_FILTERS_80  = 0x9,         
    FLEXCAN_RX_FIFO_ID_FILTERS_88  = 0xA,         
    FLEXCAN_RX_FIFO_ID_FILTERS_96  = 0xB,         
    FLEXCAN_RX_FIFO_ID_FILTERS_104 = 0xC,         
    FLEXCAN_RX_FIFO_ID_FILTERS_112 = 0xD,         
    FLEXCAN_RX_FIFO_ID_FILTERS_120 = 0xE,         
    FLEXCAN_RX_FIFO_ID_FILTERS_128 = 0xF          
} flexcan_rx_fifo_id_filter_num_t;

typedef enum {
    FLEXCAN_RX_MASK_GLOBAL,      
    FLEXCAN_RX_MASK_INDIVIDUAL   
} flexcan_rx_mask_type_t;

typedef enum {
    FLEXCAN_RX_FIFO_ID_FORMAT_A, 
    FLEXCAN_RX_FIFO_ID_FORMAT_B, 
    FLEXCAN_RX_FIFO_ID_FORMAT_C, 
    FLEXCAN_RX_FIFO_ID_FORMAT_D  
} flexcan_rx_fifo_id_element_format_t;

typedef struct {
    bool isRemoteFrame;      
    bool isExtendedFrame;    
    uint32_t id;             
} flexcan_id_table_t;

typedef enum {
    FLEXCAN_NORMAL_MODE,        
    FLEXCAN_LISTEN_ONLY_MODE,   
    FLEXCAN_LOOPBACK_MODE,      
    FLEXCAN_FREEZE_MODE,        
    FLEXCAN_DISABLE_MODE        
} flexcan_operation_modes_t;

#if FEATURE_CAN_HAS_FD
typedef enum {
    FLEXCAN_PAYLOAD_SIZE_8 = 0,  
    FLEXCAN_PAYLOAD_SIZE_16 ,    
    FLEXCAN_PAYLOAD_SIZE_32 ,    
    FLEXCAN_PAYLOAD_SIZE_64      
} flexcan_fd_payload_size_t;
#endif

typedef struct {
    uint32_t propSeg;         
    uint32_t phaseSeg1;       
    uint32_t phaseSeg2;       
    uint32_t preDivider;      
    uint32_t rJumpwidth;      
} flexcan_time_segment_t;

typedef struct {
    uint32_t max_num_mb;                            
    flexcan_rx_fifo_id_filter_num_t num_id_filters; 
    bool is_rx_fifo_needed;                         
    flexcan_operation_modes_t flexcanMode;          
#if FEATURE_CAN_HAS_FD
    flexcan_fd_payload_size_t payload;              
    bool fd_enable;                                 
#endif
#if FEATURE_CAN_HAS_PE_CLKSRC_SELECT
    flexcan_clk_source_t pe_clock;                  
#endif
    flexcan_time_segment_t bitrate;                 
#if FEATURE_CAN_HAS_FD
    flexcan_time_segment_t bitrate_cbt;             
#endif
    flexcan_rxfifo_transfer_type_t transfer_type;   
#if FEATURE_CAN_HAS_DMA_ENABLE
    uint8_t rxFifoDMAChannel;                       
#endif
} flexcan_user_config_t;

#if FEATURE_CAN_HAS_PRETENDED_NETWORKING

typedef struct {
    bool extendedId;    
    bool remoteFrame;   
    uint32_t id;        
} flexcan_pn_id_filter_t;

typedef struct {
    uint8_t dlcLow;       
    uint8_t dlcHigh;      
    uint8_t payload1[8U]; 
    uint8_t payload2[8U]; 
} flexcan_pn_payload_filter_t;

typedef enum {
    FLEXCAN_FILTER_ID,                  
    FLEXCAN_FILTER_ID_PAYLOAD,          
    FLEXCAN_FILTER_ID_NTIMES,           
    FLEXCAN_FILTER_ID_PAYLOAD_NTIMES    
} flexcan_pn_filter_combination_t;

typedef enum {
    FLEXCAN_FILTER_MATCH_EXACT,   
    FLEXCAN_FILTER_MATCH_GEQ,     
    FLEXCAN_FILTER_MATCH_LEQ,     
    FLEXCAN_FILTER_MATCH_RANGE    
} flexcan_pn_filter_selection_t;

typedef struct {
    bool wakeUpTimeout;                               
    bool wakeUpMatch;                                 
    uint16_t numMatches;                              
    uint16_t matchTimeout;                            
    flexcan_pn_filter_combination_t filterComb;       
    flexcan_pn_id_filter_t idFilter1;                 
    flexcan_pn_id_filter_t idFilter2;                 
    flexcan_pn_filter_selection_t idFilterType;       
    flexcan_pn_filter_selection_t payloadFilterType;  
    flexcan_pn_payload_filter_t payloadFilter;        
} flexcan_pn_config_t;

#endif 

typedef void (*flexcan_callback_t)(uint8_t instance, flexcan_event_type_t eventType,
                                   uint32_t buffIdx, flexcan_state_t *flexcanState);

typedef void (*flexcan_error_callback_t)(uint8_t instance, flexcan_event_type_t eventType,
                                         flexcan_state_t *flexcanState);


#if defined(__cplusplus)
extern "C" {
#endif


void FLEXCAN_DRV_SetBitrate(uint8_t instance, const flexcan_time_segment_t *bitrate);

#if FEATURE_CAN_HAS_FD
void FLEXCAN_DRV_SetBitrateCbt(uint8_t instance, const flexcan_time_segment_t *bitrate);
#endif

void FLEXCAN_DRV_GetBitrate(uint8_t instance, flexcan_time_segment_t *bitrate);

#if FEATURE_CAN_HAS_FD
void FLEXCAN_DRV_GetBitrateFD(uint8_t instance, flexcan_time_segment_t *bitrate);
#endif



void FLEXCAN_DRV_SetRxMaskType(uint8_t instance, flexcan_rx_mask_type_t type);

void FLEXCAN_DRV_SetRxFifoGlobalMask(
    uint8_t instance,
    flexcan_msgbuff_id_type_t id_type,
    uint32_t mask);

void FLEXCAN_DRV_SetRxMbGlobalMask(
    uint8_t instance,
    flexcan_msgbuff_id_type_t id_type,
    uint32_t mask);

void FLEXCAN_DRV_SetRxMb14Mask(
    uint8_t instance,
    flexcan_msgbuff_id_type_t id_type,
    uint32_t mask);

void FLEXCAN_DRV_SetRxMb15Mask(
    uint8_t instance,
    flexcan_msgbuff_id_type_t id_type,
    uint32_t mask);

status_t FLEXCAN_DRV_SetRxIndividualMask(
    uint8_t instance,
    flexcan_msgbuff_id_type_t id_type,
    uint8_t mb_idx,
    uint32_t mask);



void FLEXCAN_DRV_GetDefaultConfig(flexcan_user_config_t *config);

status_t FLEXCAN_DRV_Init(
       uint8_t instance,
       flexcan_state_t *state,
       const flexcan_user_config_t *data);

status_t FLEXCAN_DRV_Deinit(uint8_t instance);

#if FEATURE_CAN_HAS_FD
void FLEXCAN_DRV_SetTDCOffset(uint8_t instance, bool enable, uint8_t offset);

uint8_t FLEXCAN_DRV_GetTDCValue(uint8_t instance);

bool FLEXCAN_DRV_GetTDCFail(uint8_t instance);

void FLEXCAN_DRV_ClearTDCFail(uint8_t instance);
#endif



status_t FLEXCAN_DRV_ConfigTxMb(
    uint8_t instance,
    uint8_t mb_idx,
    const flexcan_data_info_t *tx_info,
    uint32_t msg_id);

status_t FLEXCAN_DRV_ConfigRemoteResponseMb(
    uint8_t instance,
    uint8_t mb_idx,
    const flexcan_data_info_t *tx_info,
    uint32_t msg_id,
    const uint8_t *mb_data);

status_t FLEXCAN_DRV_SendBlocking(
    uint8_t instance,
    uint8_t mb_idx,
    const flexcan_data_info_t *tx_info,
    uint32_t msg_id,
    const uint8_t *mb_data,
    uint32_t timeout_ms);

status_t FLEXCAN_DRV_Send(
    uint8_t instance,
    uint8_t mb_idx,
    const flexcan_data_info_t *tx_info,
    uint32_t msg_id,
    const uint8_t *mb_data);



status_t FLEXCAN_DRV_ConfigRxMb(
    uint8_t instance,
    uint8_t mb_idx,
    const flexcan_data_info_t *rx_info,
    uint32_t msg_id);

void FLEXCAN_DRV_ConfigRxFifo(
    uint8_t instance,
    flexcan_rx_fifo_id_element_format_t id_format,
    const flexcan_id_table_t *id_filter_table);

status_t FLEXCAN_DRV_ReceiveBlocking(
    uint8_t instance,
    uint8_t mb_idx,
    flexcan_msgbuff_t *data,
    uint32_t timeout_ms);

status_t FLEXCAN_DRV_Receive(
    uint8_t instance,
    uint8_t mb_idx,
    flexcan_msgbuff_t *data);

status_t FLEXCAN_DRV_RxFifoBlocking(
    uint8_t instance,
    flexcan_msgbuff_t *data,
    uint32_t timeout_ms);

status_t FLEXCAN_DRV_RxFifo(
    uint8_t instance,
    flexcan_msgbuff_t *data);



status_t FLEXCAN_DRV_AbortTransfer(uint8_t instance, uint8_t mb_idx);

status_t FLEXCAN_DRV_GetTransferStatus(uint8_t instance, uint8_t mb_idx);

uint32_t FLEXCAN_DRV_GetErrorStatus(uint8_t instance);



void FLEXCAN_DRV_InstallEventCallback(uint8_t instance,
                                      flexcan_callback_t callback,
                                      void *callbackParam);

void FLEXCAN_DRV_InstallErrorCallback(uint8_t instance,
                                      flexcan_error_callback_t callback,
                                      void *callbackParam);


#if FEATURE_CAN_HAS_PRETENDED_NETWORKING


void FLEXCAN_DRV_ConfigPN(uint8_t instance, bool enable, const flexcan_pn_config_t *pnConfig);

void FLEXCAN_DRV_GetWMB(uint8_t instance, uint8_t wmbIndex, flexcan_msgbuff_t *wmb);


#endif 

#if FEATURE_CAN_HAS_SELF_WAKE_UP


status_t FLEXCAN_DRV_ConfigSelfWakeUp(uint8_t instance, bool enable, bool lowPassFilterEn);


#endif 

#ifdef __cplusplus
}
#endif


#endif 


