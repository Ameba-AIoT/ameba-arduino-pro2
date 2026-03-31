/******************************************************************************
*
* Copyright(c) 2021 Realtek Corporation. All rights reserved.
*
******************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <arm_math.h>

#include <hal_cache.h>
#include "mmf2_module.h"
#include "osdep_service.h"
#include "module_facerecog.h"

#include "ftl_common_api.h"
#include "crypto_api.h"
#include "device_lock.h"

/* this module ast as vipnn post processing handling module, depend on vipnn output*/
#include "module_vipnn.h"

#define DBG_LEVEL	LOG_ERR

#define LOG_OFF		4
#define LOG_ERR		3
#define LOG_MSG		2
#define LOG_INF		1
#define LOG_ALL		0

#define dprintf(level, ...) if(level >= DBG_LEVEL) do{printf(__VA_ARGS__);}while(0)

#define ABS(x) ((x)>0?(x):-(x))

static uint32_t nn_measure_tick[8];
#define TICK_INIT()
#define TICK_GET() (uint32_t)mm_read_mediatime_ms()

#define NN_MEASURE_INIT(n)	do{nn_measure_tick[n] = 0; TICK_INIT();}while(0)
#define NN_MEASURE_START(n) do{nn_measure_tick[n] = TICK_GET();}while(0)
#define NN_MEASURE_STOP(n)  do{nn_measure_tick[n] = TICK_GET() - nn_measure_tick[n];}while(0)
#define NN_MEASURE_PRINT(n) do{printf("nn tick[%d] = %d\n\r", n, nn_measure_tick[n]);}while(0)
//#define NN_MEASURE_PRINT(n) do{}while(0)

#include "fwfs.h"


void facerecog_dump_feature(void *feature, int feature_num)
{
	dprintf(LOG_INF, "register feature number %d\n\r", feature_num);
}

void facerecog_dump_frc(void *frc_info, int frc_num)
{
#if 0
	struct FRC_INFO_S *info = (struct FRC_INFO_S *)frc_info;
	dprintf(LOG_INF, "---------%02d----------\n\r", frc_num);
	for (int i = 0; i < frc_num; i++) {
		struct cvRect_S *bb = &info[i].bbox;
		dprintf(LOG_INF, "%02d bbox : %d, %d, %d, %d\n\r", i, bb->xmin, bb->ymin, bb->xmax, bb->ymax);
		dprintf(LOG_INF, "%02d idx  : %d\n\r", i, info[i].reg_index);
		dprintf(LOG_INF, "%02d score: %f\n\r", i, info[i].score);
	}
#endif
	dprintf(LOG_INF, "--------------------\n\r");
}


//-----------------------------------------------------------------------
float similarity1(float *a, float *b, int dim)
{
	float sim = 0.0, tmp;
	for (int i = 0; i < dim; i++) {
		float diff = a[i] - b[i];
		sim += diff * diff;
	}

	arm_sqrt_f32(sim, &tmp);
	return tmp;
}

float similarity2(float *a, float *b, int dim)
{
	float sim = 0.0;
	for (int i = 0; i < dim; i++) {
		float diff = a[i] - b[i];
		sim += diff * diff;
	}

	return sim;
}

static float sqrt_arm(float x)
{
	float tmp;
	arm_sqrt_f32(x, &tmp);
	return tmp;
}

#define FACERECOG_REDUCE_SQRT 1
#if FACERECOG_REDUCE_SQRT
#define SIMILARITY similarity2
#define THRES(x) ((x)*(x))
#define SIMVAL(x) (sqrt_arm(x))
#else
#include
#define SIMILARITY similarity1
#define THRES(x) (x)
#define SIMVAL(x) (x)
#endif

void facerecog_feature_dump(float *buf, int size)
{
	__disable_irq();
	for (int i = 0; i < size; i += 16) {
		for (int x = 0; x < 16; x++) {
			printf(" %2.2f", buf[i + x]);
		}
		printf("\n\r");
	}
	__enable_irq();
}

