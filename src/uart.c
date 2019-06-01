#define COM_TX_FIFO	((short) 0x3f8)
#define COM_RX_FIFO	((short) 0x3f8)
#define COM_RX_STATUS	((short) 0x3fd)

static inline unsigned char inb(unsigned short port)
{
	unsigned char val;
	__asm__ __volatile__("inb %w1, %0":"=a"(val):"Nd"(port));
	return val;
}

static inline void outb(unsigned short port, unsigned char val)
{
	__asm__ volatile ("outb %0, %1"::"a" (val), "d"(port));
}

int uart_getchar()
{
	while (!(inb(COM_RX_STATUS) & 0x01)) ;
	return (int)inb(COM_RX_FIFO);
}

void uart_putchar(int ch)
{
	outb(COM_TX_FIFO, ch);
}
