/*
 * Copyright (c) 2019 - 2020 IoT Company of Midea Group.
 *
 * File Name 		:
 * Description		: hal ble
 *
 * Version			: v0.0.1
 * Author			: Moore
 * Date				: 2020/03/14  refactoring
 * History			:
 */

#ifndef _MS_HAL_BLE_H_
#define _MS_HAL_BLE_H_

/**
 * !!! please see the config.mk to make sure your chip whether had those function !!!
 * MS_CONFIG_BLE_SUPPORT
 * !!! if not, do not adapter following interfaces
 */

#include "ms_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MS_CONFIG_BLE_SUPPORT

#define MS_HAL_BLE_HI_WORD(x)  ((uint8_t)((x & 0xFF00) >> 8))
#define MS_HAL_BLE_LO_WORD(x)  ((uint8_t)(x))

typedef enum {
	MS_HAL_BLE_STACK_EVENT_STACK_READY = 0,
	MS_HAL_BLE_STACK_EVENT_STACK_FAIL,
	MS_HAL_BLE_STACK_EVENT_ADV_ON,
	MS_HAL_BLE_STACK_EVENT_ADV_OFF,
	///@deprecated Use MS_HAL_BLE_STACK_EVENT_CONNECTION_REPORT
	MS_HAL_BLE_STACK_EVENT_PERIPHERAL_CONNECTED, //!< Bluetooth connected as peripheral
	///@deprecated Use MS_HAL_BLE_STACK_EVENT_CONNECTION_REPORT
	MS_HAL_BLE_STACK_EVENT_CENTRAL_CONNECTED,	//!< Bluetooth connected as central
	MS_HAL_BLE_STACK_EVENT_DISCONNECTED,		 //!< Bluetooth disconnect
	MS_HAL_BLE_STACK_EVENT_SCAN_ON,			  //!< ble scan start
	MS_HAL_BLE_STACK_EVENT_SCAN_OFF,			 //!< ble scan stops
	MS_HAL_BLE_STACK_EVENT_NONCONN_ADV_ON,	   //!< ble nonconn advertising start
	MS_HAL_BLE_STACK_EVENT_NONCONN_ADV_OFF,	  //!< ble nonconn advertising stops
	//Part 2
	MS_HAL_BLE_STACK_EVENT_NOTIFY_REQ,		   //!< ble notify data callback  //GATT_EVENT,Master get Ntf data form Slave
	MS_HAL_BLE_STACK_EVENT_INDICATE_REQ,		 //!< ble indicate data callback //GATT_REQ_EVENT,Master get Ind data form Slave
	MS_HAL_BLE_STACK_EVENT_DISC_SVC_REPORT,	  //!< discovery all service report
	MS_HAL_BLE_STACK_EVENT_DISC_CHAR_REPORT,	 //!< discovery all char report
	MS_HAL_BLE_STACK_EVENT_DISC_DESC_REPORT,	 //!< discovery all descriptor report
	MS_HAL_BLE_STACK_EVENT_MTU_CHANGED,		  //!< MTU changed callback
	MS_HAL_BLE_STACK_EVENT_CONNECTION_REPORT,	//!< Connection information
	MS_HAL_BLE_STACK_EVENT_CONNECT_PARAM_UPDATE_REQ,	//!< Connection information


	MS_HAL_BLE_STACK_EVENT_CMP = 0X80,		   //!< Complete event start ID, Do not use.
	MS_HAL_BLE_STACK_EVENT_CMP_MTU,			  //!< MTU change complete
	MS_HAL_BLE_STACK_EVENT_CMP_SVC_DISC,		 //!< discovery service done
	MS_HAL_BLE_STACK_EVENT_CMP_CHAR_DISC,		//!< discovery characteristic done
	MS_HAL_BLE_STACK_EVENT_CMP_DISC_DESC_CHAR,   //!< discover characteristic descriptor done
	MS_HAL_BLE_STACK_EVENT_CMP_WRITE_REQ,		//!< write request complete
	MS_HAL_BLE_STACK_EVENT_CMP_WRITE_CMD,		//!< write cmd complete
	MS_HAL_BLE_STACK_EVENT_CMP_NOTIFY,		   //!< Notify complete
	MS_HAL_BLE_STACK_EVENT_CMP_INDICATE,		 //!< Indicate complete
} ms_hal_ble_stack_event_t;

