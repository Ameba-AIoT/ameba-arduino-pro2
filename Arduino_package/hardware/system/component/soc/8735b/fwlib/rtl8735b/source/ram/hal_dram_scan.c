#include "hal.h"
#include "hal_dram_scan.h"
#include "rtl8735b_dpi_type.h"
#include "hal_dram_init.h"
#include "hal_cache.h"

/*PLL Refrence clock is 40MHz*/
#define DDR_PLL_REF_CLK 40

#if DRAM_SCAN

const unsigned int dram_patterns[] = {
	0x01234567,
	0xfedcba98,
	0xA5A5A5A5,
	0x5A5A5A5A,
	0x5A5AA5A5,
	0xA5A55A5A,
};

uint8_t dram_normal_patterns(uint32_t dram_start, uint32_t dram_size, uint32_t area_size)
{
	uint32_t pattern_idx = 0, access_idx = 0;
	uint32_t start_value;
	uint32_t *write_start, *test_start;
	uint32_t *read_start;

	//dbg_printf("\r\n=======start dram_normal_patterns test=======\r\n");
	for (pattern_idx = 0; pattern_idx < (sizeof(dram_patterns) / sizeof(uint32_t)); pattern_idx++) {
		/* write pattern */
		write_start = (uint32_t *)(dram_start + (pattern_idx * dram_size) % (area_size));
		test_start = write_start;

		read_start = (uint32_t *)((uint32_t) write_start + dram_size - 4);

		for (access_idx = 0; access_idx < dram_size; access_idx += 4) {
			*write_start = dram_patterns[pattern_idx];
			write_start++;
		}

		dcache_clean_by_addr((uint32_t *)test_start, (int32_t)dram_size);

		dcache_invalidate_by_addr((uint32_t *)test_start, (int32_t)dram_size);

		//check data in reverse order
		for (access_idx = 0; access_idx < dram_size; access_idx += 4) {
			start_value = (*read_start);
			if (start_value != dram_patterns[pattern_idx]) {
				dbg_printf("[dram_normal_patterns test FAIL] Addr @0x%x = 0x%x, Pattern = 0x%x\r\n",
						   read_start, start_value, dram_patterns[pattern_idx]);
				return _FAIL;
			} else {
				//dbg_printf("[dram_normal_patterns test PASS] Addr @0x%x = 0x%x, Pattern = 0x%x\r\n",
				//    read_start, start_value, dram_patterns[pattern_idx]);
			}
			read_start--;
		}
	}

	//dbg_printf("dram_normal_patterns test PASS!\r\n");
	return _SUCCESS;
}

uint8_t dram_addr_rot(uint32_t dram_start, uint32_t dram_size, uint32_t area_size)
{
	uint32_t idx;
	uint32_t offset;
	uint32_t start_value;
	uint32_t read_start_addr;
	uint32_t *start, *test_start;
	uint32_t *read_start;

	//dbg_printf("\r\n=======start dram_addr_rot test=======\r\n");

	for (idx = 0; idx < 32; idx = idx + 4) {
		/*write pattern*/
		start = (uint32_t *)(dram_start + ((idx / 4) * dram_size) % (area_size));
		test_start = start;

		read_start = (uint32_t *)((uint32_t) start + dram_size - 4);
		read_start_addr = ((uint32_t) start);

		start = (uint32_t *)(((uint32_t) start));
		for (offset = 0; offset < dram_size; offset = offset + 4) {
			*start = (read_start_addr << idx);
			start++;
			read_start_addr = read_start_addr + 4;
		}

		dcache_clean_by_addr((uint32_t *)test_start, (int32_t)dram_size);

		dcache_invalidate_by_addr((uint32_t *)test_start, (int32_t)dram_size);

		read_start_addr = ((uint32_t) read_start);
		/*check data reversing order*/
		for (offset = 0; offset < dram_size; offset = offset + 4) {
			start_value = (*read_start);
			if (start_value != ((read_start_addr) << idx)) {
				dbg_printf("[addr_rot FAIL]Reverse order Addr @0x%x = 0x%x, Pattern = 0x%x\r\n",
						   read_start, start_value, ((read_start_addr) << idx));
				return _FAIL;
			}
			read_start_addr = read_start_addr - 4;
			read_start--;
		}

		read_start_addr += 4;
		read_start++;

		/*check data sequential order*/
		for (offset = 0; offset < dram_size; offset = offset + 4) {
			start_value = (*read_start);
			if (start_value != ((read_start_addr) << idx)) {
				dbg_printf("[addr_rot FAIL]Sequential order Addr @0x%x = 0x%x, Pattern = 0x%x\r\n",
						   read_start, start_value, ((read_start_addr) << idx));
				return _FAIL;
			}
			read_start_addr = read_start_addr + 4;
			read_start++;
		}

		//dbg_printf("rotate %d 0x%x pass\r\n", idx, (uint32_t)start);
	}

	//dbg_printf("dram_addr_rot test PASS!\r\n");
	return _SUCCESS;
}

uint8_t dram_com_addr_rot(uint32_t dram_start, uint32_t dram_size, uint32_t area_size)
{
	uint32_t idx;
	uint32_t offset;
	uint32_t start_value;
	uint32_t read_start_addr;
	uint32_t *start, *test_start;
	uint32_t *read_start;

	//dbg_printf("\r\n=======start dram_com_addr_rot test=======\r\n");

	for (idx = 0; idx < 32; idx = idx + 4) {
		/*write pattern*/
		start = (uint32_t *)(dram_start + ((idx / 4) * dram_size) % (area_size));
		test_start = start;

		read_start = (uint32_t *)((uint32_t) start + dram_size - 4);
		read_start_addr = ((uint32_t) start);

		start = (uint32_t *)((uint32_t) start);
		for (offset = 0; offset < dram_size; offset = offset + 4) {
			*start = ~(read_start_addr << idx);
			start++;
			read_start_addr = read_start_addr + 4;
		}

		dcache_clean_by_addr((uint32_t *)test_start, (int32_t)dram_size);

		dcache_invalidate_by_addr((uint32_t *)test_start, (int32_t)dram_size);

		read_start_addr = ((uint32_t) read_start);
		/*check data reversing order*/
		for (offset = 0; offset < dram_size; offset = offset + 4) {
			start_value = (*read_start);
			if (start_value != (~(read_start_addr << idx))) {
				dbg_printf("[com_addr_rot fail]Reverse order Addr @0x%x = 0x%x, Pattern = 0x%x\r\n",
						   read_start, start_value, ~((read_start_addr) << idx));
				return _FAIL;
			}
			read_start_addr = read_start_addr - 4;
			read_start--;
		}

		read_start_addr += 4;
		read_start++;

		/*check data sequential order*/
		for (offset = 0; offset < dram_size; offset = offset + 4) {
			start_value = (*read_start);
			if (start_value != (~(read_start_addr << idx))) {
				dbg_printf("[com_addr_rot fail]Sequential order Addr @0x%x = 0x%x, Pattern = 0x%x\r\n",
						   read_start, start_value, ~((read_start_addr) << idx));
				return _FAIL;
			}
			read_start_addr = read_start_addr + 4;
			read_start++;
		}

		//dbg_printf("~rotate %d 0x%x pass\r\n", idx, (uint32_t)start);
	}

	//dbg_printf("dram_com_addr_rot test PASS!\r\n");
	return _SUCCESS;
}

uint8_t dram_byte_access(uint32_t dram_start, uint32_t dram_size, uint32_t area_size)
{
	uint8_t byte;
	uint32_t idx;
	uint32_t offset;
	uint32_t start_value;

	uint8_t *start_b, *test_start;
	uint32_t *start_w;

	//dbg_printf("\r\n=======start dram_byte_access test=======\r\n");

	for (idx = 0; idx < (sizeof(dram_patterns) / sizeof(uint32_t)); idx++) {
		/*write byte pattern*/
		start_w = (uint32_t *)(dram_start + (idx * dram_size) % (area_size) + dram_size - 4);
		start_b = (uint8_t *)(dram_start + (idx * dram_size) % (area_size));
		test_start = start_b;

		for (offset = 0; offset < dram_size; offset = offset + 4) {
			byte = (uint8_t)(dram_patterns[idx] >> 24);
			*(start_b + 3) = byte;
			byte = (uint8_t)(dram_patterns[idx] >> 16);
			*(start_b + 2) = byte;
			byte = (uint8_t)(dram_patterns[idx] >> 8);
			*(start_b + 1) = byte;
			byte = (uint8_t)(dram_patterns[idx]);
			*(start_b) = byte;

			start_b += 4;
		}

		dcache_clean_by_addr((uint32_t *)test_start, (int32_t)dram_size);

		dcache_invalidate_by_addr((uint32_t *)test_start, (int32_t)dram_size);

		/* read word and check data */
		for (offset = 0; offset < dram_size; offset = offset + 4) {
			start_value = *start_w;
			if (start_value != dram_patterns[idx]) {
				dbg_printf("[byte_access fail] Addr @0x%x = 0x%x, Pattern = 0x%x\r\n", start_w, start_value, dram_patterns[idx]);
				return _FAIL;
			}
			start_w--;
		}
		//dbg_printf("pattern[%d](0x%x) 0x%x pass\r\n", idx, dram_patterns[idx], start_b);
	}
	//dbg_printf("dram_byte_access test PASS!\r\n");
	return _SUCCESS;
}

