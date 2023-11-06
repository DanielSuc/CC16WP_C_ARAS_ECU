#ifndef canCom1_H
#define canCom1_H

#include "clockMan1.h"
#include "Cpu.h"
#include "dmaController1.h"
#include "osif1.h"
#include "sfl_fifo.h"
#include "hal_can.h"

#if defined(CPU_S32K142)
#define NUMBER_OF_CAN_INSTANCES (2U)
#else
#define NUMBER_OF_CAN_INSTANCES (3U)
#endif


#define INST_CANCOM1 (0U)
#define INST_CANCOM2 (1U)
#define INST_CANCOM3 (2U)

typedef struct {
    bool fd_enable;                         
    uint8_t fd_padding;                     
    bool enable_brs;                        
} struct_can_fd_tx_config_t;

typedef struct
{
	uint8_t can_instance_number;							
	flexcan_state_t * can_state_struct;						
	const flexcan_user_config_t * can_init_config_struct;	
	struct_can_fd_tx_config_t *ptr_tx_mode;      			
}struct_can_config_t;

extern struct_can_config_t struct_can_config_tbl[NUMBER_OF_CAN_INSTANCES];

extern flexcan_state_t can_state[NUMBER_OF_CAN_INSTANCES];

extern const flexcan_user_config_t can_fd_InitConfig;
extern const flexcan_user_config_t can_hs_InitConfig;

extern struct_can_fd_tx_config_t can_hs_tx_config;
extern struct_can_fd_tx_config_t can_fd_tx_config;

#endif