typedef struct {
	uint16_t conn_hdl;
	uint16_t att_hdl;
	uint16_t data_len;
	uint8_t *data;
} ms_hal_ble_gatt_msg_t;

typedef struct {
	uint16_t conn_hdl;
	uint16_t start_hdl;
	uint16_t end_hdl;
	uint8_t uuid_len;
	uint8_t *uuid;
} ms_hal_ble_disc_svc_msg_t;

typedef struct {
	uint16_t conn_hdl;
	uint16_t att_hdl;
	uint16_t pointer_hdl;
	uint8_t prop;
	uint8_t uuid_len;
	uint8_t *uuid;
} ms_hal_ble_disc_char_msg_t;

typedef struct {
	uint16_t conn_hdl;
	uint16_t att_hdl;
	uint8_t uuid_len;
	uint8_t *uuid;
} ms_hal_ble_disc_desc_msg_t;

typedef struct {
	uint16_t conn_hdl;
	uint16_t mtu;
} ms_hal_ble_mtu_changed_msg_t;

typedef struct {
	uint16_t conn_hdl;
	uint8_t *addr;
	uint16_t con_interval;
	uint16_t con_latency;
	uint16_t sup_timeout;
	uint8_t clk_accuracy;
	uint8_t peer_addr_type;
	uint8_t role;
} ms_hal_ble_connetion_msg_t;

typedef struct {
	uint16_t conn_hdl;
	uint8_t reason;
} ms_hal_ble_disconnect_msg_t;

typedef struct {
	uint16_t conn_hdl;
	uint16_t conn_intv_min;
	uint16_t conn_intv_max;
	uint16_t slave_latency;
	uint16_t timeout;
} ms_hal_ble_conn_param_msg_t;

typedef struct {
	ms_hal_ble_stack_event_t event_type;
	union {
		uint16_t conn_hdl;
		ms_hal_ble_gatt_msg_t gatt_msg;
		ms_hal_ble_disc_svc_msg_t disc_svc_msg;
		ms_hal_ble_disc_char_msg_t disc_char_msg;
		ms_hal_ble_disc_desc_msg_t disc_desc_msg;
		ms_hal_ble_mtu_changed_msg_t mtu_changed_msg;
		ms_hal_ble_connetion_msg_t connection_msg;
		ms_hal_ble_disconnect_msg_t disconnect_msg;
		ms_hal_ble_conn_param_msg_t conn_param_msg;
	} param;
} ms_hal_ble_stack_msg_t;

typedef int (*ms_hal_ble_stack_callback_t)(ms_hal_ble_stack_msg_t);

/**
 * @brief system interface, get module ble mac
 * @param[in/out] mac
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_get_mac_address(uint8_t *p_mac);

/**
 * @brief hal interface, start & update ble advertising
 * @param[in] adv_data
 * @param[in] adv_len
 * @param[in] rsp_date
 * @param[in] rsp_len
 * @return ms_hal_result_t
 * @note 1. if app connect device, please return false.
 *	   2. if will use this interface to update adv data, please check whether is support.
 *
 */
ms_hal_result_t ms_hal_ble_adv_start(uint8_t *adv_data, uint16_t adv_len, uint8_t *rsp_data, uint16_t rsp_len);

/**
 * @brief hal interface, stop ble advertising
 * @param void
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_adv_stop(void);

/**
 * @brief hal interface, get ble advertising status
 * @param void
 * @return on/off, 1:on, 0:off
 */
uint8_t ms_hal_ble_adv_status(void);

/**
 * @brief hal interface, get ble nonconn advertising status
 * @param void
 * @return on/off, 1:on, 0:off
 */
uint8_t ms_hal_ble_nonconn_adv_status(void);


