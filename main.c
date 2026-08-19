#include "uart.h"

void main(void)
{
    uart_init();
    uart_puts("MIPS EFI firmware: hello\n");
    while (1)
        ;
}