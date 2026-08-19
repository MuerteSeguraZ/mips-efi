#include "efi/efi.h"
#include "uart.h"

/* Convert one UTF-16 character to our UART (we only care about ASCII for now) */
static void output_char16(CHAR16 c)
{
    if (c == 0)
        return;
    if (c < 0x80)
        uart_putc((char)c);
    else
        uart_putc('?');
}

static EFI_STATUS efi_output_string(
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    CHAR16 *String)
{
    (void)This;

    if (!String)
        return EFI_SUCCESS;

    while (*String) {
        if (*String == L'\n')
            uart_putc('\r');
        output_char16(*String);
        String++;
    }
    return EFI_SUCCESS;
}

static EFI_STATUS efi_text_reset(
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
    BOOLEAN ExtendedVerification)
{
    (void)This;
    (void)ExtendedVerification;
    return EFI_SUCCESS;
}

static EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL gConOut = {
    .Reset = efi_text_reset,
    .OutputString = efi_output_string,
};

void efi_console_init(EFI_SYSTEM_TABLE *st)
{
    st->ConOut = &gConOut;
    st->ConsoleOutHandle = (EFI_HANDLE)&gConOut;   /* any unique value is fine */
}