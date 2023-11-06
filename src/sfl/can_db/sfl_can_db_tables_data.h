#ifndef SFL_CAN_DB_TABLES_DATA_H
#define SFL_CAN_DB_TABLES_DATA_H

#include "hal_data_types.h"
#include "hal_can.h"
#include "can_db_tables.h"
#include "sfl_timer.h"
#include "string.h"
#include "sfl_fifo.h"
#include "flexcan_driver.h"

typedef struct
{
    uint32_t can_clock;
    uint32_t arbitr_baud;
    uint32_t data_baud;
    uint8_t  arbitr_smp;
    uint8_t  data_smp;
} __attribute__((packed)) struct_ROLE_CAN_EXT_BAUD_INPUT_DEMO;

typedef struct
{
    uint16_t  presc;
    uint8_t   rjw;
    uint8_t   propseg;
    uint8_t   pseg1;
    uint8_t   pseg2;
    uint16_t  tolerance;
    uint8_t   smp;
} __attribute__((packed)) struct_ROLE_CAN_EXT_BAUD_OUTPUT_PHASE_DEMO;

typedef struct
{
    struct_ROLE_CAN_EXT_BAUD_OUTPUT_PHASE_DEMO phase[2];
} __attribute__((packed)) struct_ROLE_CAN_EXT_BAUD_OUTPUT_DEMO;

typedef struct
{
    struct_ROLE_CAN_EXT_BAUD_INPUT_DEMO inp;
    struct_ROLE_CAN_EXT_BAUD_OUTPUT_DEMO out;
} __attribute__((packed)) struct_ROLE_CAN_EXT_BAUD_DEMO;

typedef struct
{
    uint8_t                  enable;
    struct_ROLE_CAN_EXT_BAUD_DEMO baud;
    uint8_t                  crc8;
} __attribute__((packed)) struct_EE_CAN_EXT_DEMO;

typedef enum
{
    CAN_FD_FRAME_PHASE_ARBITRATION,
    CAN_FD_FRAME_PHASE_DATA
} enum_PHY_CAN_FRAME_PHASE_DEMO;

#define dyn_CAN_DP_MAX                  can_db.DP_MAX
#define dyn_CAN_BUS_MAX                 can_db.BUS_MAX
#define dyn_CAN_BLOCK_MAX               can_db.BLOCK_MAX
#define dyn_CAN_BAUDRATE                can_db.BAUDRATE
#define dyn_CAN_BUS_1                   can_db.BUS_1
#define dyn_OS_PORT_INPUT_PIN_MAX       os_io->PORT_INPUT_PIN_MAX
#define dyn_OS_PORT_PIN_MAX             os_io->PORT_PIN_MAX
#define dyn_OS_ANALOG_PIN_MAX           os_io->PORT_ANALOG_PIN_MAX
#define BIOS_CAN_BAUDRATE_NAME_LEN      10


typedef enum
{
    NONE                      =23,       
    BIOS_CAN_EXT_BAUDRATE     =0,        
    BIOS_CAN_10KBIT           =8,
    BIOS_CAN_20KBIT           =7,
    BIOS_CAN_33_33KBIT        =11,
    BIOS_CAN_50KBIT           =6,
    BIOS_CAN_83_33KBIT        =10,
    BIOS_CAN_100KBIT          =9,
    BIOS_CAN_125KBIT          =5,
    BIOS_CAN_250KBIT          =4,
    BIOS_CAN_500KBIT          =3,
    BIOS_CAN_800KBIT          =2,
    BIOS_CAN_1MBIT            =1,
    BIOS_CAN_FD_START_ID      =30,       
    BIOS_CAN_FD_EXT_BAUDRATE  =31,       
    BIOS_CAN_FD_125_250       =32,       
    BIOS_CAN_FD_125_500       =33,       
    BIOS_CAN_FD_125_800       =34,       
    BIOS_CAN_FD_125_1000      =35,       
    BIOS_CAN_FD_125_2000      =36,       
    BIOS_CAN_FD_125_3000      =37,       
    BIOS_CAN_FD_125_4000      =38,       
    BIOS_CAN_FD_125_5000      =39,       
    BIOS_CAN_FD_250_500       =40,       
    BIOS_CAN_FD_250_800       =41,       
    BIOS_CAN_FD_250_1000      =42,       
    BIOS_CAN_FD_250_2000      =43,       
    BIOS_CAN_FD_250_3000      =44,       
    BIOS_CAN_FD_250_4000      =45,       
    BIOS_CAN_FD_250_5000      =46,       
    BIOS_CAN_FD_500_800       =47,       
    BIOS_CAN_FD_500_1000      =48,       
    BIOS_CAN_FD_500_2000      =49,       
    BIOS_CAN_FD_500_3000      =50,       
    BIOS_CAN_FD_500_4000      =51,       
    BIOS_CAN_FD_500_5000      =52,       
    BIOS_CAN_FD_800_1000      =53,       
    BIOS_CAN_FD_800_2000      =54,       
    BIOS_CAN_FD_800_3000      =55,       
    BIOS_CAN_FD_800_4000      =56,       
    BIOS_CAN_FD_800_5000      =57,       
    BIOS_CAN_FD_1000_2000     =58,       
    BIOS_CAN_FD_1000_3000     =59,       
    BIOS_CAN_FD_1000_4000     =60,       
    BIOS_CAN_FD_1000_5000     =61,       
    BIOS_CAN_BAUD_MAX                    
}enum_BIOS_CAN_FD_BAUDRATE;


