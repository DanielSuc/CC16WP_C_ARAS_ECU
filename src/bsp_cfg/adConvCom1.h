
#ifndef BSP_CFG_ADCONVCOM1_H_
#define BSP_CFG_ADCONVCOM1_H_

#include "adc_driver.h"
#include "io_tables.h"


#define INST_ADCONV1 (0U)
#define INST_ADCONV2 (1U)

extern const adc_converter_config_t adConv_ConvConfig;


typedef struct
{
        const adc_chan_config_t channel_cfg;   
        enum_pin_name io_pin_name;              
}struct_adc_init_config_t;


#endif 

