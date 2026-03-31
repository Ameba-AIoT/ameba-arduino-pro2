/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      main.c
   * @brief     Source file for BLE central client project, mainly used for initialize modules
   * @author    jane
   * @date      2017-06-12
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */

/*============================================================================*
 *                              Header Files
 *============================================================================*/
#include <platform_opts_bt.h>
#if defined(CONFIG_BT_CENTRAL) && CONFIG_BT_CENTRAL
#include <os_sched.h>
#include <string.h>
#include <ble_central_app_task.h>
#include <trace_app.h>
#include <gap.h>
#include <gap_config.h>
#include <gap_bond_le.h>
#include <gap_scan.h>
#include <profile_client.h>
#include <gap_msg.h>
#include <ble_central_client_app.h>
#include <gcs_client.h>
#include <ble_central_link_mgr.h>
#include "trace_uart.h"
#include <bte.h>
#include "wifi_constants.h"
#include <wifi_conf.h>
#include "rtk_coex.h"
#include "platform_stdlib.h"
#include <gap_adv.h>
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
#include <gap_ext_scan.h>
#endif
extern bool bt_trace_deinit(void);

/** @defgroup  CENTRAL_CLIENT_DEMO_MAIN Central Client Main
    * @brief Main file to initialize hardware and BT stack and start task scheduling
    * @{
    */

/*============================================================================*
 *                              Constants
 *============================================================================*/
/** @brief Default scan interval (units of 0.625ms, 0x520=820ms) */
#define DEFAULT_SCAN_INTERVAL     0x520
/** @brief Default scan window (units of 0.625ms, 0x520=820ms) */
#define DEFAULT_SCAN_WINDOW       0x520

#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
static ext_scan_param_t ext_scan_param = {
	.own_addr_type 				= GAP_LOCAL_ADDR_LE_PUBLIC,
	.ext_scan_phys      		= {1, 1},
	.type               		= {GAP_SCAN_MODE_ACTIVE, GAP_SCAN_MODE_ACTIVE},
	.ext_scan_interval      	= {108, 108},
	.ext_scan_window			= {54, 54},
	.ext_scan_duration			= 0,
	.ext_scan_period			= 0,
	.ext_scan_filter_policy		= GAP_SCAN_FILTER_ANY,
	.ext_scan_filter_duplicate	= GAP_SCAN_FILTER_DUPLICATE_ENABLE,
};
#endif
/*============================================================================*
 *                              Functions
 *============================================================================*/
/**
 * @brief  Config bt stack related feature
 *
 * NOTE: This function shall be called before @ref bte_init is invoked.
 * @return void
 */
//extern void gap_config_hci_task_secure_context(uint32_t size);
void ble_central_bt_stack_config_init(void)
{
	gap_config_max_le_link_num(BLE_CENTRAL_APP_MAX_LINKS);
	gap_config_max_le_paired_device(BLE_CENTRAL_APP_MAX_LINKS);
	//gap_config_hci_task_secure_context (280);
}

/**
  * @brief  Initialize central and gap bond manager related parameters
  * @return void
  */
