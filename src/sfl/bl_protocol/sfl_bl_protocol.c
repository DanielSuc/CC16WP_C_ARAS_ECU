#include "sfl_bl_protocol.h"

#ifdef BOOTLOADER_FLASH_ACTIVE
    #include "bl_flash.h"
#endif

const struct st_bl_msg bl_msg[E_BL_MAX] = {
{   E_SUB_PC_CMD ,{0x00, 0x00}  ,E_CHECK_NONE   ,2  ,{0x00,}                                ,NULL_PTR                   ,E_SEND_SN_SCAN ,E_SUB_BL_ADDR  ,8  ,{0x00,}                        },  
{   E_SUB_PC_CMD ,{0x20, 0x10}  ,E_CHECK_SN     ,6  ,{0x00,}                                ,NULL_PTR                   ,E_SEND_SN_DATA ,E_SUB_BL_RESP  ,8  ,{0x21, 0x10,}                  },  
{   E_SUB_PC_CMD ,{0x60, 0x22}  ,E_CHECK_DATA   ,8  ,{0x57, 0xF0, 0xCA, 0xEA, 0xF2, 0xF5}   ,&sfl_bl_set_program_state  ,E_SEND_SN_DATA ,E_SUB_BL_RESP  ,8  ,{0x61, 0x22,}                  },  
{   E_SUB_PC_CMD ,{0x70, 0x22}  ,E_CHECK_DATA   ,8  ,{0x75, 0x0F, 0xAC, 0xAE, 0x2F, 0x5F}   ,&sfl_bl_set_program_state  ,E_SEND_SN_DATA ,E_SUB_BL_RESP  ,8  ,{0x71, 0x22,}                  },  
{   E_SUB_PC_CMD ,{0x40, 0x22}  ,E_CHECK_DATA   ,8  ,{0x44, 0xEF, 0xBA, 0xAA, 0xE2, 0xF1}   ,&sfl_bl_set_program_state  ,E_SEND_SN_DATA ,E_SUB_BL_RESP  ,8  ,{0x41, 0x22,}                  },  
{   E_SUB_PC_CMD ,{0x50, 0x22}  ,E_CHECK_DATA   ,8  ,{0x45, 0xEE, 0xBB, 0xAB, 0xE3, 0xF2}   ,&sfl_bl_set_program_state  ,E_SEND_SN_DATA ,E_SUB_BL_RESP  ,8  ,{0x51, 0x22,}                  },  
{   E_SUB_PC_CMD ,{0x20, 0x01}  ,E_CHECK_DATA   ,5  ,{0x3F, 0x33, 0xFA,}                    ,&sfl_bl_set_eeprom_access  ,E_SEND_DATA    ,E_SUB_BL_RESP  ,5  ,{0x20, 0xF0, 0x01, 0x00, 0x00,}},  
{   E_SUB_PC_CMD ,{0x20, 0x04}  ,E_CHECK_DATA   ,5  ,{0x4F, 0x44, 0xFB,}                    ,&sfl_bl_set_eeprom_access  ,E_SEND_DATA    ,E_SUB_BL_RESP  ,5  ,{0x20, 0xF0, 0x01, 0x00, 0x00,}},  
{   E_SUB_PC_CMD ,{0x20, 0x08}  ,E_CHECK_DATA   ,5  ,{0x8F, 0x88, 0xFB,}                    ,&sfl_bl_set_eeprom_access  ,E_SEND_DATA    ,E_SUB_BL_RESP  ,5  ,{0x20, 0xF0, 0x01, 0x00, 0x00,}},  
{   E_SUB_PC_CMD ,{0x20, 0x11}  ,E_CHECK_DATA   ,5  ,{0xF3, 0x33, 0xAF,}                    ,&sfl_bl_set_eeprom_access  ,E_SEND_DATA    ,E_SUB_BL_RESP  ,5  ,{0x21, 0x11, 0x01, 0x00, 0x00,}},  
{   E_SUB_PC_CMD ,{0x20, 0x02}  ,E_CHECK_NONE   ,2  ,{0x00,}                                ,&sfl_bl_set_eeprom_access  ,E_SEND_DATA    ,E_SUB_BL_RESP  ,5  ,{0x20, 0xF0, 0x02, 0x00, 0x00,}},  
{   E_SUB_PC_EEP_DATA ,{0, 0 }  ,E_CHECK_NONE   ,0  ,{0x00,}                                ,&sfl_bl_can_write_eeprom   ,E_SEND_SPECIFIC,E_SUB_BL_RESP  ,0  ,{0x00,}                        },  
{   E_SUB_PC_CMD ,{0x20, 0x03}  ,E_CHECK_NONE   ,5  ,{0x00,}                                ,&sfl_bl_can_read_eeprom    ,E_SEND_SPECIFIC,E_SUB_BL_RESP  ,0  ,{0x00,}                        },  
#ifdef BOOTLOADER_FLASH_ACTIVE
{   E_SUB_PC_CMD ,{0x20, 0x00}        ,E_CHECK_NONE   ,5  ,{0x00,}                                ,&sfl_bl_set_flasher_state  ,E_SEND_DATA    ,E_SUB_BL_RESP   ,8  ,{0x21, 0x0,}                  },  
{   E_SUB_PC_CMD ,{0x02, 0x02}        ,E_CHECK_NONE   ,5  ,{0x00,}                                ,&sfl_bl_can_clear_flash    ,E_SEND_SPECIFIC,E_SUB_BL_RESP   ,8  ,{0x00}                        },  
{   E_SUB_PC_FLASH_DATA ,{0x0, 0x0}   ,E_CHECK_NONE   ,0  ,{0x00,}                                ,&sfl_bl_can_write_flash    ,E_SEND_SPECIFIC,E_SUB_BL_RESP   ,0  ,{0x00,}                       },  
#else
{   E_SUB_PC_CMD ,{0x20, 0x00}        ,E_CHECK_NONE   ,5  ,{0x00,}                                ,&sfl_bl_set_flasher_state  ,E_SEND_SPECIFIC    ,E_SUB_BL_RESP   ,8  ,{0x2F, 0xFF,}                  },  
#endif
};

