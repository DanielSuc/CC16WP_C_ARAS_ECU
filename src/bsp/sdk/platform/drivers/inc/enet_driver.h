
#ifndef ENET_H
#define ENET_H

#include "device_registers.h"
#include "status.h"
#include "osif.h"
#include <stdlib.h>




#define ENET_FRAME_MAX_FRAMELEN         1518U
#define ENET_MIN_BUFFERSIZE             64U

#define ENET_BUFF_ALIGN(x)       (((uint32_t)(x) + (FEATURE_ENET_BUFF_ALIGNMENT - 1UL)) & ~(FEATURE_ENET_BUFF_ALIGNMENT - 1UL))
#define ENET_BUFF_IS_ALIGNED(x)  (((uint32_t)(x) & ~(FEATURE_ENET_BUFF_ALIGNMENT - 1UL)) != 0UL)

#define ENET_BUFFDESCR_ALIGN(x)       (((uint32_t)(x) + (FEATURE_ENET_BUFFDESCR_ALIGNMENT - 1UL)) & ~(FEATURE_ENET_BUFFDESCR_ALIGNMENT - 1UL))
#define ENET_BUFFDESCR_IS_ALIGNED(x)  (((uint32_t)(x) & ~(FEATURE_ENET_BUFFDESCR_ALIGNMENT - 1UL)) != 0UL)

#define ENET_TX_WATERMARK_SHIFT       (6U)
#define ENET_TX_WATERMARK_MASK        (0x3FU)

typedef enum
{
    ENET_MII_MODE = 0U, 
    ENET_RMII_MODE,     
#if FEATURE_ENET_HAS_RGMII
	ENET_RGMII_MODE
#endif 
} enet_mii_mode_t;

typedef enum
{
    ENET_MII_SPEED_10M = 0U,  
    ENET_MII_SPEED_100M,      
#if FEATURE_ENET_HAS_SPEED_1000M
	ENET_MII_SPEED_1000M      
#endif 
} enet_mii_speed_t;

typedef enum
{
    ENET_MII_HALF_DUPLEX = 0U, 
    ENET_MII_FULL_DUPLEX       
} enet_mii_duplex_t;

typedef enum
{
    ENET_RX_CONFIG_ENABLE_PAYLOAD_LEN_CHECK  = 0x0001U,
    ENET_RX_CONFIG_STRIP_CRC_FIELD           = 0x0002U,
    ENET_RX_CONFIG_FORWARD_PAUSE_FRAMES      = 0x0004U,
    ENET_RX_CONFIG_REMOVE_PADDING            = 0x0008U,
    ENET_RX_CONFIG_ENABLE_FLOW_CONTROL       = 0x0010U,
    ENET_RX_CONFIG_REJECT_BROADCAST_FRAMES   = 0x0020U,
    ENET_RX_CONFIG_ENABLE_PROMISCUOUS_MODE   = 0x0040U,
    ENET_RX_CONFIG_ENABLE_MII_LOOPBACK       = 0x0080U
} enet_rx_special_config_t;

typedef enum
{
    ENET_TX_CONFIG_DISABLE_CRC_APPEND           = 0x0001U,
    ENET_TX_CONFIG_ENABLE_MAC_ADDR_INSERTION    = 0x0002U,
} enet_tx_special_config_t;

