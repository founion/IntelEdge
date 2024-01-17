/*
 * ljh_1103_7.c
 *
 * Created: 2023-11-03 오후 4:24:39
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
        key = PINE & 0xF0; // 스위치를 누르지 않으면 PINE4,5,6,7에는 1이 인가된다. 0,1,2,3번 스위치를 누르면 각각 4,5,6,7에 0이 인가되고 이를 0xF0과 &연산하면 다음과 같다.
        switch(key)
        {
            case 0b11100000: PORTC = 0x00; // 0b11100000 : 입력 4번에 0 = 0번스위치 누른 경우                                                                  
            break;
            case 0b11010000: PORTC = 0xFF; // 0b11010000 : 입력 5번에 0 = 1번스위치 누른 경우
            break; 
            case 0b10110000: PORTC = 0x55; // 0b10110000 : 입력 6번에 0 = 2번스위치 누른 경우
            break;                        
            case 0b01110000: PORTC = 0xAA; // 0b01110000 : 입력 7번에 0 = 3번스위치 누른 경우
            break;
            default:
			break;
        } // end of switch
    } // end of while
} // end of main