uint8_t dram_half_word_access(uint32_t dram_start, uint32_t dram_size, uint32_t area_size)
{
	uint16_t h_word;
	uint32_t idx;
	uint32_t offset;
	uint32_t start_value;

	uint16_t *start_h, *test_start;
	uint32_t *start_w;

	//dbg_printf("\r\n=======start dram_half_word_access test=======\r\n");
	for (idx = 0; idx < (sizeof(dram_patterns) / sizeof(uint32_t)); idx++) {
		/*write half_word pattern*/
		start_h = (uint16_t *)(dram_start + (idx * dram_size) % (area_size));
		test_start = start_h;
		start_w = (uint32_t *)(dram_start + (idx * dram_size) % (area_size) + dram_size - 4);

		for (offset = 0; offset < dram_size; offset = offset + 4) {
			h_word = (uint16_t)(dram_patterns[idx] >> 16);
			*(start_h + 1) = h_word;
			h_word = (uint16_t)(dram_patterns[idx]);
			*(start_h) = h_word;

			start_h += 2;
		}

		dcache_clean_by_addr((uint32_t *)test_start, (int32_t)dram_size);

		dcache_invalidate_by_addr((uint32_t *)test_start, (int32_t)dram_size);

		/*read work and check data*/
		for (offset = 0; offset < dram_size; offset = offset + 4) {
			start_value = (*start_w);
			if (start_value != dram_patterns[idx]) {
				dbg_printf("[half_word_access fail] Addr @0x%x = 0x%x, Pattern = 0x%x\r\n", start_w, start_value, dram_patterns[idx]);
				return _FAIL;
			}
			start_w--;
		}
		//dbg_printf("pattern[%d](0x%x) 0x%x pass\r\n", idx, dram_patterns[idx], start_h);
	}
	//dbg_printf("dram_half_word_access test PASS!\r\n");
	return _SUCCESS;
}

uint8_t dram_walking_of_1(uint32_t dram_start, uint32_t dram_size, uint32_t area_size)
{
	uint32_t idx;
	uint32_t offset;

	uint32_t walk_pattern;
	uint32_t start_value;
	uint32_t *start, *test_start;
	uint32_t *read_start;

	//dbg_printf("\r\n=======start dram_walking_of_1 test=======\r\n");
	for (idx = 0; idx < 32; idx++) {
		/*generate pattern*/
		walk_pattern = (1 << idx);

		/*write pattern*/
		start = (uint32_t *)(dram_start + (idx * dram_size) % (area_size));
		test_start = start;

		read_start = (uint32_t *)(((uint32_t) start + dram_size - 4));
		for (offset = 0; offset < dram_size; offset = offset + 4) {
			*start = walk_pattern;
			start++;
		}

		dcache_clean_by_addr((uint32_t *)test_start, (int32_t)dram_size);

		dcache_invalidate_by_addr((uint32_t *)test_start, (int32_t)dram_size);

		/*check data*/
		for (offset = 0; offset < dram_size; offset = offset + 4) {
			start_value = (*read_start);
			if (start_value != walk_pattern) {
				dbg_printf("[walking_of_1 fail] Addr @0x%x = 0x%x, Pattern = 0x%x\r\n", read_start, start_value, walk_pattern);
				//dbg_printf("FAIL!\r\n");
				return _FAIL;
			}
			read_start--;
		}
		//dbg_printf("pattern[%d](0x%x) 0x%x pass\r\n", idx, walk_pattern, start);
	}
	//dbg_printf("dram_walking_of_1 test PASS!\r\n");
	return _SUCCESS;
}

uint8_t dram_walking_of_0(uint32_t dram_start, uint32_t dram_size, uint32_t area_size)
{
	uint32_t idx;
	uint32_t offset;

	uint32_t walk_pattern;
	uint32_t start_value;
	uint32_t *start, *test_start;
	uint32_t *read_start;

	//dbg_printf("\r\n=======start dram_walking_of_0 test=======\r\n");
	for (idx = 0; idx < 32; idx++) {
		/*generate pattern*/
		walk_pattern = ~(1 << idx);

		/*write pattern*/
		start = (uint32_t *)(dram_start + (idx * dram_size) % (area_size));
		test_start = start;

		read_start = (uint32_t *)(((uint32_t) start + dram_size - 4));
		for (offset = 0; offset < dram_size; offset = offset + 4) {
			*start = walk_pattern;
			start++;
		}

		dcache_clean_by_addr((uint32_t *)test_start, (int32_t)dram_size);

		dcache_invalidate_by_addr((uint32_t *)test_start, (int32_t)dram_size);

		/*check data*/
		for (offset = 0; offset < dram_size; offset = offset + 4) {
			start_value = (*read_start);
			if (start_value != walk_pattern) {
				dbg_printf("[walking_of_0 fail] Addr @0x%x = 0x%x, Pattern = 0x%x\r\n", read_start, start_value, walk_pattern);
				return _FAIL;
			}
			read_start--;
		}
		//dbg_printf("pattern[%d](0x%x) 0x%x pass\r\n", idx, walk_pattern, start);
	}
	//dbg_printf("dram_walking_of_0 test PASS!\r\n");
	return _SUCCESS;
}

uint8_t memcpy_test(uint32_t dram_start, uint32_t dram_size, uint32_t area_size)
{
	uint32_t idx;
	uint32_t offset;

	uint32_t start_value;
	uint32_t read_start_addr;
	uint32_t *start, *test_start;
	uint32_t *read_start;

	//dbg_printf("\r\n=======start memcpy_test test=======\r\n");
	for (idx = 0; idx < 32; idx = idx + 4) {
		/*write pattern*/
		start = (uint32_t *)(dram_start + (idx * dram_size) % (area_size));
		test_start = start;

		read_start_addr = ((uint32_t) start + (dram_size - 4));

		read_start = (uint32_t *)(((uint32_t) start + dram_size - 4));
		for (offset = 0; offset < dram_size; offset = offset + 4) {
			*start = ((uint32_t) start << idx);
			start++;
		}

		dcache_clean_by_addr((uint32_t *)test_start, (int32_t)dram_size);

		memcpy((uint8_t *)(dram_start + dram_size), (uint8_t *)(test_start), dram_size);

		dcache_clean_by_addr((uint32_t *)(dram_start + dram_size), (int32_t)dram_size);
		dcache_invalidate_by_addr((uint32_t *)(dram_start + dram_size), (int32_t)dram_size);

		/*check uncached data*/
#if 1
		read_start = (uint32_t *)(dram_start + dram_size + dram_size - 4);
		for (offset = 0; offset < dram_size; offset = offset + 4) {
			start_value = (*read_start);
			if (start_value != ((read_start_addr) << idx)) {
				dbg_printf("[memcpy test fail %d] Addr @0x%x = 0x%x, Pattern = 0x%x\r\n",
						   idx, read_start, start_value, ((read_start_addr) << idx));
				return _FAIL;
			}
			read_start = read_start - 1;
			read_start_addr = read_start_addr - 4;
		}
#endif
		//dbg_printf("memcpy %d 0x%x pass\r\n", idx, start);
	}

	//dbg_printf("memcpy_test test PASS!\r\n");
	return _SUCCESS;
}

uint8_t dram_access_long_run_test(void)
{
	uint32_t start_addr = DRAM_MEM_BASE + 0x0;

	//uint32_t test_size = 0x10000;
	uint32_t test_size = 0x8000000;
	u32 loop = 0;
	u32 start, end;
	dbg_printf("DRAM long run testing ...\r\n");
	while (1) {
		start = hal_read_cur_time();
		if (dram_normal_patterns(start_addr, test_size, test_size) == _FAIL) {
			return _FAIL;
		}

#if 1
		if (dram_addr_rot(start_addr, test_size, test_size) == _FAIL) {
			return _FAIL;
		}
#endif

#if 1
		if (dram_com_addr_rot(start_addr, test_size, test_size) == _FAIL) {
			return _FAIL;
		}
#endif

#if 1
		//comment for code size
		if (dram_byte_access(start_addr, test_size, test_size) == _FAIL) {
			return _FAIL;
		}
#endif

#if 1
		if (dram_half_word_access(start_addr, test_size, test_size) == _FAIL) {
			return _FAIL;
		}
#endif

#if 1
		if (dram_walking_of_1(start_addr, test_size, test_size) == _FAIL) {
			return _FAIL;
		}
#endif

#if 1
		if (dram_walking_of_0(start_addr, test_size, test_size) == _FAIL) {
			return _FAIL;
		}
#endif

#if 1
		if (memcpy_test(start_addr, 0x2000000, 0x2000000) == _FAIL)
			//if(memcpy_test(start_addr, test_size, test_size) == _FAIL)
		{
			return _FAIL;
		}
#endif
		end = hal_read_cur_time();
		//dbg_printf("Loop = %d Pass, period = %d\r\n", loop++, end-start);
		dbg_printf("Loop = %d Pass\r\n", loop++);
	}
	return _SUCCESS;

}


