/*
*******************************************************************************
* Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
*******************************************************************************
*/

#ifndef __RTK_LEGACY_GAP_H__
#define __RTK_LEGACY_GAP_H__

/* -------------------------------- Includes -------------------------------- */
#include <rtk_bt_defs.h>

#ifdef __cplusplus
extern "C" {
#endif
/* -------------------------------- Defines --------------------------------- */

/**
 * @def       RTK_DEV_DEVICE_NAME_MAX
 * @brief     Bluetooth device name max length.
 */
#define RTK_DEV_DEVICE_NAME_MAX         (39+1)

/**
 * @typedef   rtk_legacy_gap_default_param_type_t
 * @brief     Bluetooth LE GAP default paramters definition.
 */
typedef enum
{
	RTK_LEGACY_GAP_PARAM_NULL                                 = 0x00, /*!< 0x00, no meaning, just prevent the enum is empty */
	RTK_LEGACY_GAP_MTU_SIZE                                   = 0x01, /*!< 0x01, means default mtu size */
} rtk_legacy_gap_default_param_type_t;

/**
 * @typedef   rtk_legacy_gap_evt_code_t
 * @brief     Bluetooth legacy gap event code definition
*/
typedef enum {
	RTK_LEGACY_EVT_SET_DEVICE_NAME_DONE,           /*!< comes when RTK_LEGACY_ACT_SET_DEVICE_NAME is done */
	RTK_LEGACY_EVT_SET_PAGE_PARAM_DONE,            /*!< comes when RTK_LEGACY_ACT_SET_PAGE_PARAM is done */
	RTK_LEGACY_EVT_SET_INQUIRY_PARAM_DONE,         /*!< comes when RTK_LEGACY_ACT_SET_INQUIRY_PARAM is done */
} rtk_legacy_gap_evt_code_t;

/**
 * @struct    rtk_legacy_gap_default_param_value_t
 * @brief     Bluetooth LEGACY GAP default paramter definition.
 */
typedef union {
	uint16_t mtu_size;                      /*!< MTU size */
} rtk_legacy_gap_default_param_value_t;

/**
 * @struct    rtk_legacy_set_dev_name_done_t
 * @brief     Bluetooth LEGACY GAP set name done event definition (ASYNC).
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_legacy_set_dev_name_done_t;

/**
 * @struct    rtk_legacy_set_page_param_done_t
 * @brief     Bluetooth LEGACY set PAGE param done event definition (ASYNC).
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_legacy_set_page_param_done_t;

/**
 * @struct    rtk_legacy_set_inquiry_param_done_t
 * @brief     Bluetooth LEGACY set PAGE param done event definition (ASYNC).
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_legacy_set_inquiry_param_done_t;

/**
 * @struct    rtk_legacy_page_param_t
 * @brief     Bluetooth Legacy Page Parameter.
 */
typedef struct
{
	uint8_t pagescan_type;                           /*!< page scan type */
	uint16_t pagescan_interval;                      /*!< page scan interval */
	uint16_t pagescan_window;                        /*!< page scan window */
	uint16_t page_timeout;                           /*!< page scan timeout */
} rtk_legacy_page_param_t;

/**
 * @struct    rtk_legacy_inquiry_param_t
 * @brief     Bluetooth Legacy Inquiry Parameter.
 */
typedef struct
{
	uint8_t inquiryscan_type;                         /*!< inquiry scan type */
	uint16_t inquiryscan_window;                      /*!< inquiry scan window */
	uint16_t inquiryscan_interval;                    /*!< inquiry scan interval */
	uint8_t inquiry_mode;                             /*!< inquiry scan mode */
} rtk_legacy_inquiry_param_t;


/**
 * @typedef   rtk_legacy_gap_cb_t
 * @brief     Legacy GAP event callback.
 * @param[in] evt_code: Event code
 * @param[in] param: Event parameters
 *
 */
typedef void (*rtk_legacy_gap_cb_t)(rtk_legacy_gap_evt_code_t evt_code, void* param);

/**
 * @brief     Register legacy gap callback.
 * @param[in] cb: callback func pointer
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_legacy_gap_register_callback(rtk_legacy_gap_cb_t cb);

/**
 * @brief     Unregister legacy gap callback.
 * @param     None
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_legacy_gap_unregister_callback(void);

/**
 * @fn        rtk_bt_err_t rtk_legacy_gap_set_default_param(rtk_legacy_gap_default_param_type_t type, rtk_legacy_gap_default_param_value_t *param)
 * @brief     Set default LEGACY GAP param before stack started [SYNC].
 * @param[in] type: The default LEGACY GAP param type
 * @param[in] param: LEGACY GAP param value need to be set
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_legacy_gap_set_default_param(rtk_legacy_gap_default_param_type_t type,
											rtk_legacy_gap_default_param_value_t *param);

/**
 * @brief     Set default LEGACY GAP param before stack started [SYNC].
 * @param[in] type: The default LEGACY GAP param type
 * @param[in] param: LEGACY GAP param value need to be set
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_legacy_gap_get_address(rtk_legacy_bd_addr_t *addr);

/**
 * @brief     Set default LEGACY GAP device name.
 * @param[in] name: name pointer
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_legacy_gap_set_device_name(const uint8_t *name);

/**
 * @brief     Set default LEGACY GAP page param.
 * @param[in] page_param: page parameters
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_legacy_gap_set_page_param(rtk_legacy_page_param_t *page_param);

/**
 * @brief     Set default LEGACY GAP inquiry param.
 * @param[in] inquiry_param: inquiry parameters
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_legacy_gap_set_inquiry_param(rtk_legacy_inquiry_param_t *inquiry_param);

#ifdef __cplusplus
}
#endif

#endif /*!< __RTK_LEGACY_GAP_H__ */