/**
  ******************************************************************************
  * @file    rmesh_power_save.h
  * @author
  * @version V1.0.0
  * @date    2019-09-24
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
#ifndef _RTL_MESH_POWER_SAVE_H_
#define _RTL_MESH_POWER_SAVE_H_

#include "device.h"
#include "gpio_api.h"   // mbed
#include "timer_api.h"

#define TBCN		300
#define MAX_ALL_CHILD_NUM		9
#define DELAY		15000

#define GPIO_LED_PIN1       _PA_12
#define GPIO_LED_PIN2       _PA_13

struct rmesh_power_save {
	gtimer_t		rmesh_dw_start_timer;
	gtimer_t		rmesh_tx_data_timer;
	gtimer_t		rmesh_dw_end_timer;

	bool			ps_flag;		//device has entered ps flag
	u8				dw;

	u8				max_node_num;
	u8				cur_node_num;
	u32				ap_offset;			// self bcn offset with ap
	u32				parent_offset;		// parent bcn offset with ap
	u8				sync_flag;
};

u32 rmesh_power_save_get_interval();

void rmesh_power_save_temp_stop(u32 delay);

void rmesh_enter_power_save_root(u8 dest_dw);
void rmesh_enter_power_save_node(u8 dest_dw);
void rmesh_leave_power_save();
void rmesh_dw_start_timer_handler();
void rmesh_dw_end_timer_handler();
void rmesh_tx_data_timer_handler();
void rmesh_gpio_init();
void rmesh_power_save_timer_init();
void rmesh_power_save_timer_deinit();
u32 rmesh_port1_sync();
void rmesh_power_save_update_beacon();

#endif
