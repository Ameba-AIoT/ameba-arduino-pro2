/** 
 * @file      rtk_ble_gap.h
 * @author    benling_xu@realsil.com.cn
 * @brief     Bluetooth LE GAP part type and function deffinition
 * @copyright Copyright (c) 2022. Realtek Semiconductor Corporation. All rights reserved.
 */

#ifndef __RTK_BLE_GAP_H__
#define __RTK_BLE_GAP_H__

#include <rtk_bt_defs.h>
#include <bt_api_config.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @def       RTK_DEV_DEVICE_NAME_MAX
 * @brief     Bluetooth device name max length.
 */
#define RTK_DEV_DEVICE_NAME_MAX         (39+1)

/**
 * @def       RTK_PAIRING_PASSKEY_MAX
 * @brief     Bluetooth pairing passkey max value.
 */
#define RTK_PAIRING_PASSKEY_MAX         999999

/**
 * @def       RTK_BLE_ADV_DATA_LEN
 * @brief     Bluetooth adv data max length.
 */
#define RTK_BLE_ADV_DATA_LEN            31

/**
 * @typedef   rtk_ble_gap_ad_type_t
 * @brief     Bluetooth ble gap advertising data type definition.
 */
typedef enum
{
	RTK_GAP_ADTYPE_FLAGS                                   = 0x01, /*!< 0x01, The Flags data type contains one bit Boolean flags. */
	RTK_GAP_ADTYPE_16BIT_MORE                              = 0x02, /*!< 0x02, Service: More 16-bit UUIDs available */
	RTK_GAP_ADTYPE_16BIT_COMPLETE                          = 0x03, /*!< 0x03, Service: Complete list of 16-bit UUIDs */
	RTK_GAP_ADTYPE_32BIT_MORE                              = 0x04, /*!< 0x04, Service: More 32-bit UUIDs available */
	RTK_GAP_ADTYPE_32BIT_COMPLETE                          = 0x05, /*!< 0x05, Service: Complete list of 32-bit UUIDs */
	RTK_GAP_ADTYPE_128BIT_MORE                             = 0x06, /*!< 0x06, Service: More 128-bit UUIDs available */
	RTK_GAP_ADTYPE_128BIT_COMPLETE                         = 0x07, /*!< 0x07, Service: Complete list of 128-bit UUIDs */
	RTK_GAP_ADTYPE_LOCAL_NAME_SHORT                        = 0x08, /*!< 0x08, Shortened local name */
	RTK_GAP_ADTYPE_LOCAL_NAME_COMPLETE                     = 0x09, /*!< 0x09, Complete local name */
	RTK_GAP_ADTYPE_POWER_LEVEL                             = 0x0A, /*!< 0x0A, TX Power Level: = 0xXX: -127 to +127 dBm */
	RTK_GAP_ADTYPE_OOB_CLASS_OF_DEVICE                     = 0x0D, /*!< 0x0D, Simple Pairing OOB Tag: Class of device (3 octets) */
	RTK_GAP_ADTYPE_OOB_SIMPLE_PAIRING_HASHC                = 0x0E, /*!< 0x0E, Simple Pairing OOB Tag: Simple Pairing Hash C (16 octets) */
	RTK_GAP_ADTYPE_OOB_SIMPLE_PAIRING_RANDR                = 0x0F, /*!< 0x0F, Simple Pairing OOB Tag: Simple Pairing Randomizer R (16 octets) */
	RTK_GAP_ADTYPE_SM_TK                                   = 0x10, /*!< 0x10, Security Manager TK Value */
	RTK_GAP_ADTYPE_SM_OOB_FLAG                             = 0x11, /*!< 0x11, Secutiry Manager OOB Flags */
	RTK_GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE               = 0x12, /*!< 0x12, Min and Max values of the connection interval (2 octets Min, 2 octets Max) (0xFFFF indicates no conn interval min or max) */
	RTK_GAP_ADTYPE_SIGNED_DATA                             = 0x13, /*!< 0x13, Signed Data field */
	RTK_GAP_ADTYPE_SERVICES_LIST_16BIT                     = 0x14, /*!< 0x14, Service Solicitation: list of 16-bit Service UUIDs */
	RTK_GAP_ADTYPE_SERVICES_LIST_128BIT                    = 0x15, /*!< 0x15, Service Solicitation: list of 128-bit Service UUIDs */
	RTK_GAP_ADTYPE_SERVICE_DATA                            = 0x16, /*!< 0x16, Service Data */
	RTK_GAP_ADTYPE_PUBLIC_TGT_ADDR                         = 0x17, /*!< 0x17, Public Target Address */
	RTK_GAP_ADTYPE_RANDOM_TGT_ADDR                         = 0x18, /*!< 0x18, Random Target Address */
	RTK_GAP_ADTYPE_APPEARANCE                              = 0x19, /*!< 0x19, Appearance */
	RTK_GAP_ADTYPE_ADV_INTERVAL                            = 0x1A, /*!< 0x1A, Advertising Interval */
	RTK_GAP_ADTYPE_LE_BT_ADDR                              = 0x1B, /*!< 0x1B, LE Bluetooth Device Address */
	RTK_GAP_ADTYPE_LE_ROLE                                 = 0x1C, /*!< 0x1C, LE Role */
	RTK_GAP_ADTYPE_SP_HASH_C256                            = 0x1D, /*!< 0x1D, Simple Pairing Hash C-256 */
	RTK_GAP_ADTYPE_SP_RAND_R256                            = 0x1E, /*!< 0x1E, Simple Pairing Randomizer R-256 */
	RTK_GAP_ADTYPE_LIST_32BIT_SILI                         = 0x1F, /*!< 0x1F, List of 32-bit Service Solicitation UUIDs */
	RTK_GAP_ADTYPE_SERVICE_DATA_32BIT                      = 0x20, /*!< 0x20, Service Data - 32-bit UUID */
	RTK_GAP_ADTYPE_SERVICE_DATA_128BIT                     = 0x21, /*!< 0x21, Service Data - 128-bit UUID */
	RTK_GAP_ADTYPE_SC_CONF_VALUE                           = 0x22, /*!< 0x22, LE Secure Connections Confirmation Value */
	RTK_GAP_ADTYPE_SC_RAND_VALUE                           = 0x23, /*!< 0x23, LE Secure Connections Random Value */
	RTK_GAP_ADTYPE_URI                                     = 0x24, /*!< 0x24, URI */
	RTK_GAP_ADTYPE_INDOOR_POSITION                         = 0x25, /*!< 0x25, Indoor Positioning */
	RTK_GAP_ADTYPE_TRANSPORT_DISCOVERY_DATA                = 0x26, /*!< 0x26, Transport Discovery Data */
	RTK_GAP_ADTYPE_LE_SUPPORTED_FEATURES                   = 0x27, /*!< 0x27, LE Supported Features */
	RTK_GAP_ADTYPE_CHAN_MAP_UPDATE_IND                     = 0x28, /*!< 0x28, Channel Map Update Indication */
	RTK_GAP_ADTYPE_MESH_PB_ADV                             = 0x29, /*!< 0x29, Mesh Pb-Adv */
	RTK_GAP_ADTYPE_MESH_PACKET                             = 0x2A, /*!< 0x2A, Mesh Packet */
	RTK_GAP_ADTYPE_MESH_BEACON                             = 0x2B, /*!< 0x2B, Mesh Beacon */
	RTK_GAP_ADTYPE_3D_INFO_DATA                            = 0x3D, /*!< 0x3D, 3D Information Data */
	RTK_GAP_ADTYPE_MANUFACTURER_SPECIFIC                   = 0xFF, /*!< 0xFF, Manufacturer Specific Data */
} rtk_ble_gap_ad_type_t;

/**
 * @typedef   rtk_ble_gap_ad_flags_data_t
 * @brief     Bluetooth ble gap advertising data type data definition.
 */
typedef enum
{
	RTK_GAP_ADTYPE_FLAGS_LIMITED                           = 0x01, /*!< 0x01, Discovery Mode: LE Limited Discoverable Mode*/
	RTK_GAP_ADTYPE_FLAGS_GENERAL                           = 0x02, /*!< 0x02, Discovery Mode: LE General Discoverable Mode*/
	RTK_GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED               = 0x04, /*!< 0x04, Discovery Mode: BR/EDR Not Supported*/
	RTK_GAP_ADTYPE_FLAGS_SIMULTANEOUS_LE_BREDR_CONTROLLER  = 0x08, /*!< 0x08, Discovery Mode: Simultaneous LE and BR/EDR Controller Supported*/
	RTK_GAP_ADTYPE_FLAGS_SIMULTANEOUS_LE_BREDR_HOST        = 0x10, /*!< 0x10, Discovery Mode: Simultaneous LE and BR/EDR Host Supported*/
} rtk_ble_gap_ad_flags_data_t;

/**
 * @typedef   rtk_bt_appearance_t
 * @brief     Bluetooth device appearance definition.
 */
