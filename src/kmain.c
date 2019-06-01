#define PROMPT	"> "

void kprintf(const char *fmt, ...);
int uart_getchar();

void kmain()
{
	unsigned char ch;

	kprintf("Roadrunner\n");
	kprintf("Type ctrl-a x to exit\n");

	kprintf(PROMPT);
	for (;;) {
		ch = uart_getchar();
		kprintf("%c", ch);
		if (ch == '\r') {
			kprintf("\n");
			kprintf(PROMPT);
		}
	}
}
