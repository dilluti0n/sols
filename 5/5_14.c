/* Ex. 5-14. Modify the sort program to handle a -r flag, which indicates sorting in reverse (decreasing) order. Be sure that -r works with -n */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

main (int argc, char* argv[])
{
	int nlines, c;
	int numeric = 0;

	while (--argc > 0)
		if ((*++argv)[0] == '-')
			while ((c = *++argv[0]) != 0) {
				switch (c) {
				case 'n':
					numeric = 1;
					break;
				case 'r':
					printf("reverse\n");
					break;
				}
			}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort_e((void **) lineptr, 0, nlines - 1,(int (*)(void*,void*))(numeric ? numcmp : strcmp));
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
		if ((*comp)(v[i], v[left])< 0)
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

void swap(void *v[], int i, int j)
{
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
