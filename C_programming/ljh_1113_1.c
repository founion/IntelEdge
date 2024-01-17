/*
 * ljh_1113_1.c
 *
 * Created: 2023-11-13 ¿ÀÀü 9:09:17
 * Author: wjdgh
 */

#include <mega128a.h>
#include <delay.h>

const unsigned char seg_pat[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void main(void)
{
    unsigned char old_key, new_key, num = 0;
    
    DDRB = DDRB | 0xF0;
    DDRD = DDRD | 0xF0;
    DDRG = DDRG | 0x0F;
    DDRE = DDRE & 0xF0;
    
    PORTB = 0x00;
    PORTD = 0x00;
    PORTG = 0b00001000;
    
    old_key = PINE & 0b00010000;
    
    while(1)
    {
        new_key = PINE & 0b00110000;
                
        if((old_key == 0x30) && (new_key == 0x20)) num = (num + 1) % 10;
        if((old_key == 0x30) && (new_key == 0x10))
        {
            if(num == 0) num = 9;
            else num --;
        }
                
        old_key = new_key;
                
        PORTD = ((seg_pat[num] & 0x0F) << 4) | (PORTD & 0x0F);
		PORTB = (seg_pat[num] & 0x70) | (PORTB & 0x0F);
		
	} // end of while
}





