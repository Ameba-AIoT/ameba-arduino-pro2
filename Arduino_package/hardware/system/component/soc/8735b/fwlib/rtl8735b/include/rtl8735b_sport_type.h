#ifndef _RTL8735B_SPORT_TYPE_H_
#define _RTL8735B_SPORT_TYPE_H_

/**************************************************************************//**
 * @defgroup SPORT_SP_TX_FIFO_0
 * @brief  SPORT TX FIFO Register                    (@ 0X000)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_TX_FIFO_0                     0
#define SPORT_MASK_SP_TX_FIFO_0                      ((u32)0xFFFFFFFF << 0)                              /*!<W 0  TX FIFO 0 address */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_CON
 * @brief  SPORT Control Register                    (@ 0X004)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_MCLK_SEL                      30
#define SPORT_MASK_SP_MCLK_SEL                       ((u32)0x00000003 << 30)                             /*!<R/W 0  Select MCLK output 01 and 11: MCLK output = SP_SRC_CLK / 1 00: MCLK output = SP_SRC_CLK / 2 10: MCLK output = SP_SRC_CLK / 4 */
#define SPORT_SHIFT_SP_SEL_I2S_RX_CH                 28
#define SPORT_MASK_SP_SEL_I2S_RX_CH                  ((u32)0x00000003 << 28)                             /*!<R/W 0  Control L and R channel data for RX. 00: L/R 01: R/L 10: L/L 11: R/R Without TDM only */
#define SPORT_SHIFT_SP_SEL_I2S_TX_CH                 26
#define SPORT_MASK_SP_SEL_I2S_TX_CH                  ((u32)0x00000003 << 26)                             /*!<R/W 0  Control L and R channel data for TX. 00: L/R 01: R/L 10: L/L 11: R/R Without TDM only */
#define SPORT_SHIFT_SP_START_RX                      25
#define SPORT_BIT_SP_START_RX                        ((u32)0x00000001 << 25)                             /*!<R/W 0  Start RX. 0: RX is disabled 1: RX is started */
#define SPORT_SHIFT_SP_RX_DISABLE                    24
#define SPORT_BIT_SP_RX_DISABLE                      ((u32)0x00000001 << 24)                             /*!<R/W 1  SPORT RX control. 0: SPORT RX is enabled 1: SPORT RX is disabled */
#define SPORT_SHIFT_SP_RX_LSB_FIRST_0                23
#define SPORT_BIT_SP_RX_LSB_FIRST_0                  ((u32)0x00000001 << 23)                             /*!<R/W 0  MSB or LSB control for RX0. 0: MSB first 1: LSB first */
#define SPORT_SHIFT_SP_TX_LSB_FIRST_0                22
#define SPORT_BIT_SP_TX_LSB_FIRST_0                  ((u32)0x00000001 << 22)                             /*!<R/W 0  MSB or LSB control for TX0. 0: MSB first 1: LSB first */
#define SPORT_SHIFT_SP_TDM_MODE_SEL_RX               20
#define SPORT_MASK_SP_TDM_MODE_SEL_RX                ((u32)0x00000003 << 20)                             /*!<R/W 0  TDM RX channel control 00: Without TDM 01: 4 channels in the TDM mode 10: 6 channels in the TDM mode 11: 8 channels in the TDM mode */
#define SPORT_SHIFT_SP_TDM_MODE_SEL_TX               18
#define SPORT_MASK_SP_TDM_MODE_SEL_TX                ((u32)0x00000003 << 18)                             /*!<R/W 0  TDM TX channel control 00: Without TDM 01: 4 channels in the TDM mode 10: 6 channels in the TDM mode 11: 8 channels in the TDM mode */
#define SPORT_SHIFT_SP_START_TX                      17
#define SPORT_BIT_SP_START_TX                        ((u32)0x00000001 << 17)                             /*!<R/W 0  Start TX. 0: TX is disabled 1: TX is started */
#define SPORT_SHIFT_SP_TX_DISABLE                    16
#define SPORT_BIT_SP_TX_DISABLE                      ((u32)0x00000001 << 16)                             /*!<R/W 1  SPORT TX control. 0: SPORT TX is enabled 1: SPORT TX is disabled */
#define SPORT_SHIFT_SP_I2S_SELF_LPBK_EN              15
#define SPORT_BIT_SP_I2S_SELF_LPBK_EN                ((u32)0x00000001 << 15)                             /*!<R/W 0  Internal loopback mode. 0: Internal loopback mode is not enabled 1: Internal loopback mode is enabled */
#define SPORT_SHIFT_SP_DATA_LEN_SEL_TX_0             12
#define SPORT_MASK_SP_DATA_LEN_SEL_TX_0              ((u32)0x00000007 << 12)                             /*!<R/W 0  Set the TX0 data length 000: 16 bits 001: 20 bits 010: 24 bits 100: 32 bits Others: Reserved */
#define SPORT_SHIFT_SP_EN_I2S_MONO_TX_0              11
#define SPORT_BIT_SP_EN_I2S_MONO_TX_0                ((u32)0x00000001 << 11)                             /*!<R/W 0  Set mono or stereo for TX0 0: stereo 1: mono */
#define SPORT_SHIFT_SP_INV_I2S_SCLK                  10
#define SPORT_BIT_SP_INV_I2S_SCLK                    ((u32)0x00000001 << 10)                             /*!<R/W 0  Set bclk inverter 0: I2S and PCM sclk is not inverted 1: I2S and PCM sclk is inverted */
#define SPORT_SHIFT_SP_DATA_FORMAT_SEL_TX            8
#define SPORT_MASK_SP_DATA_FORMAT_SEL_TX             ((u32)0x00000003 << 8)                              /*!<R/W 0  Set data format 00: I2S 01: Left Justified 10: PCM mode A 11: PCM mode B */
#define SPORT_SHIFT_SP_MCU_CTL_MODE                  7
#define SPORT_BIT_SP_MCU_CTL_MODE                    ((u32)0x00000001 << 7)                              /*!<R/W 0  Select DMA mode or FIFO mode. 0: Internal DMA mode. 1: FIFO mode. */
#define SPORT_SHIFT_SP_LOOPBACK                      6
#define SPORT_BIT_SP_LOOPBACK                        ((u32)0x00000001 << 6)                              /*!<R/W 0  Self loopback mode. 0: Off. 1: Enable self loopback mode. */
#define SPORT_SHIFT_SP_WCLK_TX_INVERSE               5
#define SPORT_BIT_SP_WCLK_TX_INVERSE                 ((u32)0x00000001 << 5)                              /*!<R/W 0  Inverte I2S/PCM word clock for TX. 0: I2S/PCM word clock is not inverted 1: I2S/PCM word clock is inverted */
#define SPORT_SHIFT_SP_SLAVE_DATA_SEL                4
#define SPORT_BIT_SP_SLAVE_DATA_SEL                  ((u32)0x00000001 << 4)                              /*!<R/W 0  I2S or PCM slave for DATA path. 0: To be not an I2S or PCM slave 1: To be an I2S or PCM slave  */
#define SPORT_SHIFT_SP_SLAVE_CLK_SEL                 3
#define SPORT_BIT_SP_SLAVE_CLK_SEL                   ((u32)0x00000001 << 3)                              /*!<R/W 0  I2S or PCM slave for CLK path. 0: To be not an I2S or PCM slave 1: To be an I2S or PCM slave  */
#define SPORT_SHIFT_SP_RX_INV_I2S_SCLK               2
#define SPORT_BIT_SP_RX_INV_I2S_SCLK                 ((u32)0x00000001 << 2)                              /*!<R/W 0  Sclk to RX path is inverted. 0: sclk to RX path is not inverted. 1: sclk to RX path is inverted. */
#define SPORT_SHIFT_SP_TX_INV_I2S_SCLK               1
#define SPORT_BIT_SP_TX_INV_I2S_SCLK                 ((u32)0x00000001 << 1)                              /*!<R/W 0  Sclk to TX path is inverted. 0: sclk to TX path is not inverted. 1: sclk to TX path is inverted. */
#define SPORT_SHIFT_SP_RESET                         0
#define SPORT_BIT_SP_RESET                           ((u32)0x00000001 << 0)                              /*!<R/W 0  Reset SPORT0 module 0: disable reset 1: reset SPORT0 module. Write 1 first and then write 0. */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_FIFO_EN_CLK_CON
 * @brief   SPORT FIFO Enable and Clock Control Register (@ 0X008)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX_FIFO_1_CH6_7_EN            31
#define SPORT_BIT_SP_RX_FIFO_1_CH6_7_EN              ((u32)0x00000001 << 31)                             /*!<R/W 0  0: Disable 1: Enable the CH6 and CH7 of RX_FIFO_1 */
#define SPORT_SHIFT_SP_RX_FIFO_1_CH4_5_EN            30
#define SPORT_BIT_SP_RX_FIFO_1_CH4_5_EN              ((u32)0x00000001 << 30)                             /*!<R/W 0  0: Disable 1: Enable the CH4 and CH5 of RX_FIFO_1 */
#define SPORT_SHIFT_SP_RX_FIFO_0_CH2_3_EN            29
#define SPORT_BIT_SP_RX_FIFO_0_CH2_3_EN              ((u32)0x00000001 << 29)                             /*!<R/W 0  0: Disable 1: Enable the CH2 and CH3 of RX_FIFO_0 */
#define SPORT_SHIFT_SP_RX_FIFO_0_CH0_1_EN            28
#define SPORT_BIT_SP_RX_FIFO_0_CH0_1_EN              ((u32)0x00000001 << 28)                             /*!<R/W 1  0: Disable 1: Enable the CH0 and CH1 of RX_FIFO_0 */
#define SPORT_SHIFT_SP_TX_FIFO_1_CH6_7_EN            27
#define SPORT_BIT_SP_TX_FIFO_1_CH6_7_EN              ((u32)0x00000001 << 27)                             /*!<R/W 0  0: Disable 1: Enable the CH6 and CH7 of TX_FIFO_1 */
#define SPORT_SHIFT_SP_TX_FIFO_1_CH4_5_EN            26
#define SPORT_BIT_SP_TX_FIFO_1_CH4_5_EN              ((u32)0x00000001 << 26)                             /*!<R/W 0  0: Disable 1: Enable the CH4 and CH5 of TX_FIFO_1 */
#define SPORT_SHIFT_SP_TX_FIFO_0_CH2_3_EN            25
#define SPORT_BIT_SP_TX_FIFO_0_CH2_3_EN              ((u32)0x00000001 << 25)                             /*!<R/W 0  0: Disable 1: Enable the CH2 and CH3 of TX_FIFO_0 */
#define SPORT_SHIFT_SP_TX_FIFO_0_CH0_1_EN            24
#define SPORT_BIT_SP_TX_FIFO_0_CH0_1_EN              ((u32)0x00000001 << 24)                             /*!<R/W 1  0: Disable 1: Enable the CH0 and CH1 of TX_FIFO_0 */
#define SPORT_SHIFT_SP_RX_SNK_LR_SWAP_0              23
#define SPORT_BIT_SP_RX_SNK_LR_SWAP_0                ((u32)0x00000001 << 23)                             /*!<R/W 0  0: Disable 1: Swap L/R audio samples written to the sink memory of RX_FIFO_0 */
#define SPORT_SHIFT_SP_RX_SNK_BYTE_SWAP_0            22
#define SPORT_BIT_SP_RX_SNK_BYTE_SWAP_0              ((u32)0x00000001 << 22)                             /*!<R/W 0  0: Disable 1: Swap H/L bytes written to the sink memory of RX_FIFO_0 */
#define SPORT_SHIFT_SP_TX_SRC_LR_SWAP_0              21
#define SPORT_BIT_SP_TX_SRC_LR_SWAP_0                ((u32)0x00000001 << 21)                             /*!<R/W 0  0: Disable 1: Swap L/R audio samples read from the source memory of TX_FIFO_0 */
#define SPORT_SHIFT_SP_TX_SRC_BYTE_SWAP_0            20
#define SPORT_BIT_SP_TX_SRC_BYTE_SWAP_0              ((u32)0x00000001 << 20)                             /*!<R/W 0  0: Disable 1: Swap H/L bytes read from the source memory of TX_FIFO_0 */
#define SPORT_SHIFT_SP_CLK_SEL                       14
#define SPORT_MASK_SP_CLK_SEL                        ((u32)0x00000003 << 14)                             /*!<R/W 0  00 and 01: SP_CLK = SP_SRC_CLK 10: SP_CLK = SP_SRC_CLK / 2 11: SP_CLK = SP_SRC_CLK / 4 */
#define SPORT_SHIFT_SP_CLEAR_RX_ERR_CNT              13
#define SPORT_BIT_SP_CLEAR_RX_ERR_CNT                ((u32)0x00000001 << 13)                             /*!<R/W 0  Write 1 and then write 0 to clear RX error counter. */
#define SPORT_SHIFT_SP_CLEAR_TX_ERR_CNT              12
#define SPORT_BIT_SP_CLEAR_TX_ERR_CNT                ((u32)0x00000001 << 12)                             /*!<R/W 0  Write 1 and then write 0 to clear TX error counter. */
#define SPORT_SHIFT_SP_ENABLE_MCLK                   11
#define SPORT_BIT_SP_ENABLE_MCLK                     ((u32)0x00000001 << 11)                             /*!<R/W 0  0: Disable 1: Enable MCLK */
#define SPORT_SHIFT_SP_DEBUG_BUS_SEL                 8
#define SPORT_MASK_SP_DEBUG_BUS_SEL                  ((u32)0x00000007 << 8)                              /*!<R/W 0  000: Debug_bus_a 001: Debug_bus_b ect. */
#define SPORT_SHIFT_SP_RX_FIFO_RESET                 2
#define SPORT_BIT_SP_RX_FIFO_RESET                   ((u32)0x00000001 << 2)                              /*!<R/W 0  0: Stop reset 1: Reset RX FIFO to make TX FIFO data become zero */
#define SPORT_SHIFT_SP_TX_FIFO_RESET                 1
#define SPORT_BIT_SP_TX_FIFO_RESET                   ((u32)0x00000001 << 1)                              /*!<R/W 0  0: Stop reset 1: Reset TX FIFO to make TX FIFO data become zero */
#define SPORT_SHIFT_SP_BCLK_RESET                    0
#define SPORT_BIT_SP_BCLK_RESET                      ((u32)0x00000001 << 0)                              /*!<R/W 0  0: Stop reset 1: Stop BCLK, and reset the state machine of the clock generator. */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_FIFO_INTR_CON
 * @brief  SPORT FIFO Interrupt Control Register     (@ 0X00C)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_TX_IDLE_INTR_1_EN             30
