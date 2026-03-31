#include <sys.h>
#include <device_lock.h>
#include "ota_8735b.h"
#include "lwipconf.h"
#include "sys_api.h"
#include "osdep_service.h"
#include "flash_api.h"
#include "snand_api.h"
#include "hal_crypto.h"
#include "hal_eddsa.h"
#include "fwfs.h"
#if UPDATE_UPGRADE_PROGRESS_TO_8773
#include "ai_glass_initialize.h"
#endif
sys_thread_t TaskOTA = NULL;
#define STACK_SIZE		1024
#define TASK_PRIORITY	tskIDLE_PRIORITY + 1

// Checksum check before make fw valid
// Please make sure target OTA firmware did contains 4 bytes checksum value, or the checksum check would always fail
// User can check target firmware postbuild routine.
#define USE_CHECKSUM 1

#if UPDATE_UPGRADE_PROGRESS_TO_8773
// For OTA progress status
volatile uint8_t progress;
// static TimerHandle_t ota_progress_timer = NULL;

// void ota_progress_timer_callback(TimerHandle_t xTimer)
// {
//     uart_resp_get_sys_upgrade((uint8_t) 1, progress);
// 	   printf("Send wifi ota progress: %u\r\n", progress);
// }

#endif


/**
  * @brief  Clear OTA signature so that boot code load default image.
  * @retval none
  */
void sys_clear_ota_signature(void)
{
	uint8_t cur_fw_idx = 0;
	uint8_t boot_sel = -1;

	cur_fw_idx = hal_sys_get_ld_fw_idx();
	if ((1 != cur_fw_idx) && (2 != cur_fw_idx)) {
		printf("\n\rcurrent fw index is wrong %d \n\r", cur_fw_idx);
		return;
	}

	boot_sel = sys_get_boot_sel();
	if (0 == boot_sel) {
		// boot from NOR flash

		flash_t flash;
		uint8_t label_init_value[8] = {0x52, 0x54, 0x4c, 0x38, 0x37, 0x33, 0x35, 0x42};
		uint8_t next_fw_label[8] = {0};
		uint32_t cur_fw_addr = 0, next_fw_addr = 0;
		uint8_t *pbuf = NULL;
		uint32_t buf_size = 4096;

		device_mutex_lock(RT_DEV_LOCK_FLASH);
		if (1 == cur_fw_idx) {
			// fw1 record in partition table
			flash_read_word(&flash, 0x2060, &cur_fw_addr);
			// fw2 record in partition table
			flash_read_word(&flash, 0x2080, &next_fw_addr);
		} else if (2 == cur_fw_idx) {
			// fw2 record in partition table
			flash_read_word(&flash, 0x2080, &cur_fw_addr);
			// fw1 record in partition table
			flash_read_word(&flash, 0x2060, &next_fw_addr);
		}
		flash_stream_read(&flash, next_fw_addr, 8, next_fw_label);
		device_mutex_unlock(RT_DEV_LOCK_FLASH);

		if (0 != memcmp(next_fw_label, label_init_value, 8)) {
			printf("\n\rOnly one valid fw, no fw to clear");
			return;
		}

		//erase current FW signature to make it boot from another FW image
		printf("\n\rcurrent FW addr = 0x%08X", cur_fw_addr);

		pbuf = malloc(buf_size);
		if (!pbuf) {
			printf("\n\rAllocate buf fail");
			return;
		}

		// need to enter critical section to prevent executing the XIP code at first sector after we erase it.
		device_mutex_lock(RT_DEV_LOCK_FLASH);
		flash_stream_read(&flash, cur_fw_addr, buf_size, pbuf);
		// NOT the first byte of ota signature to make it invalid
		pbuf[0] = ~(pbuf[0]);
		flash_erase_sector(&flash, cur_fw_addr);
		flash_burst_write(&flash, cur_fw_addr, buf_size, pbuf);
		device_mutex_unlock(RT_DEV_LOCK_FLASH);

		free(pbuf);
	} else if (1 == boot_sel) {
		// boot from NAND flash

		//uint8_t partition_data[2112] __attribute__((aligned(32)));
		//uint8_t data_r[2112] __attribute__((aligned(32)));
		uint8_t *partition_data;
		uint8_t *data_r;
		partition_data = malloc(2112);
		data_r = malloc(2112);
		uint32_t crc_out = 0;
		uint32_t crypto_ret;
		int update_partition_table = 0;
		int partition_start_block = 16 ; //B-cut:20

		if (IS_CUT_B(hal_sys_get_rom_ver())) {
			partition_start_block = 20 ; //B-cut:20
		}

		snand_t flash;
		snand_init(&flash);
		snand_global_unlock();


		//read partition_table block16-23
		for (int i = partition_start_block; i < 24; i++) {
			snand_page_read(&flash, i * 64, 2048 + 4, &partition_data[0]);
			if ((partition_data[2048] == 0xff) && (partition_data[2049] == 0xc4)) {
				break;
			}
		}

		if (1 == cur_fw_idx) {
			for (int i = 0; i < 16; i++) {
				if ((partition_data[i * 128] == 0x87) && (partition_data[i * 128 + 1] == 0xff) && (partition_data[i * 128 + 2] == 0x35) &&
					(partition_data[i * 128 + 3] == 0xff) && (partition_data[i * 128 + 4] == 0xc8) && (partition_data[i * 128 + 5] == 0xb9)) {
					printf("partition_table FW2 type_id is valid \n\r");
					update_partition_table = 1;
				}
			}
			if (update_partition_table == 1) {
				for (int i = 0; i < 16; i++) {
					if ((partition_data[i * 128] == 0x87) && (partition_data[i * 128 + 1] == 0xff) && (partition_data[i * 128 + 2] == 0x35) &&
						(partition_data[i * 128 + 3] == 0xff) && (partition_data[i * 128 + 4] == 0xc7) && (partition_data[i * 128 + 5] == 0xc1)) {
						printf("clear partition_table FW1 magic_num \n\r");
						partition_data[i * 128] = 0x0; //0x87 to 0x0
						partition_data[i * 128 + 2] = 0x0; //0x35 to 0x0
					}
				}
			}
		} else if (2 == cur_fw_idx) {
			for (int i = 0; i < 16; i++) {
				if ((partition_data[i * 128] == 0x87) && (partition_data[i * 128 + 1] == 0xff) && (partition_data[i * 128 + 2] == 0x35) &&
					(partition_data[i * 128 + 3] == 0xff) && (partition_data[i * 128 + 4] == 0xc7) && (partition_data[i * 128 + 5] == 0xc1)) {
					printf("partition_table FW1 type_id is valid \n\r");
					update_partition_table = 1;
				}
			}
			if (update_partition_table == 1) {
				for (int i = 0; i < 16; i++) {
					if ((partition_data[i * 128] == 0x87) && (partition_data[i * 128 + 1] == 0xff) && (partition_data[i * 128 + 2] == 0x35) &&
						(partition_data[i * 128 + 3] == 0xff) && (partition_data[i * 128 + 4] == 0xc8) && (partition_data[i * 128 + 5] == 0xb9)) {
						printf("clear partition_table FW2 magic_num \n\r");
						partition_data[i * 128] = 0x0; //0x87 to 0x0
						partition_data[i * 128 + 2] = 0x0; //0x35 to 0x0
					}
				}
			}
		}

		//update partition table CRC16
		if (update_partition_table == 1) {
			crypto_ret = hal_crypto_engine_init();
			if (crypto_ret != SUCCESS) {
				printf("Crypto Init Failed!%d\r\n", crypto_ret);
				return;
			}
			crypto_ret =  hal_crypto_crc16_division(partition_data, 2048, &crc_out);
			if (crypto_ret != SUCCESS) {
				printf("CRC failed\r\n");
				// ignore error and go-on
				return;
			}

			printf("crc_out = 0x%x \n\r", crc_out);
			partition_data[2050] = (uint8_t)(crc_out & 0xff);
			partition_data[2051] = (uint8_t)(crc_out >> 8);
		}

		//update partition table block16-23
		if (update_partition_table == 1) {
			int success = 0;
			int fail = 0;
			for (int i = partition_start_block; i < 24; i++) {
				fail = 0;
				snand_erase_block(&flash, i * 64);
				snand_page_write(&flash, i * 64, 2048 + 4, &partition_data[0]);
				snand_page_read(&flash, i * 64, 2048 + 4, &data_r[0]);
				if (memcmp(partition_data, data_r, (2048 + 4)) != 0) {
					printf("bolck %d write fail! \n\r", i);
					fail = 1;
					snand_erase_block(&flash, i * 64);
					data_r[2048] = 0;
					snand_page_write(&flash, i * 64, 2048 + 4, &data_r[0]);
				}
				if (fail == 0) {
					success = success + 1;
				}
				if (success == 2) {
					break;
				}
			}

		}
		free(partition_data);
		free(data_r);

	}

	printf("\n\rClear OTA signature success.");
}

