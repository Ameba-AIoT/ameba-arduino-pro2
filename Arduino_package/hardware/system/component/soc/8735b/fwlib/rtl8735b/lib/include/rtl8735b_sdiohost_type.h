#ifndef _RTL8735B_SDIOHOST_TYPE_H_
#define _RTL8735B_SDIOHOST_TYPE_H_

/**************************************************************************//**
 * @defgroup SDIOHOST_SRAM_CTL
 * @brief  SRAM Configuration Register               (@ 0XA00)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_BUF_READ_SIZE                 24
#define SDIOHOST_MASK_BUF_READ_SIZE                  ((u32)0x00000003 << 24)                             /*!<R/W 0x2  Buffer Data Port Read Size (BDPRS) 2'b00: 1-byte access, port_a_rd_ptr increments by 1 2'b01: 2-byte access, port_a_rd_ptr increments by 2 2'b10: 4-byte access, port_a_rd_ptr increments by 4 2'b11: Decoding byte enable (BE[3:0]) bus signal If block-size is odd-byte, please set buf_read_size = 2'b00. */
#define SDIOHOST_SHIFT_AHBM_HPROT_CFG                20
#define SDIOHOST_MASK_AHBM_HPROT_CFG                 ((u32)0x0000000F << 20)                             /*!<R/W 0x1  AHB Bus Protection Control */
#define SDIOHOST_SHIFT_AHBM_HBURST_CFG               16
#define SDIOHOST_MASK_AHBM_HBURST_CFG                ((u32)0x0000000F << 16)                             /*!<R/W 0xF  2'b0001: ena_inc4: INCR4 Burst Type Enable 2'b0010: ena_inc8: INCR8 Burst Type Enable 2'b0100: ena_inc16: INCR16 Burst Type Enable 2'b1000: ena_incrx_align: Alignment Burst Type Enable */
#define SDIOHOST_SHIFT_LX_SWAP                       10
#define SDIOHOST_BIT_LX_SWAP                         ((u32)0x00000001 << 10)                             /*!<R/W 0  RSVD */
#define SDIOHOST_SHIFT_LX_BURST_SIZE                 8
#define SDIOHOST_MASK_LX_BURST_SIZE                  ((u32)0x00000003 << 8)                              /*!<R/W 0x2  2'b00: Burst length = 64 bytes (16 DWORD) 2'b01: Burst length = 128 bytes (32 DWORD) 2'b10: Burst length = 256 bytes (64 DWORD) 2'b11: Reserved */
#define SDIOHOST_SHIFT_MCU_BUF_ACCESS                1
#define SDIOHOST_MASK_MCU_BUF_ACCESS                 ((u32)0x00000003 << 1)                              /*!<R/W 0  in bit[0] = 1 condition, bit[2:1] = 'b00: buf access disable. bit[2:1] = 'b01: buff abs access enable, ring buffer address is direct mapping to 0x4005_CB00 ~ 0x4005_CEFF. (mcu_addr[15:0] = 0x0 ~ 0x3FF, mcu_cs_buf_absolute) 0x4005_CB30 (sram data [7:0]), 0x4005_CB31 (sram data [15:8]), 0x4005_CB32 (sram data [23:16]), 0x4005_CB33 (sram data [31:24]), address will auto increase by 4. bit[2:1] = 'b10: buf auto access enable, ring buffer could be accessed by register (mcu_addr = F30 ~ FE33 mcu_cs_buf_auto) bit[2:1] = 'b11: buf access disable. */
#define SDIOHOST_SHIFT_MCU_SEL                       0
#define SDIOHOST_BIT_MCU_SEL                         ((u32)0x00000001 << 0)                              /*!<R 0  These bits select the type of interface for the SDIO Host. 0: elbi interface (DWORD access for SDIO Host standard register) 1: mcu interface (byte access for SDIO IP register) */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_IP_CTL
 * @brief  SDIO IP Control Register                  (@ 0XA10)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_IP_ENDIAN_SEL                 4
#define SDIOHOST_BIT_IP_ENDIAN_SEL                   ((u32)0x00000001 << 4)                              /*!<R/W 0  0:Little; 1:Big */
#define SDIOHOST_SHIFT_L4_GATED_DISABLE_IP           3
#define SDIOHOST_BIT_L4_GATED_DISABLE_IP             ((u32)0x00000001 << 3)                              /*!<R/W 0  Disable L4 clock gated for ip */
#define SDIOHOST_SHIFT_DBUS_ENDIAN_SEL               2
#define SDIOHOST_BIT_DBUS_ENDIAN_SEL                 ((u32)0x00000001 << 2)                              /*!<R/W 0  0: Little; 1: Big */
#define SDIOHOST_SHIFT_L4_GATED_DISABLE              1
#define SDIOHOST_BIT_L4_GATED_DISABLE                ((u32)0x00000001 << 1)                              /*!<R/W 0  Disable L4 clock gated */
#define SDIOHOST_SHIFT_SUSPEND_N                     0
#define SDIOHOST_BIT_SUSPEND_N                       ((u32)0x00000001 << 0)                              /*!<R/W 0x1  suspend, low active */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_DBG1
 * @brief  Debug 1                                   (@ 0XA20)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_WRITE_ENABLE3                 9
#define SDIOHOST_BIT_WRITE_ENABLE3                   ((u32)0x00000001 << 9)                              /*!<W 0  Write enable for bit[8..6] */
#define SDIOHOST_SHIFT_SEL1                          6
#define SDIOHOST_MASK_SEL1                           ((u32)0x00000007 << 6)                              /*!<R/W 0  Select control of dbg_sel1.  */
#define SDIOHOST_SHIFT_WRITE_ENABLE2                 5
#define SDIOHOST_BIT_WRITE_ENABLE2                   ((u32)0x00000001 << 5)                              /*!<W 0  Write enable for bit[4..2] */
#define SDIOHOST_SHIFT_SEL0                          2
#define SDIOHOST_MASK_SEL0                           ((u32)0x00000007 << 2)                              /*!<R/W 0  Select control of dbg_sel0. */
#define SDIOHOST_SHIFT_WRITE_ENABLE1                 1
#define SDIOHOST_BIT_WRITE_ENABLE1                   ((u32)0x00000001 << 1)                              /*!<W 0  Write enable for bit0. */
#define SDIOHOST_SHIFT_ENABLE                        0
#define SDIOHOST_BIT_ENABLE                          ((u32)0x00000001 << 0)                              /*!<R/W 0  Debug Enable. */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_DBG2
 * @brief  Debug 2                                   (@ 0XA24)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_DBUS_DBG_SEL                  0
#define SDIOHOST_MASK_DBUS_DBG_SEL                   ((u32)0x00000007 << 0)                              /*!<R/W 0  sdio dbus dbg select */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_DBG3
 * @brief  Debug 3                                   (@ 0XA28)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_IP_DBG_SEL                    0
#define SDIOHOST_MASK_IP_DBG_SEL                     ((u32)0x000000FF << 0)                              /*!<R/W 0  sdio ip dbg select */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_ISR
 * @brief  Interrupt Service Routine                 (@ 0XA30)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_INT4                          4
#define SDIOHOST_BIT_INT4                            ((u32)0x00000001 << 4)                              /*!<R/W 0  SDIO Int4. SDIO IP Int. */
#define SDIOHOST_SHIFT_INT3                          3
#define SDIOHOST_BIT_INT3                            ((u32)0x00000001 << 3)                              /*!<R/W 0  SD Int3.SB1 wlast/rlast. */
#define SDIOHOST_SHIFT_RSVD1                         2
#define SDIOHOST_BIT_RSVD1                           ((u32)0x00000001 << 2)                              /*!<- 0  RSVD */
#define SDIOHOST_SHIFT_INT1                          1
#define SDIOHOST_BIT_INT1                            ((u32)0x00000001 << 1)                              /*!<R/W 0  SDIO Int1. DMA done. */
#define SDIOHOST_SHIFT_WRITE_DATA                    0
#define SDIOHOST_BIT_WRITE_DATA                      ((u32)0x00000001 << 0)                              /*!<W 0  1 to set, 0 to clear bit with 1. */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_ISREN
 * @brief  Interrupt Service Routine Enable          (@ 0XA34)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_INT4_EN                       4
#define SDIOHOST_BIT_INT4_EN                         ((u32)0x00000001 << 4)                              /*!<R/W 0  SDIO Int4 Enable, IP Int Enable */
#define SDIOHOST_SHIFT_INT3_EN                       3
#define SDIOHOST_BIT_INT3_EN                         ((u32)0x00000001 << 3)                              /*!<R/W 0  SDIO Int3 Enable, SB1 wlast/rlast Int Enable */
#define SDIOHOST_SHIFT_INT1_EN                       1
#define SDIOHOST_BIT_INT1_EN                         ((u32)0x00000001 << 1)                              /*!<R/W 0  SDIO Int1 Enable, Dma done Int Enable */
#define SDIOHOST_SHIFT_WRITE_DATA                    0
#define SDIOHOST_BIT_WRITE_DATA                      ((u32)0x00000001 << 0)                              /*!<W 0  1 to set, 0 to clear bit with 1. */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_CLKGEN_CTL
 * @brief  Clock Generator Control                   (@ 0XA44)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_SD30_SAMPLE_CHANGE            18
#define SDIOHOST_BIT_SD30_SAMPLE_CHANGE              ((u32)0x00000001 << 18)                             /*!<R/W 0  0: from sd30_sample_clk_src, 1: clk4M */
#define SDIOHOST_SHIFT_SD30_PUSH_CHANGE              17
#define SDIOHOST_BIT_SD30_PUSH_CHANGE                ((u32)0x00000001 << 17)                             /*!<R/W 0  0: from sd30_push_clk_src, clk4M */
#define SDIOHOST_SHIFT_CRC_CLK_CHANGE                16
#define SDIOHOST_BIT_CRC_CLK_CHANGE                  ((u32)0x00000001 << 16)                             /*!<R/W 0  0: from crc_clk_src, 1: clk4M */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_DMA_RST
 * @brief  DMA Reset                                 (@ 0XA50)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_DMABUS_INFO                   16
#define SDIOHOST_MASK_DMABUS_INFO                    ((u32)0x000000FF << 16)                             /*!<R 0   */
#define SDIOHOST_SHIFT_CUR_PE_DMA_FSM                8
#define SDIOHOST_MASK_CUR_PE_DMA_FSM                 ((u32)0x000000FF << 8)                              /*!<R 0x1   */
#define SDIOHOST_SHIFT_DMA_RST_ACK_CTL               3
#define SDIOHOST_BIT_DMA_RST_ACK_CTL                 ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_DMA_STOP                      2
#define SDIOHOST_BIT_DMA_STOP                        ((u32)0x00000001 << 2)                              /*!<R/W 0  Set this bit to stop dma, (suggest running dma_stop before doing software reset to avoid DMA hang) */
#define SDIOHOST_SHIFT_DMA_CFG                       1
#define SDIOHOST_BIT_DMA_CFG                         ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_DMA_RSTN                      0
#define SDIOHOST_BIT_DMA_RSTN                        ((u32)0x00000001 << 0)                              /*!<R/W 0x1  dma soft reset. */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_DUMMY_SYS1
 * @brief  sdioh_dma_rst                             (@ 0XA58)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_DMY                           1
