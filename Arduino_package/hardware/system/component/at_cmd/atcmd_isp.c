#include <platform_stdlib.h>
#include <platform_opts.h>
#include <build_info.h>
#include "log_service.h"
#include "atcmd_isp.h"
#include "main.h"
#include "flash_api.h"
#include "hal_osd_util.h"
#include "hal_md_util.h"
#include "hal_video.h"
#include "osd/osd_custom.h"
#include "osd/osd_api.h"
#include "video_api.h"
#include "isp_api.h"

#include "isp_ctrl_api.h"
#include "module_video.h"
#include "../../usb/usb_class/device/class/uvc/tuning-server.h"

#define ENABLE_OSD_CMD      0
#define ENABLE_AE_METER_CMD 0

//-------- AT SYS commands ---------------------------------------------------------------
#define CMD_DATA_SIZE 65536

void fATIT(void *arg)
{
	int i;
	int ccmd;
	int value;
	char *cmd_data;
	struct isp_tuning_cmd *iq_cmd;
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	if (!arg) {
		return;
	}


	argc = parse_param(arg, argv);
	if (argc < 1) {	// usage
		printf("iqtun cmd\r\n");
		printf("      0: rts_isp_tuning_get_iq\n");
		printf("      1 : rts_isp_tuning_set_iq\r\n");
		printf("      2 : rts_isp_tuning_get_statis\r\n");
		printf("      3 : rts_isp_tuning_get_param\r\n");
		printf("      4 : rts_isp_tuning_set_param\r\n");
		return;
	}
	ccmd = atoi(argv[1]);

	cmd_data = malloc(CMD_DATA_SIZE);
	if (cmd_data == NULL) {
		printf("malloc cmd buf fail\r\n");
		return;
	}
	iq_cmd = (struct isp_tuning_cmd *)cmd_data;

	if (ccmd == 0) {
		iq_cmd->addr = ISP_TUNING_IQ_TABLE_ALL;
		hal_video_isp_tuning(VOE_ISP_TUNING_GET_IQ, iq_cmd);
	} else if (ccmd == 1) {
		iq_cmd->addr = ISP_TUNING_IQ_TABLE_ALL;
		hal_video_isp_tuning(VOE_ISP_TUNING_SET_IQ, iq_cmd);
	} else if (ccmd == 2) {
		iq_cmd->addr = ISP_TUNING_STATIS_ALL;
		hal_video_isp_tuning(VOE_ISP_TUNING_GET_STATIS, iq_cmd);
	} else if (ccmd == 3) {
		iq_cmd->addr = ISP_TUNING_PARAM_ALL;
		hal_video_isp_tuning(VOE_ISP_TUNING_GET_PARAM, iq_cmd);
	} else if (ccmd == 4) {
		iq_cmd->addr = ISP_TUNING_PARAM_ALL;
		hal_video_isp_tuning(VOE_ISP_TUNING_SET_PARAM, iq_cmd);
	} else if (ccmd == 11) {
		iq_cmd->addr = atoi(argv[1]);
		iq_cmd->len  = atoi(argv[2]);
		hal_video_isp_tuning(VOE_ISP_TUNING_READ_VREG, iq_cmd);
		for (i = 0; i < iq_cmd->len; i++) {
			printf("virtual reg[%d]: 0x02%X.\r\n", i, iq_cmd->data[i]);
		}
		iq_cmd->data[i] = atoi(argv[3 + i]);
	} else if (ccmd == 12) {
		iq_cmd->addr = atoi(argv[1]);
		iq_cmd->len  = atoi(argv[2]);
		for (i = 0; i < iq_cmd->len; i++) {
			iq_cmd->data[i] = atoi(argv[3 + i]);
		}
		hal_video_isp_tuning(VOE_ISP_TUNING_WRITE_VREG, iq_cmd);
	}

	if (ccmd >= 0 && ccmd <= 4) {
		vTaskDelay(300);
		printf("len = %d.\r\n", iq_cmd->len);
	}

	if (cmd_data) {
		free(cmd_data);
	}
}
void fATIC(void *arg)
{
	int i;
	int set_flag;
	int ret;
	int id;
	int set_value;
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	if (!arg) {
		return;
	}

	argc = parse_param(arg, argv);
	if (strcmp(argv[1], "help") == 0) {
		printf("Usage: ATIC=set_flag,Control-ID,value\r\n");
		printf("[set_flag  ] : set:1, get:0.\r\n");
		printf("[Control-ID] : control ID\r\n");
		printf("[value     ] : set value if set_flag=1.\r\n");
		printf("Control ID list.\r\n");
		printf("BRIGHTNESS                (0x0000) \r\n");
		printf("CONTRAST                  (0x0001) \r\n");
		printf("SATURATION                (0x0002) \r\n");
		printf("AUTO_WHITE_BALANCE        (0x000C) \r\n");
		printf("RED_BALANCE               (0x000E) \r\n");
		printf("BLUE_BALANCE              (0x000F) \r\n");
		printf("GAMMA                     (0x0010) \r\n");
		printf("EXPOSURE                  (0x0011) \r\n");
		printf("AUTOGAIN                  (0x0012) \r\n");
		printf("GAIN                      (0x0013) \r\n");
		printf("POWER_LINE_FREQUENCY      (0x0018) \r\n");
		printf("WHITE_BALANCE_TEMPERATURE (0x001A) \r\n");
		printf("SHARPNESS                 (0x001B) \r\n");
		printf("GREEN_BALANCE             (0xF000) \r\n");
		printf("DAY_NIGHT                 (0xF002) \r\n");
		printf("DYNAMIC_IQ                (0xF004) \r\n");
		printf("TEMPORAL_DENOISE          (0xF005) \r\n");
		printf("LDC                       (0xF008) \r\n");
		printf("GRAY                      (0xF009) \r\n");
		printf("WDR_MODE                  (0xF00C) \r\n");
		printf("WDR_LEVEL                 (0xF00D) \r\n");
		printf("MIRROR_FLIP               (0xF020) \r\n");
		printf("MAX_FPS                   (0xF021) \r\n");
		printf("MIN_FPS                   (0xF022) \r\n");
		return;
	}

	if (argc >= 2) {
		set_flag = atoi(argv[1]);
		id = atoi(argv[2]);
		printf("[isp ctrl] set_flag:%d  id:%d.\r\n", set_flag, id);
		if (set_flag == 0) {
			hal_video_isp_ctrl(id, set_flag, &ret);
			if (ret != -1) {
				printf("result 0x%08x %d \r\n", ret, ret);
			} else {
				printf("isp_ctrl get error\r\n");
			}
		} else {

			if (argc >= 3) {
				hal_video_isp_ctrl(id, 0, &ret);
				if (ret != -1) {
					printf("before set result 0x%08x %d \r\n", ret, ret);
					vTaskDelay(20);
					set_value = atoi(argv[3]);
					printf("[isp ctrl] set_value:%d.\r\n", set_value);

					ret = hal_video_isp_ctrl(id, set_flag, &set_value);
					if (ret != 0) {
						printf("isp_ctrl set error\r\n");
					} else {
						vTaskDelay(20);
						hal_video_isp_ctrl(id, 0, &ret);
						if (ret != -1) {
							printf("check result 0x%08x %d \r\n", ret, ret);
						} else {
							printf("isp_ctrl get error\r\n");
						}
					}
				} else {
					printf("isp_ctrl get error\r\n");
				}

			} else {
				printf("isp_ctrl set error : need 3 argument: set_flag id  set_value\r\n");
			}
		}

	} else {
		printf("isp_ctrl  error : need 2~3 argument: set_flag id  [set_value] \r\n");
	}
}
void fATIX(void *arg)
{
	int i;
	int argc = 0;
	int addr = 0;
	int num = 0;
	int value32 = 0;
	short value16 = 0;
	char value8  = 0;
	char *argv[MAX_ARGC] = {0};

	if (!arg) {
		return;
	}

	argc = parse_param(arg, argv);
	if (strcmp(argv[1], "help") == 0) {
		printf("Usage: ATIX=FUNCTION,ADDRESS,NUMBER,VALUE1,VALUE2...\r\n");
		printf("[FUNCTION] read32,write32,read16,write16,read8,write8.\r\n");
		printf("[ADDRESS ] register address.(2 bytes,exclude base-address)\r\n");
		printf("[NUMBER  ] number of value.\r\n");
		printf("[VALUE#  ] necessary if FUNCTION=write32, write16 or write8.\r\n");
	}

	num  = atoi(argv[3]);
	if (num <= 0) {
		return;
	}

	addr = atoi(argv[2]);
	if (strcmp(argv[1], "read32") == 0) {

		printf("[ISP]register read addr from 0x%X:\r\n", 0x40300000 | addr);
		for (i = 0; i < num; i++) {
			if (i > 0 && i % 8 == 0) {
				printf("\r\n");
			}
			printf("0x%X \r\n", HAL_READ32(0x40300000, addr + 4 * i));
		}
		printf("\r\n");
	} else if (strcmp(argv[1], "write32") == 0) {

		printf("[ISP]register write addr from 0x%X:\r\n", 0x40300000 | addr);
		for (i = 0; i < num; i++) {
			if (i > 0 && i % 8 == 0) {
				printf("\r\n");
			}
			value32 = atoi(argv[4 + i]);
			HAL_WRITE32(0x40300000, (addr + 4 * i), value32);
			printf("0x%X \r\n", value32);
		}
		printf("\r\n");
	} else if (strcmp(argv[1], "read16") == 0) {

		printf("[ISP]register read addr from 0x%X:\r\n", 0x40300000 | addr);
		for (i = 0; i < num; i++) {
			if (i > 0 && i % 8 == 0) {
				printf("\r\n");
			}
			printf("0x%X \r\n", HAL_READ16(0x40300000, addr + 2 * i));
		}
		printf("\r\n");
	} else if (strcmp(argv[1], "write16") == 0) {

		printf("[ISP]register write addr from 0x%X:\r\n", 0x40300000 | addr);
		for (i = 0; i < num; i++) {
			if (i > 0 && i % 8 == 0) {
				printf("\r\n");
			}
			value16 = (short)atoi(argv[4 + i]);
			HAL_WRITE16(0x40300000, (addr + 2 * i), value16);
			printf("0x%X \r\n", value16);
		}
		printf("\r\n");
	} else if (strcmp(argv[1], "read8") == 0) {

		printf("[ISP]register read addr from 0x%X:\r\n", 0x40300000 | addr);
		for (i = 0; i < num; i++) {
			if (i > 0 && i % 8 == 0) {
				printf("\r\n");
			}
			printf("0x%X \r\n", HAL_READ8(0x40300000, addr + 1 * i));
		}
		printf("\r\n");
	} else if (strcmp(argv[1], "write8") == 0) {

		printf("[ISP]register write addr from 0x%X:\r\n", 0x40300000 | addr);
		for (i = 0; i < num; i++) {
			if (i > 0 && i % 8 == 0) {
				printf("\r\n");
			}
			value8 = (char)atoi(argv[4 + i]);
			HAL_WRITE8(0x40300000, (addr + 1 * i), value8);
			printf("0x%X \r\n", value8);
		}
		printf("\r\n");
	}
}