uint8_t dram_access_test(void)
{
	uint32_t start_addr = DRAM_MEM_BASE + 0x0;

	uint32_t test_size = 0x10000;
	//uint32_t test_size = 0x4000000;
	u32 loop = 0;
	u32 start, end;
//while(1) {
	start = hal_read_cur_time();
	if (dram_normal_patterns(start_addr, test_size, test_size) == _FAIL) {
		return _FAIL;
	}

#if 1
	if (dram_addr_rot(start_addr, test_size, test_size) == _FAIL) {
		return _FAIL;
	}
#endif

#if 1
	if (dram_com_addr_rot(start_addr, test_size, test_size) == _FAIL) {
		return _FAIL;
	}
#endif

#if 1
	//comment for code size
	if (dram_byte_access(start_addr, test_size, test_size) == _FAIL) {
		return _FAIL;
	}
#endif

#if 1
	if (dram_half_word_access(start_addr, test_size, test_size) == _FAIL) {
		return _FAIL;
	}
#endif

#if 1
	if (dram_walking_of_1(start_addr, test_size, test_size) == _FAIL) {
		return _FAIL;
	}
#endif

#if 1
	if (dram_walking_of_0(start_addr, test_size, test_size) == _FAIL) {
		return _FAIL;
	}
#endif

#if 1
	//if(memcpy_test(start_addr, 0x2000000, 0x2000000) == _FAIL)
	if (memcpy_test(start_addr, test_size, test_size) == _FAIL) {
		return _FAIL;
	}
#endif
	end = hal_read_cur_time();
	//dbg_printf("Loop = %d Pass, period = %d\r\n", loop++, end-start);
//}
	return _SUCCESS;

}

void dram_odt_alwayson(void)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;

	//ODT always on
	dpi_dev_map->DPI_READ_CTRL2 |= (DPI_BIT_ODT_FORCE_SEL | DPI_BIT_ODT_FORCE_SIG);
	dpi_dev_map->DPI_READ_CTRL2_1 |= (DPI_BIT_ODT_FORCE_SEL | DPI_BIT_ODT_FORCE_SIG);
}

void dram_scan_rd_dly(u32 reg_index, u32 byte_index)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;
	u32 delay_index;
	u32 *addr = (&dpi_dev_map->DPI_DQS_IN_DLY0) + reg_index;
	u32 backup = *addr;

	dbg_printf("addr %x byte %x, value = %x\r\n", addr, byte_index, *addr);
	for (delay_index = 0; delay_index < 32; delay_index++) {
		cpu_read_modify_write(addr, delay_index << (byte_index * 8), 0x1F << (byte_index * 8));

		/*FW set read delay chain of data slice*/
		dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);

		if (dram_access_test() == _SUCCESS) {
			dbg_printf("%x pass.\r\n", delay_index);
		}
	}

	/*Retore to default value*/
	//*addr = 0x0A0A0A0A;
	*addr = backup;
}

void dram_scan_wr_dly(u32 reg_index, u32 shift_index)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;
	u32 delay_index;
	u32 *addr = (&dpi_dev_map->DPI_DQ_DLY_0) + reg_index;

	dbg_printf("addr %x byte %x, value = %x\r\n", addr, shift_index, *addr);
	for (delay_index = 0; delay_index < 16; delay_index++) {
		cpu_read_modify_write(addr, delay_index << (shift_index * 4), 0xF << (shift_index * 4));

		/*FW set read delay chain of data slice*/
		dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_WR_DLY | DPI_BIT_WRITE_EN_0);

		if (dram_access_test() == _SUCCESS) {
			dbg_printf("%x pass.\r\n", delay_index);
		}
	}

	/*Retore to default value*/
	*addr = 0x88888888;
}