/**
 * @brief hal interface, start ble stack
 * @param void
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_stack_start(void);

/**
 * @brief hal interface, stop ble stack
 * @param void
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_stack_stop(void);

/**
 * @brief hal interface, get ble stack status
 * @param void
 * @return on/off, 1:on, 0:off
 */
uint8_t ms_hal_ble_get_stack_status(void);


/**
 * @brief hal interface, set ble stack callback
 * @param ms_hal_ble_stack_callback_t
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_set_stack_event_register(ms_hal_ble_stack_callback_t event_handler);

/**
 * @brief hal interface, the point to ms_hal_ble_stack_callback function
 * @param ms_hal_ble_stack_event_t
 * @return int
 */
extern ms_hal_ble_stack_callback_t ms_hal_ble_stack_callback;

/**
 * @brief hal interface, set ble gap connect parameter
 * @param[in] *param
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_gap_connect_params(void *param);

/**
 * @brief hal interface, get ble gap connect status
 * @param [in] conn_hdl 链路句柄
 * @return IsConnect?, 1:had connected, 0:not connect
 */
uint8_t ms_hal_ble_gap_connect_status(uint16_t conn_hdl);

/**
 * @brief hal interface, set ble gap to disconnect
 * @param [in] conn_hdl 链路句柄
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_gap_disconnect(uint16_t conn_hdl);

/**
 * @brief hal interface, set ble mtu value
 * @param[in] *value
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_mtu_set(uint16_t value);

/**
 * @brief hal interface, get ble mtu value
 * @param [in] conn_hdl 链路句柄
 * @return mtu_value
 */
uint16_t ms_hal_ble_mtu_get(uint16_t conn_hdl);


/**
 * @brief hal interface, get ble scan status
 * @param void
 * @return on/off, on:1, off:0
 */
uint8_t ms_hal_ble_scan_status(void);

// UUID Service
// service +characteristic +charc_user_description +client_charc_config
typedef void (*ms_hal_ble_service_null_cb)(void);
typedef void (*ms_hal_ble_service_read_cb)(uint8_t *data, uint16_t size);
typedef void (*ms_hal_ble_service_write_cb)(uint8_t *data, uint16_t size);
typedef void (*ms_hal_ble_service_indicate_cb)(void);

#define MS_HAL_BLE_ATTRIB_CHAR_PROP_NONE				0x00
#define MS_HAL_BLE_ATTRIB_CHAR_PROP_BROADCAST		   0x01
#define MS_HAL_BLE_ATTRIB_CHAR_PROP_READ				0x02
#define MS_HAL_BLE_ATTRIB_CHAR_PROP_WRITE_NO_RSP		0x04
#define MS_HAL_BLE_ATTRIB_CHAR_PROP_WRITE			   0x08
#define MS_HAL_BLE_ATTRIB_CHAR_PROP_NOTIFY			  0x10
#define MS_HAL_BLE_ATTRIB_CHAR_PROP_INDICATE			0x20
#define MS_HAL_BLE_ATTRIB_CHAR_PROP_WRITE_AUTHEN_SIGNED 0x40
#define MS_HAL_BLE_ATTRIB_CHAR_PROP_EXT_PROP			0x80

#define MS_HAL_BLE_ATTRIB_PERM_NONE			  0x00
#define MS_HAL_BLE_ATTRIB_PERM_READ			  0x01
#define MS_HAL_BLE_ATTRIB_PERM_WRITE			 0x02
#define MS_HAL_BLE_ATTRIB_PERM_NOTIF_IND		 0x04

typedef enum _ms_hal_ble_uuid_type_ {
	ENUM_MS_HAL_BLE_UUID_TYPE_NULL = 0,
	ENUM_MS_HAL_BLE_UUID_TYPE_16_BIT,
	ENUM_MS_HAL_BLE_UUID_TYPE_128_bit,
} ms_hal_ble_uuid_type_t;

