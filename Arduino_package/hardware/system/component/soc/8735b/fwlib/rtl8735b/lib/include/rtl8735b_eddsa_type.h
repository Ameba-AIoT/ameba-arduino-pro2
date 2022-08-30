#ifndef _RTL8735B_EDDSA_TYPE_H_
#define _RTL8735B_EDDSA_TYPE_H_

/**************************************************************************//**
 * @defgroup EDDSA_ENG_INIT_REG
 * @brief  EdDSA Engine Initial Setting Register     (@ 0X000)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_SWPTR                            8
#define EDDSA_BIT_SWPTR                              ((u32)0x00000001 << 8)                              /*!<R/W 0  eng_clk_enable */
#define EDDSA_SHIFT_ENG_RST                          0
#define EDDSA_BIT_ENG_RST                            ((u32)0x00000001 << 0)                              /*!<R/W 0  Engine synchronize reset */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_CONF_INT_REG
 * @brief  EdDSA Engine Configure Interrupt Register (@ 0X008)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_DECODE_FAIL                  12
#define EDDSA_BIT_ENG_DECODE_FAIL                    ((u32)0x00000001 << 12)                             /*!<R/W 0  Engine decode fail interrupt. Put high to clear fail interrupt. */
#define EDDSA_SHIFT_MODE3_FINISH                     11
#define EDDSA_BIT_MODE3_FINISH                       ((u32)0x00000001 << 11)                             /*!<R/W 0  Engine mode3 interrupt. Put high to clear mode3 interrupt. */
#define EDDSA_SHIFT_MODE2_FINISH                     10
#define EDDSA_BIT_MODE2_FINISH                       ((u32)0x00000001 << 10)                             /*!<R/W 0  Engine mode2 interrupt. Put high to clear mode2 interrupt. */
#define EDDSA_SHIFT_MODE1_FINISH                     9
#define EDDSA_BIT_MODE1_FINISH                       ((u32)0x00000001 << 9)                              /*!<R/W 0  Engine mode1 interrupt. Put high to clear mode1 interrupt. */
#define EDDSA_SHIFT_MODE0_FINISH                     8
#define EDDSA_BIT_MODE0_FINISH                       ((u32)0x00000001 << 8)                              /*!<R/W 0  Engine mode0 interrupt. Put high to clear mode0 interrupt. */
#define EDDSA_SHIFT_ENG_IDLE                         4
#define EDDSA_BIT_ENG_IDLE                           ((u32)0x00000001 << 4)                              /*!<R 0  When engine is busy, this bit will be put high. */
#define EDDSA_SHIFT_HASH_OK                          2
#define EDDSA_BIT_HASH_OK                            ((u32)0x00000001 << 2)                              /*!<R/W 0  When Hash digest input value is ready, put hask_ok to high. Only use this bit in some auto-flow setting. When programer set this bit to 1'b1, it means that hash digest input value is ready, engine can contiune processing next auto-flow step. */
#define EDDSA_SHIFT_ENG_START                        0
#define EDDSA_BIT_ENG_START                          ((u32)0x00000001 << 0)                              /*!<R/W 0  Start for EdDSA function. It's almost for all EdDSA function, except some auto-flow settings. When programer set this bit to 1'b1, it means that input values of the engine mode are ready, so engine can process the mode. Usually it won't be set with HASH_OK. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_CTRL_REG
 * @brief  EdDSA Engine Contol Register              (@ 0X00C)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_YO2_WORD_SWAP                    31
