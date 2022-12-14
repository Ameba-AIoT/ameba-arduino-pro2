#ifndef _GADEGT_DEBUG_H_
#define _GADGET_DEBUG_H_

#include "diag.h"

#define GADGET_DEBUG       1

#if GADGET_DEBUG
#define ETH_PRINT(fmt, args...)                 DBG_8195A("\n\r[%s]%s: " fmt, __FUNCTION__, ## args)
#define ETH_ERROR(fmt, args...)                 DBG_8195A("\n\r[%s]%s: " fmt, __FUNCTION__, ## args)
#define ETH_WARM(fmt, args...)                  DBG_8195A("\n\r[%s]%s: " fmt, __FUNCTION__, ## args)
#define FUN_ENTER                                   DBG_8195A("\n\r[%s ==>]\n", __func__)
#define FUN_EXIT                                    DBG_8195A("\n\r[%s <==]\n", __func__)
#define FUN_TRACE                                   DBG_8195A("\n\r[%s]:%d \n", __func__, __LINE__)
#else
#define ETH_PRINT(fmt, args...)
#define ETH_ERROR(fmt, args...)                 DBG_8195A("\n\r%s: " fmt,__FUNCTION__, ## args)
#define ETH_WARM(fmt, args...)
#define FUN_ENTER
#define FUN_EXIT
#define FUN_TRACE
#endif

#endif