/* 4-12. Adapt the ideas of printd to write a recursive version of itoa; that is, convert an integer into a string by calling a recursive routine. */

void itoa(int n, char a[])
{
	static int i = 0;

	if (n == 0)
		return;
	if (n < 0) {
		a[i++] = '-';
		n = -n;
	}
	char temp = n % 10 + '0';
	n /= 10;
	itoa(n, a);
	a[i++] = temp;
}