/* write a recursive version of the function reverse(s), which reverses the string s in place. */
#include <stdio.h>
#include <string.h>

void reverse (char s[])
{
	static int i = 0;
	int len = strlen(s);
	int tmp;

	if (2*(i+1) > len)
		return;

	tmp = s[len - i - 1];
	s[len - i - 1] = s[i];
	s[i++] = tmp;

	reverse(s);
}