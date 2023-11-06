#include "sfl_math.h"



int16_t os_util_lookup1D( int16_t *table_x, int16_t *table_y, uint16_t count_points, int16_t val_x, enum_LUT_MODE mode )
{


    uint16_t i, k = 0;    
    int32_t dy;
    int32_t dx = 0;
    int32_t ret;
    uint8_t val_inside;
    int16_t x2;
    int16_t y2 = 0;
    int16_t *tab_x;
    int16_t *tab_y;

    ret = 0L;
    val_inside = 0u; 

    if( ( 2u <= count_points ) &&
        ( ( LUT_MODE_MAX ) > mode ) )
    {
        x2 = table_x[count_points - 1u];


        if( val_x > x2 )
        {
            k = count_points - 2u;

            dx = x2 - val_x;

            y2 = table_y[count_points - 1u];

            if( mode == LUT_MODE_CALIBRATION )
            {

                ret = (int32_t) val_x - ( (int32_t) table_x[k] - table_y[k] );
                val_inside = 2u;
            }
        }
        else
        {

            val_inside = 1u;

            tab_x = table_x + 1u;
            for( i = 1u; i < count_points; i++ )
            {
                x2 = *tab_x;

                if( val_x <= x2 )
                {
                    k = i - 1u;
                    y2 = *( table_y + i );

                    if( val_x < *table_x )
                    {
                        x2 = *table_x;
                        y2 = *table_y;
                    }

                    dx = x2 - val_x;
                    break;
                }
                else
                {
                }

                tab_x++;

            } 
        }

        if( 2u != val_inside )
        {

            if( mode == ( LUT_MODE_LIMIT ) )
            {
                x2 = table_x[0u];
                if( val_x < x2 )
                {
                    ret = table_y[0u];
                    val_inside = 2u;
                }
            }
            else if( mode == ( LUT_MODE_MAX ) )
            {
                x2 = table_x[count_points - 1u];
                if( val_x > x2 )
                {
                    ret = table_y[count_points - 1u];
                    val_inside = 2u;
                }
            }
        }


        if( 2u != val_inside )
        {

            tab_x = table_x + k;
            tab_y = table_y + k;

            dy = (int32_t) ( *( tab_y + 1u ) - *tab_y ) * (int32_t) dx;
            dy /= (int32_t) ( *( tab_x + 1u ) - *tab_x );
            ret = y2 - dy;

        }


        if( ret > NR_MAX_INT16 )
        {
            ret = NR_MAX_INT16;
        }
        else if( ret < NR_MIN_INT16 )
        {
            ret = NR_MIN_INT16;
        }
        else
        {
        }

        if( ( ( mode == LUT_MODE_CALIBRATION ) || ( mode == LUT_MODE_EXTRAPOLATION_POS ) ) && ( ret < 0L ) )
        {
            ret = 0L;
        }
        else
        {
        }

    } 

    return ret;
}

int32_t os_util_lookup1D_32( int32_t *table_x, int32_t *table_y, uint16_t count, int32_t val, enum_LUT_MODE mode )
{


    uint16_t i, k = 0;
    int32_t m, b;
    int32_t ret;
    uint8_t val_inside = 0;

    if( val <= table_x[0] )
    {
        k = 0;
    }
    else if( val >= table_x[count - 1] )
    {
        if( ( mode == LUT_MODE_EXTRAPOLATION ) || ( mode == LUT_MODE_EXTRAPOLATION_POS ) )
        {
            k = count - 2;
        }
        else
        {
            k = count - 1;
        }

        if( mode == LUT_MODE_CALIBRATION )
        {
            ret = val - ( table_x[k] - table_y[k] );
            val_inside = 2;
        }
        else
        {
        }
    }
    else
    {
        for( i = 0; i < ( count - 1 ); i++ )
        {
            if( val < table_x[i + 1] )
            {
                k = i;
                break;
            }
            else
            {
            }
        }

        val_inside = 1;
    }

    if( ( mode == LUT_MODE_LIMIT ) && ( val_inside == 0 ) )
    {
        ret = table_y[k];
    }
    else if( val_inside != 2 )
    {
        m = ( ( table_y[k + 1] - table_y[k] ) * 1000L ) / ( table_x[k + 1] - table_x[k] );
        b = table_y[k] - ( ( m * table_x[k] ) / 1000L );
        ret = ( m * val ) / 1000L + b;
    }
    else
    {
    }

    if( ( ( mode == LUT_MODE_CALIBRATION ) || ( mode == LUT_MODE_EXTRAPOLATION_POS ) ) && ( ret < 0 ) )
    {
        ret = 0;
    }
    else
    {
    }

    return ret;
}

