/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      central_client_app.h
   * @brief     This file handles BLE central client application routines.
   * @author    jane
   * @date      2017-06-06
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */

#ifndef _BLE_CENTRAL_CLIENT_APP_H_
#define _BLE_CENTRAL_CLIENT_APP_H_

#ifdef __cplusplus
extern "C" {
#endif
/*============================================================================*
 *                              Header Files
 *============================================================================*/
#include <profile_client.h>
#include <app_msg.h>
#include <app_common_flags.h>

#define BD_ADDR_FMT "%02x:%02x:%02x:%02x:%02x:%02x"
#define BD_ADDR_ARG(x) (x)[5],(x)[4],(x)[3],(x)[2],(x)[1],(x)[0]
#define UUID_128_FORMAT "0x%2X:0x%2X:0x%2X:0x%2X:0x%2X:0x%2X:0x%2X:0x%2X:0x%2X:0x%2X:0x%2X:0x%2X:0x%2X:0x%2X:0x%2X:0x%2X"
#define UUID_128(x)  x[0],x[1],x[2],x[3],x[4],x[5],x[6],x[7],x[8],x[9],x[10],x[11],x[12],x[13],x[14],x[15]
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
typedef struct {
	/** Own_Address_Type */
	T_GAP_LOCAL_ADDR_TYPE own_addr_type;
	/**
	 * Scanning_PHYs\n
	 * phys[0] for 1M PHY, phys[1] for Coded PHY\n
	 * */
	uint8_t ext_scan_phys[2];
	T_GAP_SCAN_MODE type[2];
	/**
	 * This is defined as the time interval from when the Controller\n
	 * started its last LE scan until it begins the subsequent LE scan.\n
	 * Range: 0x0004 to 0xFFFF\n
	 * Default: 0x0040 (40 ms)\n
	 * Time = N * 0.625 ms\n
	 * Time Range: 2.5 ms to 40.959375 s\n
	 * interval[0] for 1M PHY, interval[1] for Coded PHY.\n
	 */
	uint16_t ext_scan_interval[2];
	/**
	 * The duration of the LE scan. LE_Scan_Window shall be less\n
	 * than or equal to LE_Scan_Interval\n
	 * Range: 0x0004 to 0xFFFF\n
	 * Default: 0x0020 (20 ms)\n
	 * Time = N * 0.625 ms\n
	 * Time Range: 2.5 ms to 40.959375 s\n
	 * window[0] for 1M PHY, window[1] for Coded PHY.\n
	 */
	uint16_t ext_scan_window[2];

	/**
	 * 0x0000 indicates scan continuously until explicitly disable.\n
	 * Other values indicate scan duration\n
	 * Range: 0x0001 to 0xFFFF\n
	 * Time = N * 10 ms\n
	 * Time Range: 10 ms to 655.35 s\n
	 */
	uint16_t ext_scan_duration;

	/**
	 * 0x0000 indicates scan continuously.\n
	 * Other values indicate time interval from when the Controller started\n
	 * its last Scan_Duration until it begins the subsequent Scan_Duration.\n
	 * Range: 0x0001 to 0xFFFF\n
	 * Time = N * 1.28 sec\n
	 * Time Range: 1.28 s to 83,884.8 s\n
	 */
	uint16_t ext_scan_period;

	/** Scanning_Filter_Policy */
	T_GAP_SCAN_FILTER_POLICY ext_scan_filter_policy;
	/** Scanning_Duplicated_Option */
	T_GAP_SCAN_FILTER_DUPLICATE ext_scan_filter_duplicate;
} ext_scan_param_t;
#endif
/*============================================================================*
 *                              Variables
 *============================================================================*/
extern T_CLIENT_ID   ble_central_gcs_client_id;         /**< General Common Services client client id*/

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
void ble_central_app_handle_io_msg(T_IO_MSG io_msg);
/**
  * @brief Callback for gap le to notify app
  * @param[in] cb_type callback msy type @ref GAP_LE_MSG_Types.
  * @param[in] p_cb_data point to callback data @ref T_LE_CB_DATA.
  * @retval result @ref T_APP_RESULT
  */
T_APP_RESULT ble_central_app_gap_callback(uint8_t cb_type, void *p_cb_data);

/**
 * @brief  Callback will be called when data sent from profile client layer.
 * @param  client_id the ID distinguish which module sent the data.
 * @param  conn_id connection ID.
 * @param  p_data  pointer to data.
 * @retval   result @ref T_APP_RESULT
 */
T_APP_RESULT ble_central_gcs_client_callback(T_CLIENT_ID client_id, uint8_t conn_id, void *p_data);
#if defined(APP_LE_EXT_ADV_SCAN_SUPPORT) && APP_LE_EXT_ADV_SCAN_SUPPORT
void ble_central_set_ext_scan_param(ext_scan_param_t *p_param);
#endif
#ifdef __cplusplus
}
#endif

#endif

