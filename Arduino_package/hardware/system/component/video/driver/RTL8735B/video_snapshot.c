#include "module_video.h"
#include "log_service.h"
#include "vfs.h"
#include "video_snapshot.h"

#define VIDEO_SNAPSHOT_JPEG_TYPE 0x02

typedef struct {
	uint8_t *output_buffer;
	uint32_t output_buffer_size;
	uint32_t output_size;
} video_buffer_t;

typedef struct {
	_sema snapshot_sema;
	unsigned char *jpeg_buf;
	unsigned int jpeg_len;
	unsigned int take_snapshot;
	unsigned int jpeg_index;
	uint32_t dest_addr;
	uint32_t dest_len;
	uint32_t dest_actual_len;
	_mutex snapshot_mutex;
	video_buffer_t video_buf;
	mm_context_t *video_snapshot_ctx;
	int (*snapshot_write)(uint8_t *buf, uint32_t len, char *filename);
} jpeg_snapshot_context_t;

static video_params_t video_snapshot_params;
static jpeg_snapshot_context_t *snapshot_ctx = NULL;
static int video_snapshot_cb(uint32_t jpeg_addr, uint32_t jpeg_len)
{
	snapshot_ctx->take_snapshot = 1;
	printf("capture_snapshot_cb snapshot size=%u\n\r", jpeg_len);
	snapshot_ctx->dest_addr = jpeg_addr;
	snapshot_ctx->dest_actual_len = jpeg_len;
	rtw_up_sema(&snapshot_ctx->snapshot_sema);
	return 0;
}

static int video_snapshot_get_buffer(video_buffer_t *video_buf, uint32_t timeout_ms)
{
	if (rtw_down_timeout_sema(&snapshot_ctx->snapshot_sema, timeout_ms)) {
		video_buf->output_buffer = (u8 *) snapshot_ctx->dest_addr;
		video_buf->output_size = snapshot_ctx->dest_actual_len;
		return 1;
	} else {
		video_buf->output_buffer = NULL;
		video_buf->output_size = 0;
		return 0;
	}
}

int snapshot_write_picture(uint8_t *buf, uint32_t len, char *filename)
{
	FILE *m_file = NULL;
	printf("jpeg %s\r\n", filename);
	m_file = fopen(filename, "w");
	fwrite(buf, 1, len, m_file);
	fclose(m_file);
	return 0;
}

static int video_capture_snapshot(char *filename)
{
	if (video_snapshot_get_buffer(&snapshot_ctx->video_buf, SNAPSHOT_TIMEOUT)) {
		snapshot_ctx->snapshot_write(snapshot_ctx->video_buf.output_buffer, snapshot_ctx->video_buf.output_size, filename);
		snapshot_ctx->take_snapshot = 0;
		return 0;
	} else {
		printf("Warn: get snapshot buffer failed\r\n");
		return -1;
	}
}

int snapshot_vfs_init(void)
{
	vfs_init(NULL);
	int ret = 0;
#if (RECORD_TYPE == SNAPSHOT_SD)
	ret = vfs_user_register("sd", VFS_FATFS, VFS_INF_SD);
#else
	ret = vfs_user_register("ram", VFS_FATFS, VFS_INF_RAM);
#endif
	if (ret < 0) {
		printf("It can't init sd card\r\n");
		return -1;
	} else {
		return 0;
	}
}

int video_snapshot_take(snapshot_user_config_t *config, char *filename)
{
	printf("Sanpshot start\r\n");
	rtw_mutex_get(&snapshot_ctx->snapshot_mutex);
	snapshot_ctx->take_snapshot = 1;
	video_snapshot_params.width = config->width;
	video_snapshot_params.height = config->height;
	video_snapshot_params.fps = config->fps;
	mm_module_ctrl(snapshot_ctx->video_snapshot_ctx, CMD_VIDEO_SET_PARAMS, (int)&video_snapshot_params);
	mm_module_ctrl(snapshot_ctx->video_snapshot_ctx, CMD_VIDEO_APPLY, video_snapshot_params.stream_id);
	mm_module_ctrl(snapshot_ctx->video_snapshot_ctx, CMD_VIDEO_SNAPSHOT, 1);
	video_capture_snapshot(filename);
	snapshot_ctx->take_snapshot = 0;
	mm_module_ctrl(snapshot_ctx->video_snapshot_ctx, CMD_VIDEO_STREAM_STOP, video_snapshot_params.stream_id);
	rtw_mutex_put(&snapshot_ctx->snapshot_mutex);
	return 0;
}