/**
  * @brief  Recover OTA signature so that boot code load upgraded image(ota image).
  * @retval none
  */
void sys_recover_ota_signature(void)
{
	uint8_t cur_fw_idx = 0;
	uint8_t boot_sel = -1;

	cur_fw_idx = hal_sys_get_ld_fw_idx();
	if ((1 != cur_fw_idx) && (2 != cur_fw_idx)) {
		printf("\n\rcurrent fw index is wrong %d \n\r", cur_fw_idx);
		return;
	}

	boot_sel = sys_get_boot_sel();
	if (0 == boot_sel) {
		// boot from NOR flash

		flash_t flash;
		uint8_t label_init_value[8] = {0x52, 0x54, 0x4c, 0x38, 0x37, 0x33, 0x35, 0x42};
		uint8_t target_fw_label[8] = {0};
		uint32_t target_fw_addr = 0;
		uint8_t *pbuf = NULL;
		uint32_t buf_size = 4096;

		device_mutex_lock(RT_DEV_LOCK_FLASH);
		if (1 == cur_fw_idx) {
			// fw2 record in partition table
			flash_read_word(&flash, 0x2080, &target_fw_addr);
		} else if (2 == cur_fw_idx) {
			// fw1 record in partition table
			flash_read_word(&flash, 0x2060, &target_fw_addr);
		}
		flash_stream_read(&flash, target_fw_addr, 8, target_fw_label);
		device_mutex_unlock(RT_DEV_LOCK_FLASH);

		// check next fw label
		if (0 == memcmp(target_fw_label, label_init_value, 8)) {
			printf("\n\rBoth fw valid, no fw to recover");
			return;
		}

		printf("\n\rtarget  FW addr = 0x%08X", target_fw_addr);

		pbuf = malloc(buf_size);
		if (!pbuf) {
			printf("\n\rAllocate buf fail");
			return;
		}

		device_mutex_lock(RT_DEV_LOCK_FLASH);
		flash_stream_read(&flash, target_fw_addr, buf_size, pbuf);
		// NOT the first byte of ota signature to make it valid
		pbuf[0] = ~(pbuf[0]);
		flash_erase_sector(&flash, target_fw_addr);
		flash_burst_write(&flash, target_fw_addr, buf_size, pbuf);
		device_mutex_unlock(RT_DEV_LOCK_FLASH);

		free(pbuf);
	} else if (1 == boot_sel) {
		// boot from NAND flash
		//uint8_t partition_data[2112] __attribute__((aligned(32)));
		//uint8_t data_r[2112] __attribute__((aligned(32)));
		uint8_t *partition_data;
		uint8_t *data_r;
		partition_data = malloc(2112);
		data_r = malloc(2112);
		uint32_t crc_out = 0;
		uint32_t crypto_ret;
		int update_partition_table = 0;
		int partition_start_block = 16 ; //B-cut:20

		if (IS_CUT_B(hal_sys_get_rom_ver())) {
			partition_start_block = 20 ; //B-cut:20
		}

		snand_t flash;
		snand_init(&flash);
		snand_global_unlock();

		//read partition_table block16-23
		for (int i = partition_start_block; i < 24; i++) {
			snand_page_read(&flash, i * 64, 2048 + 8, &partition_data[0]);
			if (partition_data[2048] == 0xff) {
				break;
			}
		}

		if (1 == cur_fw_idx) {
			for (int i = 0; i < 16; i++) {
				if ((partition_data[i * 128 + 4] == 0xc8) && (partition_data[i * 128 + 5] == 0xb9)) {
					printf("partition_table FW2 type_id is valid \n\r");
					partition_data[i * 128] = 0x87; //0x0 to 0x87
					partition_data[i * 128 + 2] = 0x35; //0x0 to 0x35
					printf("recover partition_table FW2 magic_num \n\r");
					update_partition_table = 1;
				}
			}
		} else if (2 == cur_fw_idx) {
			for (int i = 0; i < 16; i++) {
				if ((partition_data[i * 128 + 4] == 0xc7) && (partition_data[i * 128 + 5] == 0xc1)) {
					printf("partition_table FW1 type_id is valid \n\r");
					partition_data[i * 128] = 0x87; //0x0 to 0x87
					partition_data[i * 128 + 2] = 0x35; //0x0 to 0x35
					printf("recover partition_table FW1 magic_num \n\r");
					update_partition_table = 1;
				}
			}
		}
		//update partition table CRC16
		if (update_partition_table == 1) {
			crypto_ret = hal_crypto_engine_init();
			if (crypto_ret != SUCCESS) {
				printf("Crypto Init Failed!%d\r\n", crypto_ret);
				return;
			}
			crypto_ret =  hal_crypto_crc16_division(partition_data, 2048, &crc_out);
			if (crypto_ret != SUCCESS) {
				printf("CRC failed\r\n");
				// ignore error and go-on
				return;
			}

			printf("crc_out = 0x%x \n\r", crc_out);
			partition_data[2050] = (uint8_t)(crc_out & 0xff);
			partition_data[2051] = (uint8_t)(crc_out >> 8);
		}

		//update partition table block16-23
		if (update_partition_table == 1) {
			int success = 0;
			int fail = 0;
			for (int i = partition_start_block; i < 24; i++) {
				fail = 0;
				snand_erase_block(&flash, i * 64);
				snand_page_write(&flash, i * 64, 2048 + 8, &partition_data[0]);
				snand_page_read(&flash, i * 64, 2048 + 8, &data_r[0]);
				if (memcmp(partition_data, data_r, (2048 + 8)) != 0) {
					printf("bolck %d write fail! \n\r", i);
					fail = 1;
					snand_erase_block(&flash, i * 64);
					data_r[2048] = 0;
					snand_page_write(&flash, i * 64, 2048 + 8, &data_r[0]);
				}
				if (fail == 0) {
					success = success + 1;
				}
				if (success == 2) {
					break;
				}
			}

		}
		free(partition_data);
		free(data_r);
	}

	printf("\n\rRecover OTA signature success.");
}

int ota_verify_signature(char *partition_name, uint8_t *manifest)
{
	uint8_t pubkey_hash[32];
	uint8_t sha256_hash[32];
	uint8_t pubkey[32];
	uint8_t signature[64];

	if (!((strcmp(partition_name, "BL_PRI") == 0) || (strcmp(partition_name, "FW1") == 0) || (strcmp(partition_name, "FW2") == 0))) {
		printf("ERROR: partition name\n\r");
		return -1;
	}

	memset(pubkey_hash, 0, sizeof(pubkey_hash));
	memset(sha256_hash, 0, sizeof(sha256_hash));
	memset(pubkey, 0, sizeof(pubkey));
	memset(signature, 0, sizeof(signature));

	void *key_cert_fp = pfw_open("KEY_CER1", M_RAW | M_RDONLY);
	if (key_cert_fp) {
		uint32_t key_cert_len = 0x5A0;
		uint8_t *key_cert = (uint8_t *) malloc(key_cert_len);
		if (key_cert) {
			pfw_read(key_cert_fp, key_cert, key_cert_len);

			if (strcmp(partition_name, "BL_PRI") == 0) {
				memcpy(pubkey_hash, key_cert + 0x2C0, sizeof(pubkey_hash));
			} else if ((strcmp(partition_name, "FW1") == 0) || (strcmp(partition_name, "FW2") == 0)) {
				memcpy(pubkey_hash, key_cert + 0x2E0, sizeof(pubkey_hash));
			}

			free(key_cert);
		} else {
			printf("ERROR: malloc\n\r");
			pfw_close(key_cert_fp);
			return -1;
		}
		pfw_close(key_cert_fp);
	} else {
		printf("ERROR: pfw_open\n\r");
		return -1;
	}

	memcpy(pubkey, manifest + 0x124, sizeof(pubkey));
	uint32_t manifest_content_len = 0x3E0;
	memcpy(signature, manifest + manifest_content_len, sizeof(signature));

	device_mutex_lock(RT_DEV_LOCK_CRYPTO);
	if (hal_crypto_engine_init() == SUCCESS) {
		hal_crypto_sha2_256_init();
		hal_crypto_sha2_256_update(pubkey, sizeof(pubkey));
		hal_crypto_sha2_256_final(sha256_hash);
		device_mutex_unlock(RT_DEV_LOCK_CRYPTO);
	} else {
		device_mutex_unlock(RT_DEV_LOCK_CRYPTO);
		printf("ERROR: hal_crypto_engine_init\n\r");
		return -1;
	}

	if (memcmp(pubkey_hash, sha256_hash, 32) != 0) {
		printf("ERROR: compare pubkey hash\n\r");
		return -1;
	}

	device_mutex_lock(RT_DEV_LOCK_CRYPTO);
	if (hal_eddsa_engine_init(EDDSA_HASH_CRYPTO_HW_SEL_EN) == SUCCESS) {
		int ret = hal_eddsa_sign_verify(signature, manifest, pubkey, manifest_content_len, EDDSA_FLOW_AUTOFLOW, ENABLE);
		device_mutex_unlock(RT_DEV_LOCK_CRYPTO);
		if (ret != SUCCESS) {
			printf("ERROR: hal_eddsa_sign_verify\n\r");
			return -1;
		}
	} else {
		device_mutex_unlock(RT_DEV_LOCK_CRYPTO);
		printf("ERROR: hal_eddsa_engine_init\n\r");
		return -1;
	}

	return 0;
}

