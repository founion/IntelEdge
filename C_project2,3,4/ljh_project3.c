/***************************************************/
/* project : 3                                     */

/* Name : Lee JeongHwan                            */
/* Modify: 2023-11-22                              */
/* Date : 2023-11-22                               */
/* Description : project2에 UART 조작 추가            */
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
U8 TIMER0_CMP_INT_BIT = 0;
U8 TIMER2_OVF_INT_BIT = 0;
U8 TIMER1_CTC_INT_BIT = 0;

U8 ADC_FLAG = 0;
U8 N1000 = 0, N100 = 0, N10 = 0, N1 = 0;
U8 V100 = 0, V10 = 0, V1 = 0;

flash U8 seg_pat[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; 

I32 cnt_0 = 0, cntt_0 = 0, cnt_2 = 0, cntt_2 = 0, cnt_1 = 0, cntt_1 = 0;
I32 ad_val = 0, ad_V_val = 0;

void Display(U8 N1000, U8 N100, U8 N10, U8 N1);
void Display_alltime(U8 N1000, U8 N100, U8 N10, U8 N1);
void AD_T_disp(int);
void AD_V_disp(int);
void ADC_T_act(void);
void ADC_V_act(void);
void Timer0_ovf_set(void);
void Timer0_cmp_set(void);
void Timer1_set(void);
void Timer2_set(void);
void PWM_mode6(void);
void PWM_mode6_stop(void);
void PWM_mode2(void);
void PWM_mode2_stop(void);
void UART_mode6_stop(void);
void UART_mode2_stop(void);
void measure_stop(void);
void UART_volt(void);
void Putch(U8 data);


void main(void)
{   
    U8 sentence[] = "The UART program mode\rExternal Interrupt4 : No 4\rExternal Interrupt5 : No 5\rExternal Interrupt6 : No 6\rExternal Interrupt7 : No 7\rPlease press the number : ";
    U8 *pStr;
    
    DDRC = 0xFF;
    PORTC = 0xFF;
    DDRB |= 0xF0;
    DDRD |= 0xF0;
    DDRG |= 0x0F;     

    UCSR0A = 0x00;
    UCSR0B = 0x18; // 0b 0001 1000, 4번비트 1 : UART 수신, 3번비트 1 : UART 송신
    UCSR0C = 0x06; // 0b 0000 0110   
    UBRR0H = 0;
    UBRR0L = 103;
    
    pStr = sentence; 
    while(*pStr != 0) Putch(*pStr++);
                
    Display(2, 0, 2, 3);
    Display(0, 5, 2, 0);
       
    SREG |= 0x80;
                
    while(1)
    {                
        if(ADC_FLAG != 1) Display_alltime(0, 5, 2, 0);
        else AD_T_disp(ad_val);
                
        //while((UCSR0A & 0x80) == 0x00);
        switch(UDR0)
        {
            case 0x34: EIMSK &= 0x00;
                       EICRB &= 0x00;
                       EIMSK = 0b00010000;
                       EICRB = 0b00000011; 
                       break;
            case 0x35: EIMSK &= 0x00;
                       EICRB &= 0x00;
                       EIMSK = 0b00100000;
                       EICRB = 0b00001000;
                       break;
            case 0x36: EIMSK &= 0x00;
                       EICRB &= 0x00;
                       EIMSK = 0b01000000;
                       EICRB = 0b00110000;
                       break;
            case 0x37: EIMSK &= 0x00;
                       EICRB &= 0x00;
                       EIMSK = 0b10000000;
                       EICRB = 0b10000000;
                       break;
                       
            default:break;
        } 
                
        if(EINT4_FLAG_BIT == 1)
        {
            EINT4_FLAG_BIT = 0; 
            ADC_FLAG = 1;
            
            Timer2_set();
        } 
        
        if(EINT5_FLAG_BIT == 1)
        {
            EINT5_FLAG_BIT = 0;
                      
            Timer1_set();
        } 
        
        if(EINT6_FLAG_BIT == 1)
        {
            EINT6_FLAG_BIT = 0;
                       
            Timer0_ovf_set();          
        } 
        
        if(EINT7_FLAG_BIT == 1)
        {
            EINT7_FLAG_BIT = 0;
                        
            TCCR3B &= 0xF8;
            delay_ms(5);

            Timer0_cmp_set();
        }
        
        if(TIMER0_OVF_INT_BIT == 1)
        {
            TIMER0_OVF_INT_BIT = 0;
            
            PWM_mode6();
                                    
            PWM_mode6_stop();            
        }
        
        if(TIMER0_CMP_INT_BIT == 1)
        {
            TIMER0_CMP_INT_BIT = 0;
            
            PWM_mode2(); 
            
            PWM_mode2_stop();
        }           
        
        if(TIMER2_OVF_INT_BIT == 1)
        {
            TIMER2_OVF_INT_BIT = 0;
                
            ADC_T_act();
        }  
        
        if(TIMER1_CTC_INT_BIT == 1)
        {
            TIMER1_CTC_INT_BIT = 0; 
            
            ADC_V_act();
        }                                       
    } // end of while   
}

/* 지금부터 함수 */
void Display(U8 N1000, U8 N100, U8 N10, U8 N1) // 학번 표시 7-Segment
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

void Display_alltime(U8 N1000, U8 N100, U8 N10, U8 N1) // 생일 표시 7-Segment
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

void AD_T_disp(int val) // 측정 온도 7-Segment에 표시
{
    float fval;
    int ival, buf; 
    
    fval = (float)val * 5.0 / 1024.0; 
    ival = (int)(fval * 1000.0);  
    
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
}  

void AD_V_disp(int val) // 측정 전압 3자리 숫자로 표시
{
    float fVval;
    int iVval, Vbuf;
    
    fVval = (float)val * 5.0 / 1024.0;    
    iVval = (int)(fVval * 100.0); 
    
    V100 = iVval / 100;
    Vbuf = iVval % 100;
    V10 = Vbuf / 10;
    V1 = Vbuf % 10;
}

void ADC_T_act(void) // 온도 측정(0.52초마다 1회씩, 총 10회)
{
    cnt_2++;
                       
    if(cnt_2 >= 130) // 4 * 130 = 520ms
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
            
        measure_stop();
        
        ADC_FLAG = 0;
        cntt_2 = 0;
    }
}

