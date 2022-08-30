/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: GATT client interfaces
 */

#ifndef OHOS_BT_GATT_CLIENT_H
#define OHOS_BT_GATT_CLIENT_H

#include "ohos_bt_def.h"

/* Refer to the definition of "HCI_LE_Connection_Update" in core 5.2|Vol 4,Part E */
typedef struct {
	int connIntervalMin; /* Minimum value for the connection interval. [N * 1.25ms] */
	int connIntervalMax; /* Maximum value for the connection interval. [N * 1.25ms] */
	int connLatency; /* Slave latency for the connection in number of connection events. [Range: 0x0000 to 0x01F3] */
	int supervisionTimeout; /* Supervision timeout for the LE Link. [N * 10 ms] */
	int minConnectionEventLen; /* The minimum length of connection event needed for LE connection. [N * 0.625ms] */
	int maxConnectionEventLen; /* [N * 0.625ms] */
} BtGattcConnPara;

/* notification/indication data */
typedef struct {
	unsigned short handle;
	unsigned char isNotify; /* 1: notification, 0: indication */
	unsigned short dataLen;
	unsigned char *data;
} BtGattNotifyData;

/* Parameters for GATT read operations */
typedef struct {
	unsigned short handle;
	unsigned short dataLen;
	unsigned char *data;
} BtGattReadData;

/* Callback invoked in response to BleGattcRegister */
typedef void (*RegisterClientCallback)(int status, int clientId, const BtUuid *appUuid);

/* Callback invoked in response to BleGattcConnect */
typedef void (*ConnectClientCallback)(int connId, int status, int clientId, const BdAddr *bdAddr);

/* Callback invoked in response to BleGattcDisconnect */
typedef void (*DisconnectClientCallback)(int connId, int status, int clientId, const BdAddr *bdAddr);

/* Callback invoked when the connection parameters for a given connection changed */
typedef void (*ConnectParaUpdateCallback)(int connId, int interval, int latency, int timeout, int status);

/* Invoked in response to BleGattcSearchServices when the GATT service discovery has been completed */
typedef void (*SearchServiceCompleteCallback)(int connId, int status);

/* Reports result of a GATT read operation */
typedef void (*ReadCharacteristicCallback)(int connId, int status, BtGattReadData *readData);

/* GATT write characteristic operation callback */
typedef void (*WriteCharacteristicCallback)(int connId, int status, unsigned short handle);

/* Callback invoked in response to BleGattcReadDescriptor */
typedef void (*ReadDescriptorCallback)(int connId, int status, BtGattReadData *readData);

/* Callback invoked in response to BleGattcWriteDescriptor */
typedef void (*WriteDescriptorCallback)(int connId, int status, unsigned short handle);

/* GATT execute prepared write callback */
typedef void (*ExecuteWriteCallback)(int connId, int status);

/* Callback invoked when the MTU size for a given connection changes */
typedef void (*ConfigureMtuSizeCallback)(int connId, int status, int mtuSize);

/* Callback invoked in response to BleGattcReadRemoteRssi */
typedef void (*ReadRemoteRssiCallback)(int clientId, const BdAddr *bdAddr, int rssi, int status);

/* Callback invoked in response to BleGattcRegisterNotifications, register/deregister */
typedef void (*RegisterNotificationCallback)(int connId, int registered, int status, unsigned short handle);

/* Callback invoked when a remote device sends a notification/indication that a client has registered for */
typedef void (*NotificationCallback)(int connId, BtGattNotifyData notifyData);

typedef struct {
	RegisterClientCallback registerClientCb;
	ConnectClientCallback connectClientCb;
	DisconnectClientCallback disconnectCb;
	ConnectParaUpdateCallback connectParaUpdateCb;
	SearchServiceCompleteCallback searchServiceCompleteCb;
	ReadCharacteristicCallback readCharacteristicCb;
	WriteCharacteristicCallback writeCharacteristicCb;
	ReadDescriptorCallback readDescriptorCb;
	WriteDescriptorCallback writeDescriptorCb;
	ExecuteWriteCallback executeWriteCb;
	ConfigureMtuSizeCallback configureMtuSizeCb;
	ReadRemoteRssiCallback readRemoteRssiCb;
	RegisterNotificationCallback registerNotificationCb;
	NotificationCallback notificationCb;
} BtGattClientCallbacks;

/*
 * @brief gatt client register, callback return clientId
 * @param[in] <appUuid> specified by upper layer
 * @return 0-success, other-fail
 */
int BleGattcRegister(BtUuid appUuid);

