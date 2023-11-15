/*
 * Ex 6-1. Our version of getword() does not properly handle underscores,
 * string constants, comments, or preprocessor control lines. Write a
 * better version.
 */

/* count C keywords */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAXWORD 100

struct key {
	char *word;
	int count;
} keytab[] = {
	{"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"do", 0},
    {"double", 0},
    {"else", 0},
    {"enum", 0},
    {"extern", 0},
    {"float", 0},
    {"for", 0},
    {"goto", 0},
    {"if", 0},
    {"int", 0},
    {"long", 0},
    {"register", 0},
    {"return", 0},
    {"short", 0},
    {"signed", 0},
    {"size_t", 0},
    {"sizeof", 0},
    {"static", 0},
    {"struct", 0},
    {"switch", 0},
    {"typedef", 0},
    {"union", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0},
};

#define NKEYS (sizeof keytab / sizeof keytab[0])

void skipchar(int *c, char start, char end);
int getword(char *word, int lim);
int binsearch(char *word, struct key tab[], int n);

int getch(void);
void ungetch(int c);

main()
{
	int n;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;
	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf ("%4d %s\n", keytab[n].count, keytab[n].word);
	return 0;
}

/* if p == start, skip input buffer to end and p to end + 1*/
void skipchar(int *p, char start, char end)
{
	if (*p == start) {
		while ((*p = getch()) != end && *p != EOF)
			;
		if (*p != EOF)
			*p = getch();
	}
}

int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch())) /* skip space */
		;
	skipchar(&c, '\"', '\"');    /* skip literals */
	skipchar(&c, '\'', '\'');
	if (c == '/') {              /* skip comments */
		if ((c = getch()) == '*') {
			while (c != '/' && c != EOF)
				skipchar(&c, c, '*');
			if (c != EOF)
				c = getch();
		} else {
			ungetch(c);
			c = '/';
		}
	}
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c) && c != '_') {
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++) {
		if (!isalnum(*w = c = getch()) && c != '_') {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
}

int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

/* getch.c */
#define MAXBUF 100

static int bp = 0;
static char buf[MAXBUF];

int getch(void)
{
	return (bp > 0)? buf[--bp] : getchar();
}

void ungetch(int c)
{
	if (bp < MAXBUF)
		buf[bp++] = c;
	else
		fprintf(stderr, "ungetch: buffer full\n");
}