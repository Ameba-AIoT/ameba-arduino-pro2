/**************************************************************************//**
 * @file     hal_video_common.h
 * @brief    The HAL API implementation for the Video device.
 * @version  V1.00
 * @date     2021-01-14
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2021 Realtek Corporation. All rights reserved.
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


#ifndef _HAL_VIDEO_COMMON_H_
#define _HAL_VIDEO_COMMON_H_

#define MAX_BPS_ADJUST			20
#define MAX_SCENE_CHANGE		20

#define MAX_PATH				64
#define DEFAULT					-255

#define TYPE_HEVC				0
#define TYPE_H264				1
#define TYPE_JPEG				2
#define TYPE_NV12				3
#define TYPE_RGB				4
#define TYPE_NV16				5


#define CODEC_HEVC				(ENABLE<<TYPE_HEVC)	// 0 0x01
#define CODEC_H264				(ENABLE<<TYPE_H264)	// 1 0x02
#define CODEC_JPEG				(ENABLE<<TYPE_JPEG)	// 2 0x04
#define CODEC_NV12				(ENABLE<<TYPE_NV12)	// 3 0x08
#define CODEC_RGB				(ENABLE<<TYPE_RGB)	// 4 0x10
#define CODEC_NV16				(ENABLE<<TYPE_NV16)	// 5 0x20

// Modify from hevcapi.h

#define IS_HEVC(a)  (a==VCENC_VIDEO_CODEC_HEVC)
#define IS_H264(a)  (a==VCENC_VIDEO_CODEC_H264)

#define MAX(a, b) ((a) > (b) ?  (a) : (b))
#define CLIP3(x, y, z)  ((z) < (x) ? (x) : ((z) > (y) ? (y) : (z)))


typedef const void *VCEncInst;

/* Function return values */
typedef enum {
	VCENC_OK = 0,
	VCENC_FRAME_READY = 1,
	VCENC_FRAME_ENQUEUE = 2,

	VCENC_ERROR = -1,
	VCENC_NULL_ARGUMENT = -2,
	VCENC_INVALID_ARGUMENT = -3,
	VCENC_MEMORY_ERROR = -4,
	VCENC_EWL_ERROR = -5,
	VCENC_EWL_MEMORY_ERROR = -6,
	VCENC_INVALID_STATUS = -7,
	VCENC_OUTPUT_BUFFER_OVERFLOW = -8,
	VCENC_HW_BUS_ERROR = -9,
	VCENC_HW_DATA_ERROR = -10,
	VCENC_HW_TIMEOUT = -11,
	VCENC_HW_RESERVED = -12,
	VCENC_SYSTEM_ERROR = -13,
	VCENC_INSTANCE_ERROR = -14,
	VCENC_HRD_ERROR = -15,
	VCENC_HW_RESET = -16,
	VCENC_OUTPUT_QUEUE_OVERFLOW = -17
} VCEncRet;

/* Video Codec Format */
typedef enum {
	VCENC_VIDEO_CODEC_HEVC = 0,
	VCENC_VIDEO_CODEC_H264 = 1,
	VCENC_VIDEO_CODEC_JPEG = 2,
	VCENC_VIDEO_CODEC_NV12 = 3,
	VCENC_VIDEO_CODEC_RGB = 4,
	VCENC_VIDEO_CODEC_NV16 = 5

} VCEncVideoCodecFormat;

/* Stream type for initialization */
typedef enum {
	VCENC_BYTE_STREAM = 0,    /* NAL unit starts with hex bytes '00 00 00 01' */
	VCENC_NAL_UNIT_STREAM = 1 /* Plain NAL units without startcode */
} VCEncStreamType;

