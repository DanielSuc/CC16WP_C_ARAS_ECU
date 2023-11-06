
#if !defined (CLOCK_S32K1xx_H)
#define CLOCK_S32K1xx_H


#include "device_registers.h"
#include "status.h"
#include <stdint.h>
#include <stdbool.h>




extern const uint8_t peripheralFeaturesList[CLOCK_NAME_COUNT];


#define NUMBER_OF_TCLK_INPUTS 3U
extern uint32_t g_TClkFreq[NUMBER_OF_TCLK_INPUTS];      

extern uint32_t g_xtal0ClkFreq;

extern uint32_t g_RtcClkInFreq;

#define SYS_CLK_MAX_NO    3U
#define CORE_CLK_INDEX    0U
#define BUS_CLK_INDEX     1U
#define SLOW_CLK_INDEX    2U

typedef enum
{
    SIM_RTCCLK_SEL_SOSCDIV1_CLK   = 0x0U,           
    SIM_RTCCLK_SEL_LPO_32K        = 0x1U,           
    SIM_RTCCLK_SEL_RTC_CLKIN      = 0x2U,           
    SIM_RTCCLK_SEL_FIRCDIV1_CLK   = 0x3U,           
} sim_rtc_clk_sel_src_t;

typedef enum
{
    SIM_LPO_CLK_SEL_LPO_128K    = 0x0,           
    SIM_LPO_CLK_SEL_NO_CLOCK    = 0x1,           
    SIM_LPO_CLK_SEL_LPO_32K     = 0x2,           
    SIM_LPO_CLK_SEL_LPO_1K      = 0x3,           
} sim_lpoclk_sel_src_t;

typedef enum
{
    SIM_CLKOUT_SEL_SYSTEM_SCG_CLKOUT     = 0U,     
    SIM_CLKOUT_SEL_SYSTEM_SOSC_DIV2_CLK  = 2U,     
    SIM_CLKOUT_SEL_SYSTEM_SIRC_DIV2_CLK  = 4U,     
    SIM_CLKOUT_SEL_SYSTEM_FIRC_DIV2_CLK  = 6U,     
    SIM_CLKOUT_SEL_SYSTEM_HCLK           = 7U,     
    SIM_CLKOUT_SEL_SYSTEM_SPLL_DIV2_CLK  = 8U,     
    SIM_CLKOUT_SEL_SYSTEM_BUS_CLK        = 9U,     
    SIM_CLKOUT_SEL_SYSTEM_LPO_128K_CLK   = 10U,    
    SIM_CLKOUT_SEL_SYSTEM_LPO_CLK        = 12U,    
    SIM_CLKOUT_SEL_SYSTEM_RTC_CLK        = 14U,    

#if defined (QuadSPI_INSTANCE_COUNT)
    SIM_CLKOUT_SEL_SYSTEM_SFIF_CLK_HYP   = 5U,     
    SIM_CLKOUT_SEL_SYSTEM_IPG_CLK        = 11U,    
    SIM_CLKOUT_SEL_SYSTEM_IPG_CLK_SFIF   = 13U,    
    SIM_CLKOUT_SEL_SYSTEM_IPG_CLK_2XSFIF = 15U     
#endif
} sim_clkout_src_t;

typedef enum
{
    SIM_CLKOUT_DIV_BY_1 = 0x0U,        
    SIM_CLKOUT_DIV_BY_2 = 0x1U,        
    SIM_CLKOUT_DIV_BY_3 = 0x2U,        
    SIM_CLKOUT_DIV_BY_4 = 0x3U,        
    SIM_CLKOUT_DIV_BY_5 = 0x4U,        
    SIM_CLKOUT_DIV_BY_6 = 0x5U,        
    SIM_CLKOUT_DIV_BY_7 = 0x6U,        
    SIM_CLKOUT_DIV_BY_8 = 0x7U,        
} sim_clkout_div_t;


typedef struct
{
    bool              initialize;     
    bool              enable;         
    sim_clkout_src_t  source;         
    sim_clkout_div_t  divider;        
} sim_clock_out_config_t;


