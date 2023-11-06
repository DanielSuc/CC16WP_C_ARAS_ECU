
#ifndef BSP_CFG_LPI2CCOM1_H_
#define BSP_CFG_LPI2CCOM1_H_


#include "lpi2c_driver.h"

#define INST_LPI2C1 0


extern const lpi2c_master_user_config_t lpi2cCom1_MasterConfig0;

extern lpi2c_master_state_t lpi2cCom1MasterState;


typedef struct
{
    uint8_t i2c_instance_number;                            
    lpi2c_master_state_t * i2c_state_struct;                     
    const lpi2c_master_user_config_t * i2c_init_config_struct;   
}struct_i2c_config_t;

#endif 

