#include "eip_auto_wdr.h"
#include "isp_ctrl_api.h"
#include "task.h"
static char AutoWDR_version[] = "AutoWDR_v1.1";

void eip_auto_wdr_get_version(void)
{
	printf("[AutoWDR] %s\r\n", AutoWDR_version);
}

void eip_auto_wdr_show_info(eip_auto_wdr_t *auto_wdr)
{
	printf("[AutoWDR] %s\r\n", AutoWDR_version);
	int i;
	if (auto_wdr->statis_info) {
		for (i = 0; i < HISTOGRAM_COUNT; i++) {
			printf("<%3d", i << 4);
		}
		printf("\r\n");
		for (i = 0; i < HISTOGRAM_COUNT; i++) {
			printf("%4d", auto_wdr->statis_info->histogram[i]);
		}
		printf("\r\n");
	}
	printf("[AutoWDR] wdr_level=%d sat_level=%d status=%d, wdr_weight=%d\r\n", auto_wdr->wdr_cur_level, auto_wdr->sat_level, auto_wdr->wdr_status,
		   auto_wdr->wdr_weight);

}

void eip_auto_wdr_task(void *param)
{
	int i;
	eip_auto_wdr_t *auto_wdr = (eip_auto_wdr_t *) param;
	eip_auto_wdr_config_t *auto_wdr_config = &(auto_wdr->wdr_config);
	while (!auto_wdr->task_stop_flag) {

		auto_wdr->wdr_weight = (auto_wdr->statis_info->histogram[0] << 3) + (auto_wdr->statis_info->histogram[1] << 2) + auto_wdr->statis_info->histogram[2]
							   + auto_wdr->statis_info->histogram[13] + auto_wdr->statis_info->histogram[14] + auto_wdr->statis_info->histogram[15];

		if (auto_wdr->wdr_weight >= auto_wdr_config->wdr_weight_thr1) {
			auto_wdr->wdr_status = 3;
		} else if (auto_wdr->wdr_weight >= auto_wdr_config->wdr_weight_thr2) {
			auto_wdr->wdr_status = 2;
		} else if (auto_wdr->wdr_weight >= auto_wdr_config->wdr_weight_thr3) {
			auto_wdr->wdr_status = 1;
		} else {
			auto_wdr->wdr_status = 0;
		}

		//adjust wdr level
		if ((auto_wdr->wdr_status >= 2) && (auto_wdr->statis_info->histogram[0] >= 0)) {
			auto_wdr->wdr_target_level += 2;
			if (auto_wdr->wdr_target_level > auto_wdr_config->wdr_max_level) {
				auto_wdr->wdr_target_level = auto_wdr_config->wdr_max_level;
			}
		}
		if (auto_wdr->wdr_status == 0) {
			auto_wdr->wdr_target_level -= 1;
			if (auto_wdr->wdr_target_level < auto_wdr_config->wdr_min_level) {
				auto_wdr->wdr_target_level = auto_wdr_config->wdr_min_level;
			}
		}
		if (auto_wdr->wdr_cur_level != auto_wdr->wdr_target_level) {
			isp_set_wdr_level(auto_wdr->wdr_target_level);
			auto_wdr->sat_level = (auto_wdr->wdr_target_level - 50) >> 2;
			isp_set_saturation(50 - auto_wdr->sat_level);
		}
		auto_wdr->wdr_cur_level = auto_wdr->wdr_target_level;

		vTaskDelay(auto_wdr_config->wdr_duration);
	}

	auto_wdr->statis_info = NULL;
	xSemaphoreGive(auto_wdr->task_stop_sema);

	vTaskDelete(NULL);
}


void eip_auto_wdr_task_start(eip_statis_infor_t *statis_info, eip_auto_wdr_t *auto_wdr)
{
	if (!auto_wdr->task_stop_flag) {
		printf("[EIP] auto wdr task already start\r\n");
		return;
	}

	auto_wdr->wdr_status = 1;
	auto_wdr->wdr_cur_level = 50;
	auto_wdr->wdr_target_level = 50;
	auto_wdr->sat_level = 0;
	auto_wdr->statis_info = statis_info;
	auto_wdr->task_stop_flag = 0;
	auto_wdr->task_stop_sema = xSemaphoreCreateBinary();
	if (auto_wdr->task_stop_sema == NULL) {
		printf("%s: eip_auto_wdr_task_stop_sema create fail \r\n", __FUNCTION__);
		return;
	}

	if (xTaskCreate(eip_auto_wdr_task, ((const char *)"eip_auto_wdr_task"), 1024, auto_wdr, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
		printf("[EIP] auto wdr task create failed\r\n");
		return;
	}
	printf("[EIP] auto wdr task start success\r\n");
}

void eip_auto_wdr_task_stop(eip_auto_wdr_t *auto_wdr)
{
	if (!auto_wdr->task_stop_flag) {
		auto_wdr->task_stop_flag = 1;
	} else {
		printf("eip_auto_wdr_task already closing.\r\n");
		return;
	}

	if (xSemaphoreTake(auto_wdr->task_stop_sema, portMAX_DELAY) == pdTRUE) {
		printf("[EIP] eip_auto_wdr_task close success\r\n");
		vSemaphoreDelete(auto_wdr->task_stop_sema);
		auto_wdr->task_stop_sema = NULL;
		return;
	}
	return;
}
