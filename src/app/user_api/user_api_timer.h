#ifndef SRC_USER_API_TIMER_H_
#define SRC_USER_API_TIMER_H_

#include <stdint.h>

typedef enum
{
    PRECISION_1US    = 0u,   
    PRECISION_10US       ,   
    PRECISION_100US      ,   
    PRECISION_1MS        ,   
    PRECISION_10MS       ,   
    PRECISION_100MS      ,   
    PRECISION_1S             
}enum_PRECISION;


uint8_t user_set_timestamp(uint32_t* timestamp, enum_PRECISION precision);
#define user_timer_set_timestamp( timestamp, precision ) user_set_timestamp( timestamp, precision )


uint8_t user_time_past(uint32_t timestamp_t0, uint32_t span, enum_PRECISION precision);
#define user_timer_time_elapsed( timestamp_t0,span,precision ) user_time_past( timestamp_t0,span,precision )


uint8_t user_get_roundtrip_time(uint32_t* roundtrip_time, enum_PRECISION precision, uint8_t reset_start);
#define user_timer_get_prog_cycletime( roundtrip_time, precision,reset_start ) user_get_roundtrip_time( roundtrip_time, precision,reset_start )


#endif 

