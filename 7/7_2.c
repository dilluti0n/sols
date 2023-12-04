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
	printf("[%2x]", c); /* EOF */
/*
 * Since char variables have 1 byte of storage, it can be considered
 * that printing EOF with %x in printf should print "ff", but it ac-
 * tually prints "ffffffff". This is because when a char value is p-
 * assed to a function like printf, it undergoes integer promotion. 
 * Integer promotion typically converts a char to an int, and if char
 * is signed and its value is negative, this promotion involves sign 
 * extension to maintain the same numerical value.
 */
	putchar('\n');
	return 0;
}