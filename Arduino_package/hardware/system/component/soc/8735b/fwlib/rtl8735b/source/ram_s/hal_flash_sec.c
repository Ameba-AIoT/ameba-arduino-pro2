/**************************************************************************//**
 * @file     hal_flash_sec.c
 * @brief    Implement flash security IP (SEC) RAM code functions.
 *
 * @version  V1.00
 * @date     2021-07-13
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
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

#include "cmsis.h"
#include "hal_flash_sec.h"

// TODO add doxygen
/**
  \brief todo
*/

//#define GET_FUNC_CHECK
#ifdef GET_FUNC_CHECK
#include "assert.h"
#endif

hal_flash_sec_adapter_t hal_sec_adtr;

extern const hal_flash_sec_func_stubs_t hal_flash_sec_stubs;
#if IS_AFTER_CUT_A(CONFIG_CHIP_VER)
extern const hal_flash_sec_extend_func_stubs_t hal_flash_sec_ext_stubs;
#endif

hal_flash_sec_status_t _flash_sec_status;

static hal_status_t check_rom_error(void)
{
	hal_flash_sec_get_status(&_flash_sec_status);

	if (1 == _flash_sec_status.remap_region_error) {
		return HAL_ERR_UNKNOWN;
	} else if (1 == _flash_sec_status.remap_addr_error) {
		return HAL_ERR_UNKNOWN;
	} else if (1 == _flash_sec_status.intr_err_apb) {
		return HAL_ERR_UNKNOWN;
	} else if (1 == _flash_sec_status.intr_err_tag) {
		return HAL_ERR_UNKNOWN;
	} else if (1 == _flash_sec_status.intr_err_resp) {
		return HAL_ERR_UNKNOWN;
	} else if (1 == _flash_sec_status.intr_err_init) {
		return HAL_ERR_UNKNOWN;
	}
	return HAL_OK;
}

static hal_status_t check_key_init(void)
{
	hal_flash_sec_get_status(&_flash_sec_status);
	if (1 != _flash_sec_status.key_init_done) {
		return HAL_ERR_HW;
	}
	return HAL_OK;
}

hal_status_t hal_flash_sec_init(hal_flash_sec_adapter_t *adtr, u8 key_sel)
{
	u32 reg_val = 0;
	reg_val |= SYSON_S_BIT_FLASH_SEC_KEY_RDY_EN;
	reg_val |= (key_sel << SYSON_S_SHIFT_SCE_KEY_SEL) & SYSON_S_MASK_SCE_KEY_SEL;
	SYSON_S->SYSON_S_REG_SYS_SEC_CTRL = reg_val;
	return HAL_OK;
}

void hal_flash_sec_get_status(hal_flash_sec_status_t *status)
{
	hal_flash_sec_stubs.hal_flash_sec_get_status(status);
}

void hal_flash_sec_get_cid(hal_flash_sec_cid_t *cid)
{
	hal_flash_sec_stubs.hal_flash_sec_get_cid(cid);
}

u32 hal_flash_sec_get_err_addr(void)
{
	return hal_flash_sec_stubs.hal_flash_sec_get_err_addr();
}

hal_status_t hal_flash_sec_aes_enable(void)
{
	hal_status_t ret;
	hal_flash_sec_stubs.hal_flash_sec_aes_enable();
	ret = check_key_init();
	if (HAL_OK != ret) {
		DBG_FLASH_SEC_ERR("AES enable failed, key_init fail\r\n");
		return ret;
	}
	ret = check_rom_error();
	if (HAL_OK != ret) {
		DBG_FLASH_SEC_ERR("AES enable failed, check error register\r\n");
		return ret;
	}
	return HAL_OK;
}

void hal_flash_sec_aes_disable(void)
{
	hal_flash_sec_stubs.hal_flash_sec_aes_disable();
}

void hal_flash_sec_clr_intr(void)
{
	hal_flash_sec_stubs.hal_flash_sec_clr_intr();
}

hal_status_t hal_flash_sec_set_ctrl(hal_flash_sec_adapter_t *adtr)
{
	// TODO check arg
	//hal_status_t ret;
	hal_status_t ret;
	ret = hal_flash_sec_stubs.hal_flash_sec_set_ctrl(adtr);
	if (HAL_OK == ret) {
		return check_rom_error();
	}
	return ret;
}

void hal_flash_sec_gcm_key_init(void)
{
	hal_flash_sec_stubs.hal_flash_sec_gcm_key_init();
	// Waiting for key ready
	// TODO
}

void hal_flash_sec_dec_key_init(void)
{
	hal_flash_sec_stubs.hal_flash_sec_dec_key_init();
	// Waiting for key ready
	// TODO
}

