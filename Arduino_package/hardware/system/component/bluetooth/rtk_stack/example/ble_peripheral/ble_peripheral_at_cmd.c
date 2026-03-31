#include "platform_opts_bt.h"
#if ((defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL) || \
	(defined(CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) && CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) || \
	(defined(CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE) && CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE))
#include "platform_opts.h"
#include <platform_stdlib.h>
#if SUPPORT_LOG_SERVICE
#include "log_service.h"
#include "atcmd_bt.h"
#include "gap.h"
#include "gap_adv.h"
#include "gap_bond_le.h"
#include "gap_conn_le.h"
#include "app_msg.h"
#include "app_flags.h"
#include "os_msg.h"
#include "os_sched.h"
#include "profile_server.h"
#include "os_mem.h"
#include "basic_types.h"
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
#include "gap_ext_adv.h"
#include <peripheral_app.h>
#endif
#if defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL
extern void *evt_queue_handle;
extern void *io_queue_handle;
#if APP_PRIVACY_EN
extern T_GAP_DEV_STATE gap_dev_state;
extern void app_change_to_pair_mode(void);
#endif
#endif

#if defined(CONFIG_BT_SCATTERNET) && CONFIG_BT_SCATTERNET
extern void *ble_scatternet_evt_queue_handle;
extern void *ble_scatternet_io_queue_handle;
#if APP_PRIVACY_EN
extern T_GAP_DEV_STATE ble_scatternet_gap_dev_state;
extern void ble_scatternet_app_change_to_pair_mode(void);
#endif
#endif

#if ((defined(CONFIG_BT_MESH_PERIPHERAL) && CONFIG_BT_MESH_PERIPHERAL) || \
	(defined(CONFIG_BT_MESH_SCATTERNET) && CONFIG_BT_MESH_SCATTERNET))
#if defined(CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) && CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE
extern T_GAP_DEV_STATE bt_mesh_provisioner_multiple_profile_gap_dev_state;
#elif defined(CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE) && CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE
extern T_GAP_DEV_STATE bt_mesh_device_multiple_profile_gap_dev_state;
#endif
extern uint16_t bt_mesh_peripheral_adv_interval;
#endif

static u8 ctoi(char c)
{
	if ((c >= 'A') && (c <= 'F')) {
		return (c - 'A' + 0x0A);
	}

	if ((c >= 'a') && (c <= 'f')) {
		return (c - 'a' + 0x0A);
	}

	if ((c >= '0') && (c <= '9')) {
		return (c - '0' + 0x00);
	}

	return 0xFF;
}

static int hex_str_to_int(u32 str_len, s8 *str)
{
	int result = 0;
	unsigned int n = 2;
	if ((str_len < 3) || (str[0] != '0') || ((str[1] != 'x') && (str[1] != 'X'))) {
		return -1;
	}
	while (n < str_len) {
		result = (result << 4) | (ctoi(str[n++]));
	}
	return result;
}

static uint8_t get_bond_storage_num(void)
{
#if UPPER_STACK_VERSION == VERSION_2019
	return bond_storage_num;
#elif UPPER_STACK_VERSION == VERSION_2021
	return le_get_max_le_paired_device_num();
#endif
}

void ble_peripheral_at_cmd_send_msg(uint16_t sub_type)
{
	uint8_t event = EVENT_IO_TO_APP;

	T_IO_MSG io_msg;

	io_msg.type = IO_MSG_TYPE_QDECODE;
	io_msg.subtype = sub_type;

#if defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL
	if (evt_queue_handle != NULL && io_queue_handle != NULL) {
		if (os_msg_send(io_queue_handle, &io_msg, 0) == false) {
			printf("ble peripheral at cmd send msg fail: subtype 0x%x\r\n", io_msg.subtype);
		} else if (os_msg_send(evt_queue_handle, &event, 0) == false) {
			printf("ble peripheral at cmd send event fail: subtype 0x%x\r\n", io_msg.subtype);
		}
	}
#endif
#if defined(CONFIG_BT_SCATTERNET) && CONFIG_BT_SCATTERNET
	if (ble_scatternet_evt_queue_handle != NULL && ble_scatternet_io_queue_handle != NULL) {
		if (os_msg_send(ble_scatternet_io_queue_handle, &io_msg, 0) == false) {
			printf("ble peripheral at cmd send msg fail: subtype 0x%x\r\n", io_msg.subtype);
		} else if (os_msg_send(ble_scatternet_evt_queue_handle, &event, 0) == false) {
			printf("ble peripheral at cmd send event fail: subtype 0x%x\r\n", io_msg.subtype);
		}
	}
#endif
}

