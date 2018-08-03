#define PROMPT	"> "

void kprint(char *s);

int uart_getchar();
void uart_putchar(int ch);

void
kmain()
{
	unsigned char ch;

	kprint("Hello world!\n");
	kprint("Type ctrl-a x to exit\n");

	kprint(PROMPT);
	for (;;) {
		ch = uart_getchar();
		uart_putchar(ch);
		if (ch == '\r') {
			uart_putchar('\n');
			kprint(PROMPT);
		}
	}
}
