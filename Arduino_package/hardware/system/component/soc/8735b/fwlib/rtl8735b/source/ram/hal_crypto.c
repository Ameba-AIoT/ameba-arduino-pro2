/**************************************************************************//**
 * @file      hal_crypto.c
 * @brief     This CRYPTO secure and non-secure HAL API functions.
 * @version   V1.00
 * @date      2023-08-01
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
 * limitations under the License. *
 *
 ******************************************************************************/

//#include <string.h>
#include <stdint.h>

#include "platform_conf.h"
#include "cmsis.h"
#include "rtl8735b_crypto.h"
#include "rtl8735b_crypto_ctrl.h"
#include "rtl8735b_crypto_type.h"
#include "hal.h"
#include "memory.h"
#include "hal_crypto.h"
#if defined(CONFIG_BUILD_NONSECURE)
#include "hal_crypto_nsc.h"
#endif

// TODO: modification for 8710C: IP HW changed(few function are disabled)
#if CONFIG_CRYPTO_EN

/**
 * @addtogroup hs_hal_crypto CRYPTO
 * @{
 */

/**
 * Define Crypto HAL APIs for one thread access.
 * If users want to access Crypto HAL APIs in multi-threads,
 * then need to build a critical section mechanism in Application layer.
 */
#define CRYPTO_THREAD_MODE 0
#define MAX_KEY_NUMBER     5
#define MAX_KEY_LENGTH     32

#if CRYPTO_THREAD_MODE
#include "cmsis_os.h"
#endif

#if defined(CONFIG_BUILD_BOOT) && (CONFIG_BUILD_BOOT == 1) // Boot loader only
#define SECTION_BL_CRYPTO_BSS            SECTION(".ram.hal_crypto.bss")
SECTION_BL_CRYPTO_BSS hal_crypto_adapter_t g_rtl_cryptoEngine_s;
#else
#if !defined(CONFIG_BUILD_NONSECURE)
hal_crypto_adapter_t g_rtl_cryptoEngine_s;
#else
hal_crypto_adapter_t g_rtl_cryptoEngine_ns;
#endif
#endif

#if !defined(CONFIG_BUILD_NONSECURE)
extern hal_crypto_func_stubs_t hal_crypto_stubs_s;
#define HAL_CRYPTO_ADAPTER      (g_rtl_cryptoEngine_s)
#define HAL_CRYPTO_FUNC_STUBS   (hal_crypto_stubs_s)
#else
extern hal_crypto_func_stubs_t hal_crypto_stubs_ns;
#define HAL_CRYPTO_ADAPTER      (g_rtl_cryptoEngine_ns)
#define HAL_CRYPTO_FUNC_STUBS   (hal_crypto_stubs_ns)
#endif

volatile int crypto_done;
volatile int crc_done;
volatile uint8_t sk_used;

/*
 * 32bytes-aligned buffer that store mix mode hash padding initial values.
 */