void dram_calibration_dck_hold_map(void)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;
	u32 dck_pi = 0;
	u32 dck_dqs0, dck_dqs1, dck_dq0, dck_dq1;
	u32 count_hold = 0;
	u32 count_setup = 0;

	//dbg_printf("dpi_dev_map->DPI_PLL_PI0 = %x\r\n", dpi_dev_map->DPI_PLL_PI0);
	//dbg_printf("dpi_dev_map->DPI_PLL_PI1 = %x\r\n", dpi_dev_map->DPI_PLL_PI1);
	//dbg_printf("dpi_dev_map->DPI_PLL_PI2 = %x\r\n", dpi_dev_map->DPI_PLL_PI2);

	dck_pi = dpi_dev_map->DPI_PLL_PI0 & DPI_MASK_POST_PI_SEL0;

	/*Update immediately*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

	dck_dqs0 = dck_pi - ((dpi_dev_map->DPI_PLL_PI0 & DPI_MASK_POST_PI_SEL2) >> DPI_SHIFT_POST_PI_SEL2);
	dck_dqs1 = dck_pi - ((dpi_dev_map->DPI_PLL_PI0 & DPI_MASK_POST_PI_SEL3) >> DPI_SHIFT_POST_PI_SEL3);
	dck_dq0 = dck_pi - ((dpi_dev_map->DPI_PLL_PI1 & DPI_MASK_POST_PI_SEL6) >> DPI_SHIFT_POST_PI_SEL6);
	dck_dq1 = dck_pi - ((dpi_dev_map->DPI_PLL_PI2 & DPI_MASK_POST_PI_SEL7) >> DPI_SHIFT_POST_PI_SEL7);
	dbg_printf("dck_dqs0 = %d, dck_dqs1 = %d, dck_dq0 = %d, dck_dq1 = %d\r\n", dck_dqs0, dck_dqs1, dck_dq0, dck_dq1);

	dram_odt_alwayson();

	/*FW set write delay chain of data slice*/
	dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_WR_DLY | DPI_BIT_WRITE_EN_0);
	/*FW set read delay chain of data slice*/
	dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);

	dck_pi += 64;

	/*Scan dck hold time window*/
	while (count_hold < 64) {
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, dck_pi << DPI_SHIFT_POST_PI_SEL0, DPI_MASK_POST_PI_SEL0);
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, (dck_pi - dck_dqs0) << DPI_SHIFT_POST_PI_SEL2, DPI_MASK_POST_PI_SEL2);
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, (dck_pi - dck_dqs1) << DPI_SHIFT_POST_PI_SEL3, DPI_MASK_POST_PI_SEL3);
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI1, (dck_pi - dck_dq0) << DPI_SHIFT_POST_PI_SEL6, DPI_MASK_POST_PI_SEL6);
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, (dck_pi - dck_dq1) << DPI_SHIFT_POST_PI_SEL7, DPI_MASK_POST_PI_SEL7);
		//dbg_printf("dck_pi = %x\r\n", dck_pi);
		//dbg_printf("dpi_dev_map->DPI_PLL_PI0 = %x\r\n", dpi_dev_map->DPI_PLL_PI0);
		//dbg_printf("dpi_dev_map->DPI_PLL_PI1 = %x\r\n", dpi_dev_map->DPI_PLL_PI1);
		//dbg_printf("dpi_dev_map->DPI_PLL_PI2 = %x\r\n", dpi_dev_map->DPI_PLL_PI2);

		/*FW set write delay chain of data slice*/
		dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_WR_DLY | DPI_BIT_WRITE_EN_0);
		/*FW set read delay chain of data slice*/
		dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);

		if (dram_access_test() == _FAIL) {
			/*Shift back to initial value*/
			dck_pi -= count_hold;
			break;
		} else {
			dbg_printf("dck_pi %d pass\r\n", dck_pi % 32);
		}

		if (count_hold >= 32) {
			break;
		}

		dck_pi++;
		count_hold++;
	}

	dbg_printf("dck hold window = %d ~ %d \r\n", (dck_pi % 32), (dck_pi % 32) + count_hold - 1);

	/*Update when no read*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x0 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);
}

void dram_calibration_dck_setup_map(void)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;
	u32 dck_pi = 0;
	u32 dck_dqs0, dck_dqs1, dck_dq0, dck_dq1;
	u32 count_hold = 0;
	u32 count_setup = 0;

	//dbg_printf("dpi_dev_map->DPI_PLL_PI0 = %x\r\n", dpi_dev_map->DPI_PLL_PI0);
	//dbg_printf("dpi_dev_map->DPI_PLL_PI1 = %x\r\n", dpi_dev_map->DPI_PLL_PI1);
	//dbg_printf("dpi_dev_map->DPI_PLL_PI2 = %x\r\n", dpi_dev_map->DPI_PLL_PI2);

	dck_pi = dpi_dev_map->DPI_PLL_PI0 & DPI_MASK_POST_PI_SEL0;

	/*Update immediately*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

	dck_dqs0 = dck_pi - ((dpi_dev_map->DPI_PLL_PI0 & DPI_MASK_POST_PI_SEL2) >> DPI_SHIFT_POST_PI_SEL2);
	dck_dqs1 = dck_pi - ((dpi_dev_map->DPI_PLL_PI0 & DPI_MASK_POST_PI_SEL3) >> DPI_SHIFT_POST_PI_SEL3);
	dck_dq0 = dck_pi - ((dpi_dev_map->DPI_PLL_PI1 & DPI_MASK_POST_PI_SEL6) >> DPI_SHIFT_POST_PI_SEL6);
	dck_dq1 = dck_pi - ((dpi_dev_map->DPI_PLL_PI2 & DPI_MASK_POST_PI_SEL7) >> DPI_SHIFT_POST_PI_SEL7);
	dbg_printf("dck_dqs0 = %d, dck_dqs1 = %d, dck_dq0 = %d, dck_dq1 = %d\r\n", dck_dqs0, dck_dqs1, dck_dq0, dck_dq1);

	dram_odt_alwayson();

	/*FW set write delay chain of data slice*/
	dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_WR_DLY | DPI_BIT_WRITE_EN_0);
	/*FW set read delay chain of data slice*/
	dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);

	dck_pi += 64;

	/*Scan dck setup time window*/
	while (count_setup < 64) {
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, dck_pi << DPI_SHIFT_POST_PI_SEL0, DPI_MASK_POST_PI_SEL0);
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, (dck_pi - dck_dqs0) << DPI_SHIFT_POST_PI_SEL2, DPI_MASK_POST_PI_SEL2);
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, (dck_pi - dck_dqs1) << DPI_SHIFT_POST_PI_SEL3, DPI_MASK_POST_PI_SEL3);
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI1, (dck_pi - dck_dq0) << DPI_SHIFT_POST_PI_SEL6, DPI_MASK_POST_PI_SEL6);
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, (dck_pi - dck_dq1) << DPI_SHIFT_POST_PI_SEL7, DPI_MASK_POST_PI_SEL7);

		/*FW set write delay chain of data slice*/
		dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_WR_DLY | DPI_BIT_WRITE_EN_0);
		/*FW set read delay chain of data slice*/
		dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);

		if (dram_access_test() == _FAIL) {
			/*Shift back to initial value*/
			dck_pi += count_setup;
			break;
		} else {
			dbg_printf("dck_pi %d pass\r\n", dck_pi % 32);
		}

		if (count_setup >= 32) {
			break;
		}

		dck_pi--;
		count_setup++;
	}

	dbg_printf("dck setup window = %d ~ %d \r\n", (dck_pi % 32) - count_setup + 1, (dck_pi % 32));

	/*Update when no read*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x0 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);
}

void dram_calibration_dcs_hold_map(void)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;
	u32 dcs_pi;
	u32 count_hold = 0;
	u32 count_setup = 0;

	dcs_pi = (dpi_dev_map->DPI_PLL_PI2 & DPI_MASK_POST_PI_SEL10) >> DPI_SHIFT_POST_PI_SEL10;

	/*Scan dck hold time window*/
	while (count_hold < 32) {
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, dcs_pi << DPI_SHIFT_POST_PI_SEL10, DPI_MASK_POST_PI_SEL10);

		/*Update immediately*/
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

		/*FW set write delay chain of data slice*/
		dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_WR_DLY | DPI_BIT_WRITE_EN_0);
		/*FW set read delay chain of data slice*/
		dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);

		if (dram_access_test() == _FAIL) {
			/*Shift back to initial value*/
			dcs_pi -= count_hold;
			break;
		} else {
			dbg_printf("cs_pi %d pass\r\n", dcs_pi);
		}

		dcs_pi++;
		count_hold++;
	}

	dbg_printf("dcs_pi hold window = %d ~ %d \r\n", dcs_pi, dcs_pi + count_hold - 1);

	/*Update when no read*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x0 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);
}

void dram_calibration_dcs_setup_map(void)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;
	u32 dcs_pi;
	u32 count_hold = 0;
	u32 count_setup = 0;

	dcs_pi = (dpi_dev_map->DPI_PLL_PI2 & DPI_MASK_POST_PI_SEL10) >> DPI_SHIFT_POST_PI_SEL10;

	/*Scan dck setup time window*/
	while (count_setup < 32) {
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, dcs_pi << DPI_SHIFT_POST_PI_SEL10, DPI_MASK_POST_PI_SEL10);

		/*Update immediately*/
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

		/*FW set write delay chain of data slice*/
		dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_WR_DLY | DPI_BIT_WRITE_EN_0);
		/*FW set read delay chain of data slice*/
		dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);

		if (dram_access_test() == _FAIL) {
			/*Shift back to initial value*/
			dcs_pi += count_setup;
			break;
		} else {
			dbg_printf("cs_pi %d pass\r\n", dcs_pi);
		}

		dcs_pi--;
		count_setup++;
	}

	dbg_printf("dcs_pi setup window = %d ~ %d \r\n", dcs_pi - count_setup + 1, dcs_pi);

	/*Update when no read*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x0 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);
}

void dram_calibration_dqs_map(void)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;
	u32 dqspi_init[2];
	u32 dqspi_hold[2];
	u32 dqspi_setup[2];
	u32 count_hold = 0;
	u32 count_setup = 0;
	u32 slice = 0;
	u32 pi_count = 0;
	u32 index = 0;

	dqspi_init[0] = (dpi_dev_map->DPI_PLL_PI0 & DPI_MASK_POST_PI_SEL2) >> DPI_SHIFT_POST_PI_SEL2;
	dqspi_init[1] = (dpi_dev_map->DPI_PLL_PI0 & DPI_MASK_POST_PI_SEL3) >> DPI_SHIFT_POST_PI_SEL3;

	for (slice = 0; slice < 2; slice++) {
		count_hold = 0;
		count_setup = 0;

		/*DQS hold time scan*/
		for (pi_count = dqspi_init[slice]; pi_count < (dqspi_init[slice] + 16); pi_count++) {
			if (slice == 0) {
				cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, pi_count << DPI_SHIFT_POST_PI_SEL2, DPI_MASK_POST_PI_SEL2);
			} else {
				cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, pi_count << DPI_SHIFT_POST_PI_SEL3, DPI_MASK_POST_PI_SEL3);
			}

			/*Update immediately*/
			cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

			/*FW set write delay chain of data slice*/
			dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_WR_DLY | DPI_BIT_WRITE_EN_0);

			if (dram_access_test() == _FAIL) {
				/*Shift back to initial value*/
				dqspi_hold[slice] = pi_count - 1;
				break;
			} else {
				dbg_printf("slice = %d, hold pi_count %d ~ %d pass\r\n", slice, dqspi_init[slice], pi_count);
			}

			count_hold++;
		}

		/*Shift back hold time to initial value*/
		for (index = 1; index <= count_hold; index++) {
			if (slice == 0) {
				cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, (pi_count - index) << DPI_SHIFT_POST_PI_SEL2, DPI_MASK_POST_PI_SEL2);
			} else {
				cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, (pi_count - index) << DPI_SHIFT_POST_PI_SEL3, DPI_MASK_POST_PI_SEL3);
			}

			/*Update immediately*/
			cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

			/*FW set write delay chain of data slice*/
			dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_WR_DLY | DPI_BIT_WRITE_EN_0);
		}

		/*DQS setup time scan*/
		for (pi_count = dqspi_init[slice] + 32; pi_count > (dqspi_init[slice] + 16); pi_count--) {
			if (slice == 0) {
				cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, pi_count << DPI_SHIFT_POST_PI_SEL2, DPI_MASK_POST_PI_SEL2);
			} else {
				cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, pi_count << DPI_SHIFT_POST_PI_SEL3, DPI_MASK_POST_PI_SEL3);
			}

			/*Update immediately*/
			cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

			/*FW set write delay chain of data slice*/
			dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_WR_DLY | DPI_BIT_WRITE_EN_0);

			if (dram_access_test() == _FAIL) {
				/*Shift back to initial value*/
				dqspi_setup[slice] = pi_count + 1;
				break;
			} else {
				dbg_printf("slice = %d, setup pi_count %d ~ %d pass\r\n", slice, dqspi_init[slice], pi_count);
			}

			count_setup++;
		}

		/*Shift back hold time to initial value*/
		for (index = 1; index <= count_setup; index++) {
			if (slice == 0) {
				cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, (pi_count + index) << DPI_SHIFT_POST_PI_SEL2, DPI_MASK_POST_PI_SEL2);
			} else {
				cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, (pi_count + index) << DPI_SHIFT_POST_PI_SEL3, DPI_MASK_POST_PI_SEL3);
			}

			/*Update immediately*/
			cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

			/*FW set write delay chain of data slice*/
			dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_WR_DLY | DPI_BIT_WRITE_EN_0);
		}
	}

	dbg_printf("Slice 0 hold_count = %d, setup_count = %d, Slice 1 hold_count = %d, setup_count = %d\r\n",
			   dqspi_hold[0] % 32, dqspi_setup[0] % 32, dqspi_hold[1] % 32, dqspi_setup[1] % 32);
}

