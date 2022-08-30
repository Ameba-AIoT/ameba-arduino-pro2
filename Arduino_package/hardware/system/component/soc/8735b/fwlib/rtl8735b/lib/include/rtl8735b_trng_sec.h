/**************************************************************************//**
 * @file     rtl8735b_trng_sec.h
 * @brief    The HAL related definition and macros for the trng device.
 *           Includes Registers and data type definition.
 * @version  V1.00
 * @date     2021-12-22
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
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
 ******************************************************************************/

#ifndef _RTL8735B_TRNG_SEC_H_
#define _RTL8735B_TRNG_SEC_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "rtl8735b_trng_type.h"

#define TRNG_LFSR_POLY_LSB_PTN          (0xA5A55A5A)
#define TRNG_LFSR_POLY_MSB_PTN          (0x55AAAA55)

//
// Error index
//
/// Pointer which points to NULL Error.
#define _ERRNO_TRNG_SEC_NULL_POINTER                              (0x10)
/// TRNG doesn't initialize Error.
#define _ERRNO_TRNG_SEC_ENGINE_NOT_INIT                           (0x11)


enum {
	TRNG_HI_CLK_SEL0                = 0x0,
	TRNG_HI_CLK_SEL1                = 0x1
};

enum {
	TRNG_LO_CLK_SEL0                = 0x0,
	TRNG_LO_CLK_SEL1                = 0x1
};

enum {
	TRNG_RNG_MODE_0     = 0x0,
	TRNG_RNG_MODE_1     = 0x1
};

enum {
	TRNG_RBC_SAMPLE_BYPASS          = 0x0,
	TRNG_RBC_SAMPLE_RATE_4VALID     = 0x1,
	TRNG_RBC_SAMPLE_RATE_2VALID     = 0x2
};

enum {
	TRNG_HSPEED_SEL0                = 0x0,
	TRNG_HSPEED_SEL1                = 0x1
};

enum {
	TRNG_LFSR_BYPASS                  = 0x0,
	TRNG_LFSR_MOD1_SEL0_MOD2_SEL0     = 0x1,
	TRNG_LFSR_MOD1_SEL1_MOD2_SEL0     = 0x2,
	TRNG_LFSR_MOD1_SEL0_MOD2_SEL1     = 0x3,
	TRNG_LFSR_MOD1_SEL1_MOD2_SEL1     = 0x4
};

enum {
	TRNG_CMP_REP_BIT_MODE           = 0x0,
	TRNG_CMP_REP_BYTE_MODE          = 0x1
};

enum {
	TRNG_CMP_ADPT1_BIT_ADPT2_BIT_MODE    = 0x0,
	TRNG_CMP_ADPT1_BYTE_ADPT2_BIT_MODE   = 0x1,
	TRNG_CMP_ADPT1_BIT_ADPT2_BYTE_MODE   = 0x2,
	TRNG_CMP_ADPT1_BYTE_ADPT2_BYTE_MODE  = 0x3
};

enum {
	TRNG_ADPT1_WINDOW_SEL0    = 0x0,
	TRNG_ADPT1_WINDOW_SEL1    = 0x1,
	TRNG_ADPT1_WINDOW_SEL2    = 0x2,
	TRNG_ADPT1_WINDOW_SEL3    = 0x3
};

enum {
	TRNG_ADPT2_WINDOW_SEL0    = 0x0,
	TRNG_ADPT2_WINDOW_SEL1    = 0x1,
	TRNG_ADPT2_WINDOW_SEL2    = 0x2,
	TRNG_ADPT2_WINDOW_SEL3    = 0x3
};

