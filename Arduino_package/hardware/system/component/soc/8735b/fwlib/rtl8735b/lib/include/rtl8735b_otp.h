/**************************************************************************//**
 * @file     rtl8735b_otp.h
 * @brief    The HAL related definition and macros for the OTP device.
 *           Includes Registers and data type definition.
 * @version  V1.00
 * @date     2021-08-05
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2020 Realtek Corporation. All rights reserved.
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

#ifndef _RTL_8735B_OTP_H_
#define _RTL_8735B_OTP_H_

#include "rtl8735b_aon_type.h"
#include "rtl8735b_syson_type.h"
#include "rtl8735b_syson_s_type.h"

#ifdef __cplusplus
extern "C" {
#endif


#define AON_BASE_REG        ((volatile AON_TypeDef *)(0))
#define PON_BASE_REG        ((volatile PON_TypeDef *)(0))
#define SYSON_BASE_REG      ((volatile SYSON_TypeDef *)(0))
#define SYSON_S_BASE_REG    ((volatile SYSON_S_TypeDef *)(0))

#define OTP_ENABLE      1
#define OTP_DISABLE     0
#define OTP_DEFAULT_SLPCEN_DLY    100
#define OTP_DEFAULT_PCEN_DLY    500
#define OTP_DEFAULT_WR_DLY      500
#define OTP_DEFAULT_RD_DLY      100

#define OTP_RW_TO_CNT           1000
#define OTP_WR_CHK_INTV         100
#define OTP_RD_CHK_INTV         100

#define OTP_WR_GRNT_CODE        0x69
#define OTP_ADDR_MSK            0x07FF
#define OTP_DATA_MSK            0xFF
#define OTP_RET_FAIL_FLG        0x80000000
#define OTP_TEST_MOD_MSK        0x07
#define OTP_TEST_ROW_MSK        0x01
#define OTP_DSB_EN_MSK          0x01
#define OTP_RB_EN_MSK           0x01
#define OTP_CZ_EN_MSK           0x01
#define OTP_PRCT_EN_MSK         0x01
#define OTP_PRCT_SZ_WL_MSK      0x01
#define OTP_AL_CTRL_MSK         0x07
#define OTP_ALDN_STS_MSK        0x01
#define OTP_AL_STS_MSK          0x03
#define OTP_BUST_EN_MSK         0x01

#define OTP_CZ_STS_ALL          0xFFFFFFFF
#define OTP_PRCT_STS_ALL        0xFFFFFFFF
#define OTP_MEM_SIZE            (uint32_t)2048
#define OTP_LGL_SIZE            (uint32_t)2048

#define OTP_PHY_RSVD_LEN        4
#define OTP_LGL_WE_NUM          4

#define OTP_LGL_ENY_HDR1_OFF    0
#define OTP_LGL_ENY_HDR0_OFF    1
#define OTP_LGL_ENY_DATA_OFF    2

#define OTP_SHIFT_LGL_PFX       4
#define OTP_LGL_PFX_MSK         0xF0
#define OTP_LGL_PFX_VAL         0x3

#define OTP_SHIFT_LGL_OFF1      0
#define OTP_LGL_OFF1_MSK        0x0F
#define OTP_SHIFT_LGL_OFFH      4

#define OTP_SHIFT_LGL_OFF0      4
#define OTP_LGL_OFF0_MSK        0xF0
#define OTP_SHIFT_LGL_OFFL      4

#define OTP_LGL_OFFH_MSK        0xF0
#define OTP_LGL_OFFL_MSK        0x0F

#define OTP_SHIFT_LGL_WE        0                           /* word enable */
#define OTP_LGL_WE              0x0F

#define OTP_LGL_END_ADDR        (uint32_t)528
#define OTP_LGL_ENTY_LEN        (uint32_t)10
#define OTP_LGL_FULL_ENY_DAT_LEN    8
#define OTP_LGL_ONE_DAT_LEN     2

#define OTP_PRCT_CRC_LEN        2

