/**************************************************************************//**
* @file        rtl8735b_sys_ctrl.h
* @brief       The HAL API implementation for SYSTEM CONTROL
*
* @version     V1.00
* @date        2022-07-22
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



#ifndef _RTL8735B_SYS_CTRL_H_
#define _RTL8735B_SYS_CTRL_H_
//#include "cmsis.h"
#include "rtl8735b_syson_s_type.h"
#include "rtl8735b_trng_sec.h"

#ifdef  __cplusplus
extern "C"
{
#endif

#define BOOT_LOAD_IMG_VRF_HASH_DIGEST_SIZE      (32)
#define BOOT_CUSTOM_UID_DERIVED_SIZE            (32)
#define BOOT_INFO_SW_RESV_MAX_SIZE              (5)
#define OTP_CHIP_ID_MAX_SIZE                    (4)
#define OTP_UUID_MAX_DATA_SIZE                  (4)
#define SJTAG_NONFIXED_KEY_MAX_SIZE             (32)

#define LXBUS_SHARED_USED_NONE                  (0x0)

#define SW_BOOT_ROM_TRAP_W_PTN                  (0x5A)
#define SW_BOOT_ROM_TRAP_W_PTN_BITSHIFT         (8)
#define SW_BOOT_ROM_TRAP_W_PTN_BITMASK          (0xFF00)
#define SW_BOOT_ROM_TRAP_CTRL_BITMASK           (0xFF)

#define LFC_MAJOR_CTRL_MASK                 0xFFFFFF00
#define LFC_MAJOR_CTRL_SHIFT                8
#define LFC_MINOR_CTRL_MASK                 0x000000FF
#define LFC_MINOR_CTRL_SHIFT                0
#define LFC_CTRL_DEF(minor, major)      ((major << LFC_MAJOR_CTRL_SHIFT) | \
                                         ((minor & LFC_MINOR_CTRL_MASK) << LFC_MINOR_CTRL_SHIFT))

typedef enum {
	RMA_NORMAL_STATE   = 0x00,
	RMA_STATE0         = 0xA0,
	RMA_STATE1         = 0xA1,
	RMA_STATE2         = 0xA2
} RMA_STATE_T;

typedef enum {
	LFC_CHIP_MANU_ID         = 0xFF,
	LFC_DEVICE_MANU_ID       = 0x7E,
	LFC_DEVICE_DEPOLYED_ID   = 0x3C,
	LFC_DEVICE_RMA1_ID       = 0x18,
	LFC_DEVICE_RMA2_ID       = 0x0,
	LFC_PROT_DEVICE_DEPY_ID  = 0x5E

} DEVICE_LFC_STS_T;

typedef enum {
	LFC_UNKNOWN_CTRL         = 0x0,
	LFC_DEVE_OPEN            = 0x33,
	LFC_DEVE_CLOSE           = 0x39,
	LFC_FORC_OPEN            = 0x93,
	LFC_FORC_CLOSE           = 0x99,
	LFC_CUST_CTRL            = 0xAA,
} DEVICE_LFC_CTRL_STS_T;

typedef enum {
	LFC_CTRL_TEST_M_FUNC   = 0xE73A7E,
	LFC_CTRL_NORM_M_FUNC   = 0xDB3ABD,
	LFC_CTRL_COMM_M_FUNC   = 0xBD3ADB,
} DEVICE_LFC_MAJOR_FUNC_T;

typedef enum {
	LFC_PG_FLOW_ENTER      =  LFC_CTRL_DEF(0x01, LFC_CTRL_TEST_M_FUNC),
	LFC_PG_DBG_SUP         =  LFC_CTRL_DEF(0x02, LFC_CTRL_TEST_M_FUNC),
	LFC_PG_LOG_SUP         =  LFC_CTRL_DEF(0x03, LFC_CTRL_TEST_M_FUNC),
} DEVICE_LFC_TEST_M_FUNC_T;

typedef enum {
	LFC_SBL_EN             =  LFC_CTRL_DEF(0x01, LFC_CTRL_NORM_M_FUNC),
	LFC_NORM_UBOOT         =  LFC_CTRL_DEF(0x02, LFC_CTRL_NORM_M_FUNC),
	LFC_NORM_DEV_SUP       =  LFC_CTRL_DEF(0x03, LFC_CTRL_NORM_M_FUNC),
	LFC_IMG_FAIL_RBK_SUP   =  LFC_CTRL_DEF(0x04, LFC_CTRL_NORM_M_FUNC),
} DEVICE_LFC_NORM_M_FUNC_T;

typedef enum {
	LFC_COMM_STDIO_EN      =  LFC_CTRL_DEF(0x01, LFC_CTRL_COMM_M_FUNC),
	LFC_DBGGER_EN          =  LFC_CTRL_DEF(0x02, LFC_CTRL_COMM_M_FUNC),
	LFC_HIGH_VAL_LOCK_EN   =  LFC_CTRL_DEF(0x03, LFC_CTRL_COMM_M_FUNC),
	LFC_SAFE_DATA_OP_EN    =  LFC_CTRL_DEF(0x04, LFC_CTRL_COMM_M_FUNC),
	LFC_FOOT_OP_EN         =  LFC_CTRL_DEF(0x05, LFC_CTRL_COMM_M_FUNC),
	LFC_ADV_LOG_LVL_EN     =  LFC_CTRL_DEF(0x06, LFC_CTRL_COMM_M_FUNC),
	LFC_COMM_DBG_EN        =  LFC_CTRL_DEF(0x07, LFC_CTRL_COMM_M_FUNC),
	LFC_COMM_MEMDBG_EN     =  LFC_CTRL_DEF(0x08, LFC_CTRL_COMM_M_FUNC),
	LFC_COMM_CRITICMD_SUP  =  LFC_CTRL_DEF(0x09, LFC_CTRL_COMM_M_FUNC),
} DEVICE_LFC_COMM_M_FUNC_T;

typedef enum {
	PHY_SBL_DIS_CTRL_ID             = 0x31,
	PHY_IMG_DIS_LDFAIL_ROLLBACK_ID  = 0x32,
	PHY_SAFE_DATA_DIS_CTRL_ID       = 0x33,
	PHY_SAFE_DATA_DLY_DIS_CTRL_ID   = 0x34,
	PHY_DBGER_CTRL_ID               = 0x35,
} OTP_PHY_LD_CFG_T;

typedef enum {
	LFC_AUTOLD_SBL_CTRL_ID                  = 0x51,
	LFC_AUTOLD_SAFE_DATA_CTRL_ID            = 0x52,
	LFC_AUTOLD_SAFE_DATA_DLY_CTRL_ID        = 0x53,
	LFC_AUTOLD_DBGER_CTRL_ID                = 0x54,
	LFC_AUTOLD_STDIO_EN_CTRL_ID             = 0x55,
	LFC_AUTOLD_ADV_LOG_LVL_CTRL_ID          = 0x56,
} OTP_LFC_AUTO_LD_CFG_T;

typedef enum {
	SJTAG_S_NONFIXED_K      = 0x1,
	SJTAG_NS_NONFIXED_K     = 0x2
} SJTAG_SET_NONFIXED_OBJ_T;

typedef enum {
	SJTAG_CTRL_DIS     = 0x0,
	SJTAG_CTRL_PWD_EN  = 0x1,
	SJTAG_CTRL_RESV    = 0x2,
	SJTAG_CTRL_EN      = 0x3
} SJTAG_CTRL_STATE_T;

typedef enum {
	VIDEO_INFO_NN   = 9,
	VIDEO_INFO_H265 = 10,
	VIDEO_INFO_ENC  = 11,
	VIDEO_INFO_ISP  = 12,
	VIDEO_INFO_ALL  = 0xFF,
} VIDEO_INFO_IDX_T;

typedef enum {
	BOOT_INFO_IDX0  = 0,
	BOOT_INFO_IDX1  = 1,
	BOOT_INFO_IDX2  = 2,
	BOOT_INFO_IDX3  = 3,
	BOOT_INFO_IDX4  = 4
} BOOT_INFO_IDX_T;

typedef enum {
	LXBUS_CTRL_SNAND        = 0x0,
	LXBUS_CTRL_CRYPTO       = 0x1,
	LXBUS_CTRL_SDHOST       = 0x2,
	LXBUS_CTRL_MII          = 0x3,
	LXBUS_CTRL_I2S          = 0x4,
} LXBUS_SHARE_USED_IDX_T;

/**
* @addtogroup N/A
* @{
*/

