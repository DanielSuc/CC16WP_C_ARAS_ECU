#ifndef SFL_DB_H
#define SFL_DB_H


#include "hal_data_types.h"
#include "can_db_tables.h"

uint32_t sfl_db_change_intel_to_motorola_32_bit( uint32_t val_in );

void sfl_db_put_signal_value_to_data_block( uint32_t value, uint8_t* ptr_to_data_block, uint16_t startbit, uint16_t length, uint8_t data_format );

void sfl_db_put_signal_value_to_data_block(uint32_t value, uint8_t* ptr_to_data_block, uint16_t startbit, uint16_t length, uint8_t data_format);

uint32_t sfl_db_get_signal_value_from_data_block(uint8_t* ptr_to_data_block, uint16_t startbit, uint16_t length, uint8_t data_format, uint8_t data_type);

#if ARCHITECTURE_64BIT
uint64_t sfl_db_change_intel_to_motorola_64_bit(uint64_t val_in);

void sfl_db_put_signal_value_to_data_block_64(uint64_t value, uint8_t* ptr_to_data_block, uint16_t startbit, uint16_t length, uint8_t data_format);

uint64_t sfl_db_get_signal_value_from_data_block_64(uint8_t* ptr_to_data_block, uint16_t startbit, uint16_t length, uint8_t data_format);

#endif 

#endif

