#ifndef SFL_BL_PROTOCOL_H
#define SFL_BL_PROTOCOL_H

#define USE_HAL                         1                   
#define HCS08_MRS_LIBRARY               0                   


#define MCU_TYPE                        E_MCU_TYPE_RH850    
#define BL_CAN_RX_FIFO_BUFFER_LEN       (16u)               

#include "hal_data_types.h"

#if USE_HAL == 1

    #include "sfl_timer.h"
    #include "hal_can.h"
    #include "hal_nvm.h"
    #include "hal_sys.h"

#elif HCS08_MRS_LIBRARY == 1


#endif

#include "sfl_bl_protocol_s32k.h"


#define PAR_OFFSET       2u                 

typedef enum
{
    ERR_OK          = 0u ,                  
    ERR_SPEED       = 1u ,                  
    ERR_RANGE       = 2u ,                  
    ERR_VALUE       = 3u ,                  
    ERR_OVERFLOW    = 4u ,                  
    ERR_MATH        = 5u ,                  
    ERR_ENABLED     = 6u ,                  
    ERR_DISABLED    = 7u ,                  
    ERR_BUSY        = 8u ,                  
    ERR_NOTAVAIL    = 9u ,                  
    ERR_RXEMPTY     = 10u,                  
    ERR_TXFULL      = 11u,                  
    ERR_BUSOFF      = 12u,                  
    ERR_OVERRUN     = 13u,                  
    ERR_FRAMING     = 14u,                  
    ERR_PARITY      = 15u,                  
    ERR_NOISE       = 16u,                  
    ERR_IDLE        = 17u,                  
    ERR_FAULT       = 18u,                  
    ERR_BREAK       = 19u,                  
    ERR_CRC         = 20u,                  
    ERR_ARBITR      = 21u,                  
    ERR_PROTECT     = 22u,                  
    ERR_UNDERFLOW   = 23u,                  
    ERR_UNDERRUN    = 24u,                  
    ERR_COMMON      = 25u,                  
    ERR_LINSYNC     = 26u,                  
    ERR_NOT_OK      = 27u,                  

}enum_MRS_BL_ERROR_CODES_T;

#define C_BL_ID             (0x1FFFFFF0u)   
#define C_BL_ID_EXT         (1u)            
#define C_BL_ID_NIBBLE      (0u)            

#define CHECK_BAUDRATE(x) (((x) & 0xFFu) >= E_BAUD_1MBIT && ((x) & 0xFFu) < E_BAUD_MAX)

#define INV_16(x) (uint16_t)(((~x) << 8) + (x))

#define CHECK_INV_16(x) (((x) & 0xFFu) == (~((x) >> 8) & 0xFFu))

#define SWAP_16(x) (((x) >>  8) & 0xFFu) | (((x) << 8) & 0xFF00u)

#define SWAP_32(x) (((x) >> 24) & 0xFFu) | (((x) << 8) & 0xFF0000u) | (((x) >> 8) & 0xFF00u) | (((x) << 24) & 0xFF000000u)

#define NIBBLE_H_L(a,b) ((a)|((b) << 4) & 0xFFu)

#define CALC_CRC(a,b,x) ((~((((x) >> 24) & 0xFFu)+(((x) >> 16u) & 0xFFu) + (((x) >> 8u) & 0xFFu) + ((x) & 0xFFu) + NIBBLE_H_L((a),(b)))) & 0xFFu)

#define C_BL_ID_CNT (ext_bl_par_data[PAR_BL_ID_EXT1].length + ext_bl_par_data[PAR_BL_ID1].length + ext_bl_par_data[PAR_BL_ID_CRC1].length)

#if USE_HAL == 1

#define BL_EEPROM_GET_DATA(addr,pu8Data,d_size)   hal_nvm_eeprom_read_by_address( addr, d_size, pu8Data)    
#define BL_EEPROM_SET_DATA(addr,pu8Data,d_size)   hal_nvm_eeprom_write_by_address(addr, d_size, pu8Data)    
#define BL_EEPROM_GET_BYTE(addr, pu8Data)         hal_nvm_eeprom_read_by_address( addr, 1u,     pu8Data)    
#define BL_EEPROM_SET_BYTE(addr, pu8Data)         hal_nvm_eeprom_write_by_address(addr, 1u,     pu8Data)    

#define TRIGGER_BL_ACCESS() (void)sfl_timer_set_timestamp(&mgl_ti_access, HAL_PRECISION_1S);                

#define RESET()         0                                                                                   

#elif HCS08_MRS_LIBRARY == 1

