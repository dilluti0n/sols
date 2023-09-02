/* p.36 ****************************************************************************
 * Write a program to determine the ranges of char, short, int, and log variables. *
 ***********************************************************************************/

/* uneffcient way
#include <stdio.h>

int main () {
	char c;
	short s;
	int i;
	long l, m, M;

	M = m = 0;
	for (c = 1; c != 0; c++) {
		if (M < c)
			M = c;
		if (m > c)
			m = c;
	}
	printf ("range of char is %ld ~ %ld\n", m, M);

	M = m = 0;
	for (s = 1; s != 0; s++) {
		if (M < s)
			M = s;
		if (m > s)
			m = s;
	}
	printf ("range of short is %ld ~ %ld\n", m, M);

	M = m = 0;
	for (i = 1; i != 0; i++) {
		if (M < i)
			M = i;
		if (m > i)
			m = i;
	}
	printf ("range of int is %ld ~ %ld\n", m, M);

	M = m = 0;
	for (l = 1; l != 0; l++) {
		if (M < l)
			M = l;
		if (m > l)
			m = l;
	}
	printf ("range of long is %ld ~ %ld\n", m, M);


	return 0;
}
*/

/* efficiant way */
#include <stdio.h>

int main () {
	char c;
	int i;
	short s;
	long l;

	c = (unsigned char) -1 >> 1;
	printf ("range of char is %d ~ %d or %#x ~ %#x \n", ~c, c, ~c, c); 

	i = (unsigned int) -1 >> 1;
	printf ("range of int is %d ~ %d or %#x ~ %#x \n", ~i, i, ~i, i); 

	s = (unsigned short) -1 >> 1;
	printf ("range of short is %d ~ %d or %#x ~ %#x \n", ~s, s, ~s, s);

	l = (unsigned long) -1 >> 1;
	printf ("range of long is %ld ~ %ld or %#lx ~ %#lx \n", ~l, l, ~l, l);

	return 0;
}
 