int video_snapshot_take_with_streaming(snapshot_user_config_t *config, char *filename)
{
	//printf("Sanpshot start %s\r\n",filename);
	rtw_mutex_get(&snapshot_ctx->snapshot_mutex);
	snapshot_ctx->take_snapshot = 1;
	mm_module_ctrl(snapshot_ctx->video_snapshot_ctx, CMD_VIDEO_SNAPSHOT, 1);
	video_capture_snapshot(filename);
	snapshot_ctx->take_snapshot = 0;
	rtw_mutex_put(&snapshot_ctx->snapshot_mutex);
	return 0;
}

int video_snapshot_init(snapshot_user_config_t *config)
{
	int ret = 0;

	int voe_heap_size = 0;

	int channel[4] = {0};
	int width[4] = {0};
	int height[4] = {0};

	if (!config->snapshot_write) {
		printf("The snapshot_write is not setup\r\n");
		return -1;
	}

	if (config->channel < 0 || config->channel > 2) {
		printf("The wrong parameters %d\r\n", config->channel);
		return -1;
	} else {
		channel[config->channel] = config->channel;
		width[config->channel] = config->width;
		height[config->channel] = config->height;
	}

	if (config->self_buf) {
		voe_heap_size = video_voe_presetting(channel[0], width[0], height[0], 0, channel[0],
											 channel[1], width[1], height[1], 0, channel[1],
											 channel[2], width[2], height[2], 0, channel[2],
											 0, 0, 0);
	}

	snapshot_ctx = (jpeg_snapshot_context_t *) malloc(sizeof(jpeg_snapshot_context_t));
	memset(snapshot_ctx, 0x00, sizeof(jpeg_snapshot_context_t));

	snapshot_ctx->snapshot_write = config->snapshot_write;

	snapshot_ctx->video_snapshot_ctx = mm_module_open(&video_module);

	video_snapshot_params.stream_id = config->channel;
	video_snapshot_params.type = VIDEO_SNAPSHOT_JPEG_TYPE;
	video_snapshot_params.width = config->width;
	video_snapshot_params.height = config->height;
	video_snapshot_params.fps = config->fps;
	video_snapshot_params.use_static_addr = 1;

	rtw_init_sema(&snapshot_ctx->snapshot_sema, 0);
	rtw_mutex_init(&snapshot_ctx->snapshot_mutex);

	if (snapshot_ctx->video_snapshot_ctx) {
		mm_module_ctrl(snapshot_ctx->video_snapshot_ctx, CMD_VIDEO_SET_PARAMS, (int)&video_snapshot_params);
	} else {
		rt_printf("video open %d fail\n\r", channel);
		goto EXIT;
	}

	mm_module_ctrl(snapshot_ctx->video_snapshot_ctx, CMD_VIDEO_SNAPSHOT_CB, (int)video_snapshot_cb);
	printf("Snapshot init done\r\n");
	return 0;
EXIT:
	if (snapshot_ctx) {
		free(snapshot_ctx);
		snapshot_ctx = NULL;
	}
	return -1;
}

int video_snapshot_init_with_streaming(snapshot_user_config_t *config)
{
	int ret = 0;

	if (!config->snapshot_write) {
		printf("The snapshot_write is not setup\r\n");
		goto EXIT;
	}

	if (!config->video_snapshot_ctx) {
		printf("The video_snapshot_ctx is not setup\r\n");
		goto EXIT;
	}

	snapshot_ctx = (jpeg_snapshot_context_t *) malloc(sizeof(jpeg_snapshot_context_t));
	memset(snapshot_ctx, 0x00, sizeof(jpeg_snapshot_context_t));

	snapshot_ctx->video_snapshot_ctx = config->video_snapshot_ctx;
	snapshot_ctx->snapshot_write = config->snapshot_write;
	rtw_init_sema(&snapshot_ctx->snapshot_sema, 0);
	rtw_mutex_init(&snapshot_ctx->snapshot_mutex);

	mm_module_ctrl(snapshot_ctx->video_snapshot_ctx, CMD_VIDEO_SNAPSHOT_CB, (int)video_snapshot_cb);
	printf("Sanpshot with streaming init done\r\n");
	return 0;
EXIT:
	if (snapshot_ctx) {
		free(snapshot_ctx);
		snapshot_ctx = NULL;
	}
	return -1;
}

