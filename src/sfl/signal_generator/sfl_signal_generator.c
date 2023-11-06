
#include "sfl_timer.h"
#include "sfl_signal_generator.h"


extern struct_SG_CONFIG_TABLE sg_config_table[];

static enum_SG_RETURN_VALUE private_sfl_sg_set_command( struct_SG_HANDLER* ptrSgHandler )
{
    enum_SG_RETURN_VALUE ret_val = SG_OK;

    switch( sg_config_table[ptrSgHandler->internalCommand].BaseMode )
    {
        case SG_BASE_MODE_CONTINUOUS_OFF:

            ptrSgHandler->internalOutputState = SG_OUTPUT_STATE_OFF;

            ptrSgHandler->internalSignalProcessingState = SG_SIGNAL_PROCESSING_PROCESS_IDLE;

        break;

        case SG_BASE_MODE_CONTINUOUS_ON:

            ptrSgHandler->internalOutputState = SG_OUTPUT_STATE_ON;

            ptrSgHandler->internalPitch1 = sg_config_table[ptrSgHandler->internalCommand].Pitch1;
            ptrSgHandler->internalLoudness = sg_config_table[ptrSgHandler->internalCommand].Loudness;
            ptrSgHandler->internalBrightness = sg_config_table[ptrSgHandler->internalCommand].Brightness;

            ptrSgHandler->internalOutputPitch = ptrSgHandler->internalPitch1;

            ptrSgHandler->internalSignalProcessingState = SG_SIGNAL_PROCESSING_PROCESS_IDLE;

        break;

        case SG_BASE_MODE_TOGGLE:

            ptrSgHandler->internalToggleState = SG_OUTPUT_STATE_ON;
            ptrSgHandler->internalOutputState = SG_OUTPUT_STATE_ON;

            ptrSgHandler->internalTimePulse = sg_config_table[ptrSgHandler->internalCommand].TimePulse;
            ptrSgHandler->internalTimeBreak = sg_config_table[ptrSgHandler->internalCommand].TimeBreak;
            ptrSgHandler->internalOnTime = sg_config_table[ptrSgHandler->internalCommand].OnTime;
            ptrSgHandler->internalOnCount = sg_config_table[ptrSgHandler->internalCommand].OnCount;
            ptrSgHandler->internalPitch1 = sg_config_table[ptrSgHandler->internalCommand].Pitch1;
            ptrSgHandler->internalOnPitch = sg_config_table[ptrSgHandler->internalCommand].OnPitch;
            ptrSgHandler->internalLoudness = sg_config_table[ptrSgHandler->internalCommand].Loudness;
            ptrSgHandler->internalBrightness = sg_config_table[ptrSgHandler->internalCommand].Brightness;

            ptrSgHandler->internalOutputPitch = ptrSgHandler->internalPitch1;

            (void) sfl_timer_set_timestamp( &( ptrSgHandler->internalPulseTimer ), HAL_PRECISION_1MS );

        break;

        case SG_BASE_MODE_DELAY_ON:

            ptrSgHandler->internalOutputState = SG_OUTPUT_STATE_OFF;

            ptrSgHandler->internalTimePulse = sg_config_table[ptrSgHandler->internalCommand].TimePulse;
            ptrSgHandler->internalTimeBreak = sg_config_table[ptrSgHandler->internalCommand].TimeBreak;
            ptrSgHandler->internalPitch1 = sg_config_table[ptrSgHandler->internalCommand].Pitch1;
            ptrSgHandler->internalLoudness = sg_config_table[ptrSgHandler->internalCommand].Loudness;
            ptrSgHandler->internalBrightness = sg_config_table[ptrSgHandler->internalCommand].Brightness;

            ptrSgHandler->internalOutputPitch = ptrSgHandler->internalPitch1;

            ptrSgHandler->internalSignalProcessingState = SG_SIGNAL_PROCESSING_PROCESS_IN_PROGRESS;

            (void) sfl_timer_set_timestamp( &( ptrSgHandler->internalPulseTimer ), HAL_PRECISION_1MS );

        break;

        case SG_BASE_MODE_DELAY_OFF:

            ptrSgHandler->internalOutputState = SG_OUTPUT_STATE_ON;

            ptrSgHandler->internalTimePulse = sg_config_table[ptrSgHandler->internalCommand].TimePulse;
            ptrSgHandler->internalTimeBreak = sg_config_table[ptrSgHandler->internalCommand].TimeBreak;
            ptrSgHandler->internalPitch1 = sg_config_table[ptrSgHandler->internalCommand].Pitch1;
            ptrSgHandler->internalLoudness = sg_config_table[ptrSgHandler->internalCommand].Loudness;
            ptrSgHandler->internalBrightness = sg_config_table[ptrSgHandler->internalCommand].Brightness;

            ptrSgHandler->internalOutputPitch = ptrSgHandler->internalPitch1;

            ptrSgHandler->internalSignalProcessingState = SG_SIGNAL_PROCESSING_PROCESS_IN_PROGRESS;

            (void) sfl_timer_set_timestamp( &( ptrSgHandler->internalBreakTimer ), HAL_PRECISION_1MS );

        break;

        default:

            ret_val = SG_ERROR_BASE_MODE_INVALID;

        break;
    }

    return ret_val;
}

