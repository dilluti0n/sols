/* p. 49 */

/* Ex 2-6. write a fucntion that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged. */
unsigned setbits (unsigned x, int p, int n, int y)
{
	y &= ~(-1 << n);             /* set all but the right n bits of y zero. */
	y <<= p - 1;                 /* the rigit n bits of y become position p to p + n - 1. other bits of y are zero. */
	x &= ~(~(-1 << n) << p - 1); /* set all position p to p + n - 1 bits to zero. */
	return x ^ y;
	
}

/* Ex 2-7. Write a function that returns x with the n bits that begin at position p inverted (i.e. 1 changed into 0 and vice versa), leaving the others unchanged. */
unsigned invert (unsigned x, int p, int n)
{
	return x ^ ~(-1 << n) << p - 1;
}

/* Ex 2-8. Write a function that returns the value of the integer x rotated to the right by n bit positions */
int rightrot (unsigned x, int n)
{
	return (x << n >> n >> n) ^ (x & ~(-1 << n) << sizeof(int) * 8 - n);
	
}