typedef struct
{
    bool                  initialize;       
    sim_rtc_clk_sel_src_t sourceRtcClk;     
    sim_lpoclk_sel_src_t  sourceLpoClk;     
    bool                  enableLpo32k;     
    bool                  enableLpo1k;      
} sim_lpo_clock_config_t;

typedef struct
{
    bool      initialize;                         
    uint32_t  tclkFreq[NUMBER_OF_TCLK_INPUTS];    
} sim_tclk_config_t;

typedef struct
{
    bool initialize;     
    bool enableMscm;     
    bool enableMpu;      
    bool enableDma;      
    bool enableErm;      
    bool enableEim;      
} sim_plat_gate_config_t;

typedef struct
{
    bool enableQspiRefClk;      
} sim_qspi_ref_clk_gating_t;


typedef enum
{
    CLOCK_TRACE_SRC_CORE_CLK            = 0x0          
} clock_trace_src_t;


typedef struct
{
    bool               initialize;    
    bool               divEnable;     
    clock_trace_src_t  source;        
    uint8_t            divider;       
    bool               divFraction;   
} sim_trace_clock_config_t;

typedef struct
{
    sim_clock_out_config_t    clockOutConfig;                 
    sim_lpo_clock_config_t    lpoClockConfig;                 
    sim_tclk_config_t         tclkConfig;                     
    sim_plat_gate_config_t    platGateConfig;                 
    sim_trace_clock_config_t  traceClockConfig;               
    sim_qspi_ref_clk_gating_t qspiRefClkGating;               
} sim_clock_config_t;


typedef enum
{
    SCG_SYSTEM_CLOCK_SRC_SYS_OSC  = 1U,       
    SCG_SYSTEM_CLOCK_SRC_SIRC     = 2U,       
    SCG_SYSTEM_CLOCK_SRC_FIRC     = 3U,       
#if FEATURE_HAS_SPLL_CLK
    SCG_SYSTEM_CLOCK_SRC_SYS_PLL  = 6U,       
#endif
    SCG_SYSTEM_CLOCK_SRC_NONE     = 255U      
} scg_system_clock_src_t;

typedef enum
{
    SCG_SYSTEM_CLOCK_DIV_BY_1   = 0U,     
    SCG_SYSTEM_CLOCK_DIV_BY_2   = 1U,     
    SCG_SYSTEM_CLOCK_DIV_BY_3   = 2U,     
    SCG_SYSTEM_CLOCK_DIV_BY_4   = 3U,     
    SCG_SYSTEM_CLOCK_DIV_BY_5   = 4U,     
    SCG_SYSTEM_CLOCK_DIV_BY_6   = 5U,     
    SCG_SYSTEM_CLOCK_DIV_BY_7   = 6U,     
    SCG_SYSTEM_CLOCK_DIV_BY_8   = 7U,     
    SCG_SYSTEM_CLOCK_DIV_BY_9   = 8U,     
    SCG_SYSTEM_CLOCK_DIV_BY_10  = 9U,     
    SCG_SYSTEM_CLOCK_DIV_BY_11  = 10U,    
    SCG_SYSTEM_CLOCK_DIV_BY_12  = 11U,    
    SCG_SYSTEM_CLOCK_DIV_BY_13  = 12U,    
    SCG_SYSTEM_CLOCK_DIV_BY_14  = 13U,    
    SCG_SYSTEM_CLOCK_DIV_BY_15  = 14U,    
    SCG_SYSTEM_CLOCK_DIV_BY_16  = 15U,    
} scg_system_clock_div_t;

typedef struct
{
    scg_system_clock_div_t divSlow;  
    scg_system_clock_div_t divBus;   
    scg_system_clock_div_t divCore;  
    scg_system_clock_src_t src;      
} scg_system_clock_config_t;


typedef enum
{
    SCG_CLOCKOUT_SRC_SCG_SLOW = 0U,   
    SCG_CLOCKOUT_SRC_SOSC     = 1U,   
    SCG_CLOCKOUT_SRC_SIRC     = 2U,   
    SCG_CLOCKOUT_SRC_FIRC     = 3U,   
    SCG_CLOCKOUT_SRC_SPLL     = 6U,   
} scg_clockout_src_t;


