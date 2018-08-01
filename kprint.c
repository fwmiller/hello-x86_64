int putchar(int ch);

void
kprint(char *s)
{
	if (s == (char *) 0)
		return;

	for (; *s != 0; s++)
		putchar(*s);
}