const struct st_ascii par_ascii[] = {
{   PAR_PARTNUMBER      ,""             },
{   PAR_DRAWINGUMBER    ,""             },
{   PAR_NAME            ,""             },
{   PAR_ORDERNUMBER     ,""             },
{   PAR_TEST_DATE       ,""             },
{   PAR_HW_VERSION      ,""             },
{   PAR_SW_VERSION      ,"NO SOFTWARE"  },
{   PAR_MODULENAME      ,"Modulname"    },
};

const struct struc_par_data ext_bl_par_data[PAR_MAX] = {
{  2       ,T_NUMBER  ,1331                                            },  
{  4       ,T_NUMBER  ,0                                               },  
{  12      ,T_ASCII   ,0                                               },  
{  12      ,T_ASCII   ,0                                               },  
{  20      ,T_ASCII   ,0                                               },  
{  8       ,T_ASCII   ,0                                               },  
{  8       ,T_ASCII   ,0                                               },  
{  2       ,T_ASCII   ,0                                               },  
{  1       ,T_NUMBER  ,0                                               },  
{  2       ,T_NUMBER  ,0                                               },  
{  1       ,T_NUMBER  ,0                                               },  
{  1       ,T_NUMBER  ,0                                               },  
{  1       ,T_NUMBER  ,0                                               },  
{  1       ,T_NUMBER  ,0                                               },  
{  1       ,T_NUMBER  ,0                                               },  
{  1       ,T_NUMBER  ,MCU_TYPE                                        },  
{  1       ,T_NUMBER  ,0                                               },  
{  3       ,T_RESERVE ,0                                               },  
{  2       ,T_NUMBER  ,0                                               },  
{  2       ,T_NUMBER  ,INV_16(0x00)                                    },  
{  2       ,T_NUMBER  ,INV_16(0x00)                                    },  
{  2       ,T_NUMBER  ,INV_16(0x00)                                    },  
{  2       ,T_NUMBER  ,INV_16(E_BAUD_125KBIT)                          },  
{  2       ,T_NUMBER  ,INV_16(E_BAUD_125KBIT)                          },  
{  1       ,T_NUMBER  ,NIBBLE_H_L(C_BL_ID_EXT,C_BL_ID_NIBBLE)          },  
{  4       ,T_NUMBER  ,C_BL_ID                                         },  
{  1       ,T_NUMBER  ,CALC_CRC(C_BL_ID_EXT, C_BL_ID_NIBBLE, C_BL_ID)  },  
{  1       ,T_NUMBER  ,NIBBLE_H_L(C_BL_ID_EXT,C_BL_ID_NIBBLE)          },  
{  4       ,T_NUMBER  ,C_BL_ID                                         },  
{  1       ,T_NUMBER  ,CALC_CRC(C_BL_ID_EXT, C_BL_ID_NIBBLE, C_BL_ID)  },  
{  20      ,T_ASCII   ,0                                               },  
{  30      ,T_ASCII   ,0                                               },  
{  1       ,T_NUMBER  ,0                                               },  
{  2       ,T_NUMBER  ,INV_16(0x03)                                    },  
{  7       ,T_RESERVE ,0                                               },  
};

const uint8_t par_ascii_max = sizeof(par_ascii) / sizeof(par_ascii[0]); 


uint8_t  ext_bl_flasher_active = 0;                 
uint32_t ext_bl_sub_fr[E_SUB_MAX];                  
uint8_t  ext_bl_access = FALSE;                     

uint8_t  mgl_bl_id_ext = C_BL_ID_EXT;               
uint8_t  mgl_bl_id_nibble = C_BL_ID_NIBBLE;         
uint8_t  mgl_prog_state;                            
uint32_t mgl_bl_id = C_BL_ID;                       
uint16_t mgl_bl_version = 0u;                       
uint32_t mgl_bl_sn = 0u;                            
uint32_t mgl_ti_access = 0u;                        
uint32_t mgl_ti_reset_delay = 0u;                   

struct_bl_can_rx_fifo mgl_bl_can_rx_fifo;           


t_access mgl_eeprom_access;                         
uint8_t ext_bl_par_addr[PAR_MAX];                   

#if USE_HAL == 1
    struct_hal_can_handle bl_protocol_handle;       
#endif

uint8_t ext_flag_trigger_app_reset = E_RESET_TYPE_NONE; 

