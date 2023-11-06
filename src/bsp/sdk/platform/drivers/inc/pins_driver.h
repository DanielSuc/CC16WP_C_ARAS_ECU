
#ifndef PINS_DRIVER_H
#define PINS_DRIVER_H

#include <stddef.h>
#include "device_registers.h"
#include "status.h"


#if defined(FEATURE_PINS_DRIVER_USING_PORT)
typedef uint32_t pins_channel_type_t;

#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
typedef uint16_t pins_channel_type_t;

#endif 

typedef uint8_t pins_level_type_t;

typedef enum
{
    GPIO_INPUT_DIRECTION       = 0x0U,  
    GPIO_OUTPUT_DIRECTION      = 0x1U,  
    GPIO_UNSPECIFIED_DIRECTION = 0x2U   
} port_data_direction_t;

#if FEATURE_PINS_HAS_PULL_SELECTION
typedef enum
{
    PORT_INTERNAL_PULL_NOT_ENABLED   = 0U,  
    PORT_INTERNAL_PULL_DOWN_ENABLED  = 1U,  
    PORT_INTERNAL_PULL_UP_ENABLED    = 2U   
} port_pull_config_t;
#endif 

#if FEATURE_PINS_HAS_OPEN_DRAIN
typedef enum
{
    PORT_OPEN_DRAIN_DISABLED  = 0U, 
    PORT_OPEN_DRAIN_ENABLED   = 1U  
} port_open_drain_t;
#endif 

#if FEATURE_PINS_HAS_DRIVE_STRENGTH
typedef enum
{
#if FEATURE_PINS_HAS_DRIVE_STRENGTH_CONTROL
    PORT_STRENGTH_DISABLED      = 0U, 
    PORT_LOW_DRIVE_STRENGTH     = 1U, 
    PORT_STR1_DRIVE_STRENGTH    = 1U, 
    PORT_STR2_DRIVE_STRENGTH    = 2U, 
    PORT_STR3_DRIVE_STRENGTH    = 3U, 
    PORT_STR4_DRIVE_STRENGTH    = 4U, 
    PORT_STR5_DRIVE_STRENGTH    = 5U, 
    PORT_STR6_DRIVE_STRENGTH    = 6U, 
    PORT_STR7_DRIVE_STRENGTH    = 7U, 
    PORT_HIGH_DRIVE_STRENGTH    = 7U  
#else 
    PORT_LOW_DRIVE_STRENGTH     = 0U,    
    PORT_HIGH_DRIVE_STRENGTH    = 1U     
#endif 
} port_drive_strength_t;
#endif 

#ifdef FEATURE_PINS_DRIVER_USING_PORT
typedef enum
{
    PORT_PIN_DISABLED            = 0U,  
    PORT_MUX_AS_GPIO             = 1U,  
    PORT_MUX_ALT2                = 2U,  
    PORT_MUX_ALT3                = 3U,  
    PORT_MUX_ALT4                = 4U,  
    PORT_MUX_ALT5                = 5U,  
    PORT_MUX_ALT6                = 6U,  
    PORT_MUX_ALT7                = 7U,  
#if FEATURE_PINS_HAS_ADC_INTERLEAVE_EN
    PORT_MUX_ADC_INTERLEAVE      = 8U   
#endif 
} port_mux_t;

typedef enum
{
    PORT_DMA_INT_DISABLED  = 0x0U,  
    PORT_DMA_RISING_EDGE   = 0x1U,  
    PORT_DMA_FALLING_EDGE  = 0x2U,  
    PORT_DMA_EITHER_EDGE   = 0x3U,  
#if FEATURE_PORT_HAS_FLAG_SET_ONLY
    PORT_FLAG_RISING_EDGE  = 0x5U,  
    PORT_FLAG_FALLING_EDGE = 0x6U,  
    PORT_FLAG_EITHER_EDGE  = 0x7U,  
#endif 
    PORT_INT_LOGIC_ZERO    = 0x8U,  
    PORT_INT_RISING_EDGE   = 0x9U,  
    PORT_INT_FALLING_EDGE  = 0xAU,  
    PORT_INT_EITHER_EDGE   = 0xBU,  
    PORT_INT_LOGIC_ONE     = 0xCU,  
#if FEATURE_PORT_HAS_TRIGGER_OUT
    PORT_HIGH_TRIGGER_OUT  = 0xDU,  
    PORT_LOW_TRIGGER_OUT   = 0xEU   
#endif 
} port_interrupt_config_t;

