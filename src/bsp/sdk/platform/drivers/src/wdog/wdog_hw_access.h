

#ifndef WDOG_HW_ACCESS_H
#define WDOG_HW_ACCESS_H

#include <stddef.h>
#include "wdog_driver.h"



#define WDOG_UNLOCK32(base)  \
{ \
    (base)->CNT = FEATURE_WDOG_UNLOCK_VALUE; \
    (void)(base)->CNT; \
}

#define WDOG_UNLOCK16(base)  \
{ \
    (base)->CNT = FEATURE_WDOG_UNLOCK16_FIRST_VALUE; \
    (void)(base)->CNT; \
    (base)->CNT = FEATURE_WDOG_UNLOCK16_SECOND_VALUE; \
    (void)(base)->CNT; \
}

#define WDOG_UNLOCK(base)    \
{ \
    if (((base)->CS & WDOG_CS_CMD32EN_MASK) != 0U) \
    { \
        WDOG_UNLOCK32(base); \
    } \
    else \
    { \
        WDOG_UNLOCK16(base); \
    } \
}


#if defined(__cplusplus)
extern "C" {
#endif


void WDOG_Deinit(WDOG_Type * const base);

void WDOG_SetInt(WDOG_Type * const base,
                 bool enable);

status_t WDOG_Config(WDOG_Type * const base,
                     const wdog_user_config_t * wdogUserConfig);

wdog_user_config_t WDOG_GetConfig(const WDOG_Type * base);

static inline bool WDOG_IsEnabled(const WDOG_Type * base)
{
    return ((base->CS & WDOG_CS_EN_MASK) >> WDOG_CS_EN_SHIFT) != 0U;
}

static inline void WDOG_Trigger(WDOG_Type * const base)
{
    if ((base->CS & WDOG_CS_CMD32EN_MASK) != 0U)
    {
        base->CNT = FEATURE_WDOG_TRIGGER_VALUE;
    }
    else
    {
        base->CNT = FEATURE_WDOG_TRIGGER16_FIRST_VALUE;
        (void)base->CNT;
        base->CNT = FEATURE_WDOG_TRIGGER16_SECOND_VALUE;
    }
}

static inline void WDOG_SetWindowMode(WDOG_Type * const base,
                                      bool enable)
{
    WDOG_UNLOCK(base);

    base->CS = (base->CS & ~WDOG_CS_WIN_MASK) | WDOG_CS_WIN(enable ? 1UL : 0UL);
}

static inline void WDOG_SetWindowValue(WDOG_Type * const base,
                                       uint16_t window)
{
    WDOG_UNLOCK(base);

    base->WIN = window;
}

static inline void WDOG_ClearIntFlag(WDOG_Type * const base)
{
    WDOG_UNLOCK(base);

    base->CS = (base->CS & ~WDOG_CS_FLG_MASK) | WDOG_CS_FLG(1U);

#ifdef ERRATA_E9005
    (void)base->CS;
#endif
}

static inline wdog_clk_source_t WDOG_GetClockSource(const WDOG_Type * base)
{
    uint32_t cs = base->CS;
    wdog_clk_source_t getclocksource;

    switch((cs & WDOG_CS_CLK_MASK) >> WDOG_CS_CLK_SHIFT)
    {
    case 0U:
        getclocksource = WDOG_BUS_CLOCK;
        break;
    case 1U:
        getclocksource = WDOG_LPO_CLOCK;
        break;
    case 2U:
        getclocksource = WDOG_SOSC_CLOCK;
        break;
    case 3U:
        getclocksource = WDOG_SIRC_CLOCK;
        break;
    default:
        getclocksource = WDOG_BUS_CLOCK;
        break;
    }

    return getclocksource;
}

static inline bool WDOG_IsUpdateEnabled(const WDOG_Type * base)
{
    return ((base->CS & WDOG_CS_UPDATE_MASK) >> WDOG_CS_UPDATE_SHIFT) != 0U;
}

static inline void WDOG_SetDebug(WDOG_Type * const base,
                                 bool enable)
{
    WDOG_UNLOCK(base);
    base->CS = (base->CS & ~WDOG_CS_DBG_MASK) | WDOG_CS_DBG(enable ? 1UL : 0UL);
}

static inline void WDOG_SetWait(WDOG_Type * const base,
                                bool enable)
{
    WDOG_UNLOCK(base);
    base->CS = (base->CS & ~WDOG_CS_WAIT_MASK) | WDOG_CS_WAIT(enable ? 1UL : 0UL);
}

static inline void WDOG_SetStop(WDOG_Type * const base,
                                bool enable)
{
    WDOG_UNLOCK(base);

    if (enable)
    {
        base->CS |= WDOG_CS_STOP_MASK;
    }
    else
    {
        base->CS &= ~WDOG_CS_STOP_MASK;
    }
}

static inline bool WDOG_IsUnlocked(const WDOG_Type * base)
{
    return ((base->CS & WDOG_CS_ULK_MASK) >> WDOG_CS_ULK_SHIFT) != 0U;
}

static inline bool WDOG_IsReconfigurationComplete(const WDOG_Type * base)
{
    return ((base->CS & WDOG_CS_RCS_MASK) >> WDOG_CS_RCS_SHIFT) != 0U;
}

static inline uint32_t WDOG_GetTestMode(const WDOG_Type * base)
{
    return ((base->CS & WDOG_CS_TST_MASK) >> WDOG_CS_TST_SHIFT);
}


#if defined(__cplusplus)
}
#endif


#endif 

