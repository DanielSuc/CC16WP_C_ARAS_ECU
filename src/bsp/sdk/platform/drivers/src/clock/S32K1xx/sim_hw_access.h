
#if !defined(SIM_HW_ACCESS_H)
#define SIM_HW_ACCESS_H

#include "device_registers.h"
#include <stdbool.h>
#include <stddef.h>




#if defined(__cplusplus)
extern "C" {
#endif 


static inline uint32_t SIM_GetRtcClkSrc(const SIM_Type * base)
{
    return ((base->LPOCLKS & SIM_LPOCLKS_RTCCLKSEL_MASK) >> SIM_LPOCLKS_RTCCLKSEL_SHIFT);
}


static inline void SIM_SetLpoClocks(SIM_Type* base, bool enableLpo1k, bool enableLpo32k, uint32_t sourceLpoClk, uint32_t sourceRtcClk)
{
    uint32_t regValue = base->LPOCLKS;

    regValue &= ~( SIM_LPOCLKS_LPO1KCLKEN_MASK  |
                   SIM_LPOCLKS_LPO32KCLKEN_MASK |
                   SIM_LPOCLKS_LPOCLKSEL_MASK   |
                   SIM_LPOCLKS_RTCCLKSEL_MASK   );

    regValue |= SIM_LPOCLKS_LPO1KCLKEN(enableLpo1k ? 1UL : 0UL);
    regValue |= SIM_LPOCLKS_LPO32KCLKEN(enableLpo32k ? 1UL : 0UL);
    regValue |= SIM_LPOCLKS_LPOCLKSEL(sourceLpoClk);
    regValue |= SIM_LPOCLKS_RTCCLKSEL(sourceRtcClk);

    base->LPOCLKS = regValue;
}

static inline void SIM_SetEimClockGate(SIM_Type* base, bool enable)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue &= (uint32_t)(~(SIM_PLATCGC_CGCEIM_MASK));
    regValue |= SIM_PLATCGC_CGCEIM(enable ? 1UL : 0UL);
    base->PLATCGC = (uint32_t)regValue;
}

static inline bool SIM_GetEimClockGate(const SIM_Type * base)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue = (regValue & SIM_PLATCGC_CGCEIM_MASK) >> SIM_PLATCGC_CGCEIM_SHIFT;
    return (regValue != 0U) ? true : false;
}

static inline void SIM_SetErmClockGate(SIM_Type* base, bool enable)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue &= (uint32_t)(~(SIM_PLATCGC_CGCERM_MASK));
    regValue |= SIM_PLATCGC_CGCERM(enable ? 1UL : 0UL);
    base->PLATCGC = (uint32_t)regValue;
}



static inline bool SIM_GetErmClockGate(const SIM_Type * base)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue = (regValue & SIM_PLATCGC_CGCERM_MASK) >> SIM_PLATCGC_CGCERM_SHIFT;
    return (regValue != 0U) ? true : false;
}

static inline void SIM_SetDmaClockGate(SIM_Type* base, bool enable)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue &= (uint32_t)(~(SIM_PLATCGC_CGCDMA_MASK));
    regValue |= SIM_PLATCGC_CGCDMA(enable ? 1UL : 0UL);
    base->PLATCGC = (uint32_t)regValue;
}



static inline bool SIM_GetDmaClockGate(const SIM_Type * base)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue = (regValue & SIM_PLATCGC_CGCDMA_MASK) >> SIM_PLATCGC_CGCDMA_SHIFT;
    return (regValue != 0U) ? true : false;
}


static inline void SIM_SetMpuClockGate(SIM_Type* base, bool enable)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue &= (uint32_t)(~(SIM_PLATCGC_CGCMPU_MASK));
    regValue |= SIM_PLATCGC_CGCMPU(enable ? 1UL : 0UL);
    base->PLATCGC = (uint32_t)regValue;
}

static inline bool SIM_GetMpuClockGate(const SIM_Type * base)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue = (regValue & SIM_PLATCGC_CGCMPU_MASK) >> SIM_PLATCGC_CGCMPU_SHIFT;
    return (regValue != 0U) ? true : false;
}

static inline void SIM_SetMscmClockGate(SIM_Type* base, bool enable)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue &= (uint32_t)(~(SIM_PLATCGC_CGCMSCM_MASK));
    regValue |= SIM_PLATCGC_CGCMSCM(enable ? 1UL : 0UL);
    base->PLATCGC = (uint32_t)regValue;
}

static inline bool SIM_GetMscmClockGate(const SIM_Type * base)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue = (regValue & SIM_PLATCGC_CGCMSCM_MASK) >> SIM_PLATCGC_CGCMSCM_SHIFT;
    return (regValue != 0U) ? true : false;
}

#if defined(QuadSPI_INSTANCE_COUNT)
static inline void SIM_SetQspiIntRefClockGate(SIM_Type* base, bool enable)
{
    uint32_t regValue = (uint32_t)base->MISCTRL0;
    regValue &= (uint32_t)(~(SIM_MISCTRL0_QSPI_CLK_SEL_MASK));
    regValue |= SIM_MISCTRL0_QSPI_CLK_SEL(enable ? 1UL : 0UL);
    base->MISCTRL0 = (uint32_t)regValue;
}

static inline bool QSPI_GetClockingModeSelection(const QuadSPI_Type *baseAddr)
{
	return ((baseAddr->MCR & QuadSPI_MCR_SCLKCFG_MASK) >> QuadSPI_MCR_SCLKCFG_SHIFT) != 0U;
}