#define SDIOHOST_MASK_DMY                            ((u32)0x7FFFFFFF << 1)                              /*!<R/W 0  Dummy bit. */
#define SDIOHOST_SHIFT_DMY0                          0
#define SDIOHOST_BIT_DMY0                            ((u32)0x00000001 << 0)                              /*!<R 0  Dummy bit, After ECOA2, bit [0] is read only type register, it presents PLL ready status  */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_CLK_DET_PLL0
 * @brief  sdioh_clk_det_pll0                        (@ 0XA5C)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_CLKDET_DONE_PLLSDIO           30
#define SDIOHOST_BIT_CLKDET_DONE_PLLSDIO             ((u32)0x00000001 << 30)                             /*!<R 0  Clock frequency detect status, 0: not finished, 1: done */
#define SDIOHOST_SHIFT_CLK_COUNT_PLLSDIO             13
#define SDIOHOST_MASK_CLK_COUNT_PLLSDIO              ((u32)0x0001FFFF << 13)                             /*!<R 0  Counter output of detected-clk */
#define SDIOHOST_SHIFT_REFCLK_COUNT_PLLSDIO          2
#define SDIOHOST_MASK_REFCLK_COUNT_PLLSDIO           ((u32)0x000007FF << 2)                              /*!<R 0  Counter output of ref-clk (27Mhz) */
#define SDIOHOST_SHIFT_SSC_USABLE_SDIO               0
#define SDIOHOST_BIT_SSC_USABLE_SDIO                 ((u32)0x00000001 << 0)                              /*!<R 0  PLL ready status */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_CLK_DET_PLL1
 * @brief  sdioh_clk_det_pll1                        (@ 0XA60)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_REG_COUNT_EN_PLLSDIO          1
#define SDIOHOST_BIT_REG_COUNT_EN_PLLSDIO            ((u32)0x00000001 << 1)                              /*!<R/W 0  Enable the counter of clk frequency detect, 0: disable, 1: start clock frequency detect */
#define SDIOHOST_SHIFT_REG_RSTN_PLLSDIO              0
#define SDIOHOST_BIT_REG_RSTN_PLLSDIO                ((u32)0x00000001 << 0)                              /*!<R/W 0  Reset, 0: reset */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_BIST_CTL
 * @brief  sdioh_bist_ctl                            (@ 0XA68)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_BIST_LS_HW_SEL                11
#define SDIOHOST_BIT_BIST_LS_HW_SEL                  ((u32)0x00000001 << 11)                             /*!<R 0   */
#define SDIOHOST_SHIFT_BIST_RING_BUF_DS_0            10
#define SDIOHOST_BIT_BIST_RING_BUF_DS_0              ((u32)0x00000001 << 10)                             /*!<R 0  DS0 */
#define SDIOHOST_SHIFT_BIST_RING_BUF_SD_0            9
#define SDIOHOST_BIT_BIST_RING_BUF_SD_0              ((u32)0x00000001 << 9)                              /*!<R 0  SD0 */
#define SDIOHOST_SHIFT_BIST_RING_BUF_RME_0           8
#define SDIOHOST_BIT_BIST_RING_BUF_RME_0             ((u32)0x00000001 << 8)                              /*!<R 0  RM0 enable */
#define SDIOHOST_SHIFT_BIST_RING_BUF_RM_0            4
#define SDIOHOST_MASK_BIST_RING_BUF_RM_0             ((u32)0x0000000F << 4)                              /*!<R 0  RM0 value */
#define SDIOHOST_SHIFT_BIST_LS                       0
#define SDIOHOST_MASK_BIST_LS                        ((u32)0x00000003 << 0)                              /*!<R 0  Bist ls bit. */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_DUMMY
 * @brief  sdioh_dummy                               (@ 0XAF0)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_DMY1                          0
#define SDIOHOST_MASK_DMY1                           ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Dummy bit. */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_MUX_CTL
 * @brief  sdioh_mux_ctl                             (@ 0XB6F)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_SDIO_POWER_DLY_EN             7
#define SDIOHOST_BIT_SDIO_POWER_DLY_EN               ((u32)0x00000001 << 7)                              /*!<R/W 1  sdio_power_dly_en 0: turn on sdio power entirely without delay 1: turn on sdio power sequentially, with 5ms delay */
#define SDIOHOST_SHIFT_CMD_USE_AFIFO_SYNC            6
#define SDIOHOST_BIT_CMD_USE_AFIFO_SYNC              ((u32)0x00000001 << 6)                              /*!<R/W 1  CMD use AFIFO sync */
#define SDIOHOST_SHIFT_UTUNING_ERR                   5
#define SDIOHOST_BIT_UTUNING_ERR                     ((u32)0x00000001 << 5)                              /*!<R/W 0  U Tuning error */
#define SDIOHOST_SHIFT_DATA_TOUT_CLK                 4
#define SDIOHOST_BIT_DATA_TOUT_CLK                   ((u32)0x00000001 << 4)                              /*!<R/W 0  Data Tout clk option */
#define SDIOHOST_SHIFT_CARD_INT_PERIOD_EN            3
#define SDIOHOST_BIT_CARD_INT_PERIOD_EN              ((u32)0x00000001 << 3)                              /*!<R/W 1  Card int period enable */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_BUS_TA_TIME
 * @brief  sdioh_bus_ta_time                         (@ 0XB74)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_STOP_CLK_CTRL_CYCLE           4
#define SDIOHOST_MASK_STOP_CLK_CTRL_CYCLE            ((u32)0x00000007 << 4)                              /*!<R/W 0x2   */
#define SDIOHOST_SHIFT_TURNAROUND_TIME_EN            3
#define SDIOHOST_BIT_TURNAROUND_TIME_EN              ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_BUS_TA_TIME                   0
#define SDIOHOST_MASK_BUS_TA_TIME                    ((u32)0x00000007 << 0)                              /*!<R/W 0x3  Bus_TA_Time These bits are used to define the number of SDCLK periods that HW should wait for SD bus turn-around time. After sending the end bit of command, HW will wait at least Bus_TA_Time to start to receive the start bit of response from card. After sending the end bit of write block, HW will also wait at least Bus_TA_Time to start to receive the start bit of CRC status from card. */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_SDIO_MMC_MODE
 * @brief  sdioh_sdio_mmc_mode                       (@ 0XB75)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_MMC_MODE                      3
#define SDIOHOST_BIT_MMC_MODE                        ((u32)0x00000001 << 3)                              /*!<RO 0  MMC Mode */
#define SDIOHOST_SHIFT_SDIO_SUPPORT                  2
#define SDIOHOST_BIT_SDIO_SUPPORT                    ((u32)0x00000001 << 2)                              /*!<RO 0  SDIO Support */
#define SDIOHOST_SHIFT_USE_DDR_TUNING                1
#define SDIOHOST_BIT_USE_DDR_TUNING                  ((u32)0x00000001 << 1)                              /*!<R/W 0  Use DDR Tuning */
#define SDIOHOST_SHIFT_USE_TX_TUNING                 0
#define SDIOHOST_BIT_USE_TX_TUNING                   ((u32)0x00000001 << 0)                              /*!<R/W 0x1  Use TX Tuning */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_RX_BEST_PHASE
 * @brief  sdioh_rx_best_phase                       (@ 0XB76)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_RX_BEST_PHASE                 0
#define SDIOHOST_MASK_RX_BEST_PHASE                  ((u32)0x0000001F << 0)                              /*!<RO 0  RX Best Phase */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_TX_BEST_PHASE
 * @brief  sdioh_tx_best_phase                       (@ 0XB77)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_TX_BEST_PHASE                 0
#define SDIOHOST_MASK_TX_BEST_PHASE                  ((u32)0x0000001F << 0)                              /*!<RO 0  TX Best Phase */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_RX_PHASE0
 * @brief  sdioh_rx_phase0                           (@ 0XB78)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_RX_PHASE_RESULT               0
#define SDIOHOST_MASK_RX_PHASE_RESULT                ((u32)0x000000FF << 0)                              /*!<RO 0  RX Phase Result [7:0] */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_RX_PHASE1
 * @brief  sdioh_rx_phase1                           (@ 0XB79)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_RX_PHASE_RESULT               0
#define SDIOHOST_MASK_RX_PHASE_RESULT                ((u32)0x000000FF << 0)                              /*!<RO 0  RX Phase Result [15:8] */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_RX_PHASE2
 * @brief  sdioh_rx_phase2                           (@ 0XB7A)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_RX_PHASE_RESULT               0
#define SDIOHOST_MASK_RX_PHASE_RESULT                ((u32)0x000000FF << 0)                              /*!<RO 0  RX Phase Result [23:16] */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_RX_PHASE3
 * @brief  sdioh_rx_phase3                           (@ 0XB7B)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_RX_PHASE_RESULT               0
#define SDIOHOST_MASK_RX_PHASE_RESULT                ((u32)0x000000FF << 0)                              /*!<RO 0  RX Phase Result [31:24] */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_TX_PHASE0
 * @brief  sdioh_tx_phase0                           (@ 0XB7C)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_TX_PHASE_RESULT               0
#define SDIOHOST_MASK_TX_PHASE_RESULT                ((u32)0x000000FF << 0)                              /*!<RO 0  TX Phase Result [7:0] */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_TX_PHASE1
 * @brief  sdioh_tx_phase1                           (@ 0XB7D)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_TX_PHASE_RESULT               0
#define SDIOHOST_MASK_TX_PHASE_RESULT                ((u32)0x000000FF << 0)                              /*!<RO 0  TX Phase Result [15:8] */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_TX_PHASE2
 * @brief  sdioh_tx_phase2                           (@ 0XB7E)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_TX_PHASE_RESULT               0
#define SDIOHOST_MASK_TX_PHASE_RESULT                ((u32)0x000000FF << 0)                              /*!<RO 0  TX Phase Result [23:16] */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_TX_PHASE3
 * @brief  sdioh_tx_phase3                           (@ 0XB7F)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_TX_PHASE_RESULT               0
#define SDIOHOST_MASK_TX_PHASE_RESULT                ((u32)0x000000FF << 0)                              /*!<RO 0  TX Phase Result [31:24] */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_PHASE_RST_TIME0
 * @brief  sdioh_phase_rst_time0                     (@ 0XB80)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_PHASE_RESET_TIME_CFG0         0
#define SDIOHOST_MASK_PHASE_RESET_TIME_CFG0          ((u32)0x000000FF << 0)                              /*!<R/W 0  Phase Reset time CFG [7:0] */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_PHASE_RST_TIME1
 * @brief  sdioh_phase_rst_time1                     (@ 0XB81)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_PHASE_RESET_TIME_CFG1         0
#define SDIOHOST_MASK_PHASE_RESET_TIME_CFG1          ((u32)0x0000000F << 0)                              /*!<R/W 0x1  Phase Reset time CFG [11:8] */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_TUNING_DUTY_CTL
 * @brief  sdioh_tuning_duty_ctl                     (@ 0XB83)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_STOP_SD_CLK_EN                4
