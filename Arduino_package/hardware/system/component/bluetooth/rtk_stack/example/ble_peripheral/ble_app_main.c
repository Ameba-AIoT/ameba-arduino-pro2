/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      main.c
   * @brief     Source file for BLE peripheral project, mainly used for initialize modules
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
#if defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL
#if UPPER_STACK_VERSION == VERSION_2019
#include <bt_flags.h>
#elif UPPER_STACK_VERSION == VERSION_2021
#include "upperstack_config.h"
#endif
#include <os_sched.h>
#include <string.h>
#include <trace_app.h>
#include <gap.h>
#include <gap_adv.h>
#include <gap_bond_le.h>
#include <profile_server.h>
#include <gap_msg.h>
#include <simple_ble_service.h>
#include <bas.h>
#include <bte.h>
#include <gap_config.h>
#include "app_task.h"
#include "peripheral_app.h"
#include "app_flags.h"
#include "platform_stdlib.h"
#include "wifi_constants.h"
#include <wifi_conf.h>
#include "rtk_coex.h"
#include "gatt_builtin_services.h"
#include "vendor_cmd.h"
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
#include <gap_ext_adv.h>
#endif
/** @defgroup  PERIPH_DEMO_MAIN Peripheral Main
    * @brief Main file to initialize hardware and BT stack and start task scheduling
    * @{
    */

/*============================================================================*
 *                              Constants
 *============================================================================*/
/** @brief  Default minimum advertising interval when device is discoverable (units of 625us, 160=100ms) */
#define DEFAULT_ADVERTISING_INTERVAL_MIN            352 //220ms
/** @brief  Default maximum advertising interval */
#define DEFAULT_ADVERTISING_INTERVAL_MAX            384 //240ms


/*============================================================================*
 *                              Variables
 *============================================================================*/

/** @brief  GAP - scan response data (max size = 31 bytes) */
static const uint8_t scan_rsp_data[] = {
	0x03,                             /* length */
	GAP_ADTYPE_APPEARANCE,            /* type="Appearance" */
	LO_WORD(GAP_GATT_APPEARANCE_UNKNOWN),
	HI_WORD(GAP_GATT_APPEARANCE_UNKNOWN),
};

/** @brief  GAP - Advertisement data (max size = 31 bytes, best kept short to conserve power) */
static const uint8_t adv_data[] = {
	/* Flags */
	0x02,             /* length */
	GAP_ADTYPE_FLAGS, /* type="Flags" */
	GAP_ADTYPE_FLAGS_LIMITED | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED,
	/* Service */
	0x03,             /* length */
	GAP_ADTYPE_16BIT_COMPLETE,
	LO_WORD(GATT_UUID_SIMPLE_PROFILE),
	HI_WORD(GATT_UUID_SIMPLE_PROFILE),
	/* Local name */
	0x0F,             /* length */
	GAP_ADTYPE_LOCAL_NAME_COMPLETE,
	'B', 'L', 'E', '_', 'P', 'E', 'R', 'I', 'P', 'H', 'E', 'R', 'A', 'L',
};
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
extern ext_adv_info_t ext_adv_tbl[GAP_MAX_EXT_ADV_SETS];
static uint8_t ext_adv_data[] = {
	// Flags
	0x02,
	GAP_ADTYPE_FLAGS,
	GAP_ADTYPE_FLAGS_LIMITED | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED,
	// Local name
	0x12,
	GAP_ADTYPE_LOCAL_NAME_COMPLETE,
	'B', 'L', 'E', '_', 'E', 'X', 'T', '_', 'A', 'D', 'V', '_','T','E','S','T','1',
	// Manufacturer Specific Data
	0xc3,
	GAP_ADTYPE_MANUFACTURER_SPECIFIC,
	0xc0, 0x00,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1,
	0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2,
	0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3,
	0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4,
	0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5,
	0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6,
	0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
	0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8,
	0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9,
	0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa,
	0xb, 0xb, 0xb, 0xb, 0xb, 0xb, 0xb, 0xb, 0xb, 0xb, 0xb, 0xb, 0xb, 0xb, 0xb, 0xb,
};

static ext_adv_param_t ext_adv_param = {
	.adv_event_prop = LE_EXT_ADV_EXTENDED_ADV_CONN_UNDIRECTED,
	.primary_adv_interval_min = 32,
	.primary_adv_interval_max = 32,
	.primary_adv_channel_map = GAP_ADVCHAN_ALL,
	.own_addr_type = GAP_LOCAL_ADDR_LE_PUBLIC,
	.own_addr = {0},
	.peer_addr_type = GAP_REMOTE_ADDR_LE_PUBLIC,
	.peer_addr = {0},//;{0x8A, 0xAA, 0xAA, 0x4C, 0xE0, 0x00},
	.filter_policy = GAP_ADV_FILTER_ANY,
	.tx_power = -15,
	.primary_adv_phy = GAP_PHYS_PRIM_ADV_1M,
	.secondary_adv_max_skip = 0,
	.secondary_adv_phy = GAP_PHYS_2M,
	.adv_sid = 0,
};
#endif
#if ((LEGACY_ADV_CONCURRENT == 1) && (F_BT_LE_USE_RANDOM_ADDR == 1))
extern uint8_t local_static_random_addr[6];
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
void bt_stack_config_init(void)
{
	gap_config_max_le_link_num(APP_MAX_LINKS);
	gap_config_max_le_paired_device(APP_MAX_LINKS);
	//gap_config_hci_task_secure_context (280);
}

