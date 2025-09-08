/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      peripheral_app.h
   * @brief     This file handles BLE peripheral application routines.
   * @author    jane
   * @date      2017-06-06
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */

#ifndef _PERIPHERAL_APP__
#define _PERIPHERAL_APP__

#ifdef __cplusplus
extern "C" {
#endif
/*============================================================================*
 *                              Header Files
 *============================================================================*/
#include <app_msg.h>
#include <gap_le.h>
#include <profile_server.h>
#include <app_flags.h>
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
#include <gap_le_types.h>
#include <gap_ext_adv.h>
#endif
#if APP_PRIVACY_EN
#include <privacy_mgnt.h>

typedef enum
{
    APP_PAIRABLE_MODE,          /**< Pairable mode. */
    APP_RECONNECTION_MODE,      /**< Reconnection mode. */
} T_APP_WORK_MODE;
#endif

/*============================================================================*
 *                              Variables
 *============================================================================*/
extern T_SERVER_ID simp_srv_id; /**< Simple ble service id*/
extern T_SERVER_ID bas_srv_id;  /**< Battery service id */

/*============================================================================*
 *                              Constants
 *============================================================================*/
#if (F_BT_LE_USE_RANDOM_ADDR == 1)
typedef struct
{
    uint8_t is_exist;
    uint8_t reserved;                 /**< remote BD type*/
    uint8_t bd_addr[GAP_BD_ADDR_LEN]; /**< remote BD */
} T_APP_STATIC_RANDOM_ADDR;
#endif
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
#define GAP_MAX_EXT_ADV_SETS      6
#define GAP_INVALID_ADV_HANDLE  0xFF
typedef struct {
	bool used;
	uint8_t adv_handle;
	T_GAP_EXT_ADV_STATE ext_adv_state;
} ext_adv_info_t;

typedef struct {
	/** Advertising_Event_Properties */
	T_LE_EXT_ADV_EXTENDED_ADV_PROPERTY adv_event_prop;
	/**
	 * Minimum advertising interval for undirected and low duty cycle\n
	 * directed advertising.\n
	 * Range: 0x000020 to 0xFFFFFF\n
	 * Time = N * 0.625 ms\n
	 * Time Range: 20 ms to 10,485.759375 s
	 */
	uint32_t primary_adv_interval_min;
	/**
	 * Maximum advertising interval for undirected and low duty cycle\n
	 * directed advertising.\n
	 * Range: 0x000020 to 0xFFFFFF\n
	 * Time = N * 0.625 ms\n
	 * Time Range: 20 ms to 10,485.759375 s
	 */
	uint32_t primary_adv_interval_max;
	/** Advertising_Primary_Channel_Map */
	uint8_t primary_adv_channel_map;
	/** Own_Address_Type_and_Address */
	T_GAP_LOCAL_ADDR_TYPE own_addr_type;
  	uint8_t own_addr[6];
	/** Peer_Address_Type_and_Address */
	T_GAP_REMOTE_ADDR_TYPE peer_addr_type;
  	uint8_t peer_addr[6];
	/** Advertising_Filter_Policy */
	T_GAP_ADV_FILTER_POLICY filter_policy;
	/**
	 * Advertising_TX_Power: indicates max Tx power.\n
	 * Range: -127 to +20\n
	 * Units: dBm\n
	 * 0x7F: Host has no preference.
	 */
	int8_t tx_power;
	/** Primary_Advertising_PHY */
	T_GAP_PHYS_PRIM_ADV_TYPE primary_adv_phy;
	/** Secondary_Advertising_Max_Skip */
	uint8_t secondary_adv_max_skip;
	/** Secondary_Advertising_PHY */
	T_GAP_PHYS_TYPE secondary_adv_phy;
	/**
	 * Value of the Advertising SID subfield in the ADI field of the PDU.\n
	 * Range: 0x00 to 0x0F\n
	 */
	uint8_t adv_sid;
} ext_adv_param_t;

typedef struct {
	/** Advertising paramter */
	ext_adv_param_t *p_adv_param;
	/** Advertising set handle created by stack */
	uint8_t *p_adv_handle;
} ext_adv_create_t;

typedef struct {
	/** Identify an advertising set. */
	uint8_t adv_handle;
	/** If non-zero: Advertising duration, in units of 10ms */
	uint16_t duration;
	/**
	 * If non-zero, indicates the maximum extended advertising events that shall attempt to
	 * send prior to terminating the extended advertising.
	 */
	uint8_t num_events;
} ext_adv_start_t;
#endif

/*============================================================================*
 *                              Functions
 *============================================================================*/

/**
 * @brief    All the application messages are pre-handled in this function
 * @note     All the IO MSGs are sent to this function, then the event handling
 *           function shall be called according to the MSG type.
 * @param[in] io_msg  IO message data
 * @return   void
 */
void app_handle_io_msg(T_IO_MSG io_msg);

/**
 * @brief    All the BT Profile service callback events are handled in this function
 * @note     Then the event handling function shall be called according to the
 *           service_id.
 * @param[in] service_id  Profile service ID
 * @param[in] p_data      Pointer to callback data
 * @return   Indicates the function call is successful or not
 * @retval   result @ref T_APP_RESULT
 */
T_APP_RESULT app_profile_callback(T_SERVER_ID service_id, void *p_data);

/**
  * @brief Callback for gap le to notify app
  * @param[in] cb_type callback msy type @ref GAP_LE_MSG_Types.
  * @param[in] p_cb_data point to callback data @ref T_LE_CB_DATA.
  * @retval result @ref T_APP_RESULT
  */
T_APP_RESULT app_gap_callback(uint8_t cb_type, void *p_cb_data);

void app_vendor_callback(uint8_t cb_type, void *p_cb_data);

#if (F_BT_LE_USE_RANDOM_ADDR == 1)
/**
 * @brief   Save static random address information into flash.
 * @param[in] p_addr Pointer to the buffer for saving data.
 * @retval 0 Save success.
 * @retval other Failed.
 */
uint32_t ble_peripheral_app_save_static_random_address(T_APP_STATIC_RANDOM_ADDR *p_addr);

/**
  * @brief  Load static random address information from storage.
  * @param[out]  p_addr Pointer to the buffer for loading data.
  * @retval 0 Load success.
  * @retval other Failed.
  */
uint32_t ble_peripheral_app_load_static_random_address(T_APP_STATIC_RANDOM_ADDR *p_addr);
#endif

#if F_BT_GAPS_CHAR_WRITEABLE
T_APP_RESULT gap_service_callback(T_SERVER_ID service_id, void *p_para);
#endif

#if APP_PRIVACY_EN
/**
  * @brief Callback for BLE privacy management module to notify app
  * @param[in] type     callback msy type @ref T_PRIVACY_CB_TYPE.
  * @param[in] cb_data  callback data.
  * @retval void
  */
void app_privacy_callback(T_PRIVACY_CB_TYPE type, T_PRIVACY_CB_DATA cb_data);

/**
  * @brief Application changes to pairable mode.
  * @retval void
  */
void app_change_to_pair_mode(void);

#endif
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
bool ble_peripheral_app_gap_ext_adv_handle_valid(uint8_t handle);
void ble_peripheral_init_ext_adv(void);
void ble_peripheral_create_ext_adv(ext_adv_param_t *param, uint8_t *handle);
void ble_peripheral_set_ext_scan_rsp_data(uint8_t adv_handle, uint16_t data_len, uint8_t *ext_data);
void ble_peripheral_set_ext_adv_data(uint8_t adv_handle, uint16_t data_len, uint8_t *ext_data);
void ble_peripheral_start_ext_adv(ext_adv_start_t *adv_start_param);
void ble_peripheral_remove_ext_adv_set(uint8_t adv_handle);
void ble_peripheral_clear_all_ext_adv_set(void);
void ble_peripheral_stop_ext_adv(uint8_t adv_handle);
#endif
#ifdef __cplusplus
}
#endif

#endif