#define SDIOHOST_BIT_STOP_SD_CLK_EN                  ((u32)0x00000001 << 4)                              /*!<R/W 0  Stop SDCLK enable */
#define SDIOHOST_SHIFT_CLEAR_INTERNAL_CLK_STABLE     3
#define SDIOHOST_BIT_CLEAR_INTERNAL_CLK_STABLE       ((u32)0x00000001 << 3)                              /*!<R/W 0  Clear Internal CLK Stable */
#define SDIOHOST_SHIFT_RX_WAIT_AFIFO_RST_EN          2
#define SDIOHOST_BIT_RX_WAIT_AFIFO_RST_EN            ((u32)0x00000001 << 2)                              /*!<R/W 0  Rx wait AFIFO Reset enable */
#define SDIOHOST_SHIFT_USE_RX_DUTY_CTL               1
#define SDIOHOST_BIT_USE_RX_DUTY_CTL                 ((u32)0x00000001 << 1)                              /*!<R/W 0  Use RX Duty Control */
#define SDIOHOST_SHIFT_USE_TX_DUTY_CTL               0
#define SDIOHOST_BIT_USE_TX_DUTY_CTL                 ((u32)0x00000001 << 0)                              /*!<R/W 0  Use TX Duty Control */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_TUNING_SOLN
 * @brief  sdioh_tuning_soln                         (@ 0XB84)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_R_WAIT_NOSTOP_SD_CLK_EN       7
#define SDIOHOST_BIT_R_WAIT_NOSTOP_SD_CLK_EN         ((u32)0x00000001 << 7)                              /*!<R/W 0x1  Read wait no stop SD CLK enable */
#define SDIOHOST_SHIFT_SD_CLK_POLARITY_SWAP          6
#define SDIOHOST_BIT_SD_CLK_POLARITY_SWAP            ((u32)0x00000001 << 6)                              /*!<R/W 0  SDIO SDCLK polarity swap */
#define SDIOHOST_SHIFT_DDR_DIGITAL_SOLN              5
#define SDIOHOST_BIT_DDR_DIGITAL_SOLN                ((u32)0x00000001 << 5)                              /*!<R/W 0  SDIO DDR Digital solution */
#define SDIOHOST_SHIFT_DDR_FW_SOLN                   4
#define SDIOHOST_BIT_DDR_FW_SOLN                     ((u32)0x00000001 << 4)                              /*!<R/W 0  SDIO DDR FW solution */
#define SDIOHOST_SHIFT_DDR_PUSH_TYPE                 3
#define SDIOHOST_BIT_DDR_PUSH_TYPE                   ((u32)0x00000001 << 3)                              /*!<R/W 0x1  SDIO DDR Push Type */
#define SDIOHOST_SHIFT_DDR_DAT_PUSH_PT               2
#define SDIOHOST_BIT_DDR_DAT_PUSH_PT                 ((u32)0x00000001 << 2)                              /*!<R/W 0  SDIO DDR DAT Push Point 0: set-up time: 1/4 SDCLK cycle; hold time: 1/4 SDCLK cycle, sd20_dato (trigged by crc_clk rising edge) 1: set-up time: 1/2 SDCLK cycle; hold time: 0 SDCLK cycle, sd30_dato (trigged by crc_clk falling edge) */
#define SDIOHOST_SHIFT_DDR_CMD_PUSH_PY               1
#define SDIOHOST_BIT_DDR_CMD_PUSH_PY                 ((u32)0x00000001 << 1)                              /*!<R/W 0x1  SDIO DDR CMD Push Point 0: output at falling edge of SDCLK(set-up time: 1/2 SDCLK cycle; hold time: 1/2 SDCLK cycle), sd30_cmdo (trigged by crc_clk falling edge) 1: output is ahead by 1/4 SDCLK period(set-up time: 3/4 SDCLK cycle; hold time: 1/4 SDCLK cycle), sd20_cmdo (trigged by crc_clk rising edge) */
#define SDIOHOST_SHIFT_SD20_PUSH_PT                  0
#define SDIOHOST_BIT_SD20_PUSH_PT                    ((u32)0x00000001 << 0)                              /*!<R/W 0  SDIO SD20 Push Point 0: output at falling edge of SDCLK(set-up time: 1/2 SDCLK cycle; hold time: 1/2 SDCLK cycle), sd20_cmdo/sd20_dato (trigged by crc_clk rising edge) 1: output is ahead by 1/4 SDCLK period(set-up time: 3/4 SDCLK cycle; hold time: 1/4 SDCLK cycle), sd30_cmdo/sd30_dato (trigged by crc_clk falling edge) */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_SAMPLE_PT_CTL
 * @brief  sdioh_sample_pt_ctl                       (@ 0XB85)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_SD20_SAMPLE_PT_SEL            3
#define SDIOHOST_BIT_SD20_SAMPLE_PT_SEL              ((u32)0x00000001 << 3)                              /*!<R/W 0  Sample Point Selection for SD20 CMD / DATA 0: sample at rising edge of SDCLK 1: sample point is delayed by 1/4 SDCLK period */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_DMA_BUF_CTL
 * @brief  sdioh_dma_buf_ctl                         (@ 0XB86)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_BUF_FLUSH_CTL_PIO             6
#define SDIOHOST_BIT_BUF_FLUSH_CTL_PIO               ((u32)0x00000001 << 6)                              /*!<R/W 1   */
#define SDIOHOST_SHIFT_BUF_FLUSH_CTL                 5
#define SDIOHOST_BIT_BUF_FLUSH_CTL                   ((u32)0x00000001 << 5)                              /*!<R/W 1   */
#define SDIOHOST_SHIFT_BUF_ROOM_VLD_CTL              4
#define SDIOHOST_BIT_BUF_ROOM_VLD_CTL                ((u32)0x00000001 << 4)                              /*!<R/W 1   */
#define SDIOHOST_SHIFT_AUTO_CMD23_INHISHIFT_CTL      2
#define SDIOHOST_BIT_AUTO_CMD23_INHIBIT_CTL          ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_AUTO_CMD23_COMPLETE_CTL       1
#define SDIOHOST_BIT_AUTO_CMD23_COMPLETE_CTL         ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_AUTO_CMD23_ERR_CTL            0
#define SDIOHOST_BIT_AUTO_CMD23_ERR_CTL              ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_SDMA_SYS_ADDR
 * @brief  SDMA System Address / Argument 2 Register (@ 0XC00)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_SDMA_SYS_ADDR                 0
#define SDIOHOST_MASK_SDMA_SYS_ADDR                  ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_BLK_SZ
 * @brief  Block Size Register                       (@ 0XC04)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_HOST_SDMA_BUFF_BOUNDARY       12
#define SDIOHOST_MASK_HOST_SDMA_BUFF_BOUNDARY        ((u32)0x00000007 << 12)                             /*!<R/W 0   */
#define SDIOHOST_SHIFT_XFER_BLK_SZ                   0
#define SDIOHOST_MASK_XFER_BLK_SZ                    ((u32)0x00000FFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_BLK_CNT
 * @brief  Block Count Register                      (@ 0XC06)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_BLK_CNT_CURR                  0
#define SDIOHOST_MASK_BLK_CNT_CURR                   ((u32)0x0000FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_CMD_ARG1
 * @brief  Argument 1 Register                       (@ 0XC08)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_CMD_ARG1                      0
#define SDIOHOST_MASK_CMD_ARG1                       ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_XFER_MODE
 * @brief   Transfer Mode Register                   (@ 0XC0C)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_MULTI_SINGLE_BLK_SEL          5
#define SDIOHOST_BIT_MULTI_SINGLE_BLK_SEL            ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_XFER_DIR_SEL                  4
#define SDIOHOST_BIT_XFER_DIR_SEL                    ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_AUTO_CMD_EN                   2
#define SDIOHOST_MASK_AUTO_CMD_EN                    ((u32)0x00000003 << 2)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_BLK_CNT_EN                    1
#define SDIOHOST_BIT_BLK_CNT_EN                      ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_DMA_EN                        0
#define SDIOHOST_BIT_DMA_EN                          ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_CMD
 * @brief  Command Register                          (@ 0XC0E)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_CMD_IDX                       8
#define SDIOHOST_MASK_CMD_IDX                        ((u32)0x0000003F << 8)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CMD_TYPE                      6
#define SDIOHOST_MASK_CMD_TYPE                       ((u32)0x00000003 << 6)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_DATA_PRESENT_SEL              5
#define SDIOHOST_BIT_DATA_PRESENT_SEL                ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CMD_IDX_CHK_EN                4
#define SDIOHOST_BIT_CMD_IDX_CHK_EN                  ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CMD_CRC_CHK_EN                3
#define SDIOHOST_BIT_CMD_CRC_CHK_EN                  ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_RESP_TYPE_SEL                 0
#define SDIOHOST_MASK_RESP_TYPE_SEL                  ((u32)0x00000003 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_RESP0
 * @brief  Response Register                         (@ 0XC10)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_CMD_RESP                      0
#define SDIOHOST_MASK_CMD_RESP                       ((u32)0xFFFFFFFF << 0)                              /*!<RO 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_RESP1
 * @brief  Response Register                         (@ 0XC14)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_CMD_RESP                      0
#define SDIOHOST_MASK_CMD_RESP                       ((u32)0xFFFFFFFF << 0)                              /*!<RO 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_RESP2
 * @brief  Response Register                         (@ 0XC18)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_CMD_RESP                      0
#define SDIOHOST_MASK_CMD_RESP                       ((u32)0xFFFFFFFF << 0)                              /*!<RO 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_RESP3
 * @brief  Response Register                         (@ 0XC1C)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_CMD_RESP                      0
#define SDIOHOST_MASK_CMD_RESP                       ((u32)0xFFFFFFFF << 0)                              /*!<RO 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_BUFFER_PORT_DATA
 * @brief   Buffer Data Port Register                (@ 0XC20)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_BUFF_DATA                     0
#define SDIOHOST_MASK_BUFF_DATA                      ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_PRESENT_STATE
 * @brief  ADC Debug Select Register                 (@ 0XC24)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_CMD_LINE_SIG_LVL              24
