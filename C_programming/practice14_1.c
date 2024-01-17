#include <stdio.h>

#define daily_rate 100000
#define hourly_rate 10000
#define minutely_rate 50

int get_pay(int hours);

int main()
{
	int work_hours, work_minutes, total_minutes, pay;
	printf("근로 시간은(시간 분)? ");
	scanf("%d %d", &work_hours, &work_minutes);
	total_minutes = (work_hours * 60) + work_minutes;
	pay = get_pay(total_minutes);
	printf("오늘의 임금은 %d원", pay);

	return 0;
}

int get_pay(int hours)
{
	int result, minute_rate, day_rate, hour_rate;
	day_rate = (hours / 480) * daily_rate;
	hour_rate = ((hours % 480) / 60) * hourly_rate;
	minute_rate = ((hours % 480) % 40) * minutely_rate;
	result = minute_rate + day_rate + hour_rate;

	return result;
}