typedef enum
{
    RTK_GAP_APPEARANCE_UNKNOWN                             = 0x0000, /*!< 0x0000 */  
    RTK_GAP_APPEARANCE_GENERIC_PHONE                       = 0x0040, /*!< 0x0040 */  
    RTK_GAP_APPEARANCE_GENERIC_COMPUTER                    = 0x0080, /*!< 0x0080 */  
    RTK_GAP_APPEARANCE_GENERIC_WATCH                       = 0x00C0, /*!< 0x00C0 */  
    RTK_GAP_APPEARANCE_SPORTS_WATCH                        = 0x00C1, /*!< 0x00C1 */  
    RTK_GAP_APPEARANCE_GENERIC_CLOCK                       = 0x0100, /*!< 0x0100 */  
    RTK_GAP_APPEARANCE_GENERIC_DISPLAY                     = 0x0140, /*!< 0x0140 */  
    RTK_GAP_APPEARANCE_GENERIC_REMOTE                      = 0x0180, /*!< 0x0180 */  
    RTK_GAP_APPEARANCE_GENERIC_EYEGLASSES                  = 0x01C0, /*!< 0x01C0 */  
    RTK_GAP_APPEARANCE_GENERIC_TAG                         = 0x0200, /*!< 0x0200 */  
    RTK_GAP_APPEARANCE_GENERIC_KEYRING                     = 0x0240, /*!< 0x0240 */  
    RTK_GAP_APPEARANCE_GENERIC_MEDIA_PLAYER                = 0x0280, /*!< 0x0280 */  
    RTK_GAP_APPEARANCE_GENERIC_BARCODE_SCANNER             = 0x02C0, /*!< 0x02C0 */  
    RTK_GAP_APPEARANCE_GENERIC_THERMOMETER                 = 0x0300, /*!< 0x0300 */  
    RTK_GAP_APPEARANCE_THERMOMETER_EAR                     = 0x0301, /*!< 0x0301 */  
    RTK_GAP_APPEARANCE_GENERIC_HEART_RATE                  = 0x0340, /*!< 0x0340 */  
    RTK_GAP_APPEARANCE_HEART_RATE_BELT                     = 0x0341, /*!< 0x0341 */  
    RTK_GAP_APPEARANCE_GENERIC_BLOOD_PRESSURE              = 0x0380, /*!< 0x0380 */  
    RTK_GAP_APPEARANCE_BLOOD_PRESSURE_ARM                  = 0x0381, /*!< 0x0381 */  
    RTK_GAP_APPEARANCE_BLOOD_PRESSURE_WRIST                = 0x0382, /*!< 0x0382 */  
    RTK_GAP_APPEARANCE_GENERIC_HID                         = 0x03C0, /*!< 0x03C0 */  
    RTK_GAP_APPEARANCE_HID_KEYBOARD                        = 0x03C1, /*!< 0x03C1 */  
    RTK_GAP_APPEARANCE_HID_MOUSE                           = 0x03C2, /*!< 0x03C2 */  
    RTK_GAP_APPEARANCE_HID_JOYSTICK                        = 0x03C3, /*!< 0x03C3 */  
    RTK_GAP_APPEARANCE_HID_GAMEPAD                         = 0x03C4, /*!< 0x03C4 */  
    RTK_GAP_APPEARANCE_HID_DIGITIZER_TABLET                = 0x03C5, /*!< 0x03C5 */  
    RTK_GAP_APPEARANCE_HID_CARD_READER                     = 0x03C6, /*!< 0x03C6 */  
    RTK_GAP_APPEARANCE_HID_DIGITAL_PEN                     = 0x03C7, /*!< 0x03C7 */  
    RTK_GAP_APPEARANCE_HID_BARCODE_SCANNER                 = 0x03C8, /*!< 0x03C8 */  
    RTK_GAP_APPEARANCE_GENERIC_GLUCOSE                     = 0x0400, /*!< 0x0400 */  
    RTK_GAP_APPEARANCE_GENERIC_WALKING                     = 0x0440, /*!< 0x0440 */  
    RTK_GAP_APPEARANCE_WALKING_IN_SHOE                     = 0x0441, /*!< 0x0441 */  
    RTK_GAP_APPEARANCE_WALKING_ON_SHOE                     = 0x0442, /*!< 0x0442 */  
    RTK_GAP_APPEARANCE_WALKING_ON_HIP                      = 0x0443, /*!< 0x0443 */  
    RTK_GAP_APPEARANCE_GENERIC_CYCLING                     = 0x0480, /*!< 0x0480 */  
    RTK_GAP_APPEARANCE_CYCLING_COMPUTER                    = 0x0481, /*!< 0x0481 */  
    RTK_GAP_APPEARANCE_CYCLING_SPEED                       = 0x0482, /*!< 0x0482 */  
    RTK_GAP_APPEARANCE_CYCLING_CADENCE                     = 0x0483, /*!< 0x0483 */  
    RTK_GAP_APPEARANCE_CYCLING_POWER                       = 0x0484, /*!< 0x0484 */  
    RTK_GAP_APPEARANCE_CYCLING_SPEED_CADENCE               = 0x0485, /*!< 0x0485 */  
    RTK_GAP_APPEARANCE_GENERIC_PULSE_OXIMETER              = 0x0C40, /*!< 0x0C40 */  
    RTK_GAP_APPEARANCE_PULSE_OXIMETER_FINGERTIP            = 0x0C41, /*!< 0x0C41 */  
    RTK_GAP_APPEARANCE_PULSE_OXIMETER_WRIST                = 0x0C42, /*!< 0x0C42 */  
    RTK_GAP_APPEARANCE_GENERIC_WEIGHT                      = 0x0C80, /*!< 0x0C80 */  
    RTK_GAP_APPEARANCE_GENERIC_PERSONAL_MOBILITY_DEVICE    = 0x0CC0, /*!< 0x0CC0 */  
    RTK_GAP_APPEARANCE_POWERED_WHEELCHAIR                  = 0x0CC1, /*!< 0x0CC1 */  
    RTK_GAP_APPEARANCE_MOBILITY_SCOOTER                    = 0x0CC2, /*!< 0x0CC2 */  
    RTK_GAP_APPEARANCE_GENERIC_CONTINUOUS_GLUCOSE_MONITOR  = 0x0D00, /*!< 0x0D00 */  
    RTK_GAP_APPEARANCE_GENERIC_INSULIN_PUMP                = 0x0D40, /*!< 0x0D40 */  
    RTK_GAP_APPEARANCE_INSULIN_PUMP_DURABLE_PUMP           = 0x0D41, /*!< 0x0D41 */  
    RTK_GAP_APPEARANCE_INSULIN_PUMP_PATCH_PUMP             = 0x0D44, /*!< 0x0D44 */  
    RTK_GAP_APPEARANCE_INSULIN_PEN                         = 0x0D48, /*!< 0x0D48 */  
    RTK_GAP_APPEARANCE_GENERIC_MEDICATION_DELIVERY         = 0x0D80, /*!< 0x0D80 */  
    RTK_GAP_APPEARANCE_GENERIC_OUTDOOR_SPORTS              = 0x1440, /*!< 0x1440 */  
    RTK_GAP_APPEARANCE_OUTDOOR_SPORTS_LOCATION             = 0x1441, /*!< 0x1441 */  
    RTK_GAP_APPEARANCE_OUTDOOR_SPORTS_LOCATION_AND_NAV     = 0x1442, /*!< 0x1442 */  
    RTK_GAP_APPEARANCE_OUTDOOR_SPORTS_LOCATION_POD         = 0x1443, /*!< 0x1443 */  
    RTK_GAP_APPEARANCE_OUTDOOR_SPORTS_LOCATION_POD_AND_NAV = 0x1444, /*!< 0x1444 */  
} rtk_bt_appearance_t;

/**
 * @typedef   rtk_bt_hci_err_t
 * @brief     Bluetooth HCI error code definition.
 */
