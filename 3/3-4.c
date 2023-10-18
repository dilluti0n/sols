/* 3-4. In a two's complement number representation, our version of itoa does not handle the largest negative number, that is, the value of n equal to -2^31. Explane why not. Modify it to print that value correctly, regardless of the machine on which it runs. */
#include <stdio.h>
#include <string.h>

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

void itoa_kr (int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	strrev(s);
}

/* -(-2^31) = 2^31 cannot be represented by signed int(-2^31 ~ 2^31 - 1). */
void itoa (int n, char s[])
{
	int i, sign;
	unsigned u = n;

	if ((sign = n) < 0)
		u = -n;
	i = 0;
	do {
		s[i++] = u % 10 + '0';
	} while ((u /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	strrev(s);
}