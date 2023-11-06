
#ifndef SFL_RAMP_GENERATOR_SFL_RAMP_GENERATOR_H_
#define SFL_RAMP_GENERATOR_SFL_RAMP_GENERATOR_H_

#include "hal_data_types.h"

typedef struct
{
    bool ramping;
    int32_t ramp_value_start;
    int32_t ramp_value_end;
    uint32_t ramp_time;
    uint32_t ramp_time_start;
} sfl_ramp_generator_control_t;

extern int32_t sfl_ramp_generator( sfl_ramp_generator_control_t *ramp, uint32_t timeElapsed );

#endif 

