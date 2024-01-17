#include <stdio.h>

int main()
{
	double pi = 3.14;
	int radius = 3;
	double area, circle;

	area = radius * radius * pi;
	circle = 2 * radius * pi;

	printf("반지름 : %d\n", radius);
	printf("원의 둘레 : %.2lf\n", circle);
	printf("원의 넓이 : %.2lf\n", area);

	return 0;
}