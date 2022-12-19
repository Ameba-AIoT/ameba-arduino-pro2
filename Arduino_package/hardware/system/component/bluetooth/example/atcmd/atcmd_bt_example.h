/*
 *******************************************************************************
 * Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __ATCMD_BT_EXAMPLE_H__
#define __ATCMD_BT_EXAMPLE_H__

#ifdef __cplusplus
extern "C"
{
#endif

int atcmd_bt_central(int argc, char* argv[]);

int atcmd_bt_peripheral(int argc, char* argv[]);

int atcmd_bt_scatternet(int argc, char* argv[]);

int atcmd_bt_a2dp_sink(int argc, char* argv[]);

int atcmd_ble_cis(int argc, char* argv[]);

#ifdef __cplusplus
}
#endif

#endif /* __ATCMD_BT_EXAMPLE_H__ */