#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getNumber()
{
	return rand() % 45 + 1;
}

int main()
{
	int lotto[6] = { 0 };
	int i, k, num;
	char dup = 'N';

	printf("** 로또 추첨을 시작합니다. **\n\n");
	srand((unsigned)time(NULL));
	for (i = 0; i < 6;)
	{
		num = getNumber();
		for (k = 0; k < 6; k++)
		{
			if (lotto[k] == num)
			{
				dup = 'Y'; /* 중복인 경우 Y */
			}
		}
		if (dup == 'N')
		{
			lotto[i++] = num; /* 중복이 아니면 num을 저장하고 i+1 */
		}
		else
		{
			dup = 'N'; /* 중복이면 num을 저장 및 i++을 하지 않고 다시 for문 실행(랜덤 숫자 뽑고, 이전 숫자들과 비교) */
		}
	}

	printf("추첨된 로또 번호 ==> ");
	for (i = 0; i < 6; i++)
	{
		printf("%d ", lotto[i]);
	}
	printf("\n\n");
}