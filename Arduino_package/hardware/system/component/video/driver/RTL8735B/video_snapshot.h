#ifndef _VIDEO_SNAPSHOT_H_
#define _VIDEO_SNAPSHOT_H_
#define SNAPSHOT_SD  1
#define SNAPSHOT_RAM 0
#define RECORD_TYPE  SNAPSHOT_SD//SNAPSHOT_RAM
#define SNAPSHOT_TIMEOUT 2000
typedef struct {
	int channel;
	int width;
	int height;
	int fps;
	int (*snapshot_write)(uint8_t *buf, uint32_t len, char *filename);
	mm_context_t *video_snapshot_ctx;
	int self_buf;
} snapshot_user_config_t;

int video_snapshot_init(snapshot_user_config_t *config);
int video_snapshot_init_with_streaming(snapshot_user_config_t *config);
int video_snapshot_deinit(void);
int video_snapshot_deinit_with_streaming(void);
int video_snapshot_take(snapshot_user_config_t *config, char *filename);
int video_snapshot_take_with_streaming(snapshot_user_config_t *config, char *filename);
int snapshot_vfs_init(void);
int snapshot_write_picture(uint8_t *buf, uint32_t len, char *filename);
void atcmd_snapshot_init(void);
#endif