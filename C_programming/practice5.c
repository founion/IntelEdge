#include <stdio.h>

#define N 10
#define STD 70

int main()
{
	int i, score = 0, sum = 0, pass = 0, fail = 0;
	double avg = 0;
	
	for (i = 0; i < N; i++)
	{
		printf("%2d��° �л��� ������ �Է��ϼ��� : ", i + 1);
		scanf("%d", &score);
		sum += score;
		if (score >= STD)
		{
			pass++;
		}
		else
		{
			fail++;
		}
	}
	avg = sum / (double)N;
	printf("��ü ��� : %.2lf, ����� �� : %d, Ż���� �� : %d\n", avg, pass, fail);

	return 0;
}