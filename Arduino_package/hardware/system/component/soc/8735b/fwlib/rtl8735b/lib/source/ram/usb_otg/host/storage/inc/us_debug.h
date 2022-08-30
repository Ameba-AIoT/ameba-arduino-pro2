#ifndef _US_DEBUG_H_
#define _US_DEBUG_H_

#include "diag.h"
#include "rtl8735_otg.h"

#define US_DEBUG    0
#define US_DRIVER   "US_DRIVER"

#if US_DEBUG
#define US_INFO(fmt, args...)                   DBG_8735B_OTG("[%s]%s: " fmt, US_DRIVER, __FUNCTION__, ## args)
#define US_ERR(fmt, args...)                    DBG_8735B_OTG("[%s]%s: " fmt, US_DRIVER,__FUNCTION__, ## args)
#define US_WARN(fmt, args...)                   DBG_8735B_OTG("[%s]%s: " fmt, US_DRIVER,__FUNCTION__, ## args)
#define FUN_ENTER                               DBG_8735B_OTG("[%s]%s ==>\n", US_DRIVER,__FUNCTION__)
#define FUN_EXIT                                DBG_8735B_OTG("[%s]%s <==\n", US_DRIVER,__FUNCTION__)
#define FUN_TRACE                               DBG_8735B_OTG("[%s]%s:%d \n", US_DRIVER,__FUNCTION__, __LINE__)
#else
#define US_INFO(fmt, args...)
#define US_ERR(fmt, args...)                    DBG_8735B_OTG("[%s]%s: " fmt, US_DRIVER,__FUNCTION__, ## args)
#define US_WARN(fmt, args...)
#define FUN_ENTER
#define FUN_EXIT
#define FUN_TRACE
#endif

void usb_stor_show_sense(
	unsigned char key,
	unsigned char asc,
	unsigned char ascq);

#include "scsi/scsi.h"
#include "scsi/scsi_cmnd.h"
void usb_stor_show_scsi_cmnd(struct scsi_cmnd *srb);

#endif /* _US_DEBUG_H_ */
