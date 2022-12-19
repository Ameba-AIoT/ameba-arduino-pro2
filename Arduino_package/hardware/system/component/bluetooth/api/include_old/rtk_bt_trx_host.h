/**
*****************************************************************************************
*     Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file     rtk_bt_trx_host.h
  * @brief    Header file for rtk bt dat transmit and recevie using ipc
  * @details  bt trx host api.
  * @author   sherman
  * @date     2022-04-26
  * @version  v1.0
  * *************************************************************************************
  */
#ifndef _RTK_BT_TRX_HOST_H_
#define _RTK_BT_TRX_HOST_H_

/* -------------------------------- Includes -------------------------------- */
#include "rtk_bt_defs.h"
#include "bt_ipc_dev_trx.h"

/* ------------------------------- Data Types ------------------------------- */

/**
 * @brief  hadle stream data received from ipc.
 * @param  p_ipc_msg[in]: pointer to ipc message
 * @return 0:fail, 1:success.
 */
rtk_bt_err_t rtk_bt_ipc_host_data_hdl(bt_ipc_dev_tx_message *p_ipc_msg);

/**
 * @brief  to send a ipc message to device and wait result.
 * @param  profile_id[in]: bt profile indication
 * @param  event[in]: data related event
 * @param  sub_event[in]: data related sub event
 * @param  len[in]: data length
 * @param  data[in]: pointer to data buffer
 * @return 0:fail, 1:success
 */
rtk_bt_err_t rtk_bt_ipc_host_data_send(uint32_t profile_id, uint32_t event, uint32_t sub_event, uint32_t len, uint8_t *data);

#endif /* _RTK_BT_TRX_HOST_H_ */