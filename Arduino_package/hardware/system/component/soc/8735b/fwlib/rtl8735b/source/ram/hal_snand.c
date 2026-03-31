/**************************************************************************//**
 * @file     hal_snand.c
 * @brief    Functions to implement the Serial NAND Flash Controller (SNAFC) operation.
 * @version  1.00
 * @date     2020-12-12
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2020 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/
#include "hal_snand.h"
#include "hal_pinmux.h"
#include "hal_cache.h"
#include "fw_snand_boot.h"
#include "memory.h"

#if CONFIG_FPGA
#include "hal_gpio.h"
#endif

#if IS_CUT_TEST(CONFIG_CHIP_VER) || (defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE==1))
#define HAL_SNAND_STUBS hal_snand_ns_stubs
extern const hal_snand_func_stubs_t hal_snand_ns_stubs;
#else
#define HAL_SNAND_STUBS hal_snand_stubs
extern const hal_snand_func_stubs_t hal_snand_stubs;
#endif


/// Size of calibration tuning pattern
#define SNAND_TUNING_PATTERN_LEN (64/sizeof(uint8_t))
/// The fixed tuning pattern
const static uint8_t snandTunningBlockPattern[SNAND_TUNING_PATTERN_LEN] = {
	0x00, 0xff, 0x0f, 0xff, 0xcc, 0xc3, 0xcc, 0xff, 0xff, 0xcc, 0x3c, 0xc3, 0xef, 0xfe, 0xff, 0xfe,
	0xdd, 0xff, 0xdf, 0xff, 0xfb, 0xff, 0xfb, 0xff, 0xff, 0x7f, 0xff, 0xbf, 0xef, 0xbd, 0xf7, 0x77,
	0xf0, 0xff, 0xf0, 0xff, 0x3c, 0xcc, 0xfc, 0x0f, 0xcf, 0xcc, 0x33, 0xcc, 0xee, 0xff, 0xef, 0xff,
	0xfd, 0xff, 0xfd, 0xff, 0xff, 0xbf, 0xff, 0xdf, 0xff, 0xf7, 0xff, 0xbb, 0xde, 0x7b, 0x7f, 0xf7,
};

#define SNAFC_MAX_CLKDIV (0x7)
#define SNAFC_MAX_PIPELAT (0x3)
#define SNAND_BUS_K_IDX (3)
#define NAND_FLSH_BLK_NUM(size)     (size >> 17)

/// Temporary buffer to load flash data
static u8 snand_memcpy_buf[NAND_PAGE_MAX_LEN] __ALIGNED(32);
/// Record which page was loaded into snand_memcpy_buf to reduce redundant load
static u32 snand_memcpy_buf_cached_page = 0xFFFFFFFF;

/// Ctrl info copied from ROM data
snand_ctrl_info_t snand_ctrl_info;
/// Partition table copied from ROM data
snand_partition_tbl_t hal_snand_part_tbl;
/// Flag indicates if layout info is inited
BOOL snand_layout_info_inited = FALSE;

#ifdef CONFIG_BUILD_NONSECURE
/// This info should be inited by S ram_start, then copied to above structs
hal_snand_layout_info_t hal_snand_layout_info_ns = {
	.ctrl_info = {
		.blk_cnt = 1,       // prevent clean by NS ram_start
	},
	.inited = FALSE,
};
#endif

/**

        \addtogroup hal_snand Flash Controller
        @{
*/
#if 0 /* keep for (verify) reference */
/**
 ++ S-NAND flash dependent callback function implementation ++
*/
static uint32_t mSnandWaitRdyFuncType0(uint32_t timeout);
static uint32_t mSnandChkWelStsFuncType0(void);
static uint32_t mSnandChkEFaillStsFuncType0(void);
static uint32_t mSnandChkPFailStsFuncType0(void);
static uint32_t mSnandChkEccStsFuncType0(void);

static uint32_t mSnandEnableQuadBusModeType0(void);
static uint32_t mSnandDisableQuadBusModeType0(void);
static uint32_t mSnandEnableOnChipEccType0(void);
static uint32_t mSnandDisableOnChipEccType0(void);

static uint32_t mSnandBlockProtectNoneFuncType0(void);
static uint32_t mSnandBlockProtectAllFuncType0(void);
static uint32_t mSnandBlockProtectNoneFuncType1(void);
static uint32_t mSnandBlockProtectAllFuncType1(void);

static uint32_t
mSnandWaitRdyFuncType0(
	uint32_t timeout
)
{
	uint32_t stsReg = 0xc0;
	uint32_t retVal;
	uint32_t swTo = 0;
#define WAIT_OIP_RDY_MSK (0x100)
#define WAIT_OIP_RDY_MAX (0x800)
	retVal = hal_snand_get_status(NULL, stsReg);
	while ((retVal >> 0 & 0x1) != 0) {
		retVal = hal_snand_get_status(NULL, stsReg);
		swTo++;
		if (swTo > WAIT_OIP_RDY_MAX) {
			break;
		}
	}
	if (swTo > WAIT_OIP_RDY_MAX) {
		return FAIL;
	}
	return SUCCESS;
}

static uint32_t
mSnandChkWelStsFuncType0(
	void
)
{
	uint32_t stsReg = 0xc0;
	uint32_t retVal;
	retVal = hal_snand_get_status(NULL, stsReg);
	if (retVal >> 1 & 0x1) {
		return SNAND_STS_WRITE_ENABLE_LATCHED;
	}
	return SNAND_STS_WEL_NONE;
}

static uint32_t
mSnandChkEFaillStsFuncType0(
	void
)
{
	uint32_t stsReg = 0xc0;
	uint32_t retVal;
	retVal = hal_snand_get_status(NULL, stsReg);
	if (retVal >> 2 & 0x1) {
		return SNAND_STS_ERASE_FAIL;
	}
	return SNAND_STS_ERASE_NO_ERR;
}

static uint32_t
mSnandChkPFailStsFuncType0
(
	void
)
{
	uint32_t stsReg = 0xc0;
	uint32_t retVal;
	retVal = hal_snand_get_status(NULL, stsReg);
	if (retVal >> 3 & 0x1) {
		return SNAND_STS_PROGRAM_FAIL;
	}
	return SNAND_STS_PROGRAM_NO_ERR;
}

static uint32_t
mSnandChkEccStsFuncType0(
	void
)
{
	uint32_t stsReg = 0xc0;
	uint32_t retVal;
	retVal = hal_snand_get_status(NULL, stsReg);
	switch (retVal >> 4 & 0x3) {
	case 0:
		return SNAND_STS_ECC_NO_ERR;
	case 1:
		return SNAND_STS_ECC_ERR_AND_FIXED;
	default:
	case 2:
		return SNAND_STS_ECC_ERR_CANNOT_FIX;
	}
}

static uint32_t
mSnandEnableQuadBusModeType0(
	void
)
{
	uint32_t stsReg = 0xb0;
	uint32_t retVal;
	retVal = hal_snand_get_status(NULL, stsReg);
	retVal |= 0x01;
	hal_snand_set_status(NULL, stsReg, retVal);
	return SUCCESS;
}

static uint32_t
mSnandDisableQuadBusModeType0(
	void
)
{
	uint32_t stsReg = 0xb0;
	uint32_t retVal;
	retVal = hal_snand_get_status(NULL, stsReg);
	retVal &= ~0x01;
	hal_snand_set_status(NULL, stsReg, retVal);
	return SUCCESS;
}

static uint32_t
mSnandEnableOnChipEccType0(
	void
)
{
	uint32_t stsReg = 0xb0;
	uint32_t retVal;
	retVal = hal_snand_get_status(NULL, stsReg);
	retVal |= (0x01 << 4);
	hal_snand_set_status(NULL, stsReg, retVal);
	return SUCCESS;
}

static uint32_t
mSnandDisableOnChipEccType0(
	void
)
{
	uint32_t stsReg = 0xb0;
	uint32_t retVal;
	retVal = hal_snand_get_status(NULL, stsReg);
	retVal &= ~(0x01 << 4);
	hal_snand_set_status(NULL, stsReg, retVal);
	return SUCCESS;
}

static uint32_t
mSnandBlockProtectNoneFuncType0(
	void
)
{
	uint32_t stsReg = 0xa0;
	uint32_t retVal;
	retVal = hal_snand_get_status(NULL, stsReg);
	retVal &= ~(0x07 << 3);
	hal_snand_set_status(NULL, stsReg, retVal);
	return SUCCESS;
}

static uint32_t
mSnandBlockProtectAllFuncType0(
	void
)
{
	uint32_t stsReg = 0xa0;
	uint32_t retVal;
	retVal = hal_snand_get_status(NULL, stsReg);
	retVal |= (0x07 << 3);
	hal_snand_set_status(NULL, stsReg, retVal);
	return SUCCESS;
}

static uint32_t
mSnandBlockProtectNoneFuncType1(
	void
)
{
	uint32_t stsReg = 0xa0;
	uint32_t retVal;
	retVal = hal_snand_get_status(NULL, stsReg);
	retVal &= ~(0x0F << 3);
	hal_snand_set_status(NULL, stsReg, retVal);
	return SUCCESS;
}

static uint32_t
mSnandBlockProtectAllFuncType1(
	void
)
{
	uint32_t stsReg = 0xa0;
	uint32_t retVal;
	retVal = hal_snand_get_status(NULL, stsReg);
	retVal |= (0x0F << 3);
	hal_snand_set_status(NULL, stsReg, retVal);
	return SUCCESS;
}
#endif /* keep for (verify) reference */
/**
 -- S-NAND flash dependent callback function implementation ++
*/

