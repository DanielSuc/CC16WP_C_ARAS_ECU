
#ifndef SRC_ROLE_PHY_CAN_H_
#define SRC_ROLE_PHY_CAN_H_

#if defined(__cplusplus)
extern "C" {
#endif



#define ROLE_DO_PARAM_LIST_CAN \
        , ROLE_MAP_REAL_PARAM_TO_NUM(struct_ROLE_CAN_MSG*, ROLE_CAN_PARAM_MSG) \
        , ROLE_MAP_REAL_PARAM_TO_NUM(struct_ROLE_CAN_MSG**, ROLE_CAN_PARAM_MSG_2PTR) \
        , ROLE_MAP_REAL_PARAM_TO_NUM(struct_ROLE_CAN_TX_PROP*, ROLE_CAN_PARAM_TX_PROP) \
        , ROLE_MAP_REAL_PARAM_TO_NUM(struct_ROLE_CAN_EXT_BAUD*, ROLE_CAN_PARAM_EXT_BAUD_PARAMS) \
        , ROLE_MAP_REAL_PARAM_TO_NUM(struct_ROLE_CAN_PARAM_CONVERTABLE*, ROLE_CAN_PARAM_CONVERTABLE) \
        , ROLE_MAP_REAL_PARAM_TO_NUM(struct_ROLE_CAN_RX_MB_INFO*, ROLE_CAN_PARAM_RX_MB_INFO)

#define CAN_TX_MB_NOT_INIT          ((uint8_t)(-1))

#if defined(CPU_S32K148)
#define S32K1xx_CAN_INST_COUNT      3

#elif defined(CPU_S32K146)
#define S32K1xx_CAN_INST_COUNT      3

#elif (defined(CPU_S32K144HFT0VLLT) || defined(CPU_S32K144LFT0MLLT))
#define S32K1xx_CAN_INST_COUNT      3

#elif defined(CPU_S32K142)
#define S32K1xx_CAN_INST_COUNT      2

#elif defined(CPU_S32K118)
#define S32K1xx_CAN_INST_COUNT      1

#elif defined(CPU_S32K116)
#define S32K1xx_CAN_INST_COUNT      1

#elif defined(CPU_MK10DN512VLL10)
#define S32K1xx_CAN_INST_COUNT      2

#else
#error "MCU type unknown. Specify the MCU type via SYSTEM_CPU in the makefile."
#endif

#define CAN_BAUD_TOL_TOINT_FACTOR   (100000u)

#define CAN_BAUD_SMP_DEFAULT        ((uint8_t)(88u))
#define CAN_BAUD_SMP_DIFF_MAX       5                   

typedef enum
{
    ROLE_CAN_PARAM_MSG = ROLE_COMPOSE_DO_PARAM_BASE(ROLE_TYPE_CAN),
    ROLE_CAN_PARAM_MSG_2PTR,
    ROLE_CAN_PARAM_TX_PROP,
    ROLE_CAN_PARAM_EXT_BAUD_PARAMS,
    ROLE_CAN_PARAM_CONVERTABLE,
    ROLE_CAN_PARAM_RX_MB_INFO,

} enum_ROLE_CAN_DO_PARAM;

typedef enum
{
    ROLE_CAN_DEACTIVATE = ROLE_COMPOSE_DO_ID(ROLE_TYPE_CAN,    0u, ROLE_ANY_PARAM_UINT32)
    , ROLE_CAN_WRITE_MSG = ROLE_COMPOSE_DO_ID(ROLE_TYPE_CAN,     1u, ROLE_CAN_PARAM_MSG)
    , ROLE_CAN_READ_MSG = ROLE_COMPOSE_DO_ID(ROLE_TYPE_CAN,      2u, ROLE_CAN_PARAM_MSG)
    , ROLE_CAN_READ_MSG_PTR = ROLE_COMPOSE_DO_ID(ROLE_TYPE_CAN,  3u, ROLE_CAN_PARAM_MSG_2PTR)

    , ROLE_CAN_SET_TX_PROP = ROLE_COMPOSE_DO_ID(ROLE_TYPE_CAN,   4u, ROLE_CAN_PARAM_TX_PROP)

#if !defined(ROLE_MINIMAL)
    , ROLE_CAN_SET_BAUDRATE = ROLE_COMPOSE_DO_ID(ROLE_TYPE_CAN,  5u, ROLE_ANY_PARAM_UINT32)
    , ROLE_CAN_SET_EXT_BAUDRATES = ROLE_COMPOSE_DO_ID(ROLE_TYPE_CAN,  6u, ROLE_CAN_PARAM_EXT_BAUD_PARAMS)
    , ROLE_CAN_IS_TX_IDLE = ROLE_COMPOSE_DO_ID(ROLE_TYPE_CAN,  7u, ROLE_ANY_PARAM_UINT32PTR)

#if defined(SPECIFICS_CONNECTED_LOGGER) || defined(SPECIFICS_CONNECTED_WALLBOX)
    , ROLE_CAN_ENABLE_IRQ = ROLE_COMPOSE_DO_ID(ROLE_TYPE_CAN,  8u, ROLE_ANY_PARAM_UINT32)
    , ROLE_CAN_DISABLE_IRQ = ROLE_COMPOSE_DO_ID(ROLE_TYPE_CAN,  9u, ROLE_ANY_PARAM_UINT32)
#endif 

#endif 

    , ROLE_CAN_CALC_EXT_BAUD_PARAMS = ROLE_COMPOSE_DO_ID(ROLE_TYPE_CAN,   10u, ROLE_CAN_PARAM_EXT_BAUD_PARAMS)
    , ROLE_CAN_GET_CLOCK_HZ = ROLE_COMPOSE_DO_ID(ROLE_TYPE_CAN,   11u, ROLE_ANY_PARAM_UINT32PTR)
    , ROLE_CAN_EXT_EE_PARAM_TO_FLEXCAN = ROLE_COMPOSE_DO_ID(ROLE_TYPE_CAN,   12u, ROLE_CAN_PARAM_CONVERTABLE)

#if defined(ROLE_MINIMAL)
    , ROLE_CAN_SIGNAL_RX_MSG = ROLE_COMPOSE_DO_ID(ROLE_TYPE_CAN,  13u, ROLE_ANY_PARAM_UINT32)
    , ROLE_CAN_CONFIG_BL_RX_MB = ROLE_COMPOSE_DO_ID(ROLE_TYPE_CAN,  14u, ROLE_CAN_PARAM_RX_MB_INFO)
    , ROLE_CAN_CONFIG_BL_TX_MB = ROLE_COMPOSE_DO_ID(ROLE_TYPE_CAN,  15u, ROLE_ANY_PARAM_UINT32)
#endif 

} enum_ROLE_CAN_DO_ID;

typedef enum
{
    PHY_CAN_BAUD_10             ,
    PHY_CAN_BAUD_20             ,
    PHY_CAN_BAUD_33             ,
    PHY_CAN_BAUD_50             ,
    PHY_CAN_BAUD_83             ,
    PHY_CAN_BAUD_100            ,
    PHY_CAN_BAUD_125            ,
    PHY_CAN_BAUD_250            ,
    PHY_CAN_BAUD_500            ,
    PHY_CAN_BAUD_800            ,
    PHY_CAN_BAUD_1000           ,

    PHY_CAN_BAUD_ARBR_DUMMY_END ,

    PHY_CAN_BAUD_2000 = PHY_CAN_BAUD_ARBR_DUMMY_END,
    PHY_CAN_BAUD_4000           ,
    PHY_CAN_BAUD_5000           ,

    PHY_CAN_BAUD_DATA_DUMMY_END

} enum_PHY_CAN_BAUDRATE;

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

typedef enum
{
    CAN_FRAME_PHASE_ARBITRATION,
    CAN_FRAME_PHASE_DATA
} enum_PHY_CAN_FRAME_PHASE;

typedef struct
{
    uint32_t msgId;                     
    uint8_t data[64];                   
    uint8_t dataLen;                    
} struct_ROLE_CAN_MSG;    

typedef struct_ROLE_CAN_MSG struct_ROLE_CAN_RXD;
typedef struct_ROLE_CAN_MSG struct_ROLE_CAN_TXD;

typedef struct
{
    uint8_t mb;
    void *ptr_msgbuff;  
} struct_ROLE_CAN_RX_MB_INFO;

typedef struct
{
    struct fd_info
    {
      bool enable;
      uint8_t padding;
      bool enable_brs;
    } fd;

    uint8_t mb_idx;

} struct_ROLE_CAN_TX_PROP;

typedef struct
{
    uint32_t can_clock;
    uint32_t arbitr_baud;
    uint32_t data_baud;
    uint8_t  arbitr_smp;
    uint8_t  data_smp;
} __attribute__((packed)) struct_ROLE_CAN_EXT_BAUD_INPUT;

typedef struct
{
    uint16_t  presc;
    uint8_t   rjw;
    uint8_t   propseg;
    uint8_t   pseg1;
    uint8_t   pseg2;
    uint16_t  tolerance;
    uint8_t   smp;
} __attribute__((packed)) struct_ROLE_CAN_EXT_BAUD_OUTPUT_PHASE;

typedef struct
{
    struct_ROLE_CAN_EXT_BAUD_OUTPUT_PHASE phase[2];
} __attribute__((packed)) struct_ROLE_CAN_EXT_BAUD_OUTPUT;

typedef struct
{
    struct_ROLE_CAN_EXT_BAUD_INPUT inp;
    struct_ROLE_CAN_EXT_BAUD_OUTPUT out;
} __attribute__((packed)) struct_ROLE_CAN_EXT_BAUD;

typedef struct
{
    struct_ROLE_CAN_EXT_BAUD *ptr_can_ext_baud;
    uint32_t can_id;
    uint32_t can_mask;
    uint8_t id_ext;
} __attribute__((packed)) struct_ROLE_CAN_EXT_BAUD_PLUS;

typedef struct
{
    uint32_t propSeg;         
    uint32_t phaseSeg1;       
    uint32_t phaseSeg2;       
    uint32_t preDivider;      
    uint32_t rJumpwidth;      
} __attribute__((packed)) struct_ROLE_CAN_FLEXCAN_PARAMS;

typedef struct
{
    const struct_ROLE_CAN_EXT_BAUD_OUTPUT_PHASE *ptr_inp;
    struct_ROLE_CAN_FLEXCAN_PARAMS *ptr_out;
    uint8_t iphase;
} __attribute__((packed)) struct_ROLE_CAN_PARAM_CONVERTABLE;


void role_phy_can_constructor(role_id_t id, pf_role_constructor parent);


#ifdef __cplusplus
}
#endif


#endif 

