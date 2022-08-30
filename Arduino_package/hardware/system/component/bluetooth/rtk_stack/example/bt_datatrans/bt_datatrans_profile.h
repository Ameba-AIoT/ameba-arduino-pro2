/**
*****************************************************************************************
*     Copyright(c) 2016, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file     datatrans_profile.h
  * @brief
  * @details
  * @author
  * @date
  * @version
  * *************************************************************************************
  */

/* Define to prevent recursive inclusion */
#ifndef _BT_DATATRANS_PORFILE_H_
#define _BT_DATRTRANS_PROFILE_H_

#ifdef __cplusplus
extern "C"  {
#endif      /* __cplusplus */

/* Add Includes here */
#include "profile_server.h"

/** @addtogroup SIMP SIMP
  * @brief Simple BLE Profile
  * @{
  */

/** @defgroup SIMP_Service SIMP Service
  * @brief Simple BLE Service
  * @{
  */

/** @defgroup SIMP_Service_Exported_Constants SIMP Service Exported Constants
  * @brief macros that other .c files may use all defined here
  * @{
  */

/** @defgroup SIMP_UUIDs SIMP UUIDs
  * @brief Simple BLE Profile UUID definitions
  * @{
  */
#define GATT_UUID_CHAR_DATA             0xFFE1
#define GATT_UUID_CHAR_DATA_NOTIFY      0xFFE2
#define GATT_UUID_FLOW_CTRL_NOTIFY      0xFFE3
/** @} End of SIMP_UUIDs */

///@cond
/** @brief  Index of each characteristic in Demo Profile service database. */
#define GATT_UUID_CHAR_DATA_INDEX               0x02
#define GATT_UUID_CHAR_DATA_NOTIFY_INDEX        0x04
#define GATT_UUID_CHAR_DATA_CCCD_INDEX          (GATT_UUID_CHAR_DATA_NOTIFY_INDEX + 1)
#define GATT_UUID_CHAR_FLOW_NOTIFY_INDEX        0x07
#define GATT_UUID_CHAR_FLOW_CCCD_INDEX          (GATT_UUID_CHAR_FLOW_NOTIFY_INDEX + 1)
///@endcond

#define DTS_DATA_NOTIFY_DISABLE 0
#define DTS_DATA_NOTIFY_ENABLE  1
#define DTS_FLOW_NOTIFY_DISABLE 2
#define DTS_FLOW_NOTIFY_ENABLE  3
#define DTS_FLOW_READ_PARA      4
#define DTS_WRITE_CHAR_DATA     5
#define DTS_WRITE_FLOW_PARA     6
typedef enum
{
    DTS_FLOW_INFO
} T_DTS_PARAM_TYPE;

typedef struct
{
    uint32_t lenth;
    uint8_t info[32];
} _T_Feature_Info;
/** @} End of SIMP_Service_Exported_Constants */

/** @defgroup SIMP_Service_Exported_Types SIMP Service Exported Types
  * @brief  types that other.c files may use all defined here
  * @{
  */

/** @defgroup TSIMP_WRITE_MSG TSIMP_WRITE_MSG
  * @brief Simple BLE service written msg to application.
  * @{
  */
//typedef struct _TSIMP_WRITE_MSG
//{
//    uint8_t opcode; //!< ref: @ref SIMP_Control_Point_OpCodes, @ref SIMP_Service_Write_Info
//    T_WRITE_TYPE write_type;
//    uint16_t len;
//    uint8_t *pValue;
//} TSIMP_WRITE_MSG;
/** @} End of TSIMP_WRITE_MSG */


/** @defgroup TSIMP_UPSTREAM_MSG_DATA TSIMP_UPSTREAM_MSG_DATA
  * @brief Simple BLE service callback message content.
  * @{
  */
//typedef union _TSIMP_UPSTREAM_MSG_DATA
//{
//    uint8_t notification_indification_index; //!< ref: @ref SIMP_Service_Notify_Indicate_Info
//    uint8_t read_value_index; //!< ref: @ref SIMP_Service_Read_Info
//    TSIMP_WRITE_MSG write;
//} TSIMP_UPSTREAM_MSG_DATA;
/** @} End of TSIMP_UPSTREAM_MSG_DATA */

/** @defgroup TSIMP_CALLBACK_DATA TSIMP_CALLBACK_DATA
  * @brief Simple BLE service data to inform application.
  * @{
  */
//typedef struct _TSIMP_CALLBACK_DATA
//{
//    T_SERVICE_CALLBACK_TYPE     msg_type;
//    uint8_t                    conn_id;
//    TSIMP_UPSTREAM_MSG_DATA    msg_data;
//} TSIMP_CALLBACK_DATA;
/** @} End of TSIMP_CALLBACK_DATA */

typedef union
{
    uint8_t notification_indification_index;
    uint8_t read_index;
    uint32_t write_index;
} T_DTS_UPSTREAM_MSG_INDEX;
typedef struct
{
    uint8_t len;
    uint8_t *data;
} T_DTS_UPSTREAM_MSG_DATA;
typedef struct _TDTS_CALLBACK_DATA
{
    T_SERVICE_CALLBACK_TYPE     msg_type;                    /**<  @brief EventId defined upper */
    T_DTS_UPSTREAM_MSG_INDEX    msg_index;
    T_DTS_UPSTREAM_MSG_DATA     msg_data;
} T_DTS_CALLBACK_DATA;

/** @} End of SIMP_Service_Exported_Types */

/** @defgroup SIMP_Service_Exported_Functions SIMP Service Exported Functions
  * @brief functions that other .c files may use all defined here
  * @{
  */
//extern void Datatrans_SettingServiceUUID(void);
extern T_SERVER_ID Datatrans_AddService(void *pFunc);
bool dts_set_flow_info_parameter(T_DTS_PARAM_TYPE param_type, uint8_t length, uint8_t *p_value);
/** @} End of SIMP_Service_Exported_Functions */

/** @} End of SIMP_Service */

/** @} End of SIMP */

#ifdef __cplusplus
}
#endif

#endif