#define EDDSA_BIT_YO2_WORD_SWAP                      ((u32)0x00000001 << 31)                             /*!<R/W 0  yo2 word swap enable control. */
#define EDDSA_SHIFT_YO2_BYTE_SWAP                    30
#define EDDSA_BIT_YO2_BYTE_SWAP                      ((u32)0x00000001 << 30)                             /*!<R/W 0  yo2 byte swap enable control. */
#define EDDSA_SHIFT_XO2_WORD_SWAP                    29
#define EDDSA_BIT_XO2_WORD_SWAP                      ((u32)0x00000001 << 29)                             /*!<R/W 0  xo2 word swap enable control. */
#define EDDSA_SHIFT_XO2_BYTE_SWAP                    28
#define EDDSA_BIT_XO2_BYTE_SWAP                      ((u32)0x00000001 << 28)                             /*!<R/W 0  xo2 byte swap enable control. */
#define EDDSA_SHIFT_YO1_WORD_SWAP                    27
#define EDDSA_BIT_YO1_WORD_SWAP                      ((u32)0x00000001 << 27)                             /*!<R/W 0  yo1 word swap enable control. */
#define EDDSA_SHIFT_YO1_BYTE_SWAP                    26
#define EDDSA_BIT_YO1_BYTE_SWAP                      ((u32)0x00000001 << 26)                             /*!<R/W 0  yo1 byte swap enable control. */
#define EDDSA_SHIFT_XO1_WORD_SWAP                    25
#define EDDSA_BIT_XO1_WORD_SWAP                      ((u32)0x00000001 << 25)                             /*!<R/W 0  xo1 word swap enable control. */
#define EDDSA_SHIFT_XO1_BYTE_SWAP                    24
#define EDDSA_BIT_XO1_BYTE_SWAP                      ((u32)0x00000001 << 24)                             /*!<R/W 0  xo1 byte swap enable control. */
#define EDDSA_SHIFT_Y2_WORD_SWAP                     23
#define EDDSA_BIT_Y2_WORD_SWAP                       ((u32)0x00000001 << 23)                             /*!<R/W 0  y2 word swap enable control. */
#define EDDSA_SHIFT_Y2_BYTE_SWAP                     22
#define EDDSA_BIT_Y2_BYTE_SWAP                       ((u32)0x00000001 << 22)                             /*!<R/W 0  y2 byte swap enable control. */
#define EDDSA_SHIFT_X2_WORD_SWAP                     21
#define EDDSA_BIT_X2_WORD_SWAP                       ((u32)0x00000001 << 21)                             /*!<R/W 0  x2 word swap enable control. */
#define EDDSA_SHIFT_X2_BYTE_SWAP                     20
#define EDDSA_BIT_X2_BYTE_SWAP                       ((u32)0x00000001 << 20)                             /*!<R/W 0  x2 byte swap enable control. */
#define EDDSA_SHIFT_Y1_WORD_SWAP                     19
#define EDDSA_BIT_Y1_WORD_SWAP                       ((u32)0x00000001 << 19)                             /*!<R/W 0  y1 word swap enable control. */
#define EDDSA_SHIFT_Y1_BYTE_SWAP                     18
#define EDDSA_BIT_Y1_BYTE_SWAP                       ((u32)0x00000001 << 18)                             /*!<R/W 0  y1 byte swap enable control. */
#define EDDSA_SHIFT_X1_WORD_SWAP                     17
#define EDDSA_BIT_X1_WORD_SWAP                       ((u32)0x00000001 << 17)                             /*!<R/W 0  x1 word swap enable control. */
#define EDDSA_SHIFT_X1_BYTE_SWAP                     16
#define EDDSA_BIT_X1_BYTE_SWAP                       ((u32)0x00000001 << 16)                             /*!<R/W 0  x1 byte swap enable control. */
#define EDDSA_SHIFT_MODE3_F_MASK                     15
#define EDDSA_BIT_MODE3_F_MASK                       ((u32)0x00000001 << 15)                             /*!<R/W 0  Mask mode3 finish interrupt. */
#define EDDSA_SHIFT_MODE2_F_MASK                     14
#define EDDSA_BIT_MODE2_F_MASK                       ((u32)0x00000001 << 14)                             /*!<R/W 0  Mask mode2 finish interrupt. */
#define EDDSA_SHIFT_MODE1_F_MASK                     13
#define EDDSA_BIT_MODE1_F_MASK                       ((u32)0x00000001 << 13)                             /*!<R/W 0  Mask mode1 finish interrupt. */
#define EDDSA_SHIFT_MODE0_F_MASK                     12
#define EDDSA_BIT_MODE0_F_MASK                       ((u32)0x00000001 << 12)                             /*!<R/W 0  Mask mode0 finish interrupt. */
#define EDDSA_SHIFT_ENG_DECODE_FAIL_MASK             11
#define EDDSA_BIT_ENG_DECODE_FAIL_MASK               ((u32)0x00000001 << 11)                             /*!<R/W 0  Mask decoding fail interrupt. */
#define EDDSA_SHIFT_RECOVER_X_EN                     10
#define EDDSA_BIT_RECOVER_X_EN                       ((u32)0x00000001 << 10)                             /*!<R/W 0  Reocver(decode) point enable contrl. When this bit is set to 1'b1, it means that enable decoding mode. */
#define EDDSA_SHIFT_SUB_POINT                        9
#define EDDSA_BIT_SUB_POINT                          ((u32)0x00000001 << 9)                              /*!<R/W 0  Point subtraction enable control in mode2.  */
#define EDDSA_SHIFT_MOD_Q                            8
#define EDDSA_BIT_MOD_Q                              ((u32)0x00000001 << 8)                              /*!<R/W 0  Select modular1 or 2 for Hash mod. Ref. Function Step chapter. #modular1 : hash[511:0] modular (2^255 - 19) #modular2 : hash[511:0] modular (2^252+ 27742317777372353535851937790883648493) */
#define EDDSA_SHIFT_H512_EN                          7
#define EDDSA_BIT_H512_EN                            ((u32)0x00000001 << 7)                              /*!<R/W 0  SHA512 hash enable control. 1: enable using sha512 0: disable using sha512 */
#define EDDSA_SHIFT_BYP_H512                         6
#define EDDSA_BIT_BYP_H512                           ((u32)0x00000001 << 6)                              /*!<R/W 0  SHA512 hash bypass mode control. 1: Bypass SHA512 0: Without bypass SHA512 */
#define EDDSA_SHIFT_AUTO_SP                          5
#define EDDSA_BIT_AUTO_SP                            ((u32)0x00000001 << 5)                              /*!<R/W 0  Auto-flow step enable control. Basically, it is used to open one pass flow in mode0/mode1 flow. It won't be set in mode2/ mode3. */
#define EDDSA_SHIFT_AP_EN                            4
#define EDDSA_BIT_AP_EN                              ((u32)0x00000001 << 4)                              /*!<R/W 0  Add point enable control. It is only used in mode3. 1: enable 0: disable */
#define EDDSA_SHIFT_FUN_SEL                          2
#define EDDSA_MASK_FUN_SEL                           ((u32)0x00000003 << 2)                              /*!<R/W 0  EdDSA engine function select. 2'd0 : Decode point/ add point/ sub mod [It depends on bit ecover_x_en and bit ap_en.] 2'd1 : Div mod 2'd2 : Add mod 2'd3 : Mult mod/ Hash mod #modular1/ Hash mod #modular2 [It depends on bit h512_en and bit mod_q] */
#define EDDSA_SHIFT_MOD_SEL                          0
#define EDDSA_MASK_MOD_SEL                           ((u32)0x00000003 << 0)                              /*!<R/W 0  EdDSA engine mode select. 2'd0 : mode0 2'd1 : mode1 2'd2 : mode2 2'd3 : mode3  */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_X1_P0_REG
 * @brief  EdDSA Engine X1 Point [31:0] Registers    (@ 0X010)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_X1_P0                        0
