/***************************************************/
/* project : 2                                     */

/* Name : Lee JeongHwan                            */
/* Modify: 2023-11-21                              */
/* Date : 2023-11-20                               */
/* Description :                                   */
/***************************************************/

#include <mega128a.h>
#include <delay.h>

typedef unsigned char U8;
typedef unsigned int I32;

U8 EINT4_FLAG_BIT = 0;
U8 EINT5_FLAG_BIT = 0;
U8 EINT6_FLAG_BIT = 0;
U8 EINT7_FLAG_BIT = 0;
U8 TIMER0_OVF_INT_BIT = 0;
U8 TIMER2_OVF_INT_BIT = 0;
U8 TIMER1_CTC_INT_BIT = 0;
U8 ADC_FLAG = 0;
U8 N1000 = 0, N100 = 0, N10 = 0, N1 = 0;
U8 V100 = 0, V10 = 0, V1 = 0;

flash U8 seg_pat[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; 

I32 cnt_0 = 0, cnt_2 = 0, cntt_2 = 0, cnt_1 = 0, cntt_1 = 0;
I32 ad_val, ad_V_val;

void Display(U8 N1000, U8 N100, U8 N10, U8 N1);
void Display_alltime(U8 N1000, U8 N100, U8 N10, U8 N1);
void Timer0_set(void);
void Timer1_set(void);
void AD_T_disp(int);
void AD_V_disp(int);
void PWM_mode6(void);
void PWM_mode2(void);
void UART_volt(void);
void UART_stop(void);
void Putch(U8 data);

void main(void)
{
    DDRB |= 0xF0;
    DDRD |= 0xF0;
    DDRG |= 0x0F;
        
    Display(2, 0, 2, 3);
    Display(0, 5, 2, 0);  
    
    EIMSK = 0b11110000;
    EICRB = 0b10111011; // 7(10) : falling, 6(11) : rising, 5(10) : falling, 4(11) : rising
       
    SREG |= 0x80;
                
    while(1)
    {
        if(ADC_FLAG != 1) Display_alltime(0, 5, 2, 0);
        else AD_T_disp(ad_val);
                
        if(EINT4_FLAG_BIT == 1)
        {
            EINT4_FLAG_BIT = 0; 
            ADC_FLAG = 1;
            
            Timer0_set();
        } 
        
        if(EINT5_FLAG_BIT == 1)
        {
            EINT5_FLAG_BIT = 0;
                      
            Timer1_set();
        } 
        
        if(EINT6_FLAG_BIT == 1)
        {
            EINT6_FLAG_BIT = 0;
            ADC_FLAG = 0;
                       
            TCCR0 = 0x06; // 0b 0000 0110 256분주 
            TCNT0 = 6; // 4ms
            
            TIMSK = 0x01; // 0b 0000 0001 timer0 + overflow mode          
        } 
        
        if(EINT7_FLAG_BIT == 1)
        {
            EINT7_FLAG_BIT = 0;

            PWM_mode2();
        }
        
        if(TIMER0_OVF_INT_BIT == 1)
        {
            TIMER0_OVF_INT_BIT = 0;
            
            PWM_mode6();
                                    
            cnt_0++;           
            if(cnt_0 >= 2500)
            {
                TCCR3B &= 0xF8;
                TIMSK &= 0x00;
                
                UART_stop();                
                        
                cnt_0 = 0;
            }             
        }   
        
        
        if(TIMER2_OVF_INT_BIT == 1)
        {
            TIMER2_OVF_INT_BIT = 0;
                
            cnt_2++;
                       
            if(cnt_2 >= 130) // 4 * 1300 = 5200ms
            {
                ADMUX = 0x07;  // 0b 0000 0111 -> ADC7사용  
                ADCSRA = 0x87; // 0b 1000 0111 -> 128분주 사용  
                delay_ms(5);
                
                ADCSRA = 0xC7; // 0b 1100 0111 -> ADC 시작(6번비트 1)
                while((ADCSRA & 0x10) == 0x00);
                
                ad_val = (int)ADCL + ((int)ADCH << 8); 
                   
                cnt_2 = 0;
                cntt_2++;
            }
            else if(cntt_2 >= 10)
            {
                TIMSK &= 0xBF;
                TCCR2 &= 0xF8;
                ADC_FLAG = 0;
                cntt_2 = 0;
            }
        }  
        
        if(TIMER1_CTC_INT_BIT == 1)
        {
            TIMER1_CTC_INT_BIT = 0; 
            
            cnt_1++;
            
            if(cnt_1 >= 10) // 520ms * 100 = 52000ms
            {
                ADMUX = 0x06;  // 0b 0000 0110 -> ADC6사용  
                ADCSRA = 0x87; // 0b 1000 0111 -> 128분주 사용  
                delay_ms(5);
                
                ADCSRA = 0xC7; // 0b 1100 0111 -> ADC 시작(6번비트 1)
                while((ADCSRA & 0x10) == 0x00);
                
                ad_V_val = (int)ADCL + ((int)ADCH << 8);
                AD_V_disp(ad_V_val);
                
                UART_volt();
                
                cnt_1 = 0;
                cntt_1++;
            }
            else if(cntt_1 >= 10)
            {
                TIMSK &= 0xEF; // 0b 1110 1111 
                TCCR1B &= 0xF8;
                
                ADC_FLAG = 0;
                cntt_1 = 0;
            }
        }                                       
    } // end of while   
}

void Display(U8 N1000, U8 N100, U8 N10, U8 N1)
{    
    U8 i;
    for(i=0;i<150;i++)
    {    
        PORTG = 0x01; // 0b00000001;  
        PORTD = ((seg_pat[N1000] & 0x0F) << 4) | (PORTD & 0x0F);
        PORTB = (seg_pat[N1000] & 0x70) | (PORTB & 0x0F);
        delay_ms(2); 
        
        PORTG = 0x02; // 0b00000010;  
        PORTD = ((seg_pat[N100] & 0x0F) << 4) | (PORTD & 0x0F);
        PORTB = (seg_pat[N100] & 0x70) | (PORTB & 0x0F);
        delay_ms(2);
        
        PORTG = 0x04; // 0b00000100;  
        PORTD = ((seg_pat[N10] & 0x0F) << 4) | (PORTD & 0x0F);
        PORTB = (seg_pat[N10] & 0x70) | (PORTB & 0x0F);
        delay_ms(2);
        
        PORTG = 0x08; // 0b00001000;  
        PORTD = ((seg_pat[N1] & 0x0F) << 4) | (PORTD & 0x0F);
        PORTB = (seg_pat[N1] & 0x70) | (PORTB & 0x0F);
        delay_ms(2); 
    }   
} 

void Display_alltime(U8 N1000, U8 N100, U8 N10, U8 N1)
{
    PORTG = 0x01; // 0b00000001;  
    PORTD = ((seg_pat[N1000] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (seg_pat[N1000] & 0x70) | (PORTB & 0x0F);
    delay_ms(1);
    
    PORTG = 0x02; // 0b00000010;  
    PORTD = ((seg_pat[N100] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (seg_pat[N100] & 0x70) | (PORTB & 0x0F);
    delay_ms(1); 
    
    PORTG = 0x04; // 0b00000100;  
    PORTD = ((seg_pat[N10] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (seg_pat[N10] & 0x70) | (PORTB & 0x0F);
    delay_ms(1); 
    
    PORTG = 0x08; // 0b00001000;  
    PORTD = ((seg_pat[N1] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (seg_pat[N1] & 0x70) | (PORTB & 0x0F);
    delay_ms(1); 
} 

void Timer0_set(void)
{
    TCCR2 = 0x04;  // 0b 0000 0100 256분주
    TCNT2 = 6;     // 5200ms / 4ms = 1300 회 
            
    TIMSK = 0x40;  // 0b 0100 0000 timer2 + overflow mode
}

void Timer1_set(void)
{
    TCCR1A = 0x00;
    TCCR1B = 0x0C; // 0b 0000 1100 ctc mode -> TCCRnB에서 4번비트 3번비트 : 0 1, 256분주
    TCCR1C = 0x00;
            
    TCNT1H = 0x00;
    TCNT1L = 0x00;
    OCR1AH = 0x7E; // 32499 -> 0x7EF3 => 520ms
    OCR1AL = 0xF3;
            
    TIMSK = 0x10;  // 0b 0001 0000 timer1 + ctc A mode
}

void AD_T_disp(int val)
{
    float fval;
    int ival, buf;
    U8 N100, N10, N1; 
    
    fval = (float)val * 5.0 / 1024.0;    // 정수화
    ival = (int)(fval * 1000.0); // 3자리 만들기 
    
    N100 = ival / 100;
    buf = ival % 100;
    N10 = buf / 10;
    N1 = buf % 10;
    
    PORTG = 0x08; // 0b00001000;  
    PORTD = ((seg_pat[N1] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (seg_pat[N1] & 0x70) | (PORTB & 0x0F);
    delay_ms(1); 
    
    PORTG = 0x04; // 0b00000100;  
    PORTD = ((seg_pat[N10] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (seg_pat[N10] & 0x70) | (PORTB & 0x0F);
    PORTB |= 0x80;
    delay_ms(1);  
    
    PORTG = 0x02; // 0b00000010;  
    PORTD = ((seg_pat[N100] & 0x0F) << 4) | (PORTD & 0x0F);
    PORTB = (seg_pat[N100] & 0x70) | (PORTB & 0x0F);
    delay_ms(1);
} // end of AD_disp 

void AD_V_disp(int val)
{
    float fVval;
    int iVval, Vbuf;
    
    fVval = (float)val * 5.0 / 1024.0;    // 정수화
    iVval = (int)(fVval * 100.0); // 3자리 만들기 
    
    V100 = iVval / 100;
    Vbuf = iVval % 100;
    V10 = Vbuf / 10;
    V1 = Vbuf % 10;
} 

void PWM_mode6(void)
{
    TCCR3A = 0x82; // 0b 1000 0010
    TCCR3B = 0x0A; // 0b 0000 1010 -> 8분주
    TCCR3C = 0x00;
            
    TCNT3H = 0x00;
    TCNT3L = 0x00;
            
    OCR3AH = 0x66;                
    OCR3AL = 0x99;
            
    DDRE |= 0x08;
}

void UART_volt(void)
{
    UCSR0A = 0x00;        
    UCSR0B = 0b00001000; 
    UCSR0C = 0b00000110; 
    UBRR0H = 0;          
    UBRR0L = 103;
                
    while((UCSR0A & 0x20) == 0x00);
    UDR0 = V100 + 0x30;
    while((UCSR0A & 0x20) == 0x00);
    UDR0 = '.';
    while((UCSR0A & 0x20) == 0x00);
    UDR0 = V10 + 0x30;
    while((UCSR0A & 0x20) == 0x00);
    UDR0 = V1 + 0x30;
    while((UCSR0A & 0x20) == 0x00);
    UDR0 = 'V';
    while((UCSR0A & 0x20) == 0x00);
    UDR0 = ' '; 
}        

void UART_stop(void)
{
    U8 string[] = "PWM mode 6 is stopped!\r";
    U8 *pStr;
    
    delay_ms(7000);
    UCSR0A = 0x00;
    UCSR0B = 0b00001000;
    UCSR0C = 0b00000110;
    UBRR0H = 0;
    UBRR0L = 103;
    
    pStr = string;
    while(*pStr != 0) Putch(*pStr++);
}

void Putch(U8 data)
{
    while((UCSR0A & 0x20) == 0x00);
    UDR0 = data;
}

void PWM_mode2(void)
{
    TCCR3B &= 0xF8;
    delay_ms(500);
            
    TCCR3A = 0x82; // 0b 1000 0010
    TCCR3B = 0x02; // 0b 0000 0010 -> 8분주
    TCCR3C = 0x00;
            
    TCNT3H = 0x00;
    TCNT3L = 0x00;
            
    OCR3AH = 0x66;                
    OCR3AL = 0x99;
            
    DDRE |= 0x08;
}

interrupt [EXT_INT4] void external_in4(void)
{
    SREG &= 0x7F; 
    
    EINT4_FLAG_BIT = 1;
    
    SREG |= 0x80; 
}

interrupt [EXT_INT5] void external_in5(void)
{
    SREG &= 0x7F; 
    
    EINT5_FLAG_BIT = 1;
    
    SREG |= 0x80; 
}

interrupt [EXT_INT6] void external_in6(void)
{
    SREG &= 0x7F; 
    
    EINT6_FLAG_BIT = 1;
    
    SREG |= 0x80; 
}

interrupt [EXT_INT7] void external_in7(void)
{
    SREG &= 0x7F; 
    
    EINT7_FLAG_BIT = 1;
    
    SREG |= 0x80; 
}

interrupt [TIM0_OVF] void timer_int0(void)
{
    TCNT0 = 6; 
    
    SREG &= 0x7F; 
    
    TIMER0_OVF_INT_BIT = 1;
    
    SREG |= 0x80;   
}

interrupt [TIM2_OVF] void timer_int2(void)
{
    TCNT2 = 6; 
    
    SREG &= 0x7F; 
    
    TIMER2_OVF_INT_BIT = 1;
    
    SREG |= 0x80;   
}

interrupt [TIM1_COMPA] void timer_int1(void)
{
    TCNT1H = 0x00;
    TCNT1L = 0x00;
    
    SREG &= 0x7F;            
    
    TIMER1_CTC_INT_BIT = 1;
    
    SREG |= 0x80;            
}

