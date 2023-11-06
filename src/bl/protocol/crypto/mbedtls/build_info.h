
#ifndef MBEDTLS_BUILD_INFO_H
#define MBEDTLS_BUILD_INFO_H


#define MBEDTLS_VERSION_MAJOR  3
#define MBEDTLS_VERSION_MINOR  1
#define MBEDTLS_VERSION_PATCH  0

#define MBEDTLS_VERSION_NUMBER         0x03010000
#define MBEDTLS_VERSION_STRING         "3.1.0"
#define MBEDTLS_VERSION_STRING_FULL    "mbed TLS 3.1.0"

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
#define _CRT_SECURE_NO_DEPRECATE 1
#endif

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls_config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_CONFIG_VERSION) && ( \
    MBEDTLS_CONFIG_VERSION < 0x03000000 || \
    MBEDTLS_CONFIG_VERSION > MBEDTLS_VERSION_NUMBER )
#error "Invalid config version, defined value of MBEDTLS_CONFIG_VERSION is unsupported"
#endif

#if defined(MBEDTLS_USER_CONFIG_FILE)
#include MBEDTLS_USER_CONFIG_FILE
#endif

#if defined(MBEDTLS_PSA_CRYPTO_CONFIG)
#include "mbedtls/config_psa.h"
#endif

#include "check_config.h"

#endif 

