/*
 * ljh_1103_7.c
 *
 * Created: 2023-11-03 ���� 4:24:39
 * Author: wjdgh
 */

#include <mega128a.h>

void main(void)
{ 
    unsigned char key;   

    DDRC = 0xFF;
    DDRE &= 0x0F;
    
    PORTC = 0xFF;
while (1)
    {
        key = PINE & 0xF0; // ����ġ�� ������ ������ PINE4,5,6,7���� 1�� �ΰ��ȴ�. 0,1,2,3�� ����ġ�� ������ ���� 4,5,6,7�� 0�� �ΰ��ǰ� �̸� 0xF0�� &�����ϸ� ������ ����.
        switch(key)
        {
            case 0b11100000: PORTC = 0x00; // 0b11100000 : �Է� 4���� 0 = 0������ġ ���� ���                                                                  
            break;
            case 0b11010000: PORTC = 0xFF; // 0b11010000 : �Է� 5���� 0 = 1������ġ ���� ���
            break; 
            case 0b10110000: PORTC = 0x55; // 0b10110000 : �Է� 6���� 0 = 2������ġ ���� ���
            break;                        
            case 0b01110000: PORTC = 0xAA; // 0b01110000 : �Է� 7���� 0 = 3������ġ ���� ���
            break;
            default:
			break;
        } // end of switch
    } // end of while
} // end of main
