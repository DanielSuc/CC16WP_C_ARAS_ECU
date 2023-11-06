#ifndef MBEDTLS_MD_WRAP_H
#define MBEDTLS_MD_WRAP_H

#include "mbedtls/build_info.h"

#include "mbedtls/md.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mbedtls_md_info_t
{
    const char * name;

    mbedtls_md_type_t type;

    unsigned char size;

    unsigned char block_size;
};

#if defined(MBEDTLS_MD5_C)
extern const mbedtls_md_info_t mbedtls_md5_info;
#endif
#if defined(MBEDTLS_RIPEMD160_C)
extern const mbedtls_md_info_t mbedtls_ripemd160_info;
#endif
#if defined(MBEDTLS_SHA1_C)
extern const mbedtls_md_info_t mbedtls_sha1_info;
#endif
#if defined(MBEDTLS_SHA224_C)
extern const mbedtls_md_info_t mbedtls_sha224_info;
#endif
#if defined(MBEDTLS_SHA256_C)
extern const mbedtls_md_info_t mbedtls_sha256_info;
#endif
#if defined(MBEDTLS_SHA384_C)
extern const mbedtls_md_info_t mbedtls_sha384_info;
#endif
#if defined(MBEDTLS_SHA512_C)
extern const mbedtls_md_info_t mbedtls_sha512_info;
#endif

#ifdef __cplusplus
}
#endif

#endif 

