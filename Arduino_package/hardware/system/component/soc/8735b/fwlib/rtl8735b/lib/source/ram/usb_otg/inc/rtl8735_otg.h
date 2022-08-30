/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#ifndef _RTL8735_OTG_H_
#define _RTL8735_OTG_H_

#include "platform_conf.h"
//#define OTG_FAST_INIT   1
//#define DWC_DEVICE_ONLY
//#undef DWC_DEVICE_ONLY
//#undef DWC_HOST_ONLY
//#undef DWC_HOST_ONLY

/* for device mode */
#define DWC_EN_ISOC 1
//#undef DWC_EN_ISOC
#if defined(DWC_EN_ISOC)
#define USB_REQ_ISO_ASAP 1
#endif

#if defined(DWC_DEVICE_ONLY)
//#define USB_DEV_FULL_SPEED
#endif
#define DWC_RM_DEV_RDNT_SRC
#define DWC_RM_HOST_RDNT_SRC
//#define CONFIG_USB_DBGINFO_EN 1
#undef CONFIG_USB_DBGINFO_EN

#ifdef DWC_HOST_ONLY
//#include "dwc_otg_hcd.h"
#endif
#define SD9_OTG_CDC_PATCH


//#define DBG_8735B_OTG(x...)   DBG_OTG_INFO(x)
#define DBG_8735B_OTG(x...)




#endif

