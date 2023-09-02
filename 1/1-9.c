/* p.20								     	    *
 * Exercise 1-9. Write a program to copy its input to its output, replacing *
 *		 each string of one or more blanks by a single blank 	    */

#include <stdio.h>

main()
{
	int c;

	while ((c = getchar()) != '\n') {
		if (c == ' ')
			putchar(c);
		while (c == ' ')
			c = getchar();
		putchar(c);
	}
}
		