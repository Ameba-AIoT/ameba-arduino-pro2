.syntax unified
    .arch   armv7-m       @ or armv8-m.main
    .thumb
    .global ulaw_encode_asm_16
    .type   ulaw_encode_asm_16, %function

@ C function prototype:
@ void ulaw_encode_asm_16(uint16_t *input, uint8_t *output, size_t len, const uint8_t *lut)
@
@ Register allocation (AAPCS):
@ r0: input  (uint16_t *)
@ r1: output (uint8_t *)
@ r2: len    (size_t)
@ r3: lut    (const uint8_t *)

@ Macro: Process 4 samples (read, lookup, pack)
.macro encode_4_samples
    ldrh    r4, [r0], #2       @ Load input[0] (16-bit), r0 += 2
    ldrh    r5, [r0], #2       @ Load input[1] (16-bit), r0 += 2
    ldrh    r6, [r0], #2       @ Load input[2] (16-bit), r0 += 2
    ldrh    r7, [r0], #2       @ Load input[3] (16-bit), r0 += 2

    ldrb    r4, [r3, r4]       @ r4 = lut[r4]
    ldrb    r5, [r3, r5]       @ r5 = lut[r5]
    ldrb    r6, [r3, r6]       @ r6 = lut[r6]
    ldrb    r7, [r3, r7]       @ r7 = lut[r7]

    @ Pack 4 bytes into one 32-bit word
    lsls    r5, r5, #8
    lsls    r6, r6, #16
    lsls    r7, r7, #24

    orrs    r4, r4, r5
    orrs    r6, r6, r7
    orrs    r4, r4, r6
.endm

ulaw_encode_asm_16:
    push    {r4-r11, lr}     @ Save working registers and link register

loop16:
    @ --- Loop unrolling, process 16 samples consecutively ---

    @ Process samples 1-4, result packed in r4
    encode_4_samples
    mov     r8, r4           @ Temporarily store the result in r8

    @ Process samples 5-8, result packed in r4
    encode_4_samples
    mov     r9, r4           @ Temporarily store the result in r9

    @ Process samples 9-12, result packed in r4
    encode_4_samples
    mov     r10, r4          @ Temporarily store the result in r10

    @ Process samples 13-16, result packed in r4
    encode_4_samples
    mov     r11, r4          @ Temporarily store the result in r11

    @ --- Write the 16-byte result at once ---
    stmia   r1!, {r8-r11}    @ Store r8-r11 (16 bytes) to output, r1 += 16

    @ --- Loop control ---
    subs    r2, r2, #16      @ len -= 16
    bne     loop16           @ If len > 0, continue loop

    pop     {r4-r11, pc}     @ Restore registers and return
    .size   ulaw_encode_asm_16, . - ulaw_encode_asm_16