/* Level for initialization */
typedef enum {
	VCENC_HEVC_LEVEL_1 = 30,
	VCENC_HEVC_LEVEL_2 = 60,
	VCENC_HEVC_LEVEL_2_1 = 63,
	VCENC_HEVC_LEVEL_3 = 90,
	VCENC_HEVC_LEVEL_3_1 = 93,
	VCENC_HEVC_LEVEL_4 = 120,
	VCENC_HEVC_LEVEL_4_1 = 123,
	VCENC_HEVC_LEVEL_5 = 150,
	VCENC_HEVC_LEVEL_5_1 = 153,
	VCENC_HEVC_LEVEL_5_2 = 156,
	VCENC_HEVC_LEVEL_6 = 180,
	VCENC_HEVC_LEVEL_6_1 = 183,
	VCENC_HEVC_LEVEL_6_2 = 186,

	/* H264 Defination*/
	VCENC_H264_LEVEL_1 = 10,
	VCENC_H264_LEVEL_1_b = 99,
	VCENC_H264_LEVEL_1_1 = 11,
	VCENC_H264_LEVEL_1_2 = 12,
	VCENC_H264_LEVEL_1_3 = 13,
	VCENC_H264_LEVEL_2 = 20,
	VCENC_H264_LEVEL_2_1 = 21,
	VCENC_H264_LEVEL_2_2 = 22,
	VCENC_H264_LEVEL_3 = 30,
	VCENC_H264_LEVEL_3_1 = 31,
	VCENC_H264_LEVEL_3_2 = 32,
	VCENC_H264_LEVEL_4 = 40,
	VCENC_H264_LEVEL_4_1 = 41,
	VCENC_H264_LEVEL_4_2 = 42,
	VCENC_H264_LEVEL_5 = 50,
	VCENC_H264_LEVEL_5_1 = 51,
	VCENC_H264_LEVEL_5_2 = 52,
	VCENC_H264_LEVEL_6 = 60,
	VCENC_H264_LEVEL_6_1 = 61,
	VCENC_H264_LEVEL_6_2 = 62
} VCEncLevel;

/* Profile for initialization */
typedef enum {
	VCENC_HEVC_MAIN_PROFILE = 0,
	VCENC_HEVC_MAIN_STILL_PICTURE_PROFILE = 1,
	VCENC_HEVC_MAIN_10_PROFILE = 2,
	VCENC_HEVC_MAINREXT = 3,
	/* H264 Defination*/
	VCENC_H264_BASE_PROFILE = 9,
	VCENC_H264_MAIN_PROFILE = 10,
	VCENC_H264_HIGH_PROFILE = 11,
	VCENC_H264_HIGH_10_PROFILE = 12,

} VCEncProfile;

/* Tier for initialization */
typedef enum {
	VCENC_HEVC_MAIN_TIER = 0,
	VCENC_HEVC_HIGH_TIER = 1,
} VCEncTier;

/* Picture YUV type for initialization */
typedef enum {
	VCENC_YUV420_PLANAR = 0,                  /* YYYY... UUUU... VVVV...  */
	VCENC_YUV420_SEMIPLANAR = 1,              /* YYYY... UVUVUV...        */
	VCENC_YUV420_SEMIPLANAR_VU = 2,           /* YYYY... VUVUVU...        */
	VCENC_YUV422_INTERLEAVED_YUYV = 3,        /* YUYVYUYV...              */
	VCENC_YUV422_INTERLEAVED_UYVY = 4,        /* UYVYUYVY...              */
	VCENC_RGB565 = 5,                         /* 16-bit RGB 16bpp         */
	VCENC_BGR565 = 6,                         /* 16-bit RGB 16bpp         */
	VCENC_RGB555 = 7,                         /* 15-bit RGB 16bpp         */
	VCENC_BGR555 = 8,                         /* 15-bit RGB 16bpp         */
	VCENC_RGB444 = 9,                         /* 12-bit RGB 16bpp         */
	VCENC_BGR444 = 10,                         /* 12-bit RGB 16bpp         */
	VCENC_RGB888 = 11,                         /* 24-bit RGB 32bpp         */
	VCENC_BGR888 = 12,                         /* 24-bit RGB 32bpp         */

	VCENC_FORMAT_MAX

} VCEncPictureType;