int ble_peripheral_at_cmd_set_adv_int(int argc, char **argv)
{
	u16 adv_int_max = atoi(argv[1]);
	u16 adv_int_min = atoi(argv[2]);
	T_GAP_DEV_STATE new_state = {0};

#if ((defined(CONFIG_BT_MESH_PERIPHERAL) && CONFIG_BT_MESH_PERIPHERAL) || \
	(defined(CONFIG_BT_MESH_SCATTERNET) && CONFIG_BT_MESH_SCATTERNET))
#if defined(CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE) && CONFIG_BT_MESH_PROVISIONER_MULTIPLE_PROFILE
	new_state = bt_mesh_provisioner_multiple_profile_gap_dev_state;
#elif defined(CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE) && CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE
	new_state = bt_mesh_device_multiple_profile_gap_dev_state;
#endif
	if (new_state.gap_init_state) {
		bt_mesh_peripheral_adv_interval = adv_int_min;
		return 0;
	}
#endif

#if ((defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL) || \
	(defined(CONFIG_BT_SCATTERNET) && CONFIG_BT_SCATTERNET))
	ble_peripheral_at_cmd_send_msg(0);
	do {
		os_delay(1);
		le_get_gap_param(GAP_PARAM_DEV_STATE, &new_state);
	} while (new_state.gap_adv_state != GAP_ADV_STATE_IDLE);

	le_adv_set_param(GAP_PARAM_ADV_INTERVAL_MAX, sizeof(adv_int_max), &adv_int_max);
	le_adv_set_param(GAP_PARAM_ADV_INTERVAL_MIN, sizeof(adv_int_min), &adv_int_min);

	ble_peripheral_at_cmd_send_msg(1);
	do {
		os_delay(1);
		le_get_gap_param(GAP_PARAM_DEV_STATE, &new_state);
	} while (new_state.gap_adv_state != GAP_ADV_STATE_ADVERTISING);
#endif

	return 0;
}

