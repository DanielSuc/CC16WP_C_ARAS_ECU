
#ifndef CSEC_DRV_H
#define CSEC_DRV_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "device_registers.h"
#include "interrupt_manager.h"
#include "status.h"
#include "callbacks.h"





#define CSEC_STATUS_BUSY              (0x1U)
#define CSEC_STATUS_SECURE_BOOT       (0x2U)
#define CSEC_STATUS_BOOT_INIT         (0x4U)
#define CSEC_STATUS_BOOT_FINISHED     (0x8U)
#define CSEC_STATUS_BOOT_OK           (0x10U)
#define CSEC_STATUS_RND_INIT          (0x20U)
#define CSEC_STATUS_EXT_DEBUGGER      (0x40U)
#define CSEC_STATUS_INT_DEBUGGER      (0x80U)

typedef uint8_t csec_status_t;

typedef enum {
    CSEC_SECRET_KEY = 0x0U,
    CSEC_MASTER_ECU,
    CSEC_BOOT_MAC_KEY,
    CSEC_BOOT_MAC,
    CSEC_KEY_1,
    CSEC_KEY_2,
    CSEC_KEY_3,
    CSEC_KEY_4,
    CSEC_KEY_5,
    CSEC_KEY_6,
    CSEC_KEY_7,
    CSEC_KEY_8,
    CSEC_KEY_9,
    CSEC_KEY_10,
    CSEC_RAM_KEY = 0xFU,
    CSEC_KEY_11 = 0x14U,
    CSEC_KEY_12,
    CSEC_KEY_13,
    CSEC_KEY_14,
    CSEC_KEY_15,
    CSEC_KEY_16,
    CSEC_KEY_17
} csec_key_id_t;

typedef enum {
    CSEC_CMD_ENC_ECB = 0x1U,
    CSEC_CMD_ENC_CBC,
    CSEC_CMD_DEC_ECB,
    CSEC_CMD_DEC_CBC,
    CSEC_CMD_GENERATE_MAC,
    CSEC_CMD_VERIFY_MAC,
    CSEC_CMD_LOAD_KEY,
    CSEC_CMD_LOAD_PLAIN_KEY,
    CSEC_CMD_EXPORT_RAM_KEY,
    CSEC_CMD_INIT_RNG,
    CSEC_CMD_EXTEND_SEED,
    CSEC_CMD_RND,
    CSEC_CMD_RESERVED_1,
    CSEC_CMD_BOOT_FAILURE,
    CSEC_CMD_BOOT_OK,
    CSEC_CMD_GET_ID,
    CSEC_CMD_BOOT_DEFINE,
    CSEC_CMD_DBG_CHAL,
    CSEC_CMD_DBG_AUTH,
    CSEC_CMD_RESERVED_2,
    CSEC_CMD_RESERVED_3,
    CSEC_CMD_MP_COMPRESS
} csec_cmd_t;

typedef enum {
    CSEC_CALL_SEQ_FIRST,
    CSEC_CALL_SEQ_SUBSEQUENT
} csec_call_sequence_t;

typedef enum {
    CSEC_BOOT_STRICT,
    CSEC_BOOT_SERIAL,
    CSEC_BOOT_PARALLEL,
    CSEC_BOOT_NOT_DEFINED
} csec_boot_flavor_t;

typedef struct {
    bool cmdInProgress;           
    csec_cmd_t cmd;               
    const uint8_t *inputBuff;     
    uint8_t *outputBuff;          
    uint32_t index;               
    uint32_t fullSize;            
    uint32_t partSize;            
    csec_key_id_t keyId;          
    status_t errCode;    
    const uint8_t *iv;            
    csec_call_sequence_t seq;     
    uint32_t msgLen;              
    bool *verifStatus;            
    bool macWritten;              
    const uint8_t *mac;           
    uint32_t macLen;              
    security_callback_t callback; 
    void *callbackParam;          
} csec_state_t;



