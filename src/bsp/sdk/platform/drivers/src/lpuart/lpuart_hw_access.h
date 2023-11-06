

#ifndef LPUART_HW_ACCESS_H__
#define LPUART_HW_ACCESS_H__

#include "lpuart_driver.h"


#define LPUART_SHIFT (16U)
#define LPUART_BAUD_REG_ID (1U)
#define LPUART_STAT_REG_ID (2U)
#define LPUART_CTRL_REG_ID (3U)
#define LPUART_DATA_REG_ID (4U)
#define LPUART_MATCH_REG_ID (5U)
#define LPUART_MODIR_REG_ID (6U)
#define LPUART_FIFO_REG_ID (7U)

typedef enum
{
    LPUART_IDLE_LINE_WAKE = 0x0U, 
    LPUART_ADDR_MARK_WAKE = 0x1U  
} lpuart_wakeup_method_t;

typedef enum
{
    LPUART_BREAK_CHAR_10_BIT_MINIMUM = 0x0U, 
    LPUART_BREAK_CHAR_13_BIT_MINIMUM = 0x1U  
} lpuart_break_char_length_t;

typedef enum
{
    LPUART_TX_DATA_REG_EMPTY          = (((uint32_t)LPUART_STAT_REG_ID << (uint32_t)LPUART_SHIFT) \
                                        | (uint32_t)LPUART_STAT_TDRE_SHIFT), \
    LPUART_TX_COMPLETE                = (((uint32_t)LPUART_STAT_REG_ID << (uint32_t)LPUART_SHIFT) \
                                        | (uint32_t)LPUART_STAT_TC_SHIFT), \
    LPUART_RX_DATA_REG_FULL           = (((uint32_t)LPUART_STAT_REG_ID << (uint32_t)LPUART_SHIFT) \
                                        | (uint32_t)LPUART_STAT_RDRF_SHIFT), \
    LPUART_IDLE_LINE_DETECT           = (((uint32_t)LPUART_STAT_REG_ID << (uint32_t)LPUART_SHIFT) \
                                        | (uint32_t)LPUART_STAT_IDLE_SHIFT), \
    LPUART_RX_OVERRUN                 = (((uint32_t)LPUART_STAT_REG_ID << (uint32_t)LPUART_SHIFT) \
                                        | (uint32_t)LPUART_STAT_OR_SHIFT), \
    LPUART_NOISE_DETECT               = (((uint32_t)LPUART_STAT_REG_ID << (uint32_t)LPUART_SHIFT) \
                                        | (uint32_t)LPUART_STAT_NF_SHIFT), \
    LPUART_FRAME_ERR                  = (((uint32_t)LPUART_STAT_REG_ID << (uint32_t)LPUART_SHIFT) \
                                        | (uint32_t)LPUART_STAT_FE_SHIFT), \
    LPUART_PARITY_ERR                 = (((uint32_t)LPUART_STAT_REG_ID << (uint32_t)LPUART_SHIFT) \
                                        | (uint32_t)LPUART_STAT_PF_SHIFT), \
    LPUART_LIN_BREAK_DETECT           = (((uint32_t)LPUART_STAT_REG_ID << (uint32_t)LPUART_SHIFT) \
                                        | (uint32_t)LPUART_STAT_LBKDIF_SHIFT), \
    LPUART_RX_ACTIVE_EDGE_DETECT      = (((uint32_t)LPUART_STAT_REG_ID << (uint32_t)LPUART_SHIFT) \
                                        | (uint32_t)LPUART_STAT_RXEDGIF_SHIFT), \
    LPUART_RX_ACTIVE                  = (((uint32_t)LPUART_STAT_REG_ID << (uint32_t)LPUART_SHIFT) \
                                        | (uint32_t)LPUART_STAT_RAF_SHIFT), \
    LPUART_NOISE_IN_CURRENT_WORD      = (((uint32_t)LPUART_DATA_REG_ID << (uint32_t)LPUART_SHIFT) \
                                        | (uint32_t)LPUART_DATA_NOISY_SHIFT), \
    LPUART_PARITY_ERR_IN_CURRENT_WORD = (((uint32_t)LPUART_DATA_REG_ID << (uint32_t)LPUART_SHIFT) \
                                        | (uint32_t)LPUART_DATA_PARITYE_SHIFT), \
#if FEATURE_LPUART_HAS_ADDRESS_MATCHING
    LPUART_MATCH_ADDR_ONE             = (((uint32_t)LPUART_STAT_REG_ID << (uint32_t)LPUART_SHIFT) \
                                        | (uint32_t)LPUART_STAT_MA1F_SHIFT), \
    LPUART_MATCH_ADDR_TWO             = (((uint32_t)LPUART_STAT_REG_ID << (uint32_t)LPUART_SHIFT) \
                                        | (uint32_t)LPUART_STAT_MA2F_SHIFT), \
#endif
#if FEATURE_LPUART_FIFO_SIZE > 0U
    LPUART_FIFO_TX_OF                 = (((uint32_t)LPUART_FIFO_REG_ID << (uint32_t)LPUART_SHIFT) \
                                        | (uint32_t)LPUART_FIFO_TXOF_SHIFT), \
    LPUART_FIFO_RX_UF                 = (((uint32_t)LPUART_FIFO_REG_ID << (uint32_t)LPUART_SHIFT) \
                                        | (uint32_t)LPUART_FIFO_RXUF_SHIFT) \
#endif
} lpuart_status_flag_t;