#if FEATURE_PINS_HAS_SLEW_RATE
typedef enum
{
    PORT_FAST_SLEW_RATE     = 0U,   
    PORT_SLOW_SLEW_RATE     = 1U    
} port_slew_rate_t;
#endif 

typedef enum
{
    PORT_DIGITAL_FILTER_BUS_CLOCK  = 0U, 
    PORT_DIGITAL_FILTER_LPO_CLOCK  = 1U  
} port_digital_filter_clock_t;

typedef struct
{
    port_digital_filter_clock_t clock;  
    uint8_t                     width;  
} port_digital_filter_config_t;

typedef enum
{
    PORT_GLOBAL_CONTROL_LOWER_HALF_PINS = 0U, 
    PORT_GLOBAL_CONTROL_UPPER_HALF_PINS = 1U  
} port_global_control_pins_t;

#if FEATURE_PINS_HAS_OVER_CURRENT
typedef enum
{
    PORT_OVER_CURRENT_DISABLED      = 0U,   
    PORT_OVER_CURRENT_INT_DISABLED  = 1U,   
    PORT_OVER_CURRENT_INT_ENABLED   = 2U    
} port_over_current_config_t;
#endif 

#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
#if FEATURE_SIUL2_HAS_DDR_PAD
typedef enum
{
    DDR_DDR3_MODE       = 0x0U,  
    DDR_LPDDR2_MODE     = 0x2U   
} port_ddr_type_t;

typedef enum
{
    DDR_MIN_DELAY       = 0x0U,  
    DDR_50PS_DELAY      = 0x1U,  
    DDR_100PS_DELAY     = 0x2U,  
    DDR_150PS_DELAY     = 0x3U   
} port_ddr_trim_delay_t;

typedef enum
{
    DDR_NO_CRPOINT      = 0x0U,  
    DDR_MINUS_CRPOINT   = 0x1U,  
    DDR_PLUS_CRPOINT    = 0x2U,  
    DDR_DOUBLE_CRPOINT  = 0x3U   
} port_ddr_crpoint_t;

typedef enum
{
    DDR_NO_TRIM         = 0x0U,  
    DDR_LEFT_TRIM       = 0x1U,  
    DDR_RIGHT_TRIM      = 0x2U   
} port_ddr_trim_t;

typedef enum
{
    PORT_DDR_INPUT_CMOS          = 0U, 
    PORT_DDR_INPUT_DIFFERENTIAL  = 1U  
} port_ddr_input_t;

typedef enum
{
    PORT_STR0_ON_DIE_TERMINATION    = 0U, 
    PORT_STR1_ON_DIE_TERMINATION    = 1U, 
    PORT_STR2_ON_DIE_TERMINATION    = 2U, 
    PORT_STR3_ON_DIE_TERMINATION    = 3U, 
    PORT_STR4_ON_DIE_TERMINATION    = 4U, 
    PORT_STR5_ON_DIE_TERMINATION    = 5U, 
    PORT_STR6_ON_DIE_TERMINATION    = 6U, 
    PORT_STR7_ON_DIE_TERMINATION    = 7U  
} port_on_die_termination_t;

typedef struct
{
    port_ddr_type_t         ddrSelection;           
    port_ddr_trim_delay_t   trimmingDelay;          
    port_ddr_crpoint_t      crosspointAdjustment;   
    port_ddr_trim_t         trimmingAdjustment;     
} pin_ddr_config_t;

#endif 

typedef enum
{
    PORT_MUX_AS_GPIO    = 0U,   
    PORT_MUX_ALT1       = 1U,   
    PORT_MUX_ALT2       = 2U,   
    PORT_MUX_ALT3       = 3U,   
    PORT_MUX_ALT4       = 4U,   
    PORT_MUX_ALT5       = 5U,   
    PORT_MUX_ALT6       = 6U,   
    PORT_MUX_ALT7       = 7U,   
    PORT_MUX_ALT8       = 8U,   
    PORT_MUX_ALT9       = 9U,   
    PORT_MUX_ALT10      = 10U,  
    PORT_MUX_ALT11      = 11U,  
    PORT_MUX_ALT12      = 12U,  
    PORT_MUX_ALT13      = 13U,  
    PORT_MUX_ALT14      = 14U,  
    PORT_MUX_ALT15      = 15U   
} port_mux_t;

typedef enum
{
    SIUL2_INT_DISABLE       = 0x0U,  
    SIUL2_INT_RISING_EDGE   = 0x1U,  
    SIUL2_INT_FALLING_EDGE  = 0x2U,  
    SIUL2_INT_EITHER_EDGE   = 0x3U   
} siul2_interrupt_type_t;

