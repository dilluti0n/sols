/* Ex 5-8. There is no error checking in day_of_year or month_day. Remedy this defect */

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* set day of year from month and day */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	if (month < 1 || month > 12) {
		printf ("[day_of_year] error: inappropriate month\n");
		return -1;
	}

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	if (day < 1 || day > daytab[leap][month]) {
		printf ("[day_of_year] error: inappropriate day\n");
		return -1;
	}
	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

/* set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	if (leap == 0 && yearday > 365 || leap != 0 && yearday > 366) {
		printf("[month_day] error: inappropriate yearday\n");
		return;
	}
	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}