// return face id, -1 is unknown person
int search_face_identity(void *p, face_feature_res_t *ff, float thres)
{
	frc_ctx_t *ctx = (frc_ctx_t *)p;

	int res_id = -1;
	float min = 128.0;

	// if use similarity2, need using square of thres
	thres = THRES(thres);


	for (int i = 0; i < ctx->face_data.reg_feature_num; i++) {
		//dprintf(LOG_INF, "----------- reg feature\n\r");
		//facerecog_feature_dump(ctx->face_data.reg_feature[i].result, 128);
		//dprintf(LOG_INF, "----------- input feature\n\r");
		//facerecog_feature_dump(ff->feature, 128);
		float sim = SIMILARITY(ctx->face_data.reg_feature[i].feature, ff->feature, 128);
		dprintf(LOG_MSG, "iD %d, name %s, sim %f\n\r", i, ctx->face_data.reg_name[i], SIMVAL(sim));
		if (sim <= thres && min > sim) {
			res_id = i;
			min = sim;
		}
	}

	return res_id;
}

int facerecog_handle(void *p, void *input, void *output)
{
	frc_ctx_t *ctx = (frc_ctx_t *)p;
	mm_queue_item_t *input_item = (mm_queue_item_t *)input;

	vipnn_out_buf_t *last_out = (vipnn_out_buf_t *)input_item->data_addr;
	int ff_cnt = last_out->res_cnt;

	dprintf(LOG_INF, "run recognition obj %d, thres %f\n\r", ff_cnt, ctx->params.sim_thres);

	if (ctx->mode == FRC_REGISTER && ff_cnt > 1) {
		dprintf(LOG_ERR, "too many object in register mode\n\r");
		return 0;
	}

	if (ctx->mode == FRC_RECOGNITION) {
		int face_id = -1;

		// fill draw context
		face_feature_res_t *ff_res = (face_feature_res_t *)&last_out->res[0];
		for (int i = 0; i < ff_cnt; i++) {
			if (ctx->face_data.reg_feature_num != 0) {
				face_id = search_face_identity(ctx, &ff_res[i], ctx->params.sim_thres);
				dprintf(LOG_MSG, "--------> %s\n\r", face_id >= 0 ? ctx->face_data.reg_name[face_id] : "unknown");
			} else {
				dprintf(LOG_MSG, "--------> no registered face data\n\r");
			}
			// fix draw context
			ctx->draw_ctx.obj_name[i] = face_id >= 0 ? ctx->face_data.reg_name[face_id] : (char *)"unknown";
			//ctx->draw_ctx.img_param[i] = &last_out->input_param;
			memcpy(&ctx->draw_ctx.bbox[i], &ff_res[i].result[2], sizeof(frc_bbox_t));
			//dprintf(LOG_MSG, "%f %f %f %f", ff_res[i].result[2], ff_res[i].result[3], ff_res[i].result[4], ff_res[i].result[5]);
		}

		// origin image width and height
		ctx->draw_ctx.pic_width = last_out->input_param->img.width;
		ctx->draw_ctx.pic_height = last_out->input_param->img.height;

		ctx->draw_ctx.obj_cnt = ff_cnt;
		if (ctx->draw) {
			ctx->draw(&ctx->draw_ctx, NULL);
		}
	} else if (ctx->mode == FRC_REGISTER) {
		face_feature_res_t *ff_res = (face_feature_res_t *)&last_out->res[0];
		if (ctx->face_data.reg_feature_num >= MAX_FRC_REG_NUM) {
			dprintf(LOG_ERR, "register fail, out of face feature space\n\r");
		} else {
			memcpy(&ctx->face_data.reg_feature[ctx->face_data.reg_feature_num].feature, ff_res[0].feature, sizeof(ff_res->feature));
			strncpy(ctx->face_data.reg_name[ctx->face_data.reg_feature_num], ctx->tmp_reg_name, 31);
			ctx->face_data.reg_feature_num++;
		}
		ctx->mode = FRC_RECOGNITION;
	} else if (ctx->mode == FRC_UNREGISTER) {
		for (int i = 0; i < (ctx->face_data.reg_feature_num); i++) {
			if (strncmp((ctx->face_data.reg_name[i]), (ctx->tmp_reg_name), 31) == 0) {
				ctx->face_data.reg_feature_num--;
				for (int j = i; j < (ctx->face_data.reg_feature_num); j++) {
					memcpy(&ctx->face_data.reg_feature[j].feature, &ctx->face_data.reg_feature[(j + 1)].feature, sizeof(face_feature_res_t));
					strncpy(ctx->face_data.reg_name[j], ctx->face_data.reg_name[j + 1], 31);
				}
				break;
			}
		}
		ctx->mode = FRC_RECOGNITION;
	}

	return 0;
}



