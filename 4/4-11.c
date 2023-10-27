/* 4-11. Modify getop so that it doesn't need to use ungetch. Hint: use an internal static variable. */
#include <stdio.h>
#define BUFSIZE 100
#define NUMBER '0'

int getop(char s[])
{
	int i = 0, c;

	static int bufp = 0;
	static char buf[BUFSIZE];

	while ((s[0] = c = (bufp > 0)? buf[--bufp] : getchar()) == ' '|| c == '\t')
		;
	s[1] = '\0';
	
	if (isupper(c)) {
		variable = c;
		return VARGET; /* if supper, get variable from var_buff */
	} if (!isdigit(c) && c != '.' && c != '-' && c != '!')
		return c; /* not a number */
	if (c == '-'){
		int next = (bufp > 0)? buf[--bufp] : getchar();
		if (!isdigit(next) && next != '.') {
			(bufp < BUFSIZE)? buf[bufp++] = next: printf("buffer full\n");
			return c; /* return '-' as an operator */
		} else
			s[++i] = c = next; /* negative number */
	} if (c == '!') /* command mode */
		return getcmd();
	if (isdigit(c))
		while (isdigit(s[++i] = c = (bufp > 0)? buf[--bufp] : getchar()))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = (bufp > 0)? buf[--bufp] : getchar()))
			;
	s[i] = '\0';
	
	(bufp < BUFSIZE)? buf[bufp++] = c: printf("buffer full\n");
	
	return NUMBER;
}

