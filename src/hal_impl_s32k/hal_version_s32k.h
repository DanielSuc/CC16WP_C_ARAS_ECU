#ifndef HAL_VERSION_S32K_H_
#define HAL_VERSION_S32K_H_
#include "hal_version.h"

#define HAL_VERSION_S32K_MAJOR        1       
#define HAL_VERSION_S32K_MINOR        4       
#define HAL_VERSION_S32K_REVISION     0       

#if (HAL_VERSION_S32K_MAJOR != HAL_VERSION_MAJOR) || (HAL_VERSION_S32K_MINOR != HAL_VERSION_MINOR) || (HAL_VERSION_S32K_REVISION < HAL_VERSION_REVISION)
#error "HAL definition version does not match HAL implementation version. Please update to compatible versions."
#endif

#endif