#define EDDSA_MASK_ENG_X1_P0                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X1 value [31:0] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_X1_P1_REG
 * @brief  EdDSA Engine X1 Point [63:32] Registers   (@ 0X014)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_X1_P1                        0
#define EDDSA_MASK_ENG_X1_P1                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X1 value [63:32] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_X1_P2_REG
 * @brief  EdDSA Engine X1 Point [95:64] Registers   (@ 0X018)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_X1_P2                        0
#define EDDSA_MASK_ENG_X1_P2                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X1 value [95:64] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_X1_P3_REG
 * @brief  EdDSA Engine X1 Point [127:96] Registers  (@ 0X01C)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_X1_P3                        0
#define EDDSA_MASK_ENG_X1_P3                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X1 value [127:96] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_X1_P4_REG
 * @brief  EdDSA Engine X1 Point [159:128] Registers (@ 0X020)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_X1_P4                        0
#define EDDSA_MASK_ENG_X1_P4                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X1 value [159:128] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_X1_P5_REG
 * @brief  EdDSA Engine X1 Point [191:160] Registers (@ 0X024)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_X1_P5                        0
#define EDDSA_MASK_ENG_X1_P5                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X1 value [191:160] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_X1_P6_REG
 * @brief  EdDSA Engine X1 Point [223:192] Registers (@ 0X028)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_X1_P6                        0
#define EDDSA_MASK_ENG_X1_P6                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X1 value [223:192] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_X1_P7_REG
 * @brief  EdDSA Engine X1 Point [255:224] Registers (@ 0X02C)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_X1_P7                        0
#define EDDSA_MASK_ENG_X1_P7                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X1 value [255:224] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_Y1_P0_REG
 * @brief  EdDSA Engine Y1 Point [31:0] Registers    (@ 0X030)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_Y1_P0                        0
#define EDDSA_MASK_ENG_Y1_P0                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y1 value [31:0] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_Y1_P1_REG
 * @brief  EdDSA Engine Y1 Point [63:32] Registers   (@ 0X034)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_Y1_P1                        0
#define EDDSA_MASK_ENG_Y1_P1                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y1 value [63:32] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_Y1_P2_REG
 * @brief  EdDSA Engine Y1 Point [95:64] Registers   (@ 0X038)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_Y1_P2                        0
#define EDDSA_MASK_ENG_Y1_P2                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y1 value [95:64] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_Y1_P3_REG
 * @brief  EdDSA Engine Y1 Point [127:96] Registers  (@ 0X03C)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_Y1_P3                        0
#define EDDSA_MASK_ENG_Y1_P3                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y1 value [127:96] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_Y1_P4_REG
 * @brief  EdDSA Engine Y1 Point [159:128] Registers (@ 0X040)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_Y1_P4                        0
#define EDDSA_MASK_ENG_Y1_P4                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y1 value [159:128] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_Y1_P5_REG
 * @brief  EdDSA Engine Y1 Point [191:160] Registers (@ 0X044)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_Y1_P5                        0
#define EDDSA_MASK_ENG_Y1_P5                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y1 value [191:160] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_Y1_P6_REG
 * @brief  EdDSA Engine Y1 Point [223:192] Registers (@ 0X048)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_Y1_P6                        0
#define EDDSA_MASK_ENG_Y1_P6                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y1 value [223:192] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_Y1_P7_REG
 * @brief  EdDSA Engine Y1 Point [255:224] Registers (@ 0X04C)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_Y1_P7                        0
#define EDDSA_MASK_ENG_Y1_P7                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y1 value [255:224] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_X2_P0_REG
 * @brief  EdDSA Engine X2 Point [31:0] Registers    (@ 0X050)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_X2_P0                        0
#define EDDSA_MASK_ENG_X2_P0                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X2 value [31:0] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_X2_P1_REG
 * @brief  EdDSA Engine X2 Point [63:32] Registers   (@ 0X054)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_X2_P1                        0
#define EDDSA_MASK_ENG_X2_P1                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X2 value [63:32] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_X2_P2_REG
 * @brief  EdDSA Engine X2 Point [95:64] Registers   (@ 0X058)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_X2_P2                        0
#define EDDSA_MASK_ENG_X2_P2                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X2 value [95:64] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_X2_P3_REG
 * @brief  EdDSA Engine X2 Point [127:96] Registers  (@ 0X05C)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_X2_P3                        0
#define EDDSA_MASK_ENG_X2_P3                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X2 value [127:96] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_X2_P4_REG
 * @brief  EdDSA Engine X2 Point [159:128] Registers (@ 0X060)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_X2_P4                        0
#define EDDSA_MASK_ENG_X2_P4                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X2 value [159:128] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_X2_P5_REG
 * @brief  EdDSA Engine X2 Point [191:160] Registers (@ 0X064)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_X2_P5                        0
#define EDDSA_MASK_ENG_X2_P5                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X2 value [191:160] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_X2_P6_REG
 * @brief  EdDSA Engine X2 Point [223:192] Registers (@ 0X068)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_X2_P6                        0
