/*
 * Ex 6-2. Write a program that reads a C program and prints in alphabeti-
 * cal order each group of variable names that are identical in the first
 * 6-characters, but different somewhere thereafter. Don't count words wi-
 * thin strings and comments. Make 6 a parameter that can be set from the
 * command line.
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAX_W_BUF 100
#define MAX_L_BUF 100
#define DEFAULT_INIT_CHAR 6
#define NR_OF_TYPES sizeof(data_types) / sizeof(data_types[0])

struct lower_node {
	char *word;
	struct lower_node *left;
	struct lower_node *right;
};

struct upper_node {
	struct lower_node *group_root;
	struct upper_node *left;
	struct upper_node *right;
};

char *data_types[] = {
    "char",
    "double",
    "float",
    "int",
    "long",
    "short",
    "void",
}; /* should be ordered lexiographically */

enum state {
	NOT_VAR = 0,
	VAR = 1,
};

int parse_arg_list(int argc, char **argv);
struct upper_node *var_classify_and_load(char *, struct upper_node *, int);

int isdtype(char *word);
int binsearch(char *, char *[], int);

struct upper_node *add_upper_tree(struct upper_node*, char*, int);
struct lower_node *add_lower_tree(struct lower_node *, char *);
void print_upper_tree(struct upper_node *);
void print_lower_tree(struct lower_node *);
struct lower_node *talloc(void);

int getword(char *, int);
int get_w(char*, int);
void ungetw(char*);
int getch(void);
void ungetch(int c);

/* word frequency count */
int main(int argc, char **argv)
{
	int init_char = DEFAULT_INIT_CHAR; 
	/* number of same initial char of vars to group_root */

	struct upper_node *root = NULL;
	char word[MAXWORD];

	if ((init_char = parse_arg_list(argc, argv)) <= 0) {
		fprintf(stderr, "err: invalid argument(s).\n");
		fprintf(stderr, "useage: var_group [positive number]\n");
		return EXIT_FAILURE;
	}

	while (get_w(word, MAXWORD) != EOF)
		root = var_classify_and_load(word, root, init_char);
	print_upper_tree(root);
	return EXIT_SUCCESS;
}

int parse_arg_list(int argc, char **argv)
{
	if (argc == 1)
		return DEFAULT_INIT_CHAR;
	if (argc == 2)
		return atoi(argv[1]);
	return 0;
}

/* load word to tree(root) if it is var */
struct upper_node *var_classify_and_load(char *word, struct upper_node *root,
                                                              int init_char)
{
	int	state; /* VAR or NOT_VAR (see enum state) */
	char buf[MAXWORD];

	state = NOT_VAR;
	while (isdtype(word)) {
		get_w(word, MAXWORD);
		state = VAR;
	}
	if (!strcmp(word, "struct")) {
		get_w(word, MAXWORD); /* struct name */
		get_w(word, MAXWORD); /* var name (or '*') */
		state = VAR;
	}
	while (word[0] == '*' && state == VAR) /* pointer */
		get_w(word,MAXWORD);
	if ((isalpha(word[0]) || word[0] == '_')
			&& get_w(buf, MAXWORD) != '(' && state == VAR) { /* exclude function */
		ungetw(buf);
		return add_upper_tree(root, word, init_char);
	}
	return root;
}

int isdtype(char *word)
{
	return (binsearch(word, data_types, NR_OF_TYPES) != -1)? 1 : 0;
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

struct upper_node *add_upper_tree(struct upper_node *p, char *w, int init_char)
{
	int cond;

	if (p == NULL) { /* root */
		p = (struct upper_node *) malloc(sizeof(struct upper_node));
		p->group_root = add_lower_tree(p->group_root, w);
		p->left = p->right = NULL;
	} else if ((cond = strncmp(p->group_root->word, w, init_char)) == 0) {
		p->group_root = add_lower_tree(p->group_root, w);
	} else if (cond > 0) {
		p->left = add_upper_tree(p->left, w, init_char);
	} else {
		p->right = add_upper_tree(p->right, w, init_char);
	}
	return p;
}

/* add a node with w, at or below p */
struct lower_node *add_lower_tree(struct lower_node *p, char *w)
{
	int cond;

	if (p == NULL) { /* at p (new word) */
		p = talloc();
		p->word = strdup(w);
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) < 0) { /* less than into left subtree */
		p->left = add_lower_tree(p->left, w);
	} else if (cond > 0) { /* greater than into left subtree */
		p->right = add_lower_tree(p->right, w);
	}
	return p;
}

void print_upper_tree(struct upper_node *p)
{
	if (p != NULL)
	{
		print_upper_tree(p->left);
		print_lower_tree(p->group_root);
		putchar('\n');
		print_upper_tree(p->right);
	}
}

/* in-order print of tree p */
void print_lower_tree(struct lower_node *p)
{
	if (p != NULL) {
		print_lower_tree(p->left);
		printf("%s\n", p->word);
		print_lower_tree(p->right);
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

/* make a lower_node */
struct lower_node *talloc(void)
{
	return (struct lower_node *) malloc(sizeof(struct lower_node));
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