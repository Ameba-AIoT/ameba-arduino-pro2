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
static const struct sensor_params_t sensor_params[] = {
	[SENSOR_DUMMY]      = {1920, 1080, 30},
	[SENSOR_F37]        = {1920, 1080, 30},
};
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

//                                      | Normal |  Fcs   |        |   ISP  |
//                                      | Driver | Driver |   IQ   |   HDR  |
//                                      ---------|--------|--------|--------|
#define SENSOR_DUMMY          0x00  //  |   v    |   v    |   -    |   -    |  /* For dummy sensor, no support fast camera start */
#define SENSOR_SC2336         0x01  //  |   v    |   v    |   v    |   -    |
#define SENSOR_GC2053         0x02  //  |   v    |   v    |   v    |   -    |
#define SENSOR_GC4653         0x03  //  |   v    |   v    |   v    |   -    |
#define SENSOR_F37            0x04  //  |   v    |   v    |   v    |   -    |
#define SENSOR_IMX327         0x05  //  |   v    |   -    |   v    |   v    |  
#define SENSOR_F51            0x06  //  |   v    |   v    |   v    |   v    |  
#define SENSOR_PS5258         0x07  //  |   v    |   -    |   v    |   -    |  /* don't support multi sensor function */
#define SENSOR_SC301          0x08  //  |   v    |   v    |   v    |   v    |  
#define SENSOR_IMX307         0x09  //  |   v    |   -    |   v    |   -    |
#define SENSOR_SC2333         0x0A  //  |   v    |   v    |   v    |   -    |
#define SENSOR_GC4023         0x0B  //  |   v    |   v    |   v    |   -    |
#define SENSOR_PS5420         0x0C  //  |   v    |   v    |   v    |   -    |
#define SENSOR_PS5270         0x0D  //  |   v    |   v    |   v    |   -    |
#define SENSOR_GC5035         0x0E  //  |   v    |   v    |   v    |   -    |
#define SENSOR_PS5268         0x0F  //  |   v    |   -    |   v    |   -    |
#define SENSOR_SC2310         0x10  //  |   v    |   -    |   v    |   -    |
#define SENSOR_PS5420_HDR     0x11  //  |   v    |   v    |   v    |   -    | 
#define SENSOR_PS5270_HDR     0x12  //  |   v    |   v    |   v    |   -    | 
#define SENSOR_F53            0x13  //  |   v    |   v    |   v    |   -    |
#define SENSOR_F55            0x14  //  |   v    |   -    |   v    |   v    |
#define SENSOR_GC4663         0x15  //  |   v    |   v    |   v    |   v    |
//#define SENSOR_GC4663_HDR   0x16  //  |   -    |   -    |   -    |   -    |  /* use SENSOR_GC4663 with init_hdr_mode = 1 */
#define SENSOR_K351           0x17  //  |   v    |   v    |   v    |   v    |
//#define SENSOR_K351_HDR     0x18  //  |   -    |   -    |   -    |   -    |  /* use SENSOR_K351   with init_hdr_mode = 1 */
#define SENSOR_OV50A40        0x19  //  |   v    |   -    |   v    |   -    |  /* Full FOV with (1/4)*(1/4) sub-sample */
//#define SENSOR_SC301_HDR    0x1A  //  |   -    |   -    |   -    |   -    |  /* use SENSOR_SC301  with init_hdr_mode = 1 */
//#define SENSOR_F51_HDR      0x1B  //  |   -    |   -    |   -    |   -    |  /* use SENSOR_F51    with init_hdr_mode = 1 */
#define SENSOR_OS04A10        0x1C  //  |   v    |   -    |   v    |   -    |
//#define SENSOR_F55_HDR      0x1D  //  |   -    |   -    |   -    |   -    |  /* use SENSOR_F55    with init_hdr_mode = 1 */
#define SENSOR_GC1084         0x1E  //  |   v    |   -    |   v    |   -    |
#define SENSOR_SC5356         0x1F  //  |   v    |   v    |   v    |   -    |
#define SENSOR_F38            0x20  //  |   v    |   -    |   v    |   -    |
#define SENSOR_PS5262         0x21  //  |   v    |   -    |   v    |   -    |
#define SENSOR_K05            0x22  //  |   v    |   -    |   v    |   -    |
#define SENSOR_MIS2008        0x23  //  |   v    |   -    |   v    |   -    |
#define SENSOR_NT99236        0x24  //  |   v    |   -    |   v    |   -    |
#define SENSOR_VD550G         0x25  //  |   v    |   -    |   v    |   -    |
#define SENSOR_GC3003         0x26  //  |   v    |   v    |   v    |   -    |
#define SENSOR_IMX662         0x27  //  |   v    |   v    |   v    |   v    |
#define SENSOR_GC2083         0x28  //  |   v    |   -    |   v    |   -    |
#define SENSOR_OV2735         0x29  //  |   v    |   v    |   v    |   -    |
#define SENSOR_SC400AI        0x2A  //  |   v    |   -    |   v    |   -    |
#define SENSOR_OV50A40_CROP   0x2B  //  |   v    |   -    |   v    |   -    | /* Crop FOV with 1/16 window size */
#define SENSOR_OV9734         0x2C  //  |   v    |   -    |   v    |   -    |
#define SENSOR_CV2003         0x2D  //  |   v    |   -    |   -    |   -    |
#define SENSOR_GC2093         0x2E  //  |   v    |   -    |   -    |   -    |
#define SENSOR_F35            0x2F  //  |   v    |   -    |   -    |   -    |
#define SENSOR_OV5693         0x30  //  |   v    |   -    |   -    |   -    |
#define SENSOR_SC3336         0x31  //  |   v    |   -    |   v    |   -    |
#define SENSOR_K06A           0x32  //  |   v    |   -    |   -    |   -    |
#define SENSOR_K306P          0x33  //  |   v    |   -    |   -    |   -    |
#define SENSOR_OV9734_SD      0x34  //  |   v    |   -    |   v    |   -    |
#define SENSOR_IMX471         0x35  //  |   v    |   v    |   v    |   -    |
#define SENSOR_IMX471_12M     0x36  //  |   v    |   -    |   v    |   -    |
#define SENSOR_IMX471_12M_SEQ 0x37  //  |   v    |   -    |   v    |   -    |
#define SENSOR_IMX681         0x38  //  |   v    |   v    |   v    |   -    |
#define SENSOR_IMX681_12M     0x39  //  |   v    |   -    |   v    |   -    |
#define SENSOR_IMX681_12M_SEQ 0x3A  //  |   v    |   -    |   v    |   -    |
#define SENSOR_FIXP_5M        0x3B  //  |   v    |   -    |   -    |   -    |
#define SENSOR_FIXP_2K        0x3C  //  |   v    |   -    |   -    |   -    |
#define SENSOR_SC5356_2M      0x3D  //  |   v    |   v    |   v    |   -    |
#define SENSOR_OS02H10        0x3E  //  |   v    |   v    |   -    |   -    |
#define SENSOR_OV13B10        0x3F  //  |   v    |   v    |   -    |   -    |
#define SENSOR_OV13B10_12M    0x40  //  |   v    |   -    |   -    |   -    |
#define SENSOR_OV13B10_12M_SEQ 0x41  //  |   v    |   -    |   -    |   -    |
#define SENSOR_OV12890         0x42  //  |   v    |   v    |   -    |   -    |
#define SENSOR_OV12890_12M     0x43  //  |   v    |   -    |   -    |   -    |
#define SENSOR_OV12890_12M_SEQ 0x44  //  |   v    |   -    |   -    |   -    |

