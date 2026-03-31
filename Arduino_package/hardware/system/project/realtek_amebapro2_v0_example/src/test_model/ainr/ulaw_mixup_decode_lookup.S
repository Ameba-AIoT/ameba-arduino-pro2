.syntax unified
    .arch   armv7-m
    .thumb
    .global ulaw_mixup_decode_asm_8
    .type   ulaw_mixup_decode_asm_8, %function

@ C function prototype:
@ void ulaw_mixup_decode_asm_8(
@     const uint8_t *denoised_input,  // r0
@     const uint8_t *original_input,  // r1
@     uint16_t *output,               // r2
@     size_t len,                     // r3
@     const uint16_t *lut             // Stored on the stack
@ )

@ Macro: Process 4 samples (read, mix, lookup, pack)
.macro mixup_decode_4_samples
    @ 1. Load 4 8-bit samples from two sources at once
    ldr     r4, [r0], #4        @ r4 = denoised[0..3], r0 += 4
    ldr     r5, [r1], #4        @ r5 = original[0..3], r1 += 4

    @ --- Process sample 0 ---
    uxtb    r6, r4              @ r6 = denoised[0]
    uxtb    r7, r5              @ r7 = original[0]
    add     r6, r6, r6, lsl #1  @ r6 = denoised[0] * 3
    add     r6, r6, r7          @ r6 = (denoised[0] * 3) + original[0]
    lsr     r6, r6, #2          @ r6 = mixed_index
    ldrh    r6, [r12, r6, lsl #1] @ r6 = decoded_val_0

    @ --- Process sample 1 ---
    ubfx    r8, r4, #8, #8      @ r8 = denoised[1]
    ubfx    r9, r5, #8, #8      @ r9 = original[1]
    add     r8, r8, r8, lsl #1
    add     r8, r8, r9
    lsr     r8, r8, #2
    ldrh    r8, [r12, r8, lsl #1] @ r8 = decoded_val_1

    @ --- Process sample 2 ---
    ubfx    r7, r4, #16, #8     @ r7 = denoised[2]
    ubfx    r9, r5, #16, #8     @ r9 = original[2]
    add     r7, r7, r7, lsl #1
    add     r7, r7, r9
    lsr     r7, r7, #2
    ldrh    r7, [r12, r7, lsl #1] @ r7 = decoded_val_2

    @ --- Process sample 3 ---
    lsr     r4, r4, #24         @ r4 = denoised[3]
    lsr     r5, r5, #24         @ r5 = original[3]
    add     r4, r4, r4, lsl #1
    add     r4, r4, r5
    lsr     r4, r4, #2
    ldrh    r4, [r12, r4, lsl #1] @ r4 = decoded_val_3

    @ --- Pack 4 16-bit results into 2 32-bit words ---
    lsl     r8, r8, #16          @ Left shift decoded_val_1 to the high 16-bits
    orr     r5, r6, r8           @ r5 = {decoded_val_1, decoded_val_0}
    
    lsl     r4, r4, #16          @ Left shift decoded_val_3 to the high 16-bits
    orr     r9, r7, r4           @ r9 = {decoded_val_3, decoded_val_2}
.endm

ulaw_mixup_decode_asm_8:
    push    {r4-r12, lr}
    ldr     r12, [sp, #40]

loop8:
    @ Process samples 1-4, results are in r5 and r9
    mixup_decode_4_samples
    @ Temporarily store the results in r10, r11 which won't be overwritten by the next macro call
    mov     r10, r5             @ r10 = {decoded_1, decoded_0}
    mov     r11, r9             @ r11 = {decoded_3, decoded_2}

    @ Process samples 5-8, results are again in r5 and r9
    mixup_decode_4_samples
    


    @ Corrected order:
    @ First, process the results of the second operation (they are in r5, r9 which could be overwritten)
    mov     r6, r5              @ r6 = samples {5, 4}
    mov     r7, r9              @ r7 = samples {7, 6}
    @ Then, process the results of the first operation (they are in the safe r10, r11)
    mov     r4, r10             @ r4 = samples {1, 0}
    mov     r5, r11             @ r5 = samples {3, 2}

    @ Write 8 16-bit samples (16 bytes) at once, register list is sorted
    stmia   r2!, {r4-r7}        @ Store r4-r7 (16 bytes) to output, output += 16

    @ --- Loop control ---
    subs    r3, r3, #8
    bne     loop8

    pop     {r4-r12, pc}
    .size   ulaw_mixup_decode_asm_8, . - ulaw_mixup_decode_asm_8