void dram_calibration_dq_map(void)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;
	u32 dqpi_init[2];
	u32 dqpi_hold[2];
	u32 dqpi_setup[2];
	u32 count_hold = 0;
	u32 count_setup = 0;
	u32 slice = 0;
	u32 pi_count = 0;
	u32 index = 0;

	dqpi_init[0] = (dpi_dev_map->DPI_PLL_PI1 & DPI_MASK_POST_PI_SEL6) >> DPI_SHIFT_POST_PI_SEL6;
	dqpi_init[1] = (dpi_dev_map->DPI_PLL_PI2 & DPI_MASK_POST_PI_SEL7) >> DPI_SHIFT_POST_PI_SEL7;

	for (slice = 0; slice < 2; slice++) {
		count_hold = 0;
		count_setup = 0;

		/*DQS hold time scan*/
		for (pi_count = dqpi_init[slice]; pi_count < (dqpi_init[slice] + 16); pi_count++) {
			if (slice == 0) {
				cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI1, pi_count << DPI_SHIFT_POST_PI_SEL6, DPI_MASK_POST_PI_SEL6);
			} else {
				cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, pi_count << DPI_SHIFT_POST_PI_SEL7, DPI_MASK_POST_PI_SEL7);
			}

			/*Update immediately*/
			cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

			/*FW set write delay chain of data slice*/
			dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_WR_DLY | DPI_BIT_WRITE_EN_0);

			if (dram_access_test() == _FAIL) {
				/*Shift back to initial value*/
				dqpi_hold[slice] = pi_count - 1;
				break;
			} else {
				dbg_printf("slice = %d, hold pi_count %d ~ %d pass\r\n", slice, dqpi_init[slice], pi_count);
			}

			count_hold++;
		}

		/*Shift back hold time to initial value*/
		for (index = 1; index <= count_hold; index++) {
			if (slice == 0) {
				cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI1, (pi_count - index) << DPI_SHIFT_POST_PI_SEL6, DPI_MASK_POST_PI_SEL6);
			} else {
				cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, (pi_count - index) << DPI_SHIFT_POST_PI_SEL7, DPI_MASK_POST_PI_SEL7);
			}

			/*Update immediately*/
			cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

			/*FW set write delay chain of data slice*/
			dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_WR_DLY | DPI_BIT_WRITE_EN_0);
		}

		/*DQS setup time scan*/
		for (pi_count = dqpi_init[slice] + 32; pi_count > (dqpi_init[slice] + 16); pi_count--) {
			if (slice == 0) {
				cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI1, pi_count << DPI_SHIFT_POST_PI_SEL6, DPI_MASK_POST_PI_SEL6);
			} else {
				cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, pi_count << DPI_SHIFT_POST_PI_SEL7, DPI_MASK_POST_PI_SEL7);
			}

			/*Update immediately*/
			cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

			/*FW set write delay chain of data slice*/
			dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_WR_DLY | DPI_BIT_WRITE_EN_0);

			if (dram_access_test() == _FAIL) {
				/*Shift back to initial value*/
				dqpi_setup[slice] = pi_count + 1;
				break;
			} else {
				dbg_printf("slice = %d, setup pi_count %d ~ %d pass\r\n", slice, dqpi_init[slice], pi_count);
			}

			count_setup++;
		}

		/*Shift back hold time to initial value*/
		for (index = 1; index <= count_setup; index++) {
			if (slice == 0) {
				cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI1, (pi_count + index) << DPI_SHIFT_POST_PI_SEL6, DPI_MASK_POST_PI_SEL6);
			} else {
				cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, (pi_count + index) << DPI_SHIFT_POST_PI_SEL7, DPI_MASK_POST_PI_SEL7);
			}

			/*Update immediately*/
			cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

			/*FW set write delay chain of data slice*/
			dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_WR_DLY | DPI_BIT_WRITE_EN_0);
		}
	}

	dbg_printf("Slice 0 hold_count = %d, setup_count = %d, Slice 1 hold_count = %d, setup_count = %d\r\n",
			   dqpi_hold[0] % 32, dqpi_setup[0] % 32, dqpi_hold[1] % 32, dqpi_setup[1] % 32);
}

void dram_calibration_rx_dqsen_map(void)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;
	u32 dqsen_init[2];
	u32 dqs_int[2];
	u32 dqsen_hold[2];
	u32 dqsen_delay_hold[2];
	u32 dqsen0_to_dqsen1;
	u32 dqsen;
	u32 dqsen_dly;
	u32 index;

	/*Initialize*/
	for (index = 0; index < 2; index++) {
		dqsen_hold[index] = 0xFF;
		dqsen_delay_hold[index] = 0xFF;
	}

	dqsen_init[0] = dpi_dev_map->DPI_READ_CTRL_0_0 & (DPI_MASK_TM_DQS_EN | DPI_MASK_TM_DQS_EN_FTUN);
	dqsen_init[1] = dpi_dev_map->DPI_READ_CTRL_0_1 & (DPI_MASK_TM_DQS_EN | DPI_MASK_TM_DQS_EN_FTUN);
	dqsen0_to_dqsen1 = dqsen_init[0] - dqsen_init[1];

	dpi_dev_map->DPI_READ_CTRL_4 |= DPI_BIT_FW_DQSEN_FTUN_UPD;
	dpi_dev_map->DPI_READ_CTRL_4_1 |= DPI_BIT_FW_DQSEN_FTUN_UPD;

	/*Set dqsen delay to 0*/
	cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_0, 0, DPI_MASK_DQS_EN_DLY_SEL);
	cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_1, 0, DPI_MASK_DQS_EN_DLY_SEL);

	/*Update immediately*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

	/*FW set read delay chain of data slice*/
	dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);

	/*Scan dqsen*/
	for (dqsen = dqsen_init[0]; dqsen < 16; dqsen++) {
		cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_0, dqsen, (DPI_MASK_TM_DQS_EN | DPI_MASK_TM_DQS_EN_FTUN));
		cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_1, dqsen - dqsen0_to_dqsen1, (DPI_MASK_TM_DQS_EN | DPI_MASK_TM_DQS_EN_FTUN));

		/*Update immediately*/
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

		/*FW set read delay chain of data slice*/
		dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);

		if (dram_access_test() == _FAIL) {
			dbg_printf("dqsen = %d DRAM access test fail.\r\n", dqsen);
			/*Reset FIFO mode*/
			cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x3 << DPI_SHIFT_RST_FIFO_MODE, DPI_MASK_RST_FIFO_MODE);
			cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_RST_FIFO_MODE, DPI_MASK_RST_FIFO_MODE);

			/*Reset DQSEN mode*/
			cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_2, 0x1 << DPI_SHIFT_RST_DQSEN_MODE, DPI_MASK_RST_DQSEN_MODE);
			cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_2, 0x0 << DPI_SHIFT_RST_DQSEN_MODE, DPI_MASK_RST_DQSEN_MODE);

			/*Reset 3Point mode*/
			cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_2, 0x1 << DPI_SHIFT_RST_3POINT_MODE, DPI_MASK_RST_3POINT_MODE);
			cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_2, 0x0 << DPI_SHIFT_RST_3POINT_MODE, DPI_MASK_RST_3POINT_MODE);
			break;
		} else {
			dbg_printf("dqsen = %d DRAM access test pass.\r\n", dqsen);
		}

		dqs_int[0] = dpi_dev_map->DPI_INT_STATUS_0 & DPI_BIT_DQS_INT_0;
		dqs_int[1] = (dpi_dev_map->DPI_INT_STATUS_0 & DPI_BIT_DQS_INT_1) >> DPI_SHIFT_DQS_INT_1;

		/*Reset FIFO mode*/
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x3 << DPI_SHIFT_RST_FIFO_MODE, DPI_MASK_RST_FIFO_MODE);
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_RST_FIFO_MODE, DPI_MASK_RST_FIFO_MODE);

		/*Reset DQSEN mode*/
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_2, 0x1 << DPI_SHIFT_RST_DQSEN_MODE, DPI_MASK_RST_DQSEN_MODE);
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_2, 0x0 << DPI_SHIFT_RST_DQSEN_MODE, DPI_MASK_RST_DQSEN_MODE);

		/*Reset 3Point mode*/
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_2, 0x1 << DPI_SHIFT_RST_3POINT_MODE, DPI_MASK_RST_3POINT_MODE);
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_2, 0x0 << DPI_SHIFT_RST_3POINT_MODE, DPI_MASK_RST_3POINT_MODE);

		dbg_printf("dqsen = %d, dqs_int = %x\r\n", dqsen, (dpi_dev_map->DPI_INT_STATUS_0) & 0x3);

		cpu_read_modify_write(&dpi_dev_map->DPI_INT_CTRL, 0x3 << DPI_SHIFT_FW_CLR_DQS_INT, DPI_BIT_FW_CLR_DQS_INT | DPI_BIT_WRITE_EN_2);
		dpi_dev_map->DPI_INT_STATUS_0 &= ~(DPI_BIT_DQS_INT_0 | DPI_BIT_DQS_INT_1 | DPI_BIT_DQS_INT_2 | DPI_BIT_DQS_INT_3);
		dpi_dev_map->DPI_INT_STATUS_0 &= ~(DPI_BIT_TM_DQSEN_LATE_INT_0 | DPI_BIT_TM_DQSEN_LATE_INT_1 | DPI_BIT_TM_DQSEN_LATE_INT_2 | DPI_BIT_TM_DQSEN_LATE_INT_3);
		dpi_dev_map->DPI_INT_STATUS_0 &= ~(DPI_BIT_TM_DQSEN_EARLY_INT_0 | DPI_BIT_TM_DQSEN_EARLY_INT_1 | DPI_BIT_TM_DQSEN_EARLY_INT_2 | DPI_BIT_TM_DQSEN_EARLY_INT_3);
		cpu_read_modify_write(&dpi_dev_map->DPI_INT_CTRL, 0x2 << DPI_SHIFT_FW_CLR_DQS_INT, DPI_BIT_FW_CLR_DQS_INT | DPI_BIT_WRITE_EN_2);

		if ((dqs_int[0] == 1) && (dqsen_hold[0] == 0xFF)) {
			dqsen_hold[0] = dqsen - 1;
		}

		if ((dqs_int[1] == 1) && (dqsen_hold[1] == 0xFF)) {
			dqsen_hold[1] = dqsen - 1;
		}

		if ((dqsen_hold[0] != 0xFF) && (dqsen_hold[1] != 0xFF)) {
			break;
		}
	}

	/*Set dqsen to dqs_init boundary from scan*/
	cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_0, dqsen_hold[0], DPI_MASK_TM_DQS_EN_FTUN | DPI_MASK_TM_DQS_EN);
	cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_1, dqsen_hold[1], DPI_MASK_TM_DQS_EN_FTUN | DPI_MASK_TM_DQS_EN);

	/*Update immediately*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

	/*FW set read delay chain of data slice*/
	dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);
