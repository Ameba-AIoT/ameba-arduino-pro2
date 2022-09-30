/* RTL_CRYPTO_FRAGMENT should be 16bytes-aligned */
#if defined(CONFIG_PLATFORM_8735B)
#define RTL_CRYPTO_FRAGMENT               65536 // 64k bytes
#else
#define RTL_CRYPTO_FRAGMENT               15360
#endif

#ifndef ARDUINO_SDK
#include "mbedtls/mbedtls_config.h"
#else
#include "mbedtls/config_arduino.h"
#endif
