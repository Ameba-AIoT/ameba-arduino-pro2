/**
*********************************************************************************************************
*               Copyright(c) 2016, Realtek Semiconductor Corporation. All rights reserved.
*********************************************************************************************************
* @file      multilink_manager.h
* @brief     Define multilink manager struct and functions.
* @details
* @author    jane
* @date      2016-02-18
* @version   v0.1
* *********************************************************************************************************
*/
//#include "bt_datatrans_app_flags.h"
//#if CENTRAL_MODE
#ifndef _BT_DATATRANS_MULTILINK_MANAGER_H_
#define _BT_DATATRANS_MULTILINK_MANAGER_H_
#include "app_msg.h"
#include "gap_conn_le.h"
#include "bt_datatrans_app_flags.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Add Includes here */
//#include "rtl876x.h"
#include "profile_client.h"
//#include "rtl876x_flash_storage.h"

/** @brief  Define links number. range: 0-4 */
//#define APP_MAX_LINKS  1
/** @brief  Define handle cache table length. */
#define APP_HDL_CACHE_LEN 24
/** @brief  Define start offset of the falsh to save GATT Server information. */
#define APP_GATT_SERVER_INFO_FLASH_OFFSET 0
/** @brief  Define device list table size. */
#define BT_DATATRANS_APP_MAX_DEVICE_INFO 10

/**
 * @brief  GATT Serve information struct.
 */
typedef struct
{
    uint16_t     uuid16;
    uint8_t      bd_addr[GAP_BD_ADDR_LEN];  /**< remote BD */
    uint8_t      bd_type;         /**< remote BD type*/
    uint8_t      reserved[3];     /**< used to TGattServerInfo four byte alignment*/
    uint16_t     hdl_cache[APP_HDL_CACHE_LEN];
} TGattServerInfo;

/**
 * @brief  Application Link control block defination.
 */
typedef struct
{
    T_GAP_CONN_STATE conn_state;  /**<  Connection state. */
    T_CLIENT_ID     client_id;
    uint8_t       end_handle_idx;
    uint8_t       disc_state;
    uint8_t       state;
    TGattServerInfo server_info;
} TAppLinkCB;

typedef struct
{
    uint8_t      bd_addr[GAP_BD_ADDR_LEN];
    uint8_t      bd_type;
} TDevInfo;
/** @brief  App link table */
extern TAppLinkCB DataTransLinkTable[BT_DATATRANS_APP_MAX_LINKS];
/** @brief  Device list table, used to save discovered device informations. */
extern TDevInfo DT_DevList[BT_DATATRANS_APP_MAX_DEVICE_INFO];
/** @brief  The number of device informations saved in DT_DevList. */
extern uint8_t DTDevListNum;

//#ifdef _IS_ASIC_
extern void DataTrans_Multilink_ParseScanInfo(T_LE_SCAN_INFO *scan_info);
//#endif
extern bool DataTrans_Multilink_FilterScanInfoByUuid(uint8_t *uuid, T_LE_SCAN_INFO *scan_info);
//extern bool DataTrans_Multilink_FilterExScanInfoByUuid(uint8_t *uuid,
//                                                       T_LE_EXT_ADV_REPORT_INFO *scan_info);
extern bool DataTrans_Multilink_AddDeviceInfo(uint8_t *bd_addr, uint8_t bd_type);
extern void DataTrans_Multilink_ClearDeviceList(void);


#ifdef __cplusplus
}
#endif

#endif

//#endif

