
#ifndef SRC_ROLE_PROTOCOL_ROLE_PROTOCOL_EE_H_
#define SRC_ROLE_PROTOCOL_ROLE_PROTOCOL_EE_H_

#include "role_phy_can.h"
#include "role_phy_spi.h"




#define EE_VERSION_COMPATIBLE        14u 

#define EE_VERSION_BL                17u 

#if EE_VERSION_BL < EE_VERSION_COMPATIBLE
#error "EE_VERSION_BL cannot be smaller than EE_VERSION_COMPATIBLE. Please correct"
#endif 

#define C_CAN_BL_PROTOCOL_VERSION     1u    

#define C_BL_VERSION                 ((uint16_t)31u)



typedef struct
{
    uint8_t                  enable;
    struct_ROLE_CAN_EXT_BAUD baud;
    uint8_t                  crc8;
} __attribute__((packed)) struct_EE_CAN_EXT;

typedef struct
{
	struct_ROLE_SPI_SETTINGS settings;
    uint8_t                  crc8;
} __attribute__((packed)) struct_EE_SPI_SETTINGS;

#if defined(ROLE_MINIMAL) || defined(BL_UPDATE_APP)
struct struct_EEPROM_OLD	
{
    uint16_t  eeprom_version;
    uint16_t  id;
    uint32_t  serial_number;
    uint8_t   part_number[12u];
    uint8_t   drawing_number[12u];
    uint8_t   name[20u];
    uint8_t   order_number[8u];
    uint8_t   test_date[8u];
    uint8_t   hw_version[2u];
    uint8_t   reset_counter;
    uint16_t  lib_version;
    uint8_t   reset_reason_lvd;
    uint8_t   reset_reason_loc;
    uint8_t   reset_reason_ilad;
    uint8_t   reset_reason_ilop;
    uint8_t   reset_reason_cop;
    uint8_t   mcu_type;
    uint8_t   hw_can_active;
    uint8_t   reserve1[3u];
    uint16_t  bl_version;
    uint16_t  prog_state;
    uint16_t  port_byte1;
    uint16_t  port_byte2;
    uint16_t  baudrate1;
    uint16_t  baudrate2;
    uint8_t   bl_id_ext1;
    uint32_t  bl_id1;
    uint8_t   bl_id_crc1;
    uint8_t   bl_id_ext2;
    uint32_t  bl_id2;
    uint8_t   bl_id_crc2;
    uint8_t   sw_version[20u];
    uint8_t   module_name[30u];
    uint8_t   bl_canbus;
    uint16_t  wd_timeout;
    uint16_t  startup_time;
    uint8_t   reserve2[7u];

    uint8_t   can_bl_protocol_version;
	struct_EE_CAN_EXT can_ext_bt;
	struct_EE_SPI_SETTINGS spi;
	uint16_t  bl_variant;
    uint8_t   eeprom_version_bl;
    uint8_t   app_bl_protocol_version;

} __attribute__((packed));

typedef struct struct_EEPROM_OLD struct_EEPROM_OLD;

typedef struct
{
    uint16_t addr_old;
    uint16_t addr_new;
    uint8_t field_len_old;
    uint8_t field_len_new;
    uint_t def_val;
    uint8_t min_len;
    bool is_string;
} struct_EE_VERSION_MAPPING;

struct struct_EEPROM0	
{
    uint16_t  eeprom_version;
    uint16_t  id;
    uint32_t  serial_number;
    uint32_t  device_number;
    uint8_t   part_number[20u];
    uint8_t   drawing_number[20u];
    uint8_t   name[20u];
    uint8_t   order_number[20u];
    uint8_t   test_date[12u];
    uint16_t  mcu_type;
    uint8_t   hw_version[2u];
    uint16_t  hw_can_active;
    uint16_t  bl_version;

    uint32_t  trace_code;
    uint8_t   factory_data_reserve[20u];
    uint16_t  reset_counter;
    uint8_t   reset_reason_lvd;
    uint8_t   reset_reason_loc;
    uint8_t   reset_reason_ilad;
    uint8_t   reset_reason_ilop;
    uint8_t   reset_reason_cop;
    uint8_t   reset_reason_reserved;