// load feature file or read from flash position
static void facerecog_load_feature(void *p)
{
	frc_ctx_t *ctx = (frc_ctx_t *)p;

	// if file, open file and read to reg_feature_num/reg_feature
	// format
	// _0____1____2____3____4__....____F___
	//  reg_feature_num   |   reg_feature array(size = MAX_FRC_REG_NUM*(MAX_FACE_FEATURE_DIM*sizeof(float)+128))

	uint8_t *buf = (uint8_t *)&ctx->face_data;

	int ret = ftl_common_read(FACE_FEATURE_DATA, buf, sizeof(face_data_t));
	if (ret < 0) {
		printf("[%s] ftl read failed\n\r", __func__);
		return;
	}
	/*
	void *fp = pfw_open("UDATA", M_RAW);
	if (!fp) {
		dprintf(LOG_ERR, "cannot open UDATA\n\r");
		return;
	}
	pfw_read(fp, buf, sizeof(face_data_t));
	pfw_close(fp);
	*/

	face_data_t *ff = (face_data_t *)buf;

	// check crc32
	uint32_t crc32_tmp;
	device_mutex_lock(RT_DEV_LOCK_CRYPTO);
	crypto_crc32_cmd(buf, sizeof(face_data_t) - sizeof(uint32_t), &crc32_tmp);
	device_mutex_unlock(RT_DEV_LOCK_CRYPTO);
	if (ff->crc32 != crc32_tmp) {
		printf("[%s] invalid content\n\r", __func__);
		ff->reg_feature_num = 0;
		return;
	}

	dprintf(LOG_INF, "Face feature %d\n\r", ff->reg_feature_num);
	for (int i = 0; i < ff->reg_feature_num; i++) {
		dprintf(LOG_INF, "%d : %s -", i, ff->reg_name[i]);
		for (int x = 0; x < MAX_FACE_FEATURE_DIM; x++) {
			dprintf(LOG_INF, "%02.1f", ff->reg_feature[i].result[x]);
		}
		dprintf(LOG_INF, "\n\r");
	}
}

static void facerecog_save_feature(void *p)
{
	frc_ctx_t *ctx = (frc_ctx_t *)p;

	uint8_t *buf = (uint8_t *)&ctx->face_data;

	face_data_t *ff = (face_data_t *)buf;
	dprintf(LOG_INF, "Face feature %d\n\r", ff->reg_feature_num);
	for (int i = 0; i < ff->reg_feature_num; i++) {
		dprintf(LOG_INF, "%d : %s -", i, ff->reg_name[i]);
		for (int x = 0; x < MAX_FACE_FEATURE_DIM; x++) {
			dprintf(LOG_INF, "%02.1f", ff->reg_feature[i].result[x]);
		}
		dprintf(LOG_INF, "\n\r");
	}

	// calculate crc32 before saving
	device_mutex_lock(RT_DEV_LOCK_CRYPTO);
	crypto_crc32_cmd(buf, sizeof(face_data_t) - sizeof(uint32_t), &ff->crc32);
	device_mutex_unlock(RT_DEV_LOCK_CRYPTO);

	int ret = ftl_common_write(FACE_FEATURE_DATA, buf, sizeof(face_data_t));
	if (ret < 0) {
		printf("[%s] ftl write failed\n\r", __func__);
	}
	/*
	void *fp = pfw_open("UDATA", M_RAW | M_CREATE);
	if (!fp) {
		dprintf(LOG_ERR, "cannot open UDATA\n\r");
		return;
	}
	pfw_write(fp, buf, sizeof(face_data_t));
	pfw_close(fp);
	*/
}


