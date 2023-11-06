#ifndef lpspiCom1_H
#define lpspiCom1_H


#include "clockMan1.h"
#include "Cpu.h"
#include "osif1.h"

#define LPSPICOM0 (0U)
#define LPSPICOM1 (1U)


extern const lpspi_master_config_t lpspiCom1_MasterConfig0;

extern const lpspi_slave_config_t lpspiCom1_SlaveConfig0;

typedef struct
{
    uint8_t spi_instance_number;
    lpspi_state_t spi_state_struct;
    const lpspi_master_config_t * const spi_init_master_config_struct;
    const lpspi_slave_config_t * const spi_init_slave_config_struct;
}struct_spi_config_t;



#endif


