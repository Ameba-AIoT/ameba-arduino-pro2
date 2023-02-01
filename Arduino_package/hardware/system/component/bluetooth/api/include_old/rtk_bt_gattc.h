/**
 * @file      rtk_bt_gattc.h
 * @author    benling_xu@realsil.com.cn
 * @brief     Bluetooth GATT client part type and function definition
 * @copyright Copyright (c) 2022. Realtek Semiconductor Corporation. All rights reserved.
 */

#ifndef __RTK_BT_GATTC_H__
#define __RTK_BT_GATTC_H__

#include <rtk_bt_defs.h>
#include <rtk_bt_gatt.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @struct    rtk_bt_gattc_app_id_t
 * @brief     Bluetooth GATT client app ID.
 */
typedef struct
{
	uint8_t conn_id;						/*!< Connection ID */
	uint8_t app_id;							/*!< APP ID */
} rtk_bt_gattc_app_id_t;

/**
 * @typedef   rtk_bt_gattc_subs_type_t
 * @brief     Bluetooth GATT client subscribe type.
 */
typedef enum
{
	NOTIFY   = 0x0001,						/*!< 0x0001 */
	INDICATE = 0x0002,						/*!< 0x0002 */
	BOTH     = 0x0003,						/*!< 0x0003 */
} rtk_bt_gattc_subs_type_t;

/**
 * @struct    rtk_bt_gattc_subs_param_t
 * @brief     Bluetooth GATT client subscribe paramter.
 */
typedef struct
{
	rtk_bt_gattc_app_id_t app;				/*!< GATT client APP */
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	uint16_t value_handle;					/*!< Subscribe value handle */
	uint16_t ccc_handle;					/*!< Subscribe CCC handle */
	rtk_bt_gattc_subs_type_t subs_type; 	/*!< Subscribe, for notify or indicate */
} rtk_bt_gattc_subs_param_t;

/**
 * @typedef   rtk_bt_gattc_unsubs_param_t
 * @brief     Bluetooth GATT client unsubscribe paramter.
 */
typedef rtk_bt_gattc_subs_param_t rtk_bt_gattc_unsubs_param_t;

/**
 * @typedef   rtk_bt_gattc_subs_param_t
 * @brief     Bluetooth GATT client discover type.
 */
typedef enum
{
	BT_GATT_DISCOVER_PRIMARY_ALL,			/*!< Discover all Primary services */
	BT_GATT_DISCOVER_PRIMARY_BY_UUID,		/*!< Discover Primary services By service UUID */
	BT_GATT_DISCOVER_INCLUDE,				/*!< Find included services */
	BT_GATT_DISCOVER_CHARACTERISTIC_ALL,	/*!< Discover all characteristic of a service */
	BT_GATT_DISCOVER_CHARACTERISTIC_BY_UUID,/*!< Discover characteristic by UUID */
	BT_GATT_DISCOVER_DESCRIPTORS_ALL,		/*!< Discover all characteristic descriptors */
} rtk_bt_gattc_discover_type_t;

/**
 * @struct    rtk_bt_gattc_discover_param_t
 * @brief     Bluetooth GATT client discover paramter for different Operation.
 */
