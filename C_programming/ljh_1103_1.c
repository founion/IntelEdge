/*
 * ljh_1103_1.c
 *
 * Created: 2023-11-03 ���� 12:36:57
 * Author: wjdgh
 */

#include <mega128a.h>

void main(void)
{ DDRC = 0xFF; // ��Ʈ C ��� ����
    PORTC = 0x55; // ��Ʈ C 0x55( �Ǵ� 0101 0101) ���
    while(1);
}