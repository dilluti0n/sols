/* Ex 5-4. Write the function strend(s,t), which retunrs 1 if the stirng t occurs at the end of the string s, and zero otherwise. */
#include <stdio.h>

int strend(char* s, char* t)
{
	const char* tmp = t;

	while (*++s)
		;
	while (*++t)
		;
	while (*--s == *--t && t > tmp)
		;
	if (*s == *t)
		return 1;
	return 0;
}

main()
{
	char s[100] ="write the function", t[10] = " function", r[10] = "functio";
	printf("strend(s,t)=%d\nstrend(s,r)=%d\n",strend(s,t),strend(s,r));
} 