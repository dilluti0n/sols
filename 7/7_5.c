/*
 * Ex 7-5. Rewrite the postfix calculator of Chapter 4 to use
 * scanf and/or sscanf to do the input and number conversion.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXLINE	100
#define MAXSTACK 100

int		getop	(char *);
void	push	(double);
double	pop		(void);

int 	sp = 0; /* stack pointer */
double 	val[MAXSTACK]; /* stack */

int main()
{
	int         varindex = 0;
	double 		op2;
	char 		str[MAXLINE], c;

	while (scanf("%s", str) != EOF) {
		if (sscanf(str, "%lf", &op2))
			push(op2);
		if (sscanf(str, "%c", &c) && !isnumber(c) && c != '.')
			switch (c) {
			/* operators */
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
				op2 = pop();
				if (op2 != 0.0)
					push (pop() / op2);
				else
					printf("error: zero divisor \n");
				break;
			default:
				fprintf(stderr, "[%s] error: unknown command %c\n", __func__, c);
				break;
			}
	}
	printf("\t%.8g\n", pop());
	return 0;
}

void push(double f)
{
	if (sp < MAXSTACK)
		val[sp++] = f;
	else
		printf("[push] error: stack full, cannot push %g\n",f);
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("[pop] error: stack empty\n");
		return 0.0;
	}
}