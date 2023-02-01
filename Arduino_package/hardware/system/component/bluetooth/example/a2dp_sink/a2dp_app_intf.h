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

#define AUDIO_HANDLE_STACK_SIZE 1024 * 4
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
 * @param  event[in]: event
 * @param  sub_event[in]: sub event.
 * @param  len[in]: indicate data length.
 * @param  data[in]: pointer to stream data.
 * @return none.
 */
uint8_t bt_a2dp_sink_data_handle(uint32_t event, uint32_t sub_event, uint32_t len, uint8_t *data);

/**
 * @brief  process the command.
 * @param  event[in]: event
 * @param  sub_event[in]: sub event.
 * @param  param_num[in]: indicate parameter number.
 * @param  param_buf[in]: pointer to parameter value.
 * @return 0: fail 1: success.
 */
uint8_t bt_a2dp_sink_event_handle(uint32_t event, uint32_t sub_event, uint32_t param_num, uint32_t *param_buf);

#endif /* _A2DP_APP_INTF_H_ */