void hal_flash_sec_clean_cache(void)
{
	hal_flash_sec_stubs.hal_flash_sec_clean_cache();
}

void hal_flash_sec_set_tag_base(u32 tag_base_addr)
{
	hal_flash_sec_stubs.hal_flash_sec_set_tag_base(tag_base_addr);

#ifdef GET_FUNC_CHECK
	u32 _tag_base;
	hal_flash_sec_get_tag_base(&_tag_base);
	if (_tag_base != tag_base_addr) {
		DBG_FLASH_SEC_ERR("Set tag check failed : %x %x\r\n", tag_base_addr, _tag_base);
	}
	//assert(_tag_base != tag_base_addr && "Get Tag check failed");
#endif
}

static u8 check_addr_region(u32 base, u32 size)
{
	if ((base & PAGE_OFFSET_MASK) || (base < FLASH_ACCESS_BASE)) {
		return 1;
	}

	if (size & PAGE_OFFSET_MASK) {
		return 1;
	}
	u32 end = base + size;
	if (end > FLASH_MAX_END) {
		return 1;
	}
	return 0;
}

hal_status_t hal_flash_sec_enable_rmp_region(uint8_t rmp_region_sel, uint32_t va_base, uint32_t pa_base, uint32_t region_size)
{
	hal_status_t ret;
	hal_flash_sec_adapter_t *adtr = &hal_sec_adtr;
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	adtr->remap_region_sel = rmp_region_sel;
	adtr->va_base = va_base;
	adtr->va_base = pa_base;
	adtr->remap_region_size = region_size;
	ret = hal_flash_sec_enable_remap_region(adtr);
#else
	ret = hal_flash_sec_ext_stubs.hal_flash_sec_enable_remap_region(adtr, rmp_region_sel, va_base, pa_base, region_size);
#endif
	return ret;
}

uint32_t hal_flash_sec_set_word_from_byte_bigen(const unsigned char *s_value)
{
	volatile uint32_t val = 0x0;
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	(val) = (((uint32_t)(s_value)[0] << 24)
			 | ((uint32_t)(s_value)[1] << 16)
			 | ((uint32_t)(s_value)[2] <<  8)
			 | ((uint32_t)(s_value)[3]));
#else
	val = hal_flash_sec_ext_stubs.hal_flash_sec_set_word_from_byte_bigen(s_value);
#endif
	return val;
}

hal_status_t hal_flash_sec_calculate_tag_base(uint32_t cache_line_size, uint32_t tag_size,
		uint32_t flash_addr, uint32_t region_size, uint32_t tag_region_addr,
		uint32_t *tag_base, uint32_t *tag_region_size)
{
	hal_status_t ret = HAL_OK;
	uint32_t ratio = 0x0, tag_offset = 0x0;

	if (cache_line_size % tag_size != 0) {
		dbg_printf("calculate_tag_base arg error: cache %% tag != 0");
		ret = HAL_ERR_PARA;
		return ret;
	}
	ratio = cache_line_size / tag_size;
	if (NULL != tag_region_size) {
		*tag_region_size = region_size / ratio;
	}

	tag_offset = (flash_addr & FLASH_OFFSET_MASK) / ratio;
	if (NULL != tag_base) {
		*tag_base = tag_region_addr - tag_offset;
	}
	return ret;
}


hal_status_t hal_flash_sec_default_calculate_tag_base(uint32_t flash_addr, uint32_t region_size,
		uint32_t tag_region_addr, uint32_t *tag_base,
		uint32_t *tag_region_size)
{
	hal_status_t ret = HAL_OK;
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	ret = hal_flash_sec_calculate_tag_base(FLASH_SEC_CACHE_32, FLASH_SEC_TAG_4, flash_addr, region_size,
										   tag_region_addr, tag_base, tag_region_size);
#else
	ret = hal_flash_sec_ext_stubs.hal_flash_sec_calculate_tag_base(FLASH_SEC_CACHE_32, FLASH_SEC_TAG_4, flash_addr, region_size,
			tag_region_addr, tag_base, tag_region_size);
#endif
	return ret;
}

hal_status_t hal_flash_sec_decrypt_init(hal_flash_sec_adapter_t *adtr, const uint8_t key_sel, uint32_t key_size,
										uint32_t cache_line_size, uint32_t tag_size)
{
	hal_status_t ret = HAL_OK;
	if (adtr == NULL) {
		ret = HAL_ERR_MEM;
		return ret;
	}

	adtr->key_size = key_size;
	adtr->tag_size = tag_size;
#if IS_AFTER_CUT_A(CONFIG_CHIP_VER)
	adtr->cache_line_size = cache_line_size;
#endif

	ret = hal_flash_sec_set_ctrl(adtr);
	if (ret != HAL_OK) {
		return ret;
	}

	ret = hal_flash_sec_init(adtr, key_sel);
	if (ret != HAL_OK) {
		return ret;
	}
	return ret;
}


