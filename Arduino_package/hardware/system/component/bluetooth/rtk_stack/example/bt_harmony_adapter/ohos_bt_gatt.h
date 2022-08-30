/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: GATT interfaces
 */

#ifndef OHOS_BT_GATT_H
#define OHOS_BT_GATT_H

#include "ohos_bt_def.h"

/* e.g. Legacy SCAN_RSP to an ADV_IND, 0x1B
   OHOS_BLE_EVT_TYPE_LEGACY_ADV | OHOS_BLE_EVT_TYPE_SCAN_RESPONSE | OHOS_BLE_EVT_TYPE_SCANNABLE_ADV | */

#define OHOS_BLE_EVT_TYPE_CONNECTABLE_ADV 0x01 /* bit[0] */
#define OHOS_BLE_EVT_TYPE_SCANNABLE_ADV 0x02 /* bit[1] */
#define OHOS_BLE_EVT_TYPE_DIRECTED_ADV 0x04 /* bit[2] */
#define OHOS_BLE_EVT_TYPE_SCAN_RESPONSE 0x08 /* bit[3] */
#define OHOS_BLE_EVT_TYPE_LEGACY_ADV 0x10 /* bit[4] */
#define OHOS_BLE_EVT_TYPE_DATA_STATUS_COMPLETE 0x00 /* bit[6:5] , 0b00:Complete */
#define OHOS_BLE_EVT_TYPE_DATA_STATUS_INCOMPLETE 0x20 /* bit[6:5], 0b01:Incomplete, more data to come */
/* bit[6:5], 0b10:Incomplete,data truncated, no more to come */
#define OHOS_BLE_EVT_TYPE_DATA_STATUS_INCOMPLETE_TRUNCATED 0x40

typedef enum {
	OHOS_BLE_ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY = 0x00,
	OHOS_BLE_ADV_FILTER_ALLOW_SCAN_WLST_CON_ANY = 0x01,
	OHOS_BLE_ADV_FILTER_ALLOW_SCAN_ANY_CON_WLST = 0x02,
	OHOS_BLE_ADV_FILTER_ALLOW_SCAN_WLST_CON_WLST = 0x03,
} BleAdvFilter;

/* BLUETOOTH CORE SPECIFICATION Version 5.2|Vol4,Part E, "HCI_LE_Set_Advertising_Parameters" */
typedef enum {
	OHOS_BLE_ADV_IND = 0x00, /* Connectable and scannable undirected advertising (default) */
	OHOS_BLE_ADV_DIRECT_IND_HIGH = 0x01, /* Connectable high duty cycle directed advertising */
	OHOS_BLE_ADV_SCAN_IND = 0x02, /* Scannable undirected advertising */
	OHOS_BLE_ADV_NONCONN_IND = 0x03, /* Non connectable undirected advertising */
	OHOS_BLE_ADV_DIRECT_IND_LOW  = 0x04, /* Connectable low duty cycle directed advertising */
} BleAdvType;

/* Local IO capability, shall be the same value defined in HCI Specification. */
typedef enum {
	OHOS_BLE_IO_CAP_OUT = 0x00, /* DisplayOnly */
	OHOS_BLE_IO_CAP_IO, /* DisplayYesNo */
	OHOS_BLE_IO_CAP_IN, /* KeyboardOnly */
	OHOS_BLE_IO_CAP_NONE, /* NoInputNoOutput */
	OHOS_BLE_IO_CAP_KBDISP, /* Keyboard display */
} BleIoCapMode;

typedef enum {
	OHOS_BLE_AUTH_NO_BOND = 0x00,
	OHOS_BLE_AUTH_BOND,
	OHOS_BLE_AUTH_REQ_MITM,
	OHOS_BLE_AUTH_REQ_SC_ONLY,
	OHOS_BLE_AUTH_REQ_SC_BOND,
	OHOS_BLE_AUTH_REQ_SC_MITM,
	OHOS_BLE_AUTH_REQ_SC_MITM_BOND
} BleAuthReqMode;

