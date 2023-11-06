
#ifndef SRC_ROLE_BOARD_ROLE_BOARD_H_
#define SRC_ROLE_BOARD_ROLE_BOARD_H_

#if defined(__cplusplus)
extern "C" {
#endif

#if 0
typedef enum
{
    E_BAUD_1MBIT                 = 1u,
    E_BAUD_800KBIT                   ,
    E_BAUD_500KBIT                   ,
    E_BAUD_250KBIT                   ,
    E_BAUD_125KBIT                   ,
    E_BAUD_50KBIT                    ,
    E_BAUD_20KBIT                    ,
    E_BAUD_10KBIT                    ,
    E_BAUD_100KBIT                   ,
    E_BAUD_83KBIT                    ,
    E_BAUD_33KBIT                    ,
    E_BAUD_MAX
} enum_bl_baudrate_t;
#endif 

typedef enum
{
	MODE_NORMAL                  = 1u,
	MODE_PAUSED                      ,
	MODE_WRITE_PROTECT

} enum_SPI_MEMORY_MODE;

#if !defined(ROLE_MINIMAL)
#include "board_variants.h"
#endif 

#define ROLE_DO_PARAM_LIST_BOARD

typedef enum
{
    ROLE_BOARD_CAN_TRANSCEIVER_TURN_ON  = ROLE_COMPOSE_DO_ID(ROLE_TYPE_BOARD,   0u, ROLE_ANY_PARAM_UINT32),
    ROLE_BOARD_CAN_TRANSCEIVER_TURN_OFF = ROLE_COMPOSE_DO_ID(ROLE_TYPE_BOARD,   1u, ROLE_ANY_PARAM_UINT32),

    ROLE_BOARD_EXT_WDOG_ENABLE          = ROLE_COMPOSE_DO_ID(ROLE_TYPE_BOARD,   2u, ROLE_ANY_PARAM_UINT32),
    ROLE_BOARD_EXT_WDOG_RESET           = ROLE_COMPOSE_DO_ID(ROLE_TYPE_BOARD,   3u, ROLE_ANY_PARAM_UINT32),

	ROLE_BOARD_SPI_MEMORY_MODE          = ROLE_COMPOSE_DO_ID(ROLE_TYPE_BOARD,   4u, ROLE_ANY_PARAM_UINT32)

} enum_ROLE_BOARD_DO_ID;



void role_board_constructor(role_id_t id, pf_role_constructor parent) __attribute__((weak));



#ifdef __cplusplus
}
#endif

#endif 

