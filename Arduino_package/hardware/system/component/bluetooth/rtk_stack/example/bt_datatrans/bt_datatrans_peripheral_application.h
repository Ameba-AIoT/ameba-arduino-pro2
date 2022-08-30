/**
*********************************************************************************************************
*               Copyright(c) 2015, Realtek Semiconductor Corporation. All rights reserved.
*********************************************************************************************************
* @file      simple_ble_peripheral_application.h
* @brief     simple_ble_peripheral_application
* @details   simple_ble_peripheral_application
* @author    jane
* @date      2015-12-22
* @version   v0.1
* *********************************************************************************************************
*/

#ifndef _BT_DATATRANS_PERIPHERAL_APPLICATION__
#define _BT_DATATRANS_PERIPHERAL_APPLICATION__

#ifdef __cplusplus
extern "C" {
#endif
#include <app_msg.h>
#include <gap_le.h>
#include <profile_server.h>
//#include <privacy_mgnt.h>
void         bt_datatrans_app_handle_io_msg(T_IO_MSG io_driver_msg_recv);
T_APP_RESULT bt_datatrans_app_profile_callback(T_SERVER_ID service_id, void *p_data);
T_APP_RESULT bt_datatrans_app_gap_callback(uint8_t cb_type, void *p_cb_data);

//void app_privacy_callback(T_PRIVACY_CB_TYPE type, T_PRIVACY_CB_DATA cb_data);
//void datatrans_start_adv(void);
#ifdef __cplusplus
}
#endif

#endif

