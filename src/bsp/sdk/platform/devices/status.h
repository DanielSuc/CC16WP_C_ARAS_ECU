
#ifndef STATUS_H
#define STATUS_H



typedef enum
{
    STATUS_SUCCESS                         = 0x000U,    
    STATUS_ERROR                           = 0x001U,    
    STATUS_BUSY                            = 0x002U,    
    STATUS_TIMEOUT                         = 0x003U,    
    STATUS_UNSUPPORTED                     = 0x004U,    
    STATUS_MCU_GATED_OFF                   = 0x100U,  
    STATUS_MCU_TRANSITION_FAILED           = 0x101U,  
    STATUS_MCU_INVALID_STATE               = 0x102U,  
    STATUS_MCU_NOTIFY_BEFORE_ERROR         = 0x103U,  
    STATUS_MCU_NOTIFY_AFTER_ERROR          = 0x104U,  
    STATUS_I2C_RECEIVED_NACK               = 0x200U,  
    STATUS_I2C_TX_UNDERRUN                 = 0x201U,  
    STATUS_I2C_RX_OVERRUN                  = 0x202U,  
    STATUS_I2C_ARBITRATION_LOST            = 0x203U,  
    STATUS_I2C_ABORTED                     = 0x204U,  
    STATUS_I2C_BUS_BUSY                    = 0x205U,  
    STATUS_CAN_BUFF_OUT_OF_RANGE           = 0x300U,  
    STATUS_CAN_NO_TRANSFER_IN_PROGRESS     = 0x301U,  
    STATUS_SEC_SEQUENCE_ERROR              = 0x402U,  
    STATUS_SEC_KEY_NOT_AVAILABLE           = 0x403U,  
    STATUS_SEC_KEY_INVALID                 = 0x404U,  
    STATUS_SEC_KEY_EMPTY                   = 0x405U,  
    STATUS_SEC_NO_SECURE_BOOT              = 0x406U,  
    STATUS_SEC_KEY_WRITE_PROTECTED         = 0x407U,  
    STATUS_SEC_KEY_UPDATE_ERROR            = 0x408U,  
    STATUS_SEC_RNG_SEED                    = 0x409U,  
    STATUS_SEC_NO_DEBUGGING                = 0x40AU,  
    STATUS_SEC_MEMORY_FAILURE              = 0x40CU,  
    STATUS_SEC_HSM_INTERNAL_MEMORY_ERROR   = 0x410U,  
    STATUS_SEC_INVALID_COMMAND             = 0x411U,  
    STATUS_SEC_TRNG_ERROR                  = 0x412U,  
    STATUS_SEC_HSM_FLASH_BLOCK_ERROR       = 0x413U,  
    STATUS_SEC_INTERNAL_CMD_ERROR          = 0x414U,  
    STATUS_SEC_MAC_LENGTH_ERROR            = 0x415U,  
    STATUS_SEC_INVALID_ARG                 = 0x421U,  
    STATUS_SEC_TRNG_CLOCK_ERROR            = 0x423U,  
    STATUS_SPI_TX_UNDERRUN                 = 0x500U,  
    STATUS_SPI_RX_OVERRUN                  = 0x501U,  
    STATUS_SPI_ABORTED                     = 0x502U,  
    STATUS_UART_TX_UNDERRUN                = 0x600U,  
    STATUS_UART_RX_OVERRUN                 = 0x601U,  
    STATUS_UART_ABORTED                    = 0x602U,  
	STATUS_UART_FRAMING_ERROR              = 0x603U,  
	STATUS_UART_PARITY_ERROR               = 0x604U,  
	STATUS_UART_NOISE_ERROR                = 0x605U,  
    STATUS_I2S_TX_UNDERRUN                 = 0x700U,  
    STATUS_I2S_RX_OVERRUN                  = 0x701U,  
    STATUS_I2S_ABORTED                     = 0x702U,  
    SBC_NVN_ERROR                          = 0x801U, 
    SBC_COMM_ERROR                         = 0x802U, 
    SBC_CMD_ERROR                          = 0x804U, 
    SBC_ERR_NA                             = 0x808U, 
    SBC_MTPNV_LOCKED                       = 0x810U, 

    STATUS_FLASH_ERROR_ENABLE              = 0x901U, 
    STATUS_FLASH_ERROR_NO_BLOCK            = 0x902U, 
    STATUS_FLASH_INPROGRESS                = 0x903U, 

    STATUS_SAI_ABORTED                     = 0xA00U, 

    STATUS_ENET_RX_QUEUE_EMPTY             = 0xA01U, 
    STATUS_ENET_TX_QUEUE_FULL              = 0xA02U, 
    STATUS_ENET_BUFF_NOT_FOUND             = 0xA03U, 

    STATUS_FCCU_ERROR_CONFIG_TIMEOUT       = 0xB01U, 
    STATUS_FCCU_ERROR_INIT_FCCU            = 0xB02U, 
    STATUS_FCCU_ERROR_SET_CONFIG           = 0xB03U, 
    STATUS_FCCU_ERROR_SET_NORMAL           = 0xB04U, 
    STATUS_FCCU_ERROR_APPLY_NCF_CONFIG     = 0xB05U, 
    STATUS_FCCU_ERROR_UPDATE_FREEZE        = 0xB06U, 
    STATUS_FCCU_ERROR_CLEAR_FREEZE         = 0xB07U, 
    STATUS_FCCU_ERROR_SET_EOUT             = 0xB08U, 
    STATUS_FCCU_ERROR_FAULT_DETECTED       = 0xB09U, 
    STATUS_FCCU_ERROR_OTHER                = 0xB0AU, 

    STATUS_EMIOS_WRONG_MODE                = 0xC00U,   
    STATUS_EMIOS_CNT_BUS_OVERFLOW          = 0xC01U,   
    STATUS_EMIOS_WRONG_CNT_BUS             = 0xC02U,   
    STATUS_EMIOS_ENABLE_GLOBAL_FRZ         = 0xC03U,   

    STATUS_EEE_ERROR_NO_ENOUGH_SPACE       = 0xD00U, 
    STATUS_EEE_ERROR_NO_ENOUGH_BLOCK       = 0xD01U, 
    STATUS_EEE_ERROR_DATA_NOT_FOUND        = 0xD02U, 
    STATUS_EEE_ERROR_NOT_IN_CACHE          = 0xD03U, 
    STATUS_EEE_ERROR_PROGRAM_INDICATOR     = 0xD04U, 
    STATUS_EEE_HVOP_INPROGRESS             = 0xD05U, 

    STATUS_USDHC_OUT_OF_RANGE              = 0xE00U,    
    STATUS_USDHC_PREPARE_ADMA_FAILED       = 0xE01U,    

    STATUS_TDM_DIARY_FULL                  = 0xF01U, 

    STATUS_PHY_ACCESS_FAILED               = 0x1001U, 
    STATUS_PHY_INCOMPATIBLE_DEVICE         = 0x1002U  
} status_t;

#endif 


