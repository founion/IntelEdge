#include <stdio.h>

#define N 10

int find_larger(int n1, int n2);

int main()
{
	int freeze[N] = { 15,0,-20,-30,50,-5,-120,-5,10,-12 };
	int max = freeze[0];
	int i;

	for (i = 1; i < N; i++)
	{
		max = find_larger(max, freeze[i]);	/*freeze[0]=15�̹Ƿ� freeze[1]���� �� ����*/
	}
	printf("��� �� ��� : ");
	for (i = 0; i < N; i++)
	{
		printf(" %d ", freeze[i]);
	}
	printf("\n���� ���� ��� �� : %d\n", max);

	return 0;
}

int find_larger(int n1, int n2)
{
	if (n1 > n2)
	{
		return n1;
	}
	else
	{
		return n2;
	}
}