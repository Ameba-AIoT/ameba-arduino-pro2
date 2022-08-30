/**************************************************************************//**
 * @file     platform_conf_sysip_s_ns.h
 * @brief    The configuration for AmebaPro High Power(TM9) platform.
 * @version  V1.00
 * @date     2022-01-12
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2019 Realtek Corporation. All rights reserved.
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

#ifndef _RTL8735B_CONF_SYSIP_S_NS_H_
#define _RTL8735B_CONF_SYSIP_S_NS_H_

#include "basic_types.h"

/*  All peripherals security attribute configuration
    <0=> Secure state <1=> Non-Secure state
*/
// Internal IPs default setting
#define CONFIG_SEC_AON                        SET_S_STATE
#define CONFIG_SEC_TRNG                       SET_S_STATE
#define CONFIG_SEC_GDMA0                      SET_NS_STATE
#define CONFIG_SEC_GDMA1                      SET_NS_STATE
#define CONFIG_SEC_SGDMA0                     SET_S_STATE
#define CONFIG_SEC_SGDMA1                     SET_S_STATE
#define CONFIG_SEC_Crypto                     SET_NS_STATE
#define CONFIG_SEC_SCrypto                    SET_S_STATE
#define CONFIG_SEC_SRXI                       SET_S_STATE
#define CONFIG_SEC_RXI                        SET_NS_STATE
#define CONFIG_SEC_SRC_OCP_OUT_L              SET_NS_STATE
#define CONFIG_SEC_OCP_OUT_L                  SET_NS_STATE
#define CONFIG_SEC_BOD                        SET_S_STATE
#define CONFIG_SEC_RTC                        SET_S_STATE
#define CONFIG_SEC_Comparator                 SET_S_STATE
#define CONFIG_SEC_Flash_SEC                  SET_S_STATE
#define CONFIG_SEC_FEPHY                      SET_S_STATE

#endif  // end of "#define _RTL8735B_CONF_S_NS_H_"

