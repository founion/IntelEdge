/*
 * ljh_1103_1.c
 *
 * Created: 2023-11-03 오후 12:36:57
 * Author: wjdgh
 */

#include <mega128a.h>

void main(void)
{ DDRC = 0xFF; // 포트 C 출력 설정
    PORTC = 0x55; // 포트 C 0x55( 또는 0101 0101) 출력
    while(1);
}