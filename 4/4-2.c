/* Ex 4-2. Extend atof to handle scientific notation of the form 123.45e-6 where a floating-point number may be followed by e or E and an optionally signed exponent. */

#include <ctype.h>
#include <stdio.h>

double atof (char s[])
{
	int 		i, sign, tmp;
	double 	val, power;

	for (i = 0; isspace(s[i]); i++)
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] -'0');
		power *= 10.0;
	}
	val = sign * val / power;

	if (s[i] == 'e' || s[i] == 'E')
		i++;
	sign = (s[i] =='-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (tmp = 0; isdigit(s[i]); i++)
		tmp = 10 * tmp + (s[i] - '0');
	for (power = 1.0; tmp > 0; tmp--)
		power *= 10.0;

	return (sign > 0) ? val * power : val / power;
}

main()
{
	double atof (char []);
	char a[100];

	scanf ("%s",a);
	printf ("%f\n",atof(a));
}