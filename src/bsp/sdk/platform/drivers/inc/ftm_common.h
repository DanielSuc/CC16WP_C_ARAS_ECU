#ifndef FTM_COMMON_H
#define FTM_COMMON_H
#include <stddef.h>
#include "status.h"
#include "device_registers.h"
#include "callbacks.h"

extern FTM_Type * const g_ftmBase[FTM_INSTANCE_COUNT];

extern const IRQn_Type g_ftmIrqId[FTM_INSTANCE_COUNT][FEATURE_FTM_CHANNEL_COUNT];
extern const IRQn_Type g_ftmFaultIrqId[FTM_INSTANCE_COUNT];
extern const IRQn_Type g_ftmOverflowIrqId[FTM_INSTANCE_COUNT];
extern const IRQn_Type g_ftmReloadIrqId[FTM_INSTANCE_COUNT];

#ifdef ERRATA_E10856
extern bool faultDetection;
#endif


#define FTM_RMW_SC(base, mask, value) (((base)->SC) = ((((base)->SC) & ~(mask)) | (value)))

#define FTM_RMW_CNT(base, mask, value) (((base)->CNT) = ((((base)->CNT) & ~(mask)) | (value)))

#define FTM_RMW_MOD(base, mask, value) (((base)->MOD) = ((((base)->MOD) & ~(mask)) | (value)))

#define FTM_RMW_CNTIN(base, mask, value) (((base)->CNTIN) = ((((base)->CNTIN) & ~(mask)) | (value)))

#define FTM_RMW_STATUS(base, mask, value) (((base)->STATUS) = ((((base)->STATUS) & ~(mask)) | (value)))

#define FTM_RMW_MODE(base, mask, value) (((base)->MODE) = ((((base)->MODE) & ~(mask)) | (value)))

#define FTM_RMW_CnSCV_REG(base, channel, mask, value) (((base)->CONTROLS[channel].CnSC) = ((((base)->CONTROLS[channel].CnSC) & ~(mask)) | (value)))

#define FTM_RMW_DEADTIME(base, mask, value) (((base)->DEADTIME) = ((((base)->DEADTIME) & ~(mask)) | (value)))
#define FTM_RMW_EXTTRIG_REG(base, mask, value) (((base)->EXTTRIG) = ((((base)->EXTTRIG) & ~(mask)) | (value)))

#define FTM_RMW_FLTCTRL(base, mask, value) (((base)->FLTCTRL) = ((((base)->FLTCTRL) & ~(mask)) | (value)))

#define FTM_RMW_FMS(base, mask, value) (((base)->FMS) = ((((base)->FMS) & ~(mask)) | (value)))

#define FTM_RMW_CONF(base, mask, value) (((base)->CONF) = ((((base)->CONF) & ~(mask)) | (value)))

#define FTM_RMW_POL(base, mask, value) (((base)->POL) = ((((base)->POL) & ~(mask)) | (value)))

#define FTM_RMW_FILTER(base, mask, value) (((base)->FILTER) = ((((base)->FILTER) & ~(mask)) | (value)))

#define FTM_RMW_SYNC(base, mask, value) (((base)->SYNC) = ((((base)->SYNC) & ~(mask)) | (value)))

#define FTM_RMW_QDCTRL(base, mask, value) (((base)->QDCTRL) = ((((base)->QDCTRL) & ~(mask)) | (value)))

#define FTM_RMW_PAIR0DEADTIME(base, mask, value) (((base)->PAIR0DEADTIME) = ((((base)->PAIR0DEADTIME) & ~(mask)) | (value)))

#define FTM_RMW_PAIR1DEADTIME(base, mask, value) (((base)->PAIR1DEADTIME) = ((((base)->PAIR1DEADTIME) & ~(mask)) | (value)))

#define FTM_RMW_PAIR2DEADTIME(base, mask, value) (((base)->PAIR2DEADTIME) = ((((base)->PAIR2DEADTIME) & ~(mask)) | (value)))

#define FTM_RMW_PAIR3DEADTIME(base, mask, value) (((base)->PAIR3DEADTIME) = ((((base)->PAIR3DEADTIME) & ~(mask)) | (value)))