#define OTP_SC_DAT_LEN          4
#define OTP_S_KEY_DAT_LEN       32
#define OTP_SS_KEY_DAT_LEN      32
#define OTP_UID_DAT_LEN         5
#define OTP_CID_DAT_LEN         8
#define OTP_COMP_DAT_LEN        8
#define OTP_ADC_DAT_LEN         24
#define OTP_WLRF_DAT_LEN        80
#define OTP_RMA_ZERO_B_LEN      8
#define OTP_RMA_MG_NUM_LEN      8
#define OTP_SZ_RSVD2_LEN        16
#define OTP_SZ_RSVD1_LEN        32

#define OTP_SZ_KEY_LK_LEN           4
#define OTP_SZ_RMA_DAT_LK_LEN       1
#define OTP_SZ_RSVD1_LK_LEN         4
#define OTP_SZ_RSVD2_LK_LEN         2

#define OTP_SC_DAT_ADDR             0x0
#define OTP_S_KEY_ROTPK_RMA_HSH_ADDR    0x1D0
#define OTP_S_KEY_SEC_RMA_ADDR      0x1F0

#define OTP_S_KEY_DAT_ADDR          0x250
#define OTP_SS_KEY_DAT_ADDR         0x370
#define OTP_UID_DAT_ADDR            0x490
#define OTP_CID_DAT_ADDR            0x498
#define OTP_COMP_DAT_ADDR           0x4A0
#define OTP_ADC_DAT_ADDR            0x4A8
#define OTP_WLRF_DAT_ADDR           0x4C0
#define OTP_SZ_LK_ADDR              0x350
#define OTP_SSZ_LK_ADDR             0x49F
#define OTP_SZ_LK_VAL               0X00

#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define OTP_SC_DAT_PRCT_IDX_ADDR        0x5F0
#define OTP_SC_DAT_PRCT_ADDR            0x5F1
#define OTP_LGL_DAT_PRCT_ADDR           0x601
#define OTP_S_KEY_DAT_PRCT_ADDR         0x707
#define OTP_SS_KEY_DAT_PRCT_ADDR        0x719
#define OTP_UID_DAT_PRCT_IDX_ADDR       0x72B
#define OTP_UID_DAT_PRCT_ADDR           0x72C
#define OTP_CID_DAT_PRCT_IDX_ADDR       0x73C
#define OTP_CID_DAT_PRCT_ADDR           0x73D
#define OTP_COMP_DAT_PRCT_ADDR          0x74D
#define OTP_ADC_DAT_PRCT_ADDR           0x74F
#define OTP_WLRF_DAT_PRCT_IDX_ADDR      0x751
#define OTP_WLRF_DAT_PRCT_ADDR          0x752

#define OTP_CZ_DAT_ADDR                 0x762
#else
#define OTP_SC_DAT_PRCT_IDX_ADDR        0x5F0
#define OTP_SC_DAT_PRCT_ADDR            0x5F2
#define OTP_LGL_DAT_PRCT_ADDR           0x602
#define OTP_S_KEY_DAT_PRCT_ADDR         0x708
#define OTP_SS_KEY_DAT_PRCT_ADDR        0x71A
#define OTP_UID_DAT_PRCT_IDX_ADDR       0x72C
#define OTP_UID_DAT_PRCT_ADDR           0x72D
#define OTP_CID_DAT_PRCT_IDX_ADDR       0x73E
#define OTP_CID_DAT_PRCT_ADDR           0x73F
#define OTP_COMP_DAT_PRCT_ADDR          0x750
#define OTP_ADC_DAT_PRCT_ADDR           0x752
#define OTP_WLRF_DAT_PRCT_IDX_ADDR      0x754
#define OTP_WLRF_DAT_PRCT_ADDR          0x755

#define OTP_CZ_DAT_ADDR                 0x766
#endif



/** \brief OTP control selection
*/
enum otp_ctrl_sel_e {
	OTPCtrlAon       =   0,                    /*!< 0: for OTP access control by AON */
	OTPCtrlSys       =   1,                    /*!< 1: for OTP access control by SYSON */
};

