/******************************************************************************
 *
 * Copyright(c) 2007 - 2018	 Realtek Corporation. All rights reserved.
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
#ifndef __RTL8710C_MCC_H__
#define __RTL8710C_MCC_H__

#ifdef CONFIG_MCC_MODE


#include "timer_api.h"
/*--------------------Define --------------------------------------------*/
#define USE_G_TIMER					0
#define USE_THREAD					0

#define MCC_TIMER1					2
#define MCC_TIMER2					3
#define TX_NULL_TIME				3// ms

#define MCC_SW_DEFINE_NULL0			0xABC
#define MCC_SW_DEFINE_NULL1			0xCBA

#define MCC_STATE_CHANNEL_READY		0
#define MCC_STATE_TXNULL			1
#define MCC_STATE_READY_TO_SWITCH	5
#define MCC_STATE_NO_SWITCH_CH		9

// FCS
#define FCS_REQ_END					0xF
//#define FCS_TXNULL_TH				0// 3

#define MCC_MAX_SCAN_CH_NUM			35
#define FCS_MAX_CHIFO_NUM			3

#define MCC_RETRY_NULL_INTERVAL		3
#define MCC_GO_STA_SWRTY_MAX		6
#define MCC_GC_STA_SWRTY_MAX		1

#define MCC_INTV_100MS				0x19000
#define MCC_INTV_200MS				0x32000



//This Value should be fine tune in the future.....
//In GO/STA mode, the period before NOA On to TxNull pkt
//#define MCC_GCSTA_PRENOAON_PERIOD	17 //isr_p2prfoff to switch channel done:10ms in 8723bs, txnull(1) retry reserve 7ms
#define MCC_GCSTA_PRENOAON_PERIOD	4//5 //reserved for switch channel & txnull(1) 3 times

#define MCC_CTS2SELF_NAV_MAX		32//31
#define MCC_NOAON_SWCH_LATENCY		2 //set this latency to match switch channel duration.

#define MCC_USERIDX0				0
#define MCC_USERIDX1				1

#define ALL_ACTION					0
#define ACTION						1
#define SLEEP						2

#define _U16_MSB(x)					(((u16)(x))>>8)
#define _U16_LSB(x)					((u8)(x))
#define _B2D(x0,x1,x2,x3)			((u32)(x0)|((u32)(x1)<<8)|((u32)(x2)<<16)|((u32)(x3)<<24))
#define _D2B(x, idx)				(u8)(((u32)(x))>>(8*(idx)))


#ifndef adapter_mac_addr(adapter)
#define adapter_mac_addr(adapter) (adapter->eeprompriv.mac_addr)
#endif

#define CONFIG_MCC_DEBUG_NOTXNULL	0
/*--------------------Define Enum----------------------------------------*/

typedef enum _MCC_C2HTYPE_ {
	C2HRPT_DISABLE					= 0,
	C2HRPT_RPT_FAIL					= 1,
	C2HRPT_RPT_ALL					= 2,
} MCC_C2HTYPE, *PMCC_C2HTYPE;

typedef enum _MCC_MODE_ {
	MCC_MODE_GO_STA					= 0,
	MCC_MODE_AP_STA					= 1,
	MCC_MODE_GC_STA					= 2,
} MCC_MODE, *PMCC_MODE;

//H2C Index: 0x10
typedef struct _H2CParam_FCS_rsvdpage_loc_ {
	u8 loc_packet[FCS_MAX_CHIFO_NUM];
} H2CParam_FCS_rsvdpage_loc, *PH2CParam_FCS_rsvdpage_loc;

//H2C Index: 0x16
typedef struct _H2CParam_FCS_MacidBitMap_ {
	u8 macid_bitmap0_low;
	u8 macid_bitmap0_high;
	u8 macid_bitmap1_low;
	u8 macid_bitmap1_high;
	u8 macid_bitmap2_low;
	u8 macid_bitmap2_high;
} H2CParam_FCS_MacidBitMap, *PH2CParam_FCS_MacidBitMap;