hal_status_t hal_flash_sec_default_decrypt_init(const uint8_t key_sel)
{
	hal_status_t ret = HAL_OK;
	hal_flash_sec_adapter_t *adtr = &hal_sec_adtr;

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	ret = hal_flash_sec_decrypt_init(adtr, key_sel, FLASH_SEC_KEY_256, FLASH_SEC_CACHE_32, FLASH_SEC_TAG_4);
#else
	ret = hal_flash_sec_ext_stubs.hal_flash_sec_decrypt_init(adtr, key_sel, FLASH_SEC_KEY_256, FLASH_SEC_CACHE_32, FLASH_SEC_TAG_4);
#endif
	return ret;
}

hal_status_t hal_flash_sec_decrypt_region_init(const uint32_t iv_low_ptn, const uint32_t iv_high_ptn, uint8_t dec_region_sel)
{
	hal_status_t ret = HAL_OK;
	hal_flash_sec_adapter_t *adtr = &hal_sec_adtr;
	if (dec_region_sel >= FLASH_SEC_DECRYPT_REGION_MAX) {
		ret = HAL_ERR_PARA;
		return ret;
	}

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	adtr->iv_low  = iv_low_ptn;
	adtr->iv_high = iv_high_ptn;
	adtr->iv_sel  = dec_region_sel;
	ret = hal_flash_sec_set_iv(adtr);
#else
	ret = hal_flash_sec_ext_stubs.hal_flash_sec_decrypt_region_init(adtr, iv_low_ptn, iv_high_ptn, dec_region_sel);
#endif
	return ret;
}

hal_status_t hal_flash_sec_decrypt_region_enable(const uint8_t cipher_sel, uint32_t dec_base, uint32_t dec_size, uint32_t tag_base)
{
	hal_status_t ret = HAL_OK;
	hal_flash_sec_adapter_t *adtr = &hal_sec_adtr;

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	uint8_t dec_region_sel = 0x0;
	dec_region_sel = (adtr->iv_sel);
	// check options
	if (dec_region_sel >= FLASH_SEC_DECRYPT_REGION_MAX) {
		ret = HAL_ERR_PARA;
		return ret;
	}
	if (check_addr_region(dec_base, dec_size)) {
		return HAL_ERR_PARA;
	}
	if (adtr->cipher >= FLASH_SEC_CIPHER_MAX) {
		return HAL_ERR_PARA;
	}

	adtr->decrypt_region_sel = dec_region_sel;
	adtr->decrypt_region_enable = ENABLE;
	adtr->cipher   = cipher_sel;
	adtr->va_base = dec_base;
	adtr->decrypt_region_size = dec_size;
	ret = hal_flash_sec_decrypt_region(adtr);
	if (ret != HAL_OK) {
		return ret;
	}

	if (FLASH_SEC_CIPHER_GCM == cipher_sel) {
		hal_flash_sec_set_tag_base(tag_base);
	}

	// Set Flash SEC Cipher engine enable
	hal_flash_sec_aes_enable();
#else
	ret = hal_flash_sec_ext_stubs.hal_flash_sec_decrypt_region_enable(adtr, cipher_sel, dec_base, dec_size, tag_base);
#endif
	return ret;
}


hal_status_t hal_flash_sec_remap_region(hal_flash_sec_adapter_t *adtr)
{
	hal_status_t ret;

	// check alignment
	u32 va_base = adtr->va_base;
	u32 pa_base = adtr->pa_base;
	u32 region_size = adtr->remap_region_size;

	if (check_addr_region(va_base, region_size)) {
		return HAL_ERR_PARA;
	}
	if (check_addr_region(pa_base, region_size)) {
		return HAL_ERR_PARA;
	}

	u32 va_end = va_base + region_size;
	u32 pa_end = pa_base + region_size;

	// check overlap
	if (va_base > pa_base) {
		if (pa_end > va_base) {
			return HAL_ERR_PARA;
		}
	} else if (va_base < pa_base) {
		if (va_end > pa_base) {
			return HAL_ERR_PARA;
		}
	} else {
		return HAL_ERR_PARA;
	}

	// check options
	if (adtr->remap_region_enable > 1) {
		return HAL_ERR_PARA;
	}
	if (adtr->remap_region_sel >= FLASH_SEC_REMAP_REGION_MAX) {
		return HAL_ERR_PARA;
	}

	ret = hal_flash_sec_stubs.hal_flash_sec_remap_region(adtr);
	if (ret == HAL_OK) {
		return check_rom_error();
	}

#ifdef GET_FUNC_CHECK
	hal_flash_sec_adapter_t _adtr;
	hal_flash_sec_get_remap_region(&_adtr);
	assert(memcmp(&_adtr, adtr, sizeof(hal_flash_sec_adapter_t)) && "Get remap region check failed");
#endif
	return ret;
}

