#ifndef IO_TABLES_H
#define IO_TABLES_H

#include "pins_driver.h"
#include "hal_data_types.h"
#include "flexTimerCom1.h"

#define NUM_OF_CONFIGURED_PINS 89
#define PD_NONE 3
#define PD_OUT GPIO_OUTPUT_DIRECTION
#define PD_IN GPIO_INPUT_DIRECTION
#define PORT_INTERNAL_PULL_DOW_ENABLED PORT_INTERNAL_PULL_DOWN_ENABLED
#define DOX_SHIFT_IN_DS DO_SHIFT_IN_DS

/* custom pin names defined in applics pin editor */
 

typedef enum
{
    CALIB_NONE                      = 0u,     ///< No Calibration at all
    CALIB_SOURCE_1P                     ,     ///< 1 sink or source points
    CALIB_SOURCE_2P                     ,     ///< 2 sink or source points
    CALIB_SOURCE_3P                     ,     ///< 3 sink or source points
    CALIB_SOURCE_4P                     ,     ///< 4 sink or source points
    CALIB_SOURCE_SINK_1P                ,     ///< 1 sink and source points
    CALIB_SOURCE_SINK_2P                ,     ///< 2 sink and source points
    CALIB_SOURCE_SINK_3P                ,     ///< 3 sink and source points
    CALIB_SOURCE_SINK_4P                      ///< 4 sink and source points
} enum_adc_CALIBRATION_TYPE;

/* enum which contains the names of all available pins of the MCU */
typedef enum
{
// PORTA                               ,
DI_AI_OUT1                = 0          ,
DI_AI_OUT4                             ,
DI_AI_OUT6                             ,
DI_AI_OUT7                             ,
MC_JTAG_TMS                            ,
MC_JTAG_TRST                           ,
DI_AI_A_IN3                            ,
DI_AI_A_IN2                            ,
MC_SCI_RXD                             ,
MC_SCI_TXD                             ,
MC_JTAG_TDO                            ,
CAN_EN1                                ,
MC_CAN_RXD2                            ,
MC_CAN_TXD2                            ,
CAN_WAKE1                              ,
DI_AI_OUT2                             ,
DI_AI_OUT3                             ,
DI_PGD                                 ,
// PORTB                               ,
DI_AI_A_IN1                            ,
DI_AI_A_IN0                            ,
DI_AI_INA_OUT4                         ,
DI_AI_INA_OUT7                         ,
DO_HSD1_OUT1                           ,
DO_HSD1_OUT3                           ,
XTAL                                   ,
EXTAL                                  ,
DO_RS2                                 ,
MC_FREQ_A_IN4                          ,
MC_FREQ_A_IN5                          ,
DO_RS4                                 ,
DI_AI_SNS4                             ,
DI_AI_SNS1                             ,
DI_AI_SNS2                             ,
DI_AI_A_IN5                            ,
DI_AI_A_IN4                            ,
DO_RS5                                 ,
// PORTC                               ,
DI_AI_INA_OUT3                         ,
DI_AI_INA_OUT2                         ,
DI_AI_KL30_1                           ,
DI_AI_KL30_2                           ,
MC_JTAG_TCLK                           ,
MC_JTAG_TDI                            ,
DI_AI_VARIANTE                         ,
DI_AI_ID                               ,
DO_RS3                                 ,
DO_RS0                                 ,
MC_FREQ_A_IN0                          ,
MC_FREQ_A_IN1                          ,
MC_FREQ_A_IN2                          ,
MC_FREQ_A_IN3                          ,
DI_AI_INA_OUT5                         ,
DI_AI_INA_OUT6                         ,
DI_AI_INA_OUT0                         ,
DI_AI_INA_OUT1                         ,
// PORTD                               ,
DO_SHIFT_SH_CP                         ,
DO_SHIFT_ST_CP                         ,
DI_AI_OUT5                             ,
DI_AI_VREF                             ,
DI_AI_SNS3                             ,
DO_HSD2_OUT4                           ,
DOX_SHIFT_IN_DS                        ,
DI_INTERFACE2_A                        ,
DI_INTERFACE2_B                        ,
DO_HSD2_OUT6                           ,
DO_VREF_EN                             ,
DO_CS_HSD2                             ,
DO_HSD2_OUT5                           ,
DI_KL15                                ,
DO_HSD1_OUT0                           ,
DO_POWER                               ,
DO_HSD2_OUT7                           ,
DO_CS_HSD1                             ,
// PORTE                               ,
CAN_ERR1                               ,
CAN_STB1                               ,
Pin74                                  ,
CAN_STB2                               ,
MC_CAN_RXD1                            ,
MC_CAN_TXD1                            ,
DI_AI_OUT0                             ,
DO_RS1                                 ,
DO_HSD1_OUT2                           ,
LIN_EN                                 ,
Pin82                                  ,
WD                                     ,
CAN_EN2                                ,
CAN_ERR2                               ,
CAN_WAKE2                              ,
DO_SHIFT_OE                            ,
DO_SHIFT_MR                            ,
PIN_MAX                                ,
 
}enum_pin_name;


