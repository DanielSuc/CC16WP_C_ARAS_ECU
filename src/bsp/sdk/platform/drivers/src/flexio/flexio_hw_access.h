
#ifndef FLEXIO_HW_ACCESS_H
#define FLEXIO_HW_ACCESS_H

#include <stdbool.h>
#include "device_registers.h"



typedef enum
{
    FLEXIO_TIMER_POLARITY_POSEDGE = 0x00U,     
    FLEXIO_TIMER_POLARITY_NEGEDGE = 0x01U,     
} flexio_timer_polarity_t;

typedef enum
{
    FLEXIO_PIN_POLARITY_HIGH = 0x00U,          
    FLEXIO_PIN_POLARITY_LOW  = 0x01U,          
} flexio_pin_polarity_t;

typedef enum
{
    FLEXIO_PIN_CONFIG_DISABLED     = 0x00U,    
    FLEXIO_PIN_CONFIG_OPEN_DRAIN   = 0x01U,    
    FLEXIO_PIN_CONFIG_BIDIR_OUTPUT = 0x02U,    
    FLEXIO_PIN_CONFIG_OUTPUT       = 0x03U,    
} flexio_pin_config_t;

typedef enum
{
    FLEXIO_SHIFTER_MODE_DISABLED          = 0x00U,  
    FLEXIO_SHIFTER_MODE_RECEIVE           = 0x01U,  
    FLEXIO_SHIFTER_MODE_TRANSMIT          = 0x02U,  
    FLEXIO_SHIFTER_MODE_MATCH_STORE       = 0x04U,  
    FLEXIO_SHIFTER_MODE_MATCH_CONTINUOUS  = 0x05U,  
} flexio_shifter_mode_t;

typedef enum
{
    FLEXIO_SHIFTER_SOURCE_PIN        = 0x00U,  
    FLEXIO_SHIFTER_SOURCE_SHIFTER    = 0x01U,  
} flexio_shifter_source_t;

typedef enum
{
    FLEXIO_SHIFTER_RW_MODE_NORMAL    = 0x00U,  
    FLEXIO_SHIFTER_RW_MODE_BIT_SWAP  = 0x01U,  
} flexio_shifter_buffer_mode_t;

typedef enum
{
    FLEXIO_TRIGGER_POLARITY_HIGH = 0x00U,          
    FLEXIO_TRIGGER_POLARITY_LOW  = 0x01U,          
} flexio_trigger_polarity_t;

typedef enum
{
    FLEXIO_TRIGGER_SOURCE_EXTERNAL  = 0x00U,  
    FLEXIO_TRIGGER_SOURCE_INTERNAL  = 0x01U,  
} flexio_trigger_source_t;

typedef enum
{
    FLEXIO_TIMER_MODE_DISABLED    = 0x00U,  
    FLEXIO_TIMER_MODE_8BIT_BAUD   = 0x01U,  
    FLEXIO_TIMER_MODE_8BIT_PWM    = 0x02U,  
    FLEXIO_TIMER_MODE_16BIT       = 0x03U,  
} flexio_timer_mode_t;

typedef enum
{
    FLEXIO_TIMER_INITOUT_ONE          = 0x00U,  
    FLEXIO_TIMER_INITOUT_ZERO         = 0x01U,  
    FLEXIO_TIMER_INITOUT_ONE_RESET    = 0x02U,  
    FLEXIO_TIMER_INITOUT_ZERO_RESET   = 0x03U,  
} flexio_timer_output_t;

typedef enum
{
    FLEXIO_TIMER_DECREMENT_CLK_SHIFT_TMR      = 0x00U,  
    FLEXIO_TIMER_DECREMENT_TRG_SHIFT_TMR      = 0x01U,  
    FLEXIO_TIMER_DECREMENT_PIN_SHIFT_PIN      = 0x02U,  
    FLEXIO_TIMER_DECREMENT_TRG_SHIFT_TRG      = 0x03U,  
} flexio_timer_decrement_t;

