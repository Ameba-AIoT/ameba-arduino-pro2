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



/**
@code
 The table below gives an overview of the hardware resources supported by each
 AmebaPro EVAL board.
     - Sensor board:

 =================================================================================================================+
   AmebaPro EVAL  | Sensor board |
 =================================================================================================================+
   AmebaPro2-EVAL   |  SC2053      |
 -----------------------------------------------------------------------------------------------------------------+
   AmebaPro2-EVAL   |  SC2336      |
 -----------------------------------------------------------------------------------------------------------------+
   AmebaPro2-EVAL   |  PS5258      |
 -----------------------------------------------------------------------------------------------------------------+
 =================================================================================================================+
@endcode
*/
struct sensor_params_t {
	unsigned int sensor_width;
	unsigned int sensor_height;
	unsigned int sensor_fps;
};

//ARDUINO_SDK, DO NOT CHANGE LINE 46 TO 84
#ifdef ARDUINO_SDK
#define ARDUINO_SDK_SENSOR 1

#if ARDUINO_SDK_SENSOR == 1
#define SENSOR_DUMMY        0x00
#define SENSOR_F37          0x01
static const struct sensor_params_t sensor_params[] = {
	{1920, 1080, 30}, //SENSOR_DUMMY        0x00
	{1920, 1080, 30},
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
#define ENABLE_FCS      	0

#else

#define SENSOR_DUMMY        0x00
#define SENSOR_F37          0x01
static const struct sensor_params_t sensor_params[] = {
	{1920, 1080, 30}, //F37
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
#endif

#else
//                                    | Normal |  Fcs   |        |
//                                    | Driver | Driver |   IQ   |
//                                    ---------|--------|--------|
#define SENSOR_DUMMY        0x00  //  |   v    |   v    |   -    |	For dummy sensor, no support fast camera start
#define SENSOR_SC2336       0x01  //  |   v    |   v    |   v    |
#define SENSOR_GC2053       0x02  //  |   v    |   v    |   v    |
#define SENSOR_GC4653       0x03  //  |   v    |   v    |   v    |
#define SENSOR_F37          0x04  //  |   v    |   v    |   v    |
#define SENSOR_IMX327       0x05  //  |   v    |   -    |   -    |
#define SENSOR_F51          0x06  //  |   v    |   v    |   v    |
#define SENSOR_PS5258       0x07  //  |   v    |   -    |   -    |  It don't support the multi sensor for PS5258 now.If you want to use the sensor,please remove it.
#define SENSOR_SC301        0x08  //  |   v    |   v    |   -    |
#define SENSOR_IMX307       0x09  //  |   v    |   -    |   -    |
#define SENSOR_SC2333       0x0A  //  |   v    |   v    |   v    |
#define SENSOR_GC4023       0x0B  //  |   v    |   v    |   v    |
#define SENSOR_PS5420       0x0C  //  |   v    |   v    |   v    |
#define SENSOR_PS5270       0x0D  //  |   v    |   v    |   v    |
#define SENSOR_GC5035       0x0E  //  |   v    |   v    |   -    |  Arduino use iq_gc2053.bin
#define SENSOR_PS5268       0x0F  //  |   v    |   -    |   -    |
#define SENSOR_SC2310       0x10  //  |   v    |   -    |   -    |
#define SENSOR_PS5420_HDR   0x11  //  |   v    |   v    |   v    |
#define SENSOR_PS5270_HDR   0x12  //  |   v    |   v    |   v    |
#define SENSOR_F53          0x13  //  |   v    |   v    |   v    |
#define SENSOR_F55          0x14  //  |   v    |   -    |   -    |
#define SENSOR_GC4663       0x15  //  |   v    |   v    |   v    |
#define SENSOR_GC4663_HDR   0x16  //  |   v    |   v    |   v    |
#define SENSOR_K351         0x17  //  |   v    |   -    |   -    |
#define SENSOR_K351_HDR     0x18  //  |   v    |   -    |   -    |
#define SENSOR_OV50A40      0x19  //  |   v    |   -    |   -    |
#define SENSOR_SC301_HDR    0x1A  //  |   v    |   v    |   -    |
#define SENSOR_F51_HDR      0x1B  //  |   v    |   v    |   v    |
#define SENSOR_OS04A10      0x1C  //  |   v    |   -    |   -    |
#define SENSOR_F55_HDR      0x1D  //  |   v    |   -    |   v    |
#define SENSOR_GC1084       0x1E  //  |   v    |   -    |   -    |

static const struct sensor_params_t sensor_params[] = {
	{1920, 1080, 30}, //SENSOR_DUMMY        0x00
	{1920, 1080, 30}, //SENSOR_SC2336       0x01
	{1920, 1080, 30}, //SENSOR_GC2053       0x02
	{2560, 1440, 24}, //SENSOR_GC4653 		0x03
	{1920, 1080, 30}, //SENSOR_F37			0x04
	{1920, 1080, 30}, //SENSOR_IMX327		0x05
	{1536, 1536, 30}, //SENSOR_F51			0x06
	{1920, 1080, 30}, //SENSOR_PS5258       0x07
	{2048, 1536, 20}, //SENSOR_SC301		0x08
	{1920, 1080, 30}, //SENSOR_IMX307		0x09
	{1920, 1080, 30}, //SENSOR_SC2333		0x0A
	{2560, 1440, 24}, //SENSOR_GC4023		0x0B
	{1952, 1944, 24}, //SENSOR_PS5420		0x0C
	{1536, 1536, 30}, //SENSOR_PS5270		0x0D
	{2592, 1944, 15}, //SENSOR_GC5035		0x0E
	{1920, 1080, 30}, //SENSOR_PS5268		0x0F
	{1920, 1080, 30}, //SENSOR_SC2310		0x10
	{1952, 1944, 24}, //SENSOR_PS5420_HDR	0x11
	{1536, 1536, 30}, //SENSOR_PS5270_HDR	0x12
	{1920, 1080, 30}, //SENSOR_F53			0x13
	{1920, 1080, 30}, //SENSOR_F55			0x14
	{2560, 1440, 24}, //SENSOR_GC4663		0x15
	{2560, 1440, 20}, //SENSOR_GC4663_HDR	0x16
	{2000, 2000, 24}, //SENSOR_K351			0x17
	{2000, 2000, 20}, //SENSOR_K351_HDR		0x18
	{2048, 1536, 30}, //SENSOR_OV50A40		0x19
	{2048, 1536, 20}, //SENSOR_SC301_HDR	0x1A
	{1536, 1536, 20}, //SENSOR_F51_HDR		0x1B
	{2560, 1440, 24}, //SENSOR_OS04A10		0x1C
	{1920, 1080, 30}, //SENSOR_F55_HDR		0x1D
	{1280, 720, 30}, //SENSOR_GC1084
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

//#define ENABLE_FCS      	1

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
