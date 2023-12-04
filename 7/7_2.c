/*
 * Ex 7-2. Write a program that will print arbitary input in a sen-
 * sible way. As a minimum, it whould print non-graphic characters
 * in octal or hexadecimal according to local custom, and break
 * long text lines.
 */
#include <stdio.h>
#include <ctype.h>

#define MAXLINE 15

main()
{
	int c;
	int cnt = 0; /* count of one line */
	while ((c = getchar()) != EOF) {
		if (!isgraph(c))
			printf("[%2x]", c);
		else 
			printf("(%2c)", c);
		if (++cnt > MAXLINE) {
			putchar('\n');
			cnt = 0;
		}
	}
	putchar('\n');
}