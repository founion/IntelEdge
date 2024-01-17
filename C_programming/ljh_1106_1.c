/*
 * ljh_1106_1.c
 *
 * Created: 2023-11-06 ¿ÀÀü 8:53:34
 * Author: wjdgh
 */  
 
#include <mega128a.h>
#include <delay.h>

void main(void)
{
    unsigned char old_sw, new_sw;
    
    DDRC = 0xFF;
    DDRE = 0x00;
    
    
               
    old_sw = PINE & 0b11110000;
    while (1)
    {
        PORTC = 0xFF;
        new_sw = PINE & 0b11110000;
        if((old_sw == 0xF0) && (new_sw == 0xE0))
        {
            PORTC = 0x0F;
            delay_ms(500);
            PORTC = 0xFF;
        }                
        if((old_sw == 0xF0) && (new_sw == 0xD0))
        {
            PORTC = 0xF0;
        }
        if((old_sw == 0xF0) && (new_sw == 0xB0))
        {
            PORTC = 0x3C;
        }
        if((old_sw == 0xF0) && (new_sw == 0x70))
        {
			PORTC = 0x00;
		}
    } //end of while
	
	old_sw = new_sw;
} // end of main