/** \brief OTP normal mode
*/
enum otp_mode_e {
	OTPRdMod           =   0,                  /*!< 0: for OTP read mode    */
	OTPALEnMod         =   1,                  /*!< 1: for OTP autoload enable mode   */
	OTPWrMod           =   2,                  /*!< 1: for OTP write mode   */
	OTPCmpMod          =   3,                  /*!< 1: for OTP compare mode   */
};

/** \brief OTP test mode
*/
enum otp_test_mode_e {
	OTPTestUserMOd      =   0,                  /*!< 0: for OTP user mode */
	OTPIniMarRdMod      =   1,                  /*!< 1: for OTP initial margin read mode   */
	OTPPgMarRdMod       =   2,                  /*!< 2: for OTP program margin read mode   */
	OTPAutoRpMarRdMOd   =   4,                  /*!< 4: for OTP auto repair margin read mode   */
	OTPRpMarRdMOd       =   5,                  /*!< 5: for OTP repair margin read mode   */
	OTPRpChkMod         =   6,                  /*!< 6: for OTP repair check mode   */
	OTPRpPgMod          =   7,                  /*!< 7: for OTP repair program mode   */
};

/** \brief OTP key counting zero selection
*/
enum otp_key_cz_sel_e {
	OTPCzRotpk1cz       =   1,                  /*!< 1: for OTP ROTPK1 counting zero select */
	OTPCzRotpk2cz       =   2,                  /*!< 2: for OTP ROTPK2 counting zero select */
	OTPCzIPsec1cz       =   3,                  /*!< 3: for OTP IPSEC1 counting zero select */
	OTPCzIPsec2cz       =   4,                  /*!< 4: for OTP IPSEC2 counting zero select */
	OTPCzEcdsa1cz       =   5,                  /*!< 5: for OTP ECDSA1 counting zero select */
	OTPCzEcdsa2cz       =   6,                  /*!< 6: for OTP ECDSA2 counting zero select */
	OTPCzRsvd1cz        =   7,                  /*!< 7: for OTP RSVD1 counting zero select */
	OTPCzRsvd2cz        =   8,                  /*!< 8: for OTP RSVD2 counting zero select */
	OTPCzRsvdcz         =   9,                  /*!< 9: for OTP RSVD1 counting zero select */
	OTPCzHukcz          =   10,                 /*!< 10: for OTP HUK counting zero select */
	OTPCzHukRsvdcz      =   11,                 /*!< 11: for OTP HUK RSVD counting zero select */
	OTPCzJtagS1cz       =   12,                 /*!< 12: for OTP JTAG S1 counting zero select */
	OTPCzJtagS2cz       =   13,                 /*!< 13: for OTP JTAG S2 counting zero select */
	OTPCzJtagNS1cz      =   14,                 /*!< 14: for OTP JTAG NS1 counting zero select */
	OTPCzJtagNS2cz      =   15,                 /*!< 15: for OTP JTAG NS2 counting zero select */
	OTPCzRsipK1cz       =   16,                 /*!< 16: for OTP RSIP K1 counting zero select */
	OTPCzRsipK2cz       =   17,                 /*!< 17: for OTP RSIP K2 counting zero select */
	OTPCzSSRsvdcz       =   18,                 /*!< 17: for OTP SS RSVD counting zero select */
};

/** \brief OTP key protection selection
*/
enum otp_key_prct_sel_e {
	OTPPrctScSts        =   1,                  /*!< 1: for OTP secure control protection select */
	OTPPrctLzSts        =   2,                  /*!< 1: for OTP logical zone proctection select */
};

/** \brief OTP autoload done status selection
*/
enum otp_aldn_sts_sel_e {
	OTPAlAonDnSts       =   4,                  /*!< 4: for OTP AON autoload done status select */
	OTPAlPonDnSts       =   5,                  /*!< 5: for OTP PON autoload done status select */
	OTPAlSysonDnSts     =   6,                  /*!< 6: for OTP SYSON autoload done status select */
};

/** \brief OTP autoload status selection
*/
enum otp_al_sts_sel_e {
	OTPAlAonSts       =   8,                    /*!< 8: for OTP AON autoload status select */
	OTPAlPonSts       =   10,                   /*!< 10: for OTP PON autoload status select */
	OTPAlSysonSts     =   12,                   /*!< 12: for OTP SYSON autoload status select */
};

