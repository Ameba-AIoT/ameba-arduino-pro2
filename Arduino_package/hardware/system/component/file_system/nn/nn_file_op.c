//--------------------------------------------------------------------------------------
// VIPNN file usage
//--------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "nn_file_op.h"
#include "vfs.h"

#define MODEL_FROM_FLASH    0x01
#define MODEL_FROM_SD       0x02
#define MODEL_SRC           MODEL_FROM_FLASH

//----- AES NN Model decryption --------------------------------------------------------
#include "crypto_api.h"
#include "hal_crypto.h"
#include "device_lock.h"

typedef enum aes_mode {
	AES_MODE_CBC
} aes_mode_t;

#define MDL_ENC_SIZE    512  //always decrypt first 512bytes fixed header
static uint8_t AESkey[32] = {0};
static uint8_t AESkeylen = 32; //always use AES-256
static uint8_t AESiv[16] = {0};
static aes_mode_t AESmode = AES_MODE_CBC;

typedef struct nn_aes_ctx {
	int nr;                     // The number of rounds.
	uint32_t *rk;               // AES round keys.
	uint32_t buf[68];           // Unaligned data buffer.
	uint8_t *pDecBuf;           // Decrypt data buffer.
	aes_mode_t mode;            // AES mode
} nn_aes_ctx_t;

int nn_aes_key_injection(uint8_t *key, uint8_t *iv)
{
	if (key == NULL || iv == NULL) {
		return -1;
	}
	memcpy(AESkey, key, sizeof(AESkey));
	memcpy(AESiv, iv, sizeof(AESiv));
	return 0;
}

static nn_aes_ctx_t *pAes_ctx = NULL;

static bool nn_encrypted(void)
{
	uint8_t zero_key[32] = {0};
	if (memcmp(AESkey, zero_key, sizeof(AESkey)) == 0) {
		return 0;
	} else {
		return 1;
	}
}

static int nn_aes_set_key(nn_aes_ctx_t *ctx, uint8_t *key, int keybits)
{
	int keyBytes = 1;

	switch (keybits) {
	case 128:
		ctx->nr = 10;
		keyBytes = 128 / 8;
		break;
	case 192:
		ctx->nr = 12;
		keyBytes = 192 / 8;
		break;
	case 256:
		ctx->nr = 14;
		keyBytes = 256 / 8;
		break;
	default :
		return -1;
	}

	ctx->rk = ctx->buf;
	memcpy(ctx->rk, key, keyBytes);

	return 0;
}

static int nn_aes_set_mode(nn_aes_ctx_t *ctx, aes_mode_t mode)
{
	ctx->mode = mode;

	return 0;
}

static int nn_aes_crypt_cbc_decrypt(nn_aes_ctx_t *ctx, size_t length, uint8_t iv[16], const uint8_t *input, uint8_t *output)
{
	if (length % 16) {
		printf("[NN decrypt] invalid input length for cbc decrypt\r\n");
		return -1;
	}

	if (length > 0) {
		uint8_t key_buf[32 + 32 + 32], *key_buf_aligned;
		uint8_t iv_buf[32 + 16 + 32], *iv_buf_aligned, iv_tmp[16];
		size_t length_done = 0;

		key_buf_aligned = (uint8_t *)(((unsigned int) key_buf + 32) / 32 * 32);
		memcpy(key_buf_aligned, ctx->rk, ((ctx->nr - 6) * 4));
		iv_buf_aligned = (uint8_t *)(((unsigned int) iv_buf + 32) / 32 * 32);
		memcpy(iv_buf_aligned, iv, 16);

		device_mutex_lock(RT_DEV_LOCK_CRYPTO);
		crypto_aes_cbc_init(key_buf_aligned, ((ctx->nr - 6) * 4));
		while ((length - length_done) > CRYPTO_MAX_MSG_LENGTH) {
			memcpy(iv_tmp, (input + length_done + CRYPTO_MAX_MSG_LENGTH - 16), 16);
			crypto_aes_cbc_decrypt(input + length_done, CRYPTO_MAX_MSG_LENGTH, iv_buf_aligned, 16, output + length_done);
			memcpy(iv_buf_aligned, iv_tmp, 16);
			length_done += CRYPTO_MAX_MSG_LENGTH;
		}
		memcpy(iv_tmp, (input + length - 16), 16);
		crypto_aes_cbc_decrypt(input + length_done, length - length_done, iv_buf_aligned, 16, output + length_done);
		device_mutex_unlock(RT_DEV_LOCK_CRYPTO);
	}

	return 0;
}

