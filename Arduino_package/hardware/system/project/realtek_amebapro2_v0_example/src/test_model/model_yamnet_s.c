//------------------------------------------------------
// yamnet from
//------------------------------------------------------
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "mmf2_module.h"
#include "module_vipnn.h"
#include "hal_cache.h"
#include "sys_api.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "svm.h"

void *yamnet_s_get_network_filename(void)
{
	return (void *)"NN_MDL/yamnet_s_hybrid.nb";	// fix name for NN model binary
}

#define MEAN_COUNT	  20
static short *src_temp = NULL;
static int src_temp_cnt = 0;
static int input_cnt = 0;
static int overlap_cnt = -1;
static void *class_score = NULL;
static int total_samples = 0;

#define INPUT_REQUEST_CNT 15600
static float input[INPUT_REQUEST_CNT];

#include "mel_spectrogram.h"
mel_spectrogram_t *pMelspectrogram = NULL;

typedef struct data_format_s {
	nn_tensor_format_t *format;
	nn_tensor_dim_t *dim;
} data_format_t;

void yamnet_s16_to_f32_copy(float *dst, short *src, int cnt)
{
	// short -> [-1.0, 1.0]
	for (int i = 0; i < cnt; i++) {
		dst[i] = (float)src[i] / 32768.0;
	}
}

void yamnet_f32_to_f16_copy(__fp16 *dst, float *src, int cnt)
{
	for (int i = 0; i < cnt; i++) {
		dst[i] = (__fp16)src[i];
	}
}

static uint8_t f_to_u8(float val, uint8_t zero_p, float scale)
{
	return (uint8_t)(val / scale) + zero_p;
}

static int16_t f_to_s16(float val, int q)
{
	return (int16_t)(val * (1 << q));
}

void yamnet_f32_to_u8_copy(uint8_t *dst, float *src, int cnt, uint8_t zero_p, float scale)
{
	for (int i = 0; i < cnt; i++) {
		dst[i] = f_to_u8(src[i], zero_p, scale);
	}
}

void yamnet_f32_to_s16_copy(int16_t *dst, float *src, int cnt, int p)
{
	for (int i = 0; i < cnt; i++) {
		dst[i] = f_to_s16(src[i], p);
	}
}

