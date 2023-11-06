

#if !defined(LPI2C_HW_ACCESS_H)
#define LPI2C_HW_ACCESS_H

#include <stdbool.h>
#include "lpi2c_driver.h"
#include "device_registers.h"





#define   LPI2C_MASTER_DATA_MATCH_INT           0x4000UL   
#define   LPI2C_MASTER_PIN_LOW_TIMEOUT_INT      0x2000UL   
#define   LPI2C_MASTER_FIFO_ERROR_INT           0x1000UL   
#define   LPI2C_MASTER_ARBITRATION_LOST_INT      0x800UL   
#define   LPI2C_MASTER_NACK_DETECT_INT           0x400UL   
#define   LPI2C_MASTER_STOP_DETECT_INT           0x200UL   
#define   LPI2C_MASTER_END_PACKET_INT            0x100UL   
#define   LPI2C_MASTER_RECEIVE_DATA_INT            0x2UL   
#define   LPI2C_MASTER_TRANSMIT_DATA_INT           0x1UL   

#define   LPI2C_SLAVE_SMBUS_ALERT_RESPONSE_INT  0x8000UL   
#define   LPI2C_SLAVE_GENERAL_CALL_INT          0x4000UL   
#define   LPI2C_SLAVE_ADDRESS_MATCH_1_INT       0x2000UL   
#define   LPI2C_SLAVE_ADDRESS_MATCH_0_INT       0x1000UL   
#define   LPI2C_SLAVE_FIFO_ERROR_INT             0x800UL   
#define   LPI2C_SLAVE_BIT_ERROR_INT              0x400UL   
#define   LPI2C_SLAVE_STOP_DETECT_INT            0x200UL   
#define   LPI2C_SLAVE_REPEATED_START_INT         0x100UL   
#define   LPI2C_SLAVE_TRANSMIT_ACK_INT             0x8UL   
#define   LPI2C_SLAVE_ADDRESS_VALID_INT            0x4UL   
#define   LPI2C_SLAVE_RECEIVE_DATA_INT             0x2UL   
#define   LPI2C_SLAVE_TRANSMIT_DATA_INT            0x1UL   

typedef enum
{
    LPI2C_CFG_2PIN_OPEN_DRAIN             = 0U,  
    LPI2C_CFG_2PIN_OUTPUT_ONLY            = 1U,  
    LPI2C_CFG_2PIN_PUSH_PULL              = 2U,  
    LPI2C_CFG_4PIN_PUSH_PULL              = 3U,  
    LPI2C_CFG_2PIN_OPEN_DRAIN_SLAVE       = 4U,  
    LPI2C_CFG_2PIN_OUTPUT_ONLY_SLAVE      = 5U,  
    LPI2C_CFG_2PIN_PUSH_PULL_SLAVE        = 6U,  
    LPI2C_CFG_4PIN_PUSH_PULL_INVERTED     = 7U,  
} lpi2c_pin_config_t;

typedef enum
{
    LPI2C_NACK_RECEIVE    = 0U,  
    LPI2C_NACK_IGNORE     = 1U,  
} lpi2c_nack_config_t;

typedef enum
{
    LPI2C_MASTER_PRESC_DIV_1    = 0U,  
    LPI2C_MASTER_PRESC_DIV_2    = 1U,  
    LPI2C_MASTER_PRESC_DIV_4    = 2U,  
    LPI2C_MASTER_PRESC_DIV_8    = 3U,  
    LPI2C_MASTER_PRESC_DIV_16   = 4U,  
    LPI2C_MASTER_PRESC_DIV_32   = 5U,  
    LPI2C_MASTER_PRESC_DIV_64   = 6U,  
    LPI2C_MASTER_PRESC_DIV_128  = 7U,  
} lpi2c_master_prescaler_t;

