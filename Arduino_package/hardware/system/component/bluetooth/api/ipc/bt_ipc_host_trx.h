/**
*****************************************************************************************
*     Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file     bt_ipc_host_trx.h
  * @brief    Head file for bt ipc host trx.
  * @details  bt ipc host trx.
  * @author   sherman
  * @date     2021-10-20
  * @version  v1.0
  * *************************************************************************************
  */

#ifndef _BT_IPC_HOST_TRX_H_
#define _BT_IPC_HOST_TRX_H_

/* -------------------------------- Includes -------------------------------- */
#include <stdint.h>
#include "ameba.h"
#include "bt_ipc_profile_config.h"
#include "rtk_bt_a2dp.h"

#define IPC_HOST_TRX_PARAM_MAX    80 //param of data struct
#define IPC_HOST_TRX_DATA_MAX     1024 //data

/* ------------------------------- Data Types ------------------------------- */

/** @brief bt ipc host trx task private struct */
struct bt_ipc_host_trx_task_struct {
	void                      *task;	/* I: workqueue thread */
	void                      *wakeup_sema;    /* for internal use only */
	void                      *terminate_sema; /* for internal use only */
	uint32_t                  blocked;          /* for internal use only */
};

typedef struct bt_ipc_host_tx_message {
    uint32_t    PROFILE_ID;
	uint32_t    TX_EVENT;
	uint8_t     data[IPC_HOST_TRX_PARAM_MAX + IPC_HOST_TRX_DATA_MAX];//buffer for tx data;
	int	        ret[4]; //for multiple return values
    uint8_t     dummy[24];//add for 64B size alignment
} bt_ipc_host_tx_message;

void bt_ipc_host_register_a2dp_trx_cb(rtk_bt_a2dp_cb_t cb);

void bt_ipc_host_unregister_a2dp_trx_cb(void);

/**
 * @brief  to initialize the ipc host for bt api.
 * @param  none.
 * @return none.
 */
void bt_ipc_trx_init_host(void);

/**
 * @brief  to deinit the ipc host for bt api.
 * @param  none.
 * @return none.
 */
void bt_ipc_trx_deinit_host(void);

/**
 * @brief  to send a ipc message to device and wait result.
 * @param  profile_id[in]: mesh/peripheral/central ...
 * @param  tx_event[in]: BT_HOST_TX_EVENT.
 * @param  param_buf[in]: pointer to BT_HOST_TX_EVENT parameter.
 * @param  buf_len[in]: buffer size.
 * @return pointer to result of BT_HOST_TX_EVENT.
 */
int *bt_ipc_trx_host_message_send(uint32_t profile_id, uint32_t tx_event, uint32_t *param_buf, uint32_t buf_len);

#endif /* _BT_IPC_HOST_TRX_H_ */

