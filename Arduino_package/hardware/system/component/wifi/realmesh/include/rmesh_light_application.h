/**
  ******************************************************************************
  * @file    rmesh_light_application.h
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
#ifndef _RTL_MESH_LIGHT_APPLICATION_H_
#define _RTL_MESH_LIGHT_APPLICATION_H_

#include "ameba_soc.h"
#include "rmesh.h"

#define GPIO_RED_LED_PIN       _PA_13
#define GPIO_GREEN_LED_PIN    _PA_14


void gpio_led_init();
void gpio_led_set_color(u8 red, u8 green);
void gpio_led_set_led_color(u8 red);
void gpio_led_set_route_color(u8 green);
void gpio_led_on_data(u8 *data, u16 len, u8 link);
void led_timer_init();

#endif //_RTL_MESH_LIGHT_APPLICATION_H_

