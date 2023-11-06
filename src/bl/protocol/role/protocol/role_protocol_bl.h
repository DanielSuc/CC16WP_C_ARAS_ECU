
#ifndef SRC_ROLE_BL_PROTOCOL_H_
#define SRC_ROLE_BL_PROTOCOL_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include "ee_helper.h"

typedef void (*bl_protocol_prereset_callback_t)(void);

#define ROLE_DO_PARAM_LIST_BL_PROTOCOL \
        , ROLE_MAP_REAL_PARAM_TO_NUM(struct_EE_CAN_EXT*, ROLE_BL_PROTOCOL_PARAM_CAN_EXT_CALC_STORE) \
        , ROLE_MAP_REAL_PARAM_TO_NUM(const struct_hal_sys_app_header_t**, ROLE_BL_PROTOCOL_PARAM_APP_HEADER_PTR) \
        , ROLE_MAP_REAL_PARAM_TO_NUM(bl_protocol_prereset_callback_t, ROLE_BL_PROTOCOL_PRE_RESET_CALLBACK) \
		, ROLE_MAP_REAL_PARAM_TO_NUM(struct_flash_handler_data**, ROLE_BL_PROTOCOL_FLASH_DATA_HANDLE_PTR) \
        , ROLE_MAP_REAL_PARAM_TO_NUM(struct_signature_t*, ROLE_BL_PROTOCOL_PARAM_INIT_RSA_SIGNATURE) \
		, ROLE_MAP_REAL_PARAM_TO_NUM(struct_data_t*, ROLE_BL_PROTOCOL_PARAM_UPDATE_RSA_SIGNATURE)



typedef enum
{
    ROLE_BL_PROTOCOL_PARAM_CAN_EXT_CALC_STORE = ROLE_COMPOSE_DO_PARAM_BASE(ROLE_TYPE_PROTOCOL_BOOTLOADER),
    ROLE_BL_PROTOCOL_PARAM_APP_HEADER_PTR,
    ROLE_BL_PROTOCOL_PRE_RESET_CALLBACK,
	ROLE_BL_PROTOCOL_FLASH_DATA_HANDLE_PTR,
    ROLE_BL_PROTOCOL_PARAM_INIT_RSA_SIGNATURE,
	ROLE_BL_PROTOCOL_PARAM_UPDATE_RSA_SIGNATURE

} enum_ROLE_BL_PROTOCOL_DO_PARAM;

