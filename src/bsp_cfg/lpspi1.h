#ifndef lpspi1_H
#define lpspi1_H


#include "clockMan1.h"
#include "Cpu.h"
#include "osif1.h"
#include "lpspiCom1.h"

#define NUMBER_OF_SPI_INSTANCES (2U)

extern struct_spi_config_t struct_spi_config_tbl[NUMBER_OF_SPI_INSTANCES];

#endif


