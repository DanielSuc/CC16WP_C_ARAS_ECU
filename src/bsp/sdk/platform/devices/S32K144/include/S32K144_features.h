

#if !defined(S32K144_FEATURES_H)
#define S32K144_FEATURES_H


#define ERRATA_E9005

#define ERRATA_E6940

#define ERRATA_E10655

#define ERRATA_E10792

#define ERRATA_E10777

#define ERRATA_E10856

#define NUMBER_OF_CORES (1u)

#define NUMBER_OF_ALT_CLOCKS  ADC_CLK_ALT_1


#define FEATURE_PCC_HAS_IN_USE_FEATURE (0)

#define FEATURE_PINS_DRIVER_USING_PORT (1)
#define FEATURE_PORT_HAS_PIN_CONTROL_LOCK (1)
#define FEATURE_PINS_HAS_OPEN_DRAIN (0)
#define FEATURE_PORT_HAS_DIGITAL_FILTER (1)
#define FEATURE_PORT_HAS_TRIGGER_OUT (0)
#define FEATURE_PORT_HAS_FLAG_SET_ONLY (0)
#define FEATURE_PINS_HAS_OVER_CURRENT (0)
#define FEATURE_PINS_HAS_PULL_SELECTION (1)
#define FEATURE_PINS_HAS_SLEW_RATE (0)
#define FEATURE_PORT_HAS_PASSIVE_FILTER (1)
#define FEATURE_PINS_HAS_DRIVE_STRENGTH (1)
#define FEATURE_PINS_HAS_DRIVE_STRENGTH_CONTROL (0)
#define FEATURE_PORT_HAS_INPUT_DISABLE (1)
#define FEATURE_PINS_HAS_ADC_INTERLEAVE_EN (1)


#define FEATURE_SOC_PORT_COUNT (5)

#define FEATURE_SOC_SCG_COUNT (1)

#define FEATURE_SCG_SIRC_HIGH_RANGE_FREQ (8000000U)

#define FEATURE_SCG_FIRC_FREQ0  (48000000U)


#define FEATURE_CMP_HAS_HARD_BLOCK_OFFSET   (1)
#define FEATURE_CMP_DAC_FIX_SELECTION       (0)
#define FEATURE_CMP_HAS_INIT_DELAY          (1)

#define C0_RESET_VALUE (CMP_C0_DMAEN(0U) | CMP_C0_IER(0U) | CMP_C0_IEF(0U) | CMP_C0_CFR(1U) |                     \
                        CMP_C0_CFF(1U) | CMP_C0_FPR(0U) | CMP_C0_SE(0U) | CMP_C0_WE(0U) |                         \
                        CMP_C0_PMODE(0U) | CMP_C0_INVT(0U) | CMP_C0_COS(0U) | CMP_C0_OPE(0U) |                    \
                        CMP_C0_EN(0U) | CMP_C0_FILTER_CNT(0U) | CMP_C0_OFFSET(0U) | CMP_C0_HYSTCTR(0U))

#define C1_RESET_VALUE (CMP_C1_INPSEL(0U) | CMP_C1_INNSEL(0U) | CMP_C1_CHN7(0U) | CMP_C1_CHN6(0U) |               \
                        CMP_C1_CHN5(0U) | CMP_C1_CHN4(0U) | CMP_C1_CHN3(0U) | CMP_C1_CHN2(0U) |                   \
                        CMP_C1_CHN1(0U) | CMP_C1_CHN0(0U) | CMP_C1_DACEN(0U) | CMP_C1_VRSEL(0U) |                 \
                        CMP_C1_PSEL(0U) | CMP_C1_MSEL(0U) |  CMP_C1_VOSEL(0U))

#define C2_RESET_VALUE (CMP_C2_RRE(0U) | CMP_C2_RRIE(0U) | CMP_C2_FXMP(0U) | CMP_C2_FXMXCH(0U) | CMP_C2_CH7F(1U) |    \
                        CMP_C2_CH6F(1U) | CMP_C2_CH5F(1U) | CMP_C2_CH4F(1U) | CMP_C2_CH3F(1U) | CMP_C2_CH2F(1U) |     \
                        CMP_C2_CH1F(1U) | CMP_C2_CH0F(1U) | CMP_C2_NSAM(0U) | CMP_C2_NSAM(0U) | CMP_C2_INITMOD(0U) |  \
                        CMP_C2_ACOn(0U))

#define CMP_DAC_SOURCE          0U
#define CMP_MUX_SOURCE          1U
#define CMP_DAC_RESOLUTION      255U


