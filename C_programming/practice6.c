#include <stdio.h>

int main()
{
	int n, even = 2, odd = 1, sum_even = 0, sum_odd = 0;

	printf("���� n�� �Է��ϼ��� : ");
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

	printf("���� 1���� %d���� Ȧ������ ���� %d�̰� ¦������ ���� %d�Դϴ�. ", n, sum_odd, sum_even);

	return 0;
}