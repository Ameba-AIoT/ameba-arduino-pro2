/**
 * @file      rtk_bt_gatts.h
 * @author    benling_xu@realsil.com.cn
 * @brief     Bluetooth GATT server part type and function definition
 * @copyright Copyright (c) 2022. Realtek Semiconductor Corporation. All rights reserved.
 */

#ifndef __RTK_BT_GATTS_H__
#define __RTK_BT_GATTS_H__

#include <rtk_bt_defs.h>
#include <rtk_bt_gatt.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @def       BT_UUID_GATT_PRIMARY_VAL
 * @brief     GATT Primary Service UUID value
 */
#define BT_UUID_GATT_PRIMARY_VAL			0x2800

/**
 * @def       BT_UUID_GATT_PRIMARY
 * @brief     GATT Primary Service
 */
#define BT_UUID_GATT_PRIMARY \
	BT_UUID_DECLARE_16(BT_UUID_GATT_PRIMARY_VAL)

/**
 * @def       BT_UUID_GATT_SECONDARY_VAL
 * @brief     GATT Secondary Service UUID value
 */
#define BT_UUID_GATT_SECONDARY_VAL			0x2801

/**
 * @def       BT_UUID_GATT_SECONDARY
 * @brief     GATT Secondary Service
 */
#define BT_UUID_GATT_SECONDARY \
	BT_UUID_DECLARE_16(BT_UUID_GATT_SECONDARY_VAL)

/**
 * @def       BT_UUID_GATT_INCLUDE_VAL
 * @brief     GATT Include Service UUID value
 */
#define BT_UUID_GATT_INCLUDE_VAL			0x2802

/**
 * @def       BT_UUID_GATT_INCLUDE
 * @brief     GATT Include Service
 */
#define BT_UUID_GATT_INCLUDE \
	BT_UUID_DECLARE_16(BT_UUID_GATT_INCLUDE_VAL)

/**
 * @def       BT_UUID_GATT_CHRC_VAL
 * @brief     GATT Characteristic UUID value
 */
#define BT_UUID_GATT_CHRC_VAL				0x2803

/**
 * @def       BT_UUID_GATT_CHRC
 * @brief     GATT Characteristic
 */
#define BT_UUID_GATT_CHRC \
	BT_UUID_DECLARE_16(BT_UUID_GATT_CHRC_VAL)

/**
 * @def       BT_UUID_GATT_CEP_VAL
 * @brief     GATT Characteristic Extended Properties UUID value
 */
#define BT_UUID_GATT_CEP_VAL				0x2900

/**
 * @def       BT_UUID_GATT_CEP
 * @brief     GATT Characteristic Extended Properties
 */
#define BT_UUID_GATT_CEP \
	BT_UUID_DECLARE_16(BT_UUID_GATT_CEP_VAL)

/**
 * @def       BT_UUID_GATT_CUD_VAL
 * @brief     GATT Characteristic User Description UUID value
 */
#define BT_UUID_GATT_CUD_VAL				0x2901

/**
 * @def       BT_UUID_GATT_CUD
 * @brief     GATT Characteristic User Description
 */
#define BT_UUID_GATT_CUD \
	BT_UUID_DECLARE_16(BT_UUID_GATT_CUD_VAL)

/**
 * @def       BT_UUID_GATT_CCC_VAL
 * @brief     GATT Client Characteristic Configuration UUID value
 */
#define BT_UUID_GATT_CCC_VAL				0x2902

/**
 * @def       BT_UUID_GATT_CCC
 * @brief     GATT Client Characteristic Configuration
 */
#define BT_UUID_GATT_CCC \
	BT_UUID_DECLARE_16(BT_UUID_GATT_CCC_VAL)

/**
 * @def       BT_UUID_GATT_SCC_VAL
 * @brief     GATT Server Characteristic Configuration UUID value
 */
#define BT_UUID_GATT_SCC_VAL 				0x2903

/**
 * @def       BT_UUID_GATT_SCC
 * @brief     GATT Server Characteristic Configuration
 */
#define BT_UUID_GATT_SCC \
	BT_UUID_DECLARE_16(BT_UUID_GATT_SCC_VAL)

/**
 * @def       BT_UUID_GATT_CPF_VAL
 * @brief     GATT Characteristic Presentation Format UUID value
 */
#define BT_UUID_GATT_CPF_VAL				0x2904

/**
 * @def       BT_UUID_GATT_CPF
 * @brief     GATT Characteristic Presentation Format
 */
