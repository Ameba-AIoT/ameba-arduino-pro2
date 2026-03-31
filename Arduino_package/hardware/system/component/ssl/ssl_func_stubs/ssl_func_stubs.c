#if defined(CONFIG_PLATFORM_8735B)
#include <stdlib.h>
__attribute__((constructor))
static void init_mbedtls_platform(void)
{
	crypto_init();
	platform_set_malloc_free(calloc, free);
}
#endif

#include "rom/rom_ssl_func_stubs.h"
#if defined(CONFIG_PLATFORM_8710C) || defined(CONFIG_PLATFORM_8735B)
#include "crypto_api.h"
#else
#include "hal_crypto.h"
#endif

#include "mbedtls/version.h"

extern const ssl_func_stubs_t __rom_stubs_ssl;

/* ssl_ram_map */
void init_rom_ssl_ram_map(
	void *(*ssl_calloc)(unsigned int, unsigned int),
	void (*ssl_free)(void *),
	int (*ssl_printf)(const char *, ...),
	u32 use_hw_crypto_func
)
{
	__rom_stubs_ssl.init_rom_ssl_ram_map(ssl_calloc, ssl_free, ssl_printf, use_hw_crypto_func);
}

void init_rom_ssl_hw_crypto_aes_ecb(
	int (*hw_crypto_aes_ecb_init)(const u8 *, const u32),
	int (*hw_crypto_aes_ecb_decrypt)(const u8 *, const u32, const u8 *, const u32, u8 *),
	int (*hw_crypto_aes_ecb_encrypt)(const u8 *, const u32, const u8 *, const u32, u8 *)
)
{
	__rom_stubs_ssl.init_rom_ssl_hw_crypto_aes_ecb(hw_crypto_aes_ecb_init, hw_crypto_aes_ecb_decrypt, hw_crypto_aes_ecb_encrypt);
}

void init_rom_ssl_hw_crypto_aes_cbc(
	int (*hw_crypto_aes_cbc_init)(const u8 *, const u32),
	int (*hw_crypto_aes_cbc_decrypt)(const u8 *, const u32, const u8 *, const u32, u8 *),
	int (*hw_crypto_aes_cbc_encrypt)(const u8 *, const u32, const u8 *, const u32, u8 *)
)
{
	__rom_stubs_ssl.init_rom_ssl_hw_crypto_aes_cbc(hw_crypto_aes_cbc_init, hw_crypto_aes_cbc_decrypt, hw_crypto_aes_cbc_encrypt);
}

void init_rom_ssl_hw_crypto_des_cbc(
	int (*hw_crypto_des_cbc_init)(const u8 *, const u32),
	int (*hw_crypto_des_cbc_decrypt)(const u8 *, const u32, const u8 *, const u32, u8 *),
	int (*hw_crypto_des_cbc_encrypt)(const u8 *, const u32, const u8 *, const u32, u8 *)
)
{
	__rom_stubs_ssl.init_rom_ssl_hw_crypto_des_cbc(hw_crypto_des_cbc_init, hw_crypto_des_cbc_decrypt, hw_crypto_des_cbc_encrypt);
}

void init_rom_ssl_hw_crypto_3des_cbc(
	int (*hw_crypto_3des_cbc_init)(const u8 *, const u32),
	int (*hw_crypto_3des_cbc_decrypt)(const u8 *, const u32, const u8 *, const u32, u8 *),
	int (*hw_crypto_3des_cbc_encrypt)(const u8 *, const u32, const u8 *, const u32, u8 *)
)
{
	__rom_stubs_ssl.init_rom_ssl_hw_crypto_3des_cbc(hw_crypto_3des_cbc_init, hw_crypto_3des_cbc_decrypt, hw_crypto_3des_cbc_encrypt);
}

#include "rom_ssl_ram_map.h"
extern struct _rom_ssl_ram_map rom_ssl_ram_map;

int platform_set_malloc_free(
	void *(*ssl_calloc)(unsigned int, unsigned int),
	void (*ssl_free)(void *)
)
{
	/* Variables */
	rom_ssl_ram_map.use_hw_crypto_func = 1;

	init_rom_ssl_ram_map(ssl_calloc, ssl_free, NULL, rom_ssl_ram_map.use_hw_crypto_func);
	init_rom_ssl_hw_crypto_aes_ecb(rtl_crypto_aes_ecb_init, rtl_crypto_aes_ecb_decrypt, rtl_crypto_aes_ecb_encrypt);
	init_rom_ssl_hw_crypto_aes_cbc(rtl_crypto_aes_cbc_init, rtl_crypto_aes_cbc_decrypt, rtl_crypto_aes_cbc_encrypt);
#if defined(CONFIG_PLATFORM_8710C) || defined(CONFIG_PLATFORM_8735B)
	/// DES funtions are on longer supported on AmebaZ2's HW crypto
	/// Must set them to NULL, so it will use SW instead of HW even use_hw_crypto_func is enabled
	init_rom_ssl_hw_crypto_des_cbc(NULL, NULL, NULL);
	init_rom_ssl_hw_crypto_3des_cbc(NULL, NULL, NULL);
#else
	init_rom_ssl_hw_crypto_des_cbc(rtl_crypto_des_cbc_init, rtl_crypto_des_cbc_decrypt, rtl_crypto_des_cbc_encrypt);
	init_rom_ssl_hw_crypto_3des_cbc(rtl_crypto_3des_cbc_init, rtl_crypto_3des_cbc_decrypt, rtl_crypto_3des_cbc_encrypt);
#endif
	return 0;
}

/* bignum */
void mbedtls_mpi_init(mbedtls_mpi *X)
{
	__rom_stubs_ssl.mbedtls_mpi_init(X);
}

void mbedtls_mpi_free(mbedtls_mpi *X)
{
	__rom_stubs_ssl.mbedtls_mpi_free(X);
}

int mbedtls_mpi_grow(mbedtls_mpi *X, size_t nblimbs)
{
	return __rom_stubs_ssl.mbedtls_mpi_grow(X, nblimbs);
}

int mbedtls_mpi_shrink(mbedtls_mpi *X, size_t nblimbs)
{
	return __rom_stubs_ssl.mbedtls_mpi_shrink(X, nblimbs);
}

int mbedtls_mpi_copy(mbedtls_mpi *X, const mbedtls_mpi *Y)
{
	return __rom_stubs_ssl.mbedtls_mpi_copy(X, Y);
}

void mbedtls_mpi_swap(mbedtls_mpi *X, mbedtls_mpi *Y)
{
	__rom_stubs_ssl.mbedtls_mpi_swap(X, Y);
}

int mbedtls_mpi_safe_cond_assign(mbedtls_mpi *X, const mbedtls_mpi *Y, unsigned char assign)
{
	return __rom_stubs_ssl.mbedtls_mpi_safe_cond_assign(X, Y, assign);
}

int mbedtls_mpi_safe_cond_swap(mbedtls_mpi *X, mbedtls_mpi *Y, unsigned char swap)
{
	return __rom_stubs_ssl.mbedtls_mpi_safe_cond_swap(X, Y, swap);
}

int mbedtls_mpi_lset(mbedtls_mpi *X, mbedtls_mpi_sint z)
{
	return __rom_stubs_ssl.mbedtls_mpi_lset(X, z);
}

int mbedtls_mpi_get_bit(const mbedtls_mpi *X, size_t pos)
{
	return __rom_stubs_ssl.mbedtls_mpi_get_bit(X, pos);
}

int mbedtls_mpi_set_bit(mbedtls_mpi *X, size_t pos, unsigned char val)
{
	return __rom_stubs_ssl.mbedtls_mpi_set_bit(X, pos, val);
}

size_t mbedtls_mpi_lsb(const mbedtls_mpi *X)
{
	return __rom_stubs_ssl.mbedtls_mpi_lsb(X);
}

size_t mbedtls_mpi_bitlen(const mbedtls_mpi *X)
{
	return __rom_stubs_ssl.mbedtls_mpi_bitlen(X);
}

size_t mbedtls_mpi_size(const mbedtls_mpi *X)
{
	return __rom_stubs_ssl.mbedtls_mpi_size(X);
}

int mbedtls_mpi_read_binary(mbedtls_mpi *X, const unsigned char *buf, size_t buflen)
{
	return __rom_stubs_ssl.mbedtls_mpi_read_binary(X, buf, buflen);
}

int mbedtls_mpi_write_binary(const mbedtls_mpi *X, unsigned char *buf, size_t buflen)
{
	return __rom_stubs_ssl.mbedtls_mpi_write_binary(X, buf, buflen);
}

int mbedtls_mpi_shift_l(mbedtls_mpi *X, size_t count)
{
	return __rom_stubs_ssl.mbedtls_mpi_shift_l(X, count);
}

int mbedtls_mpi_shift_r(mbedtls_mpi *X, size_t count)
{
	return __rom_stubs_ssl.mbedtls_mpi_shift_r(X, count);
}

int mbedtls_mpi_cmp_abs(const mbedtls_mpi *X, const mbedtls_mpi *Y)
{
	return __rom_stubs_ssl.mbedtls_mpi_cmp_abs(X, Y);
}

int mbedtls_mpi_cmp_mpi(const mbedtls_mpi *X, const mbedtls_mpi *Y)
{
	return __rom_stubs_ssl.mbedtls_mpi_cmp_mpi(X, Y);
}

int mbedtls_mpi_cmp_int(const mbedtls_mpi *X, mbedtls_mpi_sint z)
{
	return __rom_stubs_ssl.mbedtls_mpi_cmp_int(X, z);
}

int mbedtls_mpi_add_abs(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B)
{
	return __rom_stubs_ssl.mbedtls_mpi_add_abs(X, A, B);
}

int mbedtls_mpi_sub_abs(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B)
{
	return __rom_stubs_ssl.mbedtls_mpi_sub_abs(X, A, B);
}

int mbedtls_mpi_add_mpi(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B)
{
	return __rom_stubs_ssl.mbedtls_mpi_add_mpi(X, A, B);
}

int mbedtls_mpi_sub_mpi(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B)
{
	return __rom_stubs_ssl.mbedtls_mpi_sub_mpi(X, A, B);
}