typedef enum
{
    LPI2C_SLAVE_ADDR_MATCH_0_7BIT              = 0U,  
    LPI2C_SLAVE_ADDR_MATCH_0_10BIT             = 1U,  
    LPI2C_SLAVE_ADDR_MATCH_0_7BIT_OR_1_7BIT    = 2U,  
    LPI2C_SLAVE_ADDR_MATCH_0_10BIT_OR_1_10BIT  = 3U,  
    LPI2C_SLAVE_ADDR_MATCH_0_7BIT_OR_1_10BIT   = 4U,  
    LPI2C_SLAVE_ADDR_MATCH_0_10BIT_OR_1_7BIT   = 5U,  
    LPI2C_SLAVE_ADDR_MATCH_RANGE_7BIT          = 6U,  
    LPI2C_SLAVE_ADDR_MATCH_RANGE_10BIT         = 7U,  
} lpi2c_slave_addr_config_t;

typedef enum
{
    LPI2C_SLAVE_NACK_END_TRANSFER       = 0U,  
    LPI2C_SLAVE_NACK_CONTINUE_TRANSFER  = 1U,  
} lpi2c_slave_nack_config_t;

typedef enum
{
    LPI2C_SLAVE_TRANSMIT_ACK   = 0U,  
    LPI2C_SLAVE_TRANSMIT_NACK  = 1U,  
} lpi2c_slave_nack_transmit_t;


#if defined(__cplusplus)
extern "C" {
#endif


static inline uint16_t  LPI2C_Get_MasterRxFIFOSize(const LPI2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->PARAM;
    tmp = (tmp & LPI2C_PARAM_MRXFIFO_MASK) >> LPI2C_PARAM_MRXFIFO_SHIFT;
    tmp = 1UL << tmp;     
    return (uint16_t)tmp;
}


static inline uint16_t LPI2C_Get_MasterTxFIFOSize(const LPI2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->PARAM;
    tmp = (tmp & LPI2C_PARAM_MTXFIFO_MASK) >> LPI2C_PARAM_MTXFIFO_SHIFT;
    tmp = 1UL << tmp;      
    return (uint16_t)tmp;
}


static inline void LPI2C_Reset_MasterRxFIFOCmd(LPI2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t)baseAddr->MCR;
    regValue &= (uint32_t)(~(LPI2C_MCR_RRF_MASK));
    regValue |= LPI2C_MCR_RRF(1u);
    baseAddr->MCR = (uint32_t)regValue;
}


static inline void LPI2C_Reset_MasterTxFIFOCmd(LPI2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t)baseAddr->MCR;
    regValue &= (uint32_t)(~(LPI2C_MCR_RTF_MASK));
    regValue |= LPI2C_MCR_RTF(1u);
    baseAddr->MCR = (uint32_t)regValue;
}

static inline void LPI2C_Set_MasterSoftwareReset(LPI2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->MCR;
    regValue &= (uint32_t)(~(LPI2C_MCR_RST_MASK));
    regValue |= LPI2C_MCR_RST(enable);
    baseAddr->MCR = (uint32_t)regValue;
}

static inline void LPI2C_Set_MasterEnable(LPI2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->MCR;
    regValue &= (uint32_t)(~(LPI2C_MCR_MEN_MASK));
    regValue |= LPI2C_MCR_MEN(enable);
    baseAddr->MCR = (uint32_t)regValue;
}

static inline bool LPI2C_Get_MasterReceiveDataReadyEvent(const LPI2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t)baseAddr->MSR;
    regValue = (regValue & LPI2C_MSR_RDF_MASK) >> LPI2C_MSR_RDF_SHIFT;
    return (bool)regValue;
}

static inline bool LPI2C_Get_MasterTransmitDataRequestEvent(const LPI2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t)baseAddr->MSR;
    regValue = (regValue & LPI2C_MSR_TDF_MASK) >> LPI2C_MSR_TDF_SHIFT;
    return (bool)regValue;
}

static inline bool LPI2C_Get_MasterFIFOErrorEvent(const LPI2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t)baseAddr->MSR;
    regValue = (regValue & LPI2C_MSR_FEF_MASK) >> LPI2C_MSR_FEF_SHIFT;
    return (bool)regValue;
}

