#ifndef _RTL8735B_TRNG_TYPE_H_
#define _RTL8735B_TRNG_TYPE_H_

/**************************************************************************//**
 * @defgroup TRNG_RNG_CTRL
 * @brief  RNG_CTRL                                  (@ 0X200)
 * @{
 *****************************************************************************/
#define TRNG_SHIFT_LFSR_MODE2                        31
#define TRNG_BIT_LFSR_MODE2                          ((u32)0x00000001 << 31)                             /*!<R/W 0  To improve the throughput of random value generation, make LFSR output bit stream continuously. When enable LFSR_mode2, RNG_MODE must be set to 1. (1: TRNG -> BIAS -> self-test -> LFSR -> buf) In this mode, RNG might have higher throughput and lower quality. */
#define TRNG_SHIFT_RSVD1                             20
#define TRNG_MASK_RSVD1                              ((u32)0x000007FF << 20)                             /*!<R 0  RSVD */
#define TRNG_SHIFT_RNG_MODE                          19
#define TRNG_BIT_RNG_MODE                            ((u32)0x00000001 << 19)                             /*!<R/W 0  0: TRNG -> BIAS -> LFSR -> self-test -> buf 1: TRNG -> BIAS -> self-test -> LFSR -> buf */
#define TRNG_SHIFT_ST_EN                             18
#define TRNG_BIT_ST_EN                               ((u32)0x00000001 << 18)                             /*!<R/W 0  Self test enable. */
#define TRNG_SHIFT_LFSR_MODE                         17
#define TRNG_BIT_LFSR_MODE                           ((u32)0x00000001 << 17)                             /*!<R/W 0  If LFSR_MODE = 1b0 & LFSR_MODE2 = 1b0: LFSR_WAIT_CNT >= 7d127(toggle achieve 128 times) output out_data If LFSR_MODE = 1b1 & LFSR_MODE2 = 1b0: Without toggle achieving 128 times output out_data directly */
#define TRNG_SHIFT_LFSR_BYPASS_1                     16
#define TRNG_BIT_LFSR_BYPASS_1                       ((u32)0x00000001 << 16)                             /*!<R/W 1  LFSR_1 will be bypassed if lfsr_bypass_1 = 1. */
#define TRNG_SHIFT_DBG1_SEL                          11
#define TRNG_MASK_DBG1_SEL                           ((u32)0x0000001F << 11)                             /*!<R/W 1  The Debug Signal Group 1 Selection. */
#define TRNG_SHIFT_DBG0_SEL                          6
#define TRNG_MASK_DBG0_SEL                           ((u32)0x0000001F << 6)                              /*!<R/W 0  The Debug Signal Group 0 Selection. */
#define TRNG_SHIFT_CORRECTOR_IMODE                   5
#define TRNG_BIT_CORRECTOR_IMODE                     ((u32)0x00000001 << 5)                              /*!<R/W 0  Random Bias Corrector sample rate 0: 4 valid TRNG 1: 2 valid TRNG (But corrector_bypass is the highest priority) */
#define TRNG_SHIFT_RSVD2                             3
#define TRNG_MASK_RSVD2                              ((u32)0x00000003 << 3)                              /*!<R 0   */
#define TRNG_SHIFT_CORRECTOR_BYPASS                  2
#define TRNG_BIT_CORRECTOR_BYPASS                    ((u32)0x00000001 << 2)                              /*!<R/W 0  Random Bias Corrector will be bypassed if corrector_bypass = 1 */
#define TRNG_SHIFT_CLK_HF_SEL                        1
#define TRNG_BIT_CLK_HF_SEL                          ((u32)0x00000001 << 1)                              /*!<R/W 0  Selection of High Speed Clock: 0: clk_hfosc_rng 1: clk_hfosc_rng/2 */
#define TRNG_SHIFT_RNG_SRST                          0
#define TRNG_BIT_RNG_SRST                            ((u32)0x00000001 << 0)                              /*!<R/W 0  RNG Software Reset, High Active. It will reset all digital except programmable registers. The minimum waiting time should be one period of low speed clock (7.8125us for 128Khz). Recommend the interval of reset must be greater than 10us. It means that this bit must pull high and hold at least 10us. */
/** @} */

