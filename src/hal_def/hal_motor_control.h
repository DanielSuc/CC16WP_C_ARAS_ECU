#ifndef HAL_MOTOR_CONTROL_H
#define HAL_MOTOR_CONTROL_H


#include "hal_data_types.h"
#include "hal_motor_control_cfg.h"


#define HAL_MOTOR_CONTROL_DUTY_CYCLE_0_PERMILLE                    0    
#define HAL_MOTOR_CONTROL_DUTY_CYCLE_1000_PERMILLE              1000    

#define HAL_MOTOR_CONTROL_DUTY_CYCLE_0_PERCENT                     0    
#define HAL_MOTOR_CONTROL_DUTY_CYCLE_100_PERCENT                 100    



typedef enum
{
    HAL_MOTOR_CONTROL_OK                    = 0u,               
    HAL_MOTOR_CONTROL_ERROR_MODE_INVALID                        

} enum_HAL_MOTOR_CONTROL_RETURN_VALUE;

typedef enum
{
    HAL_MOTOR_CONTROL_STATE_NOT_SET        = 0u,                
    HAL_MOTOR_CONTROL_STATE_STOPPED            ,                
    HAL_MOTOR_CONTROL_STATE_IN_BRAKE           ,                
    HAL_MOTOR_CONTROL_STATE_MOVING_LEFT        ,                
    HAL_MOTOR_CONTROL_STATE_MOVING_RIGHT       ,                
    HAL_MOTOR_CONTROL_STATE_ERROR                               

} enum_HAL_MOTOR_CONTROL_STATE;

typedef enum
{
    HAL_MOTOR_CONTROL_MODE_STOP            = 0u,                
    HAL_MOTOR_CONTROL_MODE_BRAKE               ,                
    HAL_MOTOR_CONTROL_MODE_MOVE_LEFT           ,                
    HAL_MOTOR_CONTROL_MODE_MOVE_RIGHT          ,                
    HAL_MOTOR_CONTROL_MODE_INVALID                              

} enum_HAL_MOTOR_CONTROL_MODE;

typedef struct
{
        enum_HAL_MOTOR_CONTROL_MODE  MotorDriveMode;            
        uint16_t                     MotorDutyCycle;            
        enum_HAL_MOTOR_CONTROL_STATE internalMotorState;        

} struct_HAL_MOTOR_CONTROL;


enum_HAL_MOTOR_CONTROL_RETURN_VALUE hal_mc_init(struct_HAL_MOTOR_CONTROL_CFG* ptrMotorControlCfg,struct_HAL_MOTOR_CONTROL* ptrMotorControl);

enum_HAL_MOTOR_CONTROL_RETURN_VALUE hal_mc_drive_motor(struct_HAL_MOTOR_CONTROL_CFG* ptrMotorControlCfg,struct_HAL_MOTOR_CONTROL* ptrMotorControl);


enum_HAL_MOTOR_CONTROL_RETURN_VALUE hal_mc_set_motor_frequency(struct_HAL_MOTOR_CONTROL* ptrMotorControl);

#endif



