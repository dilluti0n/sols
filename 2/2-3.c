/* p. 46 ****************************************************************************
 * Ex 2-3. Write a function htoi (s), which converts a string of hexadecimal digits *
 *         (including an optional 0x or 0X) into its equivalent integer value.       *
 ************************************************************************************/

#include <math.h>
#include <string.h>
#include <stdio.h>

int htoi (char* s) {
	int cnt, res;
	_Bool a, b, c;
	
	res = 0;
	int len = strlen(s);
	cnt = len - 1;
	for (; *s; s++, cnt--) {
		if (cnt == len - 1 && *s == '0' && (*(s + 1) == 'x' || *(s + 1) == 'X')) {
			s += 2;
			cnt -= 2;
		}

		a = *s >= '0' && *s <= '9';
		b = *s >= 'A' && *s <= 'F';
		c = *s >= 'a' && *s <= 'f';

		if ( !(a || b || c) )
			return -1;
		if ( a )
			res += (*s - '0') * pow (16, cnt);
		else if ( b )
			res += ((*s - 'A') + 10) * pow (16, cnt);
		else if ( c )
			res += ((*s - 'a') + 10) * pow (16, cnt);
	}
	return res;
}

int main () {
	char s[100];

	scanf ("%s", s);
	printf ("%s (16) = %d (10)\n", s, htoi(s));

	return 0;
}