typedef enum
{
    RTK_BT_HCI_ERR_SUCCESS                                 = 0x00, /*!< 0x00 */
    RTK_BT_HCI_ERR_UNKNOWN_CMD                             = 0x01, /*!< 0x01 */
    RTK_BT_HCI_ERR_UNKNOWN_CONN_ID                         = 0x02, /*!< 0x02 */
    RTK_BT_HCI_ERR_HW_FAILURE                              = 0x03, /*!< 0x03 */
    RTK_BT_HCI_ERR_PAGE_TIMEOUT                            = 0x04, /*!< 0x04 */
    RTK_BT_HCI_ERR_AUTH_FAIL                               = 0x05, /*!< 0x05 */
    RTK_BT_HCI_ERR_PIN_OR_KEY_MISSING                      = 0x06, /*!< 0x06 */
    RTK_BT_HCI_ERR_MEM_CAPACITY_EXCEEDED                   = 0x07, /*!< 0x07 */
    RTK_BT_HCI_ERR_CONN_TIMEOUT                            = 0x08, /*!< 0x08 */
    RTK_BT_HCI_ERR_CONN_LIMIT_EXCEEDED                     = 0x09, /*!< 0x09 */
    RTK_BT_HCI_ERR_SYNC_CONN_LIMIT_EXCEEDED                = 0x0a, /*!< 0x0a */
    RTK_BT_HCI_ERR_CONN_ALREADY_EXISTS                     = 0x0b, /*!< 0x0b */
    RTK_BT_HCI_ERR_CMD_DISALLOWED                          = 0x0c, /*!< 0x0c */
    RTK_BT_HCI_ERR_INSUFFICIENT_RESOURCES                  = 0x0d, /*!< 0x0d */
    RTK_BT_HCI_ERR_INSUFFICIENT_SECURITY                   = 0x0e, /*!< 0x0e */
    RTK_BT_HCI_ERR_BD_ADDR_UNACCEPTABLE                    = 0x0f, /*!< 0x0f */
    RTK_BT_HCI_ERR_CONN_ACCEPT_TIMEOUT                     = 0x10, /*!< 0x10 */
    RTK_BT_HCI_ERR_UNSUPP_FEATURE_PARAM_VAL                = 0x11, /*!< 0x11 */
    RTK_BT_HCI_ERR_INVALID_PARAM                           = 0x12, /*!< 0x12 */
    RTK_BT_HCI_ERR_REMOTE_USER_TERM_CONN                   = 0x13, /*!< 0x13 */
    RTK_BT_HCI_ERR_REMOTE_LOW_RESOURCES                    = 0x14, /*!< 0x14 */
    RTK_BT_HCI_ERR_REMOTE_POWER_OFF                        = 0x15, /*!< 0x15 */
    RTK_BT_HCI_ERR_LOCALHOST_TERM_CONN                     = 0x16, /*!< 0x16 */
    RTK_BT_HCI_ERR_REPEATED_ATTEMPTS                       = 0x17, /*!< 0x17 */
    RTK_BT_HCI_ERR_PAIRING_NOT_ALLOWED                     = 0x18, /*!< 0x18 */
    RTK_BT_HCI_ERR_UNKNOWN_LMP_PDU                         = 0x19, /*!< 0x19 */
    RTK_BT_HCI_ERR_UNSUPP_REMOTE_FEATURE                   = 0x1a, /*!< 0x1a */
    RTK_BT_HCI_ERR_SCO_OFFSET_REJECTED                     = 0x1b, /*!< 0x1b */
    RTK_BT_HCI_ERR_SCO_INTERVAL_REJECTED                   = 0x1c, /*!< 0x1c */
    RTK_BT_HCI_ERR_SCO_AIR_MODE_REJECTED                   = 0x1d, /*!< 0x1d */
    RTK_BT_HCI_ERR_INVALID_LL_PARAM                        = 0x1e, /*!< 0x1e */
    RTK_BT_HCI_ERR_UNSPECIFIED                             = 0x1f, /*!< 0x1f */
    RTK_BT_HCI_ERR_UNSUPP_LL_PARAM_VAL                     = 0x20, /*!< 0x20 */
    RTK_BT_HCI_ERR_ROLE_CHANGE_NOT_ALLOWED                 = 0x21, /*!< 0x21 */
    RTK_BT_HCI_ERR_LL_RESP_TIMEOUT                         = 0x22, /*!< 0x22 */
    RTK_BT_HCI_ERR_LL_PROC_COLLISION                       = 0x23, /*!< 0x23 */
    RTK_BT_HCI_ERR_LMP_PDU_NOT_ALLOWED                     = 0x24, /*!< 0x24 */
    RTK_BT_HCI_ERR_ENC_MODE_NOT_ACCEPTABLE                 = 0x25, /*!< 0x25 */
    RTK_BT_HCI_ERR_LINK_KEY_CANNOT_BE_CHANGED              = 0x26, /*!< 0x26 */
    RTK_BT_HCI_ERR_REQUESTED_QOS_NOT_SUPPORTED             = 0x27, /*!< 0x27 */
    RTK_BT_HCI_ERR_INSTANT_PASSED                          = 0x28, /*!< 0x28 */
    RTK_BT_HCI_ERR_PAIRING_NOT_SUPPORTED                   = 0x29, /*!< 0x29 */
    RTK_BT_HCI_ERR_DIFF_TRANS_COLLISION                    = 0x2a, /*!< 0x2a */
    RTK_BT_HCI_ERR_QOS_UNACCEPTABLE_PARAM                  = 0x2c, /*!< 0x2c */
    RTK_BT_HCI_ERR_QOS_REJECTED                            = 0x2d, /*!< 0x2d */
    RTK_BT_HCI_ERR_CHAN_ASSESS_NOT_SUPPORTED               = 0x2e, /*!< 0x2e */
    RTK_BT_HCI_ERR_INSUFF_SECURITY                         = 0x2f, /*!< 0x2f */
    RTK_BT_HCI_ERR_PARAM_OUT_OF_MANDATORY_RANGE            = 0x30, /*!< 0x30 */
    RTK_BT_HCI_ERR_ROLE_SWITCH_PENDING                     = 0x32, /*!< 0x32 */
    RTK_BT_HCI_ERR_RESERVED_SLOT_VIOLATION                 = 0x34, /*!< 0x34 */
    RTK_BT_HCI_ERR_ROLE_SWITCH_FAILED                      = 0x35, /*!< 0x35 */
    RTK_BT_HCI_ERR_EXT_INQ_RESP_TOO_LARGE                  = 0x36, /*!< 0x36 */
    RTK_BT_HCI_ERR_SIMPLE_PAIR_NOT_SUPP_BY_HOST            = 0x37, /*!< 0x37 */
    RTK_BT_HCI_ERR_HOST_BUSY_PAIRING                       = 0x38, /*!< 0x38 */
    RTK_BT_HCI_ERR_CONN_REJECTED_DUE_TO_NO_CHAN            = 0x39, /*!< 0x39 */
    RTK_BT_HCI_ERR_CONTROLLER_BUSY                         = 0x3a, /*!< 0x3a */
    RTK_BT_HCI_ERR_UNACCEPT_CONN_PARAM                     = 0x3b, /*!< 0x3b */
    RTK_BT_HCI_ERR_ADV_TIMEOUT                             = 0x3c, /*!< 0x3c */
    RTK_BT_HCI_ERR_TERM_DUE_TO_MIC_FAIL                    = 0x3d, /*!< 0x3d */
    RTK_BT_HCI_ERR_CONN_FAIL_TO_ESTAB                      = 0x3e, /*!< 0x3e */
    RTK_BT_HCI_ERR_MAC_CONN_FAILED                         = 0x3f, /*!< 0x3f */
    RTK_BT_HCI_ERR_CLOCK_ADJUST_REJECTED                   = 0x40, /*!< 0x40 */
    RTK_BT_HCI_ERR_SUBMAP_NOT_DEFINED                      = 0x41, /*!< 0x41 */
    RTK_BT_HCI_ERR_UNKNOWN_ADV_IDENTIFIER                  = 0x42, /*!< 0x42 */
    RTK_BT_HCI_ERR_LIMIT_REACHED                           = 0x43, /*!< 0x43 */
    RTK_BT_HCI_ERR_OP_CANCELLED_BY_HOST                    = 0x44, /*!< 0x44 */
    RTK_BT_HCI_ERR_PACKET_TOO_LONG                         = 0x45, /*!< 0x45 */
    RTK_BT_HCI_ERR_UNKNOWN                                 = 0xff, /*!< 0xff */
} rtk_bt_hci_err_t;

/**
 * @typedef   rtk_ble_gap_default_param_type_t
 * @brief     Bluetooth LE GAP default paramters definition.
 */
typedef enum
{
    RTK_BLE_GAP_PARAM_NULL                                 = 0x00, /*!< 0x00, no meaning, just prevent the enum is empty */
    RTK_BLE_GAP_MTU_SIZE                                   = 0x01, /*!< 0x01, means default mtu size */
#if RTK_BLE_4_2_DATA_LEN_EXT_SUPPORT
    RTK_BLE_GAP_WRITE_DEFAULT_DATA_LEN                     = 0x02, /*!< 0x02, means default data len */
#endif /*!< RTK_BLE_4_2_DATA_LEN_EXT_SUPPORT */
#if defined(RTK_BLE_5_0_SET_PHYS_SUPPORT) && (RTK_BLE_5_0_SET_PHYS_SUPPORT)
    RTK_BLE_GAP_SET_DEFAULT_PHY                            = 0x03, /*!< 0x03, means default phy parameters */
#endif /*!< RTK_BLE_5_0_SET_PHYS_SUPPORT */
} rtk_ble_gap_default_param_type_t;

/**
 * @typedef   rtk_ble_link_role_t
 * @brief     Bluetooth LE GAP link role definition.
 */
typedef enum
{
    RTK_BLE_ROLE_MASTER                                    = 0x00, /*!< 0x00, means master */
    RTK_BLE_ROLE_SLAVE                                     = 0x01, /*!< 0x01, means slave */
    RTK_BLE_ROLE_UNKNOWN,                                          /*!< unknown */
} rtk_ble_link_role_t;

/**
 * @typedef   rtk_ble_adv_type_t
 * @brief     Bluetooth LE GAP adv type definition.
 */
typedef enum
{
    RTK_BLE_ADV_TYPE_IND                                   = 0x00, /*!< 0x00, Connectable and scannable undirected advertising (ADV_IND) (default) */
    RTK_BLE_ADV_TYPE_DIRECT_IND_HIGH                       = 0x01, /*!< 0x01, Connectable high duty cycle directed advertising (ADV_DIRECT_IND, high duty cycle) */
    RTK_BLE_ADV_TYPE_SCAN_IND                              = 0x02, /*!< 0x02, Scannable undirected advertising (ADV_SCAN_IND) */
    RTK_BLE_ADV_TYPE_NONCONN_IND                           = 0x03, /*!< 0x03, Non connectable undirected advertising (ADV_NONCONN_IND) */
    RTK_BLE_ADV_TYPE_DIRECT_IND_LOW                        = 0x04, /*!< 0x04, Connectable low duty cycle directed advertising (ADV_DIRECT_IND, low duty cycle) */
    RTK_BLE_ADV_TYPE_RESERVED,                                     /*!< reserved */
} rtk_ble_adv_type_t;

/**
 * @typedef   rtk_ble_adv_ch_map_t
 * @brief     Bluetooth LE GAP adv type definition.
 */
typedef enum
{
    RTK_BLE_ADV_CHNL_37                                    = 0x01, /*!< 0x00, Channel 37 shall be used */
    RTK_BLE_ADV_CHNL_38                                    = 0x02, /*!< 0x02, Channel 38 shall be used */
    RTK_BLE_ADV_CHNL_39                                    = 0x04, /*!< 0x04, Channel 39 shall be used */
    RTK_BLE_ADV_CHNL_ALL                                   = 0x07, /*!< 0x07, Channel 37,38,39 shall be used */
    RTK_BLE_ADV_CHNL_RESERVED,                                     /*!< reserved */
} rtk_ble_adv_ch_map_t;

/**
 * @typedef   rtk_ble_adv_filter_t
 * @brief     Bluetooth LE GAP adv filter type definition.
 */
typedef enum
{
    RTK_BLE_ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY              = 0, /*!< 0, Allow both scan and connection requests from anyone */
    RTK_BLE_ADV_FILTER_ALLOW_SCAN_WLST_CON_ANY             = 1, /*!< 1, Allow both scan req from White List devices only and connection req from anyone */
    RTK_BLE_ADV_FILTER_ALLOW_SCAN_ANY_CON_WLST             = 2, /*!< 2, Allow both scan req from anyone and connection req from White List devices only */
    RTK_BLE_ADV_FILTER_ALLOW_SCAN_WLST_CON_WLST            = 3, /*!< 3, Allow scan and connection requests from White List devices only */
    RTK_BLE_ADV_FILTER_RESERVED,                                /*!< All bigger value are reserved */
} rtk_ble_adv_filter_t;

/**
 * @struct    rtk_ble_adv_data_t
 * @brief     Bluetooth LE GAP adv data definition.
 */
typedef struct
{
    uint32_t len;                           /*!< adv data len */
    uint8_t data[RTK_BLE_ADV_DATA_LEN];     /*!< ad data, maximun length is 31 */
} rtk_ble_adv_data_t;

/**
 * @typedef   rtk_ble_scan_rsp_data_t
 * @brief     Bluetooth LE GAP scan response data definition.
 */
typedef rtk_ble_adv_data_t rtk_ble_scan_rsp_data_t;

/**
 * @struct    rtk_ble_adv_param_t
 * @brief     Bluetooth LE GAP set adv data paramter definition.
 */
typedef struct {
	/** 
	 * Minimum advertising interval for undirected and low duty cycle\n
	 * directed advertising.\n
	 * Range: 0x0020 to 0x4000\n
	 * Default: 0x0800 (1.28 s)\n
	 * Time = N * 0.625 ms\n
	 * Time Range: 20 ms to 10.24 s
	 */
    uint16_t interval_min;
	/**
	 * Maximum advertising interval for undirected and low duty cycle\n
	 * directed advertising.\n
	 * Range: 0x0020 to 0x4000\n
	 * Default: 0x0800 (1.28 s)\n
	 * Time = N * 0.625 ms\n
	 * Time Range: 20 ms to 10.24 s
	 */
    uint16_t interval_max;
    /** Advertising_Type */
    rtk_ble_adv_type_t type;
    /** Own_Address_Type */
    rtk_ble_addr_type_t own_addr_type;
    /** Peer_Address_Type */
    rtk_ble_bd_addr_t peer_addr;
    /** Advertising_Channel_Map */
    rtk_ble_adv_ch_map_t channel_map;
    /** Advertising_Filter_Policy */
    rtk_ble_adv_filter_t filter_policy;
} rtk_ble_adv_param_t;

