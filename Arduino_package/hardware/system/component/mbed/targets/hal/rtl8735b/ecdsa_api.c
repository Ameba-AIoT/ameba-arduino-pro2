
/**************************************************************************//**
 * @file     ecdsa_api.c
 * @brief    This file implements the SGPIO Mbed HAL API functions.
 *
 * @version  V1.00
 * @date     2017-05-03
 *
 * @note
 *
 ******************************************************************************
 * @attention
 *
 * Copyright(c) 2007 - 2022 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */
#include "objects.h"
#include "ecdsa_api.h"
#include "hal_ecdsa.h"


void ecdsa_init(ecdsa_t *obj)
{
	hal_ecdsa_adapter_t *pecdsa_adapter = &obj->ecdsa_adapter;
	u32 sta;

	sta = hal_ecdsa_init(pecdsa_adapter);

	if (sta != 0x00) {
		DBG_ECDSA_ERR("ecdsa_init error \r\n");
	}
}

void ecdsa_cb_irq_handler(ecdsa_t *obj, ecdsa_irq_handler handler, void *parg)
{
	hal_ecdsa_adapter_t *pecdsa_adapter = &obj->ecdsa_adapter;

	hal_ecdsa_cb_handler(pecdsa_adapter, (ecdsa_irq_user_cb_t)handler, parg);
}

void ecdsa_set_curve(ecdsa_t *obj, ecdsa_curve_para_t *pecdsa_curve_para)
{
	hal_ecdsa_adapter_t *pecdsa_adapter = &obj->ecdsa_adapter;
	hal_ecdsa_curve_table_t curve_table_tp;

	curve_table_tp.ppoint_x = pecdsa_curve_para->ppoint_x;
	curve_table_tp.ppoint_y = pecdsa_curve_para->ppoint_y;
	curve_table_tp.pa_adr = pecdsa_curve_para->pa_adr;
	curve_table_tp.pprime = pecdsa_curve_para->pprime;
	curve_table_tp.porder_n = pecdsa_curve_para->porder_n;

	hal_ecdsa_set_curve(pecdsa_adapter, pecdsa_curve_para->curve, &curve_table_tp, pecdsa_curve_para->bit_num);

	if (pecdsa_curve_para->bit_num != ECDSA_L_256) {
		hal_ecdsa_hash_256_en(pecdsa_adapter, ENABLE);
	} else {
		hal_ecdsa_hash_256_en(pecdsa_adapter, DISABLE);
	}

}

void ecdsa_signature(ecdsa_t *obj, u32 *pprivate_key, u32 *prandom_k)
{
	hal_ecdsa_adapter_t *pecdsa_adapter = &obj->ecdsa_adapter;

	hal_ecdsa_set_mode(pecdsa_adapter, ECDSA_SIGN, ECDSA_NONE);

	hal_ecdsa_signature(pecdsa_adapter, pprivate_key, prandom_k);
}

void ecdsa_verificaion(ecdsa_t *obj, u32 *ppublic_key_x, u32 *ppublic_key_y, u32 *pr, u32 *ps)
{
	hal_ecdsa_adapter_t *pecdsa_adapter = &obj->ecdsa_adapter;
	hal_ecdsa_veri_input_t veri_in;

	hal_ecdsa_set_mode(pecdsa_adapter, ECDSA_VERI, ECDSA_NONE);

	veri_in.ppub_key_x = ppublic_key_x;
	veri_in.ppub_key_y = ppublic_key_y;
	veri_in.pr_adr = pr;
	veri_in.ps_adr = ps;
	hal_ecdsa_verify(pecdsa_adapter, &veri_in);

}

void ecdsa_hash(ecdsa_t *obj, u32 *phash)
{
	hal_ecdsa_adapter_t *pecdsa_adapter = &obj->ecdsa_adapter;

	hal_ecdsa_hash(pecdsa_adapter, phash);
}

void ecdsa_deinit(ecdsa_t *obj)
{
	hal_ecdsa_adapter_t *pecdsa_adapter = &obj->ecdsa_adapter;
	u32 sta;

	sta = hal_ecdsa_deinit(pecdsa_adapter);

	if (sta != 0x00) {
		DBG_ECDSA_ERR("ecdsa_deinit error \r\n");
	}
}

u32 ecdsa_get_err_sta(ecdsa_t *obj)
{
	hal_ecdsa_adapter_t *pecdsa_adapter = &obj->ecdsa_adapter;

	return hal_ecdsa_get_err_sta(pecdsa_adapter);
}

void ecdsa_get_pbk(ecdsa_t *obj, u32 *ppub_key_x, u32 *ppub_key_y)
{
	hal_ecdsa_adapter_t *pecdsa_adapter = &obj->ecdsa_adapter;

	hal_ecdsa_get_pbk(pecdsa_adapter, ppub_key_x, ppub_key_y);
}

void ecdsa_get_rs(ecdsa_t *obj, u32 *pr_adr, u32 *ps_adr)
{
	hal_ecdsa_adapter_t *pecdsa_adapter = &obj->ecdsa_adapter;

	hal_ecdsa_get_rs(pecdsa_adapter, pr_adr, ps_adr);
}

void ecdsa_get_result_x_y(ecdsa_t *obj, u32 *prx_adr, u32 *pry_adr)
{
	hal_ecdsa_adapter_t *pecdsa_adapter = &obj->ecdsa_adapter;

	hal_ecdsa_get_result_x_y(pecdsa_adapter, prx_adr, pry_adr);
}

u32 ecdsa_get_veri_result(ecdsa_t *obj)
{
	hal_ecdsa_adapter_t *pecdsa_adapter = &obj->ecdsa_adapter;

	return hal_ecdsa_get_veri_result(pecdsa_adapter);
}

void ecdsa_gen_public_key(ecdsa_t *obj, uint32_t *ppriv_key, uint32_t *ppoint_x, uint32_t *ppoint_y)
{
	hal_ecdsa_adapter_t *pecdsa_adapter = &obj->ecdsa_adapter;

	hal_ecdsa_gen_public_key(pecdsa_adapter, ppriv_key, ppoint_x, ppoint_y);
}

void ecdsa_select_prk(ecdsa_t *obj, ecdsa_sel_prk sel_private_key)
{
	hal_ecdsa_adapter_t *pecdsa_adapter = &obj->ecdsa_adapter;

	hal_ecdsa_select_prk(pecdsa_adapter, sel_private_key);
}

