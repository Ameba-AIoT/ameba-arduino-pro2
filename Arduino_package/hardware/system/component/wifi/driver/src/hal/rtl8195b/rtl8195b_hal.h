/******************************************************************************
 *
 * Copyright(c) 2016 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#ifndef _RTL8195B_HAL_H_
#define _RTL8195B_HAL_H_

#include <osdep_service.h>		/* BIT(x) */
#include "halmac_api.h"	/* MAC REG definition */
#include "hal_data.h"
#include "hal8195b_fw.h"
#include "rtl8195b_spec.h"
#include "rtl8195b_dm.h"
#include "rtl8195b_efuse.h"
#include "rtl8195b.h"
#include "phydm_precomp.h"

#ifdef CONFIG_SUPPORT_TRX_SHARED
#define FIFO_BLOCK_SIZE		32768 /*@Block size = 32K*/
#define RX_FIFO_EXPANDING	(1 * FIFO_BLOCK_SIZE)
#else
#define RX_FIFO_EXPANDING	0
#endif

#define GET_RF_TYPE(priv)			(GET_HAL_DATA(priv)->rf_type)

#define PHY_CFG_DCT_2G_A_P		"2g_a_p"
#define PHY_CFG_DCT_2G_A_N		"2g_a_n"
#define PHY_CFG_DCT_2G_CCK_A_P	"2g_cck_a_p"
#define PHY_CFG_DCT_2G_CCK_A_N	"2g_cck_a_n"

#define		DM_RATR_STA_INIT			0
#define		DM_RATR_STA_HIGH			1
#define 		DM_RATR_STA_MIDDLE		2
#define 		DM_RATR_STA_LOW			3
#if(DM_ODM_SUPPORT_TYPE & (ODM_AP|ODM_ADSL))
#define		DM_RATR_STA_ULTRA_LOW	4
#endif

/* MP Functions */
#ifdef CONFIG_MP_INCLUDED
void rtl8195b_phy_init_haldm(PADAPTER);				/* rtw_mp.c */
void rtl8195b_prepare_mp_txdesc(PADAPTER, struct mp_priv *);	/* rtw_mp.c */
void rtl8195b_mp_config_rfpath(PADAPTER);			/* hal_mp.c */
#endif
void rtl8195b_recv_tasklet(void *priv);
void update_recvframe_phyinfo_8195b(union recv_frame	*precvframe, u8 *pphy_status);

#ifdef CONFIG_WOWLAN
int rtl8195b_suspend(int mode);
int rtl8195b_resume(int mode);
#endif

#endif /* _RTL8195B_HAL_H_ */