#define SPORT_BIT_SP_TX_IDLE_INTR_1_EN               ((u32)0x00000001 << 30)                             /*!<R/W 0  0: Disable 1: Generate the interrupt when TX is working, and TX FIFO_1 is empty. */
#define SPORT_SHIFT_SP_RX_FIFO_EMPTY_1_EN            29
#define SPORT_BIT_SP_RX_FIFO_EMPTY_1_EN              ((u32)0x00000001 << 29)                             /*!<R/W 0  0: Disable 1: Enable RX FIFO_1 empty interrupt */
#define SPORT_SHIFT_SP_TX_FIFO_EMPTY_1_EN            28
#define SPORT_BIT_SP_TX_FIFO_EMPTY_1_EN              ((u32)0x00000001 << 28)                             /*!<R/W 0  0: Disable 1: Enable TX FIFO_1 empty interrupt */
#define SPORT_SHIFT_SP_RX_FIFO_FULL_INTR_1_EN        27
#define SPORT_BIT_SP_RX_FIFO_FULL_INTR_1_EN          ((u32)0x00000001 << 27)                             /*!<R/W 0  0: Disable 1: Enable RX FIFO_1 full interrupt */
#define SPORT_SHIFT_SP_TX_FIFO_FULL_INTR_1_EN        26
#define SPORT_BIT_SP_TX_FIFO_FULL_INTR_1_EN          ((u32)0x00000001 << 26)                             /*!<R/W 0  0: Disable 1: Enable TX FIFO_1 full interrupt */
#define SPORT_SHIFT_SP_RX_FIFO_TH_INTR_1_EN          25
#define SPORT_BIT_SP_RX_FIFO_TH_INTR_1_EN            ((u32)0x00000001 << 25)                             /*!<R/W 0  0: Disable 1: When RX FIFO_1 level is greater than SP_RX_FIFO_TH, generate the interrupt. */
#define SPORT_SHIFT_SP_TX_FIFO_TH_INTR_1_EN          24
#define SPORT_BIT_SP_TX_FIFO_TH_INTR_1_EN            ((u32)0x00000001 << 24)                             /*!<R/W 0  0: Disable 1: When TX FIFO_1 level is less than SP_TX_FIFO_TH, generate the interrupt. */
#define SPORT_SHIFT_SP_TX_IDLE_INTR_0_EN             22
#define SPORT_BIT_SP_TX_IDLE_INTR_0_EN               ((u32)0x00000001 << 22)                             /*!<R/W 0  0: Disable 1: Generate the interrupt when TX is working, and TX FIFO_0 is empty. */
#define SPORT_SHIFT_SP_RX_FIFO_EMPTY_0_EN            21
#define SPORT_BIT_SP_RX_FIFO_EMPTY_0_EN              ((u32)0x00000001 << 21)                             /*!<R/W 0  0: Disable 1: Enable RX FIFO_0 empty interrupt */
#define SPORT_SHIFT_SP_TX_FIFO_EMPTY_0_EN            20
#define SPORT_BIT_SP_TX_FIFO_EMPTY_0_EN              ((u32)0x00000001 << 20)                             /*!<R/W 0  0: Disable 1: Enable TX FIFO_0 empty interrupt */
#define SPORT_SHIFT_SP_RX_FIFO_FULL_INTR_0_EN        19
#define SPORT_BIT_SP_RX_FIFO_FULL_INTR_0_EN          ((u32)0x00000001 << 19)                             /*!<R/W 0  0: Disable 1: Enable RX FIFO_0 full interrupt */
#define SPORT_SHIFT_SP_TX_FIFO_FULL_INTR_0_EN        18
#define SPORT_BIT_SP_TX_FIFO_FULL_INTR_0_EN          ((u32)0x00000001 << 18)                             /*!<R/W 0  0: Disable 1: Enable TX FIFO_0 full interrupt */
#define SPORT_SHIFT_SP_RX_FIFO_TH_INTR_0_EN          17
#define SPORT_BIT_SP_RX_FIFO_TH_INTR_0_EN            ((u32)0x00000001 << 17)                             /*!<R/W 0  0: Disable 1: When RX FIFO_0 level is greater than SP_RX_FIFO_TH, generate the interrupt. */
#define SPORT_SHIFT_SP_TX_FIFO_TH_INTR_0_EN          16
#define SPORT_BIT_SP_TX_FIFO_TH_INTR_0_EN            ((u32)0x00000001 << 16)                             /*!<R/W 0  0: Disable 1: When TX FIFO_0 level is less than SP_TX_FIFO_TH, generate the interrupt. */
#define SPORT_SHIFT_SP_CLR_TX_IDLE_INTR_1            13
#define SPORT_BIT_SP_CLR_TX_IDLE_INTR_1              ((u32)0x00000001 << 13)                             /*!<R/W 0  Clear TX FIFO_1 idle interrupt. F/W writes 1 and then 0 to clear TX interrupt. */
#define SPORT_SHIFT_SP_CLR_RX_FIFO_EMPTY_1           12
#define SPORT_BIT_SP_CLR_RX_FIFO_EMPTY_1             ((u32)0x00000001 << 12)                             /*!<R/W 0  Clear RX FIFO_1 empty interrupt. F/W writes 1 and then 0 to clear RX interrupt. */
#define SPORT_SHIFT_SP_CLR_TX_FIFO_EMPTY_1           11
#define SPORT_BIT_SP_CLR_TX_FIFO_EMPTY_1             ((u32)0x00000001 << 11)                             /*!<R/W 0  Clear TX FIFO_1 empty interrupt. F/W writes 1 and then 0 to clear TX interrupt. */
#define SPORT_SHIFT_SP_CLR_RX_FIFO_FULL_INTR_1       10
#define SPORT_BIT_SP_CLR_RX_FIFO_FULL_INTR_1         ((u32)0x00000001 << 10)                             /*!<R/W 0  Clear RX FIFO_1 full interrupt. F/W writes 1 and then 0 to clear RX interrupt. */
#define SPORT_SHIFT_SP_CLR_TX_FIFO_FULL_INTR_1       9
#define SPORT_BIT_SP_CLR_TX_FIFO_FULL_INTR_1         ((u32)0x00000001 << 9)                              /*!<R/W 0  Clear TX FIFO_1 full interrupt. F/W writes 1 and then 0 to clear TX interrupt. */
#define SPORT_SHIFT_SP_CLR_RX_FIFO_TH_INTR_1         8
#define SPORT_BIT_SP_CLR_RX_FIFO_TH_INTR_1           ((u32)0x00000001 << 8)                              /*!<R/W 0  For MCU mode (bypass DMA), F/W writes 1 and then 0 to clear RX interrupt. Note: RX interrupt is to indicate that MCU can get audio data from RX FIFO_1 */
#define SPORT_SHIFT_SP_CLR_TX_FIFO_TH_INTR_1         7
#define SPORT_BIT_SP_CLR_TX_FIFO_TH_INTR_1           ((u32)0x00000001 << 7)                              /*!<R/W 0  For MCU mode (bypass DMA), F/W writes 1 and then 0 to clear RX interrupt. Note: TX interrupt is to indicate that MCU can write audio data to TX FIFO_1 */
#define SPORT_SHIFT_SP_CLR_TX_IDLE_INTR_0            6
#define SPORT_BIT_SP_CLR_TX_IDLE_INTR_0              ((u32)0x00000001 << 6)                              /*!<R/W 0  Clear TX FIFO_0 idle interrupt. F/W writes 1 and then 0 to clear TX interrupt. */
#define SPORT_SHIFT_SP_CLR_RX_FIFO_EMPTY_0           5
#define SPORT_BIT_SP_CLR_RX_FIFO_EMPTY_0             ((u32)0x00000001 << 5)                              /*!<R/W 0  Clear RX FIFO_0 empty interrupt. F/W writes 1 and then 0 to clear RX interrupt. */
#define SPORT_SHIFT_SP_CLR_TX_FIFO_EMPTY_0           4
#define SPORT_BIT_SP_CLR_TX_FIFO_EMPTY_0             ((u32)0x00000001 << 4)                              /*!<R/W 0  Clear TX FIFO_0 empty interrupt. F/W writes 1 and then 0 to clear TX interrupt. */
#define SPORT_SHIFT_SP_CLR_RX_FIFO_FULL_INTR_0       3
#define SPORT_BIT_SP_CLR_RX_FIFO_FULL_INTR_0         ((u32)0x00000001 << 3)                              /*!<R/W 0  Clear RX FIFO_0 full interrupt. F/W writes 1 and then 0 to clear RX interrupt. */
#define SPORT_SHIFT_SP_CLR_TX_FIFO_FULL_INTR_0       2
#define SPORT_BIT_SP_CLR_TX_FIFO_FULL_INTR_0         ((u32)0x00000001 << 2)                              /*!<R/W 0  Clear TX FIFO_0 full interrupt. F/W writes 1 and then 0 to clear TX interrupt. */
#define SPORT_SHIFT_SP_CLR_RX_FIFO_TH_INTR_0         1
#define SPORT_BIT_SP_CLR_RX_FIFO_TH_INTR_0           ((u32)0x00000001 << 1)                              /*!<R/W 0  For MCU mode (bypass DMA), F/W writes 1 and then 0 to clear RX interrupt. Note: RX interrupt is to indicate that MCU can get audio data from RX FIFO_0 */
#define SPORT_SHIFT_SP_CLR_TX_FIFO_TH_INTR_0         0
#define SPORT_BIT_SP_CLR_TX_FIFO_TH_INTR_0           ((u32)0x00000001 << 0)                              /*!<R/W 0  For MCU mode (bypass DMA), F/W writes 1 and then 0 to clear RX interrupt. Note: TX interrupt is to indicate that MCU can write audio data to TX FIFO_0 */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_RX_FIFO_0
 * @brief  SPORT RX FIFO_0 Register                  (@ 0X010)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX_FIFO_0                     0
#define SPORT_MASK_SP_RX_FIFO_0                      ((u32)0xFFFFFFFF << 0)                              /*!<R 0  RX FIFO_0 data register */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_FIFO_CNT_STA
 * @brief  SPORT FIFO Counter Status Register        (@ 0X014)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX_DEPTH_CNT_1                24
#define SPORT_MASK_SP_RX_DEPTH_CNT_1                 ((u32)0x0000003F << 24)                             /*!<R 0  Read RX FIFO_1 depth status. When RX FIFO_1 is empty, this value shows 32. */
#define SPORT_SHIFT_SP_TX_DEPTH_CNT_1                16
#define SPORT_MASK_SP_TX_DEPTH_CNT_1                 ((u32)0x0000003F << 16)                             /*!<R 0  Read TX FIFO_1 depth status. When TX FIFO_1 is empty, this value shows 32. */
#define SPORT_SHIFT_SP_RX_DEPTH_CNT_0                8
#define SPORT_MASK_SP_RX_DEPTH_CNT_0                 ((u32)0x0000003F << 8)                              /*!<R 0  Read RX FIFO_0 depth status. When RX FIFO_0 is empty, this value shows 32. */
#define SPORT_SHIFT_SP_TX_DEPTH_CNT_0                0
#define SPORT_MASK_SP_TX_DEPTH_CNT_0                 ((u32)0x0000003F << 0)                              /*!<R 0  Read TX FIFO_0 depth status. When TX FIFO_0 is empty, this value shows 32. */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_TX_RX_ERR_STA
 * @brief  SPORT TX and RX Error Status Register     (@ 0X018)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX_ERR_CNT                    16
