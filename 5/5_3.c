/* Ex 5-3. Write a pointer version of the function strcat that we showed in chapter 2: strcat(s,t) copies the string t to the end of s. */

#include <stdio.h>

void strcat_p (char* s, char* t)
{
	while (*++s)
		;
	while ((*s++ = *t++))
		;
}

main()
{
	char s[100] = "programming in C";
	strcat_p(s," is fun\n");

	puts(s);
}