typedef enum {
	EDDSA_SYS = 0,
	GPIO_SYS = 1,
	GPIO_PON = 2,
	GPIO_AON = 3,

	DDR_SYS = 4,

	GDMA0_SYS = 5,
	GDMA1_SYS = 6,
	FLASH_SYS = 7,
	SPI0_SYS = 8,
	SPI1_SYS = 9,
	HS_SPI0_SYS = 10,
	HS_SPI1_SYS = 11,
	UART0_SYS = 12,
	UART1_SYS = 13,
	UART2_SYS = 14,
	UART3_SYS = 15,
	UART4_SYS = 16,
	TIMER0_SYS = 17,
	TIMER1_SYS = 18,
	TIMER2_SYS = 19,
	TIMER3_SYS = 20,
	PWM_SYS = 21,
	RSA_SYS = 22,
	CRYPTO_SYS = 23,
	I2C0_SYS = 24,
	I2C1_SYS = 25,
	I2C2_SYS = 26,
	I2C3_SYS = 27,
	ECDSA_SYS = 28,
	ADC_SYS = 29,
	RTC_SYS = 30,
	SPORT_SYS = 31,
	I2S0_SYS = 32,
	I2S1_SYS = 33,
	LXBUS_SYS = 34,

	ISP_SYS = 35,
	MIPI_SYS = 36,
	ENC_SYS = 37,
	NN_SYS = 38,
	VOE_SYS = 39,

	CPU_SYS = 40,
	SGPIO_SYS = 41,
	TRNG_SYS = 42,

	SI_SYS = 43,
	AUDIO_CODEC_EN = 44,
	AUDIO_CODEC_SCLK_EN = 45,
	AUDIO_CODEC_PORB_EN = 46,
	AUDIO_CODEC_LDO_EN = 47,
	AUDIO_CODEC_EXTE_EN = 48,
	AUDIO_CODEC_LDO_TUNE = 49,
	TRNG_32K = 50,
	TRNG_128K = 51,
	LDO_SDIO_3V3_EN = 52,
	TRNG_SEC = 53,
	SDHOST_SYS = 54,
	SDHOST_CLK1_PHASE = 55,
	SDHOST_CLK2_PHASE = 56,
	LDO_SDIO_1V8_CTRL = 57,
	OTG_SYS_CTRL = 58,
	SNAND_SYS = 59,
	SNAND_MUX = 60,

} IPs_CLK_FUNC_t;