typedef enum
{
    FLEXIO_TIMER_RESET_NEVER                  = 0x00U,  
    FLEXIO_TIMER_RESET_PIN_OUT                = 0x02U,  
    FLEXIO_TIMER_RESET_TRG_OUT                = 0x03U,  
    FLEXIO_TIMER_RESET_PIN_RISING             = 0x04U,  
    FLEXIO_TIMER_RESET_TRG_RISING             = 0x06U,  
    FLEXIO_TIMER_RESET_TRG_BOTH               = 0x07U,  
} flexio_timer_reset_t;

typedef enum
{
    FLEXIO_TIMER_DISABLE_NEVER                = 0x00U,  
    FLEXIO_TIMER_DISABLE_TIM_DISABLE          = 0x01U,  
    FLEXIO_TIMER_DISABLE_TIM_CMP              = 0x02U,  
    FLEXIO_TIMER_DISABLE_TIM_CMP_TRG_LOW      = 0x03U,  
    FLEXIO_TIMER_DISABLE_PIN                  = 0x04U,  
    FLEXIO_TIMER_DISABLE_PIN_TRG_HIGH         = 0x05U,  
    FLEXIO_TIMER_DISABLE_TRG                  = 0x06U,  
} flexio_timer_disable_t;

typedef enum
{
    FLEXIO_TIMER_ENABLE_ALWAYS                  = 0x00U,  
    FLEXIO_TIMER_ENABLE_TIM_ENABLE              = 0x01U,  
    FLEXIO_TIMER_ENABLE_TRG_HIGH                = 0x02U,  
    FLEXIO_TIMER_ENABLE_TRG_PIN_HIGH            = 0x03U,  
    FLEXIO_TIMER_ENABLE_PIN_POSEDGE             = 0x04U,  
    FLEXIO_TIMER_ENABLE_PIN_POSEDGE_TRG_HIGH    = 0x05U,  
    FLEXIO_TIMER_ENABLE_TRG_POSEDGE             = 0x06U,  
    FLEXIO_TIMER_ENABLE_TRG_EDGE                = 0x07U,  
} flexio_timer_enable_t;

typedef enum
{
    FLEXIO_TIMER_STOP_BIT_DISABLED              = 0x00U,  
    FLEXIO_TIMER_STOP_BIT_TIM_CMP               = 0x01U,  
    FLEXIO_TIMER_STOP_BIT_TIM_DIS               = 0x02U,  
    FLEXIO_TIMER_STOP_BIT_TIM_CMP_DIS           = 0x03U,  
} flexio_timer_stop_t;

typedef enum
{
    FLEXIO_SHIFTER_STOP_BIT_DISABLED            = 0x00U,  
    FLEXIO_SHIFTER_STOP_BIT_0                   = 0x02U,  
    FLEXIO_SHIFTER_STOP_BIT_1                   = 0x03U,  
} flexio_shifter_stop_t;

typedef enum
{
    FLEXIO_SHIFTER_START_BIT_DISABLED       = 0x00U,  
    FLEXIO_SHIFTER_START_BIT_DISABLED_SH    = 0x01U,  
    FLEXIO_SHIFTER_START_BIT_0              = 0x02U,  
    FLEXIO_SHIFTER_START_BIT_1              = 0x03U,  
} flexio_shifter_start_t;

typedef enum
{
    FLEXIO_TIMER_START_BIT_DISABLED              = 0x00U,  
    FLEXIO_TIMER_START_BIT_ENABLED               = 0x01U,  
} flexio_timer_start_t;