#define BL_EEPROM_GET_DATA(addr,pu8Data,d_size)   IEE1_GetData((IEE1_TAddress)addr, pu8Data, d_size)        
#define BL_EEPROM_SET_DATA(addr,pu8Data,d_size)   IEE1_SetData((IEE1_TAddress)addr, pu8Data, d_size)        
#define BL_EEPROM_GET_BYTE(addr,data)             IEE1_GetByte((IEE1_TAddress)addr,data)                    
#define BL_EEPROM_SET_BYTE(addr,data)             IEE1_SetByte((IEE1_TAddress)addr,data)                    

#define TRIGGER_BL_ACCESS() os_timestamp(&mgl_ti_access, OS_1000ms);                                        

#define ILLEGAL_OPCODE 0x9E00                                                                               
#define RESET()  __asm DCW ILLEGAL_OPCODE                                                                   

#endif


typedef enum
{
    E_ACCESS_NONE                = 0u,      
    E_ACCESS_BL                      ,      
    E_ACCESS_CAL                     ,      
    E_ACCESS_USER                    ,      
    E_ACCESS_ALL                     ,      
    E_ACCESS_MAX                            
}t_access;


typedef enum
{
    E_SUB_BL_ADDR                = 0u,      
    E_SUB_PC_CMD                     ,      
    E_SUB_BL_RESP                    ,      
    E_SUB_PC_FLASH_DATA              ,      
    E_SUB_BL_EEP_DATA                ,      
    E_SUB_PC_EEP_DATA                ,      
    E_SUB_BL_HW_RESP                 ,      
    E_SUB_PC_HW_CMD                  ,      
    E_SUB_MAX                               
}t_bl_sub;


typedef enum
{
    E_CHECK_NONE                 = 0u,      
    E_CHECK_SN                       ,      
    E_CHECK_DATA                     ,      
    E_CHECK_MAX                             
}t_check;


typedef enum
{
    E_SEND_SN_SCAN               = 0u,      
    E_SEND_SN_DATA                   ,      
    E_SEND_DATA                      ,      
    E_SEND_SPECIFIC                  ,      
    E_SEND_MAX                              
}t_send;

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

enum E_PROG_STATE
{
    E_PROG_OK                    = 0u,      
    E_PROG_STOP_PARAMETER            ,      
    E_PROG_STOP_RESET                ,      
    E_PROG_STOP_USER                 ,      
    E_PROG_STOP_MASTER               ,      
    E_PROG_MAX                              
};


typedef enum
{
    T_NUMBER                     = 0u,      
    T_ASCII                          ,      
    T_RESERVE                        ,      
    T_MAX                                   

}t_par_datatype;

typedef enum E_BL_MSG
{
    E_BL_SCAN                    =0u,       
    E_BL_ADDRESSING                 ,       
    E_BL_PROG_STOP_MASTER           ,       
    E_BL_PROG_START_MASTER          ,       
    E_BL_PROG_STOP_USER             ,       
    E_BL_PROG_START_USER            ,       
    E_BL_EEPROM_WRITE_BL            ,       
    E_BL_EEPROM_WRITE_CAL           ,       
    E_BL_EEPROM_WRITE_USER          ,       
    E_BL_EEPROM_WRITE_ALL           ,       
    E_BL_EEPROM_WRITE_STOP          ,       
    E_BL_EEPROM_WRITE               ,       
    E_BL_EEPROM_READ                ,       
#ifdef BOOTLOADER_FLASH_ACTIVE
    E_BL_FLASH_REQUEST              ,       
    E_BL_FLASH_CLEAR_APPL           ,       
    E_BL_FLASH_WRITE                ,       
#else
    E_BL_FLASH_REQUEST              ,       
#endif
    E_BL_MAX                                

}t_bl_msg;

enum E_PAR_DATA
{
    PAR_ID                      = 0u,       
    PAR_SERIALNUMBER                ,       
    PAR_PARTNUMBER                  ,       
    PAR_DRAWINGUMBER                ,       
    PAR_NAME                        ,       
    PAR_ORDERNUMBER                 ,       
    PAR_TEST_DATE                   ,       
    PAR_HW_VERSION                  ,       
    PAR_RESETCOUNTER                ,       
    PAR_LIB_VERSION                 ,       
    PAR_RESETREASON_LVD             ,       
    PAR_RESETREASON_LOC             ,       
    PAR_RESETREASON_ILAD            ,       
    PAR_RESETREASON_ILOP            ,       
    PAR_RESETREASON_COP             ,       
    PAR_MCU_TYPE                    ,       
    PAR_HW_CAN_ACTIVE               ,       
    PAR_RESERVE1                    ,       
    PAR_BL_VERSION                  ,       
    PAR_PROG_STATE                  ,       
    PAR_PORTBYTE1                   ,       
    PAR_PORTBYTE2                   ,       
    PAR_BL_BAUDRATE1                ,       
    PAR_BL_BAUDRATE2                ,       
    PAR_BL_ID_EXT1                  ,       
    PAR_BL_ID1                      ,       
    PAR_BL_ID_CRC1                  ,       
    PAR_BL_ID_EXT2                  ,       
    PAR_BL_ID2                      ,       
    PAR_BL_ID_CRC2                  ,       
    PAR_SW_VERSION                  ,       
    PAR_MODULENAME                  ,       
    PAR_BL_CANBUS                   ,       
    PAR_WD_TIMEOUT                  ,       
    PAR_RESERVE2                    ,       
    PAR_MAX                                 
};

