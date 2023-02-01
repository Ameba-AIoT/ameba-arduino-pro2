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
#ifndef _RTL8710CA_RECV_H_
#define _RTL8710CA_RECV_H_

#include <drv_types.h>		/* PADAPTER and etc. */
#if defined(RTW_HALMAC)
#include "hal_halmac.h"	/* HALMAC_RX_FIFO_SIZE_8710C */
#endif

#if (SKB_PRE_ALLOCATE_RX==1)
#define MAX_RECVBUF_SZ	MAX_SKB_BUF_SIZE //1650 //(RX_DMA_SIZE_8195A - RX_DMA_RESERVED_SIZE_8195A)
#else
#define MAX_RECVBUF_SZ	(HAL_INTERFACE_OVERHEAD_SKB_DATA+RX_DRIVER_INFO+\
						RXDESC_SIZE +\
						(MAX_RX_PKT_LIMIT * 512) +\
						SKB_RESERVED_FOR_SAFETY)		// 0+32+24+512*4+0 = 2104
#endif

s32 rtl8710ca_init_recv_priv(PADAPTER);
void rtl8710ca_free_recv_priv(PADAPTER);
/*_pkt* rtl8710ca_alloc_recvbuf_skb(struct recv_buf*, u32 size);*/
/*void rtl8710ca_free_recvbuf_skb(struct recv_buf*);*/
void rtl8710c_query_rx_desc_status(union recv_frame *precvframe, u8 *pdesc);
void rtl8710c_query_rx_phy_status(union recv_frame	*precvframe, u8 *pphy_status);
void rtl8710ca_rxhandler(PADAPTER, struct recv_buf *);

#endif /* _RTL8710CA_RECV_H_ */
