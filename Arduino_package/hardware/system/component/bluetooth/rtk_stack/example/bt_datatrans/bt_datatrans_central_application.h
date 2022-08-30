/**
*********************************************************************************************************
*               Copyright(c) 2016, Realtek Semiconductor Corporation. All rights reserved.
*********************************************************************************************************
* @file      simple_ble_central_application.h
* @brief     simpleBLEMultilink app implementation
* @details   simpleBLEMultilink app implementation
* @author    jane
* @date      2016-02-18
* @version   v0.1
* *********************************************************************************************************
*/
#if CENTRAL_MODE

#ifndef _BT_DATATRANS_CENTRAL_APPLICATION_H_
#define _BT_DATATRANS_CENTRAL_APPLICATION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "profile_client.h"
#include "app_msg.h"

extern T_APP_RESULT bt_datatrans_app_client_callback(T_CLIENT_ID client_id, uint8_t conn_id,
                                        void *pData);
#ifdef __cplusplus
}
#endif

#endif

#endif
