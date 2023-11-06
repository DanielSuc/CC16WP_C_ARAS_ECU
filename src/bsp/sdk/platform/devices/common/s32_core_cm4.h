

#if !defined (CORE_CM4_H)
#define CORE_CM4_H


#ifdef __cplusplus
extern "C" {
#endif

#define BKPT_ASM __asm("BKPT #0\n\t")


#if defined (__GNUC__) || defined (__ARMCC_VERSION)
#if defined (__VFP_FP__) && !defined (__SOFTFP__)
#define ENABLE_FPU
#endif

#elif defined (__ICCARM__)
#if defined __ARMVFP__
#define ENABLE_FPU
#endif

#elif defined (__ghs__) || defined (__DCC__)
#if defined (__VFP__)
#define ENABLE_FPU
#endif
#endif 

#if defined (__GNUC__) 
#define ENABLE_INTERRUPTS() __asm volatile ("cpsie i" : : : "memory");
#else
#define ENABLE_INTERRUPTS() __asm("cpsie i")
#endif


#if defined (__GNUC__)
#define DISABLE_INTERRUPTS() __asm volatile ("cpsid i" : : : "memory");
#else
#define DISABLE_INTERRUPTS() __asm("cpsid i")
#endif


#if defined (__GNUC__)
#define STANDBY() __asm volatile ("wfi")
#else
#define STANDBY() __asm("wfi")
#endif

#define NOP() __asm volatile ("nop")

#if defined (__GNUC__) || defined (__ICCARM__) || defined (__ghs__) || defined (__ARMCC_VERSION)
#define REV_BYTES_32(a, b) __asm volatile ("rev %0, %1" : "=r" (b) : "r" (a))
#else
#define REV_BYTES_32(a, b) (b = ((a & 0xFF000000U) >> 24U) | ((a & 0xFF0000U) >> 8U) \
                                | ((a & 0xFF00U) << 8U) | ((a & 0xFFU) << 24U))
#endif

#if defined (__GNUC__) || defined (__ICCARM__) || defined (__ghs__) || defined (__ARMCC_VERSION)
#define REV_BYTES_16(a, b) __asm volatile ("rev16 %0, %1" : "=r" (b) : "r" (a))
#else
#define REV_BYTES_16(a, b) (b = ((a & 0xFF000000U) >> 8U) | ((a & 0xFF0000U) << 8U) \
                                | ((a & 0xFF00U) >> 8U) | ((a & 0xFFU) << 8U))
#endif

#if defined ( __GNUC__ ) || defined (__ARMCC_VERSION)
    #define START_FUNCTION_DECLARATION_RAMSECTION
    #define END_FUNCTION_DECLARATION_RAMSECTION        __attribute__((section (".code_ram")));

    #define START_FUNCTION_DECLARATION_RAMSECTION_NOINLINE
    #define END_FUNCTION_DECLARATION_RAMSECTION_NOINLINE        __attribute__((noinline, section (".code_ram")));

#elif defined ( __ghs__ )
    #define START_FUNCTION_DECLARATION_RAMSECTION      _Pragma("ghs callmode=far")
    #define END_FUNCTION_DECLARATION_RAMSECTION        __attribute__((section (".code_ram")));\
                                                       _Pragma("ghs callmode=default")
#elif defined ( __ICCARM__ )
    #define START_FUNCTION_DECLARATION_RAMSECTION      __ramfunc
    #define END_FUNCTION_DECLARATION_RAMSECTION        ;
#elif defined ( __DCC__ )
    #define START_FUNCTION_DECLARATION_RAMSECTION      _Pragma("section CODE \".code_ram\"") \
                                                       _Pragma("use_section CODE")
    #define END_FUNCTION_DECLARATION_RAMSECTION        ; \
                                                       _Pragma("section CODE \".text\"")
#else
    #define START_FUNCTION_DECLARATION_RAMSECTION      
    #define END_FUNCTION_DECLARATION_RAMSECTION        ;
#endif

    #define START_FUNCTION_DEFINITION_RAMSECTION
    #define END_FUNCTION_DEFINITION_RAMSECTION

#if defined (__ICCARM__)
    #define DISABLE_CHECK_RAMSECTION_FUNCTION_CALL     _Pragma("diag_suppress=Ta022")
    #define ENABLE_CHECK_RAMSECTION_FUNCTION_CALL      _Pragma("diag_default=Ta022")
#else
    #define DISABLE_CHECK_RAMSECTION_FUNCTION_CALL
    #define ENABLE_CHECK_RAMSECTION_FUNCTION_CALL
#endif

#define GET_CORE_ID()	0U

#if defined ( __GNUC__ ) || defined ( __ghs__ ) || defined ( __DCC__ ) || defined (__ARMCC_VERSION)
    #define ALIGNED(x)      __attribute__((aligned(x)))
#elif defined ( __ICCARM__ )
    #define stringify(s) tostring(s)
    #define tostring(s) #s
    #define ALIGNED(x)      _Pragma(stringify(data_alignment=x))
#else
    #define ALIGNED(x)
#endif

#define CORE_LITTLE_ENDIAN

#ifdef __cplusplus
}
#endif

#endif 


