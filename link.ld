ENTRY(_start)

SECTIONS
{
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
}