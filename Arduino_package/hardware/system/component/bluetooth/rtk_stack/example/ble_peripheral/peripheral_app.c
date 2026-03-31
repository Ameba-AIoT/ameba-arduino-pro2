/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      peripheral_app.c
   * @brief     This file handles BLE peripheral application routines.
   * @author    jane
   * @date      2017-06-06
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
#include "platform_stdlib.h"
#include <trace_app.h>
#include <string.h>
#include <gap.h>
#include <gap_adv.h>
#include <gap_bond_le.h>
#include <profile_server.h>
#include <gap_msg.h>
#include <simple_ble_service.h>
#include <bas.h>
#include <app_msg.h>
#include "peripheral_app.h"
#include <gap_conn_le.h>
#include "platform_stdlib.h"
#include "ble_peripheral_at_cmd.h"
#include "gatt_builtin_services.h"
#include "os_msg.h"
#include "os_sync.h"
#include "os_task.h"
#include "os_timer.h"
#include "os_sched.h"
#include "vendor_cmd.h"
#if UPPER_STACK_VERSION == VERSION_2021
#include "gap_vendor.h"
#endif
#if (F_BT_LE_USE_RANDOM_ADDR == 1)
#include "ftl_app.h"
#endif
#if APP_PRIVACY_EN
#include <privacy_mgnt.h>
#endif
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
#include <gap_ext_adv.h>
#endif
/*============================================================================*
 *                              Constants
 *============================================================================*/
#if (F_BT_LE_USE_RANDOM_ADDR == 1)
/** @brief  Define start offset of the flash to save static random address. */
#define BLE_PERIPHERAL_APP_STATIC_RANDOM_ADDR_OFFSET 0
#endif

/** @defgroup  PERIPH_APP Peripheral Application
    * @brief This file handles BLE peripheral application routines.
    * @{
    */
/*============================================================================*
 *                              Variables
 *============================================================================*/
/** @addtogroup  PERIPH_SEVER_CALLBACK Profile Server Callback Event Handler
    * @brief Handle profile server callback event
    * @{
    */
T_SERVER_ID simp_srv_id; /**< Simple ble service id*/
T_SERVER_ID bas_srv_id;  /**< Battery service id */
/** @} */ /* End of group PERIPH_SEVER_CALLBACK */
/** @defgroup  PERIPH_GAP_MSG GAP Message Handler
    * @brief Handle GAP Message
    * @{
    */
T_GAP_DEV_STATE gap_dev_state = {0, 0, 0, 0, 0};                 /**< GAP device state */
T_GAP_CONN_STATE gap_conn_state = GAP_CONN_STATE_DISCONNECTED; /**< GAP connection state */
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
uint8_t random_update_flag = 0;
#endif
#if APP_PRIVACY_EN
T_PRIVACY_STATE app_privacy_state = PRIVACY_STATE_INIT;
T_PRIVACY_ADDR_RESOLUTION_STATE app_privacy_resolution_state = PRIVACY_ADDR_RESOLUTION_DISABLED;
T_APP_WORK_MODE app_work_mode = APP_PAIRABLE_MODE;
#endif

#if (LEGACY_ADV_CONCURRENT == 1)
extern void *evt_queue_handle;
extern void *io_queue_handle;

typedef struct
{
	void *task_handle;
	void *sem_handle;
	void *queue_handle;
	void *timer0_handle;
	void *timer1_handle;
	bool start_stop_flag;
	bool send_adv_flag;
	bool deinit_flag;
} T_LEGACY_ADV_CONCURRENT;

typedef struct
{
	uint16_t adv_interval;
	uint8_t local_bd_type;
	uint8_t adv_data[31];
	uint8_t adv_data_size;
	uint8_t scan_rsp_data[31];
	uint8_t scan_rsp_data_size;
} T_LEGACY_ADV_INFO;

T_LEGACY_ADV_CONCURRENT lac_adapter;
T_LEGACY_ADV_INFO adv_info_0;
T_LEGACY_ADV_INFO adv_info_1;

#if (F_BT_LE_USE_RANDOM_ADDR == 1)
uint8_t local_public_addr[6] = {0};
uint8_t local_static_random_addr[6] = {0};
#endif

uint8_t adv_data_0[31] =
{
	0x02,
	GAP_ADTYPE_FLAGS,
	GAP_ADTYPE_FLAGS_LIMITED | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED,
	0x03,
	GAP_ADTYPE_16BIT_COMPLETE,
	LO_WORD(0x1234),
	HI_WORD(0x1234),
	0x17,
	GAP_ADTYPE_LOCAL_NAME_COMPLETE,
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15
};

uint8_t scan_rsp_data_0[31] =
{
	0x1E,
	GAP_ADTYPE_MANUFACTURER_SPECIFIC,
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C
};

uint8_t adv_data_1[31] =
{
	0x02,
	GAP_ADTYPE_FLAGS,
	GAP_ADTYPE_FLAGS_LIMITED | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED,
	0x03,
	GAP_ADTYPE_16BIT_COMPLETE,
	LO_WORD(0x5678),
	HI_WORD(0x5678),
	0x17,
	GAP_ADTYPE_LOCAL_NAME_COMPLETE,
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55
};

uint8_t scan_rsp_data_1[31] =
{
	0x1E,
	GAP_ADTYPE_MANUFACTURER_SPECIFIC,
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C
};
#endif

/*============================================================================*
 *                              Functions
 *============================================================================*/
void app_handle_gap_msg(T_IO_MSG  *p_gap_msg);
/**
 * @brief    All the application messages are pre-handled in this function
 * @note     All the IO MSGs are sent to this function, then the event handling
 *           function shall be called according to the MSG type.
 * @param[in] io_msg  IO message data
 * @return   void
 */
void app_handle_io_msg(T_IO_MSG io_msg)
{
	uint16_t msg_type = io_msg.type;

	switch (msg_type) {
	case IO_MSG_TYPE_BT_STATUS: {
		app_handle_gap_msg(&io_msg);
	}
	break;
	case IO_MSG_TYPE_AT_CMD: {
		uint16_t subtype = io_msg.subtype;
		void *arg = io_msg.u.buf;
		ble_peripheral_app_handle_at_cmd(subtype, arg);
	}
	break;
	case IO_MSG_TYPE_QDECODE: {
		if (io_msg.subtype == 0) {
			le_adv_stop();
		} else if (io_msg.subtype == 1) {
			le_adv_start();
#if (LEGACY_ADV_CONCURRENT == 1)
		} else if (io_msg.subtype == 2) {
			if (lac_adapter.start_stop_flag == true)
				break;
			T_GAP_CAUSE ret = GAP_CAUSE_SUCCESS;
			ret = le_adv_update_param();
			if (ret != GAP_CAUSE_SUCCESS) {
				printf("le_adv_update_param fail! ret = 0x%x\r\n", ret);
			}
#endif
		}
	}
	break;
	default:
		break;
	}
}

#if APP_PRIVACY_EN
/**
  * @brief Application changes to pairable mode.
  * @retval void
  */
void app_change_to_pair_mode(void){
	APP_PRINT_INFO0("app_change_to_pair_mode");
	printf("app change to pair mode\r\n");
	if (app_work_mode == APP_RECONNECTION_MODE){
	    if (gap_dev_state.gap_adv_state == GAP_ADV_STATE_ADVERTISING){
	        le_adv_stop();
	    }
	}
	app_work_mode = APP_PAIRABLE_MODE;
}

/**
 * @brief    Start advertising
 *
 * @return   void
 */
void app_adv_start(void)
{
    uint8_t  adv_evt_type = GAP_ADTYPE_ADV_IND;
    uint8_t  adv_filter_policy = GAP_ADV_FILTER_ANY;
    T_LE_KEY_ENTRY *p_entry;
    p_entry = le_get_high_priority_bond();

    if (p_entry == NULL)
    {
        /* No bonded device, send connectable undirected advertisement without using whitelist*/
        app_work_mode = APP_PAIRABLE_MODE;
        adv_filter_policy = GAP_ADV_FILTER_ANY;
        if (app_privacy_resolution_state == PRIVACY_ADDR_RESOLUTION_ENABLED)
        {
            privacy_set_addr_resolution(false);
        }
    }
    else
    {
        app_work_mode = APP_RECONNECTION_MODE;
        adv_filter_policy = GAP_ADV_FILTER_WHITE_LIST_ALL;
        if (app_privacy_resolution_state == PRIVACY_ADDR_RESOLUTION_DISABLED)
        {
            privacy_set_addr_resolution(true);
        }
    }
    le_adv_set_param(GAP_PARAM_ADV_EVENT_TYPE, sizeof(adv_evt_type), &adv_evt_type);
    le_adv_set_param(GAP_PARAM_ADV_FILTER_POLICY, sizeof(adv_filter_policy), &adv_filter_policy);
    le_adv_start();
}

