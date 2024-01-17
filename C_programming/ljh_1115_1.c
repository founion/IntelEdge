#include <mega128a.h>
#include <delay.h>

typedef unsigned char U;

flash U seg_pat[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
U N1 = 0, N10 = 0, N100 = 0, N1000 = 0;
U pos = 0;
U hour = 12, min = 0, sec = 0;

U TIMER0_OVF_INT_BIT = 0;
U EINT4_FLAG_BIT = 0;
U EINT5_FLAG_BIT = 0;
U EINT6_FLAG_BIT = 0;
U EINT7_FLAG_BIT = 0;

unsigned short cnt = 0;

void Time_out(void);

void main(void)
{
    DDRB |= 0xF0;
    DDRD |= 0xF0;
    DDRG |= 0x0F;
    
    PORTB = 0x00;
    PORTD = 0x00;
    
    EIMSK = 0b11110000;
    EICRB = 0b10101111;
    
    TIMSK = 0x01; // 0b 0000 0001
    
    TCCR0 = 0x06; // 0b 0000 0110
    TCNT0 = 131;  // 2ms -> 500회   
    
    SREG |= 0x80;
    
    while(1)
    {
        Time_out();
        
        if(TIMER0_OVF_INT_BIT == 1)
        {
            TIMER0_OVF_INT_BIT = 0;           
        }
                       
        if(cnt >= 500)
        {
            cnt = 0;
            sec++;
            if(sec == 60)
            {
                sec = 0;
                min++;
                if(min == 60)
                {
                    min = 0;
                    hour = (hour + 1) % 24;
                }
            }
        }    
        
        
        if(EINT4_FLAG_BIT == 1)
        {
            EINT4_FLAG_BIT = 0;
            
            N1 = min % 10;
            N10 = min / 10;
            N100 = hour % 10;
            N1000 = hour / 10;
            
            if(pos == 0) N1 = (N1 + 1) % 10;
            else if(pos == 1) N10 = (N10 + 1) % 6;
            else if(pos == 2)
            {
                if(N1000 == 2) N100 = (N100 + 1) % 4;
                else N100 = (N100 + 1) % 10;
            }
            else
            {
                if(N100 > 4) N1000 = (N1000 + 1) % 2;
                else N1000 = (N1000 + 1) % 3;
            }
            
            hour = N1000 * 10 + N100;
            min = N10 * 10 + N1;                
        } // end of EINT4
        
        if(EINT5_FLAG_BIT == 1)
        {
            EINT5_FLAG_BIT = 0;
            
            N1 = min % 10;
            N10 = min / 10;
            N100 = hour % 10;
            N1000 = hour / 10;
            
            if(pos == 0)
            {
                if(N1 == 0) N1 = 9;
                else N1--;
            }
            else if(pos == 1)
            {
                if(N10 == 0) N10 = 5;
                else N10--;
            }
            else if(pos == 2)
            {
                if(N1000 == 2)
                { 
                    if(N100 == 0) N100 = 3;
                    else N100--;
                }
                else
                {
                    if(N100 == 0) N100 = 9;
                    else N100--;
                }
            }
            else
            {
                if(N100 > 4)
                {
                    if(N1000 == 0) N1000 = 1;
                    else N1000--;
                }
                else 
                {
                    if(N1000 == 0) N1000 = 2;
                    else N1000--;
                }
            }
            
            hour = N1000 * 10 + N100;
            min = N10 * 10 + N1;                
        } // end of EINT5
        
        if(EINT6_FLAG_BIT == 1)
        {
            EINT6_FLAG_BIT = 0;
            
            pos = (pos + 1) % 4;
        } // end of EINT6
        
        if(EINT7_FLAG_BIT == 1)
        {
            EINT7_FLAG_BIT = 0;
            
            if(pos == 0) pos = 3;
            else pos--;
        } // end of EINT7   
    } // end of while
}

interrupt [TIM0_OVF] void timer_int0(void)
{    
    TCNT0 = 131;
    
    cnt++;             // 한번더 초기화
    
    SREG &= 0x7F;            // 다른 인터럽트 허용x
    
    TIMER0_OVF_INT_BIT = 1;
    
    SREG |= 0x80;            // 다른 인터럽트 허용    
}

interrupt [EXT_INT4] void external_in4(void)
{
    SREG &= 0x7F;      // 다른 인터럽트 허용x
    
    EINT4_FLAG_BIT = 1;
    
    SREG |= 0x80;      // 다른 인터럽트 허용
}

interrupt [EXT_INT5] void external_in5(void)
{
    SREG &= 0x7F;      // 다른 인터럽트 허용x
    
    EINT5_FLAG_BIT = 1; 
    
    SREG |= 0x80;      // 다른 인터럽트 허용
}

interrupt [EXT_INT6] void external_in6(void)
{
    SREG &= 0x7F;      // 다른 인터럽트 허용x
    
    EINT6_FLAG_BIT = 1;
    
    SREG |= 0x80;      // 다른 인터럽트 허용
}

interrupt [EXT_INT7] void external_in7(void)
{
    SREG &= 0x7F;      // 다른 인터럽트 허용x
    
    EINT7_FLAG_BIT = 1; 
    
    SREG |= 0x80;      // 다른 인터럽트 허용
}

void Time_out(void)
{
    PORTG = 0b00001000;
    PORTD = ((seg_pat[min % 10] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (seg_pat[min % 10] & 0x70) | (PORTB & 0x0F);
    if(pos == 0) PORTB |= 0x80;
    delay_ms(5);
    
    PORTG = 0b00000100;
    PORTD = ((seg_pat[min / 10] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (seg_pat[min / 10] & 0x70) | (PORTB & 0x0F);
    if(pos == 1) PORTB |= 0x80;
    delay_ms(5);
    
    PORTG = 0b00000010;
    PORTD = ((seg_pat[hour % 10] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (seg_pat[hour % 10] & 0x70) | (PORTB & 0x0F);
    if(pos == 2) PORTB |= 0x80;
    delay_ms(5);
    
    PORTG = 0b00000001;
    PORTD = ((seg_pat[hour / 10] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (seg_pat[hour / 10] & 0x70) | (PORTB & 0x0F);
    if(pos == 3) PORTB |= 0x80;
    delay_ms(5);
}