/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __RTK_BT_SDP_INTERN_H__
#define __RTK_BT_SDP_INTERN_H__

#include <rtk_bt_defs.h>
#include <rtk_bt_msg_intern.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief     Action of SDP 
 */
typedef enum {
	RTK_BT_SDP_ACT_RECORD_ADD = 1,
	RTK_BT_SDP_ACT_IPC_REGISTER_GAP_CB,
	RTK_BT_SDP_ACT_IPC_UNREGISTER_GAP_CB,
} rtk_bt_sdp_act_t;

uint32_t get_bt_sdp_evt_mem_size(uint8_t evt_code);

void* rtk_bt_sdp_deep_copy(rtk_bt_msg_t* msg, void* param);

void rtk_bt_sdp_deep_free(rtk_bt_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BT_SDP_INTERN_H__ */