/**
  * @brief Callback for BLE privacy management module to notify app
  * @param[in] type     callback msy type @ref T_PRIVACY_CB_TYPE.
  * @param[in] cb_data  callback data.
  * @retval void
  */
void app_privacy_callback(T_PRIVACY_CB_TYPE type, T_PRIVACY_CB_DATA cb_data)
{
    APP_PRINT_INFO1("app_privacy_callback: type %d", type);
    switch (type)
    {
    case PRIVACY_STATE_MSGTYPE:
        app_privacy_state = cb_data.privacy_state;
        APP_PRINT_INFO1("PRIVACY_STATE_MSGTYPE: status %d", app_privacy_state);
        break;

    case PRIVACY_RESOLUTION_STATUS_MSGTYPE:
        app_privacy_resolution_state = cb_data.resolution_state;
        APP_PRINT_INFO1("PRIVACY_RESOLUTION_STATUS_MSGTYPE: status %d", app_privacy_resolution_state);
        break;

    default:
        break;
    }
}
#endif

/**
 * @brief    Handle msg GAP_MSG_LE_DEV_STATE_CHANGE
 * @note     All the gap device state events are pre-handled in this function.
 *           Then the event handling function shall be called according to the new_state
 * @param[in] new_state  New gap device state
 * @param[in] cause GAP device state change cause
 * @return   void
 */
void app_handle_dev_state_evt(T_GAP_DEV_STATE new_state, uint16_t cause)
{
	APP_PRINT_INFO3("app_handle_dev_state_evt: init state %d, adv state %d, cause 0x%x",
					new_state.gap_init_state, new_state.gap_adv_state, cause);
#if APP_PRIVACY_EN
	if ((new_state.gap_init_state == GAP_INIT_STATE_STACK_READY)
		&& (new_state.gap_adv_state == GAP_ADV_STATE_IDLE)
		&& (new_state.gap_conn_state == GAP_CONN_DEV_STATE_IDLE))
	{
		privacy_handle_resolv_list();
	}
#endif

	if (gap_dev_state.gap_init_state != new_state.gap_init_state) {
		if (new_state.gap_init_state == GAP_INIT_STATE_STACK_READY) {
			uint8_t bt_addr[6];
			APP_PRINT_INFO0("GAP stack ready");
			printf("[BLE peripheral] GAP stack ready\r\n");
			/*stack ready*/
			gap_get_param(GAP_PARAM_BD_ADDR, bt_addr);
			printf("local bd addr: 0x%02x:%02x:%02x:%02x:%02x:%02x\r\n", \
					bt_addr[5], bt_addr[4], bt_addr[3], bt_addr[2], bt_addr[1], bt_addr[0]);
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
			ext_adv_start_t adv_start_param;
			adv_start_param.adv_handle = 0;
			adv_start_param.duration = 0;
			adv_start_param.num_events = 0;
			ble_peripheral_start_ext_adv(&adv_start_param);
#else
#if APP_PRIVACY_EN
			app_adv_start();
#else
#if (LEGACY_ADV_CONCURRENT == 1)	//Do not auto start ADV, need legacy_adv_concurrent_init for configuration
#if (F_BT_LE_USE_RANDOM_ADDR == 1)
			memcpy(local_public_addr, bt_addr, 6);
#endif
#else
			le_adv_start();
#endif
#endif
#endif
		}
	}

	if (gap_dev_state.gap_adv_state != new_state.gap_adv_state) {
		if (new_state.gap_adv_state == GAP_ADV_STATE_IDLE) {
			if (new_state.gap_adv_sub_state == GAP_ADV_TO_IDLE_CAUSE_CONN) {
				APP_PRINT_INFO0("GAP adv stoped: because connection created");
				printf("GAP adv stoped: because connection created\r\n");
			} else {
				APP_PRINT_INFO0("GAP adv stoped");
				printf("GAP adv stopped\r\n");
			}
		} else if (new_state.gap_adv_state == GAP_ADV_STATE_ADVERTISING) {
			APP_PRINT_INFO0("GAP adv start");
			printf("GAP adv start\r\n");
		}
	}

	gap_dev_state = new_state;
}

#if (LEGACY_ADV_CONCURRENT == 1)
void legacy_adv_concurrent_start();
void legacy_adv_concurrent_stop();
#endif
/**
 * @brief    Handle msg GAP_MSG_LE_CONN_STATE_CHANGE
 * @note     All the gap conn state events are pre-handled in this function.
 *           Then the event handling function shall be called according to the new_state
 * @param[in] conn_id Connection ID
 * @param[in] new_state  New gap connection state
 * @param[in] disc_cause Use this cause when new_state is GAP_CONN_STATE_DISCONNECTED
 * @return   void
 */
void app_handle_conn_state_evt(uint8_t conn_id, T_GAP_CONN_STATE new_state, uint16_t disc_cause)
{
	APP_PRINT_INFO4("app_handle_conn_state_evt: conn_id %d old_state %d new_state %d, disc_cause 0x%x",
					conn_id, gap_conn_state, new_state, disc_cause);
	switch (new_state) {
	case GAP_CONN_STATE_DISCONNECTED: {
		if ((disc_cause != (HCI_ERR | HCI_ERR_REMOTE_USER_TERMINATE))
			&& (disc_cause != (HCI_ERR | HCI_ERR_LOCAL_HOST_TERMINATE))) {
			APP_PRINT_ERROR1("app_handle_conn_state_evt: connection lost cause 0x%x", disc_cause);
		}
		printf("[BLE peripheral] BT Disconnected, cause 0x%x, start ADV\r\n", disc_cause);
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
		//uint8_t adv_handle = 0;
		//le_ext_adv_enable(1, &adv_handle);
#else
#if APP_PRIVACY_EN
		app_adv_start();
#else
#if (LEGACY_ADV_CONCURRENT == 1)
		legacy_adv_concurrent_start();
#else
		le_adv_start();
#endif
#endif
#endif
	}
	break;

	case GAP_CONN_STATE_CONNECTED: {
		uint16_t conn_interval;
		uint16_t conn_latency;
		uint16_t conn_supervision_timeout;
		uint8_t  remote_bd[6];
		T_GAP_REMOTE_ADDR_TYPE remote_bd_type;

		le_get_conn_param(GAP_PARAM_CONN_INTERVAL, &conn_interval, conn_id);
		le_get_conn_param(GAP_PARAM_CONN_LATENCY, &conn_latency, conn_id);
		le_get_conn_param(GAP_PARAM_CONN_TIMEOUT, &conn_supervision_timeout, conn_id);
		le_get_conn_addr(conn_id, remote_bd, (void *)&remote_bd_type);
		APP_PRINT_INFO5("GAP_CONN_STATE_CONNECTED:remote_bd %s, remote_addr_type %d, conn_interval 0x%x, conn_latency 0x%x, conn_supervision_timeout 0x%x",
						TRACE_BDADDR(remote_bd), remote_bd_type,
						conn_interval, conn_latency, conn_supervision_timeout);
		printf("[BLE peripheral] BT Connected\r\n");
#if (LEGACY_ADV_CONCURRENT == 1)
		legacy_adv_concurrent_stop();
#else
		//Do nothing, stack auto stop ADV
#endif
	}
	break;

	default:
		break;
	}
	gap_conn_state = new_state;
}

/**
 * @brief    Handle msg GAP_MSG_LE_AUTHEN_STATE_CHANGE
 * @note     All the gap authentication state events are pre-handled in this function.
 *           Then the event handling function shall be called according to the new_state
 * @param[in] conn_id Connection ID
 * @param[in] new_state  New authentication state
 * @param[in] cause Use this cause when new_state is GAP_AUTHEN_STATE_COMPLETE
 * @return   void
 */
