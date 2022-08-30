/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: Common definition
 */

#ifndef OHOS_BT_DEF_H
#define OHOS_BT_DEF_H

/* Device address length */
#define OHOS_BD_ADDR_LEN 6

/* Bluetooth 16-byte UUID */
#define OHOS_BLE_UUID_MAX_LEN 16

/* Characteristic Properties */
#define OHOS_GATT_CHARACTER_PROPERTY_BIT_BROADCAST 0x01 /* Characteristic is broadcastable */
#define OHOS_GATT_CHARACTER_PROPERTY_BIT_READ 0x02 /* Characteristic is readable */
#define OHOS_GATT_CHARACTER_PROPERTY_BIT_WRITE_NO_RSP 0x04 /* Characteristic can be written without response */
#define OHOS_GATT_CHARACTER_PROPERTY_BIT_WRITE 0x08 /* Characteristic can be written */
#define OHOS_GATT_CHARACTER_PROPERTY_BIT_NOTIFY 0x10 /* Characteristic supports notification */
#define OHOS_GATT_CHARACTER_PROPERTY_BIT_INDICATE 0x20 /* Characteristic supports indication */
#define OHOS_GATT_CHARACTER_PROPERTY_BIT_SIGNED_WRITE 0x40 /* Characteristic supports write with signature */
#define OHOS_GATT_CHARACTER_PROPERTY_BIT_EXTENDED_PROPERTY 0x80 /* Characteristic has extended properties */

/* Attribute permissions */
#define OHOS_GATT_PERMISSION_READ 0x01 /* read permission */
#define OHOS_GATT_PERMISSION_READ_ENCRYPTED 0x02 /* Allow encrypted read operations */
#define OHOS_GATT_PERMISSION_READ_ENCRYPTED_MITM 0x04 /* Allow reading with man-in-the-middle protection */
#define OHOS_GATT_PERMISSION_WRITE 0x10 /* write permission */
#define OHOS_GATT_PERMISSION_WRITE_ENCRYPTED 0x20 /* Allow encrypted writes */
#define OHOS_GATT_PERMISSION_WRITE_ENCRYPTED_MITM 0x40 /* Allow encrypted writes with man-in-the-middle protection */
#define OHOS_GATT_PERMISSION_WRITE_SIGNED 0x80 /* Allow signed write operations */
/* Allow signed write operations with man-in-the-middle protection */
#define OHOS_GATT_PERMISSION_WRITE_SIGNED_MITM = 0x100

typedef enum {
	OHOS_BT_TRANSPORT_INVALID = 0x00,
	OHOS_BT_TRANSPORT_BR_EDR = 0x01,
	OHOS_BT_TRANSPORT_LE = 0x02
} BtTransportId;

typedef enum {
	OHOS_BT_STATUS_SUCCESS,
	OHOS_BT_STATUS_FAIL,
	OHOS_BT_STATUS_NOT_READY,
	OHOS_BT_STATUS_NOMEM,
	OHOS_BT_STATUS_BUSY,
	OHOS_BT_STATUS_DONE,
	OHOS_BT_STATUS_UNSUPPORTED,
	OHOS_BT_STATUS_PARM_INVALID,
	OHOS_BT_STATUS_UNHANDLED,
	OHOS_BT_STATUS_AUTH_FAILURE,
	OHOS_BT_STATUS_RMT_DEV_DOWN,
	OHOS_BT_STATUS_AUTH_REJECTED
} BtStatus;

/* Error Code, BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 3, Part F, table 3.4 */
typedef enum {
	OHOS_GATT_SUCCESS = 0x00,
	OHOS_GATT_INVALID_HANDLE = 0x01,
	OHOS_GATT_READ_NOT_PERMITTED = 0x02,
	OHOS_GATT_WRITE_NOT_PERMITTED = 0x03,
	OHOS_GATT_INVALID_PDU = 0x04,
	OHOS_GATT_INSUFFICIENT_AUTHENTICATION = 0x05,
	OHOS_GATT_REQUEST_NOT_SUPPORTED = 0x06,
	OHOS_GATT_INVALID_OFFSET = 0x07,
	OHOS_GATT_INSUFFICIENT_AUTHORIZATION = 0x08,
	OHOS_GATT_PREPARE_QUEUE_FULL = 0x09,
	OHOS_GATT_ATTRIBUTE_NOT_FOUND = 0x0A,
	OHOS_GATT_ATTRIBUTE_NOT_LONG = 0x0B,
	OHOS_GATT_INSUFFICIENT_ENCRYPTION_KEY_SIZE = 0x0C,
	OHOS_GATT_INVALID_ATTRIBUTE_VALUE_LENGTH = 0x0D,
	OHOS_GATT_UNLIKELY_ERROR = 0x0E,
	OHOS_GATT_INSUFFICIENT_ENCRYPTION = 0x0F,
	OHOS_GATT_UNSUPPORTED_GROUP_TYPE = 0x10,
	OHOS_GATT_INSUFFICIENT_RESOURCES = 0x11,
	OHOS_GATT_DATABASE_OUT_OF_SYNC = 0x12,
	OHOS_GATT_VALUE_NOT_ALLOWED = 0x13,
} GattStatus;

typedef enum {
	OHOS_BLE_ATTRIB_TYPE_SERVICE = 0x00,
	OHOS_BLE_ATTRIB_TYPE_CHAR,
	OHOS_BLE_ATTRIB_TYPE_CHAR_VALUE,
	OHOS_BLE_ATTRIB_TYPE_CHAR_CLIENT_CONFIG,
	OHOS_BLE_ATTRIB_TYPE_CHAR_USER_DESCR,
} BleAttribType;

typedef enum {
	OHOS_UUID_TYPE_NULL = 0x00,
	OHOS_UUID_TYPE_16_BIT,
	OHOS_UUID_TYPE_32_BIT,
	OHOS_UUID_TYPE_128_BIT,
} UuidType;

typedef enum {
	OHOS_GATT_AUTH_REQ_NONE = 0x00,
	OHOS_GATT_AUTH_REQ_NO_MITM = 0x01, /* unauthenticated encryption */
	OHOS_GATT_AUTH_REQ_MITM = 0x02, /* authenticated encryption */
	OHOS_GATT_AUTH_REQ_SIGNED_NO_MITM = 0x03,
	OHOS_GATT_AUTH_REQ_SIGNED_MITM = 0x04
} BtGattAuthReq;

typedef enum {
	OHOS_GATT_WRITE_NO_RSP = 0x01, /* Write only. "Write Command" */
	OHOS_GATT_WRITE_DEFAULT = 0x02, /* Write and need response from remote device. "Write Request" */
	OHOS_GATT_WRITE_PREPARE = 0x03, /* Request the server to prepare to write the value. "Prepare Write" */
	OHOS_GATT_WRITE_SIGNED = 0x04 /* Write including authentication signature. "Signed Write Command" */
} BtGattWriteType;

/* Device address */
typedef struct {
	unsigned char addr[OHOS_BD_ADDR_LEN];
} BdAddr;

/* uuid with len */
typedef struct {
	unsigned char uuidLen;
	char *uuid;
} BtUuid;
#endif