typedef enum {
	UART_IRC_4M = 0,
	UART_PERI_40M,
	UART_XTAL,
	RSVD
} UART0_CLK_SELECT_t;


typedef enum {
	ENC_166M = 0,   // SYS_PLL/3,  500Mhz or 300Mhz/3
	ENC_125M,       // SYS_PLL/4,  500Mhz or 300Mhz/4
	ENC_100M,       // Peri_PLL/4, 400Mhz/4=100Mhz
} ENC_CLK_SELECT_t;

typedef enum {
	CPU_500M = 0,   // CLK 500Mhz
	CPU_400M,       // CLK 400Mhz
	CPU_300M,       // CLK 300Mhz
} CPU_CLK_SELECT_t;


typedef enum {
	NN_500M = 0,   // CLK 500Mhz
	NN_400M,       // CLK 400Mhz
	NN_250M,       // CLK 2500Mhz
} NN_CLK_SELECT_t;

typedef enum {
	TRNG_HI_XTAL40M_LO32K  = 0,
	TRNG_HI_XTAL40M_LO128K = 1,
	TRNG_HI_PLL40M_LO32K   = 2,
	TRNG_HI_PLL40M_LO128K  = 3
} TRNG_CLK_SELECT_t;

typedef enum {
	FLASH_CTRL_CLK_SEL250M  = 0,
	FLASH_CTRL_CLK_SEL200M  = 1,
} NOR_FLH_CTRL_CLK_SELECT_t;