typedef enum _ms_hal_ble_attrib_type_ {
	ENUM_MS_HAL_BLE_ATTRIB_TYPE_SERVICE = 1,
	ENUM_MS_HAL_BLE_ATTRIB_TYPE_CHAR,
	ENUM_MS_HAL_BLE_ATTRIB_TYPE_CHAR_VALUE,
	ENUM_MS_HAL_BLE_ATTRIB_TYPE_CHAR_CLIENT_CONFIG,
	ENUM_MS_HAL_BLE_ATTRIB_TYPE_CHAR_USER_DESCR,
} ms_hal_ble_attrib_type_t;

typedef union _ms_hal_ble_attrib_callback_ {
	ms_hal_ble_service_null_cb null_cb;
	ms_hal_ble_service_read_cb read_cb;
	ms_hal_ble_service_write_cb write_cb;
	ms_hal_ble_service_indicate_cb indicate_cb;
} ms_hal_ble_attrib_callback_t;

typedef struct _ms_hal_ble_service_attrib_ {
	uint8_t att_type;
	uint8_t uuid_type;
	uint8_t uuid[2 + 14];
	uint8_t prop;
	uint16_t value_len;
	uint8_t *value_context;
	uint8_t perm;
	ms_hal_ble_attrib_callback_t callback;
} ms_hal_ble_service_attrib_t;

/**
 * att_type is service/characteristic/characteristic_value/char_client_config/char_user_descr, see ms_hal_ble_attrib_type_t
 * uuid_type : see ms_hal_ble_uuid_type_t
 * uuid : 16bit/128bit uuid
 * prop : if att_type is characteristic, you need to choose MS_HAL_BLE_ATTRIB_CHAR_PROP_XXX
 *		if att_type is characteristic_value, you need to check the last characteristic->prop
 * value_len : len of value_context
 * value_context : normal for char_user_descr
 * perm : you need to choose MS_HAL_BLE_ATTRIB_PERM_XXX
 */
typedef int ms_hal_ble_gatts_service_handle_t;

/**
 * @brief hal interface, add ble gatt service
 * @param[in] handle 服务句柄
 * @param[in] *attrib_database 属性（数组指针）
 * @param[in] attrib_database_count 属性个数
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_gatt_service_add(ms_hal_ble_gatts_service_handle_t *handle, ms_hal_ble_service_attrib_t **attrib_database,
		uint16_t attrib_database_count);

/**
 * @brief hal interface, send ble gatt data
 * @param[in] handle 服务句柄
 * @param[in] attrib_offset 属性偏移
 * @param[in] data 数据
 * @param[in] len 数据长度
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_gatt_data_send(uint16_t conn_hdl, ms_hal_ble_gatts_service_handle_t *handle, uint16_t attrib_offset, uint8_t *data, uint16_t len);


typedef struct {
	uint32_t					adv_intv_min;	   /// Minimum advertising interval (in unit of 625us). Must be greater than 20ms
	uint32_t					adv_intv_max;	   /// Maximum advertising interval (in unit of 625us). Must be greater than 20ms
} ms_hal_ble_gap_adv_params;


//广播不可连接广播包，不带[02 01 06]头，与之前广播包不一样
/**
 * @brief hal interface, start & update ble nonconn advertising
 * @param[in] adv_data
 * @param[in] adv_len
 * @return ms_hal_result_t
 * @note 1. if app connect device, please return false.
 *	   2. if will use this interface to update adv data, please check whether is support.
 *
 */
ms_hal_result_t ms_hal_ble_nonconn_adv_start(ms_hal_ble_gap_adv_params *param, uint8_t *adv_data, uint16_t adv_len);

/**
 * @brief hal interface, stop ble nonconn advertising
 * @param void
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_nonconn_adv_stop(void);




/*!
	@brief BLE ddress Type
*/

typedef enum {
	MS_HAL_BLE_ADDR_TYPE_PUBLIC = 0,			   ///< public address
	MS_HAL_BLE_ADDR_TYPE_RANDOM_STATIC = 1,		///< random static address
	MS_HAL_BLE_ADDR_TYPE_RANDOM_RESOLVABLE = 2,	///< random resolvable addresss
	MS_HAL_BLE_ADDR_TYPE_RANDOM_NON_RESOLVABLE = 3, ///< random non resolvable address
} ms_hal_ble_addr_type;

