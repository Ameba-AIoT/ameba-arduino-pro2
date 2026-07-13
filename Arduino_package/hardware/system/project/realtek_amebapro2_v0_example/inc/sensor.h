/**
 ******************************************************************************
 *This file contains sensor configurations for AmebaPro platform
 ******************************************************************************
*/


#ifndef __SENSOR_H
#define __SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

struct sensor_params_t {
	unsigned int sensor_width;
	unsigned int sensor_height;
	unsigned int sensor_fps;
};

//ARDUINO_SDK, DO NOT CHANGE LINE 20 TO 43
#ifdef ARDUINO_SDK

#define SENSOR_DUMMY        0x00
#define SENSOR_F37          0x01
//static const struct sensor_params_t sensor_params[] = {
//	[SENSOR_DUMMY]      = {1920, 1080, 30},
//	[SENSOR_F37]              = {1920, 1080, 30},
//};
#define SENSOR_MAX         2
static const unsigned char sen_id[SENSOR_MAX] = {
	SENSOR_DUMMY,
	SENSOR_F37,
};
#define USE_SENSOR      	SENSOR_F37
static const      char manual_iq[SENSOR_MAX][64] = {
	"iq",
	"iq_f37",
};
#define ENABLE_FCS      	1

#else

//                                        | Normal |  Fcs   |        |   ISP  |        |
//                                        | Driver | Driver |   IQ   |   HDR  | bi-I2C |
// RTK                                    ---------|--------|--------|--------|--------|
#define SENSOR_DUMMY            0x00  //  |   v    |   -    |   -    |   -    |    -   |	/* For dummy sensor, no support fast camera start */
#define SENSOR_FIXP_5M          0x01  //  |   v    |   -    |   -    |   -    |    -   |
#define SENSOR_FIXP_2K          0x02  //  |   v    |   -    |   -    |   -    |    -   |
#define SENSOR_YUV_2M_30        0x03  //  |   v    |   -    |   -    |   -    |    -   |
#define SENSOR_YUV_HD_60        0x04  //  |   v    |   -    |   -    |   -    |    -   |
/* CVSENS */
#define SENSOR_CV2003           0x05  //  |   v    |   -    |   -    |   -    |    -   |
/* IMAGEDESIGN */
#define SENSOR_MIS2008          0x06  //  |   v    |   -    |   v    |   -    |    -   |
/* NOVATEK */
#define SENSOR_NT99236          0x07  //  |   v    |   -    |   v    |   -    |    -   |
/* ST */
#define SENSOR_VD550G           0x08  //  |   v    |   -    |   v    |   -    |    -   |
/* SAMSUNG */
#define SENSOR_HM6S             0x09  //  |   v    |   -    |   v    |   -    |    -   |
#define SENSOR_HM6S_12M         0x0A  //  |   v    |   -    |   v    |   -    |    -   |
#define SENSOR_HM6S_108M        0x0B  //  |   v    |   -    |   v    |   -    |    -   |
/* SMARTSENS */
#define SENSOR_SC2333           0x10  //  |   v    |   v    |   v    |   -    |    v   |
#define SENSOR_SC2336           0x11  //  |   v    |   v    |   v    |   -    |    v   |
#define SENSOR_SC231H           0x12  //  |   v    |   -    |   v    |   -    |    v   |
#define SENSOR_SC2310           0x13  //  |   v    |   -    |   v    |   v    |    v   |
#define SENSOR_SC301            0x14  //  |   v    |   v    |   v    |   v    |    v   |
#define SENSOR_SC3336           0x15  //  |   v    |   -    |   v    |   -    |    v   |
#define SENSOR_SC400AI          0x16  //  |   v    |   -    |   v    |   -    |    v   |
#define SENSOR_SC450AI          0x17  //  |   v    |   -    |   -    |   -    |    v   |
#define SENSOR_SC485SL          0x18  //  |   v    |   -    |   -    |   -    |    v   |
#define SENSOR_SC5356           0x19  //  |   v    |   v    |   v    |   -    |    -   |
#define SENSOR_SC5356_2M        0x1A  //  |   v    |   v    |   v    |   -    |    -   |
/* GALAXYCORE */
#define SENSOR_GC1084           0x20  //  |   v    |   -    |   v    |   -    |    -   |
#define SENSOR_GC2053           0x21  //  |   v    |   v    |   v    |   -    |    v   |
#define SENSOR_GC2083           0x22  //  |   v    |   -    |   v    |   -    |    v   |
#define SENSOR_GC2093           0x23  //  |   v    |   -    |   v    |   v    |    v   |
#define SENSOR_GC3003           0x24  //  |   v    |   v    |   v    |   -    |    -   |
#define SENSOR_GC4023           0x25  //  |   v    |   v    |   v    |   -    |    v   |
#define SENSOR_GC4103           0x26  //  |   v    |   -    |   v    |   -    |    -   |
#define SENSOR_GC4653           0x27  //  |   v    |   v    |   v    |   -    |    v   |
#define SENSOR_GC4663           0x28  //  |   v    |   v    |   v    |   v    |    v   |
#define SENSOR_GC4693           0x29  //  |   v    |   v    |   -    |   -    |    v   |
#define SENSOR_GC5035           0x2A  //  |   v    |   v    |   v    |   -    |    -   |
#define SENSOR_GC05A2           0x2B  //  |   v    |   v    |   v    |   -    |    -   |
/* SONY */
#define SENSOR_IMX307           0x30  //  |   v    |   -    |   v    |   v    |    -   |
#define SENSOR_IMX327           0x31  //  |   v    |   -    |   v    |   v    |    -   |
#define SENSOR_IMX662           0x32  //  |   v    |   v    |   v    |   v    |    -   |
#define SENSOR_IMX471           0x33  //  |   v    |   v    |   v    |   -    |    -   |
#define SENSOR_IMX471_12M       0x34  //  |   v    |   -    |   v    |   -    |    -   |
#define SENSOR_IMX471_12M_SEQ   0x35  //  |   v    |   -    |   v    |   -    |    -   |
#define SENSOR_IMX681           0x36  //  |   v    |   v    |   v    |   -    |    -   |
#define SENSOR_IMX681_5M        0x37  //  |   v    |   v    |   v    |   -    |    -   |
#define SENSOR_IMX681_12M       0x38  //  |   v    |   -    |   v    |   -    |    -   |
#define SENSOR_IMX681_12M_SEQ   0x39  //  |   v    |   -    |   v    |   -    |    -   |
/* SOI */
#define SENSOR_F35              0x40  //  |   v    |   -    |   -    |   -    |    v   |
#define SENSOR_F37              0x41  //  |   v    |   v    |   v    |   -    |    v   |
#define SENSOR_F38              0x42  //  |   v    |   -    |   v    |   -    |    v   |
#define SENSOR_F51              0x43  //  |   v    |   v    |   v    |   v    |    -   |
#define SENSOR_F53              0x44  //  |   v    |   v    |   v    |   -    |    -   |
#define SENSOR_F55              0x45  //  |   v    |   -    |   v    |   v    |    v   |
#define SENSOR_F57              0x46  //  |   v    |   -    |   -    |   -    |    v   |
#define SENSOR_K05              0x47  //  |   v    |   -    |   v    |   -    |    -   |
#define SENSOR_K06A             0x48  //  |   v    |   -    |   -    |   -    |    -   |
#define SENSOR_K306P            0x49  //  |   v    |   v    |   v    |   v    |    v   |
#define SENSOR_K306P_HD         0x4A  //  |   v    |   v    |   v    |   -    |    v   |
#define SENSOR_K351             0x4B  //  |   v    |   v    |   v    |   v    |    -   |
/* OMNIVISION */
#define SENSOR_OV2735           0x50  //  |   v    |   v    |   v    |   -    |    -   |
#define SENSOR_OV5647           0x51  //  |   v    |   -    |   -    |   -    |    -   |
#define SENSOR_OV5693           0x52  //  |   v    |   -    |   -    |   -    |    -   |
#define SENSOR_OV9734           0x53  //  |   v    |   -    |   v    |   -    |    -   |
#define SENSOR_OV9734_SD        0x54  //  |   v    |   -    |   v    |   -    |    -   |
#define SENSOR_OS02H10          0x55  //  |   v    |   v    |   v    |   v    |    -   |
#define SENSOR_OS04A10          0x56  //  |   v    |   -    |   v    |   -    |    -   |
#define SENSOR_OV13B10          0x57  //  |   v    |   v    |   -    |   -    |    -   |
#define SENSOR_OV13B10_12M      0x58  //  |   v    |   -    |   -    |   -    |    -   |
#define SENSOR_OV13B10_12M_SEQ  0x59  //  |   v    |   -    |   -    |   -    |    -   |
#define SENSOR_OV12890          0x5A  //  |   v    |   v    |   -    |   -    |    -   |
#define SENSOR_OV12890_12M      0x5B  //  |   v    |   -    |   -    |   -    |    -   |
#define SENSOR_OV12890_12M_SEQ  0x5C  //  |   v    |   -    |   -    |   -    |    -   |
#define SENSOR_OV50A40          0x5D  //  |   v    |   -    |   v    |   -    |    -   |
#define SENSOR_OV50A40_50M      0x5E  //  |   v    |   -    |   v    |   -    |    -   |
/* PRIMESENSOR */
#define SENSOR_PS5258           0x60  //  |   v    |   -    |   v    |   -    |    -   |
#define SENSOR_PS5262           0x61  //  |   v    |   v    |   v    |   -    |    -   |
#define SENSOR_PS5268           0x62  //  |   v    |   v    |   v    |   -    |    -   |
#define SENSOR_PS5270           0x63  //  |   v    |   v    |   v    |   -    |    -   |
#define SENSOR_PS5270_HDR       0x64  //  |   v    |   v    |   v    |   -    |    -   |
#define SENSOR_PS5420           0x65  //  |   v    |   v    |   v    |   -    |    -   |
#define SENSOR_PS5420_HDR       0x66  //  |   v    |   v    |   v    |   -    |    -   |



