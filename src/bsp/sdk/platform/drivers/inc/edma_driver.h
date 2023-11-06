

#if !defined(EDMA_DRIVER_H)
#define EDMA_DRIVER_H

#include "device_registers.h"
#include "status.h"
#include <stddef.h>



#define STCD_SIZE(number)           (((number) * 32U) - 1U)
#define STCD_ADDR(address)          (((uint32_t)address + 31UL) & ~0x1FUL)

#define EDMA_ERR_LSB_MASK           1U

typedef enum {
    EDMA_CHN_ERR_INT = 0U,         
    EDMA_CHN_HALF_MAJOR_LOOP_INT,  
    EDMA_CHN_MAJOR_LOOP_INT        
} edma_channel_interrupt_t;

typedef enum {
    EDMA_ARBITRATION_FIXED_PRIORITY = 0U,  
    EDMA_ARBITRATION_ROUND_ROBIN           
} edma_arbitration_algorithm_t;

typedef enum {
    EDMA_CHN_PRIORITY_0 = 0U,
    EDMA_CHN_PRIORITY_1 = 1U,
    EDMA_CHN_PRIORITY_2 = 2U,
    EDMA_CHN_PRIORITY_3 = 3U,
#ifndef FEATURE_DMA_4_CH_PRIORITIES    
    EDMA_CHN_PRIORITY_4 = 4U,
    EDMA_CHN_PRIORITY_5 = 5U,
    EDMA_CHN_PRIORITY_6 = 6U,
    EDMA_CHN_PRIORITY_7 = 7U,
#ifndef FEATURE_DMA_8_CH_PRIORITIES
    EDMA_CHN_PRIORITY_8 = 8U,
    EDMA_CHN_PRIORITY_9 = 9U,
    EDMA_CHN_PRIORITY_10 = 10U,
    EDMA_CHN_PRIORITY_11 = 11U,
    EDMA_CHN_PRIORITY_12 = 12U,
    EDMA_CHN_PRIORITY_13 = 13U,
    EDMA_CHN_PRIORITY_14 = 14U,
    EDMA_CHN_PRIORITY_15 = 15U,
#endif
#endif
    EDMA_CHN_DEFAULT_PRIORITY = 255U
} edma_channel_priority_t;

#if FEATURE_DMA_CHANNEL_GROUP_COUNT > 0x1U
typedef enum {
#ifdef FEATURE_DMA_HWV3
    EDMA_CHN_GROUP_0 = 0U,
    EDMA_CHN_GROUP_1 = 1U,
    EDMA_CHN_GROUP_2 = 2U,
    EDMA_CHN_GROUP_3 = 3U,
    EDMA_CHN_GROUP_4 = 4U,
    EDMA_CHN_GROUP_5 = 5U,
    EDMA_CHN_GROUP_6 = 6U,
    EDMA_CHN_GROUP_7 = 7U,
    EDMA_CHN_GROUP_8 = 8U,
    EDMA_CHN_GROUP_9 = 9U,
    EDMA_CHN_GROUP_10 = 10U,
    EDMA_CHN_GROUP_11 = 11U,
    EDMA_CHN_GROUP_12 = 12U,
    EDMA_CHN_GROUP_13 = 13U,
    EDMA_CHN_GROUP_14 = 14U,
    EDMA_CHN_GROUP_15 = 15U,
    EDMA_CHN_GROUP_16 = 16U,
    EDMA_CHN_GROUP_17 = 17U,
    EDMA_CHN_GROUP_18 = 18U,
    EDMA_CHN_GROUP_19 = 19U,
    EDMA_CHN_GROUP_20 = 20U,
    EDMA_CHN_GROUP_21 = 21U,
    EDMA_CHN_GROUP_22 = 22U,
    EDMA_CHN_GROUP_23 = 23U,
    EDMA_CHN_GROUP_24 = 24U,
    EDMA_CHN_GROUP_25 = 25U,
    EDMA_CHN_GROUP_26 = 26U,
    EDMA_CHN_GROUP_27 = 27U,
    EDMA_CHN_GROUP_28 = 28U,
    EDMA_CHN_GROUP_29 = 29U,
    EDMA_CHN_GROUP_30 = 30U,
    EDMA_CHN_GROUP_31 = 31U
#else
    EDMA_GRP0_PRIO_LOW_GRP1_PRIO_HIGH = 0U,
    EDMA_GRP0_PRIO_HIGH_GRP1_PRIO_LOW = 1U
#endif
} edma_group_priority_t;
#endif

