#ifndef ROM_APPLE_FUNC_RENAME_H
#define ROM_APPLE_FUNC_RENAME_H

// chacha20
#define CRYPTO_chacha_20                _CRYPTO_chacha_20
// ed25519
#define rom_ed25519_gen_keypair         _rom_ed25519_gen_keypair
#define rom_ed25519_gen_signature       _rom_ed25519_gen_signature
#define rom_ed25519_verify_signature    _rom_ed25519_verify_signature
// poly1305
#define CRYPTO_poly1305_init            _CRYPTO_poly1305_init
#define CRYPTO_poly1305_update          _CRYPTO_poly1305_update
#define CRYPTO_poly1305_finish          _CRYPTO_poly1305_finish
// sha512
#define rom_sha512_starts               _rom_sha512_starts
#define rom_sha512_update               _rom_sha512_update
#define rom_sha512_finish               _rom_sha512_finish
#define rom_sha512                      _rom_sha512
#define rom_sha512_hmac_starts          _rom_sha512_hmac_starts
#define rom_sha512_hmac_update          _rom_sha512_hmac_update
#define rom_sha512_hmac_finish          _rom_sha512_hmac_finish
#define rom_sha512_hmac_reset           _rom_sha512_hmac_reset
#define rom_sha512_hmac                 _rom_sha512_hmac
#define rom_sha512_hkdf                 _rom_sha512_hkdf
// curve25519
#define curve25519_donna                _curve25519_donna
// aes
#define aes_init                        _aes_init
#define aes_encrypt_key128              _aes_encrypt_key128
#define aes_encrypt_key192              _aes_encrypt_key192
#define aes_encrypt_key256              _aes_encrypt_key256
#define aes_encrypt_key                 _aes_encrypt_key
#define aes_decrypt_key128              _aes_decrypt_key128
#define aes_decrypt_key192              _aes_decrypt_key192
#define aes_decrypt_key256              _aes_decrypt_key256
#define aes_decrypt_key                 _aes_decrypt_key
#define aes_test_alignment_detection    _aes_test_alignment_detection
#define aes_ecb_encrypt                 _aes_ecb_encrypt
#define aes_ecb_decrypt                 _aes_ecb_decrypt
#define aes_cbc_encrypt                 _aes_cbc_encrypt
#define aes_cbc_decrypt                 _aes_cbc_decrypt
#define aes_mode_reset                  _aes_mode_reset
#define aes_cfb_encrypt                 _aes_cfb_encrypt
#define aes_cfb_decrypt                 _aes_cfb_decrypt
#define aes_ofb_crypt                   _aes_ofb_crypt
#define aes_ctr_crypt                   _aes_ctr_crypt

/* Use AES encrypt/decrypt in wlan ROM codes */
#define aes_set_key                     _aes_set_key
#define aes_encrypt                     _aes_encrypt
#define aes_decrypt                     _aes_decrypt

#endif // ROM_APPLE_FUNC_RENAME_H