#define FEATURE_FLS_IS_FTFA (0u)
#define FEATURE_FLS_IS_FTFC (1u)
#define FEATURE_FLS_IS_FTFE (0u)
#define FEATURE_FLS_IS_FTFL (0u)
#define FEATURE_FLS_HAS_FLEX_RAM_FLAGS (1u)
#define FEATURE_FLS_HAS_PF_SWAPPING_STATUS_FLAG (0u)
#define FEATURE_FLS_HAS_EEROM_REGION_PROTECTION (1u)
#define FEATURE_FLS_HAS_DATA_FLS_REGION_PROTECTION (1u)
#define FEATURE_FLS_PF_BLOCK_COUNT (1u)
#define FEATURE_FLS_PF_BLOCK_SIZE (0x80000U)
#define FEATURE_FLS_PF_BLOCK_SECTOR_SIZE (4096u)
#define FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE (8u)
#define FEATURE_FLS_HAS_PF_BLOCK_SWAP (0u)
#define FEATURE_FLS_HAS_FLEX_NVM (1u)
#define FEATURE_FLS_DF_BLOCK_COUNT (1u)
#define FEATURE_FLS_DF_BLOCK_SIZE (65536u)
#define FEATURE_FLS_DF_BLOCK_SECTOR_SIZE (2048u)
#define FEATURE_FLS_DF_BLOCK_WRITE_UNIT_SIZE (8u)
#define FEATURE_FLS_DF_START_ADDRESS (0x10000000u)
#define FEATURE_FLS_HAS_FLEX_RAM (1u)
#define FEATURE_FLS_FLEX_RAM_SIZE (4096u)
#define FEATURE_FLS_FLEX_RAM_START_ADDRESS (0x14000000u)
#define FEATURE_FLS_HAS_READ_1S_BLOCK_CMD (1u)
#define FEATURE_FLS_HAS_READ_1S_SECTION_CMD (1u)
#define FEATURE_FLS_HAS_PROGRAM_CHECK_CMD (1u)
#define FEATURE_FLS_HAS_READ_RESOURCE_CMD (0u)
#define FEATURE_FLS_HAS_PROGRAM_LONGWORD_CMD (0u)
#define FEATURE_FLS_HAS_PROGRAM_PHRASE_CMD (1u)
#define FEATURE_FLS_HAS_ERASE_BLOCK_CMD (1u)
#define FEATURE_FLS_HAS_ERASE_SECTOR_CMD (1u)
#define FEATURE_FLS_HAS_PROGRAM_SECTION_CMD (1u)
#define FEATURE_FLS_HAS_READ_1S_ALL_BLOCKS_CMD (1u)
#define FEATURE_FLS_HAS_READ_ONCE_CMD (1u)
#define FEATURE_FLS_HAS_PROGRAM_ONCE_CMD (1u)
#define FEATURE_FLS_HAS_ERASE_ALL_CMD (1u)
#define FEATURE_FLS_HAS_VERIFY_BACKDOOR_ACCESS_KEY_CMD (1u)
#define FEATURE_FLS_HAS_SWAP_CONTROL_CMD (0u)
#define FEATURE_FLS_HAS_ERASE_ALL_BLOCKS_UNSECURE_CMD (1u)
#define FEATURE_FLS_HAS_PROGRAM_PARTITION_CMD (1u)
#define FEATURE_FLS_HAS_SET_FLEXRAM_FUNCTION_CMD (1u)
#define FEATURE_FLS_PF_BLOCK_CMD_ADDRESS_ALIGMENT (16u)
#define FEATURE_FLS_PF_SECTOR_CMD_ADDRESS_ALIGMENT (16u)
#define FEATURE_FLS_PF_SECTION_CMD_ADDRESS_ALIGMENT (16u)
#define FEATURE_FLS_PF_RESOURCE_CMD_ADDRESS_ALIGMENT (8u)
#define FEATURE_FLS_PF_CHECK_CMD_ADDRESS_ALIGMENT (4u)
#define FEATURE_FLS_PF_SWAP_CONTROL_CMD_ADDRESS_ALIGMENT (0u)
#define FEATURE_FLS_DF_BLOCK_CMD_ADDRESS_ALIGMENT (8u)
#define FEATURE_FLS_DF_SECTOR_CMD_ADDRESS_ALIGMENT (8u)
#define FEATURE_FLS_DF_SECTION_CMD_ADDRESS_ALIGMENT (8u)
#define FEATURE_FLS_DF_RESOURCE_CMD_ADDRESS_ALIGMENT (8u)
#define FEATURE_FLS_DF_CHECK_CMD_ADDRESS_ALIGMENT (4u)
#define FEATURE_FLS_DF_SIZE_0000 (0x00010000u)
#define FEATURE_FLS_DF_SIZE_0001 (0xFFFFFFFFu)
#define FEATURE_FLS_DF_SIZE_0010 (0xFFFFFFFFu)
#define FEATURE_FLS_DF_SIZE_0011 (0x00008000u)
#define FEATURE_FLS_DF_SIZE_0100 (0x00000000u)
#define FEATURE_FLS_DF_SIZE_0101 (0xFFFFFFFFu)
#define FEATURE_FLS_DF_SIZE_0110 (0xFFFFFFFFu)
#define FEATURE_FLS_DF_SIZE_0111 (0xFFFFFFFFu)
#define FEATURE_FLS_DF_SIZE_1000 (0x00000000u)
#define FEATURE_FLS_DF_SIZE_1001 (0xFFFFFFFFu)
#define FEATURE_FLS_DF_SIZE_1010 (0x00004000u)
#define FEATURE_FLS_DF_SIZE_1011 (0x00008000u)
#define FEATURE_FLS_DF_SIZE_1100 (0x00010000u)
#define FEATURE_FLS_DF_SIZE_1101 (0xFFFFFFFFu)
#define FEATURE_FLS_DF_SIZE_1110 (0xFFFFFFFFu)
#define FEATURE_FLS_DF_SIZE_1111 (0x00010000u)
#define FEATURE_FLS_EE_SIZE_0000 (0xFFFFu)
#define FEATURE_FLS_EE_SIZE_0001 (0xFFFFu)
#define FEATURE_FLS_EE_SIZE_0010 (0x1000u)
#define FEATURE_FLS_EE_SIZE_0011 (0xFFFFu)
#define FEATURE_FLS_EE_SIZE_0100 (0xFFFFu)
#define FEATURE_FLS_EE_SIZE_0101 (0xFFFFu)
#define FEATURE_FLS_EE_SIZE_0110 (0xFFFFu)
#define FEATURE_FLS_EE_SIZE_0111 (0xFFFFu)
#define FEATURE_FLS_EE_SIZE_1000 (0xFFFFu)
#define FEATURE_FLS_EE_SIZE_1001 (0xFFFFu)
#define FEATURE_FLS_EE_SIZE_1010 (0xFFFFu)
#define FEATURE_FLS_EE_SIZE_1011 (0xFFFFu)
#define FEATURE_FLS_EE_SIZE_1100 (0xFFFFu)
#define FEATURE_FLS_EE_SIZE_1101 (0xFFFFu)
#define FEATURE_FLS_EE_SIZE_1110 (0xFFFFu)
#define FEATURE_FLS_EE_SIZE_1111 (0x0000u)
#define FEATURE_FLS_HAS_DETECT_ECC_ERROR (1)
#define FEATURE_FLS_HAS_INTERRUPT_DOUBLE_BIT_FAULT_IRQ (1)


#define FEATURE_CAN_RXFIFO_FRAME_AVAILABLE  (5U)
#define FEATURE_CAN_RXFIFO_WARNING          (6U)
#define FEATURE_CAN_RXFIFO_OVERFLOW         (7U)
#define FEATURE_CAN0_HAS_FD                 (1)
#define FEATURE_CAN1_HAS_FD                 (0)
#define FEATURE_CAN2_HAS_FD                 (0)
#define FEATURE_CAN0_MAX_MB_NUM             (32U)
#define FEATURE_CAN1_MAX_MB_NUM             (16U)
#define FEATURE_CAN2_MAX_MB_NUM             (16U)
#define FEATURE_CAN_HAS_PE_CLKSRC_SELECT    (1)
#define FEATURE_CAN_HAS_DMA_ENABLE          (1)
#define FEATURE_CAN_MAX_MB_NUM              (32U)
#define FEATURE_CAN_MAX_MB_NUM_ARRAY        { FEATURE_CAN0_MAX_MB_NUM, \
                                              FEATURE_CAN1_MAX_MB_NUM, \
                                              FEATURE_CAN2_MAX_MB_NUM }
#define FEATURE_CAN_HAS_PRETENDED_NETWORKING    (1)
#define FEATURE_CAN_HAS_STFCNTEN_ENABLE         (0)
#define FEATURE_CAN_HAS_ISOCANFDEN_ENABLE       (1)
#define FEATURE_CAN_HAS_MBDSR1                  (0)
#define FEATURE_CAN_HAS_MBDSR2                  (0)
#define FEATURE_CAN_EDMA_REQUESTS              { EDMA_REQ_FLEXCAN0, \
                                                 EDMA_REQ_FLEXCAN1, \
                                                 EDMA_REQ_FLEXCAN2 }


#define FEATURE_CAN_MB_IRQS_MAX_COUNT       (2U)
#define FEATURE_CAN_MB_IRQS                 { CAN_ORed_0_15_MB_IRQS, \
                                              CAN_ORed_16_31_MB_IRQS }
#define FEATURE_CAN_HAS_WAKE_UP_IRQ         (1)
#define FEATURE_CAN_HAS_SELF_WAKE_UP        (0)
#define FEATURE_CAN_HAS_FD                  (1)
#define FEATURE_CAN_PE_OSC_CLK_NAME         SOSC_CLK
#define FEATURE_CAN_HAS_MEM_ERR_DET			(0)


#define FEATURE_LPUART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
#define FEATURE_LPUART_HAS_MODEM_SUPPORT (1)
#define FEATURE_LPUART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (1)
#define FEATURE_LPUART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (1)
#define FEATURE_LPUART_FIFO_SIZE (4U)
#define FEATURE_LPUART_HAS_ADDRESS_MATCHING (1)
#define FEATURE_LPUART_HAS_DMA_ENABLE (1)
#define FEATURE_LPUART_STAT_REG_FLAGS_MASK (0xC01FC000U)
#define FEATURE_LPUART_FIFO_REG_FLAGS_MASK (0x00030000U)
#define FEATURE_LPUART_FIFO_RESET_MASK (0x0003C000U)
#define FEATURE_LPUART_DEFAULT_OSR (0x0FUL)
#define FEATURE_LPUART_DEFAULT_SBR (0x04UL)
#define LPUART_CLOCK_NAMES {LPUART0_CLK, LPUART1_CLK, LPUART2_CLK}