int ble_peripheral_at_cmd_auth(int argc, char **argv)
{
	u8 conn_id;
	u32 passcode;
	T_GAP_CFM_CAUSE confirm;
	int ret;

	if (strcmp(argv[1], "SEND") == 0) {
		if (argc != 3) {
			printf("ERROR:input parameter error!\r\n");
			return -1;
		}
		conn_id = atoi(argv[2]);
		le_bond_pair(conn_id);
	} else if (strcmp(argv[1], "KEY") == 0) {
		if (argc != 4) {
			printf("ERROR:input parameter error!\r\n");
			return -1;
		}
		conn_id = atoi(argv[2]);
		if (strlen(argv[3]) > 6) {
			confirm = GAP_CFM_CAUSE_REJECT;
		} else {
			confirm = GAP_CFM_CAUSE_ACCEPT;
		}
		s8 *str = (s8 *)argv[3];
		for (unsigned int i = 0; i < strlen(argv[3]); i ++) {
			if ((str[i ++] < '0') || (str[i ++] > '9')) {
				printf("ERROR:input parameter error!\r\n");
				return -1;
			}
		}

		passcode = atoi(argv[3]);
		if (passcode > GAP_PASSCODE_MAX) {
			printf("ERROR:passcode is out of range[0-999999]!\r\n");
			confirm = GAP_CFM_CAUSE_REJECT;
		}
		le_bond_passkey_input_confirm(conn_id, passcode, confirm);
	} else if (strcmp(argv[1], "MODE") == 0) {
		u8	auth_pair_mode = GAP_PAIRING_MODE_PAIRABLE;
		u16 auth_flags = GAP_AUTHEN_BIT_BONDING_FLAG;
		u8	auth_io_cap = GAP_IO_CAP_NO_INPUT_NO_OUTPUT;
#if F_BT_LE_SMP_OOB_SUPPORT
		u8	oob_enable = false;
#endif
		u8	auth_sec_req_enable = false;
		u16 auth_sec_req_flags = GAP_AUTHEN_BIT_BONDING_FLAG;

		if (argc >= 3) {
			auth_flags = hex_str_to_int(strlen(argv[2]), (s8 *)argv[2]);
			auth_sec_req_flags =  auth_flags;
		}
		if (argc >= 4) {
			auth_io_cap = atoi(argv[3]);
		}
		if (argc >= 5) {
			auth_sec_req_enable = atoi(argv[4]);
		}
#if F_BT_LE_SMP_OOB_SUPPORT
//		if (argc >= 6) {
//			oob_enable = atoi(argv[5]);
//		}
#endif

		gap_set_param(GAP_PARAM_BOND_PAIRING_MODE, sizeof(auth_pair_mode), &auth_pair_mode);
		gap_set_param(GAP_PARAM_BOND_AUTHEN_REQUIREMENTS_FLAGS, sizeof(auth_flags), &auth_flags);
		gap_set_param(GAP_PARAM_BOND_IO_CAPABILITIES, sizeof(auth_io_cap), &auth_io_cap);
#if F_BT_LE_SMP_OOB_SUPPORT
		gap_set_param(GAP_PARAM_BOND_OOB_ENABLED, sizeof(uint8_t), &oob_enable);
#endif
		le_bond_set_param(GAP_PARAM_BOND_SEC_REQ_ENABLE, sizeof(auth_sec_req_enable), &auth_sec_req_enable);
		le_bond_set_param(GAP_PARAM_BOND_SEC_REQ_REQUIREMENT, sizeof(auth_sec_req_flags), &auth_sec_req_flags);
		ret = gap_set_pairable_mode();

		if (ret == GAP_CAUSE_SUCCESS) {
			printf("Set pairable mode success!\r\n");
		} else {
			printf("Set pairable mode fail!\r\n");
		}
	} else {
		printf("ERROR:input parameter error!\r\n");
		return -1;
	}

	return ret;
}

int ble_peripheral_at_cmd_send_userconf(int argc, char **argv)
{
	(void) argc;
	u8 conn_id;
	u8 conf;
	int ret;
	T_GAP_CFM_CAUSE confirm;

	conn_id = atoi(argv[1]);
	conf = atoi(argv[2]);
	if (conf == 0) {
		confirm = GAP_CFM_CAUSE_REJECT;
	} else {
		confirm = GAP_CFM_CAUSE_ACCEPT;
	}

	ret = le_bond_user_confirm(conn_id, confirm);
	return ret;
}

int ble_peripheral_at_cmd_update_conn_request(int argc, char **argv)
{
	(void) argc;
	int ret;
	u8 conn_id = atoi(argv[1]);
	u16 conn_interval_min = hex_str_to_int(strlen(argv[2]), (s8 *) argv[2]);
	u16 conn_interval_max = hex_str_to_int(strlen(argv[3]), (s8 *)argv[3]);
	u16 conn_latency = hex_str_to_int(strlen(argv[4]), (s8 *)argv[4]);
	u16 supervision_timeout = hex_str_to_int(strlen(argv[5]), (s8 *)argv[5]);

	ret = le_update_conn_param(conn_id,
							   conn_interval_min,
							   conn_interval_max,
							   conn_latency,
							   supervision_timeout,
							   2 * (conn_interval_min - 1),
							   2 * (conn_interval_max - 1));
	return ret;

}

int ble_peripheral_at_cmd_bond_information(int argc, char **argv)
{
	(void) argc;

	if (strcmp(argv[1], "CLEAR") == 0) {
		le_bond_clear_all_keys();
	} else if (strcmp(argv[1], "INFO") == 0) {
		u8 i;
		T_LE_KEY_ENTRY *p_entry;
		for (i = 0; i < get_bond_storage_num(); i++) {
			p_entry = le_find_key_entry_by_idx(i);
			if (p_entry != NULL) {
				printf("bond_dev[%d]: bd 0x%02x%02x%02x%02x%02x%02x, addr_type %d, flags 0x%x\r\n",
					   p_entry->idx,
					   p_entry->remote_bd.addr[5],
					   p_entry->remote_bd.addr[4],
					   p_entry->remote_bd.addr[3],
					   p_entry->remote_bd.addr[2],
					   p_entry->remote_bd.addr[1],
					   p_entry->remote_bd.addr[0],
					   p_entry->remote_bd.remote_bd_type,
					   p_entry->flags);
			}
		}
	} else {
		return -1;
	}

	return 0;
}