#if 0
	for (dqsen_dly = 1; dqsen_dly < 64; dqsen_dly += 1) {
		/*Set dqsen to dqs_init boundary from scan*/
		cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_0, dqsen_dly << DPI_SHIFT_DQS_EN_DLY_SEL, DPI_MASK_DQS_FIFO_DLY_SEL);
		cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_1, dqsen_dly << DPI_SHIFT_DQS_EN_DLY_SEL, DPI_MASK_DQS_FIFO_DLY_SEL);

		/*Update immediately*/
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

		/*FW set read delay chain of data slice*/
		dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);

		if (dram_access_test() == _FAIL) {
			dbg_printf("dqsen_dly = %d DRAM access test fail.\r\n", dqsen_dly);
		} else {
			dbg_printf("dqsen_dly = %d DRAM access test pass.\r\n", dqsen_dly);
		}

		dqs_int[0] = dpi_dev_map->DPI_INT_STATUS_0 & DPI_BIT_DQS_INT_0;
		dqs_int[1] = (dpi_dev_map->DPI_INT_STATUS_0 & DPI_BIT_DQS_INT_1) >> DPI_SHIFT_DQS_INT_1;

		/*Reset FIFO mode*/
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x3 << DPI_SHIFT_RST_FIFO_MODE, DPI_MASK_RST_FIFO_MODE);
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_RST_FIFO_MODE, DPI_MASK_RST_FIFO_MODE);

		/*Reset DQSEN mode*/
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_2, 0x1 << DPI_SHIFT_RST_DQSEN_MODE, DPI_MASK_RST_DQSEN_MODE);
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_2, 0x0 << DPI_SHIFT_RST_DQSEN_MODE, DPI_MASK_RST_DQSEN_MODE);

		/*Reset 3Point mode*/
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_2, 0x1 << DPI_SHIFT_RST_3POINT_MODE, DPI_MASK_RST_3POINT_MODE);
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_2, 0x0 << DPI_SHIFT_RST_3POINT_MODE, DPI_MASK_RST_3POINT_MODE);

		dbg_printf("dqsen_dly = %d, dqs_int = %x\r\n", dqsen_dly, dpi_dev_map->DPI_INT_STATUS_0);

		cpu_read_modify_write(&dpi_dev_map->DPI_INT_CTRL, 0x3 << DPI_SHIFT_FW_CLR_DQS_INT, DPI_BIT_FW_CLR_DQS_INT | DPI_BIT_WRITE_EN_2);
		dpi_dev_map->DPI_INT_STATUS_0 &= ~(DPI_BIT_DQS_INT_0 | DPI_BIT_DQS_INT_1 | DPI_BIT_DQS_INT_2 | DPI_BIT_DQS_INT_3);
		dpi_dev_map->DPI_INT_STATUS_0 &= ~(DPI_BIT_TM_DQSEN_LATE_INT_0 | DPI_BIT_TM_DQSEN_LATE_INT_1 | DPI_BIT_TM_DQSEN_LATE_INT_2 | DPI_BIT_TM_DQSEN_LATE_INT_3);
		dpi_dev_map->DPI_INT_STATUS_0 &= ~(DPI_BIT_TM_DQSEN_EARLY_INT_0 | DPI_BIT_TM_DQSEN_EARLY_INT_1 | DPI_BIT_TM_DQSEN_EARLY_INT_2 | DPI_BIT_TM_DQSEN_EARLY_INT_3);
		cpu_read_modify_write(&dpi_dev_map->DPI_INT_CTRL, 0x2 << DPI_SHIFT_FW_CLR_DQS_INT, DPI_BIT_FW_CLR_DQS_INT | DPI_BIT_WRITE_EN_2);

		if ((dqs_int[0] == 1) && (dqsen_delay_hold[0] == 0xFF)) {
			dqsen_delay_hold[0] = dqsen_dly - 1;
		}

		if ((dqs_int[1] == 1) && (dqsen_delay_hold[1] == 0xFF)) {
			dqsen_delay_hold[1] = dqsen_dly - 1;
		}

		if ((dqsen_delay_hold[0] != 0xFF) && (dqsen_delay_hold[1] != 0xFF)) {
			break;
		}
	}

	/*Set dqsen_delay from scan*/
	cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_0, dqsen_delay_hold[0] << DPI_SHIFT_DQS_EN_DLY_SEL, DPI_MASK_DQS_FIFO_DLY_SEL);
	cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_1, dqsen_delay_hold[1] << DPI_SHIFT_DQS_EN_DLY_SEL, DPI_MASK_DQS_FIFO_DLY_SEL);

	/*Set dqsen to dqs_init boundary from scan, need to check value*/
	cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_0, dqsen_hold[0] - 1, DPI_MASK_TM_DQS_EN_FTUN | DPI_MASK_TM_DQS_EN);
	cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_1, dqsen_hold[1] - 1, DPI_MASK_TM_DQS_EN_FTUN | DPI_MASK_TM_DQS_EN);

	/*Update immediately*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

	/*FW set read delay chain of data slice*/
	dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);
#endif
}

void dram_calibration_rx_fifo_map(void)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;
	u32 fifo_init;
	u32 valid_fifo_max = 0;
	u32 valid_fifo_min;
	u32 fifo_index;


	fifo_init = dpi_dev_map->DPI_READ_CTRL1 & DPI_MASK_TM_RD_FIFO;
	valid_fifo_min = fifo_init;

	/*Disable 3 point calibration*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x3 << DPI_SHIFT_CAL_SET_MODE, DPI_MASK_CAL_SET_MODE);

	for (fifo_index = fifo_init; fifo_index < 64; fifo_index++) {
		cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL1, fifo_index, DPI_MASK_TM_RD_FIFO);

		/*Update immediately*/
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

		/*FW set read delay chain of data slice*/
		dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);

		if (dram_access_test() == _FAIL) {
			dbg_printf("fifo_index = %d DRAM access test fail.\r\n", fifo_index);
			/*Reset FIFO mode*/
			cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x3 << DPI_SHIFT_RST_FIFO_MODE, DPI_MASK_RST_FIFO_MODE);
			cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_RST_FIFO_MODE, DPI_MASK_RST_FIFO_MODE);
			break;
		} else {
			dbg_printf("fifo_index = %d DRAM access test pass.\r\n", fifo_index);
		}

		/*Reset FIFO mode*/
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x3 << DPI_SHIFT_RST_FIFO_MODE, DPI_MASK_RST_FIFO_MODE);
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_RST_FIFO_MODE, DPI_MASK_RST_FIFO_MODE);
		valid_fifo_max = fifo_index;
	}

	/*Disable 3 point calibration*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x3 << DPI_SHIFT_CAL_SET_MODE, DPI_MASK_CAL_SET_MODE);

	for (fifo_index = fifo_init - 1; fifo_index > 0; fifo_index--) {
		cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL1, fifo_index, DPI_MASK_TM_RD_FIFO);

		/*Update immediately*/
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

		/*FW set read delay chain of data slice*/
		dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);

		if (dram_access_test() == _FAIL) {
			dbg_printf("fifo_index = %d DRAM access test fail.\r\n", fifo_index);
			/*Reset FIFO mode*/
			cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x3 << DPI_SHIFT_RST_FIFO_MODE, DPI_MASK_RST_FIFO_MODE);
			cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_RST_FIFO_MODE, DPI_MASK_RST_FIFO_MODE);
			break;
		} else {
			valid_fifo_min = fifo_index;
			dbg_printf("fifo_index = %d DRAM access test pass.\r\n", fifo_index);
		}

		/*Reset FIFO mode*/
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x3 << DPI_SHIFT_RST_FIFO_MODE, DPI_MASK_RST_FIFO_MODE);
		cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_RST_FIFO_MODE, DPI_MASK_RST_FIFO_MODE);
	}

	cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL1, valid_fifo_min + 1, DPI_MASK_TM_RD_FIFO);

	/*Update immediately*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);

	/*FW set read delay chain of data slice*/
	dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);
}

