
#ifndef OSIF_H
#define OSIF_H

#include <stdint.h>






#ifdef USING_OS_FREERTOS
#include "FreeRTOS.h"
#include "semphr.h"
typedef SemaphoreHandle_t mutex_t;
typedef SemaphoreHandle_t semaphore_t;

#else
typedef uint8_t mutex_t;
typedef volatile uint8_t semaphore_t;
#endif 


#define OSIF_WAIT_FOREVER 0xFFFFFFFFu

#include "status.h"


void ext_osif_Tick(void);

#if defined (__cplusplus)
extern "C" {
#endif

void OSIF_TimeDelay(const uint32_t delay);

uint32_t OSIF_GetMilliseconds(void);

status_t OSIF_MutexLock(const mutex_t * const pMutex,
                        const uint32_t timeout);

status_t OSIF_MutexUnlock(const mutex_t * const pMutex);


status_t OSIF_MutexCreate(mutex_t * const pMutex);

status_t OSIF_MutexDestroy(const mutex_t * const pMutex);


status_t OSIF_SemaWait(semaphore_t * const pSem,
                       const uint32_t timeout);


status_t OSIF_SemaPost(semaphore_t * const pSem);


status_t OSIF_SemaCreate(semaphore_t * const pSem,
                         const uint8_t initValue);


status_t OSIF_SemaDestroy(const semaphore_t * const pSem);

#if defined (__cplusplus)
}
#endif


#endif 