/**
 * @typedef   rtk_ble_scan_type_t
 * @brief     Bluetooth LE GAP scan type definition.
 */
typedef enum {
    RTK_BLE_SCAN_TYPE_PASSIVE = 0,          /*!< 0, Passive scan */
    RTK_BLE_SCAN_TYPE_ACTIVE,               /*!< 1, Active scan */
    RTK_BLE_SCAN_TYPE_RESERVED,             /*!< All bigger value are reserved */
} rtk_ble_scan_type_t;

/**
 * @typedef   rtk_ble_scan_filter_t
 * @brief     Bluetooth LE GAP scan filter type definition.
 */
typedef enum {
    RTK_BLE_SCAN_FILTER_ALLOW_ALL           = 0x0,  /*!< Accept all :
                                                     * 1. advertisement packets except directed advertising packets not addressed to this device (default). 
                                                     */
    RTK_BLE_SCAN_FILTER_ALLOW_ONLY_WLST     = 0x1,  /*!< Accept only :
                                                     * 1. advertisement packets from devices where the advertiser’s address is in the White list.
                                                     * 2. Directed advertising packets which are not addressed for this device shall be ignored. 
                                                     */
    RTK_BLE_SCAN_FILTER_ALLOW_UND_RPA_DIR   = 0x2,  /*!< Accept all :
                                                     * 1. undirected advertisement packets, and
                                                     * 2. directed advertising packets where the initiator address is a resolvable private address, and
                                                     * 3. directed advertising packets addressed to this device.
                                                     */
    RTK_BLE_SCAN_FILTER_ALLOW_WLIST_RPA_DIR = 0x3,  /*!< Accept all :
                                                     * 1. advertisement packets from devices where the advertiser’s address is in the White list, and
                                                     * 2. directed advertising packets where the initiator address is a resolvable private address, and
                                                     * 3. directed advertising packets addressed to this device.
                                                     */
} rtk_ble_scan_filter_t;

/**
 * @struct    rtk_ble_scan_param_t
 * @brief     Bluetooth LE GAP scan paramters definition.
 */
typedef struct {
    /** LE_Scan_Type */
    rtk_ble_scan_type_t type;
    /** 
     * This is defined as the time interval from when the Controller\n
     * started its last LE scan until it begins the subsequent LE scan.\n
     * Range: 0x0004 to 0x4000\n
     * Default: 0x0010 (10 ms)\n
     * Time = N * 0.625 ms\n
     * Time Range: 2.5 ms to 10.24 s\n
     */
    uint16_t interval;
    /** 
     * The duration of the LE scan. LE_Scan_Window shall be less\n
     * than or equal to LE_Scan_Interval\n
     * Range: 0x0004 to 0x4000\n
     * Default: 0x0010 (10 ms)\n
     * Time = N * 0.625 ms\n
     * Time Range: 2.5 ms to 10.24 s\n
     */
    uint16_t window;
    /** Own_Address_Type */
    rtk_ble_addr_type_t own_addr_type;
    /** Scanning_Filter_Policy */
    rtk_ble_scan_filter_t filter_policy;
} rtk_ble_scan_param_t;

/**
 * @typedef   rtk_ble_scan_duplicate_t
 * @brief     Bluetooth LE GAP scan duplicate filter type definition.
 */
typedef enum {
    RTK_BLE_SCAN_DUPLICATE_DISABLE = 0,     /*!< 0, Link Layer should generate advertising reports to the host for each packet received */
    RTK_BLE_SCAN_DUPLICATE_ENABLE,          /*!< 1, Link Layer should filter out duplicate advertising reports to the Host */
    RTK_BLE_SCAN_DUPLICATE_RESERVED,        /*!< All bigger value are reserved */
} rtk_ble_scan_duplicate_t;

/**
 * @struct    rtk_ble_scan_option_t
 * @brief     Bluetooth LE GAP scan option definition.
 */
typedef struct {
    rtk_ble_scan_duplicate_t duplicate;     /*!< scan duplicate filter */
} rtk_ble_scan_option_t;

/**
 * @typedef   rtk_ble_conn_filter_t
 * @brief     Bluetooth LE GAP connection filter type definition.
 */
typedef enum {    
    RTK_BLE_CONN_FILTER_WITHOUT_WHITELIST,  /*!< 0, filter without whitelist */
    RTK_BLE_CONN_FILTER_WITH_WHITELIST,     /*!< 1, filter with whitelist */
    RTK_BLE_CONN_FILTER_RESERVED,           /*!< All bigger value are reserved */
} rtk_ble_conn_filter_t;

/**
 * @struct    rtk_ble_conn_param_t
 * @brief     Bluetooth LE GAP connection paramters definition.
 */
typedef struct {
    /**
     * Minimum value for the connection interval. This shall be less\n
     * than or equal to Connection_Interval_Max.\n
     * Range: 0x0006 to 0x0C80\n
     * Time = N * 1.25 ms\n
     * Time Range: 7.5 ms to 4 s.\n
     */ 
    uint16_t conn_interval_min;
    /**
     * Maximum value for the connection interval. This shall be\n
     * greater than or equal to Connection_Interval_Min.\n
     * Range: 0x0006 to 0x0C80\n
     * Time = N * 1.25 ms\n
     * Time Range: 7.5 ms to 4 s.\n
     */
    uint16_t conn_interval_max;
    /**
     * Slave latency for the connection in number of connection events.\n
     * Range: 0x0000 to 0x01F3\n
     */
    uint16_t conn_latency;
    /**
     * Supervision timeout for the LE Link.\n
     * Range: 0x000A to 0x0C80\n
     * Time = N * 10 ms\n
     * Time Range: 100 ms to 32 s\n
     */
    uint16_t timeout;
} rtk_ble_conn_param_t;

/**
 * @struct    rtk_ble_update_conn_param_t
 * @brief     Bluetooth LE GAP connection update paramters definition.
 */
typedef struct {
    uint8_t conn_id;                        /*!< Connection_id */
    rtk_ble_conn_param_t param;             /*!< connection paramters */
} rtk_ble_update_conn_param_t;

/**
 * @struct    rtk_ble_create_conn_param_t
 * @brief     Bluetooth LE GAP create connection paramters definition.
 */
typedef struct {
    /**
     * This is defined as the time interval from when the Controller started\n
     * its last LE scan until it begins the subsequent LE scan.\n
     * Range: 0x0004 to 0x4000\n
     * Time = N * 0.625 ms\n
     * Time Range: 2.5 ms to 10.24 s\n
     */
    uint16_t scan_interval;
    /**
     * Amount of time for the duration of the LE scan. LE_Scan_Window\n
     * shall be less than or equal to LE_Scan_Interval\n
     * Range: 0x0004 to 0x4000\n
     * Time = N * 0.625 ms\n
     * Time Range: 2.5 ms to 10.24 s\n
     */
    uint16_t scan_window;
    /** Initiator_Filter_Policy */
    rtk_ble_conn_filter_t filter_policy;
    /** Peer_Address */
    rtk_ble_bd_addr_t peer_addr;
    /** Own_Address_Type */
    rtk_ble_addr_type_t own_addr_type;
    /** Connection paramters */
    rtk_ble_conn_param_t param;
} rtk_ble_create_conn_param_t;

/**
 * @struct    rtk_ble_disconn_param_t
 * @brief     Bluetooth LE GAP disconnection paramters definition.
 */
typedef struct {
    /** Connection_id */
    uint8_t conn_id;
} rtk_ble_disconn_param_t;

/**
 * @typedef   rtk_ble_wl_op_t
 * @brief     Bluetooth LE GAP whitelist operation type definition.
 */
typedef enum {
    RTK_BLE_WHITELIST_CLEAR,                /*!< Clear whitelist */
    RTK_BLE_WHITELIST_ADD,                  /*!< Add device to whitelist */
    RTK_BLE_WHITELIST_REMOVE,               /*!< Remove device from whitelist */
    RTK_BLE_WHITELIST_RESERVED,             /*!< All bigger value are reserved  */
} rtk_ble_wl_op_t;

/**
 * @struct    rtk_ble_wl_op_param_t
 * @brief     Bluetooth LE GAP whitelist operation paramters definition.
 */
typedef struct {
    rtk_ble_wl_op_t op;                     /*!< whitelist operation type */
    rtk_ble_bd_addr_t addr;                 /*!< device address */
} rtk_ble_wl_op_param_t;

/**
 * @struct    rtk_ble_read_rssi_param_t
 * @brief     Bluetooth LE GAP read rssi operation paramters definition.
 */
typedef struct {
    uint8_t conn_id;                        /*!< Connection_id */
} rtk_ble_read_rssi_param_t;

/**
 * @struct    rtk_ble_data_len_t
 * @brief     Bluetooth LE GAP data length paramters definition.
 */
typedef struct {
    /**
     * Preferred maximum number of payload octets that the local Controller\n
     * should include in a single LL Data PDU on this connection.\n
     * Range 0x001B to 0x00FB\n
     */
    uint16_t max_tx_octets;
    /**
     * Preferred maximum number of microseconds that the local Controller\n
     * should use to transmit a single Link Layer packet containing an LL\n
     * Data PDU on this connection.\n
     * Range 0x0148 to 0x4290\n
     */
    uint16_t max_tx_time;
} rtk_ble_data_len_t;

/**
 * @struct    rtk_ble_data_len_ind_t
 * @brief     Bluetooth LE GAP data length Change event paramters definition.
 */
typedef struct {
    /**
     * The maximum number of payload octets in a LLData PDU that the local\n
     * Controller will send on this connection.\n
     * Range 0x001B to 0x00FB\n
     */
    uint16_t max_tx_octets;
    /**
     * The maximum time that the local Controller will take to send a Link\n
     * Layer packet containing an LL Data PDU on this connection.\n
     * Range 0x0148 to 0x4290\n
     */
    uint16_t max_tx_time;
    /**
     * The maximum number of payload octets in a Link Layer packet that the\n
     * local Controller expects to receive on this connection.\n
     * Range 0x001B to 0x00FB\n
     */
    uint16_t max_rx_octets;
    /**
     * The maximum time that the local Controller expects to take to receive a\n
     * Link Layer packet on this connection.\n
     * Range 0x0148 to 0x4290\n
     */
    uint16_t max_rx_time;
} rtk_ble_data_len_ind_t;