/**************************************************************************//**
 * @defgroup TRNG_RNG_RETURN0
 * @brief  RNG_RETURN0                               (@ 0X021C)
 * @{
 *****************************************************************************/
#define TRNG_SHIFT_RSVD3                             1
#define TRNG_MASK_RSVD3                              ((u32)0x7FFFFFFF << 1)                              /*!<R 0  RSVD */
#define TRNG_SHIFT_OUT_READY                         0
#define TRNG_BIT_OUT_READY                           ((u32)0x00000001 << 0)                              /*!<R 0  The Random Number is ready to read. If BIT_OUT_READY = b1, then user can read BIT_RANDOM_OUT. */
/** @} */

/**************************************************************************//**
 * @defgroup TRNG_RNG_RETURN1
 * @brief  RNG_RETURN1                               (@ 0X0220)
 * @{
 *****************************************************************************/
#define TRNG_SHIFT_VALID_                            0
#define TRNG_MASK_VALID_                             ((u32)0xFFFFFFFF << 0)                              /*!<R 0  The Bit Number of Realtek Random Number is Generated after reset. It will be wrapped around if reach the top.[Use for debugging] */
/** @} */

/**************************************************************************//**
 * @defgroup TRNG_RNG_RETURN2
 * @brief  RNG_RETURN2                               (@ 0X0224)
 * @{
 *****************************************************************************/
#define TRNG_SHIFT_DROP_NUM                          0
#define TRNG_MASK_DROP_NUM                           ((u32)0xFFFFFFFF << 0)                              /*!<R 0  The Bit Number of Realtek Random Number is Dropped after reset. It will be wrapped around if reach the top. [Use for debugging] */
/** @} */

/**************************************************************************//**
 * @defgroup TRNG_RNG_RESULTR
 * @brief  RNG_RESULTR                               (@ 0X0228)
 * @{
 *****************************************************************************/
#define TRNG_SHIFT_RANDOM_OUT                        0
#define TRNG_MASK_RANDOM_OUT                         ((u32)0xFFFFFFFF << 0)                              /*!<R 0  Random Number Value. It will return all zeros if random number is not ready (BIT_OUT_READY = 0). */
/** @} */

/**************************************************************************//**
 * @defgroup TRNG_RNG_LFSR_POLY_LSB
 * @brief  RNG_LFSR_POLY_LSB                         (@ 0X022C)
 * @{
 *****************************************************************************/
#define TRNG_SHIFT_LFSR_POLY_LSB                     0
#define TRNG_MASK_LFSR_POLY_LSB                      ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  RNG LFSR_1 Polynomial LSB 32-bit from register */
/** @} */

/**************************************************************************//**
 * @defgroup TRNG_RNG_LFSR_POLY_MSB
 * @brief  RNG_LFSR_POLY_MSB                         (@ 0X230)
 * @{
 *****************************************************************************/
#define TRNG_SHIFT_LFSR_POLY_MSB                     0
#define TRNG_MASK_LFSR_POLY_MSB                      ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  RNG LFSR_1 Polynomial MSB 32-bit from register */
/** @} */

/**************************************************************************//**
 * @defgroup TRNG_RNG_POWER_EN
 * @brief  RNG_POWER_EN                              (@ 0X0238)
 * @{
 *****************************************************************************/
#define TRNG_SHIFT_RSVD4                             1
#define TRNG_MASK_RSVD4                              ((u32)0x7FFFFFFF << 1)                              /*!<R 0  RSVD */
#define TRNG_SHIFT_POWER_GATING_EN                   0
#define TRNG_BIT_POWER_GATING_EN                     ((u32)0x00000001 << 0)                              /*!<R/W 1  Enable power gating function. */
/** @} */