#if FEATURE_FTM_HAS_SUPPORTED_DITHERING
#define FTM_RMW_MOD_MIRROR(base, mask, value) (((base)->MOD_MIRROR) = ((((base)->MOD_MIRROR) & ~(mask)) | (value)))

#define FTM_RMW_CnV_MIRROR(base, channel, mask, value) (((base)->CV_MIRROR[channel]) = ((((base)->CV_MIRROR[channel]) & ~(mask)) | (value)))
#endif

#define CHAN0_IDX (0U)
#define CHAN1_IDX (1U)
#define CHAN2_IDX (2U)
#define CHAN3_IDX (3U)
#define CHAN4_IDX (4U)
#define CHAN5_IDX (5U)
#define CHAN6_IDX (6U)
#define CHAN7_IDX (7U)

typedef enum
{
	read_allowed 				= 0x00U,	
	write_allowed				= 0x01U,	
}ftm_counter_access;

typedef enum
{
    FTM_MODE_NOT_INITIALIZED    = 0x00U,    
    FTM_MODE_INPUT_CAPTURE      = 0x01U,    
    FTM_MODE_OUTPUT_COMPARE     = 0x02U,    
    FTM_MODE_EDGE_ALIGNED_PWM   = 0x03U,    
    FTM_MODE_CEN_ALIGNED_PWM    = 0x04U,    
    FTM_MODE_QUADRATURE_DECODER = 0x05U,    
    FTM_MODE_UP_TIMER           = 0x06U,    
    FTM_MODE_UP_DOWN_TIMER      = 0x07U     
} ftm_config_mode_t;

typedef enum
{
    FTM_CLOCK_SOURCE_NONE           = 0x00U,    
    FTM_CLOCK_SOURCE_SYSTEMCLK      = 0x01U,    
    FTM_CLOCK_SOURCE_FIXEDCLK       = 0x02U,    
    FTM_CLOCK_SOURCE_EXTERNALCLK    = 0x03U     
} ftm_clock_source_t;

typedef enum
{
    FTM_CLOCK_DIVID_BY_1    = 0x00U,    
    FTM_CLOCK_DIVID_BY_2    = 0x01U,    
    FTM_CLOCK_DIVID_BY_4    = 0x02U,    
    FTM_CLOCK_DIVID_BY_8    = 0x03U,    
    FTM_CLOCK_DIVID_BY_16   = 0x04U,    
    FTM_CLOCK_DIVID_BY_32   = 0x05U,    
    FTM_CLOCK_DIVID_BY_64   = 0x06U,    
    FTM_CLOCK_DIVID_BY_128  = 0x07U     
} ftm_clock_ps_t;

typedef enum
{
    FTM_CHANNEL0_INT_ENABLE       = 0x00000001U,    
    FTM_CHANNEL1_INT_ENABLE       = 0x00000002U,    
    FTM_CHANNEL2_INT_ENABLE       = 0x00000004U,    
    FTM_CHANNEL3_INT_ENABLE       = 0x00000008U,    
    FTM_CHANNEL4_INT_ENABLE       = 0x00000010U,    
    FTM_CHANNEL5_INT_ENABLE       = 0x00000020U,    
    FTM_CHANNEL6_INT_ENABLE       = 0x00000040U,    
    FTM_CHANNEL7_INT_ENABLE       = 0x00000080U,    
    FTM_FAULT_INT_ENABLE          = 0x00000100U,    
    FTM_TIME_OVER_FLOW_INT_ENABLE = 0x00000200U,    
    FTM_RELOAD_INT_ENABLE         = 0x00000400U     
} ftm_interrupt_option_t;

typedef enum
{
    FTM_CHANNEL0_FLAG        = 0x00000001U,    
    FTM_CHANNEL1_FLAG        = 0x00000002U,    
    FTM_CHANNEL2_FLAG        = 0x00000004U,    
    FTM_CHANNEL3_FLAG        = 0x00000008U,    
    FTM_CHANNEL4_FLAG        = 0x00000010U,    
    FTM_CHANNEL5_FLAG        = 0x00000020U,    
    FTM_CHANNEL6_FLAG        = 0x00000040U,    
    FTM_CHANNEL7_FLAG        = 0x00000080U,    
    FTM_FAULT_FLAG           = 0x00000100U,    
    FTM_TIME_OVER_FLOW_FLAG  = 0x00000200U,    
    FTM_RELOAD_FLAG          = 0x00000400U,    
    FTM_CHANNEL_TRIGGER_FLAG = 0x00000800U     
} ftm_status_flag_t;