/**
 * @brief      Verify public key and signature in the manifest of bootloader or firmware in flash
 * @param[in]  partition_name: the partition name of bootloader or firmware to be verified. It could be BL_PRI, FW1 or FW2.
 * @return     0: if public key and signature verification is SUCCESS
 * @return     -1: if any errors duing public key and signature verification
 */
int ota_verify_flash_signature(char *partition_name)
{
	int ret = 0;

	if (!((strcmp(partition_name, "BL_PRI") == 0) || (strcmp(partition_name, "FW1") == 0) || (strcmp(partition_name, "FW2") == 0))) {
		printf("ERROR: partition name\n\r");
		return -1;
	}

	void *partition_fp = pfw_open(partition_name, M_RAW | M_RDONLY);
	if (partition_fp) {
		uint32_t manifest_len = 0x3E0 + 64;
		uint8_t *manifest = (uint8_t *) malloc(manifest_len);
		if (manifest) {
			pfw_read(partition_fp, manifest, manifest_len);
			pfw_close(partition_fp);
			ret = ota_verify_signature(partition_name, manifest);
			free(manifest);
		} else {
			printf("ERROR: malloc\n\r");
			pfw_close(partition_fp);
			return -1;
		}
	} else {
		printf("ERROR: pfw_open\n\r");
		return -1;
	}

	return ret;
}

int ota_flash_NOR(uint32_t target_fw_idx, uint32_t total_blocks, uint32_t cur_block, uint8_t *buf, uint32_t data_len, _file_checksum file_checksum)
{
	static uint32_t target_fw_addr = 0;
	static uint32_t target_fw_len = 0;
#if USE_CHECKSUM
	static uint32_t flash_checksum = 0;
#endif
	static uint8_t label_backup[8];
	uint8_t label_readback[8];
	flash_t flash;
	int ret = 0;

	// for first block
	if (0 == cur_block) {
		device_mutex_lock(RT_DEV_LOCK_FLASH);
		if (OTA_FW1 == target_fw_idx) {
			// fw1 record in partition table
			flash_read_word(&flash, 0x2060, &target_fw_addr);
			flash_read_word(&flash, 0x2064, &target_fw_len);
		} else if (OTA_FW2 == target_fw_idx) {
			// fw2 record in partition table
			flash_read_word(&flash, 0x2080, &target_fw_addr);
			flash_read_word(&flash, 0x2084, &target_fw_len);
		} else if (OTA_BL_PRI == target_fw_idx) { //BL_PRI
			flash_read_word(&flash, 0x2020, &target_fw_addr);
			flash_read_word(&flash, 0x2024, &target_fw_len);
		} else if (OTA_ISP_IQ == target_fw_idx) { //ISP_IQ
			flash_read_word(&flash, 0x20a0, &target_fw_addr);
			flash_read_word(&flash, 0x20a4, &target_fw_len);
		} else if (OTA_NN_MDL == target_fw_idx) { //NN_MDL
			flash_read_word(&flash, 0x20c0, &target_fw_addr);
			flash_read_word(&flash, 0x20c4, &target_fw_len);
		}
		device_mutex_unlock(RT_DEV_LOCK_FLASH);
		printf("\n\r[%s] target_fw_addr=0x%x, target_fw_len=0x%x\n\r", __FUNCTION__, target_fw_addr, target_fw_len);
		if ((total_blocks * NOR_BLOCK_SIZE) > target_fw_len) {
			ret = -1;
			goto exit;
		}

		memcpy(label_backup, buf, 8); // save 8-bytes fw label
		memset(buf, 0xFF, 8); // not flash write 8-bytes fw label
#if USE_CHECKSUM
		flash_checksum = 0;
#endif
	}

	// flash write
	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_erase_sector(&flash, target_fw_addr + cur_block * NOR_BLOCK_SIZE);
	if (flash_burst_write(&flash, target_fw_addr + cur_block * NOR_BLOCK_SIZE, data_len, buf) < 0) {
		printf("\n\r[%s] flash write failed", __FUNCTION__);
		device_mutex_unlock(RT_DEV_LOCK_FLASH);
		ret = -1;
		goto exit;
	}
	device_mutex_unlock(RT_DEV_LOCK_FLASH);

#if USE_CHECKSUM
	// read flash data back and calculate checksum
	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_stream_read(&flash, target_fw_addr + cur_block * NOR_BLOCK_SIZE, data_len, buf);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);
	for (int i = 0; i < data_len; i ++) {
		if ((0 == cur_block) && (i < 8)) {
			flash_checksum += label_backup[i];
		} else {
			flash_checksum += buf[i];
		}
	}
#endif

	// for final block
	if (cur_block == (total_blocks - 1)) {
#if USE_CHECKSUM
		printf("\n\rflash checksum 0x%8x attached checksum 0x%8x", flash_checksum, file_checksum.u);

		if (file_checksum.u != flash_checksum) {
			printf("\n\r[%s] The checksume is wrong!\n\r", __FUNCTION__);
			ret = -1;
			goto exit;
		}
#endif
		// write back 8-bytes fw label
		printf("\n\r[%s] Append FW label", __FUNCTION__);
		device_mutex_lock(RT_DEV_LOCK_FLASH);
		if (flash_burst_write(&flash, target_fw_addr, 8, label_backup) < 0) {
			printf("\n\r[%s] flash write failed", __FUNCTION__);
			ret = -1;
		}
		flash_stream_read(&flash, target_fw_addr, 8, label_readback);
		device_mutex_unlock(RT_DEV_LOCK_FLASH);

		printf("\n\r[%s] FW label:\n\r", __FUNCTION__);
		for (int i = 0; i < 8; i ++) {
			printf(" %02X", label_readback[i]);
		}
		printf("\n\r");
	}

exit:

	return ret;
}

