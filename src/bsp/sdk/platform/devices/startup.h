
#ifndef STARTUP_H
#define STARTUP_H

#include <stdint.h>
#include "device_registers.h"


#if (defined(S32K14x_SERIES) || defined(S32K11x_SERIES) || defined(S32V234_SERIES) || defined(MPC574x_SERIES) || defined(S32R_SERIES) || defined(S32MTV_SERIES) || defined(SJA1110_SERIES))
    #if (defined(__ICCARM__))     
        #define INTERRUPTS_SECTION_START               __section_begin(".intvec")
        #define INTERRUPTS_SECTION_END                 __section_end(".intvec")
        #define BSS_SECTION_START                      __section_begin(".bss")
        #define BSS_SECTION_END                        __section_end(".bss")
        #define DATA_SECTION_START                     __section_begin(".data")
        #define DATA_SECTION_END                       __section_end(".data")
        #define CUSTOMSECTION_SECTION_START            __section_begin(".customSection")
        #define CUSTOMSECTION_SECTION_END              __section_end(".customSection")
        #define CODE_RAM_SECTION_START                 __section_begin("__CODE_RAM")
        #define CODE_RAM_SECTION_END                   __section_end("__CODE_RAM")
        #define DATA_INIT_SECTION_START                __section_begin(".data_init")
        #define DATA_INIT_SECTION_END                  __section_end(".data_init")
        #define CODE_ROM_SECTION_START                 __section_begin("__CODE_ROM")
        #define CODE_ROM_SECTION_END                   __section_end("__CODE_ROM")

    #elif (defined(__ARMCC_VERSION))
        #define INTERRUPTS_SECTION_START               (uint8_t *)__VECTOR_ROM_START
        #define INTERRUPTS_SECTION_END                 (uint8_t *)__VECTOR_ROM_END
        #define BSS_SECTION_START                      (uint8_t *)__BSS_START
        #define BSS_SECTION_END                        (uint8_t *)__BSS_END
        #define DATA_SECTION_START                     (uint8_t *)__DATA_RAM_START
        #define DATA_SECTION_END                       (uint8_t *)__DATA_RAM_END
        #define CUSTOMSECTION_SECTION_START            (uint8_t *)__CUSTOM_SECTION_START
        #define CUSTOMSECTION_SECTION_END              (uint8_t *)__CUSTOM_SECTION_END
        #define CODE_RAM_SECTION_START                 (uint8_t *)__CODE_RAM_START
        #define CODE_RAM_SECTION_END                   (uint8_t *)__CODE_RAM_END

        extern uint32_t __VECTOR_ROM_START;
        extern uint32_t __VECTOR_ROM_END;
        extern uint32_t __BSS_START;
        extern uint32_t __BSS_END;
        extern uint32_t __DATA_RAM_START;
        extern uint32_t __DATA_RAM_END;
        extern uint32_t __CUSTOM_SECTION_START;
        extern uint32_t __CUSTOM_SECTION_END;
        extern uint32_t __CODE_RAM_START;
        extern uint32_t __CODE_RAM_END;
    #else
        #define INTERRUPTS_SECTION_START               (uint8_t *)&__interrupts_start__
        #define INTERRUPTS_SECTION_END                 (uint8_t *)&__interrupts_end__
        #define BSS_SECTION_START                      (uint8_t *)&__bss_start__
        #define BSS_SECTION_END                        (uint8_t *)&__bss_end__
        #define DATA_SECTION_START                     (uint8_t *)&__data_start__
        #define DATA_SECTION_END                       (uint8_t *)&__data_end__
        #define CUSTOMSECTION_SECTION_START            (uint8_t *)&__customSection_start__
        #define CUSTOMSECTION_SECTION_END              (uint8_t *)&__customSection_end__
        #define CODE_RAM_SECTION_START                 (uint8_t *)&__code_ram_start__
        #define CODE_RAM_SECTION_END                   (uint8_t *)&__code_ram_end__

        extern uint32_t __interrupts_start__;
        extern uint32_t __interrupts_end__;
        extern uint32_t __bss_start__;
        extern uint32_t __bss_end__;
        extern uint32_t __data_start__;
        extern uint32_t __data_end__;
        extern uint32_t __customSection_start__;
        extern uint32_t __customSection_end__;
        extern uint32_t __code_ram_start__;
        extern uint32_t __code_ram_end__;
    #endif
#endif

#if (defined(__ICCARM__))
    #pragma section = ".data"
    #pragma section = ".data_init"
    #pragma section = ".bss"
    #pragma section = ".intvec"
    #pragma section = ".customSection"
    #pragma section = ".customSection_init"
    #pragma section = "__CODE_RAM"
    #pragma section = "__CODE_ROM"
#endif

void init_data_bss(void);

#endif 


