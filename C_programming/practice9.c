#include <stdio.h>

#define SIZE 5

int main()
{
	int i, sum = 0, count = 0;
	int quiz[SIZE];
	float avg;

	printf("%d���� ������ ������� �Է��ϼ���.\n", SIZE);
	for (i = 0; i < SIZE; i++)
	{
		printf("%d���� ���� : ", i + 1);
		scanf("%d", &quiz[i]);
		sum = sum + quiz[i];
	}

	avg = (float)sum / SIZE;
	printf("========================\n");
	printf("��ȣ ����  ��հ��� ����\n");
	printf("========================\n");

	for (i = 0; i < SIZE; i++)
	{
		if (avg > quiz[i])
		{
			count++;
		}
		printf("%2d    %2d   %5.2lf\n", i + 1, quiz[i], quiz[i] - avg);
	}
	printf("========================\n");
	printf("��� ���� : %.2lf\n", avg);
	printf("========================\n");
	printf("��� �̸� �л� �� : %d", count);


	return 0;
}