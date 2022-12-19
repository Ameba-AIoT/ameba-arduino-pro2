/**************************************************************************//**
 * @file     voe_boot_loader.h
 * @brief    The HAL API implementation for the pin mux managemment.
 * @version  V1.00
 * @date     2022-09-13
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

#ifndef _VOE_BOOT_LOADER_H_
#define _VOE_BOOT_LOADER_H_
#include "cmsis.h"
#include "hal_dev_load.h"
#include "rtl8735b_voe_status.h"

#ifdef  __cplusplus
extern "C"
{
#endif

#define BOOT_LD_MULTI_FCS_MAX                        10
#define BOOT_LD_VOE_LD_INFO_DIGEST_MAX               32            /* Bytes */
#define BOOT_LD_FCS_PARA_IMG_MAX_SIZE                (0x1000)      /* Bytes */

typedef struct isp_multi_fcs_info_s {
	uint32_t sensor_set_size[BOOT_LD_MULTI_FCS_MAX];
	uint32_t resv[22];
} isp_multi_fcs_info_t;

typedef struct iq_info_s {
	uint32_t start_addr;
	uint32_t data_size;
	uint32_t resv[14];
} iq_info_t;

typedef struct sensor_info_s {
	uint32_t start_addr;
	uint32_t data_size;
	uint32_t resv[14];
} sensor_info_t;

typedef struct sensor_set_info_s {
	uint32_t fcs_data_size;
	uint32_t fcs_data_offset;   // offset in byres ref. fcs_hdr_start
	uint32_t iq_start_addr;     // offset in byres ref. fcs data start
	uint32_t iq_data_size;
	uint32_t sensor_start_addr; // offset in byres ref. fcs data start
	uint32_t sensor_data_size;
	uint32_t resv[2];
} sensor_set_info_t;

typedef struct isp_multi_fcs_ld_info_s {
	uint8_t fcs_id;
	uint8_t multi_fcs_cnt;
	uint8_t fcs_ld_chk_en;
	uint8_t resv1;
	uint32_t magic;
	uint32_t version;
	uint32_t wait_km_init_timeout_us;
	uint32_t fcs_hdr_start;
	uint32_t ispiq_img_offset;                  // offset in byres ref. img hdr start(indep isp_iq/ fw isp_iq)
	uint32_t resv2[2];
	sensor_set_info_t sensor_set[BOOT_LD_MULTI_FCS_MAX];
	dev_part_record_ld_t part_record;            // provide img manifest location
	uint32_t mani_unprt_offset;                 // offset in byres ref. img manifest start
	uint32_t img_hdr_offset;                    // offset in byres ref. img manifest start
	uint32_t fcs_hdr_offset;                    // offset in byres ref. img manifest start
	uint8_t digest[BOOT_LD_VOE_LD_INFO_DIGEST_MAX];
} isp_multi_fcs_ld_info_t;

typedef struct voe_fcs_peri_info_s {

	uint8_t i2c_id;
	uint8_t timer_id;
	uint8_t adc_id;   // use 1 gpio
	uint8_t pwm_id;   // same function as ir_led

	uint8_t gpio_list[GPIO_MAX];

	uint8_t gpio_cnt;
	uint8_t snr_clk_pin;
	uint8_t i2c_scl;
	uint8_t i2c_sda;

	uint8_t fcs_peri_valid;
	uint8_t fcs_OK;

	uint16_t fcs_data_verion;
	uint16_t fcs_data_id;

	uint8_t reserved[6];

} voe_fcs_peri_info_t, *pvoe_fcs_peri_info_t;

typedef struct voe_isp_img_reld_info_type_s {
	uint32_t fcs_hdr_start;
	uint32_t ispiq_img_start_addr;
	uint32_t resv_offset;
	uint32_t voe_offset;        // ref load fw img start addr
} voe_isp_img_reld_info_type_t, *pvoe_isp_img_reld_info_type_t;

typedef struct voe_img_ld_info_type_s {
	dev_part_record_ld_t part_record;       // provide img manifest location
	uint32_t img_hdr_offset;                // img_hdr_offset
	uint32_t voe_data_offset;               // voe_data_offset
	uint32_t voe_data_len;                  // voe_data_len
	voe_isp_img_reld_info_type_t reld_info;
	uint32_t resv;
	uint8_t digest[BOOT_LD_VOE_LD_INFO_DIGEST_MAX];
} voe_img_ld_info_type_t, *pvoe_img_ld_info_type_t;

typedef void (*voe_cpy_t)(void *, void *, size_t);

typedef struct voe_fcs_load_ctl_s {
	voe_cpy_t voe_cpy;
	voe_cpy_t isp_cpy;
	int *fw_addr;
	isp_multi_fcs_ld_info_t *p_fcs_ld_info;
	voe_fcs_peri_info_t *p_fcs_peri_info;
	void *p_fcs_para_raw;
} voe_fcs_load_ctrl_t, *pvoe_fcs_load_ctrl_t;

int load_voe_boot_process(const uint8_t ctrl_obj, int *fw_addr, isp_multi_fcs_ld_info_t *p_fcs_ld_info);
int hal_voe_boot_process(voe_fcs_load_ctrl_t *pvoe_fcs_ld_ctrl);

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _HAL_PINMUX_H_"


