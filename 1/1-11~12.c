/* p. 21****************************************************************************************************
 * Ex 1-11. How would you test the word count program? What kinds of input are most likely to uncover bugs *
 *	    if there are any?										   *
 *													   *
 * Ex 1-12. Write a program that prints its input one word per line.					   *
 ***********************************************************************************************************/
#include <stdio.h>

#define IN 1
#define OUT 0

main()
{
	int c, state = IN;

	while ((c = getchar()) != '\n') {
		if (c == ' ' || c == '\t') 
			state = OUT;
		else if (state == OUT) {
			state = IN;
			putchar('\n');
		}
		if (state == IN)
			putchar(c);
	}
}