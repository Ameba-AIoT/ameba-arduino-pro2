/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      bt_breeze_app_flags.h
   * @brief     This file is used to config app functions.
   * @author    jane
   * @date      2017-06-06
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */

#ifndef _BT_BREEZE_APP_FLAGS_H_
#define _BT_BREEZE_APP_FLAGS_H_

#include "platform_opts_bt.h"
#if UPPER_STACK_VERSION == VERSION_2019
#include "bt_flags.h"
#elif UPPER_STACK_VERSION == VERSION_2021
#include "upperstack_config.h"
#endif

/** @defgroup  BREEZE_Config Breeze App Configuration
    * @brief This file is used to config app functions.
    * @{
    */
/*============================================================================*
 *                              Constants
 *============================================================================*/

/** @brief  Config APP LE link number */
#define BLE_BREEZE_APP_MAX_LINKS  1

#define BREEZE_TEMP_WORK_AROUND 1

/** @} */ /* End of group BREEZE_Config */
#endif