#define FEATURE_FLEXIO_MAX_SHIFTER_COUNT  (4U)
#define FEATURE_FLEXIO_DMA_REQ_0    EDMA_REQ_FLEXIO_SHIFTER0
#define FEATURE_FLEXIO_DMA_REQ_1    EDMA_REQ_FLEXIO_SHIFTER1
#define FEATURE_FLEXIO_DMA_REQ_2    EDMA_REQ_FLEXIO_SHIFTER2
#define FEATURE_FLEXIO_DMA_REQ_3    EDMA_REQ_FLEXIO_SHIFTER3


#define LPSPI_DMA_INSTANCE 0U


#define LPI2C_DMA_INSTANCE 0U

#define LPI2C_EDMA_REQ                           {{(uint8_t)EDMA_REQ_LPI2C0_TX, (uint8_t)EDMA_REQ_LPI2C0_RX}}
#define LPI2C_PCC_CLOCKS                         {LPI2C0_CLK}


#define FEATURE_INTERRUPT_IRQ_MIN         (NonMaskableInt_IRQn)
#define FEATURE_INTERRUPT_IRQ_MAX         (FTM3_Ovf_Reload_IRQn)
#define FEATURE_NVIC_PRIO_BITS            (4U)
#define FEATURE_INTERRUPT_HAS_SOFTWARE_IRQ  (0u)
#define FEATURE_INTERRUPT_HAS_PENDING_STATE (1u)
#define FEATURE_INTERRUPT_HAS_ACTIVE_STATE  (1u)
#define FEATURE_INTERRUPT_MULTICORE_SUPPORT  (0u)
#define FEATURE_INTERRUPT_INT_VECTORS {&S32_SCB->VTOR}



#define FEATURE_SCB_VECTKEY               (0x05FAU)



#define FEATURE_SMC_HAS_STOPO (1U)
#define FEATURE_SMC_HAS_PSTOPO (0U)
#define FEATURE_SMC_HAS_WAIT_VLPW (0U)
#define FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE (1U)
#define FEATURE_SCG_SPLL_VALUE (6U)

#define FEATURE_RCM_HAS_EXISTENCE_CMU_LOSS_OF_CLOCK (0)
#define FEATURE_RCM_HAS_CMU_LOSS_OF_CLOCK (0)
#define FEATURE_RCM_HAS_STICKY_CMU_LOSS_OF_CLOCK (0)


#define FEATURE_MPU_HARDWARE_REVISION_LEVEL   (1U)
#define FEATURE_MPU_HAS_PROCESS_IDENTIFIER    (1U)
#define FEATURE_MPU_MASTER_COUNT              (3U)
#define FEATURE_MPU_MAX_LOW_MASTER_NUMBER     (3U)
#define FEATURE_MPU_MAX_HIGH_MASTER_NUMBER    (7U)

#define FEATURE_MPU_LOW_MASTER_CONTROL_WIDTH  (6U)
#define FEATURE_MPU_HIGH_MASTER_CONTROL_WIDTH (2U)

#define FEATURE_MPU_MASTER_CORE               (0U)
#define FEATURE_MPU_MASTER_DEBUGGER           (1U)
#define FEATURE_MPU_MASTER_DMA                (2U)
#define FEATURE_MPU_MASTER                        \
{                                                 \
    FEATURE_MPU_MASTER_CORE,          \
    FEATURE_MPU_MASTER_DEBUGGER,  \
    FEATURE_MPU_MASTER_DMA,            \
}

#define FEATURE_MPU_SLAVE_COUNT               (4U)
#define FEATURE_MPU_SLAVE_FLASH_BOOTROM       (0U)
#define FEATURE_MPU_SLAVE_SRAM_BACKDOOR       (1U)
#define FEATURE_MPU_SLAVE_SRAM_L_FRONTDOOR    (2U)
#define FEATURE_MPU_SLAVE_SRAM_U_FRONTDOOR    (3U)
#define FEATURE_MPU_SLAVE_MASK                (0xF0000000U)
#define FEATURE_MPU_SLAVE_SHIFT               (28u)
#define FEATURE_MPU_SLAVE_WIDTH               (4u)
#define FEATURE_MPU_SLAVE(x)                  (((uint32_t)(((uint32_t)(x))<<FEATURE_MPU_SLAVE_SHIFT))&FEATURE_MPU_SLAVE_MASK)


#define FEATURE_WDOG_UNLOCK_VALUE                       (0xD928C520U)
#define FEATURE_WDOG_TRIGGER_VALUE                      (0xB480A602U)
#define FEATURE_WDOG_TO_RESET_VALUE                     (0x400U)
#define FEATURE_WDOG_MINIMUM_TIMEOUT_VALUE              (0x0U)
#define FEATURE_WDOG_WIN_RESET_VALUE                    (0x0U)
#define FEATURE_WDOG_CS_RESERVED_MASK                   (0x2000U)
#define FEATURE_WDOG_CLK_FROM_LPO                       (0x1UL)
#define FEATURE_WDOG_UNLOCK16_FIRST_VALUE               (0xC520U)
#define FEATURE_WDOG_UNLOCK16_SECOND_VALUE              (0xD928U)
#define FEATURE_WDOG_TRIGGER16_FIRST_VALUE              (0xA602U)
#define FEATURE_WDOG_TRIGGER16_SECOND_VALUE             (0xB480U)
#define FEATURE_WDOG_CS_RESET_VALUE                     (0x2520U)


#define FEATURE_CRC_DRIVER_SOFT_POLYNOMIAL
#define FEATURE_CRC_DEFAULT_WIDTH               CRC_BITS_16
#define FEATURE_CRC_DEFAULT_READ_TRANSPOSE      CRC_TRANSPOSE_NONE
#define FEATURE_CRC_DEFAULT_WRITE_TRANSPOSE     CRC_TRANSPOSE_NONE
#define FEATURE_CRC_DEFAULT_POLYNOMIAL          (0x1021U)
#define FEATURE_CRC_DEFAULT_SEED                (0xFFFFU)


#define FEATURE_DMA_CHANNELS (16U)
#define FEATURE_DMA_VIRTUAL_CHANNELS (FEATURE_DMA_CHANNELS * DMA_INSTANCE_COUNT)
#define FEATURE_DMA_CHANNELS_INTERRUPT_LINES (16U)
#define FEATURE_DMA_VIRTUAL_CHANNELS_INTERRUPT_LINES ((uint32_t)FEATURE_DMA_CHANNELS_INTERRUPT_LINES * (uint32_t)DMA_INSTANCE_COUNT)
#define FEATURE_DMA_ERROR_INTERRUPT_LINES (1U)
#define FEATURE_DMA_VIRTUAL_ERROR_INTERRUPT_LINES ((uint32_t)FEATURE_DMA_ERROR_INTERRUPT_LINES * (uint32_t)DMA_INSTANCE_COUNT)
#define FEATURE_DMA_HAS_ERROR_IRQ
#define FEATURE_DMA_SEPARATE_IRQ_LINES_PER_CHN
#define FEATURE_DMA_CHN_TO_DCHPRI_INDEX(x) ((x) ^ 3U)
#define FEATURE_DMA_CHANNEL_GROUP_COUNT (1U)
#define FEATURE_DMA_CLOCK_NAMES {SIM_DMA_CLK}
#define FEATURE_DMA_CH_WIDTH (4U)
#define FEATURE_DMA_VCH_TO_INSTANCE(x) 	((x) >> (uint32_t)FEATURE_DMA_CH_WIDTH)
#define FEATURE_DMA_VCH_TO_CH(x)        ((x) & ((uint32_t)FEATURE_DMA_CHANNELS - 1U))
#define FEATURE_DMA_TRANSFER_SIZE_16B
#define FEATURE_DMA_TRANSFER_SIZE_32B