void app_handle_authen_state_evt(uint8_t conn_id, uint8_t new_state, uint16_t cause)
{
	APP_PRINT_INFO2("app_handle_authen_state_evt:conn_id %d, cause 0x%x", conn_id, cause);

	switch (new_state) {
	case GAP_AUTHEN_STATE_STARTED: {
		APP_PRINT_INFO0("app_handle_authen_state_evt: GAP_AUTHEN_STATE_STARTED");
	}
	break;

	case GAP_AUTHEN_STATE_COMPLETE: {
		if (cause == GAP_SUCCESS) {
			printf("Pair success\r\n");
			APP_PRINT_INFO0("app_handle_authen_state_evt: GAP_AUTHEN_STATE_COMPLETE pair success");

		} else {
			printf("Pair failed: cause 0x%x\r\n", cause);
			APP_PRINT_INFO0("app_handle_authen_state_evt: GAP_AUTHEN_STATE_COMPLETE pair failed");
		}
	}
	break;

	default: {
		APP_PRINT_ERROR1("app_handle_authen_state_evt: unknown newstate %d", new_state);
	}
	break;
	}
}

/**
 * @brief    Handle msg GAP_MSG_LE_CONN_MTU_INFO
 * @note     This msg is used to inform APP that exchange mtu procedure is completed.
 * @param[in] conn_id Connection ID
 * @param[in] mtu_size  New mtu size
 * @return   void
 */
void app_handle_conn_mtu_info_evt(uint8_t conn_id, uint16_t mtu_size)
{
	APP_PRINT_INFO2("app_handle_conn_mtu_info_evt: conn_id %d, mtu_size %d", conn_id, mtu_size);
}

/**
 * @brief    Handle msg GAP_MSG_LE_CONN_PARAM_UPDATE
 * @note     All the connection parameter update change  events are pre-handled in this function.
 * @param[in] conn_id Connection ID
 * @param[in] status  New update state
 * @param[in] cause Use this cause when status is GAP_CONN_PARAM_UPDATE_STATUS_FAIL
 * @return   void
 */
void app_handle_conn_param_update_evt(uint8_t conn_id, uint8_t status, uint16_t cause)
{
	switch (status) {
	case GAP_CONN_PARAM_UPDATE_STATUS_SUCCESS: {
		uint16_t conn_interval;
		uint16_t conn_slave_latency;
		uint16_t conn_supervision_timeout;

		le_get_conn_param(GAP_PARAM_CONN_INTERVAL, &conn_interval, conn_id);
		le_get_conn_param(GAP_PARAM_CONN_LATENCY, &conn_slave_latency, conn_id);
		le_get_conn_param(GAP_PARAM_CONN_TIMEOUT, &conn_supervision_timeout, conn_id);
		APP_PRINT_INFO3("app_handle_conn_param_update_evt update success:conn_interval 0x%x, conn_slave_latency 0x%x, conn_supervision_timeout 0x%x",
						conn_interval, conn_slave_latency, conn_supervision_timeout);
		printf("app_handle_conn_param_update_evt update success:conn_interval 0x%x, conn_slave_latency 0x%x, conn_supervision_timeout 0x%x\r\n",
			   conn_interval, conn_slave_latency, conn_supervision_timeout);
	}
	break;

	case GAP_CONN_PARAM_UPDATE_STATUS_FAIL: {
		APP_PRINT_ERROR1("app_handle_conn_param_update_evt update failed: cause 0x%x", cause);
		printf("app_handle_conn_param_update_evt update failed: cause 0x%x", cause);
	}
	break;

	case GAP_CONN_PARAM_UPDATE_STATUS_PENDING: {
		APP_PRINT_INFO0("app_handle_conn_param_update_evt update pending.");
		printf("ble_central_app_handle_conn_param_update_evt update pending: conn_id %d\r\n", conn_id);
	}
	break;

	default:
		break;
	}
}
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
ext_adv_info_t ext_adv_tbl[GAP_MAX_EXT_ADV_SETS] = {0};
bool ble_peripheral_app_gap_ext_adv_handle_valid(uint8_t handle)
{
	int idx;

	for (idx = 0; idx < GAP_MAX_EXT_ADV_SETS; idx++) {
		if (ext_adv_tbl[idx].used &&
			ext_adv_tbl[idx].adv_handle == handle) {
			return true;
		}
	}

	return false;
}
void ble_peripheral_app_handle_ext_adv_state_evt(uint8_t adv_handle, T_GAP_EXT_ADV_STATE new_state, uint16_t cause)
{
	uint8_t idx = 0;
	T_GAP_EXT_ADV_STATE pre_state;

	for (idx = 0; idx < GAP_MAX_EXT_ADV_SETS; idx++) {
		if (ext_adv_tbl[idx].used &&
			ext_adv_tbl[idx].adv_handle == adv_handle) {
			pre_state = ext_adv_tbl[idx].ext_adv_state;
			ext_adv_tbl[idx].ext_adv_state = new_state;
			break;
		}
	}

	if (idx == GAP_MAX_EXT_ADV_SETS) {
		return;
	}

	APP_PRINT_INFO4("ble_peripheral_app_handle_ext_adv_state_evt: adv_handle 0x%x newState %d oldState %d cause 0x%x\r\n",
					adv_handle, new_state, pre_state, cause);

	if (EXT_ADV_STATE_IDLE == new_state) {
		if (EXT_ADV_STATE_START == pre_state) {
			printf("[ext_adv_state_evt]: Ext ADV[%d] started failed, cause: 0x%04x\r\n", adv_handle, cause);
		} else {
			if (cause == (HCI_ERR | HCI_ERR_OPERATION_CANCELLED_BY_HOST)) {
				printf("[ext_adv_state_evt]:Ext ADV[%d] stop by Host\r\n", adv_handle);
			} else if (cause == (HCI_ERR | HCI_ERR_DIRECTED_ADV_TIMEOUT) ||
					   cause == (HCI_ERR | HCI_ERR_LIMIT_REACHED)) {
				printf("[ext_adv_state_evt]:Ext ADV[%d] stop by duration\r\n", adv_handle);
			} else if (cause == 0) {
				printf("[ext_adv_state_evt]:Ext ADV[%d] stop by connection\r\n", adv_handle);
			}
		}

	} else {
		if (EXT_ADV_STATE_START == pre_state) {
			printf("[ext_adv_state_evt]: Ext ADV[%d] start success\r\n", adv_handle);
		} else if (EXT_ADV_STATE_STOP == pre_state) {
			printf("[ext_adv_state_evt]: Ext ADV[%d] stopped failed, cause: 0x%04x\r\n", adv_handle, cause);
		}
	}
}
#endif
/**
 * @brief    All the BT GAP MSG are pre-handled in this function.
 * @note     Then the event handling function shall be called according to the
 *           subtype of T_IO_MSG
 * @param[in] p_gap_msg Pointer to GAP msg
 * @return   void
 */