int mbedtls_mpi_add_int(mbedtls_mpi *X, const mbedtls_mpi *A, mbedtls_mpi_sint b)
{
	return __rom_stubs_ssl.mbedtls_mpi_add_int(X, A, b);
}

int mbedtls_mpi_sub_int(mbedtls_mpi *X, const mbedtls_mpi *A, mbedtls_mpi_sint b)
{
	return __rom_stubs_ssl.mbedtls_mpi_sub_int(X, A, b);
}

int mbedtls_mpi_mul_mpi(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B)
{
	return __rom_stubs_ssl.mbedtls_mpi_mul_mpi(X, A, B);
}

int mbedtls_mpi_read_string(mbedtls_mpi *X, int radix, const char *s)
{
	return __rom_stubs_ssl.mbedtls_mpi_read_string(X, radix, s);
}

int mbedtls_mpi_mul_int(mbedtls_mpi *X, const mbedtls_mpi *A, mbedtls_mpi_uint b)
{
	return __rom_stubs_ssl.mbedtls_mpi_mul_int(X, A, b);
}

int mbedtls_mpi_div_mpi(mbedtls_mpi *Q, mbedtls_mpi *R, const mbedtls_mpi *A, const mbedtls_mpi *B)
{
	return __rom_stubs_ssl.mbedtls_mpi_div_mpi(Q, R, A, B);
}

int mbedtls_mpi_div_int(mbedtls_mpi *Q, mbedtls_mpi *R, const mbedtls_mpi *A, mbedtls_mpi_sint b)
{
	return __rom_stubs_ssl.mbedtls_mpi_div_int(Q, R, A, b);
}

int mbedtls_mpi_mod_mpi(mbedtls_mpi *R, const mbedtls_mpi *A, const mbedtls_mpi *B)
{
	return __rom_stubs_ssl.mbedtls_mpi_mod_mpi(R, A, B);
}

int mbedtls_mpi_mod_int(mbedtls_mpi_uint *r, const mbedtls_mpi *A, mbedtls_mpi_sint b)
{
	return __rom_stubs_ssl.mbedtls_mpi_mod_int(r, A, b);
}

int mbedtls_mpi_write_string(const mbedtls_mpi *X, int radix, char *buf, size_t buflen, size_t *olen)
{
	return __rom_stubs_ssl.mbedtls_mpi_write_string(X, radix, buf, buflen, olen);
}

int mbedtls_mpi_exp_mod(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *E, const mbedtls_mpi *N, mbedtls_mpi *_RR)
{
	return __rom_stubs_ssl.mbedtls_mpi_exp_mod(X, A, E, N, _RR);
}

int mbedtls_mpi_gcd(mbedtls_mpi *G, const mbedtls_mpi *A, const mbedtls_mpi *B)
{
	return __rom_stubs_ssl.mbedtls_mpi_gcd(G, A, B);
}

int mbedtls_mpi_fill_random(mbedtls_mpi *X, size_t size, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_mpi_fill_random(X, size, f_rng, p_rng);
}

int mbedtls_mpi_inv_mod(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *N)
{
	return __rom_stubs_ssl.mbedtls_mpi_inv_mod(X, A, N);
}

int mbedtls_mpi_is_prime(const mbedtls_mpi *X, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_mpi_is_prime(X, f_rng, p_rng);
}

int mbedtls_mpi_gen_prime(mbedtls_mpi *X, size_t nbits, int dh_flag, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_mpi_gen_prime(X, nbits, dh_flag, f_rng, p_rng);
}

#if !(defined(CONFIG_PLATFORM_8735B) && (MBEDTLS_VERSION_NUMBER>=0x03000000 || MBEDTLS_VERSION_NUMBER==0x02100600 || MBEDTLS_VERSION_NUMBER==0x021C0100))

#if !(defined(CONFIG_PLATFORM_8710C) && defined(CONFIG_BUILD_SECURE) && (CONFIG_BUILD_SECURE == 1))
/* ecp */
const mbedtls_ecp_curve_info *mbedtls_ecp_curve_list(void)
{
	return __rom_stubs_ssl.mbedtls_ecp_curve_list();
}

const mbedtls_ecp_curve_info *mbedtls_ecp_curve_info_from_grp_id(mbedtls_ecp_group_id grp_id)
{
	return __rom_stubs_ssl.mbedtls_ecp_curve_info_from_grp_id(grp_id);
}

const mbedtls_ecp_curve_info *mbedtls_ecp_curve_info_from_tls_id(uint16_t tls_id)
{
	return __rom_stubs_ssl.mbedtls_ecp_curve_info_from_tls_id(tls_id);
}

const mbedtls_ecp_curve_info *mbedtls_ecp_curve_info_from_name(const char *name)
{
	return __rom_stubs_ssl.mbedtls_ecp_curve_info_from_name(name);
}

void mbedtls_ecp_point_init(mbedtls_ecp_point *pt)
{
	__rom_stubs_ssl.mbedtls_ecp_point_init(pt);
}

void mbedtls_ecp_group_init(mbedtls_ecp_group *grp)
{
	__rom_stubs_ssl.mbedtls_ecp_group_init(grp);
}

void mbedtls_ecp_keypair_init(mbedtls_ecp_keypair *key)
{
	__rom_stubs_ssl.mbedtls_ecp_keypair_init(key);
}

void mbedtls_ecp_point_free(mbedtls_ecp_point *pt)
{
	__rom_stubs_ssl.mbedtls_ecp_point_free(pt);
}

void mbedtls_ecp_group_free(mbedtls_ecp_group *grp)
{
	__rom_stubs_ssl.mbedtls_ecp_group_free(grp);
}

void mbedtls_ecp_keypair_free(mbedtls_ecp_keypair *key)
{
	__rom_stubs_ssl.mbedtls_ecp_keypair_free(key);
}

int mbedtls_ecp_copy(mbedtls_ecp_point *P, const mbedtls_ecp_point *Q)
{
	return __rom_stubs_ssl.mbedtls_ecp_copy(P, Q);
}

int mbedtls_ecp_group_copy(mbedtls_ecp_group *dst, const mbedtls_ecp_group *src)
{
	return __rom_stubs_ssl.mbedtls_ecp_group_copy(dst, src);
}

int mbedtls_ecp_set_zero(mbedtls_ecp_point *pt)
{
	return __rom_stubs_ssl.mbedtls_ecp_set_zero(pt);
}

int mbedtls_ecp_is_zero(mbedtls_ecp_point *pt)
{
	return __rom_stubs_ssl.mbedtls_ecp_is_zero(pt);
}

int mbedtls_ecp_point_cmp(const mbedtls_ecp_point *P, const mbedtls_ecp_point *Q)
{
	return __rom_stubs_ssl.mbedtls_ecp_point_cmp(P, Q);
}

int mbedtls_ecp_point_read_string(mbedtls_ecp_point *P, int radix, const char *x, const char *y)
{
	return __rom_stubs_ssl.mbedtls_ecp_point_read_string(P, radix, x, y);
}

int mbedtls_ecp_point_write_binary(const mbedtls_ecp_group *grp, const mbedtls_ecp_point *P, int format, size_t *olen, unsigned char *buf, size_t buflen)
{
	return __rom_stubs_ssl.mbedtls_ecp_point_write_binary(grp, P, format, olen, buf, buflen);
}

int mbedtls_ecp_point_read_binary(const mbedtls_ecp_group *grp, mbedtls_ecp_point *pt, const unsigned char *buf, size_t ilen)
{
	return __rom_stubs_ssl.mbedtls_ecp_point_read_binary(grp, pt, buf, ilen);
}

int mbedtls_ecp_tls_read_point(const mbedtls_ecp_group *grp, mbedtls_ecp_point *pt, const unsigned char **buf, size_t buf_len)
{
	return __rom_stubs_ssl.mbedtls_ecp_tls_read_point(grp, pt, buf, buf_len);
}

int mbedtls_ecp_tls_write_point(const mbedtls_ecp_group *grp, const mbedtls_ecp_point *pt, int format, size_t *olen, unsigned char *buf, size_t blen)
{
	return __rom_stubs_ssl.mbedtls_ecp_tls_write_point(grp, pt, format, olen, buf, blen);
}

int mbedtls_ecp_tls_read_group(mbedtls_ecp_group *grp, const unsigned char **buf, size_t len)
{
	return __rom_stubs_ssl.mbedtls_ecp_tls_read_group(grp, buf, len);
}

int mbedtls_ecp_tls_write_group(const mbedtls_ecp_group *grp, size_t *olen, unsigned char *buf, size_t blen)
{
	return __rom_stubs_ssl.mbedtls_ecp_tls_write_group(grp, olen, buf, blen);
}

int mbedtls_ecp_check_pubkey(const mbedtls_ecp_group *grp, const mbedtls_ecp_point *pt)
{
	return __rom_stubs_ssl.mbedtls_ecp_check_pubkey(grp, pt);
}

int mbedtls_ecp_check_privkey(const mbedtls_ecp_group *grp, const mbedtls_mpi *d)
{
	return __rom_stubs_ssl.mbedtls_ecp_check_privkey(grp, d);
}

int mbedtls_ecp_mul(mbedtls_ecp_group *grp, mbedtls_ecp_point *R, const mbedtls_mpi *m, const mbedtls_ecp_point *P, int (*f_rng)(void *, unsigned char *,
					size_t), void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_ecp_mul(grp, R, m, P, f_rng, p_rng);
}

int mbedtls_ecp_muladd(mbedtls_ecp_group *grp, mbedtls_ecp_point *R, const mbedtls_mpi *m, const mbedtls_ecp_point *P, const mbedtls_mpi *n,
					   const mbedtls_ecp_point *Q)
{
	return __rom_stubs_ssl.mbedtls_ecp_muladd(grp, R, m, P, n, Q);
}

int mbedtls_ecp_gen_keypair_base(mbedtls_ecp_group *grp, const mbedtls_ecp_point *G, mbedtls_mpi *d, mbedtls_ecp_point *Q, int (*f_rng)(void *, unsigned char *,
								 size_t), void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_ecp_gen_keypair_base(grp, G, d, Q, f_rng, p_rng);
}

