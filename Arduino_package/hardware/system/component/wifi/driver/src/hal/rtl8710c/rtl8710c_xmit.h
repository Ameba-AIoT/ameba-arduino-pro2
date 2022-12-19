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
 ******************************************************************************/
#ifndef _RTL8710CA_XMIT_H_
#define _RTL8710CA_XMIT_H_

#include <drv_types.h>		/* PADAPTER, rtw_xmit.h and etc. */

#define TX_DESC_MODE        	1
#define MAX_TXBD_SEQMENT_NUM    ((TX_DESC_MODE)? (4*TX_DESC_MODE): 2) // TXBD_SEQMENT_NUM 0: 2, 1: 4, 2: 8
#define TXBD_SEGMENT_SIZE		8 // 8 bytes = 2DW

#if !defined(RTW_HALMAC)
//
//defined for TX DESC Operation
//
typedef struct txdesc_8723b {
	// Offset 0
	u32 pktlen: 16;
	u32 offset: 8;
	u32 bmc: 1;
	u32 htc: 1;
	u32 rsvd0026: 1;
	u32 rsvd0027: 1;
	u32 linip: 1;
	u32 noacm: 1;
	u32 gf: 1;
	u32 rsvd0031: 1;

	// Offset 4
	u32 macid: 7;
	u32 rsvd0407: 1;
	u32 qsel: 5;
	u32 rdg_nav_ext: 1;
	u32 lsig_txop_en: 1;
	u32 pifs: 1;
	u32 rate_id: 5;
	u32 en_desc_id: 1;
	u32 sectype: 2;
	u32 pkt_offset: 5; // unit: 8 bytes
	u32 moredata: 1;
	u32 txop_ps_cap: 1;
	u32 txop_ps_mode: 1;

	// Offset 8
	u32 p_aid: 9;
	u32 rsvd0809: 1;
	u32 cca_rts: 2;
	u32 agg_en: 1;
	u32 rdg_en: 1;
	u32 null_0: 1;
	u32 null_1: 1;
	u32 bk: 1;
	u32 morefrag: 1;
	u32 raw: 1;
	u32 spe_rpt: 1;
	u32 ampdu_density: 3;
	u32 bt_null: 1;
	u32 g_id: 6;
	u32 rsvd0830: 2;

	// Offset 12
	u32 wheader_len: 4;
	u32 chk_en: 1;
	u32 early_rate: 1;
	u32 hw_ssn_sel: 2;
	u32 userate: 1;
	u32 disrtsfb: 1;
	u32 disdatafb: 1;
	u32 cts2self: 1;
	u32 rtsen: 1;
	u32 hw_rts_en: 1;
	u32 port_id: 1;
	u32 navusehdr: 1;
	u32 use_max_len: 1;
	u32 max_agg_num: 5;
	u32 ndpa: 2;
	u32 ampdu_max_time: 8;

	// Offset 16
	u32 datarate: 7;
	u32 try_rate: 1;
	u32 data_ratefb_lmt: 5;
	u32 rts_ratefb_lmt: 4;
	u32 rty_lmt_en: 1;
	u32 data_rt_lmt: 6;
	u32 rtsrate: 5;
	u32 pcts_en: 1;
	u32 pcts_mask_idx: 2;

	// Offset 20
	u32 data_sc: 4;
	u32 data_short: 1;
	u32 data_bw: 2;
	u32 data_ldpc: 1;
	u32 data_stbc: 2;
	u32 vcs_stbc: 2;
	u32 rts_short: 1;
	u32 rts_sc: 4;
	u32 rsvd2016: 7;
	u32 tx_ant: 4;
	u32 txpwr_offset: 3;
	u32 rsvd2031: 1;

	// Offset 24
	u32 sw_define: 12;
	u32 mbssid: 4;
	u32 antsel_A: 3;
	u32 antsel_B: 3;
	u32 antsel_C: 3;
	u32 antsel_D: 3;
	u32 rsvd2428: 4;

	// Offset 28
	u32 checksum: 16;
	u32 rsvd2816: 8;
	u32 usb_txagg_num: 8;

	// Offset 32
	u32 rts_rc: 6;
	u32 bar_rty_th: 2;
	u32 data_rc: 6;
	u32 rsvd3214: 1;
	u32 en_hwseq: 1;
	u32 nextneadpage: 8;
	u32 tailpage: 8;

	// Offset 36
	u32 padding_len: 11;
	u32 txbf_path: 1;
	u32 seq: 12;
	u32 final_data_rate: 8;
} TXDESC_8723B, *PTXDESC_8723B;

// Dword 0
#define GET_TX_DESC_OWN_8723B(__pTxDesc)				LE_BITS_TO_4BYTE(__pTxDesc, 31, 1)