/**
 ++ GLOBAL-TOP-dependent information (not specified by SNAFC) ++
*/
hal_status_t hal_snand_pinmux_ctl(hal_snafc_adaptor_t *pAdaptor /* unused */, uint8_t ctl)
{
	hal_status_t ret = HAL_OK;
#if CONFIG_FPGA /* Philip@2021/06/03, DV's Saurabh Adhikari said, during SNAFC enable, C1/C3 should not set to pull-up */
	uint8_t quad_pin_sel = 0; /* 0 for 1-pin, 2-pin, !0 for 4-pin */
#endif

	if (ctl == ENABLE) {
#if CONFIG_FPGA
		hal_pinmux_register(PIN_C0, PID_GPIO);
		hal_pinmux_register(PIN_C2, PID_GPIO);
		hal_pinmux_register(PIN_C4, PID_GPIO);
		hal_pinmux_register(PIN_C5, PID_GPIO);

		if (quad_pin_sel) {
			hal_pinmux_register(PIN_C1, PID_GPIO);
			hal_pinmux_register(PIN_C3, PID_GPIO);
		} else {
			hal_gpio_pull_ctrl((u32)PIN_C1, Pin_PullUp);
			hal_gpio_pull_ctrl((u32)PIN_C3, Pin_PullUp);
		}
#else
		hal_pinmux_register(PIN_C0, PID_FLASH);
		hal_pinmux_register(PIN_C2, PID_FLASH);
		hal_pinmux_register(PIN_C4, PID_FLASH);
		hal_pinmux_register(PIN_C5, PID_FLASH);

#if 1 /* Philip@2021/06/03, DV's Saurabh Adhikari said, during SNAFC enable, C1/C3 should not set to pull-up */
		hal_pinmux_register(PIN_C1, PID_FLASH);
		hal_pinmux_register(PIN_C3, PID_FLASH);
#else /* original */
		if (quad_pin_sel) {
			hal_pinmux_register(PIN_C1, PID_FLASH);
			hal_pinmux_register(PIN_C3, PID_FLASH);
		} else {
			hal_gpio_pull_ctrl((u32)PIN_C1, Pin_PullUp);
			hal_gpio_pull_ctrl((u32)PIN_C3, Pin_PullUp);
		}
#endif
#endif
	} else {
#if CONFIG_FPGA
		hal_pinmux_unregister(PIN_C0, PID_GPIO);
		hal_pinmux_unregister(PIN_C2, PID_GPIO);
		hal_pinmux_unregister(PIN_C4, PID_GPIO);
		hal_pinmux_unregister(PIN_C5, PID_GPIO);

		if (quad_pin_sel) {
			hal_pinmux_unregister(PIN_C1, PID_GPIO);
			hal_pinmux_unregister(PIN_C3, PID_GPIO);
		} else {
			hal_gpio_pull_ctrl((u32)PIN_C1, Pin_PullDefault);
			hal_gpio_pull_ctrl((u32)PIN_C3, Pin_PullDefault);
		}
#else
		hal_pinmux_unregister(PIN_C0, PID_FLASH);
		hal_pinmux_unregister(PIN_C2, PID_FLASH);
		hal_pinmux_unregister(PIN_C4, PID_FLASH);
		hal_pinmux_unregister(PIN_C5, PID_FLASH);

#if 1 /* Philip@2021/06/03, DV's Saurabh Adhikari said, during SNAFC enable, C1/C3 should not set to pull-up */
		hal_pinmux_unregister(PIN_C1, PID_FLASH);
		hal_pinmux_unregister(PIN_C3, PID_FLASH);
#else /* original */
		if (quad_pin_sel) {
			hal_pinmux_unregister(PIN_C1, PID_FLASH);
			hal_pinmux_unregister(PIN_C3, PID_FLASH);
		} else {
			hal_gpio_pull_ctrl((u32)PIN_C1, Pin_PullDefault);
			hal_gpio_pull_ctrl((u32)PIN_C3, Pin_PullDefault);
		}
#endif
#endif
	}

	return ret;
}/* hal_snand_pinmux_ctl */
/**
 -- GLOBAL-TOP-dependent information (not specified by SNAFC) --
*/

/**

        \addtogroup hs_hal_snand_ram_func Flash Controller HAL RAM APIs
        \ingroup hs_hal_snand
        \brief The flash controller HAL APIs. Functions become an interface between API functions and ROM codes.
        @{
*/

void
hal_snand_init(
	hal_snafc_adaptor_t *pAdaptor
)
{
	hal_snand_pinmux_ctl(pAdaptor, ENABLE);
	HAL_SNAND_STUBS.hal_snand_init(pAdaptor);

	// Init ctrl info
	if (FALSE == snand_layout_info_inited) {
		hal_snand_init_ctrl_info();
		// TODO return FAIL
	}

	return;
} /* hal_snand_init */


void
hal_snand_deinit(
	hal_snafc_adaptor_t *pAdaptor
)
{
	HAL_SNAND_STUBS.hal_snand_deinit(pAdaptor);
	hal_snand_pinmux_ctl(pAdaptor, DISABLE);
	return;
} /* hal_snand_deinit */

void hal_snand_adtr_reset(hal_snafc_adaptor_t *pSnafcAdaptor)
{
	if (pSnafcAdaptor) {
		memset(pSnafcAdaptor, 0, sizeof(hal_snafc_adaptor_t));
		pSnafcAdaptor->initVal[SNAFC_SPEED_SEL_0].l = 0x00001043; /* 0x00003043 */ /* Est. sck=12.50 MHz, with pipe_lat=0 (0..3) */
		pSnafcAdaptor->initVal[SNAFC_SPEED_SEL_1].l = 0x00001023; /* 0x00003023 */ /* Est. sck=20.83 MHz, with pipe_lat=0 (0..3) */
		pSnafcAdaptor->initVal[SNAFC_SPEED_SEL_2].l = 0x00001013; /* 0x00003013 */ /* Est. sck=31.25 MHz, with pipe_lat=0 (0..3) */
		pSnafcAdaptor->initVal[SNAFC_SPEED_SEL_3].l = 0x00001103; /* 0x00003103 */ /* Est. sck=62.50 MHz, with pipe_lat=1 (0..3) */
		pSnafcAdaptor->clkSel = SNAFC_SPEED_SEL_1;
		pSnafcAdaptor->pinmuxSel = SnafcPinmuxCfg_0;
		pSnafcAdaptor->maxCtrlRdyCnt = 0x1000;
		pSnafcAdaptor->maxDmaRdyCnt = 0x10000;
		pSnafcAdaptor->maxWaitOipCnt = 0x4000;
		pSnafcAdaptor->dma_en = 1;
		pSnafcAdaptor->col_addr = 0;
		pSnafcAdaptor->funcWaitSnandReady = NULL;
		pSnafcAdaptor->funcBlockProtectNone = NULL;
		pSnafcAdaptor->funcBlockProtectAll = NULL;
		pSnafcAdaptor->funcEnQuadSpiMode = NULL;
		pSnafcAdaptor->funcDisQuadSpiMode = NULL;
		pSnafcAdaptor->funcChkEccSts = NULL;
		pSnafcAdaptor->funcChkPgmSts = NULL;
		pSnafcAdaptor->snand_cmd_info.w_cmd_cycle = 1;
		pSnafcAdaptor->snand_cmd_info.w_cmd = SNAND_PROGRAM_LOAD_OP;
		pSnafcAdaptor->snand_cmd_info.w_addr_cycle = 3;
		pSnafcAdaptor->snand_cmd_info.w_addr_io = SNAFC_SIO_WIDTH;
		pSnafcAdaptor->snand_cmd_info.w_data_io = SNAFC_SIO_WIDTH;
		pSnafcAdaptor->snand_cmd_info.r_cmd_cycle = 1;
		pSnafcAdaptor->snand_cmd_info.r_cmd = SNAND_NORMAL_READ_OP;
		pSnafcAdaptor->snand_cmd_info.r_addr_cycle = 3;
		pSnafcAdaptor->snand_cmd_info.r_addr_io = SNAFC_SIO_WIDTH;
		pSnafcAdaptor->snand_cmd_info.r_data_io = SNAFC_SIO_WIDTH;
	}
}

void hal_snand_clk_sel(hal_snafc_adaptor_t *snafc_adpt, snafc_clk_sel_t sel)
{
	if (snafc_adpt) {
		if (sel > SNAFC_SPEED_SEL_3) {
			sel = SNAFC_SPEED_SEL_3;
		}
		snafc_adpt->clkSel = sel;
	}
}

uint32_t
hal_snand_reset_to_spi(
	hal_snafc_adaptor_t *pAdaptor
)
{
	return HAL_SNAND_STUBS.hal_snand_reset_to_spi(pAdaptor);
} /* hal_snand_reset_to_spi */


uint32_t
hal_snand_read_id(
	hal_snafc_adaptor_t *pAdaptor
)
{
	uint32_t retVal;
	retVal = HAL_SNAND_STUBS.hal_snand_read_id(pAdaptor);
	if (pAdaptor) {
		pAdaptor->devId[0] = (retVal >> 16) & 0xFF;
		pAdaptor->devId[1] = (retVal >> 8) & 0xFF;
		pAdaptor->devId[2] = (retVal >> 0) & 0xFF;
	}
	return retVal;
} /* hal_snand_read_id */


