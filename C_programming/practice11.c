#include <stdio.h>

#define COL 3
#define ROW 4

int main()
{
	int col, row;
	int matrixA[COL][ROW];
	int matrixB[COL][ROW];

	printf("��� A�Է�\n");
	for (col = 0; col < COL; col++)
	{
		for (row = 0; row < ROW; row++)
		{
			printf("%d�� %d��? ", col + 1, row + 1);
			scanf("%d", &matrixA[col][row]);
		}
	}
	printf("��� B�Է�\n");
	for (col = 0; col < COL; col++)
	{
		for (row = 0; row < ROW; row++)
		{
			printf("%d�� %d��? ", col + 1, row + 1);
			scanf("%d", &matrixB[col][row]);
		}
	}
	printf("��� A      +   ��� B      =   ��� C\n");
	for (col = 0; col < COL; col++)
	{
		printf("[");
		for (row = 0; row < ROW; row++)
		{
			printf("%3d", matrixA[col][row]);
		}
		printf("]\t");
		printf("[");
		for (row = 0; row < ROW; row++)
		{
			printf("%3d", matrixB[col][row]);
		}
		printf("]\t");
		printf("[");
		for (row = 0; row < ROW; row++)
		{
			printf("%3d", (matrixA[col][row] + matrixB[col][row]));
		}
		printf("]\t");
		printf("\n");
	}

	return 0;
}