int video_snapshot_deinit(void)
{
	if (snapshot_ctx) {
		if (snapshot_ctx->take_snapshot) {
			printf("It is running\r\n");
			return -1;
		} else {
			rtw_free_sema(&snapshot_ctx->snapshot_sema);
			rtw_mutex_free(&snapshot_ctx->snapshot_mutex);
			free(snapshot_ctx);
			snapshot_ctx = NULL;
		}
	}
	mm_module_close(snapshot_ctx->video_snapshot_ctx);
	printf("DEINT WITH SINGLE\r\n");
	//video_deinit();
	return 0;
}

int video_snapshot_deinit_with_streaming(void)
{
	if (snapshot_ctx) {
		if (snapshot_ctx->take_snapshot) {
			printf("It is running\r\n");
			return -1;
		} else {
			rtw_free_sema(&snapshot_ctx->snapshot_sema);
			rtw_mutex_free(&snapshot_ctx->snapshot_mutex);
			free(snapshot_ctx);
			snapshot_ctx = NULL;
			printf("DEINT WITH STREAMING\r\n");
		}
	}
	return 0;
}
snapshot_user_config_t snap_config;
static void fSNAP(void *arg)
{
	int ret = 0;
	char snapshot_name[32];
	static int count = 0;
	if (!strcmp(arg, "INIT")) { //It is only for single channel without h264
		memset(&snap_config, 0x00, sizeof(snap_config));
		snap_config.width = 1920;
		snap_config.height = 1080;
		snap_config.fps = 10;
		snap_config.channel = 2;
		snap_config.self_buf = 1;
		snap_config.snapshot_write = snapshot_write_picture;
		printf("snap_config.snapshot_write %p %p", snap_config.snapshot_write, snapshot_write_picture);

		ret = snapshot_vfs_init();
		if (ret < 0) {
			printf("It can't init the sd card\r\n");
			return;
		}
		ret = video_snapshot_init(&snap_config);
		if (ret < 0) {
			printf("It can't be inited\r\n");
		}
	} else if (!strcmp(arg, "SNAP")) {//snapshot with single channel
		if (snapshot_ctx) {
			memset(snapshot_name, 0x00, sizeof(snapshot_name));
#if (RECORD_TYPE == SNAPSHOT_SD)
			sprintf(snapshot_name, "sd:/%d.jpg", count);
#else
			sprintf(snapshot_name, "ram:/%d.jpg", count);
#endif
			ret = video_snapshot_take(&snap_config, snapshot_name);
			count++;
			if (ret < 0) {
				printf("snapshot fail\r\n");
			}
		} else {
			printf("The snapshot is not init\r\n");
		}
	} else if (!strcmp(arg, "SNAPS")) { //snapshot with streaming
		if (snapshot_ctx) {
			memset(snapshot_name, 0x00, sizeof(snapshot_name));
#if (RECORD_TYPE == SNAPSHOT_SD)
			sprintf(snapshot_name, "sd:/%d.jpg", count);
#else
			sprintf(snapshot_name, "ram:/%d.jpg", count);
#endif
			ret = video_snapshot_take_with_streaming(&snap_config, snapshot_name);
			if (ret < 0) {
				printf("snapshot fail\r\n");
			}
			count++;
		} else {
			printf("The snapshot is not init\r\n");
		}
	} else if (!strcmp(arg, "DINT")) {
		if (snapshot_ctx) {
			ret = video_snapshot_deinit();
			if (ret < 0) {
				printf("snapshot deinit fail\r\n");
			}
		} else {
			printf("The snapshot is not init\r\n");
		}
	} else if (!strcmp(arg, "SDINT")) {
		if (snapshot_ctx) {
			ret = video_snapshot_deinit_with_streaming();
			if (ret < 0) {
				printf("snapshot deinit fail\r\n");
			}
		} else {
			printf("The snapshot is not init\r\n");
		}
	} else {
		printf("invalid cmd\r\n");
	}
}

static log_item_t userctrl_items[] = {
	{"SNAP", fSNAP, },
};

void atcmd_snapshot_init(void)
{
	log_service_add_table(userctrl_items, sizeof(userctrl_items) / sizeof(userctrl_items[0]));
}