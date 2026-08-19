#include "uart.h"

void main(void)
{
    uart_init();
    uart_puts("MIPS EFI firmware: early env OK\n");
    while (1)
        ;
}