void ble_central_app_le_gap_init(void)
{
	/* Device name and device appearance */
	uint8_t  device_name[GAP_DEVICE_NAME_LEN] = "BLE_CENTRAL_CLIENT";
	uint16_t appearance = GAP_GATT_APPEARANCE_UNKNOWN;

	/* GAP Bond Manager parameters */
	uint8_t  auth_pair_mode = GAP_PAIRING_MODE_PAIRABLE;
	uint16_t auth_flags = GAP_AUTHEN_BIT_BONDING_FLAG;
	uint8_t  auth_io_cap = GAP_IO_CAP_NO_INPUT_NO_OUTPUT;
#if F_BT_LE_SMP_OOB_SUPPORT
	uint8_t  auth_oob = false;
#endif
	uint8_t  auth_use_fix_passkey = false;
	uint32_t auth_fix_passkey = 0;
	uint8_t  auth_sec_req_enable = false;
	uint16_t auth_sec_req_flags = GAP_AUTHEN_BIT_BONDING_FLAG;
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
	uint8_t use_ext_adv = true;
	/* Ext scan parameters */
	le_ext_scan_gap_msg_info_way(false);
	le_set_gap_param(GAP_PARAM_USE_EXTENDED_ADV, sizeof(use_ext_adv), &use_ext_adv);
	ble_central_set_ext_scan_param(&ext_scan_param);
#else
	/* Scan parameters */
	uint8_t  scan_mode = GAP_SCAN_MODE_ACTIVE;
	uint16_t scan_interval = DEFAULT_SCAN_INTERVAL;
	uint16_t scan_window = DEFAULT_SCAN_WINDOW;
	uint8_t  scan_filter_policy = GAP_SCAN_FILTER_ANY;
	uint8_t  scan_filter_duplicate = GAP_SCAN_FILTER_DUPLICATE_ENABLE;

	/* Set scan parameters */
	le_scan_set_param(GAP_PARAM_SCAN_MODE, sizeof(scan_mode), &scan_mode);
	le_scan_set_param(GAP_PARAM_SCAN_INTERVAL, sizeof(scan_interval), &scan_interval);
	le_scan_set_param(GAP_PARAM_SCAN_WINDOW, sizeof(scan_window), &scan_window);
	le_scan_set_param(GAP_PARAM_SCAN_FILTER_POLICY, sizeof(scan_filter_policy),
					  &scan_filter_policy);
	le_scan_set_param(GAP_PARAM_SCAN_FILTER_DUPLICATES, sizeof(scan_filter_duplicate),
					  &scan_filter_duplicate);
#endif

	/* Set device name and device appearance */
	le_set_gap_param(GAP_PARAM_DEVICE_NAME, GAP_DEVICE_NAME_LEN, device_name);
	le_set_gap_param(GAP_PARAM_APPEARANCE, sizeof(appearance), &appearance);

	/* Setup the GAP Bond Manager */
	gap_set_param(GAP_PARAM_BOND_PAIRING_MODE, sizeof(auth_pair_mode), &auth_pair_mode);
	gap_set_param(GAP_PARAM_BOND_AUTHEN_REQUIREMENTS_FLAGS, sizeof(auth_flags), &auth_flags);
	gap_set_param(GAP_PARAM_BOND_IO_CAPABILITIES, sizeof(auth_io_cap), &auth_io_cap);
#if F_BT_LE_SMP_OOB_SUPPORT
	gap_set_param(GAP_PARAM_BOND_OOB_ENABLED, sizeof(auth_oob), &auth_oob);
#endif
	le_bond_set_param(GAP_PARAM_BOND_FIXED_PASSKEY, sizeof(auth_fix_passkey), &auth_fix_passkey);
	le_bond_set_param(GAP_PARAM_BOND_FIXED_PASSKEY_ENABLE, sizeof(auth_use_fix_passkey),
					  &auth_use_fix_passkey);
	le_bond_set_param(GAP_PARAM_BOND_SEC_REQ_ENABLE, sizeof(auth_sec_req_enable), &auth_sec_req_enable);
	le_bond_set_param(GAP_PARAM_BOND_SEC_REQ_REQUIREMENT, sizeof(auth_sec_req_flags),
					  &auth_sec_req_flags);

	/* register gap message callback */
	le_register_app_cb(ble_central_app_gap_callback);
#if F_BT_LE_USE_STATIC_RANDOM_ADDR
	T_APP_STATIC_RANDOM_ADDR random_addr;
	bool gen_addr = true;
	uint8_t local_bd_type = GAP_LOCAL_ADDR_LE_RANDOM;
	if (ble_central_app_load_static_random_address(&random_addr) == 0) {
		if (random_addr.is_exist == true) {
			gen_addr = false;
		}
	}
	if (gen_addr) {
		if (le_gen_rand_addr(GAP_RAND_ADDR_STATIC, random_addr.bd_addr) == GAP_CAUSE_SUCCESS) {
			random_addr.is_exist = true;
			ble_central_app_save_static_random_address(&random_addr);
		}
	}
	le_cfg_local_identity_address(random_addr.bd_addr, GAP_IDENT_ADDR_RAND);
	le_set_gap_param(GAP_PARAM_RANDOM_ADDR, 6, random_addr.bd_addr);
	//only for peripheral,broadcaster
	//le_adv_set_param(GAP_PARAM_ADV_LOCAL_ADDR_TYPE, sizeof(local_bd_type), &local_bd_type);
	//only for central,observer
	le_scan_set_param(GAP_PARAM_SCAN_LOCAL_ADDR_TYPE, sizeof(local_bd_type), &local_bd_type);
#endif
#if F_BT_LE_5_0_SET_PHY_SUPPORT
	uint8_t phys_prefer = GAP_PHYS_PREFER_ALL;
#if defined(CONFIG_PLATFORM_8710C)
	uint8_t tx_phys_prefer = GAP_PHYS_PREFER_1M_BIT;
	uint8_t rx_phys_prefer = GAP_PHYS_PREFER_1M_BIT;
#elif defined(CONFIG_PLATFORM_8721D)
	uint8_t tx_phys_prefer = GAP_PHYS_PREFER_1M_BIT | GAP_PHYS_PREFER_2M_BIT;
	uint8_t rx_phys_prefer = GAP_PHYS_PREFER_1M_BIT | GAP_PHYS_PREFER_2M_BIT;
#elif defined(CONFIG_PLATFORM_AMEBAD2) || defined(CONFIG_PLATFORM_8735B)
	uint8_t tx_phys_prefer = GAP_PHYS_PREFER_1M_BIT | GAP_PHYS_PREFER_2M_BIT | GAP_PHYS_PREFER_CODED_BIT;
	uint8_t rx_phys_prefer = GAP_PHYS_PREFER_1M_BIT | GAP_PHYS_PREFER_2M_BIT | GAP_PHYS_PREFER_CODED_BIT;
#endif
	le_set_gap_param(GAP_PARAM_DEFAULT_PHYS_PREFER, sizeof(phys_prefer), &phys_prefer);
	le_set_gap_param(GAP_PARAM_DEFAULT_TX_PHYS_PREFER, sizeof(tx_phys_prefer), &tx_phys_prefer);
	le_set_gap_param(GAP_PARAM_DEFAULT_RX_PHYS_PREFER, sizeof(rx_phys_prefer), &rx_phys_prefer);
#endif
}

