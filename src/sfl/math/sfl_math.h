#ifndef SFL_MATH_H
#define SFL_MATH_H


#include "hal_data_types.h"

#define NR_MAX_INT16    32767       
#define NR_MIN_INT16   -32768       

typedef enum
{
    LUT_MODE_EXTRAPOLATION = 0,      
    LUT_MODE_LIMIT,      
    LUT_MODE_CALIBRATION,      
    LUT_MODE_EXTRAPOLATION_POS,     
    LUT_MODE_MAX                    
} enum_LUT_MODE;


int16_t os_util_lookup1D( int16_t *table_x, int16_t *table_y, uint16_t count_points, int16_t val_x, enum_LUT_MODE mode );

int32_t os_util_lookup1D_32( int32_t *table_x, int32_t *table_y, uint16_t count, int32_t val, enum_LUT_MODE mode );

int16_t os_util_lookup2D( int16_t *table_x, int16_t *table_y, uint8_t count_x, uint8_t count_y, int16_t *table_z, int16_t val_x, int16_t val_y );

int32_t os_util_lookup2D_32( int32_t *table_x, int32_t *table_y, uint8_t count_x, uint8_t count_y, int32_t *table_z, int32_t val_x, int32_t val_y );

#endif

