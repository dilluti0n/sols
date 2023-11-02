/* Ex 5-11. Modify the programs entab and detab (chap 1) to accept a list of tab stops as arguments. Use the default tab settings if there are no arguments. */

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT 4 /* default tab */

main (int argc, char* argv[])
{
	int tab = DEFAULT, c;

	while (--argc > 0 && (*++argv)[0] == '-')
		while ((c = *++argv[0]))
			switch (c) {
			case 't':
				if (argv[1] == NULL || !(tab = atoi(argv[1]))) {
					fprintf(stderr, "err: inappropriate tab parameter\n");
					printf("Useage: detab -t {tab}\n");
					exit(EXIT_FAILURE);
				}
				break;
			default:
				fprintf(stderr, "err: unknown parameter -%c\n",c);
				printf("Useage: detab -t {tab}\n");
				exit(EXIT_FAILURE);
				break;
			}

	while ((c = getchar()) != EOF) {
		if(c == '\t')
			for (int i = tab; i > 0; i--)
				putchar(' ');
		else
			putchar(c);
	}
	putchar(EOF);
}
