#ifndef _MP4_DEMUX_
#define _MP4_DEMUX_
typedef struct _header {
	unsigned int size;
	unsigned char str[4];
} header;

#include "basic_types.h"
#include "osdep_service.h"
#include "fatfs_sdcard_api.h"

#define mvhd_length 8
#define trak_length 8
#define mdia_length 8
#define minf_length 8

#define video_type 0
#define audio_type 1

#define H264_TYPE 0x00
#define H265_TYPE 0x01

#define AUDIO_AAC  0X00
#define AUDIO_ULAW 0X01
#define AUDIO_ALAW 0X02

typedef struct _mp4_demux {
	FATFS       m_fs;
	int         drv_num;
	char        _drv[32];
	FIL             *m_file;
	unsigned int video_len;
	unsigned int audio_len;
	unsigned int key_len;
	unsigned int sample_index;
	unsigned int channel_count;
	unsigned char vps[0x40];
	unsigned char sps[0x40];
	unsigned char pps[0x40];
	unsigned short vps_length;
	unsigned short sps_length;
	unsigned short pps_length;
	unsigned short encode_type;
	unsigned int *video_size_buffer;
	unsigned int *video_offset_buffer;
	unsigned int *video_keyframe_buffer;
	unsigned int *audio_size_buffer;
	unsigned int *audio_offset_buffer;
	unsigned int *video_timestamp_buf;
	unsigned int *audio_timestamp_buf;
	unsigned int video_max_size;
	unsigned int audio_max_size;
	unsigned int video_exist;
	unsigned int audio_exist;
	unsigned int fps;
	unsigned short width;
	unsigned short height;
	unsigned int audio_sample_rate;
	unsigned int audio_channel;
	unsigned char *info_buf;
	unsigned int info_offset;
	unsigned int info_size;
	unsigned int info_moov_offset;
	unsigned int audio_format_type;
	int vfs_format_enable;
	FILE     *vfs_file;
} mp4_demux;

int get_video_frame(mp4_demux *mp4_demuxer, unsigned char *buf, int index, unsigned char *key_frame, unsigned int *duration_time, unsigned int *timestamp);
int get_audio_frame(mp4_demux *mp4_demuxer, unsigned char *buf, int index, unsigned int *duration_time, unsigned int *timestamp);
int mp4_demuxer_open(mp4_demux *mp4_demuxer, char *filename);
void mp4_demuxer_close(mp4_demux *mp4_demuxer);
void set_mp4_demuxer_fatfs_param(mp4_demux *mp4_demuxer, fatfs_sd_params_t *fatfs_param);
void set_mp4_demuxer_vfs_enable(mp4_demux *mp4_demuxer);
int mp4_demuxer_seek(mp4_demux *mp4_demuxer, unsigned int video_ms, int *video_index, int *audio_index);
int get_timestamp(mp4_demux *mp4_demuxer, unsigned int type, unsigned int index);
int check_video_key_frame(mp4_demux *mp4_demuxer, int index);
#endif //_MP4_DEMUX_