/**************************************************************************//**
 * @defgroup TRNG_RNG_ST_SETTING
 * @brief  RNG_ST_SETTING                            (@ 0X023C)
 * @{
 *****************************************************************************/
#define TRNG_SHIFT_THR_DONE_ADAP1                    28
#define TRNG_MASK_THR_DONE_ADAP1                     ((u32)0x0000000F << 28)                             /*!<R/W 0x4  Done threshold for adaptive proportion test (pass times) Default : pass four times, done_adap1 will be asserted */
#define TRNG_SHIFT_THR_DONE_ADAP2                    24
#define TRNG_MASK_THR_DONE_ADAP2                     ((u32)0x0000000F << 24)                             /*!<R/W 0x4  Done threshold for adaptive proportion test (pass times) Default : pass four times, done_adap2 will be asserted */
#define TRNG_SHIFT_RSVD5                             23
#define TRNG_BIT_RSVD5                               ((u32)0x00000001 << 23)                             /*!<R 0  RSVD */
#define TRNG_SHIFT_COMPARE_REP                       22
#define TRNG_BIT_COMPARE_REP                         ((u32)0x00000001 << 22)                             /*!<R/W 1  Compare unit for repetition test 0 : bit mode 1 : byte mode(recommend) */
#define TRNG_SHIFT_COMPARE_UNIT_ADAP1                21
#define TRNG_BIT_COMPARE_UNIT_ADAP1                  ((u32)0x00000001 << 21)                             /*!<R/W 0  Compare unit for adaptive test 1 0 : bit mode 1 : byte mode */
#define TRNG_SHIFT_COMPARE_UNIT_ADAP2                20
#define TRNG_BIT_COMPARE_UNIT_ADAP2                  ((u32)0x00000001 << 20)                             /*!<R/W 0  Compare unit for adaptive test 2 0 : bit mode 1 : byte mode */
#define TRNG_SHIFT_WINDOW_SIZE_ADAP1                 18
#define TRNG_MASK_WINDOW_SIZE_ADAP1                  ((u32)0x00000003 << 18)                             /*!<R/W 1  Byte mode: 0 : window size = 64 1 : window size = 256 2 : window size = 4096 3 : window size = 65536 Bit mode: 0 : window size = 512 1 : window size = 1024 2 : window size = 2048 */
#define TRNG_SHIFT_WINDOW_SIZE_ADAP2                 16
#define TRNG_MASK_WINDOW_SIZE_ADAP2                  ((u32)0x00000003 << 16)                             /*!<R/W 1  Byte mode: 0 : window size = 64 1 : window size = 256 2 : window size = 4096 3 : window size = 65536 Bit mode: 0 : window size = 512 1 : window size = 1024 2 : window size = 2048 */
#define TRNG_SHIFT_THR_ERR_REP                       8
#define TRNG_MASK_THR_ERR_REP                        ((u32)0x000000FF << 8)                              /*!<R/W 0x5  Error threshold for repetition count test. Cut off =( BIT_THR_ERR_REP + 1) */
#define TRNG_SHIFT_THR_DONE_REP                      0
#define TRNG_MASK_THR_DONE_REP                       ((u32)0x000000FF << 0)                              /*!<R/W 0  Done threshold for repetition count test */
/** @} */

/**************************************************************************//**
 * @defgroup TRNG_RNG_ST_RETURN
 * @brief  RNG_ST_RETURN                             (@ 0X0240)
 * @{
 *****************************************************************************/