//H2C Index: 0x18
typedef struct _H2CParam_MCC_param_ {
	u8 order: 4;
	u8 totalnum: 4;

	u8 chidx;

	u8 bw: 2;
	u8 bw40sc: 3;
	u8 bw80sc: 3;

	u8 duration;	// UNIT:1TU

	u8 role: 3;		//0: STA, 1: AP, 2: GC, 3: GO.
	u8 InCurCh: 1;	//1: if null pkt retry fail, keep in current channel,  0: if null pkt retry fail, switch to next channel
	u8 DisSwRetry: 1;	// 0: means enable sw retry, 1: means disable sw retry
	u8 MaxSwRetryIdx: 1;
	u8 rsvd: 2;

	u8 rsvd1;

	u8 rfetype: 4;
	u8 distxnull: 1;
	u8 c2hrpt: 2;
	u8 channelscan: 1;
	//u8 queuesel;
} H2CParam_MCC_param, *PH2CParam_MCC_param;

//H2C Index: 0x19
typedef struct _H2CParam_MCC_Time_param_ {
	u8 MCC_TSFSync_enable: 1;
	u8 TSF_Sync_offset: 7;
	u8 MCC_start_time;
	u8 MCC_interval;
	u8 MCC_EarlySwitch;
	u8 rsvd;
	u8 Update_En: 1;
	u8 Update_Dur0: 7;
} _H2CParam_MCC_Time_param_, *_PH2CParam_MCC_Time_param_;

//H2C Index: 0x1A
typedef struct _H2CParam_MCC_IQK_param_ {
	u8 IQK_Ready : 1;
	u8 IQK_index : 4;
	u8 IQK_rsv : 3;
	u8 IQK_RX_L;
	u8 IQK_RX_M;
	u8 IQK_RX_H;
	u8 IQK_TX_L;
	u8 IQK_TX_M;
	u8 IQK_TX_H;
} _H2CParam_MCC_IQK_param_, *_PH2CParam_MCC_IQK_param_;

typedef struct _macid_info_ {
	u16 Addr;
	u8 Offset;
} MacidInfo, *PMacidInfo;

typedef struct _channel_info_ {
	u8			Chidx;
	u8			BW: 2;
	u8			BW40SC: 3;
	u8			BW80SC: 3;
	//u8		  Duration;	  // UNIT:8ms
	MacidInfo	Macid[2];
	u8			TxNull1: 1;
	u8			TxNull1Ok: 1;
	u8			DisTxNull: 1;
	u8			ChannelScan: 1;
	u8			rsvd: 4;
	u8			Durationl;
	u8			Durationh;
	u8			Count;
	//u8	Queuesel;
	u8			loc_Nulldata;
	u8			ScanCh_Rsvdpage_loc;

	// Scan Channel set format
	//u8		  ChSetLen; // total channel number
	//u8		  ChidxSet[MCC_MAX_SCAN_CH_NUM];
} ChannelInfo, *PChannelInfo;

typedef struct _MCC_CH_INFO_ {
	//h2c cmd 0x11, Byte1~4
	u8			Chidx;
	u8			BW: 2;
	u8			BW40SC: 3;
	u8			BW80SC: 3;
	u8			Duration;
	u8			Role: 3;
	u8			InCurCh: 1;
	u8			DisSwRetry: 1;
	u8			MaxSwRetryIdx: 1;
	u8			rsvd: 2;
	//h2c cmd 0x11, Byte7[7]
	u8			ChannelScan: 1;
	u8			rsvd1: 7;
	//h2c cmd 0x16
	u8			LowBitMap;
	u8			HighBitMap;


	// not h2c cmd format
	u8			TxNull1: 1; // 1: Tx Null(1) is done,	 0: Tx Null(1) is not yet start.
	u8			TxNull1Ok: 1; // 1: Tx Null(1) is done and ok.
	u8			TxNull1OkLate: 1; //Tx Null (1) ok after ISR_P2PRFON
	u8			rsvd2: 5;
	u8			Count;
	//u8	Queuesel;
	u8			loc_packet;
	u8			ScanCh_Rsvdpage_loc;

	// Scan Channel set format
	//u8		  ChSetLen; // total channel number
	//u8		  ChidxSet[MCC_MAX_SCAN_CH_NUM];
} MCC_CH_INFO, *PMCC_CH_INFO;

