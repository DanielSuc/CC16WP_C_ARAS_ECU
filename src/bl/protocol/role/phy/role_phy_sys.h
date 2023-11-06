
#ifndef SRC_ROLE_PHY_SYS_H_
#define SRC_ROLE_PHY_SYS_H_

#if defined(__cplusplus)
extern "C" {
#endif


#if !defined(ROLE_MINIMAL) && defined(IO_TEST_ENABLE)

#define ROLE_DO_PARAM_LIST_SYS \
		, ROLE_MAP_REAL_PARAM_TO_NUM(struct_IO_TEST_SCI_INP*, ROLE_SYS_SCI_INP) \
		, ROLE_MAP_REAL_PARAM_TO_NUM(struct_IO_TEST_SHIFT_REG_INFO*, ROLE_SYS_SHIFT_INFO) \
		, ROLE_MAP_REAL_PARAM_TO_NUM(struct_IO_TEST_SHIFT_REG_WRITE*, ROLE_SYS_SHIFT_REG_WRITE) \
		, ROLE_MAP_REAL_PARAM_TO_NUM(struct_IO_TEST_SPI_INIT*, ROLE_SYS_SPI_INIT_INP) \
		, ROLE_MAP_REAL_PARAM_TO_NUM(struct_IO_TEST_SPI_WRITE*, ROLE_SYS_SPI_WRITE_INP)

#elif !defined(ROLE_MINIMAL) && defined(SPECIFICS_WALLBOX)

#define ROLE_DO_PARAM_LIST_SYS \
		, ROLE_MAP_REAL_PARAM_TO_NUM(struct_CRC_DATA*, ROLE_SYS_CRC_WBX_PARAM)

#else

#define ROLE_DO_PARAM_LIST_SYS

#endif 

#if !defined(ROLE_MINIMAL)
typedef enum
{
	ROLE_SYS_SCI_INP = ROLE_COMPOSE_DO_PARAM_BASE(ROLE_TYPE_SYS),
    ROLE_SYS_SHIFT_INFO,
	ROLE_SYS_SHIFT_REG_WRITE,
	ROLE_SYS_SPI_INIT_INP,
	ROLE_SYS_SPI_WRITE_INP,
	ROLE_SYS_CRC_WBX_PARAM,

} enum_ROLE_SYS_DO_PARAM;
#endif 


#define RESET_REASON_LVD            (0x1u)
#define RESET_REASON_LOC            (0x2u)
#define RESET_REASON_LOL            (0x4u)
#define RESET_REASON_CMU_LOC        (0x8u)
#define RESET_REASON_WDOG           (0x10u)
#define RESET_REASON_EXT_PIN        (0x20u)
#define RESET_REASON_POR            (0x40u)
#define RESET_REASON_JTAG           (0x80u)
#define RESET_REASON_LOCKUP         (0x100u)
#define RESET_REASON_SW             (0x200u)
#define RESET_REASON_MDM_AP         (0x400u)
#define RESET_REASON_STOP_ACK_ERR   (0x800u)

#if (defined(CPU_S32K148) || defined(CPU_S32K146) || defined(CPU_S32K144HFT0VLLT) || defined(CPU_S32K144LFT0MLLT) || defined(CPU_S32K142))

#define PIN_PRACTICLE_MAX_COUNT     (18u)   

#ifdef PORT_INSTANCE_COUNT
#define PORT_PRACTICLE_MAX_COUNT    PORT_INSTANCE_COUNT
#else
#define PORT_PRACTICLE_MAX_COUNT    (5u)
#endif 

#elif defined(CPU_MK10DN512VLL10)

#define PIN_PRACTICLE_MAX_COUNT     PORT_PCR_COUNT
#define PORT_PRACTICLE_MAX_COUNT    (5u)

#else
#error "MCU type unknown. Please add support of new MCU."
#endif 

#define SYS_PORT_PIN_VAL(port_offset, pin_offset, action)   ((uint32_t)( (port_offset << 16u) + (pin_offset << 8u) + action ))

#if defined (__GNUC__)
#define ENABLE_INTERRUPTS() __asm volatile ("cpsie i" : : : "memory");
#else
#define ENABLE_INTERRUPTS() __asm("cpsie i")
#endif

#if defined (__GNUC__)
#define DISABLE_INTERRUPTS() __asm volatile ("cpsid i" : : : "memory");
#else
#define DISABLE_INTERRUPTS() __asm("cpsid i")
#endif

#if !defined(ROLE_MINIMAL) && defined(IO_TEST_ENABLE)
typedef struct
{
    bool        active;
    uint8_t     port;
    uint8_t     bit;
    uint8_t     sign;
    uint8_t     send_delay_active;
    uint32_t    send_delay;
    uint8_t     send_active;
    uint8_t     send_nr;
    bool        tx_set;

    uint8_t		sci_nr;
    uint8_t		baud_nr;
} struct_IO_TEST_SCI_INP;

enum E_SHIFT_OUT
{
    E_SH_DS=0,
    E_SH_OE,
    E_SH_MR,
    E_SH_SH_CP,
    E_SH_ST_CP,
    E_SH_MAX
};

typedef struct
{
    uint8_t port;
    uint8_t pin;
} struct_IO_TEST_SHIFT_REG;

typedef struct
{
    uint8_t pin;
    uint8_t on_off;
} struct_IO_TEST_SHIFT_REG_WRITE;

typedef struct
{
	struct_IO_TEST_SHIFT_REG shift_reg_arr[E_SH_MAX];
    uint8_t cnt;
} struct_IO_TEST_SHIFT_REG_INFO;

enum E_PINS
{
    E_BIT=0,
    E_PORT,
    E_PP_MAX
};

typedef struct
{
    uint8_t port;
    uint8_t pin;
    uint8_t pol;
    uint8_t io_buff[4];
    uint8_t error_byte;
} struct_IO_TEST_SPI_INIT;

typedef struct
{
    uint8_t port;
    uint8_t pin;
    uint8_t io_buff[5];
    uint8_t error_byte;
} struct_IO_TEST_SPI_WRITE;

#define C_SHIFT_BYTES_MAX         4u
#define C_SPI_BAUD_MAX            6u
#define C_SPI_CS_MAX              3u

#endif 


typedef enum
{
    ROLE_SYS_ENABLE_WDOG   = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    0u,     ROLE_ANY_PARAM_UINT32)
  , ROLE_SYS_DISABLE_WDOG  = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    1u,     ROLE_ANY_PARAM_UINT32)
  , ROLE_SYS_RESET_WDOG    = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    2u,     ROLE_ANY_PARAM_UINT32)
  , ROLE_SYS_RESET         = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    3u,     ROLE_ANY_PARAM_UINT32)
  , ROLE_SYS_JUMP_TO_APP   = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    4u,     ROLE_ANY_PARAM_UINT32)
  , ROLE_SYS_RESET_REASON  = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    5u,     ROLE_ANY_PARAM_UINT32PTR)
  , ROLE_SYS_OUT_PIN_STATE = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    6u,     ROLE_ANY_PARAM_UINT32)
  , ROLE_SYS_INP_PIN_STATE = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    7u,     ROLE_ANY_PARAM_UINT32PTR)
  , ROLE_SYS_INP_PIN_STATE_LITE = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    22u,     ROLE_ANY_PARAM_UINT32PTR)
  , ROLE_SYS_GET_CORE_FREQ = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    8u,     ROLE_ANY_PARAM_UINT32PTR)
  , ROLE_SYS_GET_UID       = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    9u,     ROLE_ANY_PARAM_UINT32PTR)