static inline bool LPI2C_Get_MasterArbitrationLostEvent(const LPI2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t)baseAddr->MSR;
    regValue = (regValue & LPI2C_MSR_ALF_MASK) >> LPI2C_MSR_ALF_SHIFT;
    return (bool)regValue;
}

static inline bool LPI2C_Get_MasterNACKDetectEvent(const LPI2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t)baseAddr->MSR;
    regValue = (regValue & LPI2C_MSR_NDF_MASK) >> LPI2C_MSR_NDF_SHIFT;
    return (bool)regValue;
}

static inline void LPI2C_Clear_MasterFIFOErrorEvent(LPI2C_Type *baseAddr)
{
    baseAddr->MSR = ((uint32_t)1U << LPI2C_MSR_FEF_SHIFT);
}

static inline void LPI2C_Clear_MasterArbitrationLostEvent(LPI2C_Type *baseAddr)
{
    baseAddr->MSR = ((uint32_t)1U << LPI2C_MSR_ALF_SHIFT);
}

static inline void LPI2C_Clear_MasterNACKDetectEvent(LPI2C_Type *baseAddr)
{
    baseAddr->MSR = ((uint32_t)1U << LPI2C_MSR_NDF_SHIFT);
}

static inline void LPI2C_Set_MasterRxDMA(LPI2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->MDER;
    regValue &= (uint32_t)(~(LPI2C_MDER_RDDE_MASK));
    regValue |= LPI2C_MDER_RDDE(enable);
    baseAddr->MDER = (uint32_t)regValue;
}

static inline void LPI2C_Set_MasterTxDMA(LPI2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->MDER;
    regValue &= (uint32_t)(~(LPI2C_MDER_TDDE_MASK));
    regValue |= LPI2C_MDER_TDDE(enable);
    baseAddr->MDER = (uint32_t)regValue;
}

static inline void LPI2C_Set_MasterInt(LPI2C_Type *baseAddr, uint32_t interrupts, bool enable)
{
    uint32_t tmp = baseAddr->MIER;

    if (enable == true)
    {
        tmp |= interrupts;
    }
    else
    {
        tmp &= ~interrupts;
    }
    baseAddr->MIER = tmp;
}

static inline void LPI2C_Set_MasterPinConfig(LPI2C_Type *baseAddr, lpi2c_pin_config_t configuration)
{
    uint32_t tmp = baseAddr->MCFGR1;
    tmp &= ~(LPI2C_MCFGR1_PINCFG_MASK);
    tmp |= LPI2C_MCFGR1_PINCFG(configuration);
    baseAddr->MCFGR1 = tmp;
}

static inline void LPI2C_Set_MasterNACKConfig(LPI2C_Type *baseAddr, lpi2c_nack_config_t configuration)
{
    uint32_t regValue = (uint32_t)baseAddr->MCFGR1;
    regValue &= (uint32_t)(~(LPI2C_MCFGR1_IGNACK_MASK));
    regValue |= LPI2C_MCFGR1_IGNACK(configuration);
    baseAddr->MCFGR1 = (uint32_t)regValue;
}

static inline void LPI2C_Set_MasterPrescaler(LPI2C_Type *baseAddr, lpi2c_master_prescaler_t prescaler)
{
    uint32_t tmp = baseAddr->MCFGR1;
    tmp &= ~(LPI2C_MCFGR1_PRESCALE_MASK);
    tmp |= LPI2C_MCFGR1_PRESCALE(prescaler);
    baseAddr->MCFGR1 = tmp;
}

static inline lpi2c_master_prescaler_t LPI2C_Get_MasterPrescaler(const LPI2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->MCFGR1;
    tmp = (tmp & LPI2C_MCFGR1_PRESCALE_MASK) >> LPI2C_MCFGR1_PRESCALE_SHIFT;
    return (lpi2c_master_prescaler_t)tmp;
}

static inline uint8_t LPI2C_Get_MasterClockHighPeriod(const LPI2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->MCCR0;
    tmp = (tmp & LPI2C_MCCR0_CLKHI_MASK) >> LPI2C_MCCR0_CLKHI_SHIFT;
    return (uint8_t)tmp;
}