/*!
	@brief BLE address structure
*/
typedef struct {
	ms_hal_ble_addr_type addr_type;			 ///< address type.
	uint8_t				addr[6];						///< address byte array.
} ms_hal_ble_addr_t;


/*!
	@brief BLE Report Type
	The report type is for the scanned peers' type. It could be AD type of passive scan or active scan(SCAN_RSP).
	It was used in structure ble_gap_evt_adv_report_t.
*/
typedef enum {
	MS_HAL_BLE_REPORT_TYPE_IND = 0x00,				 ///< Type for ADV_IND found (passive)
	MS_HAL_BLE_REPORT_TYPE_DIRECT_IND = 0x01,		  ///< Type for ADV_DIRECT_IND found (passive)
	MS_HAL_BLE_REPORT_TYPE_SCAN_IND	= 0x02,		 ///< Type for ADV_SCAN_IND found (passive)
	MS_HAL_BLE_REPORT_TYPE_NONCONN_IND  = 0x03,		///< Type for ADV_NONCONN_IND found (passive)
	MS_HAL_BLE_REPORT_TYPE_SCAN_RSP = 0x04			 ///< Type for SCAN_RSP found (active)
} ms_hal_ble_report_type;


typedef struct {
	ms_hal_ble_report_type	 type;						   // report ad type
	ms_hal_ble_addr_t	 peer_addr;						   // peer addr
	int8_t				   tx_pwr;						   /// TX power (in dBm)
	int8_t					 rssi;						   // rssi
	uint16_t					len;						   //data len
	uint8_t				   *data;						   //data
} ms_hal_ble_scan_t;


//扫描回调
typedef void (*ms_hal_ble_scan_callback_t)(ms_hal_ble_scan_t *data);


/*!
	@brief BLE while listing.
*/
typedef struct {
	uint8_t				 addr_count;	///< device count
	ms_hal_ble_addr_t 		*p_addrs;	   ///< device address's array. Its size is equal to addr_count.
} ms_hal_ble_whitelist_t;


typedef enum {
	MS_HAL_BLE_SCAN_FP_ACCEPT_ALL						  = 0x00,  /**< Accept all advertising packets except directed advertising packets
																	not addressed to this device. */
	MS_HAL_BLE_SCAN_FP_WHITELIST						   = 0x01,  /**< Accept advertising packets from devices in the whitelist except directed
																	packets not addressed to this device. */
	MS_HAL_BLE_SCAN_FP_ALL_NOT_RESOLVED_DIRECTED		   = 0x02,  /**< Accept all advertising packets specified in @ref BLE_GAP_SCAN_FP_ACCEPT_ALL.
																	In addition, accept directed advertising packets, where the advertiser's
																	address is a resolvable private address that cannot be resolved. */
	MS_HAL_BLE_SCAN_FP_WHITELIST_NOT_RESOLVED_DIRECTED	 = 0x03,  /**< Accept all advertising packets specified in @ref BLE_GAP_SCAN_FP_WHITELIST.
																	In addition, accept directed advertising packets, where the advertiser's
																	address is a resolvable private address that cannot be resolved. */
} ms_hal_ble_scan_filter_policy_t;


typedef struct {
	bool									   active;				//scan active or passive
	bool							filter_duplicated;			  ///< Filter duplicated device
	ms_hal_ble_scan_filter_policy_t	 filter_policy;
	ms_hal_ble_whitelist_t 			  *p_whitelist;			  ///< Pointer to whitelist, NULL if no whitelist or the current active whitelist is to be used.
	uint16_t							   scan_intvl;			  ///< Scan interval between 0x0004 and 0x4000 in 0.625ms units (2.5ms to 10.24s).
	uint16_t							  scan_window;			  ///< Scan window between 0x0004 and 0x4000 in 0.625ms units (2.5ms to 10.24s).
} ms_hal_ble_scan_params_t;


