/**************************************************************************//**
 * @file     sw_feature_conf.h
 * @brief    The configuration for AmebaPro2 sw feature.
 * @version  V1.00
 * @date     2022-07-01
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
#include "verify_conf.h"

/***************** Dependent Toggle ***********/
#define CONFIG_VERIFY_VIDEO_FEATURE         0

/***************** Dependent Toggle End *******/

#if defined(CONFIG_OTG_EN) && CONFIG_OTG_EN == 1

/*
  OTG operate three mode
  1) #define DWC_DEVICE_ONLY
      -> only device code.

  2)#define DWC_HOST_ONLY
      -> only host code.

  3) no define both (DWC_DEVICE_ONLY & DWC_HOST_ONLY).   (default)
      -> two mode support,
          which mode is judge by the global variable "gOtgHostMode", which is located in <dwc_otg_driver.c> file.
          if variable "gOtgHostMode"=1, the otg is in HOST mode.
          if variable "gOtgHostMode"=0, the otg is in DEVICE mode.

*/
//#define DWC_DEVICE_ONLY
//#define DWC_HOST_ONLY

#if defined(CONFIG_VERIFY_VIDEO_FEATURE) && CONFIG_VERIFY_VIDEO_FEATURE == 1
// Turn on USB MSC for video
#define CONFIG_MSC_EN                       1

#elif defined(CONFIG_VERIFY_OTG) && CONFIG_VERIFY_OTG == 1
// Turn on USB vendor for verify
#define CONFIG_USB_VENDOR_EN                1

#endif  // end of "#if defined(CONFIG_VERIFY_OTG) && CONFIG_VERIFY_OTG == 1"
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