#define SET_TX_DESC_PKT_SIZE_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc, 0, 16, __Value)
#define SET_TX_DESC_OFFSET_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc, 16, 8, __Value)
#define SET_TX_DESC_BMC_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc, 24, 1, __Value)
#define SET_TX_DESC_HTC_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc, 25, 1, __Value)
#define SET_TX_DESC_LAST_SEG_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc, 26, 1, __Value)
#define SET_TX_DESC_FIRST_SEG_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc, 27, 1, __Value)
#define SET_TX_DESC_LINIP_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc, 28, 1, __Value)
#define SET_TX_DESC_NO_ACM_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc, 29, 1, __Value)
#define SET_TX_DESC_GF_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc, 30, 1, __Value)
#define SET_TX_DESC_OWN_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc, 31, 1, __Value)

// Dword 1
#define SET_TX_DESC_MACID_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+4, 0, 7, __Value)
#define SET_TX_DESC_QUEUE_SEL_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+4, 8, 5, __Value)
#define SET_TX_DESC_RDG_NAV_EXT_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+4, 13, 1, __Value)
#define SET_TX_DESC_LSIG_TXOP_EN_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+4, 14, 1, __Value)
#define SET_TX_DESC_PIFS_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+4, 15, 1, __Value)
#define SET_TX_DESC_RATE_ID_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+4, 16, 5, __Value)
#define SET_TX_DESC_EN_DESC_ID_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+4, 21, 1, __Value)
#define SET_TX_DESC_SEC_TYPE_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+4, 22, 2, __Value)
#define SET_TX_DESC_PKT_OFFSET_8723B(__pTxDesc, __Value)		SET_BITS_TO_LE_4BYTE(__pTxDesc+4, 24, 5, __Value)


// Dword 2
#define SET_TX_DESC_PAID_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+8, 0,  9, __Value)
#define SET_TX_DESC_CCA_RTS_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+8, 10, 2, __Value)
#define SET_TX_DESC_AGG_ENABLE_8723B(__pTxDesc, __Value)		SET_BITS_TO_LE_4BYTE(__pTxDesc+8, 12, 1, __Value)
#define SET_TX_DESC_RDG_ENABLE_8723B(__pTxDesc, __Value)		SET_BITS_TO_LE_4BYTE(__pTxDesc+8, 13, 1, __Value)
#define SET_TX_DESC_AGG_BREAK_8723B(__pTxDesc, __Value) 				SET_BITS_TO_LE_4BYTE(__pTxDesc+8, 16, 1, __Value)
#define SET_TX_DESC_MORE_FRAG_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+8, 17, 1, __Value)
#define SET_TX_DESC_RAW_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+8, 18, 1, __Value)
#define SET_TX_DESC_SPE_RPT_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+8, 19, 1, __Value)
#define SET_TX_DESC_AMPDU_DENSITY_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+8, 20, 3, __Value)
#define SET_TX_DESC_BT_INT_8723B(__pTxDesc, __Value)			SET_BITS_TO_LE_4BYTE(__pTxDesc+8, 23, 1, __Value)
#define SET_TX_DESC_GID_8723B(__pTxDesc, __Value)			SET_BITS_TO_LE_4BYTE(__pTxDesc+8, 24, 6, __Value)


// Dword 3
#define SET_TX_DESC_WHEADER_LEN_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+12, 0, 4, __Value)
#define SET_TX_DESC_CHK_EN_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+12, 4, 1, __Value)
#define SET_TX_DESC_EARLY_MODE_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+12, 5, 1, __Value)
#define SET_TX_DESC_HWSEQ_SEL_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+12, 6, 2, __Value)
#define SET_TX_DESC_USE_RATE_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+12, 8, 1, __Value)
#define SET_TX_DESC_DISABLE_RTS_FB_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+12, 9, 1, __Value)
#define SET_TX_DESC_DISABLE_FB_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+12, 10, 1, __Value)
#define SET_TX_DESC_CTS2SELF_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+12, 11, 1, __Value)
#define SET_TX_DESC_RTS_ENABLE_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+12, 12, 1, __Value)
#define SET_TX_DESC_HW_RTS_ENABLE_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+12, 13, 1, __Value)
#define SET_TX_DESC_NAV_USE_HDR_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+12, 15, 1, __Value)
#define SET_TX_DESC_USE_MAX_LEN_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+12, 16, 1, __Value)
#define SET_TX_DESC_MAX_AGG_NUM_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+12, 17, 5, __Value)
#define SET_TX_DESC_NDPA_8723B(__pTxDesc, __Value)		SET_BITS_TO_LE_4BYTE(__pTxDesc+12, 22, 2, __Value)
#define SET_TX_DESC_AMPDU_MAX_TIME_8723B(__pTxDesc, __Value)		SET_BITS_TO_LE_4BYTE(__pTxDesc+12, 24, 8, __Value)

// Dword 4
#define SET_TX_DESC_TX_RATE_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+16, 0, 7, __Value)
#define SET_TX_DESC_DATA_RATE_FB_LIMIT_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+16, 8, 5, __Value)
#define SET_TX_DESC_RTS_RATE_FB_LIMIT_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+16, 13, 4, __Value)
#define SET_TX_DESC_RETRY_LIMIT_ENABLE_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+16, 17, 1, __Value)
#define SET_TX_DESC_DATA_RETRY_LIMIT_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+16, 18, 6, __Value)
#define SET_TX_DESC_RTS_RATE_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+16, 24, 5, __Value)