#define BT_UUID_GATT_CPF \
	BT_UUID_DECLARE_16(BT_UUID_GATT_CPF_VAL)

/**
 * @def       BT_UUID_GATT_CAF_VAL
 * @brief     GATT Characteristic Aggregated Format UUID value
 */
#define BT_UUID_GATT_CAF_VAL 				0x2905

/**
 * @def       BT_UUID_GATT_CAF
 * @brief     GATT Characteristic Aggregated Format
 */
#define BT_UUID_GATT_CAF \
	BT_UUID_DECLARE_16(BT_UUID_GATT_CAF_VAL)

/**
 * @def       RTK_BT_GATT_CHRC_BROADCAST
 * @brief     Characteristic broadcast property.
 *            If set, permits broadcasts of the Characteristic Value using Server
 *            Characteristic Configuration Descriptor.
 */
#define RTK_BT_GATT_CHRC_BROADCAST			0x01

/**
 * @def       RTK_BT_GATT_CHRC_READ
 * @brief     Characteristic read property.
 *            If set, permits reads of the Characteristic Value.
 */
#define RTK_BT_GATT_CHRC_READ				0x02

/**
 * @def       RTK_BT_GATT_CHRC_WRITE_WITHOUT_RESP
 * @brief     Characteristic write without response property.
 *            If set, permits write of the Characteristic Value without response.
 */
#define RTK_BT_GATT_CHRC_WRITE_WITHOUT_RESP	0x04

/**
 * @def       RTK_BT_GATT_CHRC_WRITE
 * @brief     Characteristic write with response property.
 *            If set, permits write of the Characteristic Value with response.
 */
#define RTK_BT_GATT_CHRC_WRITE				0x08

/**
 * @def       RTK_BT_GATT_CHRC_NOTIFY
 * @brief     Characteristic notify property.
 *            If set, permits notifications of a Characteristic Value without acknowledgment.
 */
#define RTK_BT_GATT_CHRC_NOTIFY				0x10

/**
 * @def       RTK_BT_GATT_CHRC_INDICATE
 * @brief     Characteristic indicate property.
 *            If set, permits indications of a Characteristic Value with acknowledgment.
 */
#define RTK_BT_GATT_CHRC_INDICATE			0x20

/**
 * @def       RTK_BT_GATT_CHRC_AUTH
 * @brief     Characteristic Authenticated Signed Writes property.
 *            If set, permits signed writes to the Characteristic Value.
 */
#define RTK_BT_GATT_CHRC_AUTH				0x40

/**
 * @def   	  RTK_BT_GATT_CHRC_EXT_PROP
 * @brief     Characteristic Extended Properties property.
 *            If set, additional characteristic properties are defined in the
 *            Characteristic Extended Properties Descriptor.
 */
#define RTK_BT_GATT_CHRC_EXT_PROP			0x80

/**
 * @enum  attr_perm_t
 * @brief GATT attribute permission bit field values.
 */
enum attr_perm_t
{
	RTK_BT_GATT_PERM_NONE          = 0,		/*!< No operations supported, e.g. for notify-only */
	RTK_BT_GATT_PERM_READ          = BIT(0),/*!< Attribute read permission. */
	RTK_BT_GATT_PERM_WRITE         = BIT(1),/*!< Attribute write permission. */
	RTK_BT_GATT_PERM_READ_ENCRYPT  = BIT(2),/*!< Attribute read permission with encryption.*/
	RTK_BT_GATT_PERM_WRITE_ENCRYPT = BIT(3),/*!< Attribute write permission with encryption. */
	RTK_BT_GATT_PERM_READ_AUTHEN   = BIT(4),/*!< Attribute read permission with authentication. */
	RTK_BT_GATT_PERM_WRITE_AUTHEN  = BIT(5),/*!< Attribute write permission with authentication. */
	RTK_BT_GATT_PERM_PREPARE_WRITE = BIT(6),/*!< Attribute prepare write permission. */
};

/**
 * @def   	  RTK_BT_GATT_FLAG_INTERNAL
 * @brief     This attribute will be handle internally (Only in BT stack).
 */
#define RTK_BT_GATT_INTERNAL                0

/**
 * @def   	  RTK_BT_GATT_FLAG_APP
 * @brief     This attribute will be handle by User APP (ALL read/write will have a callback).
 */
#define RTK_BT_GATT_APP                     1