#define FEATURE_DMAMUX_AVAILABLE
#define FEATURE_DMAMUX_CHANNELS (16U)
#define FEATURE_DMAMUX_HAS_TRIG (1)
#define FEATURE_DMAMUX_REQ_SRC_TO_CH(x) (x)
#define FEATURE_DMAMUX_REQ_SRC_TO_INSTANCE(x) (0U)
#define FEATURE_DMAMUX_DMA_CH_TO_CH(x) (x)
#define FEATURE_DMAMUX_CHN_REG_INDEX(x) (x)
#define FEATURE_DMAMUX_CLOCK_NAMES {DMAMUX0_CLK}

typedef enum {
    EDMA_REQ_DISABLED = 0U,
    EDMA_REQ_LPUART0_RX = 2U,
    EDMA_REQ_LPUART0_TX = 3U,
    EDMA_REQ_LPUART1_RX = 4U,
    EDMA_REQ_LPUART1_TX = 5U,
    EDMA_REQ_LPUART2_RX = 6U,
    EDMA_REQ_LPUART2_TX = 7U,
    EDMA_REQ_FLEXIO_SHIFTER0 = 10U,
    EDMA_REQ_FLEXIO_SHIFTER1 = 11U,
    EDMA_REQ_FLEXIO_SHIFTER2 = 12U,
    EDMA_REQ_FLEXIO_SHIFTER3 = 13U,
    EDMA_REQ_LPSPI0_RX = 14U,
    EDMA_REQ_LPSPI0_TX = 15U,
    EDMA_REQ_LPSPI1_RX = 16U,
    EDMA_REQ_LPSPI1_TX = 17U,
    EDMA_REQ_LPSPI2_RX = 18U,
    EDMA_REQ_LPSPI2_TX = 19U,
    EDMA_REQ_FTM1_CHANNEL_0 = 20U,
    EDMA_REQ_FTM1_CHANNEL_1 = 21U,
    EDMA_REQ_FTM1_CHANNEL_2 = 22U,
    EDMA_REQ_FTM1_CHANNEL_3 = 23U,
    EDMA_REQ_FTM1_CHANNEL_4 = 24U,
    EDMA_REQ_FTM1_CHANNEL_5 = 25U,
    EDMA_REQ_FTM1_CHANNEL_6 = 26U,
    EDMA_REQ_FTM1_CHANNEL_7 = 27U,
    EDMA_REQ_FTM2_CHANNEL_0 = 28U,
    EDMA_REQ_FTM2_CHANNEL_1 = 29U,
    EDMA_REQ_FTM2_CHANNEL_2 = 30U,
    EDMA_REQ_FTM2_CHANNEL_3 = 31U,
    EDMA_REQ_FTM2_CHANNEL_4 = 32U,
    EDMA_REQ_FTM2_CHANNEL_5 = 33U,
    EDMA_REQ_FTM2_CHANNEL_6 = 34U,
    EDMA_REQ_FTM2_CHANNEL_7 = 35U,
    EDMA_REQ_FTM0_OR_CH0_CH7 = 36U,
    EDMA_REQ_FTM3_OR_CH0_CH7 = 37U,
    EDMA_REQ_ADC0 = 42U,
    EDMA_REQ_ADC1 = 43U,
    EDMA_REQ_LPI2C0_RX = 44U,
    EDMA_REQ_LPI2C0_TX = 45U,
    EDMA_REQ_PDB0 = 46U,
    EDMA_REQ_PDB1 = 47U,
    EDMA_REQ_CMP0 = 48U,
    EDMA_REQ_PORTA = 49U,
    EDMA_REQ_PORTB = 50U,
    EDMA_REQ_PORTC = 51U,
    EDMA_REQ_PORTD = 52U,
    EDMA_REQ_PORTE = 53U,
    EDMA_REQ_FLEXCAN0 = 54U,
    EDMA_REQ_FLEXCAN1 = 55U,
    EDMA_REQ_FLEXCAN2 = 56U,
    EDMA_REQ_LPTMR0 = 59U,
    EDMA_REQ_DMAMUX_ALWAYS_ENABLED0 = 62U,
    EDMA_REQ_DMAMUX_ALWAYS_ENABLED1 = 63U
} dma_request_source_t;


#define LPI2C_HAS_FAST_PLUS_MODE (0U)
#define LPI2C_HAS_HIGH_SPEED_MODE (0U)
#define LPI2C_HAS_ULTRA_FAST_MODE (0U)

#define FEATURE_FTM_CHANNEL_COUNT               (8U)
#define FTM_FEATURE_FAULT_CHANNELS              (4U)
#define FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH     (8U)
#define FTM_FEATURE_OUTPUT_CHANNEL_OFFSET       (16U)
#define FTM_FEATURE_CNT_MAX_VALUE_U32           (0x0000FFFFU)
#define FTM_FEATURE_INPUT_CAPTURE_SINGLE_SHOT   (2U)
#define FEATURE_FTM_HAS_SUPPORTED_DITHERING     (0U)
#define FEATURE_FTM_HAS_NUM_IRQS_CHANS          (4U)


#define FEATURE_EWM_KEY_FIRST_BYTE      (0xB4U)
#define FEATURE_EWM_KEY_SECOND_BYTE     (0x2CU)
#define FEATURE_EWM_CMPH_MAX_VALUE      (0xFEU)
#define FEATURE_EWM_CMPL_MIN_VALUE      (0x00U)

#define FEATURE_HAS_HIGH_SPEED_RUN_MODE  (1U)
#define FEATURE_HAS_SPLL_CLK             (1U)

typedef enum {

    CORE_CLK                     = 0u,       
    BUS_CLK                      = 1u,       
    SLOW_CLK                     = 2u,       
    CLKOUT_CLK                   = 3u,       

    SIRC_CLK                     = 4u,       
    FIRC_CLK                     = 5u,       
    SOSC_CLK                     = 6u,       
    SPLL_CLK                     = 7u,       
    RTC_CLKIN_CLK                = 8u,       
    SCG_CLKOUT_CLK               = 9u,       

    SIRCDIV1_CLK                 = 10u,      
    SIRCDIV2_CLK                 = 11u,      
    FIRCDIV1_CLK                 = 12u,      
    FIRCDIV2_CLK                 = 13u,      
    SOSCDIV1_CLK                 = 14u,      
    SOSCDIV2_CLK                 = 15u,      
    SPLLDIV1_CLK                 = 16u,      
    SPLLDIV2_CLK                 = 17u,      

    SCG_END_OF_CLOCKS            = 18u,      

    SIM_FTM0_CLOCKSEL            = 21u,      
    SIM_FTM1_CLOCKSEL            = 22u,      
    SIM_FTM2_CLOCKSEL            = 23u,      
    SIM_FTM3_CLOCKSEL            = 24u,      
    SIM_CLKOUTSELL               = 25u,      
    SIM_RTCCLK_CLK               = 26u,      
    SIM_LPO_CLK                  = 27u,      
    SIM_LPO_1K_CLK               = 28u,      
    SIM_LPO_32K_CLK              = 29u,      
    SIM_LPO_128K_CLK             = 30u,      
    SIM_EIM_CLK                  = 31u,      
    SIM_ERM_CLK                  = 32u,      
    SIM_DMA_CLK                  = 33u,      
    SIM_MPU_CLK                  = 34u,      
    SIM_MSCM_CLK                 = 35u,      
    SIM_END_OF_CLOCKS            = 36u,      

    CMP0_CLK                     = 41u,      
    CRC0_CLK                     = 42u,      
    DMAMUX0_CLK                  = 43u,      
    EWM0_CLK                     = 44u,      
    PORTA_CLK                    = 45u,      
    PORTB_CLK                    = 46u,      
    PORTC_CLK                    = 47u,      
    PORTD_CLK                    = 48u,      
    PORTE_CLK                    = 49u,      
    RTC0_CLK                     = 50u,      
    PCC_END_OF_BUS_CLOCKS        = 51u,      
    FlexCAN0_CLK                 = 52u,      
    FlexCAN1_CLK                 = 53u,      
    FlexCAN2_CLK                 = 54u,      
    PDB0_CLK                     = 55u,      
    PDB1_CLK                     = 56u,      
    PCC_END_OF_SYS_CLOCKS        = 57u,      
    FTFC0_CLK                    = 58u,      
    PCC_END_OF_SLOW_CLOCKS       = 59u,      
    FTM0_CLK                     = 60u,      
    FTM1_CLK                     = 61u,      
    FTM2_CLK                     = 62u,      
    FTM3_CLK                     = 63u,      
    PCC_END_OF_ASYNCH_DIV1_CLOCKS= 64u,      
    ADC0_CLK                     = 65u,      
    ADC1_CLK                     = 66u,      
    FLEXIO0_CLK                  = 67u,      
    LPI2C0_CLK                   = 68u,      
    LPIT0_CLK                    = 69u,      
    LPSPI0_CLK                   = 70u,      
    LPSPI1_CLK                   = 71u,      
    LPSPI2_CLK                   = 72u,      
    LPTMR0_CLK                   = 73u,      
    LPUART0_CLK                  = 74u,      
    LPUART1_CLK                  = 75u,      
    LPUART2_CLK                  = 76u,      
    PCC_END_OF_ASYNCH_DIV2_CLOCKS= 77u,      
    PCC_END_OF_CLOCKS            = 78u,      
    CLOCK_NAME_COUNT             = 79u,      
} clock_names_t;

