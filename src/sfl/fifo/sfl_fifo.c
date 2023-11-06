#include "sfl_fifo.h"
#include "hal_sys.h"
#include <string.h>




enum_SFL_FIFO_ERROR_CODES sfl_fifo_init( SFL_FIFO_CONFIG_TYPE* config, uint32_t element_count, uint32_t element_size )
{
    enum_SFL_FIFO_ERROR_CODES retval = SFL_FIFO_ERROR_NONE;
    if( ( config == 0 ) || ( element_count < 1 ) || ( element_size < 1 ) )
    {
        retval = SFL_FIFO_ERROR_PARAM;
    }
    else
    {
        config->count = 0;
        config->max = element_count;
        config->next_write = 0;
        config->next_read = 0;
        config->write_in_progress = 0;
        config->read_in_progress = 0;
        config->read_lock = SFL_FIFO_READLOCK_DISABLED;
        config->element_size = element_size;
    }
    return retval;
}

uint32_t sfl_fifo_get_count( SFL_FIFO_CONFIG_TYPE* config )
{
    uint32_t ret = 0;
    ret = config->count;
    return ret;
}

uint32_t sfl_fifo_get_free( SFL_FIFO_CONFIG_TYPE* config )
{
    uint32_t ret = 0;
    ret = ( config->max - config->count );
    return ret;
}

void sfl_fifo_lock_read( SFL_FIFO_CONFIG_TYPE* config )
{
    hal_sys_disable_all_interrupts();
    config->read_lock = SFL_FIFO_READLOCK_ENABLED;
    hal_sys_enable_all_interrupts();
}

void sfl_fifo_unlock_read( SFL_FIFO_CONFIG_TYPE* config )
{
    hal_sys_disable_all_interrupts();
    config->read_lock = SFL_FIFO_READLOCK_DISABLED;
    hal_sys_enable_all_interrupts();
}

enum_SFL_FIFO_READLOCK_TYPE sfl_fifo_get_read_lock( SFL_FIFO_CONFIG_TYPE* config )
{
    enum_SFL_FIFO_READLOCK_TYPE ret;
    hal_sys_disable_all_interrupts();
    ret = config->read_lock;
    hal_sys_enable_all_interrupts();
    return ret;
}

enum_SFL_FIFO_ERROR_CODES sfl_fifo_put( SFL_FIFO_CONFIG_TYPE* config, uint8_t* new_data, uint8_t* buff )
{
    enum_SFL_FIFO_ERROR_CODES retval = SFL_FIFO_ERROR_UNKNOWN;
    hal_sys_disable_all_interrupts();
    if( config->write_in_progress == 0 )
    {
        config->write_in_progress = 1;

        if( ( config->count + 1 ) > config->max )
        {
            retval = SFL_FIFO_ERROR_OVERFLOW;
        }
        else
        {

            uint8_t* tempbuffer = buff;
            tempbuffer += config->next_write * config->element_size;
            memcpy( tempbuffer, new_data, config->element_size );

            ( config->next_write )++;
            if( config->next_write >= config->max )
            {
                ( config->next_write ) = 0;
            }
            else
            {
            }
            ( config->count )++;

            retval = SFL_FIFO_ERROR_NONE;
        }
        config->write_in_progress = 0;
    }
    else
    {
        retval = SFL_FIFO_ERROR_BUSY;
    }
    hal_sys_enable_all_interrupts();
    return retval;
}

enum_SFL_FIFO_ERROR_CODES sfl_fifo_get( SFL_FIFO_CONFIG_TYPE* config, uint8_t* result, uint8_t* buff )
{
    enum_SFL_FIFO_ERROR_CODES retval = SFL_FIFO_ERROR_UNKNOWN;
    hal_sys_disable_all_interrupts();
    if( config->read_in_progress == 0 )
    {
        config->read_in_progress = 1;
        if( ( config->count ) > 0 )
        {

            uint8_t* tempbuffer = buff;
            tempbuffer += config->next_read * config->element_size;
            memcpy( result, tempbuffer, config->element_size );

            ( config->next_read )++;
            if( config->next_read >= config->max )
            {
                config->next_read = 0;
            }
            else
            {
            }
            ( config->count )--;

            retval = SFL_FIFO_ERROR_NONE;
        }
        else
        {
            retval = SFL_FIFO_ERROR_EMPTY;
        }
        config->read_in_progress = 0;
    }
    else
    {
        retval = SFL_FIFO_ERROR_BUSY;
    }
    hal_sys_enable_all_interrupts();
    return retval;
}

