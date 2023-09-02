/* p. 24 *************************************************************************************
 * Ex 1-13. Write a program to print a histogram of the lengths of words in its input. It is *
 *          easy to draw the histogram with bars horizontal; a vertical orientation is more  *
 *          challenging.                                                                     *
 *********************************************************************************************/

#include <stdio.h>

#define MAXWORD 20

main()
{
	int nWord[MAXWORD+1];
	int Max, c, tmp, i, j;

	for (i = 0; i <= MAXWORD; i++)
		nWord[i] = 0;
	
	tmp = 0;
	while ((c = getchar()) != '\n') {
		++tmp;
		if (c == ' ' || c == '\t' || c == '\n') {
			nWord[tmp-1] += 1;
			tmp = 0;
			nWord[0] = 0;
		}
	}

	Max = nWord[1];
	for (i = 2; i <= MAXWORD; i++)
		if (Max < nWord[i])
			Max = nWord[i];

	for (i = Max; i > 0; i--) {
		for (j = 1; j <= MAXWORD; j++) {
			if (nWord[j] >= i)
				printf (" ##");
			else
				printf ("   ");
		}
		printf("\n");
	}

	for (j = 1; j <= MAXWORD; j++)
		printf ("%3d", j);
	printf("\n");

}