/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
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
#ifndef __RTL8188E_CMD_H__
#define __RTL8188E_CMD_H__

typedef enum _RTL8188E_H2C_CMD_ID {
	//Class Common
	H2C_COM_RSVD_PAGE			= 0x00,
	H2C_COM_MEDIA_STATUS_RPT	= 0x01,
	H2C_COM_SCAN					= 0x02,
	H2C_COM_KEEP_ALIVE			= 0x03,
	H2C_COM_DISCNT_DECISION		= 0x04,
#ifndef CONFIG_WOWLAN
	H2C_COM_WWLAN				= 0x05,
#endif
	H2C_COM_INIT_OFFLOAD			= 0x06,
	H2C_COM_REMOTE_WAKE_CTL	= 0x07,
	H2C_COM_AP_OFFLOAD			= 0x08,
	H2C_COM_BCN_RSVD_PAGE		= 0x09,
	H2C_COM_PROB_RSP_RSVD_PAGE	= 0x0A,

	//Class PS
	H2C_PS_PWR_MODE				= 0x20,
	H2C_PS_TUNE_PARA				= 0x21,
	H2C_PS_TUNE_PARA_2			= 0x22,
	H2C_PS_LPS_PARA				= 0x23,
	H2C_PS_P2P_OFFLOAD			= 0x24,
	H2C_PS_LOW_PWR 				= 0x25,
	H2C_PS_EXT_CLK_OFF 			= 0x26,

	//Class DM
	H2C_DM_MACID_CFG				= 0x40,
	H2C_DM_TXBF					= 0x41,
	H2C_RSSI_SETTING 			= 0x42,

	//Class BT
	H2C_BT_COEX_MASK				= 0x60,
	H2C_BT_COEX_GPIO_MODE		= 0x61,
	H2C_BT_DAC_SWING_VAL			= 0x62,
	H2C_BT_PSD_RST				= 0x63,

	//Class Remote WakeUp
#ifdef CONFIG_WOWLAN
	H2C_COM_WWLAN				= 0x80,
	H2C_COM_REMOTE_WAKE_CTRL	= 0x81,
#endif

	//Class
	H2C_RESET_TSF				= 0xc0,
} RTL8188E_H2C_CMD_ID;

// Description: Determine the types of H2C commands that are the same in driver and Fw.
// Fisrt constructed by tynli. 2009.10.09.
struct cmd_msg_parm {
	u8 eid; //element id
	u8 sz; // sz
	u8 buf[6];
};

enum {
	PWRS
};

typedef struct _SETPWRMODE_PARM {
	u8 Mode;//0:Active,1:LPS,2:WMMPS
	//u8 RLBM:4;//0:Min,1:Max,2: User define
	u8 SmartPS_RLBM;//LPS=0:PS_Poll,1:PS_Poll,2:NullData,WMM=0:PS_Poll,1:NullData
	u8 AwakeInterval;	// unit: beacon interval
	u8 bAllQueueUAPSD;
	u8 PwrState;//AllON(0x0c),RFON(0x04),RFOFF(0x00)
} SETPWRMODE_PARM, *PSETPWRMODE_PARM;

#ifdef RTW_PACK_STRUCT_USE_INCLUDES
#  include "pack_begin.h"
#endif
RTW_PACK_STRUCT_BEGIN
struct H2C_SS_RFOFF_PARAM {
	u8 ROFOn; // 1: on, 0:off
	u16 gpio_period; // unit: 1024 us
} RTW_PACK_STRUCT_STRUCT;
RTW_PACK_STRUCT_END
#ifdef RTW_PACK_STRUCT_USE_INCLUDES
#  include "pack_end.h"
#endif


typedef struct JOINBSSRPT_PARM {
	u8 OpMode;	// RT_MEDIA_STATUS
#ifdef CONFIG_WOWLAN
	u8 MacID;       // MACID
#endif //CONFIG_WOWLAN
} JOINBSSRPT_PARM, *PJOINBSSRPT_PARM;

typedef struct _RSVDPAGE_LOC {
	u8 LocProbeRsp;
	u8 LocPsPoll;
	u8 LocNullData;
	u8 LocQosNull;
	u8 LocBTQosNull;
} RSVDPAGE_LOC, *PRSVDPAGE_LOC;

struct P2P_PS_Offload_t {
	u8 Offload_En: 1;
	u8 role: 1; // 1: Owner, 0: Client
	u8 CTWindow_En: 1;
	u8 NoA0_En: 1;
	u8 NoA1_En: 1;
	u8 AllStaSleep: 1; // Only valid in Owner
	u8 discovery: 1;
	u8 rsvd: 1;
};

struct P2P_PS_CTWPeriod_t {
	u8 CTWPeriod;	//TU
};


// host message to firmware cmd
void rtl8188e_set_FwPwrMode_cmd(_adapter *padapter, u8 Mode);
void rtl8188e_set_FwJoinBssReport_cmd(_adapter *padapter, u8 mstatus);
u8 rtl8188e_set_rssi_cmd(_adapter *padapter, u8 *param);
u8 rtl8188e_set_raid_cmd(_adapter *padapter, u32 mask);
void rtl8188e_Add_RateATid(PADAPTER pAdapter, u32 bitmap, u8 *arg_ary, u8 rssi_level);
//u8 rtl8192c_set_FwSelectSuspend_cmd(_adapter * padapter, u8 bfwpoll, u16 period);


void CheckFwRsvdPageContent(_adapter *padapter);
void rtl8188e_set_FwMediaStatus_cmd(_adapter *padapter, u16 mstatus_rpt);

#ifdef CONFIG_TSF_RESET_OFFLOAD
//u8 rtl8188e_reset_tsf(_adapter *padapter, u8 reset_port);
int reset_tsf(_adapter *Adapter, u8 reset_port);
#endif	// CONFIG_TSF_RESET_OFFLOAD

#ifdef CONFIG_WOWLAN
typedef struct _SETWOWLAN_PARM {
	u8		mode;
	u8		gpio_index;
	u8		gpio_duration;
	u8		second_mode;
	u8		reserve;
} SETWOWLAN_PARM, *PSETWOWLAN_PARM;

#define FW_WOWLAN_FUN_EN				BIT(0)
#define FW_WOWLAN_PATTERN_MATCH			BIT(1)
#define FW_WOWLAN_MAGIC_PKT				BIT(2)
#define FW_WOWLAN_UNICAST				BIT(3)
#define FW_WOWLAN_ALL_PKT_DROP			BIT(4)
#define FW_WOWLAN_GPIO_ACTIVE			BIT(5)
#define FW_WOWLAN_REKEY_WAKEUP			BIT(6)
#define FW_WOWLAN_DEAUTH_WAKEUP			BIT(7)

#define FW_WOWLAN_GPIO_WAKEUP_EN		BIT(0)
#define FW_FW_PARSE_MAGIC_PKT			BIT(1)

#define FW_REMOTE_WAKE_CTRL_EN			BIT(0)
#define FW_REALWOWLAN_EN				BIT(5)
void rtl8188es_set_wowlan_cmd(_adapter *padapter, u8 enable);
void SetFwRelatedForWoWLAN8188ES(_adapter *padapter, u8 bHostIsGoingtoSleep);
#endif//CONFIG_WOWLAN
#endif//__RTL8188E_CMD_H__