void
hal_snand_set_quad_enable(
	hal_snafc_adaptor_t *pAdaptor
)
{
	u32 val, status_id = 0xb0;

	// Enable quad bit mode
	val = hal_snand_get_status(pAdaptor, status_id);
	val |= 0x01;
	hal_snand_set_status(pAdaptor, status_id, val);
	//return HAL_SNAND_STUBS.hal_snand_set_quad_enable(pAdaptor);
} /* hal_snand_set_quad_enable */


void
hal_snand_unset_quad_enable(
	hal_snafc_adaptor_t *pAdaptor
)
{
	u32 val, status_id = 0xb0;

	// Disable quad bit mode
	val = hal_snand_get_status(pAdaptor, status_id);
	val &= (~0x01);
	hal_snand_set_status(pAdaptor, status_id, val);
	//return HAL_SNAND_STUBS.hal_snand_unset_quad_enable(pAdaptor);
} /* hal_snand_unset_quad_enable */



void
hal_snand_set_status(
	hal_snafc_adaptor_t *pAdaptor,
	uint8_t cmd,
	uint8_t data
)
{
	return HAL_SNAND_STUBS.hal_snand_set_feature(pAdaptor, cmd, data);
} /* hal_snand_set_status */


void
hal_snand_set_status_no_check(
	hal_snafc_adaptor_t *pAdaptor,
	uint8_t cmd,
	uint8_t data
)
{
	return HAL_SNAND_STUBS.hal_snand_set_feature_no_check(pAdaptor, cmd, data);
} /* hal_snand_set_status_no_check */


uint32_t
hal_snand_get_status(
	hal_snafc_adaptor_t *pAdaptor,
	uint8_t cmd
)
{
	return HAL_SNAND_STUBS.hal_snand_get_feature(pAdaptor, cmd);
} /* hal_snand_get_status */


uint32_t
hal_snand_wait_ready(
	hal_snafc_adaptor_t *pAdaptor
)
{
	return HAL_SNAND_STUBS.hal_snand_wait_ready(pAdaptor);
} /* hal_snand_wait_ready */


void
hal_snand_set_write_enable(
	hal_snafc_adaptor_t *pAdaptor
)
{
	return HAL_SNAND_STUBS.hal_snand_set_write_enable(pAdaptor);
} /* hal_snand_set_write_enable */


void
hal_snand_set_write_disable(
	hal_snafc_adaptor_t *pAdaptor
)
{
	return HAL_SNAND_STUBS.hal_snand_set_write_disable(pAdaptor);
} /* hal_snand_set_write_disable */


uint32_t
hal_snand_block_erase(
	hal_snafc_adaptor_t *pAdaptor,
	uint32_t blkPageAddr
)
{
	uint32_t retVal = SUCCESS;
	retVal = HAL_SNAND_STUBS.hal_snand_block_erase(pAdaptor, blkPageAddr);
	return retVal;
} /* hal_snand_block_erase */


uint32_t
hal_snand_page_program(
	hal_snafc_adaptor_t *pAdaptor,
	uint32_t blkPageAddr
)
{
	uint32_t retVal = SUCCESS;
	retVal = HAL_SNAND_STUBS.hal_snand_page_program(pAdaptor, blkPageAddr);
	return retVal;
} /* hal_snand_page_program */


uint32_t
hal_snand_pio_read(
	hal_snafc_adaptor_t *pAdaptor,
	void *memAddr,
	uint32_t dataLens,
	uint32_t blkPageAddr
)
{
	uint32_t retVal = SUCCESS;
	uint8_t bakVal = 0;
	if (pAdaptor) {
		bakVal = pAdaptor->dma_en;
		if (bakVal) {
			pAdaptor->dma_en = 0;
		}
	}
	retVal = HAL_SNAND_STUBS.hal_snand_pageRead(pAdaptor, memAddr, dataLens, blkPageAddr);
	if (pAdaptor && bakVal) {
		pAdaptor->dma_en = bakVal;
	}
	return retVal;
} /* hal_snand_pio_read */

uint32_t
hal_snand_page_read(
	hal_snafc_adaptor_t *pAdaptor,
	void *memAddr,
	uint32_t dataLens,
	uint32_t blkPageAddr
)
{
	uint32_t retVal = SUCCESS;

	// DMA dest should be 16 byte-algn, size: 4 byte-align
	// To deal with cache, extend to 32 byte-align
	if ((pAdaptor != NULL) && (pAdaptor->dma_en == 1)) {
		u8 use_indr_dma = FALSE;

		if ((u32)memAddr & (32 - 1)) {
			// Unaligned DMA -> use indirect DMA
			use_indr_dma = TRUE;
		}

		if (dataLens & 0x3) {
			use_indr_dma = TRUE;
		}

		if (use_indr_dma) {
			u32 padding_size = dataLens;
			if (dataLens & 0x3) {
				padding_size += 4;
			}
			dcache_clean_invalidate_by_addr((void *)snand_memcpy_buf, padding_size);
			retVal = HAL_SNAND_STUBS.hal_snand_pageRead(pAdaptor, snand_memcpy_buf, padding_size, blkPageAddr);
			snand_memcpy_buf_cached_page = blkPageAddr;
			dcache_invalidate_by_addr((void *)snand_memcpy_buf, padding_size);

			if (retVal == SUCCESS) {
				memcpy(memAddr, snand_memcpy_buf, dataLens);
			}

		} else {
			// Handle cache for DMA
			dcache_clean_invalidate_by_addr(memAddr, dataLens);
			retVal = HAL_SNAND_STUBS.hal_snand_pageRead(pAdaptor, memAddr, dataLens, blkPageAddr);
			dcache_invalidate_by_addr(memAddr, dataLens);
		}
	} else {
		retVal = HAL_SNAND_STUBS.hal_snand_pageRead(pAdaptor, memAddr, dataLens, blkPageAddr);
	}
	return retVal;
} /* hal_snand_page_read */


// Read NAND page, with caching page in snand_memcpy_buf, dont use with NAND write, Internal use
static uint32_t
hal_snand_page_read_w_cache(
	hal_snafc_adaptor_t *pAdaptor,
	void *memAddr,
	uint32_t dataLens,
	uint32_t blkPageAddr
)
{
	if (memAddr == snand_memcpy_buf && dataLens == NAND_PAGE_LEN) {
		if (blkPageAddr == snand_memcpy_buf_cached_page) {
			// All parameter matches cached data
			return SUCCESS;
		} else {
			snand_memcpy_buf_cached_page = blkPageAddr;
		}
	}

	return hal_snand_page_read(pAdaptor, memAddr, dataLens, blkPageAddr);
}

uint32_t
hal_snand_pio_write(
	hal_snafc_adaptor_t *pAdaptor,
	void *memAddr,
	uint32_t dataLens,
	uint32_t blkPageAddr
)
{
	uint32_t retVal = SUCCESS;
	uint8_t bakVal = 0;
	if (pAdaptor) {
		bakVal = pAdaptor->dma_en;
		if (bakVal) {
			pAdaptor->dma_en = 0;
		}
	}
	retVal = HAL_SNAND_STUBS.hal_snand_pageWrite(pAdaptor, memAddr, dataLens, blkPageAddr);
	if (pAdaptor && bakVal) {
		pAdaptor->dma_en = bakVal;
	}
	return retVal;
} /* hal_snand_pio_write */


uint32_t
hal_snand_dma_read(
	hal_snafc_adaptor_t *pAdaptor,
	void *memAddr,
	uint32_t dataLens,
	uint32_t blkPageAddr
)
{
	uint32_t retVal = SUCCESS;
	uint8_t bakVal = 0;
	if (pAdaptor) {
		bakVal = pAdaptor->dma_en;
		if (!bakVal) {
			pAdaptor->dma_en = 1;
		}
	}
	retVal = HAL_SNAND_STUBS.hal_snand_pageRead(pAdaptor, memAddr, dataLens, blkPageAddr);
	if (pAdaptor && !bakVal) {
		pAdaptor->dma_en = bakVal;
	}
	return retVal;
} /* hal_snand_dma_read */


uint32_t
hal_snand_dma_write(
	hal_snafc_adaptor_t *pAdaptor,
	void *memAddr,
	uint32_t dataLens,
	uint32_t blkPageAddr
)
{
	uint32_t retVal = SUCCESS;
	uint8_t bakVal = 0;
	if (pAdaptor) {
		bakVal = pAdaptor->dma_en;
		if (!bakVal) {
			pAdaptor->dma_en = 1;
		}
	}
	retVal = HAL_SNAND_STUBS.hal_snand_pageWrite(pAdaptor, memAddr, dataLens, blkPageAddr);
	if (pAdaptor && !bakVal) {
		pAdaptor->dma_en = bakVal;
	}
	return retVal;
} /* hal_snand_dma_write */

/**
 *  @brief      Select IO mode. Call this function before hal_snand_init
 *
 *  @param[in]  snafc_adpt The SNAFC adapter.
 *  @param[in]  mode Selected mode (snafcBusTypeMode_t)
 *
 *  @returns    Void.
 */
