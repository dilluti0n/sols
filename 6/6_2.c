#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

#define MAXWORD 100
#define MAX_W_BUF 100
#define MAX_L_BUF 100

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

int get_w(char*, int);
void ungetw(char*);

int getch(void);
void ungetch(int c);

struct tnode *talloc(void);

/* word frequency count */
main()
{
	struct tnode *root = NULL;
	char word[MAXWORD], buf[MAXWORD];

	while (get_w(word, MAXWORD) != EOF)
		if (isalpha(word[0])) {
			if (get_w(buf, MAXWORD) != '(')
				root = addtree(root, word);
			ungetw(buf);
		}
	treeprint(root);
}

/* add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) { /* at p (new word) */
		p = talloc();
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0) {
		p->count++; /* repeated word */
	} else if (cond < 0) { /* less than into left subtree */
		p->left = addtree(p->left, w);
	} else { /* greater than into left subtree */
		p->right = addtree(p->right, w);
	}
	return p;
}

/* in-order print of tree p */
void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

/* get word from input */
int getword(char *word, int lim)
{
	int c;
	char *w = word;

	while(isspace(c = getch()))
		;
	while (c == '#') { /* skip preprocessors */
		while ((c = getch()) != '\n' && c != EOF)
			;
		c = getch();
	}
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
	if (!isalpha(c) && c != '_') {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch()) && *w != '_') {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

static int w_bp = 0;
static char *w_buf[MAX_W_BUF];

/* buffered getword */
int get_w(char *word, int lim)
{
	if (w_bp > 0) {
		strcpy(word, w_buf[--w_bp]);
		free(w_buf[w_bp]);
		w_buf[w_bp] = NULL;
		return word[0];
	}
	return getword(word, lim);		
}

/* store word to w_buf */
void ungetw(char *word)
{
	if (w_bp < MAX_W_BUF)
		w_buf[w_bp++] = strdup(word);
	else
		fprintf(stderr, "ungetw: buffer full\n");
}

/* make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

static char buf[MAX_L_BUF];
static int bp = 0;

int getch(void)
{
	return (bp > 0)? buf[--bp] : getchar();
}

void ungetch(int c)
{
	if (bp < MAX_L_BUF)
		buf[bp++] = c;
	else
		fprintf(stderr, "ungetch: buffer full\n");
}