/**
 * @struct    rtk_ble_conn_data_len_t
 * @brief     Bluetooth LE GAP set connection data length paramters definition.
 */
typedef struct {
    uint8_t conn_id;                /*!< Connection_id */
    rtk_ble_data_len_t data_len;    /*!< data length paramter */
} rtk_ble_conn_data_len_t;

/**
 * @struct    rtk_ble_conn_phy_info_t
 * @brief     Bluetooth LE GAP set connection phy info definition.
 */
typedef struct {
    /** 
     * Connection transmit PHY\n
     * 0x01 The transmitter PHY for the connection is LE 1M\n
     * 0x02 The transmitter PHY for the connection is LE 2M\n
     * 0x03 The transmitter PHY for the connection is LE Coded\n
     * All other values Reserved for future use\n
     */
	uint8_t tx_phy;
    /** 
     * Connection receive PHY\n
     * 0x01 The receiver PHY for the connection is LE 1M\n
     * 0x02 The receiver PHY for the connection is LE 2M\n
     * 0x03 The receiver PHY for the connection is LE Coded\n
     * All other values Reserved for future use\n
     */
	uint8_t rx_phy;
} rtk_ble_conn_phy_info_t;

/**
 * @struct    rtk_ble_conn_info_t
 * @brief     Bluetooth LE GAP connection info definition.
 */
typedef struct {
    /** Controller role */
    rtk_ble_link_role_t role;
	/** 
     * Destination (Remote) Identity Address or remote Resolvable Private\n
	 * Address (RPA) before identity has been resolved.\n
     */
	rtk_ble_bd_addr_t peer;
    /** Remote device address used during connection setup. */
	rtk_ble_bd_addr_t remote;
    /**
     * Connection interval used on this connection.\n
     * Range: 0x0006 to 0x0C80\n
     * Time = N * 1.25 ms\n
     * Time Range: 7.5 ms to 4000 ms.\n
     */
    uint16_t interval;
	/** 
     * Slave latency for the connection in number of connection events.\n
     * Range: 0x0000 to 0x01F3\n
     */
    uint16_t latency;
	/** 
     * Connection supervision timeout.
     * Range: 0x000A to 0x0C80
     * Time = N * 10 ms
     * Time Range: 100 ms to 32 s
     */
	uint16_t timeout;
    /** connection phy info */
	rtk_ble_conn_phy_info_t phy;
} rtk_ble_conn_info_t;

/**
 * @def       RTK_BLE_CHAN_MAP_LEN
 * @brief     Bluetooth LE channel map length.
 */
#define RTK_BLE_CHAN_MAP_LEN                5

/**
 * @typedef   rtk_ble_channels_t
 * @brief     Bluetooth LE channel map type definition.
 */
typedef uint8_t rtk_ble_channels_t[RTK_BLE_CHAN_MAP_LEN];

/**
 * @struct    rtk_ble_default_phy_param_t
 * @brief     Bluetooth LE GAP default phy paramter definition.
 */
typedef struct {
    /**
     * bit 0: The Host has no preference among the transmitter PHYs supported by the Controller
     * bit 1: The Host has no preference among the receiver PHYs supported by the Controller
     * All other bits Reserved for future use
     */
    uint8_t  prefer_all_phy;
    /**
     * bit 0: The Host prefers to use the LE 1M transmitter PHY (possibly among others)
     * bit 1: The Host prefers to use the LE 2M transmitter PHY (possibly among others)
     * bit 2: The Host prefers to use the LE Coded transmitter PHY (possibly among others)
     * All other bits Reserved for future use
     */
	uint8_t  prefer_tx_phy;
    /**
     * bit 0: The Host prefers to use the LE 1M receiver PHY (possibly among others)
     * bit 1: The Host prefers to use the LE 2M receiver PHY (possibly among others)
     * bit 2: The Host prefers to use the LE Coded receiver PHY (possibly among others)
     * All other bits Reserved for future use
     */
	uint8_t  prefer_rx_phy;
} rtk_ble_default_phy_param_t;

/**
 * @struct    rtk_ble_conn_phy_param_t
 * @brief     Bluetooth LE GAP connection phy paramter definition.
 */
typedef struct {
    uint8_t conn_id;                        /*!< Connection_id */
    rtk_ble_default_phy_param_t param;      /*!< Connection phy paramter */
    uint16_t options;                       /*!< Connection PHY options. */
} rtk_ble_conn_phy_param_t;

/**
 * @typedef   rtk_ble_privacy_mode_t
 * @brief     Bluetooth LE GAP privacy mode type definition.
 */
typedef enum {
    BLE_PRIVACY_MODE_NETWORK,               /*!< 0x00, Use Network Privacy Mode for this peer device (default) */
    BLE_PRIVACY_MODE_DEVICE,                /*!< 0x01, Use Device Privacy Mode for this peer device */
} rtk_ble_privacy_mode_t;

/**
 * @struct    rtk_ble_privacy_mode_param_t
 * @brief     Bluetooth LE GAP privacy mode paramter definition.
 */
typedef struct {
    rtk_ble_bd_addr_t addr;                 /*!< Peer_Identity_Address */
    rtk_ble_privacy_mode_t mode;            /*!< Privacy_Mode */
} rtk_ble_privacy_mode_param_t;

/**
 * @typedef   rtk_ble_adv_report_type_t
 * @brief     Bluetooth LE GAP adv type in adv report definition.
 */
typedef enum {
    RTK_BLE_EVT_CONN_ADV       = 0x00,      /*!< ADV_IND         */
    RTK_BLE_EVT_CONN_DIR_ADV   = 0x01,      /*!< ADV_DIRECT_IND  */
    RTK_BLE_EVT_DISC_ADV       = 0x02,      /*!< ADV_SCAN_IND    */
    RTK_BLE_EVT_NON_CONN_ADV   = 0x03,      /*!< ADV_NONCONN_IND */
    RTK_BLE_EVT_SCAN_RSP       = 0x04,      /*!< SCAN_RSP        */
} rtk_ble_adv_report_type_t;

/**
 * @struct    rtk_ble_adv_report_t
 * @brief     Bluetooth LE GAP adv report paramter definition.
 */
typedef struct {
    rtk_ble_adv_report_type_t evt_type;     /*!< adv type */
    rtk_ble_bd_addr_t addr;                 /*!< peer addr */
    uint8_t len;                            /*!< adv data len */
    uint8_t data[RTK_BLE_ADV_DATA_LEN];     /*!< adv data */
    int8_t rssi;                            /*!< adv rssi */
} rtk_ble_adv_report_t;

/**
 * @struct    rtk_ble_conn_param_ind_t
 * @brief     Bluetooth LE GAP adv report paramter definition.
 */
typedef struct {
    /**
     * Connection interval used on this connection.\n
     * Range: 0x0006 to 0x0C80\n
     * Time = N * 1.25 ms\n
     * Time Range: 7.5 ms to 4000 ms.\n
     */
    uint16_t conn_interval;
    /**
     * Slave latency for the connection in number of connection events.\n
     * Range: 0x0000 to 0x01F3\n
     */
    uint16_t conn_latency;
    /**
     * Connection supervision timeout.\n
     * Range: 0x000A to 0x0C80\n
     * Time = N * 10 ms\n
     * Time Range: 100 ms to 32 s\n
     */
    uint16_t timeout;
} rtk_ble_conn_param_ind_t;

/**
 * @typedef   rtk_ble_io_cap_flag_t
 * @brief     Bluetooth BLE SM IO capability type definition.
 */
typedef enum {
	RTK_IO_CAP_DISPALY_ONLY     = 0x00,     /*!< 0x00 DisplayOnly */
	RTK_IO_CAP_DISPLAY_YES_NO   = 0x01,     /*!< 0x01 DisplayYesNo */
	RTK_IO_CAP_KEYBOARD_ONLY    = 0x02,     /*!< 0x02 KeyboardOnly */
	RTK_IO_CAP_NO_IN_NO_OUT     = 0x03,     /*!< 0x03 NoInputNoOutput */
	RTK_IO_CAP_KEYBOARD_DISPALY = 0x04,     /*!< 0x04 KeyboardDisplay */
	RTK_IO_CAP_RESERVED         = 0x05,     /*!< 0x05-0xFF Reserved for future use */
} rtk_ble_io_cap_flag_t;


/**
 * @typedef   rtk_ble_oob_data_flag_t
 * @brief     Bluetooth BLE SM OOB data type definition.
 */
typedef enum {
	RTK_OOB_DATA_DISBALE        = 0x00,     /*!< 0x00 OOB data diable */
	RTK_OOB_DATA_ENABLE         = 0x01,     /*!< 0x01 OOB data enable */
	RTK_OOB_DATA_RESERVED       = 0x02,     /*!< 0x02-0xFF Reserved */
} rtk_ble_oob_data_flag_t;

/**
 * @typedef   rtk_bond_flag_t
 * @brief     Bluetooth BLE SM BONDING type definition.
 */
typedef enum {
	RTK_BONDING_DISABLE         = 0x00,     /*!< 0x00 No Bonding */
	RTK_BONDING_ENABLE          = 0x01,     /*!< 0x01 Bonding */
	RTK_BONDING_RESERVED        = 0x02,     /*!< 0x02-0xFF Reserved */
} rtk_bond_flag_t;

/**
 * @typedef   rtk_sec_pair_flag_t
 * @brief     Bluetooth BLE SM security connection pairing type definition.
 */
typedef enum {
	RTK_SECURITY_PAIR_DISABLE   = 0x00,     /*!< 0x00 security pairing disable */
	RTK_SECURITY_PAIR_ENABLE    = 0x01,     /*!< 0x00 security pairing enable */
	RTK_SECURITY_PAIR_RESERVED  = 0x02,     /*!< 0x02-0xFF Reserved */
} rtk_sec_pair_flag_t;

/**
 * @typedef   rtk_mitm_flag_t
 * @brief     Bluetooth BLE SM pairing MITM type definition.
 */
typedef enum {
    RTK_MITM_ON                 = 0x00,     /*!< 0x00 pairing MITM disable */
    RTK_MITM_OFF                = 0x01,     /*!< 0x00 pairing MITM enable */
    RTK_MITM_RESERVED           = 0x02,     /*!< 0x02-0xFF Reserved */
} rtk_mitm_flag_t;