static inline bool SIM_GetClockingModeSelection(const SIM_Type *baseAddr)
{
	return ((baseAddr->MISCTRL0 & SIM_MISCTRL0_QSPI_CLK_SEL_MASK) >> SIM_MISCTRL0_QSPI_CLK_SEL_SHIFT) != 0U;
}

static inline uint32_t QSPI_GetClockingProgrammableDividerValue(const QuadSPI_Type *baseAddr)
{
	return (baseAddr->SOCCR & QuadSPI_SOCCR_SOCCFG_MASK) >> QuadSPI_SOCCR_SOCCFG_SHIFT;
}
#endif


static inline uint32_t SIM_GetFtm0ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM0CLKSEL_MASK) >> SIM_FTMOPT0_FTM0CLKSEL_SHIFT;
}

static inline uint32_t SIM_GetFtm1ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM1CLKSEL_MASK) >> SIM_FTMOPT0_FTM1CLKSEL_SHIFT;
}

static inline uint32_t SIM_GetFtm2ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM2CLKSEL_MASK) >> SIM_FTMOPT0_FTM2CLKSEL_SHIFT;
}

static inline uint32_t SIM_GetFtm3ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM3CLKSEL_MASK) >> SIM_FTMOPT0_FTM3CLKSEL_SHIFT;
}

#if FTM_INSTANCE_COUNT > 4U
static inline uint32_t SIM_GetFtm4ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM4CLKSEL_MASK) >> SIM_FTMOPT0_FTM4CLKSEL_SHIFT;
}
#endif

#if FTM_INSTANCE_COUNT > 5U
static inline uint32_t SIM_GetFtm5ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM5CLKSEL_MASK) >> SIM_FTMOPT0_FTM5CLKSEL_SHIFT;
}
#endif

#if FTM_INSTANCE_COUNT > 6U
static inline uint32_t SIM_GetFtm6ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM6CLKSEL_MASK) >> SIM_FTMOPT0_FTM6CLKSEL_SHIFT;
}
#endif


#if FTM_INSTANCE_COUNT > 7U
static inline uint32_t SIM_GetFtm7ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM7CLKSEL_MASK) >> SIM_FTMOPT0_FTM7CLKSEL_SHIFT;
}
#endif

static inline bool SIM_GetLpo32KStatus(const SIM_Type * base)
{
    return (((base->LPOCLKS & SIM_LPOCLKS_LPO32KCLKEN_MASK) >> SIM_LPOCLKS_LPO32KCLKEN_SHIFT) != 0U) ? true : false;
}

static inline bool SIM_GetLpo1KStatus(const SIM_Type * base)
{
    return (((base->LPOCLKS & SIM_LPOCLKS_LPO1KCLKEN_MASK) >> SIM_LPOCLKS_LPO1KCLKEN_SHIFT) != 0U) ? true : false;
}

static inline uint32_t SIM_GetLpoClkSelectorValue(const SIM_Type * base)
{
    return ((base->LPOCLKS & SIM_LPOCLKS_LPOCLKSEL_MASK) >> SIM_LPOCLKS_LPOCLKSEL_SHIFT);
}

static inline bool SIM_GetClockoutStatus(const SIM_Type * base)
{
    return (((base->CHIPCTL & SIM_CHIPCTL_CLKOUTEN_MASK) >> SIM_CHIPCTL_CLKOUTEN_SHIFT) == 0U) ? false : true;
}

static inline uint32_t SIM_GetClockoutDividerValue(const SIM_Type * base)
{
    return ((base->CHIPCTL & SIM_CHIPCTL_CLKOUTDIV_MASK) >> SIM_CHIPCTL_CLKOUTDIV_SHIFT);
}

static inline uint32_t SIM_GetClockoutSelectorValue(const SIM_Type * base)
{
    return ((base->CHIPCTL & SIM_CHIPCTL_CLKOUTSEL_MASK) >> SIM_CHIPCTL_CLKOUTSEL_SHIFT);
}

static inline void SIM_SetClockout(SIM_Type* base, bool enable, uint32_t source, uint32_t divider)
{
    uint32_t regValue = base->CHIPCTL;

    regValue &= ~( SIM_CHIPCTL_CLKOUTEN_MASK  |
    		       SIM_CHIPCTL_CLKOUTDIV_MASK |
			       SIM_CHIPCTL_CLKOUTSEL_MASK );

    regValue |= SIM_CHIPCTL_CLKOUTEN(enable ? 1UL : 0UL);
    regValue |= SIM_CHIPCTL_CLKOUTSEL(source);
    regValue |= SIM_CHIPCTL_CLKOUTDIV(divider);

    base->CHIPCTL = regValue;
}

static inline void SIM_SetTraceClockSource(SIM_Type* base, uint32_t clTraceSrc)
{
    uint32_t regValue;

    regValue = (uint32_t)base->CHIPCTL;
    regValue &= (uint32_t)(~(SIM_CHIPCTL_TRACECLK_SEL_MASK));
    regValue |= SIM_CHIPCTL_TRACECLK_SEL(clTraceSrc);
    base->CHIPCTL = (uint32_t)regValue;
}

static inline void SIM_ClearTraceClockConfig(SIM_Type * base)
{
    base->CLKDIV4 &= 0U;
}

static inline void SIM_SetTraceClockConfig(SIM_Type * base, bool enable, uint32_t divider, uint32_t multiplier)
{
    base->CLKDIV4 = SIM_CLKDIV4_TRACEDIVEN(enable ? 1UL : 0UL) |
                    SIM_CLKDIV4_TRACEDIV(divider)              |
                    SIM_CLKDIV4_TRACEFRAC(multiplier);
}



#if defined(__cplusplus)
}
#endif 



#endif 


