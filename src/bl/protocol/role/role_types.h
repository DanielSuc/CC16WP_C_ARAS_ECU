
#ifndef SRC_ROLE_TYPES_H_
#define SRC_ROLE_TYPES_H_

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct struct_ROLE struct_ROLE;

typedef uint16_t     role_id_t;
typedef uint16_t     role_do_param_t;
typedef uint32_t     role_do_id_t;

#define ROLE_ID_TYPE(id)            ((uint8_t)( id >> 8u ))     
#define ROLE_ID_IND(id)             ((uint8_t)( id ))           

#define ROLE_DO_TYPE(id)            ((uint8_t)( id >> 24u ))     
#define ROLE_DO_ID(id)              ((uint16_t)( id >> 16u ))    
#define ROLE_DO_PARAM(id)           ((role_do_param_t)( id ))    

#define ROLE_COMPOSE_ID(type, ind) \
  ( (((role_id_t)type) << 8u) | ((uint8_t)ind) )

#define ROLE_COMPOSE_DO_PARAM_BASE(type) \
  (((role_do_param_t)(type & (uint8_t)(-1))) << 8u)

#define ROLE_COMPOSE_DO_ID(type, ind, param_id) \
  ( (((role_do_id_t)(type & (uint8_t)(-1))) << 24u) \
  | (((role_do_id_t)(ind & (uint8_t)(-1))) << 16u) \
  | ((role_do_id_t)(param_id & (role_do_param_t)(-1))) )

#define ROLE_MAP_REAL_PARAM_TO_NUM(param, num) \
  param : num


typedef enum
{
    ROLE_TYPE_ANY,

    ROLE_TYPE_BOARD,

    ROLE_TYPE_PHY,

    ROLE_TYPE_SYS = ROLE_TYPE_PHY,
    ROLE_TYPE_TICK,
    ROLE_TYPE_FLASH,
    ROLE_TYPE_CAN,
    ROLE_TYPE_SPI,

    ROLE_TYPE_PROTOCOL,
    ROLE_TYPE_PROTOCOL_BOOTLOADER = ROLE_TYPE_PROTOCOL,
    ROLE_TYPE_WALLBOX_BOOTLOADER,

    ROLE_TYPE_SPI_BOOTLOADER

} enum_ROLE_TYPE;

typedef enum
{
    ROLE_ID_BOARD = ROLE_COMPOSE_ID(ROLE_TYPE_BOARD, 0u),

    ROLE_ID_PHY_SYS = ROLE_COMPOSE_ID(ROLE_TYPE_SYS, 1u),
    ROLE_ID_PHY_TICK = ROLE_COMPOSE_ID(ROLE_TYPE_TICK, 2u),
    ROLE_ID_PHY_FLASH = ROLE_COMPOSE_ID(ROLE_TYPE_FLASH, 3u),

    ROLE_ID_PHY_CAN0 = ROLE_COMPOSE_ID(ROLE_TYPE_CAN, 4u),
    ROLE_ID_PHY_CAN1 = ROLE_COMPOSE_ID(ROLE_TYPE_CAN, 5u),
    ROLE_ID_PHY_CAN2 = ROLE_COMPOSE_ID(ROLE_TYPE_CAN, 6u),

    ROLE_ID_PHY_SPI = ROLE_COMPOSE_ID(ROLE_TYPE_SPI, 7u),

	ROLE_ID_PROTOCOL_BOOTLOADER = ROLE_COMPOSE_ID(ROLE_TYPE_PROTOCOL_BOOTLOADER, 8u),
    ROLE_ID_WALLBOX_BOOTLOADER = ROLE_COMPOSE_ID(ROLE_TYPE_WALLBOX_BOOTLOADER, 9u),

    ROLE_ID_SPI_BOOTLOADER = ROLE_COMPOSE_ID(ROLE_TYPE_SPI_BOOTLOADER, 10u),

	ROLE_ID_DUMMY_END
} enum_ROLE_ID;

typedef enum
{
    ROLE_ANY_PARAM_UINT32 = ROLE_COMPOSE_DO_PARAM_BASE(ROLE_TYPE_ANY),
    ROLE_ANY_PARAM_UINT32PTR
} enum_ROLE_ANY_DO_PARAM;

typedef enum
{
    ROLE_INIT = ROLE_COMPOSE_DO_ID(ROLE_TYPE_ANY, 0u, ROLE_ANY_PARAM_UINT32),
    ROLE_START = ROLE_COMPOSE_DO_ID(ROLE_TYPE_ANY, 1u, ROLE_ANY_PARAM_UINT32),
    ROLE_STOP = ROLE_COMPOSE_DO_ID(ROLE_TYPE_ANY, 2u, ROLE_ANY_PARAM_UINT32)
} enum_ROLE_ANY_DO_ID;

#define ROLE_DO_PARAM_LIST_ANY \
          ROLE_MAP_REAL_PARAM_TO_NUM(uint32_t, ROLE_ANY_PARAM_UINT32) \
        , ROLE_MAP_REAL_PARAM_TO_NUM(uint32_t*, ROLE_ANY_PARAM_UINT32PTR)


typedef void (*pf_role_constructor)(struct_ROLE *ptr_role);     

typedef enum
{
    ROLE_STATE_DORMANT,                 
    ROLE_STATE_ACTIVE                   
} enum_ROLE_STATE;

#ifdef __cplusplus
}
#endif

#endif 