typedef enum
{
    FTM_SYSTEM_CLOCK    = 0U,       
    FTM_PWM_SYNC        = 1U        
} ftm_reg_update_t;

typedef enum
{
    FTM_WAIT_LOADING_POINTS = 0U,   
    FTM_UPDATE_NOW          = 1U    
} ftm_pwm_sync_mode_t;

typedef enum
{
    FTM_DEADTIME_DIVID_BY_1  = 0x01U, 
    FTM_DEADTIME_DIVID_BY_4  = 0x02U, 
    FTM_DEADTIME_DIVID_BY_16 = 0x03U  
} ftm_deadtime_ps_t;

typedef enum
{
    FTM_BDM_MODE_00 = 0x00U,    
    FTM_BDM_MODE_01 = 0x01U,    
    FTM_BDM_MODE_10 = 0x02U,    
    FTM_BDM_MODE_11 = 0x03U     
} ftm_bdm_mode_t;

typedef struct
{
    ftm_clock_source_t ftmClockSource;                                          
    ftm_config_mode_t ftmMode;                                                  
    uint16_t ftmPeriod;                                                         
    uint32_t ftmSourceClockFrequency;                                           
    uint16_t measurementResults[FEATURE_FTM_CHANNEL_COUNT];                     
    volatile uint32_t counter_diff_high[FEATURE_FTM_CHANNEL_COUNT];					
    volatile uint32_t counter_diff_low[FEATURE_FTM_CHANNEL_COUNT];					
    volatile ftm_counter_access  access_flag[FEATURE_FTM_CHANNEL_COUNT];		
    volatile uint8_t zero_detection[FEATURE_FTM_CHANNEL_COUNT];					
    volatile uint32_t edge_counter_val[FEATURE_FTM_CHANNEL_COUNT];				
    void *encoder_pin[FEATURE_FTM_CHANNEL_COUNT];								
    void * channelsCallbacksParams[FEATURE_FTM_CHANNEL_COUNT];     
    ic_callback_t channelsCallbacks[FEATURE_FTM_CHANNEL_COUNT];    
    bool enableNotification[FEATURE_FTM_CHANNEL_COUNT];            
} ftm_state_t;


typedef struct
{
    bool softwareSync;                          
    bool hardwareSync0;                         
    bool hardwareSync1;                         
    bool hardwareSync2;                         
    bool maxLoadingPoint;                       
    bool minLoadingPoint;                       
    ftm_reg_update_t inverterSync;              
    ftm_reg_update_t outRegSync;                
    ftm_reg_update_t maskRegSync;               
    ftm_reg_update_t initCounterSync;           
    bool autoClearTrigger;                      
    ftm_pwm_sync_mode_t syncPoint;              
} ftm_pwm_sync_t;

typedef struct
{
    ftm_pwm_sync_t syncMethod;              
    ftm_config_mode_t ftmMode;              
    ftm_clock_ps_t ftmPrescaler;            
    ftm_clock_source_t ftmClockSource;      
    ftm_bdm_mode_t BDMMode;                 
    bool isTofIsrEnabled;                   
    bool enableInitializationTrigger;       
} ftm_user_config_t;

extern ftm_state_t * ftmStatePtr[FTM_INSTANCE_COUNT];


