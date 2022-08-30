/**
 * @file      rtk_bt_defs.h
 * @author    benling_xu@realsil.com.cn
 * @brief     Bluetooth common type definition
 * @copyright Copyright (c) 2022. Realtek Semiconductor Corporation. All rights reserved.
 */

#ifndef __RTK_BT_DEFS_H__
#define __RTK_BT_DEFS_H__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @typedef   rtk_bt_err_t
 * @brief     Bluetooth API return value definition.
 */
typedef enum
{
    RTK_BT_OK = 0,                      /*!< 0, means success */
    RTK_BT_FAIL,                        /*!< 1, means fail */
} rtk_bt_err_t;

/**
 * @typedef   rtk_bt_evt_status_t
 * @brief     Bluetooth event status.
 */
typedef enum
{
    RTK_BT_EVT_ERR_NONE = 0,            /*!< 0, means success */
    RTK_BT_EVT_ERR_FAIL,                /*!< 1, means common failure */
    RTK_BT_EVT_ERR_NO_PERM,             /*!< 2, form 2 to 16 similar to errno.h */
    RTK_BT_EVT_ERR_NOT_READY,           /*!< 3 */
    RTK_BT_EVT_ERR_NOMEM,               /*!< 4 */
    RTK_BT_EVT_ERR_BUSY,                /*!< 5 */
    RTK_BT_EVT_ERR_DONE,                /*!< 6 */
    RTK_BT_EVT_ERR_UNSUPPORTED,         /*!< 7 */
    RTK_BT_EVT_ERR_PARM_INVALID,        /*!< 8 */
    RTK_BT_EVT_ERR_UNHANDLED,           /*!< 9 */
    RTK_BT_EVT_ERR_NEED_TRY_AGAIN,      /*!< 10 */
    RTK_BT_EVT_ERR_ALREADY_DONE,        /*!< 11 */
    RKT_BT_EVT_ERR_ALREADY_IN_PROGRESS, /*!< 12 */
    RTK_BT_EVT_ERR_IO,                  /*!< 13 */
    RTK_BT_EVT_ERR_NO_BUFS,             /*!< 14 */
    RTK_BT_EVT_ERR_NO_ENTRY,            /*!< 15 */
    RTK_BT_EVT_ERR_NO_RESOURCE,         /*!< 16 */
    RTK_BT_EVT_ERR_ADV_OVER_LENGTH,     /*!< 17, following value related to BT stack */
    RTK_BT_EVT_ERR_NOT_CONNECTED,       /*!< 18 */
    RTK_BT_EVT_ERR_IRK_NOT_FOUND,       /*!< 19 */
    RTK_BT_EVT_ERR_STATE_INVALID,       /*!< 20 */
    RTK_BT_EVT_ERR_CREDITS,             /*!< 21 */
    RTK_BT_EVT_ERR_SEND_REQ_FAILURE,    /*!< 22 */
    RTK_BT_EVT_ERR_PDU_SIZE_INVALID,    /*!< 23 */
    RTK_BT_EVT_ERR_CONN_NUM_LIMIT,      /*!< 24 */
    RTK_BT_EVT_ERR_NO_BOND,             /*!< 25 */
    RTK_BT_EVT_ERR_HCI_EVT,             /*!< 26 */
    RTK_BT_EVT_ERR_UNKNOWN,             /*!< 27, means unknown value */
} rtk_bt_evt_status_t;

/**
 * @typedef   rtk_ble_addr_type_t
 * @brief     Bluetooth device address type definition.
 */
typedef enum
{
    BLE_ADDR_TYPE_PUBLIC = 0x00,        /*!< Public Device Address */
    BLE_ADDR_TYPE_RANDOM = 0x01,        /*!< Random Device Address */
    BLE_ADDR_TYPE_RPA_PUBLIC = 0x02,    /*!< Public Identity Address (RPA) */
    BLE_ADDR_TYPE_RPA_RANDOM = 0x03,    /*!< Random (static) Identity Address (RPA)*/
} rtk_ble_addr_type_t;

/**
 * @def       RTK_BD_ADDR_LEN
 * @brief     Bluetooth device address length macro.
 */
#define RTK_BD_ADDR_LEN 6

/**
 * @typedef   rtk_bt_bd_addr_t
 * @brief     Bluetooth device address type definition.
 */
typedef uint8_t rtk_bt_bd_addr_t[RTK_BD_ADDR_LEN];

/**
 * @struct    rtk_ble_bd_addr_t
 * @brief     Bluetooth LE device address type definition.
 */
typedef struct
{
    rtk_ble_addr_type_t type;           /*!< address type */
    rtk_bt_bd_addr_t addr;              /*!< address */
} rtk_ble_bd_addr_t;

/**
 * @defgroup  BT_Macros BT_Macros
 * @brief     List all BT related macros definition
 */

/**
 * @defgroup  BT_Types BT_Types
 * @brief     List all BT related type definition
 */

/**
 * @defgroup  BT_APIs BT_APIs
 * @brief     List all BT related APIs
 */

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BT_DEFS_H__ */
