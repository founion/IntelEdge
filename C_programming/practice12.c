#include <stdio.h>

#define L 2
#define M 3
#define N 4

int main()
{
	int t[L][M][N] = { {{20,22,30,35},{12,19,35,22},{10,9,15,20}},
		{{20,22,30,35},{12,19,35,22},{12,15,9,25}} };
	int i, j, k;

	for (i = 0; i < L; i++)
	{
		printf("\n %d¸é \n\n", i + 1);
		for (j = 0; j < M; j++)
		{
			for (k = 0; k < N; k++)
			{
				printf("%3d", t[i][j][k]);
			}
			printf("\n");
		}
	}

	return 0;
}