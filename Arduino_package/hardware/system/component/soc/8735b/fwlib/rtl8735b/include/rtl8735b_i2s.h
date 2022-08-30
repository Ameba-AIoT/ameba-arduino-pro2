/**************************************************************************//**
 * @file     rtl8735bh_i2s.h
 * @brief    The HAL related definition and macros for the I2S device.
 *           Includes Registers and data type definition.
 * @version  V1.00
 * @date     2016-07-20
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

#ifndef _RTL8735BH_I2S_H_
#define _RTL8735BH_I2S_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rtl8735b_i2s_type.h"

/**
 * @addtogroup hs_hal_i2s I2S
 * @{
 */

/**
  \brief  Define the I2S port ID.
*/
enum  i2s_index_sel_e {
	I2s0_Sel    =   0x0,
	I2s1_Sel    =   0x1,
	I2s_Max_Id  =   0x2
};
typedef uint8_t i2s_index_sel_t;


/**
  \brief I2S Device Mode.
*/
enum  i2s_dev_mode_e {
	I2S_MASTER_MODE =   0x0,
	I2S_SLAVE_MODE  =   0x1
};
typedef uint8_t i2s_dev_mode_t;

/**
  \brief I2S Word Length.
*/
enum  i2s_word_len_e {
	I2S_WL_16 = 0x0, //I2S_WL_16
	I2S_WL_24 = 0x1,
	I2S_WL_32 = 0x2
};
typedef uint8_t i2s_word_len_t;

/**
  \brief I2S Bus Transmit/Receive.
*/
enum  i2s_direction_e {
	I2S_ONLY_RX     =   0x0,
	I2S_ONLY_TX     =   0x1,
	I2S_TXRX        =   0x2
};
typedef uint8_t i2s_direction_t;

/**
  \brief I2S Channel Number.
*/
enum  i2s_ch_num_e {
	I2S_CH_STEREO   =   0x0,
	I2S_CH_5p1      =   0x1,
	I2S_CH_MONO     =   0x2
};
typedef uint8_t i2s_ch_num_t;

/**
  \brief I2S Byte Swap.
*/
enum  i2s_byte_swap_e {
	I2S_BIG_INDIAN      =   0x0,
	I2S_LITTLE_INDIAN   =   0x1
};
typedef uint8_t i2s_byte_swap_t;

/**
  \brief I2S Invert SCK.
*/
enum  i2s_sck_inv_e {
	I2S_SCKINV_DISABLE  =   0x0,
	I2S_SCKINV_ENABLE   =   0x1
};
typedef uint8_t i2s_sck_inv_t;

/**
  \brief I2S WS Swap.
*/
enum  i2s_ws_swap_e {
	I2S_LEFT_PHASE      =   0x0,
	I2S_RIGHT_PHASE     =   0x1
};
typedef uint8_t i2s_ws_swap_t;

/**
  \brief I2S Loopback Mode.
*/
enum  i2s_loopback_e {
	I2S_LOOPBACK_DISABLE    =   0x0,
	I2S_LOOPBACK_ENABLE     =   0x1
};
typedef uint8_t i2s_loopback_t;

/**
  \brief I2S Format.
*/
enum  i2s_format_e {
	I2S_FORMAT_I2S          =   0x0,
	I2S_FORMAT_LEFT_JUST    =   0x1,
	I2S_FORMAT_RIGHT_JUST   =   0x2
};
typedef uint8_t i2s_format_t;

/**
  \brief I2S Page Number.
*/
enum  i2s_page_num_e {
	I2S_USELESS_PAGE    =   0x1,
	I2S_2PAGE           =   0x2,
	I2S_3PAGE           =   0x3,
	I2S_4PAGE           =   0x4
};
typedef uint8_t i2s_page_num_t;

/**
  \brief I2S Burst Size.
*/
enum  i2s_burst_size_e {
	I2S_BURST8      =   0x07,
	I2S_BURST12     =   0x0b,
	I2S_BURST16     =   0x0f
};
typedef uint8_t i2s_burst_size_t;

/**
  \brief Send the starting clock edge of data.
*/
enum  i2s_edge_sw_e {
	I2S_NEGATIVE_EDGE   =   0x00,
	I2S_POSITIVE_EDGE   =   0x01
};
typedef uint8_t i2s_edge_sw_t;

