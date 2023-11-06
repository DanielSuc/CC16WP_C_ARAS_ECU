
#ifndef SRC_ROLE_BL_WBX_H_
#define SRC_ROLE_BL_WBX_H_

#if defined(SPECIFICS_WALLBOX)

#if defined(__cplusplus)
extern "C" {
#endif


typedef enum
{
    ROLE_BL_WBX_CHECK_AND_JUMP_APP = ROLE_COMPOSE_DO_ID(ROLE_TYPE_WALLBOX_BOOTLOADER, 0u, ROLE_ANY_PARAM_UINT32)

} enum_ROLE_BL_WBX_DO_ID;


#define BASE_SW_VERSION_MAJOR       0
#define BASE_SW_VERSION_MINOR       0
#define BASE_SW_VERSION_BUILD       3

#define STRINGIZE2(s)               #s
#define STRINGIZE(s)                STRINGIZE2(s)

#define BASE_SW_STRING  (STRINGIZE(BASE_SW_VERSION_MAJOR) "." STRINGIZE(BASE_SW_VERSION_MINOR) "." STRINGIZE(BASE_SW_VERSION_BUILD))
#define BASE_SW_FULL    ((BASE_SW_VERSION_MAJOR << 16) + (BASE_SW_VERSION_MINOR << 8) + BASE_SW_VERSION_BUILD)

#ifndef WALLBOX_HW_REV_NUM
#error "HW version (WALLBOX_HW_REV_NUM) not defined"
#endif

#pragma message "HW version: " STRINGIZE(WALLBOX_HW_REV_STR)
#pragma message "HW version num: " STRINGIZE(WALLBOX_HW_REV_NUM)

#define BTLDR_FLASH_RESERVE_SIZE    64

#define APP_NORM_RESET_REQUEST_FG_MAGIC_NUM (0xa5) 
#define MAX_ALLOWED_APP_WDT_CNT     255

typedef enum
{
    first_fw,
    second_fw,
    no_fw
} firmware_num_t;

typedef struct __attribute__ ((packed, aligned (BTLDR_FLASH_RESERVE_SIZE)))
{
    const uint16_t fw_num;
}boot_data_t;


#define BOOTLOADER_APP_FIRMWARE_REV_SIZE (32)
typedef const struct __attribute__ ((packed))
{
    const boot_data_t boot_data;                
    const uint32_t crc;                         
    const uint32_t app_size;                    
    const unsigned char app_sw_revision[BOOTLOADER_APP_FIRMWARE_REV_SIZE];    
#if (!defined(ROLE_MINIMAL) && !defined(BL_UPDATE_APP))  
    const uint32_t * const vtor_table_ptr;      
    const uint32_t * const got_flash_ptr;       
    uint32_t * const got_ram_ptr;               
    const uint32_t got_size;                    
#endif  

} btldr_app_header;

typedef struct
{
    uint32_t (*Wdt_Reset_ptr)(void);
    uint32_t (*Get_Version_ptr)(void);
    unsigned char *(*Get_CurrApp_Version_ptr)(void);
    unsigned char *(*Get_AlternateApp_Version_ptr)(void);
    uint32_t (*Get_User_EEPROM_Region_ptr)(uint32_t *start, uint32_t *length);
    uint32_t (*Get_User_DataFlash_Region_ptr)(uint32_t *startAddr, uint32_t *length, uint16_t *write_granularity, uint16_t *erase_granularity);
    uint32_t (*Get_AppImage_Region_Parameters_ptr)(uint32_t *maxSize, uint32_t *write_chunk_size, uint32_t *erase_sector_size);
    uint32_t (*Erase_AppImage_Sector_ptr)(uint32_t sector_num);
    uint32_t (*Write_AppImage_Chunk_ptr)(uint32_t chunkIndex, uint8_t *data);
    uint32_t (*Validate_AppImage_ptr)(void);
    uint32_t (*Reset_Application_ptr)(void);

    uint32_t (*Write_User_EEPROM_Region_ptr)   ( uint32_t dest_addr, void * pData, uint32_t size);
    uint32_t (*Erase_User_DataFlash_Region_ptr)( uint32_t dest_addr, uint32_t size);
    uint32_t (*Write_User_DataFlash_Region_ptr)( uint32_t dest_addr, void * pData, uint32_t size);

    uint32_t (*Get_CurrApp_Statistics_ptr)(void *pData, uint32_t dataSize);        
    uint32_t (*Get_AlternateApp_Statistics_ptr)(void *pData, uint32_t dataSize);   

} btldr_functions_t;

typedef struct __attribute__((packed))
{
    uint8_t padding[2];      
    uint8_t wdt_reset_count; 
    uint8_t sw_unexpected_reset_count;  
} firmware_configs_t;

typedef struct __attribute__((packed))
{
    firmware_configs_t fw[2];    
    uint8_t last_loaded_fw;      
    uint8_t init_key;            
    uint8_t reserved0 [6];          
} eeprom_config_t;

typedef struct __attribute__ ((packed))
{
    uint32_t wdtRstCnt;                
    uint32_t swUnexpRstCnt;            
} btldr_app_statistics_t;



void role_wbx_bl_constructor(role_id_t id, pf_role_constructor parent);

#ifdef __cplusplus
}
#endif

#endif 

#endif 