void ADC_V_act(void) // 전압 측정(5.2초마다 1회씩, 총 10회)
{
    cnt_1++;
            
    if(cnt_1 >= 10) // 520ms * 10 = 5200ms
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
        
        measure_stop();
                    
        ADC_FLAG = 0;
        cntt_1 = 0;
    }
}

void Timer0_ovf_set(void) // timer0, overflow mode, 256분주, 4ms
{
    TCCR0 = 0x06; 
    TCNT0 = 6; 
            
    TIMSK = 0x01; 
}

void Timer0_cmp_set(void) // timer0, ctc mode, 256분주, 4ms
{
    TCCR0 = 0x0E; // 0b 0000 1110
    TCNT0 = 0;
    OCR0 = 249;
    
    TIMSK = 0x02; // 0b 0000 0010
}   

void Timer1_set(void) // timer1, ctc A mode, 256분주, 520ms(ocr = 32499)
{
    TCCR1A = 0x00;
    TCCR1B = 0x0C; 
    TCCR1C = 0x00;
            
    TCNT1H = 0x00;
    TCNT1L = 0x00;
    OCR1AH = 0x7E; 
    OCR1AL = 0xF3;
            
    TIMSK = 0x10;  
}

void Timer2_set(void) // timer2, overflow mode, 256분주, 4ms 
{
    TCCR2 = 0x04;  
    TCNT2 = 6;      
            
    TIMSK = 0x40;  
}

void PWM_mode6(void) // 8분주, duty ratio 20%
{
    TCCR3A = 0x82; 
    TCCR3B = 0x0A; 
    TCCR3C = 0x00;
            
    TCNT3H = 0x00;
    TCNT3L = 0x00;
            
    OCR3AH = 0x66;                
    OCR3AL = 0x99;
            
    DDRE |= 0x08;
}

