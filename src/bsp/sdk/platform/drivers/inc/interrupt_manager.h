#if !defined(INTERRUPT_MANAGER_H)
#define INTERRUPT_MANAGER_H

#include "device_registers.h"






#if FEATURE_MSCM_HAS_CPU_INTERRUPT_ROUTER

typedef enum
{
    INTERRUPT_MANAGER_TARGET_SELF       = -2,
    INTERRUPT_MANAGER_TARGET_OTHERS     = -1,
    INTERRUPT_MANAGER_TARGET_NONE       =  0,
    INTERRUPT_MANAGER_TARGET_CP0        =  1,
    INTERRUPT_MANAGER_TARGET_CP1        =  2,
    INTERRUPT_MANAGER_TARGET_CP0_CP1    =  3
} interrupt_manager_cpu_targets_t;

#endif 

#if FEATURE_INTERRUPT_MULTICORE_SUPPORT

typedef enum
{
	INTERRUPT_CORE_DISABLED     = 0U,
    INTERRUPT_CORE_ENABLED      = 1U
} interrupt_core_enable_t;

#endif 

typedef void (* isr_t)(void);

void DefaultISR(void);


#if defined(__cplusplus)
extern "C" {
#endif 


void INT_SYS_InstallHandler(IRQn_Type irqNumber,
                            const isr_t newHandler,
                            isr_t* const oldHandler);

void INT_SYS_EnableIRQ(IRQn_Type irqNumber);

void INT_SYS_DisableIRQ(IRQn_Type irqNumber);

void INT_SYS_EnableIRQGlobal(void);

void INT_SYS_DisableIRQGlobal(void);

void INT_SYS_SetPriority(IRQn_Type irqNumber, uint8_t priority);

uint8_t INT_SYS_GetPriority(IRQn_Type irqNumber);

#if FEATURE_INTERRUPT_HAS_PENDING_STATE
void INT_SYS_ClearPending(IRQn_Type irqNumber);

void INT_SYS_SetPending(IRQn_Type irqNumber);

uint32_t INT_SYS_GetPending(IRQn_Type irqNumber);

#endif 

#if FEATURE_INTERRUPT_HAS_ACTIVE_STATE
uint32_t INT_SYS_GetActive(IRQn_Type irqNumber);

#endif 

#if FEATURE_INTERRUPT_HAS_SOFTWARE_IRQ

void INT_SYS_SetSoftwareIRQRequest(IRQn_Type irqNumber);

void INT_SYS_ClearSoftwareIRQRequest(IRQn_Type irqNumber);

#endif 


#if FEATURE_INTERRUPT_MULTICORE_SUPPORT

void INT_SYS_EnableIRQ_MC(IRQn_Type irqNumber, const uint8_t *coresIds, uint8_t coresCnt);

void INT_SYS_GetCoresForIRQ(IRQn_Type irqNumber, interrupt_core_enable_t *cores);

void INT_SYS_DisableIRQ_MC(IRQn_Type irqNumber, const uint8_t *coresIds, uint8_t coresCnt);

void INT_SYS_DisableIRQ_MC_All(IRQn_Type irqNumber);

#endif 


#if FEATURE_MSCM_HAS_CPU_INTERRUPT_ROUTER

void INT_SYS_GenerateDirectedCpuInterrupt(IRQn_Type irqNumber, interrupt_manager_cpu_targets_t cpu_target);

#endif 


#if defined(__cplusplus)
}
#endif 


#endif 