#define SPORT_MASK_SP_RX_ERR_CNT                     ((u32)0x0000FFFF << 16)                             /*!<R 0  RX error counter Note: This counter should always be zero if everything works well. */
#define SPORT_SHIFT_SP_TX_ERR_CNT                    0
#define SPORT_MASK_SP_TX_ERR_CNT                     ((u32)0x0000FFFF << 0)                              /*!<R 0  TX error counter Note: This counter should always be zero if everything works well. */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_TX_FRA_DIV
 * @brief  SPORT TX Fractional Divider Register      (@ 0X01C)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_TX_MI_NI_UPDATE               31
#define SPORT_BIT_SP_TX_MI_NI_UPDATE                 ((u32)0x00000001 << 31)                             /*!<R/W 0  Update mi and ni. 0: Off 1: To update mi and ni to get the new clock rate. This bit will be reset automatically when the update is done. */
#define SPORT_SHIFT_SP_TX_NI                         16
#define SPORT_MASK_SP_TX_NI                          ((u32)0x00007FFF << 16)                             /*!<R/W 0x30  the same mi  */
#define SPORT_SHIFT_SP_TX_MI                         0
#define SPORT_MASK_SP_TX_MI                          ((u32)0x0000FFFF << 0)                              /*!<R/W 0x271  BCLK = 40MHz x (ni/mi) For example: BCLK=3.072MHz=40MHz x (48/625) */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_LRCK_FIFO_TH_CON
 * @brief   SPORT LRCK and FIFO Threshold Control Register (@ 0X020)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX_BCLK_DIV_RATIO             24
#define SPORT_MASK_SP_RX_BCLK_DIV_RATIO              ((u32)0x000000FF << 24)                             /*!<R/W 0x3F  Control RX LRCK divider. */
#define SPORT_SHIFT_SP_BCLK_DIV_RATIO                16
#define SPORT_MASK_SP_BCLK_DIV_RATIO                 ((u32)0x000000FF << 16)                             /*!<R/W 0x3F  Control LRCK divider. */
#define SPORT_SHIFT_SP_RX_FIFO_TH                    8
#define SPORT_MASK_SP_RX_FIFO_TH                     ((u32)0x0000003F << 8)                              /*!<R/W 0x10  Set RX FIFO interrupt and DMA request threshold. */
#define SPORT_SHIFT_SP_TX_FIFO_TH                    0
#define SPORT_MASK_SP_TX_FIFO_TH                     ((u32)0x0000003F << 0)                              /*!<R/W 0x10  Set TX FIFO interrupt and DMA request threshold. */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_FIFO_INTR_STA
 * @brief  SPORT FIFO Interrupt Status Register      (@ 0X024)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX_FIFO_EMPTY_0               31
#define SPORT_BIT_SP_RX_FIFO_EMPTY_0                 ((u32)0x00000001 << 31)                             /*!<R 1  RX FIFO raw status 1: RX FIFO_0 is empty */
#define SPORT_SHIFT_SP_TX_FIFO_EMPTY_0               30
#define SPORT_BIT_SP_TX_FIFO_EMPTY_0                 ((u32)0x00000001 << 30)                             /*!<R 1  TX FIFO raw status 1: TX FIFO_0 is empty */
#define SPORT_SHIFT_SP_RX_FIFO_FULL_0                29
#define SPORT_BIT_SP_RX_FIFO_FULL_0                  ((u32)0x00000001 << 29)                             /*!<R 0  RX FIFO raw status 1: RX FIFO_0 is full  */
#define SPORT_SHIFT_SP_TX_FIFO_FULL_0                28
#define SPORT_BIT_SP_TX_FIFO_FULL_0                  ((u32)0x00000001 << 28)                             /*!<R 0  TX FIFO raw status 1: TX FIFO_0 is full */
#define SPORT_SHIFT_SP_RX_FIFO_EMPTY_1               27
#define SPORT_BIT_SP_RX_FIFO_EMPTY_1                 ((u32)0x00000001 << 27)                             /*!<R 1  RX FIFO raw status 1: RX FIFO_1 is empty */
#define SPORT_SHIFT_SP_TX_FIFO_EMPTY_1               26
#define SPORT_BIT_SP_TX_FIFO_EMPTY_1                 ((u32)0x00000001 << 26)                             /*!<R 1  TX FIFO raw status 1: TX FIFO_1 is empty */
#define SPORT_SHIFT_SP_RX_FIFO_FULL_1                25
#define SPORT_BIT_SP_RX_FIFO_FULL_1                  ((u32)0x00000001 << 25)                             /*!<R 0  RX FIFO raw status 1: RX FIFO_1 is full */
#define SPORT_SHIFT_SP_TX_FIFO_FULL_1                24
#define SPORT_BIT_SP_TX_FIFO_FULL_1                  ((u32)0x00000001 << 24)                             /*!<R 0  TX FIFO raw status 1: TX FIFO_1 is full  */
#define SPORT_SHIFT_SP_TX_IDLE_INTR_1                13
#define SPORT_BIT_SP_TX_IDLE_INTR_1                  ((u32)0x00000001 << 13)                             /*!<R 0  Interrupt status 1: TX is working but FIFO_1 is empty.  */
#define SPORT_SHIFT_SP_RX_FIFO_EMPTY_INTR_1          12
#define SPORT_BIT_SP_RX_FIFO_EMPTY_INTR_1            ((u32)0x00000001 << 12)                             /*!<R 0  Interrupt status 1: RX FIFO_1 is empty */
#define SPORT_SHIFT_SP_TX_FIFO_EMPTY_INTR_1          11
#define SPORT_BIT_SP_TX_FIFO_EMPTY_INTR_1            ((u32)0x00000001 << 11)                             /*!<R 0  Interrupt status 1: TX FIFO_1 is empty */
#define SPORT_SHIFT_SP_RX_FIFO_FULL_INTR_1           10
#define SPORT_BIT_SP_RX_FIFO_FULL_INTR_1             ((u32)0x00000001 << 10)                             /*!<R 0  Interrupt status 1: RX FIFO_1 is full */
#define SPORT_SHIFT_SP_TX_FIFO_FULL_INTR_1           9
#define SPORT_BIT_SP_TX_FIFO_FULL_INTR_1             ((u32)0x00000001 << 9)                              /*!<R 0  Interrupt status 1: TX FIFO_1 is full */
#define SPORT_SHIFT_SP_RX_FIFO_TH_INTR_1             8
#define SPORT_BIT_SP_RX_FIFO_TH_INTR_1               ((u32)0x00000001 << 8)                              /*!<R 0  Interrupt status 1: It is ready to receive data */
#define SPORT_SHIFT_SP_TX_FIFO_TH_INTR_1             7
#define SPORT_BIT_SP_TX_FIFO_TH_INTR_1               ((u32)0x00000001 << 7)                              /*!<R 0  Interrupt status 1: It is ready to send data out */
#define SPORT_SHIFT_SP_TX_IDLE_INTR_0                6
#define SPORT_BIT_SP_TX_IDLE_INTR_0                  ((u32)0x00000001 << 6)                              /*!<R 0  Interrupt status 1: TX is working but FIFO_0 is empty. */
#define SPORT_SHIFT_SP_RX_FIFO_EMPTY_INTR_0          5
#define SPORT_BIT_SP_RX_FIFO_EMPTY_INTR_0            ((u32)0x00000001 << 5)                              /*!<R 0  Interrupt status 1: TX FIFO_0 is empty */
#define SPORT_SHIFT_SP_TX_FIFO_EMPTY_INTR_0          4
#define SPORT_BIT_SP_TX_FIFO_EMPTY_INTR_0            ((u32)0x00000001 << 4)                              /*!<R 0  Interrupt status 1: TX FIFO_0 is empty */
#define SPORT_SHIFT_SP_RX_FIFO_FULL_INTR_0           3
#define SPORT_BIT_SP_RX_FIFO_FULL_INTR_0             ((u32)0x00000001 << 3)                              /*!<R 0  Interrupt status 1: RX FIFO_0 is full */
#define SPORT_SHIFT_SP_TX_FIFO_FULL_INTR_0           2
#define SPORT_BIT_SP_TX_FIFO_FULL_INTR_0             ((u32)0x00000001 << 2)                              /*!<R 0  Interrupt status 1: TX FIFO_0 is full */
#define SPORT_SHIFT_SP_RX_FIFO_TH_INTR_0             1
#define SPORT_BIT_SP_RX_FIFO_TH_INTR_0               ((u32)0x00000001 << 1)                              /*!<R 0  Interrupt status 1: It is ready to send data out */
#define SPORT_SHIFT_SP_TX_FIFO_TH_INTR_0             0
#define SPORT_BIT_SP_TX_FIFO_TH_INTR_0               ((u32)0x00000001 << 0)                              /*!<R 0  Interrupt status 1: It is ready to send data out */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_FORM_CON
 * @brief   SPORT Format Control                     (@ 0X028)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_TRX_SAME_CH_LEN               31
#define SPORT_BIT_SP_TRX_SAME_CH_LEN                 ((u32)0x00000001 << 31)                             /*!<R/W 0  0: TX and RX channel length according to SP_CH_LEN_SEL_RX and SP_CH_LEN_SEL_RX. 1: Force that TX and RX have the same channel length */
#define SPORT_SHIFT_SP_CH_LEN_SEL_RX                 28
#define SPORT_MASK_SP_CH_LEN_SEL_RX                  ((u32)0x00000007 << 28)                             /*!<R/W 0x4  Set RX channel length. 000: 16 bits 001: 20 bits 010: 24 bits 100: 32 bits Others: Reserved */
#define SPORT_SHIFT_SP_CH_LEN_SEL_TX                 24
#define SPORT_MASK_SP_CH_LEN_SEL_TX                  ((u32)0x00000007 << 24)                             /*!<R/W 0x4  Set TX channel length. 000: 16 bits 001: 20 bits 010: 24 bits 100: 32 bits Others: Reserved */
#define SPORT_SHIFT_SP_DATA_LEN_SEL_RX_0             12
#define SPORT_MASK_SP_DATA_LEN_SEL_RX_0              ((u32)0x00000007 << 12)                             /*!<R/W 0  It is valid if SP_TRX_SAME_FS is 0. Data length of SD_I 000: 16 bits 001: 20 bits 010: 24 bits 100: 32 bits Others: Reserved */
#define SPORT_SHIFT_SP_EN_I2S_MONO_RX_0              11
#define SPORT_BIT_SP_EN_I2S_MONO_RX_0                ((u32)0x00000001 << 11)                             /*!<R/W 0  It is valid if SP_TRX_SAME_FS is 0. Data format of SD_I 0: stereo 1: mono */
#define SPORT_SHIFT_SP_TRX_SAME_LRCK                 10
#define SPORT_BIT_SP_TRX_SAME_LRCK                   ((u32)0x00000001 << 10)                             /*!<R/W 0  0: LRCK_RX is not as same as LRCK 1: LRCK_RX is as same as LRCK */
#define SPORT_SHIFT_SP_DATA_FORMAT_SEL_RX            8
#define SPORT_MASK_SP_DATA_FORMAT_SEL_RX             ((u32)0x00000003 << 8)                              /*!<R/W 0  It is valid if SP_TRX_SAME_FS is 0. Data format of SD_I 00: I2S 01: Left Justified 10: PCM mode A 11: PCM mode B */
#define SPORT_SHIFT_SP_FIXED_BCLK                    7
#define SPORT_BIT_SP_FIXED_BCLK                      ((u32)0x00000001 << 7)                              /*!<R/W 0  0: Disable the fixed BCLK 1: Enable the fixed BCLK */
#define SPORT_SHIFT_SP_FIXED_BCLK_SEL                6
#define SPORT_BIT_SP_FIXED_BCLK_SEL                  ((u32)0x00000001 << 6)                              /*!<R/W 0  0: BCLK is fixed at SP_CLK / 4 1: BCLK is fixed at SP_CLK / 2 */
#define SPORT_SHIFT_SP_BCLK_RX_INVERSE               5
#define SPORT_BIT_SP_BCLK_RX_INVERSE                 ((u32)0x00000001 << 5)                              /*!<R/W 0  0: Disable 1: Invert the phase of LRCK_RX */
#define SPORT_SHIFT_SP_BCLK_OUT_INVERSE              3
#define SPORT_BIT_SP_BCLK_OUT_INVERSE                ((u32)0x00000001 << 3)                              /*!<R/W 0  0: Disable 1: Invert the phase of BCLK */
#define SPORT_SHIFT_SP_TRX_SAME_LENGTH               2
#define SPORT_BIT_SP_TRX_SAME_LENGTH                 ((u32)0x00000001 << 2)                              /*!<R/W 0x1  0: Do not have the same data length. 1: Have the same data length. */
#define SPORT_SHIFT_SP_TRX_SAME_CH                   1
#define SPORT_BIT_SP_TRX_SAME_CH                     ((u32)0x00000001 << 1)                              /*!<R/W 0x1  0: Do not have the same channel setting. 1: Have the same channel setting. Both are either stereo or mono. */
#define SPORT_SHIFT_SP_TRX_SAME_FS                   0
#define SPORT_BIT_SP_TRX_SAME_FS                     ((u32)0x00000001 << 0)                              /*!<R/W 0x1  Support TX and RX use different sample rates. 0: TX and RX do not have the same sampling rate 1: TX and RX have the same sampling rate */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_RX_FRA_DIV
 * @brief  SPORT RX Fractional Divider Register      (@ 0X02C)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX_MI_NI_UPDATE               31