void PWM_mode6_stop(void) // 10초 이후에 정지
{
    cnt_0++;           
    if(cnt_0 >= 2500)
    {
        TCCR3B &= 0xF8;
        TIMSK &= 0x00;
                    
        UART_mode6_stop();
        
        measure_stop();        
                           
        cnt_0 = 0;
    } 
}

void PWM_mode2(void) // 8분주, duty ratio 20%
{            
    TCCR3A = 0x82; 
    TCCR3B = 0x02; 
    TCCR3C = 0x00;
            
    TCNT3H = 0x00;
    TCNT3L = 0x00;
            
    OCR3AH = 0x66;                
    OCR3AL = 0x99;
            
    DDRE |= 0x08;
}

void PWM_mode2_stop(void) // 8초 이후에 정지
{
    cntt_0++;           
    if(cntt_0 >= 2000)
    {
        TCCR3B &= 0xF8;
        TIMSK &= 0x00;
                    
        UART_mode2_stop();
        
        measure_stop();                
                            
        cntt_0 = 0;
    } 
}  

void UART_mode6_stop(void) // PWM 정지 UART 표시
{
    U8 string1[] = "PWM (mode6) is stopped!.\r";
    U8 *pStr1;
    
    UCSR0A &= 0x00;
    UCSR0B = 0b00001000;
    UCSR0C = 0b00000110;
    UBRR0H = 0;
    UBRR0L = 103;
    
    delay_ms(5);
    pStr1 = string1;
    while(*pStr1 != 0) Putch(*pStr1++);
}

void UART_mode2_stop(void) // PC PWM 정지 UART 표시
{
    U8 string2[] = "PC PWM (mode2) is stopped!.\r";
    U8 *pStr2;
    
    delay_ms(5);
    UCSR0A &= 0x00;
    UCSR0B = 0b00001000;
    UCSR0C = 0b00000110;
    UBRR0H = 0;
    UBRR0L = 103;
    
    pStr2 = string2;
    while(*pStr2 != 0) Putch(*pStr2++);
}

void measure_stop(void) // PWM 정지 UART 표시
{
    U8 stringT[] = "\rCompleted";
    U8 stringP[] = "\rPlease press the number : ";
    U8 *pStrT, *pStrP;
    
    UCSR0A &= 0x00;
    UCSR0B = 0b00001000;
    UCSR0C = 0b00000110;
    UBRR0H = 0;
    UBRR0L = 103;
    
    delay_ms(5);
    pStrT = stringT;
    pStrP = stringP;
    while(*pStrT != 0) Putch(*pStrT++);
    while(*pStrP != 0) Putch(*pStrP++);
    
    UCSR0B = 0x18; // 다음 수신
}  

void UART_volt(void) // 측정 전압 UART 표시
{
    UCSR0A &= 0x00;        
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

void Putch(U8 data)
{
    while((UCSR0A & 0x20) == 0x00);
    UDR0 = data;
}

/* 지금부터 인터럽트 서브루틴 */
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

interrupt [TIM0_OVF] void timer0_int1(void)
{
    TCNT0 = 6; 
    
    SREG &= 0x7F; 
    
    TIMER0_OVF_INT_BIT = 1;
    
    SREG |= 0x80;   
}

interrupt [TIM0_COMP] void timer0_int2(void)
{
    TCNT0 = 0;
    
    SREG &= 0x7F; 
    
    TIMER0_CMP_INT_BIT = 1;
    
    SREG |= 0x80;
}

interrupt [TIM2_OVF] void timer2_int2(void)
{
    TCNT2 = 6; 
    
    SREG &= 0x7F; 
    
    TIMER2_OVF_INT_BIT = 1;
    
    SREG |= 0x80;   
}

interrupt [TIM1_COMPA] void timer1_int1(void)
{
    TCNT1H = 0x00;
    TCNT1L = 0x00;
    
    SREG &= 0x7F;            
    
    TIMER1_CTC_INT_BIT = 1;
    
    SREG |= 0x80;            
}