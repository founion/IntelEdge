#include <stdio.h>

#define SIZE 5

int main()
{
	int i, sum = 0, count = 0;
	int quiz[SIZE];
	float avg;

	printf("%d명의 점수를 순서대로 입력하세요.\n", SIZE);
	for (i = 0; i < SIZE; i++)
	{
		printf("%d번의 점수 : ", i + 1);
		scanf("%d", &quiz[i]);
		sum = sum + quiz[i];
	}

	avg = (float)sum / SIZE;
	printf("========================\n");
	printf("번호 점수  평균과의 차이\n");
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
	printf("평균 점수 : %.2lf\n", avg);
	printf("========================\n");
	printf("평균 미만 학생 수 : %d", count);


	return 0;
}