void app_handle_gap_msg(T_IO_MSG *p_gap_msg)
{
	T_LE_GAP_MSG gap_msg;
	uint8_t conn_id;
	memcpy(&gap_msg, &p_gap_msg->u.param, sizeof(p_gap_msg->u.param));

	APP_PRINT_TRACE1("app_handle_gap_msg: subtype %d", p_gap_msg->subtype);
	switch (p_gap_msg->subtype) {
	case GAP_MSG_LE_DEV_STATE_CHANGE: {
		app_handle_dev_state_evt(gap_msg.msg_data.gap_dev_state_change.new_state,
								 gap_msg.msg_data.gap_dev_state_change.cause);
	}
	break;

	case GAP_MSG_LE_CONN_STATE_CHANGE: {
		app_handle_conn_state_evt(gap_msg.msg_data.gap_conn_state_change.conn_id,
								  (T_GAP_CONN_STATE)gap_msg.msg_data.gap_conn_state_change.new_state,
								  gap_msg.msg_data.gap_conn_state_change.disc_cause);
	}
	break;

	case GAP_MSG_LE_CONN_MTU_INFO: {
		app_handle_conn_mtu_info_evt(gap_msg.msg_data.gap_conn_mtu_info.conn_id,
									 gap_msg.msg_data.gap_conn_mtu_info.mtu_size);
	}
	break;

	case GAP_MSG_LE_CONN_PARAM_UPDATE: {
		app_handle_conn_param_update_evt(gap_msg.msg_data.gap_conn_param_update.conn_id,
										 gap_msg.msg_data.gap_conn_param_update.status,
										 gap_msg.msg_data.gap_conn_param_update.cause);
	}
	break;

	case GAP_MSG_LE_AUTHEN_STATE_CHANGE: {
		app_handle_authen_state_evt(gap_msg.msg_data.gap_authen_state.conn_id,
									gap_msg.msg_data.gap_authen_state.new_state,
									gap_msg.msg_data.gap_authen_state.status);
	}
	break;

	case GAP_MSG_LE_BOND_JUST_WORK: {
		conn_id = gap_msg.msg_data.gap_bond_just_work_conf.conn_id;
		le_bond_just_work_confirm(conn_id, GAP_CFM_CAUSE_ACCEPT);
		APP_PRINT_INFO0("GAP_MSG_LE_BOND_JUST_WORK");
	}
	break;

	case GAP_MSG_LE_BOND_PASSKEY_DISPLAY: {
		uint32_t display_value = 0;
		conn_id = gap_msg.msg_data.gap_bond_passkey_display.conn_id;
		le_bond_get_display_key(conn_id, &display_value);
		APP_PRINT_INFO1("GAP_MSG_LE_BOND_PASSKEY_DISPLAY:passkey %d", display_value);
		le_bond_passkey_display_confirm(conn_id, GAP_CFM_CAUSE_ACCEPT);
		printf("GAP_MSG_LE_BOND_PASSKEY_DISPLAY:passkey %06d\r\n", display_value);
	}
	break;

	case GAP_MSG_LE_BOND_USER_CONFIRMATION: {
		uint32_t display_value = 0;
		conn_id = gap_msg.msg_data.gap_bond_user_conf.conn_id;
		le_bond_get_display_key(conn_id, &display_value);
		APP_PRINT_INFO1("GAP_MSG_LE_BOND_USER_CONFIRMATION: passkey %d", display_value);
		printf("GAP_MSG_LE_BOND_USER_CONFIRMATION: passkey %06d\r\n", display_value);
		//le_bond_user_confirm(conn_id, GAP_CFM_CAUSE_ACCEPT);
	}
	break;

	case GAP_MSG_LE_BOND_PASSKEY_INPUT: {
		//uint32_t passkey = 888888;
		conn_id = gap_msg.msg_data.gap_bond_passkey_input.conn_id;
		APP_PRINT_INFO1("GAP_MSG_LE_BOND_PASSKEY_INPUT: conn_id %d", conn_id);
		//le_bond_passkey_input_confirm(conn_id, passkey, GAP_CFM_CAUSE_ACCEPT);
		printf("GAP_MSG_LE_BOND_PASSKEY_INPUT: conn_id %d\r\n", conn_id);
	}
	break;
#if F_BT_LE_SMP_OOB_SUPPORT
	case GAP_MSG_LE_BOND_OOB_INPUT: {
		uint8_t oob_data[GAP_OOB_LEN] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		conn_id = gap_msg.msg_data.gap_bond_oob_input.conn_id;
		APP_PRINT_INFO0("GAP_MSG_LE_BOND_OOB_INPUT");
		le_bond_set_param(GAP_PARAM_BOND_OOB_DATA, GAP_OOB_LEN, oob_data);
		le_bond_oob_input_confirm(conn_id, GAP_CFM_CAUSE_ACCEPT);
	}
	break;
#endif
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
	case GAP_MSG_LE_EXT_ADV_STATE_CHANGE:{
		ble_peripheral_app_handle_ext_adv_state_evt(gap_msg.msg_data.gap_ext_adv_state_change.adv_handle,
									 (T_GAP_EXT_ADV_STATE)gap_msg.msg_data.gap_ext_adv_state_change.new_state,
									 gap_msg.msg_data.gap_ext_adv_state_change.cause);
	}
	break;
#endif
	default:
		APP_PRINT_ERROR1("app_handle_gap_msg: unknown subtype %d", p_gap_msg->subtype);
		break;
	}
}
/** @} */ /* End of group PERIPH_GAP_MSG */

/** @defgroup  PERIPH_GAP_CALLBACK GAP Callback Event Handler
    * @brief Handle GAP callback event
    * @{
    */
/**
  * @brief Callback for gap le to notify app
  * @param[in] cb_type callback msy type @ref GAP_LE_MSG_Types.
  * @param[in] p_cb_data point to callback data @ref T_LE_CB_DATA.
  * @retval result @ref T_APP_RESULT
  */