static const struct sensor_params_t sensor_params[] = {
	[SENSOR_DUMMY]        = {1920, 1080, 30},
	[SENSOR_SC2336]       = {1920, 1080, 30},
	[SENSOR_GC2053]       = {1920, 1080, 30},
	[SENSOR_GC4653]       = {2560, 1440, 24},
	[SENSOR_F37]          = {1920, 1080, 30},
	[SENSOR_IMX327]       = {1920, 1080, 24},
	[SENSOR_F51]          = {1536, 1536, 20},
	[SENSOR_PS5258]       = {1920, 1080, 30},
	[SENSOR_SC301]        = {2048, 1536, 20},
	[SENSOR_IMX307]       = {1920, 1080, 30},
	[SENSOR_SC2333]       = {1920, 1080, 30},
	[SENSOR_GC4023]       = {2560, 1440, 24},
	[SENSOR_PS5420]       = {1952, 1944, 24},
	[SENSOR_PS5270]       = {1536, 1536, 30},
	[SENSOR_GC5035]       = {2592, 1944, 15},
	[SENSOR_PS5268]       = {1920, 1080, 30},
	[SENSOR_SC2310]       = {1920, 1080, 30},
	[SENSOR_PS5420_HDR]   = {1952, 1944, 24},
	[SENSOR_PS5270_HDR]   = {1536, 1536, 25},
	[SENSOR_F53]          = {1920, 1080, 30},
	[SENSOR_F55]          = {1920, 1080, 30},
	[SENSOR_GC4663]       = {2560, 1440, 24},
//  [SENSOR_GC4663_HDR]   = {2560, 1440, 20},
	[SENSOR_K351]         = {2000, 2000, 20},
//  [SENSOR_K351_HDR]     = {2000, 2000, 20},
	[SENSOR_OV50A40]      = {2048, 1536, 30},
//  [SENSOR_SC301_HDR]    = {2048, 1536, 20},
//  [SENSOR_F51_HDR]      = {1536, 1536, 20},
	[SENSOR_OS04A10]      = {2560, 1440, 24},
//  [SENSOR_F55_HDR]      = {1920, 1080, 30},
	[SENSOR_GC1084]       = {1280,  720, 30},
	[SENSOR_SC5356]       = {2592, 1944, 15},
	[SENSOR_F38]          = {1920, 1080, 30},
	[SENSOR_PS5262]       = {1920, 1080, 30},
	[SENSOR_K05]          = {2592, 1944, 15},
	[SENSOR_MIS2008]      = {1920, 1080, 30},
	[SENSOR_NT99236]      = {1920, 1080, 30},
	[SENSOR_VD550G]       = { 640,  600, 60},
	[SENSOR_GC3003]       = {2304, 1296, 30},
	[SENSOR_IMX662]       = {1920, 1080, 30},
	[SENSOR_GC2083]       = {1920, 1080, 30},
	[SENSOR_OV2735]       = {1920, 1080, 30},
	[SENSOR_SC400AI]      = {2560, 1440, 24},
	[SENSOR_OV50A40_CROP] = {2048, 1536, 30},
	[SENSOR_OV9734]       = {1280,  720, 30},
	[SENSOR_CV2003]       = {1920, 1080, 30},
	[SENSOR_GC2093]       = {1920, 1080, 30},
	[SENSOR_F35]          = {1920, 1080, 30},
	[SENSOR_OV5693]       = {2592, 1944, 15},
	[SENSOR_SC3336]       = {2304, 1296, 30},
	[SENSOR_K06A]         = {2560, 1440, 24},
	[SENSOR_K306P]        = {2560, 1440, 24},
	[SENSOR_OV9734_SD]    = { 640,  360, 60},
	[SENSOR_IMX471]       = {2304, 1728, 24},
	[SENSOR_IMX471_12M]       = {4032, 3024, 5},
	[SENSOR_IMX471_12M_SEQ]   = {2032, 3024, 5}, //width = 2016 + 16(overlap)
	[SENSOR_IMX681]           = {2000, 1500, 30},
	[SENSOR_IMX681_12M]       = {4016, 3012, 4},
	[SENSOR_IMX681_12M_SEQ]   = {2032, 1532, 4}, //width = 2008 + 24(overlap) //height = 1506 + 26
	[SENSOR_FIXP_5M]          = {2592, 1944, 30}, //fix pattern
	[SENSOR_FIXP_2K]          = {2560, 1440, 30},
	[SENSOR_SC5356_2M]        = {1088, 1944, 30},
	[SENSOR_OS02H10]          = {1920, 1080, 30},
	[SENSOR_OV13B10]  	      = {2096,  1560, 30},
	[SENSOR_OV13B10_12M]      = {4032,  3024, 10},
	[SENSOR_OV13B10_12M_SEQ]  = {2032,  1532, 5}, //width = 2016 + 16(overlap) //height = 1512 + 20
	[SENSOR_OV12890]  	      = {2048,  1536, 30},
	[SENSOR_OV12890_12M]      = {4032,  3024, 8},
	[SENSOR_OV12890_12M_SEQ]  = {2032,  1532, 5}, //width = 2016 + 16(overlap) //height = 1512 + 20
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
