
#if !defined(CLOCK_H)
#define CLOCK_H

#include "device_registers.h"
#include "status.h"


 #if (defined(S32K14x_SERIES) || defined(S32K11x_SERIES))
    #include "../src/clock/S32K1xx/clock_S32K1xx.h"
#elif (defined(S32MTV_SERIES))
    #include "../src/clock/S32Mxx/clock_S32Mxx.h"
#elif (defined(MPC5777C_SERIES))
    #include "../src/clock/MPC5777C/clock_MPC5777C.c"
#elif (defined(MPC574x_SERIES) || defined(S32R_SERIES))
    #include "../src/clock/MPC57xx/clock_MPC57xx.h"
#elif (defined(S32S247_SERIES))
    #include "../src/clock/S32Sxx/clock_S32Sxx.h"
#elif (defined(SJA1110_SERIES))
    #include "../src/clock/SJA1110x/clock_SJA1110x.h"
#elif (defined(S32V234_SERIES))
    #include "../src/clock/S32Vxx/clock_S32Vxx.h"
#else
    #error "No valid CPU defined!"
#endif





#if defined(__cplusplus)
extern "C" {
#endif 




status_t CLOCK_DRV_GetFreq(clock_names_t clockName,
                           uint32_t *frequency);


status_t CLOCK_DRV_Init(clock_user_config_t const * config);



#if defined(__cplusplus)
}
#endif 


#endif 


