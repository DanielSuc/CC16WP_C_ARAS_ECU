#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

#include "defines_general.h"

#include "role_types.h"
#include "role_base.h"
#include "role_board.h"
#include "ee_helper.h"
#include "role.h"

#include "user_api_eeprom.h"
#include "hal_nvm.h"

FILENUM(23)   



enum_HAL_NVM_RETURN_VALUE user_eeprom_read_raw(uint32_t const ee_addr, uint32_t const len, uint8_t *const ptr_data)
{
    if(ptr_data)
    {
        if( (EE_FACTORY_DATA_START <= ee_addr) && (ee_addr <= EE_USER_END) )
        {
            if( (ee_addr + len - 1) <= EE_USER_END )
            {
                return hal_nvm_eeprom_read_by_address(ee_addr, len, ptr_data);
            }
            else
            {
                return HAL_NVM_ERROR_DATA_LEN_INVALID;
            }
        }
        else
        {
            return HAL_NVM_ERROR_DATA_ADDR_INVALID;
        }
    }
    else
    {
        return HAL_NVM_ERROR_DATA_ADDR_INVALID;
    }
}


enum_HAL_NVM_RETURN_VALUE user_eeprom_write_raw(uint32_t const ee_addr, uint32_t const len, uint8_t const *const ptr_data)
{
    if( (EE_USER_START <= ee_addr) && (ee_addr <= EE_USER_END) )
    {
        if( (ee_addr + len - 1) <= EE_USER_END )
        {
            return hal_nvm_eeprom_write_by_address(ee_addr, len, ptr_data);
        }
        else
        {
            return HAL_NVM_ERROR_DATA_LEN_INVALID;
        }
    }
    else
    {
        return HAL_NVM_ERROR_DATA_ADDR_INVALID;
    }
}


enum_HAL_NVM_RETURN_VALUE user_eeprom_read(uint32_t const ee_addr, uint32_t const len, uint8_t *const ptr_data)
{
    uint32_t eeprom_address = EE_USER_START + ee_addr;

    if( (EE_USER_START <= eeprom_address) && (eeprom_address <= EE_USER_END) )
    {
        return user_eeprom_read_raw(eeprom_address, len, ptr_data);
    }
    else
    {
        return HAL_NVM_ERROR_DATA_ADDR_INVALID;
    }
}


enum_HAL_NVM_RETURN_VALUE user_eeprom_write(uint32_t const ee_addr, uint32_t const len, uint8_t const *const ptr_data)
{
    uint32_t eeprom_address = EE_USER_START + ee_addr;

    if( (EE_USER_START <= eeprom_address) && (eeprom_address <= EE_USER_END) )
    {
        return user_eeprom_write_raw(eeprom_address, len, ptr_data);
    }
    else
    {
        return HAL_NVM_ERROR_DATA_ADDR_INVALID;
    }
}


enum_HAL_NVM_RETURN_VALUE user_eeprom_read_32bit(uint32_t const ee_addr, uint32_t const len, uint32_t *const ptr_data)
{
    return user_eeprom_read(ee_addr, len, (uint8_t*) ptr_data);
}


enum_HAL_NVM_RETURN_VALUE user_eeprom_write_32bit(uint32_t const ee_addr, uint32_t const len, uint32_t const *const ptr_data)
{
    return user_eeprom_write(ee_addr, len, (uint8_t*) ptr_data);
}


uint32_t user_eeprom_read_value_32bit(uint32_t const ee_addr)
{
    uint8_t arr[4];
    uint32_t return_val = 0x00;

    user_eeprom_read(ee_addr, 4, arr);

    memcpy(&return_val, &arr, sizeof(arr));

    return return_val;
}


enum_HAL_NVM_RETURN_VALUE user_eeprom_write_value_32bit(uint32_t const ee_addr, uint32_t const value)
{
    return user_eeprom_write(ee_addr, 4, (uint8_t*) &value);
}

uint16_t user_eeprom_read_module_eeprom_version(void)
{
    return *user_eeprom_ptr_to_uint16_field_member(EEPROM_VERSION);
}

uint16_t user_eeprom_read_module_id(void)
{
    return SWAP16(*user_eeprom_ptr_to_uint16_field_member(ID));
}

uint32_t user_eeprom_read_module_serial_nr(void)
{
    uint32_t retval = 0;

    retval = SWAP32(*(uint32_t *)EE_READ_PTR(serial_number)) & 0x00FFFFFF;
    return retval;
}

uint32_t user_eeprom_read_module_device_type(void)
{

    uint32_t retval = 0;

    retval = SWAP32(*(uint32_t *)EE_READ_PTR(serial_number)) & 0xFF000000;
    return retval;
}

