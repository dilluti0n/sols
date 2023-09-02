/* p. 51 */

/* Ex. 2-9. In a two's complement number system, x &= (x - 1) deletes the rightmost 1-bit in x. explain why. Use this observation to write a faster version of bitcount */
int bitcount (unsigned x)
{
	int b;
	for (b = 0; x != 0; x &= (x - 1))
		b++;
}

/* for x = 0000 0010 0011 0000, x - 1 = 0000 0010 0010 1111, x & (x - 1) = 0000 0010 0010 0000. */