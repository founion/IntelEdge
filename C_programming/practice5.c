#include <stdio.h>

#define N 10
#define STD 70

int main()
{
	int i, score = 0, sum = 0, pass = 0, fail = 0;
	double avg = 0;
	
	for (i = 0; i < N; i++)
	{
		printf("%2d번째 학생의 점수를 입력하세요 : ", i + 1);
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
	printf("전체 평균 : %.2lf, 통과자 수 : %d, 탈락자 수 : %d\n", avg, pass, fail);

	return 0;
}