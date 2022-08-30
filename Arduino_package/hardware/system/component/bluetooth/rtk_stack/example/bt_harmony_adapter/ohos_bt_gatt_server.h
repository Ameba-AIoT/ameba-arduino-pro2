/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: GATT server interfaces
 */

#ifndef OHOS_BT_GATT_SERVER_H
#define OHOS_BT_GATT_SERVER_H

#include "ohos_bt_def.h"

typedef enum {
	OHOS_BLE_SEC_NONE = 0x00,
	OHOS_BLE_SEC_ENCRYPT,
	OHOS_BLE_SEC_ENCRYPT_NO_MITM,
	OHOS_BLE_SEC_ENCRYPT_MITM
} BleSecAct;

typedef struct {
	int connectId; /* connection index */
	int status; /* read/write character status, GattStatus */
	int attrHandle; /* attribute handle */
	int valueLen;
	char *value; /* response data from host */
} GattsSendRspParam;

typedef struct {
	int connectId; /* connection index */
	int attrHandle; /* attribute handle */
	int confirm; /* true(indication)-the client shall respond a conformation, false(notification)-send a notification */
	int valueLen; /* response data from host */
	char *value;
} GattsSendIndParam;

typedef struct {
	int connId; /* connect index */
	int transId; /* BtTransportId */
	BdAddr *bdAddr;
	int attrHandle; /* The handle of the attribute to be read */
	int offset; /* The offset of the first octet to be read */
	bool isLong; /* If isLong is true, then this request is part of a Long Read procedure */
} BtReqReadCbPara;

typedef struct {
	int connId; /* connect index */
	int transId; /* BtTransportId */
	BdAddr *bdAddr;
	int attrHandle; /* The handle of the attribute to be written */
	int offset; /* The offset of the first octet to be written */
	int length;
	bool needRsp; /* if the remote device requires a response */
	bool isPrep; /* if this write operation should be queued for later execution */
	unsigned char *value;
} BtReqWriteCbPara;

/* Callback invoked in response to register_server */
typedef void (*RegisterServerCallback)(int status, int serverId, BtUuid *appUuid);

/* Callback indicating that a remote device has connected */
typedef void (*ConnectServerCallback)(int connId, int serverId, const BdAddr *bdAddr);

/* Callback indicating that a remote device has disconnected */
typedef void (*DisconnectServerCallback)(int connId, int serverId, const BdAddr *bdAddr);

/* Callback invoked in response to add service */
typedef void (*ServiceAddCallback)(int status, int serverId, BtUuid *uuid, int srvcHandle);

/* Callback indicating that an included service has been added to a service */
typedef void (*IncludeServiceAddCallback)(int status, int serverId, int srvcHandle, int includeSrvcHandle);

/* Callback invoked when a characteristic has been added to a service */
typedef void (*CharacteristicAddCallback)(int status, int serverId, BtUuid *uuid,
		int srvcHandle, int characteristicHandle);

/* Callback invoked when a descriptor has been added to a characteristic */
typedef void (*DescriptorAddCallback)(int status, int serverId, BtUuid *uuid,
									  int srvcHandle, int descriptorHandle);

/* Callback invoked in response to start_service */
typedef void (*ServiceStartCallback)(int status, int serverId, int srvcHandle);

/* Callback invoked in response to stop_service */
typedef void (*ServiceStopCallback)(int status, int serverId, int srvcHandle);

/* Callback triggered when a service has been deleted */
typedef void (*ServiceDeleteCallback)(int status, int serverId, int srvcHandle);

/* Callback invoked when a remote device has requested to read a characteristicor descriptor.
 * The application must respond by calling send_response
 */
typedef void (*RequestReadCallback)(BtReqReadCbPara readCbPara);

/* Callback invoked when a remote device has requested to write to a characteristic or descriptor. */
typedef void (*RequestWriteCallback)(BtReqWriteCbPara writeCbPara);

/* Callback triggered in response to send_response if the remote device sends a confirmation */
typedef void (*ResponseConfirmationCallback)(int status, int handle);

/* Callback confirming that a notification or indication has been sent to a remote device */
typedef void (*IndicationSentCallback)(int connId, int status);

/* Callback invoked when the MTU for a given connection changes */
typedef void (*MtuChangeCallback)(int connId, int mtu);

typedef struct {
	RegisterServerCallback registerServerCb;
	ConnectServerCallback connectServerCb;
	DisconnectServerCallback disconnectServerCb;
	ServiceAddCallback serviceAddCb;
	IncludeServiceAddCallback includeServiceAddCb;
	CharacteristicAddCallback characteristicAddCb;
	DescriptorAddCallback descriptorAddCb;
	ServiceStartCallback serviceStartCb;
	ServiceStopCallback serviceStopCb;
	ServiceDeleteCallback serviceDeleteCb;
	RequestReadCallback requestReadCb;
	RequestWriteCallback requestWriteCb;
	ResponseConfirmationCallback responseConfirmationCb;
	IndicationSentCallback indicationSentCb;
	MtuChangeCallback mtuChangeCb;
} BtGattServerCallbacks;

typedef int (*BleGattServiceRead)(unsigned char *buff, unsigned int *len);

typedef int (*BleGattServiceWrite)(unsigned char *buff, unsigned int len);

typedef int (*BleGattServiceIndicate)(unsigned char *buff, unsigned int len);

typedef struct {
	BleGattServiceRead read;
	BleGattServiceWrite write;
	BleGattServiceIndicate indicate;
} BleGattOperateFunc;