void hal_snand_io_mode_sel(hal_snafc_adaptor_t *snafc_adpt, snafcBusTypeMode_t mode)
{
	if (!snafc_adpt) {
		return;
	}

	switch (mode) {
	case SnafcOneIOMode:
		snafc_adpt->snand_cmd_info.w_cmd = SNAND_PROGRAM_LOAD_OP;
		snafc_adpt->snand_cmd_info.w_data_io = SNAFC_SIO_WIDTH;
		snafc_adpt->snand_cmd_info.r_cmd = SNAND_NORMAL_READ_OP;
		snafc_adpt->snand_cmd_info.r_data_io = SNAFC_SIO_WIDTH;
		break;

	case SnafcQuadIOMode:
		snafc_adpt->snand_cmd_info.w_cmd = SNAND_PROGRAM_LOAD_X4_OP;
		snafc_adpt->snand_cmd_info.w_data_io = SNAFC_QIO_WIDTH;
		snafc_adpt->snand_cmd_info.r_cmd = SNAND_FAST_READ_X4_OP;
		snafc_adpt->snand_cmd_info.r_data_io = SNAFC_QIO_WIDTH;
		break;
	default:
		break;
	}
}

/**
 *  @brief      Configure the adapter clock setting.
 *
 *  @param[in]  snafc_adpt The SNAFC adapter.
 *  @param[in]  idx The index of in-use clock setting slot.
 *  @param[in]  clkDiv The clock division value
 *  @param[in]  latchDelay The latch delay value
 *
 *  @returns    The result status code.
 */
static int32_t hal_snand_bus_cfg(
	hal_snafc_adaptor_t *snafc_adpt,
	uint32_t idx,
	uint32_t clkDiv,
	uint32_t latchDelay
)
{
	uint32_t tmpVal;
	if (snafc_adpt == NULL) {
		return FAIL;
	}
	if (idx >= 3) {
		idx = 3;
	}
	if (clkDiv >= SNAFC_MAX_CLKDIV) {
		clkDiv = SNAFC_MAX_CLKDIV;
	}
	if (latchDelay >= SNAFC_MAX_PIPELAT) {
		latchDelay = SNAFC_MAX_PIPELAT;
	}
	snafc_adpt->clkSel = idx;
	tmpVal = snafc_adpt->initVal[idx].l;
	tmpVal = (tmpVal & ~(SNAFC_MASK_SPI_CLK_DIV | SNAFC_MASK_PIPE_LAT)) | (latchDelay << SNAFC_SHIFT_PIPE_LAT) | (clkDiv << SNAFC_SHIFT_SPI_CLK_DIV);
	snafc_adpt->initVal[idx].l = tmpVal;
	return SUCCESS;
}

/**
 *  @brief      Run calibration for current NAND Flash.
 *              Try to read predefined golden pattern from NAND control info block.
 *              The testing phases are predefined.
 *
 *  @param[in]  snafc_adpt The SNAFC adapter.
 *
 *  @returns    The result status code.
 */
int32_t hal_snand_bus_calibr(
	hal_snafc_adaptor_t *snafc_adpt
)
{
	uint32_t loopIdx, back_clk_sel, back_init_val;
	uint8_t tmpBuf[SNAND_TUNING_PATTERN_LEN];
	s32 ret;

	if (!snafc_adpt) {
		return FAIL;
	}

	// Backup value
	back_clk_sel = snafc_adpt->clkSel;
	back_init_val = snafc_adpt->initVal[SNAND_BUS_K_IDX].l;

	// Get ctrl info block idx
	uint32_t blk_id = hal_snand_boot_stubs.ctrl_info->ctrl_info_blk_idx;
	uint32_t page_addr = blk_id * HAL_NAND_PAGE_PER_BLK + HAL_NAND_CALIBR_PTN_PAGE;

	// Check calibration pattern exits
	hal_snand_pio_read(snafc_adpt, tmpBuf, SNAND_TUNING_PATTERN_LEN, page_addr);
	ret = memcmp((void *)tmpBuf, snandTunningBlockPattern, SNAND_TUNING_PATTERN_LEN);
	if (ret != 0) {
		DBG_SNAND_ERR("No calibr ptn\r\n");
		return FAIL;
	}

	// Init/ Deinit to apply new setting
	hal_snand_deinit(snafc_adpt);

	for (loopIdx = 0; loopIdx < 4; loopIdx++) {

		// Predefined clock phases
		switch (loopIdx) {
		case 0:
			hal_snand_bus_cfg(snafc_adpt, SNAND_BUS_K_IDX/*idx*/, 0/*clkDiv*/, 1/*latchDelay*/);
			break;
		case 1:
			hal_snand_bus_cfg(snafc_adpt, SNAND_BUS_K_IDX/*idx*/, 0/*clkDiv*/, 0/*latchDelay*/);
			break;
		case 2:
			hal_snand_bus_cfg(snafc_adpt, SNAND_BUS_K_IDX/*idx*/, 1/*clkDiv*/, 0/*latchDelay*/);
			break;
		case 3:
			hal_snand_bus_cfg(snafc_adpt, SNAND_BUS_K_IDX/*idx*/, 1/*clkDiv*/, 1/*latchDelay*/);
			break;
		}
		hal_snand_init(snafc_adpt);
		hal_snand_pio_read(snafc_adpt, tmpBuf, SNAND_TUNING_PATTERN_LEN, page_addr);
		ret = memcmp((void *)tmpBuf, snandTunningBlockPattern, SNAND_TUNING_PATTERN_LEN);

		if (ret == 0) {
			DBG_SNAND_INFO("Calibration pass on case %d\r\n", loopIdx);
			return SUCCESS;
		}

		hal_snand_deinit(snafc_adpt);
	}

	DBG_SNAND_WARN("No calibr ptn match\r\n");

	// Restore value
	snafc_adpt->clkSel = back_clk_sel;
	snafc_adpt->initVal[SNAND_BUS_K_IDX].l = back_init_val;

	// Init with origin setting
	hal_snand_init(snafc_adpt);

	return FAIL;
}

/**
 *  @brief      Clone snand_addr_t object.
 *
 *  @param[out] dest The destination object.
 *  @param[in]  src The source object.
 *
 *  @returns    Void.
 */
static inline void snand_addr_clone(snand_addr_t *dest, const snand_addr_t *src)
{
	memcpy(dest, src, sizeof(snand_addr_t));
}

/**
 *  @brief      Read flash data from specified flash address inside a flash page.
 *              Caller should not read across page boundary.
 *
 *  @param[in]  adpt The SNAFC adapter.
 *  @param[out] dest The address of data destination.
 *  @param[in]  addr The source flash address.
 *  @param[in]  size The size of data to read.
 *
 *  @returns    The result status code.
 */
s32 hal_snand_addr_cpy(hal_snafc_adaptor_t *adpt, void *dest, const snand_addr_t *addr, u32 size)
{
	s32 ret;

	if ((addr->col + size) > NAND_PAGE_LEN) {
		DBG_SNAND_ERR("Read cross page bound 0x%x + 0x%x\r\n", addr->col, size);
		return FAIL;
	}

	// cache result
	ret = hal_snand_page_read_w_cache(adpt, snand_memcpy_buf, NAND_PAGE_LEN, addr->page);
	if (ret != HAL_OK) {
		return ret;
	}

	memcpy(dest, snand_memcpy_buf + addr->col, size);
	return SUCCESS;
}

/**
 *  @brief      Move forward the current address of the NAND address object by an offset.
 *
 *  @param[in]  snand_addr The NAND address object.
 *  @param[in]  offset The offset to move in bytes.
 *
 *  @returns    Void.
 */
void hal_snand_addr_ofst(snand_addr_t *snand_addr, u32 offset)
{
	u32 page, col;
	page = snand_addr->page;
	col = snand_addr->col;
	u32 cur_page = snand_addr->page;
	u32 cur_col = snand_addr->col;

	DBG_SNAND_INFO("offset 0x%x:0x%x + 0x%x\r\n", page, col, offset);

	if (cur_col >= NAND_PAGE_LEN) {
		DBG_SNAND_WARN("Fix invalid flash col %u\r\n", cur_col);

		u32 new_col = NAND_PAGE_OFST(cur_col);
		offset += cur_col - new_col;
		cur_col = new_col;
	}

	cur_page += NAND_ADDR2PAGE(offset);
	cur_col += NAND_PAGE_OFST(offset);
	if (cur_col >= NAND_PAGE_LEN) {
		cur_col -= NAND_PAGE_LEN;
		cur_page += 1;
	}

	snand_addr->page = cur_page;
	snand_addr->col = cur_col;
}

/**
 *  @brief      Copy the NAND ctrl info and partition table from ROM stub
 *              NS domain will have to wait Secure domain copy them to a fixed location.
 *
 *  @returns    The result status code.
 */
s32 hal_snand_init_ctrl_info(void)
{
#ifdef CONFIG_BUILD_NONSECURE
	if (FALSE == hal_snand_layout_info_ns.inited) {
		// NS domain ctrl info should have been inited by S domain
		DBG_SNAND_ERR("snand ctrl info uninited\r\n");
		return FAIL;
	}

	// Copy entire ctrl info
	memcpy(&snand_ctrl_info, &hal_snand_layout_info_ns.ctrl_info, sizeof(snand_ctrl_info));
	// Copy entire partition table
	memcpy(&hal_snand_part_tbl, &hal_snand_layout_info_ns.part_tbl, sizeof(snand_partition_tbl_t));
#else

	// Copy entire ctrl info
	memcpy(&snand_ctrl_info, hal_snand_boot_stubs.ctrl_info, sizeof(snand_ctrl_info));
	// Copy entire partition table
	memcpy(&hal_snand_part_tbl, hal_snand_boot_stubs.part_tbl, sizeof(snand_partition_tbl_t));

#endif

	snand_layout_info_inited = TRUE;
	return SUCCESS;
}


