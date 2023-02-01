/*
 *******************************************************************************
 * Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __IAS_SERVICE_H__
#define __IAS_SERVICE_H__

#include <rtk_bt_defs.h>
#include <rtk_bt_gatts.h>

#ifdef __cplusplus
extern "C"  {
#endif

void immediate_alert_srv_callback(rtk_bt_gatts_evt_code_t event, void *data);

rtk_bt_err_t immediate_alert_srv_add(void);

#ifdef __cplusplus
}
#endif

#endif  /* __IAS_SERVICE_H__ */