static void facerecog_reset_feature(void *p)
{
	frc_ctx_t *ctx = (frc_ctx_t *)p;
	ctx->face_data.reg_feature_num = 0;
}

int facerecog_control(void *p, int cmd, int arg)
{
	frc_ctx_t *ctx = (frc_ctx_t *)p;

	switch (cmd) {
	case CMD_FRC_SET_PARAMS:
		memcpy(&ctx->params, (void *)arg, sizeof(frc_param_t));
		break;
	case CMD_FRC_SET_THRES100:
		ctx->params.sim_thres = (float)arg / 100.0;
		break;
	case CMD_FRC_SET_OSD_DRAW:
		ctx->draw = (draw_func_t)arg;
		break;

	case CMD_FRC_REGISTER_MODE:
		ctx->mode = FRC_REGISTER;
		if (arg) {
			strncpy(ctx->tmp_reg_name, (char *)arg, 31);
			dprintf(LOG_INF, "reg mode %d, reg name %s\n\r", ctx->mode, ctx->tmp_reg_name);
		} else {
			dprintf(LOG_INF, "reg mode %d\n\r", ctx->mode);
		}
		break;
	case CMD_FRC_RECOGNITION_MODE:
		ctx->mode = FRC_RECOGNITION;
		dprintf(LOG_INF, "rec mode %d\n\r", ctx->mode);
		break;
	case CMD_FRC_UNREGISTER_MODE:
		ctx->mode = FRC_UNREGISTER;
		if (arg) {
			strncpy(ctx->tmp_reg_name, (char *)arg, 31);
			dprintf(LOG_INF, "reg mode %d, reg name %s\n\r", ctx->mode, ctx->tmp_reg_name);
		} else {
			dprintf(LOG_INF, "reg mode %d\n\r", ctx->mode);
		}
		break;
	case CMD_FRC_LOAD_FEATURES:
		facerecog_load_feature(p);
		break;
	case CMD_FRC_SAVE_FEATURES:
		facerecog_save_feature(p);
		break;
	case CMD_FRC_RESET_FEATURES:
		facerecog_reset_feature(p);
		break;
	}

	return 0;
}

void *facerecog_destroy(void *p)
{
	frc_ctx_t *ctx = (frc_ctx_t *)p;

	if (ctx) {
		free(ctx);
	}

	return NULL;
}

void *facerecog_create(void *parent)
{
	frc_ctx_t *ctx = (frc_ctx_t *)malloc(sizeof(frc_ctx_t));

	if (!ctx) {
		return NULL;
	}
	memset(ctx, 0, sizeof(frc_ctx_t));

	device_mutex_lock(RT_DEV_LOCK_CRYPTO);
	crypto_init();
	device_mutex_unlock(RT_DEV_LOCK_CRYPTO);

	NN_MEASURE_INIT(0);
	NN_MEASURE_INIT(1);
	NN_MEASURE_INIT(2);
	NN_MEASURE_INIT(3);
	NN_MEASURE_INIT(4);

	return ctx;
}

/*
 * example1, create module => control(load feature)
 * example2, create module => register mode => save feature => switch to recognition mode
 *
 */


mm_module_t facerecog_module = {
	.create = facerecog_create,
	.destroy = facerecog_destroy,
	.control = facerecog_control,
	.handle = facerecog_handle,

	.output_type = MM_TYPE_NONE,
	.module_type = MM_TYPE_VDSP,
	.name = "facerecog"
};
