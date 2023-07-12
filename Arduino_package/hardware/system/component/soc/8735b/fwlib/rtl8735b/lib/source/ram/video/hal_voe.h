/**************************************************************************//**
 * @file     hal_voe.h
 * @brief    The HAL API implementation for the VOE module
 * @version  V1.00
 * @date     2020-11-26
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

#ifndef HAL_VOE_H
#define HAL_VOE_H

#include "rtl8735b_voe_type.h"

#ifdef __cplusplus
extern "C" {
#endif


#define REMAP_S7_ITCM   0x04000000	//0x04000000~0x0407FFFF
#define REMAP_S7_DTCM   0x00080000	//0x20080000~0x200FFFFF

#define VOE_CODE_SHIFT  0x3A000	// video_adp shift on VOE DDR

#define VOE_DDR_S       0x70000000	// 1MB
#define VOE_DDR_E       0x70100000

#define VOE_IROM_S      0x00000000	// 1KB
#define VOE_IROM_E      0x000003FF
#define VOE_IRAM_S      0x00040000	// 64KB
#define VOE_IRAM_E      0x0004FFFF

#define VOE_DROM_S      0x20010000	// 16KB
#define VOE_DROM_E      0x20013FFF
#define VOE_DRAM_S      0x20000000	// 64KB
#define VOE_DRAM_E      0x2000FFFF

#define TM_SRAM_S       VOE_DRAM_S + REMAP_S7_DTCM
#define TM_DRAM_S		VOE_DDR_S + VOE_CODE_SHIFT

#define VOE_STATUS_DIS  0
#define VOE_STATUS_EN   1
#define VOE_STATUS_OK   2
#define VOE_STATUS_NOK  3

//#define __TTFF_VOE__

/**
 * @addtogroup hs_hal_voe VOE
 * @{
 * @brief The VOE HAL APIs.
 */


typedef void (*voe_callback_t)(void *);


/*
  \brief  The data structure to handle the voe module, includes the configuration, register base address and interrupt call back functions.
*/
typedef void (*voe_cpy_t)(void *, void *, size_t);

typedef struct hal_voe_adapter_s {

	voe_cpy_t voe_cpy;
	u32 ddr2_fw_addr;
	u32 ddr2_voe_addr;
	u32 ddr2_size;

	voe_callback_t km_message_cb;   /*! callback function for km message */
	void *km_message_cb_para;        /*! the argument for km message callback function */

	voe_callback_t erac_finish_cb;  /*! callback function for line buffer overflow */
	void *erac_finish_cb_para;      /*! the argument for line buffer overflow */

	u32 voe_send_message;
	volatile u32 voe_cmd;

	volatile u32 voe_status;		/*! 0:disable, 1:enable 2: OK 3:NOK */
	u32 timeout;
} hal_voe_adapter_t, *phal_voe_adapter_t;


hal_status_t hal_voe_erac_wr(u32 data_addr, u32 offset, u16 wr_num, voe_callback_t callback, void *arg);

void hal_voe_receive_message(hal_voe_adapter_t *pvoe_adpt);

bool hal_voe_get_receive_message_status(void);

void hal_voe_clean_receive_message_status(void);

u32 hal_voe_send2voe(u32 cmd, u32 param1, u32 param2);

int hal_voe_load_fw(voe_cpy_t voe_cpy, int *fw_addr, int *voe_ddr_addr);

int hal_voe_load_sensor(voe_cpy_t voe_cpy, int *fw_addr, int *voe_ddr_addr);
int hal_voe_load_iq(voe_cpy_t voe_cpy, int *fw_addr, int *voe_ddr_addr);

int hal_voe_cb(void *voe_cb, void *erac_done);
int hal_voe_seam(int enable);

int hal_voe_init(u32 heap_addr, u32 heap_size);
void hal_voe_deinit(void);



hal_status_t hal_voe_erac_init(voe_callback_t wait_cmd_sent_cb, void *cb_para);


u16 hal_voe_parse_cmd(u32 voe_message);

bool hal_voe_check_erac_write_cmd(void);



void hal_voe_set_lb_overflow_int(hal_voe_adapter_t *pvoe_adpt, voe_callback_t callback, void *arg, u8 int_en);
void hal_voe_deinit(void);


// Raymond Added
hal_status_t hal_voe_cmd_cb(voe_callback_t receive_cmd_cb, void *cb_para);
u16 hal_voe_cmd(void);
u16 hal_voe_cmd_data(void);	// Added By Raymond
uint32_t check_km_cmd(void);
uint32_t check_km_ch(void);
uint32_t check_km_status(void);

int hal_voe_fcs_check_km_run_done(void);
int hal_voe_fcs_set_voe_fm_load_flag_final(void);
int hal_voe_fcs_check_OK(void);
int hal_voe_ready(void);

int hal_voe_set_wdt(int mode, int sec);
void hal_voe_cpy(void *dest, void *src, size_t len);
void hal_voe_show_fcs_result(void);
int hal_voe_load_cali_iq(voe_cpy_t isp_cpy, int *iq_cali_addr, int *voe_ddr_addr, u32 cali_iq_size);


/** @} */ /* End of group hs_hal_voe */

#ifdef __cplusplus
}
#endif

#endif

