
#ifndef CRC_HW_ACCESS_H
#define CRC_HW_ACCESS_H


#include "crc_driver.h"




#if defined(__cplusplus)
extern "C" {
#endif

void CRC_Init(CRC_Type * const base);

uint32_t CRC_GetCrcResult(const CRC_Type * const base);

void CRC_SetSeedReg(CRC_Type * const base,
		            uint32_t seedValue);

static inline uint32_t CRC_GetDataReg(const CRC_Type * const base)
{
    return base->DATAu.DATA;
}

static inline void CRC_SetDataReg(CRC_Type * const base,
                                  uint32_t value)
{
    base->DATAu.DATA = value;
}

static inline uint16_t CRC_GetDataHReg(const CRC_Type * const base)
{
    return base->DATAu.DATA_16.H;
}

static inline uint16_t CRC_GetDataLReg(const CRC_Type * const base)
{
    return base->DATAu.DATA_16.L;
}

static inline void CRC_SetDataLReg(CRC_Type * const base,
                                   uint16_t value)
{
    base->DATAu.DATA_16.L = value;
}

static inline void CRC_SetDataLLReg(CRC_Type * const base,
                                    uint8_t value)
{
    base->DATAu.DATA_8.LL = value;
}

static inline uint32_t CRC_GetPolyReg(const CRC_Type * const base)
{
    return base->GPOLY;
}

static inline void CRC_SetPolyReg(CRC_Type * const base,
                                  uint32_t value)
{
    base->GPOLY = value;
}

static inline void CRC_SetSeedOrDataMode(CRC_Type * const base,
                                         bool enable)
{
    uint32_t ctrlTemp = base->CTRL;

    ctrlTemp &= ~(CRC_CTRL_WAS_MASK);
    ctrlTemp |= CRC_CTRL_WAS(enable ? 1UL : 0UL);
    base->CTRL = ctrlTemp;
}

static inline bool CRC_GetFXorMode(const CRC_Type * const base)
{
    return ((base->CTRL & CRC_CTRL_FXOR_MASK) >> CRC_CTRL_FXOR_SHIFT) != 0U;
}

static inline void CRC_SetFXorMode(CRC_Type * const base,
                                   bool enable)
{
    uint32_t ctrlTemp = base->CTRL;

    ctrlTemp &= ~(CRC_CTRL_FXOR_MASK);
    ctrlTemp |= CRC_CTRL_FXOR(enable ? 1UL : 0UL);
    base->CTRL = ctrlTemp;
}

static inline crc_bit_width_t CRC_GetProtocolWidth(const CRC_Type * const base)
{
    crc_bit_width_t retVal = CRC_BITS_16;

    if (((base->CTRL & CRC_CTRL_TCRC_MASK) >> CRC_CTRL_TCRC_SHIFT) != 0U)
    {
        retVal = CRC_BITS_32;
    }

    return retVal;
}

static inline void CRC_SetProtocolWidth(CRC_Type * const base,
                                        crc_bit_width_t width)
{
    uint32_t ctrlTemp = base->CTRL;

    ctrlTemp &= ~(CRC_CTRL_TCRC_MASK);
    ctrlTemp |= CRC_CTRL_TCRC(width);
    base->CTRL = ctrlTemp;
}

static inline crc_transpose_t CRC_GetWriteTranspose(const CRC_Type * const base)
{
    crc_transpose_t type;
    uint32_t temp = (base->CTRL & CRC_CTRL_TOT_MASK) >> CRC_CTRL_TOT_SHIFT;

    switch (temp)
    {
        case 1U:
            type = CRC_TRANSPOSE_BITS;
            break;
        case 2U:
            type = CRC_TRANSPOSE_BITS_AND_BYTES;
            break;
        case 3U:
            type = CRC_TRANSPOSE_BYTES;
            break;
        default:
            type = CRC_TRANSPOSE_NONE;
            break;
    }

    return type;
}

static inline void CRC_SetWriteTranspose(CRC_Type * const base,
                                         crc_transpose_t transp)
{
    uint32_t ctrlTemp = base->CTRL;

    ctrlTemp &= ~(CRC_CTRL_TOT_MASK);
    ctrlTemp |= CRC_CTRL_TOT(transp);
    base->CTRL = ctrlTemp;
}

static inline crc_transpose_t CRC_GetReadTranspose(const CRC_Type * const base)
{
    crc_transpose_t type;
    uint32_t temp = (base->CTRL & CRC_CTRL_TOTR_MASK) >> CRC_CTRL_TOTR_SHIFT;

    switch (temp)
    {
        case 1U:
            type = CRC_TRANSPOSE_BITS;
            break;
        case 2U:
            type = CRC_TRANSPOSE_BITS_AND_BYTES;
            break;
        case 3U:
            type = CRC_TRANSPOSE_BYTES;
            break;
        default:
            type = CRC_TRANSPOSE_NONE;
            break;
    }

    return type;
}

static inline void CRC_SetReadTranspose(CRC_Type * const base,
                                        crc_transpose_t transp)
{
    uint32_t ctrlTemp = base->CTRL;

    ctrlTemp &= ~(CRC_CTRL_TOTR_MASK);
    ctrlTemp |= CRC_CTRL_TOTR(transp);
    base->CTRL = ctrlTemp;
}


#if defined(__cplusplus)
}
#endif


#endif 