typedef enum {
    EDMA_MODULO_OFF = 0U,
    EDMA_MODULO_2B,
    EDMA_MODULO_4B,
    EDMA_MODULO_8B,
    EDMA_MODULO_16B,
    EDMA_MODULO_32B,
    EDMA_MODULO_64B,
    EDMA_MODULO_128B,
    EDMA_MODULO_256B,
    EDMA_MODULO_512B,
    EDMA_MODULO_1KB,
    EDMA_MODULO_2KB,
    EDMA_MODULO_4KB,
    EDMA_MODULO_8KB,
    EDMA_MODULO_16KB,
    EDMA_MODULO_32KB,
    EDMA_MODULO_64KB,
    EDMA_MODULO_128KB,
    EDMA_MODULO_256KB,
    EDMA_MODULO_512KB,
    EDMA_MODULO_1MB,
    EDMA_MODULO_2MB,
    EDMA_MODULO_4MB,
    EDMA_MODULO_8MB,
    EDMA_MODULO_16MB,
    EDMA_MODULO_32MB,
    EDMA_MODULO_64MB,
    EDMA_MODULO_128MB,
    EDMA_MODULO_256MB,
    EDMA_MODULO_512MB,
    EDMA_MODULO_1GB,
    EDMA_MODULO_2GB
} edma_modulo_t;

typedef enum {
#ifdef FEATURE_DMA_HWV3
    EDMA_TRANSFER_SIZE_1B  = 0x0U,
    EDMA_TRANSFER_SIZE_2B  = 0x1U,
    EDMA_TRANSFER_SIZE_4B  = 0x2U,
    EDMA_TRANSFER_SIZE_8B  = 0x3U,
    EDMA_TRANSFER_SIZE_16B = 0x4U,
    EDMA_TRANSFER_SIZE_32B = 0x5U,
    EDMA_TRANSFER_SIZE_64B = 0x6U
#else
    EDMA_TRANSFER_SIZE_1B  = 0x0U,
    EDMA_TRANSFER_SIZE_2B  = 0x1U,
    EDMA_TRANSFER_SIZE_4B  = 0x2U,
#ifdef FEATURE_DMA_TRANSFER_SIZE_8B
    EDMA_TRANSFER_SIZE_8B  = 0x3U,
#endif
#ifdef FEATURE_DMA_TRANSFER_SIZE_16B 
    EDMA_TRANSFER_SIZE_16B = 0x4U,
#endif
#ifdef FEATURE_DMA_TRANSFER_SIZE_32B
    EDMA_TRANSFER_SIZE_32B = 0x5U,
#endif    
#ifdef FEATURE_DMA_TRANSFER_SIZE_64B
    EDMA_TRANSFER_SIZE_64B = 0x6U
#endif
#endif
} edma_transfer_size_t;

typedef struct {
    edma_arbitration_algorithm_t chnArbitration;         
#if FEATURE_DMA_CHANNEL_GROUP_COUNT > 0x1U
#ifndef FEATURE_DMA_HWV3
    edma_arbitration_algorithm_t groupArbitration;       
    edma_group_priority_t groupPriority;                 
#endif
#endif
    bool haltOnError;                                    
} edma_user_config_t;

typedef enum {
    EDMA_CHN_NORMAL = 0U,           
    EDMA_CHN_ERROR                  
} edma_chn_status_t;

typedef void (*edma_callback_t)(void *parameter, edma_chn_status_t status);

typedef struct {
    uint8_t virtChn;                     
    edma_callback_t callback;            
    void *parameter;                     
    volatile edma_chn_status_t status;   
} edma_chn_state_t;

