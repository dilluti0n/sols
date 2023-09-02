/* p.20								      *
 * Exercise 1-8. Write a program to count blanks, tabs, and newlines. */

#include <stdio.h>

struct cnt {
	int blanks;
	int tabs;
	int newlines;
};

main()
{
	int c;
	
	struct cnt n = {0,0,0};

	while ((c = getchar()) != EOF) {
		if (c == ' ')
			++n.blanks;
		if (c == '\t')
			++n.tabs;
		if (c == '\n')
			++n.newlines;
	}

	printf ("blanks   %2d\n", n.blanks);
	printf ("tabs     %2d\n", n.tabs);
	printf ("newlines %2d\n", n.newlines);
}