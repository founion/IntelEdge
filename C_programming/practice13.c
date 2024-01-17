#include <stdio.h>

int find_larger(int n1, int n2);

int main()
{
	int n1, n2;
	int max;
	printf("두 숫자를 입력하세요 : ");
	scanf("%d %d", &n1, &n2);
	max = find_larger(n1, n2);

	printf("두 숫자 %d와 %d 중 큰 숫자는 %d입니다.\n", n1, n2, max);

	return 0;
}

int find_larger(int m1, int m2)
{
	int result;
	if (m1 > m2)
	{
		result = m1;
	}
	else
	{
		result = m2;
	}
	
	return result;
}