

#ifndef dmaController1_H
#define dmaController1_H

#include "clockMan1.h"
#include "Cpu.h"

#define EDMA_CHN1_NUMBER   1U

#define EDMA_CHN2_NUMBER   2U

#define EDMA_CONFIGURED_CHANNELS_COUNT   2U

extern edma_state_t dmaController1_State;

extern edma_chn_state_t * const edmaChnStateArray[EDMA_CONFIGURED_CHANNELS_COUNT];

extern const edma_user_config_t dmaController1_InitConfig0;

extern const edma_channel_config_t * const edmaChnConfigArray[EDMA_CONFIGURED_CHANNELS_COUNT];



#endif  



