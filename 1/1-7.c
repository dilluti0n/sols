/* p. 17  						   *
 * Exercise 1-7. Write a program to print the value of EOF */

#include <stdio.h>

main()
{
	putchar(EOF);
	printf ("\n%u", sizeof(EOF));
	printf ("\n%#x\n",EOF);
	printf ("%d\n",EOF);
	printf ("%u\n",EOF);

	printf ("EOF is %u-byte reserved word of %d(signed), %u or %#x(unsigned) \n", sizeof(EOF),EOF,EOF,EOF);
	
}

/* EOF is 4-byte reserved word of -1(signed), 4294967295 or 0xffffffff(unsigned) */