/**
 *  @brief      Init the NAND partition adapter.
 *              All mapped physical blocks will be checked boundary.
 *
 *  @param[in]  part_adpt The NAND partition adapter.
 *  @param[in]  adpt The SNAFC adapter.
 *  @param[in]  entry The first partition record of the specified partition.
 *
 *  @returns    The result status code.
 */
s32 hal_snand_part_adpt_init(hal_snand_part_adpt_t *part_adpt, hal_snafc_adaptor_t *adpt, const snand_part_entry_t *entry)
{
	s32 ret;
	u32 chip_blk_cnt;

	part_adpt->adpt = adpt;
	DBG_SNAND_INFO("part init\r\n");

	if (NULL == entry) {
		return FAIL;
	}

	// Get total block count
	chip_blk_cnt = NAND_BLK_CNT;

	snand_vmap_t *vmap = &part_adpt->vmap;

	// Init virtual map
	const u32 map_size = entry->blk_cnt;
	vmap->map_size = map_size;
	vmap->cur_rec_idx = 0;
	snand_addr_clone(&vmap->vmap0_addr, &entry->vmap_addr);

	// Check all mapping block
	snand_addr_t cur_map_addr;
	snand_addr_clone(&cur_map_addr, &entry->vmap_addr);

	snand_vblk_idx_t *map_buf = vmap->map;

	u32 blk_id = 0;
	while (blk_id < map_size) {
		ret = hal_snand_addr_cpy(adpt, map_buf,
								 &cur_map_addr, sizeof(snand_vblk_idx_t) * SNAND_VMAP_MAX);
		if (ret != HAL_OK) {
			return _ERRNO_BOOT_SNAFC_MEMCPY_FAIL;
		}

		for (u32 i = 0; i < SNAND_VMAP_MAX; i++) {
			if (map_buf[i] >= chip_blk_cnt) {
				DBG_SNAND_ERR("vmap[%d] = %u > flash size\r\n",
							  blk_id, map_buf[i]);
				return _ERRNO_BOOT_NAND_BLK_OVERFLOW;
			}

			blk_id++;
			if (blk_id == map_size) {
				break;
			}
		}
		hal_snand_addr_ofst(&cur_map_addr, sizeof(snand_part_record_t));
	}

	// Load 1st vmap
	ret = hal_snand_addr_cpy(adpt, &vmap->map, &entry->vmap_addr, sizeof(vmap->map));
	if (ret != HAL_OK) {
		return ret;
	}

	return SUCCESS;
}

/**
 *  @brief      Convert logical block to physical block index.
 *              It will automatically load next record if out of boundary.
 *
 *              Limitation for default flash size:
 *              Virtual map size: 0x7FFFF
 *              Record group size: 0x2AA
 *
 *  @param[in]  adpt The SNAFC adapter.
 *  @param[in]  vmap The virtual map to lookup.
 *  @param[in]  vblk The logical block to convert.
 *
 *  @returns    The mapped physical block. Returns -1 if lookup failed.
 */
static s32 hal_snand_map_blk(hal_snafc_adaptor_t *adpt, snand_vmap_t *vmap, const snand_vblk_idx_t vblk)
{
	hal_status_t hal_ret;
	snand_vblk_idx_t ret;

	if (vblk >= vmap->map_size) {
		DBG_SNAND_ERR("Lookup vblk %x overflow map\r\n", vblk);
		return -1;
	}

	if (vmap->map_size <= SNAND_VMAP_MAX) {
		ret = vmap->map[vblk];

	} else if ((vblk / SNAND_VMAP_MAX) == vmap->cur_rec_idx) {
		ret = vmap->map[vblk % SNAND_VMAP_MAX];

	} else {
		// Get address of 1st virtual map
		snand_addr_t vmap_addr;
		snand_addr_clone(&vmap_addr, &vmap->vmap0_addr);
		u16 need_rec_idx = vblk / SNAND_VMAP_MAX;

		// Get address of new virtual map
		hal_snand_addr_ofst(&vmap_addr, need_rec_idx * sizeof(snand_part_record_t));

		// Load entire virtual map
		hal_ret = hal_snand_addr_cpy(adpt, &vmap->map, &vmap_addr, sizeof(vmap->map));
		if (hal_ret != HAL_OK) {
			DBG_SNAND_ERR("Load rec %x failed\r\n", need_rec_idx);
			return -1;
		}
		DBG_SNAND_INFO("Load part rec %x\r\n", need_rec_idx);
		vmap->cur_rec_idx = need_rec_idx;

		ret = vmap->map[vblk % SNAND_VMAP_MAX];
	}

	DBG_SNAND_INFO("vblk 0x%x -> pblk 0x%x\r\n", vblk, ret);
	return ret;
}

/**
 *  @brief      Convert partition offset to flash physical address (does not count spare area)
 *
 *  @param[in]  part_adpt The NAND partition adapter.
 *  @param[in]  part_ofst The offset from partition start to the desired address.
 *  @param[out] ret_addr The converted address.
 *
 *  @returns    The result status code.
 */
s32 hal_snand_ofst_2_addr(hal_snand_part_adpt_t *part_adpt, const u32 part_ofst, u32 *ret_addr)
{
	u32 cur_vblk, cur_page, cur_vpage;
	u16 cur_col = NAND_PAGE_OFST(part_ofst);
	s32 cur_blk;

	hal_snafc_adaptor_t *snafc_adpt = part_adpt->adpt;
	snand_vmap_t *vmap = &part_adpt->vmap;

	// Prevent over-map copy
	const u32 max_ofst = NAND_PAGE2ADDR(NAND_BLK2PAGE(part_adpt->vmap.map_size));
	if (max_ofst < part_ofst) {
		DBG_SNAND_ERR("Read flash block out of map\r\n");
		return _ERRNO_BOOT_SNAFC_MEMCPY_FAIL;
	}

	cur_vpage = NAND_ADDR2PAGE(part_ofst);

	// Get v-block
	cur_vblk = NAND_PAGE2BLK(cur_vpage);

	// Get p-block
	cur_blk = hal_snand_map_blk(snafc_adpt, vmap, cur_vblk);
	if (cur_blk < 0) {
		return _ERRNO_BOOT_SNAFC_MEMCPY_FAIL;
	}

	// Get p-page
	cur_page = NAND_BLK2PAGE(cur_blk) + NAND_BLK_OFST(cur_vpage);

	*ret_addr = NAND_PAGE2ADDR(cur_page) + cur_col;

	return SUCCESS;
}

/**
 *  @brief      Load data from NAND Flash partition.
 *              Prefix and postfix page data that is not page aligned will be
 *              loaded to tmp buffer first.
 *              Always read entire NAND flash page.
 *
 *  @param[in]  part_adpt The NAND partition adapter.
 *  @param[in]  dest The load destination.
 *  @param[in]  part_ofst The offset from partition start to the desired address.
 *  @param[in]  size The size to load in bytes
 *
 *  @returns    Void.
 */
s32 hal_snand_load_from_part(hal_snand_part_adpt_t *part_adpt, void *dest,
							 const u32 part_ofst, const u32 size)
{
	u32 size_left = size;
	s32 ret, cur_blk;
	u32 cur_vblk, cur_page, cur_vpage;
	u8 *cur_dst = (u8 *)dest;
	u16 cur_col = NAND_PAGE_OFST(part_ofst);

	DBG_SNAND_INFO("part 0x%x (%x) -> 0x%x\r\n", part_ofst, size, dest);

	hal_snafc_adaptor_t *snafc_adpt = part_adpt->adpt;
	snand_vmap_t *vmap = &part_adpt->vmap;

	// Prevent over-map copy
	const u32 max_ofst = NAND_PAGE2ADDR(NAND_BLK2PAGE(part_adpt->vmap.map_size));
	if (max_ofst < (part_ofst + size)) {
		DBG_SNAND_ERR("Read flash block out of map\r\n");
		return _ERRNO_BOOT_SNAFC_MEMCPY_FAIL;
	}

	cur_vpage = NAND_ADDR2PAGE(part_ofst);

	// Get v-block
	cur_vblk = NAND_PAGE2BLK(cur_vpage);

	// Get p-block
	cur_blk = hal_snand_map_blk(snafc_adpt, vmap, cur_vblk);
	if (cur_blk < 0) {
		return _ERRNO_BOOT_SNAFC_MEMCPY_FAIL;
	}

	// Get p-page
	cur_page = NAND_BLK2PAGE(cur_blk) + NAND_BLK_OFST(cur_vpage);

	// Handle 1st page when start reading from middle of page
	if (cur_col != 0) {
		u16 page_data_len = NAND_PAGE_LEN - cur_col;

		// cache result
		ret = hal_snand_page_read_w_cache(snafc_adpt, snand_memcpy_buf, NAND_PAGE_LEN, cur_page);
		if (SUCCESS != ret) {
			return _ERRNO_BOOT_SNAFC_MEMCPY_FAIL;
		}

		if (page_data_len <= size) {
			// Copy to cur_dst
			memcpy(cur_dst, snand_memcpy_buf + cur_col, page_data_len);

			cur_dst += page_data_len;
			cur_page += 1;
			size_left -= page_data_len;

			if (NAND_BLK_OFST(cur_page) == 0) {
				cur_vblk++;
			}

		} else {
			page_data_len = size;
			memcpy(cur_dst, snand_memcpy_buf + cur_col, page_data_len);

			cur_dst += page_data_len;
			size_left = 0;
			// end of memcpy
		}
	}

	while (size_left > 0) {
		// Check current page cross block bound
		if (NAND_BLK_OFST(cur_page) == 0) {
			cur_blk = hal_snand_map_blk(snafc_adpt, vmap, cur_vblk);
			if (cur_blk < 0) {
				return _ERRNO_BOOT_SNAFC_MEMCPY_FAIL;
			}
			cur_page = NAND_BLK2PAGE(cur_blk);
		}

		if (size_left >= NAND_PAGE_LEN) {
			// Handle rest data >= 1 page
			ret = hal_snand_page_read(snafc_adpt, cur_dst, NAND_PAGE_LEN, cur_page);
			if (SUCCESS != ret) {
				return _ERRNO_BOOT_SNAFC_MEMCPY_FAIL;
			}

			cur_dst += NAND_PAGE_LEN;
			size_left -= NAND_PAGE_LEN;

			cur_page += 1;
			if (NAND_BLK_OFST(cur_page) == 0) {
				cur_vblk++;
			}
		} else {
			// cache result
			// Handle rest data < 1 page
			ret = hal_snand_page_read_w_cache(snafc_adpt, snand_memcpy_buf, NAND_PAGE_LEN, cur_page);
			if (SUCCESS != ret) {
				return _ERRNO_BOOT_SNAFC_MEMCPY_FAIL;
			}

			memcpy(cur_dst, snand_memcpy_buf, size_left);
			size_left = 0;
		}
	}

	return SUCCESS;
}

