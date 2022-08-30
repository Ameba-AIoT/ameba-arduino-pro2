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
#ifndef _RTL8735BA_XMIT_H_
#define _RTL8735BA_XMIT_H_

#include <drv_types.h>		/* PADAPTER, rtw_xmit.h and etc. */

#define TX_DESC_MODE        	1
#define MAX_TXBD_SEQMENT_NUM    ((TX_DESC_MODE)? (4*TX_DESC_MODE): 2) // TXBD_SEQMENT_NUM 0: 2, 1: 4, 2: 8
#define TXBD_SEGMENT_SIZE		8 // 8 bytes = 2DW

/* TX BD */
#define SET_TXBUFFER_DESC_LEN_WITH_OFFSET(__pTxDesc, __Offset, __Valeu) \
	SET_BITS_TO_LE_4BYTE(__pTxDesc+(__Offset*8), 0, 16, __Valeu)
#define SET_TXBUFFER_DESC_AMSDU_WITH_OFFSET(__pTxDesc, __Offset, __Valeu) \
	SET_BITS_TO_LE_4BYTE(__pTxDesc+(__Offset*8), 31, 1, __Valeu)
#define SET_TXBUFFER_DESC_ADD_LOW_WITH_OFFSET(__pTxDesc, __Offset, __Valeu) \
	SET_BITS_TO_LE_4BYTE(__pTxDesc+(__Offset*8)+4, 0, 32, __Valeu)

s32 rtl8735ba_init_xmit_priv(PADAPTER);
void rtl8735ba_free_xmit_priv(PADAPTER);
s32 rtl8735ba_hal_xmitframe_enqueue(PADAPTER, struct xmit_frame *pxmitframe);
s32 rtl8735ba_hal_xmit(PADAPTER, struct xmit_frame *pxmitframe);
s32 rtl8735ba_mgnt_xmit(PADAPTER, struct xmit_frame *pxmitframe);
struct xmit_buf *rtl8735b_dequeue_xmitbuf(struct rtw_tx_ring *ring);

//s32 rtl8735ba_xmit_buf_handler(PADAPTER);
//thread_return rtl8735ba_xmit_thread(thread_context);

#endif /* _RTL8735BA_XMIT_H_ */