typedef enum
{
    ENET_BABR_INTERRUPT = ENET_EIR_BABR_MASK,
    ENET_BABT_INTERRUPT = ENET_EIR_BABT_MASK,
    ENET_GRACE_STOP_INTERRUPT = ENET_EIR_GRA_MASK,
    ENET_TX_FRAME_INTERRUPT = ENET_EIR_TXF_MASK,
    ENET_TX_BUFFER_INTERRUPT = ENET_EIR_TXB_MASK,
    ENET_RX_FRAME_INTERRUPT = ENET_EIR_RXF_MASK,
    ENET_RX_BUFFER_INTERRUPT = ENET_EIR_RXB_MASK,
    ENET_MII_INTERRUPT = ENET_EIR_MII_MASK,
    ENET_EBERR_INTERRUPT = ENET_EIR_EBERR_MASK,
    ENET_LATE_COLLISION_INTERRUPT = ENET_EIR_LC_MASK,
    ENET_RETRY_LIMIT_INTERRUPT = ENET_EIR_RL_MASK,
    ENET_UNDERRUN_INTERRUPT = ENET_EIR_UN_MASK,
    ENET_PAYLOAD_RX_INTERRUPT = ENET_EIR_PLR_MASK,
    ENET_WAKEUP_INTERRUPT = ENET_EIR_WAKEUP_MASK,
    ENET_TS_AVAIL_INTERRUPT = ENET_EIR_TS_AVAIL_MASK,
    ENET_TS_TIMER_INTERRUPT = ENET_EIR_TS_TIMER_MASK,
#if (FEATURE_ENET_RING_COUNT > 1U)
    ENET_RX_FLUSH_2_INTERRUPT = ENET_EIR_RXFLUSH_2_MASK,
    ENET_RX_FLUSH_1_INTERRUPT = ENET_EIR_RXFLUSH_1_MASK,
    ENET_RX_FLUSH_0_INTERRUPT = ENET_EIR_RXFLUSH_0_MASK,
    ENET_TX_FRAME_1_INTERRUPT = ENET_EIR_TXF1_MASK,
    ENET_TX_BUFFER_1_INTERRUPT = ENET_EIR_TXB1_MASK,
    ENET_RX_FRAME_1_INTERRUPT = ENET_EIR_RXF1_MASK,
    ENET_RX_BUFFER_1_INTERRUPT = ENET_EIR_RXB1_MASK,
    ENET_TX_FRAME_2_INTERRUPT = ENET_EIR_TXF2_MASK,
    ENET_TX_BUFFER_2_INTERRUPT = ENET_EIR_TXB2_MASK,
    ENET_RX_FRAME_2_INTERRUPT = ENET_EIR_RXF2_MASK,
    ENET_RX_BUFFER_2_INTERRUPT = ENET_EIR_RXB2_MASK,
#endif 
#if FEATURE_ENET_HAS_RECEIVE_PARSER
    ENET_PARSERERR_INTERRUPT = ENET_EIR_PARSERR_MASK,
    ENET_PARSRF_INTERRUPT = ENET_EIR_PARSRF_MASK,
#endif 
} enet_interrupt_t;

typedef enum
{
    ENET_TX_ACCEL_ENABLE_SHIFT16        = ENET_TACC_SHIFT16_MASK,
    ENET_TX_ACCEL_INSERT_IP_CHECKSUM    = ENET_TACC_IPCHK_MASK,
    ENET_TX_ACCEL_INSERT_PROTO_CHECKSUM = ENET_TACC_PROCHK_MASK
} enet_tx_accelerator_t;

typedef enum
{
    ENET_RX_ACCEL_REMOVE_PAD         = ENET_RACC_PADREM_MASK,
    ENET_RX_ACCEL_ENABLE_IP_CHECK    = ENET_RACC_IPDIS_MASK,
    ENET_RX_ACCEL_ENABLE_PROTO_CHECK = ENET_RACC_PRODIS_MASK,
    ENET_RX_ACCEL_ENABLE_MAC_CHECK   = ENET_RACC_LINEDIS_MASK,
    ENET_RX_ACCEL_ENABLE_SHIFT16     = ENET_RACC_SHIFT16_MASK
} enet_rx_accelerator_t;

typedef struct
{
    uint8_t *data;
    uint16_t length;
} enet_buffer_t;

#if (defined(CORE_BIG_ENDIAN))
typedef struct
{
    uint16_t control; 
    uint16_t length;  
    uint8_t *buffer;  
#if FEATURE_ENET_HAS_ENHANCED_BD
    uint32_t enh1;    
    uint32_t enh2;    
    uint32_t enh3;    
    uint32_t timestamp;  
    uint32_t reserved1;  
    uint32_t reserved2;  
#endif 
} enet_buffer_descriptor_t;
#elif (defined(CORE_LITTLE_ENDIAN))
typedef struct
{
    uint16_t length;  
    uint16_t control; 
    uint8_t *buffer;  
#if FEATURE_ENET_HAS_ENHANCED_BD
    uint32_t enh1;    
    uint32_t enh2;    
    uint32_t enh3;    
    uint32_t timestamp;  
    uint32_t reserved1;  
    uint32_t reserved2;  
#endif 
} enet_buffer_descriptor_t;
#else
    #error "Endianness not defined!"
#endif

typedef enum
{
    ENET_RX_EVENT,
    ENET_TX_EVENT,
    ENET_ERR_EVENT,
    ENET_WAKE_UP_EVENT,
    ENET_PARSER_EVENT
} enet_event_t;

