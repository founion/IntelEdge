#include <stdio.h>

int main()
{
	int n1, n2;
	int max, min;
	printf("�� �� n1, n2�� �Է��Ͻÿ�\n");
	scanf_s("%d%d", &n1, &n2);
	n1 > n2 ? (max = n1, min = n2) : (max = n2, min = n1);

	printf("ū�� %d�� ������ %d�� ���� �� = %d\n", max, min, max / min);
	printf("ū�� %d�� ������ %d�� ���� ������ = %d\n", max, min, max % min);

	return 0;

}