int mbedtls_ecp_gen_keypair(mbedtls_ecp_group *grp, mbedtls_mpi *d, mbedtls_ecp_point *Q, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_ecp_gen_keypair(grp, d, Q, f_rng, p_rng);
}

int mbedtls_ecp_gen_key(mbedtls_ecp_group_id grp_id, mbedtls_ecp_keypair *key, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_ecp_gen_key(grp_id, key, f_rng, p_rng);
}

int mbedtls_ecp_check_pub_priv(const mbedtls_ecp_keypair *pub, const mbedtls_ecp_keypair *prv)
{
	return __rom_stubs_ssl.mbedtls_ecp_check_pub_priv(pub, prv);
}

/*
 * List of supported curves, group ID only
 */
#define ECP_NB_CURVES 12
static mbedtls_ecp_group_id ecp_supported_grp_id[ECP_NB_CURVES];
const mbedtls_ecp_group_id *mbedtls_ecp_grp_id_list(void)
{
	static int init_done = 0;

	if (! init_done) {
		size_t i = 0;
		const mbedtls_ecp_curve_info *curve_info;

		for (curve_info = mbedtls_ecp_curve_list();
			 curve_info->grp_id != MBEDTLS_ECP_DP_NONE;
			 curve_info++) {
			ecp_supported_grp_id[i++] = curve_info->grp_id;
		}
		ecp_supported_grp_id[i] = MBEDTLS_ECP_DP_NONE;

		init_done = 1;
	}

	return (ecp_supported_grp_id);
}

/* ecp_curves */
int mbedtls_ecp_group_load(mbedtls_ecp_group *grp, mbedtls_ecp_group_id id)
{
	return __rom_stubs_ssl.mbedtls_ecp_group_load(grp, id);
}
#endif /* !(defined(CONFIG_PLATFORM_8710C) && defined(CONFIG_BUILD_SECURE) && (CONFIG_BUILD_SECURE == 1)) */

#if !((defined(CONFIG_PLATFORM_8710C) || defined(CONFIG_PLATFORM_8735B)) && defined(CONFIG_BUILD_SECURE) && (CONFIG_BUILD_SECURE == 1))
/* sha1 */
void mbedtls_sha1_init(mbedtls_sha1_context *ctx)
{
	__rom_stubs_ssl.mbedtls_sha1_init(ctx);
}

void mbedtls_sha1_free(mbedtls_sha1_context *ctx)
{
	__rom_stubs_ssl.mbedtls_sha1_free(ctx);
}

void mbedtls_sha1_clone(mbedtls_sha1_context *dst, const mbedtls_sha1_context *src)
{
	__rom_stubs_ssl.mbedtls_sha1_clone(dst, src);
}

void mbedtls_sha1_starts(mbedtls_sha1_context *ctx)
{
	__rom_stubs_ssl.mbedtls_sha1_starts(ctx);
}

void mbedtls_sha1_process(mbedtls_sha1_context *ctx, const unsigned char data[64])
{
	__rom_stubs_ssl.mbedtls_sha1_process(ctx, data);
}

void mbedtls_sha1_update(mbedtls_sha1_context *ctx, const unsigned char *input, size_t ilen)
{
	__rom_stubs_ssl.mbedtls_sha1_update(ctx, input, ilen);
}

void mbedtls_sha1_finish(mbedtls_sha1_context *ctx, unsigned char output[20])
{
	__rom_stubs_ssl.mbedtls_sha1_finish(ctx, output);
}

void mbedtls_sha1(const unsigned char *input, size_t ilen, unsigned char output[20])
{
	__rom_stubs_ssl.mbedtls_sha1(input, ilen, output);
}
#if !defined(SUPPORT_HW_SSL_HMAC_SHA256)
/* sha256 */
void mbedtls_sha256_init(mbedtls_sha256_context *ctx)
{
	__rom_stubs_ssl.mbedtls_sha256_init(ctx);
}

void mbedtls_sha256_free(mbedtls_sha256_context *ctx)
{
	__rom_stubs_ssl.mbedtls_sha256_free(ctx);
}

void mbedtls_sha256_clone(mbedtls_sha256_context *dst, const mbedtls_sha256_context *src)
{
	__rom_stubs_ssl.mbedtls_sha256_clone(dst, src);
}

void mbedtls_sha256_starts(mbedtls_sha256_context *ctx, int is224)
{
	__rom_stubs_ssl.mbedtls_sha256_starts(ctx, is224);
}
#if defined(ENABLE_AMAZON_COMMON)
void mbedtls_sha256_starts_ret(mbedtls_sha256_context *ctx, int is224)
{
	__rom_stubs_ssl.mbedtls_sha256_starts(ctx, is224);
}
#endif

void mbedtls_sha256_process(mbedtls_sha256_context *ctx, const unsigned char data[64])
{
	__rom_stubs_ssl.mbedtls_sha256_process(ctx, data);
}

void mbedtls_sha256_update(mbedtls_sha256_context *ctx, const unsigned char *input, size_t ilen)
{
	__rom_stubs_ssl.mbedtls_sha256_update(ctx, input, ilen);
}
#if defined(ENABLE_AMAZON_COMMON)
void mbedtls_sha256_update_ret(mbedtls_sha256_context *ctx, const unsigned char *input, size_t ilen)
{
	__rom_stubs_ssl.mbedtls_sha256_update(ctx, input, ilen);
}
#endif

void mbedtls_sha256_finish(mbedtls_sha256_context *ctx, unsigned char output[32])
{
	__rom_stubs_ssl.mbedtls_sha256_finish(ctx, output);
}
#if defined(ENABLE_AMAZON_COMMON)
void mbedtls_sha256_finish_ret(mbedtls_sha256_context *ctx, unsigned char output[32])
{
	__rom_stubs_ssl.mbedtls_sha256_finish(ctx, output);
}
#endif

void mbedtls_sha256(const unsigned char *input, size_t ilen, unsigned char output[32], int is224)
{
	__rom_stubs_ssl.mbedtls_sha256(input, ilen, output, is224);
}

#if defined(ENABLE_AMAZON_COMMON)
void mbedtls_sha256_ret(const unsigned char *input, size_t ilen, unsigned char output[32], int is224)
{
	__rom_stubs_ssl.mbedtls_sha256(input, ilen, output, is224);
}
#endif
#endif /* SUPPORT_HW_SSL_HMAC_SHA256 */
/* sha512 */
void mbedtls_sha512_init(mbedtls_sha512_context *ctx)
{
	__rom_stubs_ssl.mbedtls_sha512_init(ctx);
}

void mbedtls_sha512_free(mbedtls_sha512_context *ctx)
{
	__rom_stubs_ssl.mbedtls_sha512_free(ctx);
}

void mbedtls_sha512_clone(mbedtls_sha512_context *dst, const mbedtls_sha512_context *src)
{
	__rom_stubs_ssl.mbedtls_sha512_clone(dst, src);
}

void mbedtls_sha512_starts(mbedtls_sha512_context *ctx, int is384)
{
	__rom_stubs_ssl.mbedtls_sha512_starts(ctx, is384);
}

void mbedtls_sha512_process(mbedtls_sha512_context *ctx, const unsigned char data[128])
{
	__rom_stubs_ssl.mbedtls_sha512_process(ctx, data);
}

void mbedtls_sha512_update(mbedtls_sha512_context *ctx, const unsigned char *input, size_t ilen)
{
	__rom_stubs_ssl.mbedtls_sha512_update(ctx, input, ilen);
}

void mbedtls_sha512_finish(mbedtls_sha512_context *ctx, unsigned char output[64])
{
	__rom_stubs_ssl.mbedtls_sha512_finish(ctx, output);
}

void mbedtls_sha512(const unsigned char *input, size_t ilen, unsigned char output[64], int is384)
{
	__rom_stubs_ssl.mbedtls_sha512(input, ilen, output, is384);
}

/* oid */
int mbedtls_oid_get_attr_short_name(const mbedtls_asn1_buf *oid, const char **short_name)
{
	return __rom_stubs_ssl.mbedtls_oid_get_attr_short_name(oid, short_name);
}

int mbedtls_oid_get_x509_ext_type(const mbedtls_asn1_buf *oid, int *ext_type)
{
	return __rom_stubs_ssl.mbedtls_oid_get_x509_ext_type(oid, ext_type);
}

int mbedtls_oid_get_extended_key_usage(const mbedtls_asn1_buf *oid, const char **description)
{
	return __rom_stubs_ssl.mbedtls_oid_get_extended_key_usage(oid, description);
}

int mbedtls_oid_get_sig_alg_desc(const mbedtls_asn1_buf *oid, const char **description)
{
	return __rom_stubs_ssl.mbedtls_oid_get_sig_alg_desc(oid, description);
}

int mbedtls_oid_get_sig_alg(const mbedtls_asn1_buf *oid, mbedtls_md_type_t *md_alg, mbedtls_pk_type_t *pk_alg)
{
	return __rom_stubs_ssl.mbedtls_oid_get_sig_alg(oid, md_alg, pk_alg);
}

int mbedtls_oid_get_oid_by_sig_alg(mbedtls_pk_type_t pk_alg, mbedtls_md_type_t md_alg, const char **oid, size_t *olen)
{
	return __rom_stubs_ssl.mbedtls_oid_get_oid_by_sig_alg(pk_alg, md_alg, oid, olen);
}

int mbedtls_oid_get_pk_alg(const mbedtls_asn1_buf *oid, mbedtls_pk_type_t *pk_alg)
{
	return __rom_stubs_ssl.mbedtls_oid_get_pk_alg(oid, pk_alg);
}

int mbedtls_oid_get_oid_by_pk_alg(mbedtls_pk_type_t pk_alg, const char **oid, size_t *olen)
{
	return __rom_stubs_ssl.mbedtls_oid_get_oid_by_pk_alg(pk_alg, oid, olen);
}

