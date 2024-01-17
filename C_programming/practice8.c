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

	printf("길이(밀리미터) : ");
	scanf("%f", &mm);
	printf("길이(cm): %.2lf\n", mm * CM);
	printf("길이(m) : %.2lf\n", mm * M);
	printf("길이(km) : %lf\n", mm * KM);
	printf("길이(inch) : %.2lf\n", mm * INCH);
	printf("길이(ft) : %.2lf\n", mm * FT);
	printf("길이(yd) : %.2lf\n", mm * YD);

	return 0;
}