typedef void (*enet_callback_t)(uint8_t instance, enet_event_t event, uint8_t ring);

#if FEATURE_ENET_HAS_ADJUSTABLE_TIMER

typedef void (*enet_timer_callback_t)(uint8_t instance, uint8_t channels);

#endif 

typedef struct
{
    uint16_t rxRingSize;                              
    uint16_t txRingSize;                              
    enet_buffer_descriptor_t *rxRingAligned;          
    enet_buffer_descriptor_t *txRingAligned;          
    uint8_t *rxBufferAligned;                         
} enet_buffer_config_t;

typedef struct
{
    uint8_t rxAccelerConfig;      
    uint8_t txAccelerConfig;      
    uint16_t maxFrameLen;         
    uint32_t interrupts;          
    enet_mii_mode_t miiMode;      
    enet_mii_speed_t miiSpeed;    
    enet_mii_duplex_t miiDuplex;  
    uint32_t rxConfig;    
    uint32_t txConfig;    
    enet_callback_t callback;
    uint8_t ringCount;    
} enet_config_t;

typedef struct
{
    enet_buffer_descriptor_t *rxBdBase[FEATURE_ENET_RING_COUNT];    
    enet_buffer_descriptor_t *rxBdCurrent[FEATURE_ENET_RING_COUNT]; 
    enet_buffer_descriptor_t *rxBdAlloc[FEATURE_ENET_RING_COUNT];   
    enet_buffer_descriptor_t *txBdBase[FEATURE_ENET_RING_COUNT];    
    enet_buffer_descriptor_t *txBdCurrent[FEATURE_ENET_RING_COUNT]; 
    enet_callback_t callback;              
#if FEATURE_ENET_HAS_ADJUSTABLE_TIMER
    enet_timer_callback_t timerCallback;   
#endif 
    uint8_t ringCount;                     
} enet_state_t;

typedef enum
{
    ENET_CTR_RMON_T_DROP = 0U,
    ENET_CTR_RMON_T_PACKETS,
    ENET_CTR_RMON_T_BC_PKT,
    ENET_CTR_RMON_T_MC_PKT,
    ENET_CTR_RMON_T_CRC_ALIGN,
    ENET_CTR_RMON_T_UNDERSIZE,
    ENET_CTR_RMON_T_OVERSIZE,
    ENET_CTR_RMON_T_FRAG,
    ENET_CTR_RMON_T_JAB,
    ENET_CTR_RMON_T_COL,
    ENET_CTR_RMON_T_P64,
    ENET_CTR_RMON_T_P65TO127,
    ENET_CTR_RMON_T_P128TO255,
    ENET_CTR_RMON_T_P256TO511,
    ENET_CTR_RMON_T_P512TO1023,
    ENET_CTR_RMON_T_P1024TO2047,
    ENET_CTR_RMON_T_P_GTE2048,
    ENET_CTR_RMON_T_OCTETS,
    ENET_CTR_IEEE_T_DROP,
    ENET_CTR_IEEE_T_FRAME_OK,
    ENET_CTR_IEEE_T_1COL,
    ENET_CTR_IEEE_T_MCOL,
    ENET_CTR_IEEE_T_DEF,
    ENET_CTR_IEEE_T_LCOL,
    ENET_CTR_IEEE_T_EXCOL,
    ENET_CTR_IEEE_T_MACERR,
    ENET_CTR_IEEE_T_CSERR,
    ENET_CTR_IEEE_T_SQE,
    ENET_CTR_IEEE_T_FDXFC,
    ENET_CTR_IEEE_T_OCTETS_OK = 29U,
    ENET_CTR_RMON_R_PACKETS = 33U,
    ENET_CTR_RMON_R_BC_PKT,
    ENET_CTR_RMON_R_MC_PKT,
    ENET_CTR_RMON_R_CRC_ALIGN,
    ENET_CTR_RMON_R_UNDERSIZE,
    ENET_CTR_RMON_R_OVERSIZE,
    ENET_CTR_RMON_R_FRAG,
    ENET_CTR_RMON_R_JAB,
    ENET_CTR_RMON_R_RESVD_0,
    ENET_CTR_RMON_R_P64,
    ENET_CTR_RMON_R_P65TO127,
    ENET_CTR_RMON_R_P128TO255,
    ENET_CTR_RMON_R_P256TO511,
    ENET_CTR_RMON_R_P512TO1023,
    ENET_CTR_RMON_R_P1024TO2047,
    ENET_CTR_RMON_R_P_GTE2048,
    ENET_CTR_RMON_R_OCTETS,
    ENET_CTR_IEEE_R_DROP,
    ENET_CTR_IEEE_R_FRAME_OK,
    ENET_CTR_IEEE_R_CRC,
    ENET_CTR_IEEE_R_ALIGN,
    ENET_CTR_IEEE_R_MACERR,
    ENET_CTR_IEEE_R_FDXFC,
    ENET_CTR_IEEE_R_OCTETS_OK
} enet_counter_t;

