#include <stdio.h>

main ()
{
	float fahr, celsius;
	const short lower = 0, upper = 300, step = 20;

	fahr = lower;
	printf ("-----------\nFahrenheit-Celsius table\n-----------\n");
	printf ("Fahr   Cels\n");
	while (fahr <= upper) {
		celsius = (5.0/9.0) * (fahr-32.0);
		printf ("%4.0f %6.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
}