int ota_flash_NAND(uint32_t target_fw_idx, uint32_t total_blocks, uint32_t cur_block, uint8_t *buf, uint32_t data_len, _file_checksum file_checksum)
{
#if USE_CHECKSUM
	static uint32_t flash_checksum = 0;
#endif
	static uint8_t partition_data[2112] __attribute__((aligned(32)));
//	uint8_t data[2112] __attribute__((aligned(32)));
//	uint8_t data_r[2112] __attribute__((aligned(32)));
//	uint8_t *partition_data;
	uint8_t *data;
	uint8_t *data_r;
//	partition_data = update_malloc(2112);
	data = update_malloc(2112);
	data_r = update_malloc(2112);
	uint32_t crc_out = 0;
	uint32_t crypto_ret;
	int block_w_nub = 24;//start  form 24
	int block_used = 0 ;
	int success = 0;
	int fail = 0;
	int ret = 0;
	int partition_valid_block = 0 ;
	static uint8_t type_id0 = 0;
	static uint8_t type_id1 = 0;
	int partition_start_block = 16 ; //B-cut:20

	if (IS_CUT_B(hal_sys_get_rom_ver())) {
		partition_start_block = 20 ;
	}

	snand_t flash;
	snand_init(&flash);
	snand_global_unlock();


	// for first block
	if (0 == cur_block) {
		//read partition_table block16-23
		for (int i = partition_start_block; i < 24; i++) {
			snand_page_read(&flash, i * 64, 2048 + 4, &data_r[0]);
			if ((data_r[2048] == 0xff) && (data_r[2049] == 0xc4)) {  //((data_r[2048] == 0xff) && (data_r[2053] == 0xc4) && (data_r[2054] == 0xd9)) {
				memcpy(partition_data, data_r, 2112);
				partition_valid_block = i;
				success = success + 1;
			} else {
				printf("\n\r Block %d  read read partition_table fail !\n\r", i);
				printf("spare= 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n\r", data_r[2048], data_r[2049], data_r[2050], data_r[2051], data_r[2052], data_r[2053], data_r[2054],
					   data_r[2055]);

			}
			if (success == 2) {
				break;
			}
			if ((i == 23) & (success == 0)) {
				printf("\n\r[%s] Read partition_table is wrong!\n\r", __FUNCTION__);
				ret = -1;
				goto exit;

			}
		}

		//check have 2 partition_table
		if (success == 1) {
			printf("Just 1 partition_table! \n\r");
			for (int i = partition_start_block; i < 24; i++) {
				if (i != partition_valid_block) {
					snand_erase_block(&flash, i * 64);
					snand_page_write(&flash, i * 64, 2048 + 4, &partition_data[0]);
					snand_page_read(&flash, i * 64, 2048 + 4, &data_r[0]);
					if (memcmp(partition_data, data_r, (2048 + 4)) != 0) {
						printf("bolck %d write fail! \n\r", i);
						snand_erase_block(&flash, i * 64);
						data_r[2048] = 0;
						snand_page_write(&flash, i * 64, 2048 + 4, &data_r[0]);
					} else { //success
						break;
					}
				}
			}
		}

#if USE_CHECKSUM
		flash_checksum = 0;
#endif
		memset(data, 0xff, 2112);
		int record_nub = 0;
		if (OTA_FW1 == target_fw_idx) { //FW1
			type_id0 = 0xc7;
			type_id1 = 0xc1;
		} else if (OTA_FW2 == target_fw_idx) { //FW2
			type_id0 = 0xc8;
			type_id1 = 0xb9;
		} else if (OTA_BL_PRI == target_fw_idx) { //BL_PRI
			type_id0 = 0xc5;
			type_id1 = 0xd1;
		} else if (OTA_ISP_IQ == target_fw_idx) { //ISP_IQ
			type_id0 = 0xce;
			type_id1 = 0x89;
		} else if (OTA_NN_MDL == target_fw_idx) { //NN_MDL
			type_id0 = 0xcf;
			type_id1 = 0x81;
		} else if (OTA_CER == target_fw_idx) { //CER
			type_id0 = 0xc2;
			type_id1 = 0xe9;
		} else {
			printf("\n\r[%s] The target_fw_idx is wrong!\n\r", __FUNCTION__);
			ret = -1;
			goto exit;
		}

		// clear target_fw record in partition table
		for (int i = 0; i < 16; i++) {
			if ((partition_data[i * 128 + 4] != type_id0) && (partition_data[i * 128 + 5] != type_id1)) {
				memcpy(&data[record_nub * 128], &partition_data[i * 128], 128);
				record_nub = record_nub + 1;
			}
		}
		//update partition_table
		memcpy(partition_data, data, 2048);
		//update partition table CRC16
		crypto_ret = hal_crypto_engine_init();
		if (crypto_ret != SUCCESS) {
			printf("Crypto Init Failed!%d\r\n", crypto_ret);
			return -1;
		}
		crypto_ret =  hal_crypto_crc16_division(partition_data, 2048, &crc_out);
		if (crypto_ret != SUCCESS) {
			printf("CRC failed\r\n");
			// ignore error and go-on
			return -1;
		}

		printf("crc_out = 0x%x \n\r", crc_out);
		partition_data[2050] = (uint8_t)(crc_out & 0xff);
		partition_data[2051] = (uint8_t)(crc_out >> 8);

		//update partition table block16-23
		success = 0;
		fail = 0;
		for (int i = partition_start_block; i < 24; i++) {
			fail = 0;
			snand_erase_block(&flash, i * 64);
			snand_page_write(&flash, i * 64, 2048 + 4, &partition_data[0]);
			snand_page_read(&flash, i * 64, 2048 + 4, &data_r[0]);
			if (memcmp(partition_data, data_r, (2048 + 4)) != 0) {
				printf("bolck %d write fail! \n\r", i);
				fail = 1;
				snand_erase_block(&flash, i * 64);
				data_r[2048] = 0;
				snand_page_write(&flash, i * 64, 2048 + 4, &data_r[0]);
			}
			if (fail == 0) {
				success = success + 1;
			}
			if (success == 2) {
				break;
			}
		}
	}
//	for (int i = 0; i < 2048; i++) {
//		printf("[%d]= 0x%x\n\r",i,partition_data[i]);
//	}
	// find a empty block
	for (int i = block_w_nub; i < 2048; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 48; k++) {
				if (block_w_nub == ((partition_data[j * 128 + 32 + k * 2 + 1] << 8) + partition_data[j * 128 + 32 + k * 2])) {
					//printf("block %d is used\n\r", block_w_nub);
					block_w_nub = block_w_nub + 1;
					block_used = 1 ;
					break;
				}
			}
			if (block_used == 1) {
				break;
			}
		}
		if (block_used == 0) {
			printf("block %d is empty\n\r", block_w_nub);
			// flash write
			memset(data, 0xff, 2112);
//			data[2048 + 1] = 0x87;
//			data[2048 + 3] = 0x35;
			/*			if (1 == target_fw_idx) {
			//				data[2048 + 5] = 0xc7;
			//				data[2048 + 6] = 0xc1;
							data[2048 + 1] = 0xc7;
						} else if (2 == target_fw_idx) {
			//				data[2048 + 5] = 0xc8;
			//				data[2048 + 6] = 0xb9;
							data[2048 + 1] = 0xc8;
						}*/
			data[2048 + 1] = type_id0;

			fail = 0;
			snand_erase_block(&flash, i * 64);
			for (int j = 0; j < 64; j++) {
				memcpy(data, &buf[2048 * j], 2048);
				snand_page_write(&flash, block_w_nub * 64 + j, 2048 + 4, &data[0]);
				snand_page_read(&flash, block_w_nub * 64 + j, 2048 + 4, &data_r[0]);
				if (memcmp(data, data_r, (2048 + 4)) != 0) {
					printf("bolck %d write fail! \n\r", i);
					fail = 1;
					snand_erase_block(&flash, block_w_nub * 64);
					data_r[2048] = 0;
					snand_page_write(&flash, block_w_nub * 64, 2048 + 4, &data_r[0]);
					block_w_nub = block_w_nub + 1;
					break;
				}
			}
			if (fail == 0) {
				break;    //success
			}
		}
		block_used = 0 ;
		if (i == 2047) {
			printf("all block is not empty , OTA fail!\n\r");
			ret = -1;
			goto exit;
		}
	}

#if USE_CHECKSUM
	for (int i = 0; i < data_len; i ++) {
		flash_checksum += buf[i];
	}
	// for final block
	if (cur_block == (total_blocks - 1)) {
		printf("\n\rflash checksum 0x%8x attached checksum 0x%8x", flash_checksum, file_checksum.u);
		if (file_checksum.u != flash_checksum) {
			printf("\n\r[%s] The checksume is wrong!\n\r", __FUNCTION__);
			ret = -1;
			goto exit;
		}
	}
#endif

	printf("block %d write success\n\r", block_w_nub);

	//update partition_table
	if ((cur_block % 48) == 0) {
		for (int i = 0; i < 16; i++) {
			if ((partition_data[i * 128 + 4] == 0xff) && (partition_data[i * 128 + 5] == 0xff)) {
				printf("partition_table record %d is empty \n\r", i);

				partition_data[i * 128 + 4] = type_id0;
				partition_data[i * 128 + 5] = type_id1;

				partition_data[i * 128 + 6] = total_blocks & 0xff;
				partition_data[i * 128 + 7] = (total_blocks >> 8) & 0xff;
				partition_data[i * 128 + 8] = (cur_block / 48) & 0xff;
				partition_data[i * 128 + 9] = ((cur_block / 48) >> 8) & 0xff;
				partition_data[i * 128 + 0x20] = block_w_nub & 0xff;
				partition_data[i * 128 + 0x20 + 1] = (block_w_nub >> 8) & 0xff;
				break;
			}
		}
	} else {
		for (int i = 0; i < 16; i++) {
			if ((partition_data[i * 128 + 4] == type_id0) && (partition_data[i * 128 + 5] == type_id1)) {
				for (int j = 0; j < 48; j++) {
					if ((partition_data[(i * 128) + 0x20 + (2 * j)] == 0xff) && (partition_data[(i * 128) + 0x20 + (2 * j) + 1] == 0xff)) {
						partition_data[(i * 128) + 0x20 + (2 * j)] = block_w_nub & 0xff;
						partition_data[(i * 128) + 0x20 + (2 * j) + 1] = (block_w_nub >> 8) & 0xff;
						break;
					}
				}
			}
		}
	}

	// for final block update magic number
	if (cur_block == (total_blocks - 1)) {
		for (int i = 0; i < 16; i++) {
			if ((partition_data[i * 128 + 4] == type_id0) && (partition_data[i * 128 + 5] == type_id1)) {
				partition_data[i * 128] = 0x87;
				partition_data[i * 128 + 2] = 0x35;
				printf("partition_table update magic number OK\n\r");
			}
		}
		//update partition table CRC16
		ret = hal_crypto_engine_init();
		if (ret != SUCCESS) {
			printf("boot_load: Crypto Init Failed!%d\r\n", ret);
			ret = _ERRNO_BOOT_SB_CRYPTO_INIT_FAIL;
			return -1;
		}
		crypto_ret =  hal_crypto_crc16_division(partition_data, 2048, &crc_out);
		if (crypto_ret != SUCCESS) {
			printf("CRC failed\r\n");
			// ignore error and go-on
			return -1;
		}

		printf("crc_out = 0x%x \n\r", crc_out);
		partition_data[2050] = (uint8_t)(crc_out & 0xff);
		partition_data[2051] = (uint8_t)(crc_out >> 8);
		//update partition table block16-23
		success = 0;
		fail = 0;
		for (int i = partition_start_block; i < 24; i++) {
			fail = 0;
			snand_erase_block(&flash, i * 64);
			snand_page_write(&flash, i * 64, 2048 + 4, &partition_data[0]);
			snand_page_read(&flash, i * 64, 2048 + 4, &data_r[0]);
			if (memcmp(partition_data, data_r, (2048 + 4)) != 0) {
				printf("bolck %d write fail! \n\r", i);
				fail = 1;
				snand_erase_block(&flash, i * 64);
				data_r[2048] = 0;
				snand_page_write(&flash, i * 64, 2048 + 4, &data_r[0]);
			}
			if (fail == 0) {
				success = success + 1;
			}
			if (success == 2) {
				break;
			}
		}
		if (IS_CUT_B(hal_sys_get_rom_ver())) { //B-cut ota BL_PRI rewrite partition_boot block 16-19
			if ((OTA_BL_PRI == target_fw_idx) | (OTA_ISP_IQ == target_fw_idx) | (OTA_CER == target_fw_idx)) { //BL_PRI or ISP_IQ or CER
				partition_start_block = 16 ;
				success = 0;
				for (int i = partition_start_block; i < 20; i++) {
					fail = 0;
					snand_erase_block(&flash, i * 64);
					snand_page_write(&flash, i * 64, 2048 + 4, &partition_data[0]);
					snand_page_read(&flash, i * 64, 2048 + 4, &data_r[0]);
					if (memcmp(partition_data, data_r, (2048 + 4)) != 0) {
						printf("bolck %d write fail! \n\r", i);
						fail = 1;
						snand_erase_block(&flash, i * 64);
						data_r[2048] = 0;
						snand_page_write(&flash, i * 64, 2048 + 4, &data_r[0]);
					}
					if (fail == 0) {
						success = success + 1;
					}
					if (success == 2) {
						break;
					}
				}
			}
		}

	}


