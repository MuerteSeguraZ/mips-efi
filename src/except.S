.section .text.tlb, "ax"
.globl tlb_refill
tlb_refill:
    la $a0, msg_tlb
    j exception_common
    nop

.section .text.general, "ax"
.globl general_exception
general_exception:
    la $a0, msg_general
    j exception_common
    nop

.section .text
.globl exception_common
exception_common:
    /* Here, $a0 already has the message pointer */
    la $t9, uart_puts
    jalr $t9
    nop
1:  b 1b
    nop

.section .rodata
msg_tlb:     .asciz "EXCEPTION: TLB refill\n"
msg_general: .asciz "EXCEPTION: general\n"