typedef enum
{
    SCG_ASYNC_CLOCK_DISABLE   = 0U,        
    SCG_ASYNC_CLOCK_DIV_BY_1  = 1U,        
    SCG_ASYNC_CLOCK_DIV_BY_2  = 2U,        
    SCG_ASYNC_CLOCK_DIV_BY_4  = 3U,        
    SCG_ASYNC_CLOCK_DIV_BY_8  = 4U,        
    SCG_ASYNC_CLOCK_DIV_BY_16 = 5U,        
    SCG_ASYNC_CLOCK_DIV_BY_32 = 6U,        
    SCG_ASYNC_CLOCK_DIV_BY_64 = 7U         
} scg_async_clock_div_t;


typedef enum
{
    SCG_SOSC_MONITOR_DISABLE = 0U,                         
    SCG_SOSC_MONITOR_INT     = 1U,                         
    SCG_SOSC_MONITOR_RESET   = 2U,                          
} scg_sosc_monitor_mode_t;

typedef enum
{
    SCG_SOSC_RANGE_MID    = 2U,  
    SCG_SOSC_RANGE_HIGH   = 3U,  
} scg_sosc_range_t;

typedef enum
{
    SCG_SOSC_GAIN_LOW    = 0x0,  
    SCG_SOSC_GAIN_HIGH   = 0x1,  
} scg_sosc_gain_t;

typedef enum
{
    SCG_SOSC_REF_EXT   = 0x0,     
    SCG_SOSC_REF_OSC   = 0x1,     
} scg_sosc_ext_ref_t;

typedef struct
{
    uint32_t  freq;                        

    scg_sosc_monitor_mode_t monitorMode;   

    scg_sosc_ext_ref_t extRef;             
    scg_sosc_gain_t    gain;               

    scg_sosc_range_t   range;              

    scg_async_clock_div_t div1;            
    scg_async_clock_div_t div2;            

    bool enableInStop;                     
    bool enableInLowPower;                 

    bool locked;                           

    bool initialize;                       
} scg_sosc_config_t;

typedef enum
{
    SCG_SIRC_RANGE_HIGH = 1U,  
} scg_sirc_range_t;

typedef struct
{
    scg_sirc_range_t range;         

    scg_async_clock_div_t div1;     
    scg_async_clock_div_t div2;     

    bool initialize;                
    bool enableInStop;              
    bool enableInLowPower;          

    bool locked;                    
} scg_sirc_config_t;

typedef enum
{
    SCG_FIRC_RANGE_48M,   
} scg_firc_range_t;

typedef struct
{
    scg_firc_range_t range;            

    scg_async_clock_div_t div1;        
    scg_async_clock_div_t div2;        

    bool enableInStop;                 
    bool enableInLowPower;             
    bool regulator;                    
    bool locked;                       

    bool initialize;                   
} scg_firc_config_t;

typedef enum
{
    SCG_SPLL_MONITOR_DISABLE = 0U,                         
    SCG_SPLL_MONITOR_INT     = 1U,                         
    SCG_SPLL_MONITOR_RESET   = 2U                          
} scg_spll_monitor_mode_t;


typedef enum
{
    SCG_SPLL_CLOCK_PREDIV_BY_1 = 0U,
    SCG_SPLL_CLOCK_PREDIV_BY_2 = 1U,
    SCG_SPLL_CLOCK_PREDIV_BY_3 = 2U,
    SCG_SPLL_CLOCK_PREDIV_BY_4 = 3U,
    SCG_SPLL_CLOCK_PREDIV_BY_5 = 4U,
    SCG_SPLL_CLOCK_PREDIV_BY_6 = 5U,
    SCG_SPLL_CLOCK_PREDIV_BY_7 = 6U,
    SCG_SPLL_CLOCK_PREDIV_BY_8 = 7U

} scg_spll_clock_prediv_t;

typedef enum
{
    SCG_SPLL_CLOCK_MULTIPLY_BY_16 = 0U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_17 = 1U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_18 = 2U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_19 = 3U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_20 = 4U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_21 = 5U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_22 = 6U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_23 = 7U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_24 = 8U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_25 = 9U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_26 = 10U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_27 = 11U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_28 = 12U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_29 = 13U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_30 = 14U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_31 = 15U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_32 = 16U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_33 = 17U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_34 = 18U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_35 = 19U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_36 = 20U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_37 = 21U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_38 = 22U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_39 = 23U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_40 = 24U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_41 = 25U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_42 = 26U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_43 = 27U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_44 = 28U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_45 = 29U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_46 = 30U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_47 = 31U
} scg_spll_clock_multiply_t;

