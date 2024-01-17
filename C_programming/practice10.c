#include <stdio.h>

#define PERSON 30
#define STARS 6

int main()
{
	int survey[PERSON] = { 1,3,2,5,3,2,1,2,3,4,5,2,3,3,2,1,4,5,2,3,5,1,3,4,2,3,1,4,2,3 };
	int vote[STARS] = { 0 };
	int i;

	for (i = 0; i < PERSON; i++)
	{
		vote[survey[i]]++;
	}

	printf("연예인  득표수 \n");
	printf("===================\n");

	for (i = 1; i < STARS; i++)
	{
		printf("%d번\t%d표\n", i, vote[i]);
	}

	return 0;
}