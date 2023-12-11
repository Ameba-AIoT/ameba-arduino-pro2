/**
 * \file sha512.h
 * \brief This file contains SHA-384 and SHA-512 definitions and functions.
 *
 * The Secure Hash Algorithms 384 and 512 (SHA-384 and SHA-512) cryptographic
 * hash functions are defined in <em>FIPS 180-4: Secure Hash Standard (SHS)</em>.
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#ifndef ROM_HOMEKIT_SHA512_H
#define ROM_HOMEKIT_SHA512_H

#include <string.h>

#if defined(_MSC_VER) || defined(__WATCOMC__)
#define UL64(x) x##ui64
typedef unsigned __int64 uint64_t;
#else
#include <inttypes.h>
#define UL64(x) x##ULL
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          SHA-512 context structure
 */
typedef struct {
	uint64_t total[2];          /*!< number of bytes processed  */
	uint64_t state[8];          /*!< intermediate digest state  */
	unsigned char buffer[128];  /*!< data block being processed */

	unsigned char ipad[128];    /*!< HMAC: inner padding        */
	unsigned char opad[128];    /*!< HMAC: outer padding        */
	int is384;                  /*!< 0 => SHA-512, else SHA-384 */
}
sha512_context;

/**
 * \brief          SHA-512 context setup
 *
 * \param ctx      context to be initialized
 * \param is384    0 = use SHA512, 1 = use SHA384
 */
void rom_sha512_starts(sha512_context *ctx, int is384);

/**
 * \brief          SHA-512 process buffer
 *
 * \param ctx      SHA-512 context
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 */
void rom_sha512_update(sha512_context *ctx, const unsigned char *input, size_t ilen);

/**
 * \brief          SHA-512 final digest
 *
 * \param ctx      SHA-512 context
 * \param output   SHA-384/512 checksum result
 */
void rom_sha512_finish(sha512_context *ctx, unsigned char output[64]);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          Output = SHA-512( input buffer )
 *
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 * \param output   SHA-384/512 checksum result
 * \param is384    0 = use SHA512, 1 = use SHA384
 */
void rom_sha512(const unsigned char *input, size_t ilen,
				unsigned char output[64], int is384);

/**
 * \brief          SHA-512 HMAC context setup
 *
 * \param ctx      HMAC context to be initialized
 * \param is384    0 = use SHA512, 1 = use SHA384
 * \param key      HMAC secret key
 * \param keylen   length of the HMAC key
 */
void rom_sha512_hmac_starts(sha512_context *ctx, const unsigned char *key,
							size_t keylen, int is384);

/**
 * \brief          SHA-512 HMAC process buffer
 *
 * \param ctx      HMAC context
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 */
void rom_sha512_hmac_update(sha512_context *ctx, const unsigned char *input, size_t ilen);

/**
 * \brief          SHA-512 HMAC final digest
 *
 * \param ctx      HMAC context
 * \param output   SHA-384/512 HMAC checksum result
 */
void rom_sha512_hmac_finish(sha512_context *ctx, unsigned char output[64]);

/**
 * \brief          SHA-512 HMAC context reset
 *
 * \param ctx      HMAC context to be reset
 */
void rom_sha512_hmac_reset(sha512_context *ctx);

/**
 * \brief          Output = HMAC-SHA-512( hmac key, input buffer )
 *
 * \param key      HMAC secret key
 * \param keylen   length of the HMAC key
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 * \param output   HMAC-SHA-384/512 result
 * \param is384    0 = use SHA512, 1 = use SHA384
 */
void rom_sha512_hmac(const unsigned char *key, size_t keylen,
					 const unsigned char *input, size_t ilen,
					 unsigned char output[64], int is384);

/*
 * HKDF-SHA-512
 */
#define SHA512_DIGEST_SIZE    64

int rom_sha512_hkdf(const unsigned char *ikm, size_t ikm_len,
					const unsigned char *salt, size_t salt_len,
					const unsigned char *info, size_t info_len,
					unsigned char *okm, size_t okm_len);

#ifdef __cplusplus
}
#endif

#endif /* ROM_HOMEKIT_SHA512_H */
