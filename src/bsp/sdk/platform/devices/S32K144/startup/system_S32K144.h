



#ifndef SYSTEM_S32K144_H_
#define SYSTEM_S32K144_H_                        

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifndef DISABLE_WDOG
  #define DISABLE_WDOG                 1
#endif

#ifndef ICACHE_ENABLE
#define ICACHE_ENABLE                  0
#endif

#ifndef CPU_XTAL_CLK_HZ
  #define CPU_XTAL_CLK_HZ                XTAL_FREQ_HZ
#endif

#ifndef CPU_INT_FAST_CLK_HZ
  #define CPU_INT_FAST_CLK_HZ            48000000u
#endif

#ifndef DEFAULT_SYSTEM_CLOCK
 #define DEFAULT_SYSTEM_CLOCK            48000000u
#endif

extern uint32_t SystemCoreClock;

void SystemInit(void);

void SystemCoreClockUpdate(void);

void SystemSoftwareReset(void);

#ifdef __cplusplus
}
#endif

#endif  