#if defined(__cplusplus)
extern "C" {
#endif

static inline void FTM_DRV_SetClockFilterPs(FTM_Type * const ftmBase,
                                            uint8_t filterPrescale)
{
    FTM_RMW_SC(ftmBase, FTM_SC_FLTPS_MASK, FTM_SC_FLTPS(filterPrescale));
}

static inline uint8_t FTM_DRV_GetClockFilterPs(const FTM_Type * ftmBase)
{
    return (uint8_t)((((ftmBase)->SC) & FTM_SC_FLTPS_MASK) >> FTM_SC_FLTPS_SHIFT);
}

static inline uint16_t FTM_DRV_GetCounter(const FTM_Type * ftmBase)
{
    return (uint16_t)((((ftmBase)->CNT) & FTM_CNT_COUNT_MASK) >> FTM_CNT_COUNT_SHIFT);
}

static inline uint16_t FTM_DRV_GetMod(const FTM_Type * ftmBase)
{
    return (uint16_t)((((ftmBase)->MOD) & FTM_MOD_MOD_MASK) >> FTM_MOD_MOD_SHIFT);
}

static inline uint16_t FTM_DRV_GetCounterInitVal(const FTM_Type * ftmBase)
{
    return (uint16_t)((((ftmBase)->CNTIN) & FTM_CNTIN_INIT_MASK) >> FTM_CNTIN_INIT_SHIFT);
}

static inline void FTM_DRV_ClearChSC(FTM_Type * const ftmBase,
                                     uint8_t channel)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    ((ftmBase)->CONTROLS[channel].CnSC) = 0U;
#ifdef ERRATA_E9005
    ftmBase->CONTROLS[channel].CnSC;
#endif
}

static inline uint8_t FTM_DRV_GetChnEdgeLevel(const FTM_Type * ftmBase,
                                              uint8_t channel)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);
    uint8_t retValue;

    retValue = (uint8_t)((((ftmBase)->CONTROLS[channel].CnSC) & FTM_CnSC_ELSA_MASK) >> FTM_CnSC_ELSA_SHIFT);

    retValue |= (uint8_t)(((((ftmBase)->CONTROLS[channel].CnSC) & FTM_CnSC_ELSB_MASK) >> FTM_CnSC_ELSB_SHIFT) << 1U);

    return retValue;
}

static inline void FTM_DRV_SetChnIcrstCmd(FTM_Type * const ftmBase,
                                          uint8_t channel,
                                          bool enable)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    FTM_RMW_CnSCV_REG(ftmBase, channel, FTM_CnSC_ICRST_MASK, FTM_CnSC_ICRST(enable));
}

static inline bool FTM_DRV_IsChnIcrst(const FTM_Type * ftmBase,
                                      uint8_t channel)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    return (((ftmBase)->CONTROLS[channel].CnSC) & FTM_CnSC_ICRST_MASK) != 0U;
}

static inline void FTM_DRV_SetChnDmaCmd(FTM_Type * const ftmBase,
                                        uint8_t channel,
                                        bool enable)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    FTM_RMW_CnSCV_REG(ftmBase, channel, FTM_CnSC_DMA_MASK, FTM_CnSC_DMA(enable));
}

static inline bool FTM_DRV_IsChnDma(const FTM_Type * ftmBase,
                                    uint8_t channel)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    return (((ftmBase)->CONTROLS[channel].CnSC) & FTM_CnSC_DMA_MASK) != 0U;
}

static inline void FTM_DRV_SetTrigModeControlCmd(FTM_Type * const ftmBase,
                                                 uint8_t channel,
                                                 bool enable)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    FTM_RMW_CnSCV_REG(ftmBase, channel, FTM_CnSC_TRIGMODE_MASK, FTM_CnSC_TRIGMODE((enable)));
}

static inline bool FTM_DRV_GetTriggerControled(const FTM_Type * ftmBase,
                                               uint8_t channel)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    return (((ftmBase)->CONTROLS[channel].CnSC) & FTM_CnSC_TRIGMODE_MASK) != 0U;
}

static inline bool FTM_DRV_GetChInputState(const FTM_Type * ftmBase,
                                           uint8_t channel)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    return (((ftmBase)->CONTROLS[channel].CnSC) & FTM_CnSC_CHIS_MASK) != 0U;
}

static inline bool FTM_DRV_GetChOutputValue(const FTM_Type * ftmBase,
                                            uint8_t channel)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    return (((ftmBase)->CONTROLS[channel].CnSC) & FTM_CnSC_CHOV_MASK) != 0U;
}

static inline uint16_t FTM_DRV_GetChnCountVal(const FTM_Type * ftmBase,
                                              uint8_t channel)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    return (uint16_t)((ftmBase)->CONTROLS[channel].CnV);
}

static inline bool FTM_DRV_GetChnEventStatus(const FTM_Type * ftmBase,
                                             uint8_t channel)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    return (((ftmBase)->STATUS) & (1UL << channel)) != 0U;
}