hal_status_t hal_flash_sec_set_iv(hal_flash_sec_adapter_t *adtr)
{
	hal_status_t ret;
	ret = hal_flash_sec_stubs.hal_flash_sec_set_iv(adtr);
#ifdef GET_FUNC_CHECK
	hal_flash_sec_adapter_t _adtr;
	hal_flash_sec_get_iv(&_adtr);
	assert(memcmp(&_adtr, adtr, sizeof(hal_flash_sec_adapter_t)) && "Get v check failed");
#endif
	return ret;
}

hal_status_t hal_flash_sec_decrypt_region(hal_flash_sec_adapter_t *adtr)
{
	hal_status_t ret;
	u32 va_base = adtr->va_base;
	u32 region_size = adtr->decrypt_region_size;

	if (check_addr_region(va_base, region_size)) {
		return HAL_ERR_PARA;
	}
	hal_flash_sec_cid_t cid;
	hal_flash_sec_get_cid(&cid);
	u8 decrypt_region_num = cid.decrypt_region_num;
	u8 iv_num = cid.iv_num;

	// check options
	if (adtr->decrypt_region_enable > 1) {
		return HAL_ERR_PARA;
	}
	if (adtr->decrypt_region_sel >= decrypt_region_num) {
		return HAL_ERR_PARA;
	}
	if (adtr->cipher >= FLASH_SEC_CIPHER_MAX) {
		return HAL_ERR_PARA;
	}
	if (adtr->iv_sel >= iv_num) {
		return HAL_ERR_PARA;
	}

	ret = hal_flash_sec_stubs.hal_flash_sec_decrypt_region(adtr);
	if (ret == HAL_OK) {
		return check_rom_error();
	}
#ifdef GET_FUNC_CHECK
	hal_flash_sec_adapter_t _adtr;
	hal_flash_sec_get_decrypt_region(&_adtr);
	assert(memcmp(&_adtr, adtr, sizeof(hal_flash_sec_adapter_t)) && "Get decrypt region check failed");
#endif
	return ret;
}

hal_status_t hal_flash_sec_enable_remap_region(hal_flash_sec_adapter_t *adtr)
{
	adtr->remap_region_enable = 1;
	return hal_flash_sec_remap_region(adtr);
}

hal_status_t hal_flash_sec_disable_remap_region(hal_flash_sec_adapter_t *adtr)
{
	return hal_flash_sec_stubs.hal_flash_sec_disable_remap_region(adtr);
}

hal_status_t hal_flash_sec_enable_decrypt_region(hal_flash_sec_adapter_t *adtr)
{
	adtr->decrypt_region_enable = 1;
	return hal_flash_sec_decrypt_region(adtr);
}

hal_status_t hal_flash_sec_disable_decrypt_region(hal_flash_sec_adapter_t *adtr)
{
	return hal_flash_sec_stubs.hal_flash_sec_disable_decrypt_region(adtr);
}

hal_status_t hal_flash_sec_disable_dec_region(uint8_t dec_region_sel)
{
	hal_status_t ret = HAL_OK;
	hal_flash_sec_adapter_t *adtr = &hal_sec_adtr;
	adtr->decrypt_region_sel = dec_region_sel;
	ret = hal_flash_sec_disable_decrypt_region(adtr);
	return ret;
}

hal_status_t hal_flash_sec_disable_rmp_region(uint8_t rmp_region_sel)
{
	hal_status_t ret = HAL_OK;
	hal_flash_sec_adapter_t *adtr = &hal_sec_adtr;
	adtr->remap_region_sel = rmp_region_sel;
	ret = hal_flash_sec_disable_remap_region(adtr);
	return ret;
}


hal_status_t hal_flash_sec_get_remap_region(hal_flash_sec_adapter_t *adtr)
{
	return hal_flash_sec_stubs.hal_flash_sec_get_remap_region(adtr);
}

hal_status_t hal_flash_sec_get_decrypt_region(hal_flash_sec_adapter_t *adtr)
{
	return hal_flash_sec_stubs.hal_flash_sec_get_decrypt_region(adtr);
}

hal_status_t hal_flash_sec_get_iv(hal_flash_sec_adapter_t *adtr)
{
	return hal_flash_sec_stubs.hal_flash_sec_get_iv(adtr);
}

void hal_flash_sec_get_tag_base(u32 *tag_base)
{
	hal_flash_sec_stubs.hal_flash_sec_get_tag_base(tag_base);
}

void hal_flash_sec_lock(void)
{
	hal_flash_sec_stubs.hal_flash_sec_lock();
}