typedef enum {
	OHOS_BLE_FILTER_ACTION_ADD = 0x00,
	OHOS_BLE_FILTER_ACTION_DELETE,
	OHOS_BLE_FILTER_ACTION_CLEAR
} BleFilterActionType;

typedef enum {
	OHOS_BLE_ADV_ADDRESS_FILTER_MASK = 0x01,
	OHOS_BLE_SERVICE_DATA_CHANGE_FILTER_MASK = 0x02,
	OHOS_BLE_SERVICE_UUID_CHECK_MASK = 0x04,
	OHOS_BLE_SERVICE_SOLICITATION_UUID_CHECK_MASK = 0x08,
	OHOS_BLE_LOCAL_NAME_CHECK_MASK = 0x10,
	OHOS_BLE_MANUFACTURER_DATA_CHECK_MASK = 0x20,
	OHOS_BLE_SERVICE_DATA_CHECK_MASK = 0x40
} BleFilterSelectMask;

typedef enum {
	OHOS_BLE_FILTER_LOGIC_OR = 0x00,
	OHOS_BLE_FILTER_LOGIC_AND
} BleFilterLogicType;

typedef enum {
	OHOS_BLE_FILTER_IMMEDIATE_MODE = 0x00,
	OHOS_BLE_FILTER_ON_FOUND_MODE,
	OHOS_BLE_FILTER_BATCHED_MODE
} BleFilterDeliveryMode;

typedef enum {
	OHOS_BLE_ADV_ADDRESS_FILTER = 0x00,
	OHOS_BLE_SERVICE_DATA_CHANGE_FILTER,
	OHOS_BLE_SERVICE_UUID_CHECK_FILTER,
	OHOS_BLE_SERVICE_SOLICITATION_UUID_CHECK_FILTER,
	OHOS_BLE_LOCAL_NAME_CHECK_FILTER,
	OHOS_BLE_MANUFACTURER_DATA_CHECK_FILTER,
	OHOS_BLE_SERVICE_DATA_CHECK_FILTER
} BleFilterSelectType;

typedef enum {
	OHOS_BLE_FILTER_PUBLIC_ADDR = 0x00,
	OHOS_BLE_FILTER_RANDOM_ADDR
} BleFilterAddrType;

/* Ble scan type */
typedef enum {
	OHOS_BLE_SCAN_TYPE_PASSIVE = 0x00, /* Passive Scanning. No scan request PDUs shall be sent. */
	OHOS_BLE_SCAN_TYPE_ACTIVE, /* Active Scanning. Scan request PDUs may be sent. */
} BleScanType;

/* Scan filter policy, possible values of BleScanParams::scanFilterPolicy
   0-Accept all advertisement packets except directed advertising packets not addressed to this device (default);
   1-Accept only advertisement packets from devices where the advertiser's address is in the White list.
   Directed advertising packets which are not addressed for this device shall be ignored;
   2-Accept all undirected advertisement packets, and all directed advertising packets where the initiator address
   is a resolvable private address, and all directed advertising packets addressed to this device;
   3-Accept all undirected advertisement packets from devices where the advertiser's address is in the White list,
   and all directed advertising packets where the initiator address is a resolvable private address, and all
   directed advertising packets addressed to this device. */
typedef enum {
	OHOS_BLE_SCAN_FILTER_POLICY_ACCEPT_ALL = 0x00,
	OHOS_BLE_SCAN_FILTER_POLICY_ONLY_WHITE_LIST,
	OHOS_BLE_SCAN_FILTER_POLICY_ACCEPT_ALL_AND_RPA,
	OHOS_BLE_SCAN_FILTER_POLICY_ONLY_WHITE_LIST_AND_RPA
} BleScanFilterPolicy;

