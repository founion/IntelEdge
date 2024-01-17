#include <mega128a.h>

typedef unsigned char U8;

U8 ch;
U8 USART0_RXC_INT_BIT = 0;

void main(void)
{    
    UCSR0A = 0x00;
    UCSR0B = 0x98; // 0b 1001 1000, 7번비트 1 : 수신 인터럽트, 4번비트 1 : UART 수신, 3번비트 1 : UART 송신
    UCSR0C = 0x06; // 0b 0000 0110   
    UBRR0H = 0;
    UBRR0L = 103;    // Baud rate : 115200으로 설정
    
    SREG |= 0x80;
    
    
    while (1)
    {
        if(USART0_RXC_INT_BIT == 1)
        {
            ch = UDR0;
            USART0_RXC_INT_BIT = 0;
            if(ch >= 'a' && ch <= 'z') ch = ch - 'a' + 'A';
            else if(ch >= 'A' && ch <= 'Z') ch = ch - 'A' + 'a';
            
            while((UCSR0A & 0x20) == 0x00);                                 
            UDR0 = ch;             
        }
    }   
}

interrupt [USART0_RXC] void usart0_rx(void)
{
      USART0_RXC_INT_BIT = 1; 
}