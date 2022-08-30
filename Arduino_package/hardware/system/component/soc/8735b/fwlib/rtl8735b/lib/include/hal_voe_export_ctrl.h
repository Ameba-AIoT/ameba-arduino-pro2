/**************************************************************************//**
* @file        hal_voe_export_ctrl.h
* @brief       The HAL API implementation for the System control
*
* @version     V1.00
* @date        2022-02-15
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



#ifndef _HAL_VOE_EXPORT_CTRL_H_
#define _HAL_VOE_EXPORT_CTRL_H_
#include "cmsis.h"
#include "fw_img_tlv.h"
#include "rtl8735b_voe_status.h"
#include "fw_img_export.h"
#include "hal_dev_load.h"

#ifdef  __cplusplus
extern "C"
{
#endif

enum {
	VOE_EXPORT_LD_ISP_IMG_MANI                      = 0x01,
	VOE_EXPORT_LD_ISP_IMG_MANI_UNPRT                = 0x02,
	VOE_EXPORT_LD_ISP_IMG_HDR                       = 0x03,
	VOE_EXPORT_LD_ISP_IMG_MULTI_FCS_HDR             = 0x04,

	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET0_FCS     = 0x10,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET1_FCS     = 0x11,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET2_FCS     = 0x12,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET3_FCS     = 0x13,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET4_FCS     = 0x14,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET5_FCS     = 0x15,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET6_FCS     = 0x16,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET7_FCS     = 0x17,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET8_FCS     = 0x18,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET9_FCS     = 0x19,

	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET0_IQ      = 0x20,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET1_IQ      = 0x21,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET2_IQ      = 0x22,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET3_IQ      = 0x23,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET4_IQ      = 0x24,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET5_IQ      = 0x25,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET6_IQ      = 0x26,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET7_IQ      = 0x27,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET8_IQ      = 0x28,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET9_IQ      = 0x29,

	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET0_SENSOR  = 0x30,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET1_SENSOR  = 0x31,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET2_SENSOR  = 0x32,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET3_SENSOR  = 0x33,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET4_SENSOR  = 0x34,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET5_SENSOR  = 0x35,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET6_SENSOR  = 0x36,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET7_SENSOR  = 0x37,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET8_SENSOR  = 0x38,
	VOE_EXPORT_LD_ISP_IMG_MULTI_SENSOR_SET9_SENSOR  = 0x39,

	VOE_EXPORT_LD_VOE_IMG_FW_MANI                   = 0x40,
	VOE_EXPORT_LD_VOE_IMG_HDR                       = 0x41,
	VOE_EXPORT_LD_VOE_IMG_DATA                      = 0x42,
};

typedef struct voe_ld_export_adapter_s {
	uint8_t dev_ld_obj;
	uint8_t resv1[3];
	isp_multi_fcs_ld_info_t *pisp_multi_sensor_ld_info;
	voe_img_ld_info_type_t  *pvoe_img_ld_info;
	uint32_t resv2[5];
	s32(*get_ld_info)(const uint8_t ld_obj, dev_load_type_t *pmem);
} voe_ld_export_adapter_t, *pvoe_ld_export_adapter_t;


/**
* @addtogroup N/A
* @{
*/

int voe_export_info_init(voe_ld_export_info_type_t *pbl4voe_ld_info, const uint8_t boot_sel);
uint8_t voe_isp_get_fcs_sensor_set_idx(void);
uint8_t voe_isp_get_fcs_ld_chk_en(void);
int32_t voe_isp_get_export_ld_info(const uint8_t ld_obj, dev_load_type_t *pmem);
int voe_isp_export_ld_info_digest_check_from_nor(const uint8_t digest_obj);


/** @} */ /* End of group hs_hal_efuse */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_SYS_CTRL_H_"


