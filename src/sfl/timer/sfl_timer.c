#include "sfl_timer.h"

static uint8_t mgl_roundtrip_init_flg = FALSE;      

void sfl_timer_init( void )
{
    mgl_roundtrip_init_flg = FALSE;
}

void sfl_timer_deinit( void )
{
}

enum_SFL_TIMER_ERR sfl_timer_set_timestamp( uint32_t* timestamp, enum_HAL_PRECISION precision )
{
    volatile enum_SFL_TIMER_ERR ret_val = SFL_TIMER_ERR_OK;

    if( hal_get_timestamp( timestamp, precision ) != HAL_TICK_OK )
    {
        ret_val = SFL_TIMER_ERR_PRECISION_INVALID;
    }

    else
    {
    }

    return ret_val;
}

enum_SFL_TIMER_ERR sfl_timer_get_time_elapsed( uint32_t* time_elapsed, uint32_t timestamp_t0, enum_HAL_PRECISION precision )
{
    volatile enum_SFL_TIMER_ERR ret_val = SFL_TIMER_ERR_GENERAL;
    uint32_t timestamp_now = 0;

    if( hal_get_timestamp( &timestamp_now, precision ) != HAL_TICK_OK )
    {
        ret_val = SFL_TIMER_ERR_PRECISION_INVALID;
    }
    else
    {
        *time_elapsed = timestamp_now - timestamp_t0;
        ret_val = SFL_TIMER_ERR_OK;
    }

    return ret_val;
}

enum_SFL_TIMER_ERR sfl_timer_time_elapsed( uint8_t* elapsed, uint32_t timestamp_t0, uint32_t span, enum_HAL_PRECISION precision )
{
    volatile enum_SFL_TIMER_ERR ret_val = SFL_TIMER_ERR_GENERAL;
    uint32_t time_elapsed = 0;

    ret_val = sfl_timer_get_time_elapsed( &time_elapsed, timestamp_t0, precision );
    if( ( ret_val == SFL_TIMER_ERR_OK ) )
    {
        if( time_elapsed >= span )
        {
            *elapsed = TRUE;
        }

        else
        {
            *elapsed = FALSE;
        }
    }
    else
    {
    }

    return ret_val;
}

enum_SFL_TIMER_ERR sfl_timer_wait( uint32_t wait_time, enum_HAL_PRECISION precision )
{
    uint32_t act_time = 0;
    uint8_t elapsed = FALSE;

    sfl_timer_set_timestamp( &act_time, precision );

    while( elapsed == FALSE )
    {
        (void) sfl_timer_time_elapsed( &elapsed, act_time, wait_time, precision );
    }

    return SFL_TIMER_ERR_OK;
}

enum_SFL_TIMER_ERR sfl_timer_get_roundtrip_time( uint32_t* roundtrip_time, enum_HAL_PRECISION precision )
{
    volatile enum_SFL_TIMER_ERR ret_val = SFL_TIMER_ERR_OK;
    static uint32_t timestamp_t0 = 0u;
    static uint32_t timestamp_t1 = 0u;

    if( mgl_roundtrip_init_flg == FALSE )
    {
        if( hal_get_timestamp( &timestamp_t0, precision ) != HAL_TICK_OK )
        {
            ret_val = SFL_TIMER_ERR_PRECISION_INVALID;
        }

        else
        {
            *roundtrip_time = timestamp_t0;

            mgl_roundtrip_init_flg = TRUE;
        }
    }

    else
    {
        if( hal_get_timestamp( &timestamp_t1, precision ) != HAL_TICK_OK )
        {
            ret_val = SFL_TIMER_ERR_PRECISION_INVALID;
        }

        else
        {
            if( timestamp_t0 < timestamp_t1 )
            {
                *roundtrip_time = timestamp_t1 - timestamp_t0;
            }

            else
            {
                *roundtrip_time = timestamp_t0 - timestamp_t1;
            }

            timestamp_t0 = timestamp_t1;
        }
    }

    return ret_val;
}


