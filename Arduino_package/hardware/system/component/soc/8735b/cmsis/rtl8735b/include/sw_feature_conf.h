/**************************************************************************//**
 * @file     sw_feature_conf.h
 * @brief    The configuration for AmebaPro2 sw feature.
 * @version  V1.00
 * @date     2022-02-18
 *
 * @note
 *
 ******************************************************************************
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
 ******************************************************************************/

#ifndef _SW_FEATURE_CONF_H_
#define _SW_FEATURE_CONF_H_

#include "platform_conf.h"
#include "verify_conf.h"

/***************** Dependent Toggle ***********/
#define CONFIG_VERIFY_VIDEO_FEATURE         0

/***************** Dependent Toggle End *******/

#if defined(CONFIG_OTG_EN) && CONFIG_OTG_EN == 1

#if 0                   //host
#undef DWC_DEVICE_ONLY
#define DWC_HOST_ONLY
#else                   //device

#define DWC_DEVICE_ONLY
#undef DWC_HOST_ONLY

#if defined(CONFIG_VERIFY_VIDEO_FEATURE) && CONFIG_VERIFY_VIDEO_FEATURE == 1
// Turn on USB MSC for video
#define CONFIG_MSC_EN                       1

#elif defined(CONFIG_VERIFY_OTG) && CONFIG_VERIFY_OTG == 1
// Turn on USB vendor for verify
#define CONFIG_USB_VENDOR_EN                1

#endif  // end of "#if defined(CONFIG_VERIFY_OTG) && CONFIG_VERIFY_OTG == 1"
#endif  // end of #if 0 else
#endif  // end of "#if defined(CONFIG_OTG_EN)"



// Enable features for video
#if defined(CONFIG_VERIFY_VIDEO_FEATURE) && CONFIG_VERIFY_VIDEO_FEATURE == 1
#define CONFIG_SDHOST_FATFS_EN              1
#endif  // end of "#if defined(CONFIG_VERIFY_VIDEO_FEATURE) && CONFIG_VERIFY_VIDEO_FEATURE == 1"



/**************** Feature List Start *********/
// Default configs

// Enable USB MSC
#ifndef CONFIG_MSC_EN
#define CONFIG_MSC_EN                       0
#endif

// Enable USB Vendor
#ifndef CONFIG_USB_VENDOR_EN
#define CONFIG_USB_VENDOR_EN                0
#endif

// Enable SD card FATFS
#ifndef CONFIG_SDHOST_FATFS_EN
#define CONFIG_SDHOST_FATFS_EN              1
#endif

/**************** Feature List End ************/


#endif  // end of "#ifndef _SW_FEATURE_CONF_H_"
