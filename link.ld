ENTRY(_start)

SECTIONS
{
    . = 0x80000000;

    .text.tlb : {
        *(.text.tlb)
    }

    . = 0x80000180;
    .text.general : {
        *(.text.general)
    }

    . = 0x80100000;

    .text : {
        *(.text.boot)
        *(.text*)
    }

    .rodata : { *(.rodata*) }
    .data : { *(.data*) }
    .bss : {
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        __bss_end = .;
    }

    /* Stack grows down from here */
    . = ALIGN(16);
    . += 0x10000;          /* 64 KB */
    __stack_top = .;
}