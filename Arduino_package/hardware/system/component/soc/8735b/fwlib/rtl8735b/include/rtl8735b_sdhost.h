/**************************************************************************//**
 * @file    rtl8735b_sdhost.h
 * @brief    The HAL related definition and macros for SD Host controller.
 * @version V1.00
 * @date    2021-10-25
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
#ifndef _RTL8735B_SDHOST_H_
#define _RTL8735B_SDHOST_H_

#include "rtl8735b_sdhost_type.h"
#include "static_assert.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup hal_sdhost HAL SDHOST
 * @ingroup 8735b_hal
 * @{
 * @brief The SD Host module.
 */

/// Defines the size of SD data block in byte
#define SD_BLK_LEN                   512
/// Defines the length of CSD register in byte
#define SD_CSD_LEN                   16
/// Defines the buffer length for storing the returned data of CMD6, R2 response, etc.
#define SDHOST_C6R2_BUF_LEN          64
/// Defines the size of card status data structure in byte
#define SD_CARD_STAT_LEN             4
/// Defines the size of SD SCR in byte
#define SD_SCR_LEN                   8
/// Defines the size of SD CID in byte
#define SD_CID_LEN                   16
/// Defines the size of SD status data structure in byte
#define SD_STATUS_LEN                64

/**
  \brief  Defines SDIO Bus Signaling Level.
*/
enum hal_sdhost_signal_level {
	SdHostSigVol33          = 0,
	SdHostSigVol18          = 1
};
typedef uint8_t hal_sdhost_sig_lvl_t;

/**
  \brief  Defines verbose level.
*/
enum hal_sdhost_verbose_level {
	SdHostVerNone           = 0,        /// No verbose print
	SdHostVerLessErr        = 0x8,      /// Convert some error log to warning, used in internal tuning
	SdHostVerInfo           = 0x10,     /// Print card info during card identification
	SdHostVerCmd            = 0x20,     /// Print every sent command
};

/**
  \brief  Defines CMD6 function group 1 (access mode).
*/
enum hal_sdhost_bus_speed {
	SdHostSpeedNA           = 0x00,
	SdHostSpeedDS           = 0x01,  // 3.3V Function 0
	SdHostSpeedHS           = 0x02,  // 3.3V Function 1
	SdHostSpeedSDR12        = 0x04,  // 1.8V Function 0
	SdHostSpeedSDR25        = 0x08,  // 1.8V Function 1
	SdHostSpeedSDR50        = 0x10,  // 1.8V Function 2
	SdHostSpeedSDR104       = 0x20,  // 1.8V Function 3
	SdHostSpeedDDR50        = 0x40,  // 1.8V Function 4
};
typedef uint32_t hal_sdhost_speed_t;

/**
  \brief  Bus frequency of SD bus.
*/
enum hal_sdhost_freq {
	SdHostFreq390KHz       = 0x1,
	SdHostFreq25MHz,
	SdHostFreq50MHz,
	SdHostFreq100MHz,
};
typedef uint8_t hal_sdhost_freq_t;

/**
  \brief  SD CID register version 1.0.
*/
typedef struct hal_sdhost_csd_v1 {
	u8 crc;
	u8 file_format;
	u8 tmp_write_prot;
	u8 perm_write_prot;
	u8 copy;
	u8 file_format_grp;
	u8 write_bl_partial;
	u8 write_bl_len;
	u8 r2w_factor;
	u8 wp_grp_enable;
	u8 wp_grp_size;
	u8 sector_size;
	u8 erase_blk_en;
	u8 c_size_mult;
	u8 vdd_w_curr_max;
	u8 vdd_w_curr_min;
	u8 vdd_r_curr_max;
	u8 vdd_r_curr_min;
	u32 c_size;
	u8 dsr_imp;
	u8 rd_blk_misalign;
	u8 wr_blk_misalign;
	u8 read_bl_partial;
	u8 read_bl_len;
	u16 ccc;
	u8 tran_speed;
	u8 nsac;
	u8 taac;
	u8  csd_structure;
} hal_sdhost_csd_v1_t;

