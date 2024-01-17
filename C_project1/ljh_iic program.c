/*                                            */
/* ljh_iic program.c                          */
/*                                            */
/* Created: 2023-11-10 오전 11:12:43           */
/* Author: wjdgh                              */
/*                                            */
/* 1Byte Read & Write Mode(use switch, array) */

#include <mega128a.h>
#include <delay.h>

#define SCL_OUT DDRD |= 0x01   // PD.0=1 클락 출력모드 
#define SDA_OUT DDRD |= 0x02   // PD.1=0 데이터 출력모드 
#define SDA_IN DDRD &= 0xFD    // PD.1=1 데이터 입력모드  

#define CLK_HIGH PORTD |= 0x01 // PD.0=1 클락 1 
#define CLK_LOW PORTD &= 0xFE  // PD.0=0 클락 0 
#define DAT_HIGH PORTD |= 0x02 // PD.1=1 데이터 1  
#define DAT_LOW PORTD &= 0xFD  // PD.1=0 데이터 0
#define n 3                    // 데이터의 수

typedef unsigned char U8;      // 데이터 타입 상수화

U8 i;                          // for문 인수 정의
U8 Dev_Add_W = 0xA0;           // 0b 1010 0000 
U8 Dev_Add_R = 0xA1;           // 0b 1010 0001
U8 IIC_Add = 0xAA;             // 0b 1010 1010
U8 IIC_Data = 0x55;            // 0b 0101 0101
U8 Read_Data = 0;              // 초기화

const U8 IIC_Data_1[n] = {0x55, 0x2D, 0xF0};              // 0b 0101 0101, 0b 0010 1101, 0b 1111 0000

void IIC_START(void);          // START 함수
void IIC_STOP(void);           // STOP 함수
void Process_write(U8 value);  // Bytewrite 8비트 데이터 쓰기
void Process_read(void);       // Randomread 8비트 데이터 받기
void ACK_write(void);          // ACK 함수 slave -> master
/* void ACK_read(void); */     // ACK 함수 master -> slave
void no_ACK(void);             // NACK 함수 master -> slave
void Byte_Write(void);         // Bytewrite 함수
void Random_read(void);        // Randomread 함수 

void main(void)
{
    U8 key, old_sw, new_sw4, new_sw5;  
      
    DDRC = 0xFF;               // 확인을 위한 LED 
    DDRE = 0x00;               // 스위치 초기 설정  
    PORTC = 0xFF;              // 초기 LED 모두 OFF
                
    SCL_OUT;                   // 클락 출력
    SDA_OUT;                   // 데이터 출력
       
    old_sw = PINE & 0xF0;      // PE4 스위치들 상태값 추출     
    
    while(1)
    {
        new_sw4 = PINE & 0x10; // 1번 스위치 
        new_sw5 = PINE & 0x20; // 2번 스위치
        key = ((old_sw != 0) && (new_sw4 == 0))? 4:0;     // 1번 스위치 Falling Edge 판단  
        if(key == 0)
        {
            key = ((old_sw != 0) && (new_sw5 == 0))? 5:0; // 2번 스위치 Falling Edge 판단
        } // end of if
                
        switch(key)
        {
            case 4: PORTC = 0xAA, Byte_Write(), delay_ms(10); break;  // 1번 스위치 Falling Edge이면 LED켜고(10101010) Bytewrite 실행   
            case 5: PORTC = 0x55, Random_read(), delay_ms(10); break; // 2번 스위치 Falling Edge이면 LED켜고(01010101) Randomread 실행

            default: break;
        } // end of switch
    } // end of while
} // end of main   

void IIC_START(void)           // START 함수
{
    DAT_HIGH;
    CLK_HIGH; 
    delay_us(6);
    DAT_LOW;
    CLK_LOW;
} // end of IIC_START
    
void IIC_STOP(void)            // STOP 함수
{
    DAT_LOW;
    CLK_HIGH; 
    delay_us(6);
    DAT_HIGH;
    CLK_LOW;
} // end of IIC_STOP

