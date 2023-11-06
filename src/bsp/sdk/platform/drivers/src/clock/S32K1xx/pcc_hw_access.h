
#if !defined(PCC_HW_ACCESS_H)
#define PCC_HW_ACCESS_H

#include "device_registers.h"
#include <stdbool.h>
#include <stddef.h>




extern const uint16_t clockNameMappings[CLOCK_NAME_COUNT];

#if defined(__cplusplus)
extern "C" {
#endif 


static inline void PCC_SetPeripheralClockControl(PCC_Type* base, clock_names_t clockName, bool clockGate, uint32_t clockSource, uint32_t divider, uint32_t multiplier)
{
   uint32_t value =  PCC_PCCn_PCS(clockSource)              |
                     PCC_PCCn_FRAC(multiplier)              |
                     PCC_PCCn_PCD(divider)                  |
                     PCC_PCCn_CGC(clockGate ? 1UL : 0UL );

   base->PCCn[clockNameMappings[clockName]] = value;
}

static inline void PCC_SetClockMode(PCC_Type* const base,
                                       const clock_names_t clockName,
                                       const bool isClockEnabled)
{
   if (isClockEnabled)
   {
       base->PCCn[clockNameMappings[clockName]] |= PCC_PCCn_CGC(1UL);
   }
   else
   {
       base->PCCn[clockNameMappings[clockName]] &= (uint32_t)(~(PCC_PCCn_CGC_MASK));
   }
}



static inline bool PCC_GetClockMode(const PCC_Type* const base,
                                       const clock_names_t clockName)
{
   uint32_t regValue = (uint32_t)base->PCCn[clockNameMappings[clockName]];
   regValue = (regValue & PCC_PCCn_CGC_MASK) >> PCC_PCCn_CGC_SHIFT;
   return (regValue == 0U) ? false : true;
}

static inline uint32_t PCC_GetClockSourceSel(const PCC_Type* const base,
                                                                 const clock_names_t clockName)
{
   return ((base->PCCn[clockNameMappings[clockName]] & PCC_PCCn_PCS_MASK) >> PCC_PCCn_PCS_SHIFT);
}

static inline uint32_t PCC_GetFracValueSel(const PCC_Type* const base,
                                               const clock_names_t clockName)
{
   return ((base->PCCn[clockNameMappings[clockName]] & PCC_PCCn_FRAC_MASK) >> PCC_PCCn_FRAC_SHIFT);
}

static inline uint32_t PCC_GetDividerSel(const PCC_Type* const base,
                                             const clock_names_t clockName)
{
   return ((base->PCCn[clockNameMappings[clockName]] & PCC_PCCn_PCD_MASK) >> PCC_PCCn_PCD_SHIFT);
}





#if defined(__cplusplus)
}
#endif 



#endif 


