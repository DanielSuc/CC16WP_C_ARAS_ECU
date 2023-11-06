

#ifndef MPU_HW_ACCESS_H
#define MPU_HW_ACCESS_H

#include "mpu_driver.h"


#if defined(__cplusplus)
extern "C" {
#endif

static inline void MPU_Enable(MPU_Type * const base,
                              bool enable)
{
    base->CESR = (base->CESR & ~MPU_CESR_VLD_MASK) | MPU_CESR_VLD(enable ? 1UL : 0UL);
}

static inline void MPU_SetRegionValidCmd(MPU_Type * const base,
                                         uint8_t regionNum,
                                         bool enable)
{
    base->RGD[regionNum].WORD3 = ((base->RGD[regionNum].WORD3 & ~MPU_RGD_WORD3_VLD_MASK)
                               | MPU_RGD_WORD3_VLD(enable ? 1UL : 0UL));
}

#if FEATURE_MPU_HAS_PROCESS_IDENTIFIER
static inline void MPU_SetProcessIdentifier(MPU_Type * const base,
                                            uint8_t regionNum,
                                            uint8_t pid)
{
    base->RGD[regionNum].WORD3 = (base->RGD[regionNum].WORD3 & ~MPU_RGD_WORD3_PID_MASK)
                               | MPU_RGD_WORD3_PID(pid);
}

static inline void MPU_SetProcessIdentifierMask(MPU_Type * const base,
                                                uint8_t regionNum,
                                                uint8_t pidMask)
{
    base->RGD[regionNum].WORD3 = (base->RGD[regionNum].WORD3 & ~MPU_RGD_WORD3_PIDMASK_MASK)
                               | MPU_RGD_WORD3_PIDMASK(pidMask);
}
#endif

void MPU_SetRegionAddr(MPU_Type * const base,
                       uint8_t regionNum,
                       uint32_t startAddr,
                       uint32_t endAddr);

void MPU_SetMasterAccessRight(MPU_Type * const base,
                              uint8_t regionNum,
                              const mpu_master_access_right_t * masterAccRight);

void MPU_InitRegion(MPU_Type * const base,
                    uint8_t regionNum);

static inline bool MPU_GetErrorStatus(const MPU_Type * const base,
                                      uint8_t slaveNum)
{

    return ((base->CESR & FEATURE_MPU_SLAVE(1UL << ((FEATURE_MPU_SLAVE_WIDTH - 1U) - slaveNum))) != 0U);
}

static inline void MPU_ClearErrorFlag(MPU_Type * const base,
                                      uint8_t slaveNum)
{
    base->CESR = (base->CESR & ~FEATURE_MPU_SLAVE_MASK)
               | FEATURE_MPU_SLAVE(1UL << ((FEATURE_MPU_SLAVE_WIDTH - 1U) - slaveNum));
}

void MPU_GetErrorInfo(const MPU_Type * const base,
                      uint8_t slaveNum,
                      mpu_access_err_info_t * errInfoPtr);

void MPU_GetDefaultMasterAccRight(uint8_t masterNum,
                                  mpu_master_access_right_t * masterAccRight);


#if defined(__cplusplus)
}
#endif


#endif 