typedef enum
{
    ROLE_BL_PROTOCOL_CAN_EXT_UPDATE = ROLE_COMPOSE_DO_ID(ROLE_TYPE_PROTOCOL_BOOTLOADER, 0u, ROLE_BL_PROTOCOL_PARAM_CAN_EXT_CALC_STORE),

    ROLE_BL_PROTOCOL_GET_APP_HEADER_PTR = ROLE_COMPOSE_DO_ID(ROLE_TYPE_PROTOCOL_BOOTLOADER, 1u, ROLE_BL_PROTOCOL_PARAM_APP_HEADER_PTR),
    ROLE_BL_PROTOCOL_GET_BL_ACCESS_KEY = ROLE_COMPOSE_DO_ID(ROLE_TYPE_PROTOCOL_BOOTLOADER, 2u, ROLE_ANY_PARAM_UINT32PTR),
    ROLE_BL_PROTOCOL_SET_BL_ACCESS_KEY = ROLE_COMPOSE_DO_ID(ROLE_TYPE_PROTOCOL_BOOTLOADER, 3u, ROLE_ANY_PARAM_UINT32),

    ROLE_BL_PROTOCOL_SET_RESET_CALLBACK = ROLE_COMPOSE_DO_ID(ROLE_TYPE_PROTOCOL_BOOTLOADER, 4u, ROLE_BL_PROTOCOL_PRE_RESET_CALLBACK),

    ROLE_BL_PROTOCOL_GET_APP_STARTUP_DELAY = ROLE_COMPOSE_DO_ID(ROLE_TYPE_PROTOCOL_BOOTLOADER, 5u, ROLE_ANY_PARAM_UINT32PTR),
    ROLE_BL_PROTOCOL_SET_APP_STARTUP_DELAY = ROLE_COMPOSE_DO_ID(ROLE_TYPE_PROTOCOL_BOOTLOADER, 6u, ROLE_ANY_PARAM_UINT32PTR),

#if defined(SPECIFICS_CONNECTED_LOGGER) || defined(SPECIFICS_CONNECTED_WALLBOX)
#if !defined(ROLE_MINIMAL)

	ROLE_BL_PROTOCOL_GET_FLASH_DATA_HANDLE_PTR = ROLE_COMPOSE_DO_ID(ROLE_TYPE_PROTOCOL_BOOTLOADER, 7u, ROLE_BL_PROTOCOL_FLASH_DATA_HANDLE_PTR),
	ROLE_BL_PROTOCOL_FLASH_DATA_FROM_HANDLE = ROLE_COMPOSE_DO_ID(ROLE_TYPE_PROTOCOL_BOOTLOADER, 8u, ROLE_ANY_PARAM_UINT32),

#else

	ROLE_BL_PROTOCOL_INIT_RSA_SIGNATURE = ROLE_COMPOSE_DO_ID(ROLE_TYPE_PROTOCOL_BOOTLOADER, 9u, ROLE_BL_PROTOCOL_PARAM_INIT_RSA_SIGNATURE),
	ROLE_BL_PROTOCOL_UPDATE_RSA_SIGNATURE = ROLE_COMPOSE_DO_ID(ROLE_TYPE_PROTOCOL_BOOTLOADER, 10u, ROLE_BL_PROTOCOL_PARAM_UPDATE_RSA_SIGNATURE),
    ROLE_BL_PROTOCOL_FINALIZE_RSA_SIGNATURE = ROLE_COMPOSE_DO_ID(ROLE_TYPE_PROTOCOL_BOOTLOADER, 11u, ROLE_ANY_PARAM_UINT32),

#endif 
#endif 

    ROLE_BL_PROTOCOL_SET_NOTIFICATION = ROLE_COMPOSE_DO_ID(ROLE_TYPE_PROTOCOL_BOOTLOADER, 12u, ROLE_ANY_PARAM_UINT32),


} enum_ROLE_BL_PROTOCOL_DO_ID;


#define CHECK_BAUDRATE(x) (((x) & 0xFFu) >= E_BAUD_1MBIT && ((x) & 0xFFu) < E_BAUD_MAX)

#define CALIBR_EE_TABLE_START_ADDR	(0x220u)
#define CALIBR_EE_TABLE_MODULE_ADDR	CALIBR_EE_TABLE_START_ADDR
#define CALIBR_EE_TABLE_DATA_ADDR	(CALIBR_EE_TABLE_MODULE_ADDR + 2u)
#define CALIBR_EE_TABLE_END_ADDR    (0x342u)

#define SIGNATURE_LENGTH            256u 

#define RESET_MAX_CNT               (50u)


#define HAL_SYS_APP_HEADER_VERSION              (1u)            

#define HAL_SYS_APP_HEADER_KEY                  (0x12345678u)   

#define HAL_SYS_BOOTLOADER_ACCESS_KEY           (0x4D525321u)   
#define HAL_SYS_BOOTLOADER_APP_START_KEY        (0x07412807u)   
#define HAL_SYS_BOOTLOADER_ACCESS_KEY_UPDATE    (0x1AF7356B)    

#define REQUIRED_APP_HEADER_VERSION             (1u)            


#define BL_STARTUP_TIME_MIN                     (10u)           
#define BL_STARTUP_TIME_MAX                     (1000u)         
#define BL_STARTUP_TIME_DEFAULT                 (1000u)         

#define FLASH_BLOCK_OFFSET                      (0u)            

#define FLASH_APPL_HEADER_OFFSET                (0x8u)          
#define FLASH_APPL_HEADER_LENGTH                (0x1000u)      

extern uint32_t __APP_HEADER_ADDR;

#define FLASH_APPL_START_ALL                    ((uint32_t)((uint8_t*)&__APP_HEADER_ADDR))  

#if (defined(CUSTOMIZE_FLASH_END_ADDRESS) && (CUSTOMIZE_FLASH_END_ADDRESS < 0x11000)) 
#error "CUSTOMIZE_FLASH_END_ADDRESS overlaps with either bootloader or application header regions. Please correct"
#endif 


#if defined(CPU_S32K148)