/**
 * @brief hal interface, start ble scan
 * @param ms_hal_ble_scan_params_t
 * @param ms_hal_ble_scan_callback_t
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_scan_start(ms_hal_ble_scan_params_t *params, ms_hal_ble_scan_callback_t function);


/**
 * @brief hal interface, stop ble scan
 * @param void
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_scan_stop(void);

typedef struct {
	uint16_t conn_intv_min;
	uint16_t conn_intv_max;
	uint16_t slave_latency;
	uint16_t timeout;
} ms_hal_ble_conn_param_t;

/**
 * @brief hal interface, ms_hal_ble_discovery_all_service
 * @param[in] conn_hdl
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_discovery_all_service(uint16_t conn_hdl);

/**
 * @brief hal interface, ms_hal_ble_discovery_service_by_uuid
 * @param[in] conn_hdl
 * @param[in] uuid_size (2/16)
 * @param[in] uuid
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_discovery_service_by_uuid(uint16_t conn_hdl, uint8_t uuid_size, uint8_t *uuid);
/**
 * @brief hal interface, ms_hal_ble_discovery_all_char
 * @param[in] conn_hdl
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_discovery_all_char(uint16_t conn_hdl);

/**
 * @brief hal interface, ms_hal_ble_discovery_char_by_uuid
 * @param[in] conn_hdl
 * @param[in] start_hdl
 * @param[in] end_hdl
 * @param[in] uuid_len (2/16)
 * @param[in] uuid
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_discovery_char_by_uuid(uint16_t conn_hdl, uint16_t start_hdl, uint16_t end_hdl, uint8_t uuid_len, uint8_t *uuid);


/**
 * @brief hal interface, ms_hal_ble_discovery_all_descriptor
 * @param[in] conn_hdl
 * @param[in] start_hdl
 * @param[in] end_hdl
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_discovery_all_descriptor(uint16_t conn_hdl, uint16_t start_hdl, uint16_t end_hdl);

/**
 * @brief hal interface, ms_hal_ble_exchange_mtu
 * @param[in] conn_hdl
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_exchange_mtu(uint16_t conn_hdl);

/**
 * @brief hal interface, ms_hal_ble_set_cccd
 * @param[in] cccd_value  notify：0x0001 indicate: 0x0002
 * @param[in] conn_hdl	链路句柄
 * @param[in] att_handle  属性句柄
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_set_cccd(uint16_t cccd_value, uint16_t conn_hdl, uint16_t att_handle);

/**
 * @brief hal interface, ms_hal_ble_gatt_write
 * @param[in] type		0：write request 1: write cmd
 * @param[in] conn_hdl	链路句柄
 * @param[in] att_handle  属性句柄
 * @param[in] len  数据长度
 * @param[in] data 数据内容
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_gatt_write(uint8_t type, uint16_t conn_hdl, uint16_t att_handle, uint16_t len, uint8_t *data);

/**
 * @brief hal interface, ms_hal_ble_connect_param_update
 * @param[in] conn_hdl	链路句柄
 * @param[in] param	   连接参数
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_connect_param_update(uint16_t conn_hdl, ms_hal_ble_conn_param_t *param);

/**
 * @brief hal interface, ms_hal_ble_conn_start
 * @param[in] target		  对端Address
 * @param[in] own_addr_type   自身Address类型。GAPM_STATIC_ADDR、GAPM_GEN_RSLV_ADDR、GAPM_GEN_NON_RSLV_ADDR
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_conn_start(uint8_t *target, uint8_t own_addr_type);

/**
 * @brief hal interface, ms_hal_ble_conn_stop
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_conn_stop(void);

/**
 * @brief hal interface, ms_hal_ble_send_param_update_cfm
 * @param[in] conn_hdl		链路句柄
 * @param[in] accept		  true；接受参数更新 false:拒绝参数更新
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_send_param_update_cfm(uint16_t conn_hdl, bool accept);

/**
 * @brief hal interface, ms_hal_ble_set_device_name
 * @param[in] name		 设备名
 * @param[in] len		  名字长度
 * @return ms_hal_result_t
 */
ms_hal_result_t ms_hal_ble_set_device_name(uint8_t *name, uint8_t len);


#endif /* MS_CONFIG_BLE_SUPPORT */

#ifdef __cplusplus
}
#endif

#endif //__MS_HAL_BLE_H__