int yamnet_s_preprocess(void *data_in, nn_data_param_t *data_param, void *tensor_in, nn_tensor_param_t *tensor_param)
{
	void **tensor = (void **)tensor_in;		// spetrum 64*96
	data_format_t fmt;

	short *src = (short *)data_in;
	fmt.format = &tensor_param->format[0];
	int src_sample_cnt = data_param->size_in_byte / (data_param->aud.bit_pre_sample / 8);

	//printf("in %d, level %d\n\r", src_sample_cnt, tensor_in_cnt);

	__fp16(*spetrum)[64]   = (__fp16(*)[64])tensor[0];
	uint8_t(*spetrum_u8)[64]   = (uint8_t(*)[64])tensor[0];
	int16_t(*spetrum_s16)[64]   = (int16_t(*)[64])tensor[0];
	int input_require_cnt = INPUT_REQUEST_CNT;

	if (overlap_cnt < 0) {
		overlap_cnt = (16000 * 0.975) - (16000 * 0.48);
		memset(input, 0, input_require_cnt * sizeof(float));
	}

	if (input_cnt == 0) {
		// copy overlap count from tail to head
		memmove(input, &input[input_require_cnt - overlap_cnt], overlap_cnt * sizeof(float));
		input_cnt = overlap_cnt;
	}

	if (!src_temp) {
		src_temp = (short *)malloc(src_sample_cnt * sizeof(short));
		if (!src_temp) {
			printf("yamnet : out of resource, size %d\n\r", src_sample_cnt * sizeof(short));
		}
	}

	int proc_size = (input_require_cnt - input_cnt) > src_sample_cnt ? src_sample_cnt : (input_require_cnt - input_cnt);

	if (src_temp_cnt) {
		//memcpy(&input[input_cnt], src_tmp, src_temp_cnt*sizeof(short));
		yamnet_s16_to_f32_copy(&input[input_cnt], src_temp, src_temp_cnt);
		input_cnt += src_temp_cnt;
		src_temp_cnt = 0;
	}

	yamnet_s16_to_f32_copy(&input[input_cnt], src, proc_size);
	//memcpy(&input[input_cnt], src, proc_size*sizeof(short));
	input_cnt += proc_size;

	if (input_cnt == input_require_cnt) {
		src_temp_cnt = src_sample_cnt - proc_size;
		if (src_temp && src_temp_cnt > 0) {
			memcpy(src_temp, &src[proc_size], src_temp_cnt * sizeof(short));
		}
		// calculate spetrum
		if (pMelspectrogram == NULL) {
			pMelspectrogram = mel_spec_create(MEL_FILTER_BIN, WINDOW_SIZE);
		}
		for (int i = 0; i < 96; i++) {
			mel_compute(pMelspectrogram, &input[HOP_SIZE * i]);
			if (fmt.format->type == VIP_BUFFER_QUANTIZE_NONE) {
				yamnet_f32_to_f16_copy(&spetrum[i][0], &pMelspectrogram->mel_energies[0], MEL_FILTER_BIN);
			} else if (fmt.format->type == VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT) {
				yamnet_f32_to_s16_copy(&spetrum_s16[i][0], &pMelspectrogram->mel_energies[0], MEL_FILTER_BIN, fmt.format->fix_point_pos);
			} else if (fmt.format->type == VIP_BUFFER_QUANTIZE_TF_ASYMM) {
				yamnet_f32_to_u8_copy(&spetrum_u8[i][0], &pMelspectrogram->mel_energies[0], MEL_FILTER_BIN, fmt.format->zero_point, fmt.format->scale);
			}
		}

		// may have alignment issue
		if (fmt.format->type == VIP_BUFFER_QUANTIZE_NONE) {
			dcache_clean_by_addr((uint32_t *)spetrum, 96 * MEL_FILTER_BIN * sizeof(__fp16));
		} else if (fmt.format->type == VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT) {
			dcache_clean_by_addr((uint32_t *)spetrum_s16, 96 * MEL_FILTER_BIN * sizeof(int16_t));
		} else if (fmt.format->type == VIP_BUFFER_QUANTIZE_TF_ASYMM) {
			dcache_clean_by_addr((uint32_t *)spetrum_u8, 96 * MEL_FILTER_BIN * sizeof(uint8_t));
		}
		input_cnt = 0;
		return PP_USE_RESULT;	// DO inference
	}


	return PP_SKIP_INF;	// SKIP,
}

#define CLASS_CNT 3
const char *sndcls_name[CLASS_CNT] = {"CO", "Background", "Smoke"};
enum {
	SNDCLS_CO = 0,
	SNDCLS_BACKGROUND = 1,
	SNDCLS_SMOKE = 2
};
#define ALARM_OCCURRENCE_THRESHOLD 	(5)
#define ALARM_SCORE_THRESHOLD 		(0.5)

//arm_max_f16()
static int argmax_fp16(float *array, int count)
{
	float tmp = 0.0;
	int index = 0;
	for (int i = 0; i < count ; i++) {
		if (array[i] > tmp) {
			tmp = array[i];
			index = i;
		}
	}
	return index;
}

static void dump_prob(float *prob, int count)
{
	for (int i = 0; i < count; i++) {
		printf("%f ", prob[i]);
	}
	printf("\r\n");
}

static int prob_comparator(const void *pa, const void *pb)
{
	yamnet_res_t *a = (yamnet_res_t *)pa;
	yamnet_res_t *b = (yamnet_res_t *)pb;
	float diff = a->prob - b->prob;
	if (diff < 0) {
		return 1;
	} else if (diff > 0) {
		return -1;
	}
	return 0;
}

static float final_scores[3];
static void compute_final_scores(float *weights)
{
	float sum = 0.0;
	for (int i = 0; i < CLASS_CNT; i++) {
		weights[i] = exp(weights[i]);
		sum += weights[i];
	}

	for (int i = 0; i < CLASS_CNT; i++) {
		weights[i] /= sum;
		final_scores[i] = weights[i];
	}
}