#define SDIOHOST_BIT_CMD_LINE_SIG_LVL                ((u32)0x00000001 << 24)                             /*!<RO 0   */
#define SDIOHOST_SHIFT_DAT_LINE_SIG_LVL              20
#define SDIOHOST_MASK_DAT_LINE_SIG_LVL               ((u32)0x0000000F << 20)                             /*!<RO 0   */
#define SDIOHOST_SHIFT_WP_SWITCH_PIN_LVL             19
#define SDIOHOST_BIT_WP_SWITCH_PIN_LVL               ((u32)0x00000001 << 19)                             /*!<RO 0   */
#define SDIOHOST_SHIFT_CD_PIN_LEVEL                  18
#define SDIOHOST_BIT_CD_PIN_LEVEL                    ((u32)0x00000001 << 18)                             /*!<RO 0   */
#define SDIOHOST_SHIFT_CARD_STATE_STABLE             17
#define SDIOHOST_BIT_CARD_STATE_STABLE               ((u32)0x00000001 << 17)                             /*!<RO 0   */
#define SDIOHOST_SHIFT_CARD_INSERTED                 16
#define SDIOHOST_BIT_CARD_INSERTED                   ((u32)0x00000001 << 16)                             /*!<RO 0   */
#define SDIOHOST_SHIFT_BUFF_READ_EN                  11
#define SDIOHOST_BIT_BUFF_READ_EN                    ((u32)0x00000001 << 11)                             /*!<RO 0   */
#define SDIOHOST_SHIFT_BUFF_WRITE_EN                 10
#define SDIOHOST_BIT_BUFF_WRITE_EN                   ((u32)0x00000001 << 10)                             /*!<RO 0   */
#define SDIOHOST_SHIFT_READ_XFER_ACTIVE              9
#define SDIOHOST_BIT_READ_XFER_ACTIVE                ((u32)0x00000001 << 9)                              /*!<RO 0   */
#define SDIOHOST_SHIFT_WRITE_XFER_ACTIVE             8
#define SDIOHOST_BIT_WRITE_XFER_ACTIVE               ((u32)0x00000001 << 8)                              /*!<RO 0   */
#define SDIOHOST_SHIFT_RETUNE_REQ                    3
#define SDIOHOST_BIT_RETUNE_REQ                      ((u32)0x00000001 << 3)                              /*!<RO 0   */
#define SDIOHOST_SHIFT_DAT_LINE_ACTIVE               2
#define SDIOHOST_BIT_DAT_LINE_ACTIVE                 ((u32)0x00000001 << 2)                              /*!<RO 0   */
#define SDIOHOST_SHIFT_CMD_INHISHIFT_DAT             1
#define SDIOHOST_BIT_CMD_INHIBIT_DAT                 ((u32)0x00000001 << 1)                              /*!<RO 0   */
#define SDIOHOST_SHIFT_CMD_INHISHIFT_CMD             0
#define SDIOHOST_BIT_CMD_INHIBIT_CMD                 ((u32)0x00000001 << 0)                              /*!<RO 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_HOST_CTL_1_REG
 * @brief  Host Control 1 Register                   (@ 0XC28)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_CD_SIG_SEL                    7
#define SDIOHOST_BIT_CD_SIG_SEL                      ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CD_TEST_LVL                   6
#define SDIOHOST_BIT_CD_TEST_LVL                     ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_EXTENDED_DATA_XFER_WIDTH      5
#define SDIOHOST_BIT_EXTENDED_DATA_XFER_WIDTH        ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_DMA_SEL                       3
#define SDIOHOST_MASK_DMA_SEL                        ((u32)0x00000003 << 3)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_HS_EN                         2
#define SDIOHOST_BIT_HS_EN                           ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_DATA_XFER_WIDTH               1
#define SDIOHOST_BIT_DATA_XFER_WIDTH                 ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_LED_CTL                       0
#define SDIOHOST_BIT_LED_CTL                         ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_PWR_CTL
 * @brief  Power Control Register                    (@ 0XC29)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_SD_BUS_VOLTAGE_SEL            1
#define SDIOHOST_MASK_SD_BUS_VOLTAGE_SEL             ((u32)0x00000007 << 1)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_SD_BUS_PWR                    0
#define SDIOHOST_BIT_SD_BUS_PWR                      ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_BLK_GAP_CTL
 * @brief  Block Gap Control Register                (@ 0XC2A)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_INT_AT_BLK_GAP                3
#define SDIOHOST_BIT_INT_AT_BLK_GAP                  ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_READ_WAIT_CTL                 2
#define SDIOHOST_BIT_READ_WAIT_CTL                   ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CONT_REQ                      1
#define SDIOHOST_BIT_CONT_REQ                        ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_STOP_AT_BLK_REQ               0
#define SDIOHOST_BIT_STOP_AT_BLK_REQ                 ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_WAKEUP_CTL
 * @brief  Wakeup Control Register                   (@ 0XC2B)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_WAKEUP_EVENT_CARD_REMOVE_EN   2
#define SDIOHOST_BIT_WAKEUP_EVENT_CARD_REMOVE_EN     ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_WAKEUP_EVENT_CARD_INSERT_EN   1
#define SDIOHOST_BIT_WAKEUP_EVENT_CARD_INSERT_EN     ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_WAKEUP_EVENT_CARD_INT_EN      0
#define SDIOHOST_BIT_WAKEUP_EVENT_CARD_INT_EN        ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_CLK_CTL
 * @brief   Clock Control Register                   (@ 0XC2C)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_SDCLK_FREQ_SEL                8
#define SDIOHOST_MASK_SDCLK_FREQ_SEL                 ((u32)0x000000FF << 8)                              /*!<R/W 0    */
#define SDIOHOST_SHIFT_SDCLK_FREQ_SEL_UPPER          6
#define SDIOHOST_MASK_SDCLK_FREQ_SEL_UPPER           ((u32)0x00000003 << 6)                              /*!<R/W 0    */
#define SDIOHOST_SHIFT_CLK_GEN_SEL                   5
#define SDIOHOST_BIT_CLK_GEN_SEL                     ((u32)0x00000001 << 5)                              /*!<R/W 0    */
#define SDIOHOST_SHIFT_SDCLK_EN                      2
#define SDIOHOST_BIT_SDCLK_EN                        ((u32)0x00000001 << 2)                              /*!<R/W 0    */
#define SDIOHOST_SHIFT_INTERNAL_CLK_STABLE           1
#define SDIOHOST_BIT_INTERNAL_CLK_STABLE             ((u32)0x00000001 << 1)                              /*!<RO 0   */
#define SDIOHOST_SHIFT_INTERNAL_CLK_EN               0
#define SDIOHOST_BIT_INTERNAL_CLK_EN                 ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_TIMEOUT_CTL
 * @brief  Timeout Control Register                  (@ 0XC2E)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_DATA_TIMEOUT_CNT_VAL          0
#define SDIOHOST_MASK_DATA_TIMEOUT_CNT_VAL           ((u32)0x0000000F << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_SW_RST
 * @brief  Software Reset Register                   (@ 0XC2F)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_SW_RST_DAT                    2
#define SDIOHOST_BIT_SW_RST_DAT                      ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_SW_RST_CMD                    1
#define SDIOHOST_BIT_SW_RST_CMD                      ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_SW_RST_ALL                    0
#define SDIOHOST_BIT_SW_RST_ALL                      ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_NORMAL_INT_STATUS
 * @brief  Normal Interrupt Status Register          (@ 0XC30)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_ERR_INT                       15
#define SDIOHOST_BIT_ERR_INT                         ((u32)0x00000001 << 15)                             /*!<RO 0   */
#define SDIOHOST_SHIFT_RETUNING_EVENT                12
#define SDIOHOST_BIT_RETUNING_EVENT                  ((u32)0x00000001 << 12)                             /*!<RO 0   */
#define SDIOHOST_SHIFT_INT_C                         11
#define SDIOHOST_BIT_INT_C                           ((u32)0x00000001 << 11)                             /*!<RO 0   */
#define SDIOHOST_SHIFT_INT_B                         10
#define SDIOHOST_BIT_INT_B                           ((u32)0x00000001 << 10)                             /*!<RO 0   */
#define SDIOHOST_SHIFT_INT_A                         9
#define SDIOHOST_BIT_INT_A                           ((u32)0x00000001 << 9)                              /*!<RO 0   */
#define SDIOHOST_SHIFT_CARD_INT                      8
#define SDIOHOST_BIT_CARD_INT                        ((u32)0x00000001 << 8)                              /*!<RO 0   */
#define SDIOHOST_SHIFT_CARD_REMOVAL                  7
#define SDIOHOST_BIT_CARD_REMOVAL                    ((u32)0x00000001 << 7)                              /*!<R/W1C 0   */
#define SDIOHOST_SHIFT_CARD_INSERTION                6
#define SDIOHOST_BIT_CARD_INSERTION                  ((u32)0x00000001 << 6)                              /*!<R/W1C 0   */
#define SDIOHOST_SHIFT_BUFF_READ_READY               5
#define SDIOHOST_BIT_BUFF_READ_READY                 ((u32)0x00000001 << 5)                              /*!<R/W1C 0   */
#define SDIOHOST_SHIFT_BUFF_WRITE_READY              4
#define SDIOHOST_BIT_BUFF_WRITE_READY                ((u32)0x00000001 << 4)                              /*!<R/W1C 0   */
#define SDIOHOST_SHIFT_DMA_INT                       3
#define SDIOHOST_BIT_DMA_INT                         ((u32)0x00000001 << 3)                              /*!<R/W1C 0   */
#define SDIOHOST_SHIFT_BLK_GAP_EVENT                 2
#define SDIOHOST_BIT_BLK_GAP_EVENT                   ((u32)0x00000001 << 2)                              /*!<R/W1C 0   */
#define SDIOHOST_SHIFT_XFER_COMPLETE                 1
#define SDIOHOST_BIT_XFER_COMPLETE                   ((u32)0x00000001 << 1)                              /*!<R/W1C 0   */
#define SDIOHOST_SHIFT_CMD_COMPLETE                  0
#define SDIOHOST_BIT_CMD_COMPLETE                    ((u32)0x00000001 << 0)                              /*!<R/W1C 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_ERR_INT_STATUS
 * @brief  Error Interrupt Status Register           (@ 0XC32)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_VENDOR_SPECIFIC_ERR           12
#define SDIOHOST_MASK_VENDOR_SPECIFIC_ERR            ((u32)0x0000000F << 12)                             /*!<R/W1C 0   */
#define SDIOHOST_SHIFT_TUNING_ERR                    10
#define SDIOHOST_BIT_TUNING_ERR                      ((u32)0x00000001 << 10)                             /*!<R/W1C 0   */
#define SDIOHOST_SHIFT_ADMA_ERR                      9
#define SDIOHOST_BIT_ADMA_ERR                        ((u32)0x00000001 << 9)                              /*!<R/W1C 0   */
#define SDIOHOST_SHIFT_AUTO_CMD_ERR                  8
#define SDIOHOST_BIT_AUTO_CMD_ERR                    ((u32)0x00000001 << 8)                              /*!<R/W1C 0   */
#define SDIOHOST_SHIFT_CURRENT_LIMIT_ERR             7
#define SDIOHOST_BIT_CURRENT_LIMIT_ERR               ((u32)0x00000001 << 7)                              /*!<R/W1C 0   */
#define SDIOHOST_SHIFT_DATA_END_SHIFT_ERR            6
#define SDIOHOST_BIT_DATA_END_BIT_ERR                ((u32)0x00000001 << 6)                              /*!<R/W1C 0   */
#define SDIOHOST_SHIFT_DATA_CRC_ERR                  5
#define SDIOHOST_BIT_DATA_CRC_ERR                    ((u32)0x00000001 << 5)                              /*!<R/W1C 0   */
#define SDIOHOST_SHIFT_DATA_TIMEOUT_ERR              4
#define SDIOHOST_BIT_DATA_TIMEOUT_ERR                ((u32)0x00000001 << 4)                              /*!<R/W1C 0   */
#define SDIOHOST_SHIFT_CMD_IDX_ERR                   3
#define SDIOHOST_BIT_CMD_IDX_ERR                     ((u32)0x00000001 << 3)                              /*!<R/W1C 0   */
#define SDIOHOST_SHIFT_CMD_END_SHIFT_ERR             2
#define SDIOHOST_BIT_CMD_END_BIT_ERR                 ((u32)0x00000001 << 2)                              /*!<R/W1C 0   */
#define SDIOHOST_SHIFT_CMD_CRC_ERR                   1
#define SDIOHOST_BIT_CMD_CRC_ERR                     ((u32)0x00000001 << 1)                              /*!<R/W1C 0   */
#define SDIOHOST_SHIFT_CMD_TIMEOUT_ERR               0
#define SDIOHOST_BIT_CMD_TIMEOUT_ERR                 ((u32)0x00000001 << 0)                              /*!<R/W1C 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_NORMAL_INT_STATUS_EN
 * @brief  Normal Interrupt Status Enable Register   (@ 0XC34)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_FIXED_TO_0                    15