int mbedtls_oid_get_ec_grp(const mbedtls_asn1_buf *oid, mbedtls_ecp_group_id *grp_id)
{
	return __rom_stubs_ssl.mbedtls_oid_get_ec_grp(oid, grp_id);
}

int mbedtls_oid_get_oid_by_ec_grp(mbedtls_ecp_group_id grp_id, const char **oid, size_t *olen)
{
	return __rom_stubs_ssl.mbedtls_oid_get_oid_by_ec_grp(grp_id, oid, olen);
}

int mbedtls_oid_get_cipher_alg(const mbedtls_asn1_buf *oid, mbedtls_cipher_type_t *cipher_alg)
{
	return __rom_stubs_ssl.mbedtls_oid_get_cipher_alg(oid, cipher_alg);
}

int mbedtls_oid_get_md_alg(const mbedtls_asn1_buf *oid, mbedtls_md_type_t *md_alg)
{
	return __rom_stubs_ssl.mbedtls_oid_get_md_alg(oid, md_alg);
}

int mbedtls_oid_get_oid_by_md(mbedtls_md_type_t md_alg, const char **oid, size_t *olen)
{
	return __rom_stubs_ssl.mbedtls_oid_get_oid_by_md(md_alg, oid, olen);
}

int mbedtls_oid_get_pkcs12_pbe_alg(const mbedtls_asn1_buf *oid, mbedtls_md_type_t *md_alg, mbedtls_cipher_type_t *cipher_alg)
{
	return __rom_stubs_ssl.mbedtls_oid_get_pkcs12_pbe_alg(oid, md_alg, cipher_alg);
}

/* md5 */
void mbedtls_md5_init(mbedtls_md5_context *ctx)
{
	__rom_stubs_ssl.mbedtls_md5_init(ctx);
}

void mbedtls_md5_free(mbedtls_md5_context *ctx)
{
	__rom_stubs_ssl.mbedtls_md5_free(ctx);
}

void mbedtls_md5_clone(mbedtls_md5_context *dst, const mbedtls_md5_context *src)
{
	__rom_stubs_ssl.mbedtls_md5_clone(dst, src);
}

void mbedtls_md5_starts(mbedtls_md5_context *ctx)
{
	__rom_stubs_ssl.mbedtls_md5_starts(ctx);
}

void mbedtls_md5_process(mbedtls_md5_context *ctx, const unsigned char data[64])
{
	__rom_stubs_ssl.mbedtls_md5_process(ctx, data);
}

void mbedtls_md5_update(mbedtls_md5_context *ctx, const unsigned char *input, size_t ilen)
{
	__rom_stubs_ssl.mbedtls_md5_update(ctx, input, ilen);
}

void mbedtls_md5_finish(mbedtls_md5_context *ctx, unsigned char output[16])
{
	__rom_stubs_ssl.mbedtls_md5_finish(ctx, output);
}

void mbedtls_md5(const unsigned char *input, size_t ilen, unsigned char output[16])
{
	__rom_stubs_ssl.mbedtls_md5(input, ilen, output);
}

/* aes */
void mbedtls_aes_init(mbedtls_aes_context *ctx)
{
	__rom_stubs_ssl.mbedtls_aes_init(ctx);
}

void mbedtls_aes_free(mbedtls_aes_context *ctx)
{
	__rom_stubs_ssl.mbedtls_aes_free(ctx);
}

int mbedtls_aes_setkey_enc(mbedtls_aes_context *ctx, const unsigned char *key, unsigned int keybits)
{
	return __rom_stubs_ssl.mbedtls_aes_setkey_enc(ctx, key, keybits);
}

int mbedtls_aes_setkey_dec(mbedtls_aes_context *ctx, const unsigned char *key, unsigned int keybits)
{
	return __rom_stubs_ssl.mbedtls_aes_setkey_dec(ctx, key, keybits);
}

void mbedtls_aes_encrypt(mbedtls_aes_context *ctx, const unsigned char input[16], unsigned char output[16])
{
	__rom_stubs_ssl.mbedtls_aes_encrypt(ctx, input, output);
}

void mbedtls_aes_decrypt(mbedtls_aes_context *ctx, const unsigned char input[16], unsigned char output[16])
{
	__rom_stubs_ssl.mbedtls_aes_decrypt(ctx, input, output);
}

int mbedtls_aes_crypt_ecb(mbedtls_aes_context *ctx, int mode, const unsigned char input[16], unsigned char output[16])
{
	return __rom_stubs_ssl.mbedtls_aes_crypt_ecb(ctx, mode, input, output);
}

int mbedtls_aes_crypt_cbc(mbedtls_aes_context *ctx, int mode, size_t length, unsigned char iv[16], const unsigned char *input, unsigned char *output)
{
	return __rom_stubs_ssl.mbedtls_aes_crypt_cbc(ctx, mode, length, iv, input, output);
}

int mbedtls_aes_crypt_cfb128(mbedtls_aes_context *ctx, int mode, size_t length, size_t *iv_off, unsigned char iv[16], const unsigned char *input,
							 unsigned char *output)
{
	return __rom_stubs_ssl.mbedtls_aes_crypt_cfb128(ctx, mode, length, iv_off, iv, input, output);
}

int mbedtls_aes_crypt_cfb8(mbedtls_aes_context *ctx, int mode, size_t length, unsigned char iv[16], const unsigned char *input, unsigned char *output)
{
	return __rom_stubs_ssl.mbedtls_aes_crypt_cfb8(ctx, mode, length, iv, input, output);
}

int mbedtls_aes_crypt_ctr(mbedtls_aes_context *ctx, size_t length, size_t *nc_off, unsigned char nonce_counter[16], unsigned char stream_block[16],
						  const unsigned char *input, unsigned char *output)
{
	return __rom_stubs_ssl.mbedtls_aes_crypt_ctr(ctx, length, nc_off, nonce_counter, stream_block, input, output);
}

/* des */
void mbedtls_des_init(mbedtls_des_context *ctx)
{
	__rom_stubs_ssl.mbedtls_des_init(ctx);
}

void mbedtls_des_free(mbedtls_des_context *ctx)
{
	__rom_stubs_ssl.mbedtls_des_free(ctx);
}

void mbedtls_des3_init(mbedtls_des3_context *ctx)
{
	__rom_stubs_ssl.mbedtls_des3_init(ctx);
}

void mbedtls_des3_free(mbedtls_des3_context *ctx)
{
	__rom_stubs_ssl.mbedtls_des3_free(ctx);
}

void mbedtls_des_key_set_parity(unsigned char key[MBEDTLS_DES_KEY_SIZE])
{
	__rom_stubs_ssl.mbedtls_des_key_set_parity(key);
}

int mbedtls_des_key_check_key_parity(const unsigned char key[MBEDTLS_DES_KEY_SIZE])
{
	return __rom_stubs_ssl.mbedtls_des_key_check_key_parity(key);
}

int mbedtls_des_key_check_weak(const unsigned char key[MBEDTLS_DES_KEY_SIZE])
{
	return __rom_stubs_ssl.mbedtls_des_key_check_weak(key);
}

void mbedtls_des_setkey(uint32_t SK[32], const unsigned char key[MBEDTLS_DES_KEY_SIZE])
{
	__rom_stubs_ssl.mbedtls_des_setkey(SK, key);
}

int mbedtls_des_setkey_enc(mbedtls_des_context *ctx, const unsigned char key[MBEDTLS_DES_KEY_SIZE])
{
	return __rom_stubs_ssl.mbedtls_des_setkey_enc(ctx, key);
}

int mbedtls_des_setkey_dec(mbedtls_des_context *ctx, const unsigned char key[MBEDTLS_DES_KEY_SIZE])
{
	return __rom_stubs_ssl.mbedtls_des_setkey_dec(ctx, key);
}

int mbedtls_des3_set2key_enc(mbedtls_des3_context *ctx, const unsigned char key[MBEDTLS_DES_KEY_SIZE * 2])
{
	return __rom_stubs_ssl.mbedtls_des3_set2key_enc(ctx, key);
}

int mbedtls_des3_set2key_dec(mbedtls_des3_context *ctx, const unsigned char key[MBEDTLS_DES_KEY_SIZE * 2])
{
	return __rom_stubs_ssl.mbedtls_des3_set2key_dec(ctx, key);
}

int mbedtls_des3_set3key_enc(mbedtls_des3_context *ctx, const unsigned char key[MBEDTLS_DES_KEY_SIZE * 3])
{
	return __rom_stubs_ssl.mbedtls_des3_set3key_enc(ctx, key);
}

int mbedtls_des3_set3key_dec(mbedtls_des3_context *ctx, const unsigned char key[MBEDTLS_DES_KEY_SIZE * 3])
{
	return __rom_stubs_ssl.mbedtls_des3_set3key_dec(ctx, key);
}

int mbedtls_des_crypt_ecb(mbedtls_des_context *ctx, const unsigned char input[8], unsigned char output[8])
{
	return __rom_stubs_ssl.mbedtls_des_crypt_ecb(ctx, input, output);
}

int mbedtls_des_crypt_cbc(mbedtls_des_context *ctx, int mode, size_t length, unsigned char iv[8], const unsigned char *input, unsigned char *output)
{
	return __rom_stubs_ssl.mbedtls_des_crypt_cbc(ctx, mode, length, iv, input, output);
}

int mbedtls_des3_crypt_ecb(mbedtls_des3_context *ctx, const unsigned char input[8], unsigned char output[8])
{
	return __rom_stubs_ssl.mbedtls_des3_crypt_ecb(ctx, input, output);
}

int mbedtls_des3_crypt_cbc(mbedtls_des3_context *ctx, int mode, size_t length, unsigned char iv[8], const unsigned char *input, unsigned char *output)
{
	return __rom_stubs_ssl.mbedtls_des3_crypt_cbc(ctx, mode, length, iv, input, output);
}
#if !defined(SUPPORT_HW_SSL_HMAC_SHA256)
/* md */
const int *mbedtls_md_list(void)
{
	return __rom_stubs_ssl.mbedtls_md_list();
}

const mbedtls_md_info_t *mbedtls_md_info_from_string(const char *md_name)
{
	return __rom_stubs_ssl.mbedtls_md_info_from_string(md_name);
}

