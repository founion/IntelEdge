/*
 * ljh_1103_4.c
 *
 * Created: 2023-11-03 ¿ÀÈÄ 2:30:57
 * Author: wjdgh
 */

#include <mega128a.h>
#include <delay.h>

void main(void)
{
    unsigned int i;
    unsigned char led;
    
    DDRC = 0xFF;
    while (1)
    {
        led = 0x7F;
        
        for(i=0;i<8;i++)
        {
            PORTC = led;
            delay_ms(500);
            led = led >> 1;
            led = led | 0x80;
        }
    }
}