    uint16_t  lib_version;
    uint16_t  prog_state;
    uint8_t   module_data_reserve[20u];
    uint16_t  port_byte1;
    uint16_t  port_byte2;
    uint16_t  baudrate1;
    uint16_t  baudrate2;
    uint8_t   bl_id_ext1;
    uint32_t  bl_id1;
    uint8_t   bl_id_crc1;
    uint8_t   bl_id_ext2;
    uint32_t  bl_id2;
    uint8_t   bl_id_crc2;
    uint8_t   sw_version[20u];
    uint8_t   module_name[30u];
    uint8_t   bl_canbus;
    uint16_t  wd_timeout;
    uint8_t   config_data_reserve[20u];

    uint8_t   reserve1[3u];				
    uint16_t  startup_time;				
    uint8_t   reserve2[7u];				

    uint8_t   can_bl_protocol_version;
    struct_EE_CAN_EXT can_ext_bt;
	struct_EE_SPI_SETTINGS spi;
	uint16_t  bl_variant;
    uint8_t   eeprom_version_bl;
    uint8_t   app_bl_protocol_version;

} __attribute__((packed));

typedef struct struct_EEPROM0 struct_EEPROM0;
#endif 

#if defined(ROLE_MINIMAL) || defined(BL_UPDATE_APP) || \
	( defined(EE_VERSION_COMPATIBLE) && (14 == EE_VERSION_COMPATIBLE) )


#if 0
#define EE14_RO_LIST \
	    uint16_t  eeprom_version; \
	    uint16_t  id; \
	    uint8_t   can_bl_protocol_version; \
	    uint16_t  bl_version; \
	    uint32_t  trace_code; \
	    uint32_t  uidl; \
	    uint32_t  uidml; \
	    uint32_t  uidmh; \
	    uint32_t  uidh; \
	    uint32_t  serial_number; \
	    uint8_t   reserved_ro[8]; \
	    uint8_t   part_number[14]; \
	    uint8_t   drawing_number[30u]; \
	    uint8_t   name[40u]; \
	    uint8_t   hw_version[2u]; \
	    uint16_t  mcu_type; \
	    uint8_t   order_number[12u]; \
	    uint8_t   test_date[10u]; \
	    uint8_t   hw_can_active; \
		uint8_t   factory_data_reserve[20u]
#endif 

#define EE14_COMPATIBLE_RO_LIST \
        uint16_t  eeprom_version; \
        uint16_t  id; \
        uint8_t   can_bl_protocol_version; \
        uint16_t  bl_version; \
        uint32_t  trace_code; \
        uint32_t  uidl; \
        uint32_t  uidml; \
        uint32_t  uidmh; \
        uint32_t  uidh; \
        uint32_t  serial_number; \
        uint8_t   reserved_ro[8]; \
        uint8_t   part_number[14]; \
        uint8_t   drawing_number[30u]; \
        uint8_t   name[40u]; \
        uint8_t   hw_version[2u]; \
        uint16_t  mcu_type; \
        uint8_t   order_number[12u]; \
        uint8_t   test_date[10u]; \
        uint8_t   hw_can_active; \
        uint16_t  bl_variant; \
        uint8_t   eeprom_version_bl; \
        uint8_t   app_bl_protocol_version; \
        uint8_t   factory_data_reserve[16u]

#define EE14_RW_LIST \
	    uint16_t  reset_counter; \
	    uint8_t   reset_reason_lvd; \
	    uint8_t   reset_reason_loc; \
	    uint8_t   reset_reason_ilad; \
	    uint8_t   reset_reason_ilop; \
	    uint8_t   reset_reason_cop; \
	    uint8_t   reset_reason_reserved; \
	    uint16_t  prog_state; \
	    uint8_t   factory_reset; \
	    uint8_t   module_data_reserve[20u]; \