int ble_peripheral_send_indi_notification(int argc, char **argv)
{
	(void) argc;

	u8 conn_id = atoi(argv[1]);
	u8 service_id = atoi(argv[2]);
	u16 attrib_index = hex_str_to_int(strlen(argv[3]), (s8 *) argv[3]);
	u8 type = atoi(argv[4]);
	int length = hex_str_to_int(strlen(argv[5]), (s8 *) argv[5]);
	int data_count;

	if (length == -1) {
		printf("Error:value length should be hexadecimal and start with '0X' or '0x'\r\n");
		return -1;
	} else if (length == 0) {
		printf("Error:value length should larger than 0\r\n");
		return -1;
	}

	u8 *data = (u8 *)os_mem_alloc(0, length * sizeof(u8));

	data_count = argc - 6;
	for (u8 i = 0; i < length; ++ i) {
		if (i < data_count) {
			data[i] = hex_str_to_int(strlen(argv[i + 6]), (s8 *)argv[i + 6]);
		} else {
			data[i] = 0xff;
		}
	}

	server_send_data(conn_id, service_id, attrib_index, data, length, (T_GATT_PDU_TYPE)type);

	if (data != NULL) {
		os_mem_free(data);
	}

	return 0;
}

#if APP_PRIVACY_EN
int ble_peripheral_change_to_pair_mode(int argc, char **argv)
{
	(void) argc;

	if (strcmp(argv[1], "PAIR") == 0) {
#if defined(CONFIG_BT_PERIPHERAL) && CONFIG_BT_PERIPHERAL
		if(gap_dev_state.gap_init_state){
			app_change_to_pair_mode();
		}
#endif
#if defined(CONFIG_BT_SCATTERNET) && CONFIG_BT_SCATTERNET
		if(ble_scatternet_gap_dev_state.gap_init_state){
			ble_scatternet_app_change_to_pair_mode();
		}
#endif
	}else{
		return -1;
	}
	return 0;
}
#endif
#endif
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
static uint8_t def_ext_adv_data[] = {
	// Flags
	0x02,
	GAP_ADTYPE_FLAGS,
	GAP_ADTYPE_FLAGS_LIMITED | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED,
	// Local name
	0x12,
	GAP_ADTYPE_LOCAL_NAME_COMPLETE,
	'R', 'T', 'K', '_', 'B', 'T', '_', 'A', 'D', 'V', '_', 'T', 'E', 'S', 'T', '_', '1',
	// Manufacturer Specific Data
	0xd8,
	GAP_ADTYPE_MANUFACTURER_SPECIFIC,
	0xd5, 0x00,
	0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2,
	0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2,
	0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2,
	0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2,
	0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2,
	0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2,
	0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2,
	0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2,
	0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2,
	0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2,
	0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2,
	0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2,
	0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2,
	0xf, 0xf, 0xf, 0xf, 0xf,
};

static uint8_t def_ext_scan_response[] = {
	//GAP_ADTYPE_APPEARANCE
	0x3,
	GAP_ADTYPE_APPEARANCE,
	LO_WORD(GAP_GATT_APPEARANCE_UNKNOWN),
	HI_WORD(GAP_GATT_APPEARANCE_UNKNOWN),
	// Manufacturer Specific Data
	0xf6,
	GAP_ADTYPE_MANUFACTURER_SPECIFIC,
	0x5d, 0x00,
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
	0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc, 0xc,
	0xd, 0xd, 0xd, 0xd, 0xd, 0xd, 0xd, 0xd, 0xd, 0xd, 0xd, 0xd, 0xd, 0xd, 0xd, 0xd,
	0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe,
	0xf, 0xf, 0xf,
};

