.section .text.boot
.globl _start
_start:
    /* temp stack */
    la      $sp, 0x80400000

    /* gcc gets mad at us if we don't do it the non-PIC way */
    la      $t9, main
    jalr    $t9
    nop

1:  b       1b
    nop