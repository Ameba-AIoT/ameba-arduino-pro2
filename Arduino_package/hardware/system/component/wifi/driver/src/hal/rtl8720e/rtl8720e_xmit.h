/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
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
#ifndef __RTL8720E_XMIT_H__
#define __RTL8720E_XMIT_H__

//
// Queue Select Value in TxDesc
//
#define QSLT_BK							0x2//0x01
#define QSLT_BE							0x0
#define QSLT_VI							0x5//0x4
#define QSLT_VO							0x7//0x6
#define QSLT_BEACON						0x10
#define QSLT_HIGH						0x11
#define QSLT_MGNT						0x12
#define QSLT_CMD						0x13

#define MAX_TID (15)

//OFFSET 0
#define OFFSET_SZ	0
#define OFFSET_SHT	16
#define BMC		BIT(24)
#define LSG		BIT(26)
#define FSG		BIT(27)
#define OWN 		BIT(31)


//OFFSET 4
#define PKT_OFFSET_SZ	0
#define BK		BIT(6)
#define QSEL_SHT	8
#define Rate_ID_SHT	16
#define NAVUSEHDR	BIT(20)
#define PKT_OFFSET_SHT	26
#define HWPC		BIT(31)

//OFFSET 8
#define AGG_EN		BIT(29)

//OFFSET 12
#define SEQ_SHT		16

//OFFSET 16
#define QoS		BIT(6)
#define HW_SEQ_EN	BIT(7)
#define USERATE		BIT(8)
#define DISDATAFB	BIT(10)
#define DATA_SHORT	BIT(24)
#define DATA_BW		BIT(25)

//OFFSET 20
#define SGI		BIT(6)

//
//defined for TX DESC Operation
//
//20211203 R01 updated
typedef struct txdesc_8723b {
	// Offset 0
	u32 pktlen: 16;
	u32 offset: 8;
	u32 bmc: 1;
	u32 rsvd0025: 1;
	u32 rsvd0026: 1;
	u32 rsvd0027: 1;
	u32 bcnpkt_tsf_ctrl: 1;
	u32 noacm: 1;
	u32 gf: 1;
	u32 rsvd0031: 1;

	// Offset 4
	u32 macid: 7;
	u32 bip_keyid_sel: 1;
	u32 qsel: 5;
	u32 force_txop: 1;
	u32 lsig_txop_en: 1;
	u32 pifs: 1;
	u32 a_ctrl_cas: 1;
	u32 a_ctrl_bsr: 1;
	u32 a_ctrl_uph: 1;
	u32 a_ctrl_bqr: 1;
	u32 htc: 1;
	u32 en_desc_id: 1;
	u32 sectype: 2;
	u32 pkt_offset: 5; // unit: 8 bytes
	u32 moredata: 1;
	u32 ftm_en: 1;
	u32 hw_aesiv: 1;

	// Offset 8
	u32 p_aid: 9;
	u32 tri_frame: 1;
	u32 cca_rts: 2;
	u32 agg_en: 1;
	u32 ack_ch_info: 1;
	u32 null_0: 1;
	u32 null_1: 1;
	u32 bk: 1;
	u32 tm_en: 1;
	u32 raw: 1;
	u32 ccx: 1;
	u32 ampdu_density: 3;
	u32 bt_int: 1;
	u32 spe_frame_ind: 3;
	u32 mu_snd_flag: 1;
	u32 rsvd0828: 4;

	// Offset 12
	u32 wheader_len: 5;
	u32 txdesc_info_en: 1;
	u32 hw_ssn_sel: 2;
	u32 userate: 1;
	u32 disrtsfb: 1;
	u32 disdatafb: 1;
	u32 cts2self: 1;
	u32 rtsen: 1;
	u32 hw_rts_en: 1;
	u32 chk_en: 1;
	u32 navusehdr: 1;
	u32 use_max_time: 1;
	u32 max_agg_num: 5;
	u32 ndpa: 2;
	u32 ampdu_max_time: 8;

	// Offset 16
	u32 data_rate: 9;
	u32 data_rty_lowest_rate: 9;
	u32 retry_limit: 6;
	u32 obw_cts2self_dup_type: 4;
	u32 try_rate: 1;
	u32 gi_ltf: 3;

	// Offset 20
	u32 data_sc: 4;
	u32 data_dcm: 1;
	u32 data_bw: 2;
	u32 data_ldpc: 1;
	u32 data_stbc: 2;
	u32 rts_stbc: 2;
	u32 rts_short: 1;
	u32 rts_sc: 4;
	u32 signaling_tapkt: 1;
	u32 data_bw_er: 1;
	u32 data_er: 1;
	u32 multi_port_id: 4;
	u32 tx_ant: 4;
	u32 rsvd2028: 2;
	u32 port_id: 1;
	u32 polluted: 1;

	// Offset 24
	u32 rtsrate: 9;
	u32 rts_rty_lowest_rate: 9;
	u32 antsel_en: 1;
	u32 rty_use_des: 1;
	u32 antsel_A: 1;
	u32 antsel_B: 1;
	u32 antsel_C: 1;
	u32 antsel_D: 1;
	u32 ant_mapA: 2;
	u32 ant_mapB: 2;
	u32 ant_mapC: 2;
	u32 ant_mapD: 2;

	// Offset 28
	u32 checksum: 16;
	u32 sw_define_l: 7;
	u32 usb_txagg_num: 9;

	// Offset 32
	u32 rts_rc: 6;
	u32 bar_rty_th: 2;
	u32 data_rc: 6;
	u32 vendor_adv: 1;
	u32 en_hwseq: 1;
	u32 nextheadpage_l: 8;
	u32 tailpage_l: 8;

	// Offset 36
	u32 group_bit_ie: 8;
	u32 sw_define_h: 4;
	u32 seq: 12;
	u32 nextheadpage_h: 4;
	u32 tailpage_h: 4;
} TXDESC_8723B, *PTXDESC_8723B;

