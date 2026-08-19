#include "uart.h"
#include "efi/efi.h"

void main(void)
{
    uart_init();
    uart_puts("MIPS EFI firmware: early env OK\n");

    efi_init();
    uart_puts("EFI System Table + ConOut ready\n");

    static CHAR16 msg[] = {
        'H','e','l','l','o',' ','f','r','o','m',' ',
        'E','F','I',' ','C','o','n','O','u','t','!',
        '\r','\n', 0
    };

    EFI_SYSTEM_TABLE *st = efi_get_system_table();
    st->ConOut->OutputString(st->ConOut, msg);

    while (1)
        ;
}