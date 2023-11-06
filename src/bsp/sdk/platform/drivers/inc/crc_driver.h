
#ifndef CRC_DRIVER_H
#define CRC_DRIVER_H


#include <stddef.h>
#include "device_registers.h"
#include "status.h"



typedef enum
{
    CRC_TRANSPOSE_NONE              = 0x00U,    
    CRC_TRANSPOSE_BITS              = 0x01U,    
    CRC_TRANSPOSE_BITS_AND_BYTES    = 0x02U,    
    CRC_TRANSPOSE_BYTES             = 0x03U     
} crc_transpose_t;

#if defined(FEATURE_CRC_DRIVER_SOFT_POLYNOMIAL)
typedef enum
{
    CRC_BITS_16 = 0U,   
    CRC_BITS_32 = 1U    
} crc_bit_width_t;

#elif defined(FEATURE_CRC_DRIVER_HARD_POLYNOMIAL)
typedef enum
{
    CRC_BITS_16_CCITT   = 0U,   
    CRC_BITS_32         = 1U,   
    CRC_BITS_8          = 2U,   
#if defined(FEATURE_CRC_BITS_8_H2F)
    CRC_BITS_8_H2F      = 3U    
#endif
} crc_mode_polynomial_t;
#endif 

typedef struct
{
#if defined(FEATURE_CRC_DRIVER_SOFT_POLYNOMIAL)
    crc_bit_width_t crcWidth;               
    uint32_t polynomial;                    
    crc_transpose_t readTranspose;          
#elif defined(FEATURE_CRC_DRIVER_HARD_POLYNOMIAL)
    crc_mode_polynomial_t polynomial;       
    bool readTranspose;                     
#endif 
    crc_transpose_t writeTranspose;         
    bool complementChecksum;                
    uint32_t seed;                          
} crc_user_config_t;


#if defined(__cplusplus)
extern "C" {
#endif

status_t CRC_DRV_Init(uint32_t instance,
                      const crc_user_config_t * userConfigPtr);

status_t CRC_DRV_Deinit(uint32_t instance);

uint32_t CRC_DRV_GetCrc32(uint32_t instance,
                          uint32_t data,
                          bool newSeed,
                          uint32_t seed);

uint32_t CRC_DRV_GetCrc16(uint32_t instance,
                          uint16_t data,
                          bool newSeed,
                          uint32_t seed);

uint32_t CRC_DRV_GetCrc8(uint32_t instance,
                         uint8_t data,
                         bool newSeed,
                         uint32_t seed);

void CRC_DRV_WriteData(uint32_t instance,
                       const uint8_t * data,
                       uint32_t dataSize);

uint32_t CRC_DRV_GetCrcResult(uint32_t instance);

status_t CRC_DRV_Configure(uint32_t instance,
                           const crc_user_config_t * userConfigPtr);

status_t CRC_DRV_GetConfig(uint32_t instance,
                           crc_user_config_t * const userConfigPtr);

status_t CRC_DRV_GetDefaultConfig(crc_user_config_t * const userConfigPtr);


#if defined(__cplusplus)
}
#endif


#endif 