#if defined(__cplusplus)
extern "C" {
#endif

void CSEC_DRV_Init(csec_state_t *state);

void CSEC_DRV_Deinit(void);

status_t CSEC_DRV_EncryptECB(csec_key_id_t keyId,
    const uint8_t *plainText, uint32_t length, uint8_t *cipherText,
    uint32_t timeout);

status_t CSEC_DRV_DecryptECB(csec_key_id_t keyId, const uint8_t *cipherText,
    uint32_t length, uint8_t *plainText, uint32_t timeout);

status_t CSEC_DRV_EncryptCBC(csec_key_id_t keyId,
    const uint8_t *plainText, uint32_t length,
    const uint8_t *iv, uint8_t *cipherText, uint32_t timeout);

status_t CSEC_DRV_DecryptCBC(csec_key_id_t keyId, const uint8_t *cipherText,
    uint32_t length, const uint8_t* iv, uint8_t *plainText, uint32_t timeout);

status_t CSEC_DRV_GenerateMAC(csec_key_id_t keyId, const uint8_t *msg,
    uint32_t msgLen, uint8_t *cmac, uint32_t timeout);

status_t CSEC_DRV_GenerateMACAddrMode(csec_key_id_t keyId,
    const uint8_t *msg, uint32_t msgLen, uint8_t *cmac);

status_t CSEC_DRV_VerifyMAC(csec_key_id_t keyId, const uint8_t *msg,
    uint32_t msgLen, const uint8_t *mac, uint16_t macLen, bool *verifStatus,
    uint32_t timeout);

status_t CSEC_DRV_VerifyMACAddrMode(csec_key_id_t keyId, const uint8_t *msg,
    uint32_t msgLen, const uint8_t *mac, uint16_t macLen, bool *verifStatus);

status_t CSEC_DRV_LoadKey(csec_key_id_t keyId, const uint8_t *m1,
    const uint8_t *m2, const uint8_t *m3, uint8_t *m4, uint8_t *m5);

status_t CSEC_DRV_LoadPlainKey(const uint8_t *plainKey);

status_t CSEC_DRV_ExportRAMKey(uint8_t *m1, uint8_t *m2,
    uint8_t *m3, uint8_t *m4, uint8_t *m5);

status_t CSEC_DRV_InitRNG(void);

status_t CSEC_DRV_ExtendSeed(const uint8_t *entropy);

status_t CSEC_DRV_GenerateRND(uint8_t *rnd);

status_t CSEC_DRV_BootFailure(void);

status_t CSEC_DRV_BootOK(void);

status_t CSEC_DRV_BootDefine(uint32_t bootSize, csec_boot_flavor_t bootFlavor);

static inline csec_status_t CSEC_DRV_GetStatus(void)
{
	return (FTFC->FCSESTAT);
}

status_t CSEC_DRV_GetID(const uint8_t *challenge, uint8_t *uid,
    uint8_t *sreg, uint8_t *mac);

status_t CSEC_DRV_DbgChal(uint8_t *challenge);

status_t CSEC_DRV_DbgAuth(const uint8_t *authorization);

status_t CSEC_DRV_MPCompress(const uint8_t *msg, uint16_t msgLen,
    uint8_t *mpCompress, uint32_t timeout);

status_t CSEC_DRV_EncryptECBAsync(csec_key_id_t keyId,
                                           const uint8_t *plainText,
                                           uint32_t length,
                                           uint8_t *cipherText);

status_t CSEC_DRV_DecryptECBAsync(csec_key_id_t keyId,
                                           const uint8_t *cipherText,
                                           uint32_t length,
                                           uint8_t *plainText);
status_t CSEC_DRV_EncryptCBCAsync(csec_key_id_t keyId,
                                           const uint8_t *plainText,
                                           uint32_t length,
                                           const uint8_t* iv,
                                           uint8_t *cipherText);

status_t CSEC_DRV_DecryptCBCAsync(csec_key_id_t keyId,
                                           const uint8_t *cipherText,
                                           uint32_t length,
                                           const uint8_t* iv,
                                           uint8_t *plainText);

status_t CSEC_DRV_GenerateMACAsync(csec_key_id_t keyId,
                                            const uint8_t *msg,
                                            uint32_t msgLen,
                                            uint8_t *cmac);

status_t CSEC_DRV_VerifyMACAsync(csec_key_id_t keyId,
                                          const uint8_t *msg,
                                          uint32_t msgLen,
                                          const uint8_t *mac,
                                          uint16_t macLen,
                                          bool *verifStatus);

status_t CSEC_DRV_GetAsyncCmdStatus(void);

void CSEC_DRV_InstallCallback(security_callback_t callbackFunc, void *callbackParam);

void CSEC_DRV_CancelCommand(void);

#if defined(__cplusplus)
}
#endif


#endif 