/** \brief OTP autoload status
*/
enum otp_al_sts_e {
	OTPAlErrCrc       =   1,                    /*!< 1: for OTP autoload error because of CRC error */
	OTPAlSuccess      =   3,                    /*!< 3: for OTP autoload successful */
};

/** \brief OTP autoload target selection
*/
enum otp_al_trg_sel_e {
	OTPAlAonEn       =   1,                    /*!< 1: for OTP AON autoload enable */
	OTPAlPonEn       =   2,                    /*!< 2: for OTP PON autoload enable */
	OTPAlSysonEn     =   4,                    /*!< 2: for OTP SYSON autoload enable */
};

/** \brief OTP general return status
*/
enum otp_gl_sts_e {
	OTPStsSuccess       =   0,                    /*!< 0: for OTP success status */
	OTPStsFailed        =   1,                    /*!< 1: for OTP failed status */
};

/** \brief OTP compare result
*/
enum otp_cmp_rslt_e {
	OTPCmpPass       =   0,                    /*!< 0: for OTP compare pass */
	OTPCmpFail       =   1,                    /*!< 1: for OTP compare fail */
};


enum high_val_sz_wlock_offset_e {
	SZ_WLOCK_ROTPK1_HSH_OFFSET          = 0x0,
	SZ_WLOCK_ROTPK2_HSH_OFFSET          = 0x4,
	SZ_WLOCK_IPSEC_CIPHER1_OFFSET       = 0x8,
	SZ_WLOCK_IPSEC_CIPHER2_OFFSET       = 0xC,
	SZ_WLOCK_ECDSA_PRIV1_OFFSET         = 0x10,
	SZ_WLOCK_ECDSA_PRIV2_OFFSET         = 0x14,
	SZ_WLOCK_RESV1_OFFSET               = 0x18,
	SZ_WLOCK_RMA_ZERO_OFFSET            = 0x1C,
	SZ_WLOCK_RMA_MGN_OFFSET             = 0x1D,
	SZ_WLOCK_RESV2_OFFSET               = 0x1E,
};

enum high_val_sz_wlock_obj_e {
	SZ_WLOCK_ROTPK1_HSH                 = 0x0,
	SZ_WLOCK_ROTPK2_HSH                 = 0x1,
	SZ_WLOCK_IPSEC_CIPHER1              = 0x2,
	SZ_WLOCK_IPSEC_CIPHER2              = 0x3,
	SZ_WLOCK_ECDSA_PRIV1                = 0x4,
	SZ_WLOCK_ECDSA_PRIV2                = 0x5,
	SZ_WLOCK_RESV1                      = 0x6,
	SZ_WLOCK_RMA_ZERO                   = 0x7,
	SZ_WLOCK_RMA_MGN                    = 0x8,
	SZ_WLOCK_RESV2                      = 0x9,
};

enum high_val_ssz_rwlock_obj_e {
	SSZ_RWLOCK_HUK1                     = 0x0,
	SSZ_RWLOCK_HUK2                     = 0x1,
	SSZ_RWLOCK_SJTAG_S1                 = 0x2,
	SSZ_RWLOCK_SJTAG_S2                 = 0x3,
	SSZ_RWLOCK_SJTAG_NS1                = 0x4,
	SSZ_RWLOCK_SJTAG_NS2                = 0x5,
	SSZ_RWLOCK_SEC_KEY1                 = 0x6,
	SSZ_RWLOCK_SEC_KEY2                 = 0x7,
	SSZ_RWLOCK_RMA_HUK                  = 0x8,
};

/**
  \brief  The data structure for an OTP port HAL operations.
*/
typedef struct hal_otp_adapter_s {
	uint32_t        slpc_en_dly;                /* power cut enable small delay count (us) */
	uint32_t        pc_en_dly;                  /* power cut enable delay count (us) */
	uint32_t        wr_dly;                     /* write delay count (us) */
	uint32_t        rd_dly;                     /* read delay count (us) */
} hal_otp_adapter_t, *phal_otp_adapter_t;