void dram_calibration_rx_dq_map(void)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;
	u8 slice_index;
	u8 reg_index;
	u8 byte_index;

	/*Update immediately*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);
	/*Disable 3 point calibration*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x3 << DPI_SHIFT_CAL_SET_MODE, DPI_MASK_CAL_SET_MODE);

	//cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_0, 0x5 << DPI_SHIFT_DQS_RC1IN_DLY_SEL, DPI_MASK_DQS_RC1IN_DLY_SEL);
	//cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_1, 0x5 << DPI_SHIFT_DQS_RC1IN_DLY_SEL, DPI_MASK_DQS_RC1IN_DLY_SEL);

	for (slice_index = 0; slice_index < 2; slice_index++) {
		for (reg_index = 0; reg_index < 4; reg_index++) {
			for (byte_index = 0; byte_index < 4; byte_index++) {
				dram_scan_rd_dly(slice_index * 6 + reg_index, byte_index);
			}
		}
	}
}

void dram_calibration_tx_dq_map(void)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;
	u8 reg_index;
	u8 shift_index;

	/*Update immediately*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);
	/*Disable 3 point calibration*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x3 << DPI_SHIFT_CAL_SET_MODE, DPI_MASK_CAL_SET_MODE);

	for (reg_index = 0; reg_index < 4; reg_index++) {
		if ((reg_index == 0) || (reg_index == 1)) {
			for (shift_index = 0; shift_index < 8; shift_index++) {
				dram_scan_wr_dly(reg_index, shift_index);
			}
		} else {
			for (shift_index = 0; shift_index < 3; shift_index++) {
				//dram_scan_wr_dly(reg_index, shift_index);
			}

		}
	}
}

#endif

void dram_r480_calibration(u8 dram_type)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;

	DBG_DRAM_WARN("R480 K.\r\n");

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	HAL_WRITE32(SYSON_S_BASE, 0x120, HAL_READ32(SYSON_S_BASE, 0x120) | (BIT19 | BIT22));
#else
	HAL_WRITE32(SYSON_S_BASE, 0x120, HAL_READ32(SYSON_S_BASE, 0x120) | (BIT18 | BIT19 | BIT22));
#endif
	dpi_dev_map->DPI_PAD_BUS_0 = 0x901B0000;

	if (dram_type == DDR_2) {
		/*vref_range_0[7]:28~92% = 0,vref_s_0[6:1],vref_pad_0[0] = 0*/
		cpu_read_modify_write(&dpi_dev_map->DPI_PAD_BUS_2, 0x4 << DPI_SHIFT_VREF_S_0, 0xFF);
	} else {
		/*vref_range_0[7]:0.5~63.5% = 0,vref_s_0[6:1] = 110111, vref_pad_0[0] = 0*/
		cpu_read_modify_write(&dpi_dev_map->DPI_PAD_BUS_2, (0x37 << DPI_SHIFT_VREF_S_0) | DPI_BIT_VREF_RANGE_0, 0xFF);
	}

	DBG_DRAM_WARN("dpi_dev_map->DPI_PAD_BUS_2 = %x\r\n", dpi_dev_map->DPI_PAD_BUS_2);

	/*zq_ena_nocd2 = 0*/
	dpi_dev_map->DPI_ZQ_NOCD2 = 0x0;

	dpi_dev_map->DPI_PAD_CTRL_PROG = 0x3000C99;

	/*Update immediately*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);////CHUN-CHI

	/*FW set read delay chain of data slice*/
	dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);

	hal_delay_us(10);

	/*R480 Calibration enable*/
	dpi_dev_map->DPI_PAD_CTRL_PROG = 0x3010C99;

	/*Wait Calibration done*/
	while (!(dpi_dev_map->DPI_PAD_RZCTRL_STATUS & 0x1));

	DBG_DRAM_WARN("PAD_ZCTRL_STATUS = %x\r\n", dpi_dev_map->DPI_PAD_ZCTRL_STATUS);
	DBG_DRAM_WARN("DPI_PAD_RZCTRL_STATUS = %x\r\n", dpi_dev_map->DPI_PAD_RZCTRL_STATUS);

	/*R480 Calibration disable*/
	dpi_dev_map->DPI_PAD_CTRL_PROG = 0x3000C99;
}

void dram_zq_calibration(u8 dram_type)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;

	DBG_DRAM_WARN("ZQ K.\r\n");

	/*Enable IBX current*/
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	HAL_WRITE32(SYSON_S_BASE, 0x120, HAL_READ32(SYSON_S_BASE, 0x120) | (BIT19 | BIT22));
#else
	HAL_WRITE32(SYSON_S_BASE, 0x120, HAL_READ32(SYSON_S_BASE, 0x120) | (BIT18 | BIT19 | BIT22));
#endif
	dpi_dev_map->DPI_PAD_BUS_0 = 0x901B0000;

	if (dram_type == DDR_2) {
		/*vref_range[27]:28~92%,zq_vref[26:21]:50%*/
		cpu_read_modify_write(&dpi_dev_map->DPI_PAD_BUS_2, 0xC << DPI_SHIFT_VREF_S_0, 0xFF);
	} else {
		/*vref_range_0[7]:0.5~63.5% = 0,vref_s_0[6:1] = 110010, vref_pad_0[0] = 0*/
		cpu_read_modify_write(&dpi_dev_map->DPI_PAD_BUS_2, (0x32 << DPI_SHIFT_VREF_S_0) | DPI_BIT_VREF_RANGE_0, 0xFF);
	}

	/*zq_ena_nocd2 = 0*/
	dpi_dev_map->DPI_ZQ_NOCD2 = 0x0;

	/*auto update when calibration done*/
	dpi_dev_map->DPI_PAD_CTRL_PROG = 0xE000C99;

	/*Update immediately*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);////CHUN-CHI

	/*FW set read delay chain of data slice*/
	dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);

	hal_delay_us(10);

	/*Enable auto update OCD/ODT set0*/
	cpu_read_modify_write(&dpi_dev_map->DPI_PAD_CTRL_PROG, 0x0, 0x70000000);

	/*OCD: 34, ODT: 120*/
	dpi_dev_map->DPI_PAD_CTRL_ZPROG = 0x14011E;
	dpi_dev_map->DPI_PAD_NOCD2_ZPROG = 0x11E;

	/*Calibration start*/
	dpi_dev_map->DPI_PAD_CTRL_PROG |= DPI_BIT_ZCTRL_START;

	/*Wait Calibration done*/
	while (!(dpi_dev_map->DPI_PAD_ZCTRL_STATUS & BIT31));

	/*Disable Calibration*/
	dpi_dev_map->DPI_PAD_CTRL_PROG &= ~DPI_BIT_ZCTRL_START;
	DBG_DRAM_WARN("set0 PAD_ZCTRL_RESULT = %x\r\n", dpi_dev_map->DPI_PAD_ZCTRL_RESULT);

	/*Enable auto update OCD/ODT set1*/
	cpu_read_modify_write(&dpi_dev_map->DPI_PAD_CTRL_PROG, 0x10000000, 0x70000000);

	/*OCD: 40, ODT: 150*/
	dpi_dev_map->DPI_PAD_CTRL_ZPROG_1 = 0x10003C;
	dpi_dev_map->DPI_PAD_NOCD2_ZPROG_1 = 0x3C;

	/*Calibration start*/
	dpi_dev_map->DPI_PAD_CTRL_PROG |= DPI_BIT_ZCTRL_START;

	/*Wait Calibration done*/
	while (!(dpi_dev_map->DPI_PAD_ZCTRL_STATUS & BIT31));

	/*Disable Calibration*/
	dpi_dev_map->DPI_PAD_CTRL_PROG &= ~DPI_BIT_ZCTRL_START;
	DBG_DRAM_WARN("set1 PAD_ZCTRL_RESULT = %x\r\n", dpi_dev_map->DPI_PAD_ZCTRL_RESULT);

	/*Enable auto update OCD/ODT set2*/
	cpu_read_modify_write(&dpi_dev_map->DPI_PAD_CTRL_PROG, 0x20000000, 0x70000000);

	/*OCD: 60, ODT: 300*/
	dpi_dev_map->DPI_PAD_CTRL_ZPROG_2 = 0x80100;
	dpi_dev_map->DPI_PAD_NOCD2_ZPROG_2 = 0x100;

	/*Calibration start*/
	dpi_dev_map->DPI_PAD_CTRL_PROG |= DPI_BIT_ZCTRL_START;

	/*Wait Calibration done*/
	while (!(dpi_dev_map->DPI_PAD_ZCTRL_STATUS & BIT31));

	/*Disable Calibration*/
	dpi_dev_map->DPI_PAD_CTRL_PROG &= ~DPI_BIT_ZCTRL_START;
	DBG_DRAM_WARN("set2 PAD_ZCTRL_RESULT = %x\r\n", dpi_dev_map->DPI_PAD_ZCTRL_RESULT);

	/*Enable auto update OCD/ODT set3*/
	cpu_read_modify_write(&dpi_dev_map->DPI_PAD_CTRL_PROG, 0x30000000, 0x70000000);

	/*OCD: 50, ODT: 800*/
	dpi_dev_map->DPI_PAD_CTRL_ZPROG_3 = 0x30030;
	dpi_dev_map->DPI_PAD_NOCD2_ZPROG_3 = 0x30;

	/*Calibration start*/
	dpi_dev_map->DPI_PAD_CTRL_PROG |= DPI_BIT_ZCTRL_START;

	/*Wait Calibration done*/
	while (!(dpi_dev_map->DPI_PAD_ZCTRL_STATUS & BIT31));

	/*Disable Calibration*/
	dpi_dev_map->DPI_PAD_CTRL_PROG &= ~DPI_BIT_ZCTRL_START;
	DBG_DRAM_WARN("set3 PAD_ZCTRL_RESULT = %x\r\n", dpi_dev_map->DPI_PAD_ZCTRL_RESULT);

	/*Enable auto update OCD/ODT set4*/
	cpu_read_modify_write(&dpi_dev_map->DPI_PAD_CTRL_PROG, 0x40000000, 0x70000000);

	/*OCD: 32, ODT: 160*/
	dpi_dev_map->DPI_PAD_CTRL_ZPROG_4 = 0xF0120;
	dpi_dev_map->DPI_PAD_NOCD2_ZPROG_4 = 0x120;

	/*Calibration start*/
	dpi_dev_map->DPI_PAD_CTRL_PROG |= DPI_BIT_ZCTRL_START;

	/*Wait Calibration done*/
	while (!(dpi_dev_map->DPI_PAD_ZCTRL_STATUS & BIT31));

	/*Disable Calibration*/
	dpi_dev_map->DPI_PAD_CTRL_PROG &= ~DPI_BIT_ZCTRL_START;
	DBG_DRAM_WARN("set4 PAD_ZCTRL_RESULT = %x\r\n", dpi_dev_map->DPI_PAD_ZCTRL_RESULT);

	/*Enable auto update OCD/ODT set5*/
	cpu_read_modify_write(&dpi_dev_map->DPI_PAD_CTRL_PROG, 0x50000000, 0x70000000);

	/*OCD: 80, ODT: 75*/
	dpi_dev_map->DPI_PAD_CTRL_ZPROG_5 = 0x20001E;
	dpi_dev_map->DPI_PAD_NOCD2_ZPROG_5 = 0x1E;

	/*Calibration start*/
	dpi_dev_map->DPI_PAD_CTRL_PROG |= DPI_BIT_ZCTRL_START;

	/*Wait Calibration done*/
	while (!(dpi_dev_map->DPI_PAD_ZCTRL_STATUS & BIT31));

	/*Disable Calibration*/
	dpi_dev_map->DPI_PAD_CTRL_PROG &= ~DPI_BIT_ZCTRL_START;
	DBG_DRAM_WARN("set5 PAD_ZCTRL_RESULT = %x\r\n", dpi_dev_map->DPI_PAD_ZCTRL_RESULT);

	/*Enable auto update OCD/ODT set6*/
	cpu_read_modify_write(&dpi_dev_map->DPI_PAD_CTRL_PROG, 0x60000000, 0x70000000);

	/*OCD: 50, ODT: 40*/
	dpi_dev_map->DPI_PAD_CTRL_ZPROG_6 = 0x3C0108;
	dpi_dev_map->DPI_PAD_NOCD2_ZPROG_6 = 0x108;

	/*Calibration start*/
	dpi_dev_map->DPI_PAD_CTRL_PROG |= DPI_BIT_ZCTRL_START;

	/*Wait Calibration done*/
	while (!(dpi_dev_map->DPI_PAD_ZCTRL_STATUS & BIT31));

	/*Disable Calibration*/
	dpi_dev_map->DPI_PAD_CTRL_PROG &= ~DPI_BIT_ZCTRL_START;
	DBG_DRAM_WARN("set6 PAD_ZCTRL_RESULT = %x\r\n", dpi_dev_map->DPI_PAD_ZCTRL_RESULT);

	dpi_dev_map->DPI_ODT_TTCP1_SET0 &= ~DPI_MASK_ODT_TTCP_SET_7_PRE;
	dpi_dev_map->DPI_ODT_TTCN1_SET0 &= ~DPI_MASK_ODT_TTCP_SET_7_PRE;
	dpi_dev_map->DPI_OCDP1_SET0 &= ~DPI_MASK_ODT_TTCP_SET_7_PRE;
	dpi_dev_map->DPI_OCDN1_SET0 &= ~DPI_MASK_ODT_TTCP_SET_7_PRE;
	dpi_dev_map->DPI_ODT_TTCP1_SET1 &= ~DPI_MASK_ODT_TTCP_SET_7;
	dpi_dev_map->DPI_ODT_TTCN1_SET1 &= ~DPI_MASK_ODT_TTCP_SET_7;
	dpi_dev_map->DPI_OCDP1_SET1 &= ~DPI_MASK_OCDP_SET_7;
	dpi_dev_map->DPI_OCDN1_SET1 &= ~DPI_MASK_OCDN_SET_7;
	dpi_dev_map->DPI_PAD_CTRL_PROG |= (DPI_BIT_DZQ_REF_UP | DPI_BIT_DZQ_AUTO_UP);

	/*Enable Power down after ZQ calibration done*/
	dpi_dev_map->DPI_PAD_BUS_1 |= BIT6;
	dpi_dev_map->DPI_PAD_BUS_0 |= BIT18;

	/*Disable IBX current*/
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	HAL_WRITE32(SYSON_S_BASE, 0x120, HAL_READ32(SYSON_S_BASE, 0x120) & ~(BIT19 | BIT22));
#else
	HAL_WRITE32(SYSON_S_BASE, 0x120, HAL_READ32(SYSON_S_BASE, 0x120) & ~(BIT18 | BIT19 | BIT22));
