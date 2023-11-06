


#ifndef LPSPI_HW_ACCESS_H
#define LPSPI_HW_ACCESS_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "status.h"
#include "device_registers.h"
#include "lpspi_shared_function.h"


typedef enum
{
    LPSPI_DIV_1     = 0U,
    LPSPI_DIV_2     = 1U,
    LPSPI_DIV_4     = 2U,
    LPSPI_DIV_8     = 3U,
    LPSPI_DIV_16    = 4U,
    LPSPI_DIV_32    = 5U,
    LPSPI_DIV_64    = 6U,
    LPSPI_DIV_128   = 7U,
} lpspi_prescaler_t;

typedef enum
{
    LPSPI_TX_DATA_FLAG      = LPSPI_SR_TDF_SHIFT, 
    LPSPI_RX_DATA_FLAG      = LPSPI_SR_RDF_SHIFT, 
    LPSPI_WORD_COMPLETE     = LPSPI_SR_WCF_SHIFT, 
    LPSPI_FRAME_COMPLETE    = LPSPI_SR_FCF_SHIFT, 
    LPSPI_TRANSFER_COMPLETE = LPSPI_SR_TCF_SHIFT, 
    LPSPI_TRANSMIT_ERROR    = LPSPI_SR_TEF_SHIFT, 
    LPSPI_RECEIVE_ERROR     = LPSPI_SR_REF_SHIFT, 
    LPSPI_DATA_MATCH        = LPSPI_SR_DMF_SHIFT, 
    LPSPI_MODULE_BUSY       = LPSPI_SR_MBF_SHIFT, 
    LPSPI_ALL_STATUS        = 0x00003F00U         
} lpspi_status_flag_t;

typedef enum
{
    LPSPI_MASTER = 1U,     
    LPSPI_SLAVE  = 0U      
} lpspi_master_slave_mode_t;

typedef enum
{
    LPSPI_SDI_IN_SDO_OUT = 0U,     
    LPSPI_SDI_IN_OUT     = 1U,     
    LPSPI_SDO_IN_OUT     = 2U,     
    LPSPI_SDI_OUT_SDO_IN = 3U      
} lpspi_pin_config_t;

typedef enum
{
    LPSPI_DATA_OUT_RETAINED = 0U, 
    LPSPI_DATA_OUT_TRISTATE = 1U  
} lpspi_data_out_config_t;

typedef enum
{
    LPSPI_SINGLE_BIT_XFER = 0U, 
    LPSPI_TWO_BIT_XFER = 1U,    
    LPSPI_FOUR_BIT_XFER = 2U    
} lpspi_transfer_width_t;

typedef struct
{
    uint32_t frameSize;              
    lpspi_transfer_width_t width;    
    bool txMask;                     
    bool rxMask;                     
    bool contCmd;                    
    bool contTransfer;               
    bool byteSwap;                   
    bool lsbFirst;                   
    lpspi_which_pcs_t whichPcs;      
    uint32_t preDiv;                
    lpspi_clock_phase_t clkPhase;    
    lpspi_sck_polarity_t clkPolarity; 
} lpspi_tx_cmd_config_t;

typedef struct
{
    uint32_t lpspiSrcClk;                
    uint32_t baudRate;                   
    lpspi_master_slave_mode_t lpspiMode; 
    lpspi_signal_polarity_t pcsPol;      
} lpspi_init_config_t;

typedef enum
{
    LPSPI_SCK_TO_PCS = LPSPI_CCR_SCKPCS_SHIFT,     
    LPSPI_PCS_TO_SCK = LPSPI_CCR_PCSSCK_SHIFT,     
    LPSPI_BETWEEN_TRANSFER = LPSPI_CCR_DBT_SHIFT  
} lpspi_delay_type_t ;

static const uint32_t s_baudratePrescaler[] = { 1, 2, 4, 8, 16, 32, 64, 128 };


