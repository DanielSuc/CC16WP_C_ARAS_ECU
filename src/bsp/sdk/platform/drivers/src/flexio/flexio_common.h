
#ifndef FLEXIO_COMMON_DRIVER_H
#define FLEXIO_COMMON_DRIVER_H

#include <stddef.h>
#include <stdbool.h>
#include "device_registers.h"
#include "flexio_hw_access.h"
#include "flexio.h"
#include "edma_driver.h"



extern FLEXIO_Type * const g_flexioBase[FLEXIO_INSTANCE_COUNT];

extern flexio_device_state_t *g_flexioDeviceStatePtr[FLEXIO_INSTANCE_COUNT];

extern const IRQn_Type g_flexioIrqId[FLEXIO_INSTANCE_COUNT];

extern const clock_names_t g_flexioClock[FLEXIO_INSTANCE_COUNT];

extern const uint8_t g_flexioDMASrc[FLEXIO_INSTANCE_COUNT][FEATURE_FLEXIO_MAX_SHIFTER_COUNT];







#if defined(__cplusplus)
extern "C" {
#endif


status_t FLEXIO_DRV_InitDriver(uint32_t instance, flexio_common_state_t *driver);


status_t FLEXIO_DRV_DeinitDriver(const flexio_common_state_t *driver);


#if defined(__cplusplus)
}
#endif


#endif 