const mbedtls_md_info_t *mbedtls_md_info_from_type(mbedtls_md_type_t md_type)
{
	return __rom_stubs_ssl.mbedtls_md_info_from_type(md_type);
}

void mbedtls_md_init(mbedtls_md_context_t *ctx)
{
	__rom_stubs_ssl.mbedtls_md_init(ctx);
}

void mbedtls_md_free(mbedtls_md_context_t *ctx)
{
	__rom_stubs_ssl.mbedtls_md_free(ctx);
}

int mbedtls_md_clone(mbedtls_md_context_t *dst, const mbedtls_md_context_t *src)
{
	return __rom_stubs_ssl.mbedtls_md_clone(dst, src);
}

int mbedtls_md_setup(mbedtls_md_context_t *ctx, const mbedtls_md_info_t *md_info, int hmac)
{
	return __rom_stubs_ssl.mbedtls_md_setup(ctx, md_info, hmac);
}

int mbedtls_md_init_ctx(mbedtls_md_context_t *ctx, const mbedtls_md_info_t *md_info)
{
	return __rom_stubs_ssl.mbedtls_md_init_ctx(ctx, md_info);
}

int mbedtls_md_starts(mbedtls_md_context_t *ctx)
{
	return __rom_stubs_ssl.mbedtls_md_starts(ctx);
}

int mbedtls_md_update(mbedtls_md_context_t *ctx, const unsigned char *input, size_t ilen)
{
	return __rom_stubs_ssl.mbedtls_md_update(ctx, input, ilen);
}

int mbedtls_md_finish(mbedtls_md_context_t *ctx, unsigned char *output)
{
	return __rom_stubs_ssl.mbedtls_md_finish(ctx, output);
}

int mbedtls_md(const mbedtls_md_info_t *md_info, const unsigned char *input, size_t ilen, unsigned char *output)
{
	return __rom_stubs_ssl.mbedtls_md(md_info, input, ilen, output);
}

int mbedtls_md_hmac_starts(mbedtls_md_context_t *ctx, const unsigned char *key, size_t keylen)
{
	return __rom_stubs_ssl.mbedtls_md_hmac_starts(ctx, key, keylen);
}

int mbedtls_md_hmac_update(mbedtls_md_context_t *ctx, const unsigned char *input, size_t ilen)
{
	return __rom_stubs_ssl.mbedtls_md_hmac_update(ctx, input, ilen);
}

int mbedtls_md_hmac_finish(mbedtls_md_context_t *ctx, unsigned char *output)
{
	return __rom_stubs_ssl.mbedtls_md_hmac_finish(ctx, output);
}

int mbedtls_md_hmac_reset(mbedtls_md_context_t *ctx)
{
	return __rom_stubs_ssl.mbedtls_md_hmac_reset(ctx);
}

int mbedtls_md_hmac(const mbedtls_md_info_t *md_info, const unsigned char *key, size_t keylen, const unsigned char *input, size_t ilen, unsigned char *output)
{
	return __rom_stubs_ssl.mbedtls_md_hmac(md_info, key, keylen, input, ilen, output);
}

int mbedtls_md_process(mbedtls_md_context_t *ctx, const unsigned char *data)
{
	return __rom_stubs_ssl.mbedtls_md_process(ctx, data);
}

unsigned char mbedtls_md_get_size(const mbedtls_md_info_t *md_info)
{
	return __rom_stubs_ssl.mbedtls_md_get_size(md_info);
}

mbedtls_md_type_t mbedtls_md_get_type(const mbedtls_md_info_t *md_info)
{
	return __rom_stubs_ssl.mbedtls_md_get_type(md_info);
}

const char *mbedtls_md_get_name(const mbedtls_md_info_t *md_info)
{
	return __rom_stubs_ssl.mbedtls_md_get_name(md_info);
}
#endif /* SUPPORT_HW_SSL_HMAC_SHA256 */
/* asn1parse */
int mbedtls_asn1_get_len(unsigned char **p, const unsigned char *end, size_t *len)
{
	return __rom_stubs_ssl.mbedtls_asn1_get_len(p, end, len);
}

int mbedtls_asn1_get_tag(unsigned char **p, const unsigned char *end, size_t *len, int tag)
{
	return __rom_stubs_ssl.mbedtls_asn1_get_tag(p, end, len, tag);
}

int mbedtls_asn1_get_bool(unsigned char **p, const unsigned char *end, int *val)
{
	return __rom_stubs_ssl.mbedtls_asn1_get_bool(p, end, val);
}

int mbedtls_asn1_get_int(unsigned char **p, const unsigned char *end, int *val)
{
	return __rom_stubs_ssl.mbedtls_asn1_get_int(p, end, val);
}

int mbedtls_asn1_get_mpi(unsigned char **p, const unsigned char *end, mbedtls_mpi *X)
{
	return __rom_stubs_ssl.mbedtls_asn1_get_mpi(p, end, X);
}

int mbedtls_asn1_get_bitstring(unsigned char **p, const unsigned char *end, mbedtls_asn1_bitstring *bs)
{
	return __rom_stubs_ssl.mbedtls_asn1_get_bitstring(p, end, bs);
}

int mbedtls_asn1_get_bitstring_null(unsigned char **p, const unsigned char *end, size_t *len)
{
	return __rom_stubs_ssl.mbedtls_asn1_get_bitstring_null(p, end, len);
}

int mbedtls_asn1_get_sequence_of(unsigned char **p, const unsigned char *end, mbedtls_asn1_sequence *cur, int tag)
{
	return __rom_stubs_ssl.mbedtls_asn1_get_sequence_of(p, end, cur, tag);
}

int mbedtls_asn1_get_alg(unsigned char **p, const unsigned char *end, mbedtls_asn1_buf *alg, mbedtls_asn1_buf *params)
{
	return __rom_stubs_ssl.mbedtls_asn1_get_alg(p, end, alg, params);
}

int mbedtls_asn1_get_alg_null(unsigned char **p, const unsigned char *end, mbedtls_asn1_buf *alg)
{
	return __rom_stubs_ssl.mbedtls_asn1_get_alg_null(p, end, alg);
}

void mbedtls_asn1_free_named_data(mbedtls_asn1_named_data *cur)
{
	__rom_stubs_ssl.mbedtls_asn1_free_named_data(cur);
}

void mbedtls_asn1_free_named_data_list(mbedtls_asn1_named_data **head)
{
	__rom_stubs_ssl.mbedtls_asn1_free_named_data_list(head);
}

mbedtls_asn1_named_data *mbedtls_asn1_find_named_data(mbedtls_asn1_named_data *list, const char *oid, size_t len)
{
	return __rom_stubs_ssl.mbedtls_asn1_find_named_data(list, oid, len);
}

/* asn1write */
int mbedtls_asn1_write_len(unsigned char **p, unsigned char *start, size_t len)
{
	return __rom_stubs_ssl.mbedtls_asn1_write_len(p, start, len);
}

int mbedtls_asn1_write_tag(unsigned char **p, unsigned char *start, unsigned char tag)
{
	return __rom_stubs_ssl.mbedtls_asn1_write_tag(p, start, tag);
}

int mbedtls_asn1_write_raw_buffer(unsigned char **p, unsigned char *start, const unsigned char *buf, size_t size)
{
	return __rom_stubs_ssl.mbedtls_asn1_write_raw_buffer(p, start, buf, size);
}

int mbedtls_asn1_write_mpi(unsigned char **p, unsigned char *start, const mbedtls_mpi *X)
{
	return __rom_stubs_ssl.mbedtls_asn1_write_mpi(p, start, X);
}

int mbedtls_asn1_write_null(unsigned char **p, unsigned char *start)
{
	return __rom_stubs_ssl.mbedtls_asn1_write_null(p, start);
}

int mbedtls_asn1_write_oid(unsigned char **p, unsigned char *start, const char *oid, size_t oid_len)
{
	return __rom_stubs_ssl.mbedtls_asn1_write_oid(p, start, oid, oid_len);
}

int mbedtls_asn1_write_algorithm_identifier(unsigned char **p, unsigned char *start, const char *oid, size_t oid_len, size_t par_len)
{
	return __rom_stubs_ssl.mbedtls_asn1_write_algorithm_identifier(p, start, oid, oid_len, par_len);
}

int mbedtls_asn1_write_bool(unsigned char **p, unsigned char *start, int boolean)
{
	return __rom_stubs_ssl.mbedtls_asn1_write_bool(p, start, boolean);
}

int mbedtls_asn1_write_int(unsigned char **p, unsigned char *start, int val)
{
	return __rom_stubs_ssl.mbedtls_asn1_write_int(p, start, val);
}

int mbedtls_asn1_write_printable_string(unsigned char **p, unsigned char *start, const char *text, size_t text_len)
{
	return __rom_stubs_ssl.mbedtls_asn1_write_printable_string(p, start, text, text_len);
}

int mbedtls_asn1_write_ia5_string(unsigned char **p, unsigned char *start, const char *text, size_t text_len)
{
	return __rom_stubs_ssl.mbedtls_asn1_write_ia5_string(p, start, text, text_len);
}

int mbedtls_asn1_write_bitstring(unsigned char **p, unsigned char *start, const unsigned char *buf, size_t bits)
{
	return __rom_stubs_ssl.mbedtls_asn1_write_bitstring(p, start, buf, bits);
}

int mbedtls_asn1_write_octet_string(unsigned char **p, unsigned char *start, const unsigned char *buf, size_t size)
{
	return __rom_stubs_ssl.mbedtls_asn1_write_octet_string(p, start, buf, size);
}

mbedtls_asn1_named_data *mbedtls_asn1_store_named_data(mbedtls_asn1_named_data **head, const char *oid, size_t oid_len, const unsigned char *val,
		size_t val_len)
{
	return __rom_stubs_ssl.mbedtls_asn1_store_named_data(head, oid, oid_len, val, val_len);
}

/* base64 */
int mbedtls_base64_encode(unsigned char *dst, size_t dlen, size_t *olen, const unsigned char *src, size_t slen)
{
	return __rom_stubs_ssl.mbedtls_base64_encode(dst, dlen, olen, src, slen);
}

