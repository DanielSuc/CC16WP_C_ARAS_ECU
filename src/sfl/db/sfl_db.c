#include "sfl_db.h"



uint8_t private_sfl_db_invert_bitorder_in_byte( uint8_t val_in )
{
    uint8_t val_out = val_in;

    val_out = ( ( val_out & 0xF0 ) >> 4 ) | ( ( val_out & 0x0F ) << 4 ); 
    val_out = ( ( val_out & 0xCC ) >> 2 ) | ( ( val_out & 0x33 ) << 2 ); 
    val_out = ( ( val_out & 0xAA ) >> 1 ) | ( ( val_out & 0x55 ) << 1 ); 

    return val_out;
}

uint32_t sfl_db_change_intel_to_motorola_32_bit( uint32_t val_in )
{
    uint32_t val_out;

    val_out = ( ( val_in & 0x000000fful ) << 24 ) + ( ( val_in & 0x0000ff00ul ) << 8 )
        + ( ( val_in & 0x00ff0000ul ) >> 8 ) + ( ( val_in & 0xff000000ul ) >> 24 );

    return val_out;
}

void sfl_db_put_signal_value_to_data_block( uint32_t value, uint8_t* ptr_to_data_block, uint16_t startbit, uint16_t length, uint8_t data_format )
{
    uint16_t index_startbyte;   
    uint16_t sh_left;           
    uint16_t counter;           

    uint32_t maske;
    uint32_t value_block;


    if( startbit > 511 )
    {
        return;
    }
    if( ( startbit + length ) > 512 ) 
    {
        return;
    }

    if( ( length > 32 ) || !length )
    {
        return;
    }

    if( ( ( startbit & 0x07 ) + length ) > 32 )
    {
        return;
    }

    maske = 0;

    for( counter = 0; counter < length; counter++ )
    {
        maske = ( maske << 1 ) | 0x00000001;  
    }
    index_startbyte = startbit >> 3;


    value_block = (uint32_t) *( ptr_to_data_block + index_startbyte )
        + ( (uint32_t) *( ptr_to_data_block + index_startbyte + 1 ) << 8 )
        + ( (uint32_t) *( ptr_to_data_block + index_startbyte + 2 ) << 16 )
        + ( (uint32_t) *( ptr_to_data_block + index_startbyte + 3 ) << 24 );

    value &= maske;

    if( data_format == TRUE )
    {

        sh_left = (uint16_t) ( 32 - ( ( startbit & 0x07 ) + length ) );
        value <<= sh_left; 

        value = sfl_db_change_intel_to_motorola_32_bit( value );
        maske <<= sh_left;

        maske = sfl_db_change_intel_to_motorola_32_bit( maske );
    }
    else
    {
        sh_left = startbit & 0x07;
        value <<= sh_left;
        maske <<= sh_left;
    }

    maske = value_block & ~maske;

    value_block = value | maske;


    *( ptr_to_data_block + index_startbyte ) = (uint8_t) ( value_block & 0x000000ffL );
    *( ptr_to_data_block + index_startbyte + 1 ) = (uint8_t) ( ( value_block & 0x0000ff00L ) >> 8 );
    *( ptr_to_data_block + index_startbyte + 2 ) = (uint8_t) ( ( value_block & 0x00ff0000L ) >> 16 );
    *( ptr_to_data_block + index_startbyte + 3 ) = (uint8_t) ( ( value_block & 0xff000000L ) >> 24 );

    return;
}