T_APP_RESULT app_gap_callback(uint8_t cb_type, void *p_cb_data)
{
	T_APP_RESULT result = APP_RESULT_SUCCESS;
	T_GAP_CAUSE cause = GAP_CAUSE_SUCCESS;
	T_LE_CB_DATA *p_data = (T_LE_CB_DATA *)p_cb_data;

	switch (cb_type) {
#if F_BT_LE_4_2_DATA_LEN_EXT_SUPPORT
	case GAP_MSG_LE_DATA_LEN_CHANGE_INFO:
		APP_PRINT_INFO3("GAP_MSG_LE_DATA_LEN_CHANGE_INFO: conn_id %d, tx octets 0x%x, max_tx_time 0x%x",
						p_data->p_le_data_len_change_info->conn_id,
						p_data->p_le_data_len_change_info->max_tx_octets,
						p_data->p_le_data_len_change_info->max_tx_time);
		break;
#endif
	case GAP_MSG_LE_MODIFY_WHITE_LIST:
		APP_PRINT_INFO2("GAP_MSG_LE_MODIFY_WHITE_LIST: operation %d, cause 0x%x",
						p_data->p_le_modify_white_list_rsp->operation,
						p_data->p_le_modify_white_list_rsp->cause);
		break;
#if (LEGACY_ADV_CONCURRENT == 1)
	case GAP_MSG_LE_ADV_UPDATE_PARAM:
		APP_PRINT_INFO1("GAP_MSG_LE_ADV_UPDATE_PARAM: cause 0x%x",
						p_data->p_le_adv_update_param_rsp->cause);
		if (p_data->p_le_adv_update_param_rsp->cause == 0) {
			if (lac_adapter.start_stop_flag == true)
				break;
			T_GAP_CAUSE ret = GAP_CAUSE_SUCCESS;
#if BT_VENDOR_CMD_ONE_SHOT_SUPPORT
			ret = le_vendor_one_shot_adv();
#endif
			if (ret != GAP_CAUSE_SUCCESS) {
				printf("le_vendor_one_shot_adv fail! ret = 0x%x\r\n", ret);
			}
		} else
			printf("GAP_MSG_LE_ADV_UPDATE_PARAM: cause 0x%x\r\n", p_data->p_le_adv_update_param_rsp->cause);
		break;
#endif
#if APP_PRIVACY_EN
	case GAP_MSG_LE_BOND_MODIFY_INFO:
		APP_PRINT_INFO1("GAP_MSG_LE_BOND_MODIFY_INFO: type 0x%x",
						p_data->p_le_bond_modify_info->type);
		privacy_handle_bond_modify_msg(p_data->p_le_bond_modify_info->type,
									   p_data->p_le_bond_modify_info->p_entry, true);
		break;
#endif
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
	case GAP_MSG_LE_EXT_ADV_START_SETTING:
		APP_PRINT_INFO3("GAP_MSG_LE_EXT_ADV_START_SETTING:cause 0x%x, flag 0x%x, adv_handle 0x%x",
						p_data->p_le_ext_adv_start_setting_rsp->cause,
						p_data->p_le_ext_adv_start_setting_rsp->flag,
						p_data->p_le_ext_adv_start_setting_rsp->adv_handle);
		if (GAP_SUCCESS != p_data->p_le_ext_adv_start_setting_rsp->cause) {
			random_update_flag = 0;
			printf("GAP_MSG_LE_EXT_ADV_START_SETTING:cause 0x%x, flag 0x%x, adv_handle 0x%x\r\n",
					p_data->p_le_ext_adv_start_setting_rsp->cause,
					p_data->p_le_ext_adv_start_setting_rsp->flag,
					p_data->p_le_ext_adv_start_setting_rsp->adv_handle);
		} else {
			if (0 == random_update_flag) {
				cause = le_ext_adv_enable(1, &p_data->p_le_ext_adv_start_setting_rsp->adv_handle);
				if (cause) {
					printf("le_ext_adv_enable cause = 0x%x \r\n", cause);
				}
			} else {
				random_update_flag = 0;
			}
		}
        break;
    case GAP_MSG_LE_EXT_ADV_REMOVE_SET:
        APP_PRINT_INFO2("GAP_MSG_LE_EXT_ADV_REMOVE_SET:cause 0x%x, adv_handle 0x%x",
                        p_data->p_le_ext_adv_remove_set_rsp->cause,
                        p_data->p_le_ext_adv_remove_set_rsp->adv_handle);
		printf("GAP_MSG_LE_EXT_ADV_REMOVE_SET:cause 0x%x, adv_handle 0x%x\r\n",
                        p_data->p_le_ext_adv_remove_set_rsp->cause,
                        p_data->p_le_ext_adv_remove_set_rsp->adv_handle);
		if (GAP_SUCCESS == p_data->p_le_ext_adv_remove_set_rsp->cause) {
			uint8_t idx;
			for (idx = 0; idx < GAP_MAX_EXT_ADV_SETS; idx++) {
				if (ext_adv_tbl[idx].used &&  ext_adv_tbl[idx].adv_handle == p_data->p_le_ext_adv_remove_set_rsp->adv_handle) {
					ext_adv_tbl[idx].used = false;
					ext_adv_tbl[idx].adv_handle = GAP_INVALID_ADV_HANDLE;
					ext_adv_tbl[idx].ext_adv_state = EXT_ADV_STATE_IDLE;
				}
			}
		} else {
			printf("GAP_MSG_LE_EXT_ADV_REMOVE_SET:cause 0x%x, adv_handle 0x%x\r\n",
					p_data->p_le_ext_adv_remove_set_rsp->cause,
				    p_data->p_le_ext_adv_remove_set_rsp->adv_handle);
		}
        break;
    case GAP_MSG_LE_EXT_ADV_CLEAR_SET:
        APP_PRINT_INFO1("GAP_MSG_LE_EXT_ADV_CLEAR_SET:cause 0x%x",
                        p_data->p_le_ext_adv_clear_set_rsp->cause);
		printf("GAP_MSG_LE_EXT_ADV_CLEAR_SET:cause 0x%x\r\n",
                        p_data->p_le_ext_adv_clear_set_rsp->cause);
		if (GAP_SUCCESS == p_data->p_le_ext_adv_clear_set_rsp->cause) {
			uint8_t idx;
			for (idx = 0; idx < GAP_MAX_EXT_ADV_SETS; idx++) {
				if (ext_adv_tbl[idx].used) {
					ext_adv_tbl[idx].used = false;
					ext_adv_tbl[idx].adv_handle = GAP_INVALID_ADV_HANDLE;
					ext_adv_tbl[idx].ext_adv_state = EXT_ADV_STATE_IDLE;
				}
			}
		} else {
			printf("GAP_MSG_LE_EXT_ADV_CLEAR_SET:cause 0x%x\r\n",
					p_data->p_le_ext_adv_clear_set_rsp->cause);
		}
        break;
    case GAP_MSG_LE_EXT_ADV_ENABLE:
        APP_PRINT_INFO1("GAP_MSG_LE_EXT_ADV_ENABLE:cause 0x%x",
                        p_data->le_cause.cause);
		printf("GAP_MSG_LE_EXT_ADV_ENABLE:cause 0x%x\r\n",
                        p_data->le_cause.cause);
        break;
    case GAP_MSG_LE_EXT_ADV_DISABLE:
        APP_PRINT_INFO1("GAP_MSG_LE_EXT_ADV_DISABLE:cause 0x%x",
                        p_data->le_cause.cause);
		printf("GAP_MSG_LE_EXT_ADV_DISABLE:cause 0x%x\r\n",
                        p_data->le_cause.cause);
        break;
	case GAP_MSG_LE_SCAN_REQ_RECEIVED_INFO:
		APP_PRINT_INFO3("GAP_MSG_LE_SCAN_REQ_RECEIVED_INFO:adv_handle 0x%x, scanner_addr_type 0x%x, scanner_addr %s",
						p_data->p_le_scan_req_received_info->adv_handle,
						p_data->p_le_scan_req_received_info->scanner_addr_type,
						TRACE_BDADDR(p_data->p_le_scan_req_received_info->scanner_addr));
		break;
	case GAP_MSG_LE_EXT_ADV_STATE_CHANGE_INFO:
		{
			ble_peripheral_app_handle_ext_adv_state_evt(p_data->p_le_ext_adv_state_change_info->adv_handle,
										 (T_GAP_EXT_ADV_STATE)p_data->p_le_ext_adv_state_change_info->state,
										 p_data->p_le_ext_adv_state_change_info->cause);
		}
		break;
#endif
	default:
		APP_PRINT_ERROR1("app_gap_callback: unhandled cb_type 0x%x", cb_type);
		break;
	}
	return result;
}
/** @} */ /* End of group PERIPH_GAP_CALLBACK */

#if F_BT_GAPS_CHAR_WRITEABLE
/** @defgroup  SCATTERNET_GAPS_WRITE GAP Service Callback Handler
    * @brief Use @ref F_BT_GAPS_CHAR_WRITEABLE to open
    * @{
    */
/**
 * @brief    All the BT GAP service callback events are handled in this function
 * @param[in] service_id  Profile service ID
 * @param[in] p_para      Pointer to callback data
 * @return   Indicates the function call is successful or not
 * @retval   result @ref T_APP_RESULT
 */
T_APP_RESULT gap_service_callback(T_SERVER_ID service_id, void *p_para)
{
	(void) service_id;
	T_APP_RESULT  result = APP_RESULT_SUCCESS;
	T_GAPS_CALLBACK_DATA *p_gap_data = (T_GAPS_CALLBACK_DATA *)p_para;
	APP_PRINT_INFO2("gap_service_callback: conn_id = %d msg_type = %d\n", p_gap_data->conn_id,
					p_gap_data->msg_type);
	APP_PRINT_INFO2("gap_service_callback: len = 0x%x,opcode = %d\n", p_gap_data->msg_data.len,
					p_gap_data->msg_data.opcode);
	if (p_gap_data->msg_type == SERVICE_CALLBACK_TYPE_WRITE_CHAR_VALUE) {
		switch (p_gap_data->msg_data.opcode) {
		case GAPS_WRITE_DEVICE_NAME: {
			T_LOCAL_NAME device_name;
			memcpy(device_name.local_name, p_gap_data->msg_data.p_value, p_gap_data->msg_data.len);
			device_name.local_name[p_gap_data->msg_data.len] = 0;
			//printf("GAPS_WRITE_DEVICE_NAME:device_name = %s\r\n",device_name.local_name);
			flash_save_local_name(&device_name);
		}
		break;

		case GAPS_WRITE_APPEARANCE: {
			uint16_t appearance_val;
			T_LOCAL_APPEARANCE appearance;
			LE_ARRAY_TO_UINT16(appearance_val, p_gap_data->msg_data.p_value);
			appearance.local_appearance = appearance_val;
			//printf("GAPS_WRITE_APPEARANCE:appearance = %s\r\n",appearance.local_appearance);
			flash_save_local_appearance(&appearance);
		}
		break;
		default:
			APP_PRINT_ERROR1("gap_service_callback: unhandled msg_data.opcode 0x%x", p_gap_data->msg_data.opcode);
			//printf("gap_service_callback: unhandled msg_data.opcode 0x%x\r\n", p_gap_data->msg_data.opcode);
			break;
		}
	}
	return result;
}
#endif

/** @defgroup  PERIPH_SEVER_CALLBACK Profile Server Callback Event Handler
    * @brief Handle profile server callback event
    * @{
    */
/**
    * @brief    All the BT Profile service callback events are handled in this function
    * @note     Then the event handling function shall be called according to the
    *           service_id
    * @param    service_id  Profile service ID
    * @param    p_data      Pointer to callback data
    * @return   T_APP_RESULT, which indicates the function call is successful or not
    * @retval   APP_RESULT_SUCCESS  Function run successfully
    * @retval   others              Function run failed, and return number indicates the reason
    */
