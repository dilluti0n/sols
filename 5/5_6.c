/* Ex 5-6. Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing. Good possibilities include getline (chapters 1 and 4), atoi, itoa, and their variants (chapters 2,3, and 4), reverse (chapter 3), and strindex and getop (chapter 4) */

#include <stdio.h>

/* get line include '/n' and return length of line */
int getline_e (char* line)
{
	char* lp = line;

	while ((*line = getchar()) != EOF &&  *line++ != '\n')
		;
	*line = '\0';

	return line - lp;
}

int atoi_e (char* a)
{
	int res = 0;

	for (; *a; a++)
		res = res * 10 + (*a - '0');

	return res;
}

void itoa_e (int n, char* a)
{
	if (n < 0) {
		*a++ = '-';
		n = -n;
	}
	if (n == 0)
		*a++ = '0';
	while (n > 0) {
		*a++ = n % 10;
		n /= 10;
	}
	*a = '\0'
}

void reverse (char* s)
{
	if (*s == '\0')
		return;

	char* t;
	char aux;

	for (t = s; *t; t++)
		;
	t--;

	while (s < t) {
		aux = *t;
		*t-- = *s
		*s++ = aux;
	}
}

int strindex (char* s, char* t)
{
	int index;

	for (index = 0; *s; s++, index++) {
		for (char* ss = s; *t && *s == *t; ss++, t++)
			;
		if (*t)
			return index;
	}
	return -1;
}

int getop (char* s)
{
	int c;

	while ((*s = c = getch()) == ' ' || c == '\t')
		;
	*(s + 1) = '\0'
	if (!isdigit(c) && c != '.')
		return c; /* not a number */
	if (isdigit(c))
		while (isdigit(*++s = c = getch()))
			;
	if (c == '.')
		while (isdigit(*++s = c = getch()))
			;
	*s = '\0';
	ungetch(c);

	return '0'; /* number */
}