exit:
//	update_free(partition_data);
	update_free(data);
	update_free(data_r);
	return ret;
}

void *update_malloc(unsigned int size)
{
	return pvPortMalloc(size);
}

void update_free(void *buf)
{
	vPortFree(buf);
}

void ota_platform_reset(void)
{
	sys_reset();

	while (1) {
		osDelay(1000);
	}
}

int update_ota_connect_server(update_cfg_local_t *cfg)
{
	struct sockaddr_in server_addr;
	int server_socket;

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0) {
		printf("\n\r[%s] Create socket failed", __FUNCTION__);
		return -1;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = cfg->ip_addr;
	server_addr.sin_port = cfg->port;

	if (connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		printf("\n\r[%s] Socket connect failed", __FUNCTION__);
		return -1;
	}

	return server_socket;
}

static void update_ota_local_task(void *param)
{
	int server_socket = -1;
	uint8_t *buf;
	int read_bytes = 0;
	uint32_t idx = 0;
	update_cfg_local_t *cfg = (update_cfg_local_t *)param;
	uint32_t file_info[3];
	int ret = -1 ;
	uint8_t cur_fw_idx = 0, target_fw_idx = 0;
	uint32_t ota_len = 0;
	_file_checksum file_checksum;
	file_checksum.u = 0;
	uint32_t buf_size = 0;
	uint8_t boot_sel = -1;
	uint32_t total_blocks = 0, cur_block = 0;

#if defined(configENABLE_TRUSTZONE) && (configENABLE_TRUSTZONE == 1)
	rtw_create_secure_context(configMINIMAL_SECURE_STACK_SIZE);
#endif
	printf("\n\r[%s] Update task start", __FUNCTION__);

	boot_sel = sys_get_boot_sel();
	if (0 == boot_sel) {
		// boot from NOR flash
		buf_size = NOR_BLOCK_SIZE;
	} else if (1 == boot_sel) {
		// boot from NAND flash
		buf_size = NAND_BLOCK_SIZE;
	}

	buf = update_malloc(buf_size);
	if (!buf) {
		printf("\n\r[%s] Alloc buffer failed", __FUNCTION__);
		goto update_ota_exit;
	}

	// Connect server
	server_socket = update_ota_connect_server(cfg);
	if (server_socket == -1) {
		goto update_ota_exit;
	}

	// Get file size from DownloadServer.
	memset(file_info, 0, sizeof(file_info));
	if (file_info[0] == 0) {
		printf("\n\r[%s] Read info first", __FUNCTION__);
		read_bytes = read(server_socket, file_info, sizeof(file_info));
		if (read_bytes <= 0) {
			printf("\n\r[%s] Read socket failed or socket closed", __FUNCTION__);
			goto update_ota_exit;
		}
		// !X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X
		// !W checksum !W padding 0 !W file size !W
		// !X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X
		printf("\n\r[%s] info %d bytes", __FUNCTION__, read_bytes);
		printf("\n\r[%s] tx file size 0x%x", __FUNCTION__, file_info[2]);
		if (file_info[2] == 0) {
			printf("\n\r[%s] No file size", __FUNCTION__);
			goto update_ota_exit;
		} else {
			ota_len = file_info[2];
			total_blocks = (ota_len + buf_size - 1) / buf_size;
		}
	}

	cur_fw_idx = hal_sys_get_ld_fw_idx();
	printf("\n\r[%s] Current firmware index is %d\r\n", __FUNCTION__, cur_fw_idx);
	if (1 == cur_fw_idx) {
		target_fw_idx = OTA_FW2;
	} else if (2 == cur_fw_idx) {
		target_fw_idx = OTA_FW1;
	} else {
		goto update_ota_exit;
	}

	// Write New FW sector
	printf("\n\r[%s] Start to read data %d bytes\r\n", __FUNCTION__, ota_len);
	while (1) {
		int rest_len = ota_len - idx;
		int data_len = rest_len > buf_size ? buf_size : rest_len;

		memset(buf, 0, buf_size);
		read_bytes = 0;
		while (read_bytes < data_len) {
			read_bytes += read(server_socket, &buf[read_bytes], data_len - read_bytes);
			if (read_bytes < 0) {
				printf("\n\r[%s] Read socket failed", __FUNCTION__);
				goto update_ota_exit;
			}
		}
		if (read_bytes == 0) {
			break;    // Read end
		}

		printf("..");

		if ((idx + read_bytes) > ota_len) {
			printf("\n\r[%s] Redundant bytes received", __FUNCTION__);
			read_bytes = ota_len - idx;
			data_len = read_bytes;
		}

#if USE_CHECKSUM
		// checksum attached at file end
		if ((idx + read_bytes) > (ota_len - 4)) {
			file_checksum.c[0] = buf[read_bytes - 4];
			file_checksum.c[1] = buf[read_bytes - 3];
			file_checksum.c[2] = buf[read_bytes - 2];
			file_checksum.c[3] = buf[read_bytes - 1];
		}
#endif
		// check final block
		cur_block = idx / buf_size;
		if (cur_block == (total_blocks - 1)) {
			data_len -= 4; // remove final 4 bytes checksum
			memset(buf + data_len, 0xFF, buf_size - data_len);
		}

		if (0 == boot_sel) {
			ret = ota_flash_NOR(target_fw_idx, total_blocks, cur_block, buf, data_len, file_checksum);
		} else if (1 == boot_sel) {
			ret = ota_flash_NAND(target_fw_idx, total_blocks, cur_block, buf, data_len, file_checksum);
		}

		if (ret < 0) {
			printf("\n\r[%s] ota flash failed", __FUNCTION__);
			goto update_ota_exit;
		}

		idx += read_bytes;

		if (idx == ota_len) {
			break;
		}
	}
	printf("\n\rRead data finished\r\n");

update_ota_exit:
	if (buf) {
		update_free(buf);
	}
	if (server_socket >= 0) {
		close(server_socket);
	}
	if (param) {
		update_free(param);
	}
	TaskOTA = NULL;
	printf("\n\r[%s] Update task exit", __FUNCTION__);
	if (!ret) {
		printf("\n\r[%s] Ready to reboot", __FUNCTION__);
		osDelay(100);
		ota_platform_reset();
	}
	vTaskDelete(NULL);
	return;
}

int update_ota_local(char *ip, int port)
{
	update_cfg_local_t *pUpdateCfg;

	if (TaskOTA) {
		printf("\n\r[%s] Update task has created.", __FUNCTION__);
		return 0;
	}
	pUpdateCfg = update_malloc(sizeof(update_cfg_local_t));
	if (pUpdateCfg == NULL) {
		printf("\n\r[%s] Alloc update cfg failed", __FUNCTION__);
		return -1;
	}
	pUpdateCfg->ip_addr = inet_addr(ip);
	pUpdateCfg->port = ntohs(port);

	if (xTaskCreate(update_ota_local_task, "OTA_server", STACK_SIZE, pUpdateCfg, TASK_PRIORITY, &TaskOTA) != pdPASS) {
		update_free(pUpdateCfg);
		printf("\n\r[%s] Create update task failed", __FUNCTION__);
	}
	return 0;
}

