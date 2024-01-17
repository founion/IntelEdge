#include <stdio.h>

void swap_value(int x, int y);
void swap_address(int* x, int* y);

int main()
{
	int x = 100, y = 200;
	printf("In main : x=%d, y=%d \n\n", x, y); /* 예상 : x=100, y=200 */

	swap_value(x, y); /* 예상 : x=200, y=100 */
	printf("In main : x=%d, y=%d (swap_value(x, y) 호출 후)\n\n", x, y); /* 예상 : x=100, y=200 */

	swap_address(&x, &y); /* 예상 : *x=200, *y=100 */
	printf("In main : x=%d, y=%d (swap_address(&x, &y) 호출 후\n\n", x, y); /* 예상 : x=200, y=100 */

	return 0;
}

void swap_value(int x, int y)
{
	int temp;
	temp = x;
	x = y;
	y = temp;
	printf("In swap_value : x=%d, y=%d \n", x, y);
}

void swap_address(int* x, int* y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
	printf("In swap_address : *x=%d, *y=%d \n", *x, *y);
}