/**
  \brief  SD CID register version 2.0.
*/
typedef struct hal_sdhost_csd_v2 {
	u8  crc;
	u8  file_format;
	u8  tmp_write_prot;
	u8  perm_write_prot;
	u8  copy;
	u8  file_format_grp;
	u8  write_bl_partial;
	u8  write_bl_len;
	u8  r2w_factor;
	u8  wp_grp_enable;
	u8  wp_grp_size;
	u8  sector_size;
	u8  erase_blk_en;
	u32 c_size;
	u8  dsr_imp;
	u8  rd_blk_misalign;
	u8  wr_blk_misalign;
	u8  read_bl_partial;
	u8  read_bl_len;
	u16 ccc;
	u8  tran_speed;
	u8  nsac;
	u8  taac;
	u8  csd_structure;
} hal_sdhost_csd_v2_t;


/**
  \brief  Compound version of SD CID register.
*/
typedef struct hal_sdhost_csd {
	u8 version;
	union {
		hal_sdhost_csd_v1_t v1;
		hal_sdhost_csd_v2_t v2;
	};
} hal_sdhost_csd_t;

/**
  \brief  Card status defined in SD spec.
*/
typedef struct hal_sdhost_card_stat {
	u8 rsvd1            : 3;
	u8 ask_seq_err      : 1;
	u8 rsvd2            : 1;
	u8 app_cmd          : 1;
	u8 rsvd3            : 2;
	u8 ready_for_data   : 1;
	u8 current_state    : 4;
	u8 erase_reset      : 1;
	u8 card_ecc_dis     : 1;
	u8 wp_erase_skip    : 1;
	u8 csd_overwrite    : 1;
	u8 rsvd4            : 2;
	u8 error            : 1;
	u8 cc_error         : 1;
	u8 card_ecc_failed  : 1;
	u8 illegal_cmd      : 1;
	u8 com_crc_err      : 1;
	u8 lock_unlock_fail : 1;
	u8 card_locked      : 1;
	u8 wp_violation     : 1;
	u8 erase_param      : 1;
	u8 erase_seq_err    : 1;
	u8 blk_len_err      : 1;
	u8 addre_err        : 1;
	u8 out_of_range     : 1;
} hal_sdhost_card_stat_t;

/// @cond _
STATIC_ASSERT(sizeof(hal_sdhost_card_stat_t) == SD_CARD_STAT_LEN, sd_card_stat_sz);
/// @endcond

/**
  \brief  SD status defined in SD spec.
*/
typedef struct hal_sdhost_sd_status {
	u8  rsvd1[49];
	u32 uhs_au_size         : 4;
	u32 uhs_speed_grade     : 4;
	u32 erase_offset        : 2;
	u32 erase_timeout       : 6;
	u8  erase_size1         : 8;
	u8  erase_size2         : 8;
	u32 rsvd2               : 4;
	u32 au_size             : 4;
	u8  perf_move           : 8;
	u8  speed_class         : 8;
	u16 prot_area_size_0_15 : 16;
	u16 prot_area_size_16_30: 16;
	u16 sd_card_type        : 16;
	u32 rsvd3               : 13;
	u32 secured_mode        : 1;
	u32 dat_bus_width       : 2;
} hal_sdhost_sd_stat_t;

/// @cond _
STATIC_ASSERT(sizeof(hal_sdhost_sd_stat_t) == SD_STATUS_LEN, sd_sd_stat_sz);
/// @endcond

/**
  \brief  SD SCR register content.
*/
typedef struct hal_sdhost_scr {
	u32 vendor_rsvd     : 32;
	u8  cmd_support     : 2;
	u16 rsvd1           : 9;
	u8  ex_security     : 4;
	u8  sd_spec3        : 1;
	u8  sd_bus_width    : 4;
	u8  sd_security     : 3;
	u8  erase_bit_stat  : 1;
	u8  sd_spec         : 4;
	u8  scr_structure   : 4;
} hal_sdhost_scr_t;

/// @cond _
STATIC_ASSERT(sizeof(hal_sdhost_scr_t) == SD_SCR_LEN, sd_scr_sz);
/// @endcond

/**
  \brief  Callback function type without parameter.
*/
typedef void (*sdhost_cb_t)(void);

/**
  \brief  Callback function type with parameter.
*/
typedef void (*sdhost_para_cb_t)(void *para);

/**
  \brief  Callback functions for secure-domain access.
*/
typedef struct hal_sdhost_s_funcs {
	void (*hal_sdhost_en_ctrl)(BOOL en);
	void (*hal_sdhost_ldo_ctrl)(u8 vol_sel);
	void (*hal_sdhost_phase_shift)(u8 vp_sel, u8 shift_sel);
} hal_sdhost_s_funcs_t;