#if FEATURE_SIUL2_EXTERNAL_INT_SUPPORT_DMA
typedef enum
{
    SIUL2_INT_USING_INTERUPT = 0x0U, 
    SIUL2_INT_USING_DMA      = 0x1U  
} siul2_interrupt_dma_select_t;
#endif 

typedef struct
{
    uint8_t                eirqPinIdx;      
    siul2_interrupt_type_t intEdgeSel;      
    bool                   digitalFilter;   
    uint8_t                maxCnt;          
#if FEATURE_SIUL2_EXTERNAL_INT_SUPPORT_DMA
    siul2_interrupt_dma_select_t intExeSel; 
#endif
} siul2_interrupt_config_t;

typedef enum
{
    PORT_OUTPUT_BUFFER_DISABLED     = 0U, 
    PORT_OUTPUT_BUFFER_ENABLED      = 1U  
} port_output_buffer_t;

typedef enum
{
    PORT_INPUT_BUFFER_DISABLED     = 0U, 
    PORT_INPUT_BUFFER_ENABLED      = 1U  
} port_input_buffer_t;

#if FEATURE_SIUL2_HAS_HYSTERESIS
typedef enum
{
    PORT_HYSTERESYS_CMOS        = 0U, 
    PORT_HYSTERESYS_SCHMITT     = 1U, 
    PORT_HYSTERESYS_DISABLED    = 0U, 
    PORT_HYSTERESYS_ENABLED     = 1U  
} port_hysteresis_t;
#endif 

#if FEATURE_SIUL2_HAS_INVERT_DATA_OUTPUT
typedef enum
{
    PORT_INVERT_OUTPUT_DISABLED  = 0U, 
    PORT_INVERT_OUTPUT_ENABLED   = 1U  
} port_invert_output_t;
#endif 

#if FEATURE_SIUL2_HAS_INVERT_DATA_INPUT
typedef enum
{
    PORT_INVERT_INPUT_DISABLED   = 0U, 
    PORT_INVERT_INPUT_ENABLED    = 1U  
} port_invert_input_t;
#endif 

#if FEATURE_SIUL2_HAS_PULL_KEEPER
typedef enum
{
    PORT_PULL_KEEP_DISABLED  = 0U, 
    PORT_PULL_KEEP_ENABLED   = 1U  
} port_pull_keep_t;

typedef enum
{
    PORT_KEEPER_ENABLED      = 0U, 
    PORT_PULL_ENABLED        = 1U  
} port_pull_keeper_select_t;

typedef enum
{
    PORT_PULL_DOWN_ENABLED   = 0U,  
    PORT_PULL_UP_MEDIUM      = 1U,  
    PORT_PULL_UP_HIGH        = 2U,  
    PORT_PULL_UP_LOW         = 3U   
} port_pull_up_down_t;

#endif 

#if FEATURE_SIUL2_HAS_ANALOG_PAD
typedef enum
{
    PORT_ANALOG_PAD_CONTROL_DISABLED = 0U, 
    PORT_ANALOG_PAD_CONTROL_ENABLED  = 1U  
} port_analog_pad_t;
#endif 

typedef enum
{
    PORT_INPUT_MUX_ALT0      = 0U,   
    PORT_INPUT_MUX_ALT1      = 1U,   
    PORT_INPUT_MUX_ALT2      = 2U,   
    PORT_INPUT_MUX_ALT3      = 3U,   
    PORT_INPUT_MUX_ALT4      = 4U,   
    PORT_INPUT_MUX_ALT5      = 5U,   
    PORT_INPUT_MUX_ALT6      = 6U,   
    PORT_INPUT_MUX_ALT7      = 7U,   
#if (FEATURE_SIUL2_INPUT_SOURCE_SELECT_WIDTH >= 4U)
    PORT_INPUT_MUX_ALT8      = 8U,   
    PORT_INPUT_MUX_ALT9      = 9U,   
    PORT_INPUT_MUX_ALT10     = 10U,  
    PORT_INPUT_MUX_ALT11     = 11U,  
    PORT_INPUT_MUX_ALT12     = 12U,  
    PORT_INPUT_MUX_ALT13     = 13U,  
    PORT_INPUT_MUX_ALT14     = 14U,  
    PORT_INPUT_MUX_ALT15     = 15U,  
#endif
    PORT_INPUT_MUX_NO_INIT           
} port_input_mux_t;

typedef enum
{
    PORT_SAFE_MODE_DISABLED     = 0U, 
    PORT_SAFE_MODE_ENABLED      = 1U  
} port_safe_mode_t;

