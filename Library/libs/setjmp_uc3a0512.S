    .text
    .align 4
    .global setjmp

setjmp:
    stm	    r12, r0, r1, r2, r3, r4, r5, r6, r7, sp, lr
    retal   0

