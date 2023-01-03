/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation All rights reserved
 *******************************************************************************
 */

#ifndef __RTK_BT_GATTC_IMPL_H__
#define __RTK_BT_GATTC_IMPL_H__

#include <rtk_bt_defs.h>
#include <rtk_bt_intern.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GATTC_APP_CONN_MAP_SIZE     \
    (GAP_MAX_LINKS / 8 + 1)

#define RTK_BT_APP_SET_CONN_MAP(map, conn_id, en)       \
    do {                                                \
        if (en)                                         \
            map[conn_id / 8] |= (1 << (conn_id % 8));   \
        else                                            \
            map[conn_id / 8] &= ~(1 << (conn_id % 8));  \
    } while (0)

#define RTK_BT_APP_IS_ON_CONN(map, conn_id)         \
    (map[conn_id / 8] & (1 << (conn_id % 8)))

typedef struct {
    /* Whether in use */
    uint8_t in_use;
    /* Subscribe value handle */
    uint16_t value_handle;
    /* Subscribe CCC handle */
    uint16_t ccc_handle;
    /* Subscribe CCC value */
    uint16_t value;
} rtk_bt_gattc_subs_record_t;

typedef enum {
    APP_UNREGISTERED = 0,
    APP_REGISTERED,
} rtk_bt_gattc_reg_status_t;

typedef struct {
    /* Whether registered */
    rtk_bt_gattc_reg_status_t is_registered;
    /* APP ID */
    uint8_t app_id;
    /* Connection Map, every bit is one connection */
    uint8_t conn[GATTC_APP_CONN_MAP_SIZE];
    /* Subscribe record, for checking validity of 
     * coming indication and notification from server. 
     */
    rtk_bt_gattc_subs_record_t subs_record[GAP_MAX_LINKS][RTK_BT_GATTC_SUBS_NUM];
} rtk_bt_gattc_app_t;

typedef enum {
    REQ_GATTC_SUBS,
    REQ_GATTC_UNSUBS,
    REQ_GATTC_DISC,
    REQ_GATTC_WRITE,
    REQ_GATTC_READ,
    CMD_GATTC_WRITE,
} rtk_bt_gattc_req_type_t;

typedef struct rtk_bt_gatt_pending_req {
    /* Next pending node */
    rtk_node_t node;
    /* Current pending request */
    rtk_bt_msg_t* req_msg;
    /* Request type */
    rtk_bt_gattc_req_type_t type;
	/* APP ID */
	uint8_t app_id;
} rtk_bt_gattc_op_ele_t;

typedef rtk_bt_gattc_op_ele_t rtk_bt_gattc_pending_subs_t;
typedef rtk_bt_gattc_op_ele_t rtk_bt_gattc_waiting_subs_t;
typedef rtk_bt_gattc_op_ele_t rtk_bt_gattc_pending_req_t;
typedef rtk_bt_gattc_op_ele_t rtk_bt_gattc_waiting_req_t;
typedef rtk_bt_gattc_op_ele_t rtk_bt_gattc_pending_cmd_t;
typedef rtk_bt_gattc_op_ele_t rtk_bt_gattc_waiting_cmd_t;

/* Alternative: rtk_bt_gattc_app_ctrl_t[RTK_BT_GATTC_APP_NUM]
 * Advantage: when unregister app, easier 
 * Disadvantage: when disconnect, harder; more memory use;
 */
typedef struct {
    /* Registered client APP, here use MAX num */
    rtk_bt_gattc_app_t app[RTK_BT_GATTC_APP_NUM];
    /* Current pending subscribe record */
    rtk_list_t pending_subs_q[GAP_MAX_LINKS];
    /* Current waiting subscribe record */
    rtk_bt_gattc_waiting_subs_t* cur_waiting_subs[GAP_MAX_LINKS];
    /* Request pending queue, for transaction flow (not sent) */
    rtk_list_t pending_req_q[GAP_MAX_LINKS];
    /* Current waiting request (been sent, only one) */
    rtk_bt_gattc_waiting_req_t* cur_waiting_req[GAP_MAX_LINKS];
    /* Write CMD pending queue, for flow control (been sent) */
    rtk_list_t pending_cmd_q[GAP_MAX_LINKS];
    /* Notify CMD waiting queue, for flow control (not sent) */
    rtk_list_t waiting_cmd_q[GAP_MAX_LINKS];
    /* Credits for flow control for write CMD  */
    uint16_t credits;
    /* Whether under indication, only yes, can send confirm */
    uint8_t under_ind;
} rtk_bt_gattc_app_ctrl_t;

/**
 * @brief      Implementation for registering GATT client app.
 * 
 * @param[in]  msg: The message for register.
 * 
 */
void rtk_bt_gattc_register_app_impl(void* app);

/**
 * @brief      Implementation for unregistering GATT client app.
 * 
 * @param[in]  msg: The message for unregister.
 * 
 */
void rtk_bt_gattc_unregister_app_impl(void* app);

/**
 * @brief      Implementation for GATT client app subscribe.
 * 
 * @param[in]  msg: The message for subscribe.
 * 
 */
void rtk_bt_gattc_app_subscribe_impl(void* param);

/**
 * @brief      Implementation for GATT client app unsubscribe.
 * 
 * @param[in]  msg: The message for unsubscribe.
 * 
 */
void rtk_bt_gattc_app_unsubscribe_impl(void* param);

/**
 * @brief      Implementation for GATT client discover.
 * 
 * @param[in]  msg: The message for discover.
 * 
 */
void rtk_bt_gattc_discover_impl(void *msg);

/**
 * @brief      Implementation for GATT client read.
 * 
 * @param[in]  msg: The message for read.
 * 
 */
void rtk_bt_gattc_read_impl(void *msg);

/**
 * @brief      Implementation for GATT client write.
 * 
 * @param[in]  msg: The message for write.
 * 
 */
void rtk_bt_gattc_write_impl(void *msg);

/**
 * @brief      Implementation for confirmation to server indication.
 * 
 * @param[in]  msg: The message for confirm.
 * 
 */
void rtk_bt_gattc_confirm_impl(void *msg);

/**
 * @brief      Initialization for GATT client.
 * 
 * @return     - true : Succeed
 *             - false: Failed
 */
bool rtk_bt_gattc_init(void);

/**
 * @brief      Deinitialization for GATT server.
 * 
 */
void rtk_bt_gattc_deinit(void);

#ifdef __cplusplus
}
#endif

#endif     /* __RTK_BT_GATTC_IMPL_H__ */