/**
 * @typedef   rtk_fixed_key_flag_t
 * @brief     Bluetooth BLE SM fixed key type definition.
 */
typedef enum {
	RTK_FIXED_KEY_DISABLE       = 0x00,     /*!< 0x00 use fixed key disable */
	RTK_FIXED_KEY_ENABLE        = 0x01,     /*!< 0x00 use fixed key enable */
	RTK_FIXED_KEY_RESERVED      = 0x02,     /*!< 0x02-0xFF Reserved */
} rtk_fixed_key_flag_t;

/**
 * @struct    rtk_ble_sm_sec_parm_t
 * @brief     Bluetooth BLE SM security parameter type definition.
 */
typedef struct {
    rtk_ble_io_cap_flag_t   io_cap;         /*!< IO capabilities */
	rtk_ble_oob_data_flag_t oob_data;       /*!< OOB data flag */
	rtk_bond_flag_t         bond;           /*!< Bonding flag  */
    rtk_mitm_flag_t         mitm;           /*!< MITM flag  */
	rtk_sec_pair_flag_t     sec_pair;       /*!< Security pair flag  */
	rtk_fixed_key_flag_t    use_fixed_key;  /*!< Use fixed key flag */
	uint32_t                fixed_key;      /*!< Fixed key */
	uint8_t                 max_key_size;   /*!< Max key size */
} rtk_ble_sm_sec_parm_t;

/**
 * @struct    rtk_ble_pair_cfm_t
 * @brief     Bluetooth BLE SM pairing confirm parameter definition.
 */
typedef struct {
    uint8_t conn_id;                        /*!< Connection_id */
    uint8_t confirm;                        /*!< whether continue to pair, 0: stop pairing; 1: continue  */
} rtk_ble_pair_cfm_t;

/**
 * @def       RTK_BLE_SM_OOB_KEY_LEN
 * @brief     Bluetooth BLE SM OOB key len definition.
 */
#define RTK_BLE_SM_OOB_KEY_LEN              16

/**
 * @typedef   rtk_ble_oob_key_t
 * @brief     Bluetooth BLE SM OOB key definition.
 */
typedef uint8_t rtk_ble_oob_key_t[RTK_BLE_SM_OOB_KEY_LEN];

/**
 * @struct    rtk_ble_auth_oob_key_t
 * @brief     Bluetooth BLE SM OOB key definition.
 */
typedef struct {
	uint8_t conn_id;                        /*!< Connection_id */
	rtk_ble_oob_key_t oob_key;              /*!< oob_key */
} rtk_ble_auth_oob_key_t;

/**
 * @struct    rtk_ble_bond_info_t
 * @brief     Bluetooth BLE SM bond information type definition.
 */
typedef struct {
    rtk_ble_bd_addr_t bd_addr;              /*!< peer addr */
	uint8_t is_connected;                   /*!< whether connected */
} rtk_ble_bond_info_t;

/**
 * @struct    rtk_ble_conn_security_t
 * @brief     Bluetooth BLE SM start paramter definition.
 */
typedef struct {
	uint8_t conn_id;                        /*!< Connection_id */
} rtk_ble_conn_security_t;

/**
 * @struct    rtk_ble_auth_key_confirm_t
 * @brief     Bluetooth BLE SM key confirm definition.
 */
typedef struct {
	uint8_t conn_id;                        /*!< Connection_id */
	uint8_t accept;                         /*!< whether accept */
} rtk_ble_auth_key_confirm_t;

/**
 * @struct    rtk_ble_auth_key_input_t
 * @brief     Bluetooth BLE SM input auth key definition.
 */
typedef struct {
	uint8_t conn_id;                        /*!< Connection_id */
	uint32_t passkey;                       /*!< pairing passkey */
} rtk_ble_auth_key_input_t;

/**
 * @struct    rtk_ble_gap_default_param_value_t
 * @brief     Bluetooth BLE GAP default paramter definition.
 */
typedef union {
    uint16_t mtu_size;                      /*!< MTU size */
    rtk_ble_data_len_t dft_data_len;        /*!< Connection_id */
    rtk_ble_default_phy_param_t dft_phy;    /*!< default phy paramter */
} rtk_ble_gap_default_param_value_t;

/**
 * @typedef   rtk_ble_gap_evt_code_t
 * @brief     Bluetooth ble gap event code definition
 * @note      RTK_BLE_EVT_xxx_DONE represents that the API act can be done imediately\n
 * (e.g. RTK_BLE_EVT_SET_APPEARANCE_DONE) or will generate a hci_command_complete_event\n
 * (e.g. RTK_BLE_EVT_START_ADV_DONE). RTK_BLE_EVT_xxx_DONE is always related to an API act.\n
 * RTK_BLE_EVT_xxx_IND represents that a specific hci command complete event happen,\n
 * (e.g. RTK_BLE_EVT_CONNECT_IND comes with hci_le_connection_complete_event ), it may\n 
 * be caused by API act, by controller or by remote device. So, RTK_BLE_EVT_xxx_IND\n
 * is not necessarily related to an API act.\n
 * RTK_BLE_EVT_xxx_IND may also represent other information the stack need to indicate\n
 * user app layer and require user to do something(e.g. RTK_BLE_EVT_AUTH_PASSKEY_DISPLAY_IND).\n
 * When the field "process_ret" of the event param returned with RTK_BLE_EVT_xxx_DONE/IND is\n
 * nonzero, it represents that the process of the API act related to this event failed.\n
*/
typedef enum {
    RTK_BLE_EVT_SET_DEVICE_NAME_DONE,           /*!< comes when rtk_ble_gap_set_device_name is done */  
    RTK_BLE_EVT_SET_APPEARANCE_DONE,            /*!< comes when rtk_ble_gap_set_appearance is done */
    RTK_BLE_EVT_SET_RAND_ADDR_DONE,             /*!< comes when rtk_ble_gap_set_rand_addr is done */
    RTK_BLE_EVT_SET_ADV_DATA_DONE,              /*!< comes when rtk_ble_gap_set_adv_data is done */
    RTK_BLE_EVT_SET_SCAN_RSP_DATA_DONE,         /*!< comes when rtk_ble_gap_set_scan_rsp_data is done */
    RTK_BLE_EVT_START_ADV_DONE,                 /*!< comes when rtk_ble_gap_start_adv is done */
    RTK_BLE_EVT_STOP_ADV_DONE,                  /*!< comes when rtk_ble_gap_stop_adv is done */
    RTK_BLE_EVT_ADV_STOPPED_IND,                /*!< indicates adv is stopped due to connection or high duty timeout */
    RTK_BLE_EVT_SET_SCAN_PARAM_DONE,            /*!< comes when rtk_ble_gap_set_scan_param is done */
    RTK_BLE_EVT_START_SCAN_DONE,                /*!< comes when rtk_ble_gap_start_scan is done */
    RTK_BLE_EVT_SCAN_RES_IND,                   /*!< reports the adv data scanned by device */
    RTK_BLE_EVT_STOP_SCAN_DONE,                 /*!< comes when rtk_ble_gap_stop_scan is done */
    RTK_BLE_EVT_CONNECT_IND,                    /*!< comes when rtk_ble_gap_connect is done or indicates a connection is established by remote */
    RTK_BLE_EVT_DISCONNECT_IND,                 /*!< comes when rtk_ble_gap_disconnect is done or indicates link is disconnected by remote */
    RTK_BLE_EVT_UPDATE_CONN_IND,                /*!< comes when rtk_ble_gap_update_conn_param is done or indicates conn param is updated following remote request */
    RTK_BLE_EVT_UPDATE_CONN_REMOTE_IND,         /*!< indicates the request of update conn param from remote */
    RTK_BLE_EVT_MODIFY_WHITE_LIST_DONE,         /*!< comes when rtk_ble_gap_modify_whitelist is done */
    RTK_BLE_EVT_READ_RSSI_DONE,                 /*!< comes when rtk_ble_gap_read_rssi is done */
    RTK_BLE_EVT_SET_CHAN_MAP_DONE,              /*!< comes when rtk_ble_gap_set_channels is done */
    RTK_BLE_EVT_WRITE_DEFAULT_DATA_LEN_DONE,    /*!< comes when rtk_ble_gap_write_default_data_len is done */
    RTK_BLE_EVT_SET_DATA_LEN_DONE,              /*!< comes when rtk_ble_gap_set_data_len is done */
    RTK_BLE_EVT_UPDATE_DATA_LEN_IND,            /*!< indicates data len is updated by controller */
    RTK_BLE_EVT_UPDATE_PHY_IND,                 /*!< comes when rtk_ble_gap_set_phy is done or indicates phy is updated by controller autonomously */
    RTK_BLE_EVT_SET_PRIVACY_ENABLE_DONE,        /*!< comes when rtk_ble_gap_set_privacy is done */
    RTK_BLE_EVT_SET_PRIVACY_MODE_DONE,          /*!< comes when rtk_ble_gap_set_privacy_mode is done */
    RTK_BLE_EVT_SET_SEC_PARAM_DONE,             /*!< comes when rtk_ble_sm_set_security_param is done */
    RTK_BLE_EVT_AUTH_PAIRING_CONFIRM_IND,       /*!< indicates user app to confirm if approve the just work pairing */
    RTK_BLE_EVT_AUTH_PASSKEY_DISPLAY_IND,       /*!< indicates user app to display the passkey */
    RTK_BLE_EVT_AUTH_PASSKEY_INPUT_IND,         /*!< indicates user app to input the passkey */
    RTK_BLE_EVT_AUTH_PASSKEY_CONFIRM_IND,       /*!< indicates user app to comfirm if the passkey comparison is correct */
    RTK_BLE_EVT_AUTH_OOB_KEY_INPUT_IND,         /*!< indicates user app to input te oob tk in legacy pairing */
    RTK_BLE_EVT_AUTH_COMPLETE_IND,              /*!< comes when rtk_ble_sm_start_security is done or indicates the pairing initiated by remote is completed */
    RTK_BLE_EVT_DELETE_BOND_DEVICE_DONE,        /*!< comes when rtk_ble_sm_delete_bond is done */
    RTK_BLE_EVT_CLEAR_BOND_DEVICE_DONE,         /*!< comes when rtk_ble_sm_clear_bond is done */
} rtk_ble_gap_evt_code_t;

