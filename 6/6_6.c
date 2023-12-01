/*
 * Ex 6-6. Implement a simple version of the #define processor (i.e., no
 * arguments) suitable for use with C programs, based on the routines of
 * this section. You may also find getch and ungetch helpful.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HASHSIZE 101
#define MAXWORD 100

struct nlist {
	char *name; /* defined name */
	char *defn; /* replacement text */
	struct nlist *next;
};

enum syntax {
	DEFINE = 500,
	UNKNOWN,	
}; /* preprocessor syntax */

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

int preprocess(char *syntax, int lim);
enum syntax syn_switcher_for_preprocess(char *syntax);
int load_define_macro(void);
int get_words_for_define_macro(char *name, char *defn, int lim);
struct nlist *install(char *name, char *defn);
struct nlist *lookup(char *s);
unsigned hash(char *s);
void print_table(void);
void print_list(struct nlist *p);
int undef(char *name);

int getword(char *word, int lim);
int getch(void);
void ungetch(int);

main()
{
	char syntax[MAXWORD];
	int c;

	while ((c = getword(syntax, MAXWORD)) != EOF)
		if (c == '#' && preprocess() < 0)
			return EXIT_FAILURE;
	print_table();
	return EXIT_SUCCESS;
}

/* preprocessing unit */
int preprocess(void)
{
	int err = 0;
	char syntax[MAXWORD];
	
	getword(syntax, MAXWORD);
	switch (syn_switcher_for_preprocess(syntax)) {
	case DEFINE:
		err = load_define_macro();
		break;
	case UNKNOWN:
		fprintf(stderr, "%s: unknown prefix \"%s\".\n",__func__, syntax);
		break;
	}
	return err;
}

/* syantax switcher for preprocess */
enum syntax syn_switcher_for_preprocess(char *syntax)
{
	if (!strcmp(syntax, "define"))
		return DEFINE;
	return UNKNOWN;
} /* use binary search instead of this when list of syntax is large */

/* get define macro (name, defn) from input stream and load to hashed list */
int load_define_macro(void)
{
	char name[MAXWORD], defn[MAXWORD];
	int err;

	err = get_words_for_define_macro(name, defn, MAXWORD);
	if (err >= 0 && install(name, defn) == NULL)
		err = -1;
	return err;
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) { /* not found */
		np = (struct nlist *) malloc(sizeof (*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			goto install_err;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np; /* insert np to head of list */
	} else { /* found */
		free((void *) np->defn); /* free previous defn */
	}
	if ((np->defn = strdup(defn)) == NULL)
		goto install_err;
	return np;
install_err:
	fprintf(stderr, "%s: allocation failed for name: %s\n", __func__, name);
	return NULL;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (!strcmp(s, np->name))
			return np; /* found */
	return NULL; /* not found */
}

/* undef: remove node named (s) from table. return negative if failed. */
int undef(char *s)
{
	struct nlist *node = hashtab[hash(s)];
	struct nlist *prev = NULL;

	for (; node != NULL; prev = node, node = node->next)
		if (!strcmp(node->name, s)) {
			if (prev != NULL)
				prev->next = node->next;
			else
				hashtab[hash(s)] = node->next;
			free(node->name);
			free(node->defn);
			free(node);
			return 0;
		}
	return -1;
}

/* hash: form hash for string s */
unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* print_table: print all stored word & defn on hashtab */
void print_table(void)
{
	struct nlist **p;
	for (p = hashtab; p - hashtab < HASHSIZE; p++)
		print_list(*p);
}

void print_list(struct nlist *p)
{
	for (; p != NULL; p = p->next)
		printf("%s: %s\n", p->name, p->defn);
}

int get_words_for_define_macro(char *name, char *defn, int lim)
{
	int c;
	char *w;

	w = name; /* get name */
	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	for (; w - name < lim; w++)
		if (isspace(*w = c = getch())) {
			ungetch(c);
			break;
		}
	if (w - name >= lim) {
		fprintf(stderr, "%s: too long macro name\n", __func__);
		return -1;
	}
	*w = '\0'; /* name */
	w = defn; /* get defn */
	while (isblank(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	for (; w - defn < lim; w++)
		if ((*w = c = getch()) == '\n') {
			ungetch(c);
			break;
		}
	if (w - defn >= lim) {
		fprintf(stderr, "%s: too long defn for name: %s\n", __func__, name);
		return -1;
	}
	*w = '\0'; /* defn */
	return 0;
}

/* getword: get toknized word from input buffer */
int getword(char *word, int lim)
{
	int c;
	char *w = word;

	while (isblank(c = getch()))
		;
	if (c == '\"') { /* skip literals with " */
		while ((c = getch()) != '\"' && c != EOF)
			if (c == '\\')
				getch();
		c = getch();
	}
	if (c == '\'') { /* skip literals with ' */
		while ((c = getch()) != '\'' && c != EOF)
			if (c == '\\')
				getch();
		c = getch();
	}
	if (c == '/') { /* skip comments */
		if ((c = getch()) == '*') {
			while ((c = getch()) != EOF)
				if (c == '*') {
					if ((c = getch()) == '/')
						break;
					else
						ungetch(c);
				}
			if (c != EOF)
				c = getch();
		} else {
			ungetch(c);
			c = '/';
		}
	}
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++) {
		if (!isalpha(*w = c = getch())) {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
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
