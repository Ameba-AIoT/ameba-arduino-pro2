/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __RTK_LEGACY_GAP_INTERN_H__
#define __RTK_LEGACY_GAP_INTERN_H__

#include <rtk_bt_defs.h>
#include <rtk_bt_msg_intern.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief     Action of LEGACY GAP message, reused as LEGACY IPC GAP message
 */
typedef enum {
	RTK_LEGACY_ACT_GET_DEVICE_ADDR = 1,
	RTK_LEGACY_ACT_SET_DEVICE_NAME,
	RTK_LEGACY_ACT_SET_PAGE_PARAM,
	RTK_LEGACY_ACT_SET_INQUIRY_PARAM,
	RTK_LEGACY_ACT_SET_DEFAULT_GAP_PARAM,
	RTK_LEGACY_ACT_IPC_REGISTER_GAP_CB,
	RTK_LEGACY_ACT_IPC_UNREGISTER_GAP_CB,
} rtk_legacy_gap_act_t;

/**
 * @brief     All bluetooth gap sync api internal paramters.
 */
/* RTK_BLE_ACT_GET_DEVICE_ADDR */
typedef struct {
	rtk_bt_err_t *pret;
	rtk_legacy_bd_addr_t *paddr;
	void* sync;
} rtk_legacy_gap_addr_param_t;

uint32_t get_legacy_gap_evt_mem_size(uint8_t evt_code);

void* rtk_legacy_gap_deep_copy(rtk_bt_msg_t* msg, void* param);

void rtk_legacy_gap_deep_free(rtk_bt_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __RTK_LEGACY_GAP_INTERN_H__ */