/**
 *  @brief      Modify NAND flash clock division and latch delay with OTP setting.
 *
 *  @param[in]  adpt The SNAFC adapter.
 *
 *  @returns    The result status code.
 */
s32 hal_snand_otp_clk_sel(hal_snafc_adaptor_t *adpt)
{
	u8 clk_div, latch;
	u8 value_sel = SNAFC_SPEED_SEL_3;
	adpt->clkSel = value_sel;

	if (otpBootCfg9->bit.nand_clk_latch_ctrl_en == 0) {
		// Not enabled
		return FAIL;
	}

	// Get value from otp
	clk_div = otpBootCfg9->bit.nand_clk_sel;
	latch = otpBootCfg9->bit.nand_latch_sel;

	adpt->initVal[value_sel].reg.pipe_lat = latch;

	/*
	clk_div_mapping: (regiser bit == 3 freq is too close to 20 HMz)
	    otp -> register bit
	    0 -> 0 (62 MHz)
	    1 -> 1 (31 MHz)
	    2 -> 2 (20 HMz)
	    3 -> 4 (12 HMz)
	*/
	if (clk_div == 3) {
		clk_div = 4;
	}
	adpt->initVal[value_sel].reg.spi_clk_div = clk_div;
	return SUCCESS;
}

s32 hal_snand_dma_cont_read_en(hal_snafc_adaptor_t *pAdaptor, u8 en)
{
#ifndef SNWINBOND_CR_SET_CMDDATA
#define SNWINBOND_CR_SET_CMDDATA    (0xB0)
#endif
#ifndef SNWINBOND_CR_SET_OFFSET
#define SNWINBOND_CR_SET_OFFSET     (3)
#endif
#ifndef SNWINBOND_CR_SET_MASK
#define SNWINBOND_CR_SET_MASK       (1 << SNWINBOND_CR_SET_OFFSET)
#endif
#ifndef SNMXIC_CR_SET_CMDDATA
#define SNMXIC_CR_SET_CMDDATA       (0xB0)
#endif
#ifndef SNMXIC_CR_SET_OFFSET
#define SNMXIC_CR_SET_OFFSET        (2)
#endif
#ifndef SNMXIC_CR_SET_MASK
#define SNMXIC_CR_SET_MASK          (1 << SNMXIC_CR_SET_OFFSET)
#endif

	uint8_t retry, vdr_idx = (pAdaptor->cont_rd_vdr_idx);
	uint32_t tCmd, tRetVal, tData;

	switch (vdr_idx) {
	case SNAND_WINBOND_25N01GVZE1G_CONTRD:
		tCmd = SNWINBOND_CR_SET_CMDDATA;
		break;
	case SNAND_MXIC_MX35LF2GE4AD_CONTRD:
		tCmd = SNMXIC_CR_SET_CMDDATA;
		break;
	default:
		tCmd = 0xFFFFFFFF;
		break;
	}
	if (0xFFFFFFFF == tCmd) {
		return FAIL;
	}
	if (ENABLE == en) {
		// vndr switch-on cont_r mode
		for (retry = 0; retry < 3; retry++) {
			tRetVal = hal_snand_get_status(pAdaptor, tCmd);
			if (SNAND_WINBOND_25N01GVZE1G_CONTRD == vdr_idx) {
				if (0 == ((tRetVal & SNWINBOND_CR_SET_MASK) >> SNWINBOND_CR_SET_OFFSET)) {
					break;
				}
				tData = tRetVal & ~(SNWINBOND_CR_SET_MASK);      // set cont_r reg
			} else if (SNAND_MXIC_MX35LF2GE4AD_CONTRD == vdr_idx) {
				if (1 == ((tRetVal & SNMXIC_CR_SET_MASK) >> SNMXIC_CR_SET_OFFSET)) {
					break;
				}
				tData = tRetVal | (SNMXIC_CR_SET_MASK | BIT0);
			}
			hal_snand_set_status(pAdaptor, tCmd, tData);
		}
		tRetVal = hal_snand_get_status(pAdaptor, tCmd);
		if (SNAND_WINBOND_25N01GVZE1G_CONTRD == vdr_idx) {
			if (0 == ((tRetVal & SNWINBOND_CR_SET_MASK) >> SNWINBOND_CR_SET_OFFSET)) {
				return SUCCESS;
			} else {
				return FAIL;
			}
		} else if (SNAND_MXIC_MX35LF2GE4AD_CONTRD == vdr_idx) {
			if (1 == ((tRetVal & SNMXIC_CR_SET_MASK) >> SNMXIC_CR_SET_OFFSET)) {
				return SUCCESS;
			} else {
				return FAIL;
			}
		}
	} else {
		// vndr switch-off cont_r mode
		for (retry = 0; retry < 3; retry++) {
			tRetVal = hal_snand_get_status(pAdaptor, tCmd);
			if (SNAND_WINBOND_25N01GVZE1G_CONTRD == vdr_idx) {
				if (1 == ((tRetVal & SNWINBOND_CR_SET_MASK) >> SNWINBOND_CR_SET_OFFSET)) {
					break;
				}
				tData = tRetVal | (SNWINBOND_CR_SET_MASK);      // set cont_r reg
			} else if (SNAND_MXIC_MX35LF2GE4AD_CONTRD == vdr_idx) {
				if (0 == ((tRetVal & SNMXIC_CR_SET_MASK) >> SNMXIC_CR_SET_OFFSET)) {
					break;
				}
				tData = tRetVal & ~(SNMXIC_CR_SET_MASK);
			}
			hal_snand_set_status(pAdaptor, tCmd, tData);
		}
		tRetVal = hal_snand_get_status(pAdaptor, tCmd);
		if (SNAND_WINBOND_25N01GVZE1G_CONTRD == vdr_idx) {
			if (1 == ((tRetVal & SNWINBOND_CR_SET_MASK) >> SNWINBOND_CR_SET_OFFSET)) {
				return SUCCESS;
			} else {
				return FAIL;
			}
		} else if (SNAND_MXIC_MX35LF2GE4AD_CONTRD == vdr_idx) {
			if (0 == ((tRetVal & SNMXIC_CR_SET_MASK) >> SNMXIC_CR_SET_OFFSET)) {
				return SUCCESS;
			} else {
				return FAIL;
			}
		}
	}
	return SUCCESS;
}

/**
 *  @brief      Vendor-specific READ mode (Winbond)(Continue Page Read)
 *
 *  @param[in]  adpt The SNAFC adapter.
 *  @param[in]  memAddr Buffer address for reading data.
 *  @param[in]  dataLens Data length want to read (Unit: byte)
 *  @param[in]  blkPageAddr Page index of S-NAND flash
 *
 *  @returns    The result status code.
 */