/**
 * @struct    rtk_bt_gatt_attr
 * @brief     GATT Attribute structure.
 */
struct rtk_bt_gatt_attr
{
	const struct bt_uuid *uuid;				/*!< Attribute UUID */
/*
 * For doxygen generation ONLY! Must predefine BT_CONFIG_DOXYGEN.
 */
#if defined(BT_CONFIG_DOXYGEN)
	union multiplex_1						/*!< multiplex_1 */
#else
	union
#endif
	{
		void* read;							/*!< Attribute read callback */
		uint16_t flag;						/*!< Attribute flag (RTK_BT_GATT_INTERNAL/RTK_BT_GATT_APP) */
	};
#if defined(BT_CONFIG_DOXYGEN)
	union multiplex_2						/*!< multiplex_2 */
#else
	union
#endif
	{
		void* write;						/*!< Attribute write callback */
		uint16_t len;						/*!< Attribute user data length */
	};
	void *user_data;						/*!< Attribute user data */
	uint16_t handle;						/*!< Attribute handle */
	uint8_t perm;							/*!< Attribute permissions */
};

/**
 * @struct    rtk_bt_gatt_service
 * @brief     GATT Service structure.
 */
struct rtk_bt_gatt_service
{
	struct rtk_bt_gatt_attr *attrs;			/*!< Service Attributes */
	size_t attr_count;						/*!< Service Attribute count */
	/**
	 * @struct    _snode
	 */
	struct _snode
	{
		struct _snode *next;				/*!< next node */
	} node;									/*!< Service Attribute node */
};

/**
 * @struct    rtk_bt_gatt_incl
 * @brief     Service that need to be included in Included Service.
 */
struct rtk_bt_gatt_incl
{
	uint8_t service_id;
	uint8_t attr_num;
	// struct rtk_bt_gatt_service *service;
};

/**
 * @struct    rtk_bt_gatt_chrc
 * @brief     Characteristic Attribute Value.
 */
struct rtk_bt_gatt_chrc
{
	const struct bt_uuid *uuid;				/*!< Characteristic UUID. */
	uint16_t value_handle;					/*!< Characteristic Value handle. */
	uint8_t	properties;						/*!< Characteristic properties. */
};

/**
 * @struct    rtk_bt_gatt_cep
 * @brief     Characteristic Extended Properties Attribute Value.
 */
struct rtk_bt_gatt_cep
{
	uint16_t properties;					/*!< Characteristic Extended properties */
};

/**
 * @def       RTK_BT_GATT_CCC_NOTIFY
 * @brief     Client Characteristic Configuration Notification.
 *            If set, changes to Characteristic Value shall be notified.
 */
#define RTK_BT_GATT_CCC_NOTIFY				0x0001

/**
 * @def       RTK_BT_GATT_CCC_INDICATE
 * @brief     Client Characteristic Configuration Indication.
 *            If set, changes to Characteristic Value shall be indicated.
 */
#define RTK_BT_GATT_CCC_INDICATE			0x0002

/**
 * @struct    bt_gatt_ccc
 * @brief     Client Characteristic Configuration Attribute Value.
 */
struct bt_gatt_ccc
{
	uint16_t flags;							/*!< Client Characteristic Configuration flags */
};

/**
 * @def RTK_BT_GATT_SCC_BROADCAST
 * @brief Server Characteristic Configuration Broadcast
 *        If set, the characteristic value shall be broadcast in the advertising data
 *        when the server is advertising.
 */
#define RTK_BT_GATT_SCC_BROADCAST			0x0001

/**
 * @struct    rtk_bt_gatt_scc
 * @brief     Server Characterestic Configuration Attribute Value.
 */
struct rtk_bt_gatt_scc
{
	uint16_t flags;							/*!< Server Characteristic Configuration flags */
};

/**
 * @struct    rtk_bt_gatt_cpf
 * @brief     GATT Characteristic Presentation Format Attribute Value.
 */
struct rtk_bt_gatt_cpf
{
	uint8_t format;							/*!< Format of the value of the characteristic */
	int8_t exponent;						/*!< Exponent field to determine how the value of this characteristic is further formatted */
	uint16_t unit;							/*!< Unit of the characteristic */
	uint8_t name_space;						/*!< Name space of the description */
	uint16_t description;					/*!< Description of the characteristic as defined in a higher layer profile */
};

/**
 * @struct    rtk_bt_gatt_caf
 * @brief     GATT Characteristic Aggregate Format Attribute Value.
 */
