/**
 * @file      rtk_bt_gatt.h
 * @author    benling_xu@realsil.com.cn
 * @brief     Bluetooth GATT client part type and function definition
 * @copyright Copyright (c) 2022. Realtek Semiconductor Corporation. All rights reserved.
 */

#ifndef __RTK_BT_GATTC_H__
#define __RTK_BT_GATTC_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <dlist.h>
#include <rtk_bt_att_defs.h>
#include <rtk_stack_config.h>

#define RTK_BT_GATTC_IF(_profile_id,_conn_id)				\
		(((_profile_id)<<16) | (_conn_id))					\

#define RTK_BT_GATTC_IF_PROFILE_ID(_val)					\
		(((_val) & 0xFF00) >> 16)							\

#define RTK_BT_GATTC_IF_CONN_ID(_val)						\
		((_val)&0x00FF)									\

typedef enum{
	RTK_BT_GATTC_DISC_REQ  = BIT0,
	RTK_BT_GATTC_READ_REQ  = BIT1,
	RTK_BT_GATTC_WRITE_REQ = BIT2,
	RTK_BT_GATTC_WRITE_CMD = BIT3,
	RTK_BT_GATTC_REGISTER_NOTIFY = BIT4,
	RTK_BT_GATTC_UNREGISTER_NOTIFY = BIT5,
	RTK_BT_GATTC_UNKNOWN = 0xFF,
}rtk_bt_gattc_req_type_t;

/**
 * @typedef   rtk_bt_gattc_discover_type_t
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
	uint16_t profile_id;					/*!< Profile ID */
	uint16_t conn_id;						/*!< Connection ID */
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	rtk_bt_gattc_discover_type_t type;		/*!< Discover type */

	union
	{
		struct disc_primary_all_param
		{
			uint8_t null;					/*!< just for Integrity */
		} disc_primary_all;					/*!< Discover All Primary Services */

		struct disc_primary_by_uuid_param
		{
			uint8_t uuid[16];				/*!< Discover UUID value, in little-endian format */
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
			uint8_t uuid[16];				/*!< Discover UUID value, in little-endian format */
			rtk_bt_uuid_type_t uuid_type;	/*!< Discover UUID type */
		} disc_char_by_uuid;				/*!< Discover Characteristics by UUID */

		struct disc_descriptor_param
		{
			uint16_t start_handle;			/*!< included service start handle */
			uint16_t end_handle;			/*!< included service end handle */
		} disc_descriptor;					/*!< Discover All Characteristic Descriptors */
	};										/*!< anonymous union member in rtk_bt_gattc_discover_param_t */
	
} rtk_bt_gattc_discover_param_t;

/**
 * @struct    rtk_bt_gattc_discover_ind_t
 * @brief     Bluetooth GATTC event discover result definition.
 */
typedef struct
{
	uint16_t conn_id;
	uint16_t profile_id;
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	rtk_bt_gattc_discover_type_t type;		/*!< Discovery type */
	uint8_t status;
	uint8_t has_data;
	union
	{
		struct disc_primary_all_per_param
		{
			uint16_t start_handle;			/*!< Primary service start handle */
			uint16_t end_handle;			/*!< Primary service end handle */
			rtk_bt_uuid_type_t uuid_type;	/*!< Primary service UUID type */
			uint8_t uuid[16];				/*!< Primary service UUID value, in little-endian format */
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
			uint8_t uuid[16];				/*!< Include service UUID value, in little-endian format */
		} disc_inc_per;						/*!< Find included services result (per service) */

		struct disc_char_all_per_param
		{
			uint16_t handle;				/*!< Characteristic declaration handle */
			uint8_t properties;				/*!< Characteristic properties */
			uint16_t value_handle;			/*!< Characteristic value attribute handle */
			rtk_bt_uuid_type_t uuid_type;	/*!< Characteristic UUID type */
			uint8_t uuid[16];				/*!< Characteristic UUID value, in little-endian format */
		} disc_char_all_per;				/*!< Discover all characteristic of a service result (per attribute) */

		struct disc_char_by_uuid_per_param
		{
			uint16_t handle;				/*!< Characteristic declaration handle */
			uint8_t properties;				/*!< Characteristic properties */
			uint16_t value_handle;			/*!< Characteristic value attribute handle */
			rtk_bt_uuid_type_t uuid_type;	/*!< Characteristic UUID type */
			uint8_t uuid[16];	/*!< Characteristic UUID value, in little-endian format */
		} disc_char_by_uuid_per;			/*!< Discover characteristic by UUID result (per attribute) */

		struct disc_descriptor_per_param
		{
			uint16_t handle;				/*!< Characteristic descriptor attribute handle */
			rtk_bt_uuid_type_t uuid_type;	/*!< Characteristic descriptor UUID type */
			uint8_t uuid[16];				/*!< Characteristic descriptor UUID value, in little-endian format */
		} disc_descriptor_per;				/*!< Discover all characteristic descriptors result (per attribute) */
	};										/*!< anonymous union member in rtk_bt_gattc_evt_disc_res_t */
} rtk_bt_gattc_discover_ind_t;

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
	uint16_t conn_id;
	uint16_t profile_id;
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	rtk_bt_gattc_read_type_t type;			/*!< attribute Value Read Type */
	union
	{
		struct by_handle_param
		{
			uint16_t handle;				/*!< attribute handle */
		} by_handle;						/*!< Read Characteristic Value */

		struct by_uuid_param
		{
			uint16_t start_handle;			/*!< First requested handle number */
			uint16_t end_handle;			/*!< Last requested handle number */
			uint8_t uuid[16];				/*!< 2 or 16 octet UUID */
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

} rtk_bt_gattc_read_param_t;

/**
 * @struct    rtk_bt_gattc_evt_read_res_t
 * @brief     Bluetooth GATTC event read result definition.
 */
typedef struct
{
	uint16_t conn_id;
	uint16_t profile_id;
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	rtk_bt_gattc_read_type_t type;			/*!< Attribute Value Read Type */
	uint8_t status;							/*!< GATTC results control */
	uint8_t has_data;
	union
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
} rtk_bt_gattc_read_ind_t;


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
	uint16_t conn_id;
	uint16_t profile_id;
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	rtk_bt_gattc_write_type_t type;			/*!< characteristic write type */
	uint16_t handle;						/*!< attribute handle */
	uint16_t length;						/*!< Length of the data */
	const void *data;						/*!< Data to be written */
} rtk_bt_gattc_write_param_t;

