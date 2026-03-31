.syntax unified
    .arch   armv7-m
    .thumb
    .global ulaw_decode_asm_8
    .type   ulaw_decode_asm_8, %function

@ C function prototype:
@ void ulaw_decode_asm_8(const uint8_t *input, uint16_t *output, size_t len, const uint16_t *lut)
@
@ Register allocation (AAPCS):
@ r0: input  (const uint8_t *)
@ r1: output (uint16_t *)
@ r2: len    (size_t)
@ r3: lut    (const uint16_t *)

@ Macro: Process 4 samples (read, unpack, lookup, pack)
.macro decode_4_samples
    @ 1. Load 4 8-bit input samples at once
    ldr     r4, [r0], #4       @ Load 4 bytes from input to r4, input += 4

    @ 2. Unpack the 4 bytes in r4 into different registers
    uxtb    r5, r4             @ r5 = byte 0 (sample 1)
    lsr     r4, r4, #8
    uxtb    r6, r4             @ r6 = byte 1 (sample 2)
    lsr     r4, r4, #8
    uxtb    r7, r4             @ r7 = byte 2 (sample 3)
    lsr     r4, r4, #8         @ r4 = byte 3 (sample 4)

    @ 3. Parallel table lookup (note using ldrh to read 16-bit results)
    @ Use lsl #1 to convert byte index to half-word offset
    ldrh    r5, [r3, r5, lsl #1]  @ r5 = lut[r5]
    ldrh    r6, [r3, r6, lsl #1]  @ r6 = lut[r6]
    ldrh    r7, [r3, r7, lsl #1]  @ r7 = lut[r7]
    ldrh    r4, [r3, r4, lsl #1]  @ r4 = lut[r4]

    @ 4. Pack the 4 16-bit results into 2 32-bit words
    lsl     r6, r6, #16          @ Left shift sample 2
    orr     r5, r5, r6           @ Merge sample 1 and 2 into r5
    
    lsl     r4, r4, #16          @ Left shift sample 4
    orr     r7, r7, r4           @ Merge sample 3 and 4 into r7
.endm

ulaw_decode_asm_8:
    push    {r4-r11, lr}

loop8:
    @ --- Loop unrolling, process 8 samples consecutively ---
    
    @ Process samples 1-4, results packed in r5 and r7
    decode_4_samples
    mov     r8, r5              @ Temp store {sample 2, sample 1}
    mov     r9, r7              @ Temp store {sample 4, sample 3}

    @ Process samples 5-8, results packed in r5 and r7
    decode_4_samples
    mov     r10, r5             @ Temp store {sample 6, sample 5}
    mov     r11, r7             @ Temp store {sample 8, sample 7}

    @ --- Write 8 16-bit samples (16 bytes) at once ---
    stmia   r1!, {r8-r11}       @ Store r8-r11 (16 bytes) to output, r1 += 16

    @ --- Loop control ---
    subs    r2, r2, #8          @ len -= 8
    bne     loop8

    pop     {r4-r11, pc}
    .size   ulaw_decode_asm_8, . - ulaw_decode_asm_8