\
	    uint16_t  wd_timeout; \
	    uint8_t   bl_canbus; \
	    uint16_t  port_byte1; \
	    uint16_t  port_byte2; \
	    uint16_t  baudrate1; \
	    uint16_t  baudrate2; \
	    uint8_t   bl_id_ext1; \
	    uint32_t  bl_id1; \
	    uint8_t   bl_id_crc1; \
	    uint8_t   bl_id_ext2; \
	    uint32_t  bl_id2; \
	    uint8_t   bl_id_crc2; \
	    uint8_t   sw_version[20u]; \
	    uint8_t   module_name[30u]; \
	    uint16_t  startup_time; \
	    uint8_t   config_data_reserve[20u]; \
\
	     \
	     \
	     \
	     \
	    struct_EE_CAN_EXT can_ext_bt


struct struct_EEPROM14_COMPATIBLE_RO 
{
    EE14_COMPATIBLE_RO_LIST ;
} __attribute__((packed));

struct struct_EEPROM14_COMPATIBLE 
{
    EE14_COMPATIBLE_RO_LIST ;
    EE14_RW_LIST;

    struct_EE_SPI_SETTINGS spi;
} __attribute__((packed));

typedef struct struct_EEPROM14_COMPATIBLE_RO struct_EEPROM14_COMPATIBLE_RO ;
typedef struct struct_EEPROM14_COMPATIBLE struct_EEPROM14_COMPATIBLE ;

typedef struct
{
    uint16_t addr;
    uint8_t field_len;
    uint_t def_val;
    uint8_t min_len;
    bool is_string;
} struct_EE_MEMB_DEFAULT;

#endif 

struct struct_PROGRAM_ONCE
{
    uint8_t ee_addr_format;
} __attribute__((packed));
typedef struct struct_PROGRAM_ONCE struct_PROGRAM_ONCE;


typedef struct
{
    uint16_t addr;
    uint16_t size;
} struct_EE_FIELD_INFO;

#if defined(BL_UPDATE_APP)
typedef struct
{
    uint16_t addr_old;
    uint16_t addr_new;
    uint8_t  len_old;
    uint8_t  len_new;
} struct_EE_DATA_PORTING;
#endif 

enum E_MCU_TYPE
{
    E_MCU_TYPE_NONE = 0,
    E_MCU_TYPE_HCS08,
    E_MCU_TYPE_HCS12,
    E_MCU_TYPE_HCS08DZ128,
    E_MCU_TYPE_MK10xx,
    E_MCU_TYPE_RH850,
    E_MCU_TYPE_S32K144,
    E_MCU_TYPE_SKEAZ64AMLH,
    E_MCU_TYPE_S32K148,
    E_MCU_TYPE_MKE18F,
    E_MCU_TYPE_HCS08DZ48,
    E_MCU_TYPE_S32K142
};

typedef enum
{
    EEPROM_ADDRESSING_OLD,
    EEPROM_ADDRESSING_NEW,
} enum_EEPROM_ADDRESSING;

typedef enum
{
    PROGRAM_ONCE_READ,
    PROGRAM_ONCE_WRITE
} enum_PROGRAM_ONCE_OP;

#define SWAP8(x)    ((uint8_t) x)
#define SWAP16(x)   ((uint16_t) ((((uint16_t)x) >>  8) & 0xFFu) | ((((uint16_t)x) << 8) & 0xFF00u))
#define SWAP32(x)   ((uint32_t) ((((uint32_t)x) >> 24) & 0xFFu) | ((((uint32_t)x) << 8) & 0xFF0000u) \
                    | ((((uint32_t)x) >> 8) & 0xFF00u) | ((((uint32_t)x) << 24) & 0xFF000000u))


#if !defined(ROLE_MINIMAL) && !defined(BL_UPDATE_APP) 

#if defined(EE_VERSION_COMPATIBLE) && (14 == EE_VERSION_COMPATIBLE)

#define EE_MEMB_ADDR(m)             offsetof(struct_EEPROM14_COMPATIBLE, m)
#define EE_MEMB_SIZE(m)             SIZEOF_MEMBER(struct_EEPROM14_COMPATIBLE, m)