/**
  \brief I2S Mute Mode.
*/
enum  i2s_mute_e {
	I2S_MUTE_DISABLE    =   0x0,
	I2S_MUTE_ENABLE     =   0x1
};
typedef uint8_t i2s_mute_t;

/**
  \brief I2S Sample Rate.
*/
enum  i2s_sample_rate_e {
	I2S_SR_8KHZ     =   0x00,
	I2S_SR_12KHZ    =   0x01,
	I2S_SR_16KHZ    =   0x02,
	I2S_SR_24KHZ    =   0x03,
	I2S_SR_32KHZ    =   0x04,
	I2S_SR_48KHZ    =   0x05,
	I2S_SR_64KHZ    =   0x06,
	I2S_SR_96KHZ    =   0x07,
	I2S_SR_192KHZ   =   0x08,
	I2S_SR_384KHZ   =   0x09,
	I2S_SR_7p35KHZ  =   0x10,
	I2S_SR_11p025KHZ =   0x11,
	I2S_SR_14p7KHZ  =   0x12,
	I2S_SR_22p05KHZ =   0x13,
	I2S_SR_29p4KHZ  =   0x14,
	I2S_SR_44p1KHZ  =   0x15,
	I2S_SR_58p8KHZ  =   0x16,
	I2S_SR_88p2KHZ  =   0x17,
	I2S_SR_176p4KHZ =   0x18
};
typedef uint8_t i2s_sample_rate_t;

/**
  \brief I2S TX interrupt mask.
*/
enum  i2s_tx_imr_e {
	I2S_TX_INT_PAGE0_OK  = (1 << 0),
	I2S_TX_INT_PAGE1_OK  = (1 << 1),
	I2S_TX_INT_PAGE2_OK  = (1 << 2),
	I2S_TX_INT_PAGE3_OK  = (1 << 3),
	I2S_TX_INT_PAGE0_UNA = (1 << 4),
	I2S_TX_INT_PAGE1_UNA = (1 << 5),
	I2S_TX_INT_PAGE2_UNA = (1 << 6),
	I2S_TX_INT_PAGE3_UNA = (1 << 7),
	I2S_TX_INT_EMPTY     = (1 << 8)
};
typedef uint32_t i2s_tx_imr_t;

/**
  \brief I2S RX interrupt mask.
*/
enum  i2s_rx_imr_e {
	I2S_RX_INT_PAGE0_OK  = (1 << 0),
	I2S_RX_INT_PAGE1_OK  = (1 << 1),
	I2S_RX_INT_PAGE2_OK  = (1 << 2),
	I2S_RX_INT_PAGE3_OK  = (1 << 3),
	I2S_RX_INT_PAGE0_UNA = (1 << 4),
	I2S_RX_INT_PAGE1_UNA = (1 << 5),
	I2S_RX_INT_PAGE2_UNA = (1 << 6),
	I2S_RX_INT_PAGE3_UNA = (1 << 7),
	I2s_RX_INT_FULL      = (1 << 8)
};
typedef uint32_t i2s_rx_imr_t;

/**
  \brief  I2S call back function for the interrupt.
*/
typedef struct hal_i2s_user_cb_s {
	VOID (*tx_ccb)(uint32_t id, char *pbuf);
	u32 tx_cbid;
	VOID (*rx_ccb)(uint32_t id, char *pbuf);
	u32 rx_cbid;
} hal_i2s_user_cb_t, *phal_i2s_user_cb_t;

/**
  \brief  I2S HAL initial data structuret.
*/
typedef struct hal_i2s_init_dat_s {
	i2s_tx_imr_t        i2s_tx_intr_msk;    /*I2S Tx Interrupt Mask*/
	i2s_rx_imr_t        i2s_rx_intr_msk;    /*I2S Rx Interrupt Mask*/

	u32                 i2s_data_byte_cnt;  /*I2S transfer byte count*/

	u8                  *i2s_tx_data;       /*I2S Tx data pointer*/
	u8                  *i2s_rx_data;       /*I2S Rx data pointer*/

	u32                 i2s_tx_intr_clr;    /*I2S Tx Interrupt register to clear */
	u32                 i2s_rx_intr_clr;    /*I2S Rx Interrupt register to clear*/
	u8                  i2s_tx_idx;         /*I2S TX page index */
	u8                  i2s_rx_idx;         /*I2S RX page index */
	u8                  i2s_hw_tx_idx;      /*I2S HW TX page index */
	u8                  i2s_hw_rx_idx;      /*I2S HW RX page index */
} hal_i2s_init_dat_t, *phal_i2s_init_dat_t;

