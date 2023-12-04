/*
 * Ex 7-3. Revise minprintf to handle more of the other facil-
 * ities of printf.
 */
#include <stdarg.h>
#include <stdio.h>

void minprintf(char *fmt, ...);

int main()
{
	minprintf("%u\n", -1);
}

void minprintf(char *fmt, ...)
{
	va_list ap; /* points to each unnamed arg in turn */
	char *p;
	union {
		int ival;
		unsigned uval;
		double dval;
		char *sval;
	} u;

	va_start(ap, fmt); /* make ap point to 1st unnmaed arg */
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		switch (*++p) {
		case 'd':
			u.ival = va_arg(ap, int);
			printf("%d", u.ival);
			break;
		case 'o':
			u.uval = va_arg(ap, unsigned);
			printf("%o", u.uval);
			break;
		case 'X':
		case 'x':
			u.uval = va_arg(ap, unsigned);
			printf("%x", u.uval);
			break;
		case 'u':
			u.uval = va_arg(ap, unsigned);
			printf("%u", u.uval);
			break;
		case 'f':
			u.dval = va_arg(ap, double);
			printf("%f", u.dval);
			break;
		case 's':
			for (u.sval = va_arg(ap, char *); *u.sval; u.sval++)
				putchar(*u.sval);
			break;
		case 'c':
			u.ival = va_arg(ap, int);
			putchar(u.ival);
			break;
		default:
			putchar(*p);
			break;
		}
	}
va_end(ap); /* clean up */
} /* end of function minprintf */