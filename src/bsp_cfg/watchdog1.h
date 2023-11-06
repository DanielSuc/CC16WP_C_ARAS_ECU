#ifndef watchdog1_H
#define watchdog1_H
#include "wdog_driver.h"
#include "clockMan1.h"
#include "Cpu.h"

#define WDT_SIGNAL_MAIN_LOOP_BIT	0x1u

#define INST_WATCHDOG1 0U

extern const wdog_user_config_t watchdog1_Config0;

#endif

