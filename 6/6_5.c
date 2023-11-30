/*
 * Ex 6-5. Write a function undef that remove a name and definition
 * from the table maintained by lookup and install.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101

struct nlist {
	char *name; /* defined name */
	char *defn; /* replacement text */
	struct nlist *next;
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

struct nlist *install(char *name, char *defn);
int undef(char *name);
struct nlist *lookup(char *s);
unsigned hash(char *s);

main()
{
	return 0;
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) { /* not found */
		np = (struct nlist *) malloc(sizeof (*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np; /* insert np to head of list */
	} else { /* found */
		free((void *) np->defn); /* free previous defn */
	}
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
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

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (!strcmp(s, np->name))
			return np; /* found */
	return NULL; /* not found */
}

/* hash: form hash for string s */
unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}