typedef enum
{
    LPUART_INT_LIN_BREAK_DETECT  = (((uint32_t)LPUART_BAUD_REG_ID << (uint32_t)LPUART_SHIFT) \
                                   | (uint32_t)LPUART_BAUD_LBKDIE_SHIFT),  
    LPUART_INT_RX_ACTIVE_EDGE    = (((uint32_t)LPUART_BAUD_REG_ID << (uint32_t)LPUART_SHIFT) \
                                   | (uint32_t)LPUART_BAUD_RXEDGIE_SHIFT), 
    LPUART_INT_TX_DATA_REG_EMPTY = (((uint32_t)LPUART_CTRL_REG_ID << (uint32_t)LPUART_SHIFT) \
                                   | (uint32_t)LPUART_CTRL_TIE_SHIFT),     
    LPUART_INT_TX_COMPLETE       = (((uint32_t)LPUART_CTRL_REG_ID << (uint32_t)LPUART_SHIFT) \
                                   | (uint32_t)LPUART_CTRL_TCIE_SHIFT),    
    LPUART_INT_RX_DATA_REG_FULL  = (((uint32_t)LPUART_CTRL_REG_ID << (uint32_t)LPUART_SHIFT) \
                                   | (uint32_t)LPUART_CTRL_RIE_SHIFT),     
    LPUART_INT_IDLE_LINE         = (((uint32_t)LPUART_CTRL_REG_ID << (uint32_t)LPUART_SHIFT) \
                                   | (uint32_t)LPUART_CTRL_ILIE_SHIFT),    
    LPUART_INT_RX_OVERRUN        = (((uint32_t)LPUART_CTRL_REG_ID << (uint32_t)LPUART_SHIFT) \
                                   | (uint32_t)LPUART_CTRL_ORIE_SHIFT),    
    LPUART_INT_NOISE_ERR_FLAG    = (((uint32_t)LPUART_CTRL_REG_ID << (uint32_t)LPUART_SHIFT) \
                                   | (uint32_t)LPUART_CTRL_NEIE_SHIFT),    
    LPUART_INT_FRAME_ERR_FLAG    = (((uint32_t)LPUART_CTRL_REG_ID << (uint32_t)LPUART_SHIFT) \
                                   | (uint32_t)LPUART_CTRL_FEIE_SHIFT),    
    LPUART_INT_PARITY_ERR_FLAG   = (((uint32_t)LPUART_CTRL_REG_ID << (uint32_t)LPUART_SHIFT) \
                                   | (uint32_t)LPUART_CTRL_PEIE_SHIFT),    
#if FEATURE_LPUART_HAS_ADDRESS_MATCHING
    LPUART_INT_MATCH_ADDR_ONE    = (((uint32_t)LPUART_CTRL_REG_ID << (uint32_t)LPUART_SHIFT) \
                                   | (uint32_t)LPUART_CTRL_MA1IE_SHIFT),   
    LPUART_INT_MATCH_ADDR_TWO    = (((uint32_t)LPUART_CTRL_REG_ID << (uint32_t)LPUART_SHIFT) \
                                   | (uint32_t)LPUART_CTRL_MA2IE_SHIFT),   
#endif
#if FEATURE_LPUART_FIFO_SIZE > 0U
    LPUART_INT_FIFO_TXOF         = (((uint32_t)LPUART_FIFO_REG_ID << (uint32_t)LPUART_SHIFT) \
                                   | (uint32_t)LPUART_FIFO_TXOFE_SHIFT),    
    LPUART_INT_FIFO_RXUF         = (((uint32_t)LPUART_FIFO_REG_ID << (uint32_t)LPUART_SHIFT) \
                                   | (uint32_t)LPUART_FIFO_RXUFE_SHIFT)     
#endif
} lpuart_interrupt_t;