void cmd_update(int argc, char **argv)
{
	int port;
	if (argc != 3) {
		printf("\n\r[%s] Usage: update IP PORT", __FUNCTION__);
		return;
	}
	port = atoi(argv[2]);
	update_ota_local(argv[1], port);
}

// choose the activated image. 0: default image / 1: upgrade image
void cmd_ota_image(bool cmd)
{
	if (cmd == 1) {
		sys_recover_ota_signature();
	} else {
		sys_clear_ota_signature();
	}
}

#ifdef HTTP_OTA_UPDATE
static char *redirect = NULL;
static int redirect_len;
static uint16_t redirect_server_port;
static char *redirect_server_host = NULL;
static char *redirect_resource = NULL;
int parser_url(char *url, char *host, uint16_t *port, char *resource)
{
	if (url) {
		char *http = NULL, *pos = NULL;

		http = strstr(url, "http://");
		if (http) { // remove http
			url += strlen("http://");
		}
		memset(host, 0, redirect_len);

		pos = strstr(url, ":");	// get port
		if (pos) {
			memcpy(host, url, (pos - url));
			pos += 1;
			*port = atoi(pos);
		} else {
			pos = strstr(url, "/");
			if (pos) {
				memcpy(host, url, (pos - url));
				url = pos;
			}
			*port = 80;
		}
		printf("server: %s\n\r", host);
		printf("port: %d\n\r", *port);

		memset(resource, 0, redirect_len);
		pos = strstr(url, "/");
		if (pos) {
			memcpy(resource, pos + 1, strlen(pos + 1));
		}
		printf("resource: %s\n\r", resource);

		return 0;
	}
	return -1;
}


/******************************************************************************************************************
** Function Name  : update_ota_http_connect_server
** Description    : connect to the OTA server
** Input          : server_socket: the socket used
**					host: host address of the OTA server
**					port: port of the OTA server
** Return         : connect ok:	socket value
**					Failed:		-1
*******************************************************************************************************************/
int update_ota_http_connect_server(int server_socket, char *host, int port)
{
	struct sockaddr_in server_addr;
	struct hostent *server;

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0) {
		printf("\n\r[%s] Create socket failed", __FUNCTION__);
		return -1;
	}

	server = gethostbyname(host);
	if (server == NULL) {
		printf("[ERROR] Get host ip failed\n");
		return -1;
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	memcpy(&server_addr.sin_addr.s_addr, server->h_addr, 4);

	if (connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		printf("\n\r[%s] Socket connect failed", __FUNCTION__);
		return -1;
	}

	return server_socket;
}

/******************************************************************************************************************
** Function Name  : parse_http_response
** Description    : Parse the http response to get some useful parameters
** Input          : response	: The http response got from server
**					response_len: The length of http response
**					result		: The struct that store the usful infor about the http response
** Return         : Parse OK:	1 -> Only got the status code
**								3 -> Got the status code and content_length, but didn't get the full header
**								4 -> Got all the information needed
**					Failed:		-1
*******************************************************************************************************************/
int parse_http_response(uint8_t *response, uint32_t response_len, http_response_result_t *result)
{
	uint32_t i, p, q, m;
	uint32_t header_end = 0;

	//Get status code
	if (0 == result->parse_status) { //didn't get the http response
		uint8_t status[4] = {0};
		i = p = q = m = 0;
		for (; i < response_len; ++i) {
			if (' ' == response[i]) {
				++m;
				if (1 == m) {//after HTTP/1.1
					p = i;
				} else if (2 == m) { //after status code
					q = i;
					break;
				}
			}
		}
		if (!p || !q || q - p != 4) { //Didn't get the status code
			return -1;
		}
		memcpy(status, response + p + 1, 3); //get the status code
		result->status_code = atoi((char const *)status);
		if (result->status_code == 200) {
			result->parse_status = 1;
		} else if (result->status_code == 302) {
			char *tmp = NULL;
			const uint8_t *location1 = (uint8_t *)"LOCATION";
			const uint8_t *location2 = (uint8_t *)"Location";
			printf("response 302:%s \r\n", response);

			if ((tmp = strstr((char const *)response, (char const *)location1)) || (tmp = strstr((char const *)response, (char const *)location2))) {
				redirect_len = strlen(tmp + 10);
				printf("Location len = %d\r\n", redirect_len);
				if (redirect == NULL) {
					redirect = update_malloc(redirect_len);
					if (redirect == NULL) {
						return -1;
					}
				}
				memset(redirect, 0, redirect_len);
				memcpy(redirect, tmp + 10, strlen(tmp + 10));
			}

			if (redirect_server_host == NULL) {
				redirect_server_host = update_malloc(redirect_len);
				if (redirect_server_host == NULL) {
					return -1;
				}
			}

			if (redirect_resource == NULL) {
				redirect_resource = update_malloc(redirect_len);
				if (redirect_resource == NULL) {
					return -1;
				}
			}

			memset(redirect_server_host, 0, redirect_len);
			memset(redirect_resource, 0, redirect_len);
			if (parser_url(redirect, redirect_server_host, &redirect_server_port, redirect_resource) < 0) {
				return -1;
			}
			return -1;
		} else {
			printf("\n\r[%s] The http response status code is %d", __FUNCTION__, result->status_code);
			return -1;
		}
	}

	//if didn't receive the full http header
	if (3 == result->parse_status) { //didn't get the http response
		//p = q = 0;
		for (i = 0; i < response_len; ++i) {
			if (response[i] == '\r' && response[i + 1] == '\n' &&
				response[i + 2] == '\r' && response[i + 3] == '\n') { //the end of header
				header_end = i + 4;
				result->parse_status = 4;
				result->header_len = header_end;
				result->body = response + header_end;
				break;
			}
		}
		if (3 == result->parse_status) {//Still didn't receive the full header
			result->header_bak = update_malloc(HEADER_BAK_LEN + 1);
			memset(result->header_bak, 0, strlen((char const *)result->header_bak));
			memcpy(result->header_bak, response + response_len - HEADER_BAK_LEN, HEADER_BAK_LEN);
		}
	}

	//Get Content-Length
	if (1 == result->parse_status) { //didn't get the content length
		const uint8_t *content_length_buf1 = (uint8_t *)"CONTENT-LENGTH";
		const uint8_t *content_length_buf2 = (uint8_t *)"Content-Length";
		const uint8_t *content_length_buf3 = (uint8_t *)"content-length";
		const uint32_t content_length_buf_len = strlen((char const *)content_length_buf1);
		p = q = 0;

		for (i = 0; i < response_len; ++i) {
			if (response[i] == '\r' && response[i + 1] == '\n') {
				q = i;//the end of the line
				if (!memcmp(response + p, content_length_buf1, content_length_buf_len) ||
					!memcmp(response + p, content_length_buf2, content_length_buf_len) ||
				    !memcmp(response + p, content_length_buf3, content_length_buf_len)) { //get the content length
					int j1 = p + content_length_buf_len, j2 = q - 1;
					while (j1 < q && (*(response + j1) == ':' || *(response + j1) == ' ')) {
						++j1;
					}
					while (j2 > j1 && *(response + j2) == ' ') {
						--j2;
					}
					uint8_t len_buf[12] = {0};
					if ((j2 - j1 + 1) <= sizeof(len_buf)) {
						memcpy(len_buf, response + j1, j2 - j1 + 1);
					} else {
						return -1;
					}
					result->body_len = atoi((char const *)len_buf);
					result->parse_status = 2;
				}
				p = i + 2;
			}
			if (response[i] == '\r' && response[i + 1] == '\n' &&
				response[i + 2] == '\r' && response[i + 3] == '\n') { //Get the end of header
				header_end = i + 4; //p is the start of the body
				if (result->parse_status == 2) { //get the full header and the content length
					result->parse_status = 4;
					result->header_len = header_end;
					result->body = response + header_end;
				} else { //there are no content length in header
					printf("\n\r[%s] No Content-Length in header", __FUNCTION__);
					return -1;
				}
				break;
			}
		}

		if (1 == result->parse_status) {//didn't get the content length and the full header
			result->header_bak = update_malloc(HEADER_BAK_LEN + 1);
			memset(result->header_bak, 0, strlen((char const *)result->header_bak));
			memcpy(result->header_bak, response + response_len - HEADER_BAK_LEN, HEADER_BAK_LEN);
		} else if (2 == result->parse_status) { //didn't get the full header but get the content length
			result->parse_status = 3;
			result->header_bak = update_malloc(HEADER_BAK_LEN + 1);
			memset(result->header_bak, 0, strlen((char const *)result->header_bak));
			memcpy(result->header_bak, response + response_len - HEADER_BAK_LEN, HEADER_BAK_LEN);
		}
	}

	return result->parse_status;
}