typedef struct {
    uint32_t errMask;    
    uint32_t timestamp;  
    uint16_t checksum;   
    uint8_t vlanPrio;    
    uint8_t headerLen;   
    uint8_t proto;       
    bool unicast;        
    bool ipv6;           
    bool ipv4Frag;       
} enet_rx_enh_info_t;

typedef struct {
    uint32_t errMask;    
    uint32_t timestamp;  
} enet_tx_enh_info_t;


#define ENET_RX_ENH_ERR_PROTO_CHECKSUM   (0x00000010U) 
#define ENET_RX_ENH_ERR_IPHDR_CHECKSUM   (0x00000020U) 
#define ENET_RX_ENH_ERR_COLLISION        (0x02000000U) 
#define ENET_RX_ENH_ERR_PHY              (0x04000000U) 
#define ENET_RX_ENH_ERR_MAC              (0x80000000U) 

#define ENET_TX_ENH_ERR_TIMESTAMP        (0x00000100U) 
#define ENET_TX_ENH_ERR_OVERFLOW         (0x00000200U) 
#define ENET_TX_ENH_ERR_LATE_COLLISION   (0x00000400U) 
#define ENET_TX_ENH_ERR_FRAME            (0x00000800U) 
#define ENET_TX_ENH_ERR_EXCESS_COLLISION (0x00001000U) 
#define ENET_TX_ENH_ERR_UNDERFLOW        (0x00002000U) 

#if FEATURE_ENET_HAS_ADJUSTABLE_TIMER

typedef struct {
    uint32_t timerPeriod;            
    uint8_t  timerInc;               
    uint32_t correctionPeriod;       
    uint8_t  correctionInc;          
    bool irqEnable;                  
    enet_timer_callback_t callback;  
} enet_timer_config_t;

typedef enum {
    ENET_TIMER_IC_RISING_EDGE = 1U,               
    ENET_TIMER_IC_FALLING_EDGE = 2U,              
    ENET_TIMER_IC_BOTH_EDGES = 3U,                
    ENET_TIMER_OC_SOFTWARE = 4U,                  
    ENET_TIMER_OC_TOGGLE_ON_COMP = 5U,            
    ENET_TIMER_OC_CLEAR_ON_COMP = 6U,             
    ENET_TIMER_OC_SET_ON_COMP = 7U,               
    ENET_TIMER_OC_CLEAR_ON_COMP_SET_ON_OVF = 10U, 
    ENET_TIMER_OC_SET_ON_COMP_CLEAR_ON_OVF = 11U, 
    ENET_TIMER_OC_PULSE_LOW_ON_COMP = 14U,        
    ENET_TIMER_OC_PULSE_HIGH_ON_COMP = 15U        
} enet_timer_channel_mode_t;

typedef struct {
    enet_timer_channel_mode_t mode; 
    bool irqEnable;                 
    bool dmaEnable;                 
} enet_timer_channel_config_t;

#endif 

typedef struct {
    bool noCRC;    
    bool noInt;    
#if FEATURE_ENET_HAS_TBS
    bool useTLT;   
    uint32_t TLT;  
#endif 
} enet_tx_options_t;

#if (FEATURE_ENET_RING_COUNT > 1U)

typedef enum {
#if FEATURE_ENET_HAS_CBS
	ENET_CBS_SCHEME = 0U,
#endif 
	ENET_ROUND_ROBIN_SCHEME = 1U
} enet_tx_scheme_t;

#endif 

