#ifndef rtcTimer1_H
#define rtcTimer1_H
#include "rtc_driver.h"
#include "clockMan1.h"
#include "Cpu.h"

#define RTCTIMER1 0UL



extern       rtc_init_config_t                  rtcTimer1_Config0;
extern       rtc_timedate_t                     rtcTimer1_StartTime0;

extern       rtc_register_lock_config_t         rtcTimer1_LockConfig0;

extern       rtc_interrupt_config_t             rtcTimer1_FaultIntConfig0;

extern       rtc_seconds_int_config_t            rtcTimer1_SecIntConfig0;


extern rtc_alarm_config_t   rtcTimer1_AlarmConfig0;

#endif