typedef struct {
	BleAttribType attrType;
	unsigned int permission; /* e.g. (OHOS_GATT_PERMISSION_READ | OHOS_GATT_PERMISSION_WRITE) */
	UuidType uuidType;
	unsigned char uuid[OHOS_BLE_UUID_MAX_LEN];
	unsigned char *value;
	unsigned char valLen;
	/* e.g. (OHOS_GATT_CHARACTER_PROPERTY_BIT_BROADCAST | OHOS_GATT_CHARACTER_PROPERTY_BIT_READ) */
	unsigned char properties;
	BleGattOperateFunc func;
} BleGattAttr;

typedef struct {
	unsigned int attrNum;
	BleGattAttr *attrList;
} BleGattService;

/*
 * @brief gatt server application register, callback return serverId
 * @param[in] <appUuid> specified by upper layer
 * @return 0-success, other-fail
 */
int BleGattsRegister(BtUuid appUuid);

/*
 * @brief gatt server deregister
 * @param[in] <clientId> server interface Id
 * @return 0-success, other-fail
 */
int BleGattsUnRegister(int serverId);

/*
 * @brief Cancel connection with remote device
 * @param[in] <serverId> server interface id
 * @param[in] <bdAddr>   remote address
 * @param[in] <connId>   connection index.
 * @return 0-success, other-fail
 */
int BleGattsDisconnect(int serverId, BdAddr bdAddr, int connId);

/*
 * @brief add service
 * @param[in] <serverId>  server interface id
 * @param[in] <srvcUuid>  service uuid and uuid length
 * @param[in] <isPrimary> is primary or secondary service.
 * @param[in] <number>    service characther attribute number.
 * @return 0-success, other-fail
 */
int BleGattsAddService(int serverId, BtUuid srvcUuid, bool isPrimary, int number);

/*
 * @brief add characteristic
 * @param[in] <serverId>    server interface id
 * @param[in] <srvcHandle>  service handle
 * @param[in] <characUuid>  characteristic uuid and uuid length
 * @param[in] <properties>  e.g. (OHOS_GATT_CHARACTER_PROPERTY_BIT_BROADCAST | OHOS_GATT_CHARACTER_PROPERTY_BIT_READ)
 * @param[in] <permissions> e.g. (OHOS_GATT_PERMISSION_READ | OHOS_GATT_PERMISSION_WRITE)
 * @return 0-success, other-fail
 */
int BleGattsAddCharacteristic(int serverId, int srvcHandle, BtUuid characUuid,
							  int properties, int permissions);

/*
 * @brief add descriptor
 * @param[in] <serverId>    server interface id
 * @param[in] <srvcHandle>  service handle
 * @param[in] <descUuid>    descriptor uuid and uuid length
 * @param[in] <permissions> e.g. (OHOS_GATT_PERMISSION_READ | OHOS_GATT_PERMISSION_WRITE)
 * @return 0-success, other-fail
 */
int BleGattsAddDescriptor(int serverId, int srvcHandle, BtUuid descUuid, int permissions);

/*
 * @brief start service
 * @param[in] <serverId>    server interface id
 * @param[in] <srvcHandle>  service handle
 * @return 0-success, other-fail
 */
int BleGattsStartService(int serverId, int srvcHandle);

/*
 * @brief start service
 * @param[in] <serverId>    server interface id
 * @param[in] <srvcHandle>  service handle
 * @return 0-success, other-fail
 */
int BleGattsStopService(int serverId, int srvcHandle);

/*
 * @brief remove a service from the list of provided services
 * @param[in] <serverId>   server interface id
 * @param[in] <srvcHandle>  service handle
 * @return 0-success, other-fail
 */
int BleGattsDeleteService(int serverId, int srvcHandle);

/*
 * @brief remove all services from the list of provided services
 * @param[in] <serverId>   server interface id
 * @return 0-success, other-fail
 */
int BleGattsClearServices(int serverId);

/*
 * @brief Send a response to a read or write request to a remote device.
 * @param[in] <serverId> server interface id
 * @param[in] <GattsSendRspParam> response param
 * @return 0-success, other-fail
 */
int BleGattsSendResponse(int serverId, GattsSendRspParam *param);

/*
 * @brief Send a notification or indication that a local characteristic has been updated
 * @param[in] <serverId> server interface id
 * @param[in] <GattsSendIndParam> indication param
 * @return 0-success, other-fail
 */
int BleGattsSendIndication(int serverId, GattsSendIndParam *param);

/*
 * @brief Set the encryption level of the data transmission channel during connection
 * @param[in] <bdAddr> remote address
 * @param[in] <secAct> BleSecAct
 * @return 0-success, other-fail
 */
int BleGattsSetEncryption(BdAddr bdAddr, BleSecAct secAct);

/*
 * @brief Callback invoked for gatt server function
 * @param[in] <BtGattServerCallbacks> Callback funcs
 * @return 0-success, other-fail
 */
int BleGattsRegisterCallbacks(BtGattServerCallbacks *func);

/*
 * @brief Start sevice include add service/characteristic/Descriptor option.
 * This API will not described in the development manual, only for Hilink.
 * @return 0-success, other-fail
 */
int BleGattsStartServiceEx(int *srvcHandle, BleGattService *srvcInfo);

/*
 * @brief Stop service.
 * This API will not described in the development manual, only for Hilink.
 * @return 0-success, other-fail
 */
int BleGattsStopServiceEx(int srvcHandle);
#endif
