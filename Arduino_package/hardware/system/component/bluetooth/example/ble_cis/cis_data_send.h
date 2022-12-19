/*
 *******************************************************************************
 * Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __RTK_BLE_CIS_DATA_SEND_H__
#define __RTK_BLE_CIS_DATA_SEND_H__

#include <rtk_bt_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

void rtk_ble_cis_send_data_init(void);

void rtk_ble_cis_send_data_deinit(void);

rtk_bt_err_t rtk_ble_cis_data_send(uint16_t conn_handle,uint16_t data_len,bool ts_flag,uint32_t time_stamp,uint16_t send_count,uint16_t sdu_interval);

rtk_bt_err_t rtk_ble_cis_data_free(uint16_t conn_handle, uint8_t *p_data);

void rtk_ble_cis_send_data_flush(void);

#ifdef __cplusplus
}
#endif

#endif  /* __RTK_BLE_CIS_DATA_SEND_H__ */