/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __RTK_BT_MSG_INTERN_H__
#define __RTK_BT_MSG_INTERN_H__

#include <rtk_bt_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MSG_RESERVED_AREA_SIZE 8
#define USE_RESERVED_AREA(size) (size <= MSG_RESERVED_AREA_SIZE)

/**
 * @brief     Event message type definition
 */
typedef struct rtk_bt_msg {
    uint8_t sig;                       /* signal type of this message */
    uint8_t pid;                       /* profile id */
    union {                            /* anonymous union */
        uint8_t act;                   /* profile action code */
        uint8_t evt;                   /* profile event code */
    };
    uint8_t flag;                      /* the data type in message */
    void*  data;                       /* data with this message */
    uint8_t reserved_area[MSG_RESERVED_AREA_SIZE];
} rtk_bt_msg_t;

/**
 * @brief     Signal type of this message
 */
typedef enum {
    RTK_BT_SIG_CALL = 0,               /* Caller, app to stack, async   */
    RTK_BT_SIG_EVENT,                  /* Event, stack to callback task */
    RTK_BT_SIG_RESERVED,               /* Reserved, for future use      */
} rtk_bt_sig_t;

/**
 * @brief     Profile ID of this message
 */
typedef enum {
    RTK_BT_PID_MAIN = 0,
    RTK_BT_PID_GAP_BLE,
    RTK_BT_PID_GAP_LEGACY,
    RTK_BT_PID_SDP,
    RTK_BT_PID_AVRCP,
    RTK_BT_PID_A2DP,
    RTK_BT_PID_GATT,
    RTK_BT_PID_GATTC,
    RTK_BT_PID_GATTS,
    RTK_BT_PID_LE_ISO_MGR,
    RTK_BT_PID_NUM,
} rtk_bt_pid_t;

/* Different action defined in different *.h */

/**
 * @brief     Operation of how to create data in message
 */
typedef enum {
    MSG_DATA_ATTACH = 1,
    MSG_DATA_ALLOC,
    MSG_DATA_ALLOC_COPY,
} rtk_bt_msg_data_create_op_t;

/**
 * @brief     Create API/Event message.
 *
 * @param[in] sig: Signal type of this message
 * @param[in] pid: Profile id
 * @param[in] act: Profile action code, multiplex event code
 *
 * @return    - NULL:  Failed
 *            - Other: Pointer to API/Event message
 */
rtk_bt_msg_t* rtk_bt_msg_create(uint8_t sig, uint8_t pid, uint8_t act);

/**
 * @brief     Delete API/Event Message.
 *
 * @param[in] msg: Pointer to API/Event message
 *
 */
void rtk_bt_msg_delete(rtk_bt_msg_t* msg);

/**
 * @brief     Create API/Event message data.
 *
 * @param[in] msg: Pointer to API/Event message
 * @param[in] op: Operation of how to create data in message
 * @param[in] param: Pointer to BT paramters
 *
 * @return    - NULL:  Failed
 *            - Other: Pointer to API/Event message
 */
rtk_bt_err_t rtk_bt_msg_data_create(rtk_bt_msg_t* msg, rtk_bt_msg_data_create_op_t op, void* param);

/**
 * @brief     Delete API/Event Message data.
 *
 * @param[in] msg: Pointer to API/Event message
 *
 */
void rtk_bt_msg_data_delete(rtk_bt_msg_t* msg);

/**
 * @brief     Send API/Event message
 *
 * @param[in] msg: Pointer to API/Event message
 *
 * @return    - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_msg_send(rtk_bt_msg_t* msg);

/**
 * @brief     combination of rtk_bt_msg_create and rtk_bt_msg_data_create
 *
 * @param[in] sig: Signal type
 * @param[in] pid: Profile id
 * @param[in] act: Profile action code
 * @param[in] op: Operation of how to create data in message
 * @param[in] param: Pointer to BT paramters
 * 
 * @return    - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_msg_t* rtk_bt_msg_create_with_data(uint8_t sig, uint8_t pid, uint8_t act,
                                         rtk_bt_msg_data_create_op_t op, void *param);

/**
 * @brief     Delete API/Event Message and data in it.
 *
 * @param[in] msg: Pointer to API/Event message
 *
 */
void rtk_bt_msg_delete_with_data(rtk_bt_msg_t* msg);

/**
 * @brief     combination of rtk_bt_msg_create_with_data and rtk_bt_msg_send
 *
 * @param[in] sig: Signal type
 * @param[in] pid: Profile id
 * @param[in] act: Profile action code
 * @param[in] param: Pointer to BT paramters
 * 
 * @return    - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_msg_create_and_send(uint8_t sig, uint8_t pid, uint8_t act, void* param);

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BT_MSG_INTERN_H__ */