#ifndef _ROM_HOMEKIT_ED25519_H_
#define _ROM_HOMEKIT_ED25519_H_

#define ED25519_SKEY_LEN      32
#define ED25519_PUBKEY_LEN    32
#define ED25519_SIG_SIZE      64

int rom_ed25519_gen_keypair(unsigned char pk[ED25519_PUBKEY_LEN],
							unsigned char skpk[ED25519_SKEY_LEN + ED25519_PUBKEY_LEN],
							unsigned char seed[ED25519_SKEY_LEN]);

int rom_ed25519_gen_signature(unsigned char sig[ED25519_SIG_SIZE],
							  const unsigned char *m, unsigned long long mlen,
							  const unsigned char skpk[ED25519_SKEY_LEN + ED25519_PUBKEY_LEN]);

int rom_ed25519_verify_signature(const unsigned char sig[ED25519_SIG_SIZE],
								 const unsigned char *m, unsigned long long mlen,
								 const unsigned char pk[ED25519_PUBKEY_LEN]);

#endif	/* _ROM_HOMEKIT_ED25519_H_ */
