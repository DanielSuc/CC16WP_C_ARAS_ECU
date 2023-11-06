
#ifndef CSEC_HW_ACCESS_H
#define CSEC_HW_ACCESS_H

#include <stdint.h>
#include <stdbool.h>
#include "device_registers.h"




#include <stddef.h>
#include "status.h"
#include "csec_driver.h"

typedef enum {
    CSEC_FUNC_FORMAT_COPY,
    CSEC_FUNC_FORMAT_ADDR
} csec_func_format_t;

#define CSEC_NO_ERROR            0x1U
#define CSEC_SEQUENCE_ERROR      0x2U
#define CSEC_KEY_NOT_AVAILABLE   0x4U
#define CSEC_KEY_INVALID         0x8U
#define CSEC_KEY_EMPTY           0x10U
#define CSEC_NO_SECURE_BOOT      0x20U
#define CSEC_KEY_WRITE_PROTECTED 0x40U
#define CSEC_KEY_UPDATE_ERROR    0x80U
#define CSEC_RNG_SEED            0x100U
#define CSEC_NO_DEBUGGING        0x200U
#define CSEC_MEMORY_FAILURE      0x400U
#define CSEC_GENERAL_ERROR       0x800U

#define CSEC_UPPER_HALF_MASK    (0xFFFF0000U)
#define CSEC_UPPER_HALF_SHIFT   (0x10U)
#define CSEC_LOWER_HALF_MASK    (0xFFFFU)
#define CSEC_LOWER_HALF_SHIFT   (0U)


#if defined(__cplusplus)
extern "C" {
#endif

static inline void CSEC_WriteCommandHeader(csec_cmd_t funcId,
                                       csec_func_format_t funcFormat,
                                       csec_call_sequence_t callSeq,
                                       csec_key_id_t keyId)
{
    CSE_PRAM->RAMn[0].DATA_32 =
        CSE_PRAM_RAMn_DATA_32_BYTE_0(funcId) |
        CSE_PRAM_RAMn_DATA_32_BYTE_1(funcFormat) |
        CSE_PRAM_RAMn_DATA_32_BYTE_2(callSeq) |
        CSE_PRAM_RAMn_DATA_32_BYTE_3(keyId);
}

void CSEC_WriteCommandBytes(uint8_t offset, const uint8_t *bytes, uint8_t numBytes);

void CSEC_WriteCommandHalfWord(uint8_t offset, uint16_t halfWord);

void CSEC_WriteCommandByte(uint8_t offset, uint8_t byte);

void CSEC_WriteCommandWords(uint8_t offset, const uint32_t *words, uint8_t numWords);

void CSEC_ReadCommandBytes(uint8_t offset, uint8_t *bytes, uint8_t numBytes);

uint8_t CSEC_ReadCommandByte(uint8_t offset);

static inline uint32_t CSEC_ReadCommandWord(uint8_t offset)
{
    return CSE_PRAM->RAMn[offset >> 2U].DATA_32;
}

static inline void CSEC_WaitCommandCompletion(void)
{
    while ((FTFC->FSTAT & FTFC_FSTAT_CCIF_MASK) == 0U)
    {
    }
}

static inline status_t CSEC_ReadErrorBits(void)
{
	uint32_t errWord;
    uint16_t errBits;
    status_t stat;

    errWord = CSEC_ReadCommandWord(FEATURE_CSEC_ERROR_BITS_OFFSET);
    errBits = (uint16_t)((errWord & CSEC_UPPER_HALF_MASK) >> CSEC_UPPER_HALF_SHIFT);

    switch (errBits)
    {
    case CSEC_NO_ERROR:
        stat = STATUS_SUCCESS;
        break;
    case CSEC_SEQUENCE_ERROR:
        stat = STATUS_SEC_SEQUENCE_ERROR;
        break;
    case CSEC_KEY_NOT_AVAILABLE:
        stat = STATUS_SEC_KEY_NOT_AVAILABLE;
        break;
    case CSEC_KEY_INVALID:
        stat = STATUS_SEC_KEY_INVALID;
        break;
    case CSEC_KEY_EMPTY:
        stat = STATUS_SEC_KEY_EMPTY;
        break;
    case CSEC_NO_SECURE_BOOT:
        stat = STATUS_SEC_NO_SECURE_BOOT;
        break;
    case CSEC_KEY_WRITE_PROTECTED:
        stat = STATUS_SEC_KEY_WRITE_PROTECTED;
        break;
    case CSEC_KEY_UPDATE_ERROR:
        stat = STATUS_SEC_KEY_UPDATE_ERROR;
        break;
    case CSEC_RNG_SEED:
        stat = STATUS_SEC_RNG_SEED;
        break;
    case CSEC_NO_DEBUGGING:
        stat = STATUS_SEC_NO_DEBUGGING;
        break;
    case CSEC_MEMORY_FAILURE:
        stat = STATUS_SEC_MEMORY_FAILURE;
        break;
    case CSEC_GENERAL_ERROR:
    default:
        stat = STATUS_ERROR;
        break;
    }

    return stat;
}

START_FUNCTION_DECLARATION_RAMSECTION
void CSEC_WriteCmdAndWait(csec_cmd_t funcId,
        csec_func_format_t funcFormat,
        csec_call_sequence_t callSeq,
        csec_key_id_t keyId)
END_FUNCTION_DECLARATION_RAMSECTION

static inline void CSEC_SetInterrupt(bool enable)
{
    uint8_t tmp = FTFC->FCNFG;

    FTFC->FCNFG = (uint8_t)((tmp & ~FTFC_FCNFG_CCIE_MASK) | FTFC_FCNFG_CCIE(enable ? 1U : 0U));
}

#if defined(__cplusplus)
}
#endif

#endif 


