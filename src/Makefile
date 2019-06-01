INCDIR = ../include

CC = gcc
CFLAGS = -c -Wall -m64 -Og -nostdinc -ffreestanding
LD = gcc
LDFLAGS = -nostdlib -Wl,-n,-T,link.ld -no-pie
RM = rm -fr

OBJS = boot.o mb2.o kmain.o print.o string.o uart.o
KERNEL = kmain.elf

INDENT_RULES = -nbad -bap -nbc -bbo -hnl -br -brs -c33 -cd33 -ncdb -ce -ci4 -cli0 -d0 -di1 -nfc1 -i8 -ip0 -l80 -lp -npcs -nprs -npsl -sai -saf -saw -ncs -nsc -sob -nfca -cp33 -ss -ts8 -il1

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

indent: clean
	indent $(INDENT_RULES) *.c
	rm *~

.c.o:
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $<

.S.o:
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $<
