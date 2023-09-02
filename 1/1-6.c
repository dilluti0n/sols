/* p. 17  							    *
 * Exercise 1-6. Verify that expression getchar() != EOF is 0 or 1. */

#include <stdio.h>

main()
{
	int c;

	c = (getchar() != EOF);
	printf ("%d", c);
	printf("\n");
}