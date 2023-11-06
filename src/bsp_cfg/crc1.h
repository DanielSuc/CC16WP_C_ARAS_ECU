#ifndef crc1_H
#define crc1_H


#include "clockMan1.h"
#include "Cpu.h"

#define NUMBER_OF_CRC_INSTANCES (1U)

#define INST_CRC1 (0U)

extern const crc_user_config_t crc1_InitConfig0;


typedef struct
{
    uint8_t crc_instance_number;                            
    const crc_user_config_t * crc_init_config_struct;       
}struct_crc_config_t;

extern struct_crc_config_t struct_crc_config_tbl[NUMBER_OF_CRC_INSTANCES];


#endif

