/**
*****************************************************************************************
*     Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file     bt_ipc_dev_trx.h
  * @brief    Source file for bt ipc dev trx.
  * @details  bt ipc dev trx.
  * @author   sherman
  * @date     2021-10-20
  * @version  v1.0
  * *************************************************************************************
  */
#ifndef _A2DP_APP_INTF_H_
#define _A2DP_APP_INTF_H_

/* -------------------------------- Includes -------------------------------- */
#include <basic_types.h>
#include "osdep_service.h"
#include "bt_ipc_dev_trx.h"
#include "bt_ipc_dev_api.h"

#define AUDIO_HANDLE_STACK_SIZE 1024 * 2
#define AUDIO_HANDLE_TASK_PRORITY_HIGH 4
#define AUDIO_HANDLE_TASK_PRORITY_MIDDLE 3
#define AUDIO_HANDLE_TASK_PRORITY_LOW 2

/* ------------------------------- Data Types ------------------------------- */

struct audio_handle_priv {
	_queue                      stream_track_queue;        //!< indicate stream data.
	uint8_t                     cmdthd_running;            //!< indicate treadrunning state.
	uint32_t                    enqueue_num;               //!< indicate enqueued stream numbers.
};

/** @brief audio stream object struct*/
struct audio_stream_obj {
	struct list_head	    list;                         //!< list struct.
	uint8_t                 type;                         //!< indicate application type.
	uint8_t                 *data;                        //!< indicate buffer.
	uint16_t                size;                         //!< indicate buffer size.
};

/**
 * @brief  process the ipc message.
 * @param  none.
 * @return none.
 */
uint8_t bt_a2dp_sink_data_handle(bt_ipc_dev_tx_message *p_ipc_msg);

/**
 * @brief  process the ipc message.
 * @param  none.
 * @return none.
 */
uint8_t bt_a2dp_sink_event_handle(bt_ipc_dev_request_message *p_ipc_msg);

#endif /* _A2DP_APP_INTF_H_ */