enum_SFL_FIFO_ERROR_CODES sfl_fifo_get_preview( SFL_FIFO_CONFIG_TYPE* config, uint8_t* result, uint8_t* buff )
{
    enum_SFL_FIFO_ERROR_CODES retval = SFL_FIFO_ERROR_UNKNOWN;
    if( config->read_in_progress == 0 )
    {
        config->read_in_progress = 1;
        if( ( config->count ) > 0 )
        {
            uint8_t* tempbuffer = buff;
            tempbuffer += config->next_read * config->element_size;
            memcpy( result, tempbuffer, config->element_size );

            retval = SFL_FIFO_ERROR_NONE;
        }
        else
        {
            retval = SFL_FIFO_ERROR_EMPTY;
        }
        config->read_in_progress = 0;
    }
    else
    {
        retval = SFL_FIFO_ERROR_BUSY;
    }
    return retval;
}

enum_SFL_FIFO_ERROR_CODES sfl_fifo_search( uint8_t* val, SFL_FIFO_CONFIG_TYPE* config, int32_t* result, uint8_t* buff )
{
    enum_SFL_FIFO_ERROR_CODES retval = SFL_FIFO_ERROR_NONE;
    uint32_t act_pos;   
    uint32_t read_index;    
    uint32_t i;         
    uint32_t j;         
    uint8_t bytes_different = 0;
    uint32_t tmp_cnt; 
    uint32_t e_size;
    uint32_t max;
    tmp_cnt = config->count; 
    read_index = config->next_read;
    e_size = config->element_size;
    act_pos = read_index * config->element_size;
    max = config->max;

    *result = -1;

    if( tmp_cnt == 0 )
    {
        retval = SFL_FIFO_ERROR_EMPTY;

    }
    else
    {
        for( i = 0; i < tmp_cnt; ++i )
        {
            bytes_different = 0;
            for( j = 0; j < ( e_size ); ++j )
            {
                if( buff[act_pos + j] != val[j] )
                {
                    bytes_different = 1;
                    j = ( e_size );
                }
                else
                {
                }
            }

            if( bytes_different == 0 )
            {
                *result = read_index;  
                i = tmp_cnt; 
            }
            else
            {
                read_index++;

                if( read_index >= max )
                {
                    read_index = 0;
                }
                else
                {
                }

                act_pos = read_index * e_size;

            } 
        } 
    } 
    return retval;
}

enum_SFL_FIFO_ERROR_CODES sfl_fifo_remove( SFL_FIFO_CONFIG_TYPE* config, uint32_t count )
{
    enum_SFL_FIFO_ERROR_CODES retval = SFL_FIFO_ERROR_NONE;
    uint32_t tmp_count;

    hal_sys_disable_all_interrupts();
    if( count > ( config->count ) )
    {
        retval = SFL_FIFO_ERROR_PARAM;
    }
    else
    {
        config->read_in_progress = 1;
        tmp_count = ( config->next_read ) + count;

        if( tmp_count < ( config->next_read ) )
        {
            retval = SFL_FIFO_ERROR_UNKNOWN;
        }
        else
        {
            if( tmp_count >= config->max )
            {
                tmp_count = tmp_count - config->max;
            }
            else
            {
            }
            config->next_read = tmp_count;
            config->count -= count;
        }

        config->read_in_progress = 0;
        retval = SFL_FIFO_ERROR_NONE;

    }
    hal_sys_enable_all_interrupts();
    return retval;
}

uint32_t sfl_fifo_get_distance( uint32_t actual, uint32_t destination, uint32_t max )
{
    uint32_t count = 0;
    if( destination > actual )
    {
        count = destination - actual;
    }
    else
    {
        count = max - actual + destination;
    }
    return count;
}

enum_SFL_FIFO_ERROR_CODES sfl_fifo_clear( SFL_FIFO_CONFIG_TYPE* config )
{
    enum_SFL_FIFO_ERROR_CODES retval = SFL_FIFO_ERROR_NONE;

    if( ( config->write_in_progress == 0 ) && ( config->read_in_progress == 0 ) )
    {
        hal_sys_disable_all_interrupts();

        config->count = 0;
        config->next_write = 0;
        config->next_read = 0;
        config->write_in_progress = 0;
        config->read_in_progress = 0;

        hal_sys_enable_all_interrupts();
    }
    else
    {
        retval = SFL_FIFO_ERROR_BUSY;
    }

    return retval;
}


