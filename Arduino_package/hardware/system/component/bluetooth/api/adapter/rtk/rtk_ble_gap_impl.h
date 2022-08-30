/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __RTK_BLE_GAP_IMPL_H__
#define __RTK_BLE_GAP_IMPL_H__

#include <gap.h>
#include <gap_msg.h>
#include <rtk_ble_gap.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t conn_is_active(uint8_t conn_id);

uint16_t conn_get_mtu_size(uint8_t conn_id);

void rtk_ble_gap_init(void);

void rtk_ble_gap_deinit(void);

rtk_bt_err_t rtk_ble_gap_get_address_impl(rtk_ble_bd_addr_t* addr);

rtk_bt_evt_status_t rtk_ble_gap_set_device_name_impl(const uint8_t* name);

rtk_bt_evt_status_t rtk_ble_gap_set_appearance_impl(rtk_bt_appearance_t appearance);

rtk_bt_evt_status_t rtk_ble_gap_set_rand_addr_impl(rtk_ble_bd_addr_t *bd_addr);

rtk_bt_evt_status_t rtk_ble_gap_set_adv_data_impl(rtk_ble_adv_data_t *adv_data);

rtk_bt_evt_status_t rtk_ble_gap_set_scan_rsp_data_impl(rtk_ble_scan_rsp_data_t* data);

rtk_bt_evt_status_t rtk_ble_gap_start_adv_impl(rtk_ble_adv_param_t* adv_param);

rtk_bt_evt_status_t rtk_ble_gap_stop_adv_impl(void);

rtk_bt_evt_status_t rtk_ble_gap_set_scan_param_impl(rtk_ble_scan_param_t* param);

rtk_bt_evt_status_t rtk_ble_gap_start_scan_impl(rtk_ble_scan_option_t* option);

rtk_bt_evt_status_t rtk_ble_gap_stop_scan_impl(void);

rtk_bt_evt_status_t rtk_ble_gap_connect_impl(rtk_ble_create_conn_param_t *param);

rtk_bt_evt_status_t rtk_ble_gap_disconnect_impl(rtk_ble_disconn_param_t *param);

rtk_bt_evt_status_t rtk_ble_gap_update_conn_param_impl(rtk_ble_update_conn_param_t* param);

rtk_bt_evt_status_t rtk_ble_gap_modify_whitelist_impl(rtk_ble_wl_op_param_t* op_param);

rtk_bt_err_t rtk_ble_gap_get_whitelist_size_impl(uint16_t *len);

rtk_bt_evt_status_t rtk_ble_gap_read_rssi_impl(rtk_ble_read_rssi_param_t* param);

rtk_bt_err_t rtk_ble_gap_get_conn_info_impl(uint8_t conn_id, rtk_ble_conn_info_t* info);

rtk_bt_evt_status_t rtk_ble_gap_set_channels_impl(rtk_ble_channels_t chan_map);

rtk_bt_evt_status_t rtk_ble_gap_write_default_data_len_impl(rtk_ble_data_len_t* param);

rtk_bt_evt_status_t rtk_ble_gap_set_data_len_impl(rtk_ble_conn_data_len_t* param);

// rtk_bt_evt_status_t rtk_ble_gap_set_default_phy_impl(rtk_ble_default_phy_param_t* phy_param);

rtk_bt_evt_status_t rtk_ble_gap_set_phy_impl(rtk_ble_conn_phy_param_t* phy_param);

rtk_bt_evt_status_t rtk_ble_gap_set_privacy_impl(uint8_t enable);

rtk_bt_evt_status_t rtk_ble_gap_set_privacy_mode_impl(rtk_ble_privacy_mode_param_t *param);

rtk_bt_evt_status_t rtk_ble_sm_set_security_param_impl(rtk_ble_sm_sec_parm_t *param);

rtk_bt_evt_status_t rtk_ble_sm_start_security_impl(rtk_ble_conn_security_t *param);

rtk_bt_evt_status_t rtk_ble_sm_pairing_confirm_impl(rtk_ble_pair_cfm_t *param);

rtk_bt_evt_status_t rtk_ble_sm_passkey_entry_impl(rtk_ble_auth_key_input_t *param);

rtk_bt_evt_status_t rtk_ble_sm_passkey_confirm_impl(rtk_ble_auth_key_confirm_t *param);

rtk_bt_evt_status_t rtk_ble_sm_set_oob_tk_impl(rtk_ble_auth_oob_key_t *param);

rtk_bt_err_t rtk_ble_sm_get_bond_num_impl(uint8_t *bond_num);

rtk_bt_err_t rtk_ble_sm_get_bond_info_impl(rtk_ble_bond_info_t *info, uint8_t *size, uint8_t *actual);

rtk_bt_evt_status_t rtk_ble_sm_delete_bond_impl(rtk_ble_bd_addr_t *bd_addr);

rtk_bt_evt_status_t rtk_ble_sm_clear_bond_impl(void);

/**
 * @brief      Handle status indication message.
 *
 * @param[in]  gap_msg: GAP meaasge in Status indication message
 * 
 */
typedef void (*rtk_bt_evt_status_hdl)(T_LE_GAP_MSG* gap_msg);

extern const rtk_bt_evt_status_hdl rtk_bt_evt_status_hdl_table[];

/**
 * @brief     GAP callback handle.
 *
 * @param[in] pid: GAP callback type
 * @param[in] data: GAP callback data
 *
 * @return    - APP Return Result
 */
T_APP_RESULT rtk_ble_gap_callback(uint8_t type, void *data);

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BLE_GAP_IMPL_H__ */