int http_update_ota(char *host, int port, char *resource)
{
	int server_socket = -1;
	uint8_t *buf = NULL, *request = NULL;
	int read_bytes = 0;
	int read_rtn = 0;
	int ret = -1;
	uint8_t cur_fw_idx = 0, target_fw_idx = 0;
	uint32_t ota_len = 0;
	http_response_result_t rsp_result = {0};
	_file_checksum file_checksum;
	file_checksum.u = 0;
	uint32_t buf_size = 0;
	uint8_t boot_sel = -1;
	uint32_t total_blocks = 0, cur_block = 0;
	uint32_t idx = 0;
	uint32_t data_len = 0;

restart_http_ota:
	redirect_server_port = 0;
	memset(&rsp_result, 0, sizeof(rsp_result));

	boot_sel = sys_get_boot_sel();
	if (0 == boot_sel) {
		// boot from NOR flash
		buf_size = NOR_BLOCK_SIZE;
	} else if (1 == boot_sel) {
		// boot from NAND flash
		buf_size = NAND_BLOCK_SIZE;
	}

	buf = update_malloc(buf_size);
	if (!buf) {
		printf("\n\r[%s] Alloc buffer failed", __FUNCTION__);
		goto update_ota_exit;
	}

	// Connect server
	server_socket = update_ota_http_connect_server(server_socket, host, port);
	if (server_socket == -1) {
		goto update_ota_exit;
	}

	printf("\n\r");

	//send http request
	request = (unsigned char *) update_malloc(strlen("GET /") + strlen(resource) + strlen(" HTTP/1.1\r\nHost: ")
			  + strlen(host) + strlen("\r\n\r\n") + 1);
	sprintf((char *)request, "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", resource, host);

	ret = write(server_socket, request, strlen((char const *)request));
	if (ret < 0) {
		printf("\n\r[%s] Send HTTP request failed", __FUNCTION__);
		goto update_ota_exit;
	}

	while (3 >= rsp_result.parse_status) { //still read header
		if (0 == rsp_result.parse_status) { //didn't get the http response
			memset(buf, 0, buf_size);
			read_bytes = read(server_socket, buf, buf_size);
			if (read_bytes <= 0) {
				printf("\n\r[%s] Read socket failed", __FUNCTION__);
				goto update_ota_exit;
			}

			idx = read_bytes;

			if (parse_http_response(buf, read_bytes, &rsp_result) == -1) {
				goto update_ota_exit;
			}
		} else if ((1 == rsp_result.parse_status) || (3 == rsp_result.parse_status)) { //just get the status code
			memset(buf, 0, buf_size);
			memcpy(buf, rsp_result.header_bak, HEADER_BAK_LEN);
			update_free(rsp_result.header_bak);
			rsp_result.header_bak = NULL;

			read_bytes = read(server_socket, buf + HEADER_BAK_LEN, (buf_size - HEADER_BAK_LEN));
			if (read_bytes <= 0) {
				printf("\n\r[%s] Read socket failed", __FUNCTION__);
				goto update_ota_exit;
			}

			idx = read_bytes + HEADER_BAK_LEN;

			if (parse_http_response(buf, read_bytes + HEADER_BAK_LEN, &rsp_result) == -1) {
				goto update_ota_exit;
			}
		}
	}

	if (0 == rsp_result.body_len) {
		printf("\n\r[%s] New firmware size = 0 !", __FUNCTION__);
		goto update_ota_exit;
	} else {
		printf("\n\r[%s] Download new firmware begin, total size : %d\n\r", __FUNCTION__, rsp_result.body_len);
		ota_len = rsp_result.body_len;
		total_blocks = (ota_len + buf_size - 1) / buf_size;
	}

	cur_fw_idx = hal_sys_get_ld_fw_idx();
	printf("\n\r[%s] Current firmware index is %d\r\n", __FUNCTION__, cur_fw_idx);
	if (1 == cur_fw_idx) {
		target_fw_idx = OTA_FW2;
	} else if (2 == cur_fw_idx) {
		target_fw_idx = OTA_FW1;
	} else {
		goto update_ota_exit;
	}
	

	// read http response body
	read_bytes = idx - rsp_result.header_len;
	if (read_bytes > 0) {
		memcpy(buf, buf + rsp_result.header_len, read_bytes);
		memset(buf + read_bytes, 0, buf_size - read_bytes);
	} else {
		memset(buf, 0, buf_size);
		read_bytes = 0;
	}

	idx = 0;
	while (idx < ota_len) {
		printf("..");
		data_len = ota_len - idx;
		if (data_len > buf_size) {
			data_len = buf_size;
		}

		while (read_bytes < data_len) {
			read_rtn = read(server_socket, &buf[read_bytes], data_len - read_bytes);
			if (read_rtn <= 0) {
				printf("\n\r[%s] Read socket failed", __FUNCTION__);
				goto update_ota_exit;
			}
			read_bytes += read_rtn;
		}

		if ((idx + read_bytes) > ota_len) {
			printf("\n\r[%s] Redundant bytes received", __FUNCTION__);
			read_bytes = ota_len - idx;
			data_len = read_bytes;
		}

#if USE_CHECKSUM
		// checksum attached at file end
		if ((idx + read_bytes) > (ota_len - 4)) {
			file_checksum.c[0] = buf[read_bytes - 4];
			file_checksum.c[1] = buf[read_bytes - 3];
			file_checksum.c[2] = buf[read_bytes - 2];
			file_checksum.c[3] = buf[read_bytes - 1];
		}
#endif
		// check final block
		cur_block = idx / buf_size;
		if (cur_block == (total_blocks - 1)) {
			data_len -= 4; // remove final 4 bytes checksum
			memset(buf + data_len, 0xFF, buf_size - data_len);
		}

		if (0 == boot_sel) {
			ret = ota_flash_NOR(target_fw_idx, total_blocks, cur_block, buf, data_len, file_checksum);
		} else if (1 == boot_sel) {
			ret = ota_flash_NAND(target_fw_idx, total_blocks, cur_block, buf, data_len, file_checksum);
		}

		if (ret < 0) {
			printf("\n\r[%s] ota flash failed", __FUNCTION__);
			goto update_ota_exit;
		}

		idx += read_bytes;

		memset(buf, 0, buf_size);
		read_bytes = 0;
	}
	printf("\n\r[%s] Download new firmware %d bytes completed\n\r", __FUNCTION__, idx);


update_ota_exit:
	if (buf) {
		update_free(buf);
	}
	if (request) {
		update_free(request);
	}
	if (server_socket >= 0) {
		close(server_socket);
	}

	// redirect_server_port != 0 means there is redirect URL can be downloaded
	if (redirect_server_port != 0) {
		host = redirect_server_host;
		resource = redirect_resource;
		port = redirect_server_port;
		printf("\n\r[%s] OTA redirect host: %s, port: %d, resource: %s", __FUNCTION__, host, port, resource);
		goto restart_http_ota;
	}

	if (redirect) {
		update_free(redirect);
	}
	if (redirect_server_host) {
		update_free(redirect_server_host);
	}
	if (redirect_resource) {
		update_free(redirect_resource);
	}

	return ret;
}
#endif

#ifdef EXT_STORAGE_OTA_UPDATE

