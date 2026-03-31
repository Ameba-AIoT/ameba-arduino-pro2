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
#if defined(CONFIG_BT_BEACON) && CONFIG_BT_BEACON
#include "platform_stdlib.h"
#include <os_sched.h>
#include <string.h>
#include <trace_app.h>
#include <gap.h>
#include <gap_adv.h>
#include <gap_msg.h>
#include "bt_beacon_app_task.h"
#include "bt_beacon_app.h"
#include "trace_uart.h"
#include <bte.h>
#include <gap_config.h>
#include "wifi_constants.h"
#include "wifi_conf.h"
#include "rtk_coex.h"

/** @defgroup  BEACON_MAIN Beacon Main
    * @brief Main file to initialize hardware and BT stack and start task scheduling
    * @{
    */

/*============================================================================*
 *                              Constants
 *============================================================================*/
/** @brief  Default minimum advertising interval when device is discoverable (units of 625us, 160=100ms) */
#define DEFAULT_ADVERTISING_INTERVAL_MIN            160
/** @brief  Default maximum advertising interval */
#define DEFAULT_ADVERTISING_INTERVAL_MAX            240

int beacon_type = 0;

#define I_BEACON		1
#define ALT_BEACON		2


/*============================================================================*
 *                              Variables
 *============================================================================*/

/** @brief  GAP - scan response data (max size = 31 bytes) */
static const uint8_t i_beacon_scan_rsp_data[] = {
	/* Manufacturer Specific */
	0x1A,             /* length */
	GAP_ADTYPE_MANUFACTURER_SPECIFIC,
	0x4C, 0x00,       /* Company: Apple */
	0x02,             /* Type: iBeacon */
	0x15,             /* iBeacon data length 0x15 (21) = UUID (16) + major (2) + minor (2) + RSSI (1) */
	0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, /* UUID (example) */
	0x00, 0x7B,       /* major (example: 123)*/
	0x01, 0xC8,       /* minor (example: 456)*/
	0xBF,             /* rssi: (example: -65 dBm) */
};

/** @brief  GAP - Advertisement data (max size = 31 bytes, best kept short to conserve power) */
static const uint8_t i_beacon_adv_data[] = {
	/* Flags */
	0x02,             /* length */
	GAP_ADTYPE_FLAGS, /* type="Flags" */
	GAP_ADTYPE_FLAGS_GENERAL | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED,
	/* Manufacturer Specific */
	0x1A,             /* length */
	GAP_ADTYPE_MANUFACTURER_SPECIFIC,
	0x4C, 0x00,       /* Company: Apple */
	0x02,             /* Type: iBeacon */
	0x15,             /* iBeacon data length 0x15 (21) = UUID (16) + major (2) + minor (2) + RSSI (1) */
	0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, /* 16 byte UUID (example) */
	0x00, 0x7B,       /* major (example: 123)*/
	0x01, 0xC8,       /* minor (example: 456)*/
	0xBF,             /* rssi: (example: -65 dBm) */
};

static const uint8_t alt_beacon_scan_rsp_data[] = {
	/* Manufacturer Specific */
	0x1B,             /* length */
	GAP_ADTYPE_MANUFACTURER_SPECIFIC,
	0x5D, 0x00,       /* Company: (example: Realtek) */
	0xBE, 0xAC,       /* Beacon Code: AltBeacon */
	0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, /* Beacon ID (example) */
	0x00, 0x7B,       /* Beacon ID major (example: 123)*/
	0x01, 0xC8,       /* Beacon ID minor (example: 456)*/
	0xBF,             /* rssi: (example: -65 dBm) */
	0xAA,             /* MFG RSVD (example: 0xAA)*/
};

/** @brief  GAP - Advertisement data (max size = 31 bytes, best kept short to conserve power) */
static const uint8_t alt_beacon_adv_data[] = {
	/* Flags */
	0x02,             /* length */
	GAP_ADTYPE_FLAGS, /* type="Flags" */
	GAP_ADTYPE_FLAGS_GENERAL | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED,
	/* Manufacturer Specific */
	0x1B,             /* length */
	GAP_ADTYPE_MANUFACTURER_SPECIFIC,
	0x5D, 0x00,       /* Company: (example: Realtek) */
	0xBE, 0xAC,       /* Beacon Code: AltBeacon */
	0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, /* Beacon ID (example) */
	0x00, 0x7B,       /* Beacon ID major (example: 123)*/
	0x01, 0xC8,       /* Beacon ID minor (example: 456)*/
	0xBF,             /* rssi: (example: -65 dBm) */
	0xAA,             /* MFG RSVD (example: 0xAA)*/
};
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
static void bt_stack_config_init(void)
{
	gap_config_max_le_link_num(0);
	gap_config_max_le_paired_device(0);
	//gap_config_hci_task_secure_context (280);
}

