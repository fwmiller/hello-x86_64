#if 0
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#endif
#include <ctype.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void uint2str(uint_t v, char *s, int base);
int uart_putchar(int ch);

static void put1(char *s, int *pos, int c)
{
	if (s != NULL) {
		s[(*pos)++] = (char)c;
		return;
	}
	uart_putchar(c);
}

void print(char *string, int *pos, const char *fmt, va_list args)
{
	int len;
	char pad;

 printloop:
	if (*fmt == '\0')
		goto printend;

	if (*fmt != '%') {
		put1(string, pos, (int)*(fmt++));
		goto printloop;
	}
	fmt++;

	if (*fmt == '0') {
		pad = '0';
		while (*(++fmt) == '0') ;
	} else
		pad = ' ';

	len = 0;
	while (isdigit(*fmt))
		len = len * 10 + (*(fmt++) - '0');

	if (*fmt == 'h' || *fmt == 'l' || *fmt == 'q' || *fmt == 'L')
		fmt++;

	switch (*fmt) {
	case 'd':
		{
			char s[80];
			int v, l, i;

			v = va_arg(args, int);

			uint2str((v < 0 ? (uint_t) - v : (uint_t) v), s, 10);

			if (len != 0 && (l = strlen(s)) <= len) {
				int padlen;

				if (v < 0)
					padlen = len - l - 1;
				else
					padlen = len - l;

				for (i = 0; i < padlen; i++)
					put1(string, pos, (int)pad);
			}
			if (v < 0)
				put1(string, pos, (int)'-');
			for (i = 0; s[i] != '\0'; i++)
				put1(string, pos, (int)s[i]);
			fmt++;
		}
		break;

	case 'u':
	case 'x':
		{
			char s[80];
			uint_t v;
			int l, i;

			v = va_arg(args, uint_t);
			uint2str(v, s, (*fmt == 'x' ? 16 : 10));

			if (len != 0 && (l = strlen(s)) <= len)
				for (i = 0; i < len - l; i++)
					put1(string, pos, (int)pad);

			for (i = 0; s[i] != '\0'; i++)
				put1(string, pos, (int)s[i]);

			fmt++;
		}
		break;

	case 's':
		{
			char *s;
			int l, i;

			s = va_arg(args, char *);

			i = 0;
			if (len == 0) {
				while (s[i] != '\0')
					put1(string, pos, (int)s[i++]);
			} else {
				while (i < len && s[i] != '\0')
					put1(string, pos, (int)s[i++]);
			}

			if (len != 0 && (l = strlen(s)) <= len)
				for (i = 0; i < len - l; i++)
					put1(string, pos, (int)' ');

			fmt++;
		}
		break;

	case 'c':
		{
			int c = va_arg(args, int);

			put1(string, pos, c);
			fmt++;
		}
		break;
	case '%':
		put1(string, pos, (int)'%');
		fmt++;
		break;
	default:
		put1(string, pos, (int)*(fmt++));
	}

	goto printloop;

 printend:
	if (string != NULL)
		put1(string, pos, (int)'\0');
}

void kprintf(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);

	print(NULL, NULL, fmt, args);
}
