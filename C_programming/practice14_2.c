/*void함수 사용하기 -> 아래방식 사용X, 글로벌 변수 사용O*/
#include <stdio.h>

#define daily_rate 100000
#define hourly_rate 10000

void get_pay(void);

int main()
{
	get_pay();
	
	return 0;
}

void get_pay(void)
{
	int total_hours, day_rate, hour_rate, result;
	printf("근로 시간은? ");
	scanf("%d", &total_hours);
	day_rate = (total_hours / 8) * daily_rate;
	hour_rate = (total_hours % 8) * hourly_rate;
	result = day_rate + hour_rate;
	printf("오늘의 임금은 %d원", result);
}