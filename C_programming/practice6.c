#include <stdio.h>

int main()
{
	int n, even = 2, odd = 1, sum_even = 0, sum_odd = 0;

	printf("정수 n을 입력하세요 : ");
	scanf("%d", &n);

	while ((odd <= n) && (even <= n))
	{
		sum_even += even;
		sum_odd += odd;
		even += 2;
		odd += 2;
	}

	if (n == odd)
	{
		sum_odd += odd;
	}

	printf("정수 1에서 %d이하 홀수들의 합은 %d이고 짝수들의 합은 %d입니다. ", n, sum_odd, sum_even);

	return 0;
}