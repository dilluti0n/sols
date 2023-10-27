/* p. 79 Ex 4-10, calculator with getline() */ 

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXOP	100
#define NUMBER '0'
#define VARSET '_'
#define VARGET 'A'
#define VARNUM 26
#define MAXCMDLINE 100
#define BUFSIZE 100
#define MAXVAL	100
#define MAXLINE	100

enum cmds { PRINT = 5000, DUPLICATE, SWAP, CLEAR, SIN, UNKNOWN};

int		getop	(char []);
void	push	(double);
double	pop		(void);
int		get_line(char [], unsigned int);
int 	getcmd	(void);

char 	cmd[MAXCMDLINE];

int 	sp = 0;
double 	val[MAXVAL]; /* stack */

char	variable;
double	var_buff[VARNUM]; /* calculator variable A, B,... */

char	line[MAXLINE];
int		line_i = 0;

int main()
{
	int 		type = 0, varindex = 0;
	double 		op2;
	char 		s[MAXOP];
	
	while (get_line(line, MAXLINE) != 0) {
		line_i = 0;
		while ((type = getop(s)) != '\0') {
		switch (type) {
		/* number */
		case NUMBER:
			push(atof(s));
			break;
			
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
		case '%':
			op2 = pop();
			if (op2 != 0)
				push ((int)pop() % (int) op2);
			else
				printf("error: zero divisor \n");
			break;
			
		/* commands */
		case PRINT:
			if (sp > 0)
				printf("[print] stack head: %.8g\n",val[sp - 1]);
			else
				printf("[print] error: stack empty\n");
			break;
		case DUPLICATE:
			if (sp > 0)
				push(val[sp - 1]);
			else
				printf("[duplicate] error: stack empty\n");
			break;
		case SWAP:
			if (sp > 1) {
				op2 = val[sp - 1];
				val[sp - 1] = val[sp - 2];
				val[sp - 2] = op2;
				printf("[swap] top two elements of stack swaped.\n");
			}
			else
				printf("[swap] error: cannot swap !!\n");	
			break;
		case CLEAR:
			sp = 0;
			printf ("[clear] stack cleared.\n");
			break;
		case UNKNOWN:
			printf("[getcmd] error: unknown command %s\n",cmd);
			break;

		/* maths */
		case '~':
			push (sin(pop()));
			break;
		case 'e':
			push (exp(pop()));
			break;
		case 't':
			push (tan(pop()));
			break;
		case '^':
			op2 = pop();
			push (pow(pop(),op2));
			break;

		/* variable */
		case VARGET:
			push(var_buff[variable - 'A']);
			break;
		case VARSET:
			if (varindex >= VARNUM)
				varindex -= VARNUM;
			var_buff[varindex++] = val[sp - 1];
			printf("[varset] set %c\n",'A' + varindex - 1);
			break;
			
		/* pop out the result */
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("[main] error: unknown command %s\n", s);
			break;
		}
		}
	}
	return 0;
}

void push(double f)
{
	if (sp < MAXVAL)
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

int getop(char s[])
{
	int i = 0, c;

	while ((s[0] = c = line[line_i++]) == ' '|| c == '\t')
		;
	s[1] = '\0';
	
	if (isupper(c)) {
		variable = c;
		return VARGET; /* if supper, get variable from var_buff */
	} if (!isdigit(c) && c != '.' && c != '-' && c != '!')
		return c; /* not a number */
	if (c == '-'){
		int next = line[line_i++];
		if (!isdigit(next) && next != '.') {
			line_i--;
			return c; /* return '-' as an operator */
		} else
			s[++i] = c = next; /* negative number */
	} else if (c == '!') /* command mode */
		return getcmd();

	/* number */
	if (isdigit(c))
		while (isdigit(s[++i] = c = line[line_i++]))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = line[line_i++]))
			;
	s[i] = '\0';
	
	line_i--;
	
	return NUMBER;
}

/*	get string from input buffer until EOF or '\n' called. 
 *	if '\n' is called, include the '\n' into string */
int get_line(char line[], unsigned int max_line_len)
{
	int c, i = 0;
	
	while(i < max_line_len - 2 && (c = getchar()) != EOF && c != '\n')
		line[i++] = c;
	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';
	
	return i;
}

/* command mode */
int getcmd ()
{
	int i = 0, c;

	while ((cmd[i++] = c = line[line_i++]) != '\n' && c != ' ' && c != '\t')
		;
	cmd[--i] = '\0';
	if (!strcmp(cmd, "print"))
		return PRINT;
	else if (!strcmp(cmd, "duplicate"))
		return DUPLICATE;
	else if (!strcmp(cmd, "swap"))
		return SWAP;
	else if (!strcmp(cmd, "clear"))
		return CLEAR;
	return UNKNOWN;
}
