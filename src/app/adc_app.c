#include "adc_app.h"
#include "adConvCom1.h"
#include "sfl_math.h"
#include "io_tables.h"
#include "hal_io.h"
#include "adc_app.h"
#include "user_api_io.h"
#include "modulhardwarecode.h"
#include "ftm_app.h"

#include "defines_general.h"
#include "role_types.h"
#include "ee_helper.h"
#include "role_protocol_bl.h"
#include "role.h"


#define CALIBR_MAX_ADC_VAL          (4095u)
#define CALIBR_MAX_VOLT_VAL         (5000u)

#define ADC_INA_OUT_N               (8u)
#define ADC_SENSE_N                 (4u)
#define SENSE_MULTIPLEXED_N         (2u)
#define ADC_CALIBR_INP_N            (ADC_INA_OUT_N + SENSE_MULTIPLEXED_N * ADC_SENSE_N)

#define CALIB_POINTS_SOURCE     3 
#define CALIB_POINTS_SINK       3 
#define CALIB_PAIR              2 
#define CALIB_DATA_TYPE    int16_t

#define CALIB_VAL_SIZE     ( (CALIB_POINTS_SOURCE + CALIB_POINTS_SINK) * CALIB_PAIR * sizeof(CALIB_DATA_TYPE) )

FILENUM(89)   
floating_avg_values_data_t mgl_mean_current_value[ADC_INA_OUT_N] ;

struct_adc_results_t adc_results[ADC_MAX] ;
uint16_t adc_interrupt_values[ADC_MAX] ;

uint8_t mgl_multiplex_group_max = 0u;

uint32_t mgl_adc_counter[ADC_INSTANCE_COUNT] ; 

uint8_t adc_results_to_adc_channel_index[ADC_MAX];

void pdb_init(void);

uint32_t adc_get_counter(uint8_t adc_instance, IRQn_Type adc_interrupt);

void pdb_init(void)
{

    PDB_DRV_Init(INST_PDB1, &pdbCom_InitConfig0);
    PDB_DRV_Enable(INST_PDB1);

    PDB_DRV_Init(INST_PDB2, &pdbCom_InitConfig0);
    PDB_DRV_Enable(INST_PDB2);



    pdb_adc_pretrigger_config_t pdb_pretrigger_config={.preTriggerEnable = true};
    uint32_t pdb_channel_index[PDB_INSTANCE_COUNT] = {0}, pdb_pretrigger_index[PDB_INSTANCE_COUNT] = {0}, adc_instance;

    for (uint8_t i = 0; i < ADC_MAX; i++)
    {

    	adc_instance = adc_config_tbl[i].adc_instance;
    	ASSERT( !(pdb_channel_index[adc_instance] >= PDB_CH_COUNT) ); 

        if (adc_config_tbl[i].multiplex == 0)
        {

        	if(pdb_pretrigger_index[adc_instance])
        	{
        		pdb_pretrigger_config.adcPreTriggerIdx = pdb_pretrigger_index[adc_instance];
        		pdb_pretrigger_config.preTriggerOutputEnable = false;
        		pdb_pretrigger_config.preTriggerBackToBackEnable = true;

        		PDB_DRV_ConfigAdcPreTrigger(adc_instance, pdb_channel_index[adc_instance], &pdb_pretrigger_config);
        	}
        	else
        	{
        		pdb_pretrigger_config.adcPreTriggerIdx = 0;
        		pdb_pretrigger_config.preTriggerOutputEnable = true;
        		pdb_pretrigger_config.preTriggerBackToBackEnable = false;

        		PDB_DRV_ConfigAdcPreTrigger(adc_instance, pdb_channel_index[adc_instance], &pdb_pretrigger_config);
        	}

        	if ( ++pdb_pretrigger_index[adc_instance] >= 8) 
        	{
        		pdb_pretrigger_index[adc_instance] = 0;
        		pdb_channel_index[adc_instance]++;
        	}
        }
    }


    uint32_t delayValue = 4000;

        PDB_DRV_SetTimerModulusValue(INST_PDB1, (uint32_t)delayValue);
        PDB_DRV_SetAdcPreTriggerDelayValue(INST_PDB1, 0UL, 0UL, ((uint32_t)delayValue/4)*0);
        PDB_DRV_SetAdcPreTriggerDelayValue(INST_PDB1, 1UL, 0UL, ((uint32_t)delayValue/4)*1);
        PDB_DRV_SetTimerModulusValue(INST_PDB2, (uint32_t)delayValue);
        PDB_DRV_SetAdcPreTriggerDelayValue(INST_PDB2, 0UL, 0UL, ((uint32_t)delayValue/4)*0);
        PDB_DRV_SetAdcPreTriggerDelayValue(INST_PDB2, 1UL, 0UL, ((uint32_t)delayValue/4)*1);

#if (defined(S32K148))	
        PDB_DRV_SetAdcPreTriggerDelayValue(INST_PDB1, 2UL, 0UL, ((uint32_t)delayValue/4)*2 );
        PDB_DRV_SetAdcPreTriggerDelayValue(INST_PDB1, 3UL, 0UL, ((uint32_t)delayValue/4)*3 );

        PDB_DRV_SetAdcPreTriggerDelayValue(INST_PDB2, 2UL, 0UL, ((uint32_t)delayValue/4)*2);
        PDB_DRV_SetAdcPreTriggerDelayValue(INST_PDB2, 3UL, 0UL, ((uint32_t)delayValue/4)*3 );

#endif
        PDB_DRV_LoadValuesCmd(INST_PDB1);
        PDB_DRV_SoftTriggerCmd(INST_PDB1);

        PDB_DRV_LoadValuesCmd(INST_PDB2);
        PDB_DRV_SoftTriggerCmd(INST_PDB2);

}


