/**************************************************************************//**
 * @file     nn_api.h
 * @brief    nn_api header
 * @version  V1.00
 * @date     2016-06-08
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

#ifndef _HAL_NN_ITP_RUN_H_
#define _HAL_NN_ITP_RUN_H_

//API for frame level setting
int nn_detect_interpreted(
	unsigned char        id,
	struct MODEL_INFO_S *model_info,
	unsigned char       *frame_in,
	struct cvRect_S     *ROIRect,
	float               *detect_result,
	int                 *detect_obj_num
);

int nn_model_run(
	unsigned char        id,
	struct MODEL_INFO_S *model_info,
	unsigned char       *frame_in,
	struct cvRect_S     *ROIRect,
	unsigned int        *tensor0out_fp,
	unsigned int        *tensor1out_fp
);


#endif  // end of "#define _HAL_NN_ITP_RUN_H_"
