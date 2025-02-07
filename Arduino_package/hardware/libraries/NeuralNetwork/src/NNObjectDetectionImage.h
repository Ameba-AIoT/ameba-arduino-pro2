#ifndef __NNOBJECTDETECTIONIMAGE_H__
#define __NNOBJECTDETECTIONIMAGE_H__

#include "NNModelSelection.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "mmf2_link.h"
#include "mmf2_siso.h"
#include "avcodec.h"

#include "module_vipnn.h"

#include "avcodec.h"
#include "vfs.h"
#include "cJSON.h"
#include "FtpClient.h"

#include "model_yolo.h"

#ifdef __cplusplus
}
#endif

#include "module_fileloader.h"
#include "module_filesaver.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_STDIO
#define STBI_ONLY_BMP
#define STBI_ONLY_JPEG

// NN tester config
#define NN_MODEL_OBJ        yolov4_tiny     /* fix here to choose model: yolov4_tiny, yolov7_tiny */
#define NN_DATASET_LABEL    coco_name       /* fix here to define label */
#define TEST_IMAGE_WIDTH	416             /* fix here to match model input size */
#define TEST_IMAGE_HEIGHT	416             /* fix here to match model input size */

#define SAVE_COCO_FORMAT    1

#define MODE_SD     0
#define MODE_FTP    1

/* Configure mode */
#define LOADER_MODE MODE_SD  /* MODE_SD, MODE_FTP */
#define SAVER_MODE MODE_SD   /* MODE_SD, MODE_FTP */

class NNObjectDetectionImage: public NNModelSelection {
public:
	NNObjectDetectionImage(void);
	~NNObjectDetectionImage(void);

	void begin(char* filelist_name);
	void end(void);

	static mm_context_t *fileloader_ctx;
	static mm_context_t *filesaver_ctx;
	static mm_context_t *vipnn_ctx;

	static mm_siso_t *siso_fileloader_vipnn;
	static mm_siso_t *siso_vipnn_filesaver;


private:
	float nn_confidence_thresh = 0.2;
	float nn_nms_thresh = 0.3; 
	static int saver_count;
	static char coco_name[80][20];
	static nn_data_param_t roi_tester;
	static fileloader_params_t test_image_params;
	static int (*media_save_file)(char *file_name, char *data_buf, int data_buf_size);

	static void set_nn_roi(int w, int h);
	static int ImageDecodeToRGB888planar_ConvertInPlace(void *pbuffer, void *pbuffer_size);
	static char *nn_get_json_format(void *p, int frame_id, char *file_name);
	static void nn_save_handler_for_evaluate(char *file_name, uint32_t data_addr, uint32_t data_size);
	static int sd_save_file(char *file_name, char *data_buf, int data_buf_size);
	static int ftp_save_file(char *file_name, char *data_buf, int data_buf_size);
	static char* strip_filename_extention(char *filename);
	static int get_id_in_filename(char *str);
	static int get_line_num_in_sdfile(char *file_name);
};

#endif