/**
  \brief  The data structure for SDIO host HAL operations.
*/
typedef struct hal_sdhost_adapter {
	SDHOST_Type *base_addr;
	volatile u8 is_card_inserted;
	volatile u8 is_wp;
	volatile u8 card_inited;
	volatile u8 wait_interrupts;
	u8 curr_sig_level;
	u8 is_sdhc_sdxc;
	u8 card_curr_ste;
	u8 sd_spec_ver;
	u8 card_support_spd_mode;
	u8 is_s18a;
	u8 voltage_mismatch;
	u8 force_33v;
	u8 verbose;
	u8 tuning_loop;
	hal_sdhost_speed_t curr_bus_spd;
	hal_sdhost_freq_t curr_freq;            // Current clock frequency of SD bus
	u8 rsvd[6];
	u16 rca;
	u32 magic_num;
	u32 blk_capacity;
	sdhost_para_cb_t card_insert_cb;
	sdhost_para_cb_t card_remove_cb;
	sdhost_para_cb_t transfer_done_cb;
	sdhost_para_cb_t task_yield_cb;
	void *card_insert_cb_para;
	void *card_remove_cb_para;
	void *transfer_done_cb_para;
	void *task_yield_cb_para;
	void (*dcache_invalidate_by_addr)(uint32_t *addr, int32_t dsize);   /*! callback function to do the D-cache invalidate  */
	void (*dcache_clean_by_addr)(uint32_t *addr, int32_t dsize);    /*! callback function to do the D-cache clean  */
	hal_sdhost_s_funcs_t *secure_funcs;
	u8 *golden_pattern_buf;
	volatile u32 xfer_int_sts;
	u8 c6r2_buf[SDHOST_C6R2_BUF_LEN] __ALIGNED(32);
	u8 cid[SD_CID_LEN];
	u8 rsvd2[27];
} hal_sdhost_adapter_t, *phal_sdhost_adapter_t;

/** @struct phal_sdhost_adapter_t
  \brief  The data structure for SDIO host HAL operations.
*/


/**
  \brief  The data structure of the stubs function for the SDIO Host HAL functions in ROM
*/
typedef struct hal_sdhost_func_stubs_s {
	io_pin_t *sdhost_pin_table;
	void (*hal_sdhost_irq_handler)(void);
	void (*hal_sdhost_irq_reg)(irq_handler_t irq_handler);
	void (*hal_sdhost_irq_unreg)(void);
	hal_status_t (*hal_sdhost_init_host)(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_s_funcs_t *secure_funcs);
	hal_status_t (*hal_sdhost_init_card)(hal_sdhost_adapter_t *psdhost_adapter);
	void (*hal_sdhost_deinit)(hal_sdhost_adapter_t *psdhost_adapter);
	hal_status_t (*hal_sdhost_read_data)(hal_sdhost_adapter_t *psdhost_adapter, u32 start_addr, u16 blk_cnt, u8 *rbuf_32align);
	hal_status_t (*hal_sdhost_write_data)(hal_sdhost_adapter_t *psdhost_adapter, u32 start_addr, u16 blk_cnt, const u8 *wbuf_32align);
	hal_status_t (*hal_sdhost_erase)(hal_sdhost_adapter_t *psdhost_adapter, u32 start_addr, u32 end_addr);
	hal_status_t (*hal_sdhost_stop_transmission)(hal_sdhost_adapter_t *psdhost_adapter);
	hal_status_t (*hal_sdhost_card_select)(hal_sdhost_adapter_t *psdhost_adapter, u8 select);
	hal_status_t (*hal_sdhost_get_card_status)(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_card_stat_t *status_buf);
	hal_status_t (*hal_sdhost_get_sd_status)(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_sd_stat_t *sd_stat);
	hal_status_t (*hal_sdhost_get_scr)(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_scr_t *scr);
	hal_status_t (*hal_sdhost_get_csd)(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_csd_t *csd);
	hal_status_t (*hal_sdhost_switch_bus_speed)(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_speed_t speed);
	u8(*hal_sdhost_get_curr_signal_level)(hal_sdhost_adapter_t *psdhost_adapter);
	hal_status_t (*hal_sdhost_get_supported_speed)(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_speed_t *speeds);
	hal_status_t (*hal_sdhost_clk_finetune)(hal_sdhost_adapter_t *adpt, u8 *buf_3blk_32align, u32 buf_size, u32 tuning_blk);
	void (*hal_sdhost_card_insert_hook)(hal_sdhost_adapter_t *psdhost_adapter, sdhost_para_cb_t pcallback, void *pdata);
	void (*hal_sdhost_card_remove_hook)(hal_sdhost_adapter_t *psdhost_adapter, sdhost_para_cb_t pcallback, void *pdata);
	void (*hal_sdhost_task_yield_hook)(hal_sdhost_adapter_t *psdhost_adapter, sdhost_para_cb_t task_yield, void *pdata);
	void (*hal_sdhost_transfer_done_int_hook)(hal_sdhost_adapter_t *psdhost_adapter, sdhost_para_cb_t transfer_done_cb, void *pdata);
	uint32_t reserved[40];  // 32 bytes align for next ROM code version function table extending.
} hal_sdhost_func_stubs_t;

