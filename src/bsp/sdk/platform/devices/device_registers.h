
#ifndef DEVICE_REGISTERS_H
#define DEVICE_REGISTERS_H



#if (defined(CPU_S32K148) || defined(CPU_S32K146) || defined(CPU_S32K144HFT0VLLT) || defined(CPU_S32K144LFT0MLLT) || defined(CPU_S32K142))

    #define S32K14x_SERIES

    #include "common/s32_core_cm4.h"

    #if defined(CPU_S32K148)

        #define S32K148_SERIES

        #include "S32K148.h"
        #include "S32K148_features.h"
        #include "system_S32K148.h"

    #elif defined(CPU_S32K146)

        #define S32K146_SERIES

        #include "S32K146/include/S32K146.h"
        #include "S32K146/include/S32K146_features.h"

    #elif (defined(CPU_S32K144HFT0VLLT) || defined(CPU_S32K144LFT0MLLT))

        #define S32K144_SERIES

        #include "S32K144.h"
        #include "S32K144_features.h"
        #include "system_S32K144.h"

    #elif defined(CPU_S32K142)

        #define S32K142_SERIES

        #include "S32K142.h"
        #include "S32K142_features.h"
        #include "system_S32K142.h"

    #endif

#elif defined(CPU_S32V234)

    #define S32V234_SERIES

    #include "common/s32_core_cm4.h"
    #include "S32V234/include/S32V234.h"
    #include "S32V234/include/S32V234_features.h"

#elif (defined(CPU_S32K116) || defined(CPU_S32K118))

    #define S32K11x_SERIES

    #include "common/s32_core_cm0.h"

    #if defined(CPU_S32K116)

        #define S32K116_SERIES
        #include "S32K116/include/S32K116.h"
        #include "S32K116/include/S32K116_features.h"
    #elif defined(CPU_S32K118)

        #define S32K118_SERIES
        #include "S32K118/include/S32K118.h"
        #include "S32K118/include/S32K118_features.h"

    #endif

#elif defined(CPU_MPC5777C)

    #define MPC5777C_SERIES

    #include "common/s32_core_e200.h"
    #include "MPC5777C/include/MPC5777C.h"
    #include "MPC5777C/include/MPC5777C_features.h"

#elif (defined(CPU_MPC5746R) || defined(CPU_MPC5748G) || defined(CPU_MPC5746C) || defined(CPU_MPC5741P)|| defined(CPU_MPC5742P)|| defined(CPU_MPC5743P)|| defined(CPU_MPC5744P) || defined(CPU_MPC5744B) || defined(CPU_MPC5745B) || defined(CPU_MPC5746B) || defined(CPU_MPC5744C) || defined(CPU_MPC5745C) || defined(CPU_MPC5747C) || defined(CPU_MPC5748C) || defined(CPU_MPC5746G) || defined(CPU_MPC5747G))

    #define MPC574x_SERIES

    #include "common/s32_core_e200.h"

    #if (defined(CPU_MPC5746R))

        #define MPC5746R_SERIES

        #include "MPC5746R/include/MPC5746R.h"
        #include "MPC5746R/include/MPC5746R_features.h"

    #elif (defined(CPU_MPC5748G))

        #define MPC5748G_SERIES

        #include "MPC5748G/include/MPC5748G.h"
        #include "MPC5748G/include/MPC5748G_features.h"

    #elif (defined(CPU_MPC5747C))

        #define MPC5747C_SERIES

        #include "MPC5747C/include/MPC5747C.h"
        #include "MPC5747C/include/MPC5747C_features.h"

    #elif (defined(CPU_MPC5748C))

        #define MPC5748C_SERIES

        #include "MPC5748C/include/MPC5748C.h"
        #include "MPC5748C/include/MPC5748C_features.h"

    #elif (defined(CPU_MPC5746G))

        #define MPC5746G_SERIES

        #include "MPC5746G/include/MPC5746G.h"
        #include "MPC5746G/include/MPC5746G_features.h"

    #elif (defined(CPU_MPC5747G))

        #define MPC5747G_SERIES

        #include "MPC5747G/include/MPC5747G.h"
        #include "MPC5747G/include/MPC5747G_features.h"

    #elif defined(CPU_MPC5746C)

        #define MPC5746C_SERIES

        #include "MPC5746C/include/MPC5746C.h"
        #include "MPC5746C/include/MPC5746C_features.h"

    #elif defined(CPU_MPC5744B)

        #define MPC5744B_SERIES

        #include "MPC5744B/include/MPC5744B.h"
        #include "MPC5744B/include/MPC5744B_features.h"

    #elif defined(CPU_MPC5745B)

        #define MPC5745B_SERIES

        #include "MPC5745B/include/MPC5745B.h"
        #include "MPC5745B/include/MPC5745B_features.h"

    #elif defined(CPU_MPC5746B)

        #define MPC5746B_SERIES

        #include "MPC5746B/include/MPC5746B.h"
        #include "MPC5746B/include/MPC5746B_features.h"

    #elif defined(CPU_MPC5744C)

        #define MPC5744C_SERIES

        #include "MPC5744C/include/MPC5744C.h"
        #include "MPC5744C/include/MPC5744C_features.h"

    #elif defined(CPU_MPC5745C)

        #define MPC5745C_SERIES

        #include "MPC5745C/include/MPC5745C.h"
        #include "MPC5745C/include/MPC5745C_features.h"

    #elif defined(CPU_MPC5741P)

        #define MPC5741P_SERIES

        #include "MPC5741P/include/MPC5741P.h"
        #include "MPC5741P/include/MPC5741P_features.h"

    #elif defined(CPU_MPC5742P)

        #define MPC5742P_SERIES

        #include "MPC5742P/include/MPC5742P.h"
        #include "MPC5742P/include/MPC5742P_features.h"

    #elif defined(CPU_MPC5743P)

        #define MPC5743P_SERIES

        #include "MPC5743P/include/MPC5743P.h"
        #include "MPC5743P/include/MPC5743P_features.h"

    #elif defined(CPU_MPC5744P)

        #define MPC5744P_SERIES

        #include "MPC5744P/include/MPC5744P.h"
        #include "MPC5744P/include/MPC5744P_features.h"

    #endif
#elif (defined(CPU_S32R274) || defined(CPU_S32R372))

    #define S32R_SERIES

    #include "common/s32_core_e200.h"

    #if (defined(CPU_S32R274))

        #define S32R274_SERIES

        #include "S32R274/include/S32R274.h"
        #include "S32R274/include/S32R274_features.h"

    #elif (defined(CPU_S32R372))

        #define S32R372_SERIES

        #include "S32R372/include/S32R372.h"
        #include "S32R372/include/S32R372_features.h"
    #endif
#elif (defined(CPU_S32MTV))

    #define S32MTV_SERIES

    #include "common/s32_core_cm4.h"

    #include "S32MTV/include/S32MTV.h"
    #include "S32MTV/include/S32MTV_features.h"

#elif defined(CPU_SJA1110)

    #define SJA1110_SERIES

    #include "common/s32_core_cm7.h"

    #include "SJA1110/include/SJA1110.h"
    #include "SJA1110/include/SJA1110_features.h"
    #include "SJA1110/include/SJA1110_floats.h"

#elif defined(CPU_S32S247)

    #define S32S247_SERIES

    #include "common/s32_core_cm7.h"

    #include "S32S247/include/S32S247.h"
    #include "S32S247/include/S32S247_features.h"

#else
    #error "No valid CPU defined!"
#endif

#include "devassert.h"

#endif 


