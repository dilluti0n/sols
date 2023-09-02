#include <stdio.h>

main()
{
	int fahr = 300;
	for (; fahr >= 0; fahr -= 20)
		printf ("%3d %6.1f\n", fahr, (5.0/9.0) * (fahr - 32));
}