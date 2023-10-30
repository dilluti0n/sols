/* Ex 5-5. Write versions of the library functions strncpy, strncat, and strncmp, which operate on at most the first n characters of their argument strings. For example, strncpy(s,t,n) copies at most n characters of t to s. Full descriptions are in Appendix B */

#include <stdio.h>

void strncpy_e (char* s, char* t, int n)
{
	while (n-- && (*s++ = *t++))
		;
}

void strncat_e (char* s, char* t, int n)
{
	while (*++s)
		;
	while (n-- && (*s++ = *t++))
		;
}

int strncmp_e (char* s, char* t, int n)
{
	for (;n > 1 && *s == *t; n--, s++, t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
}
	

main()
{
	char s[100] = "aaaa enough!";
	char* t = "good";
	strncpy_e (s,t,4);
	puts(s);
	puts(t);
	strncat_e (s,t,5);
	puts(s);
	printf("%d %d\n",strncmp_e (s,s,4),strncmp_e ("goodg","good",4));
}