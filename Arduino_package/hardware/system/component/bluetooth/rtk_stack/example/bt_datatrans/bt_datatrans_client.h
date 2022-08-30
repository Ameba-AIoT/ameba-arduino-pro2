/**
*****************************************************************************************
*     Copyright(c) 2016, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file     simple_ble_client.h
  * @brief    Head file for using Simple BLE Client.
  * @details  Simple BLE data structs and external functions declaration.
  * @author   jane
  * @date     2016-02-18
  * @version  v0.1
  * *************************************************************************************
  */

/* Define to prevent recursive inclusion */
#ifndef _BT_DATATRANS_CLIENT_H_
#define _BT_DATATRANS_CLIENT_H_

#ifdef  __cplusplus
extern "C" {
#endif      /* __cplusplus */

/* Add Includes here */
#include "profile_client.h"


/** @addtogroup DATATRANS SIMP
  * @{
  */

/** @defgroup DATATRANS_Client DATATRANS Client
  * @brief DATATRANS Client
  * @{
  */

/** @defgroup DATATRANS_Client_Exported_Types DATATRANS Client Exported Types
  * @brief  types that other.c files may use all defined here
  * @{
  */
/** @defgroup DATATRANS_UUIDs DATATRANS UUIDs
  * @brief DATATRANS Profile UUID definitions
  * @{
  */
#define GATT_UUID_CHAR_DATA             0xFFE1
#define GATT_UUID_CHAR_DATA_NOTIFY      0xFFE2
#define GATT_UUID_FLOW_CTRL_NOTIFY      0xFFE3
/** @} End of DATATRANS_UUIDs */

#define GATT_UUID_GAP                               0x1800

#define DTS_MAX_LINKS 1

/** @defgroup T_TransClientHandleType T_TransClientHandleType
  * @{ Handle cache for intrested UUIDs
  */
typedef enum
{
    HDL_GAP_SRV_START,              // start handle of gap service
    HDL_GAP_SRV_END,                // end handle of gap service
    HDL_GAP_DEVICE_NAME,            // device name value handle
    HDL_GAP_APPEARANCE,             // appearance value handle
    HDL_DTS_SRV_START,           // start handle of datatrans service
    HDL_DTS_SRV_END,             // end handle of datatrans service
    HDL_DTS_VALUE_WRITE,           // data_write value handle
    HDL_DTS_VALUE_NOTIFY,          // V1_data_notify value handle
    HDL_DTS_VALUE_NOTIFY_CCCD,     // v1_data_notify cccd handle
    HDL_DTS_FLOW,                  // v2_flow_ctrl value handle
    HDL_DTS_FLOW_CCCD,             // v2_flow_ctrl cccd handle
    HDL_DTS_CACHE_LEN
} T_KNS_HANDLE_TYPE;
/** End of T_TransClientHandleType * @} */

/** @defgroup T_TransClientDiscState T_TransClientDiscState
  * @{ used to inform app the discovery procedure
  */
typedef enum
{
    DISC_DTS_IDLE,
    DISC_DTS_START,
    DISC_DTS_DONE,
    DISC_DTS_FAILED
} T_DTS_DISC_STATE;
/** End of T_TransClientDiscState
  * @}
  */


/** @brief kns client read type*/
typedef enum
{
    DTS_READ_DATA_NOTIFY_CCCD,
    DTS_READ_FLOW,
    DTS_READ_FLOW_NOTIFY_CCCD,
} T_DTS_READ_TYPE;

/** @brief KNS client read value*/
typedef struct
{
    uint16_t value_size;
    uint8_t *p_value;
} T_DTS_READ_VALUE;

/** @brief KNS client read data*/
typedef union
{
    T_DTS_READ_VALUE flow_read;
    bool data_notify_cccd;
    bool flow_notify_cccd;
} T_DTS_READ_DATA;

/** @brief KNS client read result*/
typedef struct
{
    T_DTS_READ_TYPE type;
    T_DTS_READ_DATA data;
    uint16_t cause;
} T_DTS_READ_RESULT;


/** @brief KNS client write type*/
typedef enum
{
    DTS_WRITE_DATA,               // data write
    DTS_WRITE_DATA_NOTIFY_CCCD,   // data_notify cccd write
    DTS_WRITE_CTRL,               // flow_ctrl_notify value(r/w/notify) write
    DTS_WRITE_FLOW_NOTIFY_CCCD,   // flow_ctrl_notify cccd write
} T_DTS_WRTIE_TYPE;

/** @brief KNS client write result*/
typedef struct
{
    T_DTS_WRTIE_TYPE type;
    uint16_t cause;
} T_DTS_WRITE_RESULT;

/** @brief KNS client notif/ind receive type*/
typedef enum
{
    DTS_DATA_NOTIFY,
    DTS_FLOW_NOTIFY,
} T_DTS_NOTIF_IND_TYPE;

/** @brief KNS client notif/ind receive data*/
typedef struct
{
    uint16_t value_size;
    uint8_t *p_value;
} T_DTS_NOTIF_IND_VALUE;

/** @brief KNS client notif/ind receive content*/
typedef struct
{
    T_DTS_NOTIF_IND_TYPE type;
    T_DTS_NOTIF_IND_VALUE data;
} T_DTS_NOTIF_IND_DATA;

/** @brief KNS client callback type*/
typedef enum
{
    DTS_CLIENT_CB_TYPE_DISC_STATE,          //!< Discovery procedure state, done or pending.
    DTS_CLIENT_CB_TYPE_READ_RESULT,         //!< Read request's result data, responsed from server.
    DTS_CLIENT_CB_TYPE_WRITE_RESULT,        //!< Write request result, success or fail.
    DTS_CLIENT_CB_TYPE_NOTIF_IND_RESULT,    //!< Notification or indication data received from server.
    DTS_CLIENT_CB_TYPE_INVALID              //!< Invalid callback type, no practical usage.
} T_DTS_CLIENT_CB_TYPE;

/** @brief KNS client callback content*/
typedef union
{
    T_DTS_DISC_STATE      disc_state;
    T_DTS_READ_RESULT     read_result;
    T_DTS_WRITE_RESULT    write_result;
    T_DTS_NOTIF_IND_DATA  notif_ind_data;
} T_DTS_CLIENT_CB_CONTENT;

/** @brief KNS client callback data*/
typedef struct
{
    T_DTS_CLIENT_CB_TYPE     cb_type;
    T_DTS_CLIENT_CB_CONTENT  cb_content;
} T_DTS_CLIENT_CB_DATA;
/** End of KNS_Client_Exported_Types * @} */


extern T_CLIENT_ID datatrans_add_client(P_FUN_GENERAL_APP_CB app_cb, uint8_t link_num);
extern void bt_datatrans_delete_client(void);
extern bool bt_datatrans_client_start_discovery(uint8_t conn_id);
extern bool dts_client_set_data_notify(uint8_t conn_id, bool notify);
extern bool dts_client_set_flow_notify(uint8_t conn_id, bool notify);
extern bool kns_client_write_data_char(uint8_t conn_id, uint16_t length, uint8_t *p_value,
                                       T_GATT_WRITE_TYPE type);
extern bool dts_client_read_by_handle(uint8_t conn_id, T_DTS_READ_TYPE read_type);
/** @} End of DataTrans_Client_Exported_Functions */

/** @} End of TRANS_Client */

/** @} End of Trans */

#ifdef  __cplusplus
}
#endif      /*  __cplusplus */

#endif  /* _DATATRANS_CLIENT_H_ */
