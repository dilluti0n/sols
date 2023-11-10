/*
 * Ex. 5-16. Add the -d ("directory order") opteon, which makes
 * comparisons only on letters, numbers and blanks. Make sure 
 * it works in conjunction with -f.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 10000

char *lineptr[MAXLINES];

int getline_e (char* line, int maxline);

int readlines (char *lineptr[], int maxlines);
void writelines (char *lineptr[], int maxlines);
void freelines (char* lineptr[], int maxlines);

void qsort_e (void *lineptr[], int left, int right,\
			int (*comp)(void*, void*));

int numcmp (char*, char*);
int strcmp_e (char*, char*);

int reverse;   /* 1, -1(reverse, -r) */
int fold;      /* 0, 1(fold, -f) */
int directory; /* 0, 1(dir, -f) */

main (int argc, char* argv[])
{
	int nlines, c;
	int numeric = 0;

	reverse = 1;
	fold = 0;
	directory = 0;
	while (--argc > 0)
		if ((*++argv)[0] == '-') {
			c = *(*argv + 1);
			switch (c) {
			case 'n':
				numeric = 1;
				break;
			case 'r':
				reverse = -1;
				break;
			case 'f':
				fold = 1;
				break;
			case 'd':
				directory = 1;
				break;
			}
		}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort_e((void **) lineptr, 0, nlines - 1,\
			(int (*)(void*,void*))(numeric ? numcmp : strcmp_e));
		writelines(lineptr,nlines);
		freelines(lineptr,nlines);
		return 0;
	} else {
		printf ("input Too Big To sort\n");
		return 1;
	}
}

int getline_e (char* line, int maxline)
{
	char* lp = line;
	int c;

	while ((*line = c = getchar()) != EOF && c != '\n' && maxline--)
		line++;

	if (c == '\n' && maxline > 0)
		*line++ = c;
	*line = '\0';

	return line - lp;
}

int readlines (char* lineptr[],int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getline_e(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || (p = malloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0';
			strcpy (p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}

void writelines(char** ptr, int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *ptr++);
}

void freelines (char** lineptr, int nlines)
{
	for (int i = 0; i < nlines; i++)
		free(lineptr[i]);
}

void qsort_e (void *v[], int left, int right,int (*comp)(void*, void*))
{
	int i, last;
	void swap (void *v[], int, int);

	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if ((*comp)(v[i], v[left]) * reverse < 0)
			swap (v, ++last, i);
	swap (v, left, last);
	qsort_e (v, left, last - 1, comp);
	qsort_e (v, last + 1, right, comp);
}

int numcmp (char* s1, char* s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	return 0;
}

int strcmp_e (char* s1, char* s2)
{
	int result;

	while (*s1 && *s2) {
		while (directory && !isalnum(*s1) && !isspace(*s1))
			++s1;
		while (directory && !isalnum(*s2) && !isspace(*s2))
			++s2;
		if ((result = fold ? tolower(*s1) - tolower(*s2) : *s1 - *s2) != 0)
			return result;
		else {
			++s1;
			++s2;
		}
	}
	return 0;
}

void swap(void *v[], int i, int j)
{
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