#define EDDSA_MASK_ENG_X2_P6                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X2 value [223:192] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_X2_P7_REG
 * @brief  EdDSA Engine X2 Point [255:224] Registers (@ 0X06C)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_X2_P7                        0
#define EDDSA_MASK_ENG_X2_P7                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X2 value [255:224] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_Y2_P0_REG
 * @brief  EdDSA Engine Y2 Point [31:0] Registers    (@ 0X070)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_Y2_P0                        0
#define EDDSA_MASK_ENG_Y2_P0                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y2 value [31:0] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_Y2_P1_REG
 * @brief  EdDSA Engine Y2 Point [63:32] Registers   (@ 0X074)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_Y2_P1                        0
#define EDDSA_MASK_ENG_Y2_P1                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y2 value [63:32] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_Y2_P2_REG
 * @brief  EdDSA Engine Y2 Point [95:64] Registers   (@ 0X078)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_Y2_P2                        0
#define EDDSA_MASK_ENG_Y2_P2                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y2 value [95:64] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_Y2_P3_REG
 * @brief  EdDSA Engine Y2 Point [127:96] Registers  (@ 0X07C)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_Y2_P3                        0
#define EDDSA_MASK_ENG_Y2_P3                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y2 value [127:96] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_Y2_P4_REG
 * @brief  EdDSA Engine Y2 Point [159:128] Registers (@ 0X080)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_Y2_P4                        0
#define EDDSA_MASK_ENG_Y2_P4                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y2 value [159:128] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_Y2_P5_REG
 * @brief  EdDSA Engine Y2 Point [191:160] Registers (@ 0X084)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_Y2_P5                        0
#define EDDSA_MASK_ENG_Y2_P5                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y2 value [191:160] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_Y2_P6_REG
 * @brief  EdDSA Engine Y2 Point [223:192] Registers (@ 0X088)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_Y2_P6                        0
#define EDDSA_MASK_ENG_Y2_P6                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y2 value [223:192] of an input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_Y2_P7_REG
 * @brief  EdDSA Engine Y2 Point [255:224] Registers (@ 0X08C)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_Y2_P7                        0
#define EDDSA_MASK_ENG_Y2_P7                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y2 value [255:224] of a input point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_XO1_P0_REG
 * @brief  EdDSA Engine X1 Output Point [31:0] Registers (@ 0X090)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_XO1_P0                       0
#define EDDSA_MASK_ENG_XO1_P0                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X1 value [31:0] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_XO1_P1_REG
 * @brief  EdDSA Engine X1 Output Point [63:32] Registers (@ 0X094)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_XO1_P1                       0
#define EDDSA_MASK_ENG_XO1_P1                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X1 value [63:32] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_XO1_P2_REG
 * @brief  EdDSA Engine X1 Output Point [95:64] Registers (@ 0X098)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_XO1_P2                       0
#define EDDSA_MASK_ENG_XO1_P2                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X1 value [95:64] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_XO1_P3_REG
 * @brief  EdDSA Engine X1 Output Point [127:96] Registers (@ 0X09C)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_XO1_P3                       0
#define EDDSA_MASK_ENG_XO1_P3                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X1 value [127:96] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_XO1_P4_REG
 * @brief  EdDSA Engine X1 Output Point [159:128] Registers (@ 0X0A0)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_XO1_P4                       0
#define EDDSA_MASK_ENG_XO1_P4                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X1 value [159:128] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_XO1_P5_REG
 * @brief  EdDSA Engine X1 Ouput Point [191:160] Registers (@ 0X0A4)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_XO1_P5                       0
#define EDDSA_MASK_ENG_XO1_P5                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X1 value [191:160] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_XO1_P6_REG
 * @brief  EdDSA Engine X1 Output Point [223:192] Registers (@ 0X0A8)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_XO1_P6                       0
#define EDDSA_MASK_ENG_XO1_P6                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X1 value [223:192] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_XO1_P7_REG
 * @brief  EdDSA Engine X1 Output Point [255:224] Registers (@ 0X0AC)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_XO1_P7                       0
#define EDDSA_MASK_ENG_XO1_P7                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X1 value [255:224] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_YO1_P0_REG
 * @brief  EdDSA Engine Y1 Output Point [31:0] Registers (@ 0X0B0)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_YO1_P0                       0
#define EDDSA_MASK_ENG_YO1_P0                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y1 value [31:0] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_YO1_P1_REG
 * @brief  EdDSA Engine Y1 Output Point [63:32] Registers (@ 0X0B4)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_YO1_P1                       0
#define EDDSA_MASK_ENG_YO1_P1                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y1 value [63:32] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_YO1_P2_REG
 * @brief  EdDSA Engine Y1 Output Point [95:64] Registers (@ 0X0B8)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_YO1_P2                       0
#define EDDSA_MASK_ENG_YO1_P2                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y1 value [95:64] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_YO1_P3_REG
 * @brief  EdDSA Engine Y1 Output Point [127:96] Registers (@ 0X0BC)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_YO1_P3                       0
#define EDDSA_MASK_ENG_YO1_P3                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y1 value [127:96] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_YO1_P4_REG
 * @brief  EdDSA Engine Y1 Output Point [159:128] Registers (@ 0X0C0)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_YO1_P4                       0
#define EDDSA_MASK_ENG_YO1_P4                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y1 value [159:128] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_YO1_P5_REG
 * @brief  EdDSA Engine Y1 Ouput Point [191:160] Registers (@ 0X0C4)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_YO1_P5                       0
