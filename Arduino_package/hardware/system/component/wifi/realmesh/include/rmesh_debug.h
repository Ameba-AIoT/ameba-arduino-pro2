/**
  ******************************************************************************
  * @file    rmesh_debug.h
  * @author
  * @version V1.0.0
  * @date    2019-10-08
  * @brief   This file is for setting debug level.
  ******************************************************************************
  * @attention
  *
  * This module is a confidential and proprietary property of RealTek and
  * possession or use of this module requires written permission of RealTek.
  *
  * Copyright(c) 2016, Realtek Semiconductor Corporation. All rights reserved.
  ******************************************************************************
  */
#ifndef _RTL_MESH_DEBUG_H_
#define _RTL_MESH_DEBUG_H_

#define RMESH_ERROR		0
#define RMESH_WARNING	1
#define RMESH_INFO		2
#define RMESH_DEBUG		3
#define RMESH_NONE		0xFF

#define RMESH_DEBUG_LEVEL RMESH_DEBUG

#if (RMESH_DEBUG_LEVEL== RMESH_NONE)
#define DBG_RMESH(level, fmt, arg...)
#define DBG_RMESH_DATA(level, _TitleString, _HexData, _HexDataLen)
#else
#define DBG_RMESH(level, fmt, arg...)     \
do {\
	if (level <= RMESH_DEBUG_LEVEL) {\
		if (level <= RMESH_ERROR) {\
			printf("\r\nERROR: " fmt "\n\r", ##arg);\
		} \
		else {\
			printf("\r\n"fmt "\n\r", ##arg);\
		} \
	}\
}while(0)

#define DBG_RMESH_DATA(level, _TitleString, _HexData, _HexDataLen)			\
do {\
	if(level <= RMESH_DEBUG_LEVEL) {\
		{									\
			int __i;								\
			u8	*ptr = (u8 *)_HexData;				\
			printf(_TitleString "--------Len=%d\n\r", _HexDataLen);						\
			for( __i=0; __i<(int)_HexDataLen; __i++ )				\
			{								\
				printf("%02X%s", ptr[__i], (((__i + 1) % 4) == 0)?"  ":" ");	\
				if (((__i + 1) % 16) == 0)	printf("\n\r");			\
			}								\
			printf("\n\r");							\
		}\
	}\
}while(0)
#endif
#endif