#if FEATURE_SIUL2_HAS_SLEW_RATE_CONTROL
typedef enum
{
    HALF_STRENGTH_WITH_SLEWRATE_CONTROL     = 0u, 
    FULL_STRENGTH_WITH_SLEWRATE_CONTROL     = 1u, 
    HALF_STRENGTH_WITHOUT_SLEWRATE_CONTROL  = 2u, 
    FULL_STRENGTH_WITHOUT_SLEWRATE_CONTROL  = 3u  
} port_slew_rate_control_t;
#endif 

#if FEATURE_PINS_HAS_SLEW_RATE
typedef enum
{
    PORT_LOW_SLEW_RATE      = 0U,   
    PORT_MEDIUM_SLEW_RATE   = 1U,   
    PORT_MEDIUM_SLEW_RATE2  = 2U,   
    PORT_HIGH_SLEW_RATE     = 3U    
} port_slew_rate_t;
#endif

#endif 

typedef struct
{
#ifdef FEATURE_PINS_DRIVER_USING_PORT
    PORT_Type         *         base;              
#elif defined FEATURE_PINS_DRIVER_USING_SIUL2
    SIUL2_Type        *         base;              
#endif
    uint32_t                    pinPortIdx;        
#if FEATURE_PINS_HAS_PULL_SELECTION
    port_pull_config_t          pullConfig;        
#endif
#if FEATURE_PINS_HAS_SLEW_RATE
    port_slew_rate_t            rateSelect;        
#endif
#if FEATURE_PORT_HAS_PASSIVE_FILTER
    bool                        passiveFilter;     
#endif
#if FEATURE_PINS_HAS_OPEN_DRAIN
    port_open_drain_t           openDrain;         
#endif
#if FEATURE_PINS_HAS_DRIVE_STRENGTH
    port_drive_strength_t       driveSelect;       
#endif
    port_mux_t                  mux;               
#if FEATURE_PORT_HAS_PIN_CONTROL_LOCK
    bool                        pinLock;           
#endif
#ifdef FEATURE_PINS_DRIVER_USING_PORT
    port_interrupt_config_t     intConfig;         
    bool                        clearIntFlag;      
    bool                        digitalFilter;     
#if FEATURE_PINS_HAS_OVER_CURRENT
    bool                        clearOCurFlag;     
    port_over_current_config_t  overCurConfig;     
#endif
#endif
    GPIO_Type         *         gpioBase;          
    port_data_direction_t       direction;         
#ifdef FEATURE_PINS_DRIVER_USING_SIUL2
    port_input_mux_t    inputMux[FEATURE_SIUL2_INPUT_MUX_WIDTH];   
#if FEATURE_SIUL2_HAS_INVERT_DATA_INPUT
    port_invert_input_t inputInvert[FEATURE_SIUL2_INPUT_MUX_WIDTH];
#endif 
    uint32_t            inputMuxReg[FEATURE_SIUL2_INPUT_MUX_WIDTH];
    port_output_buffer_t        outputBuffer;      
    port_input_buffer_t         inputBuffer;       
    siul2_interrupt_config_t    intConfig;         
#if FEATURE_SIUL2_HAS_SAFE_MODE_CONTROL
    port_safe_mode_t            safeMode;          
#endif 
#if FEATURE_SIUL2_HAS_SLEW_RATE_CONTROL
    port_slew_rate_control_t    slewRateCtrlSel;   
#endif 
#if FEATURE_SIUL2_HAS_HYSTERESIS
    port_hysteresis_t           hysteresisSelect;  
#endif 
#if FEATURE_SIUL2_HAS_DDR_PAD
    pin_ddr_config_t            ddrConfiguration;  
    port_ddr_input_t            inputMode;         
    port_on_die_termination_t   odtSelect;         
#endif 
#if FEATURE_SIUL2_HAS_INVERT_DATA_OUTPUT
    port_invert_output_t        invertOutput;      
#endif 
#if FEATURE_SIUL2_HAS_PULL_KEEPER
    port_pull_keep_t            pullKeepEnable;    
    port_pull_keeper_select_t   pullKeepSelect;    
    port_pull_up_down_t         pullSelect;        
#endif 
#if FEATURE_SIUL2_HAS_ANALOG_PAD
    port_analog_pad_t           analogPadCtrlSel;  
#endif 
#endif 
    pins_level_type_t           initValue;         
} pin_settings_config_t;


