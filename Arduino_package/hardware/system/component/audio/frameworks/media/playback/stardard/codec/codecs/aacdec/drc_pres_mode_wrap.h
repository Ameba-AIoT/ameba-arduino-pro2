/*
 * Copyright (c) 2021 Realtek, LLC.
 * All rights reserved.
 *
 * Licensed under the Realtek License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from Realtek
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once
#include "aacdecoder_lib.h"

typedef enum {
	DRC_PRES_MODE_WRAP_DESIRED_TARGET         = 0x0000,
	DRC_PRES_MODE_WRAP_DESIRED_ATT_FACTOR     = 0x0001,
	DRC_PRES_MODE_WRAP_DESIRED_BOOST_FACTOR   = 0x0002,
	DRC_PRES_MODE_WRAP_DESIRED_HEAVY          = 0x0003,
	DRC_PRES_MODE_WRAP_ENCODER_TARGET         = 0x0004
} DRC_PRES_MODE_WRAP_PARAM;


class CDrcPresModeWrapper
{
public:
	CDrcPresModeWrapper();
	~CDrcPresModeWrapper();
	void SetDecoderHandle(const HANDLE_AACDECODER handle);
	void SetParam(const DRC_PRES_MODE_WRAP_PARAM param, const int value);
	void SubmitStreamData(CStreamInfo *);
	void Update();

protected:
	HANDLE_AACDECODER handle_decoder_;
	int des_target_;
	int des_att_factor_;
	int des_boost_factor_;
	int des_heavy_;

	int encoder_target_;

	int last_target_;
	int last_att_factor_;
	int last_boost_factor_;
	int last_heavy_;

	SCHAR stream_prl_;
	SCHAR stream_drc_pres_mode_;
	INT stream_nr_aac_chan_;
	INT stream_nr_out_chan_;

	bool is_downmix_;
	bool is_mono_downmix_;
	bool is_stereo_downmix_;

	bool data_update_;
};