/**
  \brief  The data structure of the stubs functions of the UART HAL functions in ROM.
*/
typedef struct hal_otp_func_stubs_s {
	phal_otp_adapter_t *ppotp_adapter;
	void (*hal_otp_init)(void);
	void (*hal_otp_deinit)(void);
	void (*hal_otp_ctrl_sel)(uint8_t otp_ctrl_sel);
	uint8_t (*hal_otp_ctrl_sel_sts)(void);
	void (*hal_otp_pmc_gnt_ctrl)(uint8_t gnt_en);
	void (*hal_otp_wr_gnt_ctrl)(uint8_t gnt_en);
	void (*hal_otpc_ctrl)(uint8_t otpc_en, uint8_t wclk_en, uint8_t rclk_en);
	uint32_t (*hal_otp_pwr_ctrl)(uint8_t pwr_en);
	void (*hal_otp_test_mod_cfg)(uint8_t test_mod);
	void (*hal_otp_test_row_ctrl)(uint8_t test_row_en);
	uint32_t (*hal_otp_chk_err_sts)(void);
	void (*hal_otp_dsb_ctrl)(uint8_t dsb_en);
	void (*hal_otp_rb_ctrl)(uint8_t rb_en);
	void (*hal_otp_cz_ctrl)(uint8_t cz_en);
	uint32_t (*hal_otp_chk_cz_sts)(uint32_t key_sel);
	uint32_t (*hal_otp_clr_cz_sts)(uint32_t key_sel);
	uint32_t (*hal_otp_prct_ctrl)(uint8_t prct_en);
	uint32_t (*hal_otp_chk_prct_sts)(uint32_t prct_sel);
	uint32_t (*hal_otp_rd_lz_er_addr)(void);
	uint32_t (*hal_otp_clr_prct_sts)(uint32_t prct_sel);
	uint32_t (*hal_otp_rd_sz_prct_sts)(void);
	uint32_t (*hal_otp_clr_sz_prct_sts)(uint32_t sz_prct_sts_sel);
	uint32_t (*hal_otp_rd_ssz_prct_sts)(void);
	uint32_t (*hal_otp_clr_ssz_prct_sts)(uint32_t ssz_prct_sts_sel);
	uint32_t (*hal_otp_szwl_ctrl)(uint32_t sz_wl_en);
	uint32_t (*hal_otp_rd_aldn_sts)(uint32_t aldn_sts_sel);
	uint32_t (*hal_otp_clr_aldn_sts)(uint32_t aldn_sts_sel);
	uint32_t (*hal_otp_rd_al_sts)(uint32_t al_sts_sel);
	uint32_t (*hal_otp_clr_al_sts)(uint32_t al_sts_sel);
	uint32_t (*hal_otp_al_cfg)(uint32_t al_trg_sel);
	uint32_t (*hal_otp_al_ctrl_aon)(uint32_t al_en);
	uint32_t (*hal_otp_bust_ctrl)(uint8_t bust_en);
	uint32_t (*hal_otp_rd_sub_aon)(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
	uint32_t (*hal_otp_rd_aon)(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
	uint8_t (*hal_otp_byte_rd_aon)(uint32_t addr);
	uint32_t (*hal_otp_wr_sub_aon)(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
	uint32_t (*hal_otp_wr_aon)(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
	void (*hal_otp_byte_wr_aon)(uint32_t addr, uint8_t wr_data);
	uint32_t (*hal_otp_cmp_aon)(uint32_t addr, uint8_t cmp_data);
	uint32_t (*hal_otp_rd_sub_sys)(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
	uint32_t (*hal_otp_rd_sys)(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
	uint8_t (*hal_otp_byte_rd_sys)(uint32_t addr);
	uint32_t (*hal_otp_wr_sub_sys)(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
	uint32_t (*hal_otp_wr_sys)(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
	void (*hal_otp_byte_wr_sys)(uint32_t addr, uint8_t wr_data);
	uint32_t (*hal_otp_cmp_sys)(uint32_t addr, uint8_t cmp_data);
	uint32_t (*hal_otp_al_ctrl_sys)(uint32_t al_en);
	uint32_t (*hal_otp_rd_sub_syss)(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
	uint32_t (*hal_otp_rd_syss)(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
	uint8_t (*hal_otp_byte_rd_syss)(uint32_t addr);
	uint32_t (*hal_otp_wr_sub_syss)(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
	uint32_t (*hal_otp_wr_syss)(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
	void (*hal_otp_byte_wr_syss)(uint32_t addr, uint8_t wr_data);
	uint32_t (*hal_otp_cmp_syss)(uint32_t addr, uint8_t cmp_data);
	uint32_t (*hal_otp_al_ctrl_syss)(uint32_t al_en);
	uint8_t (*hal_otp_byte_wr_marr_aon)(uint32_t addr, uint8_t wr_data, uint8_t adj_vol);
	uint8_t (*hal_otp_byte_wr_marr_sys)(uint32_t addr, uint8_t wr_data, uint8_t adj_vol);
	uint8_t (*hal_otp_byte_wr_marr_syss)(uint32_t addr, uint8_t wr_data, uint8_t adj_vol);
	uint8_t *hal_otp_adj_vol_lvl;
	uint8_t (*hal_otp_rp_mar_rd_syss)(uint8_t auto_en);
	uint8_t (*hal_otp_rp_chk_syss)(void);
	uint8_t (*hal_otp_rp_pg_syss)(void);
	void (*hal_otp_set_aon_vol)(uint8_t aon_vol);

	uint32_t (*hal_otp_sz_key_wr)(uint8_t sz_key_idx, uint8_t *wr_data);
	uint32_t (*hal_otp_sz_key_rd)(uint8_t sz_key_idx, uint8_t *rd_data);
	uint32_t (*hal_otp_sz_key_lock)(uint8_t sz_key_idx);
	uint32_t (*hal_otp_ssz_key_wr)(uint8_t ssz_key_idx, uint8_t *wr_data);
	uint32_t (*hal_otp_ssz_key_rd)(uint8_t ssz_key_idx, uint8_t *rd_data);
	uint32_t reserved[3];  // reserved space for next ROM code version function table extending.
} hal_otp_func_stubs_t;

void hal_rtl_otp_init(void);
void hal_rtl_otp_deinit(void);
void hal_rtl_otp_ctrl_sel(uint8_t otp_ctrl_sel);
uint8_t hal_rtl_otp_ctrl_sel_sts(void);
void hal_rtl_otp_pmc_gnt_ctrl(uint8_t gnt_en);
void hal_rtl_otp_wr_gnt_ctrl(uint8_t gnt_en);
void hal_rtl_otpc_ctrl(uint8_t otpc_en, uint8_t wclk_en, uint8_t rclk_en) ;
uint32_t hal_rtl_otp_pwr_ctrl(uint8_t pwr_en);
void hal_rtl_otp_test_mod_cfg(uint8_t test_mod);
void hal_rtl_otp_test_row_ctrl(uint8_t test_row_en);
uint32_t hal_rtl_otp_chk_err_sts(void);
void hal_rtl_otp_dsb_ctrl(uint8_t dsb_en);
void hal_rtl_otp_rb_ctrl(uint8_t rb_en);
void hal_rtl_otp_cz_ctrl(uint8_t cz_en);
uint32_t hal_rtl_otp_chk_cz_sts(uint32_t key_sel);
uint32_t hal_rtl_otp_clr_cz_sts(uint32_t key_sel);
uint32_t hal_rtl_otp_prct_ctrl(uint8_t prct_en);
uint32_t hal_rtl_otp_chk_prct_sts(uint32_t prct_sel);
uint32_t hal_rtl_otp_rd_lz_er_addr(void);
uint32_t hal_rtl_otp_clr_prct_sts(uint32_t prct_sel);
uint32_t hal_rtl_otp_rd_sz_prct_sts(void);
uint32_t hal_rtl_otp_clr_sz_prct_sts(uint32_t sz_prct_sts_sel);
uint32_t hal_rtl_otp_rd_ssz_prct_sts(void);
uint32_t hal_rtl_otp_clr_ssz_prct_sts(uint32_t ssz_prct_sts_sel);
uint32_t hal_rtl_otp_szwl_ctrl(uint32_t sz_wl_en);
uint32_t hal_rtl_otp_rd_aldn_sts(uint32_t aldn_sts_sel);
uint32_t hal_rtl_otp_clr_aldn_sts(uint32_t aldn_sts_sel);
uint32_t hal_rtl_otp_rd_al_sts(uint32_t al_sts_sel);
uint32_t hal_rtl_otp_clr_al_sts(uint32_t al_sts_sel);
uint32_t hal_rtl_otp_al_cfg(uint32_t al_trg_sel);
uint32_t hal_rtl_otp_al_ctrl_aon(uint32_t al_en);
uint32_t hal_rtl_otp_bust_ctrl(uint8_t bust_en);
/*-----------------------------------------------------------------------------------------------------*/
uint32_t hal_rtl_otp_rd_sub_aon(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint32_t hal_rtl_otp_rd_aon(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint8_t hal_rtl_otp_byte_rd_aon(uint32_t addr);
uint32_t hal_rtl_otp_wr_sub_aon(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
uint32_t hal_rtl_otp_wr_aon(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
void hal_rtl_otp_byte_wr_aon(uint32_t addr, uint8_t wr_data);
uint32_t hal_rtl_otp_cmp_aon(uint32_t addr, uint8_t cmp_data);
/*-----------------------------------------------------------------------------------------------------*/
uint32_t hal_rtl_otp_rd_sub_sys(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint32_t hal_rtl_otp_rd_sys(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint8_t hal_rtl_otp_byte_rd_sys(uint32_t addr);
uint32_t hal_rtl_otp_wr_sub_sys(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
uint32_t hal_rtl_otp_wr_sys(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
void hal_rtl_otp_byte_wr_sys(uint32_t addr, uint8_t wr_data);
uint32_t hal_rtl_otp_cmp_sys(uint32_t addr, uint8_t cmp_data);
uint32_t hal_rtl_otp_al_ctrl_sys(uint32_t al_en);
/*-----------------------------------------------------------------------------------------------------*/
uint32_t hal_rtl_otp_rd_sub_syss(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint32_t hal_rtl_otp_rd_syss(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint8_t hal_rtl_otp_byte_rd_syss(uint32_t addr);
uint32_t hal_rtl_otp_wr_sub_syss(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
uint32_t hal_rtl_otp_wr_syss(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
void hal_rtl_otp_byte_wr_syss(uint32_t addr, uint8_t wr_data);
uint32_t hal_rtl_otp_cmp_syss(uint32_t addr, uint8_t cmp_data);
uint32_t hal_rtl_otp_al_ctrl_syss(uint32_t al_en);

uint8_t hal_rtl_otp_byte_wr_marr_aon(uint32_t addr, uint8_t wr_data, uint8_t adj_vol);
uint8_t hal_rtl_otp_byte_wr_marr_sys(uint32_t addr, uint8_t wr_data, uint8_t adj_vol);
uint8_t hal_rtl_otp_byte_wr_marr_syss(uint32_t addr, uint8_t wr_data, uint8_t adj_vol);

uint8_t hal_rtl_otp_rp_mar_rd_syss(uint8_t auto_en);
uint8_t hal_rtl_otp_rp_chk_syss(void);
uint8_t hal_rtl_otp_rp_pg_syss(void);
void hal_rtl_otp_set_aon_vol(uint8_t aon_vol);

uint32_t hal_rtl_otp_sz_key_wr(uint8_t sz_key_idx, uint8_t *wr_data);
uint32_t hal_rtl_otp_sz_key_rd(uint8_t sz_key_idx, uint8_t *rd_data);
uint32_t hal_rtl_otp_sz_key_lock(uint8_t sz_key_idx);
uint32_t hal_rtl_otp_ssz_key_wr(uint8_t ssz_key_idx, uint8_t *wr_data);
uint32_t hal_rtl_otp_ssz_key_rd(uint8_t ssz_key_idx, uint8_t *rd_data);



#ifdef __cplusplus
}
#endif

#endif  // #ifndef _RTL_8735B_OTP_H_