#if defined(CUSTOMIZE_FLASH_END_ADDRESS)
#define FLASH_APPL_END_ALL                      CUSTOMIZE_FLASH_END_ADDRESS     
#else
#define FLASH_APPL_END_ALL                      (0x17FFFFu)     
#endif 

#define FLASH_SECTOR_SIZE                       (4096u)         
#define FLASH_BLOCK_AVAILABLE                   (uint8_t)(0xFFu)    

#elif defined(CPU_S32K146)

#if defined(CUSTOMIZE_FLASH_END_ADDRESS)
#define FLASH_APPL_END_ALL                      CUSTOMIZE_FLASH_END_ADDRESS     
#else
#define FLASH_APPL_END_ALL                      (0xFFFFFu)      
#endif 

#define FLASH_SECTOR_SIZE                       (4096u)         
#define FLASH_BLOCK_AVAILABLE                   (uint8_t)(256u)    

#elif (defined(CPU_S32K144HFT0VLLT) || defined(CPU_S32K144LFT0MLLT))

#if defined(CUSTOMIZE_FLASH_END_ADDRESS)
#define FLASH_APPL_END_ALL                      CUSTOMIZE_FLASH_END_ADDRESS     
#else
#define FLASH_APPL_END_ALL                      (0x7FFFFu)      
#endif 

#if defined(SPECIFICS_CONNECTED_LOGGER) || defined(SPECIFICS_CONNECTED_WALLBOX)
#define SPI_PARTITION_BIN_SIZE                  (0x7FFFFu)
#endif 

#define FLASH_SECTOR_SIZE                       (4096u)         
#define FLASH_BLOCK_AVAILABLE                   (uint8_t)(128u)    

#elif defined(CPU_S32K142)

#if defined(CUSTOMIZE_FLASH_END_ADDRESS)
#define FLASH_APPL_END_ALL                      CUSTOMIZE_FLASH_END_ADDRESS     
#else
#define FLASH_APPL_END_ALL                      (0x3FFFFu)      
#endif 

#define FLASH_SECTOR_SIZE                       (2048u)         
#define FLASH_BLOCK_AVAILABLE                   (uint8_t)(128u)    

#elif defined(CPU_MK10DN512VLL10)

#if defined(CUSTOMIZE_FLASH_END_ADDRESS)
#define FLASH_APPL_END_ALL                      CUSTOMIZE_FLASH_END_ADDRESS     
#else
#define FLASH_APPL_END_ALL                      (0x78000u)      
#endif 

#define FLASH_SECTOR_SIZE                       (2048u)         
#define FLASH_BLOCK_AVAILABLE                   (uint8_t)(256u - (32u + 16u))    

#else
#error "MCU type unknown. Specify the MCU type via SYSTEM_CPU in the makefile."
#endif

#if !defined(BL_UPDATE_APP)
#define FLASH_APPL_START                        ((uint32_t)((uint8_t*)&__APP_HEADER_ADDR) + FLASH_APPL_HEADER_LENGTH) 
#define FLASH_APPL_SIZE                         ((uint32_t)(FLASH_APPL_END_ALL - FLASH_APPL_START))
#define FLASH_APPL_HEADER_START                 FLASH_APPL_START_ALL

#define FLASH_UPDATE_APPL_START_ALL             (uint32_t)( ((FLASH_APPL_END_ALL + 1u) + FLASH_APPL_START_ALL) / 2)      
#define FLASH_UPDATE_APPL_END_ALL               FLASH_APPL_END_ALL

#define FLASH_UPDATE_APPL_HEADER_START          FLASH_UPDATE_APPL_START_ALL                 
#define FLASH_UPDATE_APPL_START                 (FLASH_UPDATE_APPL_START_ALL + FLASH_APPL_HEADER_LENGTH)    

#else
#define FLASH_APPL_START                        ((uint32_t)0u) 
#define FLASH_APPL_SIZE                         ((uint32_t)0x10000u)
#define FLASH_APPL_HEADER_START                 FLASH_APPL_START_ALL

#define FLASH_UPDATE_APPL_START_ALL             (uint32_t)( ((FLASH_APPL_END_ALL + 1u) + FLASH_APPL_START_ALL) / 2)      
#define FLASH_UPDATE_APPL_END_ALL               FLASH_APPL_END_ALL