struct rtk_bt_gatt_caf
{
	uint16_t count;							/*!< The count of List of Attribute Handles */
	uint16_t* handles;						/*!< List of Attribute Handles */
};

/**
 * @def       RTK_BT_GATT_ATTRIBUTE
 * @brief     Declaration Macro.
 *            Helper macro to declare an attribute.
 * @param     _uuid Attribute uuid.
 * @param     _perm Attribute access permissions.
 * @param     _user_data Attribute user data.
 * @param     _len Attribute user data length.
 * @param     _flag Attribute flag.
 */
#define RTK_BT_GATT_ATTRIBUTE(_uuid, _perm, _user_data, _len, _flag) \
	{                                                                \
		.uuid = _uuid,                                               \
		.perm = _perm,                                               \
		.user_data = (void*)_user_data,                              \
		.len = _len,                                                 \
		.flag = _flag,                                               \
	}

/**
 * @def       RTK_BT_GATT_PRIMARY_SERVICE
 * @brief     Primary Service Declaration Macro.
 *            Helper macro to declare a primary service attribute.
 * @param     _service Service attribute value. (struct bt_uuid *)
 */
#define RTK_BT_GATT_PRIMARY_SERVICE(_service)                          \
	RTK_BT_GATT_ATTRIBUTE(BT_UUID_GATT_PRIMARY, RTK_BT_GATT_PERM_READ, \
						  _service, 0, RTK_BT_GATT_INTERNAL)

/**
 * @def       RTK_BT_GATT_SECONDARY_SERVICE
 * @brief     Secondary Service Declaration Macro.
 *            Helper macro to declare a secondary service attribute.
 * @param     _service Service attribute value. (struct bt_uuid *)
 */
#define RTK_BT_GATT_SECONDARY_SERVICE(_service)                          \
	RTK_BT_GATT_ATTRIBUTE(BT_UUID_GATT_SECONDARY, RTK_BT_GATT_PERM_READ, \
						  _service, 0, RTK_BT_GATT_INTERNAL)

/**
 * @def       RTK_BT_GATT_INCLUDE_SERVICE
 * @brief     Include Service Declaration Macro.
 *            Helper macro to declare database internal include service attribute.
 * @param     _service_incl Pointer to a struct rtk_bt_gatt_incl (struct rtk_bt_gatt_incl *)
 */
#define RTK_BT_GATT_INCLUDE_SERVICE(_service_incl)                     \
	RTK_BT_GATT_ATTRIBUTE(BT_UUID_GATT_INCLUDE, RTK_BT_GATT_PERM_READ, \
						  _service_incl, 0, RTK_BT_GATT_INTERNAL)

/**
 * @def       RTK_BT_GATT_CHRC_INIT
 * @brief     Initialization Macro.
 *            Helper macro to init an attribute.
 * @param     _uuid Attribute uuid.
 * @param     _handle Attribute handle.
 * @param     _props Attribute access properties.
 */
#define RTK_BT_GATT_CHRC_INIT(_uuid, _handle, _props) \
	{                                                 \
		.uuid = _uuid,                                \
		.value_handle = _handle,                      \
		.properties = _props,                         \
	}

/**
 * @def       RTK_BT_GATT_CHARACTERISTIC
 * @brief     Characteristic and Value Declaration Macro.
 *            Helper macro to declare a characteristic attribute along with its
 *            attribute value.
 * @param     _uuid Characteristic attribute uuid.
 * @param     _props Characteristic attribute properties.
 * @param     _perm Characteristic Attribute access permissions.
 */
#define RTK_BT_GATT_CHARACTERISTIC(_uuid, _props, _perm)                \
	RTK_BT_GATT_ATTRIBUTE(BT_UUID_GATT_CHRC, RTK_BT_GATT_PERM_READ,     \
						  ((struct rtk_bt_gatt_chrc[]){                 \
							  RTK_BT_GATT_CHRC_INIT(_uuid, 0U, _props), \
						  }), 0, RTK_BT_GATT_INTERNAL),                 \
	RTK_BT_GATT_ATTRIBUTE(_uuid, _perm, NULL, 0, RTK_BT_GATT_APP)