uint32_t sfl_db_get_signal_value_from_data_block(uint8_t* ptr_to_data_block, uint16_t startbit, uint16_t length, uint8_t data_format, uint8_t data_type)
{
    uint16_t index_startbyte;
    uint16_t counter;

    uint32_t result;
    uint32_t mask;

    if( startbit > 511 )
    {
        return 0;
    }
    else
    {
    }

    if( ( startbit + length ) > 512 )
    {
        return 0;
    }
    else
    {
    }

    if( ( length > 32 ) || !length )
    {
        return 0;
    }
    else
    {
    }

    if( ( ( startbit & 0x07 ) + length ) > 32 )
    {
        return 0;
    }
    else
    {
    }

    index_startbyte = startbit >> 3;

    if( data_format == TRUE )
    {
        result = (uint32_t)*(ptr_to_data_block + index_startbyte + 3) + ((uint32_t)*(ptr_to_data_block + index_startbyte + 2) << 8)
        + ((uint32_t)*(ptr_to_data_block + index_startbyte + 1) << 16) + ((uint32_t)*(ptr_to_data_block + index_startbyte) << 24);

        result >>= (uint8_t)(32 - ((startbit & 0x07) + length));
    }
    else
    {
        result = (uint32_t)*(ptr_to_data_block + index_startbyte) + ((uint32_t)*(ptr_to_data_block + index_startbyte + 1) << 8)
        + ((uint32_t)*(ptr_to_data_block + index_startbyte + 2) << 16) + ((uint32_t)*(ptr_to_data_block + index_startbyte + 3) << 24);

        result >>= (startbit & 0x07);
    }

    mask = 0;

    for(counter = 0; counter < length; counter++)
    {
        mask = ( mask << 1 ) | 0x00000001;
    }

    result &= mask;

    if( (data_type == SINT) || (data_type == SLONG) || (data_type == SBYTE) )
    {
        for( counter = 32; counter > 0; counter--)
        {
            if( counter <= length )
            {
                mask = (mask << 1) | 0x00000000;
            }
            else
            {
                if( (result >> (length - 1) ) == 1 )
                {
                    mask = (mask << 1) | 0x00000001;
                }
                else
                {
                    mask = (mask << 1) | 0x00000000;
                }

            }
        }

        result ^= mask;
    }


    return result;
}

#if ARCHITECTURE_64BIT
uint64_t sfl_db_change_intel_to_motorola_64_bit(uint64_t val_in)
{
    uint64_t val_out;

    val_out = ( ((val_in & 0x00000000000000FF) << 56) + ((val_in & 0x000000000000FF00) << 40)
        + ((val_in & 0x0000000000FF0000) << 24) + ((val_in & 0x00000000FF000000) << 8)
        + ((val_in & 0x000000FF00000000) >> 8) + ((val_in & 0x0000FF0000000000) >> 24)
        + ((val_in & 0x00FF000000000000) >> 40) + ((val_in & 0xFF00000000000000) >> 56) );

    return val_out;
}