typedef struct
{
    scg_spll_monitor_mode_t monitorMode; 

    uint8_t        prediv;               
    uint8_t        mult;                 
    uint8_t        src;                  

    scg_async_clock_div_t div1;          
    scg_async_clock_div_t div2;          

    bool enableInStop;                   

    bool locked;                         
    bool initialize;                     
} scg_spll_config_t;

typedef struct
{
    uint32_t rtcClkInFreq;              
    bool initialize;                    
} scg_rtc_config_t;

typedef struct
{
    scg_system_clock_config_t rccrConfig;      
    scg_system_clock_config_t vccrConfig;      
    scg_system_clock_config_t hccrConfig;      
    scg_system_clock_src_t    alternateClock;  
    bool                      initialize;      
} scg_clock_mode_config_t;

typedef struct
{
    scg_clockout_src_t        source;          
    bool                      initialize;      
} scg_clockout_config_t;

typedef struct
{
    scg_sirc_config_t         sircConfig;      
    scg_firc_config_t         fircConfig;      
    scg_sosc_config_t         soscConfig;      
    scg_spll_config_t         spllConfig;      
    scg_rtc_config_t          rtcConfig;       
    scg_clockout_config_t     clockOutConfig;  
    scg_clock_mode_config_t   clockModeConfig; 
} scg_config_t;

typedef uint8_t peripheral_clock_source_t;

#define    CLK_SRC_OFF          0x00U             
#define    CLK_SRC_SOSC         0x01U             
#define    CLK_SRC_SIRC         0x02U             
#define    CLK_SRC_FIRC         0x03U             
#define    CLK_SRC_SPLL         0x06U             
#define    CLK_SRC_SOSC_DIV1    0x01U             
#define    CLK_SRC_SIRC_DIV1    0x02U             
#define    CLK_SRC_FIRC_DIV1    0x03U             
#define    CLK_SRC_SPLL_DIV1    0x06U             
#define    CLK_SRC_SOSC_DIV2    0x01U             
#define    CLK_SRC_SIRC_DIV2    0x02U             
#define    CLK_SRC_FIRC_DIV2    0x03U             
#define    CLK_SRC_SPLL_DIV2    0x06U             

typedef enum
{
    MULTIPLY_BY_ONE   = 0x00U,             
    MULTIPLY_BY_TWO   = 0x01U              
} peripheral_clock_frac_t;

typedef enum
{
    DIVIDE_BY_ONE     = 0x00U,             
    DIVIDE_BY_TWO     = 0x01U,             
    DIVIDE_BY_THREE   = 0x02U,             
    DIVIDE_BY_FOUR    = 0x03U,             
    DIVIDE_BY_FIVE    = 0x04U,             
    DIVIDE_BY_SIX     = 0x05U,             
    DIVIDE_BY_SEVEN   = 0x06U,             
    DIVIDE_BY_EIGTH   = 0x07U              
} peripheral_clock_divider_t;

typedef struct
{
    clock_names_t clockName;
    bool clkGate;                                      
    peripheral_clock_source_t clkSrc;                  
    peripheral_clock_frac_t frac;                      
    peripheral_clock_divider_t divider;                
} peripheral_clock_config_t;

typedef struct
{
    uint32_t count;                                    
    peripheral_clock_config_t * peripheralClocks;       
} pcc_config_t;

typedef struct
{
    bool                  initialize;       
    bool                  enable;           
    int8_t                trimValue;        
} pmc_lpo_clock_config_t;

typedef struct
{
    pmc_lpo_clock_config_t lpoClockConfig;   
} pmc_config_t;

typedef struct
{
    scg_config_t                scgConfig;      
    sim_clock_config_t          simConfig;      
    pcc_config_t                pccConfig;      
    pmc_config_t                pmcConfig;      
} clock_manager_user_config_t;

typedef clock_manager_user_config_t clock_user_config_t;