/**
 * @struct    rtk_ble_set_dev_name_done_t
 * @brief     Bluetooth BLE GAP set name done event definition (ASYNC).
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_set_dev_name_done_t;

/**
 * @struct    rtk_ble_set_appearance_done_t
 * @brief     Bluetooth BLE GAP set appearance done event definition (ASYNC).
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_set_appearance_done_t;

/**
 * @struct    rtk_ble_set_rand_addr_done_t
 * @brief     Bluetooth BLE GAP set rand addr done event definition (ASYNC).
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_set_rand_addr_done_t;

/**
 * @struct    rtk_ble_set_adv_data_done_t
 * @brief     Bluetooth BLE GAP set adv data done event definition (ASYNC).
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_set_adv_data_done_t;

/**
 * @struct    rtk_ble_set_scan_rsp_done_t
 * @brief     Bluetooth BLE GAP set scan response data done event definition (ASYNC).
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_set_scan_rsp_done_t;

/**
 * @struct    rtk_ble_start_adv_done_t
 * @brief     Bluetooth BLE GAP start adv done event definition (ASYNC).
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_start_adv_done_t;

/**
 * @struct    rtk_ble_stop_adv_done_t
 * @brief     Bluetooth BLE GAP stop adv done event definition (ASYNC).
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_stop_adv_done_t;

/**
 * @typedef   rtk_bt_evt_adv_stop_ind_cause_t
 * @brief     Bluetooth Advertising stop event cause.
 */
typedef enum {
    RTK_BT_EVT_CAUSE_ADV_STOPPED_BY_CONN = 0,   /*!< 0, because connection start */
    RTK_BT_EVT_CAUSE_ADV_STOPPED_BY_DURATION,   /*!< 1, because duration timeout */
} rtk_bt_evt_adv_stop_ind_cause_t;

/**
 * @struct    rtk_ble_adv_stopped_ind_t
 * @brief     Bluetooth Advertising stopped reason.
 */
typedef struct {
    rtk_bt_evt_adv_stop_ind_cause_t cause;      /*!< cause */
} rtk_ble_adv_stopped_ind_t;

/**
 * @struct    rtk_ble_set_scan_param_done_t
 * @brief     Bluetooth set scan done result.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_set_scan_param_done_t;

/**
 * @struct    rtk_ble_start_scan_done_t
 * @brief     Bluetooth start scan done result.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_start_scan_done_t;

/**
 * @struct    rtk_ble_scan_res_ind_t
 * @brief     Bluetooth scan result.
 */
typedef struct {
    uint8_t num_report;                         /*!< Number in adv report */
    rtk_ble_adv_report_t adv_report;            /*!< adv report data */
} rtk_ble_scan_res_ind_t;

/**
 * @struct    rtk_ble_stop_scan_done_t
 * @brief     Bluetooth stop scan result.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_stop_scan_done_t;

/**
 * @struct    rtk_ble_conn_ind_t
 * @brief     Bluetooth connection complete result.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
    rtk_bt_hci_err_t status;                    /*!< if process_ret == RTK_BT_EVT_ERR_HCI_EVT, give the hci_err code */
    rtk_ble_link_role_t role;                   /*!< controller role in the link */
    uint8_t conn_id;                            /*!< connection id */
    rtk_ble_bd_addr_t addr;                     /*!< peer addr */
    rtk_ble_conn_param_ind_t param;             /*!< connection paramters */
} rtk_ble_conn_ind_t;

/**
 * @struct    rtk_ble_disconn_ind_t
 * @brief     Bluetooth disconnection complete result.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
    rtk_bt_hci_err_t status;                    /*!< if process_ret == RTK_BT_EVT_ERR_HCI_EVT, give the hci_err code */
    rtk_bt_hci_err_t reason;                    /*!< give the reason for disconnection */
    rtk_ble_link_role_t role;                   /*!< controller role in the link */
    uint8_t conn_id;                            /*!< connection id */
    rtk_ble_bd_addr_t addr;                     /*!< peer addr */
} rtk_ble_disconn_ind_t;

/**
 * @struct    rtk_ble_update_conn_remote_ind_t
 * @brief     Bluetooth update connection from remote result.
 */
typedef struct {
    uint8_t accept;                             /*!< whether host stack accept the remote conn param update request, 0: reject; 1: accept */
    uint8_t conn_id;                            /*!< connection id */
    rtk_ble_bd_addr_t addr;                     /*!< peer addr */
    rtk_ble_conn_param_t param;                 /*!< connection parameter */
} rtk_ble_update_conn_remote_ind_t;

/**
 * @struct    rtk_ble_update_conn_ind_t
 * @brief     Bluetooth update connection complete result.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
    rtk_bt_hci_err_t status;                    /*!< event process hci status */
    uint8_t conn_id;                            /*!< connection id */
    rtk_ble_bd_addr_t addr;                     /*!< peer addr */
    rtk_ble_conn_param_ind_t param;             /*!< connection parameter */
} rtk_ble_update_conn_ind_t;

/**
 * @struct    rtk_ble_modify_whitelist_done_t
 * @brief     Bluetooth whitelist operation complete result.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
    rtk_ble_wl_op_t op;                         /*!< whitelist operation */
} rtk_ble_modify_whitelist_done_t;

/**
 * @struct    rtk_ble_read_rssi_done_t
 * @brief     Bluetooth read rssi complete result.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
    uint8_t conn_id;                            /*!< connection id */
    int8_t rssi;                                /*!< connection rssi */
} rtk_ble_read_rssi_done_t;

/**
 * @struct    rtk_ble_set_chan_map_done_t
 * @brief     Bluetooth set channel map complete result.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_set_chan_map_done_t;

/**
 * @struct    rtk_ble_write_def_data_len_done_t
 * @brief     Bluetooth set default data length complete result.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_write_def_data_len_done_t;

/**
 * @struct    rtk_ble_set_data_len_done_t
 * @brief     Bluetooth set connection data len complete result.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
    uint8_t conn_id;                            /*!< connection id */
} rtk_ble_set_data_len_done_t;

/**
 * @struct    rtk_ble_update_data_len_ind_t
 * @brief     Bluetooth update connection data len indicate result.
 */
typedef struct {
    uint8_t conn_id;                            /*!< connection id */
    rtk_ble_data_len_ind_t data_len;            /*!< data length */
} rtk_ble_update_data_len_ind_t;

/**
 * @struct    rtk_ble_set_def_phy_done_t
 * @brief     Bluetooth set default phy done result.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_set_def_phy_done_t;

/**
 * @struct    rtk_ble_set_phy_done_t
 * @brief     Bluetooth set phy done result.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_set_phy_done_t;

/**
 * @struct    rtk_ble_update_phy_ind_t
 * @brief     Bluetooth set phy done result.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
    rtk_bt_hci_err_t status;                    /*!< event process hci status */
    uint8_t conn_id;                            /*!< connection id */
    rtk_ble_bd_addr_t addr;                     /*!< peer addr */
    rtk_ble_conn_phy_info_t phy_info;           /*!< phy info */
} rtk_ble_update_phy_ind_t;

/**
 * @struct    rtk_ble_set_privacy_done_t
 * @brief     Bluetooth set privacy done result.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_set_privacy_done_t;

/**
 * @struct    rtk_ble_set_privacy_mode_done_t
 * @brief     Bluetooth set privacy mode done result.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_set_privacy_mode_done_t;

/**
 * @struct    rtk_ble_set_sec_param_done_t
 * @brief     Bluetooth set security parameter done result.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_set_sec_param_done_t;

/**
 * @struct    rtk_ble_auth_pair_cfm_ind_t
 * @brief     Bluetooth confirm auth pair paramter.
 */
typedef struct {
    uint8_t conn_id;                            /*!< connection id */
    rtk_ble_bd_addr_t addr;                     /*!< peer addr */
} rtk_ble_auth_pair_cfm_ind_t;

/**
 * @struct    rtk_ble_auth_key_display_ind_t
 * @brief     Bluetooth key display indicate.
 */
typedef struct {
    uint8_t conn_id;                            /*!< connection id */
    rtk_ble_bd_addr_t addr;                     /*!< peer addr */
    uint32_t passkey;                           /*!< passkey */
} rtk_ble_auth_key_display_ind_t;

/**
 * @struct    rtk_ble_auth_key_input_ind_t
 * @brief     Bluetooth key input indicate.
 */
typedef struct {
    uint8_t conn_id;                            /*!< connection id */
    rtk_ble_bd_addr_t addr;                     /*!< peer addr */
} rtk_ble_auth_key_input_ind_t;

/**
 * @struct    rtk_ble_auth_key_cfm_ind_t
 * @brief     Bluetooth key confirm indicate.
 */
typedef struct {
    uint8_t conn_id;                            /*!< connection id */
    rtk_ble_bd_addr_t addr;                     /*!< peer addr */
    uint32_t passkey;                           /*!< passkey */
} rtk_ble_auth_key_cfm_ind_t;

/**
 * @struct    rtk_ble_auth_oob_input_ind_t
 * @brief     Bluetooth oob input indicate.
 */
typedef struct {
    uint8_t conn_id;                            /*!< connection id */
    rtk_ble_bd_addr_t addr;                     /*!< peer addr */
} rtk_ble_auth_oob_input_ind_t;

/**
 * @struct    rtk_ble_auth_complete_ind_t
 * @brief     Bluetooth auth completed indicate.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
    uint8_t reason;                             /*!< error code of pairing, 0: pairing success; 1~0xFF: smp_err code */
    uint8_t conn_id;                            /*!< connection id */
    rtk_ble_bd_addr_t addr;                     /*!< peer addr */
} rtk_ble_auth_complete_ind_t;

/**
 * @struct    rtk_ble_del_bond_dev_done_t
 * @brief     Bluetooth delete bond device completed indicate.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_del_bond_dev_done_t;

/**
 * @struct    rtk_ble_clr_bond_dev_done_t
 * @brief     Bluetooth clear bond device completed indicate.
 */
typedef struct {
    rtk_bt_evt_status_t process_ret;            /*!< event process result */
} rtk_ble_clr_bond_dev_done_t;

/**
 * @typedef   rtk_ble_gap_cb_t
 * @brief     BLE GAP event callback.
 * @param[in] evt_code: Event code
 * @param[in] param: Event parameters
 *
 */
typedef void (*rtk_ble_gap_cb_t)(rtk_ble_gap_evt_code_t evt_code, void* param);

