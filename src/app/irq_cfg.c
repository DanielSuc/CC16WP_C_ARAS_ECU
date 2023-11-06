
#include <stdint.h>
#include "irq_cfg.h"
#include "device_registers.h"

const struct_IRQ_PRIORITY mgl_irq_prio[] =
{
		{.irqn_min = DMA0_IRQn,				.irqn_max = DMA15_IRQn,					.irqn_prio = 4},	
		{.irqn_min = ADC0_IRQn,				.irqn_max = ADC1_IRQn,					.irqn_prio = 4},	
		{.irqn_min = PDB0_IRQn,				.irqn_max = PDB0_IRQn,					.irqn_prio = 4},	
		{.irqn_min = PDB1_IRQn,				.irqn_max = PDB1_IRQn,					.irqn_prio = 4},	
		{.irqn_min = LPTMR0_IRQn,			.irqn_max = LPTMR0_IRQn,				.irqn_prio = 3},	
		{.irqn_min = PORTA_IRQn,			.irqn_max = PORTA_IRQn,					.irqn_prio = 2},	
#if	( ( MCU_TYP == S32K144 ) || ( MCU_TYP == S32K148 ) )
		{.irqn_min = LPUART2_RxTx_IRQn,		.irqn_max = LPUART2_RxTx_IRQn,			.irqn_prio = 2},	
#endif
		{.irqn_min = LPUART0_RxTx_IRQn,		.irqn_max = LPUART1_RxTx_IRQn,			.irqn_prio = 8},	
		{.irqn_min = PORTB_IRQn,			.irqn_max = PORTE_IRQn,					.irqn_prio = 8},	
		{.irqn_min = CAN0_ORed_IRQn,		.irqn_max = CAN0_ORed_16_31_MB_IRQn,	.irqn_prio = 7},	
		{.irqn_min = CAN1_ORed_IRQn,		.irqn_max = CAN1_ORed_0_15_MB_IRQn,		.irqn_prio = 7},	
#if	( ( MCU_TYP == S32K144 ) || ( MCU_TYP == S32K148 ) )
		{.irqn_min = CAN2_ORed_IRQn,		.irqn_max = CAN2_ORed_0_15_MB_IRQn,		.irqn_prio = 7},	
#endif
		{.irqn_min = LPI2C0_Slave_IRQn,		.irqn_max = LPI2C0_Slave_IRQn,			.irqn_prio = 5},	
		{.irqn_min = LPI2C0_Master_IRQn,	.irqn_max = LPI2C0_Master_IRQn,			.irqn_prio = 5},	
		{.irqn_min = LPSPI0_IRQn,			.irqn_max = LPSPI1_IRQn,				.irqn_prio = 6},	
#if	( ( MCU_TYP == S32K144 ) || ( MCU_TYP == S32K148 ) )
		{.irqn_min = LPSPI2_IRQn,			.irqn_max = LPSPI2_IRQn,				.irqn_prio = 6},	
#endif
		{.irqn_min = FTM0_Ch0_Ch1_IRQn,		.irqn_max = FTM0_Ovf_Reload_IRQn,		.irqn_prio = 1},	
		{.irqn_min = FTM1_Ch0_Ch1_IRQn,		.irqn_max = FTM1_Ovf_Reload_IRQn,		.irqn_prio = 1},	
		{.irqn_min = FTM2_Ch0_Ch1_IRQn,		.irqn_max = FTM2_Ovf_Reload_IRQn,		.irqn_prio = 1},	
		{.irqn_min = FTM3_Ch0_Ch1_IRQn,		.irqn_max = FTM3_Ovf_Reload_IRQn,		.irqn_prio = 1},	
#if ( MCU_TYP == S32K148 )
		{.irqn_min = FTM4_Ch0_Ch1_IRQn,		.irqn_max = FTM4_Ovf_Reload_IRQn,		.irqn_prio = 1},	
		{.irqn_min = FTM5_Ch0_Ch1_IRQn,		.irqn_max = FTM5_Ovf_Reload_IRQn,		.irqn_prio = 1},	
		{.irqn_min = FTM6_Ch0_Ch1_IRQn,		.irqn_max = FTM6_Ovf_Reload_IRQn,		.irqn_prio = 1},	
		{.irqn_min = FTM7_Ch0_Ch1_IRQn,		.irqn_max = FTM7_Ovf_Reload_IRQn,		.irqn_prio = 1},	
#endif
		{.irqn_min = IRQ_NAN, .irqn_max = IRQ_NAN, .irqn_prio = IRQ_NAN}								
};