static inline uint32_t FTM_DRV_GetEventStatus(const FTM_Type * ftmBase)
{
    return ((ftmBase)->STATUS) & (0xFFU);
}

static inline void FTM_DRV_ClearChnEventStatus(FTM_Type * const ftmBase,
                                               uint8_t channel)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    ((ftmBase)->STATUS) &= (~(1UL << channel));
#ifdef ERRATA_E9005
    ftmBase->STATUS;
#endif
}

static inline void FTM_DRV_SetChnOutputMask(FTM_Type * const ftmBase,
                                            uint8_t channel,
                                            bool mask)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    if (mask)
    {
        ((ftmBase)->OUTMASK) |= (1UL << channel);
    }
    else
    {
        ((ftmBase)->OUTMASK) &= ~(1UL << channel);
    }
}

static inline void FTM_DRV_SetChnOutputInitStateCmd(FTM_Type * const ftmBase,
                                                    uint8_t channel,
                                                    bool state)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    if (state)
    {
        ((ftmBase)->OUTINIT) |= (1UL << channel);
    }
    else
    {
        ((ftmBase)->OUTINIT) &= ~(1UL << channel);
    }
}

static inline void FTM_DRV_DisableFaultInt(FTM_Type * const ftmBase)
{
    FTM_RMW_MODE(ftmBase, FTM_MODE_FAULTIE_MASK, FTM_MODE_FAULTIE(0U));
}

static inline void FTM_DRV_SetCaptureTestCmd(FTM_Type * const ftmBase,
                                             bool enable)
{
    FTM_RMW_MODE(ftmBase, FTM_MODE_CAPTEST_MASK, FTM_MODE_CAPTEST(enable));
}

static inline bool FTM_DRV_IsFtmEnable(const FTM_Type * ftmBase)
{
    return ((ftmBase->MODE & FTM_MODE_FTMEN_MASK) >> FTM_MODE_FTMEN_SHIFT) != 0U;
}

static inline void FTM_DRV_SetCountReinitSyncCmd(FTM_Type * const ftmBase,
                                                 bool enable)
{
    FTM_RMW_SYNC(ftmBase, FTM_SYNC_REINIT_MASK, FTM_SYNC_REINIT(enable));
}

static inline bool FTM_DRV_IsWriteProtectionEnabled(const FTM_Type * ftmBase)
{
    return (ftmBase->FMS & FTM_FMS_WPEN_MASK) != 0U;
}

static inline bool FTM_DRV_IsFaultInputEnabled(const FTM_Type * ftmBase)
{
    return (ftmBase->FMS & FTM_FMS_FAULTIN_MASK) != 0U;
}

static inline bool FTM_DRV_IsFaultFlagDetected(const FTM_Type * ftmBase,
                                               uint8_t channel)
{
    DEV_ASSERT(channel < CHAN4_IDX);

    return (ftmBase->FMS & (FTM_FMS_FAULTF0_MASK << channel)) != 0U;
}

static inline void FTM_DRV_ClearFaultFlagDetected(FTM_Type * const ftmBase,
                                                  uint8_t channel)
{
    DEV_ASSERT(channel < CHAN4_IDX);

    ((ftmBase)->FMS) &= (~(1UL << channel));
#ifdef ERRATA_E9005
    ftmBase->FMS;
#endif
}

static inline void FTM_DRV_SetDualChnInvertCmd(FTM_Type * const ftmBase,
                                               uint8_t chnlPairNum,
                                               bool enable)
{
    DEV_ASSERT(chnlPairNum < (FEATURE_FTM_CHANNEL_COUNT >> 1U));

    if (enable)
    {
        ((ftmBase)->INVCTRL) |=  (1UL << chnlPairNum);
    }
    else
    {
        ((ftmBase)->INVCTRL) &=  ~(1UL << chnlPairNum);
    }
}

static inline void FTM_DRV_SetChnSoftwareCtrlCmd(FTM_Type * const ftmBase,
                                                 uint8_t channel,
                                                 bool enable)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    if (enable)
    {
        ((ftmBase)->SWOCTRL) |=  (1UL << channel);
    }
    else
    {
        ((ftmBase)->SWOCTRL) &=  ~(1UL << channel);
    }
}