static int evaluate_by_score_filter(float(*cscore)[CLASS_CNT], int sample_num)
{
	/*
	    Reduce false alarms by score filter.
	    Customers can adjust ALARM_SCORE_THRESHOLD and ALARM_OCCURRENCE_THRESHOLD according to requirements and test results.
	*/
	int i = 0, alarm_count = 0;
	float weights[CLASS_CNT] = {0.0};
	float scores[ALARM_OCCURRENCE_THRESHOLD][CLASS_CNT] = {{0.0}};

	for (i = 0; i < ALARM_OCCURRENCE_THRESHOLD; i++) {
		scores[i][SNDCLS_CO] = 0.000001;
		scores[i][SNDCLS_BACKGROUND] = (i == ALARM_OCCURRENCE_THRESHOLD - 1) ? (float)(i * 0.999999) : (float)(ALARM_OCCURRENCE_THRESHOLD - i);
		scores[i][SNDCLS_SMOKE] = 0.000001;
	}

#if 0 //debug
	for (i = 0; i < sample_num; i++) {
		dump_prob(cscore[i], CLASS_CNT);
	}
#endif

	for (i = 0; i < sample_num && alarm_count < ALARM_OCCURRENCE_THRESHOLD; i++) {
		if (cscore[i][SNDCLS_CO] < ALARM_SCORE_THRESHOLD && cscore[i][SNDCLS_SMOKE] < ALARM_SCORE_THRESHOLD) {
			continue;
		}
		scores[alarm_count][SNDCLS_CO] = cscore[i][SNDCLS_CO];
		scores[alarm_count][SNDCLS_BACKGROUND] = cscore[i][SNDCLS_BACKGROUND];
		scores[alarm_count][SNDCLS_SMOKE] = cscore[i][SNDCLS_SMOKE];
		alarm_count++;
	}

	for (i = 0; i < ALARM_OCCURRENCE_THRESHOLD; i++) {
		weights[SNDCLS_CO] += scores[i][SNDCLS_CO];
		weights[SNDCLS_BACKGROUND] += scores[i][SNDCLS_BACKGROUND];
		weights[SNDCLS_SMOKE] += scores[i][SNDCLS_SMOKE];
	}

	compute_final_scores(weights);
	if (argmax_fp16(weights, CLASS_CNT) == SNDCLS_BACKGROUND) {
		return SNDCLS_BACKGROUND;    //False alarm
	} else {
		return -1;    //Pass to next evaluator
	}
}


static float sigmoid(float x)
{
	return 1 / (1 + exp(-x));
}

#define MIN_BG_PERIOD (6)
#define MAX_BG_PERIOD (10)
static void heuristic_final_scores(int background_period, float *weights, float(*cscore)[CLASS_CNT], int sample_num)
{
	weights[SNDCLS_CO] = (float) background_period;
	int i;
	for (i = 0; i < sample_num; i++) {
		weights[SNDCLS_CO] += cscore[i][SNDCLS_CO];
	}

	final_scores[SNDCLS_CO] = weights[SNDCLS_CO] = sigmoid(weights[SNDCLS_CO] / (float)MIN_BG_PERIOD);
	final_scores[SNDCLS_SMOKE] = weights[SNDCLS_SMOKE] = 1.0 - weights[SNDCLS_CO];
	final_scores[SNDCLS_BACKGROUND] = weights[SNDCLS_BACKGROUND] = 0.0;
}

