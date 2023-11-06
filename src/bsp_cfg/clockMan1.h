#ifndef clockMan1_H
#define clockMan1_H

#include <stdbool.h>
#include <stdint.h>

#include "Cpu.h"


extern const clock_manager_user_config_t clockMan1_InitConfig0;

#define CLOCK_MANAGER_CONFIG_CNT 1U

extern clock_manager_user_config_t const *g_clockManConfigsArr[];

extern const peripheral_clock_config_t peripheralClockConfig0[];

#if defined(CPU_S32K148)
#define NUM_OF_PERIPHERAL_CLOCKS_0 34U
#elif defined(CPU_S32K142)
#define NUM_OF_PERIPHERAL_CLOCKS_0 27U
#else
#define NUM_OF_PERIPHERAL_CLOCKS_0 30U
#endif

#define CLOCK_MANAGER_CALLBACK_CNT 0U

extern clock_manager_callback_user_config_t *g_clockManCallbacksArr[];
#endif