static inline void LPI2C_Set_MasterClockHighPeriod(LPI2C_Type *baseAddr, uint8_t value)
{
    uint32_t tmp = baseAddr->MCCR0;
    tmp &= ~(LPI2C_MCCR0_CLKHI_MASK);
    tmp |= LPI2C_MCCR0_CLKHI(value);
    baseAddr->MCCR0 = tmp;
}

static inline void LPI2C_Set_MasterDataValidDelay(LPI2C_Type *baseAddr, uint8_t value)
{
    uint32_t tmp = baseAddr->MCCR0;
    tmp &= ~(LPI2C_MCCR0_DATAVD_MASK);
    tmp |= LPI2C_MCCR0_DATAVD(value);
    baseAddr->MCCR0 = tmp;
}

static inline void LPI2C_Set_MasterSetupHoldDelay(LPI2C_Type *baseAddr, uint8_t value)
{
    uint32_t tmp = baseAddr->MCCR0;
    tmp &= ~(LPI2C_MCCR0_SETHOLD_MASK);
    tmp |= LPI2C_MCCR0_SETHOLD(value);
    baseAddr->MCCR0 = tmp;
}

static inline void LPI2C_Set_MasterClockLowPeriod(LPI2C_Type *baseAddr, uint8_t value)
{
    uint32_t tmp = baseAddr->MCCR0;
    tmp &= ~(LPI2C_MCCR0_CLKLO_MASK);
    tmp |= LPI2C_MCCR0_CLKLO(value);
    baseAddr->MCCR0 = tmp;
}

static inline uint8_t LPI2C_Get_MasterClockLowPeriod(const LPI2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->MCCR0;
    tmp = (tmp & LPI2C_MCCR0_CLKLO_MASK) >> LPI2C_MCCR0_CLKLO_SHIFT;
    return (uint8_t)tmp;
}

#if(LPI2C_HAS_HIGH_SPEED_MODE)
static inline void LPI2C_Set_MasterDataValidDelayHS(LPI2C_Type *baseAddr, uint8_t value)
{
    uint32_t tmp = baseAddr->MCCR1;
    tmp &= ~(LPI2C_MCCR1_DATAVD_MASK);
    tmp |= LPI2C_MCCR1_DATAVD(value);
    baseAddr->MCCR1 = tmp;
}
#endif

#if(LPI2C_HAS_HIGH_SPEED_MODE)
static inline void LPI2C_Set_MasterSetupHoldDelayHS(LPI2C_Type *baseAddr, uint8_t value)
{
    uint32_t tmp = baseAddr->MCCR1;
    tmp &= ~(LPI2C_MCCR1_SETHOLD_MASK);
    tmp |= LPI2C_MCCR1_SETHOLD(value);
    baseAddr->MCCR1 = tmp;
}
#endif

#if(LPI2C_HAS_HIGH_SPEED_MODE)
static inline void LPI2C_Set_MasterClockHighPeriodHS(LPI2C_Type *baseAddr, uint8_t value)
{
    uint32_t tmp = baseAddr->MCCR1;
    tmp &= ~(LPI2C_MCCR1_CLKHI_MASK);
    tmp |= LPI2C_MCCR1_CLKHI(value);
    baseAddr->MCCR1 = tmp;
}
#endif

#if(LPI2C_HAS_HIGH_SPEED_MODE)
static inline uint8_t LPI2C_Get_MasterClockHighPeriodHS(const LPI2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->MCCR1;
    tmp = (tmp & LPI2C_MCCR1_CLKHI_MASK) >> LPI2C_MCCR1_CLKHI_SHIFT;
    return (uint8_t)tmp;
}
#endif

#if(LPI2C_HAS_HIGH_SPEED_MODE)
static inline void LPI2C_Set_MasterClockLowPeriodHS(LPI2C_Type *baseAddr, uint8_t value)
{
    uint32_t tmp = baseAddr->MCCR1;
    tmp &= ~(LPI2C_MCCR1_CLKLO_MASK);
    tmp |= LPI2C_MCCR1_CLKLO(value);
    baseAddr->MCCR1 = tmp;
}
#endif