/* Picture rotation for pre-processing */
typedef enum {
	VCENC_ROTATE_0 = 0,
	VCENC_ROTATE_90R = 1, /* Rotate 90 degrees clockwise */
	VCENC_ROTATE_90L = 2,  /* Rotate 90 degrees counter-clockwise */
	VCENC_ROTATE_180R = 3  /* Rotate 180 degrees clockwise */
} VCEncPictureRotation;

typedef enum {
	VCENC_MIRROR_NO = 0, /* no mirror */
	VCENC_MIRROR_YES = 1 /* mirror */
} VCEncPictureMirror;

/* Picture color space conversion (RGB input) for pre-processing */
typedef enum {
	VCENC_RGBTOYUV_BT601 = 0, /* Color conversion of limited range[16,235] according to BT.601 */
	VCENC_RGBTOYUV_BT709 = 1, /* Color conversion of limited range[16,235] according to BT.709 */
	VCENC_RGBTOYUV_USER_DEFINED = 2,   /* User defined color conversion */
	VCENC_RGBTOYUV_BT2020 = 3, /* Color conversion according to BT.2020 */
	VCENC_RGBTOYUV_BT601_FULL_RANGE = 4, /* Color conversion of full range[0,255] according to BT.601*/
	VCENC_RGBTOYUV_BT601_LIMITED_RANGE = 5, /* Color conversion of limited range[0,219] according to BT.601*/
	VCENC_RGBTOYUV_BT709_FULL_RANGE = 6 /* Color conversion of full range[0,255] according to BT.709*/
} VCEncColorConversionType;
/* Picture type for encoding */
typedef enum {
	VCENC_RESERVED = -255,
	VCENC_INTRA_FRAME = 0,
	VCENC_PREDICTED_FRAME = 1,
//	VCENC_PREDICTED_FRAME_META = 2,		// ToDo
	VCENC_BIDIR_PREDICTED_FRAME = 2,
	VCENC_NOTCODED_FRAME  /* Used just as a return value */
} VCEncPictureCodingType;


typedef enum {
	VCENC_CHROMA_IDC_400 = 0,
	VCENC_CHROMA_IDC_420 = 1,
	VCENC_CHROMA_IDC_422 = 2,
} VCEncChromaIdcType;

/* Structure for roi control */

typedef struct {
	i32 roiAreaEnable;
	i32 roiAreaTop;
	i32 roiAreaLeft;
	i32 roiAreaBottom;
	i32 roiAreaRight;
	i32 roiDeltaQp;
	i32 roiQp;
} roi_ctrl_s;

