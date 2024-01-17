/*
 * ljh_1103_8.c
 *
 * Created: 2023-11-03 ¿ÀÈÄ 4:29:56
 * Author: wjdgh
 */

#include <mega128a.h>

const unsigned char led[8] = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};

void main(void)
{
    unsigned char old_sw, new_sw;
    unsigned char state = 0;
    
    DDRC = 0xFF;
    DDRE = 0x00;
    PORTC = led[state];
    
    old_sw = PINE & 0b00010000;
    
    while (1)
    {
        new_sw = PINE & 0b00010000;
        if((old_sw != 0) && (new_sw == 0))   
        {
            state = (state + 1) % 8;
            PORTC = led[state];
        } // end of if
        old_sw = new_sw;        
    } // end of while
} // end of main