enum_HAL_NVM_RETURN_VALUE user_eeprom_read_module_part_nr(uint8_t buffer[], uint8_t const size_buffer, bool const filter)
{
    return user_eeprom_read_module_ascii_field(PART_NR, buffer, size_buffer, filter);
}

enum_HAL_NVM_RETURN_VALUE user_eeprom_read_module_drawing_nr(uint8_t buffer[], uint8_t const size_buffer, bool const filter)
{
    return user_eeprom_read_module_ascii_field(DRAWING_NR, buffer, size_buffer, filter);
}

enum_HAL_NVM_RETURN_VALUE user_eeprom_read_module_name(uint8_t buffer[], uint8_t const size_buffer, bool const filter)
{
    return user_eeprom_read_module_ascii_field(HW_TYPE, buffer, size_buffer, filter);
}

enum_HAL_NVM_RETURN_VALUE user_eeprom_read_module_order_nr(uint8_t buffer[], uint8_t const size_buffer, bool const filter)
{
    return user_eeprom_read_module_ascii_field(ORDER_NR, buffer, size_buffer, filter);
}

enum_HAL_NVM_RETURN_VALUE user_eeprom_read_module_test_date(uint8_t buffer[], uint8_t const size_buffer, bool const filter)
{
    return user_eeprom_read_module_ascii_field(TEST_DATE, buffer, size_buffer, filter);
}

uint16_t user_eeprom_read_module_mcu_type(void)
{
    return *user_eeprom_ptr_to_uint16_field_member(MCU);
}

enum_HAL_NVM_RETURN_VALUE user_eeprom_read_module_hw_version(uint8_t buffer[], uint8_t const size_buffer, bool const filter)
{
    return user_eeprom_read_module_ascii_field(HW_VERSION, buffer, size_buffer, filter);
}

uint16_t user_eeprom_read_module_hw_can_active(void)
{
    return *user_eeprom_ptr_to_uint16_field_member(HW_ACTIVE);
}

uint16_t user_eeprom_read_module_bootloader_version(void)
{
    return SWAP16(*user_eeprom_ptr_to_uint16_field_member(BL_VERSION));
}

uint16_t user_eeprom_read_module_reset_counter(void)
{
    return *user_eeprom_ptr_to_uint16_field_member(RESET_COUNTER);
}

uint8_t user_eeprom_read_module_reset_reason(void)
{
    uint8_t retval = 0, lvd = 0, loc = 0, ilad = 0, ilop = 0, cop = 0;

    lvd = *(uint8_t *)EE_READ_PTR(reset_reason_lvd);
    loc = *(uint8_t *)EE_READ_PTR(reset_reason_loc);
    ilad = *(uint8_t *)EE_READ_PTR(reset_reason_ilad);
    ilop = *(uint8_t *)EE_READ_PTR(reset_reason_ilop);
    cop = *(uint8_t *)EE_READ_PTR(reset_reason_cop);

    retval = retval | (cop << 4) | (ilop << 3) | (ilad << 2) | (loc << 1) | lvd;
    return retval;
}

uint16_t user_eeprom_read_module_prog_status(void)
{
    return SWAP16(*user_eeprom_ptr_to_uint16_field_member(PROG_STATUS)) & 0x000F;
}

enum_HAL_NVM_RETURN_VALUE user_eeprom_read_app_name(uint8_t *const buffer, uint8_t const size_buffer, bool const filter)
{
    return user_eeprom_read_module_ascii_field(APP_NAME, buffer, size_buffer, filter);
}

enum_HAL_NVM_RETURN_VALUE user_eeprom_read_app_version(uint8_t *const buffer, uint8_t const size_buffer, bool const filter)
{
    return user_eeprom_read_module_ascii_field(APP_VERSION, buffer, size_buffer, filter);
}

enum_HAL_NVM_RETURN_VALUE user_eeprom_write_app_info(uint8_t const *const app_name, uint8_t const *const app_version)
{
    EE_WRITE(module_name, app_name);
    EE_WRITE(sw_version, app_version);

    return HAL_NVM_OK;
}


enum_HAL_NVM_RETURN_VALUE user_eeprom_reset_reset_counter(void)
{
    EE_WRITE_MAX32(reset_counter, 0u);
    return HAL_NVM_OK;
}

uint16_t user_eeprom_read_module_cop_wd_timeout(void)
{
    return !SWAP16(*user_eeprom_ptr_to_uint16_field_member(COP_WD_TIMEOUT));
}

