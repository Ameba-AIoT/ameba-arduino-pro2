/*
*******************************************************************************
* Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
*******************************************************************************
*/

#ifndef __RTK_BT_SDP_H__
#define __RTK_BT_SDP_H__

/* -------------------------------- Includes -------------------------------- */
#include <rtk_bt_defs.h>
#include <dlist.h>

#ifdef __cplusplus
extern "C" {
#endif
/* -------------------------------- Defines --------------------------------- */
#define RFC_HFP_CHANN_NUM               1
#define RFC_HSP_CHANN_NUM               2
#define RFC_IAP_CHANN_NUM               3
#define RFC_HS_ASP_CHANN_NUM            5
#define RFC_SPP_CHANN_NUM               6
#define RFC_GFPS_CHANN_NUM              7
#define RFC_SPECIFIC2_CHANN_NUM         8
#define RFC_PBAP_CHANN_NUM              10
#define RFC_SPP_XIAOAI_CHANN_NUM        11
#define RFC_SPP_AMA_CHANN_NUM           12
#define RFC_SPP_BISTO_CTRL_CHANN_NUM    13
#define RFC_SPP_BISTO_AU_CHANN_NUM      14
#define RFC_HS_HID_CHANN_NUM            16
#define RTK_BT_SDK_MAX_RECORD_LENGTH    100

typedef enum {
	RTK_BT_SDP_NONE,           /*!< No Event */
} rtk_bt_sdp_evt_code_t;

/* @brief sdp record struct*/
typedef struct {
	struct list_head          list;                     //!< list of .rtk_sdp_record_t.
	uint8_t                   record[RTK_BT_SDK_MAX_RECORD_LENGTH];                   //!< record data
	uint32_t                  length;                   //!< indicate length of record data
} rtk_sdp_record_t;

/* @brief sdp record param struct*/
typedef struct {
	uint8_t                   record[RTK_BT_SDK_MAX_RECORD_LENGTH];                   //!< record data
	uint32_t                  length;                   //!< indicate length of record data
} rtk_sdp_record_param_t;

/**
 * @typedef   rtk_bt_sdp_cb_t
 * @brief     BT SDP event callback.
 * @param[in] evt_code: Event code
 * @param[in] param: Event parameters
 *
 */
typedef void (*rtk_bt_sdp_cb_t)(rtk_bt_sdp_evt_code_t evt_code, void* param);

/**
 * @brief     Register bt sdk callback.
 * @param[in] cb: callback func pointer
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_sdp_register_callback(rtk_bt_sdp_cb_t cb);

/**
 * @brief     Unregister bt sdk callback.
 * @param     None
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_sdp_unregister_callback(void);

/**
 * @brief  process sdp record enqueue.
 * @param[in] plist: list to sdp record struct
 * @return 0 success; 1 fail.
 */
rtk_bt_err_t rtk_sdp_record_list_enqueue(struct list_head *plist);

/**
 * @brief  process sdp record dequeue.
 * @param  none.
 * @return pointer to record list.
 */
struct list_head *rtk_sdp_record_list_dequeue(void);

/**
 * @brief  sdp record add.
 * @param[in] record: pointer to record data
 * @param[in] length: record data length
 * @return 0 success; 1 fail.
 */
rtk_bt_err_t rtk_sdp_record_add(void *record, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif /*!< __RTK_BT_SDP_H__ */