typedef struct
{
	rtk_bt_gattc_app_id_t app;				/*!< GATT client APP */
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	rtk_bt_gattc_discover_type_t type;		/*!< Discover type */
/*
 * For doxygen generation ONLY! Must predefine BT_CONFIG_DOXYGEN.
 */
#if defined(BT_CONFIG_DOXYGEN)
	union gattc_discover_ops
#else
	union
#endif
	{
		struct disc_primary_all_param
		{
			uint8_t null;					/*!< just for Integrity */
		} disc_primary_all;					/*!< Discover All Primary Services */

		struct disc_primary_by_uuid_param
		{
			uint8_t uuid[BT_UUID_SIZE_MAX];	/*!< Discover UUID value, in little-endian format */
			rtk_bt_uuid_type_t uuid_type;	/*!< Discover UUID type */
		} disc_primary_by_uuid;				/*!< Discover Primary Service by Service UUID */

		struct disc_inc_param
		{
			uint16_t start_handle;			/*!< included service start handle */
			uint16_t end_handle;			/*!< included service end handle */
		} disc_inc;							/*!< Find Included Services */

		struct disc_char_all_param
		{
			uint16_t start_handle;			/*!< included service start handle */
			uint16_t end_handle;			/*!< included service end handle */
		} disc_char_all;					/*!< Discover All Characteristics of a Service */

		struct disc_char_by_uuid_param
		{
			uint16_t start_handle;			/*!< included service start handle */
			uint16_t end_handle;			/*!< included service end handle */
			uint8_t uuid[BT_UUID_SIZE_MAX];	/*!< Discover UUID value, in little-endian format */
			rtk_bt_uuid_type_t uuid_type;	/*!< Discover UUID type */
		} disc_char_by_uuid;				/*!< Discover Characteristics by UUID */

		struct disc_descriptor_param
		{
			uint16_t start_handle;			/*!< included service start handle */
			uint16_t end_handle;			/*!< included service end handle */
		} disc_descriptor;					/*!< Discover All Characteristic Descriptors */
	};										/*!< anonymous union member in rtk_bt_gattc_discover_param_t */
	
	uint8_t intern_flag;					/*!< For internal use, user no need to care it */
} rtk_bt_gattc_discover_param_t;

/**
 * @typedef   rtk_bt_gattc_read_type_t
 * @brief     Bluetooth GATT client read type.
 */
typedef enum
{
	BT_GATT_CHAR_READ_BY_HANDLE,			/*!< Read characteristic Value */
	BT_GATT_CHAR_READ_BY_UUID,				/*!< Read Using characteristic UUID */
	BT_GATT_CHAR_READ_MULTIPLE,				/*!< Read Multiple characteristic Values */
	BT_GATT_CHAR_READ_MULTIPLE_VARIABLE,	/*!< Read Multiple variable characteristic Values */
} rtk_bt_gattc_read_type_t;

/**
 * @struct    rtk_bt_gattc_read_param_t
 * @brief     Bluetooth GATT client read paramter.
 */
typedef struct
{
	rtk_bt_gattc_app_id_t app;				/*!< GATT client APP */
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	rtk_bt_gattc_read_type_t type;			/*!< attribute Value Read Type */
/*
 * For doxygen generation ONLY! Must predefine BT_CONFIG_DOXYGEN.
 */
#if defined(BT_CONFIG_DOXYGEN)
	union gattc_read_ops
#else
	union
#endif
	{
		struct by_handle_param
		{
			uint16_t handle;				/*!< attribute handle */
		} by_handle;						/*!< Read Characteristic Value */

		struct by_uuid_param
		{
			uint16_t start_handle;			/*!< First requested handle number */
			uint16_t end_handle;			/*!< Last requested handle number */
			uint8_t uuid[BT_UUID_SIZE_MAX];	/*!< 2 or 16 octet UUID */
			rtk_bt_uuid_type_t uuid_type;	/*!< Read UUID type */
		} by_uuid;							/*!< Read Using Characteristic UUID */

		struct multiple_param
		{
			uint32_t handle_count;			/*!< The Number of multiple handles are used */
			uint16_t *handles;				/*!< attribute handles array */
		} multiple;							/*!< Read Multiple Characteristic Values */

		struct multiple_variable_param
		{
			uint32_t handle_count;			/*!< The Number of multiple handles are used */
			uint16_t *handles;				/*!< attribute handles array */
		} multiple_variable;				/*!< Read Multiple Variable Length Characteristic Values */
	};										/*!< anonymous union member in rtk_bt_gattc_read_param_t */

	uint8_t intern_flag;					/*!< For internal use, user no need to care it */
} rtk_bt_gattc_read_param_t;

/**
 * @typedef   rtk_bt_gattc_write_type_t
 * @brief     Bluetooth GATT client write type.
 */
typedef enum
{
	BT_GATT_CHAR_WRITE_BY_HANDLE,			/*!< Write characteristic Value */
	BT_GATT_CHAR_WRITE_NO_RSP,				/*!< Write characteristic Value without response */
	BT_GATT_CHAR_WRITE_NO_RSP_SIGNED,		/*!< Write characteristic Value without response and with signed data. */
} rtk_bt_gattc_write_type_t;

