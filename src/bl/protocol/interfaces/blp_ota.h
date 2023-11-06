
#ifndef SRC_BLP_OTA_H_
#define SRC_BLP_OTA_H_

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(SPECIFICS_CONNECTED_LOGGER_TEST) || defined(SPECIFICS_CONNECTED_WALLBOX_TEST) || defined(ROLE_MINIMAL)

#define OTA_BIN_STATE_NONE						((state_bin_t)0xFFFFFFFFu)
#define OTA_BIN_STATE_UNDEFINED					((state_bin_t)0xFFFFFFFEu)
#define OTA_BIN_STATE_NEW						((state_bin_t)0xFFFFFFFCu)
#define OTA_BIN_STATE_VERIFY_1					((state_bin_t)0xFFFFFFF8u)
#define OTA_BIN_STATE_VERIFY_2                  ((state_bin_t)0xFFFFFFF0u)
#define OTA_BIN_STATE_VERIFY_3                  ((state_bin_t)0xFFFFFFE0u)
#define OTA_BIN_STATE_VERIFY_4                  ((state_bin_t)0xFFFFFFC0u)
#define OTA_BIN_STATE_VERIFY_LAST               ((state_bin_t)0xFFFFFF80u)
#define OTA_BIN_STATE_VALID						((state_bin_t)0xFFFFFF00u)
#define OTA_BIN_STATE_INVALID					((state_bin_t)0xFFFFFE00u)
#define OTA_BIN_STATE_ABORTED 					((state_bin_t)0xFFFFFC00u)
#define OTA_BIN_STATE_DISCARDED					((state_bin_t)0xFFFFF800u)

#define OTA_BIN_TYPE_NONE						((type_bin_t)0xFFu)
#define OTA_BIN_TYPE_APP						((type_bin_t)0xFEu)
#define OTA_BIN_TYPE_BLUPDATER					((type_bin_t)0xFCu)

typedef bool (*ota_spimem_data_erase_fptr_t) (uint32_t address, uint32_t len);
typedef bool (*ota_spimem_data_write_fptr_t) (uint32_t address, const uint8_t *data, uint32_t len);
typedef bool (*ota_spimem_data_read_fptr_t)  (uint32_t address, uint8_t *data, uint32_t len);
typedef struct
{
	ota_spimem_data_erase_fptr_t data_erase;
	ota_spimem_data_write_fptr_t data_write;
	ota_spimem_data_read_fptr_t  data_read;

	uint32_t sector_size;
	uint32_t mem_size;

} struct_OTA_SPIMEM_IO_INFO;


bool 		ota_init							(struct_OTA_SPIMEM_IO_INFO *ptr_io_info);

uint8_t		ota_get_partition_max_count			();

bool		ota_erase_partition					(uint8_t partition_number);

uint8_t		ota_get_partition_type				(uint8_t partition_number);
uint32_t	ota_get_partition_state				(uint8_t partition_number);
uint32_t	ota_get_partition_seq_counter		(uint8_t partition_number);
uint32_t	ota_get_partition_fw_address		(uint8_t partition_number);
uint32_t	ota_get_partition_settings_address	(uint8_t partition_number);

bool 		ota_set_partition_type				(uint8_t partition_number, uint8_t type);
bool 		ota_set_partition_state				(uint8_t partition_number, uint32_t state);

#endif 

#if defined(SPECIFICS_CONNECTED_LOGGER_TEST) || defined(SPECIFICS_CONNECTED_WALLBOX_TEST)
bool ota_test_flash_app_to_spi_memory(uint32_t address_offset, uint8_t const *ptr_val, uint16_t size);

#if defined(SPECIFICS_CONNECTED_WALLBOX_TEST)
bool copy_from_reserved_space_to_partition(uint32_t bin_size, bool force_program);
void hang_if_test_condition_met();
void record_fault_case(uint8_t fault_case);
uint8_t read_fault_case();
void reset_test();
#endif 

#endif 

#ifdef __cplusplus
}
#endif

#endif 

