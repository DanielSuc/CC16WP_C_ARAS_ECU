#ifndef SRC_APP_USER_API_USER_API_UTIL_H_
#define SRC_APP_USER_API_USER_API_UTIL_H_
#include <stdint.h>
#include "sfl_math.h"


uint16_t user_lookup_1D_16(int16_t *table_x, int16_t *table_y, uint16_t count, int16_t val, enum_LUT_MODE mode);
#define user_util_get_lookup_value_1D_16( table_x,table_y,count,val,mode ) user_lookup_1D_16( table_x,table_y,count,val,mode )


uint32_t user_lookup_1D_32 (int32_t *table_x, int32_t *table_y, uint16_t count, int32_t val, enum_LUT_MODE mode);
#define user_util_get_lookup_value_1D_32( table_x,table_y,count,val,mode ) user_lookup_1D_32( table_x,table_y,count,val,mode )


uint16_t user_lookup_2D_16(int16_t *table_x, int16_t *table_y, uint16_t count_x, uint16_t count_y, int16_t *table_z, int16_t val_x, int16_t val_y);
#define user_util_get_lookup_value_2D_16( table_x,table_y,count_x,count_y,table_z,val_x,val_y ) user_lookup_2D_16( table_x,table_y,count_x,count_y,table_z,val_x,val_y )


uint32_t user_lookup_2D_32(int32_t *table_x, int32_t *table_y, uint16_t count_x, uint16_t count_y, int32_t *table_z, int32_t val_x, int32_t val_y);
#define user_util_get_lookup_value_2D_32( table_x,table_y,count_x,count_y,table_z,val_x,val_y ) user_lookup_2D_32( table_x,table_y,count_x,count_y,table_z,val_x,val_y )


#endif 

