/* Ex 5-9. Rewrite the routines day_of_year and month_day with pointers instead of indexing. */
#include <stdio.h>

static char daytab[][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int, int, int);
void month_day(int, int, int*, int*);

main()
{
	printf("%d\n", day_of_year(2023, 2, 1));
	int month, day;
	month_day(2023, day_of_year(2023,11,1), &month, &day);
	printf("%d/%d\n",month,day);
}

/* set day of year from month and day */
int day_of_year(int year, int month, int day)
{
	char *pc;

	if (month < 1 || month > 12) {
		printf ("[day_of_year] error: inappropriate month\n");
		return -1;
	}

	pc = *(daytab + (year % 4 == 0 && year % 100 != 0 || year % 400 == 0));
	const char* pe = pc + month;
	if (day < 1 || day > *pe) {
		printf ("[day_of_year] error: inappropriate day\n");
		return -1;
	}

	while (++pc < pe)
		day += *pc;
	return day;
}

/* set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int leap;
	char *pc ,*pm;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	if (leap == 0 && yearday > 365 || leap != 0 && yearday > 366) {
		printf("[month_day] error: inappropriate yearday\n");
		return;
	}
	pc = pm = *(daytab + leap);
	while(yearday > *pc)
		yearday -= *pc++;
	*pmonth = pc - pm;
	*pday = yearday;
}