/**
*****************************************************************************************
*     Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
* @file     a2dp_app_debug.h
* @brief    Source file for a2dp app debug.
* @details  User command interfaces.
* @author   sherman
* @date     2021-06-10
* @version  v1.0
* *************************************************************************************
*/
#ifndef _A2DP_APP_DEBUG_H_
#define _A2DP_APP_DEBUG_H_

// #define CONFIG_A2DP_APP_DEBUG

#ifdef CONFIG_A2DP_APP_DEBUG
#define _dbgdump	printf("\n\r"); printf
#define PREFIX	"[A2DP_APP] "
#if	defined (_dbgdump)
#undef DBG_AAD
#define DBG_AAD(...)     do {\
		_dbgdump(PREFIX __VA_ARGS__);\
	}while(0)
#endif
#else
#define DBG_AAD(x, ...) do {} while(0)
#endif /* CONFIG_A2DP_APP_DEBUG */

#endif /* _A2DP_APP_DEBUG_H_ */