/**
 * @file      rtk_bt_gatt.h
 * @author    benling_xu@realsil.com.cn
 * @brief     Bluetooth GATT common part type deffinition
 * @copyright Copyright (c) 2022. Realtek Semiconductor Corporation. All rights reserved.
 */

#ifndef __RTK_BT_GATT_H__
#define __RTK_BT_GATT_H__

#include <rtk_bt_defs.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @def       BT_UUID_SIZE_16
 * @brief     Bluetooth UUID16 size.
 */
#define BT_UUID_SIZE_16 2

/**
 * @def       BT_UUID_SIZE_32
 * @brief     Bluetooth UUID32 size.
 */
#define BT_UUID_SIZE_32 4

/**
 * @def       BT_UUID_SIZE_128
 * @brief     Bluetooth UUID128 size.
 */
#define BT_UUID_SIZE_128 16

/**
 * @def       BT_UUID_SIZE_MAX
 * @brief     Bluetooth UUIDMAX size.
 */
#define BT_UUID_SIZE_MAX BT_UUID_SIZE_128

/**
 * @typedef   rtk_bt_uuid_type_t
 * @brief     Bluetooth UUID type definition.
 */
typedef enum
{
	BT_UUID_TYPE_16,     /*!< UUID type 16-bit */
	BT_UUID_TYPE_32,     /*!< UUID type 32-bit */
	BT_UUID_TYPE_128,    /*!< UUID type 128-bit */
} rtk_bt_uuid_type_t;

/**
 * @struct    bt_uuid
 * @brief     A 'tentative' type definition.
 */
struct bt_uuid
{
	uint8_t type;        /*!< UUID type */
};

/**
 * @struct    bt_uuid_16
 * @brief     UUID16 type definition.
 */
struct bt_uuid_16
{
	struct bt_uuid uuid; /*!< UUID generic type */
	uint16_t val;		 /*!< UUID value, 16-bit in host endianness */
};

/**
 * @struct    bt_uuid_32
 * @brief     UUID32 type definition.
 */
struct bt_uuid_32
{
	struct bt_uuid uuid; /*!< UUID generic type */
	uint32_t val;		 /*!< UUID value, 32-bit in host endianness */
};

/**
 * @struct    bt_uuid_128
 * @brief     UUI128 type definition.
 */
struct bt_uuid_128
{
	struct bt_uuid uuid; /*!< UUID generic type */
	uint8_t val[BT_UUID_SIZE_128]; /*!< UUID value, 128-bit in host endianness */
};

/**
 * @def       BT_UUID_INIT_16
 * @brief     Initialize a 16-bit UUID.
 * @param     value: 16-bit UUID value in host endianness.
 */
#define BT_UUID_INIT_16(value) \
{                              \
	.uuid = {BT_UUID_TYPE_16}, \
	.val = (value),            \
}

/**
 * @def       BT_UUID_INIT_32
 * @brief     Initialize a 32-bit UUID.
 * @param     value: 32-bit UUID value in host endianness.
 */
#define BT_UUID_INIT_32(value) \
{                              \
	.uuid = {BT_UUID_TYPE_32}, \
	.val = (value),            \
}

/**
 * @def       BT_UUID_INIT_128
 * @brief     Initialize a 128-bit UUID.
 * @param     value: 128-bit UUID array values in little-endian format.
 */
#define BT_UUID_INIT_128(value...) \
{                                  \
	.uuid = {BT_UUID_TYPE_128},    \
	.val = {value},                \
}

/**
 * @def       BT_UUID_DECLARE_16
 * @brief     Helper to declare a 16-bit UUID inline.
 * @param     value: 16-bit UUID value in host endianness.
 * @return    Pointer to a generic UUID.
 */
#define BT_UUID_DECLARE_16(value) \
((struct bt_uuid *)((struct bt_uuid_16[]){BT_UUID_INIT_16(value)}))

/**
 * @def       BT_UUID_DECLARE_32
 * @brief     Helper to declare a 32-bit UUID inline.
 * @param     value: 32-bit UUID value in host endianness.
 * @return    Pointer to a generic UUID.
 */
#define BT_UUID_DECLARE_32(value) \
((struct bt_uuid *)((struct bt_uuid_32[]){BT_UUID_INIT_32(value)}))

/**
 * @def       offsetof
 * @brief     Get offset of struct member to struct beginning
 * @param     type: name of the type that @p ptr is an element of
 * @param     member: the name of the field within the struct @p ptr points to
 * @return    acutal offset
 */
#ifndef offsetof
#define offsetof(type, member) ((long)&((type *)0)->member)
#endif

/**
 * @def       CONTAINER_OF
 * @brief     Get a pointer to a container structure from an element
 * @param     ptr: pointer to a structure element
 * @param     type: name of the type that @p ptr is an element of
 * @param     field: the name of the field within the struct @p ptr points to
 * @return    a pointer to the structure that contains @p ptr
 */
#ifndef CONTAINER_OF
#define CONTAINER_OF(ptr, type, field) \
	((type *)(((char *)(ptr)) - offsetof(type, field)))
#endif

/**
 * @def       BT_UUID_DECLARE_128
 * @brief     Helper to declare a 128-bit UUID inline.
 * @param     value: 128-bit UUID array values in little-endian format.
 * @return    Pointer to a generic UUID.
 */
#define BT_UUID_DECLARE_128(value...) \
((struct bt_uuid *)((struct bt_uuid_128[]){BT_UUID_INIT_128(value)}))

/**
 * @def       BT_UUID_16
 * @brief     Helper macro to access the 16-bit UUID from a generic UUID.
 */
#define BT_UUID_16(__u) CONTAINER_OF(__u, struct bt_uuid_16, uuid)

/**
 * @def       BT_UUID_32
 * @brief     Helper macro to access the 32-bit UUID from a generic UUID.
 */
#define BT_UUID_32(__u) CONTAINER_OF(__u, struct bt_uuid_32, uuid)

/**
 * @def       BT_UUID_128
 * @brief     Helper macro to access the 128-bit UUID from a generic UUID.
 */
#define BT_UUID_128(__u) CONTAINER_OF(__u, struct bt_uuid_128, uuid)

/**
 * @def       BIT
 * @brief     Helper to get n bit mask.
 */
#ifndef BIT
#define BIT(n) (1UL << (n))
#endif

/**
 * @enum      attr_write_flag_t
 * @brief     GATT attribute write flags
 */
enum attr_write_flag_t
{
	BT_GATT_WRITE_FLAG_PREPARE = BIT(0), /*!< Attribute prepare write flag */
	BT_GATT_WRITE_FLAG_CMD     = BIT(1), /*!< Attribute write command flag */
};

/**
 * @def       RTK_GATT_APP_ID_MAX
 * @brief     Maximum of the application id.
 */
#define RTK_GATT_APP_ID_MAX     0xFF

/**
 * @def       RTK_GATTS_SRV_COMMON_ID
 * @brief     Maximum of the service id.
 */
#define RTK_GATTS_SRV_COMMON_ID RTK_GATT_APP_ID_MAX

/**
 * @def       RTK_GATT_APP_COMMON_ID
 * @brief     Maximum of the app id.
 */
#define RTK_GATT_APP_COMMON_ID RTK_GATT_APP_ID_MAX

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BT_GATT_H__ */