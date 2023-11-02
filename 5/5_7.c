/* Ex 5-7. Rewrite readlines to store lines in an array supplied by main, rather than calling alloc to maintain storage. How much faster is the program? */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define MAXSTORE 5000

char* lineptr[MAXLINES];

int readlines (char *lineptr[], int nlines, char* storage);
void writelines (char *lineptr[], int nlines);

int getline_e (char*, int);
void qsort_e (char* v[], int left, int right);

main()
{
	int nlines;
	char strbuf[MAXSTORE];

	if ((nlines = readlines (lineptr, MAXLINES, strbuf)) >= 0) {
		qsort_e (lineptr, 0, nlines - 1);
		printf ("----\n");
		writelines (lineptr, nlines);
		return 0;
	} else {
		printf ("error: input too big to sort\n");
		return 1;
	}
}

int getline_e (char* line, int maxline)
{
	char* lp = line;

	while ((*line = getchar()) != EOF && *line++ != '\n' && maxline--)
		;
	*line = '\0';

	return line - lp;
}

int readlines (char* lineptr[], int maxlines, char* storage)
{
	int len, nlines;
	char *p = storage, line[MAXLEN];

	nlines = 0;
	while ((len = getline_e(line, MAXLEN)) > 0)
		if (nlines >= maxlines || strlen(storage) + len > MAXSTORE)
			return -1;
		else {
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
			p += len;
		}
	return nlines;
}

void writelines (char* lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

void qsort_e (char* v[], int left, int right)
{
	int i, last;
	void swap (char *v[], int i, int j);

	if (left >= right)
		return;
	swap (v, left, (left + right)/2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap (v, left, last);
	qsort_e (v, left, last - 1);
	qsort_e (v, last + 1, right);
}

void swap (char* v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}