#define SDIOHOST_BIT_FIXED_TO_0                      ((u32)0x00000001 << 15)                             /*!<RO 0   */
#define SDIOHOST_SHIFT_RETUNE_EVENT_STATUS_EN        12
#define SDIOHOST_BIT_RETUNE_EVENT_STATUS_EN          ((u32)0x00000001 << 12)                             /*!<R/W 0   */
#define SDIOHOST_SHIFT_INT_C_STATUS_EN               11
#define SDIOHOST_BIT_INT_C_STATUS_EN                 ((u32)0x00000001 << 11)                             /*!<R/W 0   */
#define SDIOHOST_SHIFT_INT_B_STATUS_EN               10
#define SDIOHOST_BIT_INT_B_STATUS_EN                 ((u32)0x00000001 << 10)                             /*!<R/W 0   */
#define SDIOHOST_SHIFT_INT_A_STATUS_EN               9
#define SDIOHOST_BIT_INT_A_STATUS_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CARD_INT_STATUS_EN            8
#define SDIOHOST_BIT_CARD_INT_STATUS_EN              ((u32)0x00000001 << 8)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CARD_REMOVAL_STATUS_EN        7
#define SDIOHOST_BIT_CARD_REMOVAL_STATUS_EN          ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CARD_INSERT_STATUS_EN         6
#define SDIOHOST_BIT_CARD_INSERT_STATUS_EN           ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_BUFF_READ_READY_STATUS_EN     5
#define SDIOHOST_BIT_BUFF_READ_READY_STATUS_EN       ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_BUFF_WRITE_READY_STATUS_EN    4
#define SDIOHOST_BIT_BUFF_WRITE_READY_STATUS_EN      ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_DMA_INT_STATUS_EN             3
#define SDIOHOST_BIT_DMA_INT_STATUS_EN               ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_BLK_GAP_EVENT_STATUS_EN       2
#define SDIOHOST_BIT_BLK_GAP_EVENT_STATUS_EN         ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_XFER_COMPLETE_STATUS_EN       1
#define SDIOHOST_BIT_XFER_COMPLETE_STATUS_EN         ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CMD_COMPLETE_STATUS_EN        0
#define SDIOHOST_BIT_CMD_COMPLETE_STATUS_EN          ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_ERR_INT_STATUS_EN
 * @brief   Error Interrupt Status Enable Register   (@ 0XC36)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_VENDOR_SPECIFIC_ERR_STATUS_EN 12
#define SDIOHOST_MASK_VENDOR_SPECIFIC_ERR_STATUS_EN  ((u32)0x0000000F << 12)                             /*!<R/W 0   */
#define SDIOHOST_SHIFT_TUNING_ERR_STATUS_EN          10
#define SDIOHOST_BIT_TUNING_ERR_STATUS_EN            ((u32)0x00000001 << 10)                             /*!<R/W 0   */
#define SDIOHOST_SHIFT_ADMA_ERR_STATUS_EN            9
#define SDIOHOST_BIT_ADMA_ERR_STATUS_EN              ((u32)0x00000001 << 9)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_AUTO_CMD_ERR_STATUS_EN        8
#define SDIOHOST_BIT_AUTO_CMD_ERR_STATUS_EN          ((u32)0x00000001 << 8)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CURRENT_LIMIT_ERR_STATUS_EN   7
#define SDIOHOST_BIT_CURRENT_LIMIT_ERR_STATUS_EN     ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_DATA_END_SHIFT_ERR_STATUS_EN  6
#define SDIOHOST_BIT_DATA_END_BIT_ERR_STATUS_EN      ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_DATA_CRC_ERR_STATUS_EN        5
#define SDIOHOST_BIT_DATA_CRC_ERR_STATUS_EN          ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_DATA_TIMEOUT_ERR_STATUS_EN    4
#define SDIOHOST_BIT_DATA_TIMEOUT_ERR_STATUS_EN      ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CMD_IDX_ERR_STATUS_EN         3
#define SDIOHOST_BIT_CMD_IDX_ERR_STATUS_EN           ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CMD_END_SHIFT_ERR_STATUS_EN   2
#define SDIOHOST_BIT_CMD_END_BIT_ERR_STATUS_EN       ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CMD_CRC_ERR_STATUS_EN         1
#define SDIOHOST_BIT_CMD_CRC_ERR_STATUS_EN           ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CMD_TIMEOUT_ERR_STATUS_EN     0
#define SDIOHOST_BIT_CMD_TIMEOUT_ERR_STATUS_EN       ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_NORMAL_SIG_EN
 * @brief  Normal Interrupt Signal Enable Register   (@ 0XC38)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_FIXED_TO_0                    15
#define SDIOHOST_BIT_FIXED_TO_0                      ((u32)0x00000001 << 15)                             /*!<RO 0   */
#define SDIOHOST_SHIFT_RETUNE_EVENT_SIGNAL_EN        12
#define SDIOHOST_BIT_RETUNE_EVENT_SIGNAL_EN          ((u32)0x00000001 << 12)                             /*!<R/W 0   */
#define SDIOHOST_SHIFT_INT_C_STATUS_SIGNAL_EN        11
#define SDIOHOST_BIT_INT_C_STATUS_SIGNAL_EN          ((u32)0x00000001 << 11)                             /*!<R/W 0   */
#define SDIOHOST_SHIFT_INT_B_STATUS_SIGNAL_EN        10
#define SDIOHOST_BIT_INT_B_STATUS_SIGNAL_EN          ((u32)0x00000001 << 10)                             /*!<R/W 0   */
#define SDIOHOST_SHIFT_INT_A_SIGNAL_EN               9
#define SDIOHOST_BIT_INT_A_SIGNAL_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CARD_INT_SIGNAL_EN            8
#define SDIOHOST_BIT_CARD_INT_SIGNAL_EN              ((u32)0x00000001 << 8)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CARD_REMOVAL_SIGNAL_EN        7
#define SDIOHOST_BIT_CARD_REMOVAL_SIGNAL_EN          ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CARD_INSERT_SIGNAL_EN         6
#define SDIOHOST_BIT_CARD_INSERT_SIGNAL_EN           ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_BUFF_READ_READY_SIGNAL_EN     5
#define SDIOHOST_BIT_BUFF_READ_READY_SIGNAL_EN       ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_BUFF_WRITE_READY_SIGNAL_EN    4
#define SDIOHOST_BIT_BUFF_WRITE_READY_SIGNAL_EN      ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_DMA_INT_SIGNAL_EN             3
#define SDIOHOST_BIT_DMA_INT_SIGNAL_EN               ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_BLK_GAP_EVENT_SIGNAL_EN       2
#define SDIOHOST_BIT_BLK_GAP_EVENT_SIGNAL_EN         ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_XFER_COMPLETE_SIGNAL_EN       1
#define SDIOHOST_BIT_XFER_COMPLETE_SIGNAL_EN         ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CMD_COMPLETE_SIGNAL_EN        0
#define SDIOHOST_BIT_CMD_COMPLETE_SIGNAL_EN          ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_ERR_SIG_EN
 * @brief  Error Interrupt Signal Enable Register    (@ 0XC3A)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_VENDOR_SPECIFIC_ERR_SIGNAL_EN 12
#define SDIOHOST_MASK_VENDOR_SPECIFIC_ERR_SIGNAL_EN  ((u32)0x0000000F << 12)                             /*!<R/W 0   */
#define SDIOHOST_SHIFT_TUNING_ERR_SIGNAL_EN          10
#define SDIOHOST_BIT_TUNING_ERR_SIGNAL_EN            ((u32)0x00000001 << 10)                             /*!<R/W 0   */
#define SDIOHOST_SHIFT_ADMA_ERR_SIGNAL_EN            9
#define SDIOHOST_BIT_ADMA_ERR_SIGNAL_EN              ((u32)0x00000001 << 9)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_AUTO_CMD_ERR_SIGNAL_EN        8
#define SDIOHOST_BIT_AUTO_CMD_ERR_SIGNAL_EN          ((u32)0x00000001 << 8)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CURRENT_LIMIT_ERR_SIGNAL_EN   7
#define SDIOHOST_BIT_CURRENT_LIMIT_ERR_SIGNAL_EN     ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_DATA_END_SHIFT_ERR_SIGNAL_EN  6
#define SDIOHOST_BIT_DATA_END_BIT_ERR_SIGNAL_EN      ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_DATA_CRC_ERR_SIGNAL_EN        5
#define SDIOHOST_BIT_DATA_CRC_ERR_SIGNAL_EN          ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_DATA_TIMEOUT_ERR_SIGNAL_EN    4
#define SDIOHOST_BIT_DATA_TIMEOUT_ERR_SIGNAL_EN      ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CMD_IDX_ERR_SIGNAL_EN         3
#define SDIOHOST_BIT_CMD_IDX_ERR_SIGNAL_EN           ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CMD_END_SHIFT_ERR_SIGNAL_EN   2
#define SDIOHOST_BIT_CMD_END_BIT_ERR_SIGNAL_EN       ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CMD_CRC_ERR_SIGNAL_EN         1
#define SDIOHOST_BIT_CMD_CRC_ERR_SIGNAL_EN           ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_CMD_TIMEOUT_ERR_SIGNAL_EN     0
#define SDIOHOST_BIT_CMD_TIMEOUT_ERR_SIGNAL_EN       ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_AUTO_CMD_ERR_STATUS
 * @brief  Auto CMD Error Status Register            (@ 0XC3C)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_CMD_NOT_ISSUED_ERR            7
#define SDIOHOST_BIT_CMD_NOT_ISSUED_ERR              ((u32)0x00000001 << 7)                              /*!<RO 0   */
#define SDIOHOST_SHIFT_IDX_ERR                       4
#define SDIOHOST_BIT_IDX_ERR                         ((u32)0x00000001 << 4)                              /*!<RO 0   */
#define SDIOHOST_SHIFT_END_SHIFT_ERR                 3
#define SDIOHOST_BIT_END_BIT_ERR                     ((u32)0x00000001 << 3)                              /*!<RO 0   */
#define SDIOHOST_SHIFT_CRC_ERR                       2
#define SDIOHOST_BIT_CRC_ERR                         ((u32)0x00000001 << 2)                              /*!<RO 0   */
#define SDIOHOST_SHIFT_TIMEOUT_ERR                   1
#define SDIOHOST_BIT_TIMEOUT_ERR                     ((u32)0x00000001 << 1)                              /*!<RO 0   */
#define SDIOHOST_SHIFT_NOT_EXE                       0
#define SDIOHOST_BIT_NOT_EXE                         ((u32)0x00000001 << 0)                              /*!<RO 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_HOST_CTL
 * @brief  Host Control 2 Register                   (@ 0XC3E)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_PRESET_VAL_EN                 15
