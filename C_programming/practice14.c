#include <stdio.h>

#define daily_rate 100000
#define hourly_rate 10000

int get_pay(int hours);

int main()
{
	int total_hours, total_rate;
	printf("근로 시간은? ");
	scanf("%d", &total_hours);
	total_rate = get_pay(total_hours);
	printf("오늘의 임금은 %d원", total_rate);

	return 0;
}

int get_pay(int hours)
{
	int result, day_rate, hour_rate;
	day_rate = (hours / 8) * daily_rate;
	hour_rate = (hours % 8) * hourly_rate;
	result = day_rate + hour_rate;

	return result;
}