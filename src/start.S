.section .text.boot
.globl _start
_start:
    /* Here's what we'll setup (CP0 Status):
     * - Set CU0 so we can access CP0,
     * - Clear BEV so we can use the normal vectors at 0x80000xxx
     * - Clear EXL/ERL/IE/KSU,
     * - Nothing more, for now.
     */
    mfc0 $t0, $12        /* Status */
    li $t1, 0x10000000   /* CU0 */
    or $t0, $t0, $t1
    li $t1, 0x00400000   /* BEV bit */
    not $t1, $t1
    and $t0, $t0, $t1    /* clear BEV */
    li $t1, ~0x1f        /* clear IE, EXL, ERL, KSU */
    and $t0, $t0, $t1
    mtc0 $t0, $12
    ehb                  /* hazard barrier (yes, this is safe on 24Kf) */

     /* Now, let's clear the BSS. */
     la $t0, __bss_start
     la $t1, __bss_end
1:
     beq $t0, $t1, 2f
     nop
     sw $zero, 0($t0)
     addiu $t0, $t0, 4
     b 1b
     nop
2:

     /* Now, let's set the stack. */
     la $sp, __stack_top

     /* Call main... */
     la $t9, main
     jalr $t9
     nop

     /* ...and IF main returns, just hang. */
1:   b 1b
     nop
  