/*
 * Ex 6-3. Write a cross-referencer that prints a list of all words in a
 * document, and, for each word, a list of the line numbers on which it
 * occurs. Remove noise words like "the", "and", and so on,
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define ARR_SIZE(X) sizeof (X) / sizeof (X[0])

int islinkingword(char *);
int binsearch(char *, char *[], int);

struct tree_node *addtree(struct tree_node *, char * word, int line);
struct list_node *addlist(struct list_node *, int line);
void tree_print(struct tree_node *);
void list_print(struct list_node *);

int getword(char *, int);

struct list_node {
	int line;
	struct list_node *next;
};

struct tree_node {
	char *word;
	struct list_node *list_head;
	struct tree_node *left;
	struct tree_node *right;
};

char *linking_words[] = {
    "And",
    "As",
    "But",
    "For",
    "Like",
    "Nor",
    "Or",
    "So",
    "The",
    "Then",
    "To",
    "Too",
    "Yet",
    "and",
    "as",
    "but",
    "for",
    "like",
    "nor",
    "or",
    "so",
    "the",
    "then",
    "to",
    "too",
    "yet",
};


main()
{
	char word[MAXWORD];
	int line;
	struct tree_node *root = NULL;

	while ((line = getword(word, MAXWORD)) != EOF)
		if (isalpha(word[0]) && !islinkingword(word))
			root = addtree(root, word, line);
	tree_print(root);

	exit(EXIT_SUCCESS);
}

int islinkingword(char *word)
{
	return (binsearch(word, linking_words,
	                  ARR_SIZE(linking_words)) != -1)? 1 : 0;
}

int binsearch(char *word, char *arr[], int n)
{
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if ((cond = strcmp(word, arr[mid])) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

struct tree_node* addtree(struct tree_node* p, char* w, int line)
{
	int cond;

	if (p == NULL) {
		p = (struct tree_node *) malloc(sizeof (struct tree_node));
		p->word = strdup(w);
		p->list_head = addlist(p->list_head, line);
		p->left = NULL;
		p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0) {
		p->list_head = addlist(p->list_head, line);
	} else if (cond < 0) {
		p->left = addtree(p->left, w, line);
	} else {
		p->right = addtree(p->right, w, line);
	}
	return p;
}

struct list_node* addlist(struct list_node* p, int line)
{
	if (p == NULL) {
		p = (struct list_node *) malloc(sizeof (struct list_node));
		p->line = line;
		p->next = NULL;
	} else {
		p->next = addlist(p->next, line);
	}
	return p;
}

void tree_print(struct tree_node *p)
{
	if (p != NULL) {
		tree_print(p->left);
		printf("%s: ", p->word);
		list_print(p->list_head);
		tree_print(p->right);
	}
}

void list_print(struct list_node *p)
{
	if (p != NULL && p->next == NULL) {
		printf("%d", p->line);
		list_print(p->next);
	} else if (p != NULL) {
		printf("%d, ", p->line);
		list_print(p->next);
	} else {
		putchar('\n');
	}
}

int getword(char *word, int lim)
{
	static int line = 1;

	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch())) /* skip space */
		if (c == '\n')
			line++;
	if (c == EOF)
		return c;
	*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return line;
	}
	for (; --lim > 0; w++) {
		if (!isalnum(*w = c = getch())) {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return line;
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