uint32_t
hal_snand_dma_cont_read(
	hal_snafc_adaptor_t *pAdaptor,
	void *memAddr,
	uint32_t dataLens,
	uint32_t blkPageAddr
)
{
	uint8_t *pTmp;
	uint32_t remainSz;
	uint8_t vdr_idx = (pAdaptor->cont_rd_vdr_idx);

#ifndef SNAFC_S_BASE
#define SNAFC_S_BASE                0x5005D000UL
#endif

#ifndef SNAFC_SR
#define SNAFC_SR	(0x040) /*!<  SPI NAND Flash Status Register (SNAFC_SR) register,			Address offset: 0x040 */
#endif
#ifndef SNAFC_CCR
#define SNAFC_CCR	(0x004) /*!<  SPI NAND Flash CS Control Register (SNAFC_CCR) register,  Address offset: 0x004 */
#define SPI_CS_NN_ENABLE (0x00000000)
#define SPI_CS_NN_DISABLE (0x00000001)
#endif
#ifndef SNAFC_WCMR
#define SNAFC_WCMR	(0x008)	/*!<  SPI NAND Flash Write Command Register (SNAFC_WCMR) register,  Address offset: 0x008 */
#endif
#ifndef SNAFC_WDR
#define SNAFC_WDR	(0x014)	/*!<  SPI NAND Flash Write Data Register (SNAFC_WDR) register,  Address offset: 0x014 */
#endif
#ifndef SNAFC_RCMR
#define SNAFC_RCMR	(0x00C)	/*!<  SPI NAND Flash Read Command Register (SNAFC_RCMR) register,  Address offset: 0x00C */
#endif
#ifndef SNAFC_RDR
#define SNAFC_RDR	(0x014)	/*!<  SPI NAND Flash Read Data Register (SNAFRDR) register,  Address offset: 0x010 */
#endif
#ifndef SNAFC_DRSAR
#define SNAFC_DRSAR	(0x01C)	/*!<  SPI NAND Flash DMA RAM Start Address Register (SNAFCDRSAR) register,  Address offset: 0x01C */
#endif
#ifndef SNAFC_DLR
#define SNAFC_DLR	(0x024)	/*!<  SPI NAND Flash DMA Length Register (SNAFDLR) register,  Address offset: 0x024 */
#endif
#ifndef SNAFC_DTR
#define SNAFC_DTR	(0x018)	/*!<  SPI NAND Flash DMA Trigger Register (SNAFDTR) register,  Address offset: 0x018 */
#define SNAFC_DTR_DMA_READ (0x00000000)
#define SNAFC_DTR_DMA_WRITE (0x00000001)
#endif

	/* ========================================= */
	/* OpCode 13h (PageDataRead) + 8 dummy + 16 bit PageAddr[15:0] */
	/* ========================================= */

	/* Wait CS# as high (idle) */
	while (!(HAL_READ32(SNAFC_S_BASE, SNAFC_SR) & SNAFC_BIT_CS));


	/* CS# enable */
	HAL_WRITE32(SNAFC_S_BASE, SNAFC_CCR, SPI_CS_NN_ENABLE);
	/**
		1. Set spi write data length = 4 byte (CMD in 1-bit mode)(Addr in 1-bit mode)
		2. According to "PageDataRead" cmd waveform, wdata = (cmd: 9F; dummy: 8 ticks).
			After write command into (SNAFC_WDR), SNAFC trigger the “PIO write” command to SPI bus.
		3. Polling SNAFC_SR [3] NFCOS as 0 for sending CMD complete. (1 means BUSY; 0 means IDLE)
	*/
	HAL_WRITE32(SNAFC_S_BASE, SNAFC_WCMR, 0x00000003); /* [29:28](I/O mode,0~2); [1:0](dataLen, n-1) */
	HAL_WRITE32(SNAFC_S_BASE, SNAFC_WDR, 0x13000000 | (blkPageAddr & 0xFFFF)); //Trigger PIO Write
	while (HAL_READ32(SNAFC_S_BASE, SNAFC_SR) & SNAFC_BIT_NFCOS);
	/* CS# disable */
	HAL_WRITE32(SNAFC_S_BASE, SNAFC_CCR, SPI_CS_NN_DISABLE);

	/* ========================================= */
	/* OpCode 0Fh (GetFeature for SR-3[0]) for waiting flash device READY */
	/* ========================================= */
	hal_snand_wait_ready(pAdaptor);

	/* ========================================= */
	/* According to (cmdWidth-addrWidth-dataWidth) configuration, generate waveform on SPI bus */
	/* ----------------------------------------- */
	/* OpCode 03h (Read(1-1-1)) + 16 bit ColumnAddr[15:0] + 8 dummy (BUF=1 read) */
	/* OpCode 6Bh (Read(1-1-4)) + 16 bit ColumnAddr[15:0] + 8 dummy (BUF=1 read) */
	/* OpCode 6Bh (Read(1-1-4)) + 32 dummy (BUF=0 read) */
	/* ========================================= */

	/* Wait CS# idle */
	while (!(HAL_READ32(SNAFC_S_BASE, SNAFC_SR) & SNAFC_BIT_CS));

	/* CS# enable */
	HAL_WRITE32(SNAFC_S_BASE, SNAFC_CCR, SPI_CS_NN_ENABLE);

	/* ----------------------------------------- */
	/* w data = 6B xx xx xx xx                   */
	/* ----------------------------------------- */
	/* Set write data length =  4byte; Data: 6B  */
	HAL_WRITE32(SNAFC_S_BASE, SNAFC_WCMR, 0x00000003); /* [29:28](I/O mode,0~2); [1:0](dataLen, n-1) */
	HAL_WRITE32(SNAFC_S_BASE, SNAFC_WDR, 0x6B000000);
	while (HAL_READ32(SNAFC_S_BASE, SNAFC_SR) & SNAFC_BIT_NFCOS);
	if (SNAND_WINBOND_25N01GVZE1G_CONTRD == vdr_idx) {
		// 3 dummy for 4-bit read for MX35LF2GE4AD
		// 4 dummy for W25N01GV
		/* Set write data length =  1byte; Data: 00  */
		HAL_WRITE32(SNAFC_S_BASE, SNAFC_WCMR, 0x00000000); /* [29:28](I/O mode,0~2); [1:0](dataLen, n-1) */
		HAL_WRITE32(SNAFC_S_BASE, SNAFC_WDR, 0x00000000);
		while (HAL_READ32(SNAFC_S_BASE, SNAFC_SR) & SNAFC_BIT_NFCOS);
	}

	/* ----------------------------------------- */
	/* Using DMA to move data                    */
	/* ----------------------------------------- */
	/*++ Due to MAX DMA length is 128KB -1 bytes. It cannot DMA whole block size (128KB) in single DMA transfer. */

	// #define TEST_MAX_DMA_LENGTH (64*1024)	// 0x1_0000 // FAIL. PLEASE DO NOT USE 64KB setting.
#define TEST_MAX_DMA_LENGTH (32*1024)		// 0x0_8000 // OK
	// #define TEST_MAX_DMA_LENGTH (16*1024)	// 0x0_4000 // OK
	remainSz = dataLens;
	pTmp = memAddr;
	while (remainSz >= (TEST_MAX_DMA_LENGTH)) {
		/* Set dma address = memAddr */
		HAL_WRITE32(SNAFC_S_BASE, SNAFC_DRSAR, pTmp);
		/* Set dma length = dataLens */ /* [29:28] = spi busWidth, 4-bit mode */
		dataLens = (TEST_MAX_DMA_LENGTH);
		HAL_WRITE32(SNAFC_S_BASE, SNAFC_DLR, ((SNAFC_QIO_WIDTH << 28) | dataLens)); /* [29:28](I/O mode,0~2); [16:0](dataLen, N (not N-1)) */
		/* Start dma transfer: [0]=0, READ from S-NAND flash; [0]=1, WRITE to S-NAND flash */
		HAL_WRITE32(SNAFC_S_BASE, SNAFC_DTR, SNAFC_DTR_DMA_READ); /* Trigger DMA write or read */ /* [0](DMARWE) 1 for WRITE; 0 for READ. */
		/* Polling for SNAFC DMA Complete */
		while (HAL_READ32(SNAFC_S_BASE, SNAFC_SR) & (SNAFC_BIT_NFDRS));
		pTmp += (dataLens);
		remainSz -= (dataLens);
		while (HAL_READ32(SNAFC_S_BASE, SNAFC_SR) & SNAFC_BIT_NFCOS);
	}
	if (remainSz) {
		/* Set dma address = memAddr */
		HAL_WRITE32(SNAFC_S_BASE, SNAFC_DRSAR, pTmp);
		/* Set dma length = dataLens */ /* [29:28] = spi busWidth, 4-bit mode */
		HAL_WRITE32(SNAFC_S_BASE, SNAFC_DLR, ((SNAFC_QIO_WIDTH << 28) | remainSz)); /* [29:28](I/O mode,0~2); [16:0](dataLen, N (not N-1)) */
		/* Start dma transfer: [0]=0, READ from S-NAND flash; [0]=1, WRITE to S-NAND flash */
		HAL_WRITE32(SNAFC_S_BASE, SNAFC_DTR, SNAFC_DTR_DMA_READ); /* Trigger DMA write or read */ /* [0](DMARWE) 1 for WRITE; 0 for READ. */
		/* Polling for SNAFC DMA Complete */
		while (HAL_READ32(SNAFC_S_BASE, SNAFC_SR) & (SNAFC_BIT_NFDRS));

		while (HAL_READ32(SNAFC_S_BASE, SNAFC_SR) & SNAFC_BIT_NFCOS);
	}
	/*-- Due to MAX DMA length is 128KB -1 bytes. It cannot DMA whole block size (128KB) in single DMA transfer. */

	/* CS# disable */
	HAL_WRITE32(SNAFC_S_BASE, SNAFC_CCR, SPI_CS_NN_DISABLE);
	/* ========================================= */

	return SUCCESS;

} /* End of hal_snand_dma_cont_read */