#include "isp_ctrl_api.h"
#include "ftl_common_api.h"
void (*uvc_v2)(void) = NULL;
static int pre_etgain = -1;
void fATII(void *arg)
{
	int i;
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	int stream_id = 0;
	int bayer_index = 0;

	if (!arg) {
		return;
	}

	argc = parse_param(arg, argv);

	if (argc < 1) {
		return;
	}

	if (strcmp(argv[1], "bayer") == 0) {
		stream_id = atoi(argv[2]);
		bayer_index = atoi(argv[3]);
		if (bayer_index < 0 || bayer_index > 9) {
			return;
		}
		if (bayer_index == 7 || bayer_index == 8 || bayer_index == 9) {
			HAL_WRITE32(0x50000000, 0x0918, 0x3733);
		}
		hal_video_isp_set_rawfmt(stream_id, bayer_index);
	} else if (strcmp(argv[1], "gray") == 0) {
		int mode = -1;
		isp_set_gray_mode(atoi(argv[2]));
		isp_get_gray_mode(&mode);
		printf("isp gray mode: %d.\r\n", mode);
	} else if (strcmp(argv[1], "log") == 0) {
		extern void tuning_set_log_level(int level);
		if (strcmp(argv[2], "all") == 0) {
			hal_video_print(atoi(argv[3]));
			isp_ctrl_enable_log(atoi(argv[3]));
			printf("log-all: %d.\r\n", atoi(argv[3]));
		} else if (strcmp(argv[2], "voe") == 0) {
			hal_video_print(atoi(argv[3]));
			printf("log-voe: %d.\r\n", atoi(argv[3]));
		} else if (strcmp(argv[2], "ispctrl") == 0) {
			isp_ctrl_enable_log(atoi(argv[3]));
			printf("log-ispctrl: %d.\r\n", atoi(argv[3]));
		} else if (strcmp(argv[2], "tuning") == 0) {
			tuning_set_log_level(atoi(argv[3]));
			printf("log-tuning: %d.\r\n", atoi(argv[3]));
		}
	} else if (strcmp(argv[1], "version") == 0) {
		video_get_version();
	} else if (strcmp(argv[1], "delay") == 0) {
		int is_tuning_delay;
		extern void tuning_command_delay(int enable);
		is_tuning_delay = atoi(argv[2]);
		tuning_command_delay(is_tuning_delay);
		printf("is_tuning_delay: %d.\r\n", is_tuning_delay);
	} else if (strcmp(argv[1], "v2") == 0) {
		if (uvc_v2) {
			uvc_v2();
		} else {
			printf("uvc_v2 is null.\r\n");
		}
	} else if (strcmp(argv[1], "fps") == 0) {
		if (strcmp(argv[2], "show") == 0) {
			video_show_fps(1);
		} else if (strcmp(argv[2], "hide") == 0) {
			video_show_fps(0);
		}
	} else if (strcmp(argv[1], "flash") == 0) {
		int fw_size = 0;
		unsigned char iq_header[28] = {0};
		if (strcmp(argv[2], "read") == 0) {
			ftl_common_read(TUNING_IQ_FW, (u8 *) &fw_size, sizeof(int));
			printf("IQ FW size: 0x%04X.\r\n", fw_size);
		} else if (strcmp(argv[2], "timestamp") == 0) {
			ftl_common_read(TUNING_IQ_FW, (u8 *) iq_header, 28);
			int *diq_header = (int *)(iq_header + 8);
			printf("IQ header: 0x%08X 0x%08X 0x%08X 0x%08X.\r\n", diq_header[0], diq_header[1], diq_header[2], diq_header[3]);
			printf("iq timestamp: %04d/%02d/%02d %02d:%02d:%02d\r\n", *(unsigned short *)(iq_header + 12), iq_header[14], iq_header[15], iq_header[16],
				   iq_header[17], *(unsigned short *)(iq_header + 18));
		} else if (strcmp(argv[2], "erase") == 0) {
			if (strcmp(argv[3], "ap") == 0) {
				extern int Erase_Fastconnect_data(void);
				Erase_Fastconnect_data();
				printf("[ATII] erase AP info.\r\n");
			} else {
				int *iq_tmp = malloc(CMD_DATA_SIZE * 4);
				if (iq_tmp) {
					memset(iq_tmp, 0, CMD_DATA_SIZE * 4);
					ftl_common_write(TUNING_IQ_FW, (u8 *)iq_tmp, CMD_DATA_SIZE * 4);
					printf("[ATII] erase 256K..Done.\r\n");
					free(iq_tmp);
				}
			}
		}
	} else if (strcmp(argv[1], "meta") == 0) {
		extern isp_statis_meta_t _meta;
		isp_statis_meta_t jmeta = _meta;
		printf("[%s]exposure_h:%d exposure_l:%d\r\n", __FUNCTION__, jmeta.exposure_h, jmeta.exposure_l);
		printf("[%s]gain_h:%d gain_l:%d\r\n", __FUNCTION__, jmeta.gain_h, jmeta.gain_l);
		printf("[%s]wb_r_gain:%d wb_b_gain:%d wb_g_gain:%d\r\n", __FUNCTION__, jmeta.wb_r_gain, jmeta.wb_b_gain, jmeta.wb_g_gain);
		printf("[%s]colot_temperature:%d\r\n", __FUNCTION__, jmeta.colot_temperature);
		printf("[%s]y_average:%d\r\n", __FUNCTION__, jmeta.y_average);
		printf("[%s]white_num:%d\r\n", __FUNCTION__, jmeta.white_num);
		printf("[%s]rg_sum:%d bg_sum:%d\r\n", __FUNCTION__, jmeta.rg_sum, jmeta.bg_sum);
		printf("[%s]hdr_mode:%d\r\n", __FUNCTION__, jmeta.hdr_mode);
		printf("[%s]sensor_fps:%d max_fps:%d\r\n", __FUNCTION__, jmeta.sensor_fps, jmeta.max_fps);
		printf("[%s]frame_count:%d\r\n", __FUNCTION__, jmeta.frame_count);
		printf("[%s]time_stamp:%d\r\n", __FUNCTION__, jmeta.time_stamp);
		printf("[%s]wdr_hist_contrast:%d\r\n", __FUNCTION__, jmeta.wdr_hist_contrast);
		printf("[%s]wdr_hist_contrast_origin:%d\r\n", __FUNCTION__, jmeta.wdr_hist_contrast_origin);
	} else if (strcmp(argv[1], "i2c") == 0) {
		struct rts_isp_i2c_reg reg;
		int ret;
		reg.addr = atoi(argv[3]);
		if (strcmp(argv[2], "read") == 0) {
			reg.data = 0;
			ret = hal_video_i2c_read(&reg);
			printf("ret: %d, read addr:0x%04X, data:0x%04X.\r\n", ret, reg.addr, reg.data);
		} else if (strcmp(argv[2], "write") == 0) {
			reg.data = atoi(argv[4]);
			printf("write addr:0x%04X, data:0x%04X.\r\n", reg.addr, reg.data);
			ret = hal_video_i2c_write(&reg);
			printf("ret: %d, .\r\n", ret);

			reg.data = 0;
			ret = hal_video_i2c_read(&reg);
			printf("ret: %d, read addr:0x%04X, data:0x%04X.\r\n", ret, reg.addr, reg.data);
		}
	} else if (strcmp(argv[1], "info") == 0) {
		if (strcmp(argv[2], "af") == 0) {
			af_statis_t af_result;
			int ret = isp_get_AF_statis(&af_result);
			if (!ret) {
				printf("fr %d af0 %d %d af1 %d %d\r\n"
					   , (int)af_result.frame_count
					   , (int)af_result.sum0
					   , (int)af_result.num0
					   , (int)af_result.sum1
					   , (int)af_result.num1);
			} else {
				printf("get info fail hal_video_get_AF_statis.\r\n");
			}
		} else if (strcmp(argv[2], "ae_hist") == 0) {
			ae_statis_t ae_result;
			int ret = isp_get_AE_statis(&ae_result, AE_STATIS_HIST);
			if (!ret) {
				printf("Value, Count, fr %d\n", (int)ae_result.frame_count);
				for (int j = 0; j < 256; j++) {
					printf("[%3d] %5d \n", j, ae_result.hist[j]);
				}
			} else {
				printf("get info fail isp_get_AE_statis.\r\n");
			}
		} else if (strcmp(argv[2], "ae_ymean") == 0) {
			ae_statis_t ae_result;
			int ret = isp_get_AE_statis(&ae_result, AE_STATIS_YMEAN);
			if (!ret) {
				printf("fr %d\n", (int)ae_result.frame_count);
				if (!ret) {
					for (int j = 0; j < 16; j++) {
						for (int k = 0; k < 16; k++) {
							printf("%4d ", ae_result.hist[j * 16 + k]);
						}
						printf("\n");
					}
				}
			} else {
				printf("get info fail isp_get_AE_statis.\r\n");
			}
		} else if (strcmp(argv[2], "awb") == 0) {
			awb_statis_t awb_result;
			int ret = isp_get_AWB_statis(&awb_result);
			if (!ret) {
				printf("fr %d awb win %d\r\n"
					   , (int)awb_result.frame_count
					   , (int)awb_result.win_cnt);
				printf("awb rg \r\n");
				for (int j = 0; j < 16; j++) {
					for (int k = 0; k < 16; k++) {
						printf("%5d ", awb_result.rg[j * 16 + k]);
					}
					printf("\r\n");
				}
				printf("awb bg \r\n");
				for (int j = 0; j < 16; j++) {
					for (int k = 0; k < 16; k++) {
						printf("%5d ", awb_result.bg[j * 16 + k]);
					}
					printf("\r\n");
				}

			} else {
				printf("get info fail hal_video_get_AWB_statis.\r\n");
			}
		} else if (strcmp(argv[2], "ae_stable") == 0) {
			char if_ae_stable = AE_UNSTABLE;
			int cur_etgain = pre_etgain;
			if_ae_stable = isp_get_ae_if_stable(&cur_etgain, 500);
			printf("ifAEStable=%d, pre_etgain=%d, cur_etgain=%d\r\n", if_ae_stable, cur_etgain, pre_etgain);
			pre_etgain = cur_etgain;
		} else if (strcmp(argv[2], "mipi") == 0) {
			int value;
			value = isp_get_info(MIPI_FRAME_COUNT);
			printf("frame_cnt: 0x%08X (%d) \r\n", value, value);
			value = isp_get_info(MIPI_PIXEL_COUNT);
			printf("pixel_cnt: 0x%08X (%d) \r\n", value, value);
			value = isp_get_info(MIPI_LINE_COUNT);
			printf("line_cnt: 0x%08X (%d) \r\n", value, value);
		} else if (strcmp(argv[2], "sys") == 0) {
			int value;
			value = isp_get_info(SYS_FRAME_COUNT);
			printf("frame_cnt(input): 0x%08X (%d) \r\n", value, value);
			value = isp_get_info(SYS_FRAME_IDLE);
			printf("frame_idle: 0x%08X (%d) \r\n", value, value);
		}
	} else if (strcmp(argv[1], "func_en") == 0) {
		int RegVale = -1;
		if (argc == 7) {
			RegVale = isp_set_func(ISP_FN_LSC, atoi(argv[2]));
			RegVale = isp_set_func(ISP_FN_NR, atoi(argv[3]));
			RegVale = isp_set_func(ISP_FN_NPC, atoi(argv[4]));
			RegVale = isp_set_func(ISP_FN_EE, atoi(argv[5]));
			RegVale = isp_set_func(ISP_FN_GAMMA, atoi(argv[6]));
		} else {
			printf("incorrect argument number.(%d)\r\nPlease follow below format:\r\n", argc);
			printf("[Example] ATII=func_en,bLSC,bNR,bDPC,bEE,bGamma\r\n");
		}
		isp_get_info(SYS_CONTROL1);
	}

}


