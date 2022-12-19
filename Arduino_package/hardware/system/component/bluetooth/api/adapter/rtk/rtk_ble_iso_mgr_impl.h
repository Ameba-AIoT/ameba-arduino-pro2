/*
 *******************************************************************************
 * Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __RTK_BLE_ISO_MGR_IMPL_H__
#define __RTK_BLE_ISO_MGR_IMPL_H__

#include <rtk_bt_defs.h>
#include "rtk_bt_config.h"
#include "app_msg.h"

#ifdef __cplusplus
extern "C" {
#endif


#define IO_MSG_TYPE_LE_MGR_SUBTYPE_SEND_ISO_DATA 0x0001
#define IO_MSG_TYPE_LE_MGR_SUBTYPE_SEND_ISO_DATA_PARAM_BIS_BIT 0x0001
#define IO_MSG_TYPE_LE_MGR_SUBTYPE_SEND_ISO_DATA_PARAM_CIS_BIT 0x0002

rtk_bt_err_t rtk_ble_iso_mgr_send_event_to_app(uint8_t event_code, void * param);
void rtk_ble_iso_mgr_handle_io_msg(T_IO_MSG *p_io_msg);
rtk_bt_evt_status_t rtk_ble_iso_mgr_iso_data_send_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_iso_data_confirm_impl(void *data);

rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_init_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_get_conn_id_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_get_cis_info_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_get_isoch_info_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_setup_path_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_remove_path_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_disconnect_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_read_tx_sync_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_read_link_quality_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_register_direct_callback_impl(void *direct_cb);

rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_acceptor_accept_cis_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_acceptor_reject_cis_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_acceptor_config_sdu_param_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_acceptor_config_cis_req_action_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_acceptor_register_callback_impl(void *data);

rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_initiator_add_cis_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_initiator_set_cig_param_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_initiator_set_cis_param_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_initiator_start_setting_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_initiator_set_cis_acl_link_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_initiator_create_cis_by_cig_id_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_initiator_create_cis_by_cis_conn_handle_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_initiator_get_cis_conn_handle_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_initiator_remove_cig_impl(void *data);
rtk_bt_evt_status_t rtk_ble_iso_mgr_cig_initiator_register_callback_impl(void *data);

bool rtk_ble_iso_cig_init(uint8_t cig_max_num,uint8_t cis_max_num);
void rtk_ble_iso_cig_deinit(void);

#ifdef __cplusplus
}
#endif

#endif  /* __RTK_BLE_ISO_MGR_IMPL_H__ */