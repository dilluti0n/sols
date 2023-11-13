/* 
 * Ex 5-18. make dcl recover from input errors.
 */

/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int  gettoken(void);

void token_reset(void);

int  tokentype;           /* type of last token */
char token[MAXTOKEN];     /* last token string */
char name[MAXTOKEN];      /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int ect. */
char out[1000];           /* output string */

/* dcl: convert declaration to words */
main()
{
	for (;;) {
		printf(">> ");   /* prompt */
		if (gettoken () == EOF) {
			printf("\n");
			break;
		}
		strcpy(datatype, token);
		out[0] = '\0';
		dcl();
		if (tokentype == '\n') {
			printf("\t%s: %s %s\n", name, out, datatype);
		} else if (tokentype == NAME) {
			fprintf(stderr, "Syntax error: unexpected input %s\n", token);
			token_reset();
		} else {
			fprintf(stderr, "Syntax error: unexpected input %c\n", tokentype);
			token_reset();
		}
	}
	return EXIT_SUCCESS;
}

/* optional *'s direct-dcl */
void dcl(void)
{
	int ns;
	
	for (ns = 0; gettoken() == '*'; )
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

/* name, (dcl), dirdcl(), dirdcl[optional size] */
void dirdcl(void)
{
	int type;
	
	if (tokentype == '(') {                    /* ( dcl ) */
		dcl();
		if (tokentype != ')')
			fprintf(stderr, "error: missing closing parenthesis ')' after %s\n", name);
	} else if (tokentype == NAME) {            /* name */
		strcpy(name, token);
	} else {
		fprintf(stderr, "error: expected name or (dcl)\n");
		name[0] = '\0';
		return; /* prevent over-call of gettoken() by following sentence. */
	}
	while ((type = gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS) {                  /* dirdcl() */
			strcat(out, " function returning");
		} else {                               /* dirdcl[optional size] */
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

/* 
 * get token from stdin. Each token is distinguished by 
 * (), (, [opt], variable name, or any other char.
 */
int gettoken(void)
{
	int c, getch(void);
	void ungetch(int);
	char *p = token;
	
	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;		/* function */
		} else {
			ungetch(c);
			return tokentype = '(';         /* ( dcl ) */
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';            /* token = [optional size] */
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';             /* token = name */
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;  /* '*' or ')' or '\n' expected */
}

/* reset the input and getch() buffer */
void token_reset(void)
{
	do {
		gettoken();
	} while (tokentype != EOF && tokentype != '\n');
}

/* getch.c */
#ifndef GETCH_C
#define GETCH_C
#include <stdio.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int c);

static int bp = 0;
static char buf[BUFSIZE];

/* buffered getchar() */
int getch(void)
{
	return (bp > 0) ? buf[--bp] : getchar();
}

/* Register c in the getch() buffer. */
void ungetch(int c)
{
	if (bp < BUFSIZE)
		buf[bp++] = c;
	else
		fprintf(stderr, "ungetch: buffer full.\n");
}
#endif