/**
 * @def       RTK_BT_GATT_DESCRIPTOR
 * @brief     Descriptor Declaration Macro.
 *            Helper macro to declare a descriptor attribute.
 * @note      If use RTK_BT_GATT_DESCRIPTOR directly, MUST use _user_data as a raw data!
 * @param     _uuid Descriptor attribute uuid.
 * @param     _perm Descriptor attribute access permissions.
 * @param     _user_data Descriptor attribute user data.
 * @param     _len Attribute user data length.
 * @param     _flag Attribute flag.
 */
#define RTK_BT_GATT_DESCRIPTOR(_uuid, _perm, _user_data, _len, _flag) \
	RTK_BT_GATT_ATTRIBUTE(_uuid, _perm, _user_data, _len, _flag)

/**
 * @def       RTK_BT_GATT_CEP
 * @brief     Characteristic Extended Properties Declaration Macro.
 *            Helper macro to declare a CEP attribute.
 * @param     _value Pointer to a struct rtk_bt_gatt_cep. (const struct rtk_bt_gatt_cep *)
 */
#define RTK_BT_GATT_CEP(_value) \
	RTK_BT_GATT_DESCRIPTOR(BT_UUID_GATT_CEP, RTK_BT_GATT_PERM_READ, (void *)_value, 0, RTK_BT_GATT_INTERNAL)

/**
 * @def       RTK_BT_GATT_CUD
 * @brief     Characteristic User Format Descriptor Declaration Macro.
 *            Helper macro to declare a CUD attribute.
 *
 * @param     _value User description NULL-terminated C string. (const uint8_t *value)
 * @param     _perm Descriptor attribute access permissions.
 */
#define RTK_BT_GATT_CUD(_value, _perm) \
	RTK_BT_GATT_DESCRIPTOR(BT_UUID_GATT_CUD, _perm, (void *)_value, 0, RTK_BT_GATT_INTERNAL)

/**
 * @def       RTK_BT_GATT_CCC
 * @brief     Client Characteristic Configuration Declaration Macro.
 *            Helper macro to declare a CCC attribute.
 * @note      Although CCCD value read/write will be handled internally, but User APP will be notified
 * @param     _perm CCC access permissions.
 */
#define RTK_BT_GATT_CCC(_perm) \
	RTK_BT_GATT_DESCRIPTOR(BT_UUID_GATT_CCC, _perm, 0, 0, RTK_BT_GATT_INTERNAL)

/**
 * @def       RTK_BT_GATT_SCC
 * @brief     Server Characteristic Configuration Declaration Macro.
 *            Helper macro to declare a CCC attribute.
 * @param     _value Poniter to Server Characteristic Configuration bits. (struct rtk_bt_gatt_scc *)
 * @param     _perm CCC access permissions.
 */
#define RTK_BT_GATT_SCC(_value, _perm) \
	RTK_BT_GATT_DESCRIPTOR(BT_UUID_GATT_SCC, _perm, (void *)_value, 0, RTK_BT_GATT_INTERNAL)

/**
 * @def       RTK_BT_GATT_CPF
 * @brief     Characteristic Presentation Format Descriptor Declaration Macro.
 *            Helper macro to declare a CPF attribute.
 * @param     _value Pointer to a struct rtk_bt_gatt_cpf. (struct rtk_bt_gatt_cpf*)
 */
#define RTK_BT_GATT_CPF(_value) \
	RTK_BT_GATT_DESCRIPTOR(BT_UUID_GATT_CPF, RTK_BT_GATT_PERM_READ, (void *)_value, 0, RTK_BT_GATT_INTERNAL)

/**
 * @def       RTK_BT_GATT_CAF
 * @brief     Characteristic Aggregate Format Descriptor Declaration Macro.
 *            Helper macro to declare a CAF attribute.
 * @param     _value Pointer to a struct rtk_bt_gatt_caf. (struct rtk_bt_gatt_caf*)
 */
#define RTK_BT_GATT_CAF(_value) \
	RTK_BT_GATT_DESCRIPTOR(BT_UUID_GATT_CAF, RTK_BT_GATT_PERM_READ, (void *)_value, 0, RTK_BT_GATT_INTERNAL)

/**
 * @def       RTK_BT_GATT_SERVICE
 * @brief     Service Structure Declaration Macro.
 *            Helper macro to declare a service structure.
 * @param     _attrs Service attributes.
 */
#define RTK_BT_GATT_SERVICE(_attrs)                           \
	{                                                         \
		.attrs = _attrs,                                      \
		.attr_count = (sizeof(_attrs) / sizeof((_attrs)[0])), \
	}

