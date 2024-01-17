#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define LEAP 366
#define NLEAP 365

int leap_year(int y);
int days(int yy);

int main()
{
	int year;
	printf("총일을 구하고 싶은 연도는? ");
	scanf("%d", &year);
	printf("%d년은 %d일까지 있습니다. ", year, days(year));

	return 0;
}

int leap_year(int y)
{
	if ((y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0)))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int days(int yy)
{
	if (leap_year(yy) == TRUE)
	{
		return LEAP;
	}
	else
	{
		return NLEAP;
	}
}