static const struct sensor_params_t sensor_params[] = {
	/* RTK */
	[SENSOR_DUMMY]            = {1920, 1080, 30},
	[SENSOR_FIXP_5M]          = {2592, 1944, 15},
	[SENSOR_FIXP_2K]          = {2560, 1440, 24},
	[SENSOR_YUV_2M_30]        = {1600, 1300, 30},
	[SENSOR_YUV_HD_60]        = {1280,  720, 60},
	/* CVSENS */
	[SENSOR_CV2003]           = {1920, 1080, 30},
	/* IMAGEDESIGN */
	[SENSOR_MIS2008]          = {1920, 1080, 30},
	/* NOVATEK */
	[SENSOR_NT99236]          = {1920, 1080, 30},
	/* ST */
	[SENSOR_VD550G]           = { 640,  600, 60},
	/* SAMSUNG */
	[SENSOR_HM6S]             = {2000, 1500, 30},
	[SENSOR_HM6S_12M]         = {2000, 1500, 30},
	[SENSOR_HM6S_108M]        = {2000, 1500, 30},
	/* SMARTSENS */
	[SENSOR_SC2333]           = {1920, 1080, 30},
	[SENSOR_SC2336]           = {1920, 1080, 30},
	[SENSOR_SC231H]           = {1920, 1080, 30},
	[SENSOR_SC2310]           = {1920, 1080, 30},
	[SENSOR_SC301]            = {2048, 1536, 20},
	[SENSOR_SC3336]           = {2304, 1296, 30},
	[SENSOR_SC400AI]          = {2560, 1440, 24},
	[SENSOR_SC450AI]          = {2560, 1440, 24},
	[SENSOR_SC485SL]          = {2560, 1440, 24},
	[SENSOR_SC5356]           = {2592, 1944, 15},
	[SENSOR_SC5356_2M]        = {1088, 1944, 30},
	/* GALAXYCORE */
	[SENSOR_GC1084]           = {1280,  720, 30},
	[SENSOR_GC2053]           = {1920, 1080, 30},
	[SENSOR_GC2083]           = {1920, 1080, 30},
	[SENSOR_GC2093]           = {1920, 1080, 30},
	[SENSOR_GC3003]           = {2304, 1296, 30},
	[SENSOR_GC4023]           = {2560, 1440, 24},
	[SENSOR_GC4103]           = {2000, 2000, 25},
	[SENSOR_GC4653]           = {2560, 1440, 24},
	[SENSOR_GC4663]           = {2560, 1440, 24},  //HDR Mode fps=20
	[SENSOR_GC4693]           = {2560, 1440, 24},
	[SENSOR_GC5035]           = {2592, 1944, 15},
	[SENSOR_GC05A2]           = {2592, 1944, 15},
	/* SONY */
	[SENSOR_IMX307]           = {1920, 1080, 30},
	[SENSOR_IMX327]           = {1920, 1080, 24},
	[SENSOR_IMX662]           = {1920, 1080, 30},
	[SENSOR_IMX471]           = {2304, 1728, 24},
	[SENSOR_IMX471_12M]       = {4032, 3024,  5},
	[SENSOR_IMX471_12M_SEQ]   = {2032, 3024,  5}, //width = 2016 + 16(overlap)
	[SENSOR_IMX681]           = {2000, 1500, 30},
	[SENSOR_IMX681_5M]        = {2592, 1944,  4},
	[SENSOR_IMX681_12M]       = {4016, 3012,  4},
	[SENSOR_IMX681_12M_SEQ]   = {2128, 1604,  4}, //width = 2008 + 120(overlap) //height = 1506 + 98(overlap)
	/* SOI */
	[SENSOR_F35]              = {1920, 1080, 30},
	[SENSOR_F37]              = {1920, 1080, 30},
	[SENSOR_F38]              = {1920, 1080, 30},
	[SENSOR_F51]              = {1536, 1536, 20},
	[SENSOR_F53]              = {1920, 1080, 30},
	[SENSOR_F55]              = {1920, 1080, 30},
	[SENSOR_F57]              = {1920, 1080, 30},
	[SENSOR_K05]              = {2592, 1944, 15},
	[SENSOR_K06A]             = {2560, 1440, 24},
	[SENSOR_K306P]            = {2560, 1440, 24},  //HDR Mode fps=20
	[SENSOR_K306P_HD]         = {1284,  724, 20},
	[SENSOR_K351]             = {2000, 2000, 20},
	/* OMNIVISION */
	[SENSOR_OV2735]           = {1920, 1080, 30},
	[SENSOR_OV5647]           = {2592, 1944, 15},
	[SENSOR_OV5693]           = {2592, 1944, 15},
	[SENSOR_OV9734]           = {1280,  720, 30},
	[SENSOR_OV9734_SD]        = { 640,  360, 60},
	[SENSOR_OS02H10]          = {1920, 1080, 30},
	[SENSOR_OS04A10]          = {2560, 1440, 24},
	[SENSOR_OV13B10]  	      = {2096, 1560, 30},
	[SENSOR_OV13B10_12M]      = {4032, 3024, 10},
	[SENSOR_OV13B10_12M_SEQ]  = {2112, 1616,  5}, //width = 2016 + 96(overlap) //height = 1512 + 104(overlap)
	[SENSOR_OV12890]  	      = {2048, 1536, 30},
	[SENSOR_OV12890_12M]      = {4032, 3024,  8},
	[SENSOR_OV12890_12M_SEQ]  = {2112, 1616,  5}, //width = 2016 + 96(overlap) //height = 1512 + 104(overlap)
	[SENSOR_OV50A40]          = {2048, 1536, 30},
	[SENSOR_OV50A40_50M]      = {2048, 1536, 30},
	/* PRIMESENSOR */
	[SENSOR_PS5258]           = {1920, 1080, 30},
	[SENSOR_PS5262]           = {1920, 1080, 30},
	[SENSOR_PS5268]           = {1920, 1080, 30},
	[SENSOR_PS5270]           = {1536, 1536, 30},
	[SENSOR_PS5270_HDR]       = {1536, 1536, 25},
	[SENSOR_PS5420]           = {1952, 1944, 24},
	[SENSOR_PS5420_HDR]       = {1952, 1944, 24},
};

