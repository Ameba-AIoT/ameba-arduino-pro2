/**
  ******************************************************************************
  * @file    rmesh_config.h
  * @author
  * @version V1.0.0
  * @date    2019-11-28
  * @brief   This file contains the network config of mesh.
  ******************************************************************************
  * @attention
  *
  * This module is a confidential and proprietary property of RealTek and
  * possession or use of this module requires written permission of RealTek.
  *
  * Copyright(c) 2019, Realtek Semiconductor Corporation. All rights reserved.
  ******************************************************************************
  */
#ifndef _RTL_MESH_SECURITY_H_
#define _RTL_MESH_SECURITY_H_

#define ENCRYPT_OFFSET		8

/* Should change for different device, RSA key is
 * generated on PC */
#define RSA_N   "9292758453063D803DD603D5E777D788" \
				"8ED1D5BF35786190FA2F23EBC0848AEA" \
				"DDA92CA6C3D80B32C4D109BE0F36D6AE" \
				"7130B9CED7ACDF54CFC7555AC14EEBAB" \
				"93A89813FBF3C4F8066D2D800F7C38A8" \
				"1AE31942917403FF4946B0A83D3D3E05" \
				"EE57C6F5F5606FB5D4BC6CD34EE0801A" \
				"5E94BB77B07507233A0BC7BAC8F90F79"

#define RSA_E   "10001"

#define RSA_D   "24BF6185468786FDD303083D25E64EFC" \
				"66CA472BC44D253102F8B4A9D3BFA750" \
				"91386C0077937FE33FA3252D28855837" \
				"AE1B484A8A9A45F7EE8C0C634F99E8CD" \
				"DF79C5CE07EE72C7F123142198164234" \
				"CABB724CF78B8173B9F880FC86322407" \
				"AF1FEDFDDE2BEB674CA15F3E81A1521E" \
				"071513A1E85B5DFA031F21ECAE91A34D"

#define RSA_P   "C36D0EB7FCD285223CFB5AABA5BDA3D8" \
				"2C01CAD19EA484A87EA4377637E75500" \
				"FCB2005C5C7DD6EC4AC023CDA285D796" \
				"C3D9E75E1EFC42488BB4F1D13AC30A57"

#define RSA_Q   "C000DF51A7C77AE8D7C7370C1FF55B69" \
				"E211C2B9E5DB1ED0BF61D0D9899620F4" \
				"910E4168387E3C30AA1E00C339A79508" \
				"8452DD96A9A5EA5D9DCA68DA636032AF"

#define RSA_DP  "C1ACF567564274FB07A0BBAD5D26E298" \
				"3C94D22288ACD763FD8E5600ED4A702D" \
				"F84198A5F06C2E72236AE490C93F07F8" \
				"3CC559CD27BC2D1CA488811730BB5725"

#define RSA_DQ  "4959CBF6F8FEF750AEE6977C155579C7" \
				"D8AAEA56749EA28623272E4F7D0592AF" \
				"7C1F1313CAC9471B5C523BFE592F517B" \
				"407A1BD76C164B93DA2D32A383E58357"

#define RSA_QP  "9AE7FBC99546432DF71896FC239EADAE" \
				"F38D18D2B2F0E2DD275AA977E2BF4411" \
				"F5A3B2A5D33605AEBBCCBA7FEB9F2D2F" \
				"A74206CEC169D74BF5A8C50D6F48EA08"

extern int myrand(void *rng_state, unsigned char *output, size_t len);
extern int real_mesh_rsa_init(struct rmesh_config_priv *mesh_network_config);

int real_mesh_aes_encrypt(u8 *key, u8 *data, int data_len, u8 *ciphertext);
u8 real_mesh_aes_decrypt(u8 *key, u8 *data, int data_len, u8 *Plaintext);

u32 real_mesh_security_padding(u8 *data, u32 len);
u32 real_mesh_security_remove_padding(u8 *data, u32 len);

void real_mesh_issue_aes_key_req();
int real_mesh_on_aes_key_rsp(u8 *pframe, int len);

#endif