#if(LPI2C_HAS_HIGH_SPEED_MODE)
static inline uint8_t LPI2C_Get_MasterClockLowPeriodHS(const LPI2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->MCCR1;
    tmp = (tmp & LPI2C_MCCR1_CLKLO_MASK) >> LPI2C_MCCR1_CLKLO_SHIFT;
    return (uint8_t)tmp;
}
#endif

static inline void LPI2C_Set_MasterRxFIFOWatermark(LPI2C_Type *baseAddr, uint16_t value)
{
    uint32_t tmp = baseAddr->MFCR;
    tmp &= ~(LPI2C_MFCR_RXWATER_MASK);
    tmp |= LPI2C_MFCR_RXWATER(value);
    baseAddr->MFCR = tmp;
}

static inline uint16_t LPI2C_Get_MasterRxFIFOWatermark(const LPI2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->MFCR;
    tmp = (tmp & LPI2C_MFCR_RXWATER_MASK) >> LPI2C_MFCR_RXWATER_SHIFT;
    return (uint16_t)tmp;
}

static inline void LPI2C_Set_MasterTxFIFOWatermark(LPI2C_Type *baseAddr, uint16_t value)
{
    uint32_t tmp = baseAddr->MFCR;
    tmp &= ~(LPI2C_MFCR_TXWATER_MASK);
    tmp |= LPI2C_MFCR_TXWATER(value);
    baseAddr->MFCR = tmp;
}

static inline uint16_t LPI2C_Get_MasterRxFIFOCount(const LPI2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->MFSR;
    tmp = (tmp & LPI2C_MFSR_RXCOUNT_MASK) >> LPI2C_MFSR_RXCOUNT_SHIFT;
    return (uint16_t)tmp;
}

static inline uint16_t LPI2C_Get_MasterTxFIFOCount(const LPI2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->MFSR;
    tmp = (tmp & LPI2C_MFSR_TXCOUNT_MASK) >> LPI2C_MFSR_TXCOUNT_SHIFT;
    return (uint16_t)tmp;
}

static inline void LPI2C_Cmd_MasterTransmit(LPI2C_Type *baseAddr, lpi2c_master_command_t cmd, uint8_t data)
{
    baseAddr->MTDR = ((uint32_t)cmd << 8U) + (uint32_t)data;
}

static inline uint8_t LPI2C_Get_MasterRxData(const LPI2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->MRDR;
    tmp = (tmp & LPI2C_MRDR_DATA_MASK) >> LPI2C_MRDR_DATA_SHIFT;
    return (uint8_t)tmp;
}

static inline void LPI2C_Set_SlaveEnable(LPI2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->SCR;
    regValue &= (uint32_t)(~(LPI2C_SCR_SEN_MASK));
    regValue |= LPI2C_SCR_SEN(enable);
    baseAddr->SCR = (uint32_t)regValue;
}

static inline void LPI2C_Set_SlaveSoftwareReset(LPI2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->SCR;
    regValue &= (uint32_t)(~(LPI2C_SCR_RST_MASK));
    regValue |= LPI2C_SCR_RST(enable);
    baseAddr->SCR = (uint32_t)regValue;
}

#if(LPI2C_HAS_ULTRA_FAST_MODE)
static inline bool LPI2C_Get_SlaveFIFOErrorEvent(const LPI2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t)baseAddr->SSR;
    regValue = (regValue & LPI2C_SSR_FEF_MASK) >> LPI2C_SSR_FEF_SHIFT;
    return (bool)regValue;
}
#endif

static inline bool LPI2C_Get_SlaveBitErrorEvent(const LPI2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t)baseAddr->SSR;
    regValue = (regValue & LPI2C_SSR_BEF_MASK) >> LPI2C_SSR_BEF_SHIFT;
    return (bool)regValue;
}