#define EE14_COMPATIBLE_MEMB(m, val)  EE_MEMB(m, val)

#else
#error "Missing EE_ macros for the defined EE_VERSION_COMPATIBLE"

#endif 

#define EE_READ_PTR(m) \
        ee_read(EE_MEMB_ADDR(m))

#define EE_WRITE(m, d) \
        ee_write(EE_MEMB_ADDR(m), EE_MEMB_SIZE(m), d)

#define EE_WRITE_MAX32(m, d) \
        ee_write_max32(EE_MEMB_ADDR(m), EE_MEMB_SIZE(m), d)

#define EE_WRITE_DEFAULT(m) \
        ee_set_defaults(EE_MEMB_ADDR(m))

#define EE_MEMB(m, val)             {EE_MEMB_ADDR(m), EE_MEMB_SIZE(m), \
                                    (uint_t)val, MIN(EE_MEMB_SIZE(m), sizeof(val)), \
                                    _Generic((val), char* : TRUE, default: FALSE) }

#else	

#define EE_MEMB_ADDR_OLD(m) 	offsetof(struct_EEPROM_OLD, m)
#define EE_MEMB_SIZE_OLD(m)		SIZEOF_MEMBER(struct_EEPROM_OLD, m)

#define EE0_MEMB_ADDR_NEW(m)    offsetof(struct_EEPROM0, m)
#define EE0_MEMB_SIZE_NEW(m)	SIZEOF_MEMBER(struct_EEPROM0, m)

#define EE0_MEMB_ADDR_BOTH(m)   ( ( ((uint32_t)EE_MEMB_ADDR_OLD(m)) << 16 ) | EE0_MEMB_ADDR_NEW(m) )
#define EE0_MEMB_SIZE_BOTH(m)   ( ( ((uint32_t)EE_MEMB_SIZE_OLD(m)) << 16 ) | EE0_MEMB_SIZE_NEW(m) )

#define EE0_MEMB_ADDR(m)         ( bl_ee_working_addr(EE0_MEMB_ADDR_BOTH(m)) )

#define EE0_READ_PTR(m) \
        ee_read(EE0_MEMB_ADDR_BOTH(m))

#define EE0_WRITE(m, d) \
        ee_write(EE0_MEMB_ADDR_BOTH(m), EE0_MEMB_SIZE_BOTH(m), d)

#define EE0_WRITE_MAX32(m, d) \
        ee_write_max32(EE0_MEMB_ADDR_BOTH(m), EE0_MEMB_SIZE_BOTH(m), d)

#define EE0_WRITE_DEFAULT(m) \
        ee_set_defaults(EE0_MEMB_ADDR_BOTH(m))

#define EE0_MEMB_MAP(m, val)        {EE_MEMB_ADDR_OLD(m), EE0_MEMB_ADDR_NEW(m), EE_MEMB_SIZE_OLD(m), EE0_MEMB_SIZE_NEW(m), \
                                    (uint_t)val, MIN(EE_MEMB_SIZE_OLD(m), sizeof(val)), \
                                    _Generic((val), char* : TRUE, default: FALSE) }


#define EE14_COMPATIBLE_MEMB_ADDR(m)    offsetof(struct_EEPROM14_COMPATIBLE, m)
#define EE14_COMPATIBLE_MEMB_SIZE(m)    SIZEOF_MEMBER(struct_EEPROM14_COMPATIBLE, m)

#define EE14_COMPATIBLE_READ_PTR(m) \
        ee_read(EE14_COMPATIBLE_MEMB_ADDR(m))

#define EE14_COMPATIBLE_WRITE(m, d) \
        ee_write(EE14_COMPATIBLE_MEMB_ADDR(m), EE14_COMPATIBLE_MEMB_SIZE(m), d)

#define EE14_COMPATIBLE_WRITE_MAX32(m, d) \
        ee_write_max32(EE14_COMPATIBLE_MEMB_ADDR(m), EE14_COMPATIBLE_MEMB_SIZE(m), d)