#endif
}

void dram_set_pll_frequency(u32 ddr_freq, unsigned short *pll_table)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;
	u32 pll_ctl3_reg = 0;

	if (ddr_freq >= 400) {
		if (ddr_freq < 500) {
			pll_table[3] = 0x1;
		}

		if (ddr_freq < 440) {
			pll_table[0] = 0x1;
		}
	}

	pll_ctl3_reg = ((pll_table[0] << DPI_SHIFT_CCO_BAND)
					| (pll_table[1] << DPI_SHIFT_CCO_KVCO)
					| (pll_table[2] << DPI_SHIFT_ICP)
					| (pll_table[3] << DPI_SHIFT_LOOP_PI_ISEL)
					| (pll_table[4] << DPI_SHIFT_LPF_CP)
					| (pll_table[5] << DPI_SHIFT_LPF_SR)
					| (pll_table[6] << DPI_SHIFT_PDIV)
					| (pll_table[7] << DPI_SHIFT_PLL_LDO_VSEL)
					| (pll_table[8] << DPI_SHIFT_PLL_SEL_CPMODE)
					| (pll_table[9] << DPI_SHIFT_POST_PI_BIAS)
					| (pll_table[10] << DPI_SHIFT_POST_PI_RL)
					| (pll_table[11] << DPI_SHIFT_POST_PI_RS)
					| (pll_table[12] << DPI_SHIFT_V11_LDO_VSEL));

	dpi_dev_map->DPI_PLL_CTL3 = pll_ctl3_reg;
	DBG_DRAM_WARN("pll_ctl3_reg = %x\r\n", pll_ctl3_reg);
}

void dram_init_clk_frequency_dss(uint32_t ddr_freq, uint32_t down_spread_percent)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;
	u32 n_code = 0, f_code = 0, n_code_t = 0, f_code_t = 0, gran_set = 0, dot_gran = 4;
	u32 value = 0;
	u32 f_code_change = 0, f_code_step = 0;
	u8 ss_en = 0;

	n_code_t = (ddr_freq / DDR_PLL_REF_CLK) - 3;
	f_code_t = ((ddr_freq * 1000 / DDR_PLL_REF_CLK) - (n_code_t + 3) * 1000) * 2048 / 1000;
	DBG_DRAM_WARN("n_code_t = %d, f_code_t = %d\r\n", n_code_t, f_code_t);

	if (down_spread_percent == 0) {
		n_code = n_code_t;
		f_code = f_code_t;
	} else {
		value = (((n_code_t + 3) * 2048 + f_code_t) * (100 - down_spread_percent)) / 100;
		DBG_DRAM_WARN("value = %d\r\n", value);
		n_code  = (value / 2048) - 3;
		f_code  = (value - (n_code + 3) * 2048);
		DBG_DRAM_WARN("n_code = %d, f_code = %d\r\n", n_code, f_code);
		f_code_change = (n_code_t * 2048 + f_code_t) - (n_code * 2048 + f_code);
		f_code_step = (DDR_PLL_REF_CLK * 1000000 / 33000) / 2;
		gran_set = f_code_change * 2048 / f_code_step;
		DBG_DRAM_WARN("f_code_change = %d, f_code_step = %d, gran_set = %d\r\n", f_code_change, f_code_step, gran_set);
		ss_en = 1;
	}

	if (ss_en) {
		/*Disable Spread spectrum*/
		dpi_dev_map->DPI_SSC0 &= ~DPI_BIT_EN_SSC;
		DBG_DRAM_WARN("&dpi_dev_map->DPI_SSC0 = %x\r\n", dpi_dev_map->DPI_SSC0);

		/*Set dot_gran & gran_set*/
		cpu_read_modify_write(&dpi_dev_map->DPI_SSC1, (gran_set | (dot_gran << DPI_SHIFT_DOT_GRAN)), DPI_MASK_GRAN_SET | DPI_MASK_DOT_GRAN);
		DBG_DRAM_WARN("&dpi_dev_map->DPI_SSC1 = %x\r\n", dpi_dev_map->DPI_SSC1);

		/*Set f_code & f_code_t*/
		cpu_read_modify_write(&dpi_dev_map->DPI_SSC2, (f_code | (f_code_t << DPI_SHIFT_F_CODE_T)), DPI_MASK_F_CODE | DPI_MASK_F_CODE_T);
		DBG_DRAM_WARN("&dpi_dev_map->DPI_SSC2 = %x\r\n", dpi_dev_map->DPI_SSC2);

		/*Set n_code & n_code_t*/
		cpu_read_modify_write(&dpi_dev_map->DPI_SSC3, (n_code | (n_code_t << DPI_SHIFT_N_CODE_T)), DPI_MASK_N_CODE | DPI_MASK_N_CODE_T);
		DBG_DRAM_WARN("&dpi_dev_map->DPI_SSC3 = %x\r\n", dpi_dev_map->DPI_SSC3);

		/*Enable Spread spectrum*/
		dpi_dev_map->DPI_SSC0 |= (DPI_BIT_EN_SSC | DPI_BIT_SSC_FLAG_INIT);
		DBG_DRAM_WARN("&dpi_dev_map->DPI_SSC0 = %x\r\n", dpi_dev_map->DPI_SSC0);
	} else {
		/*Set f_code & f_code_t*/
		cpu_read_modify_write(&dpi_dev_map->DPI_SSC2, (f_code | (f_code_t << DPI_SHIFT_F_CODE_T)), DPI_MASK_F_CODE | DPI_MASK_F_CODE_T);

		/*Set n_code & n_code_t*/
		cpu_read_modify_write(&dpi_dev_map->DPI_SSC3, (n_code | (n_code_t << DPI_SHIFT_N_CODE_T)), DPI_MASK_N_CODE | DPI_MASK_N_CODE_T);
	}
}

