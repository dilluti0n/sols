#include <stdio.h>

main ()
{
	int cels = 0;
	
	for (; cels <= 300; cels += 20)
		printf ("%3d %4d\n", cels, 9*(cels/5) + 32);
}