#define EE14_COMPATIBLE_WRITE_DEFAULT(m) \
        ee_set_defaults(EE14_COMPATIBLE_MEMB_ADDR(m))

#define EE14_COMPATIBLE_MEMB(m, val)    {EE14_COMPATIBLE_MEMB_ADDR(m), EE14_COMPATIBLE_MEMB_SIZE(m), \
                                        (uint_t)val, MIN(EE14_COMPATIBLE_MEMB_SIZE(m), sizeof(val)), \
                                        _Generic((val), char* : TRUE, default: FALSE) }


#define EE_INVALID_ADDR             (0xFFFFFFFFu)


#define EE_MEMB_ADDR(m) \
        (  0 == ee_version_get_compatible() ? EE0_MEMB_ADDR(m)  : \
		   ( 1 == ee_version_get_compatible() || \
            14 == ee_version_get_compatible() || \
            15 == ee_version_get_compatible() || \
            16 == ee_version_get_compatible() ) ? EE14_COMPATIBLE_MEMB_ADDR(m) : \
                    EE_INVALID_ADDR \
		)

#define EE_MEMB_SIZE(m) \
        (  0 == ee_version_get_compatible() ? EE0_MEMB_SIZE_NEW(m)  : \
           ( 1 == ee_version_get_compatible() || \
            14 == ee_version_get_compatible() || \
            15 == ee_version_get_compatible() || \
            16 == ee_version_get_compatible() ) ? EE14_COMPATIBLE_MEMB_SIZE(m) : \
                    0u \
		)

#define EE_READ_PTR(m) \
        (  0 == ee_version_get_compatible() ? EE0_READ_PTR(m)  : \
		   ( 1 == ee_version_get_compatible() || \
            14 == ee_version_get_compatible() || \
            15 == ee_version_get_compatible() || \
            16 == ee_version_get_compatible() ) ? EE14_COMPATIBLE_READ_PTR(m) : \
                       ((uint8_t*)NULL) \
		)

#define EE_WRITE(m, d) \
        (  0 == ee_version_get_compatible() ? EE0_WRITE(m, d)  : \
		   ( 1 == ee_version_get_compatible() || \
            14 == ee_version_get_compatible() || \
            15 == ee_version_get_compatible() || \
            16 == ee_version_get_compatible() ) ? EE14_COMPATIBLE_WRITE(m, d) : \
                    CODE_FAIL \
		)

#define EE_WRITE_MAX32(m, d) \
        (  0 == ee_version_get_compatible() ? EE0_WRITE_MAX32(m, d)  : \
    	   ( 1 == ee_version_get_compatible() || \
            14 == ee_version_get_compatible() || \
            15 == ee_version_get_compatible() || \
            16 == ee_version_get_compatible() ) ? EE14_COMPATIBLE_WRITE_MAX32(m, d) : \
                    CODE_FAIL \
		)

#define EE_WRITE_DEFAULT(m) \
        (  0 == ee_version_get_compatible() ? EE0_WRITE_DEFAULT(m)  : \
		   ( 1 == ee_version_get_compatible() || \
            14 == ee_version_get_compatible() || \
            15 == ee_version_get_compatible() || \
            16 == ee_version_get_compatible() ) ? EE14_COMPATIBLE_WRITE_DEFAULT(m) : \
                    CODE_FAIL \
		)

#if defined(BL_UPDATE_APP)

#if defined(EE_VERSION_COMPATIBLE) && (14 == EE_VERSION_COMPATIBLE)

#define EE0_TO_LATEST_EE_DATA_PORT(m)  {EE0_MEMB_ADDR_NEW(m), EE14_COMPATIBLE_MEMB_ADDR(m), \
										EE0_MEMB_SIZE_NEW(m), EE14_COMPATIBLE_MEMB_SIZE(m)}

#define EE_MEMB_ADDR_LATEST(m)          EE14_COMPATIBLE_MEMB_ADDR(m)
#define EE_MEMB_SIZE_LATEST(m)          EE14_COMPATIBLE_MEMB_SIZE(m)

