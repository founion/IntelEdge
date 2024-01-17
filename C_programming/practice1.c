#include <stdio.h>

int main()
{
	int hours, days, hourly_rate, pay;

	hours = 8;
	days = 25;
	hourly_rate = 4700;
	pay = hours * days * hourly_rate;

	printf("아르바이트 총 시간 %d시간 \n", hours * days);
	printf("총 아르바이트 급여 %d원\n", pay);

	return 0;
}