#ifndef _RTL8735B_ECDSA_TYPE_H_
#define _RTL8735B_ECDSA_TYPE_H_

/**************************************************************************//**
 * @defgroup ECDSA_ECR1_REG
 * @brief  ECDSA Cntrol 1 Register                   (@ 0X000)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_CLK_ENABLE                   8
#define ECDSA_BIT_ENG_CLK_ENABLE                     ((u32)0x00000001 << 8)                              /*!<R/W 1  ecdsa engine clock enable */
#define ECDSA_SHIFT_ENG_RST                          0
#define ECDSA_BIT_ENG_RST                            ((u32)0x00000001 << 0)                              /*!<R/W 0  ecdsa reset */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_SWAP_REG
 * @brief  ECDSA Swap Conrol Register                (@ 0X004)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_SIGN_S_SWAP                      13
#define ECDSA_BIT_SIGN_S_SWAP                        ((u32)0x00000001 << 13)                             /*!<R/W 0  Byte swap for eng_sign_s. */
#define ECDSA_SHIFT_SIGN_R_SWAP                      12
#define ECDSA_BIT_SIGN_R_SWAP                        ((u32)0x00000001 << 12)                             /*!<R/W 0  Byte swap for eng_sign_r. */
#define ECDSA_SHIFT_ORDER_N_SWAP                     11
#define ECDSA_BIT_ORDER_N_SWAP                       ((u32)0x00000001 << 11)                             /*!<R/W 0  Byte swap for order_n. */
#define ECDSA_SHIFT_H_SWAP                           10
#define ECDSA_BIT_H_SWAP                             ((u32)0x00000001 << 10)                             /*!<R/W 0  Byte swap for eng_h. */
#define ECDSA_SHIFT_PRIME_SWAP                       9
#define ECDSA_BIT_PRIME_SWAP                         ((u32)0x00000001 << 9)                              /*!<R/W 0  Byte swap for prime. */
#define ECDSA_SHIFT_COR_A_SWAP                       8
#define ECDSA_BIT_COR_A_SWAP                         ((u32)0x00000001 << 8)                              /*!<R/W 0  Byte swap for cor_a. */
#define ECDSA_SHIFT_YO_SWAP                          7
#define ECDSA_BIT_YO_SWAP                            ((u32)0x00000001 << 7)                              /*!<R/W 0  Byte swap for eng_yo. */
#define ECDSA_SHIFT_XO_SWAP                          6
#define ECDSA_BIT_XO_SWAP                            ((u32)0x00000001 << 6)                              /*!<R/W 0  Byte swap for eng_xo. */
#define ECDSA_SHIFT_VERIFY_S_SWAP                    5
#define ECDSA_BIT_VERIFY_S_SWAP                      ((u32)0x00000001 << 5)                              /*!<R/W 0  Byte swap for eng_verify_s. */
#define ECDSA_SHIFT_VERIFY_R_SWAP                    4
#define ECDSA_BIT_VERIFY_R_SWAP                      ((u32)0x00000001 << 4)                              /*!<R/W 0  Byte swap for eng_verify_r. */
#define ECDSA_SHIFT_GY_SWAP                          3
#define ECDSA_BIT_GY_SWAP                            ((u32)0x00000001 << 3)                              /*!<R/W 0  Byte swap for eng_gy. */
#define ECDSA_SHIFT_GX_SWAP                          2
#define ECDSA_BIT_GX_SWAP                            ((u32)0x00000001 << 2)                              /*!<R/W 0  Byte swap for eng_gx. */
#define ECDSA_SHIFT_Y_SWAP                           1
#define ECDSA_BIT_Y_SWAP                             ((u32)0x00000001 << 1)                              /*!<R/W 0  Byte swap for eng_y. */
#define ECDSA_SHIFT_X_SWAP                           0
#define ECDSA_BIT_X_SWAP                             ((u32)0x00000001 << 0)                              /*!<R/W 0  Byte swap for eng_x. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_EISR_REG
 * @brief  ECDSA Interrupt Status Register           (@ 0X008)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_INFINITY_KEY                     17
