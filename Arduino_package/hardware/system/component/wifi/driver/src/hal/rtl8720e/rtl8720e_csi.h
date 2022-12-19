/******************************************************************************
 *
 * Copyright(c)2019 Realtek Corporation.
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
 *****************************************************************************/
#ifndef __RTL8720E_CSI_H__
#define __RTL8720E_CSI_H__

#ifdef CONFIG_CSI

#define CSI_MAX_SIZE  2048
#define CSI_PKT_TOTAL  1
#define CSI_REPORRT_DONE_TIMEOUT  10  /* ms */
#define CSI_BB_BLOCK_SZ  (10 * 128)
#define CSI_BB_BLOCK_NUM  2

struct rtw_csi_bbcr_cfg {
	bool csi_phy0_en;
	bool csi_phy1_en;
	u32 csi_ele_bitmap;
	u8 csi_grp_num_non_he;  /* 0:per tone; 1:per 2tone; 2:per 4tone; 3:per 16tone */
	u8 csi_grp_num_he;
	bool csi_alg_opt;  /* 0:LS(channel estimation); 1:CS(channel smoothing) */
	bool csi_ch_opt;  /* 0:legacy portion; 1:no-legacy portion */
	bool csi_wl_opt;  /* 0:S(8,4); 1:S(16,12) */
	bool csi_type;  /* 0:legacy channel; 1:mimo channel */
	u8 csi_seg_len;  /* 0:12(96bytes); 1:28(224bytes);2:60(480bytes);3:124(992bytes) */
	u8 csi_blk_start_idx;
	u8 csi_blk_end_idx;
};

struct rtw_csi_rpt_hdr_info {
	u32 total_len;  /* header(16byte) + Raw data length(Unit: byte) */
	u8 total_seg_num;
	u8 avg_noise_pow;
	bool is_pkt_end;
	bool set_valid;
	u8 nr;
	u8 nc;
	u8 segment_size;  /* unit (8Bytes) */
	u8 sts0_evm;
	u8 sequence_number;
};

struct rtw_csi_phyinfo_rpt {
	u8 rssi[2];
	u16 amp_wgt_rx0;
	u8 rssi_avg;
	u8 sts1_evm;
	u8 rxsc;
	u16 amp_wgt_rx1;
};

struct rtw_csi_drv_rpt {
	u32 raw_data_len;
	u8 seg_idx_curr;
};

struct rtw_csi_desc {
	u8 rx_bw;
	u16 csi_length;
	u16 rx_rate;
	u32 r_rx_tsfl;
};

struct rx_csi_data {
	_list list;
	u8 *csi_buffer;
	u32 length;
	rtw_csi_header_t csi_header;
};

struct rx_csi_pool {
	struct rx_csi_data csi_pkt[CSI_PKT_TOTAL];
	_list idle;
	_list busy;
	_lock idle_lock;  /* spinlock */
	_lock busy_lock;  /* spinlock */
	u32 idle_cnt;
	u32 busy_cnt;
};

void rtl8720e_csi_deinit(_adapter *padapter);
s32 rtl8720e_csi_en(_adapter *padapter, rtw_csi_action_parm_t *act_param);
s32 rtl8720e_csi_cfg(_adapter *padapter, rtw_csi_action_parm_t *act_param);
s32 rtl8720e_csi_report(_adapter *padapter, u32 buf_len, u8 *csi_buf, u32 *len, rtw_csi_header_t *csi_hdr);
void rtl8720e_csi_pkt_hdl(_adapter *padapter, u8 *buf, struct rtw_csi_desc *csi_desc);
#endif /* CONFIG_CSI */

#endif