/**
 * @struct    rtk_bt_gattc_evt_write_res_t
 * @brief     Bluetooth GATTC event write result definition.
 */
typedef struct
{
	uint16_t conn_id;
	uint16_t profile_id;
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	rtk_bt_gattc_write_type_t type;			/*!< Attribute Value write Type */
	uint8_t status;
	uint8_t has_data;
} rtk_bt_gattc_write_ind_t;

typedef struct{
	uint16_t conn_id;
	uint16_t profile_id;
	uint16_t seq;
	bool bnotify;
	bool bindicate;
	bool bregister;
	uint16_t ccc_handle;
	uint16_t value_handle;
	uint16_t value;
}rtk_bt_gattc_register_notify_param_t;

typedef struct{
	uint16_t conn_id;
	uint16_t profile_id;
	uint16_t seq;
	uint8_t state;
	uint8_t has_data;
	uint16_t ccc_handle;
	uint16_t value_handle;
	uint16_t value;
}rtk_bt_gattc_register_notify_ind_t;


/**
 * @struct    rtk_bt_gattc_evt_indicate_t
 * @brief     Bluetooth GATTC event indicate definition.
 */
typedef struct
{
	uint16_t conn_id;
	uint16_t profile_id;
	uint16_t handle;						/*!< Attribute Value handle */
	uint16_t len;							/*!< The length of handle value */
	uint8_t *value;							/*!< Handle value */
} rtk_bt_gattc_notify_ind_t;




typedef struct{
	struct list_head list;
	uint16_t profile_id;
	uint16_t ccc_handle;
	uint16_t value_handle;
	uint16_t value;
	bool bnotify;
	bool bindicate;
}rtk_bt_gattc_notify_record_t;


typedef struct{
	struct list_head list;
	uint16_t conn_id;
	uint16_t profile_id;
	uint32_t req_type;
	uint32_t sub_req_type;
	uint32_t user_data;
	void * req_param;
}rtk_bt_gattc_req_t;

typedef struct{
	struct list_head list;
	uint16_t conn_id;
	struct list_head profile_list;
	void * profile_list_mutex;
	struct list_head handle_req_list;
	void * handle_req_list_mutex;
	struct list_head cccd_req_list;
	void *cccd_req_list_mutex;
	struct list_head notify_record_list;
	void *notify_record_list_mutex;
}rtk_bt_gattc_if_t;

typedef struct{
	struct list_head list;
	uint16_t profile_id;
}rtk_bt_gattc_profile_t;

typedef struct{
	struct list_head gattc_if_list;
	void * gattc_if_list_mutex;
	struct list_head gattc_pending_req_list;
	void * gattc_pending_req_list_mutex;
	uint16_t credits;
}rtk_bt_gattc_app_priv_t;


#ifdef __cplusplus
}
#endif

#endif /* __RTK_BT_GATTC_H__ */