static inline bool LPI2C_Get_SlaveSTOPDetectEvent(const LPI2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t)baseAddr->SSR;
    regValue = (regValue & LPI2C_SSR_SDF_MASK) >> LPI2C_SSR_SDF_SHIFT;
    return (bool)regValue;
}

static inline bool LPI2C_Get_SlaveRepeatedStartEvent(const LPI2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t)baseAddr->SSR;
    regValue = (regValue & LPI2C_SSR_RSF_MASK) >> LPI2C_SSR_RSF_SHIFT;
    return (bool)regValue;
}

static inline bool LPI2C_Get_SlaveAddressValidEvent(const LPI2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t)baseAddr->SSR;
    regValue = (regValue & LPI2C_SSR_AVF_MASK) >> LPI2C_SSR_AVF_SHIFT;
    return (bool)regValue;
}

static inline bool LPI2C_Get_SlaveReceiveDataEvent(const LPI2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t)baseAddr->SSR;
    regValue = (regValue & LPI2C_SSR_RDF_MASK) >> LPI2C_SSR_RDF_SHIFT;
    return (bool)regValue;
}

static inline bool LPI2C_Get_SlaveTransmitDataEvent(const LPI2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t)baseAddr->SSR;
    regValue = (regValue & LPI2C_SSR_TDF_MASK) >> LPI2C_SSR_TDF_SHIFT;
    return (bool)regValue;
}

#if(LPI2C_HAS_ULTRA_FAST_MODE)
static inline void LPI2C_Clear_SlaveFIFOErrorEvent(LPI2C_Type *baseAddr)
{
    baseAddr->SSR = ((uint32_t)1U << LPI2C_SSR_FEF_SHIFT);
}
#endif

static inline void LPI2C_Clear_SlaveBitErrorEvent(LPI2C_Type *baseAddr)
{
    baseAddr->SSR = ((uint32_t)1U << LPI2C_SSR_BEF_SHIFT);
}

static inline void LPI2C_Clear_SlaveSTOPDetectEvent(LPI2C_Type *baseAddr)
{
    baseAddr->SSR = ((uint32_t)1U << LPI2C_SSR_SDF_SHIFT);
}

static inline void LPI2C_Clear_SlaveRepeatedStartEvent(LPI2C_Type *baseAddr)
{
    baseAddr->SSR = ((uint32_t)1U << LPI2C_SSR_RSF_SHIFT);
}

static inline void LPI2C_Set_SlaveInt(LPI2C_Type *baseAddr, uint32_t interrupts, bool enable)
{
    uint32_t tmp = baseAddr->SIER;

    if (enable == true)
    {
        tmp |= interrupts;
    }
    else
    {
        tmp &= ~interrupts;
    }
    baseAddr->SIER = tmp;
}

static inline bool LPI2C_Get_SlaveInt(const LPI2C_Type *baseAddr, uint32_t interrupts)
{
    uint32_t tmp = baseAddr->SIER;
    bool hasInterrupts = false;

    if ((tmp & interrupts) != (uint32_t)0U)
    {
        hasInterrupts = true;
    }

    return hasInterrupts;
}

static inline void LPI2C_Set_SlaveRxDMA(LPI2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->SDER;
    regValue &= (uint32_t)(~(LPI2C_SDER_RDDE_MASK));
    regValue |= LPI2C_SDER_RDDE(enable);
    baseAddr->SDER = (uint32_t)regValue;
}

static inline void LPI2C_Set_SlaveTxDMA(LPI2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->SDER;
    regValue &= (uint32_t)(~(LPI2C_SDER_TDDE_MASK));
    regValue |= LPI2C_SDER_TDDE(enable);
    baseAddr->SDER = (uint32_t)regValue;
}

static inline void LPI2C_Set_SlaveAddrConfig(LPI2C_Type *baseAddr, lpi2c_slave_addr_config_t configuration)
{
    uint32_t tmp = baseAddr->SCFGR1;
    tmp &= ~(LPI2C_SCFGR1_ADDRCFG_MASK);
    tmp |= LPI2C_SCFGR1_ADDRCFG(configuration);
    baseAddr->SCFGR1 = tmp;
}

