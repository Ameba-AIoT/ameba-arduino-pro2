#include <profile_server.h>
#include "ms_hal_ble.h"

#define MS_READ_MAX_LEN 300
#define MS_WRITE_MAX_LEN 300
#define BMS_MAX_ATTR_NUM 12

typedef struct {
	T_WRITE_TYPE write_type;
	unsigned int len;
	uint8_t *p_value;
	ms_hal_ble_service_write_cb write_cb;
} T_MS_WRITE_MSG;

typedef struct {
	uint16_t attr_index;
	uint16_t ccc_val;
} T_MS_CCCD_MSG;

typedef union {
	T_MS_CCCD_MSG cccd;
	T_MS_WRITE_MSG write;
} T_MS_MSG_DATA;


typedef struct {
	uint8_t conn_id;
	T_SERVER_ID srv_id;
	T_SERVICE_CALLBACK_TYPE msg_type;
	T_MS_MSG_DATA msg_data;

} T_MS_ADAPTER_CALLBACK_DATA;


typedef struct {
	uint8_t type;
	uint8_t conn_id;
	uint8_t srv_id;
	uint16_t attrib_index;
	uint8_t *val;
	uint16_t len;
} BMS_INDICATION_PARAM;


typedef struct {
	uint8_t att_handle;
	ms_hal_ble_attrib_callback_t func;
} BMS_SERVICE_CALLBACK_INFO;


typedef struct BMS_SERVICE_INFO {
	uint8_t srvId;
	uint8_t att_num;
	T_ATTRIB_APPL *att_tbl;
	BMS_SERVICE_CALLBACK_INFO *cbInfo;
	struct BMS_SERVICE_INFO *next;
} BMS_SERVICE_INFO;

BMS_SERVICE_INFO *ble_ms_adapter_parse_srv_tbl(ms_hal_ble_service_attrib_t **profile, uint16_t attrib_count);
bool ble_ms_adapter_send_indication_notification(uint8_t conn_id, uint8_t service_id, uint8_t handle, uint8_t *p_value, uint16_t length, bool type);
T_SERVER_ID ble_ms_adapter_add_service(BMS_SERVICE_INFO *service_info, void *p_func);