#else
#error "Please add missing EEPROM version support for BL Updater"
#endif 

#endif 

#endif 

#define LITTLE_ENDIAN       0
#define BIG_ENDIAN          1

#define EE_ARCH_FORMAT      LITTLE_ENDIAN
#define EE_IO_FORMAT        BIG_ENDIAN

#define EE_ALL_DEFAULTS     ((uint32_t)-1)

#define BL_PROTOCOL_CAN_ID  ((uint32_t)0x1FFFFFF0u)
#define C_BL_ID             ((uint16_t)2332u) 
#define C_BL_ID_PREV        ((uint16_t)1331u) 

#define C_BL_ID_EXT         (1u)
#define C_BL_ID_NIBBLE      (0u)

#define C_BL_ID_CNT         (EE_MEMB_SIZE(bl_id_ext1) + EE_MEMB_SIZE(bl_id1) + EE_MEMB_SIZE(bl_id_crc1))

#define INV_16(x)           ((uint16_t)(( ((uint16_t)(~x)) << 8) + (x & 0xFF)))
#define INV_8(x)            ((uint8_t) (( ((uint8_t)(~x)) << 4) + (x & 0x0F)))
#define CHECK_INV_8(x)      (((x) & 0x0Fu) == (~((x) >> 4) & 0x0Fu))    

#if EE_ARCH_FORMAT != EE_IO_FORMAT

#define SWAP(x)             _Generic((x),   uint16_t: SWAP16(x), \
                                            uint32_t: SWAP32(x), \
                                            int16_t:  SWAP16(x), \
                                            int32_t:  SWAP32(x), \
                                            default:  SWAP8(x))

#else

#define SWAP(x)             (x)

#endif 

#define NIBBLE_H_L(a,b)     ((a) | (((b) << 4) & 0xFFu))

#define CALC_CRC(a,b,x)     ((~((((x) >> 24) & 0xFFu)+(((x) >> 16u) & 0xFFu) + \
                                (((x) >> 8u) & 0xFFu) + ((x) & 0xFFu) + \
                                NIBBLE_H_L((a),(b)))) & 0xFFu)

#if defined(CPU_S32K148)
#define ROLE_BL_PROTOCOL_MCU_TYPE            ((uint8_t)E_MCU_TYPE_S32K148)


#elif (defined(CPU_S32K144HFT0VLLT) || defined(CPU_S32K144LFT0MLLT))
#define ROLE_BL_PROTOCOL_MCU_TYPE            ((uint8_t)E_MCU_TYPE_S32K144)

#elif defined(CPU_S32K142)
#define ROLE_BL_PROTOCOL_MCU_TYPE            ((uint8_t)E_MCU_TYPE_S32K142)

#elif defined(CPU_MK10DN512VLL10)
#define ROLE_BL_PROTOCOL_MCU_TYPE            ((uint8_t)E_MCU_TYPE_MK10xx)

#else
#error "MCU type unknown. Specify the MCU type via SYSTEM_CPU in the makefile."
#endif

#define EE_BAD_ADDRESS      ((uint16_t)-1)

#define BL_APP_MODE_APP							((uint32_t)0u)
#define BL_APP_MODE_STANDALONE					((uint32_t)1u)


bool ee_is_id_match(uint32_t app_mode);

#if defined(BL_UPDATE_APP)
void ee_version_compatible_reset();
#endif 

uint16_t ee_version_get_compatible();

bool ee_is_address_mapping_used();

uint8_t* ee_read(uint32_t offset);

enum_CODE ee_write(uint32_t offset, uint32_t size, const uint8_t *ptr_val);

enum_CODE ee_write_max32(uint32_t offset, uint32_t size, uint32_t val);

enum_CODE ee_set_defaults(uint32_t offset);

#if defined(BL_UPDATE_APP)
enum_CODE ee_port_data();
#endif 

uint16_t bl_ee_working_addr(uint32_t addr);


#endif 

