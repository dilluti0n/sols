/* Ex 5-2. Write getfloat, the floating-point analog of getint. What type does getfloat return as its function value? */

#include <ctype.h>
#include <stdio.h>

#define MAXBUF 100

int getch(void);
void ungetch(int);
int getfloat(double*);

int bp = 0;
char buf[MAXBUF];

int main()
{
	double f = -1;
	getfloat(&f);
	getfloat(&f);
	printf("%g\n",f);
}

int getfloat (double* pf)
{
	int c, sign = 1;

	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != '+' && c != '-' && c != '.')
		return 0; /* not a number */
	sign = (c == '-')? -1:1;
	if (c == '+'||c == '-')
		if (!isdigit(c = getch()) && c != '.') {
			ungetch(c);
			return 0;
		}
	*pf = 0;
	ungetch(c);
	while (isdigit(c = getch()))
		*pf = *pf * 10 + (c - '0');
	if (c == '.') {
		int cnt = 0;
		while (isdigit(c = getch())) {
			*pf = *pf * 10 + (c - '0');
			cnt ++;
		}
		while (cnt--)
			*pf /= 10;
	}
	*pf *= sign;

	if (c != EOF)
		ungetch(c);
	return c;
}

int getch()
{
	return (bp > 0)?buf[--bp]:getchar();
}

void ungetch(int c)
{
	if (bp < MAXBUF)
		buf[bp++] = c;
	else
		printf("ungetch: buffer full\n");
}
