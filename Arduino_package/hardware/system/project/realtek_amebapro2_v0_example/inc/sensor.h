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

#ifdef ARDUINO_SDK
#define SENSOR_F37		0x00
#else
#define SENSOR_DUMMY        0x00 //For dummy sensor, no support fast camera start
#define SENSOR_SC2336       0x01
#define SENSOR_GC2053       0x02
#define SENSOR_GC4653 		0x03
#define SENSOR_F37			0x04
#define SENSOR_IMX327		0x05
#define SENSOR_F51			0x06
#define SENSOR_PS5258       0x07 //It don't support the multi sensor for PS5258 now.If you want to use the sensor,please remove it.
#define SENSOR_SC301		0x08
#define SENSOR_IMX307		0x09
#define SENSOR_SC2333		0x0A
#define SENSOR_GC4023		0x0B
#define SENSOR_PS5420		0x0C
#define SENSOR_PS5270		0x0D
#define SENSOR_GC5035		0x0E
#define SENSOR_PS5268		0x0F
#define SENSOR_SC2310		0x10
#endif

static const struct sensor_params_t sensor_params[] = {
	{1920, 1080, 30}, //DUMMY
	{1920, 1080, 30}, //SC2336
	{1920, 1080, 30}, //GC2053
	{2560, 1440, 15}, //GC4653
	{1920, 1080, 30}, //F37
	{1920, 1080, 30}, //IMX327
	{1536, 1536, 30}, //F51
	{1920, 1080, 30}, //PS5258
	{2048, 1536, 20}, //SC301
	{1920, 1080, 30}, //IMX307
	{1920, 1080, 30}, //SC2333
	{2560, 1440, 15}, //GC4023
	{1952, 1944, 30}, //PS5420
	{1536, 1536, 30}, //PS5270
	{2592, 1944, 30}, //GC5035
	{1920, 1080, 30}, //PS5268
	{1920, 1080, 30}, //SC2310
};


#define SENSOR_MAX         5

static const unsigned char sen_id[SENSOR_MAX] = {
	SENSOR_F37
};
#define USE_SENSOR      	SENSOR_F37

static const      char manual_iq[SENSOR_MAX][64] = {
	"iq_f37",
};
#define MANUAL_SENSOR_IQ	0xFF

#define ENABLE_FCS      	0

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
