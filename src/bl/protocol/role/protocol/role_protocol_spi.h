
#ifndef SRC_ROLE_PROTOCOL_SPI_H_
#define SRC_ROLE_PROTOCOL_SPI_H_

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(SPECIFICS_CONNECTED_LOGGER) || defined(SPECIFICS_CONNECTED_WALLBOX)


#define RESET_COUNTER_THRESHOLD_ROLLBACK    (30u)

#define SPI_MEM_PTBL_OFFSET					(0u) 
#define SPI_MEM_PTBL_MAGIC_ID				(0x7074626Cu)
#define SPI_MEM_PTBL_VERSION				(1u)
#define SPI_MEM_PTBL_INVALID_ADDRESS		(0xFFFFFFFFu)

#define SPI_MEM_PTBL_V1_NMAX_ADDRESSES		(2u)

#define SPI_MEM_BINS_ABSOLUTE_NMAX			(SPI_MEM_PTBL_V1_NMAX_ADDRESSES)

#define SPI_MEM_BIN_HEADER_VERSION_INVALID	(0u)
#define SPI_MEM_BIN_HEADER_VERSION			(1u)

#define STATE_BIN_NONE						((state_bin_t)0xFFFFFFFFu)
#define STATE_BIN_UNDEFINED					((state_bin_t)0xFFFFFFFEu)
#define STATE_BIN_NEW						((state_bin_t)0xFFFFFFFCu)
#define STATE_BIN_VERIFY_1					((state_bin_t)0xFFFFFFF8u)
#define STATE_BIN_VERIFY_2                  ((state_bin_t)0xFFFFFFF0u)
#define STATE_BIN_VERIFY_3                  ((state_bin_t)0xFFFFFFE0u)
#define STATE_BIN_VERIFY_4                  ((state_bin_t)0xFFFFFFC0u)
#define STATE_BIN_VERIFY_LAST               ((state_bin_t)0xFFFFFF80u)
#define STATE_BIN_VALID						((state_bin_t)0xFFFFFF00u)
#define STATE_BIN_INVALID					((state_bin_t)0xFFFFFE00u)
#define STATE_BIN_ABORTED 					((state_bin_t)0xFFFFFC00u)
#define STATE_BIN_DISCARDED					((state_bin_t)0xFFFFF800u)

#define TYPE_BIN_NONE						((type_bin_t)0xFFu)
#define TYPE_BIN_APP						((type_bin_t)0xFEu)
#define TYPE_BIN_BLUPDATER					((type_bin_t)0xFCu)

#define SEQ_COUNTER_NONE					((uint32_t)0xFFFFFFFFu)


#define ROLE_DO_PARAM_LIST_SPI_PROTOCOL \
		, ROLE_MAP_REAL_PARAM_TO_NUM(struct_SPI_MEM_IO_INFO*, ROLE_SPI_PROTOCOL_IO_INFO) \
		, ROLE_MAP_REAL_PARAM_TO_NUM(struct_SPI_MEM_PARTITION_KEY*, ROLE_SPI_PROTOCOL_PARTITION_KEY)



typedef enum
{
	ROLE_SPI_PROTOCOL_IO_INFO = ROLE_COMPOSE_DO_PARAM_BASE(ROLE_ID_SPI_BOOTLOADER),
	ROLE_SPI_PROTOCOL_PARTITION_KEY,

} enum_ROLE_SPI_PROTOCOL_DO_PARAM;


typedef enum
{

    ROLE_SPI_PROTOCOL_MEM_INIT_IO_INFO = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SPI_BOOTLOADER, 0u, ROLE_SPI_PROTOCOL_IO_INFO),
    ROLE_SPI_PROTOCOL_MEM_CHECK = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SPI_BOOTLOADER, 1u, ROLE_ANY_PARAM_UINT32),
#if !defined(ROLE_MINIMAL)
    ROLE_SPI_PROTOCOL_PROGRAM_LAST_VALID_BIN = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SPI_BOOTLOADER, 2u, ROLE_ANY_PARAM_UINT32),