/* Extended Advertising Event Type, possible values of BtScanResultData::eventType */
typedef enum {
	OHOS_BLE_EVT_NON_CONNECTABLE_NON_SCANNABLE = 0x00, /* Extended Non-Connectable and Non-Scannable undirected */
	OHOS_BLE_EVT_NON_CONNECTABLE_NON_SCANNABLE_DIRECTED = 0x04, /* Extended NonConnectable and NonScannable directed */
	OHOS_BLE_EVT_CONNECTABLE = 0x01, /* Extended Connectable undirected */
	OHOS_BLE_EVT_CONNECTABLE_DIRECTED = 0x05, /* Extended Connectable directed */
	OHOS_BLE_EVT_SCANNABLE = 0x02, /* Extended Scannable undirected */
	OHOS_BLE_EVT_SCANNABLE_DIRECTED = 0x06, /* Extended Scannable directed */

	OHOS_BLE_EVT_LEGACY_NON_CONNECTABLE = 0x10, /* Legacy Non-Connectable undirected, ADV_NONCONN_IND */
	OHOS_BLE_EVT_LEGACY_SCANNABLE = 0x12, /* Legacy Scannable undirected, ADV_SCAN_IND */
	OHOS_BLE_EVT_LEGACY_CONNECTABLE = 0x13, /* Legacy Connectable & Scannable undirected, ADV_IND */
	OHOS_BLE_EVT_LEGACY_CONNECTABLE_DIRECTED = 0x15, /* Legacy Connectable directed, ADV_DIRECT_IND */
	OHOS_BLE_EVT_LEGACY_SCAN_RSP_TO_ADV_SCAN = 0x1A, /* Legacy SCAN_RSP to an ADV_SCAN_IND */
	OHOS_BLE_EVT_LEGACY_SCAN_RSP_TO_ADV = 0x1B, /* Legacy SCAN_RSP to an ADV_IND */
} BleScanResultEvtType;

/* Extended Advertising Data Status, possible values of BtScanResultData::dataStatus */
typedef enum {
	OHOS_BLE_DATA_COMPLETE = 0x00, /* Complete data or final trunck */
	OHOS_BLE_DATA_INCOMPLETE_MORE_TO_COME = 0x01, /* Incomplete data, more data to come */
	OHOS_BLE_DATA_INCOMPLETE_TRUNCATED = 0x02, /* Incomplete data, truncated, no more data to come */
} BleScanResultDataStatus;

/* Addr type of scan result, possible values of BtScanResultData::addrType */
typedef enum {
	OHOS_BLE_PUBLIC_DEVICE_ADDRESS = 0x00, /* Public Device Address */
	OHOS_BLE_RANDOM_DEVICE_ADDRESS = 0x01, /* Random Device Address */
	OHOS_BLE_PUBLIC_IDENTITY_ADDRESS = 0x02, /* Public Identity Address (corresponds to Resolved Private Address) */
	/* Random (static) Identity Address (corresponds to Resolved Private Address) */
	OHOS_BLE_RANDOM_STATIC_IDENTITY_ADDRESS = 0x03,
	OHOS_BLE_UNRESOLVABLE_RANDOM_DEVICE_ADDRESS = 0xFE,
	OHOS_BLE_NO_ADDRESS = 0xFF, /* No address provided (anonymous advertisement) */
} BleScanResultAddrType;

/* adv data */
typedef struct {
	unsigned short advLength;
	char *advData; /* advertising data */
	unsigned short scanRspLength;
	char *scanRspData; /* scan response data */
} BleConfigAdvData;