/*
 * @brief gatt client deregister
 * @param[in] <clientId> client Id
 * @return 0-success, other-fail
 */
int BleGattcUnRegister(int clientId);

/*
 * @brief Create a connection to a remote LE or dual-mode device
 * @param[in] <clientId> client Id
 * @param[in] <bdAddr> remote address
 * @param[in] <isDirect> is a direct connection or a background auto connection
 * @param[in] <transport> BtTransportId
 * @return 0-success, other-fail
 */
int BleGattcConnect(int clientId, const BdAddr *bdAddr, bool isDirect, int transport);

/*
 * @brief Disconnect a remote device or cancel a pending connection
 * @param[in] <clientId> client Id
 * @param[in] <bdAddr> remote address
 * @param[in] <connId>   connection index.
 * @return 0-success, other-fail
 */
int BleGattcDisconnect(int clientId, const BdAddr *bdAddr, int connId);

/*
 * @brief Send a connection parameter update request to the remote device.
 * @param[in] <bdAddr> remote address
 * @param[in] <BtGattcConnPara> connection param refer to "HCI_LE_Connection_Update".
 * @return 0-success, other-fail
 */
int BleGattcConnectParaUpdate(const BdAddr *bdAddr, BtGattcConnPara connPara);

/*
 * @brief This function is called to request a GATT service discovery on a GATT server.
          Optionally, the results can be filtered for a given UUID.
 * @param[in] <bdAddr> remote address
 * @param[in] <filterUuid> a UUID of the service application is interested in. If Null, discover for all services
 * @return 0-success, other-fail
 */
int BleGattcSearchServices(int connId, BtUuid filterUuid);

/*
 * @brief This function is called to read a characteristics value from the server.
 * @param[in] <connId> connection ID
 * @param[in] <handle> characteritic handle to read
 * @return 0-success, other-fail
 */
int BleGattcReadCharacteristic(int connId, int handle);

/*
 * @brief This function is called to write a characteristics value to the server.
 * @param[in] <connId> connection ID
 * @param[in] <handle> characteritic handle to read
 * @param[in] <writeType> BtGattWriteType, default: write need rsp
 * @param[in] <len> the data length
 * @param[in] <value> the data to be writen
 * @return 0-success, other-fail
 */
int BleGattcWriteCharacteristic(int connId, int handle, int writeType, int len, char *value);

/*
 * @brief This function is called to read a characteristics value from the server.
 * @param[in] <connId> connection ID
 * @param[in] <handle> descriptor handle to read
 * @return 0-success, other-fail
 */
int BleGattcReadDescriptor(int connId, int handle);

/*
 * @brief This function is called to write a descriptor value to the server.
 * @param[in] <connId> connection ID
 * @param[in] <handle> descriptor handle to read
 * @param[in] <writeType> BtGattWriteType, default: write need rsp
 * @param[in] <len> the data length
 * @param[in] <value> the data to be writen
 * @return 0-success, other-fail
 */
int BleGattcWriteDescriptor(int connId, int handle, int writeType, int len, char *value);

/*
 * @brief This function is called to send an execute write request to the server(or cancel the prepare write).
 * @param[in] <connId> connection ID
 * @param[in] <execute> [1-execute, 0-cancel], to execute or cancel the prepare write request(s).
 * @return 0-success, other-fail
 */
int BleGattcExecuteWrite(int connId, int execute);

/*
 * @brief This function is called to configure the ATT MTU size for a connection on an LE transport.
 * @param[in] <connId> connection ID
 * @param[in] <mtuSize> attribute MTU size.
 * @return 0-success, other-fail
 */
int BleGattcConfigureMtuSize(int connId, int mtuSize);

/*
 * @brief Read the RSSI for a connected remote device.
 * @param[in] <clientId> client Id
 * @param[in] <bdAddr> remote address
 * @return 0-success, other-fail
 */
int BleGattcReadRemoteRssi(int clientId, const BdAddr *bdAddr);

/*
 * @brief Enable or disable notifications/indications for a given characteristic.
 * @param[in] <clientId> client Id
 * @param[in] <bdAddr> remote address
 * @param[in] <handle> characteristic handle
 * @param[in] <enable> 1-register, 0-deregister
 * @return 0-success, other-fail
 */
int BleGattcRegisterNotifications(int clientId, const BdAddr *bdAddr, int handle, int enable);

/*
 * @brief Callback invoked for gatt client function
 * @param[in] <BtGattClientCallbacks> Callback funcs
 * @return 0-success, other-fail
 */
int BleGattcRegisterCallbacks(BtGattClientCallbacks *func);
#endif