typedef enum {
	SW_PG_TRAP_CTRL_ID        = 0x0,
} SW_BOOT_ROM_TRAP_IDX_T;

typedef enum {
	SW_PG_TRAP_CTRL_SHIFT     = 0x0,
} SW_BOOT_ROM_TRAP_SHIFT_T;

typedef union {
	__IOM uint8_t byte;

	struct {
		__IOM uint8_t resolution           : 2;       /*!< [1..0]  */
		__IOM uint8_t mem_size_sel1        : 2;       /*!< [3..2]  */
		__IOM uint8_t mem_size_sel2        : 2;       /*!< [5..4]  */
		__IOM uint8_t dual_band            : 2;       /*!< [7..6]  */
	} bit;
} otp_chip_id0_t, *potp_chip_id0_t;

typedef union {
	__IOM uint8_t byte;

	struct {
		__IOM uint8_t mipi_intf_en         : 2;       /*!< [1..0]  */
		__IOM uint8_t isp_en               : 2;       /*!< [3..2] (2'b11:ON, 2'b10:OFF, 2'b01:OFF, 2'b00:ON) */
		__IOM uint8_t video_enc_sel        : 2;       /*!< [5..4] (2'b11:H.265+H.264, 2'b10:H.264, 2'b01:H.265+H.264, 2'b00:OFF)*/
		__IOM uint8_t lps_mode_en          : 2;       /*!< [7..6]  */
	} bit;
} otp_chip_id1_t, *potp_chip_id1_t;

typedef union {
	__IOM uint8_t byte;

	struct {
		__IOM uint8_t ddr2_3_sel           : 2;       /*!< [1..0]  */
		__IOM uint8_t nn_turn_key_sel      : 2;       /*!< [3..2]  */
		__IOM uint8_t nn_engine_en         : 2;       /*!< [5..4]  (2'b11:ON, 2'b10:OFF, 2'b01:OFF, 2'b00:ON) */
		__IOM uint8_t eth_en               : 2;       /*!< [7..6]  */
	} bit;
} otp_chip_id2_t, *potp_chip_id2_t;

typedef union {
	__IOM uint8_t byte;

	struct {
		__IM  uint8_t : 8;                        /*!< [7..0] Reserved */
	} bit;
} otp_chip_id3_t, *potp_chip_id3_t;

typedef union {
	__IOM uint32_t word;

	struct {
		otp_chip_id0_t cfg0;                 /*!< [0..7]   OTP chid0 defined at 0x498 */
		otp_chip_id1_t cfg1;                 /*!< [8..15]  OTP chid1 defined at 0x499 */
		otp_chip_id2_t cfg2;                 /*!< [16..23] OTP chid2 defined at 0x49A*/
		otp_chip_id3_t cfg3;                 /*!< [24..31] OTP chid3 defined at 0x49B */
	} byte;
} otp_chip_id_t, *potp_chip_id_t;

typedef enum {
	ISP_CHIP_ID_ON_1     = 0x0,
	ISP_CHIP_ID_OFF_1    = 0x1,
	ISP_CHIP_ID_OFF_2    = 0x2,
	ISP_CHIP_ID_ON_2     = 0x3,
} ISP_CHIP_ID_EN_CTRL_t;