void ADC_init(void)
{
    ADC_DRV_ConfigConverter(INST_ADCONV1, &adConv_ConvConfig);
    ADC_DRV_ConfigConverter(INST_ADCONV2, &adConv_ConvConfig);


	uint16_t *cal_data_identifier = (uint16_t*)ee_read(CALIBR_EE_TABLE_START_ADDR);
	bool run_autocalibration = true;

	switch(*cal_data_identifier)
	{
	case 0xFFFF:
		run_autocalibration = true;
		break;
	case 28083: 
		run_autocalibration = false;
		break;
	default:
		run_autocalibration = true;
		break;
	}

    if(run_autocalibration)
    {
		ADC_DRV_AutoCalibration(INST_ADCONV1);
		ADC_DRV_AutoCalibration(INST_ADCONV2);
    }

#if 0
    adc_calibration_t user_calib_config;

    if (*(uint16_t*) ee_read(CALIBR_EE_TABLE_MODULE_ADDR) == 28085)
    {
        user_calib_config.userGain = 
        user_calib_config.userOffset = 
    }
    else 
    {
        user_calib_config.userGain = 0;
        user_calib_config.userOffset = 0;
    }

    ADC_DRV_ConfigUserCalibration(INST_ADCONV1, &user_calib_config_adc);
    ADC_DRV_ConfigUserCalibration(INST_ADCONV2, &user_calib_config_adc);
#endif

    uint16_t last_channel[ADC_INSTANCE_COUNT] = {0}; 
    for (uint8_t i = 0; i < ADC_MAX; i++)
    {
    	if( !adc_config_tbl[i].multiplex )
    	{
    		last_channel[adc_config_tbl[i].adc_instance] = i;
    	}
    }

    uint16_t current_channel[ADC_INSTANCE_COUNT] = {0};     
    for (uint8_t i = 0; i < ADC_MAX; i++)
    {
    	uint8_t adc_instance = adc_config_tbl[i].adc_instance;

        if (adc_config_tbl[i].multiplex == 0)
        {
        	adc_chan_config_t channel_config;
        	channel_config.channel = adc_config_tbl[i].adc_channel;
        	channel_config.interruptEnable = false;
            if( last_channel[adc_instance] == i )
            {
            	channel_config.interruptEnable = true;
            }
        	adc_results_to_adc_channel_index[i] = current_channel[adc_instance];

        	ADC_DRV_ConfigChan(adc_instance, current_channel[adc_instance], &channel_config);
        	current_channel[adc_instance]++;
        }
        else
        {

        	for(uint8_t j = 0; j < ADC_MAX; j++)
        	{
        		if( (adc_config_tbl[i].adc_instance == adc_config_tbl[j].adc_instance) && (adc_config_tbl[i].adc_channel == adc_config_tbl[j].adc_channel) && !adc_config_tbl[j].multiplex )
        		{
        			adc_results_to_adc_channel_index[i] = j;
        			break;
        		}
        	}
            if (adc_config_tbl[i].multiplex_group > mgl_multiplex_group_max)
            {
                mgl_multiplex_group_max++;
            }
        }
    }

    INT_SYS_InstallHandler(ADC0_IRQn, &ADC1_IRQHandler, (isr_t*) 0);
    INT_SYS_InstallHandler(ADC1_IRQn, &ADC2_IRQHandler, (isr_t*) 0);


    pdb_init();


    INT_SYS_EnableIRQ(ADC0_IRQn);
    INT_SYS_EnableIRQ(ADC1_IRQn);
}