typedef enum {
    ENET_RX_SECTION_FULL = 0U, 
    ENET_RX_SECTION_EMPTY,     
    ENET_RX_ALMOST_EMPTY,      
    ENET_RX_ALMOST_FULL,       
    ENET_TX_SECTION_EMPTY,     
    ENET_TX_ALMOST_EMPTY,      
    ENET_TX_ALMOST_FULL        
} enet_fifo_threshold_t;

#if FEATURE_ENET_HAS_RECEIVE_PARSER

typedef struct {
    bool acceptEndError;    
    uint8_t endErrorQueue;  
    bool clearCounters;     
    bool inverseByteOrder;  
} enet_rx_parser_config_t;

typedef struct {
    uint32_t compareValue;  
    uint32_t compareMask;   
    uint8_t compareOffset;  
} enet_rx_parser_rule_t;

typedef enum {
    ENET_RX_PARSER_CNT_DISCARD = 0U,  
    ENET_RX_PARSER_CNT_ACCEPT_0,      
    ENET_RX_PARSER_CNT_REJECT_0,      
    ENET_RX_PARSER_CNT_ACCEPT_1,      
    ENET_RX_PARSER_CNT_REJECT_1,      
    ENET_RX_PARSER_CNT_ACCEPT_2,      
    ENET_RX_PARSER_CNT_REJECT_2       
} enet_rx_parser_counter_t;

typedef enum {
    ENET_RX_PARSER_STAT_MXINDERR = ENET_RXPARST_INVMAXIDX_MASK,  
    ENET_RX_PARSER_STAT_TBLDPTERR = ENET_RXPARST_TBLDPTERR_MASK, 
    ENET_RX_PARSER_STAT_NOMTCERR = ENET_RXPARST_NOMTCERR_MASK,   
    ENET_RX_PARSER_STAT_FMOFFERR = ENET_RXPARST_FMOFFERR_MASK,   
    ENET_RX_PARSER_STAT_PRSENDERR = ENET_RXPARST_PRSENDERR_MASK, 
    ENET_RX_PARSER_STAT_INVMAXIDX = ENET_RXPARST_INVMAXIDX_MASK, 
    ENET_RX_PARSER_STAT_RXPRSDN = ENET_RXPARST_RXPRSDN_MASK      
} enet_rx_parser_status_t;

#endif 


