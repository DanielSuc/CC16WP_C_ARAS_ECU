
#if !defined(SCG_HW_ACCESS_H)
#define SCG_HW_ACCESS_H

#include "device_registers.h"
#include <stdbool.h>
#include <stddef.h>






#if defined(__cplusplus)
extern "C" {
#endif 


static inline uint32_t SCG_GetClockoutSourceSel(const SCG_Type * base)
{
    return (base->CLKOUTCNFG & SCG_CLKOUTCNFG_CLKOUTSEL_MASK) >> SCG_CLKOUTCNFG_CLKOUTSEL_SHIFT;
}


static inline uint32_t SCG_GetCurrentSystemClockSource(const SCG_Type * base)
{
    return ((base->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT);
}

static inline uint32_t SCG_GetCurrentCoreClockDividerRatio(const SCG_Type * base)
{
    return ((base->CSR & SCG_CSR_DIVCORE_MASK) >> SCG_CSR_DIVCORE_SHIFT);
}

static inline uint32_t SCG_GetCurrentBusClockDividerRatio(const SCG_Type * base)
{
    return ((base->CSR & SCG_CSR_DIVBUS_MASK) >> SCG_CSR_DIVBUS_SHIFT);
}

static inline uint32_t SCG_GetCurrentSlowClockDividerRatio(const SCG_Type * base)
{
    return ((base->CSR & SCG_CSR_DIVSLOW_MASK) >> SCG_CSR_DIVSLOW_SHIFT);
}

static inline void SCG_SetRunClockControl(SCG_Type * base, uint32_t source, uint32_t coreDivider, uint32_t busDivider, uint32_t slowDivider)
{
    uint32_t value = (uint32_t)(((source      << SCG_RCCR_SCS_SHIFT)     & SCG_RCCR_SCS_MASK)     |
                                ((coreDivider << SCG_RCCR_DIVCORE_SHIFT) & SCG_RCCR_DIVCORE_MASK) |
                                ((busDivider  << SCG_RCCR_DIVBUS_SHIFT)  & SCG_RCCR_DIVBUS_MASK)  |
                                ((slowDivider << SCG_RCCR_DIVSLOW_SHIFT) & SCG_RCCR_DIVSLOW_MASK) );
    base->RCCR = value;
}

static inline void SCG_SetVlprClockControl(SCG_Type * base, uint32_t source, uint32_t coreDivider, uint32_t busDivider, uint32_t slowDivider)
{
	uint32_t value = (uint32_t)(((source      << SCG_VCCR_SCS_SHIFT)     & SCG_VCCR_SCS_MASK)     |
								((coreDivider << SCG_VCCR_DIVCORE_SHIFT) & SCG_VCCR_DIVCORE_MASK) |
								((busDivider  << SCG_VCCR_DIVBUS_SHIFT)  & SCG_VCCR_DIVBUS_MASK)  |
								((slowDivider << SCG_VCCR_DIVSLOW_SHIFT) & SCG_VCCR_DIVSLOW_MASK) );

    base->VCCR = value;
}

#if FEATURE_HAS_HIGH_SPEED_RUN_MODE
static inline void SCG_SetHsrunClockControl(SCG_Type * base, uint32_t source, uint32_t coreDivider, uint32_t busDivider, uint32_t slowDivider)
{
	uint32_t value = (uint32_t)(((source      << SCG_HCCR_SCS_SHIFT)     & SCG_HCCR_SCS_MASK)     |
								((coreDivider << SCG_HCCR_DIVCORE_SHIFT) & SCG_HCCR_DIVCORE_MASK) |
								((busDivider  << SCG_HCCR_DIVBUS_SHIFT)  & SCG_HCCR_DIVBUS_MASK)  |
								((slowDivider << SCG_HCCR_DIVSLOW_SHIFT) & SCG_HCCR_DIVSLOW_MASK) );

	base->HCCR = value;
}
#endif

static inline uint32_t SCG_GetFircFirstAsyncDivider(const SCG_Type * base)
{
    return (base->FIRCDIV & SCG_FIRCDIV_FIRCDIV1_MASK) >> SCG_FIRCDIV_FIRCDIV1_SHIFT;
}

static inline uint32_t SCG_GetFircSecondAsyncDivider(const SCG_Type * base)
{
    return (base->FIRCDIV & SCG_FIRCDIV_FIRCDIV2_MASK) >> SCG_FIRCDIV_FIRCDIV2_SHIFT;
}


static inline void SCG_SetFircAsyncConfig(SCG_Type * base, uint32_t div1, uint32_t div2)
{
    uint32_t value = (uint32_t)(((div1 << SCG_FIRCDIV_FIRCDIV1_SHIFT) & SCG_FIRCDIV_FIRCDIV1_MASK)     |
                                ((div2 << SCG_FIRCDIV_FIRCDIV2_SHIFT) & SCG_FIRCDIV_FIRCDIV2_MASK) );
    base->FIRCDIV = value;
}


static inline uint32_t SCG_GetSircFirstAsyncDivider(const SCG_Type * base)
{
    return (base->SIRCDIV & SCG_SIRCDIV_SIRCDIV1_MASK) >> SCG_SIRCDIV_SIRCDIV1_SHIFT;
}

static inline uint32_t SCG_GetSircSecondAsyncDivider(const SCG_Type * base)
{
    return (base->SIRCDIV & SCG_SIRCDIV_SIRCDIV2_MASK) >> SCG_SIRCDIV_SIRCDIV2_SHIFT;
}


static inline void SCG_SetSircAsyncConfig(SCG_Type * base, uint32_t div1, uint32_t div2)
{
    uint32_t value = (uint32_t)(((div1 << SCG_SIRCDIV_SIRCDIV1_SHIFT) & SCG_SIRCDIV_SIRCDIV1_MASK)     |
                                ((div2 << SCG_SIRCDIV_SIRCDIV2_SHIFT) & SCG_SIRCDIV_SIRCDIV2_MASK) );
    base->SIRCDIV = value;
}



static inline uint32_t SCG_GetSoscFirstAsyncDivider(const SCG_Type * base)
{
    return (base->SOSCDIV & SCG_SOSCDIV_SOSCDIV1_MASK) >> SCG_SOSCDIV_SOSCDIV1_SHIFT;
}

static inline uint32_t SCG_GetSoscSecondAsyncDivider(const SCG_Type * base)
{
    return (base->SOSCDIV & SCG_SOSCDIV_SOSCDIV2_MASK) >> SCG_SOSCDIV_SOSCDIV2_SHIFT;
}


static inline void SCG_SetSoscAsyncConfig(SCG_Type * base, uint32_t div1, uint32_t div2)
{
    uint32_t value = (uint32_t)(((div1 << SCG_SOSCDIV_SOSCDIV1_SHIFT) & SCG_SOSCDIV_SOSCDIV1_MASK)     |
                                ((div2 << SCG_SOSCDIV_SOSCDIV2_SHIFT) & SCG_SOSCDIV_SOSCDIV2_MASK) );
    base->SOSCDIV = value;
}

#if FEATURE_HAS_SPLL_CLK
static inline uint32_t SCG_GetSpllFirstAsyncDivider(const SCG_Type * base)
{
    return (base->SPLLDIV & SCG_SPLLDIV_SPLLDIV1_MASK) >> SCG_SPLLDIV_SPLLDIV1_SHIFT;
}

static inline uint32_t SCG_GetSpllSecondAsyncDivider(const SCG_Type * base)
{
    return (base->SPLLDIV & SCG_SPLLDIV_SPLLDIV2_MASK) >> SCG_SPLLDIV_SPLLDIV2_SHIFT;
}


static inline void SCG_SetSpllAsyncConfig(SCG_Type * base, uint32_t div1, uint32_t div2)
{
    uint32_t value = (uint32_t)(((div1 << SCG_SPLLDIV_SPLLDIV1_SHIFT) & SCG_SPLLDIV_SPLLDIV1_MASK)     |
                                ((div2 << SCG_SPLLDIV_SPLLDIV2_SHIFT) & SCG_SPLLDIV_SPLLDIV2_MASK) );
    base->SPLLDIV = value;
}
#endif

static inline void SCG_SetClockoutSourceSel(SCG_Type * base, uint32_t source)
{
	uint32_t regValue;

    regValue = base->CLKOUTCNFG;
    regValue &= ~(SCG_CLKOUTCNFG_CLKOUTSEL_MASK);
    regValue |= SCG_CLKOUTCNFG_CLKOUTSEL(source);
    base->CLKOUTCNFG = regValue;
}



uint32_t SCG_GetSysOscFreq(const SCG_Type * base);





uint32_t SCG_GetSircFreq(const SCG_Type * base);




uint32_t SCG_GetFircFreq(const SCG_Type * base);


static inline bool SCG_GetSircSystemClockMode(const SCG_Type* const base)
{
    uint32_t regValue = (uint32_t)base->SIRCCSR;
    regValue = (regValue & SCG_SIRCCSR_SIRCSEL_MASK) >> SCG_SIRCCSR_SIRCSEL_SHIFT;
    return (regValue == 0U) ? false : true;
}

static inline bool SCG_GetSircStatus(const SCG_Type* const base)
{
    return (((base->SIRCCSR & SCG_SIRCCSR_SIRCVLD_MASK) >> SCG_SIRCCSR_SIRCVLD_SHIFT) != 0U) ? true : false;
}

static inline uint32_t SCG_GetSircRange(const SCG_Type* const base)
{
    return ((base->SIRCCFG & SCG_SIRCCFG_RANGE_MASK) >> SCG_SIRCCFG_RANGE_SHIFT);
}

static inline void SCG_ClearSircLock(SCG_Type*  base)
{
    base->SIRCCSR &= (uint32_t)(~(SCG_SIRCCSR_LK_MASK));
}


static inline void SCG_ClearSircControl(SCG_Type* base)
{
    base->SIRCCSR = 0U;
}


static inline void SCG_SetSircConfiguration(SCG_Type* base, uint8_t range)
{
    base->SIRCCFG = SCG_SIRCCFG_RANGE(range);
}

static inline void SCG_SetSircControl(SCG_Type* base, bool enableInStop, bool enableInLowPower, bool lockMode)
{
    uint32_t value = SCG_SIRCCSR_SIRCEN(1U)                                  |
                     SCG_SIRCCSR_SIRCSTEN(((enableInStop)     ? 1UL : 0UL )) |
                     SCG_SIRCCSR_SIRCLPEN(((enableInLowPower) ? 1UL : 0UL )) |
                     SCG_SIRCCSR_LK((lockMode) ? 1UL : 0UL);

    base->SIRCCSR = value;
}


static inline bool SCG_GetFircSystemClockMode(const SCG_Type* const base)
{
    uint32_t regValue = (uint32_t)base->FIRCCSR;
    regValue = (regValue & SCG_FIRCCSR_FIRCSEL_MASK) >> SCG_FIRCCSR_FIRCSEL_SHIFT;
    return (regValue == 0U) ? false : true;
}

static inline bool SCG_GetFircStatus(const SCG_Type* const base)
{
    return (((base->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK) >> SCG_FIRCCSR_FIRCVLD_SHIFT) != 0U) ? true : false;
}

static inline uint32_t SCG_GetFircRange(const SCG_Type* const base)
{
    return ((base->FIRCCFG & SCG_FIRCCFG_RANGE_MASK) >> SCG_FIRCCFG_RANGE_SHIFT);
}

static inline void SCG_ClearFircLock(SCG_Type*  base)
{
    base->FIRCCSR &= (uint32_t)(~(SCG_FIRCCSR_LK_MASK));
}


static inline void SCG_ClearFircControl(SCG_Type* base)
{
    base->FIRCCSR = SCG_FIRCCSR_FIRCERR_MASK;
}


static inline void SCG_SetFircConfiguration(SCG_Type* base, uint8_t range)
{
    base->FIRCCFG = SCG_FIRCCFG_RANGE(range);
}

static inline void SCG_SetFircControl(SCG_Type* base, bool regulator, bool lockMode)
{
    uint32_t value = SCG_FIRCCSR_FIRCEN(1U)                             |
                     SCG_FIRCCSR_FIRCREGOFF((regulator) ? 0UL : 1UL)    |
                     SCG_FIRCCSR_LK((lockMode) ? 1UL : 0UL);

    base->FIRCCSR = value;
}


static inline bool SCG_GetSoscSystemClockMode(const SCG_Type* const base)
{
    uint32_t regValue = (uint32_t)base->SOSCCSR;
    regValue = (regValue & SCG_SOSCCSR_SOSCSEL_MASK) >> SCG_SOSCCSR_SOSCSEL_SHIFT;
    return (regValue == 0U) ? false : true;
}

static inline bool SCG_GetSoscStatus(const SCG_Type* const base)
{
    return (((base->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK) >> SCG_SOSCCSR_SOSCVLD_SHIFT) != 0U) ? true : false;
}

static inline void SCG_ClearSoscLock(SCG_Type*  base)
{
    base->SOSCCSR &= (uint32_t)(~(SCG_SOSCCSR_LK_MASK));
}


static inline void SCG_ClearSoscControl(SCG_Type* base)
{
    base->SOSCCSR = SCG_SOSCCSR_SOSCERR_MASK;
}



static inline void SCG_SetSoscConfiguration(SCG_Type* base, uint32_t range, uint32_t gain, uint32_t extRef)
{
    base->SOSCCFG = SCG_SOSCCFG_RANGE(range)        |
                    SCG_SOSCCFG_HGO(gain)           |
                    SCG_SOSCCFG_EREFS(extRef);
}

static inline void SCG_SetSoscControl(SCG_Type* base, bool monitorMode, bool resetMode, bool lockMode)
{
    uint32_t value = SCG_SOSCCSR_SOSCEN(1U)                        |
    		         SCG_SOSCCSR_SOSCCM((monitorMode) ? 1UL : 0UL) |
					 SCG_SOSCCSR_SOSCCMRE((resetMode) ? 1UL : 0UL) |
                     SCG_SOSCCSR_LK((lockMode) ? 1UL : 0UL);

    base->SOSCCSR = value;
}

#if FEATURE_HAS_SPLL_CLK
static inline bool SCG_GetSpllSystemClockMode(const SCG_Type* const base)
{
    uint32_t regValue = (uint32_t)base->SPLLCSR;
    regValue = (regValue & SCG_SPLLCSR_SPLLSEL_MASK) >> SCG_SPLLCSR_SPLLSEL_SHIFT;
    return (regValue == 0U) ? false : true;
}

static inline bool SCG_GetSpllStatus(const SCG_Type* const base)
{
    return (((base->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK) >> SCG_SPLLCSR_SPLLVLD_SHIFT) != 0U) ? true : false;
}

static inline uint32_t SCG_GetSpllPredivider(const SCG_Type* const base)
{
    return ((base->SPLLCFG & SCG_SPLLCFG_PREDIV_MASK) >> SCG_SPLLCFG_PREDIV_SHIFT);
}

static inline uint32_t SCG_GetSpllMultiplier(const SCG_Type* const base)
{
    return ((base->SPLLCFG & SCG_SPLLCFG_MULT_MASK) >> SCG_SPLLCFG_MULT_SHIFT);
}

static inline void SCG_ClearSpllLock(SCG_Type*  base)
{
    base->SPLLCSR &= (uint32_t)(~(SCG_SPLLCSR_LK_MASK));
}


static inline void SCG_ClearSpllControl(SCG_Type* base)
{
    base->SPLLCSR = SCG_SPLLCSR_SPLLERR_MASK;
}

static inline void SCG_SetSpllConfiguration(SCG_Type* base, uint8_t divider, uint8_t multiplier)
{
    base->SPLLCFG = SCG_SPLLCFG_PREDIV(divider)  |
                    SCG_SPLLCFG_MULT(multiplier);
}

static inline void SCG_SetSpllControl(SCG_Type* base, bool monitorMode, bool resetMode, bool lockMode)
{
    uint32_t value = SCG_SPLLCSR_SPLLEN(1U)                        |
    		         SCG_SPLLCSR_SPLLCM((monitorMode) ? 1UL : 0UL) |
					 SCG_SPLLCSR_SPLLCMRE((resetMode) ? 1UL : 0UL) |
                     SCG_SPLLCSR_LK((lockMode) ? 1UL : 0UL);

    base->SPLLCSR = value;
}
#endif


#if defined(__cplusplus)
}
#endif 



#endif 