#if defined(__cplusplus)
extern "C" {
#endif


static inline uint8_t FLEXIO_GetShifterNum(const FLEXIO_Type *baseAddr)
{
    uint32_t tmp = baseAddr->PARAM;
    tmp = (tmp & FLEXIO_PARAM_SHIFTER_MASK) >> FLEXIO_PARAM_SHIFTER_SHIFT;
    return (uint8_t)tmp;
}


static inline void FLEXIO_SetDebugMode(FLEXIO_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->CTRL;
    regValue &= (uint32_t)(~(FLEXIO_CTRL_DBGE_MASK));
    regValue |= FLEXIO_CTRL_DBGE(enable);
    baseAddr->CTRL = (uint32_t)regValue;
}


static inline void FLEXIO_SetSoftwareReset(FLEXIO_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->CTRL;
    regValue &= (uint32_t)(~(FLEXIO_CTRL_SWRST_MASK));
    regValue |= FLEXIO_CTRL_SWRST(enable);
    baseAddr->CTRL = (uint32_t)regValue;
}


static inline void FLEXIO_SetEnable(FLEXIO_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t)baseAddr->CTRL;
    regValue &= (uint32_t)(~(FLEXIO_CTRL_FLEXEN_MASK));
    regValue |= FLEXIO_CTRL_FLEXEN(enable);
    baseAddr->CTRL = (uint32_t)regValue;
}


static inline uint8_t FLEXIO_GetPinData(const FLEXIO_Type *baseAddr)
{
    uint32_t tmp = baseAddr->PIN;
    tmp = (tmp & FLEXIO_PIN_PDI_MASK) >> FLEXIO_PIN_PDI_SHIFT;
    return (uint8_t)tmp;
}


static inline bool FLEXIO_GetShifterStatus(const FLEXIO_Type *baseAddr, uint8_t shifter)
{
    uint32_t regValue = (uint32_t)baseAddr->SHIFTSTAT;
    regValue = (regValue >> shifter) & 1U;
    return (bool)regValue;
}


static inline uint32_t FLEXIO_GetAllShifterStatus(const FLEXIO_Type *baseAddr)
{
    return baseAddr->SHIFTSTAT;
}


static inline void FLEXIO_ClearShifterStatus(FLEXIO_Type *baseAddr, uint8_t shifter)
{
    baseAddr->SHIFTSTAT = 1UL << shifter;
}


static inline bool FLEXIO_GetShifterErrorStatus(const FLEXIO_Type *baseAddr, uint8_t shifter)
{
    uint32_t regValue = (uint32_t)baseAddr->SHIFTERR;
    regValue = (regValue >> shifter) & 1U;
    return (bool)regValue;
}


static inline uint32_t FLEXIO_GetAllShifterErrorStatus(const FLEXIO_Type *baseAddr)
{
    return baseAddr->SHIFTERR;
}


static inline void FLEXIO_ClearShifterErrorStatus(FLEXIO_Type *baseAddr, uint8_t shifter)
{
    baseAddr->SHIFTERR = 1UL << shifter;
}


static inline bool FLEXIO_GetTimerStatus(const FLEXIO_Type *baseAddr, uint8_t timer)
{
    uint32_t regValue = (uint32_t)baseAddr->TIMSTAT;
    regValue = (regValue >> timer) & 1U;
    return (bool)regValue;
}


static inline uint32_t FLEXIO_GetAllTimerStatus(const FLEXIO_Type *baseAddr)
{
    return baseAddr->TIMSTAT;
}


static inline void FLEXIO_ClearTimerStatus(FLEXIO_Type *baseAddr, uint8_t timer)
{
    baseAddr->TIMSTAT = 1UL << timer;
}


static inline uint32_t FLEXIO_GetAllShifterInterrupt(const FLEXIO_Type *baseAddr)
{
    return baseAddr->SHIFTSIEN;
}


static inline void FLEXIO_SetShifterInterrupt(FLEXIO_Type *baseAddr, uint8_t interruptMask, bool enable)
{
    uint32_t tmp;

    tmp = baseAddr->SHIFTSIEN;

    if (enable == true)
    {
        tmp |= interruptMask;
    }
    else
    {
        tmp &= ~interruptMask;
    }
    baseAddr->SHIFTSIEN = tmp;
}



