/*void�Լ� ����ϱ� -> �Ʒ���� ���X, �۷ι� ���� ���O*/
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
	printf("�ٷ� �ð���? ");
	scanf("%d", &total_hours);
	day_rate = (total_hours / 8) * daily_rate;
	hour_rate = (total_hours % 8) * hourly_rate;
	result = day_rate + hour_rate;
	printf("������ �ӱ��� %d��", result);
}