T_APP_RESULT app_profile_callback(T_SERVER_ID service_id, void *p_data)
{
	T_APP_RESULT app_result = APP_RESULT_SUCCESS;
	if (service_id == SERVICE_PROFILE_GENERAL_ID) {
		T_SERVER_APP_CB_DATA *p_param = (T_SERVER_APP_CB_DATA *)p_data;
		switch (p_param->eventId) {
		case PROFILE_EVT_SRV_REG_COMPLETE:// srv register result event.
			APP_PRINT_INFO1("PROFILE_EVT_SRV_REG_COMPLETE: result %d",
							p_param->event_data.service_reg_result);
			break;

		case PROFILE_EVT_SEND_DATA_COMPLETE:
			APP_PRINT_INFO5("PROFILE_EVT_SEND_DATA_COMPLETE: conn_id %d, cause 0x%x, service_id %d, attrib_idx 0x%x, credits %d",
							p_param->event_data.send_data_result.conn_id,
							p_param->event_data.send_data_result.cause,
							p_param->event_data.send_data_result.service_id,
							p_param->event_data.send_data_result.attrib_idx,
							p_param->event_data.send_data_result.credits);
			printf("PROFILE_EVT_SEND_DATA_COMPLETE: conn_id %d, cause 0x%x, service_id %d, attrib_idx 0x%x, credits %d\r\n",
				   p_param->event_data.send_data_result.conn_id,
				   p_param->event_data.send_data_result.cause,
				   p_param->event_data.send_data_result.service_id,
				   p_param->event_data.send_data_result.attrib_idx,
				   p_param->event_data.send_data_result.credits);
			if (p_param->event_data.send_data_result.cause == GAP_SUCCESS) {
				APP_PRINT_INFO0("PROFILE_EVT_SEND_DATA_COMPLETE success");
				printf("PROFILE_EVT_SEND_DATA_COMPLETE success\r\n");
			} else {
				APP_PRINT_ERROR0("PROFILE_EVT_SEND_DATA_COMPLETE failed");
				printf("PROFILE_EVT_SEND_DATA_COMPLETE failed\r\n");
			}
			break;

		default:
			break;
		}
	} else  if (service_id == simp_srv_id) {
		TSIMP_CALLBACK_DATA *p_simp_cb_data = (TSIMP_CALLBACK_DATA *)p_data;
		switch (p_simp_cb_data->msg_type) {
		case SERVICE_CALLBACK_TYPE_INDIFICATION_NOTIFICATION: {
			switch (p_simp_cb_data->msg_data.notification_indification_index) {
			case SIMP_NOTIFY_INDICATE_V3_ENABLE: {
				APP_PRINT_INFO0("SIMP_NOTIFY_INDICATE_V3_ENABLE");
				printf("SIMP_NOTIFY_INDICATE_V3_ENABLE\r\n");
			}
			break;

			case SIMP_NOTIFY_INDICATE_V3_DISABLE: {
				APP_PRINT_INFO0("SIMP_NOTIFY_INDICATE_V3_DISABLE");
				printf("SIMP_NOTIFY_INDICATE_V3_DISABLE\r\n");
			}
			break;
			case SIMP_NOTIFY_INDICATE_V4_ENABLE: {
				APP_PRINT_INFO0("SIMP_NOTIFY_INDICATE_V4_ENABLE");
				printf("SIMP_NOTIFY_INDICATE_V4_ENABLE\r\n");
			}
			break;
			case SIMP_NOTIFY_INDICATE_V4_DISABLE: {
				APP_PRINT_INFO0("SIMP_NOTIFY_INDICATE_V4_DISABLE");
				printf("SIMP_NOTIFY_INDICATE_V4_DISABLE\r\n");
			}
			break;
			default:
				break;
			}
		}
		break;

		case SERVICE_CALLBACK_TYPE_READ_CHAR_VALUE: {
			if (p_simp_cb_data->msg_data.read_value_index == SIMP_READ_V1) {
				uint8_t value[2] = {0x01, 0x02};
				APP_PRINT_INFO0("SIMP_READ_V1");
				printf("SIMP_READ_V1: value 0x%02x 0x%02x\r\n", value[0], value[1]);
				simp_ble_service_set_parameter(SIMPLE_BLE_SERVICE_PARAM_V1_READ_CHAR_VAL, 2, &value);
			}
		}
		break;
		case SERVICE_CALLBACK_TYPE_WRITE_CHAR_VALUE: {
			switch (p_simp_cb_data->msg_data.write.opcode) {
			case SIMP_WRITE_V2: {
				APP_PRINT_INFO2("SIMP_WRITE_V2: write type %d, len %d", p_simp_cb_data->msg_data.write.write_type,
								p_simp_cb_data->msg_data.write.len);
				printf("SIMP_WRITE_V2: write type %d, len %d\r\n", p_simp_cb_data->msg_data.write.write_type,
					   p_simp_cb_data->msg_data.write.len);
				printf("SIMP_WRITE_V2: value ");
				for (int i = 0; i < p_simp_cb_data->msg_data.write.len; i ++) {
					printf("0x%02x ", *(p_simp_cb_data->msg_data.write.p_value + i));
				}
				printf("\r\n");
			}
			break;
			default:
				break;
			}
		}
		break;

		default:
			break;
		}
	} else if (service_id == bas_srv_id) {
		T_BAS_CALLBACK_DATA *p_bas_cb_data = (T_BAS_CALLBACK_DATA *)p_data;
		switch (p_bas_cb_data->msg_type) {
		case SERVICE_CALLBACK_TYPE_INDIFICATION_NOTIFICATION: {
			switch (p_bas_cb_data->msg_data.notification_indification_index) {
			case BAS_NOTIFY_BATTERY_LEVEL_ENABLE: {
				APP_PRINT_INFO0("BAS_NOTIFY_BATTERY_LEVEL_ENABLE");
				printf("BAS_NOTIFY_BATTERY_LEVEL_ENABLE\r\n");
			}
			break;

			case BAS_NOTIFY_BATTERY_LEVEL_DISABLE: {
				APP_PRINT_INFO0("BAS_NOTIFY_BATTERY_LEVEL_DISABLE");
				printf("BAS_NOTIFY_BATTERY_LEVEL_DISABLE\r\n");
			}
			break;
			default:
				break;
			}
		}
		break;

		case SERVICE_CALLBACK_TYPE_READ_CHAR_VALUE: {
			if (p_bas_cb_data->msg_data.read_value_index == BAS_READ_BATTERY_LEVEL) {
				uint8_t battery_level = 90;
				APP_PRINT_INFO1("BAS_READ_BATTERY_LEVEL: battery_level %d", battery_level);
				printf("BAS_READ_BATTERY_LEVEL: battery_level %d\r\n", battery_level);
				bas_set_parameter(BAS_PARAM_BATTERY_LEVEL, 1, &battery_level);
			}
		}
		break;

		default:
			break;
		}
	}

	return app_result;
}

void app_vendor_callback(uint8_t cb_type, void *p_cb_data)
{
	T_GAP_VENDOR_CB_DATA cb_data;
	memcpy(&cb_data, p_cb_data, sizeof(T_GAP_VENDOR_CB_DATA));
	APP_PRINT_INFO1("app_vendor_callback: command 0x%x", cb_data.p_gap_vendor_cmd_rsp->command);
	switch (cb_type)
	{
		case GAP_MSG_VENDOR_CMD_RSP:
			switch(cb_data.p_gap_vendor_cmd_rsp->command)
			{
#if BT_VENDOR_CMD_ONE_SHOT_SUPPORT
				case HCI_LE_VENDOR_EXTENSION_FEATURE2:
					//if(cb_data.p_gap_vendor_cmd_rsp->param[0] == HCI_EXT_SUB_ONE_SHOT_ADV)
					{
						APP_PRINT_ERROR1("One shot adv resp: cause 0x%x", cb_data.p_gap_vendor_cmd_rsp->cause);
#if (LEGACY_ADV_CONCURRENT == 1)
						if (cb_data.p_gap_vendor_cmd_rsp->cause == 0) {
							if (lac_adapter.deinit_flag == true)
								break;
							if (lac_adapter.sem_handle != NULL) {
								if (os_sem_give(lac_adapter.sem_handle) == false) {
									printf("os_sem_give lac_adapter.sem_handle fail!\r\n");
								}
							}
						} else
							printf("One shot adv resp: cause 0x%x\r\n", cb_data.p_gap_vendor_cmd_rsp->cause);
#endif
					}
					break;
#endif
				default:
					break;
			}
			break;

		default:
			break;
	}

	return;
}

