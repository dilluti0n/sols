/* 3-3. Write a function expand(s1, s2) that expands shorthanded notations like a-z in the string s1 into the complete list abc...xyz in s2. */

#include <stdio.h>

void expand (char s1[], char s2[])
{
	int i, j = 0;
	char c;

	for (i = 0; s1[i] != '\0'; i++) {
		if (s1[i] == '-' && i > 0 && s1[i+1] != '\0' && s1[i-1] < s1[i+1]) {
			c = s1[i-1];
			while (++c != s1[i+1])
				s2[j++] = c;
		} else if (s1[i] == '-') {
			i++;
			s2[j++] = s1[i];
		} else
			s2[j++] = s1[i];	
	}
	s2[j] = '\0';
}
