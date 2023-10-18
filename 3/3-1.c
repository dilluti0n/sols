/* p. 58 */

/* Ex 3-1. Our binary serch makes two tests inside the loop, when one would suffice (at the price of more test outside). Write a version with only one test inside the loop and measure the difference in run-time. */
#include <stdio.h>
#include <time.h>

#define TEST 10000

int binsearch (int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	if (x == v[low - 1])
		return low - 1;
	else
		return -1;
}

int binsearch_kr (int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

void initVector (int v[], int n)
{
	for (int i = 0; i < n; i++)
		v[i] = i;
}

int main ()
{
	int v[TEST], b, b_kr;
	long start, bb, bb_kr;
	double avg = 0;
	initVector (v, TEST);

	for (int i = 0; i < TEST; i++) {
		start = clock();
		b = binsearch(i, v, TEST);
		bb = clock() - start;
		b_kr = binsearch_kr(i, v, TEST);
		bb_kr = clock() - bb;
		avg += (bb_kr - bb);
		printf ("%i test: b = %i (%.3f ms), b_kr = %i (%.3f ms)\n", i, b, (double) bb/1000, b_kr, (double) bb_kr/1000);
	}
	printf ("avg of diff = %.3f ms\n", avg/(TEST*1000));
	return 0;
}
	