#ifndef __INC_HAL8723BDESC_H
#define __INC_HAL8723BDESC_H

#define RX_STATUS_DESC_SIZE_8723B		24
#define RX_DRV_INFO_SIZE_UNIT_8723B 8


//DWORD 0
#define SET_RX_STATUS_DESC_PKT_LEN_8723B(__pRxStatusDesc, __Value)		SET_BITS_TO_LE_4BYTE( __pRxStatusDesc, 0, 14, __Value)
#define SET_RX_STATUS_DESC_EOR_8723B(__pRxStatusDesc, __Value)		SET_BITS_TO_LE_4BYTE( __pRxStatusDesc, 30, 1, __Value)
#define SET_RX_STATUS_DESC_OWN_8723B(__pRxStatusDesc, __Value)		SET_BITS_TO_LE_4BYTE( __pRxStatusDesc, 31, 1, __Value)

#define GET_RX_STATUS_DESC_PKT_LEN_8723B(__pRxStatusDesc)			LE_BITS_TO_4BYTE( __pRxStatusDesc, 0, 14)
#define GET_RX_STATUS_DESC_CRC32_8723B(__pRxStatusDesc) 		LE_BITS_TO_4BYTE( __pRxStatusDesc, 14, 1)
#define GET_RX_STATUS_DESC_ICV_8723B(__pRxStatusDesc)				LE_BITS_TO_4BYTE( __pRxStatusDesc, 15, 1)
#define GET_RX_STATUS_DESC_DRVINFO_SIZE_8723B(__pRxStatusDesc)		LE_BITS_TO_4BYTE( __pRxStatusDesc, 16, 4)
#define GET_RX_STATUS_DESC_SECURITY_8723B(__pRxStatusDesc)			LE_BITS_TO_4BYTE( __pRxStatusDesc, 20, 3)
#define GET_RX_STATUS_DESC_QOS_8723B(__pRxStatusDesc)				LE_BITS_TO_4BYTE( __pRxStatusDesc, 23, 1)
#define GET_RX_STATUS_DESC_SHIFT_8723B(__pRxStatusDesc) 		LE_BITS_TO_4BYTE( __pRxStatusDesc, 24, 2)
#define GET_RX_STATUS_DESC_PHY_STATUS_8723B(__pRxStatusDesc)			LE_BITS_TO_4BYTE( __pRxStatusDesc, 26, 1)
#define GET_RX_STATUS_DESC_SWDEC_8723B(__pRxStatusDesc) 		LE_BITS_TO_4BYTE( __pRxStatusDesc, 27, 1)
#define GET_RX_STATUS_DESC_LAST_SEG_8723B(__pRxStatusDesc)			LE_BITS_TO_4BYTE( __pRxStatusDesc, 28, 1)
#define GET_RX_STATUS_DESC_FIRST_SEG_8723B(__pRxStatusDesc) 		LE_BITS_TO_4BYTE( __pRxStatusDesc, 29, 1)
#define GET_RX_STATUS_DESC_EOR_8723B(__pRxStatusDesc)				LE_BITS_TO_4BYTE( __pRxStatusDesc, 30, 1)
#define GET_RX_STATUS_DESC_OWN_8723B(__pRxStatusDesc)				LE_BITS_TO_4BYTE( __pRxStatusDesc, 31, 1)