#define TRNG_SHIFT_RSVD6                             8
#define TRNG_MASK_RSVD6                              ((u32)0x00FFFFFF << 8)                              /*!<R 0  RSVD */
#define TRNG_SHIFT_ST_DONE                           7
#define TRNG_BIT_ST_DONE                             ((u32)0x00000001 << 7)                              /*!<R 0  Self test is ready */
#define TRNG_SHIFT_DONE_REP                          6
#define TRNG_BIT_DONE_REP                            ((u32)0x00000001 << 6)                              /*!<R 0  Repetition count test is ready */
#define TRNG_SHIFT_DONE_ADAP1                        5
#define TRNG_BIT_DONE_ADAP1                          ((u32)0x00000001 << 5)                              /*!<R 0  Adaptive proportion test 1 is ready */
#define TRNG_SHIFT_DONE_ADAP2                        4
#define TRNG_BIT_DONE_ADAP2                          ((u32)0x00000001 << 4)                              /*!<R 0  Adaptive proportion test 2 is ready */
#define TRNG_SHIFT_ERR_ST                            3
#define TRNG_BIT_ERR_ST                              ((u32)0x00000001 << 3)                              /*!<R/W 0  Error will be asserted when self test detects error */
#define TRNG_SHIFT_ERR_REP                           2
#define TRNG_BIT_ERR_REP                             ((u32)0x00000001 << 2)                              /*!<R/W 0  Error will be asserted when repetition count test detects error */
#define TRNG_SHIFT_ERR_AFAP1                         1
#define TRNG_BIT_ERR_AFAP1                           ((u32)0x00000001 << 1)                              /*!<R/W 0  Error will be asserted when adaptive proportion test detects error */
#define TRNG_SHIFT_ERR_ADAP2                         0
#define TRNG_BIT_ERR_ADAP2                           ((u32)0x00000001 << 0)                              /*!<R/W 0  Error will be asserted when adaptive proportion test detects error */
/** @} */

/**************************************************************************//**
 * @defgroup TRNG_RNG_DBGR
 * @brief  RNG_DBGR                                  (@ 0X0250)
 * @{
 *****************************************************************************/
#define TRNG_SHIFT_DBG_GROUP_1                       16
#define TRNG_MASK_DBG_GROUP_1                        ((u32)0x0000FFFF << 16)                             /*!<R 0  Debug Group 1 values. */
#define TRNG_SHIFT_DBG_GROUP_0                       0
#define TRNG_MASK_DBG_GROUP_0                        ((u32)0x0000FFFF << 0)                              /*!<R 0  Debug Group 0 values. */
/** @} */

/**************************************************************************//**
 * @defgroup TRNG_RNG_INT
 * @brief  RNG_INT                                   (@ 0X0254)
 * @{
 *****************************************************************************/
#define TRNG_SHIFT_RSVD7                             4
#define TRNG_MASK_RSVD7                              ((u32)0x0FFFFFFF << 4)                              /*!<R 0   */
#define TRNG_SHIFT_ST_ERR                            3
#define TRNG_BIT_ST_ERR                              ((u32)0x00000001 << 3)                              /*!<R/W 0  Interrupt for Self Test Error */
#define TRNG_SHIFT_PARITY                            2
#define TRNG_BIT_PARITY                              ((u32)0x00000001 << 2)                              /*!<R/W 0  Interrupt for buffer parity check */
#define TRNG_SHIFT_RSVD8                             1
#define TRNG_BIT_RSVD8                               ((u32)0x00000001 << 1)                              /*!<R 0   */
#define TRNG_SHIFT_WRITE_DATA                        0
#define TRNG_BIT_WRITE_DATA                          ((u32)0x00000001 << 0)                              /*!<W 0  1 to set, 0 to clear bit with 1. */
/** @} */

/**************************************************************************//**
 * @defgroup TRNG_RNG_ST_THR_ERR
 * @brief  RNG_ST_THR_ERR                            (@ 0X0260)
 * @{
 *****************************************************************************/
#define TRNG_SHIFT_ADAP1                             16
#define TRNG_MASK_ADAP1                              ((u32)0x0000FFFF << 16)                             /*!<R/W 0x270  Error threshold for adaptive proportion test Bit-mode: Max = 3/4 * window size Byte-mode: Max = 1/4 * window size */
#define TRNG_SHIFT_ADAP2                             0
#define TRNG_MASK_ADAP2                              ((u32)0x0000FFFF << 0)                              /*!<R/W 0x270  Error threshold for adaptive proportion test Bit-mode: Max = 3/4 * window size Byte-mode: Max = 1/4 * window size */
/** @} */

