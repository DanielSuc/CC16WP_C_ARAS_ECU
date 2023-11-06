
#ifndef MBEDTLS_MD_H
#define MBEDTLS_MD_H
#include "mbedtls/private_access.h"

#include <stddef.h>

#include "mbedtls/build_info.h"
#include "mbedtls/platform_util.h"

#define MBEDTLS_ERR_MD_FEATURE_UNAVAILABLE                -0x5080
#define MBEDTLS_ERR_MD_BAD_INPUT_DATA                     -0x5100
#define MBEDTLS_ERR_MD_ALLOC_FAILED                       -0x5180
#define MBEDTLS_ERR_MD_FILE_IO_ERROR                      -0x5200

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    MBEDTLS_MD_NONE=0,    
    MBEDTLS_MD_MD5,       
    MBEDTLS_MD_SHA1,      
    MBEDTLS_MD_SHA224,    
    MBEDTLS_MD_SHA256,    
    MBEDTLS_MD_SHA384,    
    MBEDTLS_MD_SHA512,    
    MBEDTLS_MD_RIPEMD160, 
} mbedtls_md_type_t;

#if defined(MBEDTLS_SHA512_C)
#define MBEDTLS_MD_MAX_SIZE         64  
#else
#define MBEDTLS_MD_MAX_SIZE         32  
#endif

#if defined(MBEDTLS_SHA512_C)
#define MBEDTLS_MD_MAX_BLOCK_SIZE         128
#else
#define MBEDTLS_MD_MAX_BLOCK_SIZE         64
#endif

typedef struct mbedtls_md_info_t mbedtls_md_info_t;

typedef struct mbedtls_md_context_t
{
    const mbedtls_md_info_t *MBEDTLS_PRIVATE(md_info);

    void *MBEDTLS_PRIVATE(md_ctx);

    void *MBEDTLS_PRIVATE(hmac_ctx);
} mbedtls_md_context_t;

const int *mbedtls_md_list( void );

const mbedtls_md_info_t *mbedtls_md_info_from_string( const char *md_name );

const mbedtls_md_info_t *mbedtls_md_info_from_type( mbedtls_md_type_t md_type );

void mbedtls_md_init( mbedtls_md_context_t *ctx );

void mbedtls_md_free( mbedtls_md_context_t *ctx );


MBEDTLS_CHECK_RETURN_TYPICAL
int mbedtls_md_setup( mbedtls_md_context_t *ctx, const mbedtls_md_info_t *md_info, int hmac );

MBEDTLS_CHECK_RETURN_TYPICAL
int mbedtls_md_clone( mbedtls_md_context_t *dst,
                      const mbedtls_md_context_t *src );

unsigned char mbedtls_md_get_size( const mbedtls_md_info_t *md_info );

mbedtls_md_type_t mbedtls_md_get_type( const mbedtls_md_info_t *md_info );

const char *mbedtls_md_get_name( const mbedtls_md_info_t *md_info );

MBEDTLS_CHECK_RETURN_TYPICAL
int mbedtls_md_starts( mbedtls_md_context_t *ctx );

MBEDTLS_CHECK_RETURN_TYPICAL
int mbedtls_md_update( mbedtls_md_context_t *ctx, const unsigned char *input, size_t ilen );

MBEDTLS_CHECK_RETURN_TYPICAL
int mbedtls_md_finish( mbedtls_md_context_t *ctx, unsigned char *output );

MBEDTLS_CHECK_RETURN_TYPICAL
int mbedtls_md( const mbedtls_md_info_t *md_info, const unsigned char *input, size_t ilen,
        unsigned char *output );

#if defined(MBEDTLS_FS_IO)
MBEDTLS_CHECK_RETURN_TYPICAL
int mbedtls_md_file( const mbedtls_md_info_t *md_info, const char *path,
                     unsigned char *output );
#endif 

MBEDTLS_CHECK_RETURN_TYPICAL
int mbedtls_md_hmac_starts( mbedtls_md_context_t *ctx, const unsigned char *key,
                    size_t keylen );

MBEDTLS_CHECK_RETURN_TYPICAL
int mbedtls_md_hmac_update( mbedtls_md_context_t *ctx, const unsigned char *input,
                    size_t ilen );

MBEDTLS_CHECK_RETURN_TYPICAL
int mbedtls_md_hmac_finish( mbedtls_md_context_t *ctx, unsigned char *output);

MBEDTLS_CHECK_RETURN_TYPICAL
int mbedtls_md_hmac_reset( mbedtls_md_context_t *ctx );

MBEDTLS_CHECK_RETURN_TYPICAL
int mbedtls_md_hmac( const mbedtls_md_info_t *md_info, const unsigned char *key, size_t keylen,
                const unsigned char *input, size_t ilen,
                unsigned char *output );

MBEDTLS_CHECK_RETURN_TYPICAL
int mbedtls_md_process( mbedtls_md_context_t *ctx, const unsigned char *data );

#ifdef __cplusplus
}
#endif

#endif 