int mbedtls_base64_decode(unsigned char *dst, size_t dlen, size_t *olen, const unsigned char *src, size_t slen)
{
	return __rom_stubs_ssl.mbedtls_base64_decode(dst, dlen, olen, src, slen);
}

/* rsa */
void mbedtls_rsa_init(mbedtls_rsa_context *ctx, int padding, int hash_id)
{
	__rom_stubs_ssl.mbedtls_rsa_init(ctx, padding, hash_id);
}

void mbedtls_rsa_set_padding(mbedtls_rsa_context *ctx, int padding, int hash_id)
{
	__rom_stubs_ssl.mbedtls_rsa_set_padding(ctx, padding, hash_id);
}

int mbedtls_rsa_check_pubkey(const mbedtls_rsa_context *ctx)
{
	return __rom_stubs_ssl.mbedtls_rsa_check_pubkey(ctx);
}

int mbedtls_rsa_check_privkey(const mbedtls_rsa_context *ctx)
{
	return __rom_stubs_ssl.mbedtls_rsa_check_privkey(ctx);
}

int mbedtls_rsa_check_pub_priv(const mbedtls_rsa_context *pub, const mbedtls_rsa_context *prv)
{
	return __rom_stubs_ssl.mbedtls_rsa_check_pub_priv(pub, prv);
}

int mbedtls_rsa_public(mbedtls_rsa_context *ctx, const unsigned char *input, unsigned char *output)
{
	return __rom_stubs_ssl.mbedtls_rsa_public(ctx, input, output);
}

int mbedtls_rsa_private(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, const unsigned char *input, unsigned char *output)
{
	return __rom_stubs_ssl.mbedtls_rsa_private(ctx, f_rng, p_rng, input, output);
}

int mbedtls_rsa_rsaes_oaep_encrypt(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, const unsigned char *label,
								   size_t label_len, size_t ilen, const unsigned char *input, unsigned char *output)
{
	return __rom_stubs_ssl.mbedtls_rsa_rsaes_oaep_encrypt(ctx, f_rng, p_rng, mode, label, label_len, ilen, input, output);
}

int mbedtls_rsa_rsaes_pkcs1_v15_encrypt(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, size_t ilen,
										const unsigned char *input, unsigned char *output)
{
	return __rom_stubs_ssl.mbedtls_rsa_rsaes_pkcs1_v15_encrypt(ctx, f_rng, p_rng, mode, ilen, input, output);
}

int mbedtls_rsa_pkcs1_encrypt(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, size_t ilen,
							  const unsigned char *input, unsigned char *output)
{
	return __rom_stubs_ssl.mbedtls_rsa_pkcs1_encrypt(ctx, f_rng, p_rng, mode, ilen, input, output);
}

int mbedtls_rsa_rsaes_oaep_decrypt(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, const unsigned char *label,
								   size_t label_len, size_t *olen, const unsigned char *input, unsigned char *output, size_t output_max_len)
{
	return __rom_stubs_ssl.mbedtls_rsa_rsaes_oaep_decrypt(ctx, f_rng, p_rng, mode, label, label_len, olen, input, output, output_max_len);
}

int mbedtls_rsa_rsaes_pkcs1_v15_decrypt(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, size_t *olen,
										const unsigned char *input, unsigned char *output, size_t output_max_len)
{
	return __rom_stubs_ssl.mbedtls_rsa_rsaes_pkcs1_v15_decrypt(ctx, f_rng, p_rng, mode, olen, input, output, output_max_len);
}

int mbedtls_rsa_pkcs1_decrypt(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, size_t *olen,
							  const unsigned char *input, unsigned char *output, size_t output_max_len)
{
	return __rom_stubs_ssl.mbedtls_rsa_pkcs1_decrypt(ctx, f_rng, p_rng, mode, olen, input, output, output_max_len);
}

int mbedtls_rsa_rsassa_pss_sign(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, mbedtls_md_type_t md_alg,
								unsigned int hashlen, const unsigned char *hash, unsigned char *sig)
{
	return __rom_stubs_ssl.mbedtls_rsa_rsassa_pss_sign(ctx, f_rng, p_rng, mode, md_alg, hashlen, hash, sig);
}

int mbedtls_rsa_rsassa_pkcs1_v15_sign(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, mbedtls_md_type_t md_alg,
									  unsigned int hashlen, const unsigned char *hash, unsigned char *sig)
{
	return __rom_stubs_ssl.mbedtls_rsa_rsassa_pkcs1_v15_sign(ctx, f_rng, p_rng, mode, md_alg, hashlen, hash, sig);
}

int mbedtls_rsa_pkcs1_sign(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, mbedtls_md_type_t md_alg,
						   unsigned int hashlen, const unsigned char *hash, unsigned char *sig)
{
	return __rom_stubs_ssl.mbedtls_rsa_pkcs1_sign(ctx, f_rng, p_rng, mode, md_alg, hashlen, hash, sig);
}

int mbedtls_rsa_rsassa_pss_verify_ext(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, mbedtls_md_type_t md_alg,
									  unsigned int hashlen, const unsigned char *hash, mbedtls_md_type_t mgf1_hash_id, int expected_salt_len, const unsigned char *sig)
{
	return __rom_stubs_ssl.mbedtls_rsa_rsassa_pss_verify_ext(ctx, f_rng, p_rng, mode, md_alg, hashlen, hash, mgf1_hash_id, expected_salt_len, sig);
}

int mbedtls_rsa_rsassa_pss_verify(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, mbedtls_md_type_t md_alg,
								  unsigned int hashlen, const unsigned char *hash, const unsigned char *sig)
{
	return __rom_stubs_ssl.mbedtls_rsa_rsassa_pss_verify(ctx, f_rng, p_rng, mode, md_alg, hashlen, hash, sig);
}

int mbedtls_rsa_rsassa_pkcs1_v15_verify(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode,
										mbedtls_md_type_t md_alg, unsigned int hashlen, const unsigned char *hash, const unsigned char *sig)
{
	return __rom_stubs_ssl.mbedtls_rsa_rsassa_pkcs1_v15_verify(ctx, f_rng, p_rng, mode, md_alg, hashlen, hash, sig);
}

int mbedtls_rsa_pkcs1_verify(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, mbedtls_md_type_t md_alg,
							 unsigned int hashlen, const unsigned char *hash, const unsigned char *sig)
{
	return __rom_stubs_ssl.mbedtls_rsa_pkcs1_verify(ctx, f_rng, p_rng, mode, md_alg, hashlen, hash, sig);
}

void mbedtls_rsa_free(mbedtls_rsa_context *ctx)
{
	__rom_stubs_ssl.mbedtls_rsa_free(ctx);
}

int mbedtls_rsa_gen_key(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, unsigned int nbits, int exponent)
{
	return __rom_stubs_ssl.mbedtls_rsa_gen_key(ctx, f_rng, p_rng, nbits, exponent);
}

int mbedtls_rsa_copy(mbedtls_rsa_context *dst, const mbedtls_rsa_context *src)
{
	return __rom_stubs_ssl.mbedtls_rsa_copy(dst, src);
}

/* ctr_drbg */
void mbedtls_ctr_drbg_init(mbedtls_ctr_drbg_context *ctx)
{
	__rom_stubs_ssl.mbedtls_ctr_drbg_init(ctx);
}

void mbedtls_ctr_drbg_free(mbedtls_ctr_drbg_context *ctx)
{
	__rom_stubs_ssl.mbedtls_ctr_drbg_free(ctx);
}

void mbedtls_ctr_drbg_set_prediction_resistance(mbedtls_ctr_drbg_context *ctx, int resistance)
{
	__rom_stubs_ssl.mbedtls_ctr_drbg_set_prediction_resistance(ctx, resistance);
}

void mbedtls_ctr_drbg_set_entropy_len(mbedtls_ctr_drbg_context *ctx, size_t len)
{
	__rom_stubs_ssl.mbedtls_ctr_drbg_set_entropy_len(ctx, len);
}

void mbedtls_ctr_drbg_set_reseed_interval(mbedtls_ctr_drbg_context *ctx, int interval)
{
	__rom_stubs_ssl.mbedtls_ctr_drbg_set_reseed_interval(ctx, interval);
}

void mbedtls_ctr_drbg_update(mbedtls_ctr_drbg_context *ctx, const unsigned char *additional, size_t add_len)
{
	__rom_stubs_ssl.mbedtls_ctr_drbg_update(ctx, additional, add_len);
}

int mbedtls_ctr_drbg_reseed(mbedtls_ctr_drbg_context *ctx, const unsigned char *additional, size_t len)
{
	return __rom_stubs_ssl.mbedtls_ctr_drbg_reseed(ctx, additional, len);
}

int mbedtls_ctr_drbg_seed_entropy_len(mbedtls_ctr_drbg_context *ctx, int (*f_entropy)(void *, unsigned char *, size_t), void *p_entropy,
									  const unsigned char *custom, size_t len, size_t entropy_len)
{
	return __rom_stubs_ssl.mbedtls_ctr_drbg_seed_entropy_len(ctx, f_entropy, p_entropy, custom, len, entropy_len);
}

int mbedtls_ctr_drbg_seed(mbedtls_ctr_drbg_context *ctx, int (*f_entropy)(void *, unsigned char *, size_t), void *p_entropy, const unsigned char *custom,
						  size_t len)
{
	return __rom_stubs_ssl.mbedtls_ctr_drbg_seed(ctx, f_entropy, p_entropy, custom, len);
}

int mbedtls_ctr_drbg_random_with_add(void *p_rng, unsigned char *output, size_t output_len, const unsigned char *additional, size_t add_len)
{
	return __rom_stubs_ssl.mbedtls_ctr_drbg_random_with_add(p_rng, output, output_len, additional, add_len);
}

int mbedtls_ctr_drbg_random(void *p_rng, unsigned char *output, size_t output_len)
{
	return __rom_stubs_ssl.mbedtls_ctr_drbg_random(p_rng, output, output_len);
}
/* hmac_drbg */
void mbedtls_hmac_drbg_init(mbedtls_hmac_drbg_context *ctx)
{
	__rom_stubs_ssl.mbedtls_hmac_drbg_init(ctx);
}

