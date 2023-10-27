/* Ex 4-1. Write the function strrindex(s,t), which returns the position of the rightmost occurrence of t in s, or -1 if there is none */
#include <string.h>
#include <stdio.h>

int strrindex (char s[], char t[])
{
	int i, j, k;

	for (i = strlen(s) - 1; i >= 0; i--) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}

main()
{
	int strrindex (char s[], char t[]);	

	char s[] = "Write the function which returns the position of the rightmost occurrence of t in s, or -1 if there is none.";
	char t[] = "the";

	printf("%i\n",strrindex (s,t));
}

