
#ifndef QUADSPI_DRIVER_H
#define QUADSPI_DRIVER_H

#include <stddef.h>
#include <stdbool.h>
#include "device_registers.h"
#include "status.h"



#define QSPI_AHB_BUFFERS   4U

#define QSPI_LUT_LOCK_KEY       0x5AF05AF0U

typedef enum
{
    QSPI_LUT_CMD_STOP            = 0U,    
    QSPI_LUT_CMD_CMD             = 1U,    
    QSPI_LUT_CMD_ADDR            = 2U,    
    QSPI_LUT_CMD_DUMMY           = 3U,    
    QSPI_LUT_CMD_MODE            = 4U,    
    QSPI_LUT_CMD_MODE2           = 5U,    
    QSPI_LUT_CMD_MODE4           = 6U,    
    QSPI_LUT_CMD_READ            = 7U,    
    QSPI_LUT_CMD_WRITE           = 8U,    
    QSPI_LUT_CMD_JMP_ON_CS       = 9U,    
    QSPI_LUT_CMD_ADDR_DDR        = 10U,   
    QSPI_LUT_CMD_MODE_DDR        = 11U,   
    QSPI_LUT_CMD_MODE2_DDR       = 12U,   
    QSPI_LUT_CMD_MODE4_DDR       = 13U,   
    QSPI_LUT_CMD_READ_DDR        = 14U,   
    QSPI_LUT_CMD_WRITE_DDR       = 15U,   
    QSPI_LUT_CMD_CMD_DDR         = 17U,   
    QSPI_LUT_CMD_CADDR           = 18U,   
    QSPI_LUT_CMD_CADDR_DDR       = 19U,   
} qspi_lut_commands_t;

typedef enum
{
    QSPI_LUT_PADS_1              = 0U,    
    QSPI_LUT_PADS_2              = 1U,    
    QSPI_LUT_PADS_4              = 2U,    
    QSPI_LUT_PADS_8              = 3U,    
} qspi_lut_pads_t;

typedef enum
{
    QSPI_TRANSFER_TYPE_SYNC         = 0U,   
    QSPI_TRANSFER_TYPE_ASYNC_INT    = 1U,   
    QSPI_TRANSFER_TYPE_ASYNC_DMA    = 2U,   
} qspi_transfer_type_t;


typedef enum
{
    QSPI_READ_MODE_INTERNAL_SAMPLING   = 0U,    
    QSPI_READ_MODE_INTERNAL_DQS        = 1U,    
    QSPI_READ_MODE_LOOPBACK_DQS        = 2U,    
    QSPI_READ_MODE_EXTERNAL_DQS        = 3U,    
} qspi_read_mode_t;


typedef enum
{
    QSPI_END_64BIT_BE      = 0U,  
    QSPI_END_32BIT_LE      = 1U,  
    QSPI_END_32BIT_BE      = 2U,  
    QSPI_END_64BIT_LE      = 3U,  
} qspi_endianess_t;

typedef enum
{
    QSPI_CLK_SRC_PLL_DIV1   = 0U,  
    QSPI_CLK_SRC_FIRC_DIV1  = 1U,  
} qspi_clock_src_t;

typedef enum
{
    QSPI_DATE_RATE_SDR         = 0U,    
    QSPI_DATE_RATE_DDR         = 1U,    
} qspi_date_rate_t;


typedef enum
{
    QSPI_FLASH_SIDE_A          = 0U,    
    QSPI_FLASH_SIDE_B          = 1U,    
} qspi_flash_side_t;


typedef enum
{
    QSPI_SAMPLE_DELAY_1        = 0U,    
    QSPI_SAMPLE_DELAY_2        = 1U,    
} qspi_sample_delay_t;

typedef enum
{
    QSPI_SAMPLE_PHASE_NON_INVERTED    = 0U,    
    QSPI_SAMPLE_PHASE_INVERTED        = 1U,    
} qspi_sample_phase_t;



typedef void (* qspi_callback_t)(uint32_t instance, void * param);

typedef struct
{
    qspi_date_rate_t dataRate;          
    bool dmaSupport;                    
#if (FEATURE_QSPI_FIXED_DMA_CHANNELS == 0)
    uint8_t dmaChannel;                 
#endif
    qspi_callback_t callback;           
    void * callbackParam;               
    qspi_flash_side_t side;             
    uint32_t memSize;                   
    uint8_t csHoldTime;                 
    uint8_t csSetupTime;                
    uint8_t columnAddr;                 
    bool wordAddresable;                
    qspi_read_mode_t readMode;          
    qspi_sample_delay_t sampleDelay;    
    qspi_sample_phase_t samplePhase;    
    uint8_t dqsDelay;                   
    bool dqsInvert;                     
    qspi_endianess_t endianess;         
    qspi_clock_src_t clock_src;         
    uint8_t divider;                    
    uint8_t io2IdleValue;               
    uint8_t io3IdleValue;               
    bool dozeMode;                      
} qspi_user_config_t;

typedef struct
{
    uint8_t masters[QSPI_AHB_BUFFERS];    
    uint16_t sizes[QSPI_AHB_BUFFERS];     
    bool allMasters;                      
    bool highPriority;                    
} qspi_ahb_config_t;