#if !defined(ROLE_MINIMAL) && defined(IO_TEST_ENABLE)
  , ROLE_SYS_SHIFT_INIT    = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    10u,    ROLE_SYS_SHIFT_INFO)
  , ROLE_SYS_SHIFT_WRITE   = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    11u,    ROLE_SYS_SHIFT_REG_WRITE)
  , ROLE_SYS_ADC_INIT      = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    12u,    ROLE_ANY_PARAM_UINT32)
  , ROLE_SYS_ADC_GET_VAL   = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    13u,    ROLE_ANY_PARAM_UINT32PTR)
  , ROLE_SYS_SCI_INIT      = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    14u,    ROLE_SYS_SCI_INP)
  , ROLE_SYS_SPI_INIT      = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    15u,    ROLE_SYS_SPI_INIT_INP)
  , ROLE_SYS_SPI_WRITE     = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    16u,    ROLE_SYS_SPI_WRITE_INP)
#endif 

#if defined(SPECIFICS_WALLBOX)
  , ROLE_SYS_CRC_INIT_WBX  = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    17u,    ROLE_ANY_PARAM_UINT32)
  , ROLE_SYS_CRC_DEINIT_WBX = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,   18u,    ROLE_ANY_PARAM_UINT32)
  , ROLE_SYS_CRC_CALC_WBX  = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    19u,    ROLE_SYS_CRC_WBX_PARAM)
  , ROLE_SYS_INVALIDATE_FLASH_WBX  = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    20u,    ROLE_ANY_PARAM_UINT32)
  , ROLE_SYS_JUMP_TO_APP_WBX   = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    21u,     ROLE_ANY_PARAM_UINT32)
#endif 

  , ROLE_SYS_CHECK_PORT_COUNT  = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    22u,     ROLE_ANY_PARAM_UINT32)
  , ROLE_SYS_CHECK_PIN_COUNT   = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SYS,    23u,     ROLE_ANY_PARAM_UINT32)

} enum_ROLE_SYS_DO_ID;

typedef enum
{
    SYS_PORT_PIN_CLEAR,
    SYS_PORT_PIN_SET,
    SYS_PORT_PIN_TOGGLE
} enum_SYS_PORT_PIN_ACTION;

typedef struct
{
	uint8_t *ptr_data;
	uint32_t size;
	uint32_t result;
} struct_CRC_DATA;


void role_phy_sys_constructor(role_id_t id, pf_role_constructor parent);


#ifdef __cplusplus
}
#endif

#endif 