typedef enum {
	V_EN_CHIP_ID_SEL_H265_H264_1  = 0x0,
	V_EN_CHIP_ID_SEL_OFF          = 0x1,
	V_EN_CHIP_ID_H264             = 0x2,
	V_EN_CHIP_ID_SEL_H265_H264_2  = 0x3,
} VIDEO_ENC_CHIP_ID_SEL_CTRL_t;

typedef enum {
	NN_ENG_CHIP_ID_ON_1     = 0x0,
	NN_ENG_CHIP_ID_OFF_1    = 0x1,
	NN_ENG_CHIP_ID_OFF_2    = 0x2,
	NN_ENG_CHIP_ID_ON_2     = 0x3,
} NN_ENG_CHIP_ID_EN_CTRL_t;

typedef enum {
	HIGH_VAL_RNG_INIT_NONE   = 0x0,
	HIGH_VAL_RNG_INIT_OK     = 0x5A,
	HIGH_VAL_RNG_INIT_FAIL   = 0x6F
} HIGH_VAL_RNG_STS_T;

typedef enum {
	HIGH_VAL_RNG_DELAYUNIT_SEL0   = 0x0,
	HIGH_VAL_RNG_DELAYUNIT_SEL1   = 0x1,
	HIGH_VAL_RNG_DELAYUNIT_SEL2   = 0x2,
	HIGH_VAL_RNG_DELAYUNIT_SEL3   = 0x3,
} HIGH_VAL_RNG_DELAY_T;

typedef hal_status_t (*hv_prot_trng_init_func_t)(void);
typedef hal_status_t (*hv_prot_trng_set_clk_func_t)(uint8_t sel_val);
typedef hal_status_t (*hv_prot_trng_swrst_en_func_t)(void);
typedef hal_status_t (*hv_prot_trng_ld_def_setting_func_t)(uint8_t selft_en);
typedef hal_status_t (*hv_prot_trng_deinit_func_t)(void);
typedef uint32_t (*hv_prot_trng_get_rand_func_t)(void);

typedef struct high_val_prot_adapter_s {
	volatile uint8_t init_sts;
	uint8_t    resv1[3];
	hv_prot_trng_init_func_t            trng_init_f;
	hv_prot_trng_set_clk_func_t         trng_set_clk_f;
	hv_prot_trng_swrst_en_func_t        trng_swrst_en_f;
	hv_prot_trng_ld_def_setting_func_t  trng_ld_def_setting_f;
	hv_prot_trng_deinit_func_t          trng_deinit_f;
	hv_prot_trng_get_rand_func_t        trng_get_rand_f;
	uint32_t   resv2[9];
} high_val_prot_adapter_t, *phigh_val_prot_adapter_t;



#if IS_AFTER_CUT_A(CONFIG_CHIP_VER)
void hal_rtl_sys_en_rma_mgn_pg(void);
#endif

void hal_rtl_sys_peripheral_en(uint8_t id, uint8_t en);
void hal_rtl_sys_lxbus_shared_en(uint8_t used_id, uint8_t en);
void hal_rtl_sys_set_clk(uint8_t id, uint8_t sel_val);
uint32_t hal_rtl_sys_get_clk(uint8_t id);