typedef struct
{
    uint32_t instance;                  
    bool dmaSupport;                    
    uint8_t dmaChannel;                 
    status_t status;                    
    bool driverBusy;                    
    qspi_callback_t callback;           
    void * callbackParam;               
    uint8_t * data;                     
    const uint8_t * roData;             
    uint32_t size;                      
    uint8_t operation;                  
} qspi_state_t;


extern QuadSPI_Type * const g_qspiBase[QuadSPI_INSTANCE_COUNT];



#if defined(__cplusplus)
extern "C" {
#endif


status_t QSPI_DRV_Init(uint32_t instance,
                       const qspi_user_config_t * userConfigPtr,
                       qspi_state_t * state);


status_t QSPI_DRV_Deinit(uint32_t instance);


status_t QSPI_DRV_GetDefaultConfig(qspi_user_config_t * userConfigPtr);


status_t QSPI_DRV_AhbSetup(uint32_t instance, const qspi_ahb_config_t *config);



static inline void QSPI_DRV_SetLut(uint32_t instance,
                                   uint8_t lut,
                                   qspi_lut_commands_t instr0,
                                   qspi_lut_pads_t pad0,
                                   uint8_t oprnd0,
                                   qspi_lut_commands_t instr1,
                                   qspi_lut_pads_t pad1,
                                   uint8_t oprnd1)
{
    QuadSPI_Type *baseAddr;
    DEV_ASSERT(instance < QuadSPI_INSTANCE_COUNT);
    DEV_ASSERT(lut < QuadSPI_LUT_COUNT);

    baseAddr = g_qspiBase[instance];
    baseAddr->LUT[lut] = QuadSPI_LUT_INSTR0(instr0)
                       | QuadSPI_LUT_PAD0(pad0)
                       | QuadSPI_LUT_OPRND0(oprnd0)
                       | QuadSPI_LUT_INSTR1(instr1)
                       | QuadSPI_LUT_PAD1(pad1)
                       | QuadSPI_LUT_OPRND1(oprnd1);
}


static inline void QSPI_DRV_LockLut(uint32_t instance)
{
    QuadSPI_Type *baseAddr;
    DEV_ASSERT(instance < QuadSPI_INSTANCE_COUNT);

    baseAddr = g_qspiBase[instance];
    baseAddr->LUTKEY = QSPI_LUT_LOCK_KEY;
    baseAddr->LCKCR = QuadSPI_LCKCR_LOCK_MASK;
}



static inline void QSPI_DRV_UnlockLut(uint32_t instance)
{
    QuadSPI_Type *baseAddr;
    DEV_ASSERT(instance < QuadSPI_INSTANCE_COUNT);

    baseAddr = g_qspiBase[instance];
    baseAddr->LUTKEY = QSPI_LUT_LOCK_KEY;
    baseAddr->LCKCR = QuadSPI_LCKCR_UNLOCK_MASK;
}


static inline void QSPI_DRV_ClearIpSeqPointer(uint32_t instance)
{
    QuadSPI_Type *baseAddr;
    DEV_ASSERT(instance < QuadSPI_INSTANCE_COUNT);

    baseAddr = g_qspiBase[instance];
    baseAddr->SPTRCLR = QuadSPI_SPTRCLR_IPPTRC_MASK;
}


static inline void QSPI_DRV_ClearAHBSeqPointer(uint32_t instance)
{
    QuadSPI_Type *baseAddr;
    DEV_ASSERT(instance < QuadSPI_INSTANCE_COUNT);

    baseAddr = g_qspiBase[instance];
    baseAddr->SPTRCLR = QuadSPI_SPTRCLR_BFPTRC_MASK;
}


static inline void QSPI_DRV_SetAhbSeqId(uint32_t instance, 
                                        uint8_t seqID)
{
    QuadSPI_Type *baseAddr;
    DEV_ASSERT(instance < QuadSPI_INSTANCE_COUNT);

    baseAddr = g_qspiBase[instance];
    baseAddr->BFGENCR =  QuadSPI_BFGENCR_SEQID(seqID);
}


status_t QSPI_DRV_IpCommand(uint32_t instance, uint8_t lut, uint32_t timeout);


status_t QSPI_DRV_IpRead(uint32_t instance, 
                         uint8_t lut, 
                         uint32_t addr, 
                         uint8_t * dataRead,
                         const uint8_t * dataCmp,
                         uint32_t size,
                         qspi_transfer_type_t transferType,
                         uint32_t timeout);


status_t QSPI_DRV_IpWrite(uint32_t instance, 
                          uint8_t lut, 
                          uint32_t addr, 
                          const uint8_t * data, 
                          uint32_t size,
                          qspi_transfer_type_t transferType,
                          uint32_t timeout);


status_t QSPI_DRV_IpErase(uint32_t instance, 
                          uint8_t lut, 
                          uint32_t addr);


status_t QSPI_DRV_IpGetStatus(uint32_t instance);


#if defined(__cplusplus)
}
#endif


#endif 