static int evaluate_by_heuristic_v3(float(*cscore)[CLASS_CNT], int sample_num)
{
	/*
	    Find T4 CO pattern by heuristic algorithm.
	    T4 stands for Temporal-Four Audio alarm sounds.
	    It consists of 4 short beeps in sequence followed by a pause of about 5 seconds before the next beep.
	    The time of pause may decrease due to the heavy echo of space, so we set the period from 6 to 10.
	*/
	int i = 0, background_period = 0, alarm_start = -1;
	float weights[CLASS_CNT] = {0.0};
	for (i = 0; i < sample_num; i++) {
		//dump_prob(cscore[i], CLASS_CNT);
		int clsidx = argmax_fp16(cscore[i], CLASS_CNT);
		if (clsidx != SNDCLS_BACKGROUND) {
			if (background_period >= MIN_BG_PERIOD) {
				heuristic_final_scores(background_period, weights, cscore, sample_num);
				if (argmax_fp16(weights, CLASS_CNT) == SNDCLS_CO) {
					return SNDCLS_CO;
				} else {
					return -1;    //Pass to next evaluator
				}
			} else {
				background_period = 0;
				alarm_start = i;
			}
		} else {
			if (alarm_start >= 0) {
				background_period = i - alarm_start;
				if (background_period > MAX_BG_PERIOD) {
					return -1; //Pass to next evaluator
				}
			}
		}
	}

	return -1; //Pass to next evaluator
}


#define SVM_SEQ_SIZE        (16) //DO NOT CHANGE
#define SVM_MAX_INPUT_SIZE  (512)
static char *scores_to_svm_sequence(float(*cscore)[CLASS_CNT], int sample_num)
{
	int i = 0, seq_start = 0, sp = 0;
	int seq[SVM_SEQ_SIZE] = {0};
	memset(seq, SNDCLS_BACKGROUND, SVM_SEQ_SIZE * sizeof(int));
	for (i = 0; i < sample_num && sp < SVM_SEQ_SIZE; i++) {
		int clsidx = argmax_fp16(cscore[i], CLASS_CNT);
		if (seq_start == 0 && clsidx != SNDCLS_BACKGROUND) {
			seq[sp++] = clsidx;
			seq_start = 1;
		} else if (seq_start == 1) {
			seq[sp++] = clsidx;
		}
	}

#if 0
	printf("sequence: ");
	for (i = 0; i < SVM_SEQ_SIZE; i++) {
		printf("%d ", seq[i]);
	}
	printf("\r\n");
#endif

	char *svminput = (char *) malloc(SVM_MAX_INPUT_SIZE);
	if (svminput == NULL) {
		printf("Failed to malloc svminput!\r\n");
		return NULL;
	}
	memset(svminput, 0x0, SVM_MAX_INPUT_SIZE);
	int cnt = 0;
	cnt += snprintf(svminput + cnt, SVM_MAX_INPUT_SIZE - cnt - 1, "0 ");
	for (sp = 0; sp < SVM_SEQ_SIZE; sp++) {
		switch (seq[sp]) {
		case 2:
		case 0:
			cnt += snprintf(svminput + cnt, SVM_MAX_INPUT_SIZE - cnt - 1, "%d:%d ", sp + 1, (seq[0] == 0) ? 1 : 2);
			break;
		default:
			break;
		}
	}
	cnt += snprintf(svminput + cnt, SVM_MAX_INPUT_SIZE - cnt - 1, "\n");

	//printf("svminput: %s\r\n", svminput);

	return svminput;
}


static struct svm_model *p_svm_model = NULL;
static struct svm_node *p_svm_node = NULL;
static const int max_nr_attr = 32;
static const double svm_max = 1.967951;  // determined by svm model
static const double svm_min = -1.967951; // determined by svm model
#define exit_input_error(line_num) do { printf("SVM: wrong input format at line %d\n", line_num); return 100.0; } while(0)