typedef struct {
	/* Minimum advertising interval for undirected and low duty cycle directed advertising. [N * 0.625ms] */
	int minInterval;
	/* Maximum advertising interval for undirected and low duty cycle directed advertising. [N * 0.625ms] */
	int maxInterval;
	BleAdvType advType;
	unsigned char ownAddrType; /* Ref. Core spec Version 5.2|Vol 4,Part E, HCI_LE_Set_Advertising_Parameters */
	unsigned char peerAddrType; /* Ref. Core spec Version 5.2|Vol 4,Part E, HCI_LE_Set_Advertising_Parameters */
	BdAddr peerAddr;
	int channelMap; /* channel used bit map, bit[0:2]->[37,38,39]. e.g. 0x01-only 37 used, 0x07-all used */
	BleAdvFilter advFilterPolicy;
	int txPower; /* dbm */
	int duration; /* duration for sending BLE ADV. [N * 10 ms] */
} BleAdvParams;

/* used to add or delete a filter specification or clear a filter list for onchip filtering */
typedef struct {
	unsigned char clientId; /* APP identifier */
	unsigned char action; /* BleFilterActionType, [0->add,1->delte,2->clear] */
	unsigned char filtIndex; /* Filter index 0 ~ max_filter */
	unsigned int featureSelection; /* BleFilterSelectMask, Bit masks for the selected features */
	unsigned int listLogicType; /* BleFilterLogicType, Logic operation for each feature selected in featureSelection */
	unsigned char filtLogicType; /* BleFilterLogicType */
	unsigned char rssiHighThres; /* [In dBm] ignore the advertiser if the signal is lower than rssiHighThres */
	unsigned char rssiLowThres; /* Valid only if delivery_mode is on_found [in dBm] */
	unsigned char deliveryMode; /* BleFilterDeliveryMode */
	/* Time for firmware to linger and collect additional advertisements before reporting.
	   (Valid only if deliveryMode is on_found)[in milliseconds] */
	unsigned int onFoundTimeout;
	/* If an advertisement, after being found, is not seen contiguously for the lost_timeout period,
	   it will be reported lost. (Valid only if deliveryMode is on_found)[in milliseconds] */
	unsigned int onLostTimeout;
	/* If an advertisement in onFound lingers in firmware for the onfound_timeout duration,
	   it will collect a few advertisements and the count is checked. If the count exceeds onFoundTimeoutCnt,
	   it's reported OnFound, immediately thereafter. Valid only if deliveryMode is on_found [count] */
	unsigned char onFoundTimeoutCnt;
	/* Total number of advertisers to track per filter. Valid only if delivery_mode is on_found [count] */
	unsigned int numOfTrackingEntries;
} BleAdvScanFilterParam;

typedef struct {
	unsigned char clientId; /* APP identifier */
	unsigned char action; /* BleFilterActionType, [0->add, 1->delte, 2->clear] */
	unsigned char filtType; /* BleFilterSelectType */
	unsigned char filtIndex; /* filter index */
	int manufacturerId; /* manufacturer id  */
	int manufacturerIdMask; /* the mask of manufacturer id */
	BtUuid *uuid; /* uuid, 128bit */
	BtUuid *uuidMask; /* mask of 128bit uuid */
	BdAddr *bdAddr; /* address, e.g. "AA:BB:CC:DD:EE:FF" */
	unsigned char addrType; /* BleFilterAddrType, [0->public, 1->random] */
	unsigned int dataLen; /* length of value */
	char *data; /* value */
	unsigned int maskLen; /* length of mask */
	char mask; /* mask */
} BleAdvScanFilterCondition;

/* BLE scan parameter */
typedef struct {
	/* Time interval from when the Controller started its last scan until it begins the subsequent scan.
	   [N=0xXX] Time = N * 0.625 ms */
	unsigned short scanInterval;
	/* Duration of the scan on the primary advertising physical channel. [N=0xXX] Time = N * 0.625 ms */
	unsigned short scanWindow;
	unsigned char scanType; /* one of BleScanType, [0->Passive, 1->Active] */
	unsigned char scanPhy; /* [0->LE 1M phy, 1->LE 2M phy, 2->LE Coded phy] */
	unsigned char scanFilterPolicy; /* one of BleScanFilterPolicy */
} BleScanParams;

