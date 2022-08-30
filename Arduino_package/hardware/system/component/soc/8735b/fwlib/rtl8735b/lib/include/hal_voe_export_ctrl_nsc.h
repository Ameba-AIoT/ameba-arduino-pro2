/**************************************************************************//**
* @file        hal_efuse_nsc.h
* @brief       The HAL Non-secure callable API implementation for the EFUSE
*
* @version     V1.00
* @date        2022-02-18
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



#ifndef _HAL_VOE_EXPORT_CTRL_NSC_H_
#define _HAL_VOE_EXPORT_CTRL_NSC_H_
#include "cmsis.h"
#include <arm_cmse.h>   /* Use CMSE intrinsics */
#include "hal_voe_export_ctrl.h"
#ifdef  __cplusplus
extern "C"
{
#endif

/**
* @addtogroup hal_sys_ctrl_nsc system control NSC
* @{
*/
#if defined(CONFIG_BUILD_SECURE)
int32_t NS_ENTRY voe_isp_get_export_ld_info_nsc(const uint8_t ld_obj, dev_load_type_t *pmem);
uint8_t NS_ENTRY voe_isp_get_fcs_ld_chk_en_nsc(void);
uint8_t NS_ENTRY voe_isp_get_fcs_sensor_set_idx_nsc(void);
#endif

#if defined(CONFIG_BUILD_NONSECURE)
int32_t voe_isp_get_export_ld_info_nsc(const uint8_t ld_obj, dev_load_type_t *pmem);
uint8_t voe_isp_get_fcs_ld_chk_en_nsc(void);
uint8_t voe_isp_get_fcs_sensor_set_idx_nsc(void);



#define voe_isp_get_export_ld_info              voe_isp_get_export_ld_info_nsc
#define voe_isp_get_fcs_ld_chk_en               voe_isp_get_fcs_ld_chk_en_nsc
#define voe_isp_get_fcs_sensor_set_idx          voe_isp_get_fcs_sensor_set_idx_nsc

#endif  // end of "#if defined(CONFIG_BUILD_NONSECURE)"

/** @} */ /* End of group hal_sys_ctrl_nsc */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_SYS_CTRL_NSC_H_"
