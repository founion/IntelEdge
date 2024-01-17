#include <stdio.h>

int main()
{
	int n1, n2;
	int max, min;
	printf("두 수 n1, n2를 입력하시오\n");
	scanf_s("%d%d", &n1, &n2);
	n1 > n2 ? (max = n1, min = n2) : (max = n2, min = n1);

	printf("큰수 %d를 작은수 %d로 나눈 몫 = %d\n", max, min, max / min);
	printf("큰수 %d를 작은수 %d로 나눈 나머지 = %d\n", max, min, max % min);

	return 0;

}