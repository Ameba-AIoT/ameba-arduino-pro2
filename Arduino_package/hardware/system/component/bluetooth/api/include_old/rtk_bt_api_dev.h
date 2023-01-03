/**
*****************************************************************************************
*     Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file     rtk_bt_api_dev.h
  * @brief    Header file for rtk bt dat transmit and recevie using ipc
  * @details  bt ipc dev api.
  * @author   sherman
  * @date     2022-04-26
  * @version  v1.0
  * *************************************************************************************
  */
#ifndef _RTK_BT_API_DEV_H_
#define _RTK_BT_API_DEV_H_

/* -------------------------------- Includes -------------------------------- */
#include "rtk_bt_defs.h"
#include "bt_ipc_host_api.h"

/* ------------------------------- Data Types ------------------------------- */

/**
 * @brief  hadle stream data received from ipc.
 * @param  p_ipc_msg[in]: pointer to ipc message
 * @return 0:fail, 1:success.
 */
rtk_bt_err_t rtk_bt_ipc_dev_cmd_hdl(bt_ipc_host_request_message *p_ipc_msg);

/**
 * @brief  to send a ipc message to device and wait result.
 * @param  profile_id[in]: bt profile indication
 * @param  event[in]: command related event
 * @param  sub_event[in]: command related sub event
 * @param  param_num[in]: parameter number
 * @param  param[in]: pointer to parameter buffer
 * @return 0:fail, 1:success
 */
rtk_bt_err_t rtk_bt_ipc_dev_cmd_send(uint32_t profile_id, uint32_t event, uint32_t sub_event, uint32_t param_num, uint32_t *param);

#endif /* _RTK_BT_API_DEV_H_ */