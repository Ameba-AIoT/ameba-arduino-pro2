#ifndef ROM_APPLE_FUNC_STUBS_H
#define ROM_APPLE_FUNC_STUBS_H

#include <ed25519/rom_homekit_ed25519.h>
#include <sha512/rom_homekit_sha512.h>
#include <Curve25519/rom_wac_curve25519-donna.h>

typedef struct apple_func_stubs_s {
	// ed25519
	int (*rom_ed25519_gen_keypair)(unsigned char pk[ED25519_PUBKEY_LEN], unsigned char skpk[ED25519_SKEY_LEN + ED25519_PUBKEY_LEN],
								   unsigned char seed[ED25519_SKEY_LEN]);
	int (*rom_ed25519_gen_signature)(unsigned char sig[ED25519_SIG_SIZE], const unsigned char *m, unsigned long long mlen,
									 const unsigned char skpk[ED25519_SKEY_LEN + ED25519_PUBKEY_LEN]);
	int (*rom_ed25519_verify_signature)(const unsigned char sig[ED25519_SIG_SIZE], const unsigned char *m, unsigned long long mlen,
										const unsigned char pk[ED25519_PUBKEY_LEN]);
	// sha512
	void (*rom_sha512_starts)(sha512_context *ctx, int is384);
	void (*rom_sha512_update)(sha512_context *ctx, const unsigned char *input, size_t ilen);
	void (*rom_sha512_finish)(sha512_context *ctx, unsigned char output[64]);
	void (*rom_sha512)(const unsigned char *input, size_t ilen, unsigned char output[64], int is384);
	void (*rom_sha512_hmac_starts)(sha512_context *ctx, const unsigned char *key, size_t keylen, int is384);
	void (*rom_sha512_hmac_update)(sha512_context *ctx, const unsigned char *input, size_t ilen);
	void (*rom_sha512_hmac_finish)(sha512_context *ctx, unsigned char output[64]);
	void (*rom_sha512_hmac_reset)(sha512_context *ctx);
	void (*rom_sha512_hmac)(const unsigned char *key, size_t keylen, const unsigned char *input, size_t ilen, unsigned char output[64], int is384);
	int (*rom_sha512_hkdf)(const unsigned char *ikm, size_t ikm_len, const unsigned char *salt, size_t salt_len, const unsigned char *info, size_t info_len,
						   unsigned char *okm, size_t okm_len);
	// curve25519
	void (*curve25519_donna)(unsigned char *outKey, const unsigned char *inSecret, const unsigned char *inBasePoint);
} apple_func_stubs_t;

#endif // ROM_APPLE_FUNC_STUBS_H