enum E_MCU_TYPE
{
    E_MCU_TYPE_NONE = 0,                    
    E_MCU_TYPE_HCS08,                       
    E_MCU_TYPE_HCS12,                       
    E_MCU_TYPE_HCS08DZ128,                  
    E_MCU_TYPE_MK10xx,                      
    E_MCU_TYPE_RH850                        
};

enum E_RESET_TYPE
{
    E_RESET_TYPE_NONE = 0,                  
    E_RESET_TYPE_BL,                        
    E_RESET_TYPE_APP                        
};






typedef struct
{
        uint32_t    id;                     
        uint8_t     dlc;                    
        uint8_t     data[8];                
        uint16_t    can_timestamp;          

}struct_bl_can_frame;

typedef struct
{
    uint8_t write_ptr;                      
    uint8_t read_ptr;                       
    uint8_t overrun;                        
    struct_bl_can_frame buffer[BL_CAN_RX_FIFO_BUFFER_LEN]; 
} struct_bl_can_rx_fifo;


struct st_bl_msg
{
    t_bl_sub d_rx_sub;                      
    uint8_t  d_in1[2];                      
    t_check  d_check;                       
    uint8_t  d_rx_dlc;                      
    uint8_t  d_in2[6];                      
    uint8_t (*d_ptr_callback)(uint8_t, struct_bl_can_frame*, struct_bl_can_frame*);     
    t_send   d_send;                        
    t_bl_sub d_tx_sub;                      
    uint8_t  d_tx_dlc;                      
    uint8_t  d_send_data[8];                
};


struct st_ascii
{
    uint8_t  par_name;                      
    uint8_t  str[30];                       
};

struct struc_par_data
{
    uint8_t length;                         
    t_par_datatype data_type;               
    uint32_t val_default;                   
};

extern uint8_t ext_bl_flasher_active;
extern uint32_t ext_bl_sub_fr[E_SUB_MAX];
extern uint8_t ext_bl_par_addr[PAR_MAX];
extern const struct struc_par_data ext_bl_par_data[PAR_MAX];
extern uint8_t ext_bl_access;
extern uint8_t ext_flag_trigger_app_reset;


#if USE_HAL == 1

    void sfl_bl_init(struct_hal_can_handle* handle);

#elif HCS08_MRS_LIBRARY == 1

    void sfl_bl_init(void);

#endif

 void sfl_bl_cyclic(void);

uint8_t sfl_bl_set_eeprom_access(uint8_t p_step, struct_bl_can_frame* p_msg_in, struct_bl_can_frame* p_msg_out);

 uint8_t sfl_bl_can_read_eeprom(uint8_t p_step, struct_bl_can_frame* p_msg_in, struct_bl_can_frame* p_msg_out);

 uint8_t sfl_bl_can_write_eeprom(uint8_t p_step, struct_bl_can_frame* p_msg_in, struct_bl_can_frame* p_msg_out);

uint8_t sfl_bl_set_program_state(uint8_t p_step, struct_bl_can_frame* p_msg_in, struct_bl_can_frame* p_msg_out);

uint8_t* sfl_bl_get_ascii_ptr(uint8_t p_index);

uint8_t sfl_bl_check_port_bit(uint8_t p_byte);

uint8_t sfl_bl_write_default_value(uint8_t i);

 uint8_t sfl_bl_check_crc(uint8_t *p_data, uint8_t p_start, uint8_t p_cnt);

uint8_t sfl_bl_can_send(uint32_t p_id, uint8_t p_dlc, uint8_t p_b0, uint8_t p_b1, uint8_t p_b2, uint8_t p_b3, uint8_t p_b4, uint8_t p_b5, uint8_t p_b6, uint8_t p_b7);

void sfl_bl_can_receive(struct_bl_can_frame* msg);

#if USE_HAL == 1

    void sfl_bl_can_receive_pre(struct_hal_can_frame_t* ptr_can_msg);

#elif HCS08_MRS_LIBRARY == 1

    void sfl_bl_can_receive_pre(bios_can_msg_typ* msg);

#endif

uint8_t sfl_bl_set_flasher_state(uint8_t p_step, struct_bl_can_frame* p_msg_in, struct_bl_can_frame* p_msg_out);

void sfl_bl_change_can_baudrate(struct_hal_can_handle* handle, enum_bl_baudrate_t baudrate);

void sfl_bl_get_hw_version(uint8_t *hw_version);

#endif 

