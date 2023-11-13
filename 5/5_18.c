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
		dcl ();
		if (tokentype == '\n') {
			printf("%s: %s %s\n", name, out, datatype);
		} else if (tokentype == NAME) {
			fprintf(stderr, "Syntax error: unexpected input %s\n", token);
			token_reset();
		} else {
			fprintf(stderr, "Syntax error: unexpected input %c\n", tokentype);
			token_reset();
		}
	}
	return 0;
}

/* optional *'s direct-dcl */
void dcl(void)
{
	int ns;
	
	for (ns = 0; gettoken() == '*'; )
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat (out, " pointer to");
}

/* name, (dcl), dirdcl(), dirdcl[optional size] */
void dirdcl(void)
{
	int type;
	
	if (tokentype == '(') {      /* ( dcl ) */
		dcl();
		if (tokentype != ')')
			printf("error: missing )\n");
	} else if (tokentype == NAME) {
		strcpy(name, token);
	} else {
		fprintf(stderr, "error: expected name or (dcl)\n");
		return;
	}
	while ((type = gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS) {
			strcat(out, " function returning");
		} else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

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
		ungetch (c);
		return tokentype = NAME;
	} else
		return tokentype = c;  /* '*' or ')' or '\n' expected */
}

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

static int bp = 0;
static char buf[BUFSIZE];

int getch (void)
{
	return (bp > 0) ? buf[--bp] : getchar();
}

void ungetch (int c)
{
	if (bp < BUFSIZE)
		buf[bp++] = c;
	else
		fprintf(stderr, "ungetch: buffer full.\n");
}
#endif