#if defined(__cplusplus)
extern "C" {
#endif

status_t PINS_DRV_Init(uint32_t pinCount,
                       const pin_settings_config_t config[]);

#ifdef FEATURE_PINS_DRIVER_USING_PORT
#if FEATURE_PINS_HAS_PULL_SELECTION
void PINS_DRV_SetPullSel(PORT_Type * const base,
                         uint32_t pin,
                         port_pull_config_t pullConfig);

#endif 

void PINS_DRV_SetMuxModeSel(PORT_Type * const base,
                            uint32_t pin,
                            port_mux_t mux);

void PINS_DRV_SetPinIntSel(PORT_Type * const base,
                           uint32_t pin,
                           port_interrupt_config_t intConfig);

port_interrupt_config_t PINS_DRV_GetPinIntSel(const PORT_Type * const base,
                                              uint32_t pin);

void PINS_DRV_ClearPinIntFlagCmd(PORT_Type * const base,
                                 uint32_t pin);

void PINS_DRV_EnableDigitalFilter(PORT_Type * const base,
                                  uint32_t pin);

void PINS_DRV_DisableDigitalFilter(PORT_Type * const base,
                                   uint32_t pin);

void PINS_DRV_ConfigDigitalFilter(PORT_Type * const base,
                                  const port_digital_filter_config_t * const config);

uint32_t PINS_DRV_GetPortIntFlag(const PORT_Type * const base);

void PINS_DRV_ClearPortIntFlagCmd(PORT_Type * const base);

void PINS_DRV_SetGlobalPinControl(PORT_Type * const base,
                                  uint16_t pins,
                                  uint16_t value,
                                  port_global_control_pins_t halfPort);

void PINS_DRV_SetGlobalIntControl(PORT_Type * const base,
                                  uint16_t pins,
                                  uint16_t value,
                                  port_global_control_pins_t halfPort);

#if FEATURE_PINS_HAS_OVER_CURRENT
uint32_t PINS_DRV_GetOverCurPortIntFlag(const PORT_Type * const base);

void PINS_DRV_ClearOverCurPortIntFlag(PORT_Type * const base);
#endif 

pins_channel_type_t PINS_DRV_GetPinsDirection(const GPIO_Type * const base);

void PINS_DRV_SetPinDirection(GPIO_Type * const base,
                              pins_channel_type_t pin,
                              pins_level_type_t direction);

void PINS_DRV_SetPinsDirection(GPIO_Type * const base,
                               pins_channel_type_t pins);

#if FEATURE_PORT_HAS_INPUT_DISABLE
void PINS_DRV_SetPortInputDisable(GPIO_Type * const base,
                                  pins_channel_type_t pins);

pins_channel_type_t PINS_DRV_GetPortInputDisable(const GPIO_Type * const base);
#endif 

#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
#if FEATURE_PINS_HAS_PULL_SELECTION
void PINS_DRV_SetPullSel(PORT_Type * const base,
                         uint16_t pin,
                         port_pull_config_t pullConfig);

#endif 

void PINS_DRV_SetOutputBuffer(PORT_Type * const base,
                              uint16_t pin,
                              bool enable,
                              port_mux_t mux);

void PINS_DRV_SetInputBuffer(PORT_Type * const base,
                             uint16_t pin,
                             bool enable,
                             uint32_t inputMuxReg,
                             port_input_mux_t inputMux);

void PINS_DRV_ConfigIntFilterClock(uint8_t prescaler);

void PINS_DRV_SetExInt(siul2_interrupt_config_t intConfig);

void PINS_DRV_ClearPinExIntFlag(uint32_t eirqPinIdx);

bool PINS_DRV_GetPinExIntFlag(uint32_t eirqPinIdx);

void PINS_DRV_ClearExIntFlag(void);

uint32_t PINS_DRV_GetExIntFlag(void);

#endif 

void PINS_DRV_WritePin(GPIO_Type * const base,
                       pins_channel_type_t pin,
                       pins_level_type_t value);

void PINS_DRV_WritePins(GPIO_Type * const base,
                        pins_channel_type_t pins);

pins_channel_type_t PINS_DRV_GetPinsOutput(const GPIO_Type * const base);

void PINS_DRV_SetPins(GPIO_Type * const base,
                      pins_channel_type_t pins);

void PINS_DRV_ClearPins(GPIO_Type * const base,
                        pins_channel_type_t pins);

void PINS_DRV_TogglePins(GPIO_Type * const base,
                         pins_channel_type_t pins);

pins_channel_type_t PINS_DRV_ReadPins(const GPIO_Type * const base);


#if defined(__cplusplus)
}
#endif


#endif 