void sfl_db_put_signal_value_to_data_block_64(uint64_t value, uint8_t* ptr_to_data_block, uint16_t startbit, uint16_t length, uint8_t data_format)
{
    uint8_t index_startbyte;
    uint8_t sh_left;
    uint8_t counter;

    uint64_t maske;
    uint64_t value_block;

    if( startbit > 63 )
    {
        return;
    }

    if( (startbit + length) > 64 )
    {
        return;
    }

    if( (length > 64) || !length )
    {
        return;
    }

    maske = 0;

    for(counter = 0; counter < length; counter++)
    {
        maske = (maske << 1) | 0x00000001;
    }

    index_startbyte = startbit >> 3;

    value_block = (uint64_t)*(ptr_to_data_block + index_startbyte)
    + ((uint64_t)*(ptr_to_data_block + index_startbyte + 1) << 8)
    + ((uint64_t)*(ptr_to_data_block + index_startbyte + 2) << 16)
    + ((uint64_t)*(ptr_to_data_block + index_startbyte + 3) << 24)
    + ((uint64_t)*(ptr_to_data_block + index_startbyte + 4) << 32)
    + ((uint64_t)*(ptr_to_data_block + index_startbyte + 5) << 40)
    + ((uint64_t)*(ptr_to_data_block + index_startbyte + 6) << 48)
    + ((uint64_t)*(ptr_to_data_block + index_startbyte + 7) << 56);

    value &= maske;

    if (data_format == TRUE)
    {
        sh_left = (uint8_t)(64 - ((startbit & 0x07) + length));
        value <<= sh_left;

        value = sfl_db_change_intel_to_motorola_64_bit(value);
        maske <<= sh_left;

        maske = sfl_db_change_intel_to_motorola_64_bit(maske);
    }
    else
    {
        sh_left = startbit & 0x07;
        value <<= sh_left;
        maske <<= sh_left;
    }

    maske = value_block & ~maske;

    value_block = value | maske;

    *(ptr_to_data_block + index_startbyte) = (uint8_t) (value_block & 0x00000000000000ffL);
    *(ptr_to_data_block + index_startbyte + 1) = (uint8_t)((value_block & 0x000000000000ff00L) >> 8);
    *(ptr_to_data_block + index_startbyte + 2) = (uint8_t)((value_block & 0x0000000000ff0000L) >> 16);
    *(ptr_to_data_block + index_startbyte + 3) = (uint8_t)((value_block & 0x00000000ff000000L) >> 24);
    *(ptr_to_data_block + index_startbyte + 4) = (uint8_t)((value_block & 0x000000ff00000000L) >> 32);
    *(ptr_to_data_block + index_startbyte + 5) = (uint8_t)((value_block & 0x0000ff0000000000L) >> 40);
    *(ptr_to_data_block + index_startbyte + 6) = (uint8_t)((value_block & 0x00ff000000000000L) >> 48);
    *(ptr_to_data_block + index_startbyte + 7) = (uint8_t)((value_block & 0xff00000000000000L) >> 56);

    return;
}

uint64_t sfl_db_get_signal_value_from_data_block_64(uint8_t* ptr_to_data_block, uint16_t startbit, uint16_t length, uint8_t data_format)
{
    uint8_t index_startbyte;
    uint8_t counter;

    uint64_t value;
    uint64_t mask;

    if( startbit > 63 )
    {
        return 0;
    }
    else
    {
    }

    if( (startbit + length) > 64 )
    {
        return 0;
    }
    else
    {
    }

    if( (length > 64) || !length )
    {
        return 0;
    }
    else
    {
    }

    index_startbyte = startbit >> 3;

    if (data_format == TRUE)
    {
        value = (uint64_t)*(ptr_to_data_block + index_startbyte + 7)
        + ((uint64_t)*(ptr_to_data_block + index_startbyte + 6) << 8)
        + ((uint64_t)*(ptr_to_data_block + index_startbyte + 5) << 16)
        + ((uint64_t)*(ptr_to_data_block + index_startbyte + 4) << 24)
        + ((uint64_t)*(ptr_to_data_block + index_startbyte + 3) << 32)
        + ((uint64_t)*(ptr_to_data_block + index_startbyte + 2) << 40)
        + ((uint64_t)*(ptr_to_data_block + index_startbyte + 1) << 48)
        + ((uint64_t)*(ptr_to_data_block + index_startbyte) << 56);

        value >>= (uint8_t)(64 - ((startbit & 0x07) + length));
    }
    else
    {
        value = (uint64_t)*(ptr_to_data_block + index_startbyte)
        + ((uint64_t)*(ptr_to_data_block + index_startbyte + 1) << 8)
        + ((uint64_t)*(ptr_to_data_block + index_startbyte + 2) << 16)
        + ((uint64_t)*(ptr_to_data_block + index_startbyte + 3) << 24)
        + ((uint64_t)*(ptr_to_data_block + index_startbyte + 4) << 32)
        + ((uint64_t)*(ptr_to_data_block + index_startbyte + 5) << 40)
        + ((uint64_t)*(ptr_to_data_block + index_startbyte + 6) << 48)
        + ((uint64_t)*(ptr_to_data_block + index_startbyte + 7) << 56);

        value >>= (startbit & 0x07);
    }

    mask = 0;

    for(counter = 0; counter < length; counter++)
    {
        mask = (mask << 1) | 0x00000001;
    }

    value &= mask;

    return value;
}
#endif 