#define SPORT_BIT_SP_RX_MI_NI_UPDATE                 ((u32)0x00000001 << 31)                             /*!<R/W 0  Update mi and ni. 0: Off 1: To update mi and ni to get the new clock rate. This bit will be reset automatically when the update is done. */
#define SPORT_SHIFT_SP_RX_NI                         16
#define SPORT_MASK_SP_RX_NI                          ((u32)0x00007FFF << 16)                             /*!<R/W 0x30  the same mi  */
#define SPORT_SHIFT_SP_RX_MI                         0
#define SPORT_MASK_SP_RX_MI                          ((u32)0x0000FFFF << 0)                              /*!<R/W 0x271  This fractional Divider mainly makes LRCK_RX. BCLK = 40MHz x (ni/mi) For example: BCLK=3.072MHz=40MHz x (48/625) */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_TX_SLOT_SELE
 * @brief  SPORT TX Slot Selection Register          (@ 0X03C)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_TX_SLOT7_SEL                  28
#define SPORT_MASK_SP_TX_SLOT7_SEL                   ((u32)0x00000007 << 28)                             /*!<R/W 0x7  Select the data of slot 7. 0: CH0 Data 1: CH1 Data 2: CH2 Data 3: CH3 Data 4: CH4 Data 5: CH5 Data 6: CH6 Data 7: CH7 Data */
#define SPORT_SHIFT_SP_TX_SLOT6_SEL                  24
#define SPORT_MASK_SP_TX_SLOT6_SEL                   ((u32)0x00000007 << 24)                             /*!<R/W 0x6  Select the data of slot 6. 0: CH0 Data 1: CH1 Data 2: CH2 Data 3: CH3 Data 4: CH4 Data 5: CH5 Data 6: CH6 Data 7: CH7 Data */
#define SPORT_SHIFT_SP_TX_SLOT5_SEL                  20
#define SPORT_MASK_SP_TX_SLOT5_SEL                   ((u32)0x00000007 << 20)                             /*!<R/W 0x5  Select the data of slot 5. 0: CH0 Data 1: CH1 Data 2: CH2 Data 3: CH3 Data 4: CH4 Data 5: CH5 Data 6: CH6 Data 7: CH7 Data */
#define SPORT_SHIFT_SP_TX_SLOT4_SEL                  16
#define SPORT_MASK_SP_TX_SLOT4_SEL                   ((u32)0x00000007 << 16)                             /*!<R/W 0x4  Select the data of slot 4. 0: CH0 Data 1: CH1 Data 2: CH2 Data 3: CH3 Data 4: CH4 Data 5: CH5 Data 6: CH6 Data 7: CH7 Data */
#define SPORT_SHIFT_SP_TX_SLOT3_SEL                  12
#define SPORT_MASK_SP_TX_SLOT3_SEL                   ((u32)0x00000007 << 12)                             /*!<R/W 0x3  Select the data of slot 3. 0: CH0 Data 1: CH1 Data 2: CH2 Data 3: CH3 Data 4: CH4 Data 5: CH5 Data 6: CH6 Data 7: CH7 Data */
#define SPORT_SHIFT_SP_TX_SLOT2_SEL                  8
#define SPORT_MASK_SP_TX_SLOT2_SEL                   ((u32)0x00000007 << 8)                              /*!<R/W 0x2  Select the data of slot 2. 0: CH0 Data 1: CH1 Data 2: CH2 Data 3: CH3 Data 4: CH4 Data 5: CH5 Data 6: CH6 Data 7: CH7 Data */
#define SPORT_SHIFT_SP_TX_SLOT1_SEL                  4
#define SPORT_MASK_SP_TX_SLOT1_SEL                   ((u32)0x00000007 << 4)                              /*!<R/W 0x1  Select the data of slot 1. 0: CH0 Data 1: CH1 Data 2: CH2 Data 3: CH3 Data 4: CH4 Data 5: CH5 Data 6: CH6 Data 7: CH7 Data */
#define SPORT_SHIFT_SP_TX_SLOT0_SEL                  0
#define SPORT_MASK_SP_TX_SLOT0_SEL                   ((u32)0x00000007 << 0)                              /*!<R/W 0  Select the data of slot 0. 0: CH0 Data 1: CH1 Data 2: CH2 Data 3: CH3 Data 4: CH4 Data 5: CH5 Data 6: CH6 Data 7: CH7 Data */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_TX_FIFO_1
 * @brief  SPORT TX FIFO_1 Register                  (@ 0X040)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_TX_FIFO_1                     0
#define SPORT_MASK_SP_TX_FIFO_1                      ((u32)0xFFFFFFFF << 0)                              /*!<W 0  TX FIFO_1 data register */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_TX1_RX1_DAT_CON
 * @brief  SPORT TX1 and RX1 Data Control Register   (@ 0X044)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX_LSB_FIRST_1                31
#define SPORT_BIT_SP_RX_LSB_FIRST_1                  ((u32)0x00000001 << 31)                             /*!<R/W 0  RX1 transmit 0: MSB first 1: LSB first */
#define SPORT_SHIFT_SP_TX_LSB_FIRST_1                30
#define SPORT_BIT_SP_TX_LSB_FIRST_1                  ((u32)0x00000001 << 30)                             /*!<R/W 0  TX1 transmit 0: MSB first 1: LSB first */
#define SPORT_SHIFT_SP_RX_SNK_LR_SWAP_1              29
#define SPORT_BIT_SP_RX_SNK_LR_SWAP_1                ((u32)0x00000001 << 29)                             /*!<R/W 0  0: Disable 1: Swap L/R audio samples written to the sink memory of RX_FIFO_1 */
#define SPORT_SHIFT_SP_RX_SNK_BYTE_SWAP_1            28
#define SPORT_BIT_SP_RX_SNK_BYTE_SWAP_1              ((u32)0x00000001 << 28)                             /*!<R/W 0  0: Disable 1: Swap H/L bytes written to the sink memory of RX_FIFO_1 */
#define SPORT_SHIFT_SP_TX_SRC_LR_SWAP_1              27
#define SPORT_BIT_SP_TX_SRC_LR_SWAP_1                ((u32)0x00000001 << 27)                             /*!<R/W 0  0: Disable 1: Swap L/R audio samples read from the source memory of TX_FIFO_1 */
#define SPORT_SHIFT_SP_TX_SRC_BYTE_SWAP_1            26
#define SPORT_BIT_SP_TX_SRC_BYTE_SWAP_1              ((u32)0x00000001 << 26)                             /*!<R/W 0  0: Disable 1: Swap H/L bytes read from the source memory of TX_FIFO_1  */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_TX1_RX1_FORM_CON
 * @brief   SPORT TX1 and RX1 Format Control Register (@ 0X048)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_EN_I2S_MONO_RX_1              31
#define SPORT_BIT_SP_EN_I2S_MONO_RX_1                ((u32)0x00000001 << 31)                             /*!<R/W 0  It is valid if SP_TRX_SAME_FS is 0. Data format of SD_I 0: stereo 1: mono */
#define SPORT_SHIFT_SP_DATA_LEN_SEL_RX_1             28
#define SPORT_MASK_SP_DATA_LEN_SEL_RX_1              ((u32)0x00000007 << 28)                             /*!<R/W 0  It is valid if SP_TRX_SAME_FS is 0. Data length of SD_I 000: 16 bits 001: 20 bits 010: 24 bits 100: 32 bits Others: Reserved */
#define SPORT_SHIFT_SP_EN_I2S_MONO_TX_1              27
#define SPORT_BIT_SP_EN_I2S_MONO_TX_1                ((u32)0x00000001 << 27)                             /*!<R/W 0  0: Stereo 1: Mono */
#define SPORT_SHIFT_SP_DATA_LEN_SEL_TX_1             24
#define SPORT_MASK_SP_DATA_LEN_SEL_TX_1              ((u32)0x00000007 << 24)                             /*!<R/W 0  000: 16 bits 001: 20 bits 010: 24 bits 100: 32 bits Others: Reserved */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_RX_FIFO_1
 * @brief  SPORT RX FIFO_1 Register                  (@ 0X050)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX_FIFO_1                     0
#define SPORT_MASK_SP_RX_FIFO_1                      ((u32)0xFFFFFFFF << 0)                              /*!<R 0  RX FIFO_1 data register */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_RX_SLOT_SELE_0_3CH
 * @brief  SPORT RX Slot Selection 0-3 Channel Register (@ 0X054)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX_CH3_SEL                    24
#define SPORT_MASK_SP_RX_CH3_SEL                     ((u32)0x00000007 << 24)                             /*!<R/W 0x3  Select the slot of CH3. 0: Slot 0 1: Slot 1 2: Slot 2 3: Slot 3 4: Slot 4 5: Slot 5 6: Slot 6 7: Slot 7 */
#define SPORT_SHIFT_SP_RX_CH2_SEL                    16
#define SPORT_MASK_SP_RX_CH2_SEL                     ((u32)0x00000007 << 16)                             /*!<R/W 0x2  Select the slot of CH2. 0: Slot 0 1: Slot 1 2: Slot 2 3: Slot 3 4: Slot 4 5: Slot 5 6: Slot 6 7: Slot 7 */
#define SPORT_SHIFT_SP_RX_CH1_SEL                    8
#define SPORT_MASK_SP_RX_CH1_SEL                     ((u32)0x00000007 << 8)                              /*!<R/W 0x1  Select the slot of CH1. 0: Slot 0 1: Slot 1 2: Slot 2 3: Slot 3 4: Slot 4 5: Slot 5 6: Slot 6 7: Slot 7 */
#define SPORT_SHIFT_SP_RX_CH0_SEL                    0
#define SPORT_MASK_SP_RX_CH0_SEL                     ((u32)0x00000007 << 0)                              /*!<R/W 0  Select the slot of CH0. 0: Slot 0 1: Slot 1 2: Slot 2 3: Slot 3 4: Slot 4 5: Slot 5 6: Slot 6 7: Slot 7 */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_RX_SLOT_SELE_4_7CH
 * @brief  SPORT RX Slot Selection 4-7 Channel Register (@ 0X058)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX_CH7_SEL                    24
#define SPORT_MASK_SP_RX_CH7_SEL                     ((u32)0x00000007 << 24)                             /*!<R/W 0x7  Select the slot of CH7. 0: Slot 0 1: Slot 1 2: Slot 2 3: Slot 3 4: Slot 4 5: Slot 5 6: Slot 6 7: Slot 7 */
#define SPORT_SHIFT_SP_RX_CH6_SEL                    16
#define SPORT_MASK_SP_RX_CH6_SEL                     ((u32)0x00000007 << 16)                             /*!<R/W 0x6  Select the slot of CH6. 0: Slot 0 1: Slot 1 2: Slot 2 3: Slot 3 4: Slot 4 5: Slot 5 6: Slot 6 7: Slot 7 */
#define SPORT_SHIFT_SP_RX_CH5_SEL                    8
#define SPORT_MASK_SP_RX_CH5_SEL                     ((u32)0x00000007 << 8)                              /*!<R/W 0x5  Select the slot of CH5. 0: Slot 0 1: Slot 1 2: Slot 2 3: Slot 3 4: Slot 4 5: Slot 5 6: Slot 6 7: Slot 7 */
#define SPORT_SHIFT_SP_RX_CH4_SEL                    0
#define SPORT_MASK_SP_RX_CH4_SEL                     ((u32)0x00000007 << 0)                              /*!<R/W 0x4  Select the slot of CH4. 0: Slot 0 1: Slot 1 2: Slot 2 3: Slot 3 4: Slot 4 5: Slot 5 6: Slot 6 7: Slot 7 */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_ERR_CNT_CON
 * @brief  SPORT Error Count Control Register        (@ 0X05C)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX_DEPTH_THR_1                24