static enum_SG_RETURN_VALUE private_sfl_sg_set_command_on_time( struct_SG_HANDLER* ptrSgHandler )
{
    enum_SG_RETURN_VALUE ret_val = SG_OK;

    if( sg_config_table[ptrSgHandler->internalCommand].BaseMode == SG_BASE_MODE_TOGGLE )
    {
        (void) sfl_timer_set_timestamp( &( ptrSgHandler->internalOnCommandTimer ), HAL_PRECISION_1MS );

        ret_val = private_sfl_sg_set_command( ptrSgHandler );
    }

    else
    {
        ret_val = SG_ERROR_BASE_MODE_INVALID;
    }

    return ret_val;
}

static enum_SG_RETURN_VALUE private_sfl_sg_set_command_on_count( struct_SG_HANDLER* ptrSgHandler )
{
    enum_SG_RETURN_VALUE ret_val = SG_OK;

    if( sg_config_table[ptrSgHandler->internalCommand].BaseMode == SG_BASE_MODE_TOGGLE )
    {
        ptrSgHandler->internalSetCommandOnCountValue = 0u;

        ret_val = private_sfl_sg_set_command( ptrSgHandler );
    }

    else
    {
        ret_val = SG_ERROR_BASE_MODE_INVALID;
    }

    return ret_val;
}