static inline uint32_t FLEXIO_GetAllShifterErrorInterrupt(const FLEXIO_Type *baseAddr)
{
    return baseAddr->SHIFTEIEN;
}


static inline void FLEXIO_SetShifterErrorInterrupt(FLEXIO_Type *baseAddr, uint8_t interruptMask, bool enable)
{
    uint32_t tmp;

    tmp = baseAddr->SHIFTEIEN;

    if (enable == true)
    {
        tmp |= interruptMask;
    }
    else
    {
        tmp &= ~interruptMask;
    }
    baseAddr->SHIFTEIEN = tmp;
}


static inline uint32_t FLEXIO_GetAllTimerInterrupt(const FLEXIO_Type *baseAddr)
{
    return baseAddr->TIMIEN;
}


static inline void FLEXIO_SetTimerInterrupt(FLEXIO_Type *baseAddr, uint8_t interruptMask, bool enable)
{
    uint32_t tmp;

    tmp = baseAddr->TIMIEN;

    if (enable == true)
    {
        tmp |= interruptMask;
    }
    else
    {
        tmp &= ~interruptMask;
    }
    baseAddr->TIMIEN = tmp;
}


static inline void FLEXIO_SetShifterDMARequest(FLEXIO_Type *baseAddr, uint8_t requestMask, bool enable)
{
    uint32_t tmp;

    tmp = baseAddr->SHIFTSDEN;

    if (enable == true)
    {
        tmp |= requestMask;
    }
    else
    {
        tmp &= ~requestMask;
    }
    baseAddr->SHIFTSDEN = tmp;
}


static inline void FLEXIO_SetShifterTimer(FLEXIO_Type *baseAddr,
                                              uint8_t shifter,
                                              uint8_t timer,
                                              flexio_timer_polarity_t polarity)
{
    uint32_t tmp = baseAddr->SHIFTCTL[shifter];
    tmp &= ~(FLEXIO_SHIFTCTL_TIMSEL_MASK);
    tmp |= FLEXIO_SHIFTCTL_TIMSEL(timer);
    tmp &= ~(FLEXIO_SHIFTCTL_TIMPOL_MASK);
    tmp |= FLEXIO_SHIFTCTL_TIMPOL(polarity);
    baseAddr->SHIFTCTL[shifter] = tmp;
}


static inline void FLEXIO_SetShifterPin(FLEXIO_Type *baseAddr,
                                            uint8_t shifter,
                                            uint8_t pin,
                                            flexio_pin_polarity_t polarity,
                                            flexio_pin_config_t config)
{
    uint32_t tmp = baseAddr->SHIFTCTL[shifter];
    tmp &= ~(FLEXIO_SHIFTCTL_PINSEL_MASK);
    tmp |= FLEXIO_SHIFTCTL_PINSEL(pin);
    tmp &= ~(FLEXIO_SHIFTCTL_PINPOL_MASK);
    tmp |= FLEXIO_SHIFTCTL_PINPOL(polarity);
    tmp &= ~(FLEXIO_SHIFTCTL_PINCFG_MASK);
    tmp |= FLEXIO_SHIFTCTL_PINCFG(config);
    baseAddr->SHIFTCTL[shifter] = tmp;
}


static inline void FLEXIO_SetShifterPinConfig(FLEXIO_Type *baseAddr,
                                                  uint8_t shifter,
                                                  flexio_pin_config_t config)
{
    uint32_t tmp = baseAddr->SHIFTCTL[shifter];
    tmp &= ~(FLEXIO_SHIFTCTL_PINCFG_MASK);
    tmp |= FLEXIO_SHIFTCTL_PINCFG(config);
    baseAddr->SHIFTCTL[shifter] = tmp;
}


static inline void FLEXIO_SetShifterMode(FLEXIO_Type *baseAddr,
                                             uint8_t shifter,
                                             flexio_shifter_mode_t mode)
{
    uint32_t tmp = baseAddr->SHIFTCTL[shifter];
    tmp &= ~(FLEXIO_SHIFTCTL_SMOD_MASK);
    tmp |= FLEXIO_SHIFTCTL_SMOD(mode);
    baseAddr->SHIFTCTL[shifter] = tmp;
}


