#include "uart.h"

/* ISA 16550 that -nographic actually uses on QEMU Malta */
#define UART_BASE 0xb80003f8

#define UART_THR  (UART_BASE + 0x00)
#define UART_LSR  (UART_BASE + 0x05)
#define UART_LSR_THRE 0x20

static inline void mmio_write8(unsigned long addr, unsigned char val)
{
    *(volatile unsigned char *)addr = val;
}

static inline unsigned char mmio_read8(unsigned long addr)
{
    return *(volatile unsigned char *)addr;
}

void uart_init(void)
{
}

void uart_putc(char c)
{
    while ((mmio_read8(UART_LSR) & UART_LSR_THRE) == 0)
        ;
    mmio_write8(UART_THR, (unsigned char)c);
}

void uart_puts(const char *s)
{
    while (*s) {
        if (*s == '\n')
            uart_putc('\r');
        uart_putc(*s++);
    }
}