static inline void FTM_DRV_SetChnSoftwareCtrlVal(FTM_Type * const ftmBase,
                                                 uint8_t channel,
                                                 bool enable)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    if ((uint32_t)enable != (((uint32_t)ftmBase->POL >> (uint32_t)channel) & (uint32_t)1U))
    {
        ((ftmBase)->SWOCTRL) |=  (1UL << (channel + FTM_SWOCTRL_CH0OCV_SHIFT));
    }
    else
    {
        ((ftmBase)->SWOCTRL) &=  ~(1UL << (channel + FTM_SWOCTRL_CH0OCV_SHIFT));
    }
}

static inline void FTM_DRV_SetGlobalLoadCmd(FTM_Type * const ftmBase)
{
    ((ftmBase)->PWMLOAD) |=  (1UL << FTM_PWMLOAD_GLDOK_SHIFT);
}

static inline void FTM_DRV_SetLoadCmd(FTM_Type * const ftmBase,
                                      bool enable)
{
    if (enable)
    {
        ((ftmBase)->PWMLOAD) |=  (1UL << FTM_PWMLOAD_GLEN_SHIFT);
    }
    else
    {
        ((ftmBase)->PWMLOAD) &=  ~(1UL << FTM_PWMLOAD_GLEN_SHIFT);
    }
}

static inline void FTM_DRV_SetHalfCycleCmd(FTM_Type * const ftmBase,
                                           bool enable)
{
    if (enable)
    {
        ((ftmBase)->PWMLOAD) |=  (1UL << FTM_PWMLOAD_HCSEL_SHIFT);
    }
    else
    {
        ((ftmBase)->PWMLOAD) &=  ~(1UL << FTM_PWMLOAD_HCSEL_SHIFT);
    }
}

static inline void FTM_DRV_SetPwmLoadCmd(FTM_Type * const ftmBase,
                                         bool enable)
{
    if (enable)
    {
        ((ftmBase)->PWMLOAD) |=  (1UL << FTM_PWMLOAD_LDOK_SHIFT);
    }
    else
    {
        ((ftmBase)->PWMLOAD) &=  ~(1UL << FTM_PWMLOAD_LDOK_SHIFT);
    }
}

static inline void FTM_DRV_SetPwmLoadChnSelCmd(FTM_Type * const ftmBase,
                                               uint8_t channel,
                                               bool enable)
{
    DEV_ASSERT(channel < FEATURE_FTM_CHANNEL_COUNT);

    if (enable)
    {
        ((ftmBase)->PWMLOAD) |=  (1UL << channel);
    }
    else
    {
        ((ftmBase)->PWMLOAD) &=  ~(1UL << channel);
    }
}

static inline void FTM_DRV_SetInitTrigOnReloadCmd(FTM_Type * const ftmBase,
                                                  bool enable)
{
    ftmBase->CONF = (ftmBase->CONF & ~FTM_CONF_ITRIGR_MASK) | FTM_CONF_ITRIGR(enable);
}

static inline void FTM_DRV_SetGlobalTimeBaseOutputCmd(FTM_Type * const ftmBase,
                                                      bool enable)
{
    ftmBase->CONF = (ftmBase->CONF & ~FTM_CONF_GTBEOUT_MASK) | FTM_CONF_GTBEOUT(enable);
}

static inline void FTM_DRV_SetGlobalTimeBaseCmd(FTM_Type * const ftmBase,
                                                bool enable)
{
    ftmBase->CONF = (ftmBase->CONF & ~FTM_CONF_GTBEEN_MASK) | FTM_CONF_GTBEEN(enable);
}

static inline void FTM_DRV_SetLoadFreq(FTM_Type * const ftmBase,
                                       uint8_t val)
{
    FTM_RMW_CONF(ftmBase, FTM_CONF_LDFQ_MASK, FTM_CONF_LDFQ(val));
}

