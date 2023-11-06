

#ifndef FLEXCAN_HW_ACCESS_H
#define FLEXCAN_HW_ACCESS_H

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "flexcan_driver.h"


enum {
    FLEXCAN_RX_INACTIVE  = 0x0, 
    FLEXCAN_RX_FULL      = 0x2, 
    FLEXCAN_RX_EMPTY     = 0x4, 
    FLEXCAN_RX_OVERRUN   = 0x6, 
    FLEXCAN_RX_BUSY      = 0x8, 
    FLEXCAN_RX_RANSWER   = 0xA, 
    FLEXCAN_RX_NOT_USED   = 0xF 
};

enum {
    FLEXCAN_TX_INACTIVE  = 0x08, 
    FLEXCAN_TX_ABORT     = 0x09, 
    FLEXCAN_TX_DATA      = 0x0C, 
    FLEXCAN_TX_REMOTE    = 0x1C, 
    FLEXCAN_TX_TANSWER   = 0x0E, 
    FLEXCAN_TX_NOT_USED   = 0xF  
};

enum {
    FLEXCAN_MB_STATUS_TYPE_TX,          
    FLEXCAN_MB_STATUS_TYPE_TX_REMOTE,   
    FLEXCAN_MB_STATUS_TYPE_RX,          
    FLEXCAN_MB_STATUS_TYPE_RX_REMOTE,   
    FLEXCAN_MB_STATUS_TYPE_RX_TX_REMOTE 
};

typedef enum {
    FLEXCAN_INT_RX_WARNING = CAN_CTRL1_RWRNMSK_MASK,     
    FLEXCAN_INT_TX_WARNING = CAN_CTRL1_TWRNMSK_MASK,     
    FLEXCAN_INT_ERR        = CAN_CTRL1_ERRMSK_MASK,      
    FLEXCAN_INT_BUSOFF     = CAN_CTRL1_BOFFMSK_MASK,     
} flexcan_int_type_t;

typedef struct {
    uint32_t code;                        
    flexcan_msgbuff_id_type_t msgIdType;  
    uint32_t dataLen;                     
    bool fd_enable;
    uint8_t fd_padding;
    bool enable_brs;                       
} flexcan_msgbuff_code_status_t;

#define CAN_ID_EXT_MASK                          0x3FFFFu
#define CAN_ID_EXT_SHIFT                         0
#define CAN_ID_EXT_WIDTH                         18

#define CAN_ID_STD_MASK                          0x1FFC0000u
#define CAN_ID_STD_SHIFT                         18
#define CAN_ID_STD_WIDTH                         11

#define CAN_ID_PRIO_MASK                         0xE0000000u
#define CAN_ID_PRIO_SHIFT                        29
#define CAN_ID_PRIO_WIDTH                        3
#define CAN_CS_TIME_STAMP_MASK                   0xFFFFu
#define CAN_CS_TIME_STAMP_SHIFT                  0
#define CAN_CS_TIME_STAMP_WIDTH                  16

#define CAN_CS_DLC_MASK                          0xF0000u
#define CAN_CS_DLC_SHIFT                         16
#define CAN_CS_DLC_WIDTH                         4

#define CAN_CS_RTR_MASK                          0x100000u
#define CAN_CS_RTR_SHIFT                         20
#define CAN_CS_RTR_WIDTH                         1

#define CAN_CS_IDE_MASK                          0x200000u
#define CAN_CS_IDE_SHIFT                         21
#define CAN_CS_IDE_WIDTH                         1

#define CAN_CS_SRR_MASK                          0x400000u
#define CAN_CS_SRR_SHIFT                         22
#define CAN_CS_SRR_WIDTH                         1

#define CAN_CS_CODE_MASK                         0xF000000u
#define CAN_CS_CODE_SHIFT                        24
#define CAN_CS_CODE_WIDTH                        4

#define CAN_MB_EDL_MASK                          0x80000000u    
#define CAN_MB_BRS_MASK                          0x40000000u    

#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATAB_RTR_SHIFT     (31U)          
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATAB_IDE_SHIFT     (30U)          
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_RTR_SHIFT      (15U)          
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_IDE_SHIFT      (14U)          
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATA_EXT_MASK       (0x3FFFFFFFU)  
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATA_EXT_SHIFT      (1U)           
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATA_STD_MASK       (0x3FF80000U)  
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATA_STD_SHIFT      (19U)          
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_EXT_MASK       (0x1FFF8000U)  
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_EXT_MASK1		 (0x3FFFU)		
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_EXT_SHIFT1     (16U)          
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_EXT_SHIFT2     (0U)           
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_STD_MASK       (0x7FFU)       
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_STD_SHIFT1     (19U)          
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_STD_SHIFT2     (3U)           
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATB_EXT_CMP_SHIFT  (15U)          
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_EXT_MASK       (0x1FE00000U)  
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_STD_MASK       (0x7F8U)       
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_SHIFT1         (24U)          
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_SHIFT2         (16U)          
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_SHIFT3         (8U)           
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_SHIFT4         (0U)           
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_EXT_CMP_SHIFT  (21U)          
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_STD_CMP_SHIFT  (3U)           
#define FLEXCAN_RX_FIFO_ID_FILTER_FORMATC_MASK         	 (0xFFU)        

