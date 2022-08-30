#ifndef __DPP_CRYPTO_H__
#define __DPP_CRYPTO_H__

#define DPP_AES_SIV_128 16
#define SHA256_DIGEST_SIZE 32
#define SHA384_DIGEST_SIZE 48
#define SHA512_DIGEST_SIZE 64

int DPP_DH_Generate_L_Configurator(u8 *bIkey_private, u32 bIkey_private_len,
								   u8 *public_key_Bx, u8 *public_key_By,
								   u8 *public_key_Px, u8 *public_key_Py,
								   u8 *L_key_x,  u8 *L_key_y,
								   u32 ecc_public_key_len, u8 ecc_id);

#endif
