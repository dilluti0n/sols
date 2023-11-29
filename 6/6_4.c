/*
 * Ex 6-4. Write a program that prints the distinct words in its 
 * input sorted into decreasing order of frequency of occurrence.
 * Precede each word by its count.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 100

struct lnode {
	char *word;
	int count;
	struct lnode *next;
};

struct tnode {
	int count;
	char *word;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *sort_by_count(struct tnode *, struct lnode *);
struct lnode *addlist(struct lnode *, char *);
void treeprint(struct tnode *);

int getword(char *word, int lim);

main()
{
	char word[MAXWORD];
	struct lnode *head = NULL;
	struct tnode *root = NULL;

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) && (head = addlist(head, word)) == NULL) {
			fprintf(stderr, "addlist: malloc failed\n");
			exit(EXIT_FAILURE);
		}

	struct lnode *node = head;
	while (node != NULL) {
		if ((root = sort_by_count(root, node)) == NULL) {
			fprintf(stderr, "sort_by_count: malloc failed\n");
			exit(EXIT_FAILURE);
		}
		node = node->next;
	}
	treeprint(root);
	exit(EXIT_SUCCESS);
}

struct tnode *sort_by_count(struct tnode *p, struct lnode *node)
{
	if (p == NULL) {
		p = (struct tnode *) malloc(sizeof (struct tnode));
		p->word = node->word;
		p->count = node->count;
	} else if (node->count <= p->count) {
		p->left = sort_by_count(p->left, node);
	} else {
		p->right = sort_by_count(p->right, node);
	}
	return p;
}

struct lnode *addlist(struct lnode *p, char *w)
{
	if (p == NULL) {
		p = (struct lnode *) malloc(sizeof (struct lnode));
		p->word = strdup(w);
		p->count = 1;
		p->next = NULL;
	} else if (!strcmp(p->word, w)) {
		(p->count)++;
	} else {
		p->next = addlist(p->next, w);
	}
	return p;
}

void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->right);
		printf("%d %s\n", p->count, p->word);
		treeprint(p->left);
	}
}

int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++) {
		if (!isalnum(*w = c = getch())) {
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