#define SPORT_MASK_SP_RX_DEPTH_THR_1                 ((u32)0x0000003F << 24)                             /*!<R/W 0x1  Threshold of RX_FIFO_1. Set as the data consumption of RX_FIFO_1 in one LRCK. This value is the FIFO layer, and one layer is 32 bits. */
#define SPORT_SHIFT_SP_TX_DEPTH_THR_1                16
#define SPORT_MASK_SP_TX_DEPTH_THR_1                 ((u32)0x0000003F << 16)                             /*!<R/W 0x1  Threshold of TX_FIFO_1. Set as the data consumption of TX_FIFO_1 in one LRCK. This value is the FIFO layer, and one layer is 32 bits. */
#define SPORT_SHIFT_SP_RX_DEPTH_THR_0                8
#define SPORT_MASK_SP_RX_DEPTH_THR_0                 ((u32)0x0000003F << 8)                              /*!<R/W 0x1  Threshold of RX_FIFO_0. Set as the data consumption of RX_FIFO_0 in one LRCK. This value is the FIFO layer, and one layer is 32 bits. */
#define SPORT_SHIFT_SP_TX_DEPTH_THR_0                0
#define SPORT_MASK_SP_TX_DEPTH_THR_0                 ((u32)0x0000003F << 0)                              /*!<R/W 0x1  Threshold of TX_FIFO_0. Set as the data consumption of TX_FIFO_0 in one LRCK. This value is the FIFO layer, and one layer is 32 bits. */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_DMA_CON
 * @brief  SPORT DMA Control Register                (@ 0X060)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_PAGE_SIZE                     16
#define SPORT_MASK_SP_PAGE_SIZE                      ((u32)0x00000FFF << 16)                             /*!<R/W 0  Memory page size = PAGE_SIZE + 1 (word unit) */
#define SPORT_SHIFT_SP_BURST_SIZE                    12
#define SPORT_MASK_SP_BURST_SIZE                     ((u32)0x00000003 << 12)                             /*!<R/W 0  Set DMA burst size. When SP_MCU_CTL_MODE is 0, SP_TX_FIFO_TH and SP_RX_FIFO_TH also must be set to 15, 7, or 3 according SP_BURST_SIZE. For example: When SP_BURST_SIZE is 0, SP_TX_FIFO_TH and SP_RX_FIFO_TH are 15. 00: Burst size is 16. Total burst data is 64 bytes. 01: Burst size is 8. Total burst data is 32 bytes. 10: Burst size is 4. Total burst data is 16 bytes. Others: Reserved */
#define SPORT_SHIFT_SP_PAGE_NUM                      8
#define SPORT_MASK_SP_PAGE_NUM                       ((u32)0x00000003 << 8)                              /*!<R/W 0x3  Page number: 00 : inactive 01 : the page number is 2 10 : the page number is 3 11 : the page number is 4 */
#define SPORT_SHIFT_SP_DMA_CTRL                      4
#define SPORT_BIT_SP_DMA_CTRL                        ((u32)0x00000001 << 4)                              /*!<R/W 0x1  DMA Burst-length calculation methods 0: Self-calculation based on Page Size and Page Pointer settings 1: Calculation based on FIFO status (default) */
#define SPORT_SHIFT_SP_RX_DMA_EN                     2
#define SPORT_BIT_SP_RX_DMA_EN                       ((u32)0x00000001 << 2)                              /*!<R/W 0  0: Disable RX DMA, close Interrupt, and keep the DMA pointer. 1: Enable RX DMA. */
#define SPORT_SHIFT_SP_TX_DMA_EN                     1
#define SPORT_BIT_SP_TX_DMA_EN                       ((u32)0x00000001 << 1)                              /*!<R/W 0  0: Disable TX DMA, close Interrupt, and keep the DMA pointer. 1: Enable TX DMA. */
#define SPORT_SHIFT_SP_DMA_RSTN                      0
#define SPORT_BIT_SP_DMA_RSTN                        ((u32)0x00000001 << 0)                              /*!<R/W 0  Reset the DMA mechanism like state machine, the DMA pointer. 0: Make I2S execute the reset 1: Make I2S stop the reset */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_TX0_DMA_PP
 * @brief  SPORT TX0 DMA Page Pointer Register       (@ 0X064)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_TX0_PAGE_PTR                  2
#define SPORT_MASK_SP_TX0_PAGE_PTR                   ((u32)0x3FFFFFFF << 2)                              /*!<R/W 0  TX0 Page pointer. This is a physical address with word-align limitation. */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_TX0_DMA_INT_EN
 * @brief  SPORT TX0 DMA Interrupt Enable Register   (@ 0X068)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_TX0_UNDERFLOW_IE              24
#define SPORT_BIT_SP_TX0_UNDERFLOW_IE                ((u32)0x00000001 << 24)                             /*!<R/W 0  TX0 FIFO Underflow Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX0_PAGE3ERRIE                19
#define SPORT_BIT_SP_TX0_PAGE3ERRIE                  ((u32)0x00000001 << 19)                             /*!<R/W 0  TX0 PAGE 3 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX0_PAGE2ERRIE                18
#define SPORT_BIT_SP_TX0_PAGE2ERRIE                  ((u32)0x00000001 << 18)                             /*!<R/W 0  TX0 PAGE 2 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX0_PAGE1ERRIE                17
#define SPORT_BIT_SP_TX0_PAGE1ERRIE                  ((u32)0x00000001 << 17)                             /*!<R/W 0  TX0 PAGE 1 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX0_PAGE0ERRIE                16
#define SPORT_BIT_SP_TX0_PAGE0ERRIE                  ((u32)0x00000001 << 16)                             /*!<R/W 0  TX0 PAGE 0 error Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX0_PAGE3UNAVA_IE             11
#define SPORT_BIT_SP_TX0_PAGE3UNAVA_IE               ((u32)0x00000001 << 11)                             /*!<R/W 0  TX0 PAGE 3 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX0_PAGE2UNAVA_IE             10
#define SPORT_BIT_SP_TX0_PAGE2UNAVA_IE               ((u32)0x00000001 << 10)                             /*!<R/W 0  TX0PAGE 2 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX0_PAGE1UNAVA_IE             9
#define SPORT_BIT_SP_TX0_PAGE1UNAVA_IE               ((u32)0x00000001 << 9)                              /*!<R/W 0  TX0 PAGE 1 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX0_PAGE0UNAVA_IE             8
#define SPORT_BIT_SP_TX0_PAGE0UNAVA_IE               ((u32)0x00000001 << 8)                              /*!<R/W 0  TX0 PAGE 0 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX0_P3OKIE                    3
#define SPORT_BIT_SP_TX0_P3OKIE                      ((u32)0x00000001 << 3)                              /*!<R/W 0  TX0 Page 3 OK Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX0_P2OKIE                    2
#define SPORT_BIT_SP_TX0_P2OKIE                      ((u32)0x00000001 << 2)                              /*!<R/W 0  TX0 Page 2 OK Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX0_P1OKIE                    1
#define SPORT_BIT_SP_TX0_P1OKIE                      ((u32)0x00000001 << 1)                              /*!<R/W 0  TX0 Page 1 OK Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX0_P0OKIE                    0
#define SPORT_BIT_SP_TX0_P0OKIE                      ((u32)0x00000001 << 0)                              /*!<R/W 0  TX0 Page 0 OK Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_TX0_DMA_INT_STA
 * @brief  SPORT TX0 DMA Interrupt Status Register   (@ 0X06C)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_TX0_UNDERFLOW_IP              24
#define SPORT_BIT_SP_TX0_UNDERFLOW_IP                ((u32)0x00000001 << 24)                             /*!<W 0  TX0 FIFO Underflow Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_TX0_PAGE3ERRIP                19
#define SPORT_BIT_SP_TX0_PAGE3ERRIP                  ((u32)0x00000001 << 19)                             /*!<W 0  TX0 PAGE 3 Error Interrupt Pending. Fabric bus responses DEC/SLV error. 0: No error interrupt 1: Interrupt pending */
#define SPORT_SHIFT_SP_TX0_PAGE2ERRIP                18
#define SPORT_BIT_SP_TX0_PAGE2ERRIP                  ((u32)0x00000001 << 18)                             /*!<W 0  TX0 PAGE 2 Error Interrupt Pending. Fabric bus responses DEC/SLV error. 0: No error interrupt 1: Interrupt pending */
#define SPORT_SHIFT_SP_TX0_PAGE1ERRIP                17
#define SPORT_BIT_SP_TX0_PAGE1ERRIP                  ((u32)0x00000001 << 17)                             /*!<W 0  TX0 PAGE 1 Error Interrupt Pending. Fabric bus responses DEC/SLV error. 0: No error interrupt 1: Interrupt pending */
#define SPORT_SHIFT_SP_TX0_PAGE0ERRIP                16
#define SPORT_BIT_SP_TX0_PAGE0ERRIP                  ((u32)0x00000001 << 16)                             /*!<W 0  TX0 PAGE 0 Error Interrupt Pending. Fabric bus responses DEC/SLV error. 0: No error interrupt 1: Interrupt pending */
#define SPORT_SHIFT_SP_TX0_PAGE3UNAVA_IP             11
#define SPORT_BIT_SP_TX0_PAGE3UNAVA_IP               ((u32)0x00000001 << 11)                             /*!<W 0  TX0 PAGE 3 unavailable Interrupt Pending. The controller wants to execute the page but this page own bit does not be set. This situation will make the interrupt. 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_TX0_PAGE2UNAVA_IP             10
#define SPORT_BIT_SP_TX0_PAGE2UNAVA_IP               ((u32)0x00000001 << 10)                             /*!<W 0  TX0 PAGE 2 unavailable Interrupt Pending. The controller wants to execute the page but this page own bit does not be set. This situation will make the interrupt. 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_TX0_PAGE1UNAVA_IP             9
#define SPORT_BIT_SP_TX0_PAGE1UNAVA_IP               ((u32)0x00000001 << 9)                              /*!<W 0  TX0 PAGE 1 unavailable Interrupt Pending. The controller wants to execute the page but this page own bit does not be set. This situation will make the interrupt. 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_TX0_PAGE0UNAVA_IP             8
#define SPORT_BIT_SP_TX0_PAGE0UNAVA_IP               ((u32)0x00000001 << 8)                              /*!<W 0  TX0 PAGE 0 unavailable Interrupt Pending. The controller wants to execute the page but this page own bit does not be set. This situation will make the interrupt. 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_TX0_P3OKIP                    3
#define SPORT_BIT_SP_TX0_P3OKIP                      ((u32)0x00000001 << 3)                              /*!<W 0  TX0 Page 3 OK Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_TX0_P2OKIP                    2
#define SPORT_BIT_SP_TX0_P2OKIP                      ((u32)0x00000001 << 2)                              /*!<W 0  TX0 Page 2 OK Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_TX0_P1OKIP                    1
#define SPORT_BIT_SP_TX0_P1OKIP                      ((u32)0x00000001 << 1)                              /*!<W 0  TX0 Page 1 OK Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_TX0_P0OKIP                    0
#define SPORT_BIT_SP_TX0_P0OKIP                      ((u32)0x00000001 << 0)                              /*!<W 0  TX0 Page 0 OK Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_TX1_DMA_PP
 * @brief  SPORT TX1 DMA Page Pointer Register       (@ 0X070)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_TX1_PAGE_PTR                  2
#define SPORT_MASK_SP_TX1_PAGE_PTR                   ((u32)0x3FFFFFFF << 2)                              /*!<R/W 0  TX1 Page pointer. This is a physical address with word-align limitation. */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_TX1_DMA_INT_EN
 * @brief  SPORT TX1 DMA Interrupt Enable Register   (@ 0X074)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_TX1_UNDERFLOW_IE              24