/**
 * @struct    rtk_bt_gattc_write_param_t
 * @brief     Bluetooth GATT client write paramter.
 */
typedef struct
{
	rtk_bt_gattc_app_id_t app;				/*!< GATT client APP */
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	rtk_bt_gattc_write_type_t type;			/*!< characteristic write type */
	uint16_t handle;						/*!< attribute handle */
	uint16_t length;						/*!< Length of the data */
	const void *data;						/*!< Data to be written */
} rtk_bt_gattc_write_param_t;

/**
 * @struct    rtk_bt_gattc_cfm_param_t
 * @brief     Bluetooth GATT client confirm paramter.
 */
typedef struct
{
	rtk_bt_gattc_app_id_t app;				/*!< GATT client APP */
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
} rtk_bt_gattc_cfm_param_t;

/**
 * @typedef   rtk_bt_gattc_evt_code_t
 * @brief     Bluetooth GATTC event code definition.
 */
typedef enum
{
	RTK_BT_EVT_GATTC_MTU_EXCHANGE,			/*!< MTU exchange event */
	RTK_BT_EVT_GATTC_SUBSCRIBE,				/*!< Client subscribe results event */
	RTK_BT_EVT_GATTC_UNSUBSCRIBE,			/*!< Client unsubscribe results event */
	RTK_BT_EVT_GATTC_DISC_RESULT,			/*!< Client dicovery results event */
	RTK_BT_EVT_GATTC_READ_RESULT,			/*!< Client read results event */
	RTK_BT_EVT_GATTC_WRITE_RESULT,			/*!< Client write results event */
	RTK_BT_EVT_GATTC_INDICATE,				/*!< Indicate event from server */
	RTK_BT_EVT_GATTC_NOTIFY,				/*!< Notify event from server */
	RTK_BT_EVT_GATTC_CONFIRM,				/*!< Client confirm results event */
} rtk_bt_gattc_evt_code_t;

/**
 * @typedef   rtk_bt_gattc_status_t
 * @brief     Bluetooth GATTC event status type definition.
 */
typedef enum
{
	RTK_BT_GATTC_RES_CONTINUE,				/*!< Only for discover and read, when ack data not completed yet. */
	RTK_BT_GATTC_RES_DONE,					/*!< GATT client operation OK or ack data completed. */
	RTK_BT_GATTC_RES_ERR_LOCAL,				/*!< GATT client operation error, due to local misfunction. */
	RTK_BT_GATTC_RES_ERR_ROMOTE,			/*!< GATT client operation error, due to remote response. */
} rtk_bt_gattc_status_t;

/**
 * @struct    rtk_bt_gattc_res_ctrl_t
 * @brief     Bluetooth GATTC event result control definition.
 */
typedef struct
{
	rtk_bt_gattc_status_t status;			/*!< The status of this GATTC operation */
/*
 * For doxygen generation ONLY! Must predefine BT_CONFIG_DOXYGEN.
 */
#if defined(BT_CONFIG_DOXYGEN)
	union err_value
#else
	union
#endif
	{
		rtk_bt_evt_status_t err_local;		/*!< Local error code, if no error is 0. */
		uint16_t err_remote;				/*!< Remote error code, if no error is 0. */
	};										/*!< The error value of this GATTC operation */
	uint8_t has_data;						/*!< Is there any valid data after 'res_ctrl'. */
} rtk_bt_gattc_res_ctrl_t;

/**
 * @struct    rtk_bt_gattc_evt_common_t
 * @brief     A helper type for getting app id.
 */
typedef struct
{
	rtk_bt_gattc_app_id_t app;				/*!< GATT client APP */
} rtk_bt_gattc_evt_common_t;

/**
 * @struct    rtk_bt_gattc_evt_subscribe_res_t
 * @brief     Bluetooth GATTC event subscribe result definition.
 */
