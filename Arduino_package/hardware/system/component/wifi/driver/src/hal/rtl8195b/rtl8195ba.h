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
#ifndef _RTL8195BA_H_
#define _RTL8195BA_H_

#include <drv_types.h>		/* PADAPTER */

/* rtl8195ba_halinit.c */
u32 rtl8195ba_hal_init(PADAPTER);
u32 rtl8195ba_hal_deinit(PADAPTER adapter);
u32 rtl8195ba_inirp_init(PADAPTER padapter);
u32 rtl8195ba_inirp_deinit(_adapter *padapter);

void rtl8195ba_init_default_value(PADAPTER);

/* rtl8195ba_ops.c */


#endif /* _RTL8195BA_HAL_H_ */