/**
 * @defgroup  ble_gap BLE GAP APIs
 * @brief     BT LE related function APIs
 * @ingroup   BT_APIs
 * @{
 */

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_register_callback(rtk_ble_gap_cb_t cb)
 * @brief     Register BLE GAP event callback [SYNC].
 * @param[in] cb: The BLE GAP event callback
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_register_callback(rtk_ble_gap_cb_t cb);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_unregister_callback(void)
 * @brief     Unregister BLE GAP event callback [SYNC].
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_unregister_callback(void);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_set_default_param(rtk_ble_gap_default_param_type_t type, rtk_ble_gap_default_param_value_t *param)
 * @brief     Set default BLE GAP param before stack started [SYNC].
 * @param[in] type: The default BLE GAP param type
 * @param[in] param: BLE GAP param value need to be set
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_set_default_param(rtk_ble_gap_default_param_type_t type, 
                                           rtk_ble_gap_default_param_value_t *param);
/**
 * @fn        rtk_bt_err_t rtk_ble_gap_get_address(rtk_ble_bd_addr_t* addr)
 * @brief     Get bluetooth identity [SYNC].
 * @param[out] addr: Device address under use [need free]
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_get_address(rtk_ble_bd_addr_t* addr);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_set_device_name(const uint8_t* name)
 * @brief     Set bluetooth Device name [ASYNC].
 * @param[in] name: Device name
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_set_device_name(const uint8_t* name);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_set_appearance(rtk_bt_appearance_t appearance)
 * @brief     Set device appearance [ASYNC].
 * @param[in] appearance: Device apperanc
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_set_appearance(rtk_bt_appearance_t appearance);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_set_rand_addr(rtk_ble_bd_addr_t* bd_addr)
 * @brief     Set random address [ASYNC].
 * @param[in] bd_addr: Random address
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_set_rand_addr(rtk_ble_bd_addr_t* bd_addr);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_set_adv_data(rtk_ble_adv_data_t* adv_data)
 * @brief     Set BLE GAP advertising data [ASYNC].
 * @param[in] adv_data: Advertising data
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_set_adv_data(rtk_ble_adv_data_t* adv_data);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_set_scan_rsp_data(rtk_ble_scan_rsp_data_t* data)
 * @brief     Set BLE GAP scan response data [ASYNC].
 * @param[in] data: Scan response data
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_set_scan_rsp_data(rtk_ble_scan_rsp_data_t* data);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_start_adv(rtk_ble_adv_param_t* param)
 * @brief     Start BLE GAP advertising [ASYNC].
 * @param[in] param: Advertising parameters
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_start_adv(rtk_ble_adv_param_t* param);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_stop_adv(void)
 * @brief     Stop BLE GAP advertising [ASYNC].
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_stop_adv(void);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_set_scan_param(rtk_ble_scan_param_t* param)
 * @brief     Set scan paramters [ASYNC].
 * @param[in] param: Scan paramters
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_set_scan_param(rtk_ble_scan_param_t* param);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_start_scan(rtk_ble_scan_option_t* option)
 * @brief     Start scan [ASYNC].
 * @param[in] option: Scan options
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_start_scan(rtk_ble_scan_option_t* option);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_stop_scan(void)
 * @brief     Stop scan [ASYNC].
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_stop_scan(void);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_connect(rtk_ble_create_conn_param_t* param)
 * @brief     Start connection [ASYNC].
 * @param[in] param: Connection parmaters
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_connect(rtk_ble_create_conn_param_t* param);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_disconnect(rtk_ble_disconn_param_t* param)
 * @brief     Start disconnection [ASYNC].
 * @param[in] param: The parameters of disconnect.
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_disconnect(rtk_ble_disconn_param_t* param);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_update_conn_param(rtk_ble_update_conn_param_t* param)
 * @brief     Update connection paramters [ASYNC].
 * @param[in] param: Updated connection parmaters
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_update_conn_param(rtk_ble_update_conn_param_t* param);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_modify_whitelist(rtk_ble_wl_op_param_t* op_param)
 * @brief     Modify device white list [ASYNC].
 * @param[in] op_param: Modification operation paramters
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_modify_whitelist(rtk_ble_wl_op_param_t* op_param);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_get_whitelist_size(uint16_t *len)
 * @brief     Get length of white list in device [SYNC].
 * @param[out] len: The length of white list
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_get_whitelist_size(uint16_t *len);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_read_rssi(rtk_ble_read_rssi_param_t* param)
 * @brief     Read specific connection RSSI [ASYNC].
 * @param[in] param: Parameters used by Reading RSSI
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_read_rssi(rtk_ble_read_rssi_param_t* param);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_get_conn_info(uint8_t conn_id, rtk_ble_conn_info_t* info)
 * @brief     Get connection information [SYNC].
 * @param[in] conn_id: Connection ID
 * @param[out] info: Connection information
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_get_conn_info(uint8_t conn_id, rtk_ble_conn_info_t* info);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_set_channels(rtk_ble_channels_t chan_map)
 * @brief     Set Bluetooth device channel map [ASYNC].
 * @param[in] chan_map: Channel map
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_set_channels(rtk_ble_channels_t chan_map);

#if RTK_BLE_4_2_DATA_LEN_EXT_SUPPORT
/**
 * @fn        rtk_bt_err_t rtk_ble_gap_write_default_data_len(rtk_ble_data_len_t* param)
 * @brief     Write Bluetooth device default data length paramters [ASYNC].
 * @param[in] param: Default data length paramters
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_write_default_data_len(rtk_ble_data_len_t* param);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_set_data_len(rtk_ble_conn_data_len_t* param)
 * @brief     Set Bluetooth device connection data length paramters [ASYNC].
 * @param[in] param: Connection data length paramters
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_set_data_len(rtk_ble_conn_data_len_t* param);
#endif  /*!< RTK_BLE_4_2_DATA_LEN_EXT_SUPPORT */

#if defined(RTK_BLE_5_0_SET_PHYS_SUPPORT) && (RTK_BLE_5_0_SET_PHYS_SUPPORT)
/**
 * @fn        rtk_bt_err_t rtk_ble_gap_set_phy(rtk_ble_conn_phy_param_t* phy_param)
 * @brief     Set Bluetooth device PHY paramters [ASYNC].
 * @param[in] phy_param: PHY paramters
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_set_phy(rtk_ble_conn_phy_param_t* phy_param);
#endif  /*!< RTK_BLE_5_0_SET_PHYS_SUPPORT */

#if RTK_BLE_PRIVACY_SUPPORT
/**
 * @fn        rtk_bt_err_t rtk_ble_gap_set_privacy(uint8_t enable)
 * @brief     Enable or disbale privacy [ASYNC].
 * @param[in] enable: Flag of enable
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_set_privacy(uint8_t enable);

/**
 * @fn        rtk_bt_err_t rtk_ble_gap_set_privacy_mode(rtk_ble_privacy_mode_param_t* param)
 * @brief     Set privacy mode in one resolving list [ASYNC].
 * @param[in] param: Privacy mode parameters
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_gap_set_privacy_mode(rtk_ble_privacy_mode_param_t* param);
#endif  /*!< RTK_BLE_PRIVACY_SUPPORT */

/**
 * @fn        rtk_bt_err_t rtk_ble_sm_set_security_param(rtk_ble_sm_sec_parm_t* param)
 * @brief     Set security paramters [ASYNC].
 * @param[in] param: Security paramters
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_sm_set_security_param(rtk_ble_sm_sec_parm_t* param);

/**
 * @fn        rtk_bt_err_t rtk_ble_sm_start_security(rtk_ble_conn_security_t* param)
 * @brief     Start security level [ASYNC].
 * @param[in] param: Security level
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_sm_start_security(rtk_ble_conn_security_t* param);

/**
 * @fn        rtk_bt_err_t rtk_ble_sm_pairing_confirm(rtk_ble_pair_cfm_t *param)
 * @brief     Start security level [ASYNC NO RESP].
 * @param[in] param: Security level
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_sm_pairing_confirm(rtk_ble_pair_cfm_t *param);

/**
 * @fn        rtk_bt_err_t rtk_ble_sm_passkey_entry(rtk_ble_auth_key_input_t* param)
 * @brief     Input the authentication key [ASYNC].
 * @param[in] param: Auth key input parameter
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_sm_passkey_entry(rtk_ble_auth_key_input_t* param);

/**
 * @fn        rtk_bt_err_t rtk_ble_sm_passkey_confirm(rtk_ble_auth_key_confirm_t* param)
 * @brief     Confirm the authentication key [ASYNC].
 * @param[in] param: Auth key confirmation parameter
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_sm_passkey_confirm(rtk_ble_auth_key_confirm_t* param);

#if RTK_BLE_SMP_OOB_SUPPORT
/**
 * @fn        rtk_bt_err_t rtk_ble_sm_set_oob_tk(rtk_ble_auth_oob_key_t* param)
 * @brief     Set OOB data [ASYNC].
 * @param[in] param: OOB data
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_sm_set_oob_tk(rtk_ble_auth_oob_key_t* param);
#endif  /*!< RTK_BLE_SMP_OOB_SUPPORT */

/**
 * @fn        rtk_bt_err_t rtk_ble_sm_get_bond_num(uint8_t* bond_num)
 * @brief     Get the number of bonded device [SYNC].
 * @param[out] bond_num: The number of bonded device
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_sm_get_bond_num(uint8_t* bond_num);

/**
 * @fn        rtk_bt_err_t rtk_ble_sm_get_bond_info(rtk_ble_bond_info_t* info, uint8_t *size, uint8_t *actual)
 * @brief     Get bonded device info [SYNC].
 * @param[in] info: The info of bonded device
 * @param[in] size: The size of bonded device we want get (buffer size of info)
 * @param[out] size: The size of bonded device we really get in info
 * @param[out] actual: The actual size of bonded device in BT stack
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_sm_get_bond_info(rtk_ble_bond_info_t* info, uint8_t *size, uint8_t *actual);

/**
 * @fn        rtk_bt_err_t rtk_ble_sm_delete_bond(rtk_ble_bd_addr_t* bd_addr)
 * @brief     Remove bonded device for bonded list [ASYNC].
 * @param[in] bd_addr: The address of bonded device
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_sm_delete_bond(rtk_ble_bd_addr_t* bd_addr);

/**
 * @fn        rtk_bt_err_t rtk_ble_sm_clear_bond(void)
 * @brief     Clear bonded list [ASYNC].
 * @return    
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_ble_sm_clear_bond(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /*!< __RTK_BLE_GAP_H__ */