//DWORD 1
#define GET_RX_STATUS_DESC_MACID_8723B(__pRxDesc)					LE_BITS_TO_4BYTE(__pRxDesc+4, 0, 7)
#define GET_RX_STATUS_DESC_TID_8723B(__pRxDesc) 					LE_BITS_TO_4BYTE(__pRxDesc+4, 8, 4)
#define GET_RX_STATUS_DESC_AMSDU_8723B(__pRxDesc)					LE_BITS_TO_4BYTE(__pRxDesc+4, 13, 1)
#define GET_RX_STATUS_DESC_RXID_MATCH_8723B(__pRxDesc)		LE_BITS_TO_4BYTE( __pRxDesc+4, 14, 1)
#define GET_RX_STATUS_DESC_PAGGR_8723B(__pRxDesc)				LE_BITS_TO_4BYTE( __pRxDesc+4, 15, 1)
#define GET_RX_STATUS_DESC_A1_FIT_8723B(__pRxDesc)				LE_BITS_TO_4BYTE( __pRxDesc+4, 16, 4)
#define GET_RX_STATUS_DESC_CHKERR_8723B(__pRxDesc)				LE_BITS_TO_4BYTE( __pRxDesc+4, 20, 1)
#define GET_RX_STATUS_DESC_IPVER_8723B(__pRxDesc)			LE_BITS_TO_4BYTE(__pRxDesc+4, 21, 1)
#define GET_RX_STATUS_DESC_IS_TCPUDP__8723B(__pRxDesc)		LE_BITS_TO_4BYTE(__pRxDesc+4, 22, 1)
#define GET_RX_STATUS_DESC_CHK_VLD_8723B(__pRxDesc) 	LE_BITS_TO_4BYTE(__pRxDesc+4, 23, 1)
#define GET_RX_STATUS_DESC_PAM_8723B(__pRxDesc) 			LE_BITS_TO_4BYTE( __pRxDesc+4, 24, 1)
#define GET_RX_STATUS_DESC_PWR_8723B(__pRxDesc) 			LE_BITS_TO_4BYTE( __pRxDesc+4, 25, 1)
#define GET_RX_STATUS_DESC_MORE_DATA_8723B(__pRxDesc)			LE_BITS_TO_4BYTE( __pRxDesc+4, 26, 1)
#define GET_RX_STATUS_DESC_MORE_FRAG_8723B(__pRxDesc)			LE_BITS_TO_4BYTE( __pRxDesc+4, 27, 1)
#define GET_RX_STATUS_DESC_TYPE_8723B(__pRxDesc)			LE_BITS_TO_4BYTE( __pRxDesc+4, 28, 2)
#define GET_RX_STATUS_DESC_MC_8723B(__pRxDesc)				LE_BITS_TO_4BYTE( __pRxDesc+4, 30, 1)
#define GET_RX_STATUS_DESC_BC_8723B(__pRxDesc)				LE_BITS_TO_4BYTE( __pRxDesc+4, 31, 1)

