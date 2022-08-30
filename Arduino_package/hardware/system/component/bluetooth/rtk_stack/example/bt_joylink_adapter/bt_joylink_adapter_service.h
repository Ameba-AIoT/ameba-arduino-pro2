#ifndef _BT_JOYLINK_ADAPTER_SERVICE_H_
#define _BT_JOYLINK_ADAPTER_SERVICE_H_

#include <profile_server.h>
#include "joylink_log.h"

#define JOYLINK_READ_MAX_LEN 300
#define JOYLINK_WRITE_MAX_LEN 300
#define BJA_MAX_ATTR_NUM 12

#define BT_JOYLINK_ADAPTER_CHAR_WRITE_INDEX  0x02
#define BT_JOYLINK_ADAPTER_CHAR_INDICATION_INDEX  0x04
#define BT_JOYLINK_ADAPTER_CHAR_INDICATION_CCCD_INDEX   (BT_JOYLINK_ADAPTER_CHAR_INDICATION_INDEX + 1)

T_SERVER_ID joylink_service_id;

typedef struct {
	T_WRITE_TYPE write_type;
	unsigned int len;
	uint8_t *p_value;
} T_JOYLINK_WRITE_MSG;

typedef struct {
	unsigned int *p_len;
	uint8_t *p_value;
} T_JOYLINK_READ_MSG;

typedef struct {
	uint16_t attr_index;
	uint16_t ccc_val;
} T_JOYLINK_CCCD_MSG;

typedef union {
	T_JOYLINK_CCCD_MSG cccd;
	T_JOYLINK_READ_MSG read;
	T_JOYLINK_WRITE_MSG write;
} T_JOYLINK_MSG_DATA;

typedef struct {
	uint8_t conn_id;
	T_SERVER_ID srv_id;
	T_SERVICE_CALLBACK_TYPE msg_type;
	T_JOYLINK_MSG_DATA msg_data;
} T_JOYLINK_CALLBACK_DATA;

typedef struct {
	uint8_t type;
	uint8_t srv_id;
	uint8_t index;
	char *val;
	uint16_t len;
} BJA_INDICATION_PARAM;

bool bt_joylink_adapter_send_indication(uint8_t conn_id, uint8_t service_id, uint8_t handle, uint8_t *p_value, uint16_t length, T_GATT_PDU_TYPE type);

#endif