typedef struct
{
	rtk_bt_gattc_app_id_t app;				/*!< GATT client APP */
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	rtk_bt_gattc_res_ctrl_t res_ctrl;		/*!< GATTC results control */
	uint16_t value_handle;					/*!< Subscribe value handle */
	uint16_t ccc_handle;					/*!< Subscribe CCC handle */
	rtk_bt_gattc_subs_type_t subs_type;		/*!< Subscribe, for notify or indicate  */
} rtk_bt_gattc_evt_subscribe_res_t;

/**
 * @typedef   rtk_bt_gattc_evt_unsubscribe_res_t
 * @brief     Bluetooth GATTC event unsubscribe result definition.
 */
typedef rtk_bt_gattc_evt_subscribe_res_t rtk_bt_gattc_evt_unsubscribe_res_t;

/**
 * @struct    rtk_bt_gattc_evt_disc_res_t
 * @brief     Bluetooth GATTC event discover result definition.
 */
typedef struct
{
	rtk_bt_gattc_app_id_t app;				/*!< GATT client APP */
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	rtk_bt_gattc_discover_type_t type;		/*!< Discovery type */
	rtk_bt_gattc_res_ctrl_t res_ctrl;		/*!< GATTC results control */
/*
 * For doxygen generation ONLY! Must predefine BT_CONFIG_DOXYGEN.
 */
#if defined(BT_CONFIG_DOXYGEN)
	union gattc_evt_disc_res
#else
	union
#endif
	{
		struct disc_primary_all_per_param
		{
			uint16_t start_handle;			/*!< Primary service start handle */
			uint16_t end_handle;			/*!< Primary service end handle */
			rtk_bt_uuid_type_t uuid_type;	/*!< Primary service UUID type */
			uint8_t uuid[BT_UUID_SIZE_MAX];	/*!< Primary service UUID value, in little-endian format */
		} disc_primary_all_per;				/*!< Discover primary all services result (per attribute) */

		struct disc_primary_by_uuid_per_param
		{
			uint16_t start_handle;			/*!< Primary service start handle */
			uint16_t end_handle;			/*!< Primary service end handle */
		} disc_primary_by_uuid_per;			/*!< Discover primary services by service UUID result (per attribute) */

		struct disc_inc_per_param
		{
			uint16_t handle;				/*!< Include service declaration handle */
			uint16_t start_handle;			/*!< Include service start handle */
			uint16_t end_handle;			/*!< Include service end handle */
			rtk_bt_uuid_type_t uuid_type;	/*!< Include service UUID type */
			uint8_t uuid[BT_UUID_SIZE_MAX];	/*!< Include service UUID value, in little-endian format */
		} disc_inc_per;						/*!< Find included services result (per service) */

		struct disc_char_all_per_param
		{
			uint16_t handle;				/*!< Characteristic declaration handle */
			uint8_t properties;				/*!< Characteristic properties */
			uint16_t value_handle;			/*!< Characteristic value attribute handle */
			rtk_bt_uuid_type_t uuid_type;	/*!< Characteristic UUID type */
			uint8_t uuid[BT_UUID_SIZE_MAX];	/*!< Characteristic UUID value, in little-endian format */
		} disc_char_all_per;				/*!< Discover all characteristic of a service result (per attribute) */

		struct disc_char_by_uuid_per_param
		{
			uint16_t handle;				/*!< Characteristic declaration handle */
			uint8_t properties;				/*!< Characteristic properties */
			uint16_t value_handle;			/*!< Characteristic value attribute handle */
			rtk_bt_uuid_type_t uuid_type;	/*!< Characteristic UUID type */
			uint8_t uuid[BT_UUID_SIZE_MAX];	/*!< Characteristic UUID value, in little-endian format */
		} disc_char_by_uuid_per;			/*!< Discover characteristic by UUID result (per attribute) */

		struct disc_descriptor_per_param
		{
			uint16_t handle;				/*!< Characteristic descriptor attribute handle */
			rtk_bt_uuid_type_t uuid_type;	/*!< Characteristic descriptor UUID type */
			uint8_t uuid[BT_UUID_SIZE_MAX];	/*!< Characteristic descriptor UUID value, in little-endian format */
		} disc_descriptor_per;				/*!< Discover all characteristic descriptors result (per attribute) */
	};										/*!< anonymous union member in rtk_bt_gattc_evt_disc_res_t */
} rtk_bt_gattc_evt_disc_res_t;