#define SDIOHOST_BIT_PRESET_VAL_EN                   ((u32)0x00000001 << 15)                             /*!<R/W 0   */
#define SDIOHOST_SHIFT_ASYNC_INT_EN                  14
#define SDIOHOST_BIT_ASYNC_INT_EN                    ((u32)0x00000001 << 14)                             /*!<R/W 0   */
#define SDIOHOST_SHIFT_SAMP_CLK_SEL                  7
#define SDIOHOST_BIT_SAMP_CLK_SEL                    ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_EXEC_TUNING                   6
#define SDIOHOST_BIT_EXEC_TUNING                     ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_DRV_STR_SEL                   4
#define SDIOHOST_MASK_DRV_STR_SEL                    ((u32)0x00000003 << 4)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_1_8V_SIG_EN                   3
#define SDIOHOST_BIT_1_8V_SIG_EN                     ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define SDIOHOST_SHIFT_UHS_MODE_EN                   0
#define SDIOHOST_MASK_UHS_MODE_EN                    ((u32)0x00000007 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_CAPABILITIES0
 * @brief  Capabilities Register                     (@ 0XC40)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_SLOT_TYPE                     30
#define SDIOHOST_MASK_SLOT_TYPE                      ((u32)0x00000003 << 30)                             /*!<R 0   */
#define SDIOHOST_SHIFT_ASYNC_INT_SUPPORT             29
#define SDIOHOST_BIT_ASYNC_INT_SUPPORT               ((u32)0x00000001 << 29)                             /*!<R 0   */
#define SDIOHOST_SHIFT_64_SHIFT_SYS_BUS_SUPPORT      28
#define SDIOHOST_BIT_64_BIT_SYS_BUS_SUPPORT          ((u32)0x00000001 << 28)                             /*!<R 0   */
#define SDIOHOST_SHIFT_1_8V_SUPPORT                  26
#define SDIOHOST_BIT_1_8V_SUPPORT                    ((u32)0x00000001 << 26)                             /*!<R 0   */
#define SDIOHOST_SHIFT_3_0V_SUPPORT                  25
#define SDIOHOST_BIT_3_0V_SUPPORT                    ((u32)0x00000001 << 25)                             /*!<R 0   */
#define SDIOHOST_SHIFT_3_3V_SUPPORT                  24
#define SDIOHOST_BIT_3_3V_SUPPORT                    ((u32)0x00000001 << 24)                             /*!<R 0   */
#define SDIOHOST_SHIFT_SUSPEND_RESUME_SUPPORT        23
#define SDIOHOST_BIT_SUSPEND_RESUME_SUPPORT          ((u32)0x00000001 << 23)                             /*!<R 0   */
#define SDIOHOST_SHIFT_SDMA_SUPPORT                  22
#define SDIOHOST_BIT_SDMA_SUPPORT                    ((u32)0x00000001 << 22)                             /*!<R 0   */
#define SDIOHOST_SHIFT_HS_SUPPORT                    21
#define SDIOHOST_BIT_HS_SUPPORT                      ((u32)0x00000001 << 21)                             /*!<R 0   */
#define SDIOHOST_SHIFT_ADMA2_SUPPORT                 19
#define SDIOHOST_BIT_ADMA2_SUPPORT                   ((u32)0x00000001 << 19)                             /*!<R 0   */
#define SDIOHOST_SHIFT_8SHIFT_SUPPORT                18
#define SDIOHOST_BIT_8BIT_SUPPORT                    ((u32)0x00000001 << 18)                             /*!<R 0   */
#define SDIOHOST_SHIFT_MAX_BLK_LEN                   16
#define SDIOHOST_MASK_MAX_BLK_LEN                    ((u32)0x00000003 << 16)                             /*!<R 0   */
#define SDIOHOST_SHIFT_BASE_CLK_FREQ                 8
#define SDIOHOST_MASK_BASE_CLK_FREQ                  ((u32)0x000000FF << 8)                              /*!<R 0   */
#define SDIOHOST_SHIFT_TIMEOUT_CLK_UNIT              7
#define SDIOHOST_BIT_TIMEOUT_CLK_UNIT                ((u32)0x00000001 << 7)                              /*!<R 0   */
#define SDIOHOST_SHIFT_TIMEOUT_CLK_FREQ              0
#define SDIOHOST_MASK_TIMEOUT_CLK_FREQ               ((u32)0x0000003F << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_CAPABILITIES1
 * @brief  Capabilities Register                     (@ 0XC44)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_CLK_MULT                      16
#define SDIOHOST_MASK_CLK_MULT                       ((u32)0x000000FF << 16)                             /*!<R 0   */
#define SDIOHOST_SHIFT_RETUNING_MODES                14
#define SDIOHOST_MASK_RETUNING_MODES                 ((u32)0x00000003 << 14)                             /*!<R 0   */
#define SDIOHOST_SHIFT_USE_TUNING_SDR50              13
#define SDIOHOST_BIT_USE_TUNING_SDR50                ((u32)0x00000001 << 13)                             /*!<R 0   */
#define SDIOHOST_SHIFT_TMR_CNT_RETUNING              8
#define SDIOHOST_MASK_TMR_CNT_RETUNING               ((u32)0x0000000F << 8)                              /*!<R 0   */
#define SDIOHOST_SHIFT_DVR_D_SUPPORT                 6
#define SDIOHOST_BIT_DVR_D_SUPPORT                   ((u32)0x00000001 << 6)                              /*!<R 0   */
#define SDIOHOST_SHIFT_DVR_C_SUPPORT                 5
#define SDIOHOST_BIT_DVR_C_SUPPORT                   ((u32)0x00000001 << 5)                              /*!<R 0   */
#define SDIOHOST_SHIFT_DVR_A_SUPPORT                 4
#define SDIOHOST_BIT_DVR_A_SUPPORT                   ((u32)0x00000001 << 4)                              /*!<R 0   */
#define SDIOHOST_SHIFT_DDR50_SUPPORT                 2
#define SDIOHOST_BIT_DDR50_SUPPORT                   ((u32)0x00000001 << 2)                              /*!<R 0   */
#define SDIOHOST_SHIFT_SDR104_SUPPORT                1
#define SDIOHOST_BIT_SDR104_SUPPORT                  ((u32)0x00000001 << 1)                              /*!<R 0   */
#define SDIOHOST_SHIFT_SDR50_SUPPORT                 0
#define SDIOHOST_BIT_SDR50_SUPPORT                   ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_MAX_CURRENT0
 * @brief  Maximum Current Capabilities Register     (@ 0XC48)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_1_8V_MAX_CURR                 16
#define SDIOHOST_MASK_1_8V_MAX_CURR                  ((u32)0x000000FF << 16)                             /*!<R 0   */
#define SDIOHOST_SHIFT_3_0V_MAX_CURR                 8
#define SDIOHOST_MASK_3_0V_MAX_CURR                  ((u32)0x000000FF << 8)                              /*!<R 0   */
#define SDIOHOST_SHIFT_3_3V_MAX_CURR                 0
#define SDIOHOST_MASK_3_3V_MAX_CURR                  ((u32)0x000000FF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_FORCE_AUTO_CMD_ERR
 * @brief  Force Event Register for Auto CMD Error Status (@ 0XC50)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_CMD_NOT_ISSUED_ERR_FORCE      7
#define SDIOHOST_BIT_CMD_NOT_ISSUED_ERR_FORCE        ((u32)0x00000001 << 7)                              /*!<R 0   */
#define SDIOHOST_SHIFT_IDX_ERR_FORCE                 4
#define SDIOHOST_BIT_IDX_ERR_FORCE                   ((u32)0x00000001 << 4)                              /*!<R 0   */
#define SDIOHOST_SHIFT_END_SHIFT_ERR_FORCE           3
#define SDIOHOST_BIT_END_BIT_ERR_FORCE               ((u32)0x00000001 << 3)                              /*!<R 0   */
#define SDIOHOST_SHIFT_CRC_ERR_FORCE                 2
#define SDIOHOST_BIT_CRC_ERR_FORCE                   ((u32)0x00000001 << 2)                              /*!<R 0   */
#define SDIOHOST_SHIFT_TIMEOUT_ERR_FORCE             1
#define SDIOHOST_BIT_TIMEOUT_ERR_FORCE               ((u32)0x00000001 << 1)                              /*!<R 0   */
#define SDIOHOST_SHIFT_NOT_EXE_FORCE                 0
#define SDIOHOST_BIT_NOT_EXE_FORCE                   ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_FORCE_ERR
 * @brief  Force Event for Error Interrupt Status    (@ 0XC52)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_VENDOR_SPECIFIC_ERR_FORCE     12
#define SDIOHOST_MASK_VENDOR_SPECIFIC_ERR_FORCE      ((u32)0x0000000F << 12)                             /*!<WO 0   */
#define SDIOHOST_SHIFT_ADMA_ERR_FORCE                9
#define SDIOHOST_BIT_ADMA_ERR_FORCE                  ((u32)0x00000001 << 9)                              /*!<WO 0   */
#define SDIOHOST_SHIFT_AUTO_CMD_ERR_FORCE            8
#define SDIOHOST_BIT_AUTO_CMD_ERR_FORCE              ((u32)0x00000001 << 8)                              /*!<WO 0   */
#define SDIOHOST_SHIFT_CURRENT_LIMIT_ERR_FORCE       7
#define SDIOHOST_BIT_CURRENT_LIMIT_ERR_FORCE         ((u32)0x00000001 << 7)                              /*!<WO 0   */
#define SDIOHOST_SHIFT_DATA_END_SHIFT_ERR_FORCE      6
#define SDIOHOST_BIT_DATA_END_BIT_ERR_FORCE          ((u32)0x00000001 << 6)                              /*!<WO 0   */
#define SDIOHOST_SHIFT_DATA_CRC_ERR_FORCE            5
#define SDIOHOST_BIT_DATA_CRC_ERR_FORCE              ((u32)0x00000001 << 5)                              /*!<WO 0   */
#define SDIOHOST_SHIFT_DATA_TIMEOUT_ERR_FORCE        4
#define SDIOHOST_BIT_DATA_TIMEOUT_ERR_FORCE          ((u32)0x00000001 << 4)                              /*!<WO 0   */
#define SDIOHOST_SHIFT_CMD_IDX_ERR_FORCE             3
#define SDIOHOST_BIT_CMD_IDX_ERR_FORCE               ((u32)0x00000001 << 3)                              /*!<WO 0   */
#define SDIOHOST_SHIFT_CMD_END_SHIFT_ERR_FORCE       2
#define SDIOHOST_BIT_CMD_END_BIT_ERR_FORCE           ((u32)0x00000001 << 2)                              /*!<WO 0   */
#define SDIOHOST_SHIFT_CMD_CRC_ERR_FORCE             1
#define SDIOHOST_BIT_CMD_CRC_ERR_FORCE               ((u32)0x00000001 << 1)                              /*!<WO 0   */
#define SDIOHOST_SHIFT_CMD_TIMEOUT_ERR_FORCE         0
#define SDIOHOST_BIT_CMD_TIMEOUT_ERR_FORCE           ((u32)0x00000001 << 0)                              /*!<WO 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_ADMA_ERR
 * @brief  ADMA Error Status Register                (@ 0XC54)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_ADMA_LEN_MISMATCH_ERR         2