#ifdef CORE_BIG_ENDIAN
    #define FlexcanSwapBytesInWordIndex(index) (index)
    #define FlexcanSwapBytesInWord(a, b) (b = a)
#elif defined CORE_LITTLE_ENDIAN
    #define FlexcanSwapBytesInWordIndex(index) (((index) & ~3U) + (3U - ((index) & 3U)))
    #define FlexcanSwapBytesInWord(a, b) REV_BYTES_32(a, b)
#else
    #error "No endianness defined!"
#endif



#if defined(__cplusplus)
extern "C" {
#endif


uint32_t FLEXCAN_GetMaxMbNum(const CAN_Type * base);

uint32_t FLEXCAN_GetRxFifoMask(	 flexcan_msgbuff_id_type_t id_type,
                                 flexcan_rx_fifo_id_element_format_t formatType,
                                 uint32_t mask);

void FLEXCAN_Enable(CAN_Type * base);

void FLEXCAN_Disable(CAN_Type * base);

static inline uint32_t RxFifoOcuppiedLastMsgBuff(uint32_t x)
{
    return (5U + ((((x) + 1U) * 8U) / 4U));
}

static inline bool FLEXCAN_IsEnabled(const CAN_Type * base)
{
    return ((((base->MCR & CAN_MCR_MDIS_MASK) >> CAN_MCR_MDIS_SHIFT) != 0U) ? false : true);
}

#if FEATURE_CAN_HAS_PE_CLKSRC_SELECT
static inline void FLEXCAN_SelectClock(CAN_Type * base, flexcan_clk_source_t clk)
{
    base->CTRL1 = (base->CTRL1 & ~CAN_CTRL1_CLKSRC_MASK) | CAN_CTRL1_CLKSRC(clk);
}
#endif

void FLEXCAN_Init(CAN_Type * base);

static inline void FLEXCAN_SetTimeSegments(CAN_Type * base, const flexcan_time_segment_t *timeSeg)
{
    DEV_ASSERT(timeSeg != NULL);

    (base->CTRL1) = ((base->CTRL1) & ~((CAN_CTRL1_PROPSEG_MASK | CAN_CTRL1_PSEG2_MASK |
                                        CAN_CTRL1_PSEG1_MASK | CAN_CTRL1_PRESDIV_MASK) |
                                        CAN_CTRL1_RJW_MASK));

    (base->CTRL1) = ((base->CTRL1) | (CAN_CTRL1_PROPSEG(timeSeg->propSeg) |
                                      CAN_CTRL1_PSEG2(timeSeg->phaseSeg2) |
                                      CAN_CTRL1_PSEG1(timeSeg->phaseSeg1) |
                                      CAN_CTRL1_PRESDIV(timeSeg->preDivider) |
                                      CAN_CTRL1_RJW(timeSeg->rJumpwidth)));
}

static inline void FLEXCAN_SetRxIndividualMask(
    CAN_Type * base,
    uint32_t msgBuffIdx,
    uint32_t mask)
{
    base->RXIMR[msgBuffIdx] = mask;
}

static inline void FLEXCAN_SetRxFifoGlobalMask(CAN_Type * base, uint32_t Mask)
{
    (base->RXFGMASK) = Mask;
}

#if FEATURE_CAN_HAS_FD
static inline void FLEXCAN_SetExtendedTimeSegments(CAN_Type * base, const flexcan_time_segment_t *timeSeg)
{
    DEV_ASSERT(timeSeg != NULL);

    (base->CBT) = ((base->CBT) & ~((CAN_CBT_EPROPSEG_MASK | CAN_CBT_EPSEG2_MASK |
                                    CAN_CBT_EPSEG1_MASK | CAN_CBT_EPRESDIV_MASK) |
                                    CAN_CBT_ERJW_MASK));

    (base->CBT) = ((base->CBT) | (CAN_CBT_EPROPSEG(timeSeg->propSeg) |
                                  CAN_CBT_EPSEG2(timeSeg->phaseSeg2) |
                                  CAN_CBT_EPSEG1(timeSeg->phaseSeg1) |
                                  CAN_CBT_EPRESDIV(timeSeg->preDivider) |
                                  CAN_CBT_ERJW(timeSeg->rJumpwidth)));
}

static inline void FLEXCAN_SetFDTimeSegments(CAN_Type * base, const flexcan_time_segment_t *timeSeg)
{
    DEV_ASSERT(timeSeg != NULL);

    (base->FDCBT) = ((base->FDCBT) & ~((CAN_FDCBT_FPROPSEG_MASK | CAN_FDCBT_FPSEG2_MASK |
                                        CAN_FDCBT_FPSEG1_MASK | CAN_FDCBT_FPRESDIV_MASK) |
                                        CAN_FDCBT_FRJW_MASK));

    (base->FDCBT) = ((base->FDCBT) | (CAN_FDCBT_FPROPSEG(timeSeg->propSeg) |
                                      CAN_FDCBT_FPSEG2(timeSeg->phaseSeg2) |
                                      CAN_FDCBT_FPSEG1(timeSeg->phaseSeg1) |
                                      CAN_FDCBT_FPRESDIV(timeSeg->preDivider) |
                                      CAN_FDCBT_FRJW(timeSeg->rJumpwidth)));
}
#endif

static inline void FLEXCAN_GetTimeSegments(const CAN_Type * base, flexcan_time_segment_t *timeSeg)
{
    DEV_ASSERT(timeSeg != NULL);

    timeSeg->preDivider = ((base->CTRL1) & CAN_CTRL1_PRESDIV_MASK) >> CAN_CTRL1_PRESDIV_SHIFT;
    timeSeg->propSeg = ((base->CTRL1) & CAN_CTRL1_PROPSEG_MASK) >> CAN_CTRL1_PROPSEG_SHIFT;
    timeSeg->phaseSeg1 = ((base->CTRL1) & CAN_CTRL1_PSEG1_MASK) >> CAN_CTRL1_PSEG1_SHIFT;
    timeSeg->phaseSeg2 = ((base->CTRL1) & CAN_CTRL1_PSEG2_MASK) >> CAN_CTRL1_PSEG2_SHIFT;
    timeSeg->rJumpwidth = ((base->CTRL1) & CAN_CTRL1_RJW_MASK) >> CAN_CTRL1_RJW_SHIFT;
}

#if FEATURE_CAN_HAS_FD
static inline void FLEXCAN_GetFDTimeSegments(const CAN_Type * base, flexcan_time_segment_t *timeSeg)
{
    DEV_ASSERT(timeSeg != NULL);

    timeSeg->preDivider = ((base->FDCBT) & CAN_FDCBT_FPRESDIV_MASK) >> CAN_FDCBT_FPRESDIV_SHIFT;
    timeSeg->propSeg = ((base->FDCBT) & CAN_FDCBT_FPROPSEG_MASK) >> CAN_FDCBT_FPROPSEG_SHIFT;
    timeSeg->phaseSeg1 = ((base->FDCBT) & CAN_FDCBT_FPSEG1_MASK) >> CAN_FDCBT_FPSEG1_SHIFT;
    timeSeg->phaseSeg2 = ((base->FDCBT) & CAN_FDCBT_FPSEG2_MASK) >> CAN_FDCBT_FPSEG2_SHIFT;
    timeSeg->rJumpwidth = ((base->FDCBT) & CAN_FDCBT_FRJW_MASK) >> CAN_FDCBT_FRJW_SHIFT;
}
#endif

void FLEXCAN_ExitFreezeMode(CAN_Type * base);

void FLEXCAN_EnterFreezeMode(CAN_Type * base);

void FLEXCAN_SetOperationMode(
    CAN_Type * base,
    flexcan_operation_modes_t mode);

#if FEATURE_CAN_HAS_FD
static inline void FLEXCAN_SetFDEnabled(CAN_Type * base, bool enable)
{
    base->MCR = (base->MCR & ~CAN_MCR_FDEN_MASK) | CAN_MCR_FDEN(enable? 1UL : 0UL);

    base->CBT = (base->CBT & ~CAN_CBT_BTF_MASK) | CAN_CBT_BTF(enable? 1UL : 0UL);
}

static inline bool FLEXCAN_IsFDEnabled(const CAN_Type * base)
{
    return (((base->MCR & CAN_MCR_FDEN_MASK) >> CAN_MCR_FDEN_SHIFT) != 0U);
}
#endif

#if FEATURE_CAN_HAS_FD
void FLEXCAN_SetPayloadSize(
    CAN_Type * base,
    flexcan_fd_payload_size_t payloadSize);

uint8_t FLEXCAN_GetPayloadSize(const CAN_Type * base);
#endif



volatile uint32_t* FLEXCAN_GetMsgBuffRegion(
        CAN_Type * base,
        uint32_t msgBuffIdx);

status_t FLEXCAN_SetTxMsgBuff(
    CAN_Type * base,
    uint32_t msgBuffIdx,
    const flexcan_msgbuff_code_status_t *cs,
    uint32_t msgId,
    const uint8_t *msgData);

void FLEXCAN_AbortTxMsgBuff(CAN_Type * base, uint32_t msgBuffIdx);

void FLEXCAN_ResetRxMsgBuff(CAN_Type * base, uint32_t msgBuffIdx);

status_t FLEXCAN_SetRxMsgBuff(
    CAN_Type * base,
    uint32_t msgBuffIdx,
    const flexcan_msgbuff_code_status_t *cs,
    uint32_t msgId);

status_t FLEXCAN_GetMsgBuff(
    CAN_Type * base,
    uint32_t msgBuffIdx,
    flexcan_msgbuff_t *msgBuff);

void FLEXCAN_LockRxMsgBuff(
    CAN_Type * base,
    uint32_t msgBuffIdx);

static inline void FLEXCAN_UnlockRxMsgBuff(const CAN_Type * base)
{
    (void)base->TIMER;
}

status_t FLEXCAN_EnableRxFifo(CAN_Type * base, uint32_t numOfFilters);

static inline bool FLEXCAN_IsRxFifoEnabled(const CAN_Type * base)
{
    return (((base->MCR & CAN_MCR_RFEN_MASK) >> CAN_MCR_RFEN_SHIFT) != 0U);
}

static inline flexcan_rx_fifo_id_element_format_t FLEXCAN_GetRxFifoIdFormat(const CAN_Type * base)
{
	flexcan_rx_fifo_id_element_format_t id_type=FLEXCAN_RX_FIFO_ID_FORMAT_A;
    switch((base->MCR & CAN_MCR_IDAM_MASK) >> CAN_MCR_IDAM_SHIFT)
    {
		case 0U:
			id_type=FLEXCAN_RX_FIFO_ID_FORMAT_A;
			break;
		case 1U:
			id_type=FLEXCAN_RX_FIFO_ID_FORMAT_B;
			break;
		case 2U:
			id_type=FLEXCAN_RX_FIFO_ID_FORMAT_C;
			break;
		case 3U:
			id_type=FLEXCAN_RX_FIFO_ID_FORMAT_D;
			break;
		default:
		{
			DEV_ASSERT(false);
			break;
		}
    }
    return id_type;
}

status_t FLEXCAN_SetMaxMsgBuffNum(
    CAN_Type * base,
    uint32_t maxMsgBuffNum);

static inline uint32_t FLEXCAN_GetMaxMsgBuffNum(const CAN_Type * base)
{
    return (((base->MCR) & CAN_MCR_MAXMB_MASK) >> CAN_MCR_MAXMB_SHIFT);
}

void FLEXCAN_SetRxFifoFilter(
    CAN_Type * base,
    flexcan_rx_fifo_id_element_format_t idFormat,
    const flexcan_id_table_t *idFilterTable);

void FLEXCAN_ReadRxFifo(
    const CAN_Type * base,
    flexcan_msgbuff_t *rxFifo);



status_t FLEXCAN_SetMsgBuffIntCmd(
    CAN_Type * base,
    uint32_t msgBuffIdx, bool enable);

void FLEXCAN_SetErrIntCmd(CAN_Type * base, flexcan_int_type_t errType, bool enable);



static inline uint8_t FLEXCAN_GetMsgBuffIntStatus(const CAN_Type * base, uint32_t msgBuffIdx)
{
	uint32_t flag = 0U;

    if (msgBuffIdx < 32U)
    {
        flag = ((base->IMASK1 & ((uint32_t)1U << (msgBuffIdx % 32U))) >> (msgBuffIdx % 32U));
    }
#if FEATURE_CAN_MAX_MB_NUM > 32U
    if ((msgBuffIdx >= 32U) && (msgBuffIdx < 64U))
    {
    	flag = ((base->IMASK2 & ((uint32_t)1U << (msgBuffIdx % 32U))) >> (msgBuffIdx % 32U));
    }
#endif
#if FEATURE_CAN_MAX_MB_NUM > 64U
    if (msgBuffIdx >= 64U)
    {
    	flag = ((base->IMASK3 & ((uint32_t)1U << (msgBuffIdx % 32U))) >> (msgBuffIdx % 32U));
    }
#endif
    return (uint8_t)flag;
}

static inline uint8_t FLEXCAN_GetMsgBuffIntStatusFlag(const CAN_Type * base, uint32_t msgBuffIdx)
{
    uint8_t flag = 0;
    uint32_t mask;

    if (msgBuffIdx < 32U)
    {
        mask = base->IMASK1 & CAN_IMASK1_BUF31TO0M_MASK;
        flag = (uint8_t)(((base->IFLAG1 & mask) >> (msgBuffIdx % 32U)) & 1U);
    }
#if FEATURE_CAN_MAX_MB_NUM > 32U
    if ((msgBuffIdx >= 32U) && (msgBuffIdx < 64U))
    {
        mask = base->IMASK2 & CAN_IMASK2_BUF63TO32M_MASK;
        flag = (uint8_t)(((base->IFLAG2 & mask) >> (msgBuffIdx % 32U)) & 1U);
    }
#endif
#if FEATURE_CAN_MAX_MB_NUM > 64U
    if (msgBuffIdx >= 64U)
    {
        mask = base->IMASK3 & CAN_IMASK3_BUF95TO64M_MASK;
        flag = (uint8_t)(((base->IFLAG3 & mask) >> (msgBuffIdx % 32U)) & 1U);
    }
#endif

    return flag;
}

static inline void FLEXCAN_ClearFIFO(CAN_Type * base)
{
    base->IFLAG1 = CAN_IFLAG1_BUF0I_MASK;
}

static inline void FLEXCAN_ClearMsgBuffIntStatusFlag(CAN_Type * base, uint32_t msgBuffIdx)
{
    uint32_t flag = ((uint32_t)1U << (msgBuffIdx % 32U));

    if (msgBuffIdx < 32U)
    {
        (base->IFLAG1) = (flag);
    }
#if FEATURE_CAN_MAX_MB_NUM > 32U
    if ((msgBuffIdx >= 32U) && (msgBuffIdx < 64U))
    {
        (base->IFLAG2) = (flag);
    }
#endif
#if FEATURE_CAN_MAX_MB_NUM > 64U
    if (msgBuffIdx >= 64U)
    {
        (base->IFLAG3) = (flag);
    }
#endif
}

static inline uint8_t FLEXCAN_GetBuffStatusFlag(const CAN_Type * base, uint32_t msgBuffIdx)
{
	uint32_t flag = 0U;

    if (msgBuffIdx < 32U)
    {
        flag = ((base->IFLAG1 & ((uint32_t)1U << (msgBuffIdx % 32U))) >> (msgBuffIdx % 32U));
    }
#if FEATURE_CAN_MAX_MB_NUM > 32U
    if ((msgBuffIdx >= 32U) && (msgBuffIdx < 64U))
    {
    	flag = ((base->IFLAG2 & ((uint32_t)1U << (msgBuffIdx % 32U))) >> (msgBuffIdx % 32U));
    }
#endif
#if FEATURE_CAN_MAX_MB_NUM > 64U
    if (msgBuffIdx >= 64U)
    {
    	flag = ((base->IFLAG3 & ((uint32_t)1U << (msgBuffIdx % 32U))) >> (msgBuffIdx % 32U));
    }
#endif
    return (uint8_t)flag;
}

void FLEXCAN_ClearErrIntStatusFlag(CAN_Type * base);

static inline uint32_t FLEXCAN_GetErrorCounters(const CAN_Type * base)
{
    return base->ECR;
}



static inline void FLEXCAN_SetRxMaskType(CAN_Type * base, flexcan_rx_mask_type_t type)
{
    if (type == FLEXCAN_RX_MASK_GLOBAL)
    {
        base->MCR = (base->MCR & ~CAN_MCR_IRMQ_MASK) | CAN_MCR_IRMQ(0U);
    }
    else
    {
        base->MCR = (base->MCR & ~CAN_MCR_IRMQ_MASK) | CAN_MCR_IRMQ(1U);
    }
}

static inline uint8_t FLEXCAN_GetNoOfIndividualMBsRxFIFO(const CAN_Type * base)
{
	uint8_t ret = (uint8_t)(((base->CTRL2) & CAN_CTRL2_RFFN_MASK) >> CAN_CTRL2_RFFN_SHIFT);
	ret = (uint8_t)(7u + ((uint32_t)ret << 1u));
	if (ret >= CAN_RXIMR_COUNT)
	{
		ret = (uint8_t)(CAN_RXIMR_COUNT - 1u);
	}
	return ret;
}

static inline void FLEXCAN_SetRxIndividualStdMask(
    CAN_Type * base,
    uint32_t msgBuffIdx,
    uint32_t stdMask)
{
    (base->RXIMR[msgBuffIdx]) = (stdMask << CAN_ID_STD_SHIFT) & CAN_ID_STD_MASK;
}

static inline void FLEXCAN_SetRxIndividualExtMask(
    CAN_Type * base,
    uint32_t msgBuffIdx,
    uint32_t extMask)
{
    base->RXIMR[msgBuffIdx] = (extMask << CAN_ID_EXT_SHIFT) & (CAN_ID_STD_MASK | CAN_ID_EXT_MASK);
}

static inline void FLEXCAN_SetRxMsgBuffGlobalStdMask(CAN_Type * base, uint32_t stdMask)
{
    (base->RXMGMASK) = (((uint32_t)(((uint32_t)(stdMask)) << CAN_ID_STD_SHIFT)) & CAN_ID_STD_MASK);
}

static inline void FLEXCAN_SetRxMsgBuffGlobalExtMask(CAN_Type * base, uint32_t extMask)
{
    (base->RXMGMASK) = (((uint32_t)(((uint32_t)(extMask)) << CAN_ID_EXT_SHIFT)) &
                        (CAN_ID_STD_MASK | CAN_ID_EXT_MASK));
}

static inline void FLEXCAN_SetRxMsgBuff14StdMask(CAN_Type * base, uint32_t stdMask)
{
    (base->RX14MASK) = (((uint32_t)(((uint32_t)(stdMask)) << CAN_ID_STD_SHIFT)) & CAN_ID_STD_MASK);
}

static inline void FLEXCAN_SetRxMsgBuff14ExtMask(CAN_Type * base, uint32_t extMask)
{
    (base->RX14MASK) = (((uint32_t)(((uint32_t)(extMask)) << CAN_ID_EXT_SHIFT)) &
                        (CAN_ID_STD_MASK | CAN_ID_EXT_MASK));
}

static inline void FLEXCAN_SetRxMsgBuff15StdMask(CAN_Type * base, uint32_t stdMask)
{
    (base->RX15MASK) = (((uint32_t)(((uint32_t)(stdMask)) << CAN_ID_STD_SHIFT)) & CAN_ID_STD_MASK);
}

static inline void FLEXCAN_SetRxMsgBuff15ExtMask(CAN_Type * base, uint32_t extMask)
{
    (base->RX15MASK) = (((uint32_t)(((uint32_t)(extMask)) << CAN_ID_EXT_SHIFT)) &
                        (CAN_ID_STD_MASK | CAN_ID_EXT_MASK));
}

#if FEATURE_CAN_HAS_FD
static inline void FLEXCAN_SetStuffBitCount(CAN_Type * base, bool enable)
{
#if FEATURE_CAN_HAS_STFCNTEN_ENABLE
    base->CTRL2 = (base->CTRL2 & ~CAN_CTRL2_STFCNTEN_MASK) | CAN_CTRL2_STFCNTEN(enable? 1UL : 0UL);
#elif FEATURE_CAN_HAS_ISOCANFDEN_ENABLE
    base->CTRL2 = (base->CTRL2 & ~CAN_CTRL2_ISOCANFDEN_MASK) |
                   CAN_CTRL2_ISOCANFDEN(enable? 1UL : 0UL);

#ifdef ERRATA_E8759
    uint8_t flag = (uint8_t)(((base->CTRL2) & CAN_CTRL2_ISOCANFDEN_MASK) >> CAN_CTRL2_ISOCANFDEN_SHIFT);

    DEV_ASSERT((enable == false) || (flag == 1UL));
    (void)flag;
#endif

#endif
}
#endif

static inline void FLEXCAN_SetSelfReception(CAN_Type * base, bool enable)
{
    base->MCR = (base->MCR & ~CAN_MCR_SRXDIS_MASK) | CAN_MCR_SRXDIS(enable? 0UL : 1UL);
}

#if FEATURE_CAN_HAS_FD
static inline void FLEXCAN_SetTDCOffset(CAN_Type * base, bool enable, uint8_t offset)
{
    uint32_t tmp;

    tmp = base->FDCTRL;
    tmp &= ~(CAN_FDCTRL_TDCEN_MASK | CAN_FDCTRL_TDCOFF_MASK);

    if (enable)
    {
        tmp = tmp | CAN_FDCTRL_TDCEN_MASK;
        tmp = tmp | CAN_FDCTRL_TDCOFF(offset);
    }

    base->FDCTRL = tmp;
}
#endif

#if FEATURE_CAN_HAS_DMA_ENABLE
static inline void FLEXCAN_SetRxFifoDMA(CAN_Type * base, bool enable)
{
    base->MCR = (base->MCR & ~CAN_MCR_DMA_MASK) | CAN_MCR_DMA(enable? 1UL : 0UL);
}
#endif

#if FEATURE_CAN_HAS_PRETENDED_NETWORKING

static inline void FLEXCAN_SetPNFilteringSelection(
        CAN_Type * base,
        bool wakeUpTimeout,
        bool wakeUpMatch,
        uint16_t numMatches,
        flexcan_pn_filter_combination_t filterComb,
        flexcan_pn_filter_selection_t idFilterType,
        flexcan_pn_filter_selection_t payloadFilterType)
{
    uint32_t tmp;

    tmp = base->CTRL1_PN;
    tmp &= ~(CAN_CTRL1_PN_WTOF_MSK_MASK |
             CAN_CTRL1_PN_WUMF_MSK_MASK |
             CAN_CTRL1_PN_NMATCH_MASK |
             CAN_CTRL1_PN_PLFS_MASK |
             CAN_CTRL1_PN_IDFS_MASK |
             CAN_CTRL1_PN_FCS_MASK);
    tmp |= CAN_CTRL1_PN_WTOF_MSK(wakeUpTimeout ? 1UL : 0UL);
    tmp |= CAN_CTRL1_PN_WUMF_MSK(wakeUpMatch ? 1UL : 0UL);
    tmp |= CAN_CTRL1_PN_NMATCH(numMatches);
    tmp |= CAN_CTRL1_PN_FCS(filterComb);
    tmp |= CAN_CTRL1_PN_IDFS(idFilterType);
    tmp |= CAN_CTRL1_PN_PLFS(payloadFilterType);
    base->CTRL1_PN = tmp;
}

static inline void FLEXCAN_SetPNTimeoutValue(CAN_Type * base, uint16_t timeoutValue)
{
    base->CTRL2_PN = (base->CTRL2_PN & ~CAN_CTRL2_PN_MATCHTO_MASK) |
                      CAN_CTRL2_PN_MATCHTO(timeoutValue);
}

static inline void FLEXCAN_SetPNIdFilter1(CAN_Type * base, flexcan_pn_id_filter_t idFilter)
{
    uint32_t tmp;

    tmp = base->FLT_ID1;
    tmp &= ~(CAN_FLT_ID1_FLT_IDE_MASK | CAN_FLT_ID1_FLT_RTR_MASK | CAN_FLT_ID1_FLT_ID1_MASK);
    tmp |= CAN_FLT_ID1_FLT_IDE(idFilter.extendedId ? 1UL : 0UL);
    tmp |= CAN_FLT_ID1_FLT_RTR(idFilter.remoteFrame ? 1UL : 0UL);
    if (idFilter.extendedId)
    {
        tmp |= CAN_FLT_ID1_FLT_ID1(idFilter.id);
    }
    else
    {
        tmp |= CAN_FLT_ID1_FLT_ID1(idFilter.id << CAN_ID_STD_SHIFT);
    }
    base->FLT_ID1 = tmp;
}

static inline void FLEXCAN_SetPNIdFilter2(CAN_Type * base, const flexcan_pn_config_t *pnConfig)
{
    uint32_t tmp;

    tmp = base->FLT_ID2_IDMASK;
    tmp &= ~(CAN_FLT_ID2_IDMASK_IDE_MSK_MASK | CAN_FLT_ID2_IDMASK_RTR_MSK_MASK | CAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK_MASK);
    tmp |= CAN_FLT_ID2_IDMASK_IDE_MSK(pnConfig->idFilter2.extendedId ? 1UL : 0UL);
    tmp |= CAN_FLT_ID2_IDMASK_RTR_MSK(pnConfig->idFilter2.remoteFrame ? 1UL : 0UL);
    if (pnConfig->idFilter1.extendedId)
    {
        tmp |= CAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK(pnConfig->idFilter2.id);
    }
    else
    {
        tmp |= CAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK(pnConfig->idFilter2.id << CAN_ID_STD_SHIFT);
    }
    base->FLT_ID2_IDMASK = tmp;
}

static inline void FLEXCAN_SetPNDlcFilter(CAN_Type * base, uint8_t dlcLow, uint8_t dlcHigh)
{
    uint32_t tmp;

    tmp = base->FLT_DLC;
    tmp &= ~(CAN_FLT_DLC_FLT_DLC_HI_MASK | CAN_FLT_DLC_FLT_DLC_HI_MASK);
    tmp |= CAN_FLT_DLC_FLT_DLC_HI(dlcHigh);
    tmp |= CAN_FLT_DLC_FLT_DLC_LO(dlcLow);
    base->FLT_DLC = tmp;
}

static inline void FLEXCAN_SetPNPayloadHighFilter1(CAN_Type * base, const uint8_t *payload)
{
    base->PL1_HI = CAN_PL1_HI_Data_byte_4(payload[4]) |
                   CAN_PL1_HI_Data_byte_5(payload[5]) |
                   CAN_PL1_HI_Data_byte_6(payload[6]) |
                   CAN_PL1_HI_Data_byte_7(payload[7]);
}

static inline void FLEXCAN_SetPNPayloadLowFilter1(CAN_Type * base, const uint8_t *payload)
{
    base->PL1_LO = CAN_PL1_LO_Data_byte_0(payload[0]) |
                   CAN_PL1_LO_Data_byte_1(payload[1]) |
                   CAN_PL1_LO_Data_byte_2(payload[2]) |
                   CAN_PL1_LO_Data_byte_3(payload[3]);
}

static inline void FLEXCAN_SetPNPayloadHighFilter2(CAN_Type * base, const uint8_t *payload)
{
    base->PL2_PLMASK_HI = CAN_PL2_PLMASK_HI_Data_byte_4(payload[4]) |
                          CAN_PL2_PLMASK_HI_Data_byte_5(payload[5]) |
                          CAN_PL2_PLMASK_HI_Data_byte_6(payload[6]) |
                          CAN_PL2_PLMASK_HI_Data_byte_7(payload[7]);
}

static inline void FLEXCAN_SetPNPayloadLowFilter2(CAN_Type * base, const uint8_t *payload)
{
    base->PL2_PLMASK_LO = CAN_PL2_PLMASK_LO_Data_byte_0(payload[0]) |
                          CAN_PL2_PLMASK_LO_Data_byte_1(payload[1]) |
                          CAN_PL2_PLMASK_LO_Data_byte_2(payload[2]) |
                          CAN_PL2_PLMASK_LO_Data_byte_3(payload[3]);
}

void FLEXCAN_ConfigPN(CAN_Type * base, const flexcan_pn_config_t *pnConfig);

static inline void FLEXCAN_SetPN(CAN_Type * base, bool enable)
{
    base->MCR = (base->MCR & ~CAN_MCR_PNET_EN_MASK) | CAN_MCR_PNET_EN(enable ? 1UL : 0UL);
}

static inline bool FLEXCAN_IsPNEnabled(const CAN_Type * base)
{
    return (((base->MCR & CAN_MCR_PNET_EN_MASK) >> CAN_MCR_PNET_EN_SHIFT) != 0U);
}

static inline uint8_t FLEXCAN_GetWTOF(const CAN_Type * base)
{
    return (uint8_t)((base->WU_MTC & CAN_WU_MTC_WTOF_MASK) >> CAN_WU_MTC_WTOF_SHIFT);
}

static inline void FLEXCAN_ClearWTOF(CAN_Type * base)
{
    base->WU_MTC |= CAN_WU_MTC_WTOF_MASK;
}

static inline uint8_t FLEXCAN_GetWUMF(const CAN_Type * base)
{
    return (uint8_t)((base->WU_MTC & CAN_WU_MTC_WUMF_MASK) >> CAN_WU_MTC_WUMF_SHIFT);
}

static inline void FLEXCAN_ClearWUMF(CAN_Type * base)
{
    base->WU_MTC |= CAN_WU_MTC_WUMF_MASK;
}

#endif 

#if FEATURE_CAN_HAS_SELF_WAKE_UP

static inline status_t FLEXCAN_SetSelfWakeUp(CAN_Type * base, bool enable)
{
    uint32_t flag;
    status_t status = STATUS_SUCCESS;

    base->MCR = (base->MCR & ~CAN_MCR_SLFWAK_MASK) | CAN_MCR_SLFWAK(enable ? 1UL : 0UL);

    flag = ((base->MCR & CAN_MCR_SLFWAK_MASK) >> CAN_MCR_SLFWAK_SHIFT);

    if (enable && (flag != 1U))
    {
        status = STATUS_ERROR;
    }
    else
    {
        base->MCR = (base->MCR & ~CAN_MCR_WAKMSK_MASK) | CAN_MCR_WAKMSK(enable ? 1UL : 0UL);
    }

    return status;
}

static inline void FLEXCAN_SetWakSrc(CAN_Type * base, bool enable)
{
    base->MCR = (base->MCR & ~CAN_MCR_WAKSRC_MASK) | CAN_MCR_WAKSRC(enable ? 1UL : 0UL);
}

static inline bool FLEXCAN_IsSelfWakeUpEnabled(const CAN_Type * base)
{
    return (((base->MCR & CAN_MCR_SLFWAK_MASK) >> CAN_MCR_SLFWAK_SHIFT) != 0U);
}

static inline uint8_t FLEXCAN_GetWAKINT(const CAN_Type * base)
{
    return (uint8_t)((base->ESR1 & CAN_ESR1_WAKINT_MASK) >> CAN_ESR1_WAKINT_SHIFT);
}

static inline void FLEXCAN_ClearWAKINT(CAN_Type * base)
{
    base->ESR1 |= CAN_ESR1_WAKINT_MASK;
}

#endif 

#if FEATURE_CAN_HAS_MEM_ERR_DET
static inline void FLEXCAN_DisableMemErrorDetection(CAN_Type * base)
{
	base->CTRL2 |=  CAN_CTRL2_ECRWRE(1);
	base->MECR = CAN_MECR_ECRWRDIS(0);
	base->MECR = CAN_MECR_NCEFAFRZ(0);
	base->CTRL2 |=  CAN_CTRL2_ECRWRE(0);
}
#endif 

#if defined(__cplusplus)
}
#endif

#endif 