#define PCC_INVALID_INDEX  0

#define PCC_CLOCK_NAME_MAPPINGS \
{                                                                                \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_CMP0_INDEX,                        \
PCC_CRC_INDEX,                         \
PCC_DMAMUX_INDEX,                      \
PCC_EWM_INDEX,                         \
PCC_PORTA_INDEX,                       \
PCC_PORTB_INDEX,                       \
PCC_PORTC_INDEX,                       \
PCC_PORTD_INDEX,                       \
PCC_PORTE_INDEX,                       \
PCC_RTC_INDEX,                         \
PCC_INVALID_INDEX,                     \
PCC_FlexCAN0_INDEX,                    \
PCC_FlexCAN1_INDEX,                    \
PCC_FlexCAN2_INDEX,                    \
PCC_PDB0_INDEX,                        \
PCC_PDB1_INDEX,                        \
PCC_INVALID_INDEX,                     \
PCC_FTFC_INDEX,                        \
PCC_INVALID_INDEX,                     \
PCC_FTM0_INDEX,                        \
PCC_FTM1_INDEX,                        \
PCC_FTM2_INDEX,                        \
PCC_FTM3_INDEX,                        \
PCC_INVALID_INDEX,                     \
PCC_ADC0_INDEX,                        \
PCC_ADC1_INDEX,                        \
PCC_FlexIO_INDEX,                      \
PCC_LPI2C0_INDEX,                      \
PCC_LPIT_INDEX,                        \
PCC_LPSPI0_INDEX,                      \
PCC_LPSPI1_INDEX,                      \
PCC_LPSPI2_INDEX,                      \
PCC_LPTMR0_INDEX,                      \
PCC_LPUART0_INDEX,                     \
PCC_LPUART1_INDEX,                     \
PCC_LPUART2_INDEX,                     \
PCC_INVALID_INDEX,                     \
PCC_INVALID_INDEX,                     \
}

#define NO_PERIPHERAL_FEATURE                   (0U)         
#define HAS_CLOCK_GATING_IN_SIM                 (1U << 0U)   
#define HAS_MULTIPLIER                          (1U << 1U)   
#define HAS_DIVIDER                             (1U << 2U)   
#define HAS_PROTOCOL_CLOCK_FROM_ASYNC1          (1U << 3U)   
#define HAS_PROTOCOL_CLOCK_FROM_ASYNC2          (1U << 4U)   
#define HAS_INT_CLOCK_FROM_BUS_CLOCK            (1U << 5U)   
#define HAS_INT_CLOCK_FROM_SYS_CLOCK            (1U << 6U)   
#define HAS_INT_CLOCK_FROM_SLOW_CLOCK           (1U << 7U)   

#define PERIPHERAL_FEATURES \
{                                                                                                                                                \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(HAS_CLOCK_GATING_IN_SIM | HAS_INT_CLOCK_FROM_SYS_CLOCK),                                              \
(HAS_CLOCK_GATING_IN_SIM | HAS_INT_CLOCK_FROM_SYS_CLOCK),                                              \
(HAS_CLOCK_GATING_IN_SIM | HAS_INT_CLOCK_FROM_SYS_CLOCK),                                              \
(HAS_CLOCK_GATING_IN_SIM | HAS_INT_CLOCK_FROM_SYS_CLOCK),                                              \
(HAS_CLOCK_GATING_IN_SIM | HAS_INT_CLOCK_FROM_SYS_CLOCK),                                              \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                        \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                        \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                        \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                        \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                        \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                        \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                        \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                        \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                        \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                        \
(NO_PERIPHERAL_FEATURE),                                                                               \
(HAS_INT_CLOCK_FROM_SYS_CLOCK),                                                                        \
(HAS_INT_CLOCK_FROM_SYS_CLOCK),                                                                        \
(HAS_INT_CLOCK_FROM_SYS_CLOCK),                                                                        \
(HAS_INT_CLOCK_FROM_SYS_CLOCK),                                                                        \
(HAS_INT_CLOCK_FROM_SYS_CLOCK),                                                                        \
(NO_PERIPHERAL_FEATURE),                                                                               \
(HAS_INT_CLOCK_FROM_SLOW_CLOCK),                                                                       \
(NO_PERIPHERAL_FEATURE),                                                                               \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC1 | HAS_INT_CLOCK_FROM_SYS_CLOCK),                                       \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC1 | HAS_INT_CLOCK_FROM_SYS_CLOCK),                                       \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC1 | HAS_INT_CLOCK_FROM_SYS_CLOCK),                                       \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC1 | HAS_INT_CLOCK_FROM_SYS_CLOCK),                                       \
(NO_PERIPHERAL_FEATURE),                                                                               \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),                                       \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),                                       \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),                                       \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),                                       \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),                                       \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),                                       \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),                                       \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),                                       \
(HAS_MULTIPLIER | HAS_DIVIDER | HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),        \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),                                       \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),                                       \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),                                       \
(NO_PERIPHERAL_FEATURE),                                                                               \
(NO_PERIPHERAL_FEATURE),                                                                               \
}

#define SIRC_STABILIZATION_TIMEOUT 100U

#define FIRC_STABILIZATION_TIMEOUT 20U

#define SOSC_STABILIZATION_TIMEOUT 3205000U;

#define SPLL_STABILIZATION_TIMEOUT 1000U;


#define TMP_SIRC_CLK   0U
#define TMP_FIRC_CLK   1U
#define TMP_SOSC_CLK   2U
#define TMP_SPLL_CLK   3U

#define TMP_SYS_DIV    0U
#define TMP_BUS_DIV    1U
#define TMP_SLOW_DIV   2U

#define TMP_SYS_CLK_NO 4U
#define TMP_SYS_DIV_NO 3U

