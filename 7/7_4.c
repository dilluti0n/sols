/*
 * Ex 7-4. Write a private version of scanf analogous to minprintf
 * from the previous version.
 */
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXDIGIT 100

enum base {
	OCT = 8,
	DEC = 10,
	HEX = 16,
};

void minscanf(char *fmt, ...);
void skip_space(FILE *file);
long input_int(FILE *file, enum base n);
double input_double(FILE *file);

main()
{
	int x, y = 0;
	double d = 0.0;
	char c[100];
	minscanf("%d", &x);
	minscanf("%s", c);
	minscanf("  a  %f", &d);
	minscanf("a%d", &y); 
	/* input "1 abc a12a12" to test */
	printf("%d %s %f %d\n", x, c, d, y);
	/* out must be "1 abc12 12.000000 12" */
}

void minscanf(char *fmt, ...)
{
	va_list ap;
	char *p;
	union pointer {
		int *iptr;
		double *dptr;
		char *cptr;
	} arg;
	int c;

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (isspace(*p)) {
			skip_space(stdin);
			continue;
		}
		if (*p != '%') {
			if (*p == getc(stdin))
				continue;
			else
				break;
		}
		switch(*++p) {
		case 'i':
		case 'd':
			arg.iptr = va_arg(ap, int *);
			skip_space(stdin);
			*arg.iptr = input_int(stdin, DEC);
			break;
		case 'X':
		case 'x':
			arg.iptr = va_arg(ap, int *);
			skip_space(stdin);
			*arg.iptr = input_int(stdin, HEX);
			break;
		case 'o':
			arg.iptr = va_arg(ap, int *);
			skip_space(stdin);
			*arg.iptr = input_int(stdin, OCT);
			break;
		case 'f':
			arg.dptr = va_arg(ap, double *);
			skip_space(stdin);
			*arg.dptr = input_double(stdin);
			break;
		case 'c': /* dont skip leading whitespaces */
			arg.cptr = va_arg(ap, char *);
			*arg.cptr = getc(stdin);
			break;
		case 's':
			arg.cptr = va_arg(ap, char *);
			skip_space(stdin);
			while (!isspace(c = getc(stdin)) && c != EOF)
				*arg.cptr++ = c;
			*arg.cptr = '\0';
			ungetc(c, stdin);
			break;
		default:
			fprintf(stderr, "%s: unknown format %c\n", __func__, *p);
			break;
		}
	}
	va_end(ap);
}

void skip_space(FILE *file)
{
	int c;

	while (isspace(c = getc(file)) && c != EOF)
		;
	if (c != EOF)
		ungetc(c, file);
}

long input_int(FILE *file, enum base n)
{
	int c;
	char out[MAXDIGIT];
	char *p = out;
	int (*is_num)(int);

	switch (n) {
	case OCT:
	case DEC:
		is_num = &isnumber;
		break;
	case HEX:
		is_num = &ishexnumber;
		break;
	}
	while ((*is_num)(c = getc(file)) && p - out < MAXDIGIT - 1
	                                 && c != EOF)
		*p++ = c;
	*p = '\0';
	ungetc(c, file);
	return strtol(out, NULL, n);
}

double input_double(FILE *file)
{
	int c, cnt;
	char out[MAXDIGIT];
	char *p = out;

	cnt = 0;
	while ((isnumber(c = getc(file)) || c == '.') && p - out < MAXDIGIT - 1 
	                                              && cnt < 2
	                                              && c != EOF) {
		*p++ = c;
		if (c == '.')
			cnt++;
	}
	*p = '\0';
	ungetc(c, file);
	return atof(out);
}