static enum_SG_RETURN_VALUE private_sfl_sg_generate_toggle( struct_SG_HANDLER* ptrSgHandler )
{
    enum_SG_RETURN_VALUE ret_val = SG_OK;
    uint8_t elapsed_pulse = FALSE;
    uint8_t elapsed_break = FALSE;

    if( ( ptrSgHandler->internalTimePulse == 0u ) ||
        ( ptrSgHandler->internalTimeBreak == 0u ) )
    {
        ret_val = SG_ERROR_SETTING_UNDEFINED;
    }

    else
    {
        (void) sfl_timer_time_elapsed( &elapsed_pulse, ptrSgHandler->internalPulseTimer, ptrSgHandler->internalTimePulse, HAL_PRECISION_1MS );
        (void) sfl_timer_time_elapsed( &elapsed_break, ptrSgHandler->internalBreakTimer, ptrSgHandler->internalTimeBreak, HAL_PRECISION_1MS );

        if( ptrSgHandler->internalToggleState == SG_OUTPUT_STATE_ON )
        {
            if( elapsed_pulse == TRUE )
            {
                (void) sfl_timer_set_timestamp( &( ptrSgHandler->internalBreakTimer ), HAL_PRECISION_1MS );

                ptrSgHandler->internalToggleState = SG_OUTPUT_STATE_OFF;

                if( ptrSgHandler->internalOnPitch != 0u )
                {
                    ptrSgHandler->internalOutputPitch = ptrSgHandler->internalOnPitch;
                }

                else
                {
                    ptrSgHandler->internalOutputPitch = 0u;
                }
            }

            else
            {
            }
        }

        else
        {
            if( elapsed_break == TRUE )
            {
                (void) sfl_timer_set_timestamp( &( ptrSgHandler->internalPulseTimer ), HAL_PRECISION_1MS );

                if( ptrSgHandler->internalOnCount != 0u )
                {
                    ptrSgHandler->internalSetCommandOnCountValue++;

                    if( ptrSgHandler->internalSetCommandOnCountValue >= ptrSgHandler->internalOnCount )
                    {
                        ptrSgHandler->internalToggleState = SG_OUTPUT_STATE_OFF;
                        ptrSgHandler->internalSignalProcessingState = SG_SIGNAL_PROCESSING_PROCESS_IDLE;
                    }

                    else
                    {
                        ptrSgHandler->internalToggleState = SG_OUTPUT_STATE_ON;

                        ptrSgHandler->internalOutputPitch = ptrSgHandler->internalPitch1;
                    }
                }

                else if( ptrSgHandler->internalOnPitch != 0u )
                {
                    ptrSgHandler->internalSetCommandOnCountValue++;

                    if( ptrSgHandler->internalSetCommandOnCountValue >= 1u )
                    {
                        ptrSgHandler->internalOutputPitch = 0u;
                        ptrSgHandler->internalToggleState = SG_OUTPUT_STATE_OFF;
                        ptrSgHandler->internalSignalProcessingState = SG_SIGNAL_PROCESSING_PROCESS_IDLE;
                    }

                    else
                    {
                        ptrSgHandler->internalToggleState = SG_OUTPUT_STATE_ON;

                        ptrSgHandler->internalOutputPitch = ptrSgHandler->internalPitch1;
                    }
                }

                else
                {
                    ptrSgHandler->internalToggleState = SG_OUTPUT_STATE_ON;

                    ptrSgHandler->internalOutputPitch = ptrSgHandler->internalPitch1;
                }
            }

            else
            {
            }
        }

        if( ptrSgHandler->internalOnPitch == 0u )
        {
            ptrSgHandler->internalOutputState = ptrSgHandler->internalToggleState;
        }
    }

    return ret_val;
}

static enum_SG_RETURN_VALUE private_sfl_sg_generate_delay( struct_SG_HANDLER* ptrSgHandler )
{
    enum_SG_RETURN_VALUE ret_val = SG_OK;
    uint8_t elapsed = FALSE;

    if( ( ptrSgHandler->internalTimePulse != 0u ) &&
        ( ptrSgHandler->internalTimeBreak == 0u ) )
    {
        (void) sfl_timer_time_elapsed( &elapsed, ptrSgHandler->internalPulseTimer, ptrSgHandler->internalTimePulse, HAL_PRECISION_1MS );

        if( elapsed == TRUE )
        {
            ptrSgHandler->internalOutputState = SG_OUTPUT_STATE_ON;

            ptrSgHandler->internalOutputPitch = ptrSgHandler->internalPitch1;

            ptrSgHandler->internalSignalProcessingState = SG_SIGNAL_PROCESSING_PROCESS_IDLE;
        }

        else
        {
            ptrSgHandler->internalOutputState = SG_OUTPUT_STATE_OFF;

            ptrSgHandler->internalOutputPitch = 0u;
        }
    }

    else if( ( ptrSgHandler->internalTimePulse == 0u ) &&
        ( ptrSgHandler->internalTimeBreak != 0u ) )
    {
        (void) sfl_timer_time_elapsed( &elapsed, ptrSgHandler->internalBreakTimer, ptrSgHandler->internalTimeBreak, HAL_PRECISION_1MS );

        if( elapsed == TRUE )
        {
            ptrSgHandler->internalOutputState = SG_OUTPUT_STATE_OFF;

            ptrSgHandler->internalSignalProcessingState = SG_SIGNAL_PROCESSING_PROCESS_IDLE;

            ptrSgHandler->internalOutputPitch = 0u;
        }

        else
        {
            ptrSgHandler->internalOutputState = SG_OUTPUT_STATE_ON;

            ptrSgHandler->internalOutputPitch = ptrSgHandler->internalPitch1;
        }
    }

    else
    {
        ret_val = SG_ERROR_SETTING_UNDEFINED;
    }

    return ret_val;
}