static inline void LPI2C_Set_SlaveHighSpeedModeDetect(LPI2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->SCFGR1;
    regValue &= (uint32_t)(~(LPI2C_SCFGR1_HSMEN_MASK));
    regValue |= LPI2C_SCFGR1_HSMEN(enable);
    baseAddr->SCFGR1 = (uint32_t)regValue;
}

static inline void LPI2C_Set_SlaveIgnoreNACK(LPI2C_Type *baseAddr, lpi2c_slave_nack_config_t nack_config)
{
    uint32_t regValue = (uint32_t)baseAddr->SCFGR1;
    regValue &= (uint32_t)(~(LPI2C_SCFGR1_IGNACK_MASK));
    regValue |= LPI2C_SCFGR1_IGNACK(nack_config);
    baseAddr->SCFGR1 = (uint32_t)regValue;
}

static inline void LPI2C_Set_SlaveACKStall(LPI2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->SCFGR1;
    regValue &= (uint32_t)(~(LPI2C_SCFGR1_ACKSTALL_MASK));
    regValue |= LPI2C_SCFGR1_ACKSTALL(enable);
    baseAddr->SCFGR1 = (uint32_t)regValue;
}

static inline void LPI2C_Set_SlaveTXDStall(LPI2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->SCFGR1;
    regValue &= (uint32_t)(~(LPI2C_SCFGR1_TXDSTALL_MASK));
    regValue |= LPI2C_SCFGR1_TXDSTALL(enable);
    baseAddr->SCFGR1 = (uint32_t)regValue;
}

static inline void LPI2C_Set_SlaveRXStall(LPI2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->SCFGR1;
    regValue &= (uint32_t)(~(LPI2C_SCFGR1_RXSTALL_MASK));
    regValue |= LPI2C_SCFGR1_RXSTALL(enable);
    baseAddr->SCFGR1 = (uint32_t)regValue;
}

static inline void LPI2C_Set_SlaveAddrStall(LPI2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->SCFGR1;
    regValue &= (uint32_t)(~(LPI2C_SCFGR1_ADRSTALL_MASK));
    regValue |= LPI2C_SCFGR1_ADRSTALL(enable);
    baseAddr->SCFGR1 = (uint32_t)regValue;
}

static inline void LPI2C_Set_SlaveAddr0(LPI2C_Type *baseAddr, uint16_t addr)
{
    uint32_t tmp = baseAddr->SAMR;
    tmp &= ~(LPI2C_SAMR_ADDR0_MASK);
    tmp |= LPI2C_SAMR_ADDR0(addr);
    baseAddr->SAMR = tmp;
}

static inline uint16_t LPI2C_Get_SlaveReceivedAddr(const LPI2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->SASR;
    tmp = (tmp & LPI2C_SASR_RADDR_MASK) >> LPI2C_SASR_RADDR_SHIFT;
    return (uint16_t)tmp;
}

static inline void LPI2C_Set_SlaveTransmitNACK(LPI2C_Type *baseAddr, lpi2c_slave_nack_transmit_t nack)
{
    uint32_t regValue = (uint32_t)baseAddr->STAR;
    regValue &= (uint32_t)(~(LPI2C_STAR_TXNACK_MASK));
    regValue |= LPI2C_STAR_TXNACK(nack);
    baseAddr->STAR = (uint32_t)regValue;
}

static inline void LPI2C_Transmit_SlaveData(LPI2C_Type *baseAddr, uint8_t data)
{
    baseAddr->STDR = (uint32_t)data;
}

static inline uint8_t LPI2C_Get_SlaveData(const LPI2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->SRDR;
    tmp = (tmp & LPI2C_SRDR_DATA_MASK) >> LPI2C_SRDR_DATA_SHIFT;
    return (uint8_t)tmp;
}

void LPI2C_Init(LPI2C_Type *baseAddr);


#if defined(__cplusplus)
}
#endif


#endif 


