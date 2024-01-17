/*
 * ljh_1103_4_2.c
 *
 * Created: 2023-11-03 ¿ÀÈÄ 2:49:36
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
        PORTC = 0x55;
        delay_ms(500);
        PORTC = 0xAA;
        delay_ms(500);
        
        led = 0xFE;
        for(i=0;i<8;i++)
        {
            PORTC = led;
            delay_ms(500);
            led = led << 1;
        }
        
        led = 0xFE;
        for(i=0;i<8;i++)
        {
            PORTC = led;
            delay_ms(500);
            led = led << 1;
            led = led | 0x01;
        } 

    }
}