/**
  * @brief  Initialize peripheral and gap bond manager related parameters
  * @return void
  */
static void app_le_gap_init(void)
{
	/* Advertising parameters */
	uint8_t  adv_evt_type = GAP_ADTYPE_ADV_NONCONN_IND;
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
	if (beacon_type == I_BEACON) {
		le_adv_set_param(GAP_PARAM_ADV_DATA, sizeof(i_beacon_adv_data), (void *)i_beacon_adv_data);
		le_adv_set_param(GAP_PARAM_SCAN_RSP_DATA, sizeof(i_beacon_scan_rsp_data), (void *)i_beacon_scan_rsp_data);
	} else if (beacon_type == ALT_BEACON) {
		le_adv_set_param(GAP_PARAM_ADV_DATA, sizeof(alt_beacon_adv_data), (void *)alt_beacon_adv_data);
		le_adv_set_param(GAP_PARAM_SCAN_RSP_DATA, sizeof(alt_beacon_scan_rsp_data), (void *)alt_beacon_scan_rsp_data);
	} else {
		printf("Error beacon type!\r\n");
	}
	/* register gap message callback */
	le_register_app_cb(bt_beacon_app_gap_callback);
}


/**
 * @brief    Contains the initialization of pinmux settings and pad settings
 * @note     All the pinmux settings and pad settings shall be initiated in this function,
 *           but if legacy driver is used, the initialization of pinmux setting and pad setting
 *           should be peformed with the IO initializing.
 * @return   void
 */
static void board_init(void)
{

}

/**
 * @brief    Contains the initialization of peripherals
 * @note     Both new architecture driver and legacy driver initialization method can be used
 * @return   void
 */
void bt_beacon_driver_init(void)
{

}

/**
 * @brief    Contains the power mode settings
 * @return   void
 */
static void pwr_mgr_init(void)
{
}

/**
 * @brief    Contains the initialization of all tasks
 * @note     There is only one task in BLE Peripheral APP, thus only one APP task is init here
 * @return   void
 */
static void task_init(void)
{
	bt_beacon_app_task_init();
}

/**
 * @brief    Entry of APP code
 * @return   int (To avoid compile warning)
 */
int bt_beacon_app_main(void)
{
	bt_trace_init();
	bt_stack_config_init();
	bte_init();
	board_init();
	le_gap_init(0);
	app_le_gap_init();
	pwr_mgr_init();
	task_init();
	printf("[BT Beacon] %s\r\n", (beacon_type == I_BEACON) ? "Apple iBeacon" : (beacon_type == ALT_BEACON) ? "AltBeacon" : "");
	return 0;
}

extern bool rtk_bt_pre_enable(void);
int bt_beacon_app_init(int type)
{
	//int bt_stack_already_on = 0;
	T_GAP_DEV_STATE new_state;
	if (rtk_bt_pre_enable() == false) {
		printf("%s fail!\r\n", __func__);
		return -1;
	}
	//judge BLE Beacon is already on
	le_get_gap_param(GAP_PARAM_DEV_STATE, &new_state);
	if (new_state.gap_init_state == GAP_INIT_STATE_STACK_READY) {
		//bt_stack_already_on = 1;
		printf("[BT Beacon]BT Stack already on\r\n");
		return 0;
	} else {
		beacon_type = type;
		bt_beacon_app_main();
	}

	bt_coex_init();

	/*Wait BT init complete*/
	do {
		os_delay(100);
		le_get_gap_param(GAP_PARAM_DEV_STATE, &new_state);
	} while (new_state.gap_init_state != GAP_INIT_STATE_STACK_READY);

	return 0;
}

extern void bt_beacon_app_task_deinit(void);
extern bool bt_trace_deinit(void);
extern T_GAP_DEV_STATE bt_beacon_gap_dev_state;

void bt_beacon_app_deinit(void)
{
	bt_beacon_app_task_deinit();

	T_GAP_DEV_STATE state;
	le_get_gap_param(GAP_PARAM_DEV_STATE, &state);
	if (state.gap_init_state != GAP_INIT_STATE_STACK_READY) {
		printf("BT Stack is not running\r\n");
	}
#if F_BT_DEINIT
	else {
		bte_deinit();
		bt_trace_deinit();
		memset(&bt_beacon_gap_dev_state, 0, sizeof(T_GAP_DEV_STATE));
		printf("BT Stack deinitalized\r\n");
	}
#endif
}

/** @} */ /* End of group BEACON_MAIN */
#endif