typedef struct hal_trng_sec_adapter_s {
	TRNG_TypeDef *base_addr;    //!< The trng registers base address
	uint8_t    isInit;
	uint8_t    resv1[3];

	uint8_t    rng_mode;
	uint8_t    selft_en;
	uint8_t    rbc_sel;
	uint8_t    hspeed_sel;

	uint8_t    lfsr_mod;
	uint8_t    cmp_rep_mode;
	uint8_t    cmp_adpt_mode;
	uint8_t    resv2;

	uint8_t    adpt1_window_sel;
	uint8_t    adpt2_window_sel;
	uint8_t    hi_clk_sel;
	uint8_t    lo_clk_sel;

	uint32_t   chk_ready_cnt_max;

	uint32_t   resv3[10];
} hal_trng_sec_adapter_t, *phal_trng_sec_adapter_t;

hal_status_t hal_rtl_trng_sec_init(hal_trng_sec_adapter_t *ptrng_adp);
hal_status_t hal_rtl_trng_sec_deinit(hal_trng_sec_adapter_t *ptrng_adp);
hal_status_t hal_rtl_trng_sec_set_clk(hal_trng_sec_adapter_t *ptrng_adp, uint8_t sel_val);
hal_status_t hal_rtl_trng_sec_swrst_en(hal_trng_sec_adapter_t *ptrng_adp);
uint32_t hal_rtl_trng_sec_get_rand(hal_trng_sec_adapter_t *ptrng_adp);
hal_status_t hal_rtl_trng_sec_set_normal_ctrl(hal_trng_sec_adapter_t *ptrng_adp, uint8_t rng_mode, uint8_t rbc_sel, uint8_t hspeed_sel);
hal_status_t hal_rtl_trng_sec_set_lfsr_ctrl(hal_trng_sec_adapter_t *ptrng_adp, uint8_t lfsr_mod, uint32_t poly_lsb, uint32_t poly_msb);
hal_status_t hal_rtl_trng_sec_set_selft_ctrl(hal_trng_sec_adapter_t *ptrng_adp, uint8_t selft_en, uint8_t cmp_rep_mode, uint8_t cmp_adpt_mode,
		uint8_t adpt1_window_sel, uint8_t adpt2_window_sel);
hal_status_t hal_rtl_trng_sec_load_default_setting(hal_trng_sec_adapter_t *ptrng_adp, uint8_t selft_en);


/**
  \brief  The data structure of the stubs function for the trng HAL functions in ROM
*/
typedef struct hal_trng_sec_func_stubs_s {
	hal_status_t (*hal_trng_sec_init)(hal_trng_sec_adapter_t *ptrng_adp);
	hal_status_t (*hal_trng_sec_deinit)(hal_trng_sec_adapter_t *ptrng_adp);
	hal_status_t (*hal_trng_sec_set_clk)(hal_trng_sec_adapter_t *ptrng_adp, uint8_t sel_val);
	hal_status_t (*hal_trng_sec_swrst_en)(hal_trng_sec_adapter_t *ptrng_adp);
	uint32_t (*hal_trng_sec_get_rand)(hal_trng_sec_adapter_t *ptrng_adp);
	hal_status_t (*hal_trng_sec_set_normal_ctrl)(hal_trng_sec_adapter_t *ptrng_adp, uint8_t rng_mode, uint8_t rbc_sel, uint8_t hspeed_sel);
	hal_status_t (*hal_trng_sec_set_lfsr_ctrl)(hal_trng_sec_adapter_t *ptrng_adp, uint8_t lfsr_mod, uint32_t poly_lsb, uint32_t poly_msb);
	hal_status_t (*hal_trng_sec_set_selft_ctrl)(hal_trng_sec_adapter_t *ptrng_adp, uint8_t selft_en, uint8_t cmp_rep_mode, uint8_t cmp_adpt_mode,
			uint8_t adpt1_window_sel, uint8_t adpt2_window_sel);
	hal_status_t (*hal_trng_sec_load_default_setting)(hal_trng_sec_adapter_t *ptrng_adp, uint8_t selft_en);
	uint32_t reserved[14];  // reserved space for next ROM code version function table extending.
} hal_trng_sec_func_stubs_t;


#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _RTL8735B_TRNG_SEC_H_"