typedef struct {
#if FEATURE_DMA_CHANNEL_GROUP_COUNT > 0x1U
#ifdef FEATURE_DMA_HWV3
    edma_group_priority_t groupPriority;     
#endif
#endif
    edma_channel_priority_t channelPriority; 
    uint8_t virtChnConfig;                   
#ifdef FEATURE_DMAMUX_AVAILABLE    
    dma_request_source_t source;             
#endif    
    edma_callback_t callback;                
    void * callbackParam;                    
    bool enableTrigger;                      			
} edma_channel_config_t;

typedef enum {
    EDMA_TRANSFER_PERIPH2MEM = 0U,   
    EDMA_TRANSFER_MEM2PERIPH,        
    EDMA_TRANSFER_MEM2MEM,           
    EDMA_TRANSFER_PERIPH2PERIPH      
} edma_transfer_type_t;

typedef struct {
    uint32_t address;           
    uint32_t length;            
    edma_transfer_type_t type;  
} edma_scatter_gather_list_t;

typedef struct {
    edma_chn_state_t * volatile virtChnState[(uint32_t)FEATURE_DMA_VIRTUAL_CHANNELS];   
} edma_state_t;

typedef struct {
    uint32_t majorLoopIterationCount;       
    bool srcOffsetEnable;                   
    bool dstOffsetEnable;                   
    int32_t minorLoopOffset;                
    bool minorLoopChnLinkEnable;            
    uint8_t minorLoopChnLinkNumber;         
    bool majorLoopChnLinkEnable;            
    uint8_t majorLoopChnLinkNumber;         
} edma_loop_transfer_config_t;

typedef struct {
    uint32_t srcAddr;                                 
    uint32_t destAddr;                                
    edma_transfer_size_t srcTransferSize;             
    edma_transfer_size_t destTransferSize;            
    int16_t srcOffset;                                
    int16_t destOffset;                               
    int32_t srcLastAddrAdjust;                        
    int32_t destLastAddrAdjust;                       
    edma_modulo_t srcModulo;                          
    edma_modulo_t destModulo;                         
    uint32_t minorByteTransferCount;                  
    bool scatterGatherEnable;                         
    uint32_t scatterGatherNextDescAddr;               
    bool interruptEnable;                             
    edma_loop_transfer_config_t *loopTransferConfig;  
} edma_transfer_config_t;

#if (defined(CORE_LITTLE_ENDIAN))
typedef struct {
    uint32_t SADDR;
    int16_t SOFF;
    uint16_t ATTR;
    uint32_t NBYTES;
    int32_t SLAST;
    uint32_t DADDR;
    int16_t DOFF;
    uint16_t CITER;
    int32_t DLAST_SGA;
    uint16_t CSR;
    uint16_t BITER;
} edma_software_tcd_t;
#elif (defined(CORE_BIG_ENDIAN))
typedef struct {
    uint32_t SADDR;
    uint16_t ATTR;
    int16_t SOFF;
    uint32_t NBYTES;
    int32_t SLAST;
    uint32_t DADDR;
    uint16_t CITER;
    int16_t DOFF;
    int32_t DLAST_SGA;
    uint16_t BITER;
    uint16_t CSR;
} edma_software_tcd_t;
#else
    #error "Endianness not defined!"
#endif