/**
 * @struct    rtk_bt_gattc_evt_read_res_t
 * @brief     Bluetooth GATTC event read result definition.
 */
typedef struct
{
	rtk_bt_gattc_app_id_t app;				/*!< GATT client APP */
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	rtk_bt_gattc_read_type_t type;			/*!< Attribute Value Read Type */
	rtk_bt_gattc_res_ctrl_t res_ctrl;		/*!< GATTC results control */
/*
 * For doxygen generation ONLY! Must predefine BT_CONFIG_DOXYGEN.
 */
#if defined(BT_CONFIG_DOXYGEN)
	union gattc_evt_read_res
#else
	union
#endif
	{
		struct by_handle_res_param
		{
			uint16_t handle;				/*!< Attribute Value handle */
			uint16_t len;					/*!< The length of handle value */
			uint8_t *value;					/*!< Handle value */
		} by_handle;						/*!< Read Characteristic Value result */

		struct by_uuid_per_param
		{
			uint16_t handle;				/*!< Attribute Value handle */
			uint16_t len;					/*!< The length of handle value */
			uint8_t *value;					/*!< Handle value */
		} by_uuid_per;						/*!< Read Using Characteristic UUID result (per attribute) */

		struct multiple_per_param
		{
			uint16_t dummy;					/*!< Useless, just for padding, make the 4 union element the same memory structure */
			uint16_t len;					/*!< The length of handle value */
			uint8_t *value;					/*!< Handle value */
		} multiple_per;						/*!< Read Multiple Characteristic Values (per attribute) */

		struct multiple_variable_per_param
		{
			uint16_t dummy;					/*!< Useless, just for padding, make the 4 union element the same memory structure */
			uint16_t len;					/*!< The length of handle value */
			uint8_t *value;					/*!< Handle value */
		} multiple_variable_per;			/*!< Read Multiple Variable Length Characteristic Values (per attribute) */
	};										/*!< anonymous union member in rtk_bt_gattc_evt_read_res_t */
} rtk_bt_gattc_evt_read_res_t;

/**
 * @struct    rtk_bt_gattc_evt_write_res_t
 * @brief     Bluetooth GATTC event write result definition.
 */
typedef struct
{
	rtk_bt_gattc_app_id_t app;				/*!< GATT client APP */
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	rtk_bt_gattc_write_type_t type;			/*!< Attribute Value write Type */
	rtk_bt_gattc_res_ctrl_t res_ctrl;		/*!< GATTC results control */
} rtk_bt_gattc_evt_write_res_t;

/**
 * @struct    rtk_bt_gattc_evt_indicate_t
 * @brief     Bluetooth GATTC event indicate definition.
 */
typedef struct
{
	rtk_bt_gattc_app_id_t app;				/*!< GATT client APP */
	uint16_t handle;						/*!< Attribute Value handle */
	uint16_t len;							/*!< The length of handle value */
	uint8_t *value;							/*!< Handle value */
} rtk_bt_gattc_evt_indicate_t;

/**
 * @typedef   rtk_bt_gattc_evt_notify_t
 * @brief     Bluetooth GATTC event noitfy definition.
 */
typedef rtk_bt_gattc_evt_indicate_t rtk_bt_gattc_evt_notify_t;

/**
 * @struct    rtk_bt_gattc_evt_confirm_t
 * @brief     Bluetooth GATTC event confirm result definition.
 */
typedef struct
{
	rtk_bt_gattc_app_id_t app;				/*!< GATT client APP */
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	rtk_bt_evt_status_t err_local;			/*!< Error code, if no error is 0. */
} rtk_bt_gattc_evt_confirm_t;

/**
 * @struct    rtk_bt_gattc_evt_mtu_exchange_t
 * @brief     Bluetooth GATTC event mtu exchange result definition.
 */
typedef struct
{
	rtk_bt_gattc_app_id_t app;				/*!< GATT client APP */
	rtk_bt_gattc_res_ctrl_t res_ctrl;		/*!< GATTC results control, if OK, is RTK_BT_GATTC_RES_DONE */
	uint16_t mtu;							/*!< MTU size */
} rtk_bt_gattc_evt_mtu_exchange_t;