#endif 

#if defined(SPECIFICS_CONNECTED_LOGGER_TEST) || defined(SPECIFICS_CONNECTED_WALLBOX_TEST) || defined(ROLE_MINIMAL)
    ROLE_SPI_PROTOCOL_GET_PARTITION_COUNT = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SPI_BOOTLOADER, 3u, ROLE_ANY_PARAM_UINT32PTR),
    ROLE_SPI_PROTOCOL_GET_PARTITION_KEY = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SPI_BOOTLOADER, 4u, ROLE_SPI_PROTOCOL_PARTITION_KEY),
    ROLE_SPI_PROTOCOL_GET_PARTITION_FW_ADDRESS = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SPI_BOOTLOADER, 5u, ROLE_ANY_PARAM_UINT32PTR),
    ROLE_SPI_PROTOCOL_GET_PARTITION_SETTINGS_ADDRESS = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SPI_BOOTLOADER, 6u, ROLE_ANY_PARAM_UINT32PTR),
    ROLE_SPI_PROTOCOL_ERASE_PARTITION = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SPI_BOOTLOADER, 7u, ROLE_ANY_PARAM_UINT32),
    ROLE_SPI_PROTOCOL_UPDATE_PARTITION = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SPI_BOOTLOADER, 8u, ROLE_SPI_PROTOCOL_PARTITION_KEY),
#endif 

} enum_ROLE_SPI_PROTOCOL_DO_ID;

typedef uint32_t address_t;
typedef uint32_t state_bin_t;
typedef uint8_t  type_bin_t;


typedef enum
{
	LATEST_BIN_STATE_OK     = 0,
	LATEST_BIN_STATE_BAD_1  = 1,
	LATEST_BIN_STATE_BAD_2  = 2,

} enum_SPI_MEM_LATEST_BIN_STATE;


typedef bool (*data_erase_fptr_t) (uint32_t address, uint32_t len);
typedef bool (*data_write_fptr_t) (uint32_t address, const uint8_t *data, uint32_t len);
typedef bool (*data_read_fptr_t)  (uint32_t address, uint8_t *data, uint32_t len);

typedef struct
{
	data_erase_fptr_t data_erase;
	data_write_fptr_t data_write;
	data_read_fptr_t  data_read;

	uint32_t sector_size;
	uint32_t mem_size;

} struct_SPI_MEM_IO_INFO;

typedef struct
{
    uint32_t  magic_id;				
    uint8_t   version;				
} __attribute__((packed)) struct_SPI_MEM_PTBL_COMMON_PART;

typedef struct
{
	struct_SPI_MEM_PTBL_COMMON_PART common;
	address_t	binheader_address[SPI_MEM_PTBL_V1_NMAX_ADDRESSES];	
    uint8_t		crc;                                          		
} __attribute__((packed)) struct_SPI_MEM_PTBL_TABLE_V1;

typedef struct
{
    uint8_t  version;                       
} __attribute__((packed)) struct_SPI_MEM_BINHEADER_COMMON;

typedef struct __attribute__((packed))
{
	type_bin_t  fw_type;                    
    state_bin_t fw_state;                   
    uint32_t seq_counter;                   
}  __attribute__((packed)) struct_SPI_MEM_BINHEADER_KEY;

typedef struct __attribute__((packed))
{
	struct_SPI_MEM_BINHEADER_COMMON common; 
	struct_SPI_MEM_BINHEADER_KEY key;       
#if 0
	address_t fw_offset;                    
#endif 

    address_t settings_offset;              
}  __attribute__((packed)) struct_SPI_MEM_BINHEADER_V1;


typedef struct
{
	uint8_t partition_number;
	struct_SPI_MEM_BINHEADER_KEY *ptr_key;

} __attribute__((packed)) struct_SPI_MEM_PARTITION_KEY;


void role_protocol_spi_constructor(role_id_t id, pf_role_constructor parent);


#endif 

#ifdef __cplusplus
}
#endif

#endif 

