#ifndef HAL_DATA_TYPES_H
#define HAL_DATA_TYPES_H


#define MRS_LITTLE_ENDIAN   1234
#define MRS_BIG_ENDIAN      4321
    #if defined __V850__ && defined __ghs__

        #define RH850F1L_GHS                 1

        typedef unsigned char                boolean;           
        typedef unsigned char               uint8_t;            
        typedef unsigned short              uint16_t;           
        typedef unsigned long               uint32_t;           
        typedef unsigned long long          uint64_t;           


        typedef signed char                   int8_t;           
        typedef signed short                  int16_t;          
        typedef signed long                   int32_t;          
        typedef signed long long              int64_t;          

        typedef float                       float32_t;          
        typedef double                      float64_t;          

        typedef uint8_t*  const reg_8bit_t;                     
        typedef uint16_t* const reg_16bit_t;                    
        typedef uint32_t* const reg_32bit_t;                    

        #define INT8_MAX    127                                 
        #define INT16_MAX   32767                               
        #define INT32_MAX   2147483647                          
        #define INT64_MAX   9223372036854775807LL               

        #define UINT8_MAX   0xffu                               
        #define UINT16_MAX  0xffffu                             
        #define UINT32_MAX  0xffffffffu                         
        #define UINT64_MAX  0xffffffffffffffffULL               

        #define ARCHITECTURE_64BIT 1                            
        #define ARCHITECTURE_BYTE_ORDER     MRS_LITTLE_ENDIAN   

    #elif defined __GNUC__

        #if __x86_64
            #define ARCHITECTURE_64BIT 1                        
        #elif __amd64
            #define ARCHITECTURE_64BIT 1                        
        #endif

        #include <stddef.h>                                     
        #include <stdint.h>                                     
        #include <stdbool.h>                                    

        typedef _Bool boolean;                                  

        #if defined __BYTE_ORDER__
            #if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
                #define ARCHITECTURE_BYTE_ORDER MRS_BIG_ENDIAN
            #elif __BYTE_ORDER__ ==  __ORDER_LITTLE_ENDIAN__
                #define ARCHITECTURE_BYTE_ORDER MRS_LITTLE_ENDIAN
            #else
                #error "unimplemented endianes detected!"
            #endif
        #else
            #include <sys/param.h>
            #if defined BYTE_ORDER
                #if BYTE_ORDER == LITTLE_ENDIAN
                    #define ARCHITECTURE_BYTE_ORDER MRS_LITTLE_ENDIAN
                #elif BYTE_ORDER == BIG_ENDIAN
                    #define ARCHITECTURE_BYTE_ORDER MRS_BIG_ENDIAN
                #else
                    #error "unimplemented endianes detected!"
                #endif
            #endif
        #endif

    #elif QT_CORE_LIB

        #include <QtGlobal>
        typedef quint8         uint8_t;                         
        typedef qint16         int16_t;                         
        typedef quint16        uint16_t;                        
        typedef qint32         int32_t;                         
        typedef quint32        uint32_t;                        

        #ifndef NULL
            #define NULL ((void *)0)                            
        #endif


    #else
        #error "no standard data types for this platform defined! Adapt hal_data_types.h"
    #endif


    #ifndef TRUE
       #define TRUE                     1u                          
    #endif

    #ifndef FALSE
       #define FALSE                    0u                          
    #endif

    #ifndef NULL_PTR
       #define NULL_PTR                 (void *) 0                  
    #endif

    #define MSB_FIRST                   0u                          
    #define LSB_FIRST                   1u                          
#endif

