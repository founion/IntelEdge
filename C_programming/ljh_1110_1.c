/*
 * ljh_1110_1.c
 *
 * Created: 2023-11-10 ¿ÀÈÄ 2:02:04
 * Author: wjdgh
 */

#include <mega128a.h>
#include <delay.h>

void main(void)
{
    unsigned char i, i_g;
    const unsigned char value[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    DDRB = DDRB |= 0xF0;
    DDRD = DDRD |= 0xF0;
    DDRG = DDRG |= 0x0F; 
    
    PORTD = 0x00;
    PORTB = 0x00;
    
    
    while (1)
    {
        PORTG = 0x08;
        for(i_g=0;i_g<4;i_g++)
        {
                   
            for(i=0;i<16;i++)
            {
                PORTD = ((value[i] & 0x0F) << 4) /*| (PORTD & 0x0F)*/;
                PORTB = (value[i] & 0xF0) /*| (PORTB & 0x0F)*/;
                delay_ms(500);
                
            } // end of for
            PORTG = PORTG >> 1; 
        }              
    } // end of while
} // end of main
