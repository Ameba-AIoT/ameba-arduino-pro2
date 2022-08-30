#include <profile_server.h>
#include "ohos_bt_gatt_server.h"
#include "ohos_bt_gatt_client.h"

#define HARMONY_READ_MAX_LEN 300
#define HARMONY_WRITE_MAX_LEN 300
#define BHA_MAX_ATTR_NUM 12

typedef struct {
	T_WRITE_TYPE write_type;
	unsigned int len;
	uint8_t *p_value;
	BleGattServiceWrite write_cb;
} T_HARMONY_WRITE_MSG;

typedef struct {
	unsigned int *p_len;
	uint8_t *p_value;
	BleGattServiceRead read_cb;
} T_HARMONY_READ_MSG;

typedef struct {
	uint16_t attr_index;
	uint16_t ccc_val;
} T_HARMONY_CCCD_MSG;

typedef union {
	T_HARMONY_CCCD_MSG cccd;
	T_HARMONY_READ_MSG read;
	T_HARMONY_WRITE_MSG write;
} T_HARMONY_MSG_DATA;

typedef struct {
	uint8_t conn_id;
	T_SERVER_ID srv_id;
	T_SERVICE_CALLBACK_TYPE msg_type;
	T_HARMONY_MSG_DATA msg_data;
} T_HARMONY_CALLBACK_DATA;


typedef struct {
	uint8_t att_handle;
	BleGattOperateFunc func;
} BHA_SERVICE_CALLBACK_INFO;

typedef enum {
	BHA_SERVICE_REG_SUCCESS = 1,
	BHA_SERVICE_REG_PENDING
} BHA_SERVICE_STATUS;

typedef struct BHA_SERVICE_INFO {
	uint8_t srvId;
	uint8_t att_num;
	uint8_t start_handle;
	BHA_SERVICE_STATUS status;
	T_ATTRIB_APPL *att_tbl;
	BHA_SERVICE_CALLBACK_INFO *cbInfo;
	struct BHA_SERVICE_INFO *next;
} BHA_SERVICE_INFO;

typedef struct {
	bool type;
	uint8_t srv_id;
	uint8_t att_handle;
	char *val;
	uint16_t len;
} BHA_INDICATION_PARAM;

typedef struct {
	uint8_t srv_id;
	uint16_t start_handle;
	uint16_t chrc_num;
	uint16_t rela_atthandle[BHA_MAX_ATTR_NUM];    /* characteristic info */
} BHA_SRV_DATABASE;
extern uint8_t bt_harmony_adapter_srvs_num;

BHA_SERVICE_INFO *bt_harmony_adapter_parse_srv_tbl(BleGattService *profile);

T_SERVER_ID bt_harmony_adapter_add_service(BHA_SERVICE_INFO *service_info, void *p_func);

bool bt_harmony_adapter_send_indication(uint8_t conn_id, uint8_t service_id, uint8_t handle, uint8_t *p_value, uint16_t length, bool type);