static inline void FLEXIO_SetShifterControl(FLEXIO_Type *baseAddr,
                                                uint8_t shifter,
                                                flexio_shifter_mode_t mode,
                                                uint8_t pin,
                                                flexio_pin_polarity_t pinPolarity,
                                                flexio_pin_config_t pinConfig,
                                                uint8_t timer,
                                                flexio_timer_polarity_t timerPolarity)
{
    baseAddr->SHIFTCTL[shifter] = FLEXIO_SHIFTCTL_SMOD(mode)
                                | FLEXIO_SHIFTCTL_PINPOL(pinPolarity)
                                | FLEXIO_SHIFTCTL_PINSEL(pin)
                                | FLEXIO_SHIFTCTL_PINCFG(pinConfig)
                                | FLEXIO_SHIFTCTL_TIMPOL(timerPolarity)
                                | FLEXIO_SHIFTCTL_TIMSEL(timer);
}


static inline void FLEXIO_SetShifterInputSource(FLEXIO_Type *baseAddr,
                                                    uint8_t shifter,
                                                    flexio_shifter_source_t source)
{
    uint32_t tmp;
    tmp = baseAddr->SHIFTCFG[shifter];
    tmp &= ~(FLEXIO_SHIFTCFG_INSRC_MASK);
    tmp |= FLEXIO_SHIFTCFG_INSRC(source);
    baseAddr->SHIFTCFG[shifter] = tmp;
}


static inline void FLEXIO_SetShifterStopBit(FLEXIO_Type *baseAddr, uint8_t shifter, flexio_shifter_stop_t stop)
{
    uint32_t tmp;
    tmp = baseAddr->SHIFTCFG[shifter];
    tmp &= ~(FLEXIO_SHIFTCFG_SSTOP_MASK);
    tmp |= FLEXIO_SHIFTCFG_SSTOP(stop);
    baseAddr->SHIFTCFG[shifter] = tmp;
}


static inline void FLEXIO_SetShifterStartBit(FLEXIO_Type *baseAddr,
                                                 uint8_t shifter,
                                                 flexio_shifter_start_t start)
{
    uint32_t tmp;
    tmp = baseAddr->SHIFTCFG[shifter];
    tmp &= ~(FLEXIO_SHIFTCFG_SSTART_MASK);
    tmp |= FLEXIO_SHIFTCFG_SSTART(start);
    baseAddr->SHIFTCFG[shifter] = tmp;
}


static inline void FLEXIO_SetShifterConfig(FLEXIO_Type *baseAddr,
                                               uint8_t shifter,
                                               flexio_shifter_start_t start,
                                               flexio_shifter_stop_t stop,
                                               flexio_shifter_source_t source)
{
    baseAddr->SHIFTCFG[shifter] = FLEXIO_SHIFTCFG_SSTART(start)
                                | FLEXIO_SHIFTCFG_SSTOP(stop)
                                | FLEXIO_SHIFTCFG_INSRC(source);
}


static inline uint32_t FLEXIO_ReadShifterBuffer(const FLEXIO_Type *baseAddr,
                                                    uint8_t shifter,
                                                    flexio_shifter_buffer_mode_t mode)
{
    uint32_t data;

    switch (mode)
    {
        case FLEXIO_SHIFTER_RW_MODE_NORMAL:
            data = baseAddr->SHIFTBUF[shifter];
            break;
        case FLEXIO_SHIFTER_RW_MODE_BIT_SWAP:
            data = baseAddr->SHIFTBUFBIS[shifter];
            break;
        default:
            data = 0U;
            break;
    }
    return data;
}


