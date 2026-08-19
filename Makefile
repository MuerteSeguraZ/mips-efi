CROSS = mipsel-linux-gnu-gcc
CC = $(CROSS)gcc
LD = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy

CFLAGS = -ffreestanding -fno-builtin -fno-pic -mno-abicalls -mno-shared -G0 -Wall -O2 -msoft-float
LDFLAGS = -T link.ld -nostdlib

OBJS = start.o main.o uart.o

all: firmware.bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

firmware.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

firmware.bin: firmware.elf
	$(OBJCOPY) -O binary $< $@

run: firmware.elf
	qemu-system-mipsel -M malta -nographic -kernel firmware.elf

clean:
	rm -f *.o *.elf *.bin