#define SDIOHOST_BIT_ADMA_LEN_MISMATCH_ERR           ((u32)0x00000001 << 2)                              /*!<R 0   */
#define SDIOHOST_SHIFT_ADMA_ERR_STATE                0
#define SDIOHOST_MASK_ADMA_ERR_STATE                 ((u32)0x00000003 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_SYS_ADDR0
 * @brief  ADMA System Address Register              (@ 0XC58)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_ADMA_SYS_ADDR                 0
#define SDIOHOST_MASK_ADMA_SYS_ADDR                  ((u32)0xFFFFFFFF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_SYS_ADDR1
 * @brief  ADMA System Address Register              (@ 0XC5C)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_ADMA_SYS_ADDR                 0
#define SDIOHOST_MASK_ADMA_SYS_ADDR                  ((u32)0xFFFFFFFF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_PRESET_VAL_INIT
 * @brief  Preset Value for Initialization           (@ 0XC60)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_DRV_STR_SEL_VAL               14
#define SDIOHOST_MASK_DRV_STR_SEL_VAL                ((u32)0x00000003 << 14)                             /*!<R 0   */
#define SDIOHOST_SHIFT_CLK_GEN_SEL_VAL               10
#define SDIOHOST_BIT_CLK_GEN_SEL_VAL                 ((u32)0x00000001 << 10)                             /*!<R 0   */
#define SDIOHOST_SHIFT_SDCLK_FREQ_SEL_VAL            0
#define SDIOHOST_MASK_SDCLK_FREQ_SEL_VAL             ((u32)0x000003FF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_PRESET_VAL_DS
 * @brief  Preset Value for Default Speed            (@ 0XC62)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_DRV_STR_SEL_VAL               14
#define SDIOHOST_MASK_DRV_STR_SEL_VAL                ((u32)0x00000003 << 14)                             /*!<R 0   */
#define SDIOHOST_SHIFT_CLK_GEN_SEL_VAL               10
#define SDIOHOST_BIT_CLK_GEN_SEL_VAL                 ((u32)0x00000001 << 10)                             /*!<R 0   */
#define SDIOHOST_SHIFT_SDCLK_FREQ_SEL_VAL            0
#define SDIOHOST_MASK_SDCLK_FREQ_SEL_VAL             ((u32)0x000003FF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_PRESET_VAL_HS
 * @brief  Preset Value for High Speed               (@ 0XC64)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_DRV_STR_SEL_VAL               14
#define SDIOHOST_MASK_DRV_STR_SEL_VAL                ((u32)0x00000003 << 14)                             /*!<R 0   */
#define SDIOHOST_SHIFT_CLK_GEN_SEL_VAL               10
#define SDIOHOST_BIT_CLK_GEN_SEL_VAL                 ((u32)0x00000001 << 10)                             /*!<R 0   */
#define SDIOHOST_SHIFT_SDCLK_FREQ_SEL_VAL            0
#define SDIOHOST_MASK_SDCLK_FREQ_SEL_VAL             ((u32)0x000003FF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_PRESET_VAL_SDR12
 * @brief  Preset Value for SDR12                    (@ 0XC66)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_DRV_STR_SEL_VAL               14
#define SDIOHOST_MASK_DRV_STR_SEL_VAL                ((u32)0x00000003 << 14)                             /*!<R 0   */
#define SDIOHOST_SHIFT_CLK_GEN_SEL_VAL               10
#define SDIOHOST_BIT_CLK_GEN_SEL_VAL                 ((u32)0x00000001 << 10)                             /*!<R 0   */
#define SDIOHOST_SHIFT_SDCLK_FREQ_SEL_VAL            0
#define SDIOHOST_MASK_SDCLK_FREQ_SEL_VAL             ((u32)0x000003FF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_PRESET_VAL_SDR25
 * @brief  Preset Value for SDR25                    (@ 0XC68)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_DRV_STR_SEL_VAL               14
#define SDIOHOST_MASK_DRV_STR_SEL_VAL                ((u32)0x00000003 << 14)                             /*!<R 0   */
#define SDIOHOST_SHIFT_CLK_GEN_SEL_VAL               10
#define SDIOHOST_BIT_CLK_GEN_SEL_VAL                 ((u32)0x00000001 << 10)                             /*!<R 0   */
#define SDIOHOST_SHIFT_SDCLK_FREQ_SEL_VAL            0
#define SDIOHOST_MASK_SDCLK_FREQ_SEL_VAL             ((u32)0x000003FF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_PRESET_VAL_SDR50
 * @brief  Preset Value for SDR50                    (@ 0XC6A)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_DRV_STR_SEL_VAL               14
#define SDIOHOST_MASK_DRV_STR_SEL_VAL                ((u32)0x00000003 << 14)                             /*!<R 0   */
#define SDIOHOST_SHIFT_CLK_GEN_SEL_VAL               10
#define SDIOHOST_BIT_CLK_GEN_SEL_VAL                 ((u32)0x00000001 << 10)                             /*!<R 0   */
#define SDIOHOST_SHIFT_SDCLK_FREQ_SEL_VAL            0
#define SDIOHOST_MASK_SDCLK_FREQ_SEL_VAL             ((u32)0x000003FF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_PRESET_VAL_SDR104
 * @brief  Preset Value for SDR104                   (@ 0XC6C)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_DRV_STR_SEL_VAL               14
#define SDIOHOST_MASK_DRV_STR_SEL_VAL                ((u32)0x00000003 << 14)                             /*!<R 0   */
#define SDIOHOST_SHIFT_CLK_GEN_SEL_VAL               10
#define SDIOHOST_BIT_CLK_GEN_SEL_VAL                 ((u32)0x00000001 << 10)                             /*!<R 0   */
#define SDIOHOST_SHIFT_SDCLK_FREQ_SEL_VAL            0
#define SDIOHOST_MASK_SDCLK_FREQ_SEL_VAL             ((u32)0x000003FF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_PRESET_VAL_DDR50
 * @brief  Preset Value for DDR50                    (@ 0XC6E)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_DRV_STR_SEL_VAL               14
#define SDIOHOST_MASK_DRV_STR_SEL_VAL                ((u32)0x00000003 << 14)                             /*!<R 0   */
#define SDIOHOST_SHIFT_CLK_GEN_SEL_VAL               10
#define SDIOHOST_BIT_CLK_GEN_SEL_VAL                 ((u32)0x00000001 << 10)                             /*!<R 0   */
#define SDIOHOST_SHIFT_SDCLK_FREQ_SEL_VAL            0
#define SDIOHOST_MASK_SDCLK_FREQ_SEL_VAL             ((u32)0x000003FF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_SHARED_BUS_CTL
 * @brief  Shared Bus Control Register               (@ 0XCE0)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_BACKEND_PWR_CTL               24
#define SDIOHOST_MASK_BACKEND_PWR_CTL                ((u32)0x0000007F << 24)                             /*!<R/W 0   */
#define SDIOHOST_SHIFT_INT_PIN_SEL                   20
#define SDIOHOST_MASK_INT_PIN_SEL                    ((u32)0x00000007 << 20)                             /*!<R/W 0   */
#define SDIOHOST_SHIFT_CLK_PIN_SEL                   16
#define SDIOHOST_MASK_CLK_PIN_SEL                    ((u32)0x00000007 << 16)                             /*!<R/W 0   */
#define SDIOHOST_SHIFT_BUS_WIDTH_PRESET              8
#define SDIOHOST_MASK_BUS_WIDTH_PRESET               ((u32)0x0000007F << 8)                              /*!<R 0   */
#define SDIOHOST_SHIFT_NUM_INT_PIN                   4
#define SDIOHOST_MASK_NUM_INT_PIN                    ((u32)0x00000003 << 4)                              /*!<R 0   */
#define SDIOHOST_SHIFT_NUM_CLK_PIN                   0
#define SDIOHOST_MASK_NUM_CLK_PIN                    ((u32)0x00000007 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_SLOT_INT
 * @brief  Slot Interrupt Status Register            (@ 0XCFC)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_INT_SIG_SLOT                  0