void hal_rtl_sys_boot_info_assign_val(uint8_t info_idx, uint32_t info_v);
uint32_t hal_rtl_sys_boot_info_get_val(uint8_t info_idx);
void hal_rtl_sys_boot_footpath_init(uint8_t info_idx);
void hal_rtl_sys_boot_footpath_store(uint8_t info_idx, uint8_t fp_v);
void hal_rtl_sys_boot_footpath_clear(uint8_t info_idx, uint8_t fp_v);
void hal_rtl_sys_sjtag_fixed_key_enable(void);
void hal_rtl_sys_sjtag_non_fixed_key_set(uint8_t set_sjtag_obj, uint8_t *pkey);
uint32_t hal_rtl_sys_get_video_info(uint8_t idx);
void hal_rtl_sys_set_video_info(uint8_t idx, uint8_t en_ctrl);
void hal_rtl_sys_get_chip_id(uint32_t *pchip_id);
uint8_t hal_rtl_sys_get_rma_state(void);
uint8_t hal_rtl_sys_get_lfc_state(void);
uint8_t hal_rtl_sys_get_lfc_state4ram(void);
uint8_t hal_rtl_sys_get_devrma2_lgl_en_sts(void);
void hal_rtl_sys_lfc_autold_precfg(const uint8_t lfc_state);
uint8_t hal_rtl_sys_chk_lfc_func_ctrl_sts(const uint32_t lfc_func_op);
uint8_t hal_rtl_sys_chk_lfc_func_ctrl_sts4ram(const uint32_t lfc_func_op);
uint8_t hal_rtl_sys_get_atld_cfg(const uint8_t op);
uint8_t hal_rtl_sys_get_phy_cfg(const uint8_t op_obj);
void hal_rtl_sys_high_value_assets_otp_lock(const uint8_t lock_obj);
uint32_t hal_rtl_sys_get_uuid(void);
uint8_t hal_rtl_sys_get_boot_select(void);

hal_status_t hal_rtl_sys_high_val_protect_trng_init(void);
hal_status_t hal_rtl_sys_high_val_protect_trng_set_clk(uint8_t sel_val);
hal_status_t hal_rtl_sys_high_val_protect_trng_swrst_en(void);
hal_status_t hal_rtl_sys_high_val_protect_trng_ld_def_setting(uint8_t selft_en);
hal_status_t hal_rtl_sys_high_val_protect_trng_deinit(void);
uint32_t hal_rtl_sys_high_val_protect_trng_get_rand(void);
void hal_rtl_sys_high_val_protect_init_hook(hv_prot_trng_init_func_t trng_init_f, hv_prot_trng_deinit_func_t trng_deinit_f,
		hv_prot_trng_ld_def_setting_func_t trng_ld_def_set_f, hv_prot_trng_get_rand_func_t trng_get_rand_f,
		hv_prot_trng_set_clk_func_t trng_set_clk_f, hv_prot_trng_swrst_en_func_t trng_swrst_enf_f);
void hal_rtl_sys_high_val_protect_init(void);
void hal_rtl_sys_high_val_protect_deinit(void);
void hal_rtl_sys_high_val_protect_ld(const uint32_t otp_addr, uint8_t *p_otp_v, const uint32_t ld_size);
void hal_rtl_sys_high_val_mem_protect_ld(void *s1, const void *s2, size_t ld_size);
void hal_rtl_sys_high_val_protect_ld_delay(uint8_t delay_unit_sel);
uint8_t hal_rtl_sys_check_high_val_protect_init(void);
hal_status_t hal_rtl_sys_adc_vref_setting(uint8_t set_value);
void hal_rtl_sys_get_sw_boot_rom_trap_op(uint8_t op_idx, void *p_m_status);
void hal_rtl_sys_set_sw_boot_rom_trap_op(uint8_t op_idx, uint8_t ctrl_status);
int hal_rtl_sys_high_val_protect_cmp(const void *a, const void *b, size_t size);
int hal_rtl_sys_flash_sec_aes_gcm_tag_cmp(const void *a, const void *b, size_t size);

#define ROM_FOOTPH_INIT(idx)                hal_rtl_sys_boot_footpath_init(idx)
#define ROM_FOOTPH_STORE(idx,fp_v)          hal_rtl_sys_boot_footpath_store(idx,fp_v)
#define ROM_FOOTPH_CLR(idx,fp_v)            hal_rtl_sys_boot_footpath_clear(idx,fp_v)


