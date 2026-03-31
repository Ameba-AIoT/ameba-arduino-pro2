/******************************************************************************
  *
  * This module is a confidential and proprietary property of RealTek and
  * possession or use of this module requires written permission of RealTek.
  *
  * Copyright(c) 2016, Realtek Semiconductor Corporation. All rights reserved.
  *
******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "main.h"

#if CONFIG_WLAN
#include "wifi_conf.h"
#include "wlan_intf.h"
#include "wifi_constants.h"
#endif
#if CONFIG_LWIP_LAYER
#include "lwip_netconf.h"
#endif
#include <platform_stdlib.h>
#include "osdep_service.h"

#ifndef CONFIG_INIT_NET
#define CONFIG_INIT_NET             1
#endif

#define STACKSIZE                   (512 + 768)

_WEAK void wlan_init_start_time(void)
{

}
_WEAK void wlan_init_end_time(void)
{

}

void init_thread(void *param)
{
	wlan_init_start_time();
#if defined(configENABLE_TRUSTZONE) && (configENABLE_TRUSTZONE == 1)
	rtw_create_secure_context(configMINIMAL_SECURE_STACK_SIZE);
#endif
	/* To avoid gcc warnings */
	(void) param;
#if CONFIG_INIT_NET
#if CONFIG_LWIP_LAYER
	/* Initilaize the LwIP stack */
	LwIP_Init();
#endif
#endif

#if CONFIG_WLAN
	wifi_on(RTW_MODE_STA);
	printf("\n\r%s(%d), Available heap 0x%x\n", __FUNCTION__, __LINE__, xPortGetFreeHeapSize());
#endif

	wlan_init_end_time();
	/* Kill init thread after all init tasks done */
	vTaskDelete(NULL);
}

void wlan_network()
{
	if (xTaskCreate(init_thread, ((const char *)"init"), STACKSIZE, NULL, tskIDLE_PRIORITY + 3 + PRIORITIE_OFFSET, NULL) != pdPASS) {
		printf("\n\r%s xTaskCreate(init_thread) failed\n", __FUNCTION__);
	}
}