static float svm_predict_seq(char *line)
{
	int total = 0;
	int i = 0;
	double target_label, predict_label;
	char *idx, *val, *label, *endptr;
	int inst_max_index = -1; // strtol gives 0 if wrong format, and precomputed kernel has <index> start from 0

	label = strtok(line, " \t\n");
	if (label == NULL) { // empty line
		exit_input_error(total + 1);
	}

	target_label = strtol(label, &endptr, 10);
	if (endptr == label || *endptr != '\0') {
		exit_input_error(total + 1);
	}

	while (1) {
		if (i >= max_nr_attr - 1) {
			break;
		}

		idx = strtok(NULL, ":");
		val = strtok(NULL, " \t");

		if (val == NULL) {
			break;
		}
		p_svm_node[i].index = (int) strtol(idx, &endptr, 10);
		if (endptr == idx || *endptr != '\0' || p_svm_node[i].index <= inst_max_index) {
			exit_input_error(total + 1);
		} else {
			inst_max_index = p_svm_node[i].index;
		}

		p_svm_node[i].value = strtod(val, &endptr);
		if (endptr == val || (*endptr != '\0' && !isspace((int)*endptr))) {
			exit_input_error(total + 1);
		}

		++i;
	}
	p_svm_node[i].index = -1;

	double dec_value;
	svm_predict_values(p_svm_model, p_svm_node, &dec_value);
	if (dec_value > svm_max) {
		dec_value = svm_max;
	} else if (dec_value < svm_min) {
		dec_value = svm_min;
	}
	//printf("dec_value: %f\r\n", (float) dec_value);
	float svm_score = (float)(dec_value - svm_min) / (float)(svm_max - svm_min);
	//printf("svm_score: %f\r\n", svm_score);
	return (float) svm_score;
}

static void sum_weights(float *weights, float(*cscore)[CLASS_CNT], int sample_num)
{
	int i;
	for (i = 0; i < sample_num; i++) {
		if (argmax_fp16(cscore[i], CLASS_CNT) != SNDCLS_BACKGROUND) {
			weights[SNDCLS_CO] += cscore[i][SNDCLS_CO];
			weights[SNDCLS_BACKGROUND] += cscore[i][SNDCLS_BACKGROUND];
			weights[SNDCLS_SMOKE] += cscore[i][SNDCLS_SMOKE];
		}
	}
}

static int evaluate_by_svm(float(*cscore)[CLASS_CNT], int sample_num)
{
	/*
	    Find CO pattern by SVM model
	*/
	if (p_svm_model == NULL) {
		p_svm_model = svm_load_model("svm_model");
		if (p_svm_model == NULL) {
			printf("can't open model file\n");
			return -1;
		}
	}

	if (p_svm_node == NULL) {
		p_svm_node = (struct svm_node *) malloc(max_nr_attr * sizeof(struct svm_node));
		if (p_svm_node == NULL) {
			printf("can't malloc svm node\n");
			return -1;
		}
	}

	char *seq = scores_to_svm_sequence(cscore, sample_num);
	if (seq == NULL) {
		return -1;
	}

	float svm_score = svm_predict_seq(seq);
	free(seq);

	if (svm_score > 1.0) {
		printf("svm_predict_seq failed\r\n");
		return -1;
	}

	float weights[CLASS_CNT] = {0.0};
	sum_weights(weights, cscore, sample_num);
	float alarm_weights = weights[SNDCLS_CO] + weights[SNDCLS_SMOKE];
	weights[SNDCLS_CO] = svm_score * alarm_weights;
	weights[SNDCLS_SMOKE] = (1.0 - svm_score) * alarm_weights;
	compute_final_scores(weights);
	if (argmax_fp16(weights, CLASS_CNT) == SNDCLS_CO) {
		return SNDCLS_CO;
	} else {
		return -1;    //Pass to next evaluator
	}

	//We dodn't free svm model data
	//svm_free_and_destroy_model(&p_svm_model);
	//free(p_svm_node);
}

static int evaluate_by_score_sum(float(*cscore)[CLASS_CNT], int sample_num)
{
	/*
	    Determine alarm type by the weights.
	*/
	float weights[CLASS_CNT] = {0.0};
	sum_weights(weights, cscore, sample_num);
	compute_final_scores(weights);
	return argmax_fp16(weights, CLASS_CNT);
}


static float s16_to_f(int16_t val, int q)
{
	return (float)val / (float)(1 << q);
}

static void data_s16_to_fp32_copy(float *dst, int16_t *src, int count, int fix_point_pos)
{
	for (int i = 0; i < count; i++) {
		dst[i] = s16_to_f(src[i], fix_point_pos);
	}
}

