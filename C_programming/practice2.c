#include <stdio.h>

int main()
{
	double pi = 3.14;
	int radius = 3;
	double area, circle;

	area = radius * radius * pi;
	circle = 2 * radius * pi;

	printf("������ : %d\n", radius);
	printf("���� �ѷ� : %.2lf\n", circle);
	printf("���� ���� : %.2lf\n", area);

	return 0;
}