static inline void FLEXIO_WriteShifterBuffer(FLEXIO_Type *baseAddr,
                                                 uint8_t shifter,
                                                 uint32_t value,
                                                 flexio_shifter_buffer_mode_t mode)
{
    switch (mode)
    {
        case FLEXIO_SHIFTER_RW_MODE_NORMAL:
            baseAddr->SHIFTBUF[shifter] = value;
            break;
        case FLEXIO_SHIFTER_RW_MODE_BIT_SWAP:
            baseAddr->SHIFTBUFBIS[shifter] = value;
            break;
        default:
            break;
    }
}


static inline void FLEXIO_SetTimerTrigger(FLEXIO_Type *baseAddr,
                                                 uint8_t timer,
                                                 uint8_t trigger,
                                                 flexio_trigger_polarity_t polarity,
                                                 flexio_trigger_source_t source)
{
    uint32_t tmp = baseAddr->TIMCTL[timer];
    tmp &= ~(FLEXIO_TIMCTL_TRGSEL_MASK);
    tmp |= FLEXIO_TIMCTL_TRGSEL(trigger);
    tmp &= ~(FLEXIO_TIMCTL_TRGPOL_MASK);
    tmp |= FLEXIO_TIMCTL_TRGPOL(polarity);
    tmp &= ~(FLEXIO_TIMCTL_TRGSRC_MASK);
    tmp |= FLEXIO_TIMCTL_TRGSRC(source);
    baseAddr->TIMCTL[timer] = tmp;
}


static inline void FLEXIO_SetTimerPin(FLEXIO_Type *baseAddr,
                                                 uint8_t timer,
                                                 uint8_t pin,
                                                 flexio_pin_polarity_t polarity,
                                                 flexio_pin_config_t config)
{
    uint32_t tmp = baseAddr->TIMCTL[timer];
    tmp &= ~(FLEXIO_TIMCTL_PINSEL_MASK);
    tmp |= FLEXIO_TIMCTL_PINSEL(pin);
    tmp &= ~(FLEXIO_TIMCTL_PINPOL_MASK);
    tmp |= FLEXIO_TIMCTL_PINPOL(polarity);
    tmp &= ~(FLEXIO_TIMCTL_PINCFG_MASK);
    tmp |= FLEXIO_TIMCTL_PINCFG(config);
    baseAddr->TIMCTL[timer] = tmp;
}


static inline void FLEXIO_SetTimerMode(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_mode_t mode)
{
    uint32_t tmp = baseAddr->TIMCTL[timer];
    tmp &= ~(FLEXIO_TIMCTL_TIMOD_MASK);
    tmp |= FLEXIO_TIMCTL_TIMOD(mode);
    baseAddr->TIMCTL[timer] = tmp;
}


static inline void FLEXIO_SetTimerControl(FLEXIO_Type *baseAddr,
                                              uint8_t timer,
                                              uint8_t trigger,
                                              flexio_trigger_polarity_t triggerPolarity,
                                              flexio_trigger_source_t triggerSource,
                                              uint8_t pin,
                                              flexio_pin_polarity_t pinPolarity,
                                              flexio_pin_config_t pinConfig,
                                              flexio_timer_mode_t mode)
{
    baseAddr->TIMCTL[timer] = FLEXIO_TIMCTL_TIMOD(mode)
                            | FLEXIO_TIMCTL_PINSEL(pin)
                            | FLEXIO_TIMCTL_PINPOL(pinPolarity)
                            | FLEXIO_TIMCTL_PINCFG(pinConfig)
                            | FLEXIO_TIMCTL_TRGSRC(triggerSource)
                            | FLEXIO_TIMCTL_TRGPOL(triggerPolarity)
                            | FLEXIO_TIMCTL_TRGSEL(trigger);
}


static inline void FLEXIO_SetTimerInitialOutput(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_output_t output)
{
    uint32_t tmp = baseAddr->TIMCFG[timer];
    tmp &= ~(FLEXIO_TIMCFG_TIMOUT_MASK);
    tmp |= FLEXIO_TIMCFG_TIMOUT(output);
    baseAddr->TIMCFG[timer] = tmp;
}


