/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      app_flags.h
   * @brief     This file is used to config app functions.
   * @author    jane
   * @date      2017-06-06
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */
#ifndef _BT_DATATRANS_APP_FLAGS_H_
#define _BT_DATATRANS_APP_FLAGS_H_

#include <app_common_flags.h>

/*============================================================================*
 *                              Constants
 *============================================================================*/

#define BT_DATATRANS_APP_MAX_LINKS   1

/*if define CENTRAL_MODE to 1,pls include datatrans_client.c & gaps_client.c in target build.*/
#define CENTRAL_MODE    1

/** @} */ /* End of group SCATTERNET_Config */
/** @} */ /* End of group SCATTERNET_DEMO */
#endif