int16_t os_util_lookup2D( int16_t *table_x, int16_t *table_y, uint8_t count_x, uint8_t count_y, int16_t *table_z, int16_t val_x, int16_t val_y )
{

    uint8_t x, y, i, x_1, y_1, y_raw;
    int32_t m1, m2, m3, b1, b2, b3, z1, z2, z;


    x = count_x - 2;  

    for( i = 0; i < ( count_x - 1 ); i++ )
    {
        if( val_x < table_x[i + 1] )
        {
            x = i;
            break;
        }
        else
        {
        }
    }


    y_raw = count_y - 2;  
    y = y_raw * count_x;

    for( i = 0; i < ( count_y - 1 ); i++ )
    {
        if( val_y < table_y[i + 1] )
        {
            y_raw = i;              
            y = y_raw * count_x;    
            break;
        }
        else
        {
        }
    }

    x_1 = x + 1;
    y_1 = y + count_x;

    m1 = ( (int32_t) ( table_z[y + x_1] - table_z[y + x] ) * 1000L ) / (int32_t) ( table_x[x_1] - table_x[x] );   
    b1 = table_z[y + x] - ( m1 * table_x[x] ) / 1000L; 
    z1 = ( m1 * val_x ) / 1000L + b1;

    m2 = ( (int32_t) ( table_z[y_1 + x_1] - table_z[y_1 + x] ) * 1000L ) / (int32_t) ( table_x[x_1] - table_x[x] );
    b2 = table_z[y_1 + x] - ( m2 * table_x[x] ) / 1000L;
    z2 = ( m2 * val_x ) / 1000L + b2;

    m3 = ( ( z2 - z1 ) * 1000L ) / ( table_y[y_raw + 1] - table_y[y_raw] ); 
    b3 = z1 - ( m3 * table_y[y_raw] ) / 1000L;
    z = ( m3 * val_y ) / 1000L + b3;

    if( z > NR_MAX_INT16 )
    {
        z = NR_MAX_INT16;
    }
    else if( z < NR_MIN_INT16 )
    {
        z = NR_MIN_INT16;
    }
    else
    {
    }

    return (int16_t) z;
}

int32_t os_util_lookup2D_32( int32_t *table_x, int32_t *table_y, uint8_t count_x, uint8_t count_y, int32_t *table_z, int32_t val_x, int32_t val_y )
{
    uint8_t x, y, i, x_1, y_1, y_raw;
    int32_t m1, m2, m3, b1, b2, b3, z1, z2, z;


    x = count_x - 2;  

    for( i = 0; i < count_x - 1; i++ )
    {
        if( val_x < table_x[i + 1] )
        {
            x = i;
            break;
        }
    }


    y_raw = count_y - 2;  
    y = y_raw * count_x;

    for( i = 0; i < count_y - 1; i++ )
    {
        if( val_y < table_y[i + 1] )
        {
            y_raw = i;              
            y = y_raw * count_x;    
            break;
        }
    }

    x_1 = x + 1;
    y_1 = y + count_x;

    m1 = ( (int32_t) ( table_z[y + x_1] - table_z[y + x] ) * 1000L ) / (int32_t) ( table_x[x_1] - table_x[x] );   
    b1 = table_z[y + x] - ( m1 * table_x[x] ) / 1000L; 
    z1 = ( m1 * val_x ) / 1000L + b1;

    m2 = ( (int32_t) ( table_z[y_1 + x_1] - table_z[y_1 + x] ) * 1000L ) / (int32_t) ( table_x[x_1] - table_x[x] );
    b2 = table_z[y_1 + x] - ( m2 * table_x[x] ) / 1000L;
    z2 = ( m2 * val_x ) / 1000L + b2;

    m3 = ( ( z2 - z1 ) * 1000L ) / ( table_y[y_raw + 1] - table_y[y_raw] ); 
    b3 = z1 - ( m3 * table_y[y_raw] ) / 1000L;
    z = ( m3 * val_y ) / 1000L + b3;

    return z;
}