static int nn_model_decrypt(const uint8_t *input, uint8_t *output)
{
	int ret = -1;
	if (pAes_ctx->mode == AES_MODE_CBC) {
		printf("[NN decrypt] decrypt model in CBC mode\r\n");
		ret = nn_aes_crypt_cbc_decrypt(pAes_ctx, MDL_ENC_SIZE, AESiv, input, output);
	} else {
		printf("[NN decrypt] unsupported AES mode\r\n");
	}
	return ret;
}

static uint8_t crypto_inited = 0;

static void nn_aes_deinit(void);

static int nn_aes_init(void *fp)
{
	printf("[NN decrypt] fisrt %d bytes of model are encrypted.\r\n", MDL_ENC_SIZE);

	int ret = 0;

	if (!crypto_inited) {
		device_mutex_lock(RT_DEV_LOCK_CRYPTO);
		crypto_init();
		device_mutex_unlock(RT_DEV_LOCK_CRYPTO);
		crypto_inited = 1;
	}

	pAes_ctx = (nn_aes_ctx_t *)malloc(sizeof(nn_aes_ctx_t));
	if (!pAes_ctx) {
		printf("[NN decrypt] fail to allocate memory for pAes_ctx\r\n");
		goto error;
	}
	memset(pAes_ctx, 0, sizeof(nn_aes_ctx_t));

	pAes_ctx->pDecBuf = (uint8_t *)malloc(MDL_ENC_SIZE);
	if (!pAes_ctx->pDecBuf) {
		printf("[NN decrypt] fail to allocate memory for pAes_ctx->pDecBuf\r\n");
		goto error;
	}

	ret = nn_aes_set_mode(pAes_ctx, AESmode);
	if (ret != 0) {
		printf("[NN decrypt] nn_aes_set_mode fail\r\n");
		goto error;
	}

	ret = nn_aes_set_key(pAes_ctx, AESkey, AESkeylen * 8);
	if (ret != 0) {
		printf("[NN decrypt] nn_aes_set_key fail\r\n");
		goto error;
	}

	//pfw_dump_mem((uint8_t *)AESiv, sizeof(AESiv));

	nn_f_seek((FILE *)fp, 0, SEEK_SET);
	ret = nn_f_read(fp, pAes_ctx->pDecBuf, MDL_ENC_SIZE);
	if (ret < 0) {
		printf("[NN decrypt] nn_f_read fail\r\n");
		goto error;
	}
	//pfw_dump_mem((uint8_t *)pAes_ctx->pDecBuf, 128);

	uint32_t t0 = xTaskGetTickCount();
	ret = nn_model_decrypt(pAes_ctx->pDecBuf, pAes_ctx->pDecBuf);
	if (ret != 0) {
		printf("[NN decrypt] nn_model_decrypt fail\r\n");
		goto error;
	}
	uint32_t t1 = xTaskGetTickCount();
	printf("[NN decrypt] decrypt model done, take %ld ms.\r\n", t1 - t0);
	//pfw_dump_mem((uint8_t *)pAes_ctx->pDecBuf, 128);
	nn_f_seek((FILE *)fp, 0, SEEK_SET);

	return 0;

error:
	nn_aes_deinit();
	return -1;
}

static void nn_aes_deinit(void)
{
	if (pAes_ctx) {
		if (pAes_ctx->pDecBuf) {
			free(pAes_ctx->pDecBuf);
		}
		free(pAes_ctx);
	}
	memset(AESkey, 0, sizeof(AESkey));
	memset(AESiv, 0, sizeof(AESiv));
}

//--------------------------------------------------------------------------------------

typedef struct nn_file_s {
	void *fd;
	int is_vfs_path;
} nn_file_t;

