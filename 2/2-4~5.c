/* p.48 */

/****************************************************************
 * Ex 2-4. Write an squeeze (s1,s2) that deletes each character *
 *         in s1 that matches any character in the stirg s2     *
 ****************************************************************/
void mySqueeze (char s1[], const char s2[])
{
	int i, j, k;
	for (k = 0; s2[k] != '\0'; k++) {
		for (i = j = 0; s1[i] != '\0'; i++)
			if (s1[i] != s2[k])
				s1[j++] = s1[i];
		s1[j] = '\0';
	}
}

/******************************************************************
 * Ex 2-5. Write the function any(s1,s2), which retuns the first  *
 *         location in the string s1 where any character from the *
 *         string s2 occurs, or -1 if s1 contains from s2         *
 ******************************************************************/
int any (const char s1[], const char s2[])
{
	_Bool state = 1;
	int cnt = 0, res = -1;
	char buffer[100];

	for (int k = 0; s2[k] != '\0'; k++) {
		for (int i = 0; s1[i] != '\0'; i++)
			if (s2[k] == s1[i]) {
				if (state) {
					state = 0;
					res = i;
				}
				cnt ++;
			}
		if (s2[k + 1] == '\0' && cnt == k + 1)
			return -1;
	}
	return res + 1;
}