/* enum which contains the names of the virtual pins*/
typedef enum
{
DCDC_8V5                  = PIN_MAX          ,
DCDC_10V                                     ,
PD_A_IN5                                     ,
PD_A_IN4                                     ,
PD_A_IN3                                     ,
PD_A_IN2                                     ,
PD_A_IN1                                     ,
PD_A_IN0                                     ,
PU_A_IN5                                     ,
PU_A_IN4                                     ,
PU_A_IN3                                     ,
PU_A_IN2                                     ,
PU_A_IN1                                     ,
PU_A_IN0                                     ,
VIRTUAL_PIN_MAX                              ,
 
}enum_virtual_pin_name;


/* enum which contains the names of the PWM channels */
typedef enum
{
PWM_HSD1_OUT0           = 0          ,
PWM_HSD1_OUT1                        ,
PWM_HSD1_OUT2                        ,
PWM_HSD1_OUT3                        ,
PWM_HSD2_OUT4                        ,
PWM_HSD2_OUT5                        ,
PWM_HSD2_OUT6                        ,
PWM_HSD2_OUT7                        ,
PWM_MAX                              ,
FREQ_A_IN1                           ,
FREQ_A_IN2                           ,
FREQ_A_IN3                           ,
FREQ_A_IN4                           ,
FREQ_A_IN5                           ,
FREQ_A_IN0                           ,
FREQ_MAX                             ,
 
}enum_pwm_pin_name;


/* enum which contains the names of the ADC channels */
typedef enum
{
AI_A_IN0                   = 0          ,
AI_A_IN1                                ,
AI_A_IN2                                ,
AI_A_IN3                                ,
AI_A_IN4                                ,
AI_A_IN5                                ,
AI_ID                                   ,
AI_INA_OUT0                             ,
AI_INA_OUT1                             ,
AI_INA_OUT2                             ,
AI_INA_OUT3                             ,
AI_INA_OUT4                             ,
AI_INA_OUT5                             ,
AI_INA_OUT6                             ,
AI_INA_OUT7                             ,
AI_KL30_1                               ,
AI_KL30_2                               ,
AI_OUT0                                 ,
AI_OUT1                                 ,
AI_OUT2                                 ,
AI_OUT3                                 ,
AI_OUT4                                 ,
AI_OUT5                                 ,
AI_OUT6                                 ,
AI_OUT7                                 ,
AI_INTERNAL_TEMP                        ,
AI_HSD1_CUR3                            ,
AI_HSD1_CUR2                            ,
AI_HSD1_CUR1                            ,
AI_HSD1_CUR0                            ,
AI_HSD2_CUR7                            ,
AI_HSD2_CUR6                            ,
AI_HSD2_CUR5                            ,
AI_HSD2_CUR4                            ,
AI_VARIANTE                             ,
AI_VREF                                 ,
AI_SNS1                                 ,
AI_SNS2                                 ,
AI_SNS3                                 ,
AI_SNS4                                 ,
ADC_MAX                                 ,
 
}enum_adc_pin_name;

extern pin_settings_config_t g_pin_mux_InitConfigArr[NUM_OF_CONFIGURED_PINS];

/*! @brief ADC structure io_tables
 * Implements : adc_config_tbl
 */
typedef struct
{
 
        uint8_t adc_instance;                   // Define on which instance the channel is
        uint8_t adc_channel;                    // Define the number of the channel
        uint32_t adc_vrefh;
        uint32_t resolution;
        _Bool multiplex;                        //Define if this Pin is a multiplex input and thus not connected physically to the processor
        uint8_t multiplex_group;                //Define which to which multiplex group this pin belongs (further information in modulhardwarecode_adc_multiplex)
        uint16_t cal_index;                     //Contains the Index on which address the calibration values has been saved in the eeprom. 0 if there are no values available
        enum_adc_CALIBRATION_TYPE cal_type;     //what kind of calibration is used.
}struct_adc_config_t;


typedef struct
{
    uint8_t pwm_instance;                   // PWM instance of the resembling pin
    uint8_t pwm_channel;                    // PWM channel of the resembling pinS
    enum_adc_pin_name adc_pin_name;
}struct_FTM_CONFIG;

typedef struct
{
        enum_virtual_pin_name name; // Virtual pin name
        uint8_t current_val;        // current_value of the virtual pin
}struct_VIRTUAL_PINS_CFG;/*! @brief Declaration of the ADC structure */

typedef struct
{
    enum_adc_pin_name adc_pin_name;  //
    enum_pwm_pin_name pwm_pin_name;  //
}struct_io_pin_linker_t;

extern const struct_adc_config_t adc_config_tbl[ADC_MAX + 1];

extern struct_VIRTUAL_PINS_CFG virtual_pin[VIRTUAL_PIN_MAX - PIN_MAX];

extern const struct_io_pin_linker_t io_pin_linker[VIRTUAL_PIN_MAX];

extern const struct_FTM_CONFIG struct_ftm_config_tbl[FREQ_MAX + 1];


#endif 