int ext_storage_update_ota(char *filename)
{
	printf("\n\r[%s] Starting SD card OTA update\n\r", __FUNCTION__);

	int ret = -1;
	FILE *my_file = NULL;
	uint8_t *buf = NULL;
	uint64_t file_size = 0;
	uint32_t buf_size = 0;
	uint32_t idx = 0;
	uint32_t total_blocks = 0;
	uint32_t cur_block = 0;
	int boot_sel = 0;
	uint8_t cur_fw_idx = 0;
	uint8_t target_fw_idx = 0;
	_file_checksum file_checksum;
	file_checksum.u = 0;
	

	// Determine boot selection
	boot_sel = sys_get_boot_sel();
	if (boot_sel == 0) {
		buf_size = NOR_BLOCK_SIZE;
	} else if (boot_sel == 1) {
		buf_size = NAND_BLOCK_SIZE;
	}

	buf = update_malloc(buf_size);
	if (!buf) {
		printf("\n\r[%s] Failed to allocate buffer\n\r", __FUNCTION__);
		goto update_ota_exit;
	}

	// Open the file using fopen
	printf("\n\r[%s] Opening file: %s\n\r", __FUNCTION__, filename);
	my_file = fopen(filename, "rb");
	if (!my_file) {
		printf("\n\r[%s] Failed to open file: %s\n\r", __FUNCTION__, filename);
		goto update_ota_exit;
	}

	printf("\n\r[%s] File opened successfully\n\r", __FUNCTION__);

	// Get file size
	fseek(my_file, 0, SEEK_END);
	file_size = ftell(my_file);
	if (file_size == -1) {
		printf("[%s] Error getting file size\n", __FUNCTION__);
	} else {
		printf("[%s] Detected file size: %llu bytes\n", __FUNCTION__, file_size);
	}
	fseek(my_file, 0, SEEK_SET);
	printf("\n\r[%s] File size: %llu\n\r", __FUNCTION__, file_size);

	// Determine current firmware index
	cur_fw_idx = hal_sys_get_ld_fw_idx();
	printf("\n\r[%s] Current firmware index is %d\n\r", __FUNCTION__, cur_fw_idx);

	if (cur_fw_idx == 1) {
		target_fw_idx = OTA_FW2;
	} else if (cur_fw_idx == 2) {
		target_fw_idx = OTA_FW1;
	} else {
		goto update_ota_exit;
	}

	total_blocks = (file_size + buf_size - 1) / buf_size;

	// Start reading and updating firmware
	printf("\n\r[%s] Start OTA update\n\r", __FUNCTION__);
	#if UPDATE_UPGRADE_PROGRESS_TO_8773
	    uart_resp_get_sys_upgrade((uint8_t) 1, (uint8_t) 0);
		int loop_counter = 0;
	#endif
	while (idx < file_size) {
		#if UPDATE_UPGRADE_PROGRESS_TO_8773
		loop_counter++;
		if (cancel_wifi_upgrade) {
			printf("\n\r[%s] OTA upgrade canceled by user\n\r", __FUNCTION__);
			progress = 0;
			loop_counter = 0;
			ret = -2;
			goto update_ota_exit;
		}
		#endif
		uint32_t rest_len = file_size - idx;
		uint32_t data_len = rest_len > buf_size ? buf_size : rest_len;

		memset(buf, 0, buf_size);
		size_t bytes_read = fread(buf, 1, data_len, my_file);
		if (bytes_read != data_len && bytes_read != 0) {
			printf("\n\r[%s] Insufficient data or read error\n\r", __FUNCTION__);
			goto update_ota_exit;
		}

		// check when file size and read size is equal, and current bytes_read is 0, -4 checksum
		if ((idx == (file_size - 4)) && (bytes_read == 0)) {
			printf("\n\r[%s] OTA update completed successfully\n\r", __FUNCTION__);
			#if UPDATE_UPGRADE_PROGRESS_TO_8773
				uart_resp_get_sys_upgrade((uint8_t) 1, (uint8_t) 100);
			#endif
			ret = 0;
			goto update_ota_exit;
		}
		#if UPDATE_UPGRADE_PROGRESS_TO_8773
		if (file_size > 0) {
			progress = (uint8_t)(((uint64_t)idx * 100) / file_size);
			if (progress > 99) {
				progress = 99;
			}
		}

		if (loop_counter % 10 == 0) {
			uart_resp_get_sys_upgrade((uint8_t) 1, progress);
			printf("[OTA Progress] Sent progress update: %u%% after %d loops\n", progress, loop_counter);
		}
		#endif

		#if UPDATE_UPGRADE_PROGRESS_TO_8773	
		printf("[Firmware updating] ==============================  updating: %u / %llu Bytes (%u%%)\n",idx, file_size, progress);
		#else
		printf("[Firmware updating] ==============================  updating: %u / %llu Bytes \n",idx, file_size);
		#endif

#if USE_CHECKSUM
		if ((idx + data_len) > (file_size - 4)) {
			file_checksum.c[0] = buf[data_len - 4];
			file_checksum.c[1] = buf[data_len - 3];
			file_checksum.c[2] = buf[data_len - 2];
			file_checksum.c[3] = buf[data_len - 1];
		}
#endif

		cur_block = idx / buf_size;
		if (cur_block == (total_blocks - 1)) {
			data_len -= 4; // Remove checksum bytes
			memset(buf + data_len, 0xFF, buf_size - data_len);
		}

		if (boot_sel == 0) {
			ret = ota_flash_NOR(target_fw_idx, total_blocks, cur_block, buf, data_len, file_checksum);
		} else if (boot_sel == 1) {
			ret = ota_flash_NAND(target_fw_idx, total_blocks, cur_block, buf, data_len, file_checksum);
		}

		if (ret < 0) {
			printf("\n\r[%s] OTA flash failed\n\r", __FUNCTION__);
			goto update_ota_exit;
		}

		idx += data_len;
	}

update_ota_exit:
	if (buf) {
		update_free(buf);
	}
	if (my_file) {
		fclose(my_file);
	}
	#if UPDATE_UPGRADE_PROGRESS_TO_8773
	loop_counter = 0;
	progress = 0;
	#endif

	return ret;
}

int ext_storage_update_boot_ota(char *filename)
{
	printf("\n\r[%s] Starting SD Card Bootloader OTA update\n\r", __FUNCTION__);

	int ret = -1;
	FILE *my_file = NULL;
	uint8_t *buf = NULL;
	uint64_t file_size = 0;
	uint32_t buf_size = 0;
	uint32_t idx = 0;
	uint32_t total_blocks = 0;
	uint32_t cur_block = 0;
	int boot_sel = 0;
	uint8_t cur_fw_idx = 0;
	uint8_t target_fw_idx = 0;
	_file_checksum file_checksum;
	file_checksum.u = 0;
	

	// Determine boot selection
	boot_sel = sys_get_boot_sel();
	if (boot_sel == 0) {
		buf_size = NOR_BLOCK_SIZE;
	} else if (boot_sel == 1) {
		buf_size = NAND_BLOCK_SIZE;
	}

	buf = update_malloc(buf_size);
	if (!buf) {
		printf("\n\r[%s] Failed to allocate buffer\n\r", __FUNCTION__);
		goto update_ota_exit;
	}

	// Open the file using fopen
	printf("\n\r[%s] Opening file: %s\n\r", __FUNCTION__, filename);
	my_file = fopen(filename, "rb");
	if (!my_file) {
		printf("\n\r[%s] Failed to open file: %s\n\r", __FUNCTION__, filename);
		goto update_ota_exit;
	}

	printf("\n\r[%s] File opened successfully\n\r", __FUNCTION__);

	// Get file size
	fseek(my_file, 0, SEEK_END);
	file_size = ftell(my_file);
	if (file_size == -1) {
		printf("[%s] Error getting file size\n", __FUNCTION__);
	} else {
		printf("[%s] Detected file size: %llu bytes\n", __FUNCTION__, file_size);
	}
	fseek(my_file, 0, SEEK_SET);
	printf("\n\r[%s] File size: %llu\n\r", __FUNCTION__, file_size);

	target_fw_idx = OTA_BL_PRI;

	total_blocks = (file_size + buf_size - 1) / buf_size;

	// Start reading and updating firmware
	printf("\n\r[%s] Start OTA update\n\r", __FUNCTION__);
	while (idx < file_size) {
		#if UPDATE_UPGRADE_PROGRESS_TO_8773
		if (cancel_wifi_upgrade) {
			printf("\n\r[%s] OTA upgrade canceled by user\n\r", __FUNCTION__);
			ret = -2;
			goto update_ota_exit;
		}
		#endif
		uint32_t rest_len = file_size - idx;
		uint32_t data_len = rest_len > buf_size ? buf_size : rest_len;

		memset(buf, 0, buf_size);
		size_t bytes_read = fread(buf, 1, data_len, my_file);
		if (bytes_read != data_len && bytes_read != 0) {
			printf("\n\r[%s] Insufficient data or read error\n\r", __FUNCTION__);
			goto update_ota_exit;
		}

		// check when file size and read size is equal, and current bytes_read is 0, -4 checksum
		if ((idx == (file_size - 4)) && (bytes_read == 0)) {
			printf("\n\r[%s] OTA update completed successfully\n\r", __FUNCTION__);
			ret = 0;
			goto update_ota_exit;
		}

		printf("[Bootloader updating] ==============================  updating: %u / %llu Bytes \n",idx, file_size);

#if USE_CHECKSUM
		if ((idx + data_len) > (file_size - 4)) {
			file_checksum.c[0] = buf[data_len - 4];
			file_checksum.c[1] = buf[data_len - 3];
			file_checksum.c[2] = buf[data_len - 2];
			file_checksum.c[3] = buf[data_len - 1];
		}
#endif

		cur_block = idx / buf_size;
		if (cur_block == (total_blocks - 1)) {
			data_len -= 4; // Remove checksum bytes
			memset(buf + data_len, 0xFF, buf_size - data_len);
		}

		if (boot_sel == 0) {
			ret = ota_flash_NOR(target_fw_idx, total_blocks, cur_block, buf, data_len, file_checksum);
		} else if (boot_sel == 1) {
			ret = ota_flash_NAND(target_fw_idx, total_blocks, cur_block, buf, data_len, file_checksum);
		}

		if (ret < 0) {
			printf("\n\r[%s] OTA flash failed\n\r", __FUNCTION__);
			goto update_ota_exit;
		}

		idx += data_len;
	}

update_ota_exit:
	if (buf) {
		update_free(buf);
	}
	if (my_file) {
		fclose(my_file);
	}

	return ret;
}

#endif