void ADC_IRQHandler(uint8_t pdb_instance, uint8_t adc_instance)
{
    for (uint8_t i = 0; i < ADC_MAX; i++)
    {
        if ((adc_config_tbl[i].adc_instance == adc_instance) && !adc_config_tbl[i].multiplex)
        {
                ADC_DRV_GetChanResult(adc_config_tbl[i].adc_instance, adc_results_to_adc_channel_index[i], &(adc_interrupt_values[i]));
        }
    }

    PDB_DRV_SoftTriggerCmd(pdb_instance);
    mgl_adc_counter[adc_instance]++;
}

void ADC1_IRQHandler(void)
{
    ADC_IRQHandler(INST_PDB1, INST_ADCONV1);
}

void ADC2_IRQHandler(void)
{
    ADC_IRQHandler(INST_PDB2, INST_ADCONV2);
}


uint32_t adc_get_counter(uint8_t adc_instance, IRQn_Type adc_interrupt)
{
    uint32_t counter;

    INT_SYS_DisableIRQ(adc_interrupt); 
    counter = mgl_adc_counter[adc_instance];
    INT_SYS_EnableIRQ(adc_interrupt);

    return counter;
}

uint32_t adc_get_measurement_range(enum_adc_pin_name const pin)
{
	uint32_t range = adc_config_tbl[pin].adc_vrefh;
#if ADC_SECOND_RANGE
	range = modulhardwarecode_adc_get_vrefh2(pin, range);
#endif

	return range;
}


uint16_t adc_get_module_type()
{
    uint16_t *ptr = (uint16_t*)ee_read(CALIBR_EE_TABLE_MODULE_ADDR);
    uint16_t tmp = (NULL != ptr) ? (*ptr) : 0u;
    return tmp;
}

void adc_copy_results_from_interrupt(uint8_t adc_instance, uint8_t* adc_done_flag, uint32_t* adc_counter, IRQn_Type adc_interrupt )
{
    uint32_t tmp_counter;

    tmp_counter = adc_get_counter(adc_instance, adc_interrupt);


    if (tmp_counter != *adc_counter)
    {
        *adc_done_flag = 1;

        INT_SYS_DisableIRQ(adc_interrupt);
        for ( uint8_t i = 0; i < ADC_MAX; ++i )
        {
            if((adc_config_tbl[i].adc_instance == adc_instance) && !adc_config_tbl[i].multiplex)
            {
                adc_results[i].result_raw = adc_interrupt_values[i];
            }

        }
        INT_SYS_EnableIRQ(adc_interrupt);
        *adc_counter = tmp_counter; 
    }
}