void *nn_f_open(char *name, int mode)
{
	nn_file_t *nn_fp = (nn_file_t *)malloc(sizeof(nn_file_t));
	if (nn_fp == NULL) {
		printf("nn_fp malloc fail\r\n");
		goto error;
	}
	memset(nn_fp, 0, sizeof(nn_file_t));
	nn_fp->is_vfs_path = strstr(name, ":/") ? 1 : 0;

	if (nn_fp->is_vfs_path) {
		nn_fp->fd = (void *)fopen(name, "r");
	} else {
#if MODEL_SRC==MODEL_FROM_FLASH
		nn_fp->fd = pfw_open(name, M_NORMAL);
#elif MODEL_SRC==MODEL_FROM_SD
		vfs_init(NULL);
		vfs_user_register("sd", VFS_FATFS, VFS_INF_SD);
		char model_name[64];
		memset(model_name, 0, sizeof(model_name));
		snprintf(model_name, sizeof(model_name), "%s%s", "sd:/", name);
		nn_fp->fd = (void *)fopen(model_name, "r");
#endif
	}
	if (nn_fp->fd == NULL) {
		printf("nn open fail\r\n");
		goto error;
	}

	if (nn_encrypted()) {
		if (nn_aes_init(nn_fp) != 0) {
			printf("[NN decrypt] fail to init nn AES\r\n");
			goto error;
		}
	}

	return (void *)nn_fp;

error:
	if (nn_fp) {
		nn_f_close(nn_fp);
	}
	return NULL;
}

void nn_f_close(void *fr)
{
	nn_file_t *nn_fp = (nn_file_t *)fr;

	if (nn_fp->is_vfs_path) {

#ifdef ARDUINO_SDK
		if (nn_fp->fd) {
			fclose((FILE *)nn_fp->fd);
		}
#else
		fclose((FILE *)nn_fp->fd);
#endif

	} else {
#if MODEL_SRC==MODEL_FROM_FLASH
		pfw_close(nn_fp->fd);
#elif MODEL_SRC==MODEL_FROM_SD

#ifdef ARDUINO_SDK
	if (nn_fp->fd) {
		fclose((FILE *)nn_fp->fd);
	}
#else
	fclose((FILE *)nn_fp->fd);
#endif

#endif
	}

	if (nn_encrypted()) {
		nn_aes_deinit();
	}
	free(nn_fp);
}

int nn_f_read(void *fr, void *data, int size)
{
	nn_file_t *nn_fp = (nn_file_t *)fr;

	int crr = nn_f_tell(nn_fp);
	int ret_size = 0;

	if (nn_fp->is_vfs_path) {
		ret_size = fread(data, size, 1, (FILE *)nn_fp->fd);
	} else {
#if MODEL_SRC==MODEL_FROM_FLASH
		ret_size = pfw_read(nn_fp->fd, data, size);
#elif MODEL_SRC==MODEL_FROM_SD
		ret_size = fread(data, size, 1, (FILE *)nn_fp->fd);
#endif
	}

	if (nn_encrypted()) {
		if (crr < MDL_ENC_SIZE) {
			int res_size = (crr + size) > MDL_ENC_SIZE ? MDL_ENC_SIZE - crr : size;
			memcpy(data, pAes_ctx->pDecBuf + crr, res_size);
		}
	}

	return ret_size;
}

int nn_f_seek(void *fr, int offset, int pos)
{
	nn_file_t *nn_fp = (nn_file_t *)fr;

	int ret = 0;
	if (nn_fp->is_vfs_path) {
		ret = fseek((FILE *)nn_fp->fd, offset, pos);
	} else {
#if MODEL_SRC==MODEL_FROM_FLASH
		ret = pfw_seek(nn_fp->fd, offset, pos);
#elif MODEL_SRC==MODEL_FROM_SD
		ret = fseek((FILE *)nn_fp->fd, offset, pos);
#endif
	}
	return ret;
}

int nn_f_tell(void *fr)
{
	nn_file_t *nn_fp = (nn_file_t *)fr;

	int ret = 0;
	if (nn_fp->is_vfs_path) {
		ret = ftell((FILE *)nn_fp->fd);
	} else {
#if MODEL_SRC==MODEL_FROM_FLASH
		ret = pfw_tell(nn_fp->fd);
#elif MODEL_SRC==MODEL_FROM_SD
		ret = ftell((FILE *)nn_fp->fd);
#endif
	}
	return ret;
}