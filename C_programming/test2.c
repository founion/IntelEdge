#include <stdio.h>
#include "test2.h"
#include "test.h"

int main()
{
	int n;

	printf("�Է� : ");
	scanf("%d", &n);
	printf("%d�� ���� = %d, %d�� ������ = %d\n", n, SQUARE(n), n, CUBE(n));
	printf("�� �̸��� %s�̰�, ���̴� %d���Դϴ�.", NAME, AGE);

	return 0;
}