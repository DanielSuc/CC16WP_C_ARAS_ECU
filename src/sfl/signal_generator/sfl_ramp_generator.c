
#include "sfl_ramp_generator.h"


int32_t sfl_ramp_generator( sfl_ramp_generator_control_t *ramp, uint32_t timeElapsed )
{
    int32_t return_value = 0;

    if( !ramp->ramping )
    {
        return_value = ramp->ramp_value_end;
    }
    else if( ( timeElapsed >= ramp->ramp_time ) || ( ramp->ramp_time == 0 ) )
    {
        return_value = ramp->ramp_value_end;
        ramp->ramping = 0; 						
    }
    else
    {
        return_value = ramp->ramp_value_start + ( ramp->ramp_value_end - ramp->ramp_value_start ) * ( (float) timeElapsed / ramp->ramp_time );
    }
    return return_value;
}

