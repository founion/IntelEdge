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

	printf("** �ζ� ��÷�� �����մϴ�. **\n\n");
	srand((unsigned)time(NULL));
	for (i = 0; i < 6;)
	{
		num = getNumber();
		for (k = 0; k < 6; k++)
		{
			if (lotto[k] == num)
			{
				dup = 'Y'; /* �ߺ��� ��� Y */
			}
		}
		if (dup == 'N')
		{
			lotto[i++] = num; /* �ߺ��� �ƴϸ� num�� �����ϰ� i+1 */
		}
		else
		{
			dup = 'N'; /* �ߺ��̸� num�� ���� �� i++�� ���� �ʰ� �ٽ� for�� ����(���� ���� �̰�, ���� ���ڵ�� ��) */
		}
	}

	printf("��÷�� �ζ� ��ȣ ==> ");
	for (i = 0; i < 6; i++)
	{
		printf("%d ", lotto[i]);
	}
	printf("\n\n");
}