#define TMP_SYSTEM_CLOCK_CONFIGS                                                                                \
{                                  \
{  SCG_SYSTEM_CLOCK_DIV_BY_1, SCG_SYSTEM_CLOCK_DIV_BY_1, SCG_SYSTEM_CLOCK_DIV_BY_2},   \
{  SCG_SYSTEM_CLOCK_DIV_BY_1, SCG_SYSTEM_CLOCK_DIV_BY_2, SCG_SYSTEM_CLOCK_DIV_BY_4},   \
{  SCG_SYSTEM_CLOCK_DIV_BY_1, SCG_SYSTEM_CLOCK_DIV_BY_2, SCG_SYSTEM_CLOCK_DIV_BY_2},   \
{  SCG_SYSTEM_CLOCK_DIV_BY_3, SCG_SYSTEM_CLOCK_DIV_BY_2, SCG_SYSTEM_CLOCK_DIV_BY_2},   \
}


#if !defined(DO_NOT_USE_DEPRECATED_SYMBOLS)
#define    CORE_CLOCK               CORE_CLK
#define    BUS_CLOCK                BUS_CLK
#define    SLOW_CLOCK               SLOW_CLK
#define    CLKOUT_CLOCK             CLKOUT_CLK
#define    SIRC_CLOCK               SIRC_CLK
#define    FIRC_CLOCK               FIRC_CLK
#define    SOSC_CLOCK               SOSC_CLK
#define    SPLL_CLOCK               SPLL_CLK
#define    RTC_CLKIN_CLOCK          RTC_CLKIN_CLK
#define    SCG_CLKOUT_CLOCK         SCG_CLKOUT_CLK
#define    SIM_RTCCLK_CLOCK         SIM_RTCCLK_CLK
#define    SIM_LPO_CLOCK            SIM_LPO_CLK
#define    SIM_LPO_1K_CLOCK         SIM_LPO_1K_CLK
#define    SIM_LPO_32K_CLOCK        SIM_LPO_32K_CLK
#define    SIM_LPO_128K_CLOCK       SIM_LPO_128K_CLK
#define    SIM_EIM_CLOCK            SIM_EIM_CLK
#define    SIM_ERM_CLOCK            SIM_ERM_CLK
#define    SIM_DMA_CLOCK            SIM_DMA_CLK
#define    SIM_MPU_CLOCK            SIM_MPU_CLK
#define    SIM_MSCM_CLOCK           SIM_MSCM_CLK
#define    PCC_DMAMUX0_CLOCK        DMAMUX0_CLK
#define    PCC_CRC0_CLOCK           CRC0_CLK
#define    PCC_RTC0_CLOCK           RTC0_CLK
#define    PCC_PORTA_CLOCK          PORTA_CLK
#define    PCC_PORTB_CLOCK          PORTB_CLK
#define    PCC_PORTC_CLOCK          PORTC_CLK
#define    PCC_PORTD_CLOCK          PORTD_CLK
#define    PCC_PORTE_CLOCK          PORTE_CLK
#define    PCC_EWM0_CLOCK           EWM0_CLK
#define    PCC_CMP0_CLOCK           CMP0_CLK
#define    PCC_FlexCAN0_CLOCK       FlexCAN0_CLK
#define    PCC_FlexCAN1_CLOCK       FlexCAN1_CLK
#define    PCC_FlexCAN2_CLOCK       FlexCAN2_CLK
#define    PCC_PDB1_CLOCK           PDB1_CLK
#define    PCC_PDB0_CLOCK           PDB0_CLK
#define    PCC_FTFC0_CLOCK          FTFC0_CLK
#define    PCC_FTM0_CLOCK           FTM0_CLK
#define    PCC_FTM1_CLOCK           FTM1_CLK
#define    PCC_FTM2_CLOCK           FTM2_CLK
#define    PCC_FTM3_CLOCK           FTM3_CLK
#define    PCC_ADC1_CLOCK           ADC1_CLK
#define    PCC_LPSPI0_CLOCK         LPSPI0_CLK
#define    PCC_LPSPI1_CLOCK         LPSPI1_CLK
#define    PCC_LPSPI2_CLOCK         LPSPI2_CLK
#define    PCC_LPIT0_CLOCK          LPIT0_CLK
#define    PCC_ADC0_CLOCK           ADC0_CLK
#define    PCC_LPTMR0_CLOCK         LPTMR0_CLK
#define    PCC_FLEXIO0_CLOCK        FLEXIO0_CLK
#define    PCC_LPI2C0_CLOCK         LPI2C0_CLK
#define    PCC_LPUART0_CLOCK        LPUART0_CLK
#define    PCC_LPUART1_CLOCK        LPUART1_CLK
#define    PCC_LPUART2_CLOCK        LPUART2_CLK
#endif 



#define FEATURE_CSEC_PAGE_LENGTH_OFFSET                   (0xEU)
#define FEATURE_CSEC_MESSAGE_LENGTH_OFFSET                (0xCU)
#define FEATURE_CSEC_MAC_LENGTH_OFFSET                    (0x8U)
#define FEATURE_CSEC_BOOT_SIZE_OFFSET                     (0x1CU)
#define FEATURE_CSEC_BOOT_FLAVOR_OFFSET                   (0x1BU)
#define FEATURE_CSEC_FLASH_START_ADDRESS_OFFSET           (0x10U)
#define FEATURE_CSEC_VERIFICATION_STATUS_OFFSET           (0x14U)
#define FEATURE_CSEC_ERROR_BITS_OFFSET                    (0x4U)
#define FEATURE_CSEC_SREG_OFFSET                          (0x2FU)

#define FEATURE_CSEC_PAGE_0_OFFSET                        (0x0U)
#define FEATURE_CSEC_PAGE_1_OFFSET                        (0x10U)
#define FEATURE_CSEC_PAGE_2_OFFSET                        (0x20U)
#define FEATURE_CSEC_PAGE_3_OFFSET                        (0x30U)
#define FEATURE_CSEC_PAGE_4_OFFSET                        (0x40U)
#define FEATURE_CSEC_PAGE_5_OFFSET                        (0x50U)
#define FEATURE_CSEC_PAGE_6_OFFSET                        (0x60U)
#define FEATURE_CSEC_PAGE_7_OFFSET                        (0x70U)



#define FEATURE_ADC_HAS_EXTRA_NUM_REGS                    (0)

#define FEATURE_ADC_MAX_NUM_EXT_CHANS                     (16)
#define FEATURE_ADC_HAS_CHANNEL_2                         (1)
#define FEATURE_ADC_HAS_CHANNEL_8                         (1)
#define ADC_CLOCKS                                        {ADC0_CLK, ADC1_CLK}

#if FEATURE_ADC_HAS_EXTRA_NUM_REGS
#define ADC_CTRL_CHANS_COUNT                              ADC_aSC1_COUNT
#else
#define ADC_CTRL_CHANS_COUNT                              ADC_SC1_COUNT
#endif 

#define ADC_DEFAULT_SAMPLE_TIME                           (0x0CU)
#define ADC_DEFAULT_USER_GAIN                             (0x04U)
#define ADC_CLOCK_FREQ_MAX_RUNTIME     (50000000u)
#define ADC_CLOCK_FREQ_MIN_RUNTIME     (2000000u)


#define FEATURE_LPIT_HAS_NUM_IRQS_CHANS                  (4U)
#define LPIT_CLOCK_NAMES    {LPIT0_CLK}


#define FEATURE_MSCM_HAS_INTERRUPT_ROUTER                (0)
#define FEATURE_MSCM_HAS_CPU_INTERRUPT_ROUTER            (0)