#include "../video/osd2/isp_osd_example.h"
#include "osd_api.h"
#include <sntp/sntp.h>
void fATIO(void *arg)
{
#if ENABLE_OSD_CMD
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	argc = parse_param(arg, argv);
	if (strcmp(argv[1], "size") == 0) {
		rts_set_char_size(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
	} else if (strcmp(argv[1], "block") == 0) {
		if (atoi(argv[4]) == 1) {
			rts_osd_block_show(atoi(argv[2]), atoi(argv[3]));
		} else {
			rts_osd_block_hide(atoi(argv[2]), atoi(argv[3]));
		}
	} else if (strcmp(argv[1], "task") == 0) {
		example_isp_osd(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
	} else if (strcmp(argv[1], "timezone") == 0) {
		rts_osd_set_timezone(atoi(argv[2]));
		printf("Current time-zone:%d.\r\n", rts_osd_get_timezone());
	} else if (strcmp(argv[1], "close") == 0) {
		rts_osd_deinit(atoi(argv[2]));
	}
#endif
}

#include "sensor_service.h"
void fATIR(void *arg)
{
	volatile int argc, error_no = 0;
	char *argv[MAX_ARGC] = {0};
	int mode;

	if (!arg) {
		AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_ERROR,
				   "\r\n[ATIR] Usage : ATIR=<function>,<VALUE>");
		error_no = 1;
		goto EXIT;
	} else {
		argc = parse_param(arg, argv);
	}

	if (strcmp(argv[1], "help") == 0) {
		printf("Usage: ATIR=FUNCTION,VALUE\r\n");
		printf("[Fun List    ] init_ir,init_als,get_hw_lux,get_sw_lux,enable,set_light,service,als_ver,dbg_als,dbg_ss,auto_pwm\r\n");
		printf("[init_ir     ] init RTK-EVB IR-CUT (on sensor board)\r\n");
		printf("[init_led    ] init RTK-EVB IR-LED & HW-ALS (on LED board)\r\n");
		printf("[init_service] init sensor service (User can refer to sensor_service.c)\r\n");
		printf("[get_hw_lux  ] get hw-als value on RTK-EVB\r\n");
		printf("[get_sw_lux  ] get sw-als value on RTK-EVB\r\n");
		printf("[set_ir_cut  ] set IR-CUT on RTK-EVB, VALUE=0/1\r\n");
		printf("[set_ir_led  ] set IR-LED strength on RTK-EVB, VALUE=0-100\r\n");
		printf("[get_version ] get sw-als version\r\n");
		printf("[set_als_dbg ] set debug level for sw-als (User can refer to als_dbg_level)\r\n");
		printf("[set_ss_dbg  ] set debug level for sensor service (User can refer to ss_dbg_level)\r\n");
		printf("[set_apwm    ] auto-pwm swich, VALUE=0/1\r\n");
	} else if (strcmp(argv[1], "init_ir") == 0) { 	// Init IR-Cut on sensor board
		ir_cut_init(NULL);
		printf("ir_cut_init.\r\n");
	} else if (strcmp(argv[1], "init_led") == 0) { 	// Init IR-LED and HW-ALS on light board
		ir_ctrl_init(NULL);
		ambient_light_sensor_init(NULL);
		ambient_light_sensor_power(1);
		printf("ir_ctrl_init/ambient_light_sensor_init.\r\n");
	} else if (strcmp(argv[1], "set_ir_cut") == 0) {
		mode = atoi(argv[2]);
		if (mode == 1) {
			ir_cut_enable(0);
			vTaskDelay(1000);
			ir_cut_enable(1);
			printf("IR Cut On\r\n");
		} else if (mode == 0) {
			ir_cut_enable(1);
			vTaskDelay(1000);
			ir_cut_enable(0);
			printf("IR Cut Off\r\n");
		}
	} else if (strcmp(argv[1], "get_hw_lux") == 0) {
		ss_cmd(SS_GET_CMD, SS_CMD_HW_LUX, &mode);
		printf("[SENSOR_SERVICE] HW_LUX(%d) \r\n", mode);
	} else if (strcmp(argv[1], "get_sw_lux") == 0) {
		ss_cmd(SS_GET_CMD, SS_CMD_SW_LUX, &mode);
		printf("[SENSOR_SERVICE] SW_LUX(%d) \r\n", mode);
	} else if (strcmp(argv[1], "set_ir_led") == 0) {
		int dValue1 = atoi(argv[2]);
		if (dValue1 > 100) {
			dValue1 = 100;
		}
		if (dValue1 < 0) {
			dValue1 = 0;
		}
		printf("led_brightness: %d (/100) \r\n", dValue1);
		ir_ctrl_set_brightness_d(dValue1);
	} else if (strcmp(argv[1], "init_service") == 0) {
		init_sensor_service();
	} else if (strcmp(argv[1], "get_version") == 0) {
		als_get_version();
		ss_cmd(SS_GET_CMD, SS_CMD_VERSION, &mode);
	} else if (strcmp(argv[1], "set_als_dbg") == 0) {
		mode = atoi(argv[2]);
		als_set_dbg_level(mode);
		printf("[SW_ALS] als_dbg_level(%d)\r\n", mode);
	} else if (strcmp(argv[1], "set_ss_dbg") == 0) {
		mode = atoi(argv[2]);
		ss_cmd(SS_SET_CMD, SS_CMD_DEBUG_LEVEL, &mode);
		ss_cmd(SS_GET_CMD, SS_CMD_DEBUG_LEVEL, &mode);
		printf("[SENSOR_SERVICE] ss_dbg_level(%d)\r\n", mode);
	} else if (strcmp(argv[1], "set_apwm") == 0) {
		mode = atoi(argv[2]);
		ss_cmd(SS_SET_CMD, SS_CMD_AUTO_PWM, &mode);
		ss_cmd(SS_GET_CMD, SS_CMD_AUTO_PWM, &mode);
		printf("[SENSOR_SERVICE] en_auto_pwm(%d)\r\n", mode);
	}

	return;
EXIT:
	printf("error at command format\r\n");
}

void fATIM(void *arg)
{
	volatile int argc, error_no = 0;
	char *argv[MAX_ARGC] = {0};
	int mode;

	if (!arg) {
		AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_ERROR,
				   "\r\n[ATIM] Usage : ATIM=ch,en,grid_mode,id,startx,starty,w,h,color,cols,rows");
		error_no = 1;
		goto EXIT;
	}

	argc = parse_param(arg, argv);
	if (argc != 12) {
		printf("[ATIM input err] parameter num: %d (should be 11)", argc - 1);
		return;
	}

	struct private_mask_s pr_mask = {0};
	//=ch,en,grid_mode,id,startx,starty,w,h,color,cols,rows  0,1,1,1,100,100,960,540,0x00FF00,32,18
	//printf("ATIM=ch,en,grid_mode,id,startx,starty,w,h,color,cols,rows \r\n");

	int grid_mode = atoi(argv[3]);
	int id = atoi(argv[4]) + 1; //1~4 only for rect-mode
	if (grid_mode) {
		id = 0;
	}
	pr_mask.color = atoi(argv[9]);//BBGGRR
	pr_mask.start_x[id] = atoi(argv[5]);//2-align
	pr_mask.start_y[id] = atoi(argv[6]);//2-align
	pr_mask.w[id] = atoi(argv[7]);//16-align when grid-mode
	pr_mask.h[id] = atoi(argv[8]);
	pr_mask.en[id] = atoi(argv[2]);
	if (grid_mode) {
		pr_mask.cols = atoi(argv[10]);//8 align
		pr_mask.rows = atoi(argv[11]);
		memset(pr_mask.bitmap, 0xAA, 160);
	}

	video_set_private_mask(atoi(argv[1]), &pr_mask);

	return;
EXIT:
	printf("error at command format\r\n");
}