void adc_processing(uint8_t *multiplex_group, bool hw_calibration_support)
{
    static uint32_t adc1_counter = 0, adc2_counter = 0;
    uint8_t adc_inst1_done = 0, adc_inst2_done = 0;
    static uint32_t multiplex_adc1_counter = 0, multiplex_adc2_counter = 0; 
    bool right_multiplex_group = FALSE, adc1_stability_cnt_passed = FALSE, adc2_stability_cnt_passed = FALSE; 
    uint8_t number_points = 0;

    adc_copy_results_from_interrupt(INST_ADCONV1, &adc_inst1_done, &adc1_counter, ADC0_IRQn);
    adc_copy_results_from_interrupt(INST_ADCONV2, &adc_inst2_done, &adc2_counter, ADC1_IRQn);

    adc1_stability_cnt_passed = (((adc1_counter) - (multiplex_adc1_counter)) >= MULTIPLEX_STABILITY_CYCLES);
    adc2_stability_cnt_passed = (((adc2_counter) - (multiplex_adc2_counter)) >= MULTIPLEX_STABILITY_CYCLES);

    if (adc_inst1_done == 1 || adc_inst2_done == 1)
    {
        for ( uint8_t i = 0; i < ADC_MAX; ++i )
        {
            right_multiplex_group = *multiplex_group == adc_config_tbl[i].multiplex_group;

            if ( adc_config_tbl[i].multiplex )
            {
                if ( (right_multiplex_group) && (adc1_stability_cnt_passed && adc2_stability_cnt_passed) )
                {
                    adc_results[i].result_digit = adc_results[adc_results_to_adc_channel_index[i]].result_raw;
                }
            }
            else
            {
                adc_results[i].result_digit = adc_results[i].result_raw;
            }


            if(hw_calibration_support)
            {
                if ( adc_config_tbl[i].cal_type != CALIB_NONE )
                {
                    int16_t *ptr = (int16_t*) ee_read(CALIBR_EE_TABLE_DATA_ADDR + adc_config_tbl[i].cal_index);

                    if ( NULL == ptr || -1 == *ptr )
                    {
                        adc_results[i].result_cal = 0;
                        adc_results[i].result_filtered = (adc_results[i].result_filtered*(AD_FILTER-1) + adc_results[i].result_digit) / AD_FILTER;
                    }
                    else
                    {
                        switch ( adc_config_tbl[i].cal_type )
                        {
                            case CALIB_SOURCE_3P: 
                                number_points = 3;
                                adc_results[i].result_cal = os_util_lookup1D(ptr, ptr + number_points, number_points,adc_results[i].result_digit, LUT_MODE_EXTRAPOLATION_POS);
                                break;

                            case CALIB_SOURCE_SINK_3P: 
                                number_points = 3;
                                    adc_results[i].result_cal = os_util_lookup1D(ptr, ptr + number_points, number_points,adc_results[i].result_digit, LUT_MODE_EXTRAPOLATION_POS);
                                break;

                            default: 
                                adc_results[i].result_cal = 0;
                                break;

                        }
                        adc_results[i].result_filtered = (adc_results[i].result_filtered*(AD_FILTER-1) + adc_results[i].result_cal) / AD_FILTER;
                    }
                }
            }
            else
            {
                adc_results[i].result_filtered = (adc_results[i].result_filtered*(AD_FILTER-1) + adc_results[i].result_digit) / AD_FILTER;
            }
        }
#if FLOATING_AVG
        static floating_avg_data_t mean_filter_data[ADC_INA_OUT_N] = {0};
        for ( int i = 0; i < ADC_INA_OUT_N; ++i )
        {
            mean_filter_data[i].amount_of_values = mgl_mean_current_value[i].amount_values;
            add_to_float_avg(&mean_filter_data[i], adc_results[i+AI_INA_OUT0].result_cal);
            mgl_mean_current_value[i].current_value = adc_calc_float_avg(&mean_filter_data[i]);
        }
#endif
    }

    if ( (adc1_stability_cnt_passed) && (adc2_stability_cnt_passed) )
    {
        multiplex_adc1_counter = adc1_counter;
        multiplex_adc2_counter = adc2_counter;
        *multiplex_group = (1 + *multiplex_group) % (mgl_multiplex_group_max + 1);
        modulhardwarecode_adc_multiplex(*multiplex_group);
    }
}

void add_to_float_avg(floating_avg_data_t *float_avg_data, uint16_t new_value)
{
	if ( float_avg_data->amount_of_values > 0 )
	{
		if ( float_avg_data->amount_of_values > AD_FILTER )
		{
			float_avg_data->amount_of_values = AD_FILTER;
		}
		float_avg_data->a_data[float_avg_data->index_next_value] = new_value;
		float_avg_data->index_next_value++;
		float_avg_data->index_next_value %= float_avg_data->amount_of_values;

		float_avg_data->amount_of_values = 1;
	}
	else
	{

	}
}


uint16_t adc_calc_float_avg(floating_avg_data_t *float_avg_data)
{
	uint32_t o_Result = 0u;

	if ( float_avg_data->amount_of_values > 0 )
	{
		if ( float_avg_data->amount_of_values > AD_FILTER )
		{
			float_avg_data->amount_of_values = AD_FILTER;
		}
		uint32_t temp_sum = 0;
		for ( uint16_t i = 0; i < (float_avg_data->amount_of_values); ++i )
		{
			temp_sum += (uint32_t) float_avg_data->a_data[i];
		}
		o_Result = (temp_sum / float_avg_data->amount_of_values);
	}
	else
	{
		o_Result = 0u;
	}

	return (uint16_t) o_Result;
}


uint16_t get_mean_analog_value(enum_adc_pin_name analog_pin, uint8_t AmountValues)
{
    mgl_mean_current_value[analog_pin-(ADC_INA_OUT_N-1)].amount_values = AmountValues;
    return mgl_mean_current_value[analog_pin-(ADC_INA_OUT_N-1)].current_value;
}

uint16_t get_mean_analog_value_exact(enum_adc_pin_name analog_pin)
{
    return mgl_mean_current_value[analog_pin-(ADC_INA_OUT_N-1)].current_value;
}


