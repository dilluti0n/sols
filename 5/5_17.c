/*
 * Ex. 5-17. Add a field-handling capability, so sorting may be done on
 * fields within lines, each field sorted according to an independant
 * set of options. (The index for this book was sorted with -df for the
 * index category and -n for the page numbers.)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 10000
#define MAXFIELD 10

int argv_pharase (int argc, char* argv[]);

int  getline_e  (char* line, int maxline);

int line_parse (char* line, char** p);
int  readlines  (char *lineptr[], int maxlines);
void writelines (char *lineptr[], int maxlines);
void freelines  (char* lineptr[], int maxlines);

void qsort_e    (void *lineptr[], int left, int right,
			int (*comp)(void*, void*));

int  numcmp    (char*, char*);
int  strcmp_e  (char*, char*);

enum options {
	FIELD = 0,
	NUMERIC,
	REVERSE,
	FOLD,
	DIRECTORY
	};

int reverse = 1;   /* 1, -1(reverse, -r) */
int fold = 0;      /* 0, 1(fold, -f) */
int directory = 0; /* 0, 1(dir, -d) */

main (int argc, char* argv[])
{
	int (*comp)(void*, void*) = strcmp_e;

	int option[MAXFIELD][5];
	char *lineptr[MAXLINES];
	int nlines, c;
	int numeric = 0; /* indicator for numeric option */

	if (argv_pharase(argc, argv, option) != 0) {
		fputs ("err: invalid argument\n", stderr);
		exit(EXIT_FAILURE);
	}
	if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
		fputs ("input too big to sort\n", stderr);
		exit(EXIT_FAILURE)
	}
	qsort_e((void **) lineptr, 0, nlines - 1, comp);
	writelines(lineptr,nlines);
	freelines(lineptr,nlines);
	return 0;
}

int argv_pharase (int argc, char* argv[], int (*option)[5])
{
	int c;
	
	if (argc >= MAXFIELD)
		return 1;
	
	while (--argc > 0 && (*++argv)[0] == '-') {
		while ((c = *argv++[0]) != '\0') {
			if (isdigit(c))
				(*option)[FIELD] = c - '0';
			switch (c) {
			case 'n':
				(*option)[NUMERIC] = 1;
				break;
			case 'r':
				(*option)[REVERSE] = 1;
				break;
			case 'f':
				(*option)[FOLD] = 1;
				break;
			case 'd':
				(*option)[DIRECTORY] = 1;
				break;
			default:
				return 1;
				break;
			}
		}
		option++;
	}
	return 0;
}

int line_parse (char* line, char** p)
{
	int i = 0;
	char* str;

	if((str = malloc (strlen(line) + 1)) == NULL)
		return -1;
	strcpy(str, line);
	while (*str != '\0' && i < MAXFIELD - 1) {
		p[i++] = str++;
		while(*str != '\0' && !isspace(*line))
			str++;
		*str++ = '\0';
		while(isspace(*str))
			str++;
	}
	p[i] = NULL;
	return i;
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
