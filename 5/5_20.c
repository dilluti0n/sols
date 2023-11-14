/* 
 * Ex 5-20. Expand dcl to handle declarations with function argument
 * types, qualifiers like const, and so on.
 */

/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum gettok_type {
	NAME,
	PARENS,
	BRACKETS
};
enum qualifier_type {
	NOT_Q,
	QUAL,
	TYPE,
};
enum mode {
	NONAME_FALSE = 0,
	NONAME_TRUE = 1
};

int isqualifier(char *token);
void assign_datatype(char *datatype);

void dcl(char* out, _Bool mode, char* name);
void dirdcl(_Bool mode, char* name);

int gettoken(void);
int gettok(void);
void ungettok(int type);

void token_reset(void);

char* types[] = {
	"void",
	"char",
	"int",
	"long",
	"float",
	"double",
	"custum_type",
	NULL
};

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
		assign_datatype(datatype);
		out[0] = '\0';
		dcl(out, NONAME_FALSE, name);
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

/* specifiy the qualifier of the delcaror. */
int isqualifier(char *token)
{
	if (!strcmp(token, "const") || !strcmp(token, "static") ||
		!strcmp(token, "extern"))
		return QUAL;
	else for (char** p = types; *p; p++) {
		if (!strcmp(token, *p))
			return TYPE;
	}
	return NOT_Q;
}

void assign_datatype(char* datatype)
{
	datatype[0] = '\0';
	while (gettok() != EOF && tokentype == NAME 
                           && isqualifier(token) != NOT_Q) {
		if (datatype[0] == '\0')
			strcat(datatype, token);
		else {
			strcat(datatype, " ");
			strcat(datatype, token);
		}
	}
	ungettok(tokentype);
}

/* optional *'s direct-dcl */
void dcl(char* out, _Bool mode, char* name)
{
	int ns;
	
	for (ns = 0; gettok() == '*'; )
		ns++;
	dirdcl(mode, name);
	while (ns-- > 0)
		strcat(out, " pointer to");
}

/* name, (dcl), dirdcl(), dirdcl[optional size] */
void dirdcl(_Bool mode, char* name)
{
	int type;
	
	if (tokentype == '(') { /* (dcl) */
		dcl(out, mode, name);
		if (tokentype != ')')
			fprintf(stderr,
				"error: missing closing parenthesis ')' after %s\n", name);
	} else if (tokentype == NAME) { /* name */
		strcpy(name, token);
	} else if (mode == NONAME_FALSE) {
		fprintf(stderr, "error: expected name or (dcl)\n");
		name[0] = '\0';
		return; /* prevent over-call of gettok() by following sentence. */
	} else if (tokentype == ')') { /* from dirdcl(args..), prevent over-call when it ends.*/
		return;
	}
	while ((type = gettok()) == PARENS || type == BRACKETS || type == '(')
		switch (type) {
		case PARENS: /* dirdcl() */
			strcat(out, " function returning");
			break;
		case '(': /* dirdcl(args..)*/
			strcat(out, " function with argument");
			do {
				char buf[100];
				char dtype[100];
				char temp[100];
				char name[MAXTOKEN];
				assign_datatype(dtype);
				buf[0] = '\0';
				dcl(buf, NONAME_TRUE, name);
				sprintf(temp, "%s %s %s,", buf, dtype, name);
				strcat(out, temp);
			} while (tokentype == ',');
			strcat(out, " returning");
			break;
		case BRACKETS: /* dirdcl[optional size] */
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
			break;
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
	} else {
		return tokentype = c;  /* '*' or ')' or '\n' expected */
	}
}

/* gettok.c */
#ifndef BUFSIZE
#define BUFSIZE 100
#endif

static char gt_bp = 0;
static char gp_buf[BUFSIZE];

/* buffered gettoken() */
int gettok(void)
{
	return (gt_bp > 0)? gp_buf[--gt_bp] : gettoken();
}

/* Register type to the gettok() buffer */
void ungettok(int type)
{
	if (gt_bp < BUFSIZE)
		gp_buf[gt_bp++] = type;
	else
		fprintf(stderr, "ungettok: buffer full.\n");
}

/* reset the input and getch() buffer */
void token_reset(void)
{
	do {
		gettoken();
	} while (tokentype != EOF && tokentype != '\n');
}

/* getch.c */
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

/* 
 * personal takeaway from creating this spaghetti: 
 * if you want to "use" a function elsewhere, never use a global variable.
 */