/**
  * @brief  Initialize peripheral and gap bond manager related parameters
  * @return void
  */
void app_le_gap_init(void)
{
	/* Device name and device appearance */
	uint8_t  device_name[GAP_DEVICE_NAME_LEN] = "BLE_PERIPHERAL";
	uint16_t appearance = GAP_GATT_APPEARANCE_UNKNOWN;
	uint8_t  slave_init_mtu_req = false;

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

	/* Set device name and device appearance */
	le_set_gap_param(GAP_PARAM_DEVICE_NAME, GAP_DEVICE_NAME_LEN, device_name);
	le_set_gap_param(GAP_PARAM_APPEARANCE, sizeof(appearance), &appearance);
	le_set_gap_param(GAP_PARAM_SLAVE_INIT_GATT_MTU_REQ, sizeof(slave_init_mtu_req),
					 &slave_init_mtu_req);
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
	uint8_t adv_handle = 0;
	ble_peripheral_init_ext_adv();
	ble_peripheral_create_ext_adv(&ext_adv_param, &adv_handle);
	ble_peripheral_set_ext_adv_data(adv_handle, sizeof(ext_adv_data), ext_adv_data);
	printf("Ext adv_handle %d\r\n", adv_handle);
#else
	/* Advertising parameters */
	uint8_t  adv_evt_type = GAP_ADTYPE_ADV_IND;
	uint8_t  adv_direct_type = GAP_REMOTE_ADDR_LE_PUBLIC;
	uint8_t  adv_direct_addr[GAP_BD_ADDR_LEN] = {0};
	uint8_t  adv_chann_map = GAP_ADVCHAN_ALL;
	uint8_t  adv_filter_policy = GAP_ADV_FILTER_ANY;
	uint16_t adv_int_min = DEFAULT_ADVERTISING_INTERVAL_MIN;
	uint16_t adv_int_max = DEFAULT_ADVERTISING_INTERVAL_MAX;

	/* Set advertising parameters */
	le_adv_set_param(GAP_PARAM_ADV_EVENT_TYPE, sizeof(adv_evt_type), &adv_evt_type);
	le_adv_set_param(GAP_PARAM_ADV_DIRECT_ADDR_TYPE, sizeof(adv_direct_type), &adv_direct_type);
	le_adv_set_param(GAP_PARAM_ADV_DIRECT_ADDR, sizeof(adv_direct_addr), adv_direct_addr);
	le_adv_set_param(GAP_PARAM_ADV_CHANNEL_MAP, sizeof(adv_chann_map), &adv_chann_map);
	le_adv_set_param(GAP_PARAM_ADV_FILTER_POLICY, sizeof(adv_filter_policy), &adv_filter_policy);
	le_adv_set_param(GAP_PARAM_ADV_INTERVAL_MIN, sizeof(adv_int_min), &adv_int_min);
	le_adv_set_param(GAP_PARAM_ADV_INTERVAL_MAX, sizeof(adv_int_max), &adv_int_max);
	le_adv_set_param(GAP_PARAM_ADV_DATA, sizeof(adv_data), (void *)adv_data);
	le_adv_set_param(GAP_PARAM_SCAN_RSP_DATA, sizeof(scan_rsp_data), (void *)scan_rsp_data);
#endif
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
	le_register_app_cb(app_gap_callback);

#if F_BT_GAPS_CHAR_WRITEABLE
	uint8_t appearance_prop = GAPS_PROPERTY_WRITE_ENABLE;
	uint8_t device_name_prop = GAPS_PROPERTY_WRITE_ENABLE;
	T_LOCAL_APPEARANCE appearance_local;
	T_LOCAL_NAME local_device_name;
	if (flash_load_local_appearance(&appearance_local) == 0) {
		gaps_set_parameter(GAPS_PARAM_APPEARANCE, sizeof(uint16_t), &appearance_local.local_appearance);
	}

	if (flash_load_local_name(&local_device_name) == 0) {
		gaps_set_parameter(GAPS_PARAM_DEVICE_NAME, GAP_DEVICE_NAME_LEN, local_device_name.local_name);
	}
	gaps_set_parameter(GAPS_PARAM_APPEARANCE_PROPERTY, sizeof(appearance_prop), &appearance_prop);
	gaps_set_parameter(GAPS_PARAM_DEVICE_NAME_PROPERTY, sizeof(device_name_prop), &device_name_prop);
	gatt_register_callback((void *)gap_service_callback);
#endif

#if (F_BT_LE_USE_RANDOM_ADDR == 1)
	T_APP_STATIC_RANDOM_ADDR random_addr;
	bool gen_addr = true;
	uint8_t local_bd_type = GAP_LOCAL_ADDR_LE_RANDOM;
	if (ble_peripheral_app_load_static_random_address(&random_addr) == 0)
	{
		if (random_addr.is_exist == true)
		{
			gen_addr = false;
		}
	}
	if (gen_addr)
	{
		if (le_gen_rand_addr(GAP_RAND_ADDR_STATIC, random_addr.bd_addr) == GAP_CAUSE_SUCCESS)
		{
			random_addr.is_exist = true;
			ble_peripheral_app_save_static_random_address(&random_addr);
		}
	}
	printf("random_addr.bd_addr = 0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x\r\n", \
		random_addr.bd_addr[5], random_addr.bd_addr[4], random_addr.bd_addr[3], random_addr.bd_addr[2], random_addr.bd_addr[1], random_addr.bd_addr[0]);
	le_set_gap_param(GAP_PARAM_RANDOM_ADDR, 6, random_addr.bd_addr);
#if (LEGACY_ADV_CONCURRENT == 1)
	memcpy(local_static_random_addr, random_addr.bd_addr, 6);
#else
	le_cfg_local_identity_address(random_addr.bd_addr, GAP_IDENT_ADDR_RAND);
	le_adv_set_param(GAP_PARAM_ADV_LOCAL_ADDR_TYPE, sizeof(local_bd_type), &local_bd_type);
#endif
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
#if APP_PRIVACY_EN
	privacy_init(app_privacy_callback, true);
#endif
	vendor_cmd_init(app_vendor_callback);
}

