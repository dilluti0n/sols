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

char token[MAXTOKEN];     /* last token string */
char out[MAXOUT];         /* output string */

/* undcl: convert word description to declaration */
main()
{
	int type;
    char temp[MAXTOKEN];

    for (;;) {
        printf(">> "); /* prompt */
        if (gettoken() == EOF){
            printf("\n");
            break;
        }
        strcpy(out, token); /* variable name */
        while ((type = gettoken()) != '\n')
            if (type == PARENS || type == BRACKETS) {
                if (out[0] == '*') { /* pointer to function or array */
                    sprintf(temp, "(%s)", out);
                    strcpy(out, temp);
                }
                strcat(out, token);
            } else if (type == '*') {
                sprintf(temp, "*%s", out);
                strcpy(out, temp);
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