void mbedtls_hmac_drbg_update(mbedtls_hmac_drbg_context *ctx, const unsigned char *additional, size_t add_len)
{
	__rom_stubs_ssl.mbedtls_hmac_drbg_update(ctx, additional, add_len);
}

int mbedtls_hmac_drbg_seed_buf(mbedtls_hmac_drbg_context *ctx, const mbedtls_md_info_t *md_info, const unsigned char *data, size_t data_len)
{
	return __rom_stubs_ssl.mbedtls_hmac_drbg_seed_buf(ctx, md_info, data, data_len);
}

int mbedtls_hmac_drbg_reseed(mbedtls_hmac_drbg_context *ctx, const unsigned char *additional, size_t len)
{
	return __rom_stubs_ssl.mbedtls_hmac_drbg_reseed(ctx, additional, len);
}

int mbedtls_hmac_drbg_seed(mbedtls_hmac_drbg_context *ctx, const mbedtls_md_info_t *md_info, int (*f_entropy)(void *, unsigned char *, size_t), void *p_entropy,
						   const unsigned char *custom, size_t len)
{
	return __rom_stubs_ssl.mbedtls_hmac_drbg_seed(ctx, md_info, f_entropy, p_entropy, custom, len);
}

void mbedtls_hmac_drbg_set_prediction_resistance(mbedtls_hmac_drbg_context *ctx, int resistance)
{
	__rom_stubs_ssl.mbedtls_hmac_drbg_set_prediction_resistance(ctx, resistance);
}

void mbedtls_hmac_drbg_set_entropy_len(mbedtls_hmac_drbg_context *ctx, size_t len)
{
	__rom_stubs_ssl.mbedtls_hmac_drbg_set_entropy_len(ctx, len);
}

void mbedtls_hmac_drbg_set_reseed_interval(mbedtls_hmac_drbg_context *ctx, int interval)
{
	__rom_stubs_ssl.mbedtls_hmac_drbg_set_reseed_interval(ctx, interval);
}

int mbedtls_hmac_drbg_random_with_add(void *p_rng, unsigned char *output, size_t out_len, const unsigned char *additional, size_t add_len)
{
	return __rom_stubs_ssl.mbedtls_hmac_drbg_random_with_add(p_rng, output, out_len, additional, add_len);
}

int mbedtls_hmac_drbg_random(void *p_rng, unsigned char *output, size_t out_len)
{
	return __rom_stubs_ssl.mbedtls_hmac_drbg_random(p_rng, output, out_len);
}

void mbedtls_hmac_drbg_free(mbedtls_hmac_drbg_context *ctx)
{
	__rom_stubs_ssl.mbedtls_hmac_drbg_free(ctx);
}

/* pem */
void mbedtls_pem_init(mbedtls_pem_context *ctx)
{
	__rom_stubs_ssl.mbedtls_pem_init(ctx);
}

int mbedtls_pem_read_buffer(mbedtls_pem_context *ctx, const char *header, const char *footer, const unsigned char *data, const unsigned char *pwd,
							size_t pwdlen, size_t *use_len)
{
	return __rom_stubs_ssl.mbedtls_pem_read_buffer(ctx, header, footer, data, pwd, pwdlen, use_len);
}

void mbedtls_pem_free(mbedtls_pem_context *ctx)
{
	__rom_stubs_ssl.mbedtls_pem_free(ctx);
}

int mbedtls_pem_write_buffer(const char *header, const char *footer, const unsigned char *der_data, size_t der_len, unsigned char *buf, size_t buf_len,
							 size_t *olen)
{
	return __rom_stubs_ssl.mbedtls_pem_write_buffer(header, footer, der_data, der_len, buf, buf_len, olen);
}

/* dhm */
void mbedtls_dhm_init(mbedtls_dhm_context *ctx)
{
	__rom_stubs_ssl.mbedtls_dhm_init(ctx);
}

int mbedtls_dhm_read_params(mbedtls_dhm_context *ctx, unsigned char **p, const unsigned char *end)
{
	return __rom_stubs_ssl.mbedtls_dhm_read_params(ctx, p, end);
}

int mbedtls_dhm_make_params(mbedtls_dhm_context *ctx, int x_size, unsigned char *output, size_t *olen, int (*f_rng)(void *, unsigned char *, size_t),
							void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_dhm_make_params(ctx, x_size, output, olen, f_rng, p_rng);
}

int mbedtls_dhm_read_public(mbedtls_dhm_context *ctx, const unsigned char *input, size_t ilen)
{
	return __rom_stubs_ssl.mbedtls_dhm_read_public(ctx, input, ilen);
}

int mbedtls_dhm_make_public(mbedtls_dhm_context *ctx, int x_size, unsigned char *output, size_t olen, int (*f_rng)(void *, unsigned char *, size_t),
							void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_dhm_make_public(ctx, x_size, output, olen, f_rng, p_rng);
}

int mbedtls_dhm_calc_secret(mbedtls_dhm_context *ctx, unsigned char *output, size_t output_size, size_t *olen, int (*f_rng)(void *, unsigned char *, size_t),
							void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_dhm_calc_secret(ctx, output, output_size, olen, f_rng, p_rng);
}

void mbedtls_dhm_free(mbedtls_dhm_context *ctx)
{
	__rom_stubs_ssl.mbedtls_dhm_free(ctx);
}

int mbedtls_dhm_parse_dhm(mbedtls_dhm_context *dhm, const unsigned char *dhmin, size_t dhminlen)
{
	return __rom_stubs_ssl.mbedtls_dhm_parse_dhm(dhm, dhmin, dhminlen);
}

/* ecjpake */
void mbedtls_ecjpake_init(mbedtls_ecjpake_context *ctx)
{
	__rom_stubs_ssl.mbedtls_ecjpake_init(ctx);
}

void mbedtls_ecjpake_free(mbedtls_ecjpake_context *ctx)
{
	__rom_stubs_ssl.mbedtls_ecjpake_free(ctx);
}

int mbedtls_ecjpake_setup(mbedtls_ecjpake_context *ctx, mbedtls_ecjpake_role role, mbedtls_md_type_t hash, mbedtls_ecp_group_id curve,
						  const unsigned char *secret, size_t len)
{
	return __rom_stubs_ssl.mbedtls_ecjpake_setup(ctx, role, hash, curve, secret, len);
}

int mbedtls_ecjpake_check(const mbedtls_ecjpake_context *ctx)
{
	return __rom_stubs_ssl.mbedtls_ecjpake_check(ctx);
}

int mbedtls_ecjpake_read_round_one(mbedtls_ecjpake_context *ctx, const unsigned char *buf, size_t len)
{
	return __rom_stubs_ssl.mbedtls_ecjpake_read_round_one(ctx, buf, len);
}

int mbedtls_ecjpake_write_round_one(mbedtls_ecjpake_context *ctx, unsigned char *buf, size_t len, size_t *olen, int (*f_rng)(void *, unsigned char *, size_t),
									void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_ecjpake_write_round_one(ctx, buf, len, olen, f_rng, p_rng);
}

int mbedtls_ecjpake_read_round_two(mbedtls_ecjpake_context *ctx, const unsigned char *buf, size_t len)
{
	return __rom_stubs_ssl.mbedtls_ecjpake_read_round_two(ctx, buf, len);
}

int mbedtls_ecjpake_write_round_two(mbedtls_ecjpake_context *ctx, unsigned char *buf, size_t len, size_t *olen, int (*f_rng)(void *, unsigned char *, size_t),
									void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_ecjpake_write_round_two(ctx, buf, len, olen, f_rng, p_rng);
}

int mbedtls_ecjpake_derive_secret(mbedtls_ecjpake_context *ctx, unsigned char *buf, size_t len, size_t *olen, int (*f_rng)(void *, unsigned char *, size_t),
								  void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_ecjpake_derive_secret(ctx, buf, len, olen, f_rng, p_rng);
}

/* arc4 */
void mbedtls_arc4_init(mbedtls_arc4_context *ctx)
{
	__rom_stubs_ssl.mbedtls_arc4_init(ctx);
}

void mbedtls_arc4_free(mbedtls_arc4_context *ctx)
{
	__rom_stubs_ssl.mbedtls_arc4_free(ctx);
}

void mbedtls_arc4_setup(mbedtls_arc4_context *ctx, const unsigned char *key, unsigned int keylen)
{
	__rom_stubs_ssl.mbedtls_arc4_setup(ctx, key, keylen);
}

int mbedtls_arc4_crypt(mbedtls_arc4_context *ctx, size_t length, const unsigned char *input, unsigned char *output)
{
	return __rom_stubs_ssl.mbedtls_arc4_crypt(ctx, length, input, output);
}

/* ecdh */
int mbedtls_ecdh_gen_public(mbedtls_ecp_group *grp, mbedtls_mpi *d, mbedtls_ecp_point *Q, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_ecdh_gen_public(grp, d, Q, f_rng, p_rng);
}

int mbedtls_ecdh_compute_shared(mbedtls_ecp_group *grp, mbedtls_mpi *z, const mbedtls_ecp_point *Q, const mbedtls_mpi *d, int (*f_rng)(void *, unsigned char *,
								size_t), void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_ecdh_compute_shared(grp, z, Q, d, f_rng, p_rng);
}

void mbedtls_ecdh_init(mbedtls_ecdh_context *ctx)
{
	__rom_stubs_ssl.mbedtls_ecdh_init(ctx);
}

void mbedtls_ecdh_free(mbedtls_ecdh_context *ctx)
{
	__rom_stubs_ssl.mbedtls_ecdh_free(ctx);
}

int mbedtls_ecdh_make_params(mbedtls_ecdh_context *ctx, size_t *olen, unsigned char *buf, size_t blen, int (*f_rng)(void *, unsigned char *, size_t),
							 void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_ecdh_make_params(ctx, olen, buf, blen, f_rng, p_rng);
}