#define EDDSA_MASK_ENG_YO1_P5                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y1 value [191:160] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_YO1_P6_REG
 * @brief  EdDSA Engine Y1 Output Point [223:192] Registers (@ 0X0C8)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_YO1_P6                       0
#define EDDSA_MASK_ENG_YO1_P6                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y1 value [223:192] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_YO1_P7_REG
 * @brief  EdDSA Engine Y1 Output Point [255:224] Registers (@ 0X0CC)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_YO1_P7                       0
#define EDDSA_MASK_ENG_YO1_P7                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y1 value [255:224] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_XO2_P0_REG
 * @brief  EdDSA Engine X2 Output Point [31:0] Registers (@ 0X0D0)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_XO2_P0                       0
#define EDDSA_MASK_ENG_XO2_P0                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X2 value [31:0] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_XO2_P1_REG
 * @brief  EdDSA Engine X2 Output Point [63:32] Registers (@ 0X0D4)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_XO2_P1                       0
#define EDDSA_MASK_ENG_XO2_P1                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X2 value [63:32] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_XO2_P2_REG
 * @brief  EdDSA Engine X2 Output Point [95:64] Registers (@ 0X0D8)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_XO2_P2                       0
#define EDDSA_MASK_ENG_XO2_P2                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X2 value [95:64] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_XO2_P3_REG
 * @brief  EdDSA Engine X2 Output Point [127:96] Registers (@ 0X0DC)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_XO2_P3                       0
#define EDDSA_MASK_ENG_XO2_P3                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X2 value [127:96] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_XO2_P4_REG
 * @brief  EdDSA Engine X2 Output Point [159:128] Registers (@ 0X0E0)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_XO2_P4                       0
#define EDDSA_MASK_ENG_XO2_P4                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X2 value [159:128] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_XO2_P5_REG
 * @brief  EdDSA Engine X2 Ouput Point [191:160] Registers (@ 0X0E4)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_XO2_P5                       0
#define EDDSA_MASK_ENG_XO2_P5                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X2 value [191:160] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_XO2_P6_REG
 * @brief  EdDSA Engine X2 Output Point [223:192] Registers (@ 0X0E8)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_XO2_P6                       0
#define EDDSA_MASK_ENG_XO2_P6                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X2 value [223:192] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_XO2_P7_REG
 * @brief  EdDSA Engine X2 Output Point [255:224] Registers (@ 0X0EC)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_XO2_P7                       0
#define EDDSA_MASK_ENG_XO2_P7                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  X2 value [255:224] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_YO2_P0_REG
 * @brief  EdDSA Engine Y2 Output Point [31:0] Registers (@ 0X0F0)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_YO2_P0                       0
#define EDDSA_MASK_ENG_YO2_P0                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y2 value [31:0] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_YO2_P1_REG
 * @brief  EdDSA Engine Y2 Output Point [63:32] Registers (@ 0X0F4)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_YO2_P1                       0
#define EDDSA_MASK_ENG_YO2_P1                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y2 value [63:32] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_YO2_P2_REG
 * @brief  EdDSA Engine Y2 Output Point [95:64] Registers (@ 0X0F8)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_YO2_P2                       0
#define EDDSA_MASK_ENG_YO2_P2                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y2 value [95:64] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_YO2_P3_REG
 * @brief  EdDSA Engine Y2 Output Point [127:96] Registers (@ 0X0FC)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_YO2_P3                       0
#define EDDSA_MASK_ENG_YO2_P3                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y2 value [127:96] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_YO2_P4_REG
 * @brief  EdDSA Engine Y2 Output Point [159:128] Registers (@ 0X100)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_YO2_P4                       0
#define EDDSA_MASK_ENG_YO2_P4                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y2 value [159:128] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_YO2_P5_REG
 * @brief  EdDSA Engine Y2 Ouput Point [191:160] Registers (@ 0X104)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_YO2_P5                       0
#define EDDSA_MASK_ENG_YO2_P5                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y2 value [191:160] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_YO2_P6_REG
 * @brief  EdDSA Engine Y2 Output Point [223:192] Registers (@ 0X108)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_YO2_P6                       0
#define EDDSA_MASK_ENG_YO2_P6                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y2 value [223:192] of an output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_YO2_P7_REG
 * @brief  EdDSA Engine Y2 Output Point [255:224] Registers (@ 0X10C)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_ENG_YO2_P7                       0
#define EDDSA_MASK_ENG_YO2_P7                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Y2 value [255:224] of a output point. */
/** @} */

/**************************************************************************//**
 * @defgroup EDDSA_ENG_DBG_OUTPUT_REG
 * @brief  EdDSA Engine Debug Output Register        (@ 0X200)
 * @{
 *****************************************************************************/
