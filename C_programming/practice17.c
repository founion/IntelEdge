#include <stdio.h>

double avg(int arr[], int n);

int main()
{
	int pen[4] = { 4500,5370,4920,6090 };
	int monthly_stock[12] = { 505,409,389,257,450,501,500,621,480,350,389,250 };
	double pen_avg, monthly_avg;

	pen_avg = avg(pen, 4);
	monthly_avg = avg(monthly_stock, 12);
	printf("Ææ Æò±Õ ÆÇ¸Å ¼ö : %.1lf\n", pen_avg);
	printf("Æò±Õ Àç°í·® : % .1lf\n", monthly_avg);

}

double avg(int arr[], int n)
{
	int i, sum = 0;

	for (i = 0; i < n; i++)
	{
		sum += arr[i];
	}
	
	return (double)sum / n;
}