void Process_write(U8 value)   // Bytewrite 8비트 데이터 쓰기 함수
{
    U8 i_write;                // 8비트 데이터 써주기 이한 반복문 변수
    U8 value_buffer;           // 쓸 데이터 버퍼값
    
    value_buffer = value; 
        
    for(i_write=0;i_write<7;i_write++)    // 7비트 데이터 써주기 위한 반복문
    {  
        CLK_LOW;
        delay_us(6);
        
        if((value_buffer & 0x80) == 0x80) // 써준 값의 최상위 비트가 1이면 데이터 HIGH
        {
            DAT_HIGH;
        }
        else // 아니면 데이터 LOW
        {
            DAT_LOW;
        }
        
        CLK_HIGH;  
        delay_us(6);
        CLK_LOW;
        value_buffer = value_buffer << 1; // MSB -> LSB까지 하나씩 shift
    } // end of for
    
    if((value_buffer & 0x80) == 0x80)     // LSB 따로 써줌
    {
        DAT_HIGH;
    }
    else
    {
        DAT_LOW;
    }
    
    CLK_HIGH;
    delay_us(6);
    CLK_LOW;           
    
    if(value_buffer == 0x80)   // 파형 오류를 제거하기 위한 구문
    {                        
        DAT_LOW;               // 데이터를 인위적으로 LOW 해줌
    }
    delay_us(2);
} // end of Byte_Write   

void Process_read(void)        // Randomread 8비트 데이터 읽기 함수
{
    U8 i, TEMP_READ_DATA = 0;
    SDA_IN;
    
    for(i=0;i<8;i++)           // 8비트 데이터 읽기
    {
        CLK_LOW;
        delay_us(6);
        CLK_HIGH;
        delay_us(6);
        CLK_LOW;               // CLK_LOW에서 데이터를 읽음
        
        TEMP_READ_DATA = ((PIND & 0x02) == 0x00) ? 0x00 : 0x80;   // 데이터 읽은 값이 0이면 0x00 아니면 0x80
        TEMP_READ_DATA = TEMP_READ_DATA >> i;                     // MSB부터 자리 정렬 shift
        Read_Data |= TEMP_READ_DATA;                              // 읽은 데이터 값 저장
    } // end of for

    if(IIC_Data == Read_Data)  // write 값과 read 값이 일치하면 LED 켜줌(0b 1111 0000)
    {
        PORTC = 0xF0;
    }
} // end of Process_read 

void ACK_write(void)           // ACK 함수 slave -> master
{
    U8 i_ack;                  // ACK 확인받기위한 반복문 변수
    
    SDA_IN;                    // 데이터 입력
    CLK_HIGH; 
    
    for(i_ack=0;i_ack<10;i_ack++) // 10번 반복중 ACK 받으면 반복문 탈출
    {
        if((PIND & 0x02) == 0x00)
        {
            i_ack = 10;
            PORTC = 0xFE;
        }
        else 
        {
            PORTC = 0xFF;
        }
    } // end of for
        
    delay_us(6);
    CLK_LOW;
    SDA_OUT;                   // 데이터 출력 
} // end of ACK_write

/*
void ACK_read(void)            // ACK 함수 master -> slave
{
    SDA_OUT;                   // 데이터 출력
    DAT_LOW;
    CLK_HIGH;
    delay_us(6);
    CLK_LOW;
} // end of ACK_read
*/

void no_ACK(void)              // NACK 함수 master -> slave 
{
    SDA_OUT;                   // 데이터 출력
    DAT_HIGH;
    CLK_HIGH;
    delay_us(6);
    CLK_LOW;
} // end of no_ACK

void Byte_Write(void)          // Bytewrite 함수
{
    IIC_START();               // start
    Process_write(Dev_Add_W);  // device address
    ACK_write();               // ack (slave -> master)
    
    Process_write(IIC_Add);    // address
    ACK_write();               // ack (slave -> master)
    
    for(i=0;i<n;i++)           // data[] 반복
    {
        Process_write(IIC_Data_1[i]); // data
        ACK_write();                  // ack (slave -> master)
    }
    IIC_STOP();                // stop
} // end of Byte_Write

void Random_read(void)         // Randomread 함수
{
    IIC_START();               // start
    Process_write(Dev_Add_W);  // device address(0번 비트 0)
    ACK_write();               // ack (slave -> master)
    
    Process_write(IIC_Add);    // address
    ACK_write();               // ack (slave -> master)
    
    IIC_START();               // start
    Process_write(Dev_Add_R);  // device address(0번 비트 1)
    ACK_write();               // ack (slave -> master)
    
    Process_read();            // data read
    no_ACK();                  // nack (master -> slave)
    IIC_STOP();                // stop
} // end of Random_read 
