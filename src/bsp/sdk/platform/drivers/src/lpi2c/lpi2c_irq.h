
#ifndef LPI2C_IRQ_H__
#define LPI2C_IRQ_H__

#include "device_registers.h"


#if defined (S32K11x_SERIES)

void LPI2C0_Master_Slave_IRQHandler(void);

#else

#if (LPI2C_INSTANCE_COUNT > 0u)
void LPI2C0_Master_IRQHandler(void);

void LPI2C0_Slave_IRQHandler(void);

#if(LPI2C_INSTANCE_COUNT == 2u)

void LPI2C1_Master_IRQHandler(void);

void LPI2C1_Slave_IRQHandler(void);

#endif 

#endif 

#endif 

#endif 

