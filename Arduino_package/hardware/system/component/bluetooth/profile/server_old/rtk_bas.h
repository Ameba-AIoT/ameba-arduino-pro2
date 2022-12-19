/*
 *******************************************************************************
 * Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __BAS_H__
#define __BAS_H__

#include <rtk_bt_defs.h>
#include <rtk_bt_gatts.h>

#ifdef __cplusplus
extern "C"  {
#endif

typedef enum {
	BAS_PARAM_BATTERY_LEVEL = 0x01,
} T_BAS_PARAM_TYPE;

void battery_service_callback(rtk_bt_gatts_evt_code_t event, void *data);

void battery_cccd_notify(uint8_t ntf_id);

rtk_bt_err_t battery_srv_add(void);

void bas_disconnect(uint8_t conn_id);

void bas_status_deinit(void);

#ifdef __cplusplus
}
#endif

#endif  /* __BAS_H__ */