#if defined(__cplusplus)
extern "C" {
#endif


void LPUART_Init(LPUART_Type * base);

static inline void LPUART_SetTransmitterCmd(LPUART_Type * base, bool enable)
{
    base->CTRL = (base->CTRL & ~LPUART_CTRL_TE_MASK) | ((enable ? 1UL : 0UL) << LPUART_CTRL_TE_SHIFT);
    while((bool)((base->CTRL & LPUART_CTRL_TE_MASK) != 0U) != enable) {}
}

static inline void LPUART_SetReceiverCmd(LPUART_Type * base, bool enable)
{
    base->CTRL = (base->CTRL & ~LPUART_CTRL_RE_MASK) | ((enable ? 1UL : 0UL) << LPUART_CTRL_RE_SHIFT);
    while((bool)((base->CTRL & LPUART_CTRL_RE_MASK) != 0U) != enable) {}
}

static inline void LPUART_SetBaudRateDivisor(LPUART_Type * base, uint32_t baudRateDivisor)
{
    DEV_ASSERT((baudRateDivisor <= 0x1FFFU) && (baudRateDivisor >= 1U));
    uint32_t baudRegValTemp;

    baudRegValTemp = base->BAUD;
    baudRegValTemp &= ~(LPUART_BAUD_SBR_MASK);
    baudRegValTemp |= baudRateDivisor & LPUART_BAUD_SBR_MASK;
    base->BAUD = baudRegValTemp;
}

static inline uint16_t LPUART_GetBaudRateDivisor(const LPUART_Type * base)
{
    return ((uint16_t)((base->BAUD & LPUART_BAUD_SBR_MASK) >> LPUART_BAUD_SBR_SHIFT));
}

#if FEATURE_LPUART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT
static inline void LPUART_SetOversamplingRatio(LPUART_Type * base, uint32_t overSamplingRatio)
{
    DEV_ASSERT(overSamplingRatio <= 0x1FU);
    uint32_t baudRegValTemp;

    baudRegValTemp = base->BAUD;
    baudRegValTemp &= ~(LPUART_BAUD_OSR_MASK);
    baudRegValTemp |= LPUART_BAUD_OSR(overSamplingRatio);
    base->BAUD = baudRegValTemp;
}

static inline uint8_t LPUART_GetOversamplingRatio(const LPUART_Type * base)
{
    return ((uint8_t)((base->BAUD & LPUART_BAUD_OSR_MASK) >> LPUART_BAUD_OSR_SHIFT));
}
#endif

#if FEATURE_LPUART_HAS_BOTH_EDGE_SAMPLING_SUPPORT
static inline void LPUART_EnableBothEdgeSamplingCmd(LPUART_Type * base)
{
    base->BAUD |= LPUART_BAUD_BOTHEDGE_MASK;
}
#endif

void LPUART_SetBitCountPerChar(LPUART_Type * base, lpuart_bit_count_per_char_t bitCountPerChar, bool parity);

void LPUART_SetParityMode(LPUART_Type * base, lpuart_parity_mode_t parityModeType);

static inline void LPUART_SetStopBitCount(LPUART_Type * base, lpuart_stop_bit_count_t stopBitCount)
{
    base->BAUD = (base->BAUD & ~LPUART_BAUD_SBNS_MASK) | ((uint32_t)stopBitCount << LPUART_BAUD_SBNS_SHIFT);
}



void LPUART_SetIntMode(LPUART_Type * base, lpuart_interrupt_t intSrc, bool enable);

bool LPUART_GetIntMode(const LPUART_Type * base, lpuart_interrupt_t intSrc);

void LPUART_CreateStatDatRegisterCopy(const LPUART_Type *const base);

bool LPUART_GetStatusFlagFromRegisterCopy(lpuart_status_flag_t statusFlag);


#if FEATURE_LPUART_HAS_DMA_ENABLE
static inline void LPUART_SetTxDmaCmd(LPUART_Type * base, bool enable)
{
    base->BAUD = (base->BAUD & ~LPUART_BAUD_TDMAE_MASK) | ((enable ? 1UL : 0UL) << LPUART_BAUD_TDMAE_SHIFT);
}

static inline void LPUART_SetRxDmaCmd(LPUART_Type * base, bool enable)
{
    base->BAUD = (base->BAUD & ~LPUART_BAUD_RDMAE_MASK) | ((enable ? 1UL : 0UL) << LPUART_BAUD_RDMAE_SHIFT);
}
#endif



static inline void LPUART_Putchar(LPUART_Type * base, uint8_t data)
{
    volatile uint8_t * dataRegBytes = (volatile uint8_t *)(&(base->DATA));
    dataRegBytes[0] = data;
}

void LPUART_Putchar9(LPUART_Type * base, uint16_t data);

void LPUART_Putchar10(LPUART_Type * base, uint16_t data);

static inline void LPUART_Getchar(const LPUART_Type * base, uint8_t *readData)
{
    DEV_ASSERT(readData != NULL);

    *readData = (uint8_t)base->DATA;
}

void LPUART_Getchar9(const LPUART_Type * base, uint16_t *readData);

void LPUART_Getchar10(const LPUART_Type * base, uint16_t *readData);



bool LPUART_GetStatusFlag(const LPUART_Type * base, lpuart_status_flag_t statusFlag);

status_t LPUART_ClearStatusFlag(LPUART_Type * base, lpuart_status_flag_t statusFlag);



void LPUART_SetErrorInterrupts(LPUART_Type * base, bool enable);

static inline void LPUART_DRV_ClearErrorFlags(LPUART_Type * base)
{
    uint32_t mask = LPUART_STAT_OR_MASK | \
                    LPUART_STAT_NF_MASK | \
                    LPUART_STAT_FE_MASK | \
                    LPUART_STAT_PF_MASK;

    base->STAT = (base->STAT & (~FEATURE_LPUART_STAT_REG_FLAGS_MASK)) | mask;
}


#if defined(__cplusplus)
}
#endif

#endif 

