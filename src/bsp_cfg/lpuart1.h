

#ifndef lpuart1_H
#define lpuart1_H

#include "clockMan1.h"
#include "Cpu.h"
#include "dmaController1.h"
#include "osif1.h"


#if defined(S32K148)
#define NUMBER_OF_LPUART_INSTANCES (3U)
#else
#define NUMBER_OF_LPUART_INSTANCES (2U)
#endif

#define MAX_LPUART_INSTANCES  (3U)


#define INST_LPUART0 (0U)
#define INST_LPUART1 (1U)
#define INST_LPUART2 (2U)



typedef struct
{
	uint8_t lpuart_instance_number;								
	lpuart_state_t * lpuart_state_struct;						
	lpuart_user_config_t * lpuart_init_config_struct;		
}struct_lpuart_config_t;

extern struct_lpuart_config_t struct_lpuart_config[MAX_LPUART_INSTANCES];

#endif  