#if (F_BT_LE_USE_RANDOM_ADDR == 1)
/**
 * @brief   Save static random address information into flash.
 * @param[in] p_addr Pointer to the buffer for saving data.
 * @retval 0 Save success.
 * @retval other Failed.
 */
uint32_t ble_peripheral_app_save_static_random_address(T_APP_STATIC_RANDOM_ADDR *p_addr)
{
	APP_PRINT_INFO0("ble_peripheral_app_save_static_random_address");
	return ftl_save(p_addr, BLE_PERIPHERAL_APP_STATIC_RANDOM_ADDR_OFFSET, sizeof(T_APP_STATIC_RANDOM_ADDR));
}

/**
  * @brief  Load static random address information from storage.
  * @param[out]  p_addr Pointer to the buffer for loading data.
  * @retval 0 Load success.
  * @retval other Failed.
  */
uint32_t ble_peripheral_app_load_static_random_address(T_APP_STATIC_RANDOM_ADDR *p_addr)
{
	uint32_t result;
	result = ftl_load(p_addr, BLE_PERIPHERAL_APP_STATIC_RANDOM_ADDR_OFFSET,
						sizeof(T_APP_STATIC_RANDOM_ADDR));
	APP_PRINT_INFO1("ble_peripheral_app_load_static_random_address: result 0x%x", result);
	if (result)
	{
		memset(p_addr, 0, sizeof(T_APP_STATIC_RANDOM_ADDR));
	}
	return result;
}
#endif

#if (LEGACY_ADV_CONCURRENT == 1)
void legacy_adv_concurrent_send_msg(void)
{
	T_IO_MSG io_msg;
	io_msg.type = IO_MSG_TYPE_QDECODE;
	io_msg.subtype = 2;

	uint8_t event = EVENT_IO_TO_APP;

	if (evt_queue_handle != NULL && io_queue_handle != NULL) {
		if (os_msg_send(io_queue_handle, &io_msg, 0) == false) {
			printf("legacy_adv_concurrent_send_msg io_queue_handle fail\r\n");
		} else if (os_msg_send(evt_queue_handle, &event, 0) == false) {
			printf("legacy_adv_concurrent_send_msg evt_queue_handle fail\r\n");
		}
	}
}

void legacy_adv_concurrent_send_adv_info(T_LEGACY_ADV_INFO *p_adv_info)
{
	if (lac_adapter.deinit_flag == true)
		return;

	if (lac_adapter.queue_handle != NULL) {
		if (os_msg_send(lac_adapter.queue_handle, p_adv_info, 0) == false) {
			printf("os_msg_send adv_info_0 lac_adapter.queue_handle fail!\r\n");
		}
	} else {
		printf("lac_adapter.queue_handle is NULL!\r\n");
	}
}

void legacy_adv_concurrent_task(void *p_param)
{
	T_LEGACY_ADV_INFO adv_info;

	while (1) {
		if (os_sem_take(lac_adapter.sem_handle, 0xFFFFFFFF) == false) {
			printf("os_sem_take lac_adapter.sem_handle fail!\r\n");
		} else {
			if (lac_adapter.deinit_flag == true) // If deinit, break the outer while loop
				break;

			while (os_msg_recv(lac_adapter.queue_handle, &adv_info, 0) == false) {
				os_delay(1);
				if (lac_adapter.start_stop_flag == true) {	// If stoped, break the inner while loop
					lac_adapter.send_adv_flag = false;
					break;
				}
			}

			if (lac_adapter.send_adv_flag == true) {
#if (F_BT_LE_USE_RANDOM_ADDR == 1)
				if (adv_info.local_bd_type == GAP_LOCAL_ADDR_LE_PUBLIC) {
					le_cfg_local_identity_address(local_public_addr, GAP_IDENT_ADDR_PUBLIC);
				} else if (adv_info.local_bd_type == GAP_LOCAL_ADDR_LE_RANDOM) {
					le_cfg_local_identity_address(local_static_random_addr, GAP_IDENT_ADDR_RAND);
				}
				le_adv_set_param(GAP_PARAM_ADV_LOCAL_ADDR_TYPE, sizeof(adv_info.local_bd_type), &adv_info.local_bd_type);
#endif
				le_adv_set_param(GAP_PARAM_ADV_DATA, adv_info.adv_data_size, (void *)adv_info.adv_data);
				le_adv_set_param(GAP_PARAM_SCAN_RSP_DATA, adv_info.scan_rsp_data_size, (void *)adv_info.scan_rsp_data);
				legacy_adv_concurrent_send_msg();
			}
		}
	}

	os_sem_delete(lac_adapter.sem_handle);
	os_msg_queue_delete(lac_adapter.queue_handle);
	os_timer_delete(&lac_adapter.timer0_handle);
	os_timer_delete(&lac_adapter.timer1_handle);
	memset(&lac_adapter, 0, sizeof(lac_adapter));
	printf("legacy_adv_concurrent_deinit success!\r\n");
	os_task_delete(NULL);
}

void legacy_adv_concurrent_timer0_callback(void *p_param)
{
	legacy_adv_concurrent_send_adv_info(&adv_info_0);
}

void legacy_adv_concurrent_timer1_callback(void *p_param)
{
	legacy_adv_concurrent_send_adv_info(&adv_info_1);
}

void legacy_adv_concurrent_init(uint32_t adv_interval_0, uint32_t adv_interval_1)
{
	if (adv_interval_0 < 20 || adv_interval_0 > 10240 || adv_interval_1 < 20 || adv_interval_1 > 10240) {
		printf("ADV interval should in [20ms, 10240ms]!\r\n");
	}

	adv_info_0.adv_interval = adv_interval_0;
#if (F_BT_LE_USE_RANDOM_ADDR == 1)
	adv_info_0.local_bd_type = GAP_LOCAL_ADDR_LE_RANDOM;
#else if (F_BT_LE_USE_RANDOM_ADDR == 0)
	adv_info_0.local_bd_type = GAP_LOCAL_ADDR_LE_PUBLIC;
#endif
	memcpy(&adv_info_0.adv_data, adv_data_0, sizeof(adv_data_0));
	memcpy(&adv_info_0.scan_rsp_data, scan_rsp_data_0, sizeof(scan_rsp_data_0));
	adv_info_0.adv_data_size = sizeof(adv_data_0);
	adv_info_0.scan_rsp_data_size = sizeof(scan_rsp_data_0);

	adv_info_1.adv_interval = adv_interval_1;
#if (F_BT_LE_USE_RANDOM_ADDR == 1)
	adv_info_1.local_bd_type = GAP_LOCAL_ADDR_LE_RANDOM;
#else if (F_BT_LE_USE_RANDOM_ADDR == 0)
	adv_info_1.local_bd_type = GAP_LOCAL_ADDR_LE_PUBLIC;
#endif
	memcpy(&adv_info_1.adv_data, adv_data_1, sizeof(adv_data_1));
	memcpy(&adv_info_1.scan_rsp_data, scan_rsp_data_1, sizeof(scan_rsp_data_1));
	adv_info_1.adv_data_size = sizeof(adv_data_1);
	adv_info_1.scan_rsp_data_size = sizeof(scan_rsp_data_1);

	memset(&lac_adapter, 0, sizeof(lac_adapter));
	lac_adapter.start_stop_flag = true;
	lac_adapter.send_adv_flag = true;
	lac_adapter.deinit_flag = false;
	if (os_sem_create(&lac_adapter.sem_handle, 0, 1) == false)
		printf("os_sem_create lac_adapter.sem_handle fail!\r\n");
	if (os_msg_queue_create(&lac_adapter.queue_handle, 0x20, sizeof(T_LEGACY_ADV_INFO)) == false)
		printf("os_msg_queue_create lac_adapter.queue_handle fail!\r\n");
	if (os_timer_create(&lac_adapter.timer0_handle, "lac timer0", 0, adv_interval_0, 1, legacy_adv_concurrent_timer0_callback) == false)
		printf("os_timer_create lac_adapter.timer0_handle fail!\r\n");
	if (os_timer_create(&lac_adapter.timer1_handle, "lac timer1", 1, adv_interval_1, 1, legacy_adv_concurrent_timer1_callback) == false)
		printf("os_timer_create lac_adapter.timer1_handle fail!\r\n");
	if (os_task_create(&lac_adapter.task_handle, "lac task", legacy_adv_concurrent_task, 0, 1024, 1) == false)
		printf("os_task_create lac_adapter.task_handle fail!\r\n");
}

