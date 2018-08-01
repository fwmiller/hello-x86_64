#define COM1_BASE	0x3f8
#define COM2_BASE	0x2f8
#define COM3_BASE	0x3e8
#define COM4_BASE	0x2e8

#define TX_FIFO		0

#define COM_TX_FIFO ((short int)(COM1_BASE + TX_FIFO))

typedef unsigned char	u8;
typedef unsigned short	u16;

static inline void outb(u16 port, u8 val) {
	__asm volatile ( "outb %0, %1" : : "a"(val), "d"(port) );
}

int putchar(int ch)
{
	outb(COM_TX_FIFO, ch);
	return ch;
}
