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

#ifndef _HAL_NN_H_
#define _HAL_NN_H_

#include "cmsis.h"

//Error code
#define NN_OK               (0)
#define NN_NG               (-1)
#define NN_NG_PARAM         (-2)

#define CVMIN(a,b) ((a < b) ? a : b)

typedef int NN_status_t;

typedef struct {
	unsigned int width;
	unsigned int height;
	unsigned char *data;
} cvImage;

typedef struct cvRect_S {
	int xmin;
	int ymin;
	int xmax;
	int ymax;
} cvRect_S;

typedef struct MODEL_INFO_S {
	unsigned int  nnreg_CmdBufferAHBControl;
	unsigned int  nnreg_AQCmdBufferAddr;
	unsigned int  tensor0Out_addr;
	unsigned int  tensor1Out_addr;
	unsigned int  tensor0in_addr;
	unsigned int  model_size;
	unsigned int  xRatio_addr;
	unsigned int  yRatio_addr;
	unsigned int  xOffset_addr;
	unsigned int  yOffset_addr;
	unsigned int  xRatio_addr1;
	unsigned int  yRatio_addr1;
	unsigned int  xOffset_addr1;
	unsigned int  yOffset_addr1;
	unsigned int  xRatio_addr2;
	unsigned int  yRatio_addr2;
	unsigned int  xOffset_addr2;
	unsigned int  yOffset_addr2;
	unsigned int  tensor0in_addrloc;
	unsigned int  tensor0in_addrloc_r;
	unsigned int  tensor0in_addrloc_g;
	unsigned int  tensor0in_addrloc_b;
	unsigned int  img_width;
	unsigned int  img_height;
	unsigned int  nn_width;
	unsigned int  nn_height;
} MODEL_INFO_S;


void nn_rxi300_regulator(float rate_multipier);

void nn_axi_outstandingRead(unsigned int numOutstandingRead);

void nn_hw_version(void);
void nn_clkcontrol(unsigned int freqscale);

//API for model setting to H/W
void nn_set_mode(void);

//API for detection -> Interpreted models
int nn_detect_interpreted(
	unsigned char        id,
	struct MODEL_INFO_S *model_info,
	unsigned char       *frame_in,
	struct cvRect_S     *ROIRect,
	float               *detect_result,
	int                 *detect_obj_num
);

//API used in nn_detect
void nn_process_kickstart(struct MODEL_INFO_S *model_info);
void nn_process_intrend(void);
void nn_process_pollend(void);
void nn_process_waitend(void (*nn_process_detectend)(void));


#endif  // end of "#define _HAL_NN_H_"
