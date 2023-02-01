/*
 *******************************************************************************
 * Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __SIMPLE_BLE_SERVICE_H__
#define __SIMPLE_BLE_SERVICE_H__

#include <rtk_bt_defs.h>
#include <rtk_bt_gatts.h>

#ifdef __cplusplus
extern "C"  {
#endif

void simple_ble_service_callback(rtk_bt_gatts_evt_code_t event, void *data);

void simple_ble_srv_cccd_indicate(uint8_t conn_id);

void simple_ble_srv_cccd_notify(uint8_t conn_id);

rtk_bt_err_t simple_ble_srv_add(void);

void simple_ble_srv_disconnect(uint8_t conn_id);

void simple_ble_srv_status_deinit(void);

#ifdef __cplusplus
}
#endif

#endif  /* __SIMPLE_BLE_SERVICE_H__ */
