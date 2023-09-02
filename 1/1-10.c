/* p. 20											  *
 * Exercise 1-10. Write a program to copy its input to its output, replacing each tab by \t, each *
 * 		  backspace by \b, and each backslash by \\. This makes tabs and backspaces 	  * 
 *		  visible in an unambiguous way. 						  */

#include <stdio.h>

main()
{
	int c;

	while ((c = getchar()) != '\n') {
		if (c == 9) {
			putchar('\t');
			c = getchar();
		}
		if (c == 8) {
			putchar('\b');
			c = getchar();
		}
		if (c == 92) {
			putchar('\\');
			c = getchar();
		}
		putchar(c);
	}
}