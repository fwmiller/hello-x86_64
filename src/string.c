#include <stdint.h>
#include <string.h>

void uint2str(uint_t v, char *s, int base)
{
	if (v == 0) {
		s[0] = '0';
		s[1] = '\0';
	} else {
		char s1[80];
		uint_t v1;
		int i = 0, j = 0;

		while (v > 0) {
			v1 = v % base;
			if (v1 < 10)
				s1[i++] = v1 + '0';
			else
				s1[i++] = v1 - 10 + 'a';
			v /= base;
		}
		while (i > 0)
			s[j++] = s1[--i];
		s[j] = '\0';
	}
}

size_t strlen(const char *s)
{
	int i = 0;

	while (s[i] != '\0')
		i++;
	return (size_t) i;
}
