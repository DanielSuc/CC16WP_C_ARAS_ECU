#ifndef HAL_NVM_H
#define HAL_NVM_H

#include "hal_data_types.h"

#define HAL_NVM_ERASED_BYTE             0x0u


typedef enum
{
    HAL_NVM_OK                      = 0u,     
    HAL_NVM_ERROR_GENERAL               ,     
    HAL_NVM_ERROR_INIT_FAILED           ,     
    HAL_NVM_ERROR_WHILE_READING         ,     
    HAL_NVM_ERROR_WHILE_WRITING         ,     
    HAL_NVM_ERROR_WHILE_CLEARING        ,     
    HAL_NVM_ERROR_BLOCK_INVALID         ,     
    HAL_NVM_ERROR_BLOCK_NO_INVALID      ,     
    HAL_NVM_ERROR_DATA_LEN_INVALID      ,     
    HAL_NVM_ERROR_DATA_ADDR_INVALID     ,     
    HAL_NVM_ERROR_NOT_IMPLEMENTED             

} enum_HAL_NVM_RETURN_VALUE;



enum_HAL_NVM_RETURN_VALUE hal_nvm_init( void );

enum_HAL_NVM_RETURN_VALUE hal_nvm_eeprom_init_block( uint16_t block_no );

enum_HAL_NVM_RETURN_VALUE hal_nvm_eeprom_check_block( uint16_t block_no );

void hal_nvm_eeprom_process_cyclic( void );

enum_HAL_NVM_RETURN_VALUE hal_nvm_eeprom_write_by_block_no( uint16_t block_no, const uint8_t* ptr_data );

enum_HAL_NVM_RETURN_VALUE hal_nvm_eeprom_read_by_block_no( uint16_t block_no, uint32_t len, uint8_t* ptr_data );

enum_HAL_NVM_RETURN_VALUE hal_nvm_eeprom_write_by_block_no_immediate( uint16_t block_no, const uint8_t* ptr_data );

enum_HAL_NVM_RETURN_VALUE hal_nvm_eeprom_read_by_block_no_immediately( uint16_t block_no, uint32_t len, uint8_t* ptr_data );

enum_HAL_NVM_RETURN_VALUE hal_nvm_eeprom_write_by_address( uint32_t addr, uint32_t len, const uint8_t* ptr_data );

enum_HAL_NVM_RETURN_VALUE hal_nvm_eeprom_read_by_address( uint32_t addr, uint32_t len, uint8_t* ptr_data );
#endif

