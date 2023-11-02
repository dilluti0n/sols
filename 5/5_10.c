/* Ex 5-10. Write the program expr, which evaluates a reverse Polish expression from the command line, where each operator or operand is a separate argument. for example, `expr 2 3 4 + *` evaluates 2 * (3 + 4) */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLEN 100
#define MAXVAL 100
#define NUMBER '0'

double stack[MAXVAL];
int sp = 0;

double pop(void);
void push(double);
int getop(char*, char*);

main (int argc, char* argv[])
{
	int c, err = -1;
	double op2;
	char s[MAXLEN];

	while (--argc > 0) {
		err = 0;
		c = getop(*++argv, s);
		switch(c) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			if((op2 = pop()))
				push(pop() / op2);
			else
				printf("error: zero div\n");
			break;
		default:
			printf("error: unknown command %c\n",c);
			err = -1;
			break;
		}
	}
	if (!err)
		printf("%g\n",pop());
	else
		printf("Useage: `expr 2 3 4 + *` evaluates 2 * (3 + 4)\n");
}

int getop (char* av, char* s)
{
	if (!isdigit(*s = *av) && *s != '.')
		return *s; /* not a number */
	while (isdigit(*++s = *++av))
		;
	if (*s == '.') {
		while (isdigit(*s++ = *++av))
			;
		*s-- = '\0';
	} else 
		*s = '\0';
	return NUMBER;
}


void push(double f)
{
	if (sp < MAXVAL)
		stack[sp++] = f;
	else
		printf("[push] error: stack full, cannot push %g\n",f);
}

double pop(void)
{
	if (sp > 0)
		return stack[--sp];
	else {
		printf("[pop] error: stack empty\n");
		return 0.0;
	}
}