static ext_adv_param_t def_ext_adv_param = {
	.adv_event_prop = LE_EXT_ADV_EXTENDED_ADV_CONN_UNDIRECTED,
	.primary_adv_interval_min = 320,
	.primary_adv_interval_max = 320,
	.primary_adv_channel_map = GAP_ADVCHAN_ALL,
	.own_addr_type = GAP_LOCAL_ADDR_LE_PUBLIC,
	.own_addr = {0},
	.peer_addr_type = GAP_REMOTE_ADDR_LE_PUBLIC,
	.peer_addr = {0},//;{0x8A, 0xAA, 0xAA, 0x4C, 0xE0, 0x00},
	.filter_policy = GAP_ADV_FILTER_ANY,
	.tx_power = 0x7E,
	.primary_adv_phy = GAP_PHYS_PRIM_ADV_1M,
	.secondary_adv_max_skip = 0,
	.secondary_adv_phy = GAP_PHYS_2M,
	.adv_sid = 0,
};

static u8 hex_str_to_bd_addr(u32 str_len, s8 *str, u8 *num_arr)
{
	num_arr += str_len / 2 - 1;
	u32 n = 0;
	u8 num = 0;

	if (str_len < 2) {
		return FALSE;
	}
	while (n < str_len) {
		if ((num = ctoi(str[n++])) == 0xFF) {
			return FALSE;
		}
		*num_arr = num << 4;
		if ((num = ctoi(str[n++])) == 0xFF) {
			return FALSE;
		}
		*num_arr |= num;
		num_arr--;
	}
	return TRUE;
}