uint16_t user_eeprom_read_bl_can_bus(void)
{
    return SWAP16(*user_eeprom_ptr_to_uint16_field_member(BL_CAN_BUS));
}

uint16_t* user_eeprom_ptr_to_uint16_field_member(enum_USER_UINT16_EEPROM_FIELD_NAME field_name)
{
    switch(field_name)
    {
        case EEPROM_VERSION:
            return (uint16_t *)EE_READ_PTR(eeprom_version);
            break;
        case ID:
            return (uint16_t *)EE_READ_PTR(id);
            break;
        case MCU:
            return (uint16_t *)EE_READ_PTR(mcu_type);
            break;
        case HW_ACTIVE:
            return (uint16_t *)EE_READ_PTR(hw_can_active);
            break;
        case BL_VERSION:
            return (uint16_t *)EE_READ_PTR(bl_version);
            break;
        case RESET_COUNTER:
            return (uint16_t *)EE_READ_PTR(reset_counter);
            break;
        case PROG_STATUS:
            return (uint16_t *)EE_READ_PTR(prog_state);
            break;
        case COP_WD_TIMEOUT:
            return (uint16_t *)EE_READ_PTR(wd_timeout);
            break;
        case BL_CAN_BUS:
            return (uint16_t *)EE_READ_PTR(bl_canbus);
            break;
        default:
            return 0;
            break;
    }
}

uint8_t* user_eeprom_ptr_to_char_field_member(enum_USER_ASCII_EEPROM_FIELD_NAME field_name)
{
    switch(field_name)
    {
        case PART_NR:
            return (uint8_t *)EE_READ_PTR(part_number);
            break;
        case DRAWING_NR:
            return (uint8_t *)EE_READ_PTR(drawing_number);
            break;
        case HW_TYPE:
            return (uint8_t *)EE_READ_PTR(name);
            break;
        case ORDER_NR:
            return (uint8_t *)EE_READ_PTR(order_number);
            break;
        case TEST_DATE:
            return (uint8_t *)EE_READ_PTR(test_date);
            break;
        case HW_VERSION:
            return (uint8_t *)EE_READ_PTR(hw_version);
            break;
        case APP_NAME:
            return (uint8_t *)EE_READ_PTR(module_name);
            break;
        case APP_VERSION:
            return (uint8_t *)EE_READ_PTR(sw_version);
            break;
        default:
            return NULL;
            break;
    }
}

uint8_t user_eeprom_length_of_field_member(enum_USER_ASCII_EEPROM_FIELD_NAME field_name)
{
    switch(field_name)
    {
        case PART_NR:
            return EE_MEMB_SIZE(part_number);
            break;
        case DRAWING_NR:
            return EE_MEMB_SIZE(drawing_number);
            break;
        case HW_TYPE:
            return EE_MEMB_SIZE(name);
            break;
        case ORDER_NR:
            return EE_MEMB_SIZE(order_number);
            break;
        case TEST_DATE:
            return EE_MEMB_SIZE(test_date);
            break;
        case HW_VERSION:
            return EE_MEMB_SIZE(hw_version);
            break;
        case APP_NAME:
            return EE_MEMB_SIZE(module_name);
            break;
        case APP_VERSION:
            return EE_MEMB_SIZE(sw_version);
            break;
        default:
            return 0;
            break;
    }
}

enum_HAL_NVM_RETURN_VALUE user_eeprom_read_module_ascii_field(enum_USER_ASCII_EEPROM_FIELD_NAME field_name, uint8_t *buffer, uint8_t size_buffer, bool filter)
{

    uint8_t length = user_eeprom_length_of_field_member(field_name);
    uint8_t char_buffer[length+1];

    memset(buffer, '\0', size_buffer);
    if(size_buffer >= length+1)
    {
        uint8_t *read_ptr;

        read_ptr=user_eeprom_ptr_to_char_field_member(field_name);

        if(read_ptr != NULL)
        {
            memcpy(char_buffer, read_ptr, length);
            if (filter)
            {
                uint8_t sp=0;
                for(uint8_t i=0; i<length; ++i){
                    if(char_buffer[i]==' ')
                    {
                        ++sp;
                    }else{
                        sp=0;
                    }

                    if(sp == 2)
                    {
                        --i;
                        memset(&char_buffer[i], '\0', length-i+1);
                        break;
                    }
                    else
                    {

                    }
                }
            }

            char_buffer[length] = '\0';
            memcpy(buffer, char_buffer, length+1);
            return HAL_NVM_OK;
        }else
        {
            return HAL_NVM_ERROR_DATA_LEN_INVALID;
        }
    }
    else
    {

    }
    return HAL_NVM_ERROR_WHILE_READING;
}

