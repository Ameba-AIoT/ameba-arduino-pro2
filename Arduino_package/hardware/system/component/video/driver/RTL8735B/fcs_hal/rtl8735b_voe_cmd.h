
/**************************************************************************//**
 * @file     rtl8735b_voe_cmd.h
 * @brief    The interface commands implementation header file.
 *
 * @version  V1.00
 * @date     2020-11-25
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
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

#ifndef _RTL8735B_VOE_CMD_H_
#define _RTL8735B_VOE_CMD_H_

// TM9 <--> KM4 command 30 bit
// command 14 bit 0x3FFF0000
// Module index 0x0
#define FW_INITIAL_ITCM_CMD                 0x1
#define FW_INITIAL_DTCM_CMD                 0x2
#define FW_INITIAL_ERROR_CMD                0x3
#define FW_INITIAL_ITCM_DONE_CMD            0x4
#define FW_INITIAL_DTCM_DONE_CMD            0x5
#define FW_DUMP_ITCM_CMD                    0x6
#define FW_DUMP_DTCM_CMD                    0x7
#define FW_REBOOT_CMD                       0x8
#define FW_DUMP_COMPILE_TIME_CMD            0x9
#define FW_DUMP_COMPILE_TIME_DONE_CMD       0xA
#define FW_DUMP_IMAGE_STATE_CMD             0xB
#define FW_DUMP_IMAGE_STATE_DONE_CMD        0xC
#define FW_REBOOT_DONE_CMD                  0xD
#define FW_VERIFY_DTCM_PATTERN_1_CMD        0xE
#define FW_VERIFY_DTCM_PATTERN_2_CMD        0xF
#define FW_CHECK_PATTERN_1_CMD              0x10
#define FW_CHECK_PATTERN_2_CMD              0x11
#define FW_BOOT_DONE_CMD                    0x12


// ERAC set
// Module index 0x100
#define FW_RET_ERAC_OK                   0x100		// KM --> TM
#define FW_RET_ERAC_ERR                  0x1FF		// KM --> TM

#define FW_ERAC_INIT_CMD                 0x110
#define FW_ERAC_WRITE_CMD                0x120
#define FW_ERAC_READ_CMD                 0x130


// VOE CMD/STATUS/CHANNEL set

// VOE STATUS (8 bit)
#define VOE_OK                           0x00
#define VOE_NOK                          0x01
#define VOE_ENC_BUF_OVERFLOW             0x02
#define VOE_ENC_QUEUE_OVERFLOW           0x03
#define VOE_JPG_BUF_OVERFLOW             0x04
#define VOE_JPG_QUEUE_OVERFLOW           0x05

// VOE CMD  (14 bit)

// VOE normal control flow

#define VOE_OPEN_CMD                     0x206
#define VOE_CLOSE_CMD                    0x207
#define VOE_RELEASE_ENC_CMD              0x208
#define VOE_RELEASE_JPG_CMD              0x209
#define VOE_OUT_CMD                      0x20B

#define VOE_FORCE_I_CMD                  0x20D
#define VOE_SET_RC_CMD                   0x20E


#define VOE_ROI_REGION_CMD               0x211

#define VOE_EXT_IN_CMD                   0x212
#define VOE_SYNC_CMD                     0x213

#define VOE_ENC_OUT_CMD                  0x215
#define VOE_JPG_OUT_CMD                  0x216
#define VOE_YUV_OUT_CMD                  0x217

// VOE debug/information command
#define VOE_MEM_INFO_CMD                 0x220
#define VOE_BUF_INFO_CMD                 0x221
#define VOE_TIME_INFO_CMD                0x222


#define VOE_PRINT_CMD                    0x225
#define VOE_GMON_CMD                     0x227
#define VOE_TEST_CMD                     0x22F

// ISP related command
#define VOE_ISP_CTRL_GET_CMD			 0x240
#define VOE_ISP_CTRL_SET_CMD			 0x241
#define VOE_ISP_TUNING_GET_IQ            0x242
#define VOE_ISP_TUNING_SET_IQ            0x243
#define VOE_ISP_TUNING_GET_STATIS        0x244
#define VOE_ISP_TUNING_GET_PARAM         0x245
#define VOE_ISP_TUNING_SET_PARAM         0x246

#define VOE_ISP_BUF_RELEASE_CMD          0x247
#define VOE_ISP_SET_RAWFMTE_CMD          0x248

#define VOE_ISP_TUNING_READ_VREG         0x249
#define VOE_ISP_TUNING_WRITE_VREG        0x24A

#define VOE_ISP_SET_SENSOR_MODE			 0x24B
#define VOE_ISP_GET_SENSOR_MODE			 0x24C

#define VOE_ISP_GET_3A_STATIS			 0x24D

#define VOE_ISP_GET_REAL_FPS			 0x24E

#define VOE_ISP_GET_AE_WEIGHT			 0x24F
#define VOE_ISP_SET_AE_WEIGHT			 0x250
#define VOE_ISP_SET_MASK				 0x251

#define VOE_ISP_SET_ZOOM_CROP			 0x252

#define VOE_SET_IQ_CALI_ENABLE			 0x253

#define VOE_ISP_SET_STM_FPS				 0x254

//OSD
#define VOE_OSD_QUERY                    0x260
#define VOE_OSD_UPDATE                   0x261
#define VOE_OSD_ENABLE                   0x262
#define VOE_OSD_ENC_EN                   0x263
#define VOE_OSD_COLOR_TABLE_SET          0x264
#define VOE_OSD_COLOR_TABLE_GET          0x265

//I2C
#define VOE_I2C_READ                     0x270
#define VOE_I2C_WRITE                    0x271

// VOE peripheral command
#define VOE_SET_WDT_CMD                  0x280

//MD
#define VOE_MD_START                     0x290
#define VOE_MD_STOP                      0x291
#define VOE_MD_GET_BUF                   0x292
#define VOE_MD_TRIGGER                   0x293
#define VOE_MD_GET_PARAM                 0x294


#define VOE_CMD_RET_ERR                  0x2FF


#define FW_RET_OK                           0x005		// KM --> TM


// VOE Verification Set

#define FW_RET_VERIFY_OK 					0x400
#define FW_RET_VERIFY_ERR                   0x4FF

#define FW_VERIFY_RDSLAVE					0x410		// KM master read other slave
#define FW_VERIFY_WRSLAVE                   0x420		// KM write read other slave
#define ISP_VERIFY_FULL						0x430		// KM verify ISP
#define ISP_VERIFY_GET_ADPTER       		0x440		// KM verify ISP - get adapter
#define FW_VERIFY_HOLE						0x450		// KM check register hole
#define VERIFY_PERI_INTC	     	  		0x460		// Show ISR handle information

#define FW_PROC_ERROR_RET                   0x3FFF


#define FW_3DNR_START_CMD                   0x310

#define FW_3DNR_DONE_RET                    0x3301


// Command index
#define CMD_ERAC_INDEX                      0x01
#define CMD_VOE_INDEX                       0x02
#define CMD_VERIFY_INDEX					0x04

#define FW_CMD_3DNR                         0x03
#define FW_3DNR_RET                         0x33



#define PARSE_TM_CMD(cmd)                   ((cmd & 0x3FFF0000)>>16)
#define PARSE_TM_CMD_CH(cmd)                ((cmd & 0x0000FF00)>>8)
#define PARSE_TM_CMD_STATUS(cmd)            (cmd & 0xFF)
#define COMBINE_MESSAGE(cmd, ch, status)    ( ((cmd&0x3FFF) << 16) | ((ch&0xFF) << 8) | status)

#define WORK_PATTERN_1                      0x5A5A5A5A
#define WORK_PATTERN_2                      0x11223344




#define VOE_RECEIVE_CMD_BUSY    0x01
#define VOE_SEND_CMD_BUSY       0x02
#define VOE_CMD_TYPE_UNKNOWN    0x04
#define VOE_H264ISR_BUSY        0x08
#define VOE_STATUS_H264_FINISH	0x10


#define SHAREMEM_BASE		0x2000F800
#define SHAREMEM_SIZE		0x800
#define ERAC_BASE_ADDR		0x2000F000
#define ERAC_NUM			256
#define ERAC_DATA_OFFSET	0x400


#endif // _RTL8735B_VOE_CMD_H_