#define SPORT_BIT_SP_TX1_UNDERFLOW_IE                ((u32)0x00000001 << 24)                             /*!<R/W 0  TX1 FIFO Underflow Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX1_PAGE3ERRIE                19
#define SPORT_BIT_SP_TX1_PAGE3ERRIE                  ((u32)0x00000001 << 19)                             /*!<R/W 0  TX1 PAGE 3 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX1_PAGE2ERRIE                18
#define SPORT_BIT_SP_TX1_PAGE2ERRIE                  ((u32)0x00000001 << 18)                             /*!<R/W 0  TX1 PAGE 2 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX1_PAGE1ERRIE                17
#define SPORT_BIT_SP_TX1_PAGE1ERRIE                  ((u32)0x00000001 << 17)                             /*!<R/W 0  TX1 PAGE 1 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX1_PAGE0ERRIE                16
#define SPORT_BIT_SP_TX1_PAGE0ERRIE                  ((u32)0x00000001 << 16)                             /*!<R/W 0  TX1 PAGE 0 error Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX1_PAGE3UNAVA_IE             11
#define SPORT_BIT_SP_TX1_PAGE3UNAVA_IE               ((u32)0x00000001 << 11)                             /*!<R/W 0  TX1 PAGE 3 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX1_PAGE2UNAVA_IE             10
#define SPORT_BIT_SP_TX1_PAGE2UNAVA_IE               ((u32)0x00000001 << 10)                             /*!<R/W 0  TX1 PAGE 2 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX1_PAGE1UNAVA_IE             9
#define SPORT_BIT_SP_TX1_PAGE1UNAVA_IE               ((u32)0x00000001 << 9)                              /*!<R/W 0  TX1 PAGE 1 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX1_PAGE0UNAVA_IE             8
#define SPORT_BIT_SP_TX1_PAGE0UNAVA_IE               ((u32)0x00000001 << 8)                              /*!<R/W 0  TX1 PAGE 0 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX1_P3OKIE                    3
#define SPORT_BIT_SP_TX1_P3OKIE                      ((u32)0x00000001 << 3)                              /*!<R/W 0  TX1 Page 3 OK Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX1_P2OKIE                    2
#define SPORT_BIT_SP_TX1_P2OKIE                      ((u32)0x00000001 << 2)                              /*!<R/W 0  TX1 Page 2 OK Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX1_P1OKIE                    1
#define SPORT_BIT_SP_TX1_P1OKIE                      ((u32)0x00000001 << 1)                              /*!<R/W 0  TX1 Page 1 OK Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_TX1_P0OKIE                    0
#define SPORT_BIT_SP_TX1_P0OKIE                      ((u32)0x00000001 << 0)                              /*!<R/W 0  TX1 Page 0 OK Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_TX1_DMA_INT_STA
 * @brief  SPORT TX1 DMA Interrupt Status Register   (@ 0X078)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_TX1_UNDERFLOW_IP              24
#define SPORT_BIT_SP_TX1_UNDERFLOW_IP                ((u32)0x00000001 << 24)                             /*!<W 0  TX1 FIFO Underflow Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_TX1_PAGE3ERRIP                19
#define SPORT_BIT_SP_TX1_PAGE3ERRIP                  ((u32)0x00000001 << 19)                             /*!<W 0  TX1 PAGE 3 Error Interrupt Pending. Fabric bus responses DEC/SLV error. 0: No error interrupt 1: Interrupt pending */
#define SPORT_SHIFT_SP_TX1_PAGE2ERRIP                18
#define SPORT_BIT_SP_TX1_PAGE2ERRIP                  ((u32)0x00000001 << 18)                             /*!<W 0  TX1 PAGE 2 Error Interrupt Pending. Fabric bus responses DEC/SLV error. 0: No error interrupt 1: Interrupt pending */
#define SPORT_SHIFT_SP_TX1_PAGE1ERRIP                17
#define SPORT_BIT_SP_TX1_PAGE1ERRIP                  ((u32)0x00000001 << 17)                             /*!<W 0  TX1 PAGE 1 Error Interrupt Pending. Fabric bus responses DEC/SLV error. 0: No error interrupt 1: Interrupt pending */
#define SPORT_SHIFT_SP_TX1_PAGE0ERRIP                16
#define SPORT_BIT_SP_TX1_PAGE0ERRIP                  ((u32)0x00000001 << 16)                             /*!<W 0  TX1 PAGE 0 Error Interrupt Pending. Fabric bus responses DEC/SLV error. 0: No error interrupt 1: Interrupt pending */
#define SPORT_SHIFT_SP_TX1_PAGE3UNAVA_IP             11
#define SPORT_BIT_SP_TX1_PAGE3UNAVA_IP               ((u32)0x00000001 << 11)                             /*!<W 0  TX1 PAGE 3 unavailable Interrupt Pending. The controller wants to execute the page but this page own bit does not be set. This situation will make the interrupt. 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_TX1_PAGE2UNAVA_IP             10
#define SPORT_BIT_SP_TX1_PAGE2UNAVA_IP               ((u32)0x00000001 << 10)                             /*!<W 0  TX1 PAGE 2 unavailable Interrupt Pending. The controller wants to execute the page but this page own bit does not be set. This situation will make the interrupt. 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_TX1_PAGE1UNAVA_IP             9
#define SPORT_BIT_SP_TX1_PAGE1UNAVA_IP               ((u32)0x00000001 << 9)                              /*!<W 0  TX1 PAGE 1 unavailable Interrupt Pending. The controller wants to execute the page but this page own bit does not be set. This situation will make the interrupt. 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_TX1_PAGE0UNAVA_IP             8
#define SPORT_BIT_SP_TX1_PAGE0UNAVA_IP               ((u32)0x00000001 << 8)                              /*!<W 0  TX1 PAGE 0 unavailable Interrupt Pending. The controller wants to execute the page but this page own bit does not be set. This situation will make the interrupt. 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_TX1_P3OKIP                    3
#define SPORT_BIT_SP_TX1_P3OKIP                      ((u32)0x00000001 << 3)                              /*!<W 0  TX1 Page 3 OK Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_TX1_P2OKIP                    2
#define SPORT_BIT_SP_TX1_P2OKIP                      ((u32)0x00000001 << 2)                              /*!<W 0  TX1 Page 2 OK Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_TX1_P1OKIP                    1
#define SPORT_BIT_SP_TX1_P1OKIP                      ((u32)0x00000001 << 1)                              /*!<W 0  TX1 Page 1 OK Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_TX1_P0OKIP                    0
#define SPORT_BIT_SP_TX1_P0OKIP                      ((u32)0x00000001 << 0)                              /*!<W 0  TX1 Page 0 OK Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_TX_PAGE_OWN
 * @brief  SPORT TX Page Own Register                (@ 0X07C)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_TX1_P3OWN                     7
#define SPORT_BIT_SP_TX1_P3OWN                       ((u32)0x00000001 << 7)                              /*!<R/W 0  TX1 Page 3 Own bit 0: Page 0 owned by CPU 1: Page 0 owned by controller DMA sets this bit to 0 when TX channel 0 Page 0 is done */
#define SPORT_SHIFT_SP_TX1_P2OWN                     6
#define SPORT_BIT_SP_TX1_P2OWN                       ((u32)0x00000001 << 6)                              /*!<R/W 0  TX1 Page 2 Own bit 0: Page 0 owned by CPU 1: Page 0 owned by controller DMA sets this bit to 0 when TX channel 0 Page 0 is done */
#define SPORT_SHIFT_SP_TX1_P1OWN                     5
#define SPORT_BIT_SP_TX1_P1OWN                       ((u32)0x00000001 << 5)                              /*!<R/W 0  TX1 Page 1 Own bit 0: Page 0 owned by CPU 1: Page 0 owned by controller DMA sets this bit to 0 when TX channel 0 Page 0 is done */
#define SPORT_SHIFT_SP_TX1_P0OWN                     4
#define SPORT_BIT_SP_TX1_P0OWN                       ((u32)0x00000001 << 4)                              /*!<R/W 0  TX1 Page 0 Own bit 0: Page 0 owned by CPU 1: Page 0 owned by controller DMA sets this bit to 0 when TX channel 0 Page 0 is done */
#define SPORT_SHIFT_SP_TX0_P3OWN                     3
#define SPORT_BIT_SP_TX0_P3OWN                       ((u32)0x00000001 << 3)                              /*!<R/W 0  TX0 Page 3 Own bit 0: Page 0 owned by CPU 1: Page 0 owned by controller DMA sets this bit to 0 when TX channel 0 Page 0 is done */
#define SPORT_SHIFT_SP_TX0_P2OWN                     2
#define SPORT_BIT_SP_TX0_P2OWN                       ((u32)0x00000001 << 2)                              /*!<R/W 0  TX0 Page 2 Own bit 0: Page 0 owned by CPU 1: Page 0 owned by controller DMA sets this bit to 0 when TX channel 0 Page 0 is done */
#define SPORT_SHIFT_SP_TX0_P1OWN                     1
#define SPORT_BIT_SP_TX0_P1OWN                       ((u32)0x00000001 << 1)                              /*!<R/W 0  TX0 Page 1 Own bit 0: Page 0 owned by CPU 1: Page 0 owned by controller DMA sets this bit to 0 when TX channel 0 Page 0 is done */
#define SPORT_SHIFT_SP_TX0_P0OWN                     0
#define SPORT_BIT_SP_TX0_P0OWN                       ((u32)0x00000001 << 0)                              /*!<R/W 0  TX0 Page 0 Own bit 0: Page 0 owned by CPU 1: Page 0 owned by controller DMA sets this bit to 0 when TX channel 0 Page 0 is done */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_RX0_DMA_PP
 * @brief  SPORT RX0 DMA Page Pointer Register       (@ 0X080)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX0_PAGE_PTR                  2
#define SPORT_MASK_SP_RX0_PAGE_PTR                   ((u32)0x3FFFFFFF << 2)                              /*!<R/W 0  RX0 Page pointer. This is a physical address with word-align limitation. */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_RX0_DMA_INT_EN
 * @brief  SPORT RX0 DMA Interrupt Enable Register   (@ 0X084)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX0_OVERFLOW_IE               24
#define SPORT_BIT_SP_RX0_OVERFLOW_IE                 ((u32)0x00000001 << 24)                             /*!<R/W 0  RX0 FIFO overflow Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX0_PAGE3ERRIE                19
#define SPORT_BIT_SP_RX0_PAGE3ERRIE                  ((u32)0x00000001 << 19)                             /*!<R/W 0  RX0 PAGE 3 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX0_PAGE2ERRIE                18
#define SPORT_BIT_SP_RX0_PAGE2ERRIE                  ((u32)0x00000001 << 18)                             /*!<R/W 0  RX0 PAGE 2 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX0_PAGE1ERRIE                17
#define SPORT_BIT_SP_RX0_PAGE1ERRIE                  ((u32)0x00000001 << 17)                             /*!<R/W 0  RX0 PAGE 1 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX0_PAGE0ERRIE                16
#define SPORT_BIT_SP_RX0_PAGE0ERRIE                  ((u32)0x00000001 << 16)                             /*!<R/W 0  RX0 PAGE 0 error Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX0_PAGE3UNAVA_IE             11
#define SPORT_BIT_SP_RX0_PAGE3UNAVA_IE               ((u32)0x00000001 << 11)                             /*!<R/W 0  RX0 PAGE 3 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX0_PAGE2UNAVA_IE             10
#define SPORT_BIT_SP_RX0_PAGE2UNAVA_IE               ((u32)0x00000001 << 10)                             /*!<R/W 0  RX0PAGE 2 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX0_PAGE1UNAVA_IE             9
#define SPORT_BIT_SP_RX0_PAGE1UNAVA_IE               ((u32)0x00000001 << 9)                              /*!<R/W 0  RX0 PAGE 1 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX0_PAGE0UNAVA_IE             8
#define SPORT_BIT_SP_RX0_PAGE0UNAVA_IE               ((u32)0x00000001 << 8)                              /*!<R/W 0  RX0 PAGE 0 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX0_P3OKIE                    3
#define SPORT_BIT_SP_RX0_P3OKIE                      ((u32)0x00000001 << 3)                              /*!<R/W 0  RX0 Page 3 OK Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX0_P2OKIE                    2
#define SPORT_BIT_SP_RX0_P2OKIE                      ((u32)0x00000001 << 2)                              /*!<R/W 0  RX0 Page 2 OK Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX0_P1OKIE                    1
#define SPORT_BIT_SP_RX0_P1OKIE                      ((u32)0x00000001 << 1)                              /*!<R/W 0  RX0 Page 1 OK Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX0_P0OKIE                    0
#define SPORT_BIT_SP_RX0_P0OKIE                      ((u32)0x00000001 << 0)                              /*!<R/W 0  RX0 Page 0 OK Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_RX0_DMA_INT_STA
 * @brief  SPORT RX0 DMA Interrupt Status Register   (@ 0X088)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX0_OVERFLOW_IP               24