/* Structure for command line options */
typedef struct {

	i32 CodecType;

	i32 outputRateNumer;      /* Output frame rate numerator */
	i32 outputRateDenom;      /* Output frame rate denominator */
	i32 inputRateNumer;      /* Input frame rate numerator */
	i32 inputRateDenom;      /* Input frame rate denominator */
	i32 firstPic;
	i32 lastPic;

	i32 width;
	i32 height;
	i32 lumWidthSrc;
	i32 lumHeightSrc;

	i32 inputFormat;
	VCEncVideoCodecFormat outputFormat;     /* Video Codec Format: HEVC/H264/JPEG/YUV */
	i32 EncMode;                            /* Encode output mode 0: pause 1: one-shot 2: continue */
	i32 JpegMode;                           /* JPEG output mode 0: pause 1: one-shot 2: continue */
	i32 YuvMode;                            /* YUV output mode 0: pause 1: one-shot 2: continue */

	i32 picture_cnt;
	i32 byteStream;
	i32 videoStab;

	i32 max_cu_size;    /* Max coding unit size in pixels */
	i32 min_cu_size;    /* Min coding unit size in pixels */
	i32 max_tr_size;    /* Max transform size in pixels */
	i32 min_tr_size;    /* Min transform size in pixels */
	i32 tr_depth_intra;   /* Max transform hierarchy depth */
	i32 tr_depth_inter;   /* Max transform hierarchy depth */

	i32 min_qp_size;

	i32 enableCabac;      /* [0,1] H.264 entropy coding mode, 0 for CAVLC, 1 for CABAC */
	i32 cabacInitFlag;

	// intra setup
	u32 strong_intra_smoothing_enabled_flag;

	i32 cirStart;
	i32 cirInterval;

	i32 intraAreaEnable;
	i32 intraAreaTop;
	i32 intraAreaLeft;
	i32 intraAreaBottom;
	i32 intraAreaRight;

	i32 pcm_loop_filter_disabled_flag;

	i32 ipcm1AreaTop;
	i32 ipcm1AreaLeft;
	i32 ipcm1AreaBottom;
	i32 ipcm1AreaRight;

	i32 ipcm2AreaTop;
	i32 ipcm2AreaLeft;
	i32 ipcm2AreaBottom;
	i32 ipcm2AreaRight;
	i32 ipcmMapEnable;
	char *ipcmMapFile;

	char *skipMapFile;
	i32 skipMapEnable;
	i32 skipMapBlockUnit;

	roi_ctrl_s roi_ctrl[8];

	/* Rate control parameters */
	i32 hrdConformance;
	i32 cpbSize;
	i32 intraPicRate;   /* IDR interval */

	i32 vbr; /* Variable Bit Rate Control by qpMin */
	i32 qpHdr;
	i32 qpMin;
	i32 qpMax;
	i32 qpMinI;
	i32 qpMaxI;
	i32 bitPerSecond;
	i32 crf; /*CRF constant*/

	i32 bitVarRangeI;
	i32 bitVarRangeP;

	u32 u32StaticSceneIbitPercent;

	i32 tolMovingBitRate;/*tolerance of max Moving bit rate */
	i32 monitorFrames;/*monitor frame length for moving bit rate*/
	i32 picRc;
	i32 ctbRc;
	i32 blockRCSize;
	u32 rcQpDeltaRange;
	u32 rcBaseMBComplexity;
	i32 picSkip;
	i32 picQpDeltaMin;
	i32 picQpDeltaMax;
	i32 ctbRcRowQpStep;

	float tolCtbRcInter;
	float tolCtbRcIntra;

	i32 bitrateWindow;
	i32 intraQpDelta;
	i32 fixedIntraQp;

	i32 disableDeblocking;

	i32 enableSao;


	i32 tc_Offset;
	i32 beta_Offset;

	i32 chromaQpOffset;

	i32 profile;              /*main profile or main still picture profile*/
	i32 tier;               /*main tier or high tier*/
	i32 level;              /*main profile level*/

	i32 bpsAdjustFrame[MAX_BPS_ADJUST];
	i32 bpsAdjustBitrate[MAX_BPS_ADJUST];
	i32 smoothPsnrInGOP;

	i32 sliceSize;

//	i32 testId;

	i32 rotation;
//	i32 mirror;
	i32 horOffsetSrc;
	i32 verOffsetSrc;
	i32 colorConversion;
	i32 scaledWidth;
	i32 scaledHeight;
	i32 scaledOutputFormat;

	i32 enableDeblockOverride;
	i32 deblockOverride;

	i32 enableScalingList;

	u32 compressor;

	i32 interlacedFrame;
	i32 fieldOrder;
	i32 videoRange;
	i32 sei;

	u32 userData;
	u32 gopSize;
	char *gopCfg;
	u32 gopLowdelay;
	i32 outReconFrame;
	u32 longTermGap;
	u32 longTermGapOffset;
	u32 ltrInterval;
	i32 longTermQpDelta;

	i32 gdrDuration;
	u32 roiMapDeltaQpBlockUnit;
	u32 roiMapDeltaQpEnable;
	char *roiMapDeltaQpFile;
	char *roiMapDeltaQpBinFile;
	char *roiMapInfoBinFile;
	char *RoimapCuCtrlInfoBinFile;
	char *RoimapCuCtrlIndexBinFile;
	u32 RoiCuCtrlVer;
	u32 RoiQpDeltaVer;
	i32 outBufSizeMax;



	i32 bitDepthLuma;
	i32 bitDepthChroma;

	u32 enableOutputCuInfo;

	u32 rdoLevel;
	u32 hashtype;
	u32 verbose;

	/* constant chroma control */
	i32 constChromaEn;
	u32 constCb;
	u32 constCr;

	i32 sceneChange[MAX_SCENE_CHANGE];

	/* for tile*/
	i32 tiles_enabled_flag;
	i32 num_tile_columns;
	i32 num_tile_rows;
	i32 loop_filter_across_tiles_enabled_flag;

	/*for skip frame encoding ctr*/
	i32 skip_frame_enabled_flag;
	i32 skip_frame_poc;

	/*stride*/
	u32 exp_of_input_alignment;
	u32 exp_of_ref_alignment;
	u32 exp_of_ref_ch_alignment;

	u32 RpsInSliceHeader;
	u32 vui_timing_info_enable;

	u32 picOrderCntType;
	u32 log2MaxPicOrderCntLsb;
	u32 log2MaxFrameNum;

	char *halfDsInput;

	u32 dumpRegister;
	u32 rasterscan;

	u32 lookaheadDepth;

	u32 cuInfoVersion;
	u32 enableRdoQuant;

	u32 AXIAlignment;

	u32 ivf;

	u32 MEVertRange;

	VCEncChromaIdcType codedChromaIdc;
	u32 PsyFactor;

	u32 aq_mode;
	double aq_strength;

	u32 preset;
	u32 writeReconToDDR;

	/* JPEG */
	i32 restartInterval;
	i32 partialCoding;
	i32 codingMode;
	i32 markerType;
	i32 qLevel;
	i32 unitsType;
	i32 xdensity;
	i32 ydensity;
	// Non support thumbnail

	i32 rcMode;
	u32 qpmin;
	u32 qpmax;
	i32 fixedQP;

	/* AmebaPro VOE/buffer control */
	i32 osd;
	//	i32 obj;

	u32 lumaSize;
	i32	enc_cnt;
	i32	slice_cnt;

	int ch;
	int status;

	int out_buf_size;
	int out_rsvd_size;
	int isp_buf_num;

	int jpg_buf_size;
	int jpg_rsvd_size;

	volatile int voe_dbg;

	int fcs;			// 1: fcs flow ROM load sensor, 0: normal flow need init. sensor

	u32 roix;
	u32 roiy;
	u32 roiw;
	u32 roih;
	u32 set_AE_init_flag;
	u32 init_gain;      	//unit:  256
	u32 init_exposure; 	//unit:  us

	u32 set_AWB_init_flag;
	u32 init_r_gain;      	//unit:  256
	u32 init_b_gain;      	//unit:  256

	u32 sensor_rst_pin;
	u32 sensor_pwdn_pin;
	u32 sensor_pwr_pin;

	u32 i2c_id;

	u32 isp_clock_level;
	u32 mipi_clock_level;
	u32 drop_frame_num;

	u32 direct_i2c_mode;  // 0-disable,  1-enable,  2-enable, remove the extra round for init AE

	u32 init_daynight_mode;  // 0-day, 1-night

	u32 gray_mode;

	u32 all_init_iq_set_flag;

	u32 fast_osd_en;
	u32 *osd_buf;

	u32 isp_meta_out;

	u32 fast_mask_en;

	u32 rsvd[54];

} __attribute__((aligned(32))) commandLine_s;

/** @} */ /* End of group hal_enc */
#endif  // end of "#define _HAL_VIDEO_COMMON_H_"

