CC = gcc
CFLAGS = -c -Wall -m64 -Og -nostdinc -ffreestanding
LD = gcc
LDFLAGS = -nostdlib -Wl,-n,-T,link.ld -no-pie
RM = rm -fr

OBJS = boot.o mb2.o kprint.o kmain.o uart.o
KERNEL = kmain.elf

all: build

build: $(OBJS) link.ld
	$(LD) $(LDFLAGS) -o $(KERNEL) $(OBJS)
	mkdir -p isofiles/boot/grub
	cp $(KERNEL) isofiles/boot/
	cp grub.cfg isofiles/boot/grub
	grub-mkrescue -o iso.img isofiles

run: build
	qemu-system-x86_64 -nographic -no-reboot -drive format=raw,file=iso.img

clean:
	$(RM) $(OBJS) $(KERNEL) isofiles iso.img

.c.o:
	$(CC) $(CFLAGS) -o $@ $<

.S.o:
	$(CC) $(CFLAGS) -o $@ $<
