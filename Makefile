CC = gcc
CFLAGS = -c -Wall
LD = gcc
LDFLAGS = -nostdlib -nostartfiles -nodefaultlibs
RM = rm -fr

OBJS = boot.o mb2.o kprint.o kmain.o uart.o

all: build

build: $(OBJS) link.ld
	$(LD) $(LDFLAGS) -Wl,-n,-T,link.ld -o kmain.elf $(OBJS)
	objdump -x -d -s kmain.elf > kmain.elf.txt
	mkdir -p isofiles/boot/grub
	cp kmain.elf isofiles/boot/
	cp grub.cfg isofiles/boot/grub
	grub-mkrescue -o iso.img isofiles

run: build
	qemu-system-x86_64 -nographic -no-reboot -drive format=raw,file=iso.img

clean:
	$(RM) $(OBJS) kmain.elf kmain.elf.txt isofiles iso.img

.c.o:
	$(CC) $(CFLAGS) -o $@ $<

.S.o:
	$(CC) $(CFLAGS) -o $@ $<