//DWORD 2
#define GET_RX_STATUS_DESC_SEQ_8723B(__pRxStatusDesc)					LE_BITS_TO_4BYTE( __pRxStatusDesc+8, 0, 12)
#define GET_RX_STATUS_DESC_FRAG_8723B(__pRxStatusDesc)				LE_BITS_TO_4BYTE( __pRxStatusDesc+8, 12, 4)
#define GET_RX_STATUS_DESC_RX_IS_QOS_8723B(__pRxStatusDesc) 		LE_BITS_TO_4BYTE( __pRxStatusDesc+8, 16, 1)
#define GET_RX_STATUS_DESC_WLANHD_IV_LEN_8723B(__pRxStatusDesc) 	LE_BITS_TO_4BYTE( __pRxStatusDesc+8, 18, 6)
#define GET_RX_STATUS_DESC_RPT_SEL_8723B(__pRxStatusDesc)			LE_BITS_TO_4BYTE( __pRxStatusDesc+8, 28, 1)

//DWORD 3
#define GET_RX_STATUS_DESC_RX_RATE_8723B(__pRxStatusDesc)				LE_BITS_TO_4BYTE( __pRxStatusDesc+12, 0, 7)
#define GET_RX_STATUS_DESC_HTC_8723B(__pRxStatusDesc)					LE_BITS_TO_4BYTE( __pRxStatusDesc+12, 10, 1)
#define GET_RX_STATUS_DESC_EOSP_8723B(__pRxStatusDesc)					LE_BITS_TO_4BYTE( __pRxStatusDesc+12, 11, 1)
#define GET_RX_STATUS_DESC_BSSID_FIT_8723B(__pRxStatusDesc) 		LE_BITS_TO_4BYTE( __pRxStatusDesc+12, 12, 2)
#ifdef CONFIG_USB_RX_AGGREGATION
#define GET_RX_STATUS_DESC_USB_AGG_PKTNUM_8723B(__pRxStatusDesc)	LE_BITS_TO_4BYTE( __pRxStatusDesc+12, 16, 8)
#endif
#define GET_RX_STATUS_DESC_PATTERN_MATCH_8723B(__pRxDesc)			LE_BITS_TO_4BYTE( __pRxDesc+12, 29, 1)
#define GET_RX_STATUS_DESC_UNICAST_MATCH_8723B(__pRxDesc)			LE_BITS_TO_4BYTE( __pRxDesc+12, 30, 1)
#define GET_RX_STATUS_DESC_MAGIC_MATCH_8723B(__pRxDesc) 		LE_BITS_TO_4BYTE( __pRxDesc+12, 31, 1)

//DWORD 6
#define GET_RX_STATUS_DESC_SPLCP_8723B(__pRxDesc)			LE_BITS_TO_4BYTE( __pRxDesc+16, 0, 1)
#define GET_RX_STATUS_DESC_LDPC_8723B(__pRxDesc)			LE_BITS_TO_4BYTE( __pRxDesc+16, 1, 1)
#define GET_RX_STATUS_DESC_STBC_8723B(__pRxDesc)			LE_BITS_TO_4BYTE( __pRxDesc+16, 2, 1)
#define GET_RX_STATUS_DESC_BW_8723B(__pRxDesc)			LE_BITS_TO_4BYTE( __pRxDesc+16, 4, 2)

