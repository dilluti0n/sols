#include <stdio.h>
#define swap(t,x,y)\
{				\
	t temp;		\
	temp = x;		\
	x = y;		\
	y = temp;		\
};



main()
{
	int x = 3, y = 4;
	swap (int, x, y);
	printf("x %d, y %d\n",x,y);
}