/**
  \brief  The data structure for an I2S port HAL operations.
*/
typedef struct hal_i2s_adapter_s {
	i2s_index_sel_t dev_num;                /*! I2S device number */
	I2S_Type *base_addr;                   /*! The I2S register base address */

	hal_i2s_init_dat_t init_dat;            /*! I2S initial data struct */
	hal_i2s_user_cb_t user_cb;              /*! Pointer to I2S User Callback */

	u32 *ptx_page_list[4];                  /*! The Tx DAM buffer: pointer of each page */
	u32 *prx_page_list[4];                  /*! The Tx DAM buffer: pointer of each page */

	u8 dcache_memory_en;                    /*! check the memory is cache or not  */

	void (*dcache_invalidate_by_addr)(uint32_t *addr, int32_t dsize);   /*! callback function to do the D-cache invalidate  */
	void (*dcache_clean_by_addr)(uint32_t *addr, int32_t dsize);        /*! callback function to do the D-cache clean  */
} hal_i2s_adapter_t, *phal_i2s_adapter_t;

/**
  \brief  The data structure of the default setting.
*/
typedef struct hal_i2s_def_setting_s {
	i2s_burst_size_t    i2s_burst_size;     /*! Burst Size for DMA*/
	i2s_dev_mode_t      i2s_master;         /*! Master or Slave mode*/
	i2s_word_len_t      i2s_word_len;       /*! Word length 16 or 24bits*/
	i2s_ch_num_t        i2s_ch_num;         /*! Channel number mono or stereo*/
	i2s_page_num_t      i2s_page_num;       /*! Page Number 2~4*/
	u16                 i2s_page_size;      /*! Page Size 1~4096 word*/
	i2s_sample_rate_t   i2s_rate;           /*! sample rate*/
	i2s_direction_t     i2s_trx_act;        /*! Conrtol the tx and rx. */
	i2s_byte_swap_t     i2s_byte_swap;      /*! Make the data do the byte switch. */
	i2s_sck_inv_t       i2s_sck_inv;        /*! Invert SCK. */
	i2s_ws_swap_t       i2s_ws_swap;        /*! Control whether the data appear in "right" or "left" phase of WS clock.  */
	i2s_format_t        i2s_format;         /*! Interface format. */
	i2s_loopback_t      i2s_loop_back;      /*! Control the loopback mode. */
	i2s_edge_sw_t       i2s_edge_sw;        /*! Chose to send data at the negative edge or positive edge of SCK. */
	i2s_tx_imr_t        i2s_tx_intr_msk;    /*! Tx Interrupt Mask. */
	i2s_rx_imr_t        i2s_rx_intr_msk;    /*! Rx Interrupt Mask. */
} hal_i2s_def_setting_t, *phal_i2s_def_setting_t;

/**
  \brief  The data structure to handle multiple I2S adapters.
*/
typedef struct hal_i2s_group_adapter_s {
	volatile uint32_t critical_lv;                  /*!< to record I2S HAL enter critical section level */
	hal_i2s_adapter_t *pi2s_adapter[I2s_Max_Id];    /*!< All the I2S adapters of this platform */
	irq_handler_t   irq_fun[I2s_Max_Id];            /*!< the IRQ handler for different I2S adapters */
} hal_i2s_group_adapter_t, *phal_i2s_group_adapter_t;

