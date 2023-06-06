/******************************************************************************
 *
 * Copyright(c) 2016 - 2018 Realtek Corporation. All rights reserved.
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
 ******************************************************************************/

#ifndef HALMAC_POWER_SEQUENCE_8735B
#define HALMAC_POWER_SEQUENCE_8735B

#include "../../halmac_pwr_seq_cmd.h"
#include "../../halmac_hw_cfg.h"

#if HALMAC_8735B_SUPPORT

#define HALMAC_8735B_PWR_SEQ_VER  "V6"

extern struct halmac_wlan_pwr_cfg *card_dis_flow_8735b[];
extern struct halmac_wlan_pwr_cfg *card_en_flow_8735b[];
extern struct halmac_wlan_pwr_cfg *suspend_flow_8735b[];
extern struct halmac_wlan_pwr_cfg *resume_flow_8735b[];
extern struct halmac_wlan_pwr_cfg *hwpdn_flow_8735b[];
extern struct halmac_wlan_pwr_cfg *enter_lps_flow_8735b[];
extern struct halmac_wlan_pwr_cfg *enter_dlps_flow_8735b[];
extern struct halmac_wlan_pwr_cfg *leave_lps_flow_8735b[];

#endif /* HALMAC_8735B_SUPPORT */

#endif