static inline void FLEXIO_SetTimerDecrement(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_decrement_t decrement)
{
    uint32_t tmp = baseAddr->TIMCFG[timer];
    tmp &= ~(FLEXIO_TIMCFG_TIMDEC_MASK);
    tmp |= FLEXIO_TIMCFG_TIMDEC(decrement);
    baseAddr->TIMCFG[timer] = tmp;
}


static inline void FLEXIO_SetTimerReset(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_reset_t reset)
{
    uint32_t tmp = baseAddr->TIMCFG[timer];
    tmp &= ~(FLEXIO_TIMCFG_TIMRST_MASK);
    tmp |= FLEXIO_TIMCFG_TIMRST(reset);
    baseAddr->TIMCFG[timer] = tmp;
}


static inline void FLEXIO_SetTimerDisable(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_disable_t disable)
{
    uint32_t tmp = baseAddr->TIMCFG[timer];
    tmp &= ~(FLEXIO_TIMCFG_TIMDIS_MASK);
    tmp |= FLEXIO_TIMCFG_TIMDIS(disable);
    baseAddr->TIMCFG[timer] = tmp;
}


static inline void FLEXIO_SetTimerEnable(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_enable_t enable)
{
    uint32_t tmp = baseAddr->TIMCFG[timer];
    tmp &= ~(FLEXIO_TIMCFG_TIMENA_MASK);
    tmp |= FLEXIO_TIMCFG_TIMENA(enable);
    baseAddr->TIMCFG[timer] = tmp;
}


static inline void FLEXIO_SetTimerStop(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_stop_t stop)
{
    uint32_t tmp = baseAddr->TIMCFG[timer];
    tmp &= ~(FLEXIO_TIMCFG_TSTOP_MASK);
    tmp |= FLEXIO_TIMCFG_TSTOP(stop);
    baseAddr->TIMCFG[timer] = tmp;
}


static inline void FLEXIO_SetTimerStart(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_start_t start)
{
    uint32_t regValue = (uint32_t)baseAddr->TIMCFG[timer];
    regValue &= (uint32_t)(~(FLEXIO_TIMCFG_TSTART_MASK));
    regValue |= FLEXIO_TIMCFG_TSTART(start);
    baseAddr->TIMCFG[timer] = (uint32_t)regValue;
}


static inline void FLEXIO_SetTimerConfig(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             flexio_timer_start_t start,
                                             flexio_timer_stop_t stop,
                                             flexio_timer_enable_t enable,
                                             flexio_timer_disable_t disable,
                                             flexio_timer_reset_t reset,
                                             flexio_timer_decrement_t decrement,
                                             flexio_timer_output_t output)
{

    baseAddr->TIMCFG[timer] = FLEXIO_TIMCFG_TSTART(start)
                            | FLEXIO_TIMCFG_TSTOP(stop)
                            | FLEXIO_TIMCFG_TIMENA(enable)
                            | FLEXIO_TIMCFG_TIMDIS(disable)
                            | FLEXIO_TIMCFG_TIMRST(reset)
                            | FLEXIO_TIMCFG_TIMDEC(decrement)
                            | FLEXIO_TIMCFG_TIMOUT(output);
}


static inline uint16_t FLEXIO_GetTimerCompare(const FLEXIO_Type *baseAddr, uint8_t timer)
{
    return (uint16_t)(baseAddr->TIMCMP[timer]);
}


static inline void FLEXIO_SetTimerCompare(FLEXIO_Type *baseAddr,
                                             uint8_t timer,
                                             uint16_t value)
{
    baseAddr->TIMCMP[timer] = (uint32_t)value;
}


static inline void FLEXIO_Init(FLEXIO_Type *baseAddr)
{
    FLEXIO_SetSoftwareReset(baseAddr, true);
    baseAddr->CTRL = 0x0U;
}

#if defined(__cplusplus)
}
#endif

#endif 