#define SDIOHOST_MASK_INT_SIG_SLOT                   ((u32)0x000000FF << 0)                              /*!<RO 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SDIOHOST_HOST_CTL_VER
 * @brief  Host Controller Version Register          (@ 0XCFE)
 * @{
 *****************************************************************************/
#define SDIOHOST_SHIFT_SPEC_VER_NUM                  0
#define SDIOHOST_MASK_SPEC_VER_NUM                   ((u32)0x000000FF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_SDIOHOST
 * @{
 * @brief rtl8735b_SDIOHOST Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t SDIOHOST_SRAM_CTL ;                      /*!<  SRAM Configuration Register register,  Address offset: 0xA00 */
	__IO uint32_t RSVD0[3];                                /*!<  Reserved,  Address offset:0xA04-0xA0C */
	__IO uint32_t SDIOHOST_IP_CTL ;                        /*!<  SDIO IP Control Register register,  Address offset: 0xA10 */
	__IO uint32_t RSVD1[3];                                /*!<  Reserved,  Address offset:0xA14-0xA1C */
	__IO uint32_t SDIOHOST_DBG1 ;                          /*!<  Debug 1 register,  Address offset: 0xA20 */
	__IO uint32_t SDIOHOST_DBG2 ;                          /*!<  Debug 2 register,  Address offset: 0xA24 */
	__IO uint32_t SDIOHOST_DBG3 ;                          /*!<  Debug 3 register,  Address offset: 0xA28 */
	__IO uint32_t RSVD2;                                  /*!<  Reserved,  Address offset:0xA2C */
	__IO uint32_t SDIOHOST_ISR ;                           /*!<  Interrupt Service Routine register,  Address offset: 0xA30 */
	__IO uint32_t SDIOHOST_ISREN ;                         /*!<  Interrupt Service Routine Enable register,  Address offset: 0xA34 */
	__IO uint32_t RSVD3[3];                                /*!<  Reserved,  Address offset:0xA38-0xA40 */
	__IO uint32_t SDIOHOST_CLKGEN_CTL ;                    /*!<  Clock Generator Control register,  Address offset: 0xA44 */
	__IO uint32_t RSVD4[2];                                /*!<  Reserved,  Address offset:0xA48-0xA4C */
	__IO uint32_t SDIOHOST_DMA_RST ;                       /*!<  DMA Reset register,  Address offset: 0xA50 */
	__IO uint32_t RSVD5;                                  /*!<  Reserved,  Address offset:0xA54 */
	__IO uint32_t SDIOHOST_DUMMY_SYS1 ;                    /*!<  sdioh_dma_rst register,  Address offset: 0xA58 */
	__I  uint32_t SDIOHOST_CLK_DET_PLL0 ;                  /*!<  sdioh_clk_det_pll0 register,  Address offset: 0xA5C */
	__IO uint32_t SDIOHOST_CLK_DET_PLL1 ;                  /*!<  sdioh_clk_det_pll1 register,  Address offset: 0xA60 */
	__IO uint32_t RSVD6;                                  /*!<  Reserved,  Address offset:0xA64 */
	__I  uint32_t SDIOHOST_BIST_CTL ;                      /*!<  sdioh_bist_ctl register,  Address offset: 0xA68 */
	__IO uint32_t RSVD7[33];                               /*!<  Reserved,  Address offset:0xA6C-0xAEC */
	__IO uint32_t SDIOHOST_DUMMY ;                         /*!<  sdioh_dummy register,  Address offset: 0xAF0 */
	__IO uint8_t RSVD8[123];                               /*!<  Reserved,  Address offset:0xAF4-0xB6E */
	__IO uint8_t SDIOHOST_MUX_CTL ;                       /*!<  sdioh_mux_ctl register,  Address offset: 0xB6F */
	__IO uint8_t RSVD9[4];                                /*!<  Reserved,  Address offset:0xB70-0xB73 */
	__IO uint8_t SDIOHOST_BUS_TA_TIME ;                   /*!<  sdioh_bus_ta_time register,  Address offset: 0xB74 */
	__IO uint8_t SDIOHOST_SDIO_MMC_MODE ;                 /*!<  sdioh_sdio_mmc_mode register,  Address offset: 0xB75 */
	__O  uint8_t SDIOHOST_RX_BEST_PHASE ;                 /*!<  sdioh_rx_best_phase register,  Address offset: 0xB76 */
	__O  uint8_t SDIOHOST_TX_BEST_PHASE ;                 /*!<  sdioh_tx_best_phase register,  Address offset: 0xB77 */
	__O  uint8_t SDIOHOST_RX_PHASE0 ;                     /*!<  sdioh_rx_phase0 register,  Address offset: 0xB78 */
	__O  uint8_t SDIOHOST_RX_PHASE1 ;                     /*!<  sdioh_rx_phase1 register,  Address offset: 0xB79 */
	__O  uint8_t SDIOHOST_RX_PHASE2 ;                     /*!<  sdioh_rx_phase2 register,  Address offset: 0xB7A */
	__O  uint8_t SDIOHOST_RX_PHASE3 ;                     /*!<  sdioh_rx_phase3 register,  Address offset: 0xB7B */
	__O  uint8_t SDIOHOST_TX_PHASE0 ;                     /*!<  sdioh_tx_phase0 register,  Address offset: 0xB7C */
	__O  uint8_t SDIOHOST_TX_PHASE1 ;                     /*!<  sdioh_tx_phase1 register,  Address offset: 0xB7D */
	__O  uint8_t SDIOHOST_TX_PHASE2 ;                     /*!<  sdioh_tx_phase2 register,  Address offset: 0xB7E */
	__O  uint8_t SDIOHOST_TX_PHASE3 ;                     /*!<  sdioh_tx_phase3 register,  Address offset: 0xB7F */
	__IO uint8_t SDIOHOST_PHASE_RST_TIME0 ;               /*!<  sdioh_phase_rst_time0 register,  Address offset: 0xB80 */
	__IO uint8_t SDIOHOST_PHASE_RST_TIME1 ;               /*!<  sdioh_phase_rst_time1 register,  Address offset: 0xB81 */
	__I  uint8_t SDIOHOST_DAT_CMD ;                       /*!<  sdioh_dat_cmd register,  Address offset: 0xB82 */
	__IO uint8_t SDIOHOST_TUNING_DUTY_CTL ;               /*!<  sdioh_tuning_duty_ctl register,  Address offset: 0xB83 */
	__IO uint8_t SDIOHOST_TUNING_SOLN ;                   /*!<  sdioh_tuning_soln register,  Address offset: 0xB84 */
	__IO uint8_t SDIOHOST_SAMPLE_PT_CTL ;                 /*!<  sdioh_sample_pt_ctl register,  Address offset: 0xB85 */
	__IO uint8_t SDIOHOST_DMA_BUF_CTL ;                   /*!<  sdioh_dma_buf_ctl register,  Address offset: 0xB86 */
	__IO uint8_t RSVD10[121];                              /*!<  Reserved,  Address offset:0xB8A-0xBFC */
	__IO uint32_t SDIOHOST_SDMA_SYS_ADDR ;                 /*!<  SDMA System Address / Argument 2 Register register,  Address offset: 0xC00 */
	__IO uint16_t SDIOHOST_BLK_SZ ;                        /*!<  Block Size Register register,  Address offset: 0xC04 */
	__IO uint16_t SDIOHOST_BLK_CNT ;                       /*!<  Block Count Register register,  Address offset: 0xC06 */
	__IO uint32_t SDIOHOST_CMD_ARG1 ;                      /*!<  Argument 1 Register register,  Address offset: 0xC08 */
	__IO uint16_t SDIOHOST_XFER_MODE ;                     /*!<   Transfer Mode Register register,  Address offset: 0xC0C */
	__IO uint16_t SDIOHOST_CMD ;                           /*!<  Command Register register,  Address offset: 0xC0E */
	__O  uint32_t SDIOHOST_RESP0 ;                         /*!<  Response Register register,  Address offset: 0xC10 */
	__O  uint32_t SDIOHOST_RESP1 ;                         /*!<  Response Register register,  Address offset: 0xC14 */
	__O  uint32_t SDIOHOST_RESP2 ;                         /*!<  Response Register register,  Address offset: 0xC18 */
	__O  uint32_t SDIOHOST_RESP3 ;                         /*!<  Response Register register,  Address offset: 0xC1C */
	__IO uint32_t SDIOHOST_BUFFER_PORT_DATA ;              /*!<   Buffer Data Port Register register,  Address offset: 0xC20 */
	__O  uint32_t SDIOHOST_PRESENT_STATE ;                 /*!<  ADC Debug Select Register register,  Address offset: 0xC24 */
	__IO uint8_t SDIOHOST_HOST_CTL_1_REG ;                /*!<  Host Control 1 Register register,  Address offset: 0xC28 */
	__IO uint8_t SDIOHOST_PWR_CTL ;                       /*!<  Power Control Register register,  Address offset: 0xC29 */
	__IO uint8_t SDIOHOST_BLK_GAP_CTL ;                   /*!<  Block Gap Control Register  register,  Address offset: 0xC2A */
	__IO uint8_t SDIOHOST_WAKEUP_CTL ;                    /*!<  Wakeup Control Register register,  Address offset: 0xC2B */
	__IO uint16_t SDIOHOST_CLK_CTL ;                       /*!<   Clock Control Register register,  Address offset: 0xC2C */
	__IO uint8_t SDIOHOST_TIMEOUT_CTL ;                   /*!<  Timeout Control Register register,  Address offset: 0xC2E */
	__IO uint8_t SDIOHOST_SW_RST ;                        /*!<  Software Reset Register register,  Address offset: 0xC2F */
	__IO uint16_t SDIOHOST_NORMAL_INT_STATUS ;             /*!<  Normal Interrupt Status Register register,  Address offset: 0xC30 */
	__IO uint16_t SDIOHOST_ERR_INT_STATUS ;                /*!<  Error Interrupt Status Register register,  Address offset: 0xC32 */
	__IO uint16_t SDIOHOST_NORMAL_INT_STATUS_EN ;          /*!<  Normal Interrupt Status Enable Register register,  Address offset: 0xC34 */
	__IO uint16_t SDIOHOST_ERR_INT_STATUS_EN ;             /*!<   Error Interrupt Status Enable Register register,  Address offset: 0xC36 */
	__IO uint16_t SDIOHOST_NORMAL_SIG_EN ;                 /*!<  Normal Interrupt Signal Enable Register register,  Address offset: 0xC38 */
	__IO uint16_t SDIOHOST_ERR_SIG_EN ;                    /*!<  Error Interrupt Signal Enable Register register,  Address offset: 0xC3A */
	__O  uint16_t SDIOHOST_AUTO_CMD_ERR_STATUS ;           /*!<  Auto CMD Error Status Register register,  Address offset: 0xC3C */
	__IO uint16_t SDIOHOST_HOST_CTL ;                      /*!<  Host Control 2 Register register,  Address offset: 0xC3E */
	__I  uint32_t SDIOHOST_CAPABILITIES0 ;                 /*!<  Capabilities Register register,  Address offset: 0xC40 */
	__I  uint32_t SDIOHOST_CAPABILITIES1 ;                 /*!<  Capabilities Register register,  Address offset: 0xC44 */
	__I  uint32_t SDIOHOST_MAX_CURRENT0 ;                  /*!<  Maximum Current Capabilities Register register,  Address offset: 0xC48 */
	__I  uint32_t SDIOHOST_MAX_CURRENT1 ;                  /*!<  Maximum Current Capabilities Register register,  Address offset: 0xC4C */
	__I  uint16_t SDIOHOST_FORCE_AUTO_CMD_ERR ;            /*!<  Force Event Register for Auto CMD Error Status register,  Address offset: 0xC50 */
	__O  uint16_t SDIOHOST_FORCE_ERR ;                     /*!<  Force Event for Error Interrupt Status register,  Address offset: 0xC52 */
	__I  uint32_t SDIOHOST_ADMA_ERR ;                      /*!<  ADMA Error Status Register register,  Address offset: 0xC54 */
	__IO uint32_t SDIOHOST_SYS_ADDR0 ;                     /*!<  ADMA System Address Register register,  Address offset: 0xC58 */
	__IO uint32_t SDIOHOST_SYS_ADDR1 ;                     /*!<  ADMA System Address Register register,  Address offset: 0xC5C */
	__I  uint16_t SDIOHOST_PRESET_VAL_INIT ;               /*!<  Preset Value for Initialization register,  Address offset: 0xC60 */
	__I  uint16_t SDIOHOST_PRESET_VAL_DS ;                 /*!<  Preset Value for Default Speed  register,  Address offset: 0xC62 */
	__I  uint16_t SDIOHOST_PRESET_VAL_HS ;                 /*!<  Preset Value for High Speed  register,  Address offset: 0xC64 */
	__I  uint16_t SDIOHOST_PRESET_VAL_SDR12 ;              /*!<  Preset Value for SDR12  register,  Address offset: 0xC66 */
	__I  uint16_t SDIOHOST_PRESET_VAL_SDR25 ;              /*!<  Preset Value for SDR25  register,  Address offset: 0xC68 */
	__I  uint16_t SDIOHOST_PRESET_VAL_SDR50 ;              /*!<  Preset Value for SDR50 register,  Address offset: 0xC6A */
	__I  uint16_t SDIOHOST_PRESET_VAL_SDR104 ;             /*!<  Preset Value for SDR104  register,  Address offset: 0xC6C */
	__I  uint16_t SDIOHOST_PRESET_VAL_DDR50 ;              /*!<  Preset Value for DDR50  register,  Address offset: 0xC6E */
	__IO uint32_t RSVD11[27];                              /*!<  Reserved,  Address offset:0xC72-0xCDC */
	__IO uint32_t SDIOHOST_SHARED_BUS_CTL ;                /*!<  Shared Bus Control Register register,  Address offset: 0xCE0 */
	__IO uint32_t RSVD12[6];                               /*!<  Reserved,  Address offset:0xCE4-0xCF8 */
	__O  uint16_t SDIOHOST_SLOT_INT ;                      /*!<  Slot Interrupt Status Register register,  Address offset: 0xCFC */
	__I  uint16_t SDIOHOST_HOST_CTL_VER ;                  /*!<  Host Controller Version Register register,          Address offset: 0xCFE */
} SDIOHOST_TypeDef;
/** @} */

#endif