/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup hs_hal_i2s_rom_func I2S HAL ROM APIs.
 * @{
 */

void hal_rtl_i2s_irq_handler(void *hid);
void hal_rtl_i2s_irq_reg(hal_i2s_adapter_t *pi2s_adapter);
void hal_rtl_i2s_irq_unreg(hal_i2s_adapter_t *pi2s_adapter);
HAL_Status hal_rtl_i2s_en_clk_ctrl(i2s_index_sel_t index_sel, BOOL en);
HAL_Status hal_rtl_i2s_func_ctrl(hal_i2s_adapter_t *pi2s_adapter, BOOL i2s_func_en);
HAL_Status hal_rtl_i2s_init(hal_i2s_adapter_t *pi2s_adapter);
HAL_Status hal_rtl_i2s_deinit(hal_i2s_adapter_t *pi2s_adapter);
void hal_rtl_i2s_enter_critical(void);
void hal_rtl_i2s_exit_critical(void);
void hal_rtl_i2s_set_parameter(hal_i2s_adapter_t *pi2s_adapter, hal_i2s_def_setting_t *psetting);
void hal_rtl_i2s_set_rate(hal_i2s_adapter_t *pi2s_adapter, i2s_sample_rate_t i2s_sample_rate);
void hal_rtl_i2s_set_dma_buf(hal_i2s_adapter_t *pi2s_adapter, u16 i2s_page_size, i2s_page_num_t i2s_page_num);
u8 hal_rtl_i2s_get_tx_page(hal_i2s_adapter_t *pi2s_adapter);
u8 hal_rtl_i2s_get_rx_page(hal_i2s_adapter_t *pi2s_adapter);
void hal_rtl_i2s_page_send(hal_i2s_adapter_t *pi2s_adapter, u8 page_idx);
HAL_Status hal_rtl_i2s_page_recv(hal_i2s_adapter_t *pi2s_adapter);
void hal_rtl_i2s_clear_all_own_bit(hal_i2s_adapter_t *pi2s_adapter);
void hal_rtl_i2s_reset(hal_i2s_adapter_t *pi2s_adapter);
void hal_rtl_i2s_en_ctrl(hal_i2s_adapter_t *pi2s_adapter, BOOL en);
void hal_rtl_i2s_clr_intr(hal_i2s_adapter_t *pi2s_adapter);
void hal_rtl_i2s_clr_all_intr(hal_i2s_adapter_t *pi2s_adapter);
void hal_rtl_i2s_intr_ctrl(hal_i2s_adapter_t *pi2s_adapter, i2s_tx_imr_t i2s_tx_intr_msk, i2s_rx_imr_t i2s_rx_intr_msk);
void hal_rtl_i2s_read_memory_cache_invalidate(hal_i2s_adapter_t *pi2s_adapter);

/**
 *  @brief  Set the word length.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] i2s_word_len The word length.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rtl_i2s_set_word_len(hal_i2s_adapter_t *pi2s_adapter, i2s_word_len_t i2s_word_len)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	pi2s_reg->I2S_CTRL = (pi2s_reg->I2S_CTRL & ~(I2S_MASK_WL)) | ((i2s_word_len << I2S_SHIFT_WL) & I2S_MASK_WL);
}

/**
 *  @brief  Set the channel nunber.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] i2s_ch_num The channel nunber.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rtl_i2s_set_ch_num(hal_i2s_adapter_t *pi2s_adapter, i2s_ch_num_t i2s_ch_num)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	pi2s_reg->I2S_CTRL = (pi2s_reg->I2S_CTRL & ~(I2S_MASK_AUDIO_MONO)) | ((i2s_ch_num << I2S_SHIFT_AUDIO_MONO) & I2S_MASK_AUDIO_MONO);
}

/**
 *  @brief  Set the page nunber.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] i2s_ch_num The page nunber.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rtl_i2s_set_page_num(hal_i2s_adapter_t *pi2s_adapter, i2s_page_num_t i2s_page_num)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	pi2s_reg->I2S_PAGE_SIZE_RATE = (pi2s_reg->I2S_PAGE_SIZE_RATE & ~(I2S_MASK_PAGE_NUM)) | (((i2s_page_num - 1) << I2S_SHIFT_PAGE_NUM) & I2S_MASK_PAGE_NUM);
}

/**
 *  @brief  Set the page size.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] i2s_ch_num The page size.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rtl_i2s_set_page_size(hal_i2s_adapter_t *pi2s_adapter, u16 i2s_page_size)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	pi2s_reg->I2S_PAGE_SIZE_RATE = (pi2s_reg->I2S_PAGE_SIZE_RATE & ~(I2S_MASK_PAGE_SIZE)) | ((i2s_page_size << I2S_SHIFT_PAGE_SIZE) & I2S_MASK_PAGE_SIZE);
}

/**
 *  @brief  Conrtol the tx and rx.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] i2s_trx_act Select the direction of the transmission.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rtl_i2s_set_direction(hal_i2s_adapter_t *pi2s_adapter, i2s_direction_t i2s_trx_act)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	pi2s_reg->I2S_CTRL = (pi2s_reg->I2S_CTRL & ~(I2S_MASK_TX_ACT)) | ((i2s_trx_act << I2S_SHIFT_TX_ACT) & I2S_MASK_TX_ACT);
}

/**
 *  @brief  Conrtol the interface format.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] format Select the interface format.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rtl_i2s_set_format(hal_i2s_adapter_t *pi2s_adapter, i2s_format_t format)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	pi2s_reg->I2S_CTRL = (pi2s_reg->I2S_CTRL & ~(I2S_MASK_FORMAT)) | ((format << I2S_SHIFT_FORMAT) & I2S_MASK_FORMAT);
}

/**
 *  @brief  Set the master or slave mode.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] dev_mode Select the master or slave mode.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rtl_i2s_set_master(hal_i2s_adapter_t *pi2s_adapter, i2s_dev_mode_t dev_mode)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	pi2s_reg->I2S_CTRL = (pi2s_reg->I2S_CTRL & ~(I2S_BIT_SLAVE_MODE)) | ((dev_mode << I2S_SHIFT_SLAVE_MODE) & I2S_BIT_SLAVE_MODE);
}

/**
 *  @brief  Set the I2S burst size.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] burst_size Burst size for DMA.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rtl_i2s_set_lxbus_burst_size(hal_i2s_adapter_t *pi2s_adapter, i2s_burst_size_t burst_size)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	pi2s_reg->I2S_CTRL = (pi2s_reg->I2S_CTRL & ~(I2S_MASK_BURST_SIZE)) | ((burst_size << I2S_SHIFT_BURST_SIZE) & I2S_MASK_BURST_SIZE);
}

/**
 *  @brief  Make the data do the byte switch.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] byte_swap Enable control.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rtl_i2s_set_byte_swap(hal_i2s_adapter_t *pi2s_adapter, i2s_byte_swap_t byte_swap)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	pi2s_reg->I2S_CTRL = (pi2s_reg->I2S_CTRL & ~(I2S_BIT_BYTE_SWAP)) | ((byte_swap << I2S_SHIFT_BYTE_SWAP) & I2S_BIT_BYTE_SWAP);
}

/**
 *  @brief  Invert I2S SCK.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] sck_inv Enable control.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rtl_i2s_set_sck_inv(hal_i2s_adapter_t *pi2s_adapter, i2s_sck_inv_t sck_inv)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	pi2s_reg->I2S_CTRL = (pi2s_reg->I2S_CTRL & ~(I2S_BIT_SCK_SWAP)) | ((sck_inv << I2S_SHIFT_SCK_SWAP) & I2S_BIT_SCK_SWAP);
}

/**
 *  @brief  Control whether the data appear in "right" or "left" phase of WS clock.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] ws_swap Enable control.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rtl_i2s_set_ws_swap(hal_i2s_adapter_t *pi2s_adapter, i2s_ws_swap_t ws_swap)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	pi2s_reg->I2S_CTRL = (pi2s_reg->I2S_CTRL & ~(I2S_BIT_LR_SWAP)) | ((ws_swap << I2S_SHIFT_LR_SWAP) & I2S_BIT_LR_SWAP);
}

/**
 *  @brief Set the I2S loopback mode.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] loopback Enable control.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rtl_i2s_set_loopback(hal_i2s_adapter_t *pi2s_adapter, i2s_loopback_t loopback)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	pi2s_reg->I2S_CTRL = (pi2s_reg->I2S_CTRL & ~(I2S_BIT_LOOP_BACK)) | ((loopback << I2S_SHIFT_LOOP_BACK) & I2S_BIT_LOOP_BACK);
}

/**
 *  @brief Chose to send data at the negative edge or positive edge of SCK.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] edge_sw Select the negative edge or positive edge.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rtl_i2s_set_data_start_edge(hal_i2s_adapter_t *pi2s_adapter, i2s_edge_sw_t edge_sw)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	pi2s_reg->I2S_CTRL = (pi2s_reg->I2S_CTRL & ~(I2S_BIT_EDGE_SW)) | ((edge_sw << I2S_SHIFT_EDGE_SW) & I2S_BIT_EDGE_SW);
}

/**
 *  @brief Control the I2S mute.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] mute Enable control.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_i2s_set_mute(hal_i2s_adapter_t *pi2s_adapter, i2s_mute_t mute)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	pi2s_reg->I2S_CTRL = (pi2s_reg->I2S_CTRL & ~(I2S_BIT_MUTE)) | ((mute << I2S_SHIFT_MUTE) & I2S_BIT_MUTE);
}


/** @} */ /* End of group hs_hal_i2s_rom_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */


/**
  \brief  The data structure of the stubs function for the I2S HAL functions in ROM
*/
typedef struct hal_i2s_func_stubs_s {
	hal_i2s_group_adapter_t *pi2s_group_adapter;
	const uint8_t *pi2s_pin_group;
	void (*hal_i2s_irq_handler)(void *hid);
	void (*hal_i2s_irq_reg)(hal_i2s_adapter_t *pi2s_adapter);
	void (*hal_i2s_irq_unreg)(hal_i2s_adapter_t *pi2s_adapter);
	HAL_Status(*hal_i2s_en)(i2s_index_sel_t index_sel, BOOL en);
	HAL_Status(*hal_i2s_clk_ctrl)(i2s_index_sel_t index_sel, BOOL en);
	HAL_Status(*hal_i2s_mclk_ctrl)(i2s_index_sel_t index_sel, BOOL en);
	HAL_Status(*hal_i2s_rx_pin_ctrl)(i2s_index_sel_t index_sel, BOOL en);
	HAL_Status(*hal_i2s_5p1_pin_ctrl)(i2s_index_sel_t index_sel, BOOL en);
	void (*hal_i2s_app_pin_ctrl)(hal_i2s_adapter_t *pi2s_adapter);
	HAL_Status(*hal_i2s_func_ctrl)(hal_i2s_adapter_t *pi2s_adapter, BOOL i2s_func_en);
	HAL_Status(*hal_i2s_init)(hal_i2s_adapter_t *pi2s_adapter);
	HAL_Status(*hal_i2s_deinit)(hal_i2s_adapter_t *pi2s_adapter);
	void (*hal_i2s_enter_critical)(void);
	void (*hal_i2s_exit_critical)(void);
	void (*hal_i2s_set_parameter)(hal_i2s_adapter_t *pi2s_adapter, hal_i2s_def_setting_t *psetting);
	void (*hal_i2s_set_rate)(hal_i2s_adapter_t *pi2s_adapter, i2s_sample_rate_t i2s_sample_rate);
	void (*hal_i2s_set_dma_buf)(hal_i2s_adapter_t *pi2s_adapter, u16 i2s_page_size, i2s_page_num_t i2s_page_num);
	u8(*hal_i2s_get_tx_page)(hal_i2s_adapter_t *pi2s_adapter);
	u8(*hal_i2s_get_rx_page)(hal_i2s_adapter_t *pi2s_adapter);
	void (*hal_i2s_page_send)(hal_i2s_adapter_t *pi2s_adapter, u8 page_idx);
	HAL_Status(*hal_i2s_page_recv)(hal_i2s_adapter_t *pi2s_adapter);
	void (*hal_i2s_clear_all_own_bit)(hal_i2s_adapter_t *pi2s_adapter);
	void (*hal_i2s_reset)(hal_i2s_adapter_t *pi2s_adapter);
	void (*hal_i2s_reset_and_disable)(hal_i2s_adapter_t *pi2s_adapter);
	void (*hal_i2s_en_ctrl)(hal_i2s_adapter_t *pi2s_adapter, BOOL en);
	void (*hal_i2s_clr_intr)(hal_i2s_adapter_t *pi2s_adapter);
	void (*hal_i2s_clr_all_intr)(hal_i2s_adapter_t *pi2s_adapter);
	void (*hal_i2s_intr_ctrl)(hal_i2s_adapter_t *pi2s_adapter, i2s_tx_imr_t i2s_tx_intr_msk, i2s_rx_imr_t i2s_rx_intr_msk);
	void (*hal_i2s_read_memory_cache_invalidate)(hal_i2s_adapter_t *pi2s_adapter);
	uint32_t reserved[16];  // reserved space for next ROM code version function table extending.
} hal_i2s_func_stubs_t;

/** @} */ /* End of group hs_hal_i2s */

#ifdef __cplusplus
}
#endif

#endif  // #ifndef _RTL8735BH_I2S_H_

