/**
*****************************************************************************************
*     Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file     bt_ipc_host_api.h
  * @brief    Head file for bt ipc host api.
  * @details  bt ipc host api.
  * @author   sherman
  * @date     2021-10-20
  * @version  v1.0
  * *************************************************************************************
  */

#ifndef _BT_IPC_HOST_API_H_
#define _BT_IPC_HOST_API_H_

/* -------------------------------- Includes -------------------------------- */
#include <stdint.h>
#include "ameba.h"
#include "bt_ipc_profile_config.h"
#include "platform_opts_bt.h"
#include "rtk_ble_gap.h"
#include "rtk_bt_gatts.h"
#include "rtk_bt_gattc.h"
#include "rtk_legacy_gap.h"
#include "rtk_bt_sdp.h"
#include "rtk_bt_avrcp.h"
#include "rtk_bt_a2dp.h"

#define IPC_HOST_API_DATA_MAX   976   // 244*4
#define IPC_HOST_API_RET_MAX    40

/* ------------------------------- Data Types ------------------------------- */

/** @brief bt ipc host api task private struct */
struct bt_ipc_host_api_task_struct {
	void                      *task;	/* I: workqueue thread */
	void                      *wakeup_sema;    /* for internal use only */
	void                      *terminate_sema; /* for internal use only */
	uint32_t                  blocked;          /* for internal use only */
};

typedef struct bt_ipc_host_request_message {
    uint32_t    PROFILE_ID;
    uint32_t    API_ID;
    uint8_t     param_buf[IPC_HOST_API_DATA_MAX];
    int32_t     ret[10];
} bt_ipc_host_request_message;

void bt_ipc_host_register_gap_cb(rtk_ble_gap_cb_t cb);

void bt_ipc_host_unregister_gap_cb(void);

void bt_ipc_host_register_legacy_gap_cb(rtk_legacy_gap_cb_t cb);

void bt_ipc_host_unregister_legacy_gap_cb(void);

void bt_ipc_host_register_sdp_cb(rtk_bt_sdp_cb_t cb);

void bt_ipc_host_unregister_sdp_cb(void);

void bt_ipc_host_register_avrcp_cb(rtk_bt_avrcp_cb_t cb);

void bt_ipc_host_unregister_avrcp_cb(void);

void bt_ipc_host_register_a2dp_cb(rtk_bt_a2dp_cb_t cb);

void bt_ipc_host_unregister_a2dp_cb(void);

void bt_ipc_host_register_gatts_cb(rtk_bt_gatts_cb_t cb);

void bt_ipc_host_unregister_gatts_cb(void);

void bt_ipc_host_register_gattc_cb(rtk_bt_gattc_cb_t cb);

void bt_ipc_host_unregister_gattc_cb(void);

/**
 * @brief  to initialize the ipc host for bt api.
 * @param  none.
 * @return none.
 */
void bt_ipc_api_init_host(void);

/**
 * @brief  to deinit the ipc host for bt api.
 * @param  none.
 * @return none.
 */
void bt_ipc_api_deinit_host(void);

/**
 * @brief  to send a ipc message to device and wait result.
 * @param  profile_index[in]: mesh/peripheral/central ...
 * @param  api_id[in]: BT_API_ID.
 * @param  param_buf[in]: pointer to API parameter.
 * @return pointer to result of API.
 */
int *bt_ipc_api_host_message_send(uint32_t profile_id, uint32_t api_id, uint8_t *param_buf, uint32_t buf_len);

#endif /* __BT_IPC_HOST_API_H__ */