typedef struct {
	unsigned char *advData;
	unsigned int advDataLen;
	unsigned char *rspData;
	unsigned int rspDataLen;
} StartAdvRawData;

typedef struct {
	unsigned char eventType; /* Advertising event type, one of BleScanResultEvtType */
	unsigned char dataStatus; /* Data status, one of BleScanResultDataStatus */
	unsigned char addrType; /* one of BleScanResultAddrType, except 0xFE */
	BdAddr addr;
	unsigned char primaryPhy; /* 0x01->LE 1M phy, 0x03->LE Coded phy */
	unsigned char secondaryPhy; /* 0x00->No packets, 0x01->LE 1M phy, 0x02->LE 2M phy, 0x03->LE Coded phy */
	/* Value of the Advertising SID subfield in the ADI field of the PDU or, for scan responses,
	   in the ADI field of the original scannable advertisement, 0xFF->No ADI field provided */
	unsigned char advSid;
	char txPower; /* Range: -127 to +20dBm, 0x7F->Tx Power information not available */
	char rssi; /* Range: -127 to +20dBm, 0x7F->RSSI is not available */
	/* Interval of the periodic advertising, Time = N * 1.25 ms, 0x0000->No periodic advertising */
	unsigned short periodicAdvInterval;
	unsigned char directAddrType; /* one of BleScanResultAddrType, except 0xFF */
	BdAddr directAddr; /* TargetA address for directed advertising event only */
	unsigned char advLen;
	unsigned char *advData;
} BtScanResultData;

/* Callback invoked when start adv operation has completed */
typedef void (*AdvEnableCallback)(int advId, int status);

/* Callback invoked when stop adv operation has completed */
typedef void (*AdvDisableCallback)(int advId, int status);

/* Callback invoked when adv instance data set operation has completed */
typedef void (*AdvDataCallback)(int advId, int status);

/* Callback invoked when adv param update operation has completed */
typedef void (*AdvUpdateCallback)(int advId, int status);

/* Callback invoked when security response operation has completed */
typedef void (*SecurityRespondCallback)(const BdAddr *bdAddr);

/* Callback for scan results */
typedef void (*ScanResultCallback)(BtScanResultData *scanResultdata);

/* Callback invoked when a scan filter enable/disable has completed */
typedef void (*ScanFilterStatusCallback)(int enable, int clientId, int status);

/* Callback invoked when a scan filter configuration command has completed */
typedef void (*ScanFilterCfgCallback)(int action, int clientId, int status, int filtType, int avblSpace);

/* Callback invoked when a scan filter param setup has completed */
typedef void (*ScanFilterParamCallback)(int action, int clientId, int status, int avblSpace);

/* Callback invoked when scan parameter set has completed */
typedef void (*ScanParameterSetCompletedCallback)(int clientId, int status);

typedef struct {
	AdvEnableCallback advEnableCb; /* start adv */
	AdvDisableCallback advDisableCb; /* stop adv */
	AdvDataCallback advDataCb;
	AdvUpdateCallback advUpdateCb; /* update adv */
	SecurityRespondCallback securityRespondCb;
	ScanResultCallback scanResultCb;
	ScanFilterCfgCallback scanFilterCfgCb;
	ScanFilterParamCallback scanFilterParamCb;
	ScanFilterStatusCallback scanFilterStatusCb;
	ScanParameterSetCompletedCallback scanParamSetCb;
} BtGattCallbacks;

/*
 * @brief Initialize the Bluetooth protocol stack
 * @param[in] void
 * @return 0-success, other-fail
 */
int InitBtStack(void);

/*
 * @brief Bluetooth protocol stack enable
 * @param[in] void
 * @return 0-success, other-fail
 */
int EnableBtStack(void);

/*
 * @brief Bluetooth protocol stack disable
 * @param[in] void
 * @return 0-success, other-fail
 */
int DisableBtStack(void);

/*
 * @brief set this device's name for friendly
 * @param[in] <name> device name
 * @param[in] <len> length
 * @return 0-success, other-fail
 */
