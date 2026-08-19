#include "uart.h"
#include "efi/efi.h"

void main(void)
{
    uart_init();
    uart_puts("MIPS EFI firmware: early env OK\n");

    efi_init();
    uart_puts("EFI System Table init\n");

    uart_puts("Triggering exception...\n");
    
    /* Let's have fun. Trigger an exception by storing to address 0 (kuseg, no TLB entry) */
    *(volatile unsigned int *)0 = 0xdeadbeef;

    uart_puts("This line should never appear\n");
    while (1)
        ;
}