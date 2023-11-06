#ifndef lpi2c1_H
#define lpi2c1_H


#include "lpi2c_driver.h"
#include "clockMan1.h"
#include "Cpu.h"
#include "dmaController1.h"
#include "osif1.h"
#include "lpi2cCom1.h"

#define NUMBER_OF_I2C_INSTANCES     (1U)

extern struct_i2c_config_t struct_i2c_config_tbl[NUMBER_OF_I2C_INSTANCES];

#endif