/**
  \brief  The data structure of the stubs function for the SYSON HAL functions in ROM
*/
typedef struct hal_sys_ctrl_func_stubs_s {
	void (*hal_sys_peripheral_en)(uint8_t id, uint8_t en);
	void (*hal_sys_set_clk)(uint8_t id, uint8_t sel_val);
	uint32_t (*hal_sys_get_clk)(uint8_t id);
	uint32_t (*hal_sys_boot_info_get_val)(uint8_t info_idx);
	void (*hal_sys_boot_info_assign_val)(uint8_t info_idx, uint32_t info_v);
	void (*hal_sys_boot_footpath_init)(uint8_t info_idx);
	void (*hal_sys_boot_footpath_store)(uint8_t info_idx, uint8_t fp_v);
	void (*hal_sys_sjtag_fixed_key_enable)(void);
	void (*hal_sys_sjtag_non_fixed_key_set)(uint8_t set_sjtag_obj, uint8_t *pkey);
	uint32_t (*hal_sys_get_video_info)(uint8_t idx);
	void (*hal_sys_set_video_info)(uint8_t idx, uint8_t en_ctrl);
	void (*hal_sys_get_chip_id)(uint32_t *pchip_id);
	void (*hal_sys_boot_footpath_clear)(uint8_t info_idx, uint8_t fp_v);
	uint8_t (*hal_sys_get_rma_state)(void);
	void (*hal_sys_high_value_assets_otp_lock)(const uint8_t lock_obj);
	uint32_t (*hal_sys_get_uuid)(void);
	void (*hal_sys_lxbus_shared_en)(uint8_t used_id, uint8_t en);
	hal_status_t (*hal_sys_adc_vref_setting)(uint8_t set_value);
	void (*hal_sys_set_sw_boot_rom_trap_op)(uint8_t op_idx, uint8_t ctrl_status);
	uint8_t (*hal_sys_get_atld_cfg)(const uint8_t op);
	uint8_t (*hal_sys_get_lfc_state)(void);
	uint8_t (*hal_sys_chk_lfc_func_ctrl)(const uint32_t lfc_func_op);
	uint32_t reserved[2];  // reserved space for next ROM code version function table extending.
} hal_sys_ctrl_func_stubs_t;

/**
  \brief  The data structure of the stubs function for the high value assets protect load functions of system ctrl in ROM
*/
typedef struct hal_sys_ctrl_high_val_prot_func_stubs_s {
	void (*hal_sys_high_val_protect_init_hook)(hv_prot_trng_init_func_t trng_init_f, hv_prot_trng_deinit_func_t trng_deinit_f,
			hv_prot_trng_ld_def_setting_func_t trng_ld_def_set_f, hv_prot_trng_get_rand_func_t trng_get_rand_f,
			hv_prot_trng_set_clk_func_t trng_set_clk_f, hv_prot_trng_swrst_en_func_t trng_swrst_enf_f);
	void (*hal_sys_high_val_protect_init)(void);
	void (*hal_sys_high_val_protect_deinit)(void);
	void (*hal_sys_high_val_protect_ld)(const uint32_t otp_addr, uint8_t *p_otp_v, const uint32_t ld_size);
	void (*hal_sys_high_val_protect_ld_delay)(uint8_t delay_unit_sel);
	uint8_t (*hal_sys_check_high_val_protect_init)(void);
	int (*hal_sys_high_val_protect_cmp)(const void *a, const void *b, size_t size);
	void (*hal_sys_high_val_mem_protect_ld)(void *s1, const void *s2, size_t ld_size);
} hal_sys_ctrl_high_val_prot_func_stubs_t;

typedef struct hal_sys_ctrl_extend_func_stubs_s {
	uint8_t *pld_img_bl_vrf_digest;
	uint8_t *pcust_uid_derived;
	uint32_t reserved[30];  // reserved space for next ROM code version function table extending.
} hal_sys_ctrl_extend_func_stubs_t;

/** @} */ /* End of group hs_hal_efuse */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _RTL8735B_SYS_CTRL_H_"


