
#ifndef DEVASSERT_H
#define DEVASSERT_H

#include <stdbool.h>



#if defined (CUSTOM_DEVASSERT)
    #include CUSTOM_DEVASSERT
#elif defined (DEV_ERROR_DETECT)
static inline void DevAssert(volatile bool x)
{
    if(x) { } else { BKPT_ASM; for(;;) {} }
}
    #define DEV_ASSERT(x) DevAssert(x)
#else
    #define DEV_ASSERT(x) ((void)0)
#endif

#endif 