static inline void FTM_DRV_SetExtPairDeadtimeValue(FTM_Type * const ftmBase,
                                                   uint8_t channelPair,
                                                   uint8_t value)
{
    DEV_ASSERT(value < 16U);
    DEV_ASSERT(channelPair < CHAN4_IDX);

    switch (channelPair)
    {
        case CHAN0_IDX:
            FTM_RMW_PAIR0DEADTIME(ftmBase, FTM_PAIR0DEADTIME_DTVALEX_MASK, FTM_PAIR0DEADTIME_DTVALEX(value));
            break;
        case CHAN1_IDX:
            FTM_RMW_PAIR1DEADTIME(ftmBase, FTM_PAIR1DEADTIME_DTVALEX_MASK, FTM_PAIR1DEADTIME_DTVALEX(value));
            break;
        case CHAN2_IDX:
            FTM_RMW_PAIR2DEADTIME(ftmBase, FTM_PAIR2DEADTIME_DTVALEX_MASK, FTM_PAIR2DEADTIME_DTVALEX(value));
            break;
        case CHAN3_IDX:
            FTM_RMW_PAIR3DEADTIME(ftmBase, FTM_PAIR3DEADTIME_DTVALEX_MASK, FTM_PAIR3DEADTIME_DTVALEX(value));
            break;
        default:
            break;
    }
}

static inline void FTM_DRV_SetPairDeadtimePrescale(FTM_Type * const ftmBase,
                                                   uint8_t channelPair,
                                                   ftm_deadtime_ps_t divider)
{
    DEV_ASSERT(channelPair < CHAN4_IDX);

    switch (channelPair)
    {
        case CHAN0_IDX:
            FTM_RMW_PAIR0DEADTIME(ftmBase, FTM_PAIR0DEADTIME_DTPS_MASK, FTM_PAIR0DEADTIME_DTPS((uint8_t)divider));
            break;
        case CHAN1_IDX:
            FTM_RMW_PAIR1DEADTIME(ftmBase, FTM_PAIR1DEADTIME_DTPS_MASK, FTM_PAIR1DEADTIME_DTPS((uint8_t)divider));
            break;
        case CHAN2_IDX:
            FTM_RMW_PAIR2DEADTIME(ftmBase, FTM_PAIR2DEADTIME_DTPS_MASK, FTM_PAIR2DEADTIME_DTPS((uint8_t)divider));
            break;
        case CHAN3_IDX:
            FTM_RMW_PAIR3DEADTIME(ftmBase, FTM_PAIR3DEADTIME_DTPS_MASK, FTM_PAIR3DEADTIME_DTPS((uint8_t)divider));
            break;
        default:
            break;
    }
}

static inline void FTM_DRV_SetPairDeadtimeCount(FTM_Type * const ftmBase,
                                                uint8_t channelPair,
                                                uint8_t count)
{
    DEV_ASSERT(channelPair < CHAN4_IDX);
    DEV_ASSERT(count < 64U);

    switch (channelPair)
    {
        case CHAN0_IDX:
            FTM_RMW_PAIR0DEADTIME(ftmBase, FTM_PAIR0DEADTIME_DTVAL_MASK, FTM_PAIR0DEADTIME_DTVAL(count));
            break;
        case CHAN1_IDX:
            FTM_RMW_PAIR1DEADTIME(ftmBase, FTM_PAIR1DEADTIME_DTVAL_MASK, FTM_PAIR1DEADTIME_DTVAL(count));
            break;
        case CHAN2_IDX:
            FTM_RMW_PAIR2DEADTIME(ftmBase, FTM_PAIR2DEADTIME_DTVAL_MASK, FTM_PAIR2DEADTIME_DTVAL(count));
            break;
        case CHAN3_IDX:
            FTM_RMW_PAIR3DEADTIME(ftmBase, FTM_PAIR3DEADTIME_DTVAL_MASK, FTM_PAIR3DEADTIME_DTVAL(count));
            break;
        default:
            break;
    }
}

#if FEATURE_FTM_HAS_SUPPORTED_DITHERING
static inline void FTM_DRV_SetMirrorMod(FTM_Type * const ftmBase,
                                        uint16_t value)
{
    FTM_RMW_MOD_MIRROR(ftmBase, FTM_MOD_MIRROR_MOD_MASK, FTM_MOD_MIRROR_MOD(value));
}

static inline uint16_t FTM_DRV_GetMirrorMod(const FTM_Type * ftmBase)
{
    return (uint16_t)((((ftmBase)->MOD_MIRROR) & FTM_MOD_MIRROR_MOD_MASK) >> FTM_MOD_MIRROR_MOD_SHIFT);
}