#define FEATURE_OSIF_USE_SYSTICK                         (1)
#define FEATURE_OSIF_USE_PIT                             (0)
#define FEATURE_OSIF_FREERTOS_ISR_CONTEXT_METHOD         (1) 

#define FEATURE_LPSPI_STATE_STRUCTURES_NULL {NULL, NULL, NULL}
#define FEATURE_LPSPI_CLOCKS_NAMES {LPSPI0_CLK, LPSPI1_CLK, LPSPI2_CLK};


#define FEATURE_LPTMR_HAS_INPUT_ALT1_SELECTION           (1U)

enum trgmux_trigger_source_e
{
    TRGMUX_TRIG_SOURCE_DISABLED             = 0U,
    TRGMUX_TRIG_SOURCE_VDD                  = 1U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN0           = 2U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN1           = 3U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN2           = 4U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN3           = 5U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN4           = 6U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN5           = 7U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN6           = 8U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN7           = 9U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN8           = 10U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN9           = 11U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN10          = 12U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN11          = 13U,
    TRGMUX_TRIG_SOURCE_CMP0_OUT             = 14U,
    TRGMUX_TRIG_SOURCE_LPIT_CH0             = 17U,
    TRGMUX_TRIG_SOURCE_LPIT_CH1             = 18U,
    TRGMUX_TRIG_SOURCE_LPIT_CH2             = 19U,
    TRGMUX_TRIG_SOURCE_LPIT_CH3             = 20U,
    TRGMUX_TRIG_SOURCE_LPTMR0               = 21U,
    TRGMUX_TRIG_SOURCE_FTM0_INIT_TRIG       = 22U,
    TRGMUX_TRIG_SOURCE_FTM0_EXT_TRIG        = 23U,
    TRGMUX_TRIG_SOURCE_FTM1_INIT_TRIG       = 24U,
    TRGMUX_TRIG_SOURCE_FTM1_EXT_TRIG        = 25U,
    TRGMUX_TRIG_SOURCE_FTM2_INIT_TRIG       = 26U,
    TRGMUX_TRIG_SOURCE_FTM2_EXT_TRIG        = 27U,
    TRGMUX_TRIG_SOURCE_FTM3_INIT_TRIG       = 28U,
    TRGMUX_TRIG_SOURCE_FTM3_EXT_TRIG        = 29U,
    TRGMUX_TRIG_SOURCE_ADC0_SC1A_COCO       = 30U,
    TRGMUX_TRIG_SOURCE_ADC0_SC1B_COCO       = 31U,
    TRGMUX_TRIG_SOURCE_ADC1_SC1A_COCO       = 32U,
    TRGMUX_TRIG_SOURCE_ADC1_SC1B_COCO       = 33U,
    TRGMUX_TRIG_SOURCE_PDB0_CH0_TRIG        = 34U,
    TRGMUX_TRIG_SOURCE_PDB0_PULSE_OUT       = 36U,
    TRGMUX_TRIG_SOURCE_PDB1_CH0_TRIG        = 37U,
    TRGMUX_TRIG_SOURCE_PDB1_PULSE_OUT       = 39U,
    TRGMUX_TRIG_SOURCE_RTC_ALARM            = 43U,
    TRGMUX_TRIG_SOURCE_RTC_SECOND           = 44U,
    TRGMUX_TRIG_SOURCE_FLEXIO_TRIG0         = 45U,
    TRGMUX_TRIG_SOURCE_FLEXIO_TRIG1         = 46U,
    TRGMUX_TRIG_SOURCE_FLEXIO_TRIG2         = 47U,
    TRGMUX_TRIG_SOURCE_FLEXIO_TRIG3         = 48U,
    TRGMUX_TRIG_SOURCE_LPUART0_RX_DATA      = 49U,
    TRGMUX_TRIG_SOURCE_LPUART0_TX_DATA      = 50U,
    TRGMUX_TRIG_SOURCE_LPUART0_RX_IDLE      = 51U,
    TRGMUX_TRIG_SOURCE_LPUART1_RX_DATA      = 52U,
    TRGMUX_TRIG_SOURCE_LPUART1_TX_DATA      = 53U,
    TRGMUX_TRIG_SOURCE_LPUART1_RX_IDLE      = 54U,
    TRGMUX_TRIG_SOURCE_LPI2C0_MASTER_TRIG   = 55U,
    TRGMUX_TRIG_SOURCE_LPI2C0_SLAVE_TRIG    = 56U,
    TRGMUX_TRIG_SOURCE_LPSPI0_FRAME         = 59U,
    TRGMUX_TRIG_SOURCE_LPSPI0_RX_DATA       = 60U,
    TRGMUX_TRIG_SOURCE_LPSPI1_FRAME         = 61U,
    TRGMUX_TRIG_SOURCE_LPSPI1_RX_DATA       = 62U,
    TRGMUX_TRIG_SOURCE_SIM_SW_TRIG          = 63U
};

enum trgmux_target_module_e
{
    TRGMUX_TARGET_MODULE_DMA_CH0            = 0U,
    TRGMUX_TARGET_MODULE_DMA_CH1            = 1U,
    TRGMUX_TARGET_MODULE_DMA_CH2            = 2U,
    TRGMUX_TARGET_MODULE_DMA_CH3            = 3U,
    TRGMUX_TARGET_MODULE_TRGMUX_OUT0        = 4U,
    TRGMUX_TARGET_MODULE_TRGMUX_OUT1        = 5U,
    TRGMUX_TARGET_MODULE_TRGMUX_OUT2        = 6U,
    TRGMUX_TARGET_MODULE_TRGMUX_OUT3        = 7U,
    TRGMUX_TARGET_MODULE_TRGMUX_OUT4        = 8U,
    TRGMUX_TARGET_MODULE_TRGMUX_OUT5        = 9U,
    TRGMUX_TARGET_MODULE_TRGMUX_OUT6        = 10U,
    TRGMUX_TARGET_MODULE_TRGMUX_OUT7        = 11U,
    TRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA0    = 12U,
    TRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA1    = 13U,
    TRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA2    = 14U,
    TRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA3    = 15U,
    TRGMUX_TARGET_MODULE_ADC1_ADHWT_TLA0    = 16U,
    TRGMUX_TARGET_MODULE_ADC1_ADHWT_TLA1    = 17U,
    TRGMUX_TARGET_MODULE_ADC1_ADHWT_TLA2    = 18U,
    TRGMUX_TARGET_MODULE_ADC1_ADHWT_TLA3    = 19U,
    TRGMUX_TARGET_MODULE_CMP0_SAMPLE        = 28U,
    TRGMUX_TARGET_MODULE_FTM0_HWTRIG0       = 40U,
    TRGMUX_TARGET_MODULE_FTM0_FAULT0        = 41U,
    TRGMUX_TARGET_MODULE_FTM0_FAULT1        = 42U,
    TRGMUX_TARGET_MODULE_FTM0_FAULT2        = 43U,
    TRGMUX_TARGET_MODULE_FTM1_HWTRIG0       = 44U,
    TRGMUX_TARGET_MODULE_FTM1_FAULT0        = 45U,
    TRGMUX_TARGET_MODULE_FTM1_FAULT1        = 46U,
    TRGMUX_TARGET_MODULE_FTM1_FAULT2        = 47U,
    TRGMUX_TARGET_MODULE_FTM2_HWTRIG0       = 48U,
    TRGMUX_TARGET_MODULE_FTM2_FAULT0        = 49U,
    TRGMUX_TARGET_MODULE_FTM2_FAULT1        = 50U,
    TRGMUX_TARGET_MODULE_FTM2_FAULT2        = 51U,
    TRGMUX_TARGET_MODULE_FTM3_HWTRIG0       = 52U,
    TRGMUX_TARGET_MODULE_FTM3_FAULT0        = 53U,
    TRGMUX_TARGET_MODULE_FTM3_FAULT1        = 54U,
    TRGMUX_TARGET_MODULE_FTM3_FAULT2        = 55U,
    TRGMUX_TARGET_MODULE_PDB0_TRG_IN        = 56U,
    TRGMUX_TARGET_MODULE_PDB1_TRG_IN        = 60U,
    TRGMUX_TARGET_MODULE_FLEXIO_TRG_TIM0    = 68U,
    TRGMUX_TARGET_MODULE_FLEXIO_TRG_TIM1    = 69U,
    TRGMUX_TARGET_MODULE_FLEXIO_TRG_TIM2    = 70U,
    TRGMUX_TARGET_MODULE_FLEXIO_TRG_TIM3    = 71U,
    TRGMUX_TARGET_MODULE_LPIT_TRG_CH0       = 72U,
    TRGMUX_TARGET_MODULE_LPIT_TRG_CH1       = 73U,
    TRGMUX_TARGET_MODULE_LPIT_TRG_CH2       = 74U,
    TRGMUX_TARGET_MODULE_LPIT_TRG_CH3       = 75U,
    TRGMUX_TARGET_MODULE_LPUART0_TRG        = 76U,
    TRGMUX_TARGET_MODULE_LPUART1_TRG        = 80U,
    TRGMUX_TARGET_MODULE_LPI2C0_TRG         = 84U,
    TRGMUX_TARGET_MODULE_LPSPI0_TRG         = 92U,
    TRGMUX_TARGET_MODULE_LPSPI1_TRG         = 96U,
    TRGMUX_TARGET_MODULE_LPTMR0_ALT0        = 100U
};