#define FLASH_UPDATE_APPL_HEADER_START          FLASH_UPDATE_APPL_START_ALL                 
#define FLASH_UPDATE_APPL_START                 (FLASH_UPDATE_APPL_START_ALL + FLASH_APPL_HEADER_LENGTH)    

#endif 


#define CRC32_OK                                0u              
#define CRC32_ERROR                             1u              

#define FLASH_BLOCKSIZE                         FLASH_SECTOR_SIZE                         

#define FLASH_PAGESIZE                          (0x100u)        

#define CHECK_INV_16(x)                         (((x) & 0xFFu) == (~((x) >> 8) & 0xFFu))    

#define EE_FACTORY_RESET_CNT_VAL                (10u)
#define EE_FACTORY_RESET_CLEAR_TIME_MS          (6000u)


#if !defined(BL_UPDATE_APP)
    #define SW_VERSION_NAME_DEFAULT "S32K BL DEFAULT     "
#else
    #define SW_VERSION_NAME_DEFAULT "S32K BL UPDATER "
#endif 



#define BL_NOTIFICATION_SPI_MEMORY_UNKNOWN              (uint32_t)(1u << 0)
#define BL_NOTIFICATION_SPI_PARTITION_REINITIALIZED     (uint32_t)(1u << 1)
#define BL_NOTIFICATION_APP_IS_RUNNING                  (uint32_t)(1u << 2)
#define BL_NOTIFICATION_APP_IS_STANADLONE               (uint32_t)(1u << 3)
#define BL_NOTIFICATION_BL_REFORMATTED_EEPROM           (uint32_t)(1u << 4)
#define BL_NOTIFICATION_APP_EEPROM_BLOCKED              (uint32_t)(1u << 5)



typedef enum
{
    STATE_SIGN_SHA_INIT = 0u,   
    STATE_SIGN_SHA_UPDATE,      
    STATE_SIGN_VERIFY           
} enum_SIGN_STATE;

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
    E_ACCESS_NONE                = 0u,
    E_ACCESS_BL                      ,
    E_ACCESS_CAL                     ,
    E_ACCESS_USER                    ,
    E_ACCESS_ALL                     ,
    E_ACCESS_MAX
}t_access;

typedef enum
{
    E_BL_SCAN                    =0u,
    E_BL_ADDRESSING                 ,
    E_BL_ADDRESSING_NEW             ,
    E_BL_PROG_STOP_MASTER           ,
    E_BL_PROG_STOP_MASTER_NEW       ,
    E_BL_PROG_START_MASTER          ,
    E_BL_PROG_START_MASTER_NEW      ,
    E_BL_PROG_STOP_USER             ,
    E_BL_PROG_STOP_USER_NEW         ,
    E_BL_PROG_START_USER            ,
    E_BL_PROG_START_USER_NEW        ,
    E_BL_EEPROM_WRITE_BL            ,
    E_BL_EEPROM_WRITE_CAL           ,
    E_BL_EEPROM_WRITE_USER          ,
    E_BL_EEPROM_WRITE_ALL           ,
    E_BL_EEPROM_WRITE_STOP          ,
    E_BL_EEPROM_WRITE               ,
    E_BL_EEPROM_READ                ,
    E_BL_NOTIFICATION_READ          ,

#if 0
    E_BL_EEPROM_CAN_EXT_BAUD_INP_SMP,
    E_BL_EEPROM_CAN_EXT_BAUD_INP    ,
    E_BL_EEPROM_CAN_EXT_BAUD_INP_AND_CHANGE,
#endif 

#if !defined(ROLE_MINIMAL)
    E_BL_FLASH_REQUEST              ,
    E_BL_FLASH_CLEAR_APPL           ,
    E_BL_FLASH_WRITE                ,
    E_BL_READ_COMMIT_HASH           ,

#if defined(IO_TEST_ENABLE)
	E_BL_HW_IO_TEST					,
#endif 

#else
    E_BL_FLASH_REQUEST              ,
#endif
    E_BL_MAX

} enum_BL_CMD;