static inline uint8_t FTM_DRV_GetModFracVal(const FTM_Type * ftmBase)
{
    return (uint8_t)((((ftmBase)->MOD_MIRROR) & FTM_MOD_MIRROR_FRACMOD_MASK) >> FTM_MOD_MIRROR_FRACMOD_SHIFT);
}

static inline void FTM_DRV_SetMirrorChnMatchVal(FTM_Type * const ftmBase,
                                                uint8_t channel,
                                                uint16_t value)
{
    FTM_RMW_CnV_MIRROR(ftmBase, channel, FTM_CV_MIRROR_VAL_MASK, FTM_CV_MIRROR_VAL(value));
}

static inline uint16_t FTM_DRV_GetMirrorChnMatchVal(const FTM_Type * ftmBase,
                                                    uint8_t channel)
{
    return (uint16_t)((((ftmBase)->CV_MIRROR[channel]) & FTM_CV_MIRROR_VAL_MASK) >> FTM_CV_MIRROR_VAL_SHIFT);
}

static inline uint8_t FTM_DRV_GetChnMatchFracVal(const FTM_Type * ftmBase,
                                                 uint8_t channel)
{
    return (uint8_t)((((ftmBase)->CV_MIRROR[channel]) & FTM_CV_MIRROR_FRACVAL_MASK) >> FTM_CV_MIRROR_FRACVAL_SHIFT);
}
#endif

status_t FTM_DRV_Init(uint32_t instance,
                      const ftm_user_config_t * info,
                      ftm_state_t * state);

status_t FTM_DRV_Deinit(uint32_t instance);

void FTM_DRV_GetDefaultConfig(ftm_user_config_t * const config);

status_t FTM_DRV_MaskOutputChannels(uint32_t instance,
                                    uint32_t channelsMask,
                                    bool softwareTrigger);


status_t FTM_DRV_SetInitialCounterValue(uint32_t instance,
                                        uint16_t counterValue,
                                        bool softwareTrigger);

status_t FTM_DRV_SetHalfCycleReloadPoint(uint32_t instance,
                                         uint16_t reloadPoint,
                                         bool softwareTrigger);

status_t FTM_DRV_SetSoftOutChnValue(uint32_t instance,
                                    uint8_t channelsValues,
                                    bool softwareTrigger);

status_t FTM_DRV_SetSoftwareOutputChannelControl(uint32_t instance,
                                                 uint8_t channelsMask,
                                                 bool softwareTrigger);

status_t FTM_DRV_SetAllChnSoftwareOutputControl(uint32_t instance,
                                                uint8_t channelMask,
                                                uint8_t channelValueMask,
                                                bool softwareTrigger);

status_t FTM_DRV_SetInvertingControl(uint32_t instance,
                                     uint8_t channelsPairMask,
                                     bool softwareTrigger);

status_t FTM_DRV_SetModuloCounterValue(uint32_t instance,
                                       uint16_t counterValue,
                                       bool softwareTrigger);

status_t FTM_DRV_SetOutputlevel(uint32_t instance,
                                uint8_t channel,
                                uint8_t level);

status_t FTM_DRV_SetSync(uint32_t instance,
                         const ftm_pwm_sync_t * param);

status_t FTM_DRV_GenerateHardwareTrigger(uint32_t instance);

status_t FTM_DRV_EnableInterrupts(uint32_t instance,
                                  uint32_t interruptMask);

void FTM_DRV_DisableInterrupts(uint32_t instance,
                               uint32_t interruptMask);

uint32_t FTM_DRV_GetEnabledInterrupts(uint32_t instance);

uint32_t FTM_DRV_GetStatusFlags(uint32_t instance);

void FTM_DRV_ClearStatusFlags(uint32_t instance,
                              uint32_t flagMask);

uint32_t FTM_DRV_GetFrequency(uint32_t instance);

uint16_t FTM_DRV_ConvertFreqToPeriodTicks(uint32_t instance,
                                          uint32_t freqencyHz);

status_t FTM_DRV_CounterReset(uint32_t instance,
                              bool softwareTrigger);

#if defined(__cplusplus)
}
#endif



#endif 