//DWORD 5
#define GET_RX_STATUS_DESC_TSFL_8723B(__pRxStatusDesc)				LE_BITS_TO_4BYTE( __pRxStatusDesc+20, 0, 32)

#define GET_RX_STATUS_DESC_BUFF_ADDR_8723B(__pRxDesc)		LE_BITS_TO_4BYTE(__pRxDesc+24, 0, 32)
#define GET_RX_STATUS_DESC_BUFF_ADDR64_8723B(__pRxDesc) 		LE_BITS_TO_4BYTE(__pRxDesc+28, 0, 32)

#define SET_RX_STATUS_DESC_BUFF_ADDR_8723B(__pRxDesc, __Value)	SET_BITS_TO_LE_4BYTE(__pRxDesc+24, 0, 32, __Value)


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
#if defined(DEV_BUS_TYPE) && (DEV_BUS_TYPE == RT_PCI_INTERFACE)
#define SET_TX_DESC_TX_BUFFER_SIZE_8723B(__pTxDesc, __Value)		SET_BITS_TO_LE_4BYTE(__pTxDesc+28, 0, 16, __Value)
#else
#define SET_TX_DESC_TX_DESC_CHECKSUM_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+28, 0, 16, __Value)
#endif
#define SET_TX_DESC_USB_TXAGG_NUM_8723B(__pTxDesc, __Value) SET_BITS_TO_LE_4BYTE(__pTxDesc+28, 24, 8, __Value)
#if defined(DEV_BUS_TYPE) && (DEV_BUS_TYPE == RT_SDIO_INTERFACE)
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


#define SET_EARLYMODE_PKTNUM_8723B(__pAddr, __Value)					SET_BITS_TO_LE_4BYTE(__pAddr, 0, 4, __Value)
#define SET_EARLYMODE_LEN0_8723B(__pAddr, __Value)					SET_BITS_TO_LE_4BYTE(__pAddr, 4, 15, __Value)
#define SET_EARLYMODE_LEN1_1_8723B(__pAddr, __Value)					SET_BITS_TO_LE_4BYTE(__pAddr, 19, 13, __Value)
#define SET_EARLYMODE_LEN1_2_8723B(__pAddr, __Value)					SET_BITS_TO_LE_4BYTE(__pAddr+4, 0, 2, __Value)
#define SET_EARLYMODE_LEN2_8723B(__pAddr, __Value)					SET_BITS_TO_LE_4BYTE(__pAddr+4, 2, 15,	__Value)
#define SET_EARLYMODE_LEN3_8723B(__pAddr, __Value)					SET_BITS_TO_LE_4BYTE(__pAddr+4, 17, 15, __Value)

#endif
//-----------------------------------------------------------
//
//	Rate
//
//-----------------------------------------------------------
// CCK Rates, TxHT = 0
#define DESC8723B_RATE1M				0x00
#define DESC8723B_RATE2M				0x01
#define DESC8723B_RATE5_5M				0x02
#define DESC8723B_RATE11M				0x03

// OFDM Rates, TxHT = 0
#define DESC8723B_RATE6M				0x04
#define DESC8723B_RATE9M				0x05
#define DESC8723B_RATE12M				0x06
#define DESC8723B_RATE18M				0x07
#define DESC8723B_RATE24M				0x08
#define DESC8723B_RATE36M				0x09
#define DESC8723B_RATE48M				0x0a
#define DESC8723B_RATE54M				0x0b