/**
 * @brief  Add GATT services and register callbacks
 * @return void
 */
void app_le_profile_init(void)
{
	server_init(2);

	simp_srv_id = simp_ble_service_add_service((void *)app_profile_callback);
	bas_srv_id  = bas_add_service((void *)app_profile_callback);
	server_register_app_cb(app_profile_callback);
}

/**
 * @brief    Contains the initialization of pinmux settings and pad settings
 * @note     All the pinmux settings and pad settings shall be initiated in this function,
 *           but if legacy driver is used, the initialization of pinmux setting and pad setting
 *           should be peformed with the IO initializing.
 * @return   void
 */
void board_init(void)
{

}

/**
 * @brief    Contains the initialization of peripherals
 * @note     Both new architecture driver and legacy driver initialization method can be used
 * @return   void
 */
void driver_init(void)
{

}

/**
 * @brief    Contains the power mode settings
 * @return   void
 */
void pwr_mgr_init(void)
{
}

/**
 * @brief    Contains the initialization of all tasks
 * @note     There is only one task in BLE Peripheral APP, thus only one APP task is init here
 * @return   void
 */
void task_init(void)
{
	app_task_init();
}

/**
 * @brief    Entry of APP code
 * @return   int (To avoid compile warning)
 */
int ble_app_main(void)
{
	bt_trace_init();
	bt_stack_config_init();
	bte_init();
	board_init();
	le_gap_init(APP_MAX_LINKS);
	app_le_gap_init();
	app_le_profile_init();
	pwr_mgr_init();
	task_init();

	return 0;
}

extern bool rtk_bt_pre_enable(void);
int ble_app_init(void)
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
		printf("[BLE Peripheral]BT Stack already on\r\n");
		return 0;
	} else {
		ble_app_main();
	}

	bt_coex_init();

	/*Wait BT init complete*/
	do {
		os_delay(100);
		le_get_gap_param(GAP_PARAM_DEV_STATE, &new_state);
	} while (new_state.gap_init_state != GAP_INIT_STATE_STACK_READY);

	return 0;
}

extern void app_task_deinit(void);
extern bool bt_trace_deinit(void);
extern T_GAP_DEV_STATE gap_dev_state;

void ble_app_deinit(void)
{
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
	memset((void *)ext_adv_tbl, 0, sizeof(ext_adv_info_t) * GAP_MAX_EXT_ADV_SETS);
#endif
	app_task_deinit();

	T_GAP_DEV_STATE state;
	le_get_gap_param(GAP_PARAM_DEV_STATE, &state);
	if (state.gap_init_state != GAP_INIT_STATE_STACK_READY) {
		printf("[BLE Peripheral]BT Stack is not running\r\n");
	}
#if F_BT_DEINIT
	else {
		bte_deinit();
		bt_trace_deinit();
		memset(&gap_dev_state, 0, sizeof(T_GAP_DEV_STATE));
		printf("[BLE Peripheral]BT Stack deinitalized\r\n");
	}
#endif
}

/** @} */ /* End of group PERIPH_DEMO_MAIN */
#endif
