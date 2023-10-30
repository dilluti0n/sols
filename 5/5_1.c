/* Ex 5-1. as written, getint treats a + or - not followed by a digit as a valid representation of zero. Fix it to push such a character back on the input. */

#include <ctype.h>
#include <stdio.h>

#define MAXBUF 100

int bp = 0;
char buf[MAXBUF];

int getch();
void ungetch(int);

int getint (int* pn)
{
	int c, sign = 1;

	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != '+' && c != '-')
		return 0; /* not a number */
	sign = (c == '-')? -1 : 1;
	if (c == '+' || c == '-')
		if (!isdigit(c = getch())) {
			ungetch(c);
			return 0; /* not a number */
		}

	*pn = 0;
	ungetch(c);
	while (isdigit(c = getch()))
		*pn = *pn * 10 + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

int getch()
{
	return (bp > 0)? buf[--bp]:getchar();
}

void ungetch(int c)
{
	if (bp < MAXBUF)
		buf[bp++] = c;
	else
		printf("ungetch: buffer full\n");
}

int main()
{
	int n[2] = {-1, -1};
	char c;
	c = getint(n);
	getint(n + 1);
	printf("%d, %d, %d\n",n[0],n[1],c);
}

