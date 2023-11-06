
#ifndef RTC_DRIVER_H
#define RTC_DRIVER_H

#include <stddef.h>
#include "status.h"
#include "interrupt_manager.h"


#define SECONDS_IN_A_DAY     (86400UL)
#define SECONDS_IN_A_HOUR    (3600U)
#define SECONDS_IN_A_MIN     (60U)
#define MINS_IN_A_HOUR       (60U)
#define HOURS_IN_A_DAY       (24U)
#define DAYS_IN_A_YEAR       (365U)
#define DAYS_IN_A_LEAP_YEAR  (366U)
#define YEAR_RANGE_START     (1970U)
#define YEAR_RANGE_END       (2099U)

typedef enum
{
    RTC_INT_1HZ   = 0x00U,     
    RTC_INT_2HZ   = 0x01U,     
    RTC_INT_4HZ   = 0x02U,     
    RTC_INT_8HZ   = 0x03U,     
    RTC_INT_16HZ  = 0x04U,     
    RTC_INT_32HZ  = 0x05U,     
    RTC_INT_64HZ  = 0x06U,     
    RTC_INT_128HZ = 0x07U      
} rtc_second_int_cfg_t;

typedef enum
{
    RTC_CLKOUT_DISABLED  = 0x00U,  
    RTC_CLKOUT_SRC_TSIC  = 0x01U,  
    RTC_CLKOUT_SRC_32KHZ = 0x02U   
} rtc_clk_out_config_t;

typedef enum
{
    RTC_CLK_SRC_OSC_32KHZ = 0x00U, 
    RTC_CLK_SRC_LPO_1KHZ  = 0x01U  
} rtc_clk_select_t;

typedef enum
{
    RTC_LOCK_REG_LOCK   = 0x00U,   
    RTC_STATUS_REG_LOCK = 0x01U,   
    RTC_CTRL_REG_LOCK   = 0x02U,   
    RTC_TCL_REG_LOCK    = 0x03U    
} rtc_lock_register_select_t;

typedef struct
{
    uint16_t year;      
    uint16_t month;     
    uint16_t day;       
    uint16_t hour;      
    uint16_t minutes;   
    uint8_t seconds;    
} rtc_timedate_t;

typedef struct
{
    uint8_t                 compensationInterval;       
    int8_t                  compensation;               
    rtc_clk_select_t        clockSelect;                
    rtc_clk_out_config_t    clockOutConfig;             
    bool                    updateEnable;               
    bool                    nonSupervisorAccessEnable;  
} rtc_init_config_t;

typedef struct
{
    rtc_timedate_t  alarmTime;                                
    uint32_t        repetitionInterval;                       
    uint32_t        numberOfRepeats;                          
    bool            repeatForever;                            
    bool            alarmIntEnable;                           
    void            (* alarmCallback)(void * callbackParam);  
    void            * callbackParams;                         
} rtc_alarm_config_t;

typedef struct
{
    bool                 overflowIntEnable;                       
    bool                 timeInvalidIntEnable;                    
    void                (* rtcCallback)(void * callbackParam);    
    void                * callbackParams;                         
} rtc_interrupt_config_t;

typedef struct
{
    rtc_second_int_cfg_t secondIntConfig;                             
    bool                 secondIntEnable;                             
    void                (* rtcSecondsCallback)(void * callbackParam); 
    void                * secondsCallbackParams;                      
} rtc_seconds_int_config_t;

typedef struct
{
    bool lockRegisterLock;              
    bool statusRegisterLock;            
    bool controlRegisterLock;           
    bool timeCompensationRegisterLock;  
} rtc_register_lock_config_t;


#if defined(__cplusplus)
extern "C" {
#endif

status_t RTC_DRV_Init(uint32_t instance, const rtc_init_config_t * const rtcUserCfg);

status_t RTC_DRV_Deinit(uint32_t instance);

void RTC_DRV_GetDefaultConfig(rtc_init_config_t * const config);

status_t RTC_DRV_StartCounter(uint32_t instance);

status_t RTC_DRV_StopCounter(uint32_t instance);

status_t RTC_DRV_GetCurrentTimeDate(uint32_t instance, rtc_timedate_t * const currentTime);

status_t RTC_DRV_SetTimeDate(uint32_t instance, const rtc_timedate_t * const time);

status_t RTC_DRV_ConfigureRegisterLock(uint32_t instance, const rtc_register_lock_config_t * const lockConfig);

void RTC_DRV_GetRegisterLock(uint32_t instance, rtc_register_lock_config_t * const lockConfig);

status_t RTC_DRV_ConfigureTimeCompensation(uint32_t instance, uint8_t  compInterval, int8_t   compensation);

void RTC_DRV_GetTimeCompensation(uint32_t instance, uint8_t * compInterval, int8_t * compensation);

void RTC_DRV_ConfigureFaultInt(uint32_t instance, rtc_interrupt_config_t * const intConfig);

void RTC_DRV_ConfigureSecondsInt(uint32_t instance, rtc_seconds_int_config_t * const intConfig);

status_t RTC_DRV_ConfigureAlarm(uint32_t instance, rtc_alarm_config_t * const alarmConfig);

void RTC_DRV_GetAlarmConfig(uint32_t instance, rtc_alarm_config_t * alarmConfig);

bool RTC_DRV_IsAlarmPending(uint32_t instance);

void RTC_DRV_ConvertSecondsToTimeDate(const uint32_t * seconds, rtc_timedate_t * const timeDate);

void RTC_DRV_ConvertTimeDateToSeconds(const rtc_timedate_t * const timeDate, uint32_t * const seconds);

bool RTC_DRV_IsYearLeap(uint16_t year);

bool RTC_DRV_IsTimeDateCorrectFormat(const rtc_timedate_t * const timeDate);

status_t RTC_DRV_GetNextAlarmTime(uint32_t instance, rtc_timedate_t * const alarmTime);

void RTC_DRV_IRQHandler(uint32_t instance);

void RTC_DRV_SecondsIRQHandler(uint32_t instance);

#if defined(__cplusplus)
}
#endif


#endif 

