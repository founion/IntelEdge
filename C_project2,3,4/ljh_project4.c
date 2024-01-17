/***************************************************/
/* project : 4                                     */

/* Name : Lee JeongHwan                            */
/* Modify: 2023-11-22                              */
/* Date : 2023-11-22                               */
/* Description : project4                          */
/***************************************************/

#include <mega128a.h>
#include <delay.h>

#define SCL_OUT DDRD |= 0x01   // PD.0=1 Ŭ�� ��� 
#define SDA_OUT DDRD |= 0x02   // PD.1=1 ������ ���
#define LD_OUT DDRD |= 0x04   // PD.2=1 LD ��� 
 
#define CLK_HIGH PORTD |= 0x01 // PD.0=1 Ŭ�� 1 
#define CLK_LOW PORTD &= 0xFE  // PD.0=0 Ŭ�� 0 
#define DAT_HIGH PORTD |= 0x02 // PD.1=1 ������ 1  
#define DAT_LOW PORTD &= 0xFD  // PD.1=0 ������ 0
#define LD_HIGH PORTD |= 0x04  // PD.2=1 LD 1
#define LD_LOW PORTD &= 0xFB   // PD.2=0 LD 0

#define n 21

typedef unsigned char U8;
typedef unsigned short U16;

U8 EINT4_FLAG_BIT = 0;

flash U16 array[n] = {0x0000, 0x001A, 0x0034, 0x004D, 0x0067, 0x0080, 0x009A, 0x00B4, 0x00CD, 0x00E7, 0x00FF, 0x00E7, 0x00CD, 0x00B4, 0x009A, 0x0080, 0x0067, 0x004D, 0x0034, 0x001A, 0x0000};
U8 i;

void Process_write(U16 value);
void DAC(void);

void main(void)
{    
    DDRC = 0xFF;
    PORTC = 0xFF;
    
    EIMSK |= 0b00010000;
    EICRB |= 0b00000010;
        
    SREG |= 0x80;
    
    LD_OUT;
    SCL_OUT;
    SDA_OUT;
    
    while (1)
    {        
        if(EINT4_FLAG_BIT == 1)
        {
            EINT4_FLAG_BIT = 0;
            
            PORTC = 0xFE;
                      
            DAC();
            
            delay_ms(100);
            
            PORTC = 0xFF;                       
        }   
    }
}

void Process_write(U16 value)  // Bytewrite 16��Ʈ ������ ���� �Լ�
{
    U8 i_write;                // 16��Ʈ ������ ���ֱ� ���� �ݺ��� ����
    U16 value_buffer;          // �� ������ ���۰�
    
    value_buffer = value; 
        
    for(i_write=0;i_write<10;i_write++)    // 10��Ʈ ������ ���ֱ� ���� �ݺ���
    {  
        CLK_LOW;
        delay_us(6);
        
        if((value_buffer & 0x200) == 0x200) DAT_HIGH;
        else DAT_LOW;
        
        value_buffer = value_buffer << 1; // MSB -> LSB���� �ϳ��� shift
        
        delay_ms(6);
        
        CLK_HIGH;
          
        delay_us(12);
        
        CLK_LOW; 
        
        delay_ms(6);   
    } // end of for 
}

void DAC(void)
{    
    for(i=0;i<21;i++)
    {
        LD_LOW;
        
        Process_write(array[i]);
        
        LD_HIGH;
    }
}

interrupt [EXT_INT4] void external_in4(void)
{
    SREG &= 0x7F; 
    
    EINT4_FLAG_BIT = 1;
    
    SREG |= 0x80; 
}    