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
	struct lnode *list_node;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *sort_by_count(struct tnode *, struct lnode *);
struct lnode *addlist(struct lnode *, char *);
void tree_print_and_free(struct tnode *);

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
	tree_print_and_free(root);
	exit(EXIT_SUCCESS);
}

struct tnode *sort_by_count(struct tnode *p, struct lnode *node)
{
	if (p == NULL) {
		p = (struct tnode *) malloc(sizeof (struct tnode));
		p->list_node = node;
	} else if (node->count <= p->list_node->count) {
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

void tree_print_and_free(struct tnode *p)
{
	if (p != NULL) {
		tree_print_and_free(p->right);
		printf("%d %s\n", p->list_node->count, p->list_node->word);
		free(p->list_node->word);
		free(p->list_node);
		tree_print_and_free(p->left);
		free(p);
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