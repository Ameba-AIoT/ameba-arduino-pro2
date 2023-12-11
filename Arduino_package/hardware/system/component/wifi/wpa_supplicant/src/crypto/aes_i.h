/*
 * AES (Rijndael) cipher
 * Copyright (c) 2003-2012, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef AES_I_H
#define AES_I_H

#include "aes.h"
#include "../crypto/rom/rom_wps_aes_i.h"

/* #define FULL_UNROLL */
#define AES_SMALL_TABLES

#ifndef AES_SMALL_TABLES

#define RCON(i) rcon[(i)]

#define TE0(i) rom_wps_Te0[((i) >> 24) & 0xff]
#define TE1(i) rom_wps_Te1[((i) >> 16) & 0xff]
#define TE2(i) rom_wps_Te2[((i) >> 8) & 0xff]
#define TE3(i) rom_wps_Te3[(i) & 0xff]
#define TE41(i) (rom_wps_Te4[((i) >> 24) & 0xff] & 0xff000000)
#define TE42(i) (rom_wps_Te4[((i) >> 16) & 0xff] & 0x00ff0000)
#define TE43(i) (rom_wps_Te4[((i) >> 8) & 0xff] & 0x0000ff00)
#define TE44(i) (rom_wps_Te4[(i) & 0xff] & 0x000000ff)
#define TE421(i) (rom_wps_Te4[((i) >> 16) & 0xff] & 0xff000000)
#define TE432(i) (rom_wps_Te4[((i) >> 8) & 0xff] & 0x00ff0000)
#define TE443(i) (rom_wps_Te4[(i) & 0xff] & 0x0000ff00)
#define TE414(i) (rom_wps_Te4[((i) >> 24) & 0xff] & 0x000000ff)
#define TE411(i) (rom_wps_Te4[((i) >> 24) & 0xff] & 0xff000000)
#define TE422(i) (rom_wps_Te4[((i) >> 16) & 0xff] & 0x00ff0000)
#define TE433(i) (rom_wps_Te4[((i) >> 8) & 0xff] & 0x0000ff00)
#define TE444(i) (rom_wps_Te4[(i) & 0xff] & 0x000000ff)
#define TE4(i) (rom_wps_Te4[(i)] & 0x000000ff)

#define TD0(i) rom_wps_Td0[((i) >> 24) & 0xff]
#define TD1(i) rom_wps_Td1[((i) >> 16) & 0xff]
#define TD2(i) rom_wps_Td2[((i) >> 8) & 0xff]
#define TD3(i) rom_wps_Td3[(i) & 0xff]
#define TD41(i) (rom_wps_Td4[((i) >> 24) & 0xff] & 0xff000000)
#define TD42(i) (rom_wps_Td4[((i) >> 16) & 0xff] & 0x00ff0000)
#define TD43(i) (rom_wps_Td4[((i) >> 8) & 0xff] & 0x0000ff00)
#define TD44(i) (rom_wps_Td4[(i) & 0xff] & 0x000000ff)
#define TD0_(i) rom_wps_Td0[(i) & 0xff]
#define TD1_(i) rom_wps_Td1[(i) & 0xff]
#define TD2_(i) rom_wps_Td2[(i) & 0xff]
#define TD3_(i) rom_wps_Td3[(i) & 0xff]

#else /* AES_SMALL_TABLES */

// #define RCON(i) ((u32) rcons[(i)] << 24)

// static inline u32 rotr(u32 val, int bits)
// {
// 	return (val >> bits) | (val << (32 - bits));
// }
#define rcons rom_wps_rcons
#define TE0(i) rom_wps_Te0[((i) >> 24) & 0xff]
#define TE1(i) rotr(rom_wps_Te0[((i) >> 16) & 0xff], 8)
#define TE2(i) rotr(rom_wps_Te0[((i) >> 8) & 0xff], 16)
#define TE3(i) rotr(rom_wps_Te0[(i) & 0xff], 24)
#define TE41(i) ((rom_wps_Te0[((i) >> 24) & 0xff] << 8) & 0xff000000)
#define TE42(i) (rom_wps_Te0[((i) >> 16) & 0xff] & 0x00ff0000)
#define TE43(i) (rom_wps_Te0[((i) >> 8) & 0xff] & 0x0000ff00)
#define TE44(i) ((rom_wps_Te0[(i) & 0xff] >> 8) & 0x000000ff)
#define TE421(i) ((rom_wps_Te0[((i) >> 16) & 0xff] << 8) & 0xff000000)
#define TE432(i) (rom_wps_Te0[((i) >> 8) & 0xff] & 0x00ff0000)
#define TE443(i) (rom_wps_Te0[(i) & 0xff] & 0x0000ff00)
#define TE414(i) ((rom_wps_Te0[((i) >> 24) & 0xff] >> 8) & 0x000000ff)
#define TE411(i) ((rom_wps_Te0[((i) >> 24) & 0xff] << 8) & 0xff000000)
#define TE422(i) (rom_wps_Te0[((i) >> 16) & 0xff] & 0x00ff0000)
#define TE433(i) (rom_wps_Te0[((i) >> 8) & 0xff] & 0x0000ff00)
#define TE444(i) ((rom_wps_Te0[(i) & 0xff] >> 8) & 0x000000ff)
#define TE4(i) ((rom_wps_Te0[(i)] >> 8) & 0x000000ff)

#define TD0(i) rom_wps_Td0[((i) >> 24) & 0xff]
#define TD1(i) rotr(rom_wps_Td0[((i) >> 16) & 0xff], 8)
#define TD2(i) rotr(rom_wps_Td0[((i) >> 8) & 0xff], 16)
#define TD3(i) rotr(rom_wps_Td0[(i) & 0xff], 24)
#define TD41(i) ((u32) rom_wps_Td4s[((i) >> 24) & 0xff] << 24)
#define TD42(i) ((u32) rom_wps_Td4s[((i) >> 16) & 0xff] << 16)
#define TD43(i) ((u32) rom_wps_Td4s[((i) >> 8) & 0xff] << 8)
#define TD44(i) ((u32) rom_wps_Td4s[(i) & 0xff])
#define TD0_(i) rom_wps_Td0[(i) & 0xff]
#define TD1_(i) rotr(rom_wps_Td0[(i) & 0xff], 8)
#define TD2_(i) rotr(rom_wps_Td0[(i) & 0xff], 16)
#define TD3_(i) rotr(rom_wps_Td0[(i) & 0xff], 24)

#endif /* AES_SMALL_TABLES */

#ifdef _MSC_VER
#define SWAP(x) (_lrotl(x, 8) & 0x00ff00ff | _lrotr(x, 8) & 0xff00ff00)
#define GETU32(p) SWAP(*((u32 *)(p)))
#define PUTU32(ct, st) { *((u32 *)(ct)) = SWAP((st)); }
#else
#define GETU32(pt) (((u32)(pt)[0] << 24) ^ ((u32)(pt)[1] << 16) ^ \
((u32)(pt)[2] <<  8) ^ ((u32)(pt)[3]))
#define PUTU32(ct, st) { \
(ct)[0] = (u8)((st) >> 24); (ct)[1] = (u8)((st) >> 16); \
(ct)[2] = (u8)((st) >>  8); (ct)[3] = (u8)(st); }
#endif

#define AES_PRIV_SIZE (4 * 4 * 15 + 4)
#define AES_PRIV_NR_POS (4 * 15)

int rijndaelKeySetupEnc(u32 rk[], const u8 cipherKey[], int keyBits);

#endif /* AES_I_H */
