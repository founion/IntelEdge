/*
 * ljh_1103_6.c
 *
 * Created: 2023-11-03 ¿ÀÈÄ 3:35:24
 * Author: wjdgh
 */

#include <mega128a.h>

void main(void)
{
    unsigned char sw;
    
    DDRC = 0xFF;
    DDRE &= 0x0F;
    
    PORTC = 0xFF;
while (1)
    {
        sw = PINE & 0b00010000;
        
        if(sw != 0)
        {
            PORTC = 0xFF;
        }
        else
        {
            PORTC = 0x00;
        }
    }
}