int SetDeviceName(const char *name, unsigned int len);

/*
 * @brief set advertising data
 * @param[in] <advId> specified by upper layer
 * @param[in] <data> adv data or scan response
 * @return 0-success, other-fail
 */
int BleSetAdvData(int advId, const BleConfigAdvData *data);

/*
 * @brief start ble advertising
 * @param[in] <advId> specified by upper layer
 * @param[in] <param> ble advertising param list
 * @return 0-success, other-fail
 */
int BleStartAdv(int advId, const BleAdvParams *param);

/*
 * @brief stop ble advertising
 * @param[in] <advId> specified by upper layer
 * @return 0-success, other-fail
 */
int BleStopAdv(int advId);

/*
 * @Update the parameters as per spec, user manual specified values and restart multi ADV
 * @param[in] <advId> specified by upper layer
 * @param[in] <param> ble advertising param list
 * @return 0-success, other-fail
 */
int BleUpdateAdv(int advId, const BleAdvParams *param);

/*
 * @brief set security IO capability
 * @param[in] <mode> BleIoCapMode
 * @return 0-success, other-fail
 */
int BleSetSecurityIoCap(BleIoCapMode mode);

/*
 * @brief set security authority
 * @param[in] <mode> BleAuthReqMode
 * @return 0-success, other-fail
 */
int BleSetSecurityAuthReq(BleAuthReqMode mode);

/*
 * @brief The device accept or reject the connection initiator.
 * @param[in] <bdAddr> initiator's address
 * @param[in] <accept> 0-reject, 1-accept
 * @return 0-success, other-fail
 */
int BleGattSecurityRsp(BdAddr bdAddr, bool accept);

/*
 * @brief read bt mac address
 * @param[in] <mac> mac addr
 * @param[in] <len> addr length
 * @return 0-success, other-fail
 */
int ReadBtMacAddr(unsigned char *mac, unsigned int len);

/*
 * @brief Setup scan filter params
 * @param[in] <param> BleAdvScanFilterParam
 * @return 0-success, other-fail
 */
int BleScanFilterParamSetup(BleAdvScanFilterParam *param);

/*
 * @brief Configure a scan filter condition
 * @param[in] <param> BleAdvScanFilterCondition
 * @return 0-success, other-fail
 */
int BleScanFilterAddRemove(BleAdvScanFilterCondition *param);

/*
 * @brief Clear all scan filter conditions for specific filter index
 * @param[in] <clientId> client Id
 * @param[in] <filterIndex> filter index
 * @return 0-success, other-fail
 */
int BleScanFilterClear(int clientId, int filterIndex);

/*
 * @brief Enable / disable scan filter feature
 * @param[in] <clientId> client Id
 * @param[in] <enable> 0-disable, 1-enable
 * @return 0-success, other-fail
 */
int BleScanFilterEnable(int clientId, bool enable);

/*
 * @brief Set BLE scan parameters
 * @param[in] <clientId> client Id
 * @param[in] <param> BleScanParams, include scanInterval,scanWindow and so on.
 * @return 0-success, other-fail
 */
int BleSetScanParameters(int clientId, BleScanParams *param);

/*
 * @brief Start Ble scan
 * @return 0-success, other-fail
 */
int BleStartScan(void);

/*
 * @brief Stop Ble scan
 * @return 0-success, other-fail
 */
int BleStopScan(void);

/*
 * @brief Callback invoked for gatt common function
 * @param[in] <BtGattCallbacks> Callback funcs
 * @return 0-success, other-fail
 */
int BleGattRegisterCallbacks(BtGattCallbacks *func);

/*
 * @brief Start advertising include set adv data.
 * This API will not described in the development manual, only for Hilink.
 * @return 0-success, other-fail
 */
int BleStartAdvEx(int *advId, const StartAdvRawData rawData, BleAdvParams advParam);
#endif
