/*
 * ljh_1103_4_1.c
 *
 * Created: 2023-11-03 ¿ÀÈÄ 2:44:00
 * Author: wjdgh
 */

#include <mega128a.h>
#include <delay.h>

const unsigned char led[8] = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};

void main(void)
{
    unsigned int i;    
    
    DDRC = 0xFF;
    while (1)
    {
        for(i=0;i<8;i++)
        {
            PORTC = led[i];
            delay_ms(500);
        }
    }
}