int mbedtls_ecdh_read_params(mbedtls_ecdh_context *ctx, const unsigned char **buf, const unsigned char *end)
{
	return __rom_stubs_ssl.mbedtls_ecdh_read_params(ctx, buf, end);
}

int mbedtls_ecdh_get_params(mbedtls_ecdh_context *ctx, const mbedtls_ecp_keypair *key, mbedtls_ecdh_side side)
{
	return __rom_stubs_ssl.mbedtls_ecdh_get_params(ctx, key, side);
}

int mbedtls_ecdh_make_public(mbedtls_ecdh_context *ctx, size_t *olen, unsigned char *buf, size_t blen, int (*f_rng)(void *, unsigned char *, size_t),
							 void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_ecdh_make_public(ctx, olen, buf, blen, f_rng, p_rng);
}

int mbedtls_ecdh_read_public(mbedtls_ecdh_context *ctx, const unsigned char *buf, size_t blen)
{
	return __rom_stubs_ssl.mbedtls_ecdh_read_public(ctx, buf, blen);
}

int mbedtls_ecdh_calc_secret(mbedtls_ecdh_context *ctx, size_t *olen, unsigned char *buf, size_t blen, int (*f_rng)(void *, unsigned char *, size_t),
							 void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_ecdh_calc_secret(ctx, olen, buf, blen, f_rng, p_rng);
}

/* ecdsa */
int mbedtls_ecdsa_sign(mbedtls_ecp_group *grp, mbedtls_mpi *r, mbedtls_mpi *s, const mbedtls_mpi *d, const unsigned char *buf, size_t blen, int (*f_rng)(void *,
					   unsigned char *, size_t), void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_ecdsa_sign(grp, r, s, d, buf, blen, f_rng, p_rng);
}

int mbedtls_ecdsa_sign_det(mbedtls_ecp_group *grp, mbedtls_mpi *r, mbedtls_mpi *s, const mbedtls_mpi *d, const unsigned char *buf, size_t blen,
						   mbedtls_md_type_t md_alg)
{
	return __rom_stubs_ssl.mbedtls_ecdsa_sign_det(grp, r, s, d, buf, blen, md_alg);
}

int mbedtls_ecdsa_verify(mbedtls_ecp_group *grp, const unsigned char *buf, size_t blen, const mbedtls_ecp_point *Q, const mbedtls_mpi *r, const mbedtls_mpi *s)
{
	return __rom_stubs_ssl.mbedtls_ecdsa_verify(grp, buf, blen, Q, r, s);
}

int mbedtls_ecdsa_write_signature(mbedtls_ecdsa_context *ctx, mbedtls_md_type_t md_alg, const unsigned char *hash, size_t hlen, unsigned char *sig,
								  size_t *slen, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_ecdsa_write_signature(ctx, md_alg, hash, hlen, sig, slen, f_rng, p_rng);
}

int mbedtls_ecdsa_write_signature_det(mbedtls_ecdsa_context *ctx, const unsigned char *hash, size_t hlen, unsigned char *sig, size_t *slen,
									  mbedtls_md_type_t md_alg)
{
	return __rom_stubs_ssl.mbedtls_ecdsa_write_signature_det(ctx, hash, hlen, sig, slen, md_alg);
}

int mbedtls_ecdsa_read_signature(mbedtls_ecdsa_context *ctx, const unsigned char *hash, size_t hlen, const unsigned char *sig, size_t slen)
{
	return __rom_stubs_ssl.mbedtls_ecdsa_read_signature(ctx, hash, hlen, sig, slen);
}

int mbedtls_ecdsa_genkey(mbedtls_ecdsa_context *ctx, mbedtls_ecp_group_id gid, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_ecdsa_genkey(ctx, gid, f_rng, p_rng);
}

int mbedtls_ecdsa_from_keypair(mbedtls_ecdsa_context *ctx, const mbedtls_ecp_keypair *key)
{
	return __rom_stubs_ssl.mbedtls_ecdsa_from_keypair(ctx, key);
}

void mbedtls_ecdsa_init(mbedtls_ecdsa_context *ctx)
{
	__rom_stubs_ssl.mbedtls_ecdsa_init(ctx);
}

void mbedtls_ecdsa_free(mbedtls_ecdsa_context *ctx)
{
	__rom_stubs_ssl.mbedtls_ecdsa_free(ctx);
}

/* pk */
void mbedtls_pk_init(mbedtls_pk_context *ctx)
{
	__rom_stubs_ssl.mbedtls_pk_init(ctx);
}

void mbedtls_pk_free(mbedtls_pk_context *ctx)
{
	__rom_stubs_ssl.mbedtls_pk_free(ctx);
}

const mbedtls_pk_info_t *mbedtls_pk_info_from_type(mbedtls_pk_type_t pk_type)
{
	return __rom_stubs_ssl.mbedtls_pk_info_from_type(pk_type);
}

int mbedtls_pk_setup(mbedtls_pk_context *ctx, const mbedtls_pk_info_t *info)
{
	return __rom_stubs_ssl.mbedtls_pk_setup(ctx, info);
}

int mbedtls_pk_setup_rsa_alt(mbedtls_pk_context *ctx, void *key, mbedtls_pk_rsa_alt_decrypt_func decrypt_func, mbedtls_pk_rsa_alt_sign_func sign_func,
							 mbedtls_pk_rsa_alt_key_len_func key_len_func)
{
	return __rom_stubs_ssl.mbedtls_pk_setup_rsa_alt(ctx, key, decrypt_func, sign_func, key_len_func);
}

int mbedtls_pk_can_do(const mbedtls_pk_context *ctx, mbedtls_pk_type_t type)
{
	return __rom_stubs_ssl.mbedtls_pk_can_do(ctx, type);
}

int mbedtls_pk_verify(mbedtls_pk_context *ctx, mbedtls_md_type_t md_alg, const unsigned char *hash, size_t hash_len, const unsigned char *sig, size_t sig_len)
{
	return __rom_stubs_ssl.mbedtls_pk_verify(ctx, md_alg, hash, hash_len, sig, sig_len);
}

int mbedtls_pk_verify_ext(mbedtls_pk_type_t type, const void *options, mbedtls_pk_context *ctx, mbedtls_md_type_t md_alg, const unsigned char *hash,
						  size_t hash_len, const unsigned char *sig, size_t sig_len)
{
	return __rom_stubs_ssl.mbedtls_pk_verify_ext(type, options, ctx, md_alg, hash, hash_len, sig, sig_len);
}

int mbedtls_pk_sign(mbedtls_pk_context *ctx, mbedtls_md_type_t md_alg, const unsigned char *hash, size_t hash_len, unsigned char *sig, size_t *sig_len,
					int (*f_rng)(void *, unsigned char *, size_t), void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_pk_sign(ctx, md_alg, hash, hash_len, sig, sig_len, f_rng, p_rng);
}

int mbedtls_pk_decrypt(mbedtls_pk_context *ctx, const unsigned char *input, size_t ilen, unsigned char *output, size_t *olen, size_t osize, int (*f_rng)(void *,
					   unsigned char *, size_t), void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_pk_decrypt(ctx, input, ilen, output, olen, osize, f_rng, p_rng);
}

int mbedtls_pk_encrypt(mbedtls_pk_context *ctx, const unsigned char *input, size_t ilen, unsigned char *output, size_t *olen, size_t osize, int (*f_rng)(void *,
					   unsigned char *, size_t), void *p_rng)
{
	return __rom_stubs_ssl.mbedtls_pk_encrypt(ctx, input, ilen, output, olen, osize, f_rng, p_rng);
}

int mbedtls_pk_check_pair(const mbedtls_pk_context *pub, const mbedtls_pk_context *prv)
{
	return __rom_stubs_ssl.mbedtls_pk_check_pair(pub, prv);
}

size_t mbedtls_pk_get_bitlen(const mbedtls_pk_context *ctx)
{
	return __rom_stubs_ssl.mbedtls_pk_get_bitlen(ctx);
}

int mbedtls_pk_debug(const mbedtls_pk_context *ctx, mbedtls_pk_debug_item *items)
{
	return __rom_stubs_ssl.mbedtls_pk_debug(ctx, items);
}

const char *mbedtls_pk_get_name(const mbedtls_pk_context *ctx)
{
	return __rom_stubs_ssl.mbedtls_pk_get_name(ctx);
}

mbedtls_pk_type_t mbedtls_pk_get_type(const mbedtls_pk_context *ctx)
{
	return __rom_stubs_ssl.mbedtls_pk_get_type(ctx);
}

/* pkwrite */
int mbedtls_pk_write_pubkey(unsigned char **p, unsigned char *start, const mbedtls_pk_context *key)
{
	return __rom_stubs_ssl.mbedtls_pk_write_pubkey(p, start, key);
}

int mbedtls_pk_write_pubkey_der(mbedtls_pk_context *key, unsigned char *buf, size_t size)
{
	return __rom_stubs_ssl.mbedtls_pk_write_pubkey_der(key, buf, size);
}

int mbedtls_pk_write_key_der(mbedtls_pk_context *key, unsigned char *buf, size_t size)
{
	return __rom_stubs_ssl.mbedtls_pk_write_key_der(key, buf, size);
}

int mbedtls_pk_write_pubkey_pem(mbedtls_pk_context *key, unsigned char *buf, size_t size)
{
	return __rom_stubs_ssl.mbedtls_pk_write_pubkey_pem(key, buf, size);
}

int mbedtls_pk_write_key_pem(mbedtls_pk_context *key, unsigned char *buf, size_t size)
{
	return __rom_stubs_ssl.mbedtls_pk_write_key_pem(key, buf, size);
}
#endif /* !((defined(CONFIG_PLATFORM_8710C) || defined(CONFIG_PLATFORM_8735B)) && defined(CONFIG_BUILD_SECURE) && (CONFIG_BUILD_SECURE == 1)) */

#endif /* !(defined(CONFIG_PLATFORM_8735B) && (MBEDTLS_VERSION_NUMBER>=0x03000000 || MBEDTLS_VERSION_NUMBER==0x02100600 || MBEDTLS_VERSION_NUMBER==0x021C0100)) */