enum_SG_RETURN_VALUE sfl_sg_init( struct_SG_HANDLER* ptrSgHandler )
{
    enum_SG_RETURN_VALUE ret_val = SG_OK;

    ptrSgHandler->internalCommand = 0u;
    ptrSgHandler->internalOutputState = SG_OUTPUT_STATE_OFF;
    ptrSgHandler->internalToggleState = SG_OUTPUT_STATE_OFF;
    ptrSgHandler->internalOutputPitch = 0u;
    ptrSgHandler->internalTimePulse = 0u;
    ptrSgHandler->internalTimeBreak = 0u;
    ptrSgHandler->internalOnTime = 0u;
    ptrSgHandler->internalOnCount = 0u;
    ptrSgHandler->internalOnPitch = 0u;
    ptrSgHandler->internalLoudness = SG_OUTPUT_LOUDNESS_QUIET;
    ptrSgHandler->internalPitch1 = 0u;
    ptrSgHandler->internalPulseTimer = UINT32_MAX;
    ptrSgHandler->internalBreakTimer = UINT32_MAX;
    ptrSgHandler->internalOnCommandTimer = UINT32_MAX;
    ptrSgHandler->internalSetCommandOnCountValue = 0u;
    ptrSgHandler->internalSignalProcessingState = SG_SIGNAL_PROCESSING_PROCESS_NOT_SET;
    ptrSgHandler->internalBrightness = 0u;

    return ret_val;
}

enum_SG_RETURN_VALUE sfl_sg_process_command( uint16_t command,
    struct_SG_HANDLER* ptrSgHandler )
{
    enum_SG_RETURN_VALUE ret_val = SG_OK;

    if( command != sg_config_table[command].Command )
    {
        ret_val = SG_ERROR_CONFIG_TABLE;
    }

    else
    {
        ptrSgHandler->internalCommand = command;

        if( sg_config_table[ptrSgHandler->internalCommand].OnTime != 0u )
        {
            ret_val = private_sfl_sg_set_command_on_time( ptrSgHandler );

            ptrSgHandler->internalSignalProcessingState = SG_SIGNAL_PROCESSING_PROCESS_IN_PROGRESS;
        }

        else if( sg_config_table[ptrSgHandler->internalCommand].OnCount != 0u )
        {
            ret_val = private_sfl_sg_set_command_on_count( ptrSgHandler );

            ptrSgHandler->internalSignalProcessingState = SG_SIGNAL_PROCESSING_PROCESS_IN_PROGRESS;
        }

        else if( sg_config_table[ptrSgHandler->internalCommand].OnPitch != 0u )
        {
            ret_val = private_sfl_sg_set_command_on_count( ptrSgHandler );

            ptrSgHandler->internalSignalProcessingState = SG_SIGNAL_PROCESSING_PROCESS_IN_PROGRESS;
        }

        else
        {
            ptrSgHandler->internalSignalProcessingState = SG_SIGNAL_PROCESSING_PROCESS_IDLE;

            ret_val = private_sfl_sg_set_command( ptrSgHandler );
        }
    }

    return ret_val;
}

