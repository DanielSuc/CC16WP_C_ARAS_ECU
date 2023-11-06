

#include "edma_hw_access.h"

void EDMA_DRV_IRQHandler(uint8_t virtualChannel);
#ifdef FEATURE_DMA_HAS_ERROR_IRQ
void EDMA_DRV_ErrorIRQHandler(uint8_t virtualChannel);
#endif


