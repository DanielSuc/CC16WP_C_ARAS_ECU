
#ifndef LPIT_HW_ACCESS_H
#define LPIT_HW_ACCESS_H

#include <stdbool.h>
#include "device_registers.h"
#include "lpit_driver.h"



#if defined(__cplusplus)
extern "C" {
#endif

static inline void LPIT_Enable(LPIT_Type * const base, volatile uint32_t delay)
{
    base->MCR |= LPIT_MCR_M_CEN_MASK;
    while(delay != 0u)
    {
        delay--;
        NOP();
        NOP();
        NOP();
    }
}

static inline void LPIT_Disable(LPIT_Type * const base)
{
    base->MCR &= ~LPIT_MCR_M_CEN_MASK;
}

static inline void LPIT_Reset(LPIT_Type * const base, volatile uint32_t delay)
{
    base->MCR |= LPIT_MCR_SW_RST_MASK;
    while(delay != 0u)
    {
        delay--;
        NOP();
        NOP();
        NOP();
    }
    base->MCR &= ~LPIT_MCR_SW_RST_MASK;
}

static inline void LPIT_StartTimerChannels(LPIT_Type * const base,
                                           uint32_t mask)
{
    base->SETTEN |= mask;
}

static inline void LPIT_StopTimerChannels(LPIT_Type * const base,
                                          uint32_t mask)
{
    base->CLRTEN |= mask;
}

static inline void LPIT_SetTimerPeriodByCount(LPIT_Type * const base,
                                              uint32_t channel,
                                              uint32_t count)
{
    base->TMR[channel].TVAL = count;
}

static inline uint32_t LPIT_GetTimerPeriodByCount(const LPIT_Type * base,
                                                  uint32_t channel)
{
    return (base->TMR[channel].TVAL);
}

static inline uint32_t LPIT_GetCurrentTimerCount(const LPIT_Type * base,
                                                 uint32_t channel)
{
    return (base->TMR[channel].CVAL);
}

static inline void LPIT_EnableInterruptTimerChannels(LPIT_Type * const base,
                                                     uint32_t mask)
{
    base->MIER |= mask;
}

static inline void LPIT_DisableInterruptTimerChannels(LPIT_Type * const base,
                                                      uint32_t mask)
{
    base->MIER &= ~mask;
}

static inline uint32_t LPIT_GetInterruptFlagTimerChannels(const LPIT_Type * base,
                                                          uint32_t mask)
{
    return (base->MSR) & mask;
}

static inline void LPIT_ClearInterruptFlagTimerChannels(LPIT_Type * const base,
                                                        uint32_t mask)
{
    base->MSR = mask;
#ifdef ERRATA_E9005
    base->MSR;
#endif
}

static inline void LPIT_SetTimerChannelModeCmd(LPIT_Type * const base,
                                               uint32_t channel,
                                               lpit_timer_modes_t mode)
{
    base->TMR[channel].TCTRL &= ~LPIT_TMR_TCTRL_MODE_MASK;
    base->TMR[channel].TCTRL |=  LPIT_TMR_TCTRL_MODE(mode);
}

static inline lpit_timer_modes_t LPIT_GetTimerChannelModeCmd(const LPIT_Type * base,
                                                             uint32_t channel)
{
    uint32_t tmp;
    lpit_timer_modes_t mode;

    tmp = (((base->TMR[channel].TCTRL) & LPIT_TMR_TCTRL_MODE_MASK)
                                 >> LPIT_TMR_TCTRL_MODE_SHIFT);
    switch (tmp)
    {
        case 0x00U:
            mode = LPIT_PERIODIC_COUNTER;
            break;
        case 0x01U:
            mode = LPIT_DUAL_PERIODIC_COUNTER;
            break;
        case 0x02U:
            mode = LPIT_TRIGGER_ACCUMULATOR;
            break;
        case 0x03U:
            mode = LPIT_INPUT_CAPTURE;
            break;
        default:
            mode = LPIT_PERIODIC_COUNTER;
            break;
    }
    return mode;
}

static inline void LPIT_SetTriggerSelectCmd(LPIT_Type * const base,
                                            uint32_t channel,
                                            uint32_t triggerChannelSelect)
{
    base->TMR[channel].TCTRL &= ~LPIT_TMR_TCTRL_TRG_SEL_MASK;
    base->TMR[channel].TCTRL |=  LPIT_TMR_TCTRL_TRG_SEL(triggerChannelSelect);
}

static inline void LPIT_SetTriggerSourceCmd(LPIT_Type * const base,
                                            uint32_t channel,
                                            lpit_trigger_source_t triggerSource)
{
    base->TMR[channel].TCTRL &= ~LPIT_TMR_TCTRL_TRG_SRC_MASK;
    base->TMR[channel].TCTRL |=  LPIT_TMR_TCTRL_TRG_SRC(triggerSource);
}

static inline void LPIT_SetReloadOnTriggerCmd(LPIT_Type * const base,
                                              uint32_t channel,
                                              bool isReloadOnTrigger)
{
    base->TMR[channel].TCTRL &= ~LPIT_TMR_TCTRL_TROT_MASK;
    base->TMR[channel].TCTRL |=  LPIT_TMR_TCTRL_TROT(isReloadOnTrigger ? 1UL : 0UL);
}

static inline void LPIT_SetStopOnInterruptCmd(LPIT_Type * const base,
                                              uint32_t channel,
                                              bool isStopOnInterrupt)
{
    base->TMR[channel].TCTRL &= ~LPIT_TMR_TCTRL_TSOI_MASK;
    base->TMR[channel].TCTRL |=  LPIT_TMR_TCTRL_TSOI(isStopOnInterrupt ? 1UL : 0UL);
}

static inline void LPIT_SetStartOnTriggerCmd(LPIT_Type * const base,
                                             uint32_t channel,
                                             bool isStartOnTrigger)
{
    base->TMR[channel].TCTRL &= ~LPIT_TMR_TCTRL_TSOT_MASK;
    base->TMR[channel].TCTRL |=  LPIT_TMR_TCTRL_TSOT(isStartOnTrigger ? 1UL : 0UL);
}

static inline void LPIT_SetTimerChannelChainCmd(LPIT_Type * const base,
                                                uint32_t channel,
                                                bool isChannelChained)
{
    base->TMR[channel].TCTRL &= ~LPIT_TMR_TCTRL_CHAIN_MASK;
    base->TMR[channel].TCTRL |=  LPIT_TMR_TCTRL_CHAIN(isChannelChained ? 1UL : 0UL);
}

static inline void LPIT_SetTimerRunInDebugCmd(LPIT_Type * const base,
                                              bool isRunInDebug)
{
    base->MCR &= ~LPIT_MCR_DBG_EN_MASK;
    base->MCR |= LPIT_MCR_DBG_EN(isRunInDebug ? 1UL: 0UL);
}

static inline void LPIT_SetTimerRunInDozeCmd(LPIT_Type * const base,
                                             bool isRunInDoze)
{
    base->MCR &= ~LPIT_MCR_DOZE_EN_MASK;
    base->MCR |= LPIT_MCR_DOZE_EN(isRunInDoze ? 1UL : 0UL);
}

#if defined(__cplusplus)
}
#endif

#endif 