/// @cond _
STATIC_ASSERT(sizeof(hal_sdhost_func_stubs_t) == 4 * 64, sdhost_stub_sz);
/// @endcond

/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup hal_sdhost_lib_func SD Host HAL APIs.
 * @ingroup hal_sdhost
 * @{
 */

void hal_rtl_sdhost_irq_reg(irq_handler_t irq_handler);
void hal_rtl_sdhost_irq_unreg(void);
hal_status_t hal_rtl_sdhost_init_host(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_s_funcs_t *secure_funcs);
hal_status_t hal_rtl_sdhost_init_card(hal_sdhost_adapter_t *psdhost_adapter);
void hal_rtl_sdhost_deinit(hal_sdhost_adapter_t *psdhost_adapter);
hal_status_t hal_rtl_sdhost_read_data(hal_sdhost_adapter_t *psdhost_adapter, u32 start_addr, u16 blk_cnt, u8 *rbuf_32align);
hal_status_t hal_rtl_sdhost_write_data(hal_sdhost_adapter_t *psdhost_adapter, u32 start_addr, u16 blk_cnt, const u8 *wbuf_32align);
hal_status_t hal_rtl_sdhost_erase(hal_sdhost_adapter_t *psdhost_adapter, u32 start_addr, u32 end_addr);
hal_status_t hal_rtl_sdhost_stop_transmission(hal_sdhost_adapter_t *psdhost_adapter);
hal_status_t hal_rtl_sdhost_get_card_status(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_card_stat_t *status_buf);
hal_status_t hal_rtl_sdhost_get_sd_status(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_sd_stat_t *sd_stat);
hal_status_t hal_rtl_sdhost_get_scr(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_scr_t *scr);
hal_status_t hal_rtl_sdhost_get_csd(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_csd_t *csd);
hal_status_t hal_rtl_sdhost_switch_bus_speed(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_speed_t  speed);
u8 hal_rtl_sdhost_get_curr_signal_level(hal_sdhost_adapter_t *psdhost_adapter);
hal_status_t hal_rtl_sdhost_get_supported_speed(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_speed_t *speeds);
void hal_rtl_sdhost_card_insert_hook(hal_sdhost_adapter_t *psdhost_adapter, sdhost_para_cb_t pcallback, void *pdata);
void hal_rtl_sdhost_card_remove_hook(hal_sdhost_adapter_t *psdhost_adapter, sdhost_para_cb_t pcallback, void *pdata);
void hal_rtl_sdhost_task_yield_hook(hal_sdhost_adapter_t *psdhost_adapter, sdhost_para_cb_t task_yield, void *pdata);
void hal_rtl_sdhost_transfer_done_int_hook(hal_sdhost_adapter_t *psdhost_adapter, sdhost_para_cb_t transfer_done_cb, void *pdata);
hal_status_t hal_rtl_sdhost_clk_finetune(hal_sdhost_adapter_t *adpt, u8 *buf_3blk_32align, u32 buf_size, u32 tuning_blk);
hal_status_t hal_rtl_sdhost_card_select(hal_sdhost_adapter_t *psdhost_adapter, u8 select);

extern const hal_sdhost_func_stubs_t hal_sdhost_stubs;

/** @} */ /* End of group hal_sdhost_lib_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */
/** @} */ /* End of group hal_sdhost */

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _RTL8735B_SDHOST_H_"


