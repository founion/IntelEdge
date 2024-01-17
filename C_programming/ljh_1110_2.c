/*
 * ljh_1110_2.c
 *
 * Created: 2023-11-10 ¿ÀÈÄ 3:23:25
 * Author: wjdgh
 */

#include <mega128a.h>
#include <delay.h>

const unsigned char seg_pat[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

void Seg4_out(int);

void main(void)
{
    int num = 0;
    
    DDRB = DDRB | 0xF0;
    DDRD = DDRD | 0xF0;
    DDRG = DDRG | 0x0F;
    
    PORTB = 0x00;
    PORTD = 0x00;
    
    while (1)
    {
        Seg4_out(num);
        num++;
        if(num > 0xFFFF) num = 0x00;    
    } // end of while
} // end of main

void Seg4_out(int num)
{
    int i, N1000, N100, N10, N1, buf;
    
    N1000 = num / 0x1000;
    buf = num % 0x1000;
    
    N100 = buf / 0x100;
    buf = buf % 0x100;
    
    N10 = buf / 0x10;
    N1 = buf % 0x10;
    
    for(i=0;i<49;i++)
    {
        PORTG = 0b00001000;
        PORTD = ((seg_pat[N1] & 0x0F) << 4) | (PORTD & 0x0f);
        PORTB = (seg_pat[N1] & 0x70) | (PORTB & 0x0F);
        delay_ms(7);
        
        PORTG = 0b00000100;
        PORTD = ((seg_pat[N10] & 0x0F) << 4) | (PORTD & 0x0f);
        PORTB = (seg_pat[N10] & 0x70) | (PORTB & 0x0F);
        delay_ms(7);
        
        PORTG = 0b00000010;
        PORTD = ((seg_pat[N100] & 0x0F) << 4) | (PORTD & 0x0f);
        PORTB = (seg_pat[N100] & 0x70) | (PORTB & 0x0F);
        delay_ms(7);
        
        PORTG = 0b00000001;
        PORTD = ((seg_pat[N1000] & 0x0F) << 4) | (PORTD & 0x0f);
        PORTB = (seg_pat[N1000] & 0x70) | (PORTB & 0x0F);
        delay_ms(7);
    } // end of for
} // end of Seg4_out