const uint8_t mix_mode_hash_padding[64] __attribute__((aligned(32))) = {
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/*
 * 32bytes-aligned buffer that store mix mode hash padding values.
 */
volatile uint8_t hash_padding[96] __attribute__((aligned(32))) = {0x0}; //Actual usage maximum size is (120 - 56)+ 8 = 72 bytes

/*
 * 32bytes-aligned buffer that store mix mode encrypt padding values.
 */
volatile uint8_t enc_padding[32] __attribute__((aligned(32))) = {0x0};

//
void hal_crypto_irq_enable(hal_crypto_adapter_t *pcrypto_adapter, void *handler);
void hal_crypto_irq_disable(hal_crypto_adapter_t *pcrypto_adapter);

/** @} */ /* End of group hs_hal_crypto */

//
#if CRYPTO_THREAD_MODE

#define CRYPTO_TIMEOUT 1000

osMutexDef(crypto_mutex);
static osMutexId crypto_mutex_id;
static int critical_init(void)
{
	crypto_mutex_id = osMutexCreate(osMutex(crypto_mutex));
	if (crypto_mutex_id == NULL) {
		rtl_printf("%s : mutex id is NULL \r\n", __func__);
		return -1;
	}

	return SUCCESS;
}

static int critical_enter(void)
{
	osStatus status;

	if (crypto_mutex_id == NULL) {
		rtl_printf("%s : mutex id is NULL \r\n", __func__);
		return -1;
	}

	status = osMutexWait(crypto_mutex_id, CRYPTO_TIMEOUT);
	if (status != osOK) {
		rtl_printf("hal_crypto: %s : mutex wait failed, status=0x%x \r\n", __func__, status);
		return -1;
	}
	return SUCCESS;
}


static int critical_leave(void)
{
	osStatus status;

	if (crypto_mutex_id == NULL) {
		rtl_printf("%s : mutex id is NULL \r\n", __func__);
		return -1;
	}

	status = osMutexRelease(crypto_mutex_id);
	if (status != osOK) {
		rtl_printf("%s : mutex release failed, status=0x%x \r\n", __func__, status);
		return -1;
	}

	return SUCCESS;
}

static int critical_deinit(void)
{
	osStatus status;

	if (crypto_mutex_id == NULL) {
		rtl_printf("%s : mutex id is NULL \r\n", __func__);
		return -1;
	}

	if (crypto_mutex_id != NULL) {
		status = osMutexDelete(osMutex(crypto_mutex));

		if (status != osOK) {
			rtl_printf("%s : mutex delete fail \r\n", __func__);
			return -1;
		}
	}
	return SUCCESS;
}

#endif


#if CRYPTO_THREAD_MODE

#define MAX_THREADS 8
#define CRYPTO_SIGNAL 0x0100

static osThreadId g_thread_id[MAX_THREADS];
static int g_thread_list_head = 0;
static int g_thread_list_tail = 0;
static osThreadId g_crc_thread_id;


static osThreadId thread_list_get(void)
{
	osThreadId id;

	if (g_thread_list_head == g_thread_list_tail) {
		return NULL;
	}

	id = g_thread_id[g_thread_list_head];
	g_thread_list_head = (g_thread_list_head + 1) % MAX_THREADS;

	return id;
}

static int thread_list_add(osThreadId id)
{
	int next = (g_thread_list_tail + 1) % MAX_THREADS;

	if (next == g_thread_list_head) {
		rtl_printf("%s : FULL \r\n", __func__);
		return -1;
	}
	g_thread_id[g_thread_list_tail] = id;
	g_thread_list_tail = next;

	return 0;
}

#endif

/**
 * @addtogroup hs_hal_crypto CRYPTO
 * @{
 */
#if !defined(CONFIG_BUILD_NONSECURE)

#undef CRYPTO_MODULE
#define CRYPTO_MODULE (CRYPTO_S_MODULE)

#undef CRYPTO_REG_BASE
#define CRYPTO_REG_BASE (CRYPTO_S_BASE)

#else

#undef CRYPTO_MODULE
#define CRYPTO_MODULE (CRYPTO_NS_MODULE)

#undef CRYPTO_REG_BASE
#define CRYPTO_REG_BASE (CRYPTO_NS_BASE)


#endif


#define ACCESS_EXTERNAL_MEM                 1

#define INITMAP_REG_HAL_CALL                (1 << 0)
#define INITMAP_DEREG_HAL_CALL              (~INITMAP_REG_HAL_CALL) // (0 << 0)

#define INITMAP_REG_S_PLATFORM              (1 << 1)
#define INITMAP_REG_NS_PLATFORM             (1 << 2)
#define INITMAP_DEREG_S_PLATFORM            (~INITMAP_REG_S_PLATFORM)  // 0x5
#define INITMAP_DEREG_NS_PLATFORM           (~INITMAP_REG_NS_PLATFORM) // 0x3

#define INITMAP_S_REG                       0x2
#define INITMAP_NS_REG                      0x4


#define HASH_PADDING_PUT_UINT32_LE(n,b,i)                       \
{                                                               \
    (b)[(i)    ] = (unsigned char) ( ( (n)       ) & 0xFF );   \
    (b)[(i) + 1] = (unsigned char) ( ( (n) >>  8 ) & 0xFF );   \
    (b)[(i) + 2] = (unsigned char) ( ( (n) >> 16 ) & 0xFF );   \
    (b)[(i) + 3] = (unsigned char) ( ( (n) >> 24 ) & 0xFF );   \
}

#define HASH_PADDING_PUT_UINT32_BE(n,b,i)               \
{                                                       \
    (b)[(i)    ] = (unsigned char) ( (n) >> 24 );       \
    (b)[(i) + 1] = (unsigned char) ( (n) >> 16 );       \
    (b)[(i) + 2] = (unsigned char) ( (n) >>  8 );       \
    (b)[(i) + 3] = (unsigned char) ( (n)       );       \
}

/**
 *  @brief To notify a thread that crypto engine or CRC engine has already calculated a result.
 *  @param[in]  ok_int_cnt  counter value of crypto engine calculated a result interrupt
 *  @param[in]  isCrc       flag value of CRC engine calculated a result interrupt
 *  @return     void
 */
void g_crypto_handler(int ok_int_cnt, int isCrc)
{
	//rtl_printf("%s : ok_int_cnt = %d , isCrc=%d\r\n",
	//      __FUNCTION__, ok_int_cnt, isCrc);

#if CRYPTO_THREAD_MODE
	osThreadId id;
	int i, loops;

	loops = ok_int_cnt;

	for (i = 0; i < loops; i++) {
		id = thread_list_get();
		if (id != NULL) {
			osSignalSet(id, CRYPTO_SIGNAL);
		} else {
			rtl_printf("%s: list get NULL \r\n", __func__);
		}
	}
#else
	if (ok_int_cnt > 0) {
		crypto_done = 1;
	}
#endif

	if (isCrc) {
#if CRYPTO_THREAD_MODE
		osSignalSet(g_crc_thread_id, CRYPTO_SIGNAL);
#else
		crc_done = 1;
#endif
	}
}

/**
 *  @brief To initialize the notified flag of crypto engine.
 *  @param[in]  pIE1  Crypto adapter object
 *  @return     value == 0     success
 *  @return     value < 0      fail
 */
int g_crypto_pre_exec(void *pIE1)
{
	(void)(pIE1);
#if CRYPTO_THREAD_MODE
	{
		int32_t signal;
		osThreadId curID = osThreadGetId();
		int ret1;

		signal = osSignalClear(curID, CRYPTO_SIGNAL);
		if (signal != osOK) {
			rtl_printf("osSignalClear failed, signal= 0x%x \r\n", signal);
			return -1;
		}
		ret1 = thread_list_add(curID);
		if (ret1 != 0) {
			rtl_printf("%s : thread_list_add FULL \r\n", __func__);
			return -1;
		}
	}
#else
	crypto_done = 0;
#endif

	return SUCCESS;
}

/**
 *  @brief To wait to be notified that the crypto engine calculates a result. If crypto calculating result
 *         interrupt arrives, it will trigger interrupt service routine which notifies this information to a thread.
 *  @param[in]  pIE1  Crypto adapter object
 *  @return     value == 0     success
 *  @return     value < 0      fail
 */
int g_crypto_wait_done(void *pIE1)
{
	uint32_t loopWait;
	volatile uint32_t ips_err;
	volatile uint32_t ips_10_status;
	hal_crypto_adapter_t *pcrypto_adapter = (hal_crypto_adapter_t *)pIE1;
	(void)(pcrypto_adapter);
	loopWait = 10000000; /* hope long enough */
#if CRYPTO_THREAD_MODE
	{
		osEvent evt;

		evt = osSignalWait(CRYPTO_SIGNAL, 100); // wait for 100 ms

		if ((evt.status != osOK) && (evt.status != osEventSignal)) {
			rtl_printf("osSignalWait failed, evt.status = 0x%x \r\n", evt.status);
			return -1;
		}
	}
#else
	if (pcrypto_adapter->isIntMode) {
		//while ( crypto_done == 0 );
		// TODO: can add some Delay / and loops limitation
		while (crypto_done == 0) {
			loopWait--;
			if (loopWait == 0) {
				ips_10_status = (CRYPTO_MODULE->ipscsr_reset_isr_conf_reg);
				ips_err = (CRYPTO_MODULE->ipscsr_err_stats_reg);
				DBG_CRYPTO_ERR("Crypto interrupt doesn't arrive.\r\n");
				DBG_CRYPTO_ERR("Wait Timeout ips status = 0x%08x, ips err = 0x%08x\r\n", ips_10_status, ips_err);
				return FAIL; /* error occurs */
			}
		}
	}
#endif
	// if not interrupt mode, suggest to use default one
	return SUCCESS;
}

#if defined(CONFIG_BUILD_SECURE)
/**
 *  @brief      Enable/Disable the clock of IPsec in RAM code.
 *  @param[in]  en  set the clock of IPsec state: 1=Enable, 0=Disable
 *  @return     void
 */
void hal_crypto_engine_init_platform_en_ctrl(const int en)
{

	hal_crypto_adapter_t *pcrypto_adapter = &g_rtl_cryptoEngine_s;
	if (!((pcrypto_adapter->initmap) & INITMAP_S_REG)) {
		if (ENABLE == sk_used) {
			hal_sys_lxbus_shared_en(LXBUS_CTRL_CRYPTO, en);
		} else {
#if IS_CUT_TEST(CONFIG_CHIP_VER) || IS_CUT_A(CONFIG_CHIP_VER)
			hal_sys_peripheral_en(CRYPTO_SYS, en);
			hal_sys_lxbus_shared_en(LXBUS_CTRL_CRYPTO, en);
#else
			hal_crypto_stubs_s.hal_crypto_engine_platform_en_ctrl(en);
#endif
		}
	}
	if (en) {
		(pcrypto_adapter->initmap) |= INITMAP_REG_NS_PLATFORM; //register non_s init
	} else {
		(pcrypto_adapter->initmap) &= INITMAP_DEREG_NS_PLATFORM; //deregister non_s init
	}
}

SECTION_NS_ENTRY_FUNC void NS_ENTRY hal_crypto_engine_init_platform_nsc(const int en)
{
	hal_crypto_engine_init_platform_en_ctrl(en);
}
#endif

#if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE==1)
#if defined(ENABLE_SECCALL_PATCH)
/*Need to be defined in different object file from the caller, otherwise -Wl,-wrap may fail*/
extern void hal_crypto_engine_init_platform(void *adapter, const int en);
#else
void hal_crypto_engine_init_platform(void *adapter, const int en)
{
	hal_crypto_engine_init_platform_nsc(en);
}
#endif
#if !defined(ENABLE_SECCALL_PATCH)
int hal_crypto_engine_init_s4ns(void)
{
	return (hal_crypto_engine_init_nsc());
}
#endif

#elif (!(defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE==1))) || (defined(CONFIG_BUILD_BOOT) && (CONFIG_BUILD_BOOT==1))
void hal_crypto_engine_init_platform(void *adapter, const int en)
{
	phal_crypto_adapter_t pcrypto_adapter = (phal_crypto_adapter_t)adapter;
	if (!((pcrypto_adapter->initmap) & INITMAP_NS_REG)) {
		if (ENABLE == sk_used) {
			hal_sys_lxbus_shared_en(LXBUS_CTRL_CRYPTO, en);
		} else {
#if IS_CUT_TEST(CONFIG_CHIP_VER) || IS_CUT_A(CONFIG_CHIP_VER)
			hal_sys_peripheral_en(CRYPTO_SYS, en);
			hal_sys_lxbus_shared_en(LXBUS_CTRL_CRYPTO, en);
#else
			hal_crypto_stubs_s.hal_crypto_engine_platform_en_ctrl(en);
#endif
		}
	}
	if (en) {
		(pcrypto_adapter->initmap) |= INITMAP_REG_S_PLATFORM;   //register s init
	} else {
		(pcrypto_adapter->initmap) &= INITMAP_DEREG_S_PLATFORM; //deregister s init
	}
}
#endif


//
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
#define EXRAM_PSRAM_START_ADDR              (0x60000000)
#define EXRAM_PSRAM_END_ADDR                (0x60400000)

typedef struct crypto_buf_addr_s {
	const uint8_t *buf_addr;
} crypto_buf_addr_t, *pcrypto_buf_addr_t;

volatile uint8_t psram_check = 0;

void exram_psram_addr_check(phal_crypto_adapter_t pcrypto_adapter, pcrypto_buf_addr_t crypto_buf_list, const uint8_t buf_total_size)
{

	uint8_t i, match_check = 0;
	CRYPTO_Type *pcrypto;
	pcrypto = pcrypto_adapter->base_addr;
	for (i = 0; i < buf_total_size; i++) {
		if (((u32)(crypto_buf_list[i].buf_addr) >= EXRAM_PSRAM_START_ADDR) &&
			((u32)(crypto_buf_list[i].buf_addr) < EXRAM_PSRAM_END_ADDR)) {
			match_check++;
		}
	}
	if (match_check > 0) {
		// set DMA single command for slow memory acessing(PSRAM/FLash one ID mode)
		pcrypto->ipscsr_swap_burst_reg_b.dma_burst_length = 1;
		psram_check = 1;
	} else {
		// set DMA Burst length for internal memory acessing(internal SRAM/ DTCM)
		pcrypto->ipscsr_swap_burst_reg_b.dma_burst_length = 16;
	}
}
#endif

int hal_crypto_engine_chk_init(void)
{
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;
	if (pcrypto_adapter->isInit == 1) {
		return TRUE;
	} else {
		return FALSE;
	}
}

int hal_crypto_engine_init(void)
{
	int ret = SUCCESS;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;
	if (pcrypto_adapter->isInit) {
		DBG_CRYPTO_WARN("Crypto engine has initialized!\r\n");
		return SUCCESS;
	}
	//For enable/disable __dbg_mem_dump()
	pcrypto_adapter->isMemDump = 0;

	pcrypto_adapter->pre_exec_func = g_crypto_pre_exec;
	pcrypto_adapter->wait_done_func = g_crypto_wait_done;

	//DBG_CRYPTO_INFO("hal_crypto_adapter->initmap = 0x%x\r\n",pcrypto_adapter->initmap);
	hal_crypto_engine_init_platform(pcrypto_adapter, 1);
	(pcrypto_adapter->initmap) |= INITMAP_REG_HAL_CALL;   //Notify rom code, init is from hal
	//DBG_CRYPTO_INFO("hal_crypto_adapter->initmap = 0x%x\r\n",pcrypto_adapter->initmap);

	ret = (HAL_CRYPTO_FUNC_STUBS.hal_crypto_engine_init)(pcrypto_adapter);
	if (ret != SUCCESS) {
		return ret;
	}
#if ACCESS_EXTERNAL_MEM
	pcrypto_adapter->arch_clean_dcache_by_size = (void (*)(uint32_t, int32_t))hal_cache_stubs.dcache_clean_by_addr;
	pcrypto_adapter->arch_invalidate_dcache_by_size = (void (*)(uint32_t, int32_t))hal_cache_stubs.dcache_invalidate_by_addr;
#else
	pcrypto_adapter->arch_clean_dcache_by_size = NULL;
	pcrypto_adapter->arch_invalidate_dcache_by_size = NULL;
#endif

#if CRYPTO_THREAD_MODE
	critical_init();
#endif
	hal_crypto_irq_enable(pcrypto_adapter, (void *)g_crypto_handler);

#if defined(CONFIG_BUILD_NONSECURE)
	ret = hal_crypto_engine_init_s4ns();
	if (SUCCESS != ret) {
		DBG_CRYPTO_ERR("secure crypto init fail!\r\n");
	}
#endif
	return ret;
}

int hal_crypto_engine_deinit(void)
{
	int ret = SUCCESS;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;
	if (pcrypto_adapter->isInit == 0) {
		DBG_CRYPTO_WARN("Crypto engine doesn't initialize!\r\n");
		return SUCCESS;
	}

	pcrypto_adapter->pre_exec_func = NULL;
	pcrypto_adapter->wait_done_func = NULL;
	pcrypto_adapter->arch_clean_dcache_by_size = NULL;
	pcrypto_adapter->arch_invalidate_dcache_by_size = NULL;
	hal_crypto_irq_disable(pcrypto_adapter);
	ret = (HAL_CRYPTO_FUNC_STUBS.hal_crypto_engine_deinit)(pcrypto_adapter);
	if (ret != SUCCESS) {
		return ret;
	}
	//DBG_CRYPTO_INFO("hal_crypto_adapter->initmap = 0x%x\r\n",pcrypto_adapter->initmap);
	hal_crypto_engine_init_platform(pcrypto_adapter, 0);
	(pcrypto_adapter->initmap) &= INITMAP_DEREG_HAL_CALL;  //deinit the notify flag
	//DBG_CRYPTO_INFO("hal_crypto_adapter->initmap = 0x%x\r\n",pcrypto_adapter->initmap);

#if CRYPTO_THREAD_MODE
	critical_deinit();
#endif
	return ret;
}

void hal_crypto_engine_key_stg_deinit(void)
{
	hal_sys_peripheral_en(CRYPTO_SYS, DISABLE);
	sk_used = DISABLE;
}

//
// IRQ
//
/**
 *  @brief The CRYPTO interrupt service routine function pointer type.
 */
typedef void (*crypto_isr_t)(int, int);

//
crypto_isr_t irq_handle;

/**
 *  @brief The CRYPTO interrupt handler. It processes interrupt events which are crypto engine calculated a result or
 *         CRC engine calculated a result.
 *  @return     void
 */
void crypto_handler(void)
{
	crypto_isr_t handler = (crypto_isr_t)irq_handle;

	//uint32_t ips_10_status, ips_err;
	volatile uint32_t ok_int_cnt;
	//volatile uint32_t val;

	ok_int_cnt = (CRYPTO_MODULE->ipscsr_reset_isr_conf_reg_b.ok_intr_cnt);
	if (ok_int_cnt > 0) {
		(CRYPTO_MODULE->ipscsr_reset_isr_conf_reg_b.clear_ok_intr_num) = ok_int_cnt;
		(CRYPTO_MODULE->ipscsr_reset_isr_conf_reg_b.cmd_ok) = 1;
	}
	//val = (CRYPTO_MODULE->ipscsr_reset_isr_conf_reg).w;
	//ips_10_status = (CRYPTO_MODULE->ipscsr_reset_isr_conf_reg).w;
	//ips_err = (CRYPTO_MODULE->ipscsr_err_stats_reg).w;
	//if ( ips_err != 0 )
	//    rtl_printf("- ips status =0x%08x, ips err = 0x%08x\r\n", ips_10_status, ips_err);

	//rtl_printf("ok_int_cnt : %d \r\n", ok_int_cnt);

	// for CRC
	{
		int isCrc = 0;
//#if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE==1)
#if !defined(CONFIG_BUILD_NONSECURE)
		volatile uint32_t val;
		//Only Non-secure support crc engine
		val = (CRYPTO_MODULE->crc_stat_reg_b.crc_ok);

		if (val) {
			(CRYPTO_MODULE->crc_stat_reg_b.crc_ok) = 1;
			isCrc = 1;
		}
#endif
		handler(ok_int_cnt, isCrc);
	}

	// To make sure the cmd_ok has been written
	__DSB();
}

/**
 *  @brief To register a interrupt handler for the crypto engine and initialize the related crypto interrupt settings.
 *  @param[in]  pcrypto_adapter   Crypto adapter object
 *  @param[in]  handler Interrupt service routine function
 *  @return     void
 */
void hal_crypto_irq_enable(hal_crypto_adapter_t *pcrypto_adapter, void *handler)
{
	irq_handle = (crypto_isr_t)handler;

#if !defined(CONFIG_BUILD_NONSECURE)
	hal_irq_set_vector(SCrypto_IRQn, (uint32_t)crypto_handler);
	hal_irq_clear_pending(SCrypto_IRQn);
	hal_irq_set_priority(SCrypto_IRQn, SCrypto_IRQPri);

	(CRYPTO_MODULE->ipscsr_reset_isr_conf_reg_b.intr_mode) = 1;
	(CRYPTO_MODULE->ipscsr_int_mask_reg_b.cmd_ok_m) = 0;
	hal_irq_enable(SCrypto_IRQn);
#else
	hal_irq_set_vector(Crypto_IRQn, (uint32_t)crypto_handler);
	hal_irq_clear_pending(Crypto_IRQn);
	hal_irq_set_priority(Crypto_IRQn, Crypto_IRQPri);

	(CRYPTO_MODULE->ipscsr_reset_isr_conf_reg_b.intr_mode) = 1;
	(CRYPTO_MODULE->ipscsr_int_mask_reg_b.cmd_ok_m) = 0;
	hal_irq_enable(Crypto_IRQn);
#endif


	pcrypto_adapter->isIntMode = 1;
}

/**
 *  @brief To un-register a interrupt handler for the crypto engine and enable interrupt mask,
 *         then inactive interrupt mode state.
 *  @param[in]  pcrypto_adapter  Crypto adapter object
 *  @return     void
 */
void hal_crypto_irq_disable(hal_crypto_adapter_t *pcrypto_adapter)
{
	if (pcrypto_adapter->isIntMode) {
		(CRYPTO_MODULE->ipscsr_int_mask_reg_b.cmd_ok_m) = 1;

#if !defined(CONFIG_BUILD_NONSECURE)
		hal_irq_disable(SCrypto_IRQn);
		hal_irq_set_vector(SCrypto_IRQn, (uint32_t)NULL);
#else
		hal_irq_disable(Crypto_IRQn);
		hal_irq_set_vector(Crypto_IRQn, (uint32_t)NULL);

#endif
		pcrypto_adapter->isIntMode = 0;
	}
}

/** @} */ /* End of group hs_hal_crypto */

//
// Authentication
//

// MD5
int hal_crypto_md5(IN const u8 *message, IN const u32 msglen, OUT u8 *pDigest)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		if (msglen > 0) {
			return _ERRNO_CRYPTO_NULL_POINTER;
		} else {
			memcpy(pDigest, md5_null_msg_result, 16);
			return SUCCESS;
		}
	}
	if (msglen == 0) {
		memcpy(pDigest, md5_null_msg_result, 16);
		return SUCCESS;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}

