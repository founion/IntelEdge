#include <stdio.h>

#define CM 0.1
#define M 0.001
#define KM 0.000001
#define INCH 0.03937
#define FT 0.003281
#define YD 0.001094

int main()
{
	float mm;

	printf("����(�и�����) : ");
	scanf("%f", &mm);
	printf("����(cm): %.2lf\n", mm * CM);
	printf("����(m) : %.2lf\n", mm * M);
	printf("����(km) : %lf\n", mm * KM);
	printf("����(inch) : %.2lf\n", mm * INCH);
	printf("����(ft) : %.2lf\n", mm * FT);
	printf("����(yd) : %.2lf\n", mm * YD);

	return 0;
}