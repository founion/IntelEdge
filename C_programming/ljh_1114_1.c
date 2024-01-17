/*
 * ljh_1114_1.c
 *
 * Created: 2023-11-14 ���� 9:05:06
 * Author: wjdgh
 */

#include <mega128a.h>

typedef unsigned char U;

U EINT4_FLAG_BIT = 0;
U EINT5_FLAG_BIT = 0;
U EINT6_FLAG_BIT = 0;
U EINT7_FLAG_BIT = 0;
U TIMER0_OVF_INT_BIT = 0;
U TIMER2_CMP_INT_BIT = 0;
U led = 0xFF;
U cnt_0 = 0;
U cnt_2 = 0;

void main(void)
{
    DDRC = 0xFF;
    PORTC = led;
    
    EIMSK = 0b11110000; // �ܺ� ���ͷ�Ʈ4,5,6,7 enable
    EICRB = 0b11101110; // �ܺ� ���ͷ�Ʈ7 rising, 6 falling, 5 rising, 4 falling
    
    SREG |= 0x80;             
    
    while (1)
    {
        if(EINT4_FLAG_BIT == 1)
        {   
            EINT4_FLAG_BIT = 0;
            
            TIMSK = 0x80; // external interrupt4 �߻� -> 0b 1000 0000 (timer2 : ctc mode)
    
            TCCR2 = 0x0D; // 0b 0000 1101 -> ctc, 1024����
            TCNT2 = 0; // Ÿ�̸�ī��Ʈ 0 (0�̸� ���ͷ�Ʈ���� �缳�� ��������)
            OCR2 = 109;   // OCR2 109 -> 7.04ms
        }
        
        if(EINT5_FLAG_BIT == 1)
        {
            EINT5_FLAG_BIT = 0;
            
            TCCR2 &= 0xF8; // external interrupt5 �߻� -> & ���� �� TTCR2�� 0,1,2�� ��Ʈ�� ���� 0�� �ǹǷ� clock�� �Է�����(Ÿ�̸�/ī���� ����)
            
            PORTC = 0xFF;  // Ÿ�̸�/ī���� ������ LED Off
        }
        
        if(EINT6_FLAG_BIT == 1)
        {   
            EINT6_FLAG_BIT = 0;
            
            TIMSK = 0x01; // external interrupt6 �߻� -> 0b 000 0001 (timer0 : ovf mode)
    
            TCCR0 = 0x05; // 0b 0000 0101 -> ovf, 128����
            TCNT0 = 94; // Ÿ�̸�ī��Ʈ 94 (0�̸� ���ͷ�Ʈ���� �缳�� ��������) -> 1.296ms           
        }
        
        if(EINT7_FLAG_BIT == 1)
        {
            EINT7_FLAG_BIT = 0;
            
            TCCR0 &= 0xF8; // external interrupt7 �߻� -> & ���� �� TTCR2�� 0,1,2�� ��Ʈ�� ���� 0�� �ǹǷ� clock�� �Է�����(Ÿ�̸�/ī���� ����)
            
            PORTC = 0xFF;  // Ÿ�̸�/ī���� ������ LED Off
        }
        
        if(TIMER0_OVF_INT_BIT == 1)
        {
            TIMER0_OVF_INT_BIT = 0;
            
            cnt_0++;
            
            if(cnt_0 == 100)      // 130[ms] / 1.296[ms] = �� 100
            {        
                PORTC = 0xF0; 
                cnt_0 = 101;
            }
            else if(cnt_0 == 200) // 130[ms] / 1.296[ms] = �� 100
            {
                PORTC = 0x0F;
                cnt_0 = 0;
            }
        }               
        
        if(TIMER2_CMP_INT_BIT == 1)
        {
            TIMER2_CMP_INT_BIT = 0;  
            
            cnt_2++;
            
            if(cnt_2 == 100)       // 704[ms] / 7.04[ms] = 100
            {
                PORTC = 0xAA;
                cnt_2 = 101;
            }
            else if(cnt_2 == 200)  // 704[ms] / 7.04[ms] = 100
            {
                PORTC = 0x55;
                cnt_2 = 0;
            }
        }
    } // end of while
}

interrupt [TIM0_OVF] void timer_int0(void)
{    
    TCNT0 = 94;              // �ѹ��� �ʱ�ȭ
    
    SREG &= 0x7F;            // �ٸ� ���ͷ�Ʈ ���x
    
    TIMER0_OVF_INT_BIT = 1;
    
    SREG |= 0x80;            // �ٸ� ���ͷ�Ʈ ���    
}

interrupt [TIM2_COMP] void timer_int2(void)
{
    TCNT2 = 0;               // ���������� �ۼ�����
    
    SREG &= 0x7F;            // �ٸ� ���ͷ�Ʈ ���x
    
    TIMER2_CMP_INT_BIT = 1;
    
    SREG |= 0x80;            // �ٸ� ���ͷ�Ʈ ���    
}

interrupt [EXT_INT4] void external_in4(void)
{
    SREG = SREG & 0x7F;
    
    EINT4_FLAG_BIT = 1;
    
    SREG = SREG | 0x80;
}

interrupt [EXT_INT5] void external_in5(void)
{
    SREG = SREG & 0x7F;
    
    EINT5_FLAG_BIT = 1; 
    
    SREG = SREG | 0x80;
}

interrupt [EXT_INT6] void external_in6(void)
{
    SREG = SREG & 0x7F;
    
    EINT6_FLAG_BIT = 1;
    
    SREG = SREG | 0x80;
}

interrupt [EXT_INT7] void external_in7(void)
{
    SREG = SREG & 0x7F;
 
    EINT7_FLAG_BIT = 1;
    
    SREG = SREG | 0x80;
}