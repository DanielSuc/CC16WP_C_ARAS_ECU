
#ifndef MBEDTLS_LIBRARY_COMMON_H
#define MBEDTLS_LIBRARY_COMMON_H

#include "mbedtls/build_info.h"

#include <stdint.h>

#if defined(MBEDTLS_TEST_HOOKS)
#define MBEDTLS_STATIC_TESTABLE
#else
#define MBEDTLS_STATIC_TESTABLE static
#endif

#if defined(MBEDTLS_TEST_HOOKS)
extern void (*mbedtls_test_hook_test_fail)( const char * test, int line, const char * file );
#define MBEDTLS_TEST_HOOK_TEST_ASSERT( TEST ) \
       do { \
            if( ( ! ( TEST ) ) && ( ( *mbedtls_test_hook_test_fail ) != NULL ) ) \
            { \
              ( *mbedtls_test_hook_test_fail )( #TEST, __LINE__, __FILE__ ); \
            } \
    } while( 0 )
#else
#define MBEDTLS_TEST_HOOK_TEST_ASSERT( TEST )
#endif 

#define MBEDTLS_ALLOW_PRIVATE_ACCESS

#define MBEDTLS_BYTE_0( x ) ( (uint8_t) (   ( x )         & 0xff ) )
#define MBEDTLS_BYTE_1( x ) ( (uint8_t) ( ( ( x ) >> 8  ) & 0xff ) )
#define MBEDTLS_BYTE_2( x ) ( (uint8_t) ( ( ( x ) >> 16 ) & 0xff ) )
#define MBEDTLS_BYTE_3( x ) ( (uint8_t) ( ( ( x ) >> 24 ) & 0xff ) )
#define MBEDTLS_BYTE_4( x ) ( (uint8_t) ( ( ( x ) >> 32 ) & 0xff ) )
#define MBEDTLS_BYTE_5( x ) ( (uint8_t) ( ( ( x ) >> 40 ) & 0xff ) )
#define MBEDTLS_BYTE_6( x ) ( (uint8_t) ( ( ( x ) >> 48 ) & 0xff ) )
#define MBEDTLS_BYTE_7( x ) ( (uint8_t) ( ( ( x ) >> 56 ) & 0xff ) )

#ifndef MBEDTLS_GET_UINT32_BE
#define MBEDTLS_GET_UINT32_BE( data , offset )                  \
    (                                                           \
          ( (uint32_t) ( data )[( offset )    ] << 24 )         \
        | ( (uint32_t) ( data )[( offset ) + 1] << 16 )         \
        | ( (uint32_t) ( data )[( offset ) + 2] <<  8 )         \
        | ( (uint32_t) ( data )[( offset ) + 3]       )         \
    )
#endif

#ifndef MBEDTLS_PUT_UINT32_BE
#define MBEDTLS_PUT_UINT32_BE( n, data, offset )                \
{                                                               \
    ( data )[( offset )    ] = MBEDTLS_BYTE_3( n );             \
    ( data )[( offset ) + 1] = MBEDTLS_BYTE_2( n );             \
    ( data )[( offset ) + 2] = MBEDTLS_BYTE_1( n );             \
    ( data )[( offset ) + 3] = MBEDTLS_BYTE_0( n );             \
}
#endif

#ifndef MBEDTLS_GET_UINT32_LE
#define MBEDTLS_GET_UINT32_LE( data, offset )                   \
    (                                                           \
          ( (uint32_t) ( data )[( offset )    ]       )         \
        | ( (uint32_t) ( data )[( offset ) + 1] <<  8 )         \
        | ( (uint32_t) ( data )[( offset ) + 2] << 16 )         \
        | ( (uint32_t) ( data )[( offset ) + 3] << 24 )         \
    )
#endif

#ifndef MBEDTLS_PUT_UINT32_LE
#define MBEDTLS_PUT_UINT32_LE( n, data, offset )                \
{                                                               \
    ( data )[( offset )    ] = MBEDTLS_BYTE_0( n );             \
    ( data )[( offset ) + 1] = MBEDTLS_BYTE_1( n );             \
    ( data )[( offset ) + 2] = MBEDTLS_BYTE_2( n );             \
    ( data )[( offset ) + 3] = MBEDTLS_BYTE_3( n );             \
}
#endif

#ifndef MBEDTLS_GET_UINT16_LE
#define MBEDTLS_GET_UINT16_LE( data, offset )                   \
    (                                                           \
          ( (uint16_t) ( data )[( offset )    ]       )         \
        | ( (uint16_t) ( data )[( offset ) + 1] <<  8 )         \
    )
#endif

#ifndef MBEDTLS_PUT_UINT16_LE
#define MBEDTLS_PUT_UINT16_LE( n, data, offset )                \
{                                                               \
    ( data )[( offset )    ] = MBEDTLS_BYTE_0( n );             \
    ( data )[( offset ) + 1] = MBEDTLS_BYTE_1( n );             \
}
#endif

#ifndef MBEDTLS_GET_UINT16_BE
#define MBEDTLS_GET_UINT16_BE( data, offset )                   \
    (                                                           \
          ( (uint16_t) ( data )[( offset )    ] << 8 )          \
        | ( (uint16_t) ( data )[( offset ) + 1]      )          \
    )
#endif

#ifndef MBEDTLS_PUT_UINT16_BE
#define MBEDTLS_PUT_UINT16_BE( n, data, offset )                \
{                                                               \
    ( data )[( offset )    ] = MBEDTLS_BYTE_1( n );             \
    ( data )[( offset ) + 1] = MBEDTLS_BYTE_0( n );             \
}
#endif

#ifndef MBEDTLS_GET_UINT24_BE
#define MBEDTLS_GET_UINT24_BE( data , offset )                  \
    (                                                           \
          ( (uint32_t) ( data )[( offset )    ] << 16 )         \
        | ( (uint32_t) ( data )[( offset ) + 1] << 8  )         \
        | ( (uint32_t) ( data )[( offset ) + 2]       )         \
    )
#endif

#ifndef MBEDTLS_PUT_UINT24_BE
#define MBEDTLS_PUT_UINT24_BE( n, data, offset )                \
{                                                               \
    ( data )[( offset )    ] = MBEDTLS_BYTE_2( n );             \
    ( data )[( offset ) + 1] = MBEDTLS_BYTE_1( n );             \
    ( data )[( offset ) + 2] = MBEDTLS_BYTE_0( n );             \
}
#endif

#ifndef MBEDTLS_GET_UINT24_LE
#define MBEDTLS_GET_UINT24_LE( data, offset )                   \
    (                                                           \
          ( (uint32_t) ( data )[( offset )    ]       )         \
        | ( (uint32_t) ( data )[( offset ) + 1] <<  8 )         \
        | ( (uint32_t) ( data )[( offset ) + 2] << 16 )         \
    )
#endif

#ifndef MBEDTLS_PUT_UINT24_LE
#define MBEDTLS_PUT_UINT24_LE( n, data, offset )                \
{                                                               \
    ( data )[( offset )    ] = MBEDTLS_BYTE_0( n );             \
    ( data )[( offset ) + 1] = MBEDTLS_BYTE_1( n );             \
    ( data )[( offset ) + 2] = MBEDTLS_BYTE_2( n );             \
}
#endif

#ifndef MBEDTLS_GET_UINT64_BE
#define MBEDTLS_GET_UINT64_BE( data, offset )                   \
    (                                                           \
          ( (uint64_t) ( data )[( offset )    ] << 56 )         \
        | ( (uint64_t) ( data )[( offset ) + 1] << 48 )         \
        | ( (uint64_t) ( data )[( offset ) + 2] << 40 )         \
        | ( (uint64_t) ( data )[( offset ) + 3] << 32 )         \
        | ( (uint64_t) ( data )[( offset ) + 4] << 24 )         \
        | ( (uint64_t) ( data )[( offset ) + 5] << 16 )         \
        | ( (uint64_t) ( data )[( offset ) + 6] <<  8 )         \
        | ( (uint64_t) ( data )[( offset ) + 7]       )         \
    )
#endif

#ifndef MBEDTLS_PUT_UINT64_BE
#define MBEDTLS_PUT_UINT64_BE( n, data, offset )                \
{                                                               \
    ( data )[( offset )    ] = MBEDTLS_BYTE_7( n );             \
    ( data )[( offset ) + 1] = MBEDTLS_BYTE_6( n );             \
    ( data )[( offset ) + 2] = MBEDTLS_BYTE_5( n );             \
    ( data )[( offset ) + 3] = MBEDTLS_BYTE_4( n );             \
    ( data )[( offset ) + 4] = MBEDTLS_BYTE_3( n );             \
    ( data )[( offset ) + 5] = MBEDTLS_BYTE_2( n );             \
    ( data )[( offset ) + 6] = MBEDTLS_BYTE_1( n );             \
    ( data )[( offset ) + 7] = MBEDTLS_BYTE_0( n );             \
}
#endif

#ifndef MBEDTLS_GET_UINT64_LE
#define MBEDTLS_GET_UINT64_LE( data, offset )                   \
    (                                                           \
          ( (uint64_t) ( data )[( offset ) + 7] << 56 )         \
        | ( (uint64_t) ( data )[( offset ) + 6] << 48 )         \
        | ( (uint64_t) ( data )[( offset ) + 5] << 40 )         \
        | ( (uint64_t) ( data )[( offset ) + 4] << 32 )         \
        | ( (uint64_t) ( data )[( offset ) + 3] << 24 )         \
        | ( (uint64_t) ( data )[( offset ) + 2] << 16 )         \
        | ( (uint64_t) ( data )[( offset ) + 1] <<  8 )         \
        | ( (uint64_t) ( data )[( offset )    ]       )         \
    )
#endif

#ifndef MBEDTLS_PUT_UINT64_LE
#define MBEDTLS_PUT_UINT64_LE( n, data, offset )                \
{                                                               \
    ( data )[( offset )    ] = MBEDTLS_BYTE_0( n );             \
    ( data )[( offset ) + 1] = MBEDTLS_BYTE_1( n );             \
    ( data )[( offset ) + 2] = MBEDTLS_BYTE_2( n );             \
    ( data )[( offset ) + 3] = MBEDTLS_BYTE_3( n );             \
    ( data )[( offset ) + 4] = MBEDTLS_BYTE_4( n );             \
    ( data )[( offset ) + 5] = MBEDTLS_BYTE_5( n );             \
    ( data )[( offset ) + 6] = MBEDTLS_BYTE_6( n );             \
    ( data )[( offset ) + 7] = MBEDTLS_BYTE_7( n );             \
}
#endif

#if (defined(_MSC_VER) && ( _MSC_VER <= 1900 ))
#define  __func__ __FUNCTION__
#endif

#endif 