typedef enum {

    NO_MODE       = 0U,
    RUN_MODE      = (1U<<0U),
    VLPR_MODE     = (1U<<1U),
    HSRUN_MODE    = (1U<<2U),
    STOP_MODE     = (1U<<3U),
    VLPS_MODE     = (1U<<4U),
    ALL_MODES     = 0x7FFFFFFF

} pwr_modes_t;


typedef enum
{
    XOSC_EXT_REF  = 0U,      
    XOSC_INT_OSC  = 1U,      
} xosc_ref_t;

typedef struct
{
    bool          gating;                     
    clock_names_t source;                     
    uint16_t      mul;                        
    uint16_t      div;                        

}module_clk_config_t;

typedef struct
{
    clock_names_t src;                         
    uint16_t dividers[SYS_CLK_MAX_NO];         
} sys_clk_config_t;

typedef struct
{
	bool       enable;                   
	xosc_ref_t refClk;                   
    uint32_t   refFreq;                  
	uint16_t   mul;                      
	uint16_t   div;                      

	uint16_t   outputDiv1;               
	uint16_t   outputDiv2;               

} clock_source_config_t;


typedef enum
{
    CLOCK_MANAGER_NOTIFY_RECOVER = 0x00U,  
    CLOCK_MANAGER_NOTIFY_BEFORE  = 0x01U,  
    CLOCK_MANAGER_NOTIFY_AFTER   = 0x02U,  
} clock_manager_notify_t;

typedef enum
{
    CLOCK_MANAGER_CALLBACK_BEFORE       = 0x01U, 
    CLOCK_MANAGER_CALLBACK_AFTER        = 0x02U, 
    CLOCK_MANAGER_CALLBACK_BEFORE_AFTER = 0x03U  
} clock_manager_callback_type_t;

typedef enum
{
    CLOCK_MANAGER_POLICY_AGREEMENT,  
    CLOCK_MANAGER_POLICY_FORCIBLE    
} clock_manager_policy_t;

typedef struct
{
    uint8_t targetClockConfigIndex;    
    clock_manager_policy_t policy;     
    clock_manager_notify_t notifyType; 
} clock_notify_struct_t;

typedef status_t (*clock_manager_callback_t)(clock_notify_struct_t *notify,
                                             void* callbackData);

typedef struct
{
    clock_manager_callback_t      callback;      
    clock_manager_callback_type_t callbackType;  
    void* callbackData;                          
} clock_manager_callback_user_config_t;

typedef struct
{
    clock_manager_user_config_t const **configTable;
    uint8_t clockConfigNum;                         
    uint8_t curConfigIndex;                         
    clock_manager_callback_user_config_t **callbackConfig; 
    uint8_t callbackNum;                            
    uint8_t errorCallbackIndex;                     
} clock_manager_state_t;




#if defined (__cplusplus)
extern "C" {
#endif 

void CLOCK_DRV_SetModuleClock(clock_names_t peripheralClock, const module_clk_config_t * moduleClkConfig);

status_t CLOCK_DRV_SetSystemClock(const pwr_modes_t * mode,
                                  const sys_clk_config_t * sysClkConfig);

void CLOCK_DRV_GetSystemClockSource(sys_clk_config_t *sysClkConfig);

status_t CLOCK_DRV_SetClockSource(clock_names_t clockSource, const clock_source_config_t * clkSrcConfig);

status_t CLOCK_SYS_Init(clock_manager_user_config_t const **clockConfigsPtr,
                        uint8_t configsNumber,
                        clock_manager_callback_user_config_t **callbacksPtr,
                        uint8_t callbacksNumber);

status_t CLOCK_SYS_UpdateConfiguration(uint8_t targetConfigIndex,
                                       clock_manager_policy_t policy);

status_t CLOCK_SYS_SetConfiguration(clock_manager_user_config_t const * config);

uint8_t CLOCK_SYS_GetCurrentConfiguration(void);

clock_manager_callback_user_config_t* CLOCK_SYS_GetErrorCallback(void);

status_t CLOCK_SYS_GetFreq(clock_names_t clockName, uint32_t *frequency);


#if defined (__cplusplus)
}
#endif 


#endif 

