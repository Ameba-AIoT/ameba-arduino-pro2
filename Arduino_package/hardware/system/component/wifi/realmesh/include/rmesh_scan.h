/**
  ******************************************************************************
  * @file    rmesh_scan.h
  * @author
  * @version V1.0.0
  * @date    2019-09-16
  * @brief   This file contains all the functions prototypes for the realmesh.
  ******************************************************************************
  * @attention
  *
  * This module is a confidential and proprietary property of RealTek and
  * possession or use of this module requires written permission of RealTek.
  *
  * Copyright(c) 2016, Realtek Semiconductor Corporation. All rights reserved.
  ******************************************************************************
  */

#ifndef _RTL_MESH_SCAN_H_
#define _RTL_MESH_SCAN_H_

#include "rmesh.h"

#define SCAN_TIMEOUT_UNDER_CONNECT 3    // 300ms


typedef void (*rmesh_scan_result_handler_t)(struct rmesh_scan_result *scan_result, int num);
typedef void (*rmesh_scan_each_handler_t)(struct rmesh_scan_result *scan_result);

/*******************************************************
 *                Enumerations
 *******************************************************/

/**
 * @brief mesh scan state
 */
typedef enum {
	RMESH_SCAN_DISABLE = 0,
	RMESH_SCANING,
	RMESH_SCAN_DONE,
};


/*******************************************************
 *                Structures
 *******************************************************/

/**
  * @brief  The structure is used to describe the SSID.
  */
struct rmesh_ssid {
	unsigned char len;    		 /* SSID length */
	unsigned char val[33]; 		/* SSID name (AP name)  */
};

/**
  * @brief  The structure is used to describe the scan result of the AP.
  */
struct rmesh_scan_result {
	struct rmesh_ssid            	SSID;				/* Service Set Identification (i.e. Name of Access Point)                    */
	u8 						BSSID[ETH_ALEN];	/* Basic Service Set Identification (i.e. MAC address of Access Point)       */
	signed short				signal_strength;  	/* Receive Signal Strength Indication in dBm. <-90=Very poor, >-30=Excellent */
	unsigned long         		bss_type;			/* Network type                                                              */
	unsigned long 				security;			/* Security type                                                             */
	unsigned long          		wps_type;			/* WPS type                                                                  */
	u8                			    	channel;			/* Radio channel that the AP beacon was received on                          */

	u8						net_config_ap;

	u8						node_type;			/* type of node: RMESH_ROOT; RMESH_NODE; RMESH_LEAF */
	u8 						current_layer;		/* current layer of node */
	u8 						current_child_num;   /* current number of children the node */
};

struct rmesh_scan_handler {
	struct rmesh_scan_result 	**pap_details;
	struct rmesh_scan_result 		*ap_details;
	int							scan_cnt;
	unsigned long					scan_complete;
	unsigned char					max_ap_size;
	int 							scan_running;
	unsigned int					scan_start_time;
	rmesh_scan_result_handler_t 	gscan_result_handler;
	rmesh_scan_each_handler_t		gscan_each_handler;
};

/*******************************************************
 *                APIs
 *******************************************************/

/* *
* @brief: start scan func, should be used in network config stage and network connect stage

* @attention

* @param	channel:	scanning channel; if channel = 0, should scan in all channel
* @param	results_handler: scan results (all)
* @param	each_handler: scan results (one)

* @retval		RMESH_SUCCESS
			RMESH_FAIL
*/
int real_mesh_scan_start(int channel, rmesh_scan_result_handler_t results_handler, rmesh_scan_each_handler_t each_handler);

/* *
* @brief: stop scan

* @attention

* @param	none

* @retval		RMESH_SUCCESS
			RMESH_FAIL
*/
void real_mesh_scan_stop();

#endif //_RTL_MESH_SCAN_H_

/******************* (C) COPYRIGHT 2016 Realtek Semiconductor *****END OF FILE****/