#if (ENABLE_AE_METER_CMD)
#define AE_METER_SIZE	256

void fATAE(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	argc = parse_param(arg, argv);
	int i, j, length;
	length = AE_METER_SIZE;
	static int bifgetMeter = NOK;
	static uint8_t ori_meter[AE_METER_SIZE];
	uint8_t cur_meter[AE_METER_SIZE];
	if (bifgetMeter == NOK) {
		bifgetMeter = isp_get_AE_meter(ori_meter, &length);
		if (bifgetMeter == NOK) {
			return;
		}
		printf("=== default ae meter in IQ table ===\n");
		for (i = 0; i < 16; i++) {
			for (j = 0; j < 16; j++) {
				printf("%3d ", ori_meter[i * 16 + j]);
			}
			printf("\n");
		}
	}
	if (strcmp(argv[1], "left") == 0) {
		for (i = 0; i < 16; i++) {
			for (j = 0; j < 16; j++) {
				if (j < 5) {
					cur_meter[i * 16 + j] = ori_meter[i * 16 + j] + 15;
				} else {
					cur_meter[i * 16 + j] = ori_meter[i * 16 + j];
				}
			}
		}
	} else if (strcmp(argv[1], "center") == 0) {
		for (i = 0; i < 16; i++) {
			for (j = 0; j < 16; j++) {
				if (j >= 5 && j <= 10) {
					cur_meter[i * 16 + j] = ori_meter[i * 16 + j] + 15;
				} else {
					cur_meter[i * 16 + j] = ori_meter[i * 16 + j];
				}
			}
		}
	} else if (strcmp(argv[1], "right") == 0) {
		for (i = 0; i < 16; i++) {
			for (j = 0; j < 16; j++) {
				if (j > 10) {
					cur_meter[i * 16 + j] = ori_meter[i * 16 + j] + 15;
				} else {
					cur_meter[i * 16 + j] = ori_meter[i * 16 + j];
				}
			}
		}
	} else if (strcmp(argv[1], "spot") == 0) {
		for (i = 0; i < 16; i++) {
			for (j = 0; j < 16; j++) {
				if ((j >= 5 && j <= 10) && (i >= 5 && i <= 10)) {
					cur_meter[i * 16 + j] = 15;
				} else {
					cur_meter[i * 16 + j] = ori_meter[i * 16 + j];
				}
			}
		}

	} else {
		memcpy(cur_meter, ori_meter, length);
	}
	int ret = isp_set_AE_meter(cur_meter, length);
	if (!ret) {
		printf("=== current ae meter ===\n");
		for (i = 0; i < 16; i++) {
			for (j = 0; j < 16; j++) {
				printf("%3d ", cur_meter[i * 16 + j]);
			}
			printf("\n");
		}
	}
}
#endif

log_item_t at_isp_items[] = {
	{"ATIT", fATIT,},
	{"ATIC", fATIC,},
	{"ATIX", fATIX,},
	{"ATII", fATII,},
	{"ATIO", fATIO,},
	{"ATIR", fATIR,},
	{"ATIM", fATIM,},
#if (ENABLE_AE_METER_CMD)
	{"ATAE", fATAE,},
#endif
};

void at_isp_init(void)
{
	log_service_add_table(at_isp_items, sizeof(at_isp_items) / sizeof(at_isp_items[0]));
}

#if SUPPORT_LOG_SERVICE
log_module_init(at_isp_init);
#endif