#define ECDSA_BIT_INFINITY_KEY                       ((u32)0x00000001 << 17)                             /*!<R 0  Engine decode fail interrupt. Put high to clear fail interrupt. */
#define ECDSA_SHIFT_SHARE_KEY_ERR                    16
#define ECDSA_BIT_SHARE_KEY_ERR                      ((u32)0x00000001 << 16)                             /*!<R 0  Share ket error message */
#define ECDSA_SHIFT_SIGN_ERR                         12
#define ECDSA_MASK_SIGN_ERR                          ((u32)0x0000000F << 12)                             /*!<R 0  Sign error message */
#define ECDSA_SHIFT_VERIFY_ERR                       10
#define ECDSA_MASK_VERIFY_ERR                        ((u32)0x00000003 << 10)                             /*!<R 0  Verify error message */
#define ECDSA_SHIFT_VERIFY_PASS                      9
#define ECDSA_BIT_VERIFY_PASS                        ((u32)0x00000001 << 9)                              /*!<R 0  Verification is completed successfully. */
#define ECDSA_SHIFT_FINISH_INT                       8
#define ECDSA_BIT_FINISH_INT                         ((u32)0x00000001 << 8)                              /*!<R/W 0  ECDSA interrupt status. This bit is cleaned by writing 1. This bit is available only if ecdsa_finish_int_mask is configured to 0 */
#define ECDSA_SHIFT_ENG_IDLE                         4
#define ECDSA_BIT_ENG_IDLE                           ((u32)0x00000001 << 4)                              /*!<R 0  When the ECDSA is idle, the bit is set to 1. */
#define ECDSA_SHIFT_HASH_OK                          2
#define ECDSA_BIT_HASH_OK                            ((u32)0x00000001 << 2)                              /*!<R/W 0  After the calculation of SHA(m) is completed, this bit will be set to 1 by the software. */
#define ECDSA_SHIFT_ENG_START                        0
#define ECDSA_BIT_ENG_START                          ((u32)0x00000001 << 0)                              /*!<W 0  When this bit is set to 1, ECDSA will start the operation according to the corresponding register. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ECR2_REG
 * @brief  ECDSA Cntrol 2 Register                   (@ 0X00C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_EXTEND_N                         14
#define ECDSA_BIT_EXTEND_N                           ((u32)0x00000001 << 14)                             /*!<R/W 0  When this bit is set to 1, order_n will extend out of 8 bits. Show as the following table. 000: 232 bit 001: 200 bit 010: 168 bit 011: 136 bit 100: 120 bit 101: 256 bit */
#define ECDSA_SHIFT_PRI_KEY_SEL                      12
#define ECDSA_MASK_PRI_KEY_SEL                       ((u32)0x00000003 << 12)                             /*!<R/W 0  Select private key 2'd0 : default private_key 2'd1 : private_key1 2'd2 : private_key2 */
#define ECDSA_SHIFT_HASH256_EN                       11
#define ECDSA_BIT_HASH256_EN                         ((u32)0x00000001 << 11)                             /*!<R/W 0  If the length of the hash message exceeds 128 bit, use this function to speed up the operation. */
#define ECDSA_SHIFT_NUM                              8
#define ECDSA_MASK_NUM                               ((u32)0x00000007 << 8)                              /*!<R/W 0  Select bit_num for correspoinding bit length, when exten_n is set to 0. Show as the following table. */
#define ECDSA_SHIFT_FINISH_INT_MASK                  7
#define ECDSA_BIT_FINISH_INT_MASK                    ((u32)0x00000001 << 7)                              /*!<R/W 0  The bit masks ecdsa_finish_int status in EISR register. */
#define ECDSA_SHIFT_FUNC_SEL                         4
#define ECDSA_MASK_FUNC_SEL                          ((u32)0x00000007 << 4)                              /*!<R/W 0  The bit is used to select the operation in basic function mode. 000: Field subtraction 001: Field division 010: Field addition 011: Field multiplication 1xx: Point addition */
#define ECDSA_SHIFT_MODE_SEL                         2
#define ECDSA_MASK_MODE_SEL                          ((u32)0x00000003 << 2)                              /*!<R/W 0  Select operating mode. 2'd0 : Verification 2'd1 : Signature 2'd2 : Scalar multiplication 2'd3 : Basic function */
#define ECDSA_SHIFT_CURVE_SEL                        0
#define ECDSA_MASK_CURVE_SEL                         ((u32)0x00000003 << 0)                              /*!<R/W 0  Select the ecc curve. 2'd0 : secp256k1 2'd1 : P-256 2'd2 : Curve25519 Weierstrass 2'd3 : Others */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_X_P0_REG
 * @brief  ECDSA Engine X Point [31:0] Registers     (@ 0X010)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_X_P0                         0
#define ECDSA_MASK_ENG_X_P0                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X value [31:0] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_X_P1_REG
 * @brief  ECDSA Engine X Point [63:32] Registers    (@ 0X014)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_X_P1                         0
#define ECDSA_MASK_ENG_X_P1                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X value [63:32] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_X_P2_REG
 * @brief  ECDSA Engine X Point [95:64] Registers    (@ 0X018)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_X_P2                         0
#define ECDSA_MASK_ENG_X_P2                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X value [95:64] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_X_P3_REG
 * @brief  ECDSA Engine X Point [127:96] Registers   (@ 0X01C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_X_P3                         0
#define ECDSA_MASK_ENG_X_P3                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X value [127:96] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_X_P4_REG
 * @brief  ECDSA Engine X Point [159:128] Registers  (@ 0X020)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_X_P4                         0
#define ECDSA_MASK_ENG_X_P4                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X value [159:128] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_X_P5_REG
 * @brief  ECDSA Engine X Point [191:160] Registers  (@ 0X024)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_X_P5                         0
#define ECDSA_MASK_ENG_X_P5                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X value [191:160] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_X_P6_REG
 * @brief  ECDSA Engine X Point [223:192] Registers  (@ 0X028)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_X_P6                         0
#define ECDSA_MASK_ENG_X_P6                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X value [223:192] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_X_P7_REG
 * @brief  ECDSA Engine X Point [255:224] Registers  (@ 0X02C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_X_P7                         0
#define ECDSA_MASK_ENG_X_P7                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X value [255:224] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_Y_P0_REG
 * @brief  ECDSA Engine Y Point [31:0] Registers     (@ 0X030)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_Y_P0                         0
#define ECDSA_MASK_ENG_Y_P0                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y value [31:0] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_Y_P1_REG
 * @brief  ECDSA Engine Y Point [63:32] Registers    (@ 0X034)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_Y_P1                         0
#define ECDSA_MASK_ENG_Y_P1                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y value [63:32] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_Y_P2_REG
 * @brief  ECDSA Engine Y Point [95:64] Registers    (@ 0X038)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_Y_P2                         0
#define ECDSA_MASK_ENG_Y_P2                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y value [95:64] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_Y_P3_REG
 * @brief  ECDSA Engine Y Point [127:96] Registers   (@ 0X03C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_Y_P3                         0
#define ECDSA_MASK_ENG_Y_P3                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y value [127:96] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_Y_P4_REG
 * @brief  ECDSA Engine Y Point [159:128] Registers  (@ 0X040)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_Y_P4                         0
#define ECDSA_MASK_ENG_Y_P4                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y value [159:128] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_Y_P5_REG
 * @brief  ECDSA Engine Y Point [191:160] Registers  (@ 0X044)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_Y_P5                         0
#define ECDSA_MASK_ENG_Y_P5                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y value [191:160] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_Y_P6_REG
 * @brief  ECDSA Engine Y Point [223:192] Registers  (@ 0X048)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_Y_P6                         0
#define ECDSA_MASK_ENG_Y_P6                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y value [223:192] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_Y_P7_REG
 * @brief  ECDSA Engine Y Point [255:224] Registers  (@ 0X04C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_Y_P7                         0
#define ECDSA_MASK_ENG_Y_P7                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y value [255:224] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_GX_PS0_REG
 * @brief  ECDSA Engine GX_PS Point [31:0] Registers (@ 0X050)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_GX_PS0                       0
#define ECDSA_MASK_ENG_GX_PS0                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  GX value [31:0] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_GX_PS1_REG
 * @brief  ECDSA Engine GX_PS Point [63:32] Registers (@ 0X054)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_GX_PS1                       0
#define ECDSA_MASK_ENG_GX_PS1                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  GX value [63:32] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_GX_PS2_REG
 * @brief  ECDSA Engine GX_PS Point [95:64] Registers (@ 0X058)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_GX_PS2                       0
#define ECDSA_MASK_ENG_GX_PS2                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  GX value [95:64] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_GX_PS3_REG
 * @brief  ECDSA Engine GX_PS Point [127:96] Registers (@ 0X05C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_GX_PS3                       0
#define ECDSA_MASK_ENG_GX_PS3                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  GX value [127:96] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_GX_PS4_REG
 * @brief  ECDSA Engine GX_PS Point [159:128] Registers (@ 0X060)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_GX_PS4                       0
#define ECDSA_MASK_ENG_GX_PS4                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  GX value [159:128] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_GX_PS5_REG
 * @brief  ECDSA Engine GX_PS Point [191:160] Registers (@ 0X064)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_GX_PS5                       0
#define ECDSA_MASK_ENG_GX_PS5                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  GX value [191:160] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_GX_PS6_REG
 * @brief  ECDSA Engine GX_PS Point [223:192] Registers (@ 0X068)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_GX_PS6                       0
#define ECDSA_MASK_ENG_GX_PS6                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  GX value [223:192] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_GX_PS7_REG
 * @brief  ECDSA Engine GX_PS Point [255:224] Registers (@ 0X06C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_GX_PS7                       0
#define ECDSA_MASK_ENG_GX_PS7                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  GX value [255:224] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_GY_PS0_REG
 * @brief  ECDSA Engine GY_PS Point [31:0] Registers (@ 0X070)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_GY_PS0                       0
#define ECDSA_MASK_ENG_GY_PS0                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  GY value [31:0] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_GY_PS1_REG
 * @brief  ECDSA Engine GY_PS Point [63:32] Registers (@ 0X074)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_GY_PS1                       0
#define ECDSA_MASK_ENG_GY_PS1                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  GY value [63:32] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_GY_PS2_REG
 * @brief  ECDSA Engine GY_PS Point [95:64] Registers (@ 0X078)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_GY_PS2                       0
#define ECDSA_MASK_ENG_GY_PS2                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  GY value [95:64] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_GY_PS3_REG
 * @brief  ECDSA Engine GY_PS Point [127:96] Registers (@ 0X07C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_GY_PS3                       0
#define ECDSA_MASK_ENG_GY_PS3                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  GY value [127:96] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_GY_PS4_REG
 * @brief  ECDSA Engine GY_PS Point [159:128] Registers (@ 0X080)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_GY_PS4                       0
#define ECDSA_MASK_ENG_GY_PS4                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  GY value [159:128] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_GY_PS5_REG
 * @brief  ECDSA Engine GY_PS Point [191:160] Registers (@ 0X084)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_GY_PS5                       0
#define ECDSA_MASK_ENG_GY_PS5                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  GY value [191:160] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_GY_PS6_REG
 * @brief  ECDSA Engine GY_PS Point [223:192] Registers (@ 0X088)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_GY_PS6                       0
#define ECDSA_MASK_ENG_GY_PS6                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  GY value [223:192] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_GY_PS7_REG
 * @brief  ECDSA Engine GY_PS Point [255:224] Registers (@ 0X08C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_GY_PS7                       0
#define ECDSA_MASK_ENG_GY_PS7                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  GY value [255:224] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_XO_P0_REG
 * @brief  ECDSA Engine X Output Point [31:0] Registers (@ 0X090)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_XO_P0                        0
#define ECDSA_MASK_ENG_XO_P0                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  XO value [31:0] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_XO_P1_REG
 * @brief  ECDSA Engine X Output Point [63:32] Registers (@ 0X094)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_XO_P1                        0
#define ECDSA_MASK_ENG_XO_P1                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  XO value [63:32] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_XO_P2_REG
 * @brief  ECDSA Engine X Output Point [95:64] Registers (@ 0X098)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_XO_P2                        0
#define ECDSA_MASK_ENG_XO_P2                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  XO value [95:64] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_XO_P3_REG
 * @brief  ECDSA Engine X Output Point [127:96] Registers (@ 0X09C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_XO_P3                        0
#define ECDSA_MASK_ENG_XO_P3                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  XO value [127:96] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_XO_P4_REG
 * @brief  ECDSA Engine X Output Point [159:128] Registers (@ 0X0A0)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_XO_P4                        0
#define ECDSA_MASK_ENG_XO_P4                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  XO value [159:128] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_XO_P5_REG
 * @brief  ECDSA Engine X Ouput Point [191:160] Registers (@ 0X0A4)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_XO_P5                        0
#define ECDSA_MASK_ENG_XO_P5                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  XO value [191:160] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_XO_P6_REG
 * @brief  ECDSA Engine X Output Point [223:192] Registers (@ 0X0A8)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_XO_P6                        0
#define ECDSA_MASK_ENG_XO_P6                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  XO value [223:192] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_XO_P7_REG
 * @brief  ECDSA Engine X Output Point [255:224] Registers (@ 0X0AC)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_XO_P7                        0
#define ECDSA_MASK_ENG_XO_P7                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  XO value [255:224] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_YO_P0_REG
 * @brief  ECDSA Engine Y Output Point [31:0] Registers (@ 0X0B0)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_YO_P0                        0
#define ECDSA_MASK_ENG_YO_P0                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  YO value [31:0] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_YO_P1_REG
 * @brief  ECDSA Engine Y Output Point [63:32] Registers (@ 0X0B4)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_YO_P1                        0
#define ECDSA_MASK_ENG_YO_P1                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  YO value [63:32] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_YO_P2_REG
 * @brief  ECDSA Engine Y Output Point [95:64] Registers (@ 0X0B8)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_YO_P2                        0
#define ECDSA_MASK_ENG_YO_P2                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  YO value [95:64] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_YO_P3_REG
 * @brief  ECDSA Engine Y Output Point [127:96] Registers (@ 0X0BC)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_YO_P3                        0
#define ECDSA_MASK_ENG_YO_P3                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  YO value [127:96] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_YO_P4_REG
 * @brief  ECDSA Engine Y Output Point [159:128] Registers (@ 0X0C0)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_YO_P4                        0
#define ECDSA_MASK_ENG_YO_P4                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  YO value [159:128] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_YO_P5_REG
 * @brief  ECDSA Engine Y Ouput Point [191:160] Registers (@ 0X0C4)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_YO_P5                        0
#define ECDSA_MASK_ENG_YO_P5                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  YO value [191:160] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_YO_P6_REG
 * @brief  ECDSA Engine Y Output Point [223:192] Registers (@ 0X0C8)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_YO_P6                        0
#define ECDSA_MASK_ENG_YO_P6                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  YO value [223:192] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_YO_P7_REG
 * @brief  ECDSA Engine Y Output Point [255:224] Registers (@ 0X0CC)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_YO_P7                        0
#define ECDSA_MASK_ENG_YO_P7                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  YO value [255:224] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_SIGN_R_S0_REG
 * @brief  ECDSA Engine R Point [31:0] Registers     (@ 0X0D0)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_SIGN_R_S0                    0
#define ECDSA_MASK_ENG_SIGN_R_S0                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  R value [31:0] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_SIGN_R_S1_REG
 * @brief  ECDSA Engine R Point [63:32] Registers    (@ 0X0D4)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_SIGN_R_S1                    0
#define ECDSA_MASK_ENG_SIGN_R_S1                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  R value [63:32] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_SIGN_R_S2_REG
 * @brief  ECDSA Engine R Point [95:64] Registers    (@ 0X0D8)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_SIGN_R_S2                    0
#define ECDSA_MASK_ENG_SIGN_R_S2                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  R value [95:64] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_SIGN_R_S3_REG
 * @brief  ECDSA Engine R Point [127:96] Registers   (@ 0X0DC)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_SIGN_R_S3                    0
#define ECDSA_MASK_ENG_SIGN_R_S3                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  R value [127:96] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_SIGN_R_S4_REG
 * @brief  ECDSA Engine R Point [159:128] Registers  (@ 0X0E0)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_SIGN_R_S4                    0
#define ECDSA_MASK_ENG_SIGN_R_S4                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  R value [159:128] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_SIGN_R_S5_REG
 * @brief  ECDSA Engine R Point [191:160] Registers  (@ 0X0E4)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_SIGN_R_S5                    0
#define ECDSA_MASK_ENG_SIGN_R_S5                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  R value [191:160] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_SIGN_R_S6_REG
 * @brief  ECDSA Engine R Point [223:192] Registers  (@ 0X0E8)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_SIGN_R_S6                    0
#define ECDSA_MASK_ENG_SIGN_R_S6                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  R value [223:192] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_SIGN_R_S7_REG
 * @brief  ECDSA Engine R Point [255:224] Registers  (@ 0X0EC)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_SIGN_R_S7                    0
#define ECDSA_MASK_ENG_SIGN_R_S7                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  R value [255:224] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_SIGN_S_S0_REG
 * @brief  ECDSA Engine S Point [31:0] Registers     (@ 0X0F0)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_SIGN_S_S0                    0
#define ECDSA_MASK_ENG_SIGN_S_S0                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  S value [31:0] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_SIGN_S_S1_REG
 * @brief  ECDSA Engine S Point [63:32] Registers    (@ 0X0F4)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_SIGN_S_S1                    0
#define ECDSA_MASK_ENG_SIGN_S_S1                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  S value [63:32] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_SIGN_S_S2_REG
 * @brief  ECDSA Engine S Point [95:64] Registers    (@ 0X0F8)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_SIGN_S_S2                    0
#define ECDSA_MASK_ENG_SIGN_S_S2                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  S value [95:64] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_SIGN_S_S3_REG
 * @brief  ECDSA Engine S Point [127:96] Registers   (@ 0X0FC)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_SIGN_S_S3                    0
#define ECDSA_MASK_ENG_SIGN_S_S3                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  S value [127:96] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_SIGN_S_S4_REG
 * @brief  ECDSA Engine S  Point [159:128] Registers (@ 0X100)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_SIGN_S_S4                    0
#define ECDSA_MASK_ENG_SIGN_S_S4                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  S value [159:128] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_SIGN_S_S5_REG
 * @brief  ECDSA Engine S Point [191:160] Registers  (@ 0X104)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_SIGN_S_S5                    0
#define ECDSA_MASK_ENG_SIGN_S_S5                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  S value [191:160] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_SIGN_S_S6_REG
 * @brief  ECDSA Engine S Point [223:192] Registers  (@ 0X108)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_SIGN_S_S6                    0
#define ECDSA_MASK_ENG_SIGN_S_S6                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  S value [223:192] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_SIGN_S_S7_REG
 * @brief  ECDSA Engine S Point [255:224] Registers  (@ 0X10C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_SIGN_S_S7                    0
#define ECDSA_MASK_ENG_SIGN_S_S7                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  S value [255:224] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_VERIFY_R_P0_REG
 * @brief  ECDSA Engine VR Point [31:0] Registers    (@ 0X110)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_VERIFY_R_P0                  0
#define ECDSA_MASK_ENG_VERIFY_R_P0                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  VR value [31:0] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_VERIFY_R_P1_REG
 * @brief  ECDSA Engine VR Point [63:32] Registers   (@ 0X114)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_VERIFY_R_P1                  0
#define ECDSA_MASK_ENG_VERIFY_R_P1                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  VR value [63:32] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_VERIFY_R_P2_REG
 * @brief  ECDSA Engine VR Point [95:64] Registers   (@ 0X118)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_VERIFY_R_P2                  0
#define ECDSA_MASK_ENG_VERIFY_R_P2                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  VR value [95:64] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_VERIFY_R_P3_REG
 * @brief  ECDSA Engine VR Point [127:96] Registers  (@ 0X11C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_VERIFY_R_P3                  0
#define ECDSA_MASK_ENG_VERIFY_R_P3                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  VR value [127:96] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_VERIFY_R_P4_REG
 * @brief  ECDSA Engine VR Point [159:128] Registers (@ 0X120)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_VERIFY_R_P4                  0
#define ECDSA_MASK_ENG_VERIFY_R_P4                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  VR value [159:128] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_VERIFY_R_P5_REG
 * @brief  ECDSA Engine VR Point [191:160] Registers (@ 0X124)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_VERIFY_R_P5                  0
#define ECDSA_MASK_ENG_VERIFY_R_P5                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  VR value [191:160] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_VERIFY_R_P6_REG
 * @brief  ECDSA Engine VR Point [223:192] Registers (@ 0X128)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_VERIFY_R_P6                  0
#define ECDSA_MASK_ENG_VERIFY_R_P6                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  VR value [223:192] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_VERIFY_R_P7_REG
 * @brief  ECDSA Engine VR Point [255:224] Registers (@ 0X12C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_VERIFY_R_P7                  0
#define ECDSA_MASK_ENG_VERIFY_R_P7                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  VR value [255:224] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_VERIFY_S_P0_REG
 * @brief  ECDSA Engine VS Point [31:0] Registers    (@ 0X130)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_VERIFY_S_P0                  0
#define ECDSA_MASK_ENG_VERIFY_S_P0                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  VS value [31:0] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_VERIFY_S_P1_REG
 * @brief  ECDSA Engine VS Point [63:32] Registers   (@ 0X134)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_VERIFY_S_P1                  0
#define ECDSA_MASK_ENG_VERIFY_S_P1                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  VS value [63:32] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_VERIFY_S_P2_REG
 * @brief  ECDSA Engine VS Point [95:64] Registers   (@ 0X138)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_VERIFY_S_P2                  0
#define ECDSA_MASK_ENG_VERIFY_S_P2                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  VS value [95:64] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_VERIFY_S_P3_REG
 * @brief  ECDSA Engine VS Point [127:96] Registers  (@ 0X13C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_VERIFY_S_P3                  0
#define ECDSA_MASK_ENG_VERIFY_S_P3                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  VS value [127:96] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_VERIFY_S_P4_REG
 * @brief  ECDSA Engine VS  Point [159:128] Registers (@ 0X140)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_VERIFY_S_P4                  0
#define ECDSA_MASK_ENG_VERIFY_S_P4                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  VS value [159:128] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_VERIFY_S_P5_REG
 * @brief  ECDSA Engine VS Point [191:160] Registers (@ 0X144)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_VERIFY_S_P5                  0
#define ECDSA_MASK_ENG_VERIFY_S_P5                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  VS value [191:160] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_VERIFY_S_P6_REG
 * @brief  ECDSA Engine VS Point [223:192] Registers (@ 0X148)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_VERIFY_S_P6                  0
#define ECDSA_MASK_ENG_VERIFY_S_P6                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  VS value [223:192] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_VERIFY_S_P7_REG
 * @brief  ECDSA Engine VS Point [255:224] Registers (@ 0X14C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_VERIFY_S_P7                  0
#define ECDSA_MASK_ENG_VERIFY_S_P7                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  VS value [255:224] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_H_P0_REG
 * @brief  ECDSA Engine H Point [31:0] Registers     (@ 0X150)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_H_P0                         0
#define ECDSA_MASK_ENG_H_P0                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  H value [31:0] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_H_P1_REG
 * @brief  ECDSA Engine H Point [63:32] Registers    (@ 0X154)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_H_P1                         0
#define ECDSA_MASK_ENG_H_P1                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  H value [63:32] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_H_P2_REG
 * @brief  ECDSA Engine H Point [95:64] Registers    (@ 0X158)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_H_P2                         0
#define ECDSA_MASK_ENG_H_P2                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  H value [95:64] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_H_P3_REG
 * @brief  ECDSA Engine H Point [127:96] Registers   (@ 0X15C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_H_P3                         0
#define ECDSA_MASK_ENG_H_P3                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  H value [127:96] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_H_P4_REG
 * @brief  ECDSA Engine H Point [159:128] Registers  (@ 0X160)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_H_P4                         0
#define ECDSA_MASK_ENG_H_P4                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  H value [159:128] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_H_P5_REG
 * @brief  ECDSA Engine H Point [191:160] Registers  (@ 0X164)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_H_P5                         0
#define ECDSA_MASK_ENG_H_P5                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  H value [191:160] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_H_P6_REG
 * @brief  ECDSA Engine H Point [223:192] Registers  (@ 0X168)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_H_P6                         0
#define ECDSA_MASK_ENG_H_P6                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  H value [223:192] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_H_P7_REG
 * @brief  ECDSA Engine H Point [255:224] Registers  (@ 0X16C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_H_P7                         0
#define ECDSA_MASK_ENG_H_P7                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  H value [255:224] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_A_P0_REG
 * @brief  ECDSA Engine A Point [31:0] Registers     (@ 0X170)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_A_P0                         0
#define ECDSA_MASK_ENG_A_P0                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  A value [31:0] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_A_P1_REG
 * @brief  ECDSA Engine A Point [63:32] Registers    (@ 0X174)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_A_P1                         0
#define ECDSA_MASK_ENG_A_P1                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  A value [63:32] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_A_P2_REG
 * @brief  ECDSA Engine A Point [95:64] Registers    (@ 0X178)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_A_P2                         0
#define ECDSA_MASK_ENG_A_P2                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  A value [95:64] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_A_P3_REG
 * @brief  ECDSA Engine A Point [127:96] Registers   (@ 0X17C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_A_P3                         0
#define ECDSA_MASK_ENG_A_P3                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  A value [127:96] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_A_P4_REG
 * @brief  ECDSA Engine A Point [159:128] Registers  (@ 0X180)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_A_P4                         0
#define ECDSA_MASK_ENG_A_P4                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  A value [159:128] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_A_P5_REG
 * @brief  ECDSA Engine A Point [191:160] Registers  (@ 0X184)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_A_P5                         0
#define ECDSA_MASK_ENG_A_P5                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  A value [191:160] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_A_P6_REG
 * @brief  ECDSA Engine A Point [223:192] Registers  (@ 0X188)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_A_P6                         0
#define ECDSA_MASK_ENG_A_P6                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  A value [223:192] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_A_P7_REG
 * @brief  ECDSA Engine A Point [255:224] Registers  (@ 0X18C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_A_P7                         0
#define ECDSA_MASK_ENG_A_P7                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  A value [255:224] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_P_P0_REG
 * @brief  ECDSA Engine P Point [31:0] Registers     (@ 0X190)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_P_P0                         0
#define ECDSA_MASK_ENG_P_P0                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  P value [31:0] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_P_P1_REG
 * @brief  ECDSA Engine P Point [63:32] Registers    (@ 0X194)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_P_P1                         0
#define ECDSA_MASK_ENG_P_P1                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  P value [63:32] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_P_P2_REG
 * @brief  ECDSA Engine P Point [95:64] Registers    (@ 0X198)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_P_P2                         0
#define ECDSA_MASK_ENG_P_P2                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  P value [95:64] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_P_P3_REG
 * @brief  ECDSA Engine P Point [127:96] Registers   (@ 0X19C)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_P_P3                         0
#define ECDSA_MASK_ENG_P_P3                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  P value [127:96] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_P_P4_REG
 * @brief  ECDSA Engine P Point [159:128] Registers  (@ 0X1A0)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_P_P4                         0
#define ECDSA_MASK_ENG_P_P4                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  P value [159:128] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_P_P5_REG
 * @brief  ECDSA Engine P Point [191:160] Registers  (@ 0X1A4)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_P_P5                         0
#define ECDSA_MASK_ENG_P_P5                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  P value [191:160] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_P_P6_REG
 * @brief  ECDSA Engine P Point [223:192] Registers  (@ 0X1A8)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_P_P6                         0
#define ECDSA_MASK_ENG_P_P6                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  P value [223:192] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_P_P7_REG
 * @brief  ECDSA Engine P Point [255:224] Registers  (@ 0X1AC)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_P_P7                         0
#define ECDSA_MASK_ENG_P_P7                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  P value [255:224] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_N_P0_REG
 * @brief  ECDSA Engine N Point [31:0] Registers     (@ 0X1B0)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_N_P0                         0
#define ECDSA_MASK_ENG_N_P0                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  N value [31:0] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_N_P1_REG
 * @brief  ECDSA Engine N Point [63:32] Registers    (@ 0X1B4)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_N_P1                         0
#define ECDSA_MASK_ENG_N_P1                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  N value [63:32] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_N_P2_REG
 * @brief  ECDSA Engine N Point [95:64] Registers    (@ 0X1B8)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_N_P2                         0
#define ECDSA_MASK_ENG_N_P2                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  N value [95:64] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_N_P3_REG
 * @brief  ECDSA Engine N Point [127:96] Registers   (@ 0X1BC)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_N_P3                         0
#define ECDSA_MASK_ENG_N_P3                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  N value [127:96] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_N_P4_REG
 * @brief  ECDSA Engine N Point [159:128] Registers  (@ 0X1C0)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_N_P4                         0
#define ECDSA_MASK_ENG_N_P4                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  N value [159:128] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_N_P5_REG
 * @brief  ECDSA Engine N Point [191:160] Registers  (@ 0X1C4)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_N_P5                         0
#define ECDSA_MASK_ENG_N_P5                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  N value [191:160] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_N_P6_REG
 * @brief  ECDSA Engine N Point [223:192] Registers  (@ 0X1C8)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_N_P6                         0
#define ECDSA_MASK_ENG_N_P6                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  N value [223:192] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ENG_N_P7_REG
 * @brief  ECDSA Engine N Point [255:224] Registers  (@ 0X1CC)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_ENG_N_P7                         0
#define ECDSA_MASK_ENG_N_P7                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  N value [255:224] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup ECDSA_ECDSA_DBG_O_REG
 * @brief  ECDSA Engine Debug Output Register        (@ 0X200)
 * @{
 *****************************************************************************/
#define ECDSA_SHIFT_DBG_O                            0
#define ECDSA_MASK_DBG_O                             ((u32)0xFFFFFFFF << 0)                              /*!<R 0  Debug Signal */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_ECDSA
 * @{
 * @brief rtl8735b_ECDSA Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t ECDSA_ECR1_REG ;                         /*!<  ECDSA Cntrol 1 Register register,  Address offset: 0x000 */
	__IO uint32_t ECDSA_SWAP_REG ;                         /*!<  ECDSA Swap Conrol Register register,  Address offset: 0x004 */
	__IO uint32_t ECDSA_EISR_REG ;                         /*!<  ECDSA Interrupt Status Register register,  Address offset: 0x008 */
	__IO uint32_t ECDSA_ECR2_REG ;                         /*!<  ECDSA Cntrol 2 Register register,  Address offset: 0x00C */
	__IO uint32_t ECDSA_ENG_X_P0_REG ;                     /*!<  ECDSA Engine X Point [31:0] Registers register,  Address offset: 0x010 */
	__IO uint32_t ECDSA_ENG_X_P1_REG ;                     /*!<  ECDSA Engine X Point [63:32] Registers register,  Address offset: 0x014 */
	__IO uint32_t ECDSA_ENG_X_P2_REG ;                     /*!<  ECDSA Engine X Point [95:64] Registers register,  Address offset: 0x018 */
	__IO uint32_t ECDSA_ENG_X_P3_REG ;                     /*!<  ECDSA Engine X Point [127:96] Registers register,  Address offset: 0x01C */
	__IO uint32_t ECDSA_ENG_X_P4_REG ;                     /*!<  ECDSA Engine X Point [159:128] Registers register,  Address offset: 0x020 */
	__IO uint32_t ECDSA_ENG_X_P5_REG ;                     /*!<  ECDSA Engine X Point [191:160] Registers register,  Address offset: 0x024 */
	__IO uint32_t ECDSA_ENG_X_P6_REG ;                     /*!<  ECDSA Engine X Point [223:192] Registers register,  Address offset: 0x028 */
	__IO uint32_t ECDSA_ENG_X_P7_REG ;                     /*!<  ECDSA Engine X Point [255:224] Registers register,  Address offset: 0x02C */
	__IO uint32_t ECDSA_ENG_Y_P0_REG ;                     /*!<  ECDSA Engine Y Point [31:0] Registers register,  Address offset: 0x030 */
	__IO uint32_t ECDSA_ENG_Y_P1_REG ;                     /*!<  ECDSA Engine Y Point [63:32] Registers register,  Address offset: 0x034 */
	__IO uint32_t ECDSA_ENG_Y_P2_REG ;                     /*!<  ECDSA Engine Y Point [95:64] Registers register,  Address offset: 0x038 */
	__IO uint32_t ECDSA_ENG_Y_P3_REG ;                     /*!<  ECDSA Engine Y Point [127:96] Registers register,  Address offset: 0x03C */
	__IO uint32_t ECDSA_ENG_Y_P4_REG ;                     /*!<  ECDSA Engine Y Point [159:128] Registers register,  Address offset: 0x040 */
	__IO uint32_t ECDSA_ENG_Y_P5_REG ;                     /*!<  ECDSA Engine Y Point [191:160] Registers register,  Address offset: 0x044 */
	__IO uint32_t ECDSA_ENG_Y_P6_REG ;                     /*!<  ECDSA Engine Y Point [223:192] Registers register,  Address offset: 0x048 */
	__IO uint32_t ECDSA_ENG_Y_P7_REG ;                     /*!<  ECDSA Engine Y Point [255:224] Registers register,  Address offset: 0x04C */
	__IO uint32_t ECDSA_ENG_GX_PS0_REG ;                   /*!<  ECDSA Engine GX_PS Point [31:0] Registers register,  Address offset: 0x050 */
	__IO uint32_t ECDSA_ENG_GX_PS1_REG ;                   /*!<  ECDSA Engine GX_PS Point [63:32] Registers register,  Address offset: 0x054 */
	__IO uint32_t ECDSA_ENG_GX_PS2_REG ;                   /*!<  ECDSA Engine GX_PS Point [95:64] Registers register,  Address offset: 0x058 */
	__IO uint32_t ECDSA_ENG_GX_PS3_REG ;                   /*!<  ECDSA Engine GX_PS Point [127:96] Registers register,  Address offset: 0x05C */
	__IO uint32_t ECDSA_ENG_GX_PS4_REG ;                   /*!<  ECDSA Engine GX_PS Point [159:128] Registers register,  Address offset: 0x060 */
	__IO uint32_t ECDSA_ENG_GX_PS5_REG ;                   /*!<  ECDSA Engine GX_PS Point [191:160] Registers register,  Address offset: 0x064 */
	__IO uint32_t ECDSA_ENG_GX_PS6_REG ;                   /*!<  ECDSA Engine GX_PS Point [223:192] Registers register,  Address offset: 0x068 */
	__IO uint32_t ECDSA_ENG_GX_PS7_REG ;                   /*!<  ECDSA Engine GX_PS Point [255:224] Registers register,  Address offset: 0x06C */
	__IO uint32_t ECDSA_ENG_GY_PS0_REG ;                   /*!<  ECDSA Engine GY_PS Point [31:0] Registers register,  Address offset: 0x070 */
	__IO uint32_t ECDSA_ENG_GY_PS1_REG ;                   /*!<  ECDSA Engine GY_PS Point [63:32] Registers register,  Address offset: 0x074 */
	__IO uint32_t ECDSA_ENG_GY_PS2_REG ;                   /*!<  ECDSA Engine GY_PS Point [95:64] Registers register,  Address offset: 0x078 */
	__IO uint32_t ECDSA_ENG_GY_PS3_REG ;                   /*!<  ECDSA Engine GY_PS Point [127:96] Registers register,  Address offset: 0x07C */
	__IO uint32_t ECDSA_ENG_GY_PS4_REG ;                   /*!<  ECDSA Engine GY_PS Point [159:128] Registers register,  Address offset: 0x080 */
	__IO uint32_t ECDSA_ENG_GY_PS5_REG ;                   /*!<  ECDSA Engine GY_PS Point [191:160] Registers register,  Address offset: 0x084 */
	__IO uint32_t ECDSA_ENG_GY_PS6_REG ;                   /*!<  ECDSA Engine GY_PS Point [223:192] Registers register,  Address offset: 0x088 */
	__IO uint32_t ECDSA_ENG_GY_PS7_REG ;                   /*!<  ECDSA Engine GY_PS Point [255:224] Registers register,  Address offset: 0x08C */
	__IO uint32_t ECDSA_ENG_XO_P0_REG ;                    /*!<  ECDSA Engine X Output Point [31:0] Registers register,  Address offset: 0x090 */
	__IO uint32_t ECDSA_ENG_XO_P1_REG ;                    /*!<  ECDSA Engine X Output Point [63:32] Registers register,  Address offset: 0x094 */
	__IO uint32_t ECDSA_ENG_XO_P2_REG ;                    /*!<  ECDSA Engine X Output Point [95:64] Registers register,  Address offset: 0x098 */
	__IO uint32_t ECDSA_ENG_XO_P3_REG ;                    /*!<  ECDSA Engine X Output Point [127:96] Registers register,  Address offset: 0x09C */
	__IO uint32_t ECDSA_ENG_XO_P4_REG ;                    /*!<  ECDSA Engine X Output Point [159:128] Registers register,  Address offset: 0x0A0 */
	__IO uint32_t ECDSA_ENG_XO_P5_REG ;                    /*!<  ECDSA Engine X Ouput Point [191:160] Registers register,  Address offset: 0x0A4 */
	__IO uint32_t ECDSA_ENG_XO_P6_REG ;                    /*!<  ECDSA Engine X Output Point [223:192] Registers register,  Address offset: 0x0A8 */
	__IO uint32_t ECDSA_ENG_XO_P7_REG ;                    /*!<  ECDSA Engine X Output Point [255:224] Registers register,  Address offset: 0x0AC */
	__IO uint32_t ECDSA_ENG_YO_P0_REG ;                    /*!<  ECDSA Engine Y Output Point [31:0] Registers register,  Address offset: 0x0B0 */
	__IO uint32_t ECDSA_ENG_YO_P1_REG ;                    /*!<  ECDSA Engine Y Output Point [63:32] Registers register,  Address offset: 0x0B4 */
	__IO uint32_t ECDSA_ENG_YO_P2_REG ;                    /*!<  ECDSA Engine Y Output Point [95:64] Registers register,  Address offset: 0x0B8 */
	__IO uint32_t ECDSA_ENG_YO_P3_REG ;                    /*!<  ECDSA Engine Y Output Point [127:96] Registers register,  Address offset: 0x0BC */
	__IO uint32_t ECDSA_ENG_YO_P4_REG ;                    /*!<  ECDSA Engine Y Output Point [159:128] Registers register,  Address offset: 0x0C0 */
	__IO uint32_t ECDSA_ENG_YO_P5_REG ;                    /*!<  ECDSA Engine Y Ouput Point [191:160] Registers register,  Address offset: 0x0C4 */
	__IO uint32_t ECDSA_ENG_YO_P6_REG ;                    /*!<  ECDSA Engine Y Output Point [223:192] Registers register,  Address offset: 0x0C8 */
	__IO uint32_t ECDSA_ENG_YO_P7_REG ;                    /*!<  ECDSA Engine Y Output Point [255:224] Registers register,  Address offset: 0x0CC */
	__IO uint32_t ECDSA_ENG_SIGN_R_S0_REG ;                /*!<  ECDSA Engine R Point [31:0] Registers register,  Address offset: 0x0D0 */
	__IO uint32_t ECDSA_ENG_SIGN_R_S1_REG ;                /*!<  ECDSA Engine R Point [63:32] Registers register,  Address offset: 0x0D4 */
	__IO uint32_t ECDSA_ENG_SIGN_R_S2_REG ;                /*!<  ECDSA Engine R Point [95:64] Registers register,  Address offset: 0x0D8 */
	__IO uint32_t ECDSA_ENG_SIGN_R_S3_REG ;                /*!<  ECDSA Engine R Point [127:96] Registers register,  Address offset: 0x0DC */
	__IO uint32_t ECDSA_ENG_SIGN_R_S4_REG ;                /*!<  ECDSA Engine R Point [159:128] Registers register,  Address offset: 0x0E0 */
	__IO uint32_t ECDSA_ENG_SIGN_R_S5_REG ;                /*!<  ECDSA Engine R Point [191:160] Registers register,  Address offset: 0x0E4 */
	__IO uint32_t ECDSA_ENG_SIGN_R_S6_REG ;                /*!<  ECDSA Engine R Point [223:192] Registers register,  Address offset: 0x0E8 */
	__IO uint32_t ECDSA_ENG_SIGN_R_S7_REG ;                /*!<  ECDSA Engine R Point [255:224] Registers register,  Address offset: 0x0EC */
	__IO uint32_t ECDSA_ENG_SIGN_S_S0_REG ;                /*!<  ECDSA Engine S Point [31:0] Registers register,  Address offset: 0x0F0 */
	__IO uint32_t ECDSA_ENG_SIGN_S_S1_REG ;                /*!<  ECDSA Engine S Point [63:32] Registers register,  Address offset: 0x0F4 */
	__IO uint32_t ECDSA_ENG_SIGN_S_S2_REG ;                /*!<  ECDSA Engine S Point [95:64] Registers register,  Address offset: 0x0F8 */
	__IO uint32_t ECDSA_ENG_SIGN_S_S3_REG ;                /*!<  ECDSA Engine S Point [127:96] Registers register,  Address offset: 0x0FC */
	__IO uint32_t ECDSA_ENG_SIGN_S_S4_REG ;                /*!<  ECDSA Engine S  Point [159:128] Registers register,  Address offset: 0x100 */
	__IO uint32_t ECDSA_ENG_SIGN_S_S5_REG ;                /*!<  ECDSA Engine S Point [191:160] Registers register,  Address offset: 0x104 */
	__IO uint32_t ECDSA_ENG_SIGN_S_S6_REG ;                /*!<  ECDSA Engine S Point [223:192] Registers register,  Address offset: 0x108 */
	__IO uint32_t ECDSA_ENG_SIGN_S_S7_REG ;                /*!<  ECDSA Engine S Point [255:224] Registers register,  Address offset: 0x10C */
	__IO uint32_t ECDSA_ENG_VERIFY_R_P0_REG ;              /*!<  ECDSA Engine VR Point [31:0] Registers register,  Address offset: 0x110 */
	__IO uint32_t ECDSA_ENG_VERIFY_R_P1_REG ;              /*!<  ECDSA Engine VR Point [63:32] Registers register,  Address offset: 0x114 */
	__IO uint32_t ECDSA_ENG_VERIFY_R_P2_REG ;              /*!<  ECDSA Engine VR Point [95:64] Registers register,  Address offset: 0x118 */
	__IO uint32_t ECDSA_ENG_VERIFY_R_P3_REG ;              /*!<  ECDSA Engine VR Point [127:96] Registers register,  Address offset: 0x11C */
	__IO uint32_t ECDSA_ENG_VERIFY_R_P4_REG ;              /*!<  ECDSA Engine VR Point [159:128] Registers register,  Address offset: 0x120 */
	__IO uint32_t ECDSA_ENG_VERIFY_R_P5_REG ;              /*!<  ECDSA Engine VR Point [191:160] Registers register,  Address offset: 0x124 */
	__IO uint32_t ECDSA_ENG_VERIFY_R_P6_REG ;              /*!<  ECDSA Engine VR Point [223:192] Registers register,  Address offset: 0x128 */
	__IO uint32_t ECDSA_ENG_VERIFY_R_P7_REG ;              /*!<  ECDSA Engine VR Point [255:224] Registers register,  Address offset: 0x12C */
	__IO uint32_t ECDSA_ENG_VERIFY_S_P0_REG ;              /*!<  ECDSA Engine VS Point [31:0] Registers register,  Address offset: 0x130 */
	__IO uint32_t ECDSA_ENG_VERIFY_S_P1_REG ;              /*!<  ECDSA Engine VS Point [63:32] Registers register,  Address offset: 0x134 */
	__IO uint32_t ECDSA_ENG_VERIFY_S_P2_REG ;              /*!<  ECDSA Engine VS Point [95:64] Registers register,  Address offset: 0x138 */
	__IO uint32_t ECDSA_ENG_VERIFY_S_P3_REG ;              /*!<  ECDSA Engine VS Point [127:96] Registers register,  Address offset: 0x13C */
	__IO uint32_t ECDSA_ENG_VERIFY_S_P4_REG ;              /*!<  ECDSA Engine VS  Point [159:128] Registers register,  Address offset: 0x140 */
	__IO uint32_t ECDSA_ENG_VERIFY_S_P5_REG ;              /*!<  ECDSA Engine VS Point [191:160] Registers register,  Address offset: 0x144 */
	__IO uint32_t ECDSA_ENG_VERIFY_S_P6_REG ;              /*!<  ECDSA Engine VS Point [223:192] Registers register,  Address offset: 0x148 */
	__IO uint32_t ECDSA_ENG_VERIFY_S_P7_REG ;              /*!<  ECDSA Engine VS Point [255:224] Registers register,  Address offset: 0x14C */
	__IO uint32_t ECDSA_ENG_H_P0_REG ;                     /*!<  ECDSA Engine H Point [31:0] Registers register,  Address offset: 0x150 */
	__IO uint32_t ECDSA_ENG_H_P1_REG ;                     /*!<  ECDSA Engine H Point [63:32] Registers register,  Address offset: 0x154 */
	__IO uint32_t ECDSA_ENG_H_P2_REG ;                     /*!<  ECDSA Engine H Point [95:64] Registers register,  Address offset: 0x158 */
	__IO uint32_t ECDSA_ENG_H_P3_REG ;                     /*!<  ECDSA Engine H Point [127:96] Registers register,  Address offset: 0x15C */
	__IO uint32_t ECDSA_ENG_H_P4_REG ;                     /*!<  ECDSA Engine H Point [159:128] Registers register,  Address offset: 0x160 */
	__IO uint32_t ECDSA_ENG_H_P5_REG ;                     /*!<  ECDSA Engine H Point [191:160] Registers register,  Address offset: 0x164 */
	__IO uint32_t ECDSA_ENG_H_P6_REG ;                     /*!<  ECDSA Engine H Point [223:192] Registers register,  Address offset: 0x168 */
	__IO uint32_t ECDSA_ENG_H_P7_REG ;                     /*!<  ECDSA Engine H Point [255:224] Registers register,  Address offset: 0x16C */
	__IO uint32_t ECDSA_ENG_A_P0_REG ;                     /*!<  ECDSA Engine A Point [31:0] Registers register,  Address offset: 0x170 */
	__IO uint32_t ECDSA_ENG_A_P1_REG ;                     /*!<  ECDSA Engine A Point [63:32] Registers register,  Address offset: 0x174 */
	__IO uint32_t ECDSA_ENG_A_P2_REG ;                     /*!<  ECDSA Engine A Point [95:64] Registers register,  Address offset: 0x178 */
	__IO uint32_t ECDSA_ENG_A_P3_REG ;                     /*!<  ECDSA Engine A Point [127:96] Registers register,  Address offset: 0x17C */
	__IO uint32_t ECDSA_ENG_A_P4_REG ;                     /*!<  ECDSA Engine A Point [159:128] Registers register,  Address offset: 0x180 */
	__IO uint32_t ECDSA_ENG_A_P5_REG ;                     /*!<  ECDSA Engine A Point [191:160] Registers register,  Address offset: 0x184 */
	__IO uint32_t ECDSA_ENG_A_P6_REG ;                     /*!<  ECDSA Engine A Point [223:192] Registers register,  Address offset: 0x188 */
	__IO uint32_t ECDSA_ENG_A_P7_REG ;                     /*!<  ECDSA Engine A Point [255:224] Registers register,  Address offset: 0x18C */
	__IO uint32_t ECDSA_ENG_P_P0_REG ;                     /*!<  ECDSA Engine P Point [31:0] Registers register,  Address offset: 0x190 */
	__IO uint32_t ECDSA_ENG_P_P1_REG ;                     /*!<  ECDSA Engine P Point [63:32] Registers register,  Address offset: 0x194 */
	__IO uint32_t ECDSA_ENG_P_P2_REG ;                     /*!<  ECDSA Engine P Point [95:64] Registers register,  Address offset: 0x198 */
	__IO uint32_t ECDSA_ENG_P_P3_REG ;                     /*!<  ECDSA Engine P Point [127:96] Registers register,  Address offset: 0x19C */
	__IO uint32_t ECDSA_ENG_P_P4_REG ;                     /*!<  ECDSA Engine P Point [159:128] Registers register,  Address offset: 0x1A0 */
	__IO uint32_t ECDSA_ENG_P_P5_REG ;                     /*!<  ECDSA Engine P Point [191:160] Registers register,  Address offset: 0x1A4 */
	__IO uint32_t ECDSA_ENG_P_P6_REG ;                     /*!<  ECDSA Engine P Point [223:192] Registers register,  Address offset: 0x1A8 */
	__IO uint32_t ECDSA_ENG_P_P7_REG ;                     /*!<  ECDSA Engine P Point [255:224] Registers register,  Address offset: 0x1AC */
	__IO uint32_t ECDSA_ENG_N_P0_REG ;                     /*!<  ECDSA Engine N Point [31:0] Registers register,  Address offset: 0x1B0 */
	__IO uint32_t ECDSA_ENG_N_P1_REG ;                     /*!<  ECDSA Engine N Point [63:32] Registers register,  Address offset: 0x1B4 */
	__IO uint32_t ECDSA_ENG_N_P2_REG ;                     /*!<  ECDSA Engine N Point [95:64] Registers register,  Address offset: 0x1B8 */
	__IO uint32_t ECDSA_ENG_N_P3_REG ;                     /*!<  ECDSA Engine N Point [127:96] Registers register,  Address offset: 0x1BC */
	__IO uint32_t ECDSA_ENG_N_P4_REG ;                     /*!<  ECDSA Engine N Point [159:128] Registers register,  Address offset: 0x1C0 */
	__IO uint32_t ECDSA_ENG_N_P5_REG ;                     /*!<  ECDSA Engine N Point [191:160] Registers register,  Address offset: 0x1C4 */
	__IO uint32_t ECDSA_ENG_N_P6_REG ;                     /*!<  ECDSA Engine N Point [223:192] Registers register,  Address offset: 0x1C8 */
	__IO uint32_t ECDSA_ENG_N_P7_REG ;                     /*!<  ECDSA Engine N Point [255:224] Registers register,  Address offset: 0x1CC */
	__IO uint32_t RSVD0[12];                               /*!<  Reserved,  Address offset:0x1D0-0x1FC */
	__I  uint32_t ECDSA_ECDSA_DBG_O_REG ;                  /*!<  ECDSA Engine Debug Output Register register,            Address offset: 0x200 */
} ECDSA_TypeDef;
/** @} */

#endif