typedef struct _fcs_info_ {
	u8			Enable: 1;
	u8			Idx: 3;	 //now user idx
	u8			RFEType: 4;
	u8			TotalNum;
	u8			Period;

	MCC_CH_INFO MccChifo[FCS_MAX_CHIFO_NUM];
	u8			PreIdx;
//	  u8		  TxNullCnt;
	u8			StopFCS: 1;
	u8			C2hrpt: 2;
	u8			NotFirstPeriod: 1;
//	  u8		  NoChangeCH:1; //it means this period is keep in same channel due to txnull(1) fail.

#if 1	//CONFIG_MCC_DEBUG_NOTXNULL
	u8			DisTxNull: 1;
	u8			rsvd: 1;
#else
	u8			rsvd: 2;
#endif

	u8			IQK_PathA: 1;
	u8			IQK_PathB: 1;

//	  u8		  NullDelayTime;//Null pkt use period
//	  u16		  Null1FailCnt;
//	  u16		  Null1LateCnt;

	// Scan Channel set format, support one set for scan
	u8			ChSetLen; // total channel number
	u8			ChidxSet[MCC_MAX_SCAN_CH_NUM];
	u8			ChSetIdx[FCS_MAX_CHIFO_NUM]; //ChidxSet[ ChSetIdx[i] ]

//	  u32		  TIME0_TSFL;
//	  u32		  TIME0_TSFH;
//	  u8		  Interval;

	u8			MCCTSFSyncEnable: 1; //from h2c
	u8			TSFoffset: 7;
	u8			MCCStart;
	u8			MCCInterval;
	u8			MCCEarlySwitch;
	u8			TSFSyncFirstDone: 1;
	u8			TSFSyncCount: 5;
	u8			MCCFirstNull: 1;
	u8			IQK_Ready: 1;
	u8			MCCIntervalCnt;
	u16			NOAOffCnt;//use to count the switch times
//	  u8		  SwChTRXBcn;
	u8			StopTxNull;
	u8			NullSwRtyCnt;
	u8			MaxSwRetryCnt;
//	  u8		  MCCMode;//0:GO+STA, 1:GC+STA, 2:AP+STA

	u8			MCCUpdateEn: 1;
	u8			MCCIdx0Duration: 7;

	u8			MCCUpdateTSF: 1;
	u8			MCCUpdateTSFOffset: 7;

	u8			MCCUpdateStTime;
	u8			MCCUpdateDur0;
	u8			MCCUpdateDur1;
	u8			MCCUpdateIntvl;
	u8			rsvdP;		 //rsvd for patch
#if USE_G_TIMER
	gtimer_t  gtimer;
	gtimer_t  gtimer1;
#else
	struct timer_list	timer1;
	struct timer_list	timer2;
#endif
	u8	   b_mcc_inited;
	struct task_struct	mcc_timer_thread;
	struct task_struct	mcc_beacon_early_thread;
	_sema  txnull1ok_sema;

	u32 beacon_early_cnt;
	u32 timeout1_cnt;
	u32 timeout2_cnt;
	u32 BCNERLY_Flag;
	u32 TXCCX_Flag;
} FCSInfo, *PFCSInfo;

//==================C2H event format ====================
// Field	 SYNC		CMD_LEN		CONTENT	   CMD_SEQ		CMD_ID
// BITS	 [127:120]	[119:112]	   [111:16]			 [15:8]		   [7:0]
typedef struct _C2H_EVT_HDR_FW {
	u8	cmd_id;
	u8	cmd_seq;
	u8	content[32];//change 12B to 32B for FTM C2H
	u8	cmd_len;
} C2H_EVT_HDR_FW, *PC2H_EVT_HDR_FW;

#define	   C2HID_MCC	0x17

u32 MCC_H2CCmdCommon8195A(PADAPTER padapter, u8 ElementID, u8 *pCmdBuffer);
void  MCC_BeaconEarly(void *Data);
bool
MCC_CheckNULL1TXOK(
	IN	PADAPTER padapter,
	IN	u16			sw_define_value,
	IN	u8			*payload
);
bool mcc_MacidAction(IN	PADAPTER padapter,	 IN	  u8  action,	 IN	  u8  useridx) ;

s32 mcc_c2h_handler(_adapter *adapter, C2H_EVT_HDR_FW	*c2h_hdr);
void mcc_C2HFCSStatus(IN	 PADAPTER padapter,	 IN	 u8	 status) ;
#if USE_G_TIMER
void mcc_ThreadTimer2TimeOut(void *Data);
thread_return mcc_timer_thread(thread_context context);
#endif
void mcc_Timer1TimeOut(void *Data);
void mcc_Timer2TimeOut(void *Data);
void mcc_BcnEarlyHDL(PADAPTER padapter) ;
thread_return mcc_beacon_early_thread(thread_context context);

#endif	//CONFIG_MCC_MODE
#endif	//__RTL8710C_MCC_H__