#if USE_HAL == 1
void sfl_bl_init( struct_hal_can_handle* handle )
{
#elif HCS08_MRS_LIBRARY == 1
    void sfl_bl_init(void)
    {
#endif

    uint16_t p_id, p_prog_state;
    const uint8_t bl_id_cnt = C_BL_ID_CNT;
    uint8_t p_arr1[8], p_arr2[8];
    uint8_t check1, check2;
    uint16_t p_pb1, p_pb2;
    uint8_t mcu_type = 0;
    uint8_t i;

#ifdef BOOTLOADER_FLASH_ACTIVE
#else
    hal_sys_set_bl_access_key( 0u );
#endif
    (void) BL_EEPROM_GET_DATA( PAR_OFFSET, (uint8_t* ) &p_id, ext_bl_par_data[PAR_ID].length );

#if USE_HAL == 1

    bl_protocol_handle = *handle;

    p_id = SWAP_16( p_id );

#endif

    for( i = 0; i < PAR_MAX; i++ )
    {
        if( i == 0 )
        {
            ext_bl_par_addr[i] = PAR_OFFSET;
        }
        else
        {
            ext_bl_par_addr[i] = ext_bl_par_addr[i - 1] + ext_bl_par_data[i - 1].length;
        }

        if( p_id != ext_bl_par_data[PAR_ID].val_default )
        {
            (void) sfl_bl_write_default_value( i );
        }
        else
        {
            if( i == PAR_SERIALNUMBER )
            {
                (void) BL_EEPROM_GET_DATA( ext_bl_par_addr[PAR_SERIALNUMBER], (uint8_t* ) &mgl_bl_sn, ext_bl_par_data[PAR_SERIALNUMBER].length );

#if USE_HAL == 1
                mgl_bl_sn = SWAP_32( mgl_bl_sn );
#endif
            }
            else if( i == PAR_PROG_STATE )
            {
                (void) BL_EEPROM_GET_DATA( ext_bl_par_addr[PAR_PROG_STATE], (uint8_t* ) &p_prog_state, ext_bl_par_data[PAR_PROG_STATE].length );

#if USE_HAL == 1
                p_prog_state = SWAP_16( p_prog_state );
#endif

                mgl_prog_state = (uint8_t) p_prog_state; 

            }
            else
            {
            }
        }
    }

    if( p_id == ext_bl_par_data[PAR_ID].val_default )
    {

        (void) BL_EEPROM_GET_DATA( ext_bl_par_addr[PAR_BL_ID_EXT1], p_arr1, bl_id_cnt );
        (void) BL_EEPROM_GET_DATA( ext_bl_par_addr[PAR_BL_ID_EXT2], p_arr2, bl_id_cnt );

        check1 = sfl_bl_check_crc( p_arr1, 0, bl_id_cnt );
        check2 = sfl_bl_check_crc( p_arr1, 0, bl_id_cnt );

        if( check1 && !check2 )
        {
            (void) BL_EEPROM_SET_DATA( ext_bl_par_addr[PAR_BL_ID_EXT2], p_arr1, bl_id_cnt );
        }
        else if( !check1 && check2 )
        {
            (void) BL_EEPROM_SET_DATA( ext_bl_par_addr[PAR_BL_ID_EXT1], p_arr2, bl_id_cnt );
        }
        else if( !check1 && !check2 )
        {
            (void) sfl_bl_write_default_value( PAR_BL_ID_EXT1 );
            (void) sfl_bl_write_default_value( PAR_BL_ID_EXT2 );
            (void) sfl_bl_write_default_value( PAR_BL_ID1 );
            (void) sfl_bl_write_default_value( PAR_BL_ID2 );
            (void) sfl_bl_write_default_value( PAR_BL_ID_CRC1 );
            (void) sfl_bl_write_default_value( PAR_BL_ID_CRC2 );
        }
        else
        {
        }

        (void) BL_EEPROM_GET_DATA( ext_bl_par_addr[PAR_BL_ID_EXT1], p_arr1, bl_id_cnt );
        mgl_bl_id_ext = p_arr1[0] & 0x0Fu;
        mgl_bl_id_nibble = ( p_arr1[0] >> 4u ) & 0x0Fu;
        mgl_bl_id_nibble = mgl_bl_id_nibble * 4u;
        mgl_bl_id = *(uint32_t*) &p_arr1[1];

#if USE_HAL == 1
        mgl_bl_id = SWAP_32( mgl_bl_id );
#endif
        mgl_bl_id |= ( (uint32_t) ( mgl_bl_id_ext & 0x01u ) << 31u );


        (void) BL_EEPROM_GET_DATA( ext_bl_par_addr[PAR_PORTBYTE1], (uint8_t* ) &p_pb1, ext_bl_par_data[PAR_PORTBYTE1].length );
        (void) BL_EEPROM_GET_DATA( ext_bl_par_addr[PAR_PORTBYTE2], (uint8_t* ) &p_pb2, ext_bl_par_data[PAR_PORTBYTE2].length );

#if USE_HAL == 1
        p_pb1 = SWAP_16( p_pb1 );
        p_pb2 = SWAP_16( p_pb2 );
#endif

        check1 = CHECK_INV_16( p_pb1 );
        check2 = CHECK_INV_16( p_pb2 );

        if( check1 && !check2 )
        {
#if USE_HAL == 1
            p_pb1 = SWAP_16( p_pb1 );
#endif
            (void) BL_EEPROM_SET_DATA( ext_bl_par_addr[PAR_PORTBYTE2], (uint8_t* ) &p_pb1, ext_bl_par_data[PAR_PORTBYTE2].length );
        }
        else if( !check1 && check2 )
        {
#if USE_HAL == 1
            p_pb2 = SWAP_16( p_pb2 );
#endif
            (void) BL_EEPROM_SET_DATA( ext_bl_par_addr[PAR_PORTBYTE1], (uint8_t* ) &p_pb2, ext_bl_par_data[PAR_PORTBYTE1].length );
        }
        else if( !check1 && !check2 )
        {
            (void) sfl_bl_write_default_value( PAR_PORTBYTE1 );
            (void) sfl_bl_write_default_value( PAR_PORTBYTE2 );
        }
        else
        {
        }


        (void) BL_EEPROM_GET_DATA( ext_bl_par_addr[PAR_BL_BAUDRATE1], (uint8_t* ) &p_pb1, ext_bl_par_data[PAR_BL_BAUDRATE1].length );
        (void) BL_EEPROM_GET_DATA( ext_bl_par_addr[PAR_BL_BAUDRATE2], (uint8_t* ) &p_pb2, ext_bl_par_data[PAR_BL_BAUDRATE2].length );

#if USE_HAL == 1
        p_pb1 = SWAP_16( p_pb1 );
        p_pb2 = SWAP_16( p_pb2 );
#endif
        check1 = ( CHECK_INV_16( p_pb1 ) ) && ( CHECK_BAUDRATE( p_pb1 ) );
        check2 = ( CHECK_INV_16( p_pb2 ) ) && ( CHECK_BAUDRATE( p_pb2 ) );

        if( check1 && !check2 )
        {
#if USE_HAL == 1
            p_pb1 = SWAP_16( p_pb1 );
#endif
            (void) BL_EEPROM_SET_DATA( ext_bl_par_addr[PAR_BL_BAUDRATE2], (uint8_t* ) &p_pb1, ext_bl_par_data[PAR_BL_BAUDRATE2].length );
        }
        else if( !check1 && check2 )
        {
#if USE_HAL == 1
            p_pb2 = SWAP_16( p_pb2 );
#endif
            (void) BL_EEPROM_SET_DATA( ext_bl_par_addr[PAR_BL_BAUDRATE1], (uint8_t* ) &p_pb2, ext_bl_par_data[PAR_BL_BAUDRATE1].length );
        }
        else if( !check1 && !check2 )
        {
            (void) sfl_bl_write_default_value( PAR_BL_BAUDRATE1 );
            (void) sfl_bl_write_default_value( PAR_BL_BAUDRATE2 );
        }
        else
        {
        }
    }

    for( i = 0; i < E_SUB_MAX; i++ )
    {
        ext_bl_sub_fr[i] = mgl_bl_id + ( (uint32_t) i << mgl_bl_id_nibble );
    }

    (void) BL_EEPROM_GET_DATA( ext_bl_par_addr[PAR_MCU_TYPE], (uint8_t* ) &mcu_type, ext_bl_par_data[PAR_MCU_TYPE].length );

    if( mcu_type != MCU_TYPE )
    {
        mcu_type = MCU_TYPE;

        (void) BL_EEPROM_SET_DATA( ext_bl_par_addr[PAR_MCU_TYPE], (uint8_t* ) &mcu_type, ext_bl_par_data[PAR_MCU_TYPE].length );
    }

    (void) BL_EEPROM_GET_DATA( ext_bl_par_addr[PAR_BL_VERSION], (uint8_t* ) &mgl_bl_version, ext_bl_par_data[PAR_BL_VERSION].length );

#if USE_HAL == 1
    mgl_bl_version = SWAP_16( mgl_bl_version );
#endif

#ifdef BOOTLOADER_FLASH_ACTIVE
    (void)BL_EEPROM_GET_DATA(ext_bl_par_addr[PAR_BL_BAUDRATE1], (uint8_t*)&p_pb1, ext_bl_par_data[PAR_BL_BAUDRATE1].length);

#if USE_HAL == 1
    p_pb1 = SWAP_16(p_pb1);
#endif
    check1 = (CHECK_INV_16(p_pb1)) && (CHECK_BAUDRATE(p_pb1));
    if(check1)
    {
        sfl_bl_change_can_baudrate(&bl_protocol_handle, (enum_bl_baudrate_t) (p_pb1 & 0xFF));
    }

    if(mgl_bl_version != C_BL_VERSION)
    {
        mgl_bl_version = C_BL_VERSION;
#if USE_HAL == 1
        mgl_bl_version = SWAP_16(mgl_bl_version);
#endif
        (void)BL_EEPROM_SET_DATA(ext_bl_par_addr[PAR_BL_VERSION], (uint8_t*)&mgl_bl_version, ext_bl_par_data[PAR_BL_VERSION].length);

    }
    mgl_bl_version = C_BL_VERSION;

    (void)BL_EEPROM_GET_DATA(ext_bl_par_addr[PAR_PORTBYTE1], (uint8_t*)&p_pb1, ext_bl_par_data[PAR_PORTBYTE1].length);

#if USE_HAL == 1
    p_pb1 = SWAP_16(p_pb1);
#endif

    check1 = CHECK_INV_16(p_pb1);

    if( ( (check1) && ((p_pb1 & 0xFFu) == 0u) ) || (hal_sys_get_bl_access_key() == HAL_SYS_BOOTLOADER_ACCESS_KEY) )
    {
        (void)sfl_bl_can_send(ext_bl_sub_fr[E_SUB_BL_ADDR], 8, 1, (uint8_t)(mgl_bl_sn>>24), (uint8_t)(mgl_bl_sn>>16), (uint8_t)(mgl_bl_sn>>8), (uint8_t)mgl_bl_sn, mgl_prog_state, mgl_bl_id_nibble, mgl_bl_version);
    }

#else
    if( mgl_bl_version == 0 )
    {
        mgl_bl_version = 1;
    }
#endif

}

uint8_t* sfl_bl_get_ascii_ptr( uint8_t p_index )
{
    uint8_t i;

    for( i = 0; i < par_ascii_max; i++ )
    {
        if( par_ascii[i].par_name == p_index )
        {
            return (uint8_t*) par_ascii[i].str;
        }
    }

    return (uint8_t*) "n/a";
}

uint8_t sfl_bl_set_eeprom_access( uint8_t p_step, struct_bl_can_frame* p_msg_in, struct_bl_can_frame* p_msg_out )
{
    uint8_t ret = ERR_OK;

    (void) p_msg_in;
    (void) p_msg_out;

    switch( p_step )
    {
        case E_BL_EEPROM_WRITE_BL:
            mgl_eeprom_access = E_ACCESS_BL;
        break;
        case E_BL_EEPROM_WRITE_CAL:
            mgl_eeprom_access = E_ACCESS_CAL;
        break;
        case E_BL_EEPROM_WRITE_USER:
            mgl_eeprom_access = E_ACCESS_USER;
        break;
        case E_BL_EEPROM_WRITE_ALL:
            mgl_eeprom_access = E_ACCESS_ALL;
        break;
        case E_BL_EEPROM_WRITE_STOP:
            mgl_eeprom_access = E_ACCESS_NONE;
        break;
        default:
            ret = ERR_VALUE;
        break;
    }

    return ret;
}

uint8_t sfl_bl_can_read_eeprom( uint8_t p_step, struct_bl_can_frame* p_msg_in, struct_bl_can_frame* p_msg_out )
{
    uint8_t ret = ERR_OK;
    uint16_t p_addr = ( ( (uint16_t) p_msg_in->data[2] << 8 ) | (uint16_t) p_msg_in->data[3] );
    uint8_t p_len = p_msg_in->data[4];
    uint8_t i;

    (void) p_step;

    p_msg_out->id = ext_bl_sub_fr[E_SUB_BL_RESP];
    p_msg_out->dlc = 5;
    p_msg_out->data[0] = p_msg_in->data[0];
    p_msg_out->data[1] = p_msg_in->data[1];

    if( p_msg_in->dlc >= 5 )
    {
        if( p_len > 8 )
        {
            p_len = 8;
        }
        else if( p_len <= 0 )
        {
            p_len = 1;
        }

        else
        {
        }

        for( i = 0; i < p_len; i++ )
        {
            ret = BL_EEPROM_GET_BYTE( ( p_addr + i ), &p_msg_out->data[i] );
            if( ret != ERR_OK )
            {
                break;
            }
        }

        if( ret == ERR_OK )
        {
            p_msg_out->id = ext_bl_sub_fr[E_SUB_BL_EEP_DATA];
            p_msg_out->dlc = p_len;
        }
        else
        {
            p_msg_out->data[2] = 0x01;
            p_msg_out->data[3] = i;
            p_msg_out->data[4] = ret;
        }
    }
    else
    {
        p_msg_out->data[2] = 0x0E;
        p_msg_out->data[3] = 0x00;
        p_msg_out->data[4] = 0x00;
    }

    return ret;
}

uint8_t sfl_bl_check_port_bit( uint8_t p_byte )
{
    uint8_t p_nr = ( p_byte >> 4 ) & 0x0F;
    uint8_t b_nr = p_byte & 0x0F;

    if( ( p_nr == 0 && b_nr == 0 ) || ( p_nr > 0 && p_nr <= 6 && b_nr > 0 && b_nr <= 8 ) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t sfl_bl_check_crc( uint8_t *p_data, uint8_t p_start, uint8_t p_cnt )
{
    uint8_t i, crc_sum = 0;

    for( i = p_start; i < p_cnt; i++ )
    {
        crc_sum += p_data[i];
    }

    if( crc_sum == 0xFF )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

uint8_t sfl_bl_can_write_eeprom( uint8_t p_step, struct_bl_can_frame* p_msg_in, struct_bl_can_frame* p_msg_out )
{
    uint8_t ret = ERR_OK;
    uint8_t ok = 0;
    uint16_t p_addr = ( (uint16_t) p_msg_in->data[0] << 8 ) | (uint16_t) p_msg_in->data[1];
    uint16_t p_len = p_msg_in->dlc - 2;
    uint16_t p_addr_end = p_addr + p_len - 1;   
    const uint8_t bl_id_cnt = C_BL_ID_CNT;

    (void) p_step;
    p_msg_out->id = ext_bl_sub_fr[E_SUB_BL_RESP];
    p_msg_out->dlc = 5;
    p_msg_out->data[0] = 0x20;
    p_msg_out->data[1] = 0xE8;
    p_msg_out->data[2] = 0x0;
    p_msg_out->data[3] = 0x0;
    p_msg_out->data[4] = 0x0;

    if( mgl_eeprom_access != E_ACCESS_NONE )
    {
        if( p_msg_in->dlc >= 3 )
        {
            if( ( mgl_eeprom_access == E_ACCESS_BL && p_addr >= ext_bl_par_addr[PAR_PORTBYTE1] && p_addr_end < 200 )  
            || ( mgl_eeprom_access == E_ACCESS_CAL && p_addr >= 200 && p_addr_end < 0x200 )
                || ( mgl_eeprom_access == E_ACCESS_USER && p_addr >= 0x200 && p_addr_end < 0x800 )
                || ( mgl_eeprom_access == E_ACCESS_ALL ) )
            {
                if( ( mgl_eeprom_access == E_ACCESS_BL || mgl_eeprom_access == E_ACCESS_ALL ) && p_addr >= ext_bl_par_addr[PAR_PORTBYTE1] && p_addr_end < 200 )
                {
                    ok = 1;

                    if( p_addr <= ext_bl_par_addr[PAR_PORTBYTE1] && p_addr_end >= ext_bl_par_addr[PAR_PORTBYTE1] )
                    {
                        ok = 0;

                        if( p_addr == ext_bl_par_addr[PAR_PORTBYTE1] && p_len == 2 )
                        {
                            if( p_msg_in->data[3] == (uint8_t) ( ~p_msg_in->data[2] ) )
                            {
                                if( sfl_bl_check_port_bit( p_msg_in->data[3] ) )
                                {
                                    ret = BL_EEPROM_SET_DATA( ext_bl_par_addr[PAR_PORTBYTE2], &p_msg_in->data[2], ext_bl_par_data[PAR_PORTBYTE2].length );
                                    ok = 1;
                                }
                                else
                                {
                                    ok = 2;
                                }
                            }
                        }
                    }

                    if( p_addr <= ext_bl_par_addr[PAR_BL_BAUDRATE1] && p_addr_end >= ext_bl_par_addr[PAR_BL_BAUDRATE1] )
                    {
                        ok = 0;

                        if( p_addr == ext_bl_par_addr[PAR_BL_BAUDRATE1] && p_len == 2 )
                        {
                            if( p_msg_in->data[3] == (uint8_t) ( ~p_msg_in->data[2] ) )
                            {
                                if( p_msg_in->data[3] > 0 && p_msg_in->data[3] < E_BAUD_MAX )
                                {
                                    ret = BL_EEPROM_SET_DATA( ext_bl_par_addr[PAR_BL_BAUDRATE2], &p_msg_in->data[2], ext_bl_par_data[PAR_BL_BAUDRATE2].length );
                                    ok = 1;
                                }
                                else
                                {
                                    ok = 3;
                                }
                            }
                        }
                    }

                    if( p_addr <= ext_bl_par_addr[PAR_BL_ID_CRC1] && p_addr_end >= ext_bl_par_addr[PAR_BL_ID_EXT1] )
                    {
                        ok = 0;

                        if( p_addr == ext_bl_par_addr[PAR_BL_ID_EXT1] && p_len == bl_id_cnt )
                        {
                            if( sfl_bl_check_crc( &p_msg_in->data[2], 0, bl_id_cnt ) )
                            {
                                ret = BL_EEPROM_SET_DATA( ext_bl_par_addr[PAR_BL_ID_EXT2], &p_msg_in->data[2], bl_id_cnt );
                                ok = 1;
                            }
                            else
                            {
                                ok = 4;
                            }
                        }
                    }
                }
                else
                {
                    ok = 1;
                }

                if( ok == 1 )
                {

                    ret = BL_EEPROM_SET_DATA( p_addr, &p_msg_in->data[2], p_len );
                    if( ret == ERR_OK )
                    {
                        p_msg_out->data[2] = 0x00;  
                    }
                    else
                    {
                        p_msg_out->data[2] = 0x01;
                        p_msg_out->data[3] = 255;
                        p_msg_out->data[4] = ret;
                    }
                }
                else
                {
                    p_msg_out->data[2] = 0x0B;
                    p_msg_out->data[3] = ok;
                }

            }
            else
            {
                p_msg_out->data[2] = 0x0C;
                p_msg_out->data[3] = ok;
            }
        }
        else
        {
            p_msg_out->data[2] = 0x0E;
        }
    }
    else
    {
        p_msg_out->data[2] = 0x0F;
    }
    return ret;
}

uint8_t sfl_bl_set_program_state( uint8_t p_step, struct_bl_can_frame* p_msg_in, struct_bl_can_frame* p_msg_out )
{
    uint8_t ret;
    uint16_t p_state;
    (void) p_msg_in;
    (void) p_msg_out;

    if( p_step == E_BL_PROG_STOP_MASTER )
    {
        p_state = INV_16( E_PROG_STOP_MASTER );
    }

    else if( p_step == E_BL_PROG_STOP_USER )
    {
        p_state = INV_16( E_PROG_STOP_USER );
    }

    else if( p_step == E_BL_PROG_START_MASTER )
    {
        p_state = INV_16( E_PROG_OK );
    }

    else if( p_step == E_BL_PROG_START_USER )
    {
        p_state = INV_16( E_PROG_OK );
    }
    else
    {
    }

#if USE_HAL == 1
    p_state = SWAP_16( p_state );
#endif

    ret = BL_EEPROM_SET_DATA( ext_bl_par_addr[PAR_PROG_STATE], (uint8_t* ) &p_state, ext_bl_par_data[PAR_PROG_STATE].length );

    return ret;
}

uint8_t sfl_bl_write_default_value( uint8_t i )
{
    uint8_t ret = ERR_OK;
    uint8_t *ptr_start;
    uint8_t *ptr_default;
    uint32_t intel_val;

    if( ext_bl_par_data[i].data_type == T_ASCII )
    {
        ptr_default = sfl_bl_get_ascii_ptr( i );
    }

    else if( ext_bl_par_data[i].data_type == T_NUMBER )
    {
#if USE_HAL == 1

        intel_val = SWAP_32( ext_bl_par_data[i].val_default );
        ptr_start = (uint8_t*) &intel_val;

#elif HCS08_MRS_LIBRARY == 1

        ptr_start = (uint8_t*)&ext_bl_par_data[i].val_default;

#endif

        ptr_default = ptr_start + ( 4 - ext_bl_par_data[i].length );
    }

    else    
    {
        ptr_default = NULL_PTR;
    }

    if( ptr_default != NULL_PTR )
    {
        ret = BL_EEPROM_SET_DATA( ext_bl_par_addr[i], ptr_default, ext_bl_par_data[i].length );
    }

    return ret;
}

uint8_t sfl_bl_can_send( uint32_t p_id, uint8_t p_dlc, uint8_t p_b0, uint8_t p_b1, uint8_t p_b2, uint8_t p_b3, uint8_t p_b4, uint8_t p_b5, uint8_t p_b6, uint8_t p_b7 )
{
#if USE_HAL == 1

    struct_hal_can_frame_t l_can_msg;
    uint8_t data[8];

    l_can_msg.can_id = p_id;
    l_can_msg.can_dlc = p_dlc;
    data[0] = p_b0;
    data[1] = p_b1;
    data[2] = p_b2;
    data[3] = p_b3;
    data[4] = p_b4;
    data[5] = p_b5;
    data[6] = p_b6;
    data[7] = p_b7;
    l_can_msg.ptr_data = data;

    return hal_can_send( &bl_protocol_handle, &l_can_msg );

#elif HCS08_MRS_LIBRARY == 1
    return os_can_send_message(p_id & 0x1FFFFFFF, (p_id >> 31) & 1, p_dlc, p_b0, p_b1, p_b2, p_b3, p_b4, p_b5, p_b6, p_b7);

#endif
}

void sfl_bl_cyclic( void )
{
#if USE_HAL == 1

    uint8_t elapsed = FALSE;
    uint8_t do_reset_elapsed = FALSE;

    if( ext_bl_access && sfl_timer_time_elapsed( &elapsed, mgl_ti_access, 10u, HAL_PRECISION_1S ) == SFL_TIMER_ERR_OK && elapsed )
    {
        ext_bl_access = FALSE;
    }

    if( mgl_bl_can_rx_fifo.read_ptr != mgl_bl_can_rx_fifo.write_ptr )
    {
        sfl_bl_can_receive( &mgl_bl_can_rx_fifo.buffer[mgl_bl_can_rx_fifo.read_ptr] );
        mgl_bl_can_rx_fifo.read_ptr++;
        if( mgl_bl_can_rx_fifo.read_ptr >= BL_CAN_RX_FIFO_BUFFER_LEN )
        {
            mgl_bl_can_rx_fifo.read_ptr = 0;
        }

    }

    (void) sfl_timer_time_elapsed( &do_reset_elapsed, mgl_ti_reset_delay, 100u, HAL_PRECISION_1MS );
    if( ext_flag_trigger_app_reset == E_RESET_TYPE_APP )
    {

        if( do_reset_elapsed == TRUE )
        {
            hal_sys_reset( HAL_SYS_RESET_TYPE_START_APP );
        }
    }
    else if( ext_flag_trigger_app_reset == E_RESET_TYPE_BL )
    {
        if( do_reset_elapsed == TRUE )
        {
            hal_sys_reset( HAL_SYS_RESET_TYPE_SOFTRESET_BL );
        }
    }
    else
    {
        (void) sfl_timer_set_timestamp( &mgl_ti_reset_delay, HAL_PRECISION_1MS );
    }

#elif HCS08_MRS_LIBRARY == 1
    if (ext_bl_access && os_time_past(mgl_ti_access, 10, OS_1000ms))
    {
        ext_bl_access = FALSE;
    }
#endif
}

void sfl_bl_can_receive( struct_bl_can_frame* msg )
{
    uint8_t i, k;
    uint8_t rx_check_ok = FALSE;
    uint8_t ret = ERR_OK;
    struct_bl_can_frame tmp_msg;
    uint8_t exit = FALSE;

    if( msg->dlc > 0 )
    {
        for( i = 0u; ( ( i < E_BL_MAX ) && ( exit == FALSE ) ); i++ )
        {
            if( msg->id == ext_bl_sub_fr[bl_msg[i].d_rx_sub] && ( i <= E_BL_ADDRESSING || ext_bl_access == TRUE ) )
            {
                if( ( msg->data[0] == bl_msg[i].d_in1[0] && msg->data[1] == bl_msg[i].d_in1[1] ) || bl_msg[i].d_rx_dlc == 0 )
                {
                    rx_check_ok = TRUE;
                    if( bl_msg[i].d_check == E_CHECK_SN )
                    {
                        if( msg->data[2] != (uint8_t) ( mgl_bl_sn >> 24 ) || msg->data[3] != (uint8_t) ( mgl_bl_sn >> 16 ) || msg->data[4] != (uint8_t) ( mgl_bl_sn >> 8 ) || msg->data[5] != (uint8_t) mgl_bl_sn )
                        {
                            rx_check_ok = FALSE;
                            ext_bl_access = FALSE;
                        }
                    }
                    else if( bl_msg[i].d_check == E_CHECK_DATA )
                    {
                        for( k = 0; k < ( bl_msg[i].d_rx_dlc - 2 ); k++ )
                        {
                            if( bl_msg[i].d_in2[k] != msg->data[2 + k] )
                            {
                                rx_check_ok = FALSE;
                            }
                        }
                    }

                    else
                    {
                    }

                    if( rx_check_ok == TRUE )
                    {
                        TRIGGER_BL_ACCESS()
                        ;

                        if( bl_msg[i].d_ptr_callback != NULL_PTR )
                        {
                            ret = bl_msg[i].d_ptr_callback( i, msg, &tmp_msg );
                        }

#ifdef BOOTLOADER_FLASH_ACTIVE
                        if (i == E_BL_ADDRESSING || i == E_BL_FLASH_REQUEST || i == E_BL_FLASH_CLEAR_APPL || i == E_BL_FLASH_WRITE )
#else
                        if( i == E_BL_ADDRESSING || i == E_BL_FLASH_REQUEST )
#endif
                        {
                            ext_bl_access = TRUE;
                        }

                        if( bl_msg[i].d_send == E_SEND_SPECIFIC )
                        {
                            (void) sfl_bl_can_send( tmp_msg.id, tmp_msg.dlc, tmp_msg.data[0], tmp_msg.data[1], tmp_msg.data[2], tmp_msg.data[3], tmp_msg.data[4], tmp_msg.data[5], tmp_msg.data[6], tmp_msg.data[7] );
                        }

                        else if( ret == ERR_OK )
                        {
                            if( bl_msg[i].d_send == E_SEND_SN_SCAN )
                            {
                                (void) sfl_bl_can_send( ext_bl_sub_fr[bl_msg[i].d_tx_sub], bl_msg[i].d_tx_dlc, 0, (uint8_t) ( mgl_bl_sn >> 24 ), (uint8_t) ( mgl_bl_sn >> 16 ), (uint8_t) ( mgl_bl_sn >> 8 ), (uint8_t) mgl_bl_sn, mgl_prog_state, mgl_bl_id_nibble, mgl_bl_version );
                            }
                            else if( bl_msg[i].d_send == E_SEND_SN_DATA )
                            {
                                (void) sfl_bl_can_send( ext_bl_sub_fr[bl_msg[i].d_tx_sub], bl_msg[i].d_tx_dlc, bl_msg[i].d_send_data[0], bl_msg[i].d_send_data[1], (uint8_t) ( mgl_bl_sn >> 24 ), (uint8_t) ( mgl_bl_sn >> 16 ), (uint8_t) ( mgl_bl_sn >> 8 ), (uint8_t) ( mgl_bl_sn ), 0, mgl_bl_version );
                            }
                            else if( bl_msg[i].d_send == E_SEND_DATA )
                            {
                                (void) sfl_bl_can_send( ext_bl_sub_fr[bl_msg[i].d_tx_sub], bl_msg[i].d_tx_dlc, bl_msg[i].d_send_data[0], bl_msg[i].d_send_data[1], bl_msg[i].d_send_data[2], bl_msg[i].d_send_data[3], bl_msg[i].d_send_data[4], bl_msg[i].d_send_data[5], bl_msg[i].d_send_data[6], bl_msg[i].d_send_data[7] );
                            }
                            else
                            {
                            }

                            if( i == E_BL_PROG_STOP_MASTER || i == E_BL_PROG_STOP_USER )
                            {
                                ext_flag_trigger_app_reset = E_RESET_TYPE_BL;
                            }

                            if( i == E_BL_PROG_START_MASTER || i == E_BL_PROG_START_USER )
                            {
                                ext_flag_trigger_app_reset = E_RESET_TYPE_APP;
                            }
                        }
                        else
                        {
                        }
                    }
                    exit = TRUE;
                }
            }
        }
    }
}

#if USE_HAL == 1

void sfl_bl_can_receive_pre( struct_hal_can_frame_t* ptr_can_msg )
{
    struct_bl_can_frame l_can_msg;
    uint8_t i;

    l_can_msg.id = ptr_can_msg->can_id;
    l_can_msg.dlc = ptr_can_msg->can_dlc;
    if( ( l_can_msg.id >= ext_bl_sub_fr[E_SUB_BL_ADDR] ) && ( l_can_msg.id <= ext_bl_sub_fr[E_SUB_MAX - 1] ) )
    {
        for( i = 0; i < 8; i++ )
        {
            l_can_msg.data[i] = ptr_can_msg->data[i];
        }

        mgl_bl_can_rx_fifo.buffer[mgl_bl_can_rx_fifo.write_ptr] = l_can_msg;

        mgl_bl_can_rx_fifo.write_ptr++;
        if( mgl_bl_can_rx_fifo.write_ptr >= BL_CAN_RX_FIFO_BUFFER_LEN )
        {
            mgl_bl_can_rx_fifo.write_ptr = 0;
        }
        if( mgl_bl_can_rx_fifo.write_ptr == mgl_bl_can_rx_fifo.read_ptr )
        {
            mgl_bl_can_rx_fifo.read_ptr++;
            if( mgl_bl_can_rx_fifo.read_ptr >= BL_CAN_RX_FIFO_BUFFER_LEN )
            {
                mgl_bl_can_rx_fifo.read_ptr = 0;
            }
            mgl_bl_can_rx_fifo.overrun++;
        }
    }
}

#elif HCS08_MRS_LIBRARY == 1

void sfl_bl_can_receive_pre(bios_can_msg_typ* msg)
{
    struct_bl_can_frame l_can_msg;
    uint8_t i;

    l_can_msg.id = msg->id | ((uint32_t)msg->id_ext << 31);
    l_can_msg.dlc = msg->len;

    for (i=0;i<8;i++)
    {
        l_can_msg.data[i] = msg->data[i];
    }

    sfl_bl_can_receive(&l_can_msg);
}

#endif

uint8_t sfl_bl_set_flasher_state( uint8_t p_step, struct_bl_can_frame* p_msg_in, struct_bl_can_frame* p_msg_out )
{
    uint8_t ret = ERR_OK;
    (void) p_msg_in;

    ext_bl_flasher_active = 1u;
#ifdef BOOTLOADER_FLASH_ACTIVE
    (void) p_msg_out;
#else
    p_msg_out->id = ext_bl_sub_fr[bl_msg[p_step].d_tx_sub];
    p_msg_out->dlc = bl_msg[p_step].d_tx_dlc;
    p_msg_out->data[0] = bl_msg[p_step].d_send_data[0];
    p_msg_out->data[1] = bl_msg[p_step].d_send_data[1];
    p_msg_out->data[2] = (uint8_t) ( mgl_bl_sn >> 24 );
    p_msg_out->data[3] = (uint8_t) ( mgl_bl_sn >> 16 );
    p_msg_out->data[4] = (uint8_t) ( mgl_bl_sn >> 8 );
    p_msg_out->data[5] = (uint8_t) ( mgl_bl_sn );
    p_msg_out->data[6] = 0;
    p_msg_out->data[7] = 0;

    ext_flag_trigger_app_reset = E_RESET_TYPE_BL;
#endif
    return ret;
}

void sfl_bl_change_can_baudrate( struct_hal_can_handle* handle, enum_bl_baudrate_t baudrate )
{
    enum_HAL_CAN_BAUDRATE baudrate_hal = HAL_CAN_BAUD_125;
    enum_HAL_CAN_RETURN_VALUE ret = HAL_CAN_OK;
    switch( baudrate )
    {
        case E_BAUD_1MBIT:
            baudrate_hal = HAL_CAN_BAUD_1000;
        break;

        case E_BAUD_800KBIT:
            baudrate_hal = HAL_CAN_BAUD_INVALID;
        break;

        case E_BAUD_500KBIT:
            baudrate_hal = HAL_CAN_BAUD_500;
        break;

        case E_BAUD_250KBIT:
            baudrate_hal = HAL_CAN_BAUD_250;
        break;

        case E_BAUD_125KBIT:
            baudrate_hal = HAL_CAN_BAUD_125;
        break;

        case E_BAUD_50KBIT:
            baudrate_hal = HAL_CAN_BAUD_50;
        break;

        case E_BAUD_20KBIT:
            baudrate_hal = HAL_CAN_BAUD_20;
        break;

        case E_BAUD_10KBIT:
            baudrate_hal = HAL_CAN_BAUD_10;
        break;

        case E_BAUD_100KBIT:
            baudrate_hal = HAL_CAN_BAUD_100;
        break;

        case E_BAUD_83KBIT:
            baudrate_hal = HAL_CAN_BAUD_83;
        break;

        case E_BAUD_33KBIT:
            baudrate_hal = HAL_CAN_BAUD_33;
        break;

        default:
            baudrate_hal = HAL_CAN_BAUD_125;
        break;
    }

    ret = hal_can_set_baudrate( handle, baudrate_hal );

    if( ret == HAL_CAN_ERROR_BAUDRATE )
    {
        ret = hal_can_set_baudrate( handle, HAL_CAN_BAUD_125 );
    }
}

void sfl_bl_get_hw_version( uint8_t *hw_version )
{
    (void) BL_EEPROM_GET_DATA( ext_bl_par_addr[PAR_HW_VERSION], hw_version, ext_bl_par_data[PAR_HW_VERSION].length );
}


