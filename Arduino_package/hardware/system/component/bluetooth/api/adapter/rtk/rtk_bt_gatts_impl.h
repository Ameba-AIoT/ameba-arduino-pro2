/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation All rights reserved
 *******************************************************************************
 */

#ifndef __RTK_BT_GATTS_IMPL_H__
#define __RTK_BT_GATTS_IMPL_H__

#include <rtk_bt_defs.h>
#include <rtk_bt_intern.h>
#include <rtk_bt_msg_intern.h>
#include <profile_server.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_GATT_SRV_APP_ID 0xFF

typedef enum {
    SRV_UNUSED = 0,
    SRV_ALLOC_FOR_INCLUDE,
    SRV_WAIT_FOR_REG,
    SRV_REGISTERING,
    SRV_REGISTERED,
} rtk_bt_gatts_srv_reg_status_t;

typedef struct {
    /* Index of CCCD */
    uint16_t index;
    /* Value of CCCD */
    uint16_t cccd_val;
} rtk_bt_gatts_cccd_record_t;

typedef struct {
    /* Service register status */
    rtk_bt_gatts_srv_reg_status_t status;
    /* Service ID designated by APP */
    uint8_t app_id;
    /* Record the order of wait for resgister service  */
    // uint8_t wait_srv_order;
    /* Service ID designated by Stack */
    T_SERVER_ID service_id;
    /* The count of this service */
    uint16_t count;
    /* The pointer of first attribute of this service in T_ATTRIB_APPL */
    void* first_attr;
    /* TODO: Record CCCD value in every service for checking 
     * validity of sending indication and notification.
     */
    //rtk_bt_gatts_cccd_record_t cccd_record[RTK_BT_GATTS_CCCD_NUM];
} rtk_bt_gatts_srv_ctrl_t;

typedef struct {
    /* Next pending node */
    rtk_node_t node;
    /* Current pending indication or notification */
    rtk_bt_msg_t* req_msg;
	/* APP ID */
	uint8_t app_id;
    /* Service ID */
    T_SERVER_ID service_id;
} rtk_bt_gatts_op_ele_t;

typedef rtk_bt_gatts_op_ele_t rtk_bt_gatts_pending_ind_t;
typedef rtk_bt_gatts_op_ele_t rtk_bt_gatts_waiting_ind_t;
typedef rtk_bt_gatts_op_ele_t rtk_bt_gatts_pending_ntf_t;
typedef rtk_bt_gatts_op_ele_t rtk_bt_gatts_waiting_ntf_t;

/* Alternative: rtk_bt_gatts_app_ctrl_t[RTK_BT_GATTS_SERVICE_NUM]
 * Advantage: when unregister service, easier 
 * Disadvantage: when disconnect, harder; more memory use;
 */
typedef struct {
    /* Registered service control, here use MAX num */
    rtk_bt_gatts_srv_ctrl_t *service[MAX_GATT_SRV_APP_ID + 1];
    /* number of service that is in status wait_for_register or registring or resgisted */
    // uint8_t srv_num;
    /* Whether there is a service is under registery */
    uint8_t srv_registering;
    /* Indicate ops pending queue, for transaction flow (not sent) */
    rtk_list_t pending_ind_q[GAP_MAX_LINKS];
    /* Current waiting idnicate (been sent, only one) */
    rtk_bt_gatts_waiting_ind_t* cur_waiting_ind[GAP_MAX_LINKS];
    /* Notify ops pending queue, for flow control (not sent) */
    rtk_list_t pending_ntf_q[GAP_MAX_LINKS];
    /* Notify ops waiting queue, for flow control (been sent) */
    rtk_list_t waiting_ntf_q[GAP_MAX_LINKS];
    /* Credits for flow control for notify  */
    uint16_t credits;
}  rtk_bt_gatts_app_ctrl_t;

typedef struct {
    uint8_t app_id;
    uint16_t index;
} gatts_ntf_cmp_t;

/**
 * @brief      Implementation for GATT registering service.
 * 
 * @param[in]  msg: The message for registering service app.
 * 
 */
void rtk_bt_gatts_register_service_impl(void* msg);

/**
 * @brief      Implementation for GATT indication.
 * 
 * @param[in]  msg: The message for indication.
 * 
 */
void rtk_bt_gatts_indicate_impl(void* msg);

/**
 * @brief      Implementation for GATT notification.
 * 
 * @param[in]  msg: The message for notification.
 * 
 */
void rtk_bt_gatts_notify_impl(void* msg);

/**
 * @brief      Implementation for response to client read.
 * 
 * @param[in]  msg: The message for read.
 * 
 */
void rtk_bt_gatts_read_resp_impl(void* msg);

/**
 * @brief      Implementation for response to client write.
 * 
 * @param[in]  msg: The message for write.
 * 
 */
void rtk_bt_gatts_write_resp_impl(void* msg);

/**
 * @brief      Initialization for GATT server.
 * 
 * @return     - true : Succeed
 *             - false: Failed
 */
bool rtk_bt_gatts_init(void);

/**
 * @brief      Deinitialization for GATT server.
 * 
 */
void rtk_bt_gatts_deinit(void);

/**
 * @brief      Implementation for GATT server when disconnected.
 * 
 * @param[in]  conn_id: The message for notification.
 * 
 */
void rtk_bt_gatts_disconnect_complete(uint8_t conn_id);

#ifdef __cplusplus
}
#endif

#endif     /* __RTK_BT_GATTS_IMPL_H__ */