/**
 * @brief  Add GATT clients and register callbacks
 * @return void
 */
void ble_central_app_le_profile_init(void)
{
	client_init(1);
	ble_central_gcs_client_id = gcs_add_client(ble_central_gcs_client_callback, BLE_CENTRAL_APP_MAX_LINKS, BLE_CENTRAL_APP_MAX_DISCOV_TABLE_NUM);
}


/**
 * @brief    Contains the initialization of all tasks
 * @note     There is only one task in BLE Central Client APP, thus only one APP task is init here
 * @return   void
 */
void ble_central_task_init(void)
{
	ble_central_app_task_init();
}

/**
 * @brief    Entry of APP code
 * @return   int (To avoid compile warning)
 */
int ble_central_app_main(void)
{
	bt_trace_init();
	ble_central_bt_stack_config_init();
	bte_init();
	le_gap_init(BLE_CENTRAL_APP_MAX_LINKS);
	ble_central_app_le_gap_init();
	ble_central_app_le_profile_init();
	ble_central_task_init();

	return 0;
}

extern bool rtk_bt_pre_enable(void);
int ble_central_app_init(void)
{
	//int bt_stack_already_on = 0;
	//(void) bt_stack_already_on;
	T_GAP_DEV_STATE new_state;

	if (rtk_bt_pre_enable() == false) {
		printf("%s fail!\r\n", __func__);
		return -1;
	}
	//judge BLE central is already on
	le_get_gap_param(GAP_PARAM_DEV_STATE, &new_state);
	if (new_state.gap_init_state == GAP_INIT_STATE_STACK_READY) {
		//bt_stack_already_on = 1;
		printf("[BLE Central]BT Stack already on\r\n");
		return 0;
	} else {
		ble_central_app_main();
	}

	bt_coex_init();

	/*Wait BT init complete*/
	do {
		os_delay(100);
		le_get_gap_param(GAP_PARAM_DEV_STATE, &new_state);
	} while (new_state.gap_init_state != GAP_INIT_STATE_STACK_READY);

	return 0;

}

extern void gcs_delete_client(void);
void ble_central_app_deinit(void)
{
	ble_central_app_task_deinit();
	T_GAP_DEV_STATE state;
	le_get_gap_param(GAP_PARAM_DEV_STATE, &state);
	if (state.gap_init_state != GAP_INIT_STATE_STACK_READY) {
		printf("[BLE Central]BT Stack is not running\r\n");
	}
#if F_BT_DEINIT
	else {
		gcs_delete_client();
		bte_deinit();
		bt_trace_deinit();
		printf("[BLE Central]BT Stack deinitalized\r\n");
	}
#endif
}
#endif
/** @} */ /* End of group CENTRAL_CLIENT_DEMO_MAIN */