s32 hal_snand_get_addr_info(hal_snand_part_adpt_t *part_adpt, const u32 part_ofst, snand_boot_addr_info_t *p_nandb_addr_info)
{
	hal_snafc_adaptor_t *snafc_adpt = part_adpt->adpt;
	snand_vmap_t *vmap = &part_adpt->vmap;
	int ret = SUCCESS;

	// Prevent over-map copy
	const u32 max_ofst = NAND_PAGE2ADDR(NAND_BLK2PAGE(part_adpt->vmap.map_size));
	if (max_ofst < part_ofst) {
		DBG_SNAND_ERR("Read flash block out of map\r\n");
		return _ERRNO_BOOT_SNAFC_MEMCPY_FAIL;
	}

	if (NULL == p_nandb_addr_info) {
		ret = _ERRNO_BOOT_SNAFC_INIT_FAIL;
		return ret;
	} else {
		p_nandb_addr_info->cur_col   = NAND_PAGE_OFST(part_ofst);
		p_nandb_addr_info->cur_vpage = NAND_ADDR2PAGE(part_ofst);

		// Get v-block
		p_nandb_addr_info->cur_vblk  = NAND_PAGE2BLK(p_nandb_addr_info->cur_vpage);

		// Get p-block
		p_nandb_addr_info->cur_blk   = hal_snand_map_blk(snafc_adpt, vmap, p_nandb_addr_info->cur_vblk);
		if (p_nandb_addr_info->cur_blk < 0) {
			return _ERRNO_BOOT_SNAFC_MEMCPY_FAIL;
		}

		// Get p-page
		p_nandb_addr_info->cur_page  = NAND_BLK2PAGE(p_nandb_addr_info->cur_blk) + NAND_BLK_OFST(p_nandb_addr_info->cur_vpage);
	}
	return ret;
}

s32 hal_snand_cont_read_chk(hal_snand_part_adpt_t *part_adpt, const u32 part_ofst, const u32 size)
{
	hal_snafc_adaptor_t *snafc_adpt = part_adpt->adpt;
	snand_boot_addr_info_t nandb_addr_info;
	u32 cur_page, tDevId;
	u16 cur_col;
	u32 size_left = size;
	s32 ret;

	// check support nand cont_r of vendor
	tDevId = hal_snand_read_id(snafc_adpt);
	if ((SNAND_WINBOND_25N01GVZE1G_TYPEID == tDevId) || (SNAND_MXIC_MX35LF2GE4AD_TYPEID == tDevId)) {
		switch (tDevId) {
		case SNAND_WINBOND_25N01GVZE1G_TYPEID:
			snafc_adpt->cont_rd_vdr_idx = SNAND_WINBOND_25N01GVZE1G_CONTRD;
			break;
		case SNAND_MXIC_MX35LF2GE4AD_TYPEID:
			snafc_adpt->cont_rd_vdr_idx = SNAND_MXIC_MX35LF2GE4AD_CONTRD;
			break;
		default:
			snafc_adpt->cont_rd_vdr_idx = SNAND_ERR_NO_SUPPORT_CONTRD;
			break;
		}
	} else {
		snafc_adpt->cont_rd_vdr_idx = SNAND_ERR_NO_SUPPORT_CONTRD;
	}
	if (SNAND_ERR_NO_SUPPORT_CONTRD == (snafc_adpt->cont_rd_vdr_idx)) {
		return DISABLE;
	}

	ret = hal_snand_get_addr_info(part_adpt, part_ofst, &nandb_addr_info);
	if (ret != SUCCESS) {
		return DISABLE;
	} else {
		cur_col   = nandb_addr_info.cur_col;
		cur_page  = nandb_addr_info.cur_page;
	}
	if ((cur_col == 0) && (NAND_BLK_OFST(cur_page) == 0)) {
		if (NAND_FLSH_BLK_NUM(size_left)) {
			return ENABLE;
		} else {
			return DISABLE;
		}
	} else {
		if (NAND_FLSH_BLK_NUM(size_left)) {
			// handle head
			u32 page_num = (NAND_PAGE_PER_BLK - (NAND_BLK_OFST(cur_page) + 1));
			size_left -= (page_num * NAND_PAGE_LEN) + (NAND_PAGE_LEN - cur_col);
			// handle block aligned
			if (NAND_FLSH_BLK_NUM(size_left)) {
				return ENABLE;
			} else {
				return DISABLE;
			}
		} else {
			return DISABLE;
		}
	}
}

s32 hal_snand_cont_read_hdl_core(hal_snand_part_adpt_t *part_adpt, void *dest, const u32 part_ofst, const u32 size)
{
	snand_boot_addr_info_t nandb_addr_info;
	hal_snafc_adaptor_t *snafc_adpt = part_adpt->adpt;
	snand_vmap_t *vmap = &part_adpt->vmap;
	u32 left_part_ofst = part_ofst;
	u32 cur_vblk, cur_page;
	s32 cur_blk;
	u32 size_left = size;
	u8 *cur_dst = (u8 *)dest;
	u32 i;
	int ret = SUCCESS;

	// handle block aligned
	if (NAND_FLSH_BLK_NUM(size_left)) {
		u32 blk_r_total = NAND_FLSH_BLK_NUM(size_left);
		ret = hal_snand_get_addr_info(part_adpt, left_part_ofst, &nandb_addr_info);
		if (ret != SUCCESS) {
			return _ERRNO_BOOT_SNAFC_INIT_FAIL;
		} else {
			cur_page  = nandb_addr_info.cur_page;
			cur_vblk  = nandb_addr_info.cur_vblk;
			cur_blk   = nandb_addr_info.cur_blk;
		}

		ret = hal_snand_dma_cont_read_en(part_adpt->adpt, ENABLE);
		if (ret != SUCCESS) {
			DBG_SNAND_WARN("Non-support valid NAND cont-rd setting!!!\r\n");
			// consider non-block aligned handle
		} else {
			for (i = blk_r_total; i > 0; i--) {
				dcache_clean_invalidate_by_addr((void *)cur_dst, NAND_BLK_LEN);
				ret = hal_snand_dma_cont_read(part_adpt->adpt, cur_dst, NAND_BLK_LEN, cur_page);
				dcache_invalidate_by_addr((void *)cur_dst, NAND_BLK_LEN);
				if (ret != SUCCESS) {
					ret = hal_snand_dma_cont_read_en(part_adpt->adpt, DISABLE);
					if (ret != SUCCESS) {
						DBG_SNAND_ERR("Switch NAND normal page read fail!!!\r\n");
						return _ERRNO_BOOT_NAND_INVALID_CTRL;
					}
					ret = _ERRNO_BOOT_SNAFC_MEMCPY_FAIL;
					return ret;
				}
				left_part_ofst += NAND_BLK_LEN;
				cur_dst        += NAND_BLK_LEN;
				size_left      -= NAND_BLK_LEN;
				cur_vblk       += 1;
				cur_blk = hal_snand_map_blk(snafc_adpt, vmap, cur_vblk);
				if (cur_blk < 0) {
					return _ERRNO_BOOT_SNAFC_MEMCPY_FAIL;
				}
				cur_page = NAND_BLK2PAGE(cur_blk);
			}
			ret = hal_snand_dma_cont_read_en(part_adpt->adpt, DISABLE);
			if (ret != SUCCESS) {
				DBG_SNAND_ERR("Switch NAND normal page read fail!!!\r\n");
				return _ERRNO_BOOT_NAND_INVALID_CTRL;
			}
		}
	}

	// handle tail or non-block aligned
	if (size_left > 0) {
		ret = hal_snand_load_from_part(part_adpt, (u8 *)cur_dst, left_part_ofst, size_left);
	}
	return ret;
}

s32 hal_snand_cont_read_hdl(hal_snand_part_adpt_t *part_adpt, void *dest, const u32 part_ofst, const u32 size)
{
	snand_boot_addr_info_t nandb_addr_info;
	u32 cur_page;
	u16 cur_col;
	int ret = SUCCESS;
	u32 size_left = size;
	u8 *cur_dst = (u8 *)dest;

	// Prevent over-map copy
	const u32 max_ofst = NAND_PAGE2ADDR(NAND_BLK2PAGE(part_adpt->vmap.map_size));
	if (max_ofst < part_ofst) {
		DBG_SNAND_ERR("Read flash block out of map\r\n");
		return _ERRNO_BOOT_SNAFC_MEMCPY_FAIL;
	}

	ret = hal_snand_get_addr_info(part_adpt, part_ofst, &nandb_addr_info);
	if (ret != SUCCESS) {
		return _ERRNO_BOOT_SNAFC_INIT_FAIL;
	} else {
		cur_col   = nandb_addr_info.cur_col;
		cur_page  = nandb_addr_info.cur_page;
	}

	if ((cur_col == 0) && (NAND_BLK_OFST(cur_page) == 0)) {
		ret = hal_snand_cont_read_hdl_core(part_adpt, (u8 *)cur_dst, part_ofst, size_left);
	} else {
		if (NAND_FLSH_BLK_NUM(size_left)) {
			// handle head
			u32 page_num = (NAND_PAGE_PER_BLK - (NAND_BLK_OFST(cur_page) + 1));
			u32 total_size_left = size_left;
			u32 left_part_ofst;
			size_left = (page_num * NAND_PAGE_LEN) + (NAND_PAGE_LEN - cur_col);
			ret = hal_snand_load_from_part(part_adpt, (u8 *)dest, part_ofst, size_left);
			if (ret != SUCCESS) {
				return _ERRNO_BOOT_SNAFC_MEMCPY_FAIL;
			} else {
				left_part_ofst  = (part_ofst + size_left);
				cur_dst         += size_left;
				total_size_left -= size_left;
				size_left       = total_size_left;
				ret = hal_snand_cont_read_hdl_core(part_adpt, (u8 *)cur_dst, left_part_ofst, size_left);
			}
		} else {
			// non-block aligned handle(normally not execute this case)
			if (size_left > 0) {
				ret = hal_snand_load_from_part(part_adpt, (u8 *)cur_dst, part_ofst, size_left);
			}
		}
	}
	return ret;
}
/** *@} */ /* End of group hal_snand_ram_func */

/** *@} */ /* End of group hal_snand */

