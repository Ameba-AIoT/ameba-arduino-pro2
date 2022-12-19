/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __RTK_BT_MAIN_INTERN_H__
#define __RTK_BT_MAIN_INTERN_H__

#include <rtk_bt_defs.h>
#include <rtk_bt_msg_intern.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief     Action of BT main message
 */
typedef enum {
    RTK_BT_ACT_MAIN_INIT = 0,
    RTK_BT_ACT_MAIN_DEINIT,
    RTK_BT_ACT_MAIN_GET_STATUS,
} rtk_bt_main_act_t;

/**
 * @brief     Action of BT IPC main message
 */
enum {
    RTK_BT_MAIN_IPC_ACT_PRE_ENABLE = 1,
    RTK_BT_MAIN_IPC_ACT_ENABLE,
    RTK_BT_MAIN_IPC_ACT_DISABLE,
};


/**
 * @brief     Bluetooth enable status
 */
typedef enum {
    RTK_BT_DISABLED = 0,
    RTK_BT_ENABLING,
    RTK_BT_ENABLED,
    RTK_BT_DISABLING
} rtk_bt_status_t;

/**
 * @brief     Bluetooth enable status Macros
 */
extern uint8_t rtk_bt_en_status;
#define RTK_BT_IS_ENABLED()          (RTK_BT_ENABLED  == rtk_bt_en_status)
#define RTK_BT_IS_DISABLED()         (RTK_BT_DISABLED == rtk_bt_en_status)
#define RTK_BT_SET_EN_STATUS(status) (rtk_bt_en_status = status)

/**
 * @brief     Bluetooth main sync api paramters definition.
 */
typedef enum {
    RTK_BT_MAIN_RET_OK,
    RTK_BT_MAIN_RET_FAIL,
} rtk_bt_main_ret_t;

typedef struct {
    rtk_bt_main_ret_t* pret;
    void* sync;
} rtk_bt_main_evt_param_t;

/**
 * @brief     Deep copy function for BT main.
 *
 * @param[in] msg: BT message
 * @param[in] param: Pointer to BT paramters
 * 
 */
void* rtk_bt_main_deep_copy(rtk_bt_msg_t* msg, void* param);

/**
 * @brief     Deep free function for BT main.
 *
 * @param[in] msg: BT message
 * 
 */
void rtk_bt_main_deep_free(rtk_bt_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BT_MAIN_INTERN_H__ */