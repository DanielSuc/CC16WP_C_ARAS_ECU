#ifndef SRC_USER_API_EEPROM_H_
#define SRC_USER_API_EEPROM_H_
#include <stdint.h>
#include "hal_nvm.h"

#define EE_FACTORY_DATA_START	0								  
#define EE_USER_START 			2048                              
#define EE_USER_END   			4095                              
#define EE_USER_SIZE  			(EE_USER_END - EE_USER_START + 1) 


typedef enum
{
	PART_NR=0,
	DRAWING_NR,
	HW_TYPE,
	ORDER_NR,
	TEST_DATE,
	HW_VERSION,
	APP_NAME,
	APP_VERSION,

} enum_USER_ASCII_EEPROM_FIELD_NAME;

typedef enum
{
	EEPROM_VERSION=0,
	ID,
	MCU,
	HW_ACTIVE,
	BL_VERSION,
	RESET_COUNTER,
	PROG_STATUS,
	COP_WD_TIMEOUT,
	BL_CAN_BUS
} enum_USER_UINT16_EEPROM_FIELD_NAME;

enum_HAL_NVM_RETURN_VALUE user_eeprom_read_raw(uint32_t const ee_addr, uint32_t const len, uint8_t *const ptr_data);


enum_HAL_NVM_RETURN_VALUE user_eeprom_write_raw(uint32_t const ee_addr, uint32_t const len, uint8_t const *const ptr_data);


enum_HAL_NVM_RETURN_VALUE user_eeprom_read(uint32_t const ee_addr, uint32_t const len, uint8_t *const ptr_data);


enum_HAL_NVM_RETURN_VALUE user_eeprom_write(uint32_t const ee_addr, uint32_t const len, uint8_t const *const ptr_data);


enum_HAL_NVM_RETURN_VALUE user_eeprom_read_32bit(uint32_t const ee_addr, uint32_t const len, uint32_t *const ptr_data);


enum_HAL_NVM_RETURN_VALUE user_eeprom_write_32bit(uint32_t const ee_addr, uint32_t const len, uint32_t const *const ptr_data);


uint32_t user_eeprom_read_value_32bit(uint32_t const ee_addr);


enum_HAL_NVM_RETURN_VALUE user_eeprom_write_value_32bit(uint32_t const ee_addr, uint32_t const value);


uint16_t user_eeprom_read_module_eeprom_version(void);

uint16_t user_eeprom_read_module_id(void);


uint32_t user_eeprom_read_module_serial_nr(void);

uint32_t user_eeprom_read_module_device_type(void);

enum_HAL_NVM_RETURN_VALUE user_eeprom_read_module_part_nr(uint8_t buffer[], uint8_t const size_buffer, bool const filter);

enum_HAL_NVM_RETURN_VALUE user_eeprom_read_module_drawing_nr(uint8_t buffer[], uint8_t const size_buffer, bool const filter);

enum_HAL_NVM_RETURN_VALUE user_eeprom_read_module_name(uint8_t buffer[], uint8_t const size_buffer, bool const filter);

enum_HAL_NVM_RETURN_VALUE user_eeprom_read_module_order_nr(uint8_t buffer[], uint8_t const size_buffer, bool const filter);

enum_HAL_NVM_RETURN_VALUE user_eeprom_read_module_test_date(uint8_t buffer[], uint8_t const size_buffer, bool const filter);

uint16_t user_eeprom_read_module_mcu_type(void);


enum_HAL_NVM_RETURN_VALUE user_eeprom_read_module_hw_version(uint8_t buffer[], uint8_t const size_buffer, bool const filter);

uint16_t user_eeprom_read_module_hw_can_active(void);

uint16_t user_eeprom_read_module_bootloader_version(void);


uint16_t user_eeprom_read_module_reset_counter(void);

uint8_t user_eeprom_read_module_reset_reason(void);

uint16_t user_eeprom_read_module_prog_status(void);


enum_HAL_NVM_RETURN_VALUE user_eeprom_read_app_name(uint8_t* buffer, uint8_t const size_buffer, bool const filter);

enum_HAL_NVM_RETURN_VALUE user_eeprom_read_app_version(uint8_t* buffer, uint8_t const size_buffer, bool const filter);

enum_HAL_NVM_RETURN_VALUE user_eeprom_write_app_info(const uint8_t *const app_name, const uint8_t *const app_version);

enum_HAL_NVM_RETURN_VALUE user_eeprom_reset_reset_counter(void);

uint16_t user_eeprom_read_module_cop_wd_timeout(void);

uint16_t user_eeprom_read_bl_can_bus(void);


uint16_t* user_eeprom_ptr_to_uint16_field_member(enum_USER_UINT16_EEPROM_FIELD_NAME field_name);

uint8_t* user_eeprom_ptr_to_char_field_member(enum_USER_ASCII_EEPROM_FIELD_NAME field_name);

uint8_t user_eeprom_length_of_field_member(enum_USER_ASCII_EEPROM_FIELD_NAME field_name);

enum_HAL_NVM_RETURN_VALUE user_eeprom_read_module_ascii_field(enum_USER_ASCII_EEPROM_FIELD_NAME field_name, uint8_t *buffer, uint8_t size_buffer, bool filter);


#endif 


