/*
 * ljh_1103_2.c
 *
 * Created: 2023-11-03 ¿ÀÈÄ 2:17:49
 * Author: wjdgh
 */

#include <mega128a.h>
#include <delay.h>

void main(void)
{
    DDRC = 0xFF;
    
    while (1)
    {
        PORTC = 0X55;
        delay_ms(500);
        
        PORTC = 0xAA;
        delay_ms(500);
    }
}