enum_SG_RETURN_VALUE sfl_sg_process_cyclic( struct_SG_HANDLER* ptrSgHandler )
{
    enum_SG_RETURN_VALUE ret_val = SG_OK;
    uint8_t elapsed = FALSE;

    if( ptrSgHandler->internalSignalProcessingState != SG_SIGNAL_PROCESSING_PROCESS_NOT_SET )
    {
        switch( sg_config_table[ptrSgHandler->internalCommand].BaseMode )
        {
            case SG_BASE_MODE_CONTINUOUS_OFF:


            break;

            case SG_BASE_MODE_CONTINUOUS_ON:


            break;

            case SG_BASE_MODE_TOGGLE:

                if( ptrSgHandler->internalOnTime != 0u )
                {
                    (void) sfl_timer_time_elapsed( &elapsed, ptrSgHandler->internalOnCommandTimer, ptrSgHandler->internalOnTime, HAL_PRECISION_1MS );

                    if( elapsed == TRUE )
                    {
                        ptrSgHandler->internalOutputState = SG_OUTPUT_STATE_OFF;
                        ptrSgHandler->internalToggleState = SG_OUTPUT_STATE_OFF;

                        ptrSgHandler->internalSignalProcessingState = SG_SIGNAL_PROCESSING_PROCESS_IDLE;
                    }

                    else
                    {
                        ret_val = private_sfl_sg_generate_toggle( ptrSgHandler );
                    }
                }

                else if( ptrSgHandler->internalOnCount != 0u )
                {
                    if( ( ptrSgHandler->internalSetCommandOnCountValue >= ptrSgHandler->internalOnCount ) &&
                        ( ptrSgHandler->internalSignalProcessingState == SG_SIGNAL_PROCESSING_PROCESS_IDLE ) )
                    {
                        ptrSgHandler->internalOutputState = SG_OUTPUT_STATE_OFF;
                    }

                    else
                    {
                        ret_val = private_sfl_sg_generate_toggle( ptrSgHandler );
                    }
                }

                else if( ptrSgHandler->internalOnPitch != 0u )
                {
                    if( ( ptrSgHandler->internalSetCommandOnCountValue >= 1u ) &&
                        ( ptrSgHandler->internalSignalProcessingState == SG_SIGNAL_PROCESSING_PROCESS_IDLE ) )
                    {
                        ptrSgHandler->internalOutputState = SG_OUTPUT_STATE_OFF;
                    }

                    else
                    {
                        ret_val = private_sfl_sg_generate_toggle( ptrSgHandler );
                    }
                }

                else
                {
                    ret_val = private_sfl_sg_generate_toggle( ptrSgHandler );
                }

            break;

            case SG_BASE_MODE_DELAY_OFF:

                ret_val = private_sfl_sg_generate_delay( ptrSgHandler );

            break;

            case SG_BASE_MODE_DELAY_ON:

                ret_val = private_sfl_sg_generate_delay( ptrSgHandler );

            break;

            default:

                ret_val = SG_ERROR_BASE_MODE_INVALID;

            break;
        }
    }

    else
    {
        ret_val = SG_ERROR_SETTING_UNDEFINED;
    }

    return ret_val;
}

enum_OUTPUT_STATE sfl_sg_get_output_state( struct_SG_HANDLER* ptrSgHandler )
{
    return ptrSgHandler->internalOutputState;
}

uint32_t sfl_sg_get_pitch( struct_SG_HANDLER* ptrSgHandler )
{
    return ptrSgHandler->internalOutputPitch;
}

uint32_t sfl_sg_get_loudness( struct_SG_HANDLER* ptrSgHandler )
{
    return ptrSgHandler->internalLoudness;
}

uint16_t sfl_sg_get_brightness( struct_SG_HANDLER* ptrSgHandler )
{
    return ptrSgHandler->internalBrightness;
}

enum_SG_SIGNAL_PROCESSING sfl_sg_get_signal_processing_state( struct_SG_HANDLER* ptrSgHandler )
{
    return ptrSgHandler->internalSignalProcessingState;
}

struct_SG_CONFIG_TABLE* sfl_sg_get_config_table( void )
{
    return &sg_config_table[0u];
}