void ble_peripheral_at_cmd_op_eadv(int argc, char **argv)
{
	uint8_t adv_handle;
	uint8_t phy;
	T_GAP_CAUSE cause = GAP_CAUSE_SUCCESS;
	ext_adv_param_t adv_param;
	ext_adv_create_t adv_create_param;
	uint8_t update_flags = EXT_ADV_SET_ADV_PARAS | EXT_ADV_SET_ADV_DATA | EXT_ADV_SET_SCAN_RSP_DATA | EXT_ADV_SET_RANDOM_ADDR;

	if(strcmp(argv[1], "eadv_param") == 0){      //config ext adv parameter
		memcpy(&adv_param, &def_ext_adv_param, sizeof(ext_adv_param_t));

		if (argc > 2) {
			adv_param.adv_sid = hex_str_to_int(strlen(argv[2]), (s8 *) argv[2]);
			if (0x0F < adv_param.adv_sid) {
				printf("invalid adv_sid %d\r\n", adv_param.adv_sid);
				return;
			}
		}
		if (argc > 3) {
			adv_param.adv_event_prop = (T_LE_EXT_ADV_EXTENDED_ADV_PROPERTY)hex_str_to_int(strlen(argv[3]), (s8 *) argv[3]);
			if (LE_EXT_ADV_EXTENDED_ADV_NON_SCAN_NON_CONN_UNDIRECTED != adv_param.adv_event_prop &&
			LE_EXT_ADV_EXTENDED_ADV_NON_SCAN_NON_CONN_DIRECTED != adv_param.adv_event_prop &&
			LE_EXT_ADV_EXTENDED_ADV_CONN_UNDIRECTED != adv_param.adv_event_prop &&
			LE_EXT_ADV_EXTENDED_ADV_CONN_DIRECTED != adv_param.adv_event_prop &&
			LE_EXT_ADV_EXTENDED_ADV_SCAN_UNDIRECTED != adv_param.adv_event_prop &&
			LE_EXT_ADV_EXTENDED_ADV_SCAN_DIRECTED != adv_param.adv_event_prop &&
			LE_EXT_ADV_LEGACY_ADV_CONN_SCAN_UNDIRECTED != adv_param.adv_event_prop &&
			LE_EXT_ADV_LEGACY_ADV_CONN_LOW_DUTY_DIRECTED != adv_param.adv_event_prop &&
			LE_EXT_ADV_LEGACY_ADV_CONN_HIGH_DUTY_DIRECTED != adv_param.adv_event_prop &&
			LE_EXT_ADV_LEGACY_ADV_SCAN_UNDIRECTED != adv_param.adv_event_prop &&
			LE_EXT_ADV_LEGACY_ADV_NON_SCAN_NON_CONN_UNDIRECTED != adv_param.adv_event_prop) {
			printf("invalid adv_event_prop %d\r\n", adv_param.adv_event_prop);
				return;
			}
		}
		if (argc > 4) {
			phy = hex_str_to_int(strlen(argv[4]), (s8 *) argv[4]);
			adv_param.primary_adv_phy = (T_GAP_PHYS_PRIM_ADV_TYPE)((phy >> 4) & 0xF);
			adv_param.secondary_adv_phy = (T_GAP_PHYS_TYPE)(phy & 0xF);
			if (GAP_PHYS_PRIM_ADV_1M != adv_param.primary_adv_phy && GAP_PHYS_PRIM_ADV_CODED != adv_param.primary_adv_phy) {
				printf("invalid primary adv phy %d phy 0x%x\r\n", adv_param.primary_adv_phy, phy);
				return;
			}
			if (GAP_PHYS_1M != adv_param.secondary_adv_phy && GAP_PHYS_2M != adv_param.secondary_adv_phy && GAP_PHYS_CODED != adv_param.secondary_adv_phy) {
				printf("invalid secondary_adv_phy %d phy 0x%x\r\n", adv_param.secondary_adv_phy, phy);
				return;
			}
		}
		if (argc > 5) {
			adv_param.filter_policy = (T_GAP_ADV_FILTER_POLICY)hex_str_to_int(strlen(argv[5]), (s8 *) argv[5]);
			if (GAP_ADV_FILTER_WHITE_LIST_ALL < adv_param.filter_policy) {
				printf("invalid adv_param.filter_policy %d\r\n", adv_param.filter_policy);
				return;
			}
		}
		if (argc > 6) {
			adv_param.tx_power = (int8_t)atoi(argv[6]);
		}
		if (argc > 7) {
			adv_param.primary_adv_interval_min = hex_str_to_int(strlen(argv[7]), (s8 *) argv[7]);
			adv_param.primary_adv_interval_max = hex_str_to_int(strlen(argv[8]), (s8 *) argv[8]);
			if (0x0020 > adv_param.primary_adv_interval_min) {
				printf("invalid primary_adv_interval_min %ld\r\n", adv_param.primary_adv_interval_min);
				return;
			}
			if (0x0020 > adv_param.primary_adv_interval_max || adv_param.primary_adv_interval_max < adv_param.primary_adv_interval_min) {
				printf("invalid primary_adv_interval_max %ld\r\n", adv_param.primary_adv_interval_max);
				return;
			}
		}

		if (argc > 9) {
			adv_param.own_addr_type = (T_GAP_LOCAL_ADDR_TYPE)hex_str_to_int(strlen(argv[9]), (s8 *) argv[9]);
			if (GAP_LOCAL_ADDR_LE_RAP_OR_RAND < adv_param.own_addr_type) {
				printf("invalid own_addr_type %d\r\n", adv_param.own_addr_type);
				return;
			}
			if (GAP_LOCAL_ADDR_LE_RANDOM == adv_param.own_addr_type) {
				if (false == hex_str_to_bd_addr(strlen(argv[10]), (s8 *)argv[10], (u8 *)adv_param.own_addr)) {
					return;
				}
			}
		}
		if (argc > 11) {
			adv_param.peer_addr_type = (T_GAP_REMOTE_ADDR_TYPE)hex_str_to_int(strlen(argv[11]), (s8 *) argv[11]);
			if (GAP_REMOTE_ADDR_LE_RANDOM_IDENTITY < adv_param.peer_addr_type) {
				printf("invalid peer_addr_type %d\r\n", adv_param.peer_addr_type);
				return;
			}
			if (false == hex_str_to_bd_addr(strlen(argv[12]), (s8 *)argv[12], (u8 *)adv_param.peer_addr)) {
				return;
			}
		}

		ble_peripheral_create_ext_adv(&adv_param, &adv_handle);
		printf("Ext adv_handle %d\r\n", adv_handle);
	} else if(strcmp(argv[1], "remove_eadv") == 0){        //remove an ext advertising set by adv handle
		if (argc != 3) {
			printf("[remove_eadv]invalid argc num %d\r\n", argc);
			return;
		}
		adv_handle = hex_str_to_int(strlen(argv[2]), (s8 *) argv[2]);
		ble_peripheral_remove_ext_adv_set(adv_handle);
	} else if (strcmp(argv[1], "clear_eadv") == 0) {			//remove all ext advertising set
		if (argc != 2) {
			printf("[clear_eadv]invalid argc num %d\r\n", argc);
			return;
		}
		ble_peripheral_clear_all_ext_adv_set();
	} else if(strcmp(argv[1], "stop_eadv") == 0){   		//stop ext adv
		if (argc != 3) {
			printf("[stop_eadv]invalid argc num %d\r\n", argc);
			return;
		}
		adv_handle = hex_str_to_int(strlen(argv[2]), (s8 *) argv[2]);
		ble_peripheral_stop_ext_adv(adv_handle);
	} else if(strcmp(argv[1], "start_eadv") == 0) {			//start ext adv
		ext_adv_start_t adv_start_param = {0,0};
		if (argc < 2 || argc > 5) {
			printf("[ext_adv_start]invalid argc num %d\r\n", argc);
			return;
		}
		adv_start_param.adv_handle = hex_str_to_int(strlen(argv[2]), (s8 *) argv[2]);
		if (!ble_peripheral_app_gap_ext_adv_handle_valid(adv_start_param.adv_handle)) {
			printf("invalid ext adv handle %d\r\n", adv_start_param.adv_handle);
			return;
		}
		if (argc > 3) {
			adv_start_param.duration = hex_str_to_int(strlen(argv[3]), (s8 *) argv[3]);
		}
		if (argc > 4) {
			adv_start_param.num_events = hex_str_to_int(strlen(argv[4]), (s8 *) argv[4]);
		}
		ble_peripheral_start_ext_adv(&adv_start_param);
	} else if (strcmp(argv[1], "eadv_data") == 0) {
		if (argc != 4) {
			printf("[eadv_data]invalid argc num %d\r\n", argc);
			return;
		}
		adv_handle = hex_str_to_int(strlen(argv[2]), (s8 *) argv[2]);
		uint8_t *pdata = (uint8_t *)def_ext_adv_data;
		uint16_t len = sizeof(def_ext_adv_data);
		len = hex_str_to_int(strlen(argv[3]), (s8 *) argv[3]);
		ble_peripheral_set_ext_adv_data(adv_handle, len, pdata);
	} else if (strcmp(argv[1], "escanrsp_data") == 0) {
		if (argc != 4) {
			printf("[escanrsp_data]invalid argc num %d\r\n", argc);
			return;
		}
		adv_handle = hex_str_to_int(strlen(argv[2]), (s8 *) argv[2]);
		uint8_t *pdata = (uint8_t *)def_ext_scan_response;
		uint16_t len = sizeof(def_ext_scan_response);
		len = hex_str_to_int(strlen(argv[3]), (s8 *) argv[3]);

		ble_peripheral_set_ext_scan_rsp_data(adv_handle, len, pdata);
	}
}
#endif
int ble_peripheral_app_handle_at_cmd(uint16_t subtype, void *arg)
{
#if SUPPORT_LOG_SERVICE
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	if (arg) {
		argc = parse_param(arg, argv);
	}

	switch (subtype) {
	case BT_ATCMD_AUTH:
		ble_peripheral_at_cmd_auth(argc, argv);
		break;
	case BT_ATCMD_SEND_USERCONF:
		ble_peripheral_at_cmd_send_userconf(argc, argv);
		break;
	case BT_ATCMD_UPDATE_CONN_REQUEST:
		ble_peripheral_at_cmd_update_conn_request(argc, argv);
		break;
	case BT_ATCMD_BOND_INFORMATION:
		ble_peripheral_at_cmd_bond_information(argc, argv);
		break;
	case BT_ATCMD_SEND_INDI_NOTI:
		ble_peripheral_send_indi_notification(argc, argv);
		break;
	case BT_ATCMD_CHANGE_TO_PAIR_MODE:
#if APP_PRIVACY_EN
		ble_peripheral_change_to_pair_mode(argc, argv);
#endif
		break;
		case BT_ATCMD_OP_EXT_ADV:
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
		ble_peripheral_at_cmd_op_eadv(argc, argv);
#endif
		break;
	default:
		break;
	}

	return 0;
#else
	return 0;
#endif
}
#endif
