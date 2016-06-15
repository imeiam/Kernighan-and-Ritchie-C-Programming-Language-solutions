/*
   Rewrite the routines day_of_year and month_day with pointers instead of indexing.
  */

#include<stdio.h>

static char daytab[2][13] =  {
		{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
			{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int day_of_year(int year, int month, int day)
{
	int i, leap;			
	if (year < 0 || month < 1 || month > 12 || day < 1)						
		return -1;

	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;

	if (day > daytab[leap][month])
		return -1;

	char *ndays = daytab[leap] + 1;
	for (i = 1; i < month; i++)
		day += *ndays++;
	return day;
}

/* month_day: set month, day from day of year */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
	if (year < 0 || yearday < 1)
		return -1;
	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
	if ((leap && yearday > 366) || (!leap && yearday > 365))
		return -1;
	char *ndays = daytab[leap] + 1;
	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= *ndays++;
	*pmonth = i;
	*pday = yearday;
	return 0;
}



int main(void){
	printf("\n 1/2/96- %d ",day_of_year(1996,2,1));
	int mon,day;
	month_day(1996,32,&mon,&day);
	printf("\n 1/2/96- month %d , day %d \n",mon,day);
	return 0;
}