// Dword 5
#define SET_TX_DESC_DATA_SC_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+20, 0, 4, __Value)
#define SET_TX_DESC_DATA_SHORT_8723B(__pTxDesc, __Value)	SET_BITS_TO_LE_4BYTE(__pTxDesc+20, 4, 1, __Value)
#define SET_TX_DESC_DATA_BW_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+20, 5, 2, __Value)
#define SET_TX_DESC_DATA_LDPC_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+20, 7, 1, __Value)
#define SET_TX_DESC_DATA_STBC_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+20, 8, 2, __Value)
#define SET_TX_DESC_CTROL_STBC_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+20, 10, 2, __Value)
#define SET_TX_DESC_RTS_SHORT_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+20, 12, 1, __Value)
#define SET_TX_DESC_RTS_SC_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+20, 13, 4, __Value)


// Dword 6
#define SET_TX_DESC_SW_DEFINE_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+24, 0, 12, __Value)
#define SET_TX_DESC_ANTSEL_A_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+24, 16, 3, __Value)
#define SET_TX_DESC_ANTSEL_B_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+24, 19, 3, __Value)
#define SET_TX_DESC_ANTSEL_C_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+24, 22, 3, __Value)
#define SET_TX_DESC_ANTSEL_D_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+24, 25, 3, __Value)

// Dword 7
#if(DEV_BUS_TYPE == RT_PCI_INTERFACE)
#define SET_TX_DESC_TX_BUFFER_SIZE_8723B(__pTxDesc, __Value)		SET_BITS_TO_LE_4BYTE(__pTxDesc+28, 0, 16, __Value)
#else
#define SET_TX_DESC_TX_DESC_CHECKSUM_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+28, 0, 16, __Value)
#endif
#define SET_TX_DESC_USB_TXAGG_NUM_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+28, 24, 8, __Value)
#if(DEV_BUS_TYPE == RT_SDIO_INTERFACE)
#define SET_TX_DESC_SDIO_TXSEQ_8723B(__pTxDesc, __Value)			SET_BITS_TO_LE_4BYTE(__pTxDesc+28, 16, 8, __Value)
#endif

// Dword 8
#define SET_TX_DESC_HWSEQ_EN_8723B(__pTxDesc, __Value)			SET_BITS_TO_LE_4BYTE(__pTxDesc+32, 15, 1, __Value)

// Dword 9
#define SET_TX_DESC_SEQ_8723B(__pTxDesc, __Value)					SET_BITS_TO_LE_4BYTE(__pTxDesc+36, 12, 12, __Value)

// Dword 10
#define SET_TX_DESC_TX_BUFFER_ADDRESS_8723B(__pTxDesc, __Value) 	SET_BITS_TO_LE_4BYTE(__pTxDesc+40, 0, 32, __Value)


// Dword 11
#define SET_TX_DESC_NEXT_DESC_ADDRESS_8723B(__pTxDesc, __Value) 	SET_BITS_TO_LE_4BYTE(__pTxDesc+48, 0, 32, __Value)

//-----------------------------------------------------------
//
//	Rate
//
//-----------------------------------------------------------
// CCK Rates, TxHT = 0
#define DESC8723B_RATE1M				0x00

#endif

/* TX BD */
#define SET_TXBUFFER_DESC_LEN_WITH_OFFSET(__pTxDesc, __Offset, __Valeu) \
	SET_BITS_TO_LE_4BYTE(__pTxDesc+(__Offset*8), 0, 16, __Valeu)
#define SET_TXBUFFER_DESC_AMSDU_WITH_OFFSET(__pTxDesc, __Offset, __Valeu) \
	SET_BITS_TO_LE_4BYTE(__pTxDesc+(__Offset*8), 31, 1, __Valeu)
#define SET_TXBUFFER_DESC_ADD_LOW_WITH_OFFSET(__pTxDesc, __Offset, __Valeu) \
	SET_BITS_TO_LE_4BYTE(__pTxDesc+(__Offset*8)+4, 0, 32, __Valeu)

s32 rtl8710ca_init_xmit_priv(PADAPTER);
void rtl8710ca_free_xmit_priv(PADAPTER);
s32 rtl8710ca_hal_xmitframe_enqueue(PADAPTER, struct xmit_frame *pxmitframe);
s32 rtl8710ca_hal_xmit(PADAPTER, struct xmit_frame *pxmitframe);
s32 rtl8710ca_mgnt_xmit(PADAPTER, struct xmit_frame *pxmitframe);
struct xmit_buf *rtl8710c_dequeue_xmitbuf(struct rtw_tx_ring *ring);

//s32 rtl8710ca_xmit_buf_handler(PADAPTER);
//thread_return rtl8710ca_xmit_thread(thread_context);

#endif /* _RTL8710CA_XMIT_H_ */
