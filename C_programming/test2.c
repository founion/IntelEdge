#include <stdio.h>
#include "test2.h"
#include "test.h"

int main()
{
	int n;

	printf("입력 : ");
	scanf("%d", &n);
	printf("%d의 제곱 = %d, %d의 세제곱 = %d\n", n, SQUARE(n), n, CUBE(n));
	printf("내 이름은 %s이고, 나이는 %d세입니다.", NAME, AGE);

	return 0;
}