#define EDDSA_SHIFT_DBG_DECOMP_CURR_STATE            28
#define EDDSA_MASK_DBG_DECOMP_CURR_STATE             ((u32)0x0000000F << 28)                             /*!<R 0  fsm signal in decoding module */
#define EDDSA_SHIFT_DBG_REG_ENG_RST                  27
#define EDDSA_BIT_DBG_REG_ENG_RST                    ((u32)0x00000001 << 27)                             /*!<R 0  reset signal in top module */
#define EDDSA_SHIFT_DBG_ENG_FINISH                   26
#define EDDSA_BIT_DBG_ENG_FINISH                     ((u32)0x00000001 << 26)                             /*!<R 0  fsm signal in top module */
#define EDDSA_SHIFT_DBG_FUNC_CURR_STATE              22
#define EDDSA_MASK_DBG_FUNC_CURR_STATE               ((u32)0x0000000F << 22)                             /*!<R 0  function fsm signal in top module */
#define EDDSA_SHIFT_DBG_CURR_STATE                   18
#define EDDSA_MASK_DBG_CURR_STATE                    ((u32)0x0000000F << 18)                             /*!<R 0  fsm signal in top module */
#define EDDSA_SHIFT_DBG_ADD_1_FINISH                 17
#define EDDSA_BIT_DBG_ADD_1_FINISH                   ((u32)0x00000001 << 17)                             /*!<R 0  finish signal in add_1 module */
#define EDDSA_SHIFT_DBG_ADD_2_FINISH                 16
#define EDDSA_BIT_DBG_ADD_2_FINISH                   ((u32)0x00000001 << 16)                             /*!<R 0  finish signal in add_2 module */
#define EDDSA_SHIFT_DBG_ADD_1_CURR_STATE             12
#define EDDSA_MASK_DBG_ADD_1_CURR_STATE              ((u32)0x0000000F << 12)                             /*!<R 0  fsm signal in add_1module */
#define EDDSA_SHIFT_DBG_ADD_1_MUL_1_FINISH           11
#define EDDSA_BIT_DBG_ADD_1_MUL_1_FINISH             ((u32)0x00000001 << 11)                             /*!<R 0  mul finish signal in add_1 module */
#define EDDSA_SHIFT_DBG_ADD_1_MUL_2_FINISH           10
#define EDDSA_BIT_DBG_ADD_1_MUL_2_FINISH             ((u32)0x00000001 << 10)                             /*!<R 0  mul finish signal in add_1 module */
#define EDDSA_SHIFT_DBG_ADD_1_INV_1_FINISH           9
#define EDDSA_BIT_DBG_ADD_1_INV_1_FINISH             ((u32)0x00000001 << 9)                              /*!<R 0  inv module finish signal in add_1 module */
#define EDDSA_SHIFT_DBG_ADD_1_INV_2_FINISH           8
#define EDDSA_BIT_DBG_ADD_1_INV_2_FINISH             ((u32)0x00000001 << 8)                              /*!<R 0  inv module finish signal in add_1 module */
#define EDDSA_SHIFT_DBG_ADD_2_CURR_STATE             4
#define EDDSA_MASK_DBG_ADD_2_CURR_STATE              ((u32)0x0000000F << 4)                              /*!<R 0  fsm signal in add_2 module */
#define EDDSA_SHIFT_DBG_ADD_2_MUL_1_FINISH           3
#define EDDSA_BIT_DBG_ADD_2_MUL_1_FINISH             ((u32)0x00000001 << 3)                              /*!<R 0  mul finish signal in add_2 module */
#define EDDSA_SHIFT_DBG_ADD_2_MUL_2_FINISH           2
#define EDDSA_BIT_DBG_ADD_2_MUL_2_FINISH             ((u32)0x00000001 << 2)                              /*!<R 0  mul finish signal in add_2 module */
#define EDDSA_SHIFT_DBG_ADD_2_INV_1_FINISH           1
#define EDDSA_BIT_DBG_ADD_2_INV_1_FINISH             ((u32)0x00000001 << 1)                              /*!<R 0  inv module finish signal in add_2 module */
#define EDDSA_SHIFT_DBG_ADD_2_INV_2_FINISH           0
#define EDDSA_BIT_DBG_ADD_2_INV_2_FINISH             ((u32)0x00000001 << 0)                              /*!<R 0  inv module finish signal in add_2 module */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_EDDSA
 * @{
 * @brief rtl8735b_EDDSA Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t EDDSA_ENG_INIT_REG ;                     /*!<  EdDSA Engine Initial Setting Register register,  Address offset: 0x000 */
	__IO uint32_t EDDSA_ENG_RESV0_REG ;                    /*!<  EdDSA Engine reserved0 Register register,  Address offset: 0x004 */
	__IO uint32_t EDDSA_ENG_CONF_INT_REG ;                 /*!<  EdDSA Engine Configure Interrupt Register register,  Address offset: 0x008 */
	__IO uint32_t EDDSA_ENG_CTRL_REG ;                     /*!<  EdDSA Engine Contol Register register,  Address offset: 0x00C */
	__IO uint32_t EDDSA_ENG_X1_P0_REG ;                    /*!<  EdDSA Engine X1 Point [31:0] Registers register,  Address offset: 0x010 */
	__IO uint32_t EDDSA_ENG_X1_P1_REG ;                    /*!<  EdDSA Engine X1 Point [63:32] Registers register,  Address offset: 0x014 */
	__IO uint32_t EDDSA_ENG_X1_P2_REG ;                    /*!<  EdDSA Engine X1 Point [95:64] Registers register,  Address offset: 0x018 */
	__IO uint32_t EDDSA_ENG_X1_P3_REG ;                    /*!<  EdDSA Engine X1 Point [127:96] Registers register,  Address offset: 0x01C */
	__IO uint32_t EDDSA_ENG_X1_P4_REG ;                    /*!<  EdDSA Engine X1 Point [159:128] Registers register,  Address offset: 0x020 */
	__IO uint32_t EDDSA_ENG_X1_P5_REG ;                    /*!<  EdDSA Engine X1 Point [191:160] Registers register,  Address offset: 0x024 */
	__IO uint32_t EDDSA_ENG_X1_P6_REG ;                    /*!<  EdDSA Engine X1 Point [223:192] Registers register,  Address offset: 0x028 */
	__IO uint32_t EDDSA_ENG_X1_P7_REG ;                    /*!<  EdDSA Engine X1 Point [255:224] Registers register,  Address offset: 0x02C */
	__IO uint32_t EDDSA_ENG_Y1_P0_REG ;                    /*!<  EdDSA Engine Y1 Point [31:0] Registers register,  Address offset: 0x030 */
	__IO uint32_t EDDSA_ENG_Y1_P1_REG ;                    /*!<  EdDSA Engine Y1 Point [63:32] Registers register,  Address offset: 0x034 */
	__IO uint32_t EDDSA_ENG_Y1_P2_REG ;                    /*!<  EdDSA Engine Y1 Point [95:64] Registers register,  Address offset: 0x038 */
	__IO uint32_t EDDSA_ENG_Y1_P3_REG ;                    /*!<  EdDSA Engine Y1 Point [127:96] Registers register,  Address offset: 0x03C */
	__IO uint32_t EDDSA_ENG_Y1_P4_REG ;                    /*!<  EdDSA Engine Y1 Point [159:128] Registers register,  Address offset: 0x040 */
	__IO uint32_t EDDSA_ENG_Y1_P5_REG ;                    /*!<  EdDSA Engine Y1 Point [191:160] Registers register,  Address offset: 0x044 */
	__IO uint32_t EDDSA_ENG_Y1_P6_REG ;                    /*!<  EdDSA Engine Y1 Point [223:192] Registers register,  Address offset: 0x048 */
	__IO uint32_t EDDSA_ENG_Y1_P7_REG ;                    /*!<  EdDSA Engine Y1 Point [255:224] Registers register,  Address offset: 0x04C */
	__IO uint32_t EDDSA_ENG_X2_P0_REG ;                    /*!<  EdDSA Engine X2 Point [31:0] Registers register,  Address offset: 0x050 */
	__IO uint32_t EDDSA_ENG_X2_P1_REG ;                    /*!<  EdDSA Engine X2 Point [63:32] Registers register,  Address offset: 0x054 */
	__IO uint32_t EDDSA_ENG_X2_P2_REG ;                    /*!<  EdDSA Engine X2 Point [95:64] Registers register,  Address offset: 0x058 */
	__IO uint32_t EDDSA_ENG_X2_P3_REG ;                    /*!<  EdDSA Engine X2 Point [127:96] Registers register,  Address offset: 0x05C */
	__IO uint32_t EDDSA_ENG_X2_P4_REG ;                    /*!<  EdDSA Engine X2 Point [159:128] Registers register,  Address offset: 0x060 */
	__IO uint32_t EDDSA_ENG_X2_P5_REG ;                    /*!<  EdDSA Engine X2 Point [191:160] Registers register,  Address offset: 0x064 */
	__IO uint32_t EDDSA_ENG_X2_P6_REG ;                    /*!<  EdDSA Engine X2 Point [223:192] Registers register,  Address offset: 0x068 */
	__IO uint32_t EDDSA_ENG_X2_P7_REG ;                    /*!<  EdDSA Engine X2 Point [255:224] Registers register,  Address offset: 0x06C */
	__IO uint32_t EDDSA_ENG_Y2_P0_REG ;                    /*!<  EdDSA Engine Y2 Point [31:0] Registers register,  Address offset: 0x070 */
	__IO uint32_t EDDSA_ENG_Y2_P1_REG ;                    /*!<  EdDSA Engine Y2 Point [63:32] Registers register,  Address offset: 0x074 */
	__IO uint32_t EDDSA_ENG_Y2_P2_REG ;                    /*!<  EdDSA Engine Y2 Point [95:64] Registers register,  Address offset: 0x078 */
	__IO uint32_t EDDSA_ENG_Y2_P3_REG ;                    /*!<  EdDSA Engine Y2 Point [127:96] Registers register,  Address offset: 0x07C */
	__IO uint32_t EDDSA_ENG_Y2_P4_REG ;                    /*!<  EdDSA Engine Y2 Point [159:128] Registers register,  Address offset: 0x080 */
	__IO uint32_t EDDSA_ENG_Y2_P5_REG ;                    /*!<  EdDSA Engine Y2 Point [191:160] Registers register,  Address offset: 0x084 */
	__IO uint32_t EDDSA_ENG_Y2_P6_REG ;                    /*!<  EdDSA Engine Y2 Point [223:192] Registers register,  Address offset: 0x088 */
	__IO uint32_t EDDSA_ENG_Y2_P7_REG ;                    /*!<  EdDSA Engine Y2 Point [255:224] Registers register,  Address offset: 0x08C */
	__IO uint32_t EDDSA_ENG_XO1_P0_REG ;                   /*!<  EdDSA Engine X1 Output Point [31:0] Registers register,  Address offset: 0x090 */
	__IO uint32_t EDDSA_ENG_XO1_P1_REG ;                   /*!<  EdDSA Engine X1 Output Point [63:32] Registers register,  Address offset: 0x094 */
	__IO uint32_t EDDSA_ENG_XO1_P2_REG ;                   /*!<  EdDSA Engine X1 Output Point [95:64] Registers register,  Address offset: 0x098 */
	__IO uint32_t EDDSA_ENG_XO1_P3_REG ;                   /*!<  EdDSA Engine X1 Output Point [127:96] Registers register,  Address offset: 0x09C */
	__IO uint32_t EDDSA_ENG_XO1_P4_REG ;                   /*!<  EdDSA Engine X1 Output Point [159:128] Registers register,  Address offset: 0x0A0 */
	__IO uint32_t EDDSA_ENG_XO1_P5_REG ;                   /*!<  EdDSA Engine X1 Ouput Point [191:160] Registers register,  Address offset: 0x0A4 */
	__IO uint32_t EDDSA_ENG_XO1_P6_REG ;                   /*!<  EdDSA Engine X1 Output Point [223:192] Registers register,  Address offset: 0x0A8 */
	__IO uint32_t EDDSA_ENG_XO1_P7_REG ;                   /*!<  EdDSA Engine X1 Output Point [255:224] Registers register,  Address offset: 0x0AC */
	__IO uint32_t EDDSA_ENG_YO1_P0_REG ;                   /*!<  EdDSA Engine Y1 Output Point [31:0] Registers register,  Address offset: 0x0B0 */
	__IO uint32_t EDDSA_ENG_YO1_P1_REG ;                   /*!<  EdDSA Engine Y1 Output Point [63:32] Registers register,  Address offset: 0x0B4 */
	__IO uint32_t EDDSA_ENG_YO1_P2_REG ;                   /*!<  EdDSA Engine Y1 Output Point [95:64] Registers register,  Address offset: 0x0B8 */
	__IO uint32_t EDDSA_ENG_YO1_P3_REG ;                   /*!<  EdDSA Engine Y1 Output Point [127:96] Registers register,  Address offset: 0x0BC */
	__IO uint32_t EDDSA_ENG_YO1_P4_REG ;                   /*!<  EdDSA Engine Y1 Output Point [159:128] Registers register,  Address offset: 0x0C0 */
	__IO uint32_t EDDSA_ENG_YO1_P5_REG ;                   /*!<  EdDSA Engine Y1 Ouput Point [191:160] Registers register,  Address offset: 0x0C4 */
	__IO uint32_t EDDSA_ENG_YO1_P6_REG ;                   /*!<  EdDSA Engine Y1 Output Point [223:192] Registers register,  Address offset: 0x0C8 */
	__IO uint32_t EDDSA_ENG_YO1_P7_REG ;                   /*!<  EdDSA Engine Y1 Output Point [255:224] Registers register,  Address offset: 0x0CC */
	__IO uint32_t EDDSA_ENG_XO2_P0_REG ;                   /*!<  EdDSA Engine X2 Output Point [31:0] Registers register,  Address offset: 0x0D0 */
	__IO uint32_t EDDSA_ENG_XO2_P1_REG ;                   /*!<  EdDSA Engine X2 Output Point [63:32] Registers register,  Address offset: 0x0D4 */
	__IO uint32_t EDDSA_ENG_XO2_P2_REG ;                   /*!<  EdDSA Engine X2 Output Point [95:64] Registers register,  Address offset: 0x0D8 */
	__IO uint32_t EDDSA_ENG_XO2_P3_REG ;                   /*!<  EdDSA Engine X2 Output Point [127:96] Registers register,  Address offset: 0x0DC */
	__IO uint32_t EDDSA_ENG_XO2_P4_REG ;                   /*!<  EdDSA Engine X2 Output Point [159:128] Registers register,  Address offset: 0x0E0 */
	__IO uint32_t EDDSA_ENG_XO2_P5_REG ;                   /*!<  EdDSA Engine X2 Ouput Point [191:160] Registers register,  Address offset: 0x0E4 */
	__IO uint32_t EDDSA_ENG_XO2_P6_REG ;                   /*!<  EdDSA Engine X2 Output Point [223:192] Registers register,  Address offset: 0x0E8 */
	__IO uint32_t EDDSA_ENG_XO2_P7_REG ;                   /*!<  EdDSA Engine X2 Output Point [255:224] Registers register,  Address offset: 0x0EC */
	__IO uint32_t EDDSA_ENG_YO2_P0_REG ;                   /*!<  EdDSA Engine Y2 Output Point [31:0] Registers register,  Address offset: 0x0F0 */
	__IO uint32_t EDDSA_ENG_YO2_P1_REG ;                   /*!<  EdDSA Engine Y2 Output Point [63:32] Registers register,  Address offset: 0x0F4 */
	__IO uint32_t EDDSA_ENG_YO2_P2_REG ;                   /*!<  EdDSA Engine Y2 Output Point [95:64] Registers register,  Address offset: 0x0F8 */
	__IO uint32_t EDDSA_ENG_YO2_P3_REG ;                   /*!<  EdDSA Engine Y2 Output Point [127:96] Registers register,  Address offset: 0x0FC */
	__IO uint32_t EDDSA_ENG_YO2_P4_REG ;                   /*!<  EdDSA Engine Y2 Output Point [159:128] Registers register,  Address offset: 0x100 */
	__IO uint32_t EDDSA_ENG_YO2_P5_REG ;                   /*!<  EdDSA Engine Y2 Ouput Point [191:160] Registers register,  Address offset: 0x104 */
	__IO uint32_t EDDSA_ENG_YO2_P6_REG ;                   /*!<  EdDSA Engine Y2 Output Point [223:192] Registers register,  Address offset: 0x108 */
	__IO uint32_t EDDSA_ENG_YO2_P7_REG ;                   /*!<  EdDSA Engine Y2 Output Point [255:224] Registers register,  Address offset: 0x10C */
	__IO uint32_t RSVD0[60];                               /*!<  Reserved,  Address offset:0x110-0x1FC */
	__I  uint32_t EDDSA_ENG_DBG_OUTPUT_REG ;               /*!<  EdDSA Engine Debug Output Register register,            Address offset: 0x200 */
} EDDSA_TypeDef;
/** @} */

#endif