#define DF_INTEL                        0
#define DF_MOTOROLA                     1

#define CAN_HANDLE_MAX_NR               3

#define SFL_CAN_CLASSIC_PAYLOAD_SIZE 8
#define SFL_CAN_FD_PAYLOAD_SIZE 64

#define BIOS_CAN_ID_NORM_A_AND_B  0 
#define BIOS_CAN_ID_NORM_A_EXT_B  1 
#define BIOS_CAN_ID_EXT_A_AND_B   2 
#define BIOS_CAN_ID_ALL_CLOSED    3 
#define BIOS_CAN_ID_ALL_OPEN      4 

#define MACRO_DEFINE_TO_STR(arg) #arg


typedef enum
{
    STAND_ID  = 0,  
    EXT_ID,          
    NO_ID           
}enum_type_can_id;


typedef struct
{
    struct_hal_can_header_t    header;
#if CAN_FD_GLOBAL_ENABLE == 1
    uint8_t                 data[SFL_CAN_FD_PAYLOAD_SIZE];
#else
    uint8_t                 data[SFL_CAN_CLASSIC_PAYLOAD_SIZE];
#endif
} struct_sfl_can_fifo_frame;

typedef struct
{
    uint32_t id;
    uint32_t timestamp;
    uint16_t id_ext    :1;
    uint16_t remote_tx :1;
    uint8_t data[64];
    uint8_t len;
    uint8_t prty;
    uint8_t can_fd;
    uint8_t can_fd_brs;

} bios_can_msg_typ;

typedef struct
{
    uint8_t name[BIOS_CAN_BAUDRATE_NAME_LEN+1];
    uint8_t sj;
    uint8_t pre;
    uint8_t t_seg1;
    uint8_t t_seg2;
    uint8_t clk_src;
    uint8_t prop;
} bios_can_baudrate_typ;

typedef struct
{
  uint8_t bus_id_in;
  uint8_t bus_id_out;

} can_gateway_db_const_typ;

#define NUMBER_OF_CAN_FILTERS	2u
#define NUMBER_OF_CAN_MASKS		2u

#if ((NUMBER_OF_CAN_FILTERS > 2u) || (NUMBER_OF_CAN_MASKS > 2u))
#error "Max number of available  CAN filters and/or masks is 2 per CAN bus"
#endif

typedef struct
{
    uint32_t  filter[NUMBER_OF_CAN_FILTERS];	
    uint32_t  mask[NUMBER_OF_CAN_MASKS];        
    uint8_t   mask_division;    				

} can_db_filter_typ;

typedef struct
{
    uint16_t   DP_MAX;
    uint8_t    BUS_MAX;
    uint16_t   BLOCK_MAX;
    uint8_t    GATEWAY_DB_MAX;  
    uint16_t   BAUDRATE;
    uint8_t    BUS_1;
    uint8_t    user_filter_active;
    uint8_t    sa_active;         
    uint8_t    sa_db;             
    uint8_t    sa_val;            
    uint16_t   sa_db_rx;          
    uint16_t   sa_val_rx;         
    can_db_filter_typ f_set[5];

} can_db_typ;

typedef struct {
    uint8_t hw_module_id;                   
    uint8_t hw_module_active;               
    uint8_t listen_only_mode_active;        
    uint8_t bios_baudrate_id;               
    uint8_t gw_input;                       
    bios_can_baudrate_typ baudrate;         
    bios_can_baudrate_typ baudrate_fd_data; 
    uint8_t can_fd_capability;              
} can_bus_db_const_typ;

typedef struct {
    uint8_t  bus_id;                  
    uint32_t can_id;                  
    uint8_t  can_id_ext;              
    uint8_t  can_fd_brs;              
    uint32_t zykluszeit_ms_max;       
    uint32_t zykluszeit_ms_min;       
    uint8_t  msg_len_dlc;             
    uint8_t  tx;                    
    uint8_t  can_bus_gw;              
    uint32_t can_id_mask;             
    uint8_t  mux_start;               
    uint8_t  mux_length;              
    uint8_t  mux_val;                 
    uint32_t timeout_ms;              

} can_block_db_const_typ;

typedef struct {
    can_block_id nr_can_block;        
    uint16_t  pos_bit_0;              
    uint16_t  bit_laenge;             
    uint8_t  datentyp;                
    uint8_t  data_format;
    uint32_t init_value;              

} can_datenpunkt_db_const_typ;