#define FEATURE_TRGMUX_TARGET_MODULE         \
{                                            \
    TRGMUX_TARGET_MODULE_DMA_CH0,            \
    TRGMUX_TARGET_MODULE_DMA_CH1,            \
    TRGMUX_TARGET_MODULE_DMA_CH2,            \
    TRGMUX_TARGET_MODULE_DMA_CH3,            \
    TRGMUX_TARGET_MODULE_TRGMUX_OUT0,        \
    TRGMUX_TARGET_MODULE_TRGMUX_OUT1,        \
    TRGMUX_TARGET_MODULE_TRGMUX_OUT2,        \
    TRGMUX_TARGET_MODULE_TRGMUX_OUT3,        \
    TRGMUX_TARGET_MODULE_TRGMUX_OUT4,        \
    TRGMUX_TARGET_MODULE_TRGMUX_OUT5,        \
    TRGMUX_TARGET_MODULE_TRGMUX_OUT6,        \
    TRGMUX_TARGET_MODULE_TRGMUX_OUT7,        \
    TRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA0,    \
    TRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA1,    \
    TRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA2,    \
    TRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA3,    \
    TRGMUX_TARGET_MODULE_ADC1_ADHWT_TLA0,    \
    TRGMUX_TARGET_MODULE_ADC1_ADHWT_TLA1,    \
    TRGMUX_TARGET_MODULE_ADC1_ADHWT_TLA2,    \
    TRGMUX_TARGET_MODULE_ADC1_ADHWT_TLA3,    \
    TRGMUX_TARGET_MODULE_CMP0_SAMPLE,        \
    TRGMUX_TARGET_MODULE_FTM0_HWTRIG0,       \
    TRGMUX_TARGET_MODULE_FTM0_FAULT0,        \
    TRGMUX_TARGET_MODULE_FTM0_FAULT1,        \
    TRGMUX_TARGET_MODULE_FTM0_FAULT2,        \
    TRGMUX_TARGET_MODULE_FTM1_HWTRIG0,       \
    TRGMUX_TARGET_MODULE_FTM1_FAULT0,        \
    TRGMUX_TARGET_MODULE_FTM1_FAULT1,        \
    TRGMUX_TARGET_MODULE_FTM1_FAULT2,        \
    TRGMUX_TARGET_MODULE_FTM2_HWTRIG0,       \
    TRGMUX_TARGET_MODULE_FTM2_FAULT0,        \
    TRGMUX_TARGET_MODULE_FTM2_FAULT1,        \
    TRGMUX_TARGET_MODULE_FTM2_FAULT2,        \
    TRGMUX_TARGET_MODULE_FTM3_HWTRIG0,       \
    TRGMUX_TARGET_MODULE_FTM3_FAULT0,        \
    TRGMUX_TARGET_MODULE_FTM3_FAULT1,        \
    TRGMUX_TARGET_MODULE_FTM3_FAULT2,        \
    TRGMUX_TARGET_MODULE_PDB0_TRG_IN,        \
    TRGMUX_TARGET_MODULE_PDB1_TRG_IN,        \
    TRGMUX_TARGET_MODULE_FLEXIO_TRG_TIM0,    \
    TRGMUX_TARGET_MODULE_FLEXIO_TRG_TIM1,    \
    TRGMUX_TARGET_MODULE_FLEXIO_TRG_TIM2,    \
    TRGMUX_TARGET_MODULE_FLEXIO_TRG_TIM3,    \
    TRGMUX_TARGET_MODULE_LPIT_TRG_CH0,       \
    TRGMUX_TARGET_MODULE_LPIT_TRG_CH1,       \
    TRGMUX_TARGET_MODULE_LPIT_TRG_CH2,       \
    TRGMUX_TARGET_MODULE_LPIT_TRG_CH3,       \
    TRGMUX_TARGET_MODULE_LPUART0_TRG,        \
    TRGMUX_TARGET_MODULE_LPUART1_TRG,        \
    TRGMUX_TARGET_MODULE_LPI2C0_TRG,         \
    TRGMUX_TARGET_MODULE_LPSPI0_TRG,         \
    TRGMUX_TARGET_MODULE_LPSPI1_TRG,         \
    TRGMUX_TARGET_MODULE_LPTMR0_ALT0         \
}


#define ISELED_PIN_0     0    
#define ISELED_PIN_1     1    
#define ISELED_PIN_2     2    
#define ISELED_PIN_3     3    
#define ISELED_PIN_4     4    
#define ISELED_PIN_5     5    
#define ISELED_PIN_6     6    
#define ISELED_PIN_7     7    
#define ISELED_PIN_8     8    
#define ISELED_PIN_9     9    
#define ISELED_PIN_10    10    
#define ISELED_PIN_11    11    
#define ISELED_PIN_12    12    
#define ISELED_PIN_13    13    
#define ISELED_PIN_14    14    
#define ISELED_PIN_15    15    
#define ISELED_PIN_16    16    
#define ISELED_PIN_17    17    
#define ISELED_PIN_18    18    
#define ISELED_PIN_19    19    

#define ISELED_PIN_20    20    
#define ISELED_PIN_21    21    
#define ISELED_PIN_22    22    
#define ISELED_PIN_23    23    
#define ISELED_PIN_24    24    
#define ISELED_PIN_25    25    
#define ISELED_PIN_26    26    
#define ISELED_PIN_27    27    
#define ISELED_PIN_28    28    
#define ISELED_PIN_29    29    
#define ISELED_PIN_30    30    
#define ISELED_PIN_31    31    
#define ISELED_PIN_32    32    
#define ISELED_PIN_33    33    

#define ISELED_PIN_34    34    
#define ISELED_PIN_35    35    
#define ISELED_PIN_36    36    
#define ISELED_PIN_37    37    
#define ISELED_PIN_38    38    
#define ISELED_PIN_39    39    


#define MAX_NR_OF_STRIPS 13U


#define FEATURE_PDB_HAS_INSTANCE_BACKTOBACK  (1)

#endif 


