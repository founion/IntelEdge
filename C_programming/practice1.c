#include <stdio.h>

int main()
{
	int hours, days, hourly_rate, pay;

	hours = 8;
	days = 25;
	hourly_rate = 4700;
	pay = hours * days * hourly_rate;

	printf("�Ƹ�����Ʈ �� �ð� %d�ð� \n", hours * days);
	printf("�� �Ƹ�����Ʈ �޿� %d��\n", pay);

	return 0;
}