typedef struct {
#if CAN_FD_GLOBAL_ENABLE == 1
    uint8_t  last_data[SFL_CAN_FD_PAYLOAD_SIZE];		
#else
    uint8_t  last_data[SFL_CAN_CLASSIC_PAYLOAD_SIZE];	
#endif
    uint32_t time_stamp_read;
    uint32_t time_stamp_write;
    uint32_t time_stamp_transmit;
    uint8_t  received         :1;
    uint8_t  expired          :1;
    uint8_t  failsafe         :1;
    uint8_t  transmit         :1; 
    uint8_t  transmit_stop    :1; 
    boolean  stop_gw_known_ids:1; 
    bios_can_msg_typ msg;

} can_block_db_ram_typ;

typedef struct
{
    uint32_t rx_fifo_size;
    uint32_t tx_fifo_size;
    struct_sfl_can_fifo_frame* ptr_tx_fifo_buffer;
    struct_sfl_can_fifo_frame* ptr_rx_fifo_buffer;
    SFL_FIFO_CONFIG_TYPE* tx_fifo_config;
    SFL_FIFO_CONFIG_TYPE* rx_fifo_config;
} struct_can_fifo_config;

#ifndef MAX_CAN_DEFAULT_SET
#define MAX_CAN_DEFAULT_SET     3       
#endif

#ifndef CAN0_TX_FIFO_SIZE
#define CAN0_TX_FIFO_SIZE 5        
#endif

#ifndef CAN1_TX_FIFO_SIZE
#define CAN1_TX_FIFO_SIZE 5        
#endif

#ifndef CAN2_TX_FIFO_SIZE
#define CAN2_TX_FIFO_SIZE 5        
#endif

#ifndef CAN0_RX_FIFO_SIZE
#define CAN0_RX_FIFO_SIZE 5        
#endif

#ifndef CAN1_RX_FIFO_SIZE
#define CAN1_RX_FIFO_SIZE 5        
#endif

#ifndef CAN2_RX_FIFO_SIZE
#define CAN2_RX_FIFO_SIZE 5        
#endif

extern struct_sfl_can_fifo_frame fifo_msg_tx_can0[CAN0_TX_FIFO_SIZE];
extern struct_sfl_can_fifo_frame fifo_msg_tx_can1[CAN1_TX_FIFO_SIZE];
extern struct_sfl_can_fifo_frame fifo_msg_tx_can2[CAN2_TX_FIFO_SIZE];

extern struct_sfl_can_fifo_frame fifo_msg_rx_can0[CAN0_RX_FIFO_SIZE];
extern struct_sfl_can_fifo_frame fifo_msg_rx_can1[CAN1_RX_FIFO_SIZE];
extern struct_sfl_can_fifo_frame fifo_msg_rx_can2[CAN2_RX_FIFO_SIZE];

extern SFL_FIFO_CONFIG_TYPE fifo_tx_can0_config_default;
extern SFL_FIFO_CONFIG_TYPE fifo_tx_can1_config_default;
extern SFL_FIFO_CONFIG_TYPE fifo_tx_can2_config_default;

extern SFL_FIFO_CONFIG_TYPE fifo_rx_can0_config_default;
extern SFL_FIFO_CONFIG_TYPE fifo_rx_can1_config_default;
extern SFL_FIFO_CONFIG_TYPE fifo_rx_can2_config_default;

extern struct_can_fifo_config can_fifo_config_default[];

extern struct_can_fifo_config* can_fifo_config_actual[MAX_CAN_DEFAULT_SET];

extern uint8_t ext_sfl_can_stop_gw_unknown_ids[CAN_BUS_MAX];

extern struct_hal_can_handle can_handle[CAN_HANDLE_MAX_NR];


void sfl_can_db_tables_data_init( void );

uint32_t calculate_can_baudrate( struct_ROLE_CAN_EXT_BAUD_DEMO* ptr_io );

uint32_t set_can_baudrate_timing( hal_can_time_segment *ptr_tseg, const struct_ROLE_CAN_EXT_BAUD_OUTPUT_PHASE_DEMO *params, enum_PHY_CAN_FRAME_PHASE_DEMO iphase );

void main_here();

uint8_t sfl_can_db_tables_convert_baud( uint8_t const baudrate, uint8_t ident );

void sfl_can_db_tables_data_init_baudrate( struct_hal_can_handle can_bus_handle, const can_bus_db_const_typ can_config );

void sfl_can_db_init( can_db_filter_typ* can_db_filter_config );

void sfl_can_db_fifo_init( void );

void sfl_can_rx_int_enable( uint8_t instance, uint32_t buffIdx );

void sfl_can_get_handle( uint8_t interface, struct_hal_can_handle* ptr_handle );

void sfl_can_db_config_mb_set_filter_mask( struct_hal_can_handle* const can_handle, const can_db_filter_typ* can_db_filter_config, const uint8_t id_type_mb[] );

uint8_t sfl_can_db_get_fifo_size( uint8_t bus_id, uint8_t tx_or_rx );

uint8_t sfl_can_db_tables_convert_baud( uint8_t const baudrate, uint8_t ident );

#endif

