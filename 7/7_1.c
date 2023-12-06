/*
 * Ex 7-1. Write a program that converts upper case to lower or
 * lower case to upper, depending on name it is invoked with,
 * as found in argv[0].
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum mod {
	ERR = -1,
	NO_ARGV = 0,
	UPPER,
	LOWER,
};

enum mod parse_argv_list(int argc, char *argv[]);

main(int argc, char *argv[])
{
	int c;
	int (*to)(int) = &tolower;
	enum mod state = parse_argv_list(argc, argv);

	switch(state) {
	case LOWER :
		to = &tolower;
		break;
	case UPPER :
		to = &toupper;
		break;
	case NO_ARGV :
		to = &tolower;
		break;
	case ERR :
		return EXIT_FAILURE;
	}
	while ((c = getchar()) != EOF)
		putchar((*to)(c));
	return EXIT_SUCCESS;
}

enum mod parse_argv_list(int argc, char *argv[])
{
	if (argc > 2) {
		fprintf(stderr, "%s: too many argv.\n", __func__);
		goto err;
	}
	if (argc == 1)
		return NO_ARGV;
	if (!strcmp(argv[1], "tolower"))
		return LOWER;
	if (!strcmp(argv[1], "toupper"))
		return UPPER;
	fprintf(stderr, "%s: invalid argv \"%s\".\n", __func__, argv[1]);
err:
	printf("Useage: convert tolower (convert upper letter to lower one.)\n");
	printf("                toupper (convert lower letter to upper one.)\n");
	return ERR;
}