// MCS Rates, TxHT = 1
#define DESC8723B_RATEMCS0				0x0c
#define DESC8723B_RATEMCS1				0x0d
#define DESC8723B_RATEMCS2				0x0e
#define DESC8723B_RATEMCS3				0x0f
#define DESC8723B_RATEMCS4				0x10
#define DESC8723B_RATEMCS5				0x11
#define DESC8723B_RATEMCS6				0x12
#define DESC8723B_RATEMCS7				0x13
#define DESC8723B_RATEMCS8				0x14
#define DESC8723B_RATEMCS9				0x15
#define DESC8723B_RATEMCS10 		0x16
#define DESC8723B_RATEMCS11 		0x17
#define DESC8723B_RATEMCS12 		0x18
#define DESC8723B_RATEMCS13 		0x19
#define DESC8723B_RATEMCS14 		0x1a
#define DESC8723B_RATEMCS15 		0x1b
#define DESC8723B_RATEVHTSS1MCS0		0x2c
#define DESC8723B_RATEVHTSS1MCS1		0x2d
#define DESC8723B_RATEVHTSS1MCS2		0x2e
#define DESC8723B_RATEVHTSS1MCS3		0x2f
#define DESC8723B_RATEVHTSS1MCS4		0x30
#define DESC8723B_RATEVHTSS1MCS5		0x31
#define DESC8723B_RATEVHTSS1MCS6		0x32
#define DESC8723B_RATEVHTSS1MCS7		0x33
#define DESC8723B_RATEVHTSS1MCS8		0x34
#define DESC8723B_RATEVHTSS1MCS9		0x35
#define DESC8723B_RATEVHTSS2MCS0		0x36
#define DESC8723B_RATEVHTSS2MCS1		0x37
#define DESC8723B_RATEVHTSS2MCS2		0x38
#define DESC8723B_RATEVHTSS2MCS3		0x39
#define DESC8723B_RATEVHTSS2MCS4		0x3a
#define DESC8723B_RATEVHTSS2MCS5		0x3b
#define DESC8723B_RATEVHTSS2MCS6		0x3c
#define DESC8723B_RATEVHTSS2MCS7		0x3d
#define DESC8723B_RATEVHTSS2MCS8		0x3e
#define DESC8723B_RATEVHTSS2MCS9		0x3f


#define 	RX_HAL_IS_CCK_RATE_8723B(pDesc)\
			(GET_RX_STATUS_DESC_RX_RATE_8723B(pDesc) == DESC8723B_RATE1M ||\
			GET_RX_STATUS_DESC_RX_RATE_8723B(pDesc) == DESC8723B_RATE2M ||\
			GET_RX_STATUS_DESC_RX_RATE_8723B(pDesc) == DESC8723B_RATE5_5M ||\
			GET_RX_STATUS_DESC_RX_RATE_8723B(pDesc) == DESC8723B_RATE11M)

#define GET_FIX_RATE_8720E(v)		((v) & 0x0FFF)
#define GET_FIX_RATE_SGI_8720E(v)	(((v) & 0x7000) >> 12)

void rtl8720e_update_txdesc(struct xmit_frame *pxmitframe, u8 *pmem);
void rtl8720e_fill_fake_txdesc(PADAPTER padapter, u8 *pDesc, u32 BufferLen, u8 IsPsPoll, u8 IsBTQosNull, u8 bDataFrame);
#ifdef CONFIG_MP_INCLUDED
void rtl8720e_prepare_mp_txdesc(PADAPTER adapter, struct mp_priv *pmp_priv);
#endif

s32 rtl8720ed_init_xmit_priv(PADAPTER padapter);
void rtl8720ed_free_xmit_priv(PADAPTER padapter);
s32	rtl8720ed_hal_xmit(_adapter *padapter, struct xmit_frame *pxmitframe);
s32 rtl8720ed_mgnt_xmit(_adapter *padapter, struct xmit_frame *pmgntframe);
s32	rtl8720ed_hal_xmitframe_enqueue(_adapter *padapter, struct xmit_frame *pxmitframe);
void rtl8720e_xmitframe_resume(_adapter *padapter);
u32 GetDmaTxbdIdx(u32 ff_hwaddr);
struct xmit_buf *rtl8720e_dequeue_xmitbuf(struct rtw_tx_ring	*ring);
BOOLEAN FreeXimtBuf(struct xmit_buf *pxmitbuf);
u8 check_tx_desc_resource(_adapter *padapter, int prio);


#endif

