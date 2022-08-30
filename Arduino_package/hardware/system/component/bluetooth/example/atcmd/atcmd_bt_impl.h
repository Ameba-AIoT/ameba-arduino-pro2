/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __ATCMD_BT_IMPL_H__
#define __ATCMD_BT_IMPL_H__

#include <rtk_bt_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

void convert_bd_addr_to_str(rtk_ble_bd_addr_t *addr, char *str, uint32_t len);

int ble_at_cmd_scan(int argc, char **argv);

int ble_at_cmd_connect(int argc, char **argv);

int ble_at_cmd_disconnect(int argc, char **argv);

int ble_at_cmd_auth(int argc , char **argv);

int ble_at_cmd_pair_confirm(int argc, char **argv);

int ble_at_cmd_bond_info(int argc, char **argv);

int ble_at_cmd_get_all_conn_info(int argc, char **argv);

int ble_at_cmd_update_conn_param(int argc, char **argv);

int ble_at_cmd_set_phy(int argc, char **argv);

int ble_at_cmd_modify_whitelist(int argc, char **argv);

int ble_at_cmd_private(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif  /* __ATCMD_BT_IMPL_H__ */