#if defined(__cplusplus)
extern "C" {
#endif


void ENET_DRV_GetDefaultConfig(enet_config_t *config);

void ENET_DRV_Init(uint8_t instance,
                   enet_state_t *state,
                   const enet_config_t *config,
                   const enet_buffer_config_t bufferConfig[],
                   const uint8_t *macAddr);

void ENET_DRV_Deinit(uint8_t instance);



status_t ENET_DRV_ReadFrame(uint8_t instance,
                            uint8_t queue,
                            enet_buffer_t * buff,
                            enet_rx_enh_info_t * info);

void ENET_DRV_ProvideRxBuff(uint8_t instance,
                            uint8_t queue,
                            enet_buffer_t * buff);

status_t ENET_DRV_SendFrame(uint8_t instance,
                            uint8_t queue,
                            const enet_buffer_t * buff,
                            enet_tx_options_t * options);

status_t ENET_DRV_GetTransmitStatus(uint8_t instance,
                                    uint8_t queue,
                                    const enet_buffer_t * buff,
                                    enet_tx_enh_info_t * info);



void ENET_DRV_EnableMDIO(uint8_t instance,
                         bool miiPreambleDisabled);

status_t ENET_DRV_MDIORead(uint8_t instance,
                           uint8_t phyAddr,
                           uint8_t phyReg,
                           uint16_t *data,
                           uint32_t timeoutMs);

status_t ENET_DRV_MDIOWrite(uint8_t instance,
                            uint8_t phyAddr,
                            uint8_t phyReg,
                            uint16_t data,
                            uint32_t timeoutMs);



void ENET_DRV_SetMacAddr(uint8_t instance,
                         const uint8_t *macAddr);

void ENET_DRV_GetMacAddr(uint8_t instance,
                         uint8_t *macAddr);

void ENET_DRV_SetUnicastForward(uint8_t instance,
                                const uint8_t *macAddr,
                                bool enable);

void ENET_DRV_SetMulticastForward(uint8_t instance,
                                  const uint8_t *macAddr,
                                  bool enable);

void ENET_DRV_SetMulticastForwardAll(uint8_t instance,
                                     bool enable);



void ENET_DRV_SetSleepMode(uint8_t instance,
                           bool enable);

void ENET_DRV_ConfigCounters(uint8_t instance,
                             bool enable);

uint32_t ENET_DRV_GetCounter(uint8_t instance,
                             enet_counter_t counter);

uint32_t ENET_DRV_GetInterruptFlags(uint8_t instance);

void ENET_DRV_SetSpeed(uint8_t instance,
                       enet_mii_speed_t speed);

#if FEATURE_ENET_HAS_ADJUSTABLE_TIMER

void ENET_DRV_TimerInit(uint8_t instance,
                        enet_timer_config_t *timerConfig);

void ENET_DRV_TimerStart(uint8_t instance);

void ENET_DRV_TimerStop(uint8_t instance);

void ENET_DRV_TimerSet(uint8_t instance,
                       uint32_t value);

void ENET_DRV_TimerGet(uint8_t instance,
                       uint32_t *value);

void ENET_DRV_TimerSetCorrection(uint8_t instance,
                                 uint32_t value,
                                 uint32_t period);

void ENET_DRV_TimerEnableChannel(uint8_t instance,
                                 uint8_t channel,
                                 enet_timer_channel_config_t *config);

void ENET_DRV_TimerSetCompare(uint8_t instance,
                              uint8_t channel,
                              uint32_t value);

void ENET_DRV_TimerGetCapture(uint8_t instance,
                              uint8_t channel,
                              uint32_t *capture);

#if FEATURE_ENET_HAS_TIMER_PULSE_WIDTH_CONTROL

void ENET_DRV_TimerSetPulseWidth(uint8_t instance,
                                 uint8_t channel,
                                 uint8_t pulseWidth);

#endif 

#endif 

#if (FEATURE_ENET_RING_COUNT > 1U)

void ENET_DRV_ConfigTxScheme(uint8_t instance,
		                     enet_tx_scheme_t scheme);

#if FEATURE_ENET_HAS_CBS

void ENET_DRV_ConfigIdleSlope(uint8_t instance,
		                      uint8_t class,
                              uint16_t idleSlope);

#endif 

void ENET_DRV_ConfigClassMatch(uint8_t instance,
                               uint8_t class,
                               uint8_t vlanPrioNum,
                               uint8_t *vlanPrio);

void ENET_DRV_ConfigRxFlush(uint8_t instance,
                            uint8_t queue,
                            bool enable);

#endif 

#if FEATURE_ENET_HAS_INTCOAL

void ENET_DRV_EnableRxInterruptCoalescing(uint8_t instance,
                                          uint8_t queue,
                                          uint8_t frameCount,
                                          uint16_t timeoutUs);

void ENET_DRV_DisableRxInterruptCoalescing(uint8_t instance,
                                           uint8_t queue);

void ENET_DRV_EnableTxInterruptCoalescing(uint8_t instance,
                                          uint8_t queue,
                                          uint8_t frameCount,
                                          uint16_t timeoutUs);

void ENET_DRV_DisableTxInterruptCoalescing(uint8_t instance,
                                           uint8_t queue);

#endif 

void ENET_DRV_SetFIFOThreshold(uint8_t instance,
                               enet_fifo_threshold_t thresholdType,
                               uint8_t thresholdValue);

void ENET_DRV_SetTxFIFOWatermark(uint8_t instance,
                                 uint16_t watermark);

void ENET_DRV_EnableTxStoreAndForward(uint8_t instance);

#if FEATURE_ENET_HAS_RECEIVE_PARSER

void ENET_DRV_RxParserInit(uint8_t instance,
                           enet_rx_parser_config_t *config);

void ENET_DRV_RxParserDeinit(uint8_t instance);

void ENET_DRV_RxParserAddAcceptRule(uint8_t instance,
                                    uint8_t queue,
                                    enet_rx_parser_rule_t *rule);

void ENET_DRV_RxParserAddRejectRule(uint8_t instance,
                                    enet_rx_parser_rule_t *rule);

void ENET_DRV_RxParserAddLinkingRule(uint8_t instance,
                                     uint8_t nextEntry,
                                     enet_rx_parser_rule_t *rule);

uint32_t ENET_DRV_RxParserGetState(uint8_t instance);

uint32_t ENET_DRV_RxParserGetCount(uint8_t instance,
                                   enet_rx_parser_counter_t counter);

#endif 


#if defined(__cplusplus)
}
#endif


#endif  




