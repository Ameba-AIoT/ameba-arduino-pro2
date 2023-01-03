/*
*******************************************************************************
* Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
*******************************************************************************
*/

#ifndef __RTK_BT_AVRCP_H__
#define __RTK_BT_AVRCP_H__

/* -------------------------------- Includes -------------------------------- */
#include <rtk_bt_defs.h>
#include <dlist.h>

#ifdef __cplusplus
extern "C" {
#endif
/* -------------------------------- Defines --------------------------------- */

typedef enum {
	RTK_BT_AVRCP_EVT_CONN_IND,                      /*!< AVRCP connection indication */
	RTK_BT_AVRCP_EVT_VOLUME_CHANGED,                /*!< AVRCP volume changed */
	RTK_BT_AVRCP_EVT_VOLUME_UP,                     /*!< AVRCP volume up */
	RTK_BT_AVRCP_EVT_VOLUME_DOWN,                   /*!< AVRCP volume down */
	RTK_BT_AVRCP_EVT_REG_VOLUME_CHANGED,            /*!< AVRCP volume reg changed */
	RTK_BT_AVRCP_EVT_CONN_CMPL,                     /*!< AVRCP conn completion */
	RTK_BT_AVRCP_EVT_PLAY_STATUS_CHANGED,           /*!< AVRCP plat status changed */
} rtk_bt_avrcp_evt_code_t;

/**
 * @struct    rtk_bt_avrcp_volume_t
 * @brief     Bluetooth AVRCP volume status.
 */
typedef struct {
	uint8_t volume;                                 /*!< indicate play volume */
} rtk_bt_avrcp_volume_t;

/**
 * @struct    rtk_bt_avrcp_sub_event_t
 * @brief     Bluetooth AVRCP play status.
 */
typedef struct {
	uint8_t avrcp_play_status;                      /*!< indicate play status */
} rtk_bt_avrcp_sub_event_t;

/**
 * @typedef   rtk_bt_avrcp_cb_t
 * @brief     BT avrcp event callback.
 * @param[in] evt_code: Event code
 * @param[in] param: Event parameters
 *
 */
typedef void (*rtk_bt_avrcp_cb_t)(rtk_bt_avrcp_evt_code_t evt_code, void* param);

/**
 * @brief     Register bt avrcp callback.
 * @param[in] cb: callback func pointer
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_avrcp_register_callback(rtk_bt_avrcp_cb_t cb);

/**
 * @brief     Unegister bt avrcp callback.
 * @param[in] cb: callback func pointer
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_avrcp_unregister_callback(void);

#ifdef __cplusplus
}
#endif

#endif /*!< __RTK_BT_AVRCP_H__ */