#define SPORT_BIT_SP_RX0_OVERFLOW_IP                 ((u32)0x00000001 << 24)                             /*!<W 0  RX0 FIFO overflow Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_RX0_PAGE3ERRIP                19
#define SPORT_BIT_SP_RX0_PAGE3ERRIP                  ((u32)0x00000001 << 19)                             /*!<W 0  RX0 PAGE 3 Error Interrupt Pending. Fabric bus responses DEC/SLV error. 0: No error interrupt 1: Interrupt pending */
#define SPORT_SHIFT_SP_RX0_PAGE2ERRIP                18
#define SPORT_BIT_SP_RX0_PAGE2ERRIP                  ((u32)0x00000001 << 18)                             /*!<W 0  RX0 PAGE 2 Error Interrupt Pending. Fabric bus responses DEC/SLV error. 0: No error interrupt 1: Interrupt pending */
#define SPORT_SHIFT_SP_RX0_PAGE1ERRIP                17
#define SPORT_BIT_SP_RX0_PAGE1ERRIP                  ((u32)0x00000001 << 17)                             /*!<W 0  RX0 PAGE 1 Error Interrupt Pending. Fabric bus responses DEC/SLV error. 0: No error interrupt 1: Interrupt pending */
#define SPORT_SHIFT_SP_RX0_PAGE0ERRIP                16
#define SPORT_BIT_SP_RX0_PAGE0ERRIP                  ((u32)0x00000001 << 16)                             /*!<W 0  RX0 PAGE 0 Error Interrupt Pending. Fabric bus responses DEC/SLV error. 0: No error interrupt 1: Interrupt pending */
#define SPORT_SHIFT_SP_RX0_PAGE3UNAVA_IP             11
#define SPORT_BIT_SP_RX0_PAGE3UNAVA_IP               ((u32)0x00000001 << 11)                             /*!<W 0  RX0 PAGE 3 unavailable Interrupt Pending. The controller wants to execute the page but this page own bit does not be set. This situation will make the interrupt. 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_RX0_PAGE2UNAVA_IP             10
#define SPORT_BIT_SP_RX0_PAGE2UNAVA_IP               ((u32)0x00000001 << 10)                             /*!<W 0  RX0 PAGE 2 unavailable Interrupt Pending. The controller wants to execute the page but this page own bit does not be set. This situation will make the interrupt. 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_RX0_PAGE1UNAVA_IP             9
#define SPORT_BIT_SP_RX0_PAGE1UNAVA_IP               ((u32)0x00000001 << 9)                              /*!<W 0  RX0 PAGE 1 unavailable Interrupt Pending. The controller wants to execute the page but this page own bit does not be set. This situation will make the interrupt. 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_RX0_PAGE0UNAVA_IP             8
#define SPORT_BIT_SP_RX0_PAGE0UNAVA_IP               ((u32)0x00000001 << 8)                              /*!<W 0  RX0 PAGE 0 unavailable Interrupt Pending. The controller wants to execute the page but this page own bit does not be set. This situation will make the interrupt. 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_RX0_P3OKIP                    3
#define SPORT_BIT_SP_RX0_P3OKIP                      ((u32)0x00000001 << 3)                              /*!<W 0  RX0 Page 3 OK Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_RX0_P2OKIP                    2
#define SPORT_BIT_SP_RX0_P2OKIP                      ((u32)0x00000001 << 2)                              /*!<W 0  RX0 Page 2 OK Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_RX0_P1OKIP                    1
#define SPORT_BIT_SP_RX0_P1OKIP                      ((u32)0x00000001 << 1)                              /*!<W 0  RX0 Page 1 OK Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_RX0_P0OKIP                    0
#define SPORT_BIT_SP_RX0_P0OKIP                      ((u32)0x00000001 << 0)                              /*!<W 0  RX0 Page 0 OK Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_RX1_DMA_PP
 * @brief  SPORT RX1 DMA Page Pointer Register       (@ 0X08C)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX1_PAGE_PTR                  2
#define SPORT_MASK_SP_RX1_PAGE_PTR                   ((u32)0x3FFFFFFF << 2)                              /*!<R/W 0  RX1 Page pointer. This is a physical address with word-align limitation. */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_RX1_DMA_INT_EN
 * @brief  SPORT RX1 DMA Interrupt Enable Register   (@ 0X090)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX1_UNDERFLOW_IE              24
#define SPORT_BIT_SP_RX1_UNDERFLOW_IE                ((u32)0x00000001 << 24)                             /*!<R/W 0  RX1 FIFO overflow Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX1_PAGE3ERRIE                19
#define SPORT_BIT_SP_RX1_PAGE3ERRIE                  ((u32)0x00000001 << 19)                             /*!<R/W 0  RX1 PAGE 3 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX1_PAGE2ERRIE                18
#define SPORT_BIT_SP_RX1_PAGE2ERRIE                  ((u32)0x00000001 << 18)                             /*!<R/W 0  RX1 PAGE 2 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX1_PAGE1ERRIE                17
#define SPORT_BIT_SP_RX1_PAGE1ERRIE                  ((u32)0x00000001 << 17)                             /*!<R/W 0  RX1 PAGE 1 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX1_PAGE0ERRIE                16
#define SPORT_BIT_SP_RX1_PAGE0ERRIE                  ((u32)0x00000001 << 16)                             /*!<R/W 0  RX1 PAGE 0 error Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX1_PAGE3UNAVA_IE             11
#define SPORT_BIT_SP_RX1_PAGE3UNAVA_IE               ((u32)0x00000001 << 11)                             /*!<R/W 0  RX1 PAGE 3 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX1_PAGE2UNAVA_IE             10
#define SPORT_BIT_SP_RX1_PAGE2UNAVA_IE               ((u32)0x00000001 << 10)                             /*!<R/W 0  RX1 PAGE 2 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX1_PAGE1UNAVA_IE             9
#define SPORT_BIT_SP_RX1_PAGE1UNAVA_IE               ((u32)0x00000001 << 9)                              /*!<R/W 0  RX1 PAGE 1 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX1_PAGE0UNAVA_IE             8
#define SPORT_BIT_SP_RX1_PAGE0UNAVA_IE               ((u32)0x00000001 << 8)                              /*!<R/W 0  RX1 PAGE 0 unavailable Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX1_P3OKIE                    3
#define SPORT_BIT_SP_RX1_P3OKIE                      ((u32)0x00000001 << 3)                              /*!<R/W 0  RX1 Page 3 OK Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX1_P2OKIE                    2
#define SPORT_BIT_SP_RX1_P2OKIE                      ((u32)0x00000001 << 2)                              /*!<R/W 0  RX1 Page 2 OK Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX1_P1OKIE                    1
#define SPORT_BIT_SP_RX1_P1OKIE                      ((u32)0x00000001 << 1)                              /*!<R/W 0  RX1 Page 1 OK Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
#define SPORT_SHIFT_SP_RX1_P0OKIE                    0
#define SPORT_BIT_SP_RX1_P0OKIE                      ((u32)0x00000001 << 0)                              /*!<R/W 0  RX1 Page 0 OK Interrupt Enable 0: Disable Interrupt 1: Enable Interrupt */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_RX1_DMA_INT_STA
 * @brief  SPORT RX1 DMA Interrupt Status Register   (@ 0X094)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX1_OVERFLOW_IP               24
#define SPORT_BIT_SP_RX1_OVERFLOW_IP                 ((u32)0x00000001 << 24)                             /*!<W 0  RX1 FIFO overflow Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_RX1_PAGE3ERRIP                19
#define SPORT_BIT_SP_RX1_PAGE3ERRIP                  ((u32)0x00000001 << 19)                             /*!<W 0  RX1 PAGE 3 Error Interrupt Pending. Fabric bus responses DEC/SLV error. 0: No error interrupt 1: Interrupt pending */
#define SPORT_SHIFT_SP_RX1_PAGE2ERRIP                18
#define SPORT_BIT_SP_RX1_PAGE2ERRIP                  ((u32)0x00000001 << 18)                             /*!<W 0  RX1 PAGE 2 Error Interrupt Pending. Fabric bus responses DEC/SLV error. 0: No error interrupt 1: Interrupt pending */
#define SPORT_SHIFT_SP_RX1_PAGE1ERRIP                17
#define SPORT_BIT_SP_RX1_PAGE1ERRIP                  ((u32)0x00000001 << 17)                             /*!<W 0  RX1 PAGE 1 Error Interrupt Pending. Fabric bus responses DEC/SLV error. 0: No error interrupt 1: Interrupt pending */
#define SPORT_SHIFT_SP_RX1_PAGE0ERRIP                16
#define SPORT_BIT_SP_RX1_PAGE0ERRIP                  ((u32)0x00000001 << 16)                             /*!<W 0  RX1 PAGE 0 Error Interrupt Pending. Fabric bus responses DEC/SLV error. 0: No error interrupt 1: Interrupt pending */
#define SPORT_SHIFT_SP_RX1_PAGE3UNAVA_IP             11
#define SPORT_BIT_SP_RX1_PAGE3UNAVA_IP               ((u32)0x00000001 << 11)                             /*!<W 0  RX1 PAGE 3 unavailable Interrupt Pending. The controller wants to execute the page but this page own bit does not be set. This situation will make the interrupt. 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_RX1_PAGE2UNAVA_IP             10
#define SPORT_BIT_SP_RX1_PAGE2UNAVA_IP               ((u32)0x00000001 << 10)                             /*!<W 0  RX1 PAGE 2 unavailable Interrupt Pending. The controller wants to execute the page but this page own bit does not be set. This situation will make the interrupt. 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_RX1_PAGE1UNAVA_IP             9
#define SPORT_BIT_SP_RX1_PAGE1UNAVA_IP               ((u32)0x00000001 << 9)                              /*!<W 0  RX1 PAGE 1 unavailable Interrupt Pending. The controller wants to execute the page but this page own bit does not be set. This situation will make the interrupt. 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_RX1_PAGE0UNAVA_IP             8
#define SPORT_BIT_SP_RX1_PAGE0UNAVA_IP               ((u32)0x00000001 << 8)                              /*!<W 0  RX1 PAGE 0 unavailable Interrupt Pending. The controller wants to execute the page but this page own bit does not be set. This situation will make the interrupt. 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_RX1_P3OKIP                    3
#define SPORT_BIT_SP_RX1_P3OKIP                      ((u32)0x00000001 << 3)                              /*!<W 0  RX1 Page 3 OK Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_RX1_P2OKIP                    2
#define SPORT_BIT_SP_RX1_P2OKIP                      ((u32)0x00000001 << 2)                              /*!<W 0  RX1 Page 2 OK Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_RX1_P1OKIP                    1
#define SPORT_BIT_SP_RX1_P1OKIP                      ((u32)0x00000001 << 1)                              /*!<W 0  RX1 Page 1 OK Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
#define SPORT_SHIFT_SP_RX1_P0OKIP                    0
#define SPORT_BIT_SP_RX1_P0OKIP                      ((u32)0x00000001 << 0)                              /*!<W 0  RX1 Page 0 OK Interrupt Pending 0: No Interrupt 1: Interrupt pending, write 1 to clear */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_RX_PAGE_OWN
 * @brief  SPORT RX Page Own Register                (@ 0X098)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX1_P3OWN                     7
#define SPORT_BIT_SP_RX1_P3OWN                       ((u32)0x00000001 << 7)                              /*!<R/W 0  RX1 Page 3 Own bit 0: Page 0 owned by CPU 1: Page 0 owned by controller DMA sets this bit to 0 when TX channel 0 Page 0 is done */
#define SPORT_SHIFT_SP_RX1_P2OWN                     6
#define SPORT_BIT_SP_RX1_P2OWN                       ((u32)0x00000001 << 6)                              /*!<R/W 0  RX1 Page 2 Own bit 0: Page 0 owned by CPU 1: Page 0 owned by controller DMA sets this bit to 0 when TX channel 0 Page 0 is done */
#define SPORT_SHIFT_SP_RX1_P1OWN                     5
#define SPORT_BIT_SP_RX1_P1OWN                       ((u32)0x00000001 << 5)                              /*!<R/W 0  RX1 Page 1 Own bit 0: Page 0 owned by CPU 1: Page 0 owned by controller DMA sets this bit to 0 when TX channel 0 Page 0 is done */
#define SPORT_SHIFT_SP_RX1_P0OWN                     4
#define SPORT_BIT_SP_RX1_P0OWN                       ((u32)0x00000001 << 4)                              /*!<R/W 0  RX1 Page 0 Own bit 0: Page 0 owned by CPU 1: Page 0 owned by controller DMA sets this bit to 0 when TX channel 0 Page 0 is done */
#define SPORT_SHIFT_SP_RX0_P3OWN                     3
#define SPORT_BIT_SP_RX0_P3OWN                       ((u32)0x00000001 << 3)                              /*!<R/W 0  RX0 Page 3 Own bit 0: Page 0 owned by CPU 1: Page 0 owned by controller DMA sets this bit to 0 when TX channel 0 Page 0 is done */
#define SPORT_SHIFT_SP_RX0_P2OWN                     2
#define SPORT_BIT_SP_RX0_P2OWN                       ((u32)0x00000001 << 2)                              /*!<R/W 0  RX0 Page 2 Own bit 0: Page 0 owned by CPU 1: Page 0 owned by controller DMA sets this bit to 0 when TX channel 0 Page 0 is done */
#define SPORT_SHIFT_SP_RX0_P1OWN                     1
#define SPORT_BIT_SP_RX0_P1OWN                       ((u32)0x00000001 << 1)                              /*!<R/W 0  RX0 Page 1 Own bit 0: Page 0 owned by CPU 1: Page 0 owned by controller DMA sets this bit to 0 when TX channel 0 Page 0 is done */
#define SPORT_SHIFT_SP_RX0_P0OWN                     0
#define SPORT_BIT_SP_RX0_P0OWN                       ((u32)0x00000001 << 0)                              /*!<R/W 0  RX0 Page 0 Own bit 0: Page 0 owned by CPU 1: Page 0 owned by controller DMA sets this bit to 0 when TX channel 0 Page 0 is done */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_TX_AXIADDR_ERR
 * @brief  SPORT TX AXI address access Error address record Register (@ 0X09C)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_TX_AXIADDR                    0
