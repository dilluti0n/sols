/* Ex 5-13. Write the program tail, which prints the last n lines of its input. (tail -n prints the last n lines of input), the program should behave rationally no matter how unreasonable the input or the value of n. */

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_N 10
#define BUFSIZE 4
#define MAXLINE 1000

char buffer[BUFSIZE];

char* getline_buf (void);

int main(int argc, char** argv)
{
	char* input[MAXLINE];
	char** strPtr;

	int n = DEFAULT_N;

	for (strPtr = input; (*strPtr = getline_buf()) != NULL; strPtr++)
		if (strPtr - input > MAXLINE) {
			fprintf(stderr, "err: too many lines\n");
			exit(EXIT_FAILURE);
		}
	while (--argc > 0 && (*++argv)[0] == '-')
		if ((n = atoi((*argv) + 1)) == 0) {
			fprintf(stderr, "err: inappropriate value of n\n");
			exit(EXIT_FAILURE);
		}
	if (n < 0) {
		for (strPtr = input; *strPtr && n; strPtr++,n++)
			printf("%s",*strPtr);
		return 0;
	}
	while (n-- > 0 && strPtr > input)
		strPtr--;
	for (; *strPtr; strPtr++)
		printf("%s",*strPtr);

	return 0;
}

/* store line from input buffer to our buffer and returns the pointer
which points the first value of line. If EOF encountered, it returns NULL pointer. */
char* getline_buf (void)
{
	static char* bufPtr = buffer;
	char* start = bufPtr;

	while (bufPtr - buffer < BUFSIZE && (*bufPtr = getchar()) != EOF && *bufPtr++ != '\n')
		;
	if (bufPtr - buffer >= BUFSIZE){
		fprintf(stderr, "err: too many input\n");
		exit(EXIT_FAILURE);
	}
	if (*bufPtr != EOF) {
		*bufPtr++ = '\0';
		return start;
	} else
		return NULL;
}

/* Useage: ./a.out -{n} < sample.txt */