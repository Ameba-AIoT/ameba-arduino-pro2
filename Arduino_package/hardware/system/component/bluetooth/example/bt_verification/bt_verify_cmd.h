/*
 *******************************************************************************
 * Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

typedef enum {
    BT_VERIFY_HELP = 0,
    BT_VERIFY_START_APP,
    BT_VERIFY_STOP_ADV,
    BT_VERIFY_SET_EXT_ADV_PARAM,
    BT_VERIFY_SET_EXT_ADV_ENABLE_PARAM,
    BT_VERIFY_START_EADV,
    BT_VERIFY_STOP_EADV,
    BT_VERIFY_REMOVE_EADV_SET,
    BT_VERIFY_CLEAR_EADV_SET,
    BT_VERIFY_START_ESCAN,
    BT_VERIFY_STOP_ESCAN,
    BT_VERIFY_SET_PHY,
    BT_VERIFY_CONN,
    BT_VERIFY_DISCONN,
    BT_VERIFY_DELETE_BOND,
    BT_VERIFY_CLEAR_BOND,
    BT_VERIFY_BOND_INFO,
    BT_VERIFY_ADD_WHITELIST,
} bt_verify_cmd_index_t;

typedef enum {
    BT_VERIFY_EXT_ADV_BIT = 0,
    BT_VERIFY_PRIVACY_BIT = 1,
} bt_verify_feature_bit_t;