#if defined(__cplusplus)
extern "C" {
#endif


void LPSPI_Init(LPSPI_Type * base);

static inline void LPSPI_Enable(LPSPI_Type * base)
{
    (base->CR) |= (uint32_t)1U << LPSPI_CR_MEN_SHIFT;
}

static inline bool LPSPI_IsModuleEnabled(const LPSPI_Type * base)
{
    return (bool)(((base->CR) & LPSPI_CR_MEN_MASK) >> LPSPI_CR_MEN_SHIFT);
}

status_t LPSPI_Disable(LPSPI_Type * base);

status_t LPSPI_SetMasterSlaveMode(LPSPI_Type * base, lpspi_master_slave_mode_t mode);

static inline bool LPSPI_IsMaster(const LPSPI_Type * base)
{
    return (bool)((base->CFGR1 >> LPSPI_CFGR1_MASTER_SHIFT) & 1U);
}

static inline void LPSPI_GetFifoSizes(const LPSPI_Type * base, uint8_t * fifoSize)
{
    if (fifoSize != NULL)
    {
        *fifoSize = (uint8_t)(1U << ((base->PARAM & LPSPI_PARAM_TXFIFO_MASK) >> LPSPI_PARAM_TXFIFO_SHIFT));
    }
}

void LPSPI_SetFlushFifoCmd(LPSPI_Type * base, bool flushTxFifo, bool flushRxFifo);

static inline void LPSPI_SetRxWatermarks(LPSPI_Type * base, uint32_t rxWater)
{
    uint32_t lpspi_tmp = base->FCR;
    lpspi_tmp &= ~(LPSPI_FCR_RXWATER_MASK);
    lpspi_tmp |= (rxWater << LPSPI_FCR_RXWATER_SHIFT);
    base->FCR = lpspi_tmp;
}

static inline void LPSPI_SetTxWatermarks(LPSPI_Type * base, uint32_t txWater)
{
    uint32_t lpspi_tmp = base->FCR;
    lpspi_tmp &= ~(LPSPI_FCR_TXWATER_MASK);
    lpspi_tmp |= (txWater << LPSPI_FCR_TXWATER_SHIFT);
    base->FCR = lpspi_tmp;
}



static inline bool LPSPI_GetStatusFlag(const LPSPI_Type * base,
                                           lpspi_status_flag_t statusFlag)
{
    return (bool)(((base->SR) >> (uint8_t)statusFlag) & 1U);
}

status_t LPSPI_ClearStatusFlag(LPSPI_Type * base, lpspi_status_flag_t statusFlag);

static inline void LPSPI_SetIntMode(LPSPI_Type * base,
                                        lpspi_status_flag_t interruptSrc, bool enable)
{
    if (enable == true)
    {
        base->IER |= (uint32_t)1U << (uint8_t)interruptSrc;
    }
    else
    {
        base->IER &= ~((uint32_t)1U << (uint8_t)interruptSrc);
    }
}

static inline bool LPSPI_GetIntMode(const LPSPI_Type * base,
                                        lpspi_status_flag_t interruptSrc)
{
    return (bool)(((base->IER) >> (uint8_t)interruptSrc) & 1U);
}



static inline void LPSPI_SetTxDmaCmd(LPSPI_Type * base, bool enable)
{
    base->DER = (base->DER & (~LPSPI_DER_TDDE_MASK)) | ((uint32_t)enable << LPSPI_DER_TDDE_SHIFT);
}

static inline void LPSPI_SetRxDmaCmd(LPSPI_Type * base, bool enable)
{
    (base->DER) = (base->DER & (~LPSPI_DER_RDDE_MASK)) | ((uint32_t)enable << LPSPI_DER_RDDE_SHIFT);
}

static inline status_t LPSPI_SetDelay(LPSPI_Type * base, lpspi_delay_type_t whichDelay, uint32_t delay)
{
    uint32_t ccrValue = 0;

    ccrValue = base->CCR & ~(0xFFUL << (uint32_t)whichDelay);
    ccrValue |= delay << (uint32_t)whichDelay;
    base->CCR = ccrValue;
    return STATUS_SUCCESS;
}



status_t LPSPI_SetPcsPolarityMode(LPSPI_Type * base, lpspi_which_pcs_t whichPcs,
                                            lpspi_signal_polarity_t pcsPolarity);

status_t LPSPI_SetPinConfigMode(LPSPI_Type * base,
                                          lpspi_pin_config_t pinCfg,
                                          lpspi_data_out_config_t dataOutConfig,
                                          bool pcs3and2Enable);

uint32_t LPSPI_SetBaudRate(LPSPI_Type * base, uint32_t bitsPerSec,
                               uint32_t sourceClockInHz, uint32_t * tcrPrescaleValue);

status_t LPSPI_SetBaudRateDivisor(LPSPI_Type * base, uint32_t divisor);

void LPSPI_SetPcs(LPSPI_Type * base, lpspi_which_pcs_t whichPcs);



void LPSPI_SetTxCommandReg(LPSPI_Type * base, const lpspi_tx_cmd_config_t * txCmdCfgSet);

static inline void LPSPI_WriteData(LPSPI_Type * base, uint32_t data)
{
    base->TDR = data;
}

static inline uint32_t LPSPI_ReadData(const LPSPI_Type * base)
{
    return (uint32_t)base->RDR;
}

static inline uint32_t LPSPI_ReadTxCount(const LPSPI_Type * base)
{
    return (uint32_t)(((uint32_t)(base->FSR & LPSPI_FSR_TXCOUNT_MASK)) >> LPSPI_FSR_TXCOUNT_SHIFT);
}

static inline uint32_t LPSPI_ReadRxCount(const LPSPI_Type * base)
{
    return (uint32_t)((((uint32_t)base->FSR & (uint32_t)LPSPI_FSR_RXCOUNT_MASK)) >> (uint32_t)LPSPI_FSR_RXCOUNT_SHIFT);
}

static inline void LPSPI_ClearRxmaskBit(LPSPI_Type * base)
{
    (base->TCR) = ((base->TCR) & (~LPSPI_TCR_RXMSK_MASK));
}

static inline void LPSPI_SetRxmskBit(LPSPI_Type * base)
{
    (base->TCR) = ((base->TCR) | (LPSPI_TCR_RXMSK_MASK));
}

static inline void LPSPI_ClearTxmaskBit(LPSPI_Type * base)
{
    (base->TCR) = ((base->TCR) & (~LPSPI_TCR_TXMSK_MASK));
}

static inline void LPSPI_SetTxmskBit(LPSPI_Type * base)
{
    (base->TCR) = ((base->TCR) | (LPSPI_TCR_TXMSK_MASK));
}

static inline void LPSPI_ClearContCBit(LPSPI_Type * base)
{
    (base->TCR) = ((base->TCR) & (~LPSPI_TCR_CONTC_MASK));
}

static inline void LPSPI_SetContCBit(LPSPI_Type * base)
{
    (base->TCR) = ((base->TCR) | (LPSPI_TCR_CONTC_MASK));
}

static inline void LPSPI_SetClockPrescaler (LPSPI_Type * base, lpspi_prescaler_t prescaler)
{
    uint32_t lpspi_tmp = base->TCR;
    lpspi_tmp &= ~(LPSPI_TCR_PRESCALE_MASK);
    lpspi_tmp |= ((uint32_t)prescaler << LPSPI_TCR_PRESCALE_SHIFT);
    base->TCR = lpspi_tmp;
}

static inline lpspi_prescaler_t LPSPI_GetClockPrescaler (const LPSPI_Type * base)
{
    return (lpspi_prescaler_t)(((uint32_t)((base->TCR) & LPSPI_TCR_PRESCALE_MASK)) >> LPSPI_TCR_PRESCALE_SHIFT);
}

static inline void LPSPI_SetSamplingPoint (LPSPI_Type * base, bool isSamplingPointDelayed)
{
    uint32_t lpspi_tmp = base->CFGR1;
    lpspi_tmp &= ~(LPSPI_CFGR1_SAMPLE_MASK);
    lpspi_tmp |= ((uint32_t)isSamplingPointDelayed << LPSPI_CFGR1_SAMPLE_SHIFT);
    base->CFGR1 = lpspi_tmp;
}


#if defined(__cplusplus)
}
#endif


#endif 


