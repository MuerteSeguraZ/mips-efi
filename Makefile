CROSS   = mipsel-linux-gnu-
CC      = $(CROSS)gcc
LD      = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy

CFLAGS  = -ffreestanding -fno-builtin -fno-pic -mno-abicalls -mno-shared \
          -G0 -Wall -O2 -msoft-float -Iinclude
LDFLAGS = -T link.ld -nostdlib

SRCS_S  = src/start.S src/except.S
SRCS_C  = src/main.c src/uart.c src/efi/system_table.c
OBJS    = $(SRCS_S:.S=.o) $(SRCS_C:.c=.o)

all: firmware.elf

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

src/%.o: src/%.S
	$(CC) $(CFLAGS) -c $< -o $@

firmware.elf: $(OBJS) link.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

run: firmware.elf
	qemu-system-mipsel -M malta -nographic -kernel firmware.elf

clean:
	rm -f src/*.o firmware.elf firmware.bin

.PHONY: all run clean