/**
 * @def       RTK_BT_GATT_SERVICE_DEFINE
 * @brief     Statically define and register a service.
 *            Helper macro to statically define and register a service.
 * @param     _name Service name.
 */
#define RTK_BT_GATT_SERVICE_DEFINE(_name, ...)                    \
	const struct rtk_bt_gatt_attr attr_##_name[] = {__VA_ARGS__}; \
	const rtk_bt_gatt_service_static, _name = RTK_BT_GATT_SERVICE(attr_##_name)

/**
 * @typedef   rtk_bt_gatts_srv_type_t
 * @brief     Service type.
 */
typedef enum
{
	GATT_SERVICE_OVER_BREDR,				/*!< 0, Service over BREDR. */
	GATT_SERVICE_OVER_BLE,					/*!< 1, Service over BLE. */
	GATT_SERVICE_TYPE_RESERVED,				/*!< 2, RESERVED. */
} rtk_bt_gatts_srv_type_t;

/**
 * @struct    rtk_bt_gatts_srv_reg_param_t
 * @brief     Bluetooth GATT server register service paramter definition.
 */
typedef struct
{
	uint8_t app_id;							/*!< Every service has a app_id. */
	rtk_bt_gatts_srv_type_t type;			/*!< GATT over which type */
	struct rtk_bt_gatt_service *srv;		/*!< GATT Service structure */
	uint8_t is_dynamic;						/*!< Whether service is alloced,
											* if srv_is_dynamic==1 and auto_free==0,
											* ONLY when callback tell us registered status CAN free the service! */
	uint8_t auto_free;						/*!< Whether need auto_free by API */
} rtk_bt_gatts_srv_reg_param_t;

/**
 * @struct    rtk_bt_gatts_indicate_param_t
 * @brief     Bluetooth GATT server indicate paramter definition.
 */
typedef struct
{
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	uint8_t app_id;							/*!< Every service has a app_id. */
	uint8_t conn_id;						/*!< Connection ID for a client */
	uint16_t index;							/*!< Attribute index in service */
	uint16_t len;							/*!< Indicate Value length */
	const void *data;						/*!< Indicate Value data */
} rtk_bt_gatts_indicate_param_t;

/**
 * @typedef   rtk_bt_gatts_notify_param_t
 * @brief     Bluetooth GATT server notify paramter definition.
 */
typedef rtk_bt_gatts_indicate_param_t rtk_bt_gatts_notify_param_t;

/**
 * @struct    rtk_bt_gatts_resp_read_param_t
 * @brief     Bluetooth GATT server read response paramter definition.
 */
typedef struct
{
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	uint8_t app_id;							/*!< Every service has a app_id. */
	uint8_t conn_id;						/*!< Connection ID for a client */
	uint16_t index;							/*!< Attribute index in service */
	uint8_t err_code;						/*!< Error code, if NOT ERR_RESP, equals 0 */
	uint16_t len;							/*!< Response Value length, when err_code == 0 */
	const void *data;						/*!< Response Value data, when err_code == 0 */
} rtk_bt_gatts_resp_read_param_t;

/**
 * @typedef   rtk_bt_gatts_write_type_t
 * @brief     Bluetooth GATT server received write request type definition.
 */
typedef enum
{
	RTK_BT_EVT_GATTS_WRITE_REQ,				/*!< GATT client write request */
	RTK_BT_EVT_GATTS_WRITE_NO_RESP,			/*!< GATT client write cmd */
	RTK_BT_EVT_GATTS_WRITE_NO_RESP_SIGNED,	/*!< GATT client write cmd (signed) */
	RTK_BT_EVT_GATTS_WRITE_LONG,			/*!< GATT client write long */
} rtk_bt_gatts_write_type_t;

/**
 * @struct    rtk_bt_gatts_resp_write_param_t
 * @brief     Bluetooth GATT server response paramter definition for write request.
 */
typedef struct
{
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	uint8_t app_id;							/*!< Every service has a app_id. */
	uint8_t conn_id;						/*!< Connection ID for a client */
	uint16_t index;							/*!< Attribute index in service */
	rtk_bt_gatts_write_type_t type;			/*!< Write type */
	uint8_t err_code;						/*!< Error code, if NOT ERR_RESP, equals 0 */
} rtk_bt_gatts_resp_write_param_t;

/**
 * @typedef   rtk_bt_gatts_evt_code_t
 * @brief     Bluetooth GATTS event code definition.
 */
typedef enum
{
	RTK_BT_EVT_GATTS_MTU_EXCHANGE = 1,		/*!< MTU exchange event (common event) */
	RTK_BT_EVT_GATTS_REG_SRV,				/*!< Register service result event */
	RTK_BT_EVT_GATTS_INDICATE,				/*!< Indicate operation result event */
	RTK_BT_EVT_GATTS_NOTIFY,				/*!< Notify operation result event, if OK, just means local sent OK. */
	RTK_BT_EVT_GATTS_READ,					/*!< Client read event in a service */
	RTK_BT_EVT_GATTS_WRITE,					/*!< Client write event in a service */
	RTK_BT_EVT_GATTS_CCCD,					/*!< CCCD update event in a service */
	RTK_BT_EVT_GATTS_RESP_READ,				/*!< Response operation result event for client read, if OK, just means local sent OK. */
	RTK_BT_EVT_GATTS_RESP_WRITE,			/*!< Response operation result event for client write, if OK, just means local sent OK. */
} rtk_bt_gatts_evt_code_t;

/**
 * @struct    rtk_bt_gatts_evt_common_t
 * @brief     A helper type for getting app id.
 */
typedef struct
{
	uint8_t app_id;							/*!< Every service has a app_id. */
} rtk_bt_gatts_evt_common_t;

/**
 * @struct    rtk_bt_gatts_evt_reg_srv_t
 * @brief     Bluetooth GATTS event register service result definition.
 */
typedef struct
{
	uint8_t app_id;							/*!< Every service has a app_id. */
	rtk_bt_evt_status_t status;				/*!< The status of registering service */
} rtk_bt_gatts_evt_reg_srv_t;

/**
 * @typedef   rtk_bt_gatts_ind_res_t
 * @brief     Bluetooth GATTS event indicate result type.
 */
typedef enum
{
	RTK_BT_GATTS_IND_RES_OK,				/*!< Success */
	RTK_BT_GATTS_IND_RES_ERR_LOCAL,			/*!< Error in send indication, due to local misfunction */
	RTK_BT_GATTS_IND_RES_ERR_REMOTE,		/*!< Error in send indication, due to remote response */
} rtk_bt_gatts_ind_res_t;

/**
 * @struct    rtk_bt_gatts_evt_indicate_t
 * @brief     Bluetooth GATTS event indicate result paramter.
 */
typedef struct
{
	uint8_t app_id;							/*!< Every service has a app_id. */
	uint8_t conn_id;						/*!< Connection ID for a client */
	rtk_bt_gatts_ind_res_t status;			/*!< Status type */
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
	};										/*!< The error value of this GATT operation */
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
} rtk_bt_gatts_evt_indicate_t;