/**
 * @typedef   rtk_bt_gattc_cb_t
 * @brief     Bluetooth GATTC callback function pointer definition.
 * @param[in] event: The event type of this data
 * @param[in] data: GATT operation data
 */
typedef void (*rtk_bt_gattc_cb_t)(rtk_bt_gattc_evt_code_t event, void *data);

/**
 * @defgroup  bt_gattc BT GATT client APIs
 * @brief     BT GATT client related function APIs
 * @ingroup   BT_APIs
 * @{
 */

/**
 * @fn        rtk_bt_err_t rtk_bt_gattc_register_callback(rtk_bt_gattc_cb_t cb);
 * @brief     Register GATT client operation callback [SYNC].
 * @param[in] cb: Callback function
 * @return     
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_gattc_register_callback(rtk_bt_gattc_cb_t cb);

/**
 * @fn        rtk_bt_err_t rtk_bt_gattc_unregister_callback(void);
 * @brief     Unregister GATT client operation callback [SYNC].
 * @return     
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_gattc_unregister_callback(void);

/**
 * @fn        rtk_bt_err_t rtk_bt_gattc_register_app(rtk_bt_gattc_app_id_t *app);
 * @brief     Register GATT client APP [SYNC].
 * @param[in] app: Parameters to register APP
 * @return     
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_gattc_register_app(rtk_bt_gattc_app_id_t *app);

/**
 * @fn        rtk_bt_err_t rtk_bt_gattc_unregister_app(rtk_bt_gattc_app_id_t *app);
 * @brief     Unregister GATT client APP [SYNC].
 * @param[in] app: Parameters to unregister APP
 * @return    - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_gattc_unregister_app(rtk_bt_gattc_app_id_t *app);

/**
 * @fn        rtk_bt_err_t rtk_bt_gattc_app_subscribe(rtk_bt_gattc_subs_param_t *param);
 * @brief     Subscribe attribute Value notify/indicate [ASYNC].
 * @param[in] param: Subscribe parameters
 * @return     
 *            - RTK_BT_OK  : Succeed
 *             - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_gattc_app_subscribe(rtk_bt_gattc_subs_param_t *param);

/**
 * @fn        rtk_bt_err_t rtk_bt_gattc_app_unsubscribe(rtk_bt_gattc_unsubs_param_t *param)
 * @brief     Unsubscribe attribute Value notify/indicate[ASYNC].
 * @param[in] param: Unsubscribe parameters
 * @return     
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_gattc_app_unsubscribe(rtk_bt_gattc_unsubs_param_t *param);

/**
 * @fn        rtk_bt_err_t rtk_bt_gattc_discover(rtk_bt_gattc_discover_param_t *param)
 * @brief     GATT client Discovery operations [ASYNC].
 * @param[in] param: Pointer to GATT client Discovery parameters
 * @return     
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_gattc_discover(rtk_bt_gattc_discover_param_t *param);

/**
 * @fn        rtk_bt_err_t rtk_bt_gattc_read(rtk_bt_gattc_read_param_t *param)
 * @brief     GATT client Read operations [ASYNC].
 *
 * @param[in] param: Pointer to GATT client Read parameters
 *
 * @return     
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_gattc_read(rtk_bt_gattc_read_param_t *param);

/**
 * @fn        rtk_bt_err_t rtk_bt_gattc_write(rtk_bt_gattc_write_param_t *param)
 * @brief     GATT client Write operations [ASYNC].
 *
 * @param[in] param: Pointer to GATT client Write parameters
 *
 * @return     
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_gattc_write(rtk_bt_gattc_write_param_t *param);

/**
 * @fn        rtk_bt_err_t rtk_bt_gattc_confirm(rtk_bt_gattc_cfm_param_t *param)
 * @brief     GATT client confirm for server indicate [ASYNC].
 *
 * @param[in] param: Pointer to GATT client confirm parameters
 *
 * @return     
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_gattc_confirm(rtk_bt_gattc_cfm_param_t *param);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /*!< __RTK_BT_GATTC_H__ */