typedef enum
{
    E_PC_HW_INIT_DIG_IN           =1u,
    E_PC_HW_INIT_ANA_IN           =2u,
    E_PC_HW_INIT_DIG_OUT          =3u,
    E_PC_HW_READ_DIG              =4u,
    E_PC_HW_READ_ANA              =5u,
    E_PC_HW_WRITE_DIG             =6u,
    E_PC_HW_GOTO_SLEEP            =7u,
    E_PC_HW_SET_CAN               =8u,   
    E_PC_HW_INIT_SHIFT_REG        =15u,
    E_PC_HW_WRITE_SHIFT_REG       =16u,
    E_PC_HW_INIT_SCI              =20u,
    E_PC_HW_INIT_SPI              =25u,
    E_PC_HW_WRITE_SPI             =26u,
    E_PC_HW_TEST_WATCHDOG         =30u,  
    E_PC_HW_GET_MORE_TIME         =50u  
} enum_BL_HW_CMD;

typedef enum
{
    E_CHECK_NONE                 = 0u,
    E_CHECK_SN                       ,
    E_CHECK_DATA                     ,
    E_CHECK_MAX
}t_check;

enum E_RESET_TYPE
{
    E_RESET_TYPE_NONE = 0,
    E_RESET_TYPE_BL,
    E_RESET_TYPE_APP
};

typedef enum
{
    E_SEND_SN_SCAN               = 0u,
    E_SEND_SN_DATA                   ,
    E_SEND_DATA                      ,
    E_SEND_SPECIFIC                  ,
    E_SEND_MAX
}t_send;

enum E_FLASH_STATE
{
  E_FLASH_RECORD_WAIT_START_CHAR = 0u   ,
  E_FLASH_RECORD_READ                  ,
  E_FLASH_RECORD_PROCESS               ,
};

typedef enum
{
    HAL_SYS_RESET_TYPE_NONE = 0,        
    HAL_SYS_RESET_TYPE_SOFTRESET_APP,   
    HAL_SYS_RESET_TYPE_SOFTRESET_BL,    
    HAL_SYS_RESET_TYPE_SOFTRESET_BL_UPDATE_FROM_COPY,    
    HAL_SYS_RESET_TYPE_HARDRESET_WD,    
    HAL_SYS_RESET_TYPE_HARDRESET_CPU,   

    HAL_SYS_RESET_TYPE_START_APP        
} enum_HAL_SYS_RESET;

typedef enum
{
    BL_EXEC_STATE_UNKNOWN = 0,
    BL_EXEC_STATE_STARTED,
    BL_EXEC_STATE_INITIALIZING,
    BL_EXEC_STATE_INITIALIZED,
    BL_EXEC_STATE_AT_LEAST_ONCE_CONNECTED,
    BL_EXEC_STATE_JUMP_TO_APP,
} enum_BL_EEPROM_STATE;


typedef enum
{
    FLASH_MODE_ERASE = 0u,  
    FLASH_MODE_PROG,        
	FLASH_MODE_FINALIZE,	
} enum_FLASH_MODE;

typedef enum
{
    E_PROG_OK                    = 0u,  
    E_PROG_STOP_PARAMETER            ,  
    E_PROG_STOP_RESET                ,  
    E_PROG_STOP_USER                 ,  
    E_PROG_STOP_MASTER               ,  
    E_PROG_MAX
} enum_PROG_STATE;


typedef struct
{
    enum_FLASH_MODE flash_mode;
    uint32_t flash_block;
    uint32_t flash_addr;
    uint8_t buffer[300u];
    uint8_t header_buffer[300u];
    enum_CODE status;
} struct_flash_handler_data;

typedef struct
{
    uint32_t header_key;            
    uint32_t header_crc;            
    uint32_t app_header_version;    
    uint32_t application_crc;       
    uint32_t application_length;    
    uint8_t sw_version[32];         
#if HAL_SYS_APP_HEADER_VERSION >= 1
    uint8_t reserve[460];
    uint8_t signature_key[512];
#endif
} struct_hal_sys_app_header_t;

typedef struct
{
	bool active;					
	bool signal;					
	bool active_at_startup;			
} struct_hw_bl_t;

typedef struct
{
    const uint8_t*  ptr_data;           
    uint32_t        data_length;        
} struct_data_t;

typedef struct
{
    uint8_t*        ptr_signature;      
    uint32_t        signature_length;   
} struct_signature_t;


void role_protocol_bl_constructor(role_id_t id, pf_role_constructor parent);

#ifdef __cplusplus
}
#endif

#endif 