#define SENSOR_MAX         5

static const unsigned char sen_id[SENSOR_MAX] = {
	SENSOR_DUMMY,
	SENSOR_GC2053,
	SENSOR_GC4653,
	SENSOR_GC4023,
	SENSOR_SC2333
};

#define USE_SENSOR      	SENSOR_GC2053

static const      char manual_iq[SENSOR_MAX][64] = {
	"iq",
	"iq_gc2053",
	"iq_gc4653",
	"iq_gc4023",
	"iq_sc2333",
};
#endif

#define MANUAL_SENSOR_IQ	0xFF

#ifndef ARDUINO_SDK
#define ENABLE_FCS      	0
#endif

#define MULTI_DISABLE       0x00
#define MULTI_ENABLE        0x01

#define MULTI_SENSOR  		MULTI_DISABLE
#define NONE_FCS_MODE       0
#define FW1_IQ_ADDR        0xF20000
#define FW2_IQ_ADDR        0xF60000
#define FW_IQ_SIZE         256*1024
#define FW_CAL_IQ_SIZE     16*1024
#define FW_SENSOR_SIZE     16*1024
#define FW_VOE_SIZE        600*1024
#define VIDEO_MPU_VOE_HEAP  0
#define SENSOR_SINGLE_DEFAULT_SETUP     0x00
#define SENSOR_MULTI_DEFAULT_SETUP      0X01
#define SENSOR_MULTI_SAVE_VALUE         0X02
#define SENSOR_MULTI_SETUP_PROCEDURE	0X03
#ifdef __cplusplus
}
#endif


#endif /* __AMEBAPRO_SENSOR_EVAL_H */
