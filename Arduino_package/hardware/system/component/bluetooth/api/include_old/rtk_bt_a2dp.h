/*
*******************************************************************************
* Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
*******************************************************************************
*/

#ifndef __RTK_BT_A2DP_H__
#define __RTK_BT_A2DP_H__

/* -------------------------------- Includes -------------------------------- */
#include <rtk_bt_defs.h>
#include <dlist.h>

#ifdef __cplusplus
extern "C" {
#endif
/* -------------------------------- Defines --------------------------------- */
#define RTK_BT_A2DP_MAX_CODEC_PARAM_LENGTH 12
#define RTK_BT_A2DP_MAX_STREAM_DATA_LENGTH 1024

typedef enum {
	RTK_BT_A2DP_EVT_CONN_IND,                      /*!< A2DP connection indication */
	RTK_BT_A2DP_EVT_CONFIG_CMPL,                   /*!< A2DP configure complete */
	RTK_BT_A2DP_EVT_STREAM_OPEN,                   /*!< A2DP stream open */
	RTK_BT_A2DP_EVT_STREAM_START_IND,              /*!< A2DP stream start indication */
	RTK_BT_A2DP_EVT_STREAM_START_RSP,              /*!< A2DP stream start response */
	RTK_BT_A2DP_EVT_STREAM_STOP,                   /*!< A2DP stream stop */
	RTK_BT_A2DP_EVT_STREAM_CLOSE,                  /*!< A2DP stream close */
	RTK_BT_A2DP_EVT_STREAM_SBC_DATA_IND,           /*!< A2DP stream sbc data indication */
} rtk_bt_a2dp_evt_code_t;

/**
 * @struct    rtk_bt_a2dp_codec_param_t
 * @brief     Bluetooth A2DP stream data indication.
 */
typedef struct {
	uint8_t  codec_type;                                /*!< codec type */
	uint32_t length;                                    /*!< codec param data length */
	uint8_t  data[RTK_BT_A2DP_MAX_CODEC_PARAM_LENGTH];                                      /*!< codec data */
} rtk_bt_a2dp_codec_param_t;

/**
 * @struct    rtk_bt_a2dp_codec_t
 * @brief     Bluetooth A2DP codec status.
 */
typedef struct {
	uint8_t codec_type;                                 /*!< indicate codec */
} rtk_bt_a2dp_codec_t;

/**
 * @struct    rtk_bt_a2dp_stream_start_t
 * @brief     Bluetooth A2DP stream start indication.
 */
typedef struct {
	uint8_t active_a2dp_link_index;                     /*!< stream index */
	uint8_t stream_cfg;                                 /*!< stream cfg */
} rtk_bt_a2dp_stream_start_t;

/**
 * @struct    rtk_bt_a2dp_stream_start_t
 * @brief     Bluetooth A2DP stream start indication.
 */
typedef struct {
	uint32_t length;                                    /*!< stream data length */
	uint8_t  data[RTK_BT_A2DP_MAX_STREAM_DATA_LENGTH];  /*!< stream data */
} rtk_bt_a2dp_stream_data_t;

/**
 * @typedef   rtk_bt_a2dp_cb_t
 * @brief     BT a2dp event callback.
 * @param[in] evt_code: Event code
 * @param[in] param: Event parameters
 *
 */
typedef void (*rtk_bt_a2dp_cb_t)(rtk_bt_a2dp_evt_code_t evt_code, void* param);

/**
 * @brief     Register bt a2dp callback.
 * @param[in] cb: callback func pointer
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_a2dp_register_callback(rtk_bt_a2dp_cb_t cb);

/**
 * @brief     Unegister bt a2dp callback.
 * @param[in] cb: callback func pointer
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_a2dp_unregister_callback(void);

/**
 * @brief  a2dp codec configure.
 * @param[in] codec_type: codec type
 * @param[in] codec_t: pointer to codec data
 * @param[in] length: codec data length
 * @return 0 success; 1 fail.
 */
rtk_bt_err_t rtk_a2dp_codec_cfg(uint8_t codec_type, void *codec_t, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif /*!< __RTK_BT_A2DP_H__ */