#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[2] = {
		{.buf_addr = message},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth(pcrypto_adapter, AUTH_TYPE_MD5, message, msglen, NULL, 0, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_md5_init(void)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
#endif
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_init(pcrypto_adapter, AUTH_TYPE_MD5, NULL, 0);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_md5_process(
	IN const u8 *message, IN const u32 msglen,
	OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		if (msglen > 0) {
			return _ERRNO_CRYPTO_NULL_POINTER;
		} else {
			memcpy(pDigest, md5_null_msg_result, 16);
			return SUCCESS;
		}
	}
	if (msglen == 0) {
		memcpy(pDigest, md5_null_msg_result, 16);
		return SUCCESS;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}

#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	crypto_buf_addr_t crypto_buf_list[2] = {
		{.buf_addr = message},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_process(pcrypto_adapter, AUTH_TYPE_MD5, message, msglen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_md5_update(IN const u8 *message, IN const u32 msglen)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}

#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = message}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_update(pcrypto_adapter, AUTH_TYPE_MD5, message, msglen);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_md5_final(OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_final(pcrypto_adapter, AUTH_TYPE_MD5, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

// SHA1
int hal_crypto_sha1(IN const u8 *message, IN const u32 msglen, OUT u8 *pDigest)
{
	int ret;

#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		if (msglen > 0) {
			return _ERRNO_CRYPTO_NULL_POINTER;
		} else {
			memcpy(pDigest, sha1_null_msg_result, 20);
			return SUCCESS;
		}
	}
	if (msglen == 0) {
		memcpy(pDigest, sha1_null_msg_result, 20);
		return SUCCESS;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[2] = {
		{.buf_addr = message},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
#endif
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth(pcrypto_adapter, AUTH_TYPE_SHA1, message, msglen, NULL, 0, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif

	return ret;
}

int hal_crypto_sha1_init(void)
{
	int ret;

#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
#endif
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_init(pcrypto_adapter, AUTH_TYPE_SHA1, NULL, 0);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_sha1_process(
	IN const u8 *message, IN const u32 msglen,
	OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		if (msglen > 0) {
			return _ERRNO_CRYPTO_NULL_POINTER;
		} else {
			memcpy(pDigest, sha1_null_msg_result, 20);
			return SUCCESS;
		}
	}
	if (msglen == 0) {
		memcpy(pDigest, sha1_null_msg_result, 20);
		return SUCCESS;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	crypto_buf_addr_t crypto_buf_list[2] = {
		{.buf_addr = message},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
#endif
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_process(pcrypto_adapter, AUTH_TYPE_SHA1, message, msglen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_sha1_update(IN const u8 *message, IN const u32 msglen)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = message}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_update(pcrypto_adapter, AUTH_TYPE_SHA1, message, msglen);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_sha1_final(OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_final(pcrypto_adapter, AUTH_TYPE_SHA1, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif

	return ret;
}

// SHA2-224
int hal_crypto_sha2_224(IN const u8 *message, IN const u32 msglen, OUT u8 *pDigest)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		if (msglen > 0) {
			return _ERRNO_CRYPTO_NULL_POINTER;
		} else {
			memcpy(pDigest, sha2_224_null_msg_result, 28);
			return SUCCESS;
		}
	}
	if (msglen == 0) {
		memcpy(pDigest, sha2_224_null_msg_result, 28);
		return SUCCESS;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[2] = {
		{.buf_addr = message},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
#endif
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth(pcrypto_adapter, AUTH_TYPE_SHA2_224_ALL, message, msglen, NULL, 0, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_sha2_224_init(void)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
#endif
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_init(pcrypto_adapter, AUTH_TYPE_SHA2_224_ALL, NULL, 0);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_sha2_224_process(
	IN const u8 *message, IN const u32 msglen,
	OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		if (msglen > 0) {
			return _ERRNO_CRYPTO_NULL_POINTER;
		} else {
			memcpy(pDigest, sha2_224_null_msg_result, 28);
			return SUCCESS;
		}
	}
	if (msglen == 0) {
		memcpy(pDigest, sha2_224_null_msg_result, 28);
		return SUCCESS;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	crypto_buf_addr_t crypto_buf_list[2] = {
		{.buf_addr = message},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
#endif
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_process(pcrypto_adapter, AUTH_TYPE_SHA2_224_ALL, message, msglen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_sha2_224_update(IN const u8 *message, IN const u32 msglen)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = message}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_update(pcrypto_adapter, AUTH_TYPE_SHA2_224_ALL, message, msglen);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_sha2_224_final(OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_final(pcrypto_adapter, AUTH_TYPE_SHA2_224_ALL, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}


// SHA2-256
int hal_crypto_sha2_256(IN const u8 *message, IN const u32 msglen, OUT u8 *pDigest)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		if (msglen > 0) {
			return _ERRNO_CRYPTO_NULL_POINTER;
		} else {
			memcpy(pDigest, sha2_256_null_msg_result, 32);
			return SUCCESS;
		}
	}
	if (msglen == 0) {
		memcpy(pDigest, sha2_256_null_msg_result, 32);
		return SUCCESS;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[2] = {
		{.buf_addr = message},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth(pcrypto_adapter, AUTH_TYPE_SHA2_256_ALL, message, msglen, NULL, 0, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_sha2_256_init(void)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
#endif
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_init(pcrypto_adapter, AUTH_TYPE_SHA2_256_ALL, NULL, 0);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_sha2_256_process(
	IN const u8 *message, IN const u32 msglen,
	OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		if (msglen > 0) {
			return _ERRNO_CRYPTO_NULL_POINTER;
		} else {
			memcpy(pDigest, sha2_256_null_msg_result, 32);
			return SUCCESS;
		}
	}
	if (msglen == 0) {
		memcpy(pDigest, sha2_256_null_msg_result, 32);
		return SUCCESS;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	crypto_buf_addr_t crypto_buf_list[2] = {
		{.buf_addr = message},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_process(pcrypto_adapter, AUTH_TYPE_SHA2_256_ALL, message, msglen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_sha2_256_update(IN const u8 *message, IN const u32 msglen)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = message}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_update(pcrypto_adapter, AUTH_TYPE_SHA2_256_ALL, message, msglen);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_sha2_256_final(OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_final(pcrypto_adapter, AUTH_TYPE_SHA2_256_ALL, pDigest);

#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

// SHA2-384
int hal_crypto_sha2_384(IN const u8 *message, IN const u32 msglen, OUT u8 *pDigest)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
//    if (message == NULL) {
//        if (msglen > 0) {
//            return _ERRNO_CRYPTO_NULL_POINTER;
//        } else {
//            memcpy(pDigest, sha2_224_null_msg_result, 28);
//            return SUCCESS;
//        }
//    }
//    if (msglen == 0) {
//        memcpy(pDigest, sha2_224_null_msg_result, 28);
//        return SUCCESS;
//    }
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[2] = {
		{.buf_addr = message},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
#endif
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth(pcrypto_adapter, AUTH_TYPE_SHA2_384_ALL, message, msglen, NULL, 0, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_sha2_384_init(void)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
#endif
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_init(pcrypto_adapter, AUTH_TYPE_SHA2_384_ALL, NULL, 0);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_sha2_384_process(
	IN const u8 *message, IN const u32 msglen,
	OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
//    if (message == NULL) {
//        if (msglen > 0) {
//            return _ERRNO_CRYPTO_NULL_POINTER;
//        } else {
//            memcpy(pDigest, sha2_224_null_msg_result, 28);
//            return SUCCESS;
//        }
//    }
//    if (msglen == 0) {
//        memcpy(pDigest, sha2_224_null_msg_result, 28);
//        return SUCCESS;
//    }
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	crypto_buf_addr_t crypto_buf_list[2] = {
		{.buf_addr = message},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
#endif
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_process(pcrypto_adapter, AUTH_TYPE_SHA2_384_ALL, message, msglen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_sha2_384_update(IN const u8 *message, IN const u32 msglen)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = message}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_update(pcrypto_adapter, AUTH_TYPE_SHA2_384_ALL, message, msglen);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_sha2_384_final(OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_final(pcrypto_adapter, AUTH_TYPE_SHA2_384_ALL, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

// SHA2-512
int hal_crypto_sha2_512(IN const u8 *message, IN const u32 msglen, OUT u8 *pDigest)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
//    if (message == NULL) {
//        if (msglen > 0) {
//            return _ERRNO_CRYPTO_NULL_POINTER;
//        } else {
//            memcpy(pDigest, sha2_224_null_msg_result, 28);
//            return SUCCESS;
//        }
//    }
//    if (msglen == 0) {
//        memcpy(pDigest, sha2_224_null_msg_result, 28);
//        return SUCCESS;
//    }
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[2] = {
		{.buf_addr = message},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
#endif
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth(pcrypto_adapter, AUTH_TYPE_SHA2_512_ALL, message, msglen, NULL, 0, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_sha2_512_init(void)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
#endif
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_init(pcrypto_adapter, AUTH_TYPE_SHA2_512_ALL, NULL, 0);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_sha2_512_process(
	IN const u8 *message, IN const u32 msglen,
	OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
//    if (message == NULL) {
//        if (msglen > 0) {
//            return _ERRNO_CRYPTO_NULL_POINTER;
//        } else {
//            memcpy(pDigest, sha2_224_null_msg_result, 28);
//            return SUCCESS;
//        }
//    }
//    if (msglen == 0) {
//        memcpy(pDigest, sha2_224_null_msg_result, 28);
//        return SUCCESS;
//    }
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	crypto_buf_addr_t crypto_buf_list[2] = {
		{.buf_addr = message},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
#endif
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_process(pcrypto_adapter, AUTH_TYPE_SHA2_512_ALL, message, msglen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_sha2_512_update(IN const u8 *message, IN const u32 msglen)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = message}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_update(pcrypto_adapter, AUTH_TYPE_SHA2_512_ALL, message, msglen);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_sha2_512_final(OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_final(pcrypto_adapter, AUTH_TYPE_SHA2_512_ALL, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}



// HMAC-md5
int hal_crypto_hmac_md5(IN const u8 *message, IN const u32 msglen,
						IN const u8 *key, IN const u32 keylen, OUT u8 *pDigest)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (keylen <= 0) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (keylen > CRYPTO_AUTH_PADDING) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[3] = {
		{.buf_addr = message},
		{.buf_addr = key},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth(pcrypto_adapter, AUTH_TYPE_HMAC_MD5, message, msglen, key, keylen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_hmac_md5_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (keylen <= 0) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (keylen > CRYPTO_AUTH_PADDING) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[1] = {
		{.buf_addr = key}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_init(pcrypto_adapter, AUTH_TYPE_HMAC_MD5, key, keylen);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_hmac_md5_process(IN const u8 *message, IN const u32 msglen, OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[2] = {
			{.buf_addr = message},
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_process(pcrypto_adapter, AUTH_TYPE_HMAC_MD5, message, msglen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_hmac_md5_update(IN const u8 *message, IN const u32 msglen)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = message}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_update(pcrypto_adapter, AUTH_TYPE_HMAC_MD5, message, msglen);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_hmac_md5_final(OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_final(pcrypto_adapter, AUTH_TYPE_HMAC_MD5, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}


// HMAC-sha1
int hal_crypto_hmac_sha1(IN const u8 *message, IN const u32 msglen,
						 IN const u8 *key, IN const u32 keylen, OUT u8 *pDigest)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (keylen <= 0) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (keylen > CRYPTO_AUTH_PADDING) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[3] = {
		{.buf_addr = message},
		{.buf_addr = key},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth(pcrypto_adapter, AUTH_TYPE_HMAC_SHA1, message, msglen, key, keylen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_hmac_sha1_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (keylen <= 0) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (keylen > CRYPTO_AUTH_PADDING) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[1] = {
		{.buf_addr = key}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_init(pcrypto_adapter, AUTH_TYPE_HMAC_SHA1, key, keylen);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_hmac_sha1_process(IN const u8 *message, IN const u32 msglen, OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[2] = {
			{.buf_addr = message},
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_process(pcrypto_adapter, AUTH_TYPE_HMAC_SHA1, message, msglen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_hmac_sha1_update(IN const u8 *message, IN const u32 msglen)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}

#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = message}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_update(pcrypto_adapter, AUTH_TYPE_HMAC_SHA1, message, msglen);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_hmac_sha1_final(OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_final(pcrypto_adapter, AUTH_TYPE_HMAC_SHA1, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}


// HMAC-sha2
// -- 224
int hal_crypto_hmac_sha2_224(IN const u8 *message, IN const u32 msglen,
							 IN const u8 *key, IN const u32 keylen, OUT u8 *pDigest)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (keylen <= 0) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (keylen > CRYPTO_AUTH_PADDING) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[3] = {
		{.buf_addr = message},
		{.buf_addr = key},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_224_ALL, message, msglen, key, keylen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_hmac_sha2_224_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (keylen <= 0) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (keylen > CRYPTO_AUTH_PADDING) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[1] = {
		{.buf_addr = key}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_init(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_224_ALL, key, keylen);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_hmac_sha2_224_process(IN const u8 *message, IN const u32 msglen, OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}

#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[2] = {
			{.buf_addr = message},
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_process(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_224_ALL, message, msglen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_hmac_sha2_224_update(IN const u8 *message, IN const u32 msglen)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}

#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = message}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_update(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_224_ALL, message, msglen);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_hmac_sha2_224_final(OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_final(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_224_ALL, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

// -- 256
int hal_crypto_hmac_sha2_256(IN const u8 *message, IN const u32 msglen,
							 IN const u8 *key, IN const u32 keylen, OUT u8 *pDigest)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (keylen <= 0) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (keylen > CRYPTO_AUTH_PADDING) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[3] = {
		{.buf_addr = message},
		{.buf_addr = key},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_256_ALL, message, msglen, key, keylen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_hmac_sha2_256_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (keylen <= 0) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (keylen > CRYPTO_AUTH_PADDING) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[1] = {
		{.buf_addr = key}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_init(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_256_ALL, key, keylen);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_hmac_sha2_256_process(IN const u8 *message, IN const u32 msglen, OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[2] = {
			{.buf_addr = message},
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_process(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_256_ALL, message, msglen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_hmac_sha2_256_update(IN const u8 *message, IN const u32 msglen)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = message}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_update(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_256_ALL, message, msglen);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}



int hal_crypto_hmac_sha2_256_final(OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_final(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_256_ALL, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

#if IS_AFTER_CUT_A(CONFIG_CHIP_VER)
#if !defined(CONFIG_BUILD_NONSECURE)

uint32_t hal_crypto_hmac_sha2_256_get_sk_cfg(const uint8_t sk_op, const uint8_t sk_idx, const uint8_t wb_op, const uint8_t wb_idx)
{
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;
	uint32_t sk_cfg = 0x0;
	hal_crypto_key_cfg_t key_cfg;
	hal_crypto_wb_cfg_t wb_cfg;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}

	key_cfg.b.sel = (sk_op & 0xF);
	key_cfg.b.idx = (sk_idx & 0xF);
	HAL_CRYPTO_FUNC_STUBS.hal_crypto_set_sk_cfg_info(&sk_cfg, (key_cfg.w), CRYPTO_KEY_STG_ROLE_KEYCFG);

	wb_cfg.b.sel = (wb_op & 0xF);
	wb_cfg.b.idx = (wb_idx & 0xF);
	HAL_CRYPTO_FUNC_STUBS.hal_crypto_set_sk_cfg_info(&sk_cfg, (wb_cfg.w), CRYPTO_KEY_STG_ROLE_WBCFG);
	return sk_cfg;
}

int hal_crypto_hmac_sha2_256_sk_init(IN const u8 *key, IN const u32 sk_cfg)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_sk_init(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_256_ALL, key, sk_cfg);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	} else {
		if (DISABLE == sk_used) {
			sk_used = ENABLE;
		}
	}
	return ret;
}

int hal_crypto_hmac_sha2_256_sk_final(OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_sk_final(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_256_ALL, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}
#endif
#endif
// -- 384
int hal_crypto_hmac_sha2_384(IN const u8 *message, IN const u32 msglen,
							 IN const u8 *key, IN const u32 keylen, OUT u8 *pDigest)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (keylen <= 0) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (keylen > CRYPTO_AUTH_PADDING) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[3] = {
		{.buf_addr = message},
		{.buf_addr = key},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_384_ALL, message, msglen, key, keylen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_hmac_sha2_384_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (keylen <= 0) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (keylen > CRYPTO_AUTH_PADDING) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[1] = {
		{.buf_addr = key}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_init(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_384_ALL, key, keylen);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_hmac_sha2_384_process(IN const u8 *message, IN const u32 msglen, OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[2] = {
			{.buf_addr = message},
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_process(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_384_ALL, message, msglen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_hmac_sha2_384_update(IN const u8 *message, IN const u32 msglen)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = message}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_update(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_384_ALL, message, msglen);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_hmac_sha2_384_final(OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_final(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_384_ALL, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

// -- 512
int hal_crypto_hmac_sha2_512(IN const u8 *message, IN const u32 msglen,
							 IN const u8 *key, IN const u32 keylen, OUT u8 *pDigest)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (keylen <= 0) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (keylen > CRYPTO_AUTH_PADDING) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[3] = {
		{.buf_addr = message},
		{.buf_addr = key},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_512_ALL, message, msglen, key, keylen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_hmac_sha2_512_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (keylen <= 0) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (keylen > CRYPTO_AUTH_PADDING) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[1] = {
		{.buf_addr = key}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_init(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_512_ALL, key, keylen);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_hmac_sha2_512_process(IN const u8 *message, IN const u32 msglen, OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[2] = {
			{.buf_addr = message},
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_process(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_512_ALL, message, msglen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_hmac_sha2_512_update(IN const u8 *message, IN const u32 msglen)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = message}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_update(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_512_ALL, message, msglen);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_hmac_sha2_512_final(OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[1] = {
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_auth_final(pcrypto_adapter, AUTH_TYPE_HMAC_SHA2_512_ALL, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_aes_sk_init_core(const u32 cipher_type, uint8_t key_num, IN const u32 keylen)
{
	int ret;
	uint32_t sk_cfg = 0x0;
	hal_crypto_key_cfg_t key_cfg;
	hal_crypto_wb_cfg_t wb_cfg;
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	DBG_CRYPTO_ERR("Test-chip NON-support\r\n");
	ret = SUCCESS;
	return ret;
#else

#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if ((keylen != CRYPTO_AES128_KEY_LENGTH) && (keylen != CRYPTO_AES192_KEY_LENGTH) &&
		(keylen != CRYPTO_AES256_KEY_LENGTH)) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[1] = {
		{.buf_addr = key}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
#endif

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}

	key_cfg.b.sel = (KEY_STG_SKTYPE_LD_SK & 0xF);
	key_cfg.b.idx = (key_num & 0xF);
	HAL_CRYPTO_FUNC_STUBS.hal_crypto_set_sk_cfg_info(&sk_cfg, (key_cfg.w), CRYPTO_KEY_STG_ROLE_KEYCFG);

	wb_cfg.b.sel = (KEY_STG_WBTYPE_WB_ONLY_BUF & 0xF);
	wb_cfg.b.idx = (KEY_STG_SK_IDX_NONE & 0xF);
	HAL_CRYPTO_FUNC_STUBS.hal_crypto_set_sk_cfg_info(&sk_cfg, (wb_cfg.w), CRYPTO_KEY_STG_ROLE_WBCFG);
	if (sk_cfg == 0x0) {
		ret = FAIL;
		dbg_printf("get sk_cfg fail:0x%x\r\n", sk_cfg);
		return ret;
	}

	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_sk_init(pcrypto_adapter, cipher_type, sk_cfg, keylen);
	if (SUCCESS == ret) {
		if (DISABLE == sk_used) {
			sk_used = ENABLE;
		}
	}
	return ret;
#endif
}

// AES-CBC

int hal_crypto_aes_cbc_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if ((keylen != CRYPTO_AES128_KEY_LENGTH) && (keylen != CRYPTO_AES192_KEY_LENGTH) &&
		(keylen != CRYPTO_AES256_KEY_LENGTH)) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[1] = {
		{.buf_addr = key}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
#endif
	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_init(pcrypto_adapter, CIPHER_TYPE_AES_CBC, key, keylen);
	return ret;
}

int hal_crypto_aes_cbc_encrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 ivlen,
	OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (ivlen != CRYPTO_AES_IV_LENGTH) {
		return _ERRNO_CRYPTO_IV_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[3] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = pResult}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
	}
#endif

	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_encrypt(pcrypto_adapter, CIPHER_TYPE_AES_CBC, message, msglen, iv, ivlen,
			NULL, 0, pResult, NULL);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_aes_cbc_decrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 ivlen,
	OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (ivlen != CRYPTO_AES_IV_LENGTH) {
		return _ERRNO_CRYPTO_IV_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[3] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = pResult}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
	}
#endif

	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_decrypt(pcrypto_adapter, CIPHER_TYPE_AES_CBC, message, msglen, iv, ivlen,
			NULL, 0, pResult, NULL);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

// AES-ECB

int hal_crypto_aes_ecb_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if ((keylen != CRYPTO_AES128_KEY_LENGTH) && (keylen != CRYPTO_AES192_KEY_LENGTH) &&
		(keylen != CRYPTO_AES256_KEY_LENGTH)) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[1] = {
		{.buf_addr = key}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
#endif

	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_init(pcrypto_adapter, CIPHER_TYPE_AES_ECB, key, keylen);
	return ret;
}

int hal_crypto_aes_ecb_sk_init(uint8_t key_num, IN const u32 keylen)
{
	int ret;

	ret = hal_crypto_aes_sk_init_core(CIPHER_TYPE_AES_ECB, key_num, keylen);
	return ret;
}

int hal_crypto_aes_ecb_encrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 ivlen,
	OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	iv = NULL;
	if (ivlen != 0) {
		return _ERRNO_CRYPTO_IV_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[3] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = pResult}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
	}
#endif

	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_encrypt(pcrypto_adapter, CIPHER_TYPE_AES_ECB, message, msglen, iv, ivlen,
			NULL, 0, pResult, NULL);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_aes_ecb_decrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 ivlen,
	OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	iv = NULL;
	if (ivlen != 0) {
		return _ERRNO_CRYPTO_IV_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[3] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = pResult}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
	}
#endif
	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_decrypt(pcrypto_adapter, CIPHER_TYPE_AES_ECB, message, msglen, iv, ivlen,
			NULL, 0, pResult, NULL);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

// AES-CTR

int hal_crypto_aes_ctr_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if ((keylen != CRYPTO_AES128_KEY_LENGTH) && (keylen != CRYPTO_AES192_KEY_LENGTH) &&
		(keylen != CRYPTO_AES256_KEY_LENGTH)) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[1] = {
		{.buf_addr = key}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
#endif

	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_init(pcrypto_adapter, CIPHER_TYPE_AES_CTR, key, keylen);
	return ret;
}

int hal_crypto_aes_ctr_encrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 ivlen,
	OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (ivlen != CRYPTO_AES_IV_LENGTH) {
		return _ERRNO_CRYPTO_IV_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[3] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = pResult}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
	}
#endif

	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_encrypt(pcrypto_adapter, CIPHER_TYPE_AES_CTR, message, msglen, iv, ivlen,
			NULL, 0, pResult, NULL);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_aes_ctr_decrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 ivlen,
	OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (ivlen != CRYPTO_AES_IV_LENGTH) {
		return _ERRNO_CRYPTO_IV_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[3] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = pResult}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_decrypt(pcrypto_adapter, CIPHER_TYPE_AES_CTR, message, msglen, iv, ivlen,
			NULL, 0, pResult, NULL);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

// AES-CFB

int hal_crypto_aes_cfb_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if ((keylen != CRYPTO_AES128_KEY_LENGTH) && (keylen != CRYPTO_AES192_KEY_LENGTH) &&
		(keylen != CRYPTO_AES256_KEY_LENGTH)) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[1] = {
		{.buf_addr = key}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
#endif

	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_init(pcrypto_adapter, CIPHER_TYPE_AES_CFB, key, keylen);
	return ret;
}

int hal_crypto_aes_cfb_encrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 ivlen,
	OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (ivlen != CRYPTO_AES_IV_LENGTH) {
		return _ERRNO_CRYPTO_IV_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[3] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = pResult}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
	}
#endif

	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_encrypt(pcrypto_adapter, CIPHER_TYPE_AES_CFB, message, msglen, iv, ivlen,
			NULL, 0, pResult, NULL);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_aes_cfb_decrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 ivlen,
	OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (ivlen != CRYPTO_AES_IV_LENGTH) {
		return _ERRNO_CRYPTO_IV_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[3] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = pResult}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
	}
#endif

	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_decrypt(pcrypto_adapter, CIPHER_TYPE_AES_CFB, message, msglen, iv, ivlen,
			NULL, 0, pResult, NULL);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

// AES-OFB

int hal_crypto_aes_ofb_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if ((keylen != CRYPTO_AES128_KEY_LENGTH) && (keylen != CRYPTO_AES192_KEY_LENGTH) &&
		(keylen != CRYPTO_AES256_KEY_LENGTH)) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[1] = {
		{.buf_addr = key}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
#endif

	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_init(pcrypto_adapter, CIPHER_TYPE_AES_OFB, key, keylen);
	return ret;
}

int hal_crypto_aes_ofb_encrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 ivlen,
	OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (ivlen != CRYPTO_AES_IV_LENGTH) {
		return _ERRNO_CRYPTO_IV_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[3] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = pResult}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_encrypt(pcrypto_adapter, CIPHER_TYPE_AES_OFB, message, msglen, iv, ivlen,
			NULL, 0, pResult, NULL);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_aes_ofb_decrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 ivlen,
	OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (ivlen != CRYPTO_AES_IV_LENGTH) {
		return _ERRNO_CRYPTO_IV_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[3] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = pResult}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
	}
#endif

	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_decrypt(pcrypto_adapter, CIPHER_TYPE_AES_OFB, message, msglen, iv, ivlen,
			NULL, 0, pResult, NULL);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

//AES GHASH

int hal_crypto_aes_ghash(
	IN const u8 *message, IN const u32 msglen,
	IN const u8 *key, IN const u32 keylen,
	OUT u8 *pDigest)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (keylen != CRYPTO_AES128_KEY_LENGTH) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[3] = {
		{.buf_addr = message},
		{.buf_addr = key},
		{.buf_addr = pDigest}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_init(pcrypto_adapter, CIPHER_TYPE_AES_GHASH, key, keylen);
	if (ret != SUCCESS) {
		return ret;
	}
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_decrypt(pcrypto_adapter, CIPHER_TYPE_AES_GHASH, message, msglen,
			NULL, 0, NULL, 0, NULL, pDigest);

#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_aes_ghash_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (keylen != CRYPTO_AES128_KEY_LENGTH) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[1] = {
		{.buf_addr = key}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_init(pcrypto_adapter, CIPHER_TYPE_AES_GHASH, key, keylen);

	return ret;
}

int hal_crypto_aes_ghash_process(IN const u8 *message, IN const u32 msglen, OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[2] = {
			{.buf_addr = message},
			{.buf_addr = pDigest}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_decrypt(pcrypto_adapter, CIPHER_TYPE_AES_GHASH, message, msglen,
			NULL, 0, NULL, 0, NULL, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

//AES GMAC

int hal_crypto_aes_gmac(
	IN const u8 *message, IN const u32 msglen,
	IN const u8 *key, IN const u32 keylen,
	IN const u8 *iv,
	IN const u8 *aad, IN const u32 aadlen, OUT u8 *pTag)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if ((keylen != CRYPTO_AES128_KEY_LENGTH) && (keylen != CRYPTO_AES192_KEY_LENGTH) &&
		(keylen != CRYPTO_AES256_KEY_LENGTH)) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if ((u32)(aad) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (aadlen > CRYPTO_MAX_AAD_LENGTH) {
		return _ERRNO_CRYPTO_AAD_OutRange;
	}
	if (pTag == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[5] = {
		{.buf_addr = message},
		{.buf_addr = key},
		{.buf_addr = iv},
		{.buf_addr = aad},
		{.buf_addr = pTag}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 5);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_init(pcrypto_adapter, CIPHER_TYPE_AES_GMAC, key, keylen);
	if (ret != SUCCESS) {
		return ret;
	}
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_decrypt(pcrypto_adapter, CIPHER_TYPE_AES_GMAC, message, msglen,
			iv, 0, aad, aadlen, NULL, pTag);

#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_aes_gmac_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if ((keylen != CRYPTO_AES128_KEY_LENGTH) && (keylen != CRYPTO_AES192_KEY_LENGTH) &&
		(keylen != CRYPTO_AES256_KEY_LENGTH)) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[1] = {
		{.buf_addr = key}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_init(pcrypto_adapter, CIPHER_TYPE_AES_GMAC, key, keylen);

	return ret;
}

int hal_crypto_aes_gmac_process(
	IN const u8 *message, IN const u32 msglen,
	IN const u8 *iv, IN const u8 *aad, IN const u32 aadlen, OUT u8 *pTag)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if ((u32)(aad) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (aadlen > CRYPTO_MAX_AAD_LENGTH) {
		return _ERRNO_CRYPTO_AAD_OutRange;
	}
	if (pTag == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[4] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = aad},
			{.buf_addr = pTag}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 4);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_decrypt(pcrypto_adapter, CIPHER_TYPE_AES_GMAC, message, msglen,
			iv, 0, aad, aadlen, NULL, pTag);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

//AES-GCTR

int hal_crypto_aes_gctr_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if ((keylen != CRYPTO_AES128_KEY_LENGTH) && (keylen != CRYPTO_AES192_KEY_LENGTH) &&
		(keylen != CRYPTO_AES256_KEY_LENGTH)) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[1] = {
		{.buf_addr = key}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
#endif

	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_init(pcrypto_adapter, CIPHER_TYPE_AES_GCTR, key, keylen);
	return ret;
}

int hal_crypto_aes_gctr_encrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv, OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[3] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = pResult}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
	}
#endif

	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_encrypt(pcrypto_adapter, CIPHER_TYPE_AES_GCTR, message, msglen, iv, 0,
			NULL, 0, pResult, NULL);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_aes_gctr_decrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv, OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[3] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = pResult}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 3);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_decrypt(pcrypto_adapter, CIPHER_TYPE_AES_GCTR, message, msglen, iv, 0,
			NULL, 0, pResult, NULL);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

// AES-GCM

int hal_crypto_aes_gcm_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if ((keylen != CRYPTO_AES128_KEY_LENGTH) && (keylen != CRYPTO_AES192_KEY_LENGTH) &&
		(keylen != CRYPTO_AES256_KEY_LENGTH)) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[1] = {
		{.buf_addr = key}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 1);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_init(pcrypto_adapter, CIPHER_TYPE_AES_GCM, key, keylen);
	return ret;
}

int hal_crypto_aes_gcm_sk_init(uint8_t key_num, IN const u32 keylen)
{
	int ret;

	ret = hal_crypto_aes_sk_init_core(CIPHER_TYPE_AES_GCM, key_num, keylen);
	return ret;
}

int hal_crypto_aes_gcm_encrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,
	IN const u8 *aad,       IN const u32 aadlen,
	OUT u8 *pResult, OUT u8 *pTag)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if ((u32)(aad) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (aadlen > CRYPTO_MAX_AAD_LENGTH) {
		return _ERRNO_CRYPTO_AAD_OutRange;
	}
	if (pTag == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[5] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = aad},
			{.buf_addr = pResult},
			{.buf_addr = pTag}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 5);
	}
#endif

	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_encrypt(pcrypto_adapter, CIPHER_TYPE_AES_GCM, message, msglen, iv, 0,
			aad, aadlen, pResult, pTag);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}


int hal_crypto_aes_gcm_decrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,
	IN const u8 *aad,       IN const u32 aadlen,
	OUT u8 *pResult, OUT u8 *pTag)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if ((u32)(aad) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (aadlen > CRYPTO_MAX_AAD_LENGTH) {
		return _ERRNO_CRYPTO_AAD_OutRange;
	}
	if (pTag == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[5] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = aad},
			{.buf_addr = pResult},
			{.buf_addr = pTag}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 5);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_decrypt(pcrypto_adapter, CIPHER_TYPE_AES_GCM, message, msglen, iv, 0,
			aad, aadlen, pResult, pTag);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_des_cbc_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (keylen != CRYPTO_DES_KEY_LENGTH) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_init(pcrypto_adapter, CIPHER_TYPE_DES_CBC, key, keylen);
	return ret;
}

int hal_crypto_des_cbc_encrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 ivlen,
	OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (ivlen != CRYPTO_DES_IV_LENGTH) {
		return _ERRNO_CRYPTO_IV_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_DES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_DES_MSGLEN_NOT_8Byte_Aligned;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_encrypt(pcrypto_adapter, CIPHER_TYPE_DES_CBC, message, msglen, iv, ivlen,
			NULL, 0, pResult, NULL);

#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_des_cbc_decrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 ivlen,
	OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (ivlen != CRYPTO_DES_IV_LENGTH) {
		return _ERRNO_CRYPTO_IV_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_DES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_DES_MSGLEN_NOT_8Byte_Aligned;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_decrypt(pcrypto_adapter, CIPHER_TYPE_DES_CBC, message, msglen, iv, ivlen,
			NULL, 0, pResult, NULL);

#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

// DES-ECB

int hal_crypto_des_ecb_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (keylen != CRYPTO_DES_KEY_LENGTH) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_init(pcrypto_adapter, CIPHER_TYPE_DES_ECB, key, keylen);

	return ret;
}

int hal_crypto_des_ecb_encrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 ivlen,
	OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	iv = NULL;
	if (ivlen != 0) {
		return _ERRNO_CRYPTO_IV_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_DES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_DES_MSGLEN_NOT_8Byte_Aligned;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_encrypt(pcrypto_adapter, CIPHER_TYPE_DES_ECB, message, msglen, iv, ivlen,
			NULL, 0, pResult, NULL);

#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_des_ecb_decrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 ivlen,
	OUT u8 *pResult)
{
	int ret;

	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	iv = NULL;
	if (ivlen != 0) {
		return _ERRNO_CRYPTO_IV_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_DES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_DES_MSGLEN_NOT_8Byte_Aligned;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_decrypt(pcrypto_adapter, CIPHER_TYPE_DES_ECB, message, msglen, iv, ivlen,
			NULL, 0, pResult, NULL);

#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

// 3DES-CBC
int hal_crypto_3des_cbc_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (keylen != CRYPTO_3DES_KEY_LENGTH) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_init(pcrypto_adapter, CIPHER_TYPE_3DES_CBC, key, keylen);

	return ret;
}

int hal_crypto_3des_cbc_encrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 ivlen,
	OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (ivlen != CRYPTO_DES_IV_LENGTH) {
		return _ERRNO_CRYPTO_IV_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_DES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_DES_MSGLEN_NOT_8Byte_Aligned;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_encrypt(pcrypto_adapter, CIPHER_TYPE_3DES_CBC, message, msglen, iv, ivlen,
			NULL, 0, pResult, NULL);

#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_3des_cbc_decrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 ivlen,
	OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (ivlen != CRYPTO_DES_IV_LENGTH) {
		return _ERRNO_CRYPTO_IV_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_DES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_DES_MSGLEN_NOT_8Byte_Aligned;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_decrypt(pcrypto_adapter, CIPHER_TYPE_3DES_CBC, message, msglen, iv, ivlen,
			NULL, 0, pResult, NULL);

#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

// 3DES-ECB

int hal_crypto_3des_ecb_init(IN const u8 *key, IN const u32 keylen)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (keylen != CRYPTO_3DES_KEY_LENGTH) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_init(pcrypto_adapter, CIPHER_TYPE_3DES_ECB, key, keylen);

	return ret;
}

int hal_crypto_3des_ecb_encrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 ivlen,
	OUT u8 *pResult)
{
	int ret;

	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	iv = NULL;
	if (ivlen != 0) {
		return _ERRNO_CRYPTO_IV_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_DES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_DES_MSGLEN_NOT_8Byte_Aligned;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_encrypt(pcrypto_adapter, CIPHER_TYPE_3DES_ECB, message, msglen, iv, ivlen,
			NULL, 0, pResult, NULL);

#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_3des_ecb_decrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 ivlen,
	OUT u8 *pResult)
{
	int ret;

	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	iv = NULL;
	if (ivlen != 0) {
		return _ERRNO_CRYPTO_IV_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_DES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_DES_MSGLEN_NOT_8Byte_Aligned;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_cipher_decrypt(pcrypto_adapter, CIPHER_TYPE_3DES_ECB, message, msglen, iv, ivlen,
			NULL, 0, pResult, NULL);

#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}


uint32_t hal_crypto_mix_mode_calculate_hash_padding(hal_crypto_adapter_t *pcrypto_adapter,
		IN const u32 auth_type, IN const u32 msglen, IN const u32 aadlen)
{
	uint64_t hash_total_len;
	uint32_t low, high, last, padn, hash_padlen;
	uint8_t hash_msglen[8] = {0x0};

	/*
	 * Calculate hash padding values and size
	 */
	memset((void *)hash_padding, 0x0, sizeof(hash_padding));
	if (pcrypto_adapter->isHMAC) {
		hash_total_len = (msglen + aadlen) + 64;
		//DBG_CRYPTO_INFO("hmac add 64bytes key pad\r\n");
	} else {
		hash_total_len = (msglen + aadlen);
	}

	/* Note:
	 * AND 0x3F -> Know the last data size which need to be calculated.
	 * Use the last data size to calculate how many bytes of padding.
	 * Because there're reserved 8 bytes to represent total msglen in bits, so (64 - 8) = 56 or (64*2 - 8) = 120
	 */
	last = ((msglen + aadlen) & 0x3F);
	padn = (last < 56) ? (56 - last) : (120 - last);
	memcpy((void *)hash_padding, (void *)mix_mode_hash_padding, padn);

	/* Total hash msglen use 8bytes to represent!!!seperate low 4 bytes, high 4 bytes!!
	 * Note:
	 * Because when store value to low, hash_total_len[31:0] need to left shift 3 bits(means 1byte to 8bits)
	 * so if there are values in b'31:29, the 32bits low value can't store over 32 bits, so leave b'31:29 of
	 * hash_total_len[31:0] to high value.
	 */
	high = ((hash_total_len & (0xFFFFFFFF)) >> 29)
		   | (((hash_total_len >> 32) & (0xFFFFFFFF)) <<  3);
	low  = ((hash_total_len & (0xFFFFFFFF)) <<  3);
	if ((AUTH_TYPE_MD5 == auth_type) || (AUTH_TYPE_HMAC_MD5 == auth_type)) {
		HASH_PADDING_PUT_UINT32_LE(low,  hash_msglen, 0);
		HASH_PADDING_PUT_UINT32_LE(high, hash_msglen, 4);
	} else {
		HASH_PADDING_PUT_UINT32_BE(high, hash_msglen, 0);
		HASH_PADDING_PUT_UINT32_BE(low, hash_msglen, 4);
	}
	memcpy((void *)(hash_padding + padn), (void *)hash_msglen, 8);
	hash_padlen = (padn + 8);

	return hash_padlen;
}

uint32_t hal_crypto_mix_mode_calculate_enc_padding(hal_crypto_adapter_t *pcrypto_adapter,
		IN const u32 auth_type, IN const u32 msglen)
{
	uint32_t new_enc_last_data_size = 0, enc_padlen = 0, mac_len = 0;

	/*
	 * Calculate enc padding size & set values
	 */
	if ((AUTH_TYPE_MD5 == auth_type) || (AUTH_TYPE_HMAC_MD5 == auth_type)) {
		mac_len = CRYPTO_MD5_DIGEST_LENGTH;
	} else if ((AUTH_TYPE_SHA1 == auth_type) || (AUTH_TYPE_HMAC_SHA1 == auth_type)) {
		mac_len = CRYPTO_SHA1_DIGEST_LENGTH;
	} else if ((AUTH_TYPE_SHA2_224_ALL == auth_type) || (AUTH_TYPE_HMAC_SHA2_224_ALL == auth_type)) {
		mac_len = SHA2_224;
	} else if ((AUTH_TYPE_SHA2_256_ALL == auth_type) || (AUTH_TYPE_HMAC_SHA2_256_ALL == auth_type)) {
		mac_len = SHA2_256;
	}
	// AES block size is 16bytes
	// Even if (plaintext msglen + mac_len) is cipher aligned, it still needs to pad a pair data of cipher aligned
	// because of crypto engine degisn.
	new_enc_last_data_size = (msglen + mac_len) % 16;
	enc_padlen = (16 - new_enc_last_data_size) % 16;
	if (enc_padlen == 0) {
		enc_padlen = 16;
	}

	memset((void *)enc_padding, 0x0F, sizeof(enc_padding));

	return enc_padlen;
}

int hal_crypto_mix_mode_init(IN const u32 cipher_type, IN const u32 auth_type,
							 IN const u8 *cipher_key, IN const u32 cipher_keylen,
							 IN const u8 *auth_key, IN const u32 auth_keylen)
{
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}

	if (cipher_key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(cipher_key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	// Ameba_zii only support AES algorithm
	if ((cipher_keylen != CRYPTO_AES128_KEY_LENGTH) && (cipher_keylen != CRYPTO_AES192_KEY_LENGTH) &&
		(cipher_keylen != CRYPTO_AES256_KEY_LENGTH)) {
		return _ERRNO_CRYPTO_KEY_OutRange;
	}
	if (auth_keylen != 0) {
		if (auth_keylen > CRYPTO_AUTH_PADDING) {
			return _ERRNO_CRYPTO_KEY_OutRange;
		}
		if (auth_key == NULL) {
			return _ERRNO_CRYPTO_NULL_POINTER;
		}
		if ((u32)(auth_key) & 0x1F) {
			return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
		}
	}
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	psram_check = 0;
	crypto_buf_addr_t crypto_buf_list[2] = {
		{.buf_addr = cipher_key},
		{.buf_addr = auth_key}
	};
	exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 2);
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_mix_mode_init(pcrypto_adapter, cipher_type, auth_type, cipher_key, cipher_keylen,
			auth_key, auth_keylen);

	return ret;
}

int hal_crypto_mix_ssh_encrypt(IN const u32 cipher_type,
							   IN const u8 *message, IN const u32 msglen,
							   IN const u8 *iv, IN const u32 ivlen,
							   IN const u8 *aad, IN const u32 aadlen,
							   IN const u32 auth_type,
							   OUT u8 *pResult, OUT u8 *pTag)
{
	int ret;
	uint32_t hash_padlen = 0;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv != NULL) {
		if ((u32)(iv) & 0x1F) {
			return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
		}
	}
	if ((u32)(aad) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (aadlen > CRYPTO_MAX_AAD_LENGTH) {
		return _ERRNO_CRYPTO_AAD_OutRange;
	}
	if (pTag == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}
	hash_padlen = hal_crypto_mix_mode_calculate_hash_padding(pcrypto_adapter, auth_type, msglen, aadlen);

#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[5] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = aad},
			{.buf_addr = pResult},
			{.buf_addr = pTag}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 5);
	}
#endif
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_mix_mode_process(pcrypto_adapter, CRYPTO_MIX_MODE_SSH_ENC,
			cipher_type, message, msglen, iv, ivlen,
			aad, aadlen, auth_type, (const u8 *)hash_padding, hash_padlen,
			NULL, 0, pResult, pTag);



#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_mix_ssh_decrypt(IN const u32 cipher_type,
							   IN const u8 *message, IN const u32 msglen,
							   IN const u8 *iv, IN const u32 ivlen,
							   IN const u8 *aad, IN const u32 aadlen,
							   IN const u32 auth_type,
							   OUT u8 *pResult, OUT u8 *pTag)
{
	int ret;
	uint32_t hash_padlen = 0;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv != NULL) {
		if ((u32)(iv) & 0x1F) {
			return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
		}
	}
	if ((u32)(aad) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (aadlen > CRYPTO_MAX_AAD_LENGTH) {
		return _ERRNO_CRYPTO_AAD_OutRange;
	}
	if (pTag == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}

	hash_padlen = hal_crypto_mix_mode_calculate_hash_padding(pcrypto_adapter, auth_type, msglen, aadlen);
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[5] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = aad},
			{.buf_addr = pResult},
			{.buf_addr = pTag}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 5);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_mix_mode_process(pcrypto_adapter, CRYPTO_MIX_MODE_SSH_DEC,
			cipher_type, message, msglen, iv, ivlen,
			aad, aadlen, auth_type, (const u8 *)hash_padding, hash_padlen,
			NULL, 0, pResult, pTag);

#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_mix_esp_encrypt(IN const u32 cipher_type,
							   IN const u8 *message, IN const u32 msglen,
							   IN const u8 *iv, IN const u32 ivlen,
							   IN const u8 *aad, IN const u32 aadlen,
							   IN const u32 auth_type,
							   OUT u8 *pResult, OUT u8 *pTag)
{
	int ret;
	uint32_t hash_padlen = 0;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv != NULL) {
		if ((u32)(iv) & 0x1F) {
			return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
		}
	}
	if ((u32)(aad) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (aadlen > CRYPTO_MAX_AAD_LENGTH) {
		return _ERRNO_CRYPTO_AAD_OutRange;
	}
	if (pTag == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}

	hash_padlen = hal_crypto_mix_mode_calculate_hash_padding(pcrypto_adapter, auth_type, msglen, aadlen);
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[5] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = aad},
			{.buf_addr = pResult},
			{.buf_addr = pTag}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 5);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_mix_mode_process(pcrypto_adapter, CRYPTO_MIX_MODE_ESP_ENC,
			cipher_type, message, msglen, iv, ivlen,
			aad, aadlen, auth_type, (const u8 *)hash_padding, hash_padlen,
			NULL, 0, pResult, pTag);



#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_mix_esp_decrypt(IN const u32 cipher_type,
							   IN const u8 *message, IN const u32 msglen,
							   IN const u8 *iv, IN const u32 ivlen,
							   IN const u8 *aad, IN const u32 aadlen,
							   IN const u32 auth_type,
							   OUT u8 *pResult, OUT u8 *pTag)
{
	int ret;
	uint32_t hash_padlen = 0;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv != NULL) {
		if ((u32)(iv) & 0x1F) {
			return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
		}
	}
	if ((u32)(aad) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (aadlen > CRYPTO_MAX_AAD_LENGTH) {
		return _ERRNO_CRYPTO_AAD_OutRange;
	}
	if (pTag == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}

	hash_padlen = hal_crypto_mix_mode_calculate_hash_padding(pcrypto_adapter, auth_type, msglen, aadlen);
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[5] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = aad},
			{.buf_addr = pResult},
			{.buf_addr = pTag}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 5);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_mix_mode_process(pcrypto_adapter, CRYPTO_MIX_MODE_ESP_DEC,
			cipher_type, message, msglen, iv, ivlen,
			aad, aadlen, auth_type, (const u8 *)hash_padding, hash_padlen,
			NULL, 0, pResult, pTag);


#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_mix_ssl_tls_encrypt(IN const u32 cipher_type,
								   IN const u8 *message, IN const u32 msglen,
								   IN const u8 *iv, IN const u32 ivlen,
								   IN const u8 *aad, IN const u32 aadlen,
								   IN const u32 auth_type,
								   OUT u8 *pResult)
{
	int ret;
	u8 *pTag = NULL;
	uint32_t hash_padlen = 0, enc_padlen = 0;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv != NULL) {
		if ((u32)(iv) & 0x1F) {
			return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
		}
	}
	if ((u32)(aad) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (aadlen > CRYPTO_MAX_AAD_LENGTH) {
		return _ERRNO_CRYPTO_AAD_OutRange;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_AES_IV_LENGTH) != 0) {
		return _ERRNO_CRYPTO_AES_MSGLEN_NOT_16Byte_Aligned;
	}

	hash_padlen = hal_crypto_mix_mode_calculate_hash_padding(pcrypto_adapter, auth_type, msglen, aadlen);

	enc_padlen  = hal_crypto_mix_mode_calculate_enc_padding(pcrypto_adapter, auth_type, msglen);
#if defined (CONFIG_EXRAM_PSRAM_EN) && (CONFIG_EXRAM_PSRAM_EN == 1)
	if (psram_check == 0) {
		crypto_buf_addr_t crypto_buf_list[4] = {
			{.buf_addr = message},
			{.buf_addr = iv},
			{.buf_addr = aad},
			{.buf_addr = pResult}
		};
		exram_psram_addr_check(pcrypto_adapter, &crypto_buf_list[0], 4);
	}
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_mix_mode_process(pcrypto_adapter, CRYPTO_MIX_MODE_SSL_TLS_ENC,
			cipher_type, message, msglen, iv, ivlen,
			aad, aadlen, auth_type, (const u8 *)hash_padding, hash_padlen,
			(const u8 *)enc_padding, enc_padlen, pResult, pTag);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}




// poly1305
int hal_crypto_poly1305(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *key,
	OUT u8 *pDigest)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_poly1305(pcrypto_adapter, message, msglen, key, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_poly1305_init(IN const u8 *key)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_poly1305_init(pcrypto_adapter, key);
	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

int hal_crypto_poly1305_process(
	IN const u8 *message, IN const u32 msglen,
	OUT u8 *pDigest)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pDigest == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_poly1305_process(pcrypto_adapter, message, msglen, pDigest);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_chacha_init(IN const u8 *key)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_chacha_init(pcrypto_adapter, key);
	return ret;
}

int hal_crypto_chacha_encrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 count,
	OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_CHACHA_MSG_ALIGN) != 0) {
		return _ERRNO_CRYPTO_CHACHA_MSGLEN_NOT_16Byte_Aligned;
	}

	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_chacha_encrypt(pcrypto_adapter, message, msglen, iv, count, pResult);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_chacha_decrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,        IN const u32 count,
	OUT u8 *pResult)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_CHACHA_MSG_ALIGN) != 0) {
		return _ERRNO_CRYPTO_CHACHA_MSGLEN_NOT_16Byte_Aligned;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_chacha_decrypt(pcrypto_adapter, message, msglen, iv, count, pResult);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_chacha_poly1305_init(IN const u8 *key)
{
	int ret;
#if CRYPTO_THREAD_MODE
	critical_enter();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(key) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_chacha_poly1305_init(pcrypto_adapter, key);
	return ret;
}

int hal_crypto_chacha_poly1305_encrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,
	IN const u8 *aad,   IN const u32 aadlen,
	OUT u8 *pResult, OUT u8 *pTag)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if ((u32)(aad) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (aadlen > CRYPTO_MAX_AAD_LENGTH) {
		return _ERRNO_CRYPTO_AAD_OutRange;
	}
	if (pTag == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_CHACHA_MSG_ALIGN) != 0) {
		return _ERRNO_CRYPTO_CHACHA_MSGLEN_NOT_16Byte_Aligned;
	}

	ret =  HAL_CRYPTO_FUNC_STUBS.hal_crypto_chacha_poly1305_encrypt(pcrypto_adapter, message, msglen, iv, aad, aadlen, pResult, pTag);
#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_chacha_poly1305_decrypt(
	IN const u8 *message,   IN const u32 msglen,
	IN const u8 *iv,
	IN const u8 *aad,   IN const u32 aadlen,
	OUT u8 *pResult, OUT u8 *pTag)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (iv == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if ((u32)(iv) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if ((u32)(aad) & 0x1F) {
		return _ERRNO_CRYPTO_ADDR_NOT_32Byte_Aligned;
	}
	if (aadlen > CRYPTO_MAX_AAD_LENGTH) {
		return _ERRNO_CRYPTO_AAD_OutRange;
	}
	if (pTag == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (pResult == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRYPTO_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	if ((msglen % CRYPTO_CHACHA_MSG_ALIGN) != 0) {
		return _ERRNO_CRYPTO_CHACHA_MSGLEN_NOT_16Byte_Aligned;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_chacha_poly1305_decrypt(pcrypto_adapter, message, msglen, iv, aad, aadlen, pResult, pTag);

#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

#if IS_CUT_TEST(CONFIG_CHIP_VER)
int hal_crypto_key_storage_writekey(uint8_t *key, uint8_t keylen, uint8_t key_num)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}

	//ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_key_storage_writekey(pcrypto_adapter, key, keylen, key_num);
	return ret;
}

int hal_crypto_key_storage_writeback(uint8_t key_num, bool _IsWriteback)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}

	//ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_key_storage_writeback(pcrypto_adapter, key_num, _IsWriteback);
	return ret;
}

int hal_crypto_key_storage_securekey(uint8_t key_num, bool _UseKey)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}

	//ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_key_storage_securekey(pcrypto_adapter, key_num, _UseKey);
	return ret;
}
#else

int hal_crypto_key_storage_securekey(uint8_t key_num, bool _UseKey)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_key_storage_securekey(pcrypto_adapter, key_num, _UseKey);
	if (SUCCESS == ret) {
		if (DISABLE == sk_used) {
			sk_used = ENABLE;
		}
	}
	return ret;
}

int hal_crypto_key_storage_writeback(uint8_t key_num, bool _IsWriteback)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_key_storage_writeback(pcrypto_adapter, key_num, _IsWriteback);
	if (SUCCESS == ret) {
		if (DISABLE == sk_used) {
			sk_used = ENABLE;
		}
	}
	return ret;
}

int hal_crypto_key_storage_writekey(uint8_t *key, uint8_t keylen, uint8_t key_num)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (key == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_key_storage_writekey(pcrypto_adapter, key, keylen, key_num);
	if (SUCCESS == ret) {
		if (DISABLE == sk_used) {
			sk_used = ENABLE;
		}
	}
	return ret;
}

int hal_crypto_key_storage_lock(uint8_t key_num, bool _Lock)
{
	int ret;
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_key_storage_lock(pcrypto_adapter, key_num);
	if (SUCCESS == ret) {
		if (DISABLE == sk_used) {
			sk_used = ENABLE;
		}
	}
	return ret;
}
#endif

//#if CRC_ROM_CTRL_RDY

//#if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE==1)
#if !defined(CONFIG_BUILD_NONSECURE)
//crc
int hal_crypto_crc32_cmd(IN const u8 *message, IN const u32 msglen, OUT u32 *pCrc)
{
#if CRYPTO_THREAD_MODE
	osThreadId curID = osThreadGetId();
#endif

	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	int ret = SUCCESS;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pCrc == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRC_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}

#if CRYPTO_THREAD_MODE
	critical_enter();
	g_crc_thread_id = curID;
#else
	crc_done = 0;
#endif

	//DBG_CRYPTO_INFO("start crc32 HW\r\n");
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_crc32_cmd(pcrypto_adapter, message, msglen);

	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
		return ret;
	}

	/*
	 * Doesn't need to wait crc_done or signal, because of using polling way
	 ***/

	*pCrc = HAL_CRYPTO_FUNC_STUBS.hal_crypto_crc_get_result(pcrypto_adapter);

#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}


int hal_crypto_crc_setting(int order, unsigned long polynom,
						   unsigned long crcinit, unsigned long crcxor, int refin, int refout)
{
#if 0
	osThreadId curID = osThreadGetId();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	int ret = SUCCESS;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}

#if 0
	critical_enter();
	g_crc_thread_id = curID;
#else
	crc_done = 0;
#endif

	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_crc_setting(pcrypto_adapter, order, polynom, crcinit, crcxor, refin, refout);



	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
	}
	return ret;
}

//#if 1

int hal_crypto_crc_cmd(IN const u8 *message, IN const u32 msglen, OUT u32 *pCrc)
{
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;
	int ret = SUCCESS;

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pCrc == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRC_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}

	(void)(pcrypto_adapter);
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_crc_cmd(pcrypto_adapter, message, msglen);

	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
		return ret;
	}
	/*
	 * Doesn't need to wait crc_done or signal, because of using polling way
	 ***/

	*pCrc = HAL_CRYPTO_FUNC_STUBS.hal_crypto_crc_get_result(pcrypto_adapter);

#if CRYPTO_THREAD_MODE
	critical_leave();
#endif

	return ret;
}

//#else

int hal_crypto_crc_dma(IN const u8 *message, IN const u32 msglen, OUT u32 *pCrc)
{
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;
	int ret = SUCCESS;
	uint32_t loopWait;
	volatile uint32_t crcstat_err;

	loopWait = 1000000;/* hope long enough */

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pCrc == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRC_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}
	(void)(pcrypto_adapter);
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	ret = hal_rtl_crypto_crc_dma_patch(pcrypto_adapter, message, msglen);
#else
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_crc_dma(pcrypto_adapter, message, msglen);
#endif

	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
		return ret;
	}

	//DBG_CRYPTO_INFO("wait\r\n");
#if CRYPTO_THREAD_MODE
	{
		osEvent evt;

		//DBG_CRYPTO_INFO("wait for signal , curID: 0x%x\r\n", curID);
		evt = osSignalWait(CRYPTO_SIGNAL, osWaitForever); // wait for 100 ms

		if ((evt.status != osOK) && (evt.status != osEventSignal)) {
			DBG_CRYPTO_ERR("osSignalWait failed, evt.status = 0x%x \r\n", evt.status);
			return -1;
		}
	}
#else
	if (pcrypto_adapter->isIntMode) {
		//while ( crc_done == 0 );
		//TODO: can add some Delay / and loops limitation
		while (crc_done == 0) {
			loopWait--;
			if (loopWait == 0) {
				crcstat_err = (CRYPTO_MODULE->crc_stat_reg);
				DBG_CRYPTO_ERR("CRC interrupt doesn't arrive.Wait Timeout crc status =0x%08x\r\n", crcstat_err);
				return FAIL; /* error occurs */
			}
		}
	}
#endif

	*pCrc = HAL_CRYPTO_FUNC_STUBS.hal_crypto_crc_get_result(pcrypto_adapter);

#if CRYPTO_THREAD_MODE
	critical_leave();
#endif

	return ret;
}

int hal_crypto_crc32_dma(IN const u8 *message, IN const u32 msglen, OUT u32 *pCrc)
{
#if CRYPTO_THREAD_MODE
	osThreadId curID = osThreadGetId();
#endif
	hal_crypto_adapter_t *pcrypto_adapter = &HAL_CRYPTO_ADAPTER;

	int ret = SUCCESS;
	uint32_t loopWait;
	volatile uint32_t crcstat_err;

	loopWait = 10000;/* hope long enough */

	if (pcrypto_adapter->isInit != _TRUE) {
		return _ERRNO_CRYPTO_ENGINE_NOT_INIT; // not init yet
	}
	if (pCrc == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (message == NULL) {
		return _ERRNO_CRYPTO_NULL_POINTER;
	}
	if (msglen == 0) {
		return 0;
	}
	if (msglen > CRC_MAX_MSG_LENGTH) {
		return _ERRNO_CRYPTO_MSG_OutRange;
	}

#if CRYPTO_THREAD_MODE
	critical_enter();
	g_crc_thread_id = curID;
#else
	crc_done = 0;
#endif

	//DBG_CRYPTO_INFO("start crc32 HW\r\n");
	ret = HAL_CRYPTO_FUNC_STUBS.hal_crypto_crc32_dma(pcrypto_adapter, message, msglen);

	if (ret != SUCCESS) {
#if CRYPTO_THREAD_MODE
		critical_leave();
#endif
		return ret;
	}

	//DBG_CRYPTO_INFO("wait\r\n");
#if CRYPTO_THREAD_MODE
	{
		osEvent evt;

		//DBG_CRYPTO_INFO("wait for signal , curID: 0x%x\r\n", curID);
		evt = osSignalWait(CRYPTO_SIGNAL, osWaitForever); // wait for 100 ms

		if ((evt.status != osOK) && (evt.status != osEventSignal)) {
			DBG_CRYPTO_ERR("osSignalWait failed, evt.status = 0x%x \r\n", evt.status);
			return -1;
		}
	}
#else
	if (pcrypto_adapter->isIntMode) {
		//while ( crc_done == 0 );
		//TODO: can add some Delay / and loops limitation
		while (crc_done == 0) {
			loopWait--;
			if (loopWait == 0) {
				crcstat_err = (CRYPTO_MODULE->crc_stat_reg);
				DBG_CRYPTO_ERR("CRC interrupt doesn't arrive.Wait Timeout crc status =0x%08x\r\n", crcstat_err);
				return FAIL; /* error occurs */
			}
		}
	}
#endif

	*pCrc = HAL_CRYPTO_FUNC_STUBS.hal_crypto_crc_get_result(pcrypto_adapter);


#if CRYPTO_THREAD_MODE
	critical_leave();
#endif
	return ret;
}

int hal_crypto_crc_division(int order, unsigned long polynom,
							unsigned long crcinit, unsigned long crcxor, int refin, int refout,
							IN uint8_t *message, IN uint32_t msglen, OUT uint32_t *Result)
{
	uint8_t *nextmessage;
	uint32_t remain, process_msglen, proceeded_CRC_init = crcinit, tmp_digest = 0x0;
	unsigned long tmp_crcxor;
	int tmp_refout;
	int ret = SUCCESS;
	remain = msglen;
	nextmessage = message;
	while (remain > 0) {
		if (remain <= CRC_MAX_MSG_LENGTH) {
			process_msglen = remain;
			tmp_crcxor = crcxor;
			tmp_refout = refout;
		} else {
			process_msglen = CRC_MAX_MSG_LENGTH;
			tmp_crcxor = 0;
			tmp_refout = 0;
		}
		ret = hal_crypto_crc_setting(order, polynom, proceeded_CRC_init, tmp_crcxor, refin, tmp_refout);
		if (ret != SUCCESS) {
			DBG_CRYPTO_ERR("crc set Error %x, remain size = %d\r\n", ret, remain);
			goto hal_crypto_crc_division_end;
		}

		ret = hal_crypto_crc_dma((uint8_t *)nextmessage, process_msglen, &tmp_digest);
		if (ret != SUCCESS) {
			DBG_CRYPTO_ERR("crc dma Error %x, remain size = %d\r\n", ret, remain);
			goto hal_crypto_crc_division_end;
		}
		remain      -= process_msglen;
		nextmessage += process_msglen;
		proceeded_CRC_init = tmp_digest;
	}
hal_crypto_crc_division_end:
	*Result = tmp_digest;
	return ret;
}

int hal_crypto_crc_division_core(const uint8_t op_crc_type, IN uint8_t *message, IN uint32_t msglen, OUT uint32_t *Result)
{
	int ret = SUCCESS;
	int order;
	unsigned long polynom, crcinit, crcxor;
	int refin, refout;
	switch (op_crc_type) {
	case CRYPTO_TYPE_CRC32:
		order = 32;
		polynom = 0x4c11db7;
		crcinit = 0xffffffff;
		crcxor = 0xffffffff;
		refin = 1;
		refout = 1;
		break;
	case CRYPTO_TYPE_CRC16:
		order = 16;
		polynom = 0x8005;
		crcinit = 0;
		crcxor = 0;
		refin = 1;
		refout = 1;
		break;
	case CRYPTO_TYPE_CRC_CCITT:
		order = 16;
		polynom = 0x1021;
		crcinit = 0xFFFF;
		crcxor = 0;
		refin = 0;
		refout = 0;
		break;
	case CRYPTO_TYPE_CRC_XMODEM:
		order = 16;
		polynom = 0x1021;
		crcinit = 0;
		crcxor = 0;
		refin = 0;
		refout = 0;
		break;
	case CRYPTO_TYPE_CRC12:
		order = 12;
		polynom = 0x80f;
		crcinit = 0;
		crcxor = 0;
		refin = 0;
		refout = 0;
		break;
	case CRYPTO_TYPE_CRC10:
		order = 10;
		polynom = 0x233;
		crcinit = 0;
		crcxor = 0;
		refin = 0;
		refout = 0;
		break;
	case CRYPTO_TYPE_CRC8:
		order = 8;
		polynom = 0x07;
		crcinit = 0;
		crcxor = 0;
		refin = 0;
		refout = 0;
		break;
	default:
		// Using CRC32
		order = 32;
		polynom = 0x4c11db7;
		crcinit = 0xffffffff;
		crcxor = 0xffffffff;
		refin = 1;
		refout = 1;
		break;
	}
	ret = hal_crypto_crc_division(order, polynom, crcinit, crcxor, refin, refout, message, msglen, Result);
	return ret;
}

int hal_crypto_crc32_division(IN uint8_t *message, IN uint32_t msglen, OUT uint32_t *Result)
{
	return (hal_crypto_crc_division_core(CRYPTO_TYPE_CRC32, message, msglen, Result));
}

int hal_crypto_crc16_division(IN uint8_t *message, IN uint32_t msglen, OUT uint32_t *Result)
{
	return (hal_crypto_crc_division_core(CRYPTO_TYPE_CRC16, message, msglen, Result));
}
#else
// NON-Secure
int hal_crypto_crc32_cmd(IN const u8 *message, IN const u32 msglen, OUT u32 *pCrc)
{
	return (hal_crypto_crc32_cmd_nsc(message, msglen, pCrc));
}

int hal_crypto_crc32_dma(IN const u8 *message, IN const u32 msglen, OUT u32 *pCrc)
{
	return (hal_crypto_crc32_dma_nsc(message, msglen, pCrc));
}

int hal_crypto_crc32_division(IN uint8_t *message, IN uint32_t msglen, OUT uint32_t *Result)
{
	return (hal_crypto_crc_division_core(CRYPTO_TYPE_CRC32, message, msglen, Result));
}

int hal_crypto_crc16_division(IN uint8_t *message, IN uint32_t msglen, OUT uint32_t *Result)
{
	return (hal_crypto_crc_division_core(CRYPTO_TYPE_CRC16, message, msglen, Result));
}

int hal_crypto_crc_division_core(const uint8_t op_crc_type, IN uint8_t *message, IN uint32_t msglen, OUT uint32_t *Result)
{
	return (hal_crypto_crc_division_core_nsc(op_crc_type, message, msglen, Result));
}

#endif
#endif  // end of "#if CONFIG_CRYPTO_EN"
