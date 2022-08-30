#ifndef __DPP_COMMON_H__
#define __DPP_COMMON_H__
#include "dpp.h"

int dpp_random(void *p_rng, u8 *output, size_t output_len);
int dpp_check_and_set_para(dpp_adapter *pdpp_adapter);
int get_public_key_info_from_der_encoded(dpp_adapter *pdpp_adapter, u8 *BI_der,
		u32 BI_der_len, u8	*public_key_x, u8 *public_key_y);
int dpp_generate_QR_code(dpp_adapter *pdpp_adapter, u8 *out_QR, u32 *QR_len);
void dpp_set_ie(u8 *packet, u8 *attr_info, u16 attr_id, u16 len);
u8	*dpp_get_ie(u8 *pbuf, u8 index[], u32 *len, sint limit);
void dpp_sha_hash(dpp_adapter *pdpp_adapter, u8 *input, u32 input_len, u8 *output);
#endif



