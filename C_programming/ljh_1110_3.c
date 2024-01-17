/*
 * ljh_1110_3.c
 *
 * Created: 2023-11-10 ¿ÀÈÄ 4:11:14
 * Author: wjdgh
 */

#include <mega128a.h>
#include <delay.h>

typedef unsigned char U8;

const unsigned char birth[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void Seg4_out(U8 N1, U8 N2, U8 N3, U8 N4);

void main(void)
{
    DDRB = DDRB | 0xF0;
    DDRD = DDRD | 0xF0;
    DDRG = DDRG | 0x0F;
    
    PORTB = 0x00;
    PORTD = 0x00;
    
    while (1)
    { 
        Seg4_out(1,9,9,8);
        delay_ms(500);
        Seg4_out(0,5,2,0);
        delay_ms(1000);             
    } 
}

void Seg4_out(U8 N1, U8 N2, U8 N3, U8 N4)
{
    PORTG = 0b00000001;
    PORTD = ((birth[N1] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (birth[N1] & 0x70) | (PORTB & 0x0F);
    delay_ms(500); 
    
    PORTG = 0b00000010;
    PORTD = ((birth[N2] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (birth[N2] & 0x70) | (PORTB & 0x0F);
    delay_ms(500);
    
    PORTG = 0b00000100;
    PORTD = ((birth[N3] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (birth[N3] & 0x70) | (PORTB & 0x0F);
    delay_ms(500);
    
    PORTG = 0b00001000;
    PORTD = ((birth[N4] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (birth[N4] & 0x70) | (PORTB & 0x0F);
    delay_ms(500);
}
