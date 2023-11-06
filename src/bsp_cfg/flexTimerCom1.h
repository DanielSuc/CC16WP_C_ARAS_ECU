
#ifndef flexTimerCom1_H
#define flexTimerCom1_H

#include "io_tables.h"
#include "pins_driver.h"
#include "ftm_pwm_driver.h"
#include "ftm_ic_driver.h"
#include "clockMan1.h"
#include "ftm_ic_driver.h"
#include "ftm_mc_driver.h"
#include "ftm_qd_driver.h"
#include "ftm_oc_driver.h"
#include "ftm_pwm_driver.h"
#include "Cpu.h"



#if defined(S32K148)
	#define FTM_IC_MODULES_USED     8U 
#else
	#define FTM_IC_MODULES_USED     4U 
#endif

#define MAX_FTM_INSTANCES 8	   

#define MODULE_NONE     (uint8_t)(-1U)
#define MODULE_0        0U
#define INST_FLEXTIMER0 MODULE_0

#define MODULE_1 1U
#define INST_FLEXTIMER1 MODULE_1

#define MODULE_2 2U
#define INST_FLEXTIMER2 MODULE_2

#define MODULE_3 3U
#define INST_FLEXTIMER3 MODULE_3

#define MODULE_4 4U
#define INST_FLEXTIMER4 MODULE_4

#define MODULE_5 5U
#define INST_FLEXTIMER5 MODULE_5

#define MODULE_6 6U
#define INST_FLEXTIMER6 MODULE_6

#define MODULE_7 7U
#define INST_FLEXTIMER7 MODULE_7


typedef struct
{
    ftm_pwm_param_t *pwm_config_t;          
    ftm_input_param_t *ic_config_t;         
    uint8_t io_pin_name;              		
    ftm_user_config_t *timer_mode_cfg;      
    ftm_state_t * ftm_state;                
    uint32_t pwm_instance;                  
    uint32_t pwm_channel;                   
    uint32_t pwm_pin_name;                  
}struct_init_ftm_config_t;




extern const ftm_pwm_fault_param_t flexTimer_FaultConfig;
extern const ftm_user_config_t  flexTimer_freq_in_InitConfig;
extern const ftm_user_config_t  flexTimer_pwm_InitConfig;

extern ftm_pwm_param_t flexTimer_PwmConfigCom;
extern ftm_independent_ch_param_t flexTimer_pwmChanConfigCom[8];

extern ftm_input_param_t flexTimer_InputCaptureConfigCom;
extern ftm_input_ch_param_t flexTimer_icChanConfigCom[8];

extern ftm_state_t ftmStateStruct[8];

#endif