/**************************************************************************//**
 * @defgroup TRNG_RNG_INT_EN
 * @brief  RNG_INT_EN                                (@ 0X0264)
 * @{
 *****************************************************************************/
#define TRNG_SHIFT_RSVD9                             4
#define TRNG_MASK_RSVD9                              ((u32)0x0FFFFFFF << 4)                              /*!<R 0  RSVD */
#define TRNG_SHIFT_ST_ERR_EN                         3
#define TRNG_BIT_ST_ERR_EN                           ((u32)0x00000001 << 3)                              /*!<R/W 0  set 1 to enable interrupt */
#define TRNG_SHIFT_PARITY_EN                         2
#define TRNG_BIT_PARITY_EN                           ((u32)0x00000001 << 2)                              /*!<R/W 0  set 1 to enable interrupt */
#define TRNG_SHIFT_RSVD10                            1
#define TRNG_BIT_RSVD10                              ((u32)0x00000001 << 1)                              /*!<R 0  RSVD */
#define TRNG_SHIFT_WIRTE_DATA_EN                     0
#define TRNG_BIT_WIRTE_DATA_EN                       ((u32)0x00000001 << 0)                              /*!<W 0  1 to set, 0 to clear bit with 1 */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_TRNG
 * @{
 * @brief rtl8735b_TRNG Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t RSVD4[128];                                  /*!<  Reserved,  Address offset:0x0-0x186*/
	__IO uint32_t TRNG_RNG_CTRL ;                          /*!<  RNG_CTRL register,  Address offset: 0x200 */
	__IO uint32_t RSVD0[6];                                /*!<  Reserved,  Address offset:0x204-0x218 */
	__I  uint32_t TRNG_RNG_RETURN0 ;                       /*!<  RNG_RETURN0 register,  Address offset: 0x021C */
	__I  uint32_t TRNG_RNG_RETURN1 ;                       /*!<  RNG_RETURN1 register,  Address offset: 0x0220 */
	__I  uint32_t TRNG_RNG_RETURN2 ;                       /*!<  RNG_RETURN2 register,  Address offset: 0x0224 */
	__I  uint32_t TRNG_RNG_RESULTR ;                       /*!<  RNG_RESULTR register,  Address offset: 0x0228 */
	__IO uint32_t TRNG_RNG_LFSR_POLY_LSB ;                 /*!<  RNG_LFSR_POLY_LSB register,  Address offset: 0x022C */
	__IO uint32_t TRNG_RNG_LFSR_POLY_MSB ;                 /*!<  RNG_LFSR_POLY_MSB register,  Address offset: 0x230 */
	__IO uint32_t RSVD1;                                  /*!<  Reserved,  Address offset:0x234 */
	__IO uint32_t TRNG_RNG_POWER_EN ;                      /*!<  RNG_POWER_EN register,  Address offset: 0x0238 */
	__IO uint32_t TRNG_RNG_ST_SETTING ;                    /*!<  RNG_ST_SETTING register,  Address offset: 0x023C */
	__IO uint32_t TRNG_RNG_ST_RETURN ;                     /*!<  RNG_ST_RETURN register,  Address offset: 0x0240 */
	__IO uint32_t RSVD2[3];                                /*!<  Reserved,  Address offset:0x244-0x24C */
	__I  uint32_t TRNG_RNG_DBGR ;                          /*!<  RNG_DBGR register,  Address offset: 0x0250 */
	__IO uint32_t TRNG_RNG_INT ;                           /*!<  RNG_INT register,  Address offset: 0x0254 */
	__IO uint32_t RSVD3[2];                                /*!<  Reserved,  Address offset:0x258-0x25C */
	__IO uint32_t TRNG_RNG_ST_THR_ERR ;                    /*!<  RNG_ST_THR_ERR register,  Address offset: 0x0260 */
	__IO uint32_t TRNG_RNG_INT_EN ;                        /*!<  RNG_INT_EN register,            Address offset: 0x0264 */
} TRNG_TypeDef;
/** @} */

#endif
