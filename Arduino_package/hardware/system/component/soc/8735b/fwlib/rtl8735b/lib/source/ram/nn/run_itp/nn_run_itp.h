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
 * Copyright(c) 2007 - 2023 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