int yamnet_s_postprocess(void *tensor_out, nn_tensor_param_t *param, void *res)
{
	void **tensor = (void **)tensor_out;
	float prob[CLASS_CNT] = {0};

	(void)res;

	data_format_t fmt;
	fmt.format = &param->format[0];
	fmt.dim = &param->dim[0];
	int class_cnt = fmt.dim->size[0];

	if (class_cnt != CLASS_CNT) {
		printf("extra class in this model\n\r");
		class_cnt = CLASS_CNT;
	}

	if (class_score == NULL) {
		class_score = malloc(MEAN_COUNT * sizeof(float) * class_cnt);
		if (!class_score) {
			printf("postprocess : out of resource\n\r");
			return 0;
		}
		memset(class_score, 0, MEAN_COUNT * sizeof(float)*class_cnt);
	}

	if (fmt.format->type == VIP_BUFFER_QUANTIZE_NONE) {
		__fp16 *data_fp16 = (__fp16 *)tensor[0];
		for (int i = 0; i < class_cnt; i++) {
			prob[i] = (float) data_fp16[i];
		}
	} else if (fmt.format->type == VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT) {
		int16_t *data_s16 = (int16_t *)tensor[0];
		data_s16_to_fp32_copy(prob, data_s16, class_cnt, fmt.format->fix_point_pos);
	}

	if ((float)prob[SNDCLS_BACKGROUND] > 0.5 && total_samples == 0) {
		//Nothing detected yet
		return 0;
	}

	//Okay.. We got something, let's check it out...
	float(*cscore)[CLASS_CNT] = (float(*)[CLASS_CNT])class_score;
	memcpy(cscore[total_samples++], prob, sizeof(float)*class_cnt);

	/*
	    We implement four evaluators to detect Smoke/CO alarm:
	    evaluate_by_score_filter(): Filter false alarms. we recommend applying this evaluator at the beginning to filter false alarms.
	                                Customers can adjust ALARM_SCORE_THRESHOLD and ALARM_OCCURRENCE_THRESHOLD according to requirements and test results.
	    evaluate_by_heuristic_v3(): Detect T4 CO alarm pattern by heuristic algorithm.
	    evaluate_by_svm(): Detect T4 CO alarm pattern by SVM model. Customers can use evaluate_by_heuristic_v3() and evaluate_by_svm() both, or one of them.
	    evaluate_by_score_sum(): The final evaluator to determine alarm type by the sum of scores.

	    compute_final_scores() and heuristic_final_scores() output the final scores.
	 */

	if (total_samples >= MEAN_COUNT) {
		int detect_classid = SNDCLS_BACKGROUND;
		do {
			detect_classid = evaluate_by_score_filter(cscore, total_samples);
			if (detect_classid >= 0)  {
				printf("evaluate_by_score_filter: ");
				break;
			}

			detect_classid = evaluate_by_heuristic_v3(cscore, total_samples);
			if (detect_classid >= 0) {
				printf("evaluate_by_heuristic_v3: ");
				break;
			}

			detect_classid = evaluate_by_svm(cscore, total_samples);
			if (detect_classid >= 0) {
				printf("evaluate_by_svm: ");
				break;
			}

			detect_classid = evaluate_by_score_sum(cscore, total_samples);
			printf("evaluate_by_score_sum: ");
		} while (0);

		if (detect_classid != SNDCLS_BACKGROUND) {
			printf("[%s] alarm detected! score: %f\r\n", sndcls_name[detect_classid], final_scores[detect_classid]);
		} else {
			printf("false alarm detected! score: %f\r\n", final_scores[detect_classid]);
		}
		total_samples = 0;
		return 0;
	}

	return 0;
}


nnmodel_t yamnet_s = {
	.nb 			= yamnet_s_get_network_filename,
	.preprocess 	= yamnet_s_preprocess,
	.postprocess 	= yamnet_s_postprocess,
	.model_src 		= MODEL_SRC_FILE,

	.name = "YAMNET_S"
};