#define SPORT_MASK_SP_TX_AXIADDR                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  TX AXI Error Address cause Error interruptlimitation. */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_TX_MISC_ERR
 * @brief  SPORT TX AXI MISC. access Error record Register (@ 0X100)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_TX_CURRENT_PAGE               29
#define SPORT_MASK_SP_TX_CURRENT_PAGE                ((u32)0x00000003 << 29)                             /*!<R 0  Current page has Error 00: page 0 01: page 1 10: page 2 11: page 3 */
#define SPORT_SHIFT_SP_TX_CHANNEL_WINNER             27
#define SPORT_BIT_SP_TX_CHANNEL_WINNER               ((u32)0x00000001 << 27)                             /*!<R 0  Channel that is served by DMA 0: Channel 0 1: Channel 1 */
#define SPORT_SHIFT_SP_TX_BURST_LEN_SETTING          24
#define SPORT_MASK_SP_TX_BURST_LEN_SETTING           ((u32)0x00000003 << 24)                             /*!<R 0  Burst length setting in DMA_CTRL = 1 */
#define SPORT_SHIFT_SP_TX_DMA_CTRL                   23
#define SPORT_BIT_SP_TX_DMA_CTRL                     ((u32)0x00000001 << 23)                             /*!<R 0  DMA Burst length calculation 0: Self-calculation 1: Burst length info from setting (refer to BURST_LEN_SETTING field) */
#define SPORT_SHIFT_SP_TX_BURST_LEN                  16
#define SPORT_MASK_SP_TX_BURST_LEN                   ((u32)0x0000000F << 16)                             /*!<R 0  TX AXI Burst Length Error transaction causes Error interrupt */
#define SPORT_SHIFT_SP_TX_PAGE_NUM                   12
#define SPORT_MASK_SP_TX_PAGE_NUM                    ((u32)0x00000003 << 12)                             /*!<R 0  Number of page setting */
#define SPORT_SHIFT_SP_TX_PAGE_SIZE                  0
#define SPORT_MASK_SP_TX_PAGE_SIZE                   ((u32)0x00000FFF << 0)                              /*!<R 0  Page Size setting */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_RX_AXIADDR_ERR
 * @brief  SPORT RX AXI address access Error address record Register (@ 0X104)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX_AXIADDR                    0
#define SPORT_MASK_SP_RX_AXIADDR                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  RX AXI Error Address cause Error interruptlimitation. */
/** @} */

/**************************************************************************//**
 * @defgroup SPORT_SP_RX_MISC_ERR
 * @brief  SPORT RX AXI MISC. access Error record Register (@ 0X108)
 * @{
 *****************************************************************************/
#define SPORT_SHIFT_SP_RX_CURRENT_PAGE               29
#define SPORT_MASK_SP_RX_CURRENT_PAGE                ((u32)0x00000003 << 29)                             /*!<R 0  Current page has Error 00: page 0 01: page 1 10: page 2 11: page 3 */
#define SPORT_SHIFT_SP_RX_CHANNEL_WINNER             27
#define SPORT_BIT_SP_RX_CHANNEL_WINNER               ((u32)0x00000001 << 27)                             /*!<R 0  Channel that is served by DMA 0: Channel 0 1: Channel 1 */
#define SPORT_SHIFT_SP_RX_BURST_LEN_SETTING          24
#define SPORT_MASK_SP_RX_BURST_LEN_SETTING           ((u32)0x00000003 << 24)                             /*!<R 0  Burst length setting in DMA_CTRL = 1 */
#define SPORT_SHIFT_SP_RX_DMA_CTRL                   23
#define SPORT_BIT_SP_RX_DMA_CTRL                     ((u32)0x00000001 << 23)                             /*!<R 0  DMA Burst length calculation 0: Self-calculation 1: Burst length info from setting (refer to BURST_LEN_SETTING field) */
#define SPORT_SHIFT_SP_RX_BURST_LEN                  16
#define SPORT_MASK_SP_RX_BURST_LEN                   ((u32)0x0000000F << 16)                             /*!<R 0  TX AXI Burst Length Error transaction causes Error interrupt */
#define SPORT_SHIFT_SP_RX_PAGE_NUM                   12
#define SPORT_MASK_SP_RX_PAGE_NUM                    ((u32)0x00000003 << 12)                             /*!<R 0  Number of page setting */
#define SPORT_SHIFT_SP_RX_PAGE_SIZE                  0
#define SPORT_MASK_SP_RX_PAGE_SIZE                   ((u32)0x00000FFF << 0)                              /*!<R 0  Page Size setting */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_SPORT
 * @{
 * @brief rtl8735b_SPORT Register Declaration
 *****************************************************************************/
typedef struct {
	__O  uint32_t SPORT_SP_TX_FIFO_0 ;                     /*!<  SPORT TX FIFO Register register,  Address offset: 0x000 */
	__IO uint32_t SPORT_SP_CON ;                           /*!<  SPORT Control Register register,  Address offset: 0x004 */
	__IO uint32_t SPORT_SP_FIFO_EN_CLK_CON ;               /*!<   SPORT FIFO Enable and Clock Control Register register,  Address offset: 0x008 */
	__IO uint32_t SPORT_SP_FIFO_INTR_CON ;                 /*!<  SPORT FIFO Interrupt Control Register register,  Address offset: 0x00C */
	__I  uint32_t SPORT_SP_RX_FIFO_0 ;                     /*!<  SPORT RX FIFO_0 Register register,  Address offset: 0x010 */
	__I  uint32_t SPORT_SP_FIFO_CNT_STA ;                  /*!<  SPORT FIFO Counter Status Register register,  Address offset: 0x014 */
	__I  uint32_t SPORT_SP_TX_RX_ERR_STA ;                 /*!<  SPORT TX and RX Error Status Register register,  Address offset: 0x018 */
	__IO uint32_t SPORT_SP_TX_FRA_DIV ;                    /*!<  SPORT TX Fractional Divider Register register,  Address offset: 0x01C */
	__IO uint32_t SPORT_SP_LRCK_FIFO_TH_CON ;              /*!<   SPORT LRCK and FIFO Threshold Control Register register,  Address offset: 0x020 */
	__I  uint32_t SPORT_SP_FIFO_INTR_STA ;                 /*!<  SPORT FIFO Interrupt Status Register register,  Address offset: 0x024 */
	__IO uint32_t SPORT_SP_FORM_CON ;                      /*!<   SPORT Format Control register,  Address offset: 0x028 */
	__IO uint32_t SPORT_SP_RX_FRA_DIV ;                    /*!<  SPORT RX Fractional Divider Register register,  Address offset: 0x02C */
	__I  uint32_t SPORT_SP_RSVD_0 ;                        /*!<  SPORT Reserve Register 0 register,  Address offset: 0x030 */
	__I  uint32_t SPORT_SP_RSVD_1 ;                        /*!<  SPORT Reserve Register 1 register,  Address offset: 0x034 */
	__I  uint32_t SPORT_SP_RSVD_2 ;                        /*!<  SPORT Reserve Register 2 register,  Address offset: 0x038 */
	__IO uint32_t SPORT_SP_TX_SLOT_SELE ;                  /*!<  SPORT TX Slot Selection Register register,  Address offset: 0x03C */
	__O  uint32_t SPORT_SP_TX_FIFO_1 ;                     /*!<  SPORT TX FIFO_1 Register register,  Address offset: 0x040 */
	__IO uint32_t SPORT_SP_TX1_RX1_DAT_CON ;               /*!<  SPORT TX1 and RX1 Data Control Register register,  Address offset: 0x044 */
	__IO uint32_t SPORT_SP_TX1_RX1_FORM_CON ;              /*!<   SPORT TX1 and RX1 Format Control Register register,  Address offset: 0x048 */
	__I  uint32_t SPORT_SP_RSVD_3 ;                        /*!<  SPORT Reserve Register 3 register,  Address offset: 0x04C */
	__I  uint32_t SPORT_SP_RX_FIFO_1 ;                     /*!<  SPORT RX FIFO_1 Register register,  Address offset: 0x050 */
	__IO uint32_t SPORT_SP_RX_SLOT_SELE_0_3CH ;            /*!<  SPORT RX Slot Selection 0-3 Channel Register register,  Address offset: 0x054 */
	__IO uint32_t SPORT_SP_RX_SLOT_SELE_4_7CH ;            /*!<  SPORT RX Slot Selection 4-7 Channel Register register,  Address offset: 0x058 */
	__IO uint32_t SPORT_SP_ERR_CNT_CON ;                   /*!<  SPORT Error Count Control Register register,  Address offset: 0x05C */
	__IO uint32_t SPORT_SP_DMA_CON ;                       /*!<  SPORT DMA Control Register register,  Address offset: 0x060 */
	__IO uint32_t SPORT_SP_TX0_DMA_PP ;                    /*!<  SPORT TX0 DMA Page Pointer Register register,  Address offset: 0x064 */
	__IO uint32_t SPORT_SP_TX0_DMA_INT_EN ;                /*!<  SPORT TX0 DMA Interrupt Enable Register register,  Address offset: 0x068 */
	__O  uint32_t SPORT_SP_TX0_DMA_INT_STA ;               /*!<  SPORT TX0 DMA Interrupt Status Register register,  Address offset: 0x06C */
	__IO uint32_t SPORT_SP_TX1_DMA_PP ;                    /*!<  SPORT TX1 DMA Page Pointer Register register,  Address offset: 0x070 */
	__IO uint32_t SPORT_SP_TX1_DMA_INT_EN ;                /*!<  SPORT TX1 DMA Interrupt Enable Register register,  Address offset: 0x074 */
	__O  uint32_t SPORT_SP_TX1_DMA_INT_STA ;               /*!<  SPORT TX1 DMA Interrupt Status Register register,  Address offset: 0x078 */
	__IO uint32_t SPORT_SP_TX_PAGE_OWN ;                   /*!<  SPORT TX Page Own Register register,  Address offset: 0x07C */
	__IO uint32_t SPORT_SP_RX0_DMA_PP ;                    /*!<  SPORT RX0 DMA Page Pointer Register register,  Address offset: 0x080 */
	__IO uint32_t SPORT_SP_RX0_DMA_INT_EN ;                /*!<  SPORT RX0 DMA Interrupt Enable Register register,  Address offset: 0x084 */
	__O  uint32_t SPORT_SP_RX0_DMA_INT_STA ;               /*!<  SPORT RX0 DMA Interrupt Status Register register,  Address offset: 0x088 */
	__IO uint32_t SPORT_SP_RX1_DMA_PP ;                    /*!<  SPORT RX1 DMA Page Pointer Register register,  Address offset: 0x08C */
	__IO uint32_t SPORT_SP_RX1_DMA_INT_EN ;                /*!<  SPORT RX1 DMA Interrupt Enable Register register,  Address offset: 0x090 */
	__O  uint32_t SPORT_SP_RX1_DMA_INT_STA ;               /*!<  SPORT RX1 DMA Interrupt Status Register register,  Address offset: 0x094 */
	__IO uint32_t SPORT_SP_RX_PAGE_OWN ;                   /*!<  SPORT RX Page Own Register register,  Address offset: 0x098 */
	__IO uint32_t SPORT_SP_TX_AXIADDR_ERR ;                /*!<  SPORT TX AXI address access Error address record Register register,  Address offset: 0x09C */
	__IO uint32_t RSVD0[24];                               /*!<  Reserved,  Address offset:0xA0-0xFC */
	__I  uint32_t SPORT_SP_TX_MISC_ERR ;                   /*!<  SPORT TX AXI MISC. access Error record Register register,  Address offset: 0x100 */
	__IO uint32_t SPORT_SP_RX_AXIADDR_ERR ;                /*!<  SPORT RX AXI address access Error address record Register register,  Address offset: 0x104 */
	__I  uint32_t SPORT_SP_RX_MISC_ERR ;                   /*!<  SPORT RX AXI MISC. access Error record Register register,           Address offset: 0x108 */
} SPORT_TypeDef;
/** @} */

#endif
