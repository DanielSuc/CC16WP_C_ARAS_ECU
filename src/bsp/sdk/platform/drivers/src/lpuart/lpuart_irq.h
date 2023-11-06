
#ifndef LPUART_IRQ_H__
#define LPUART_IRQ_H__

#include "device_registers.h"
#include "interrupt_manager.h"

extern void LPUART_DRV_IRQHandler(uint32_t instance);


#if (LPUART_INSTANCE_COUNT > 0U)
void LPUART0_IrqHandler(void);
#endif

#if (LPUART_INSTANCE_COUNT > 1U)
void LPUART1_IrqHandler(void);
#endif

#if (LPUART_INSTANCE_COUNT > 2U)
void LPUART2_IrqHandler(void);
#endif

#if (LPUART_INSTANCE_COUNT > 3U)
void LPUART3_IrqHandler(void);
#endif

extern isr_t g_lpuartIsr[LPUART_INSTANCE_COUNT];

#endif 

