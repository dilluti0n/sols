/* 
 * Ex 5-19. Modify undcl so that it does not add 
 * redundant parentheses to declations.
 */

/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define MAXOUT 1000

enum { NAME, PARENS, BRACKETS };

int  gettoken(void);

int  gettok(void);
void ungettok(int c);

char token[MAXTOKEN];     /* last token string */
char out[MAXOUT];         /* output string */

/* undcl: convert word description to declaration */
main()
{
	int type;
    char temp[MAXTOKEN];

    for (;;) {
        printf(">> "); /* prompt */
        if (gettok() == EOF){
            printf("\n");
            break;
        }
        strcpy(out, token); /* variable name */
        while ((type = gettok()) != '\n')
            if (type == PARENS || type == BRACKETS) {
                strcat(out, token);
            } else if (type == '*' && (type = gettok()) != BRACKETS && type != PARENS) {
                sprintf(temp, "*%s", out);
                strcpy(out, temp);
                ungettok(type);
            } else if (type == BRACKETS || type == PARENS) {
                sprintf(temp, "(*%s)", out);
                strcpy(out, token);
                ungettok(type);
            } else if (type == NAME) { /* type name */
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else {
                fprintf(stderr, "invalid input at %s\n", token);
            }
        printf("%s\n", out);
    }
	return EXIT_SUCCESS;
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
			return PARENS;		/* function */
		} else {
			ungetch(c);
			return '(';         /* ( dcl ) */
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';            /* token = [optional size] */
		return BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';             /* token = name */
		ungetch(c);
		return NAME;
	} else
		return c;  /* '*' or ')' or '\n' expected */
}

/* gettok.c */
int gettok(void);
void ungettok(int c);

#ifndef BUFSIZE
#define BUFSIZE 100
#endif

static int gettok_bp = 0;
static char gettok_buf[BUFSIZE];

int gettok(void)
{
    if (gettok_bp-- > 0)
        switch (gettok_buf[gettok_bp]) {
        case PARENS:
            strcpy(token, "()");
            return PARENS;
            break;
        case BRACKETS:
            strcpy(token, "[]");
            return BRACKETS;
            break;
        } 
    else
        return gettoken();
}

void ungettok(int c)
{
    if (gettok_bp < BUFSIZE)
        gettok_buf[gettok_bp++] = c;
    else
        fprintf(stderr, "ungettok: buffer full.\n");
}

/* getch.c */
#ifndef GETCH_C
#define GETCH_C
#include <stdio.h>

#ifndef BUFSIZE
#define BUFSIZE 100
#endif

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