/**
 * @struct    rtk_bt_gatts_evt_notify_t
 * @brief     Bluetooth GATTS event indicate result paramter.
 */
typedef struct
{
	uint8_t app_id;							/*!< Every service has a app_id. */
	uint8_t conn_id;						/*!< Connection ID for a client */
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
	rtk_bt_evt_status_t err_local;			/*!< Error code, if no error is 0. */
} rtk_bt_gatts_evt_notify_t;

/**
 * @struct    rtk_bt_gatts_evt_read_t
 * @brief     Bluetooth GATTS event read request paramter.
 */
typedef struct
{
	uint8_t app_id;							/*!< Every service has a app_id. */
	uint8_t conn_id;						/*!< Connection ID for a client */
	uint16_t index;							/*!< Attribute index in service */
	uint16_t offset;						/*!< offset in data, for blob read */
} rtk_bt_gatts_evt_read_t;

/**
 * @struct    rtk_bt_gatts_evt_write_t
 * @brief     Bluetooth GATTS event write request paramter.
 */
typedef struct
{
	uint8_t app_id;							/*!< Every service has a app_id. */
	uint8_t conn_id;						/*!< Connection ID for a client */
	uint16_t index;							/*!< Attribute index in service */
	uint16_t offset;						/*!< offset in data, for queue write */
	rtk_bt_gatts_write_type_t type;			/*!< Write type */
	uint16_t len;							/*!< Length of write data */
	uint8_t *value;							/*!< Write data */
} rtk_bt_gatts_evt_write_t;

/**
 * @struct    rtk_bt_gatts_evt_cccd_ops_t
 * @brief     Bluetooth GATTS event CCCD ops paramter.
 */
