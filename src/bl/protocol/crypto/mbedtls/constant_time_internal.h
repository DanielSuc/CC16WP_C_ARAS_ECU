
#ifndef MBEDTLS_CONSTANT_TIME_INTERNAL_H
#define MBEDTLS_CONSTANT_TIME_INTERNAL_H

#include "common.h"

#if defined(MBEDTLS_BIGNUM_C)
#include "mbedtls/bignum.h"
#endif

#if defined(MBEDTLS_SSL_TLS_C)
#include "ssl_misc.h"
#endif

#include <stddef.h>


unsigned mbedtls_ct_uint_mask( unsigned value );

#if defined(MBEDTLS_SSL_SOME_SUITES_USE_TLS_CBC)

size_t mbedtls_ct_size_mask( size_t value );

#endif 

#if defined(MBEDTLS_BIGNUM_C)

mbedtls_mpi_uint mbedtls_ct_mpi_uint_mask( mbedtls_mpi_uint value );

#endif 

#if defined(MBEDTLS_SSL_SOME_SUITES_USE_TLS_CBC)

size_t mbedtls_ct_size_mask_ge( size_t x,
                                size_t y );

#endif 

unsigned mbedtls_ct_size_bool_eq( size_t x,
                                  size_t y );

#if defined(MBEDTLS_BIGNUM_C)

unsigned mbedtls_ct_mpi_uint_lt( const mbedtls_mpi_uint x,
                                 const mbedtls_mpi_uint y );

#endif 

unsigned mbedtls_ct_uint_if( unsigned condition,
                             unsigned if1,
                             unsigned if0 );

#if defined(MBEDTLS_BIGNUM_C)

void mbedtls_ct_mpi_uint_cond_assign( size_t n,
                                      mbedtls_mpi_uint *dest,
                                      const mbedtls_mpi_uint *src,
                                      unsigned char condition );

#endif 

#if defined(MBEDTLS_BASE64_C)

unsigned char mbedtls_ct_base64_enc_char( unsigned char value );

signed char mbedtls_ct_base64_dec_value( unsigned char c );

#endif 

#if defined(MBEDTLS_SSL_SOME_SUITES_USE_TLS_CBC)

void mbedtls_ct_memcpy_if_eq( unsigned char *dest,
                              const unsigned char *src,
                              size_t len,
                              size_t c1, size_t c2 );

void mbedtls_ct_memcpy_offset( unsigned char *dest,
                               const unsigned char *src,
                               size_t offset,
                               size_t offset_min,
                               size_t offset_max,
                               size_t len );

int mbedtls_ct_hmac( mbedtls_md_context_t *ctx,
                     const unsigned char *add_data,
                     size_t add_data_len,
                     const unsigned char *data,
                     size_t data_len_secret,
                     size_t min_data_len,
                     size_t max_data_len,
                     unsigned char *output );

#endif 

#if defined(MBEDTLS_PKCS1_V15) && defined(MBEDTLS_RSA_C) && !defined(MBEDTLS_RSA_ALT)

int mbedtls_ct_rsaes_pkcs1_v15_unpadding( unsigned char *input,
                                          size_t ilen,
                                          unsigned char *output,
                                          size_t output_max_len,
                                          size_t *olen );

#endif 

#endif 

