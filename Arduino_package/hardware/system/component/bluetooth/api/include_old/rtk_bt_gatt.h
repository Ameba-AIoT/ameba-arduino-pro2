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

/** @brief Encode 128 bit UUID into array values in little-endian format.
 *
 *  Helper macro to initialize a 128-bit UUID array value from the readable form
 *  of UUIDs, or encode 128-bit UUID values into advertising data
 *  Can be combined with BT_UUID_DECLARE_128 to declare a 128-bit UUID.
 *
 *  Example of how to declare the UUID `6E400001-B5A3-F393-E0A9-E50E24DCCA9E`
 *
 *  @code
 *  BT_UUID_DECLARE_128(
 *       BT_UUID_128_ENCODE(0x6E400001, 0xB5A3, 0xF393, 0xE0A9, 0xE50E24DCCA9E))
 *  @endcode
 *
 *  Example of how to encode the UUID `6E400001-B5A3-F393-E0A9-E50E24DCCA9E`
 *  into advertising data.
 *
 *  @code
 *  BT_DATA_BYTES(BT_DATA_UUID128_ALL,
 *       BT_UUID_128_ENCODE(0x6E400001, 0xB5A3, 0xF393, 0xE0A9, 0xE50E24DCCA9E))
 *  @endcode
 *
 *  Just replace the hyphen by the comma and add `0x` prefixes.
 *
 *  @param w32 First part of the UUID (32 bits)
 *  @param w1  Second part of the UUID (16 bits)
 *  @param w2  Third part of the UUID (16 bits)
 *  @param w3  Fourth part of the UUID (16 bits)
 *  @param w48 Fifth part of the UUID (48 bits)
 *
 *  @return The comma separated values for UUID 128 initializer that
 *          may be used directly as an argument for
 *          @ref BT_UUID_INIT_128 or @ref BT_UUID_DECLARE_128
 */
#define BT_UUID_128_ENCODE(w32, w1, w2, w3, w48) \
	(((w48) >>  0) & 0xFF), \
	(((w48) >>  8) & 0xFF), \
	(((w48) >> 16) & 0xFF), \
	(((w48) >> 24) & 0xFF), \
	(((w48) >> 32) & 0xFF), \
	(((w48) >> 40) & 0xFF), \
	(((w3)  >>  0) & 0xFF), \
	(((w3)  >>  8) & 0xFF), \
	(((w2)  >>  0) & 0xFF), \
	(((w2)  >>  8) & 0xFF), \
	(((w1)  >>  0) & 0xFF), \
	(((w1)  >>  8) & 0xFF), \
	(((w32) >>  0) & 0xFF), \
	(((w32) >>  8) & 0xFF), \
	(((w32) >> 16) & 0xFF), \
	(((w32) >> 24) & 0xFF)

/** @brief Encode 16-bit UUID into array values in little-endian format.
 *
 *  Helper macro to encode 16-bit UUID values into advertising data.
 *
 *  Example of how to encode the UUID `0x180a` into advertising data.
 *
 *  @code
 *  BT_DATA_BYTES(BT_DATA_UUID16_ALL, BT_UUID_16_ENCODE(0x180a))
 *  @endcode
 *
 * @param w16 UUID value (16-bits)
 *
 * @return The comma separated values for UUID 16 value that
 *         may be used directly as an argument for @ref BT_DATA_BYTES.
 */
#define BT_UUID_16_ENCODE(w16)  \
	(((w16) >>  0) & 0xFF), \
	(((w16) >>  8) & 0xFF)

/** @brief Encode 32-bit UUID into array values in little-endian format.
 *
 *  Helper macro to encode 32-bit UUID values into advertising data.
 *
 *  Example of how to encode the UUID `0x180a01af` into advertising data.
 *
 *  @code
 *  BT_DATA_BYTES(BT_DATA_UUID32_ALL, BT_UUID_32_ENCODE(0x180a01af))
 *  @endcode
 *
 * @param w32 UUID value (32-bits)
 *
 * @return The comma separated values for UUID 32 value that
 *         may be used directly as an argument for @ref BT_DATA_BYTES.
 */
#define BT_UUID_32_ENCODE(w32)  \
	(((w32) >>  0) & 0xFF), \
	(((w32) >>  8) & 0xFF), \
	(((w32) >> 16) & 0xFF), \
	(((w32) >> 24) & 0xFF)

#define RTK_BT_UUID_GET_SIZE(type) \
	((BT_UUID_TYPE_16  == (type)) ? (BT_UUID_SIZE_16)  : \
	((BT_UUID_TYPE_32  == (type)) ? (BT_UUID_SIZE_32)  : \
	((BT_UUID_TYPE_128 == (type)) ? (BT_UUID_SIZE_128) : (0))))

#define RTK_BT_UUID_IS_VALID(type, uuid) \
	(((BT_UUID_TYPE_16  == (type)) || \
	  (BT_UUID_TYPE_32  == (type)) || \
	  (BT_UUID_TYPE_128 == (type))) && (uuid))

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