typedef struct
{
	uint8_t app_id;							/*!< Every service has a app_id. */
	uint8_t conn_id;						/*!< Connection ID for a client */
	uint16_t index;							/*!< Attribute index in service */
	uint16_t value;							/*!< CCCD update value */
} rtk_bt_gatts_evt_cccd_ops_t;

/**
 * @struct    rtk_bt_gatts_evt_resp_read_t
 * @brief     Bluetooth GATTS event for local response result for client read ops.
 */
typedef struct
{
	uint8_t app_id;							/*!< Every service has a app_id. */
	uint8_t conn_id;						/*!< Connection ID for a client */
	rtk_bt_evt_status_t err_local;			/*!< Error code, if no error is 0. */
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
} rtk_bt_gatts_evt_resp_read_t;

/**
 * @struct    rtk_bt_gatts_evt_resp_write_t
 * @brief     Bluetooth GATTS event for local response result for client write ops.
 */
typedef struct
{
	uint8_t app_id;							/*!< Every service has a app_id. */
	uint8_t conn_id;						/*!< Connection ID for a client */
	rtk_bt_evt_status_t err_local;			/*!< Error code, if no error is 0. */
	uint16_t seq;							/*!< Sequence number, for convinience, not mandatory */
} rtk_bt_gatts_evt_resp_write_t;

/**
 * @struct    rtk_bt_gatts_evt_mtu_exchange_t
 * @brief     Bluetooth GATTS event for mtu exchange result.
 */
typedef struct
{
	uint8_t app_id;							/*!< Every service has a app_id. */
	uint8_t conn_id;						/*!< Connection ID */
	uint16_t mtu;							/*!< MTU size */
} rtk_bt_gatts_evt_mtu_exchange_t;

/**
 * @typedef   rtk_bt_gatts_cb_t
 * @brief     GATT server operation callback handle.
 * @param[in] event: The event type of this data
 * @param[in] data: GATT operation data
 */
typedef void (*rtk_bt_gatts_cb_t)(rtk_bt_gatts_evt_code_t event, void *data);

/**
 * @defgroup  bt_gatts BT GATT server APIs
 * @brief     BT GATT server related function APIs
 * @ingroup   BT_APIs
 * @{
 */

/**
 * @fn        rtk_bt_err_t rtk_bt_gatts_register_callback(rtk_bt_gatts_cb_t cb)
 * @brief     Register GATT server callback (SYNC).
 * @param[in] cb: The callback handle
 * @return
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_gatts_register_callback(rtk_bt_gatts_cb_t cb);

/**
 * @fn        rtk_bt_err_t rtk_bt_gatts_unregister_callback(void)
 * @brief      Unregister GATT server callback (SYNC).
 * @return
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_gatts_unregister_callback(void);

/**
 * @fn        rtk_bt_err_t rtk_bt_gatts_register_service(rtk_bt_gatts_srv_reg_param_t *param)
 * @brief     Register GATT service (ASYNC).
 * @param[in] param: The parameters for registering service app.
 * @return
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_gatts_register_service(rtk_bt_gatts_srv_reg_param_t *param);

/**
 * @fn        rtk_bt_err_t rtk_bt_gatts_indicate(rtk_bt_gatts_indicate_param_t *param)
 * @brief      Indicate action initiated by server (ASYNC).
 *
 * @param[in]  param: The parameters for indication.
 *
 * @return
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_gatts_indicate(rtk_bt_gatts_indicate_param_t *param);

/**
 * @fn        rtk_bt_err_t rtk_bt_gatts_notify(rtk_bt_gatts_notify_param_t *param)
 * @brief      Notify action initiated by server (ASYNC).
 * @param[in]  param: The parameters for notification.
 * @return
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_gatts_notify(rtk_bt_gatts_notify_param_t *param);

/**
 * @fn        rtk_bt_err_t rtk_bt_gatts_read_resp(rtk_bt_gatts_resp_read_param_t *param)
 * @brief      Server response for client read operation (ASYNC).
 * @param[in]  param: The parameters for read response.
 * @return
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_gatts_read_resp(rtk_bt_gatts_resp_read_param_t *param);

/**
 * @fn        rtk_bt_err_t rtk_bt_gatts_write_resp(rtk_bt_gatts_resp_write_param_t *param)
 * @brief     Server response for client write operation (ASYNC).
 * @param[in] param: The parameters for write response.
 * @return
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_gatts_write_resp(rtk_bt_gatts_resp_write_param_t *param);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BT_GATTS_H__ */