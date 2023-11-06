
#ifndef FLEXIO_DRIVER_H
#define FLEXIO_DRIVER_H

#include <stddef.h>
#include <stdbool.h>
#include "device_registers.h"
#include "osif.h"
#include "status.h"





typedef enum
{
    FLEXIO_DRIVER_TYPE_INTERRUPTS    = 0U,  
    FLEXIO_DRIVER_TYPE_POLLING       = 1U,  
    FLEXIO_DRIVER_TYPE_DMA           = 2U,  
} flexio_driver_type_t;




typedef void (*flexio_isr_t)(void *isrParam);

typedef struct
{
    flexio_isr_t isr;         
    uint32_t instance;        
    uint8_t resourceCount;    
    uint8_t resourceIndex;    
} flexio_common_state_t;

typedef struct
{
    uint8_t resourceAllocation;    
    mutex_t resourceLock;          
    flexio_common_state_t *flexioStatePtr[FEATURE_FLEXIO_MAX_SHIFTER_COUNT];
} flexio_device_state_t;




#if defined(__cplusplus)
extern "C" {
#endif

status_t FLEXIO_DRV_InitDevice(uint32_t instance, flexio_device_state_t *deviceState);


status_t FLEXIO_DRV_DeinitDevice(uint32_t instance);


status_t FLEXIO_DRV_Reset(uint32_t instance);



#if defined(__cplusplus)
}
#endif


#endif 