void legacy_adv_concurrent_start()
{
	if (lac_adapter.start_stop_flag == true) {
		lac_adapter.start_stop_flag = false;
		lac_adapter.send_adv_flag = true;
		legacy_adv_concurrent_send_adv_info(&adv_info_0);
		legacy_adv_concurrent_send_adv_info(&adv_info_1);
		os_sem_give(lac_adapter.sem_handle);
		os_timer_start(&lac_adapter.timer0_handle);
		os_timer_start(&lac_adapter.timer1_handle);
	}
}

void legacy_adv_concurrent_stop()
{
	if (lac_adapter.start_stop_flag == false) {
		lac_adapter.start_stop_flag = true;
		os_timer_stop(&lac_adapter.timer0_handle);
		os_timer_stop(&lac_adapter.timer1_handle);
	}
}

void legacy_adv_concurrent_deinit()
{
	if (lac_adapter.start_stop_flag == false) {
		legacy_adv_concurrent_stop();
	}

	lac_adapter.deinit_flag = true;
	os_sem_give(lac_adapter.sem_handle);
}
#endif

#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT	
void ble_peripheral_init_ext_adv(void)
{
	uint8_t use_ext_adv = true;
	le_set_gap_param(GAP_PARAM_USE_EXTENDED_ADV, sizeof(use_ext_adv), &use_ext_adv);
	le_ext_adv_init(GAP_MAX_EXT_ADV_SETS);
}

void ble_peripheral_create_ext_adv(ext_adv_param_t *ext_adv_param, uint8_t *handle)
{
	T_GAP_CAUSE cause = GAP_CAUSE_SUCCESS;
	bool scan_req_notification_enable = false;
	uint8_t use_extended = true;
	uint8_t *random_address = NULL;
	int idx;

	for (idx = 0; idx < GAP_MAX_EXT_ADV_SETS; idx++) {
		if (!ext_adv_tbl[idx].used) {
			break;
		}
	}

	if (GAP_MAX_EXT_ADV_SETS == idx) {
		printf("invalid idx\r\n");
		return;
	}

	uint8_t adv_handle = le_ext_adv_create_adv_handle();
	if (0xFF == adv_handle) {
		printf("invalid adv handle\r\n");
		return;
	}

	/* Set extend advertising parameters */
	le_set_gap_param(GAP_PARAM_USE_EXTENDED_ADV, sizeof(use_extended), &use_extended);

	cause = le_ext_adv_set_adv_param(adv_handle,
								ext_adv_param->adv_event_prop,
								ext_adv_param->primary_adv_interval_min,
								ext_adv_param->primary_adv_interval_max,
								ext_adv_param->primary_adv_channel_map,
								ext_adv_param->own_addr_type,
								ext_adv_param->peer_addr_type,
								ext_adv_param->peer_addr,
								ext_adv_param->filter_policy,
								ext_adv_param->tx_power,
								ext_adv_param->primary_adv_phy,
								ext_adv_param->secondary_adv_max_skip,
								ext_adv_param->secondary_adv_phy,
								ext_adv_param->adv_sid,
								scan_req_notification_enable);

	if (cause) {
		printf("le_ext_adv_set_adv_param cause = %x \r\n", cause);
		return;
	}
	random_update_flag = 0;
	if (GAP_LOCAL_ADDR_LE_RANDOM == ext_adv_param->own_addr_type) {
		printf("Random address:");
		for (int i = 0;i < 6; i ++) {
			printf("0x%x ", *(ext_adv_param->own_addr + i));
		}
		printf("\n\r");
		cause = le_ext_adv_set_random(adv_handle, ext_adv_param->own_addr);
		if (cause) {
			printf("le_ext_adv_set_random cause = %x \r\n", cause);
			return;
		}
		random_update_flag = 1;
		cause = le_ext_adv_start_setting(adv_handle, EXT_ADV_SET_RANDOM_ADDR);
		if (cause) {
			random_update_flag = 0;
			printf("le_ext_adv_start_setting cause = %x \r\n", cause);
			return;
		}
	}

	ext_adv_tbl[idx].used = true;
	ext_adv_tbl[idx].adv_handle = adv_handle;
	ext_adv_tbl[idx].ext_adv_state = EXT_ADV_STATE_IDLE;

	*handle = adv_handle;
}

void ble_peripheral_set_ext_scan_rsp_data(uint8_t adv_handle, uint16_t data_len, uint8_t *ext_scan_rsp)
{
	T_GAP_CAUSE cause = GAP_CAUSE_SUCCESS;
	if (!ble_peripheral_app_gap_ext_adv_handle_valid(adv_handle)) {
		printf("invalid ext adv handle %d\r\n", adv_handle);
		return;
	}
	cause = le_ext_adv_set_scan_response_data(adv_handle, data_len, ext_scan_rsp);
	if (cause) {
		printf("le_ext_adv_set_scan_response_data cause = %x \r\n", cause);
	}
}

void ble_peripheral_set_ext_adv_data(uint8_t adv_handle, uint16_t data_len, uint8_t *ext_adv_rsp)
{
	T_GAP_CAUSE cause = GAP_CAUSE_SUCCESS;
	if (!ble_peripheral_app_gap_ext_adv_handle_valid(adv_handle)) {
		printf("invalid ext adv handle %d\r\n", adv_handle);
		return;
	}
	cause = le_ext_adv_set_adv_data(adv_handle, data_len, ext_adv_rsp);
	if (cause) {
		printf("le_ext_adv_set_adv_data cause = %x \r\n", cause);
	}
}

void ble_peripheral_start_ext_adv(ext_adv_start_t *adv_start_param)
{
	T_GAP_CAUSE cause = GAP_CAUSE_SUCCESS;
	uint8_t adv_handle = adv_start_param->adv_handle;
	uint16_t duration = adv_start_param->duration;
	uint8_t num_events = adv_start_param->num_events;

	if (!ble_peripheral_app_gap_ext_adv_handle_valid(adv_handle)) {
		printf("invalid ext adv handle %d\r\n", adv_handle);
		return;
	}

	cause = le_ext_adv_set_adv_enable_param(adv_handle, duration, num_events);

	if (cause) {
		printf("le_ext_adv_set_adv_enable_param cause = %x \r\n", cause);
		return;
	}

	cause = le_ext_adv_start_setting(adv_handle, EXT_ADV_SET_AUTO);
	if (cause) {
		printf("le_ext_adv_start_setting cause = %x \r\n", cause);
	}
}
void ble_peripheral_remove_ext_adv_set(uint8_t adv_handle)
{
	T_GAP_CAUSE cause = GAP_CAUSE_SUCCESS;
	if (!ble_peripheral_app_gap_ext_adv_handle_valid(adv_handle)) {
		printf("invalid ext adv handle %d\r\n", adv_handle);
		return;
	}
	cause = le_ext_adv_remove_set(adv_handle);
	if (cause) {
		printf("le_ext_adv_remove_set cause = %x \r\n", cause);
	}
}

void ble_peripheral_clear_all_ext_adv_set(void)
{
	T_GAP_CAUSE cause = GAP_CAUSE_SUCCESS;
	cause = le_ext_adv_clear_set();
	if (cause) {
		printf("le_ext_adv_clear_set cause = %x \r\n", cause);
	}
}

void ble_peripheral_stop_ext_adv(uint8_t adv_handle)
{
	T_GAP_CAUSE cause = GAP_CAUSE_SUCCESS;
	for (uint8_t idx = 0; idx < GAP_MAX_EXT_ADV_SETS; idx++) {
		if (ext_adv_tbl[idx].used && ext_adv_tbl[idx].adv_handle == adv_handle) {
			if (ext_adv_tbl[idx].ext_adv_state == EXT_ADV_STATE_IDLE) {
				printf("ext adv[%d] already stop\r\n", adv_handle);
				return;
			}
		}
	}
	cause = le_ext_adv_disable(1, &adv_handle);
	if (cause) {
		printf("le_ext_adv_disable cause = %x \r\n", cause);
	}
}
#endif

/** @} */ /* End of group PERIPH_SEVER_CALLBACK */
/** @} */ /* End of group PERIPH_APP */
#endif