#if defined(__cplusplus)
extern "C" {
#endif



status_t EDMA_DRV_Init(edma_state_t * edmaState,
                       const edma_user_config_t *userConfig,
                       edma_chn_state_t * const chnStateArray[],
                       const edma_channel_config_t * const chnConfigArray[],
                       uint32_t chnCount);

status_t EDMA_DRV_Deinit(void);



status_t EDMA_DRV_ChannelInit(edma_chn_state_t *edmaChannelState,
                              const edma_channel_config_t *edmaChannelConfig);

status_t EDMA_DRV_ReleaseChannel(uint8_t virtualChannel);



void EDMA_DRV_PushConfigToReg(uint8_t virtualChannel,
                              const edma_transfer_config_t *tcd);

void EDMA_DRV_PushConfigToSTCD(const edma_transfer_config_t *config,
                               edma_software_tcd_t *stcd);

status_t EDMA_DRV_ConfigSingleBlockTransfer(uint8_t virtualChannel,
                                            edma_transfer_type_t type,
                                            uint32_t srcAddr,
                                            uint32_t destAddr,
                                            edma_transfer_size_t transferSize,
                                            uint32_t dataBufferSize);

status_t EDMA_DRV_ConfigMultiBlockTransfer(uint8_t virtualChannel,
                                           edma_transfer_type_t type,
                                           uint32_t srcAddr,
                                           uint32_t destAddr,
                                           edma_transfer_size_t transferSize,
                                           uint32_t blockSize,
                                           uint32_t blockCount,
                                           bool disableReqOnCompletion);

status_t EDMA_DRV_ConfigLoopTransfer(uint8_t virtualChannel,
                                     const edma_transfer_config_t *transferConfig);

status_t EDMA_DRV_ConfigScatterGatherTransfer(uint8_t virtualChannel,
                                              edma_software_tcd_t *stcd,
                                              edma_transfer_size_t transferSize,
                                              uint32_t bytesOnEachRequest,
                                              const edma_scatter_gather_list_t *srcList,
                                              const edma_scatter_gather_list_t *destList,
                                              uint8_t tcdCount);

void EDMA_DRV_CancelTransfer(bool error);


status_t EDMA_DRV_StartChannel(uint8_t virtualChannel);

status_t EDMA_DRV_StopChannel(uint8_t virtualChannel);

status_t EDMA_DRV_SetChannelRequestAndTrigger(uint8_t virtualChannel,
                                              uint8_t request,
                                              bool enableTrigger);

void EDMA_DRV_ClearTCD(uint8_t virtualChannel);

void EDMA_DRV_SetSrcAddr(uint8_t virtualChannel,
                         uint32_t address);

void EDMA_DRV_SetSrcOffset(uint8_t virtualChannel,
                           int16_t offset);

void EDMA_DRV_SetSrcReadChunkSize(uint8_t virtualChannel,
                                  edma_transfer_size_t size);

void EDMA_DRV_SetSrcLastAddrAdjustment(uint8_t virtualChannel,
                                       int32_t adjust);

void EDMA_DRV_SetDestAddr(uint8_t virtualChannel,
                          uint32_t address);

void EDMA_DRV_SetDestOffset(uint8_t virtualChannel,
                            int16_t offset);

void EDMA_DRV_SetDestWriteChunkSize(uint8_t virtualChannel,
                                    edma_transfer_size_t size);

void EDMA_DRV_SetDestLastAddrAdjustment(uint8_t virtualChannel,
                                        int32_t adjust);

void EDMA_DRV_SetMinorLoopBlockSize(uint8_t virtualChannel,
                                    uint32_t nbytes);

void EDMA_DRV_SetMajorLoopIterationCount(uint8_t virtualChannel,
                                         uint32_t majorLoopCount);

uint32_t EDMA_DRV_GetRemainingMajorIterationsCount(uint8_t virtualChannel);

void EDMA_DRV_SetScatterGatherLink(uint8_t virtualChannel,
                                   uint32_t nextTCDAddr);

void EDMA_DRV_DisableRequestsOnTransferComplete(uint8_t virtualChannel,
                                                bool disable);

void EDMA_DRV_ConfigureInterrupt(uint8_t virtualChannel,
                                 edma_channel_interrupt_t intSrc,
                                 bool enable);

void EDMA_DRV_TriggerSwRequest(uint8_t virtualChannel);



status_t EDMA_DRV_InstallCallback(uint8_t virtualChannel,
                                  edma_callback_t callback,
                                  void *parameter);


edma_chn_status_t EDMA_DRV_GetChannelStatus(uint8_t virtualChannel);



#if defined(__cplusplus)
}
#endif


#endif 


