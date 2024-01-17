/*                                            */
/* ljh_iic program.c                          */
/*                                            */
/* Created: 2023-11-10 ���� 11:12:43           */
/* Author: wjdgh                              */
/*                                            */
/* 1Byte Read & Write Mode(use switch, array) */

#include <mega128a.h>
#include <delay.h>

#define SCL_OUT DDRD |= 0x01   // PD.0=1 Ŭ�� ��¸�� 
#define SDA_OUT DDRD |= 0x02   // PD.1=0 ������ ��¸�� 
#define SDA_IN DDRD &= 0xFD    // PD.1=1 ������ �Է¸��  

#define CLK_HIGH PORTD |= 0x01 // PD.0=1 Ŭ�� 1 
#define CLK_LOW PORTD &= 0xFE  // PD.0=0 Ŭ�� 0 
#define DAT_HIGH PORTD |= 0x02 // PD.1=1 ������ 1  
#define DAT_LOW PORTD &= 0xFD  // PD.1=0 ������ 0
#define n 3                    // �������� ��

typedef unsigned char U8;      // ������ Ÿ�� ���ȭ

U8 i;                          // for�� �μ� ����
U8 Dev_Add_W = 0xA0;           // 0b 1010 0000 
U8 Dev_Add_R = 0xA1;           // 0b 1010 0001
U8 IIC_Add = 0xAA;             // 0b 1010 1010
U8 IIC_Data = 0x55;            // 0b 0101 0101
U8 Read_Data = 0;              // �ʱ�ȭ

const U8 IIC_Data_1[n] = {0x55, 0x2D, 0xF0};              // 0b 0101 0101, 0b 0010 1101, 0b 1111 0000

void IIC_START(void);          // START �Լ�
void IIC_STOP(void);           // STOP �Լ�
void Process_write(U8 value);  // Bytewrite 8��Ʈ ������ ����
void Process_read(void);       // Randomread 8��Ʈ ������ �ޱ�
void ACK_write(void);          // ACK �Լ� slave -> master
/* void ACK_read(void); */     // ACK �Լ� master -> slave
void no_ACK(void);             // NACK �Լ� master -> slave
void Byte_Write(void);         // Bytewrite �Լ�
void Random_read(void);        // Randomread �Լ� 

void main(void)
{
    U8 key, old_sw, new_sw4, new_sw5;  
      
    DDRC = 0xFF;               // Ȯ���� ���� LED 
    DDRE = 0x00;               // ����ġ �ʱ� ����  
    PORTC = 0xFF;              // �ʱ� LED ��� OFF
                
    SCL_OUT;                   // Ŭ�� ���
    SDA_OUT;                   // ������ ���
       
    old_sw = PINE & 0xF0;      // PE4 ����ġ�� ���°� ����     
    
    while(1)
    {
        new_sw4 = PINE & 0x10; // 1�� ����ġ 
        new_sw5 = PINE & 0x20; // 2�� ����ġ
        key = ((old_sw != 0) && (new_sw4 == 0))? 4:0;     // 1�� ����ġ Falling Edge �Ǵ�  
        if(key == 0)
        {
            key = ((old_sw != 0) && (new_sw5 == 0))? 5:0; // 2�� ����ġ Falling Edge �Ǵ�
        } // end of if
                
        switch(key)
        {
            case 4: PORTC = 0xAA, Byte_Write(), delay_ms(10); break;  // 1�� ����ġ Falling Edge�̸� LED�Ѱ�(10101010) Bytewrite ����   
            case 5: PORTC = 0x55, Random_read(), delay_ms(10); break; // 2�� ����ġ Falling Edge�̸� LED�Ѱ�(01010101) Randomread ����

            default: break;
        } // end of switch
    } // end of while
} // end of main   

void IIC_START(void)           // START �Լ�
{
    DAT_HIGH;
    CLK_HIGH; 
    delay_us(6);
    DAT_LOW;
    CLK_LOW;
} // end of IIC_START
    
void IIC_STOP(void)            // STOP �Լ�
{
    DAT_LOW;
    CLK_HIGH; 
    delay_us(6);
    DAT_HIGH;
    CLK_LOW;
} // end of IIC_STOP

void Process_write(U8 value)   // Bytewrite 8��Ʈ ������ ���� �Լ�
{
    U8 i_write;                // 8��Ʈ ������ ���ֱ� ���� �ݺ��� ����
    U8 value_buffer;           // �� ������ ���۰�
    
    value_buffer = value; 
        
    for(i_write=0;i_write<7;i_write++)    // 7��Ʈ ������ ���ֱ� ���� �ݺ���
    {  
        CLK_LOW;
        delay_us(6);
        
        if((value_buffer & 0x80) == 0x80) // ���� ���� �ֻ��� ��Ʈ�� 1�̸� ������ HIGH
        {
            DAT_HIGH;
        }
        else // �ƴϸ� ������ LOW
        {
            DAT_LOW;
        }
        
        CLK_HIGH;  
        delay_us(6);
        CLK_LOW;
        value_buffer = value_buffer << 1; // MSB -> LSB���� �ϳ��� shift
    } // end of for
    
    if((value_buffer & 0x80) == 0x80)     // LSB ���� ����
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
    
    if(value_buffer == 0x80)   // ���� ������ �����ϱ� ���� ����
    {                        
        DAT_LOW;               // �����͸� ���������� LOW ����
    }
    delay_us(2);
} // end of Byte_Write   

void Process_read(void)        // Randomread 8��Ʈ ������ �б� �Լ�
{
    U8 i, TEMP_READ_DATA = 0;
    SDA_IN;
    
    for(i=0;i<8;i++)           // 8��Ʈ ������ �б�
    {
        CLK_LOW;
        delay_us(6);
        CLK_HIGH;
        delay_us(6);
        CLK_LOW;               // CLK_LOW���� �����͸� ����
        
        TEMP_READ_DATA = ((PIND & 0x02) == 0x00) ? 0x00 : 0x80;   // ������ ���� ���� 0�̸� 0x00 �ƴϸ� 0x80
        TEMP_READ_DATA = TEMP_READ_DATA >> i;                     // MSB���� �ڸ� ���� shift
        Read_Data |= TEMP_READ_DATA;                              // ���� ������ �� ����
    } // end of for

    if(IIC_Data == Read_Data)  // write ���� read ���� ��ġ�ϸ� LED ����(0b 1111 0000)
    {
        PORTC = 0xF0;
    }
} // end of Process_read 

void ACK_write(void)           // ACK �Լ� slave -> master
{
    U8 i_ack;                  // ACK Ȯ�ιޱ����� �ݺ��� ����
    
    SDA_IN;                    // ������ �Է�
    CLK_HIGH; 
    
    for(i_ack=0;i_ack<10;i_ack++) // 10�� �ݺ��� ACK ������ �ݺ��� Ż��
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
    SDA_OUT;                   // ������ ��� 
} // end of ACK_write

/*
void ACK_read(void)            // ACK �Լ� master -> slave
{
    SDA_OUT;                   // ������ ���
    DAT_LOW;
    CLK_HIGH;
    delay_us(6);
    CLK_LOW;
} // end of ACK_read
*/

void no_ACK(void)              // NACK �Լ� master -> slave 
{
    SDA_OUT;                   // ������ ���
    DAT_HIGH;
    CLK_HIGH;
    delay_us(6);
    CLK_LOW;
} // end of no_ACK

void Byte_Write(void)          // Bytewrite �Լ�
{
    IIC_START();               // start
    Process_write(Dev_Add_W);  // device address
    ACK_write();               // ack (slave -> master)
    
    Process_write(IIC_Add);    // address
    ACK_write();               // ack (slave -> master)
    
    for(i=0;i<n;i++)           // data[] �ݺ�
    {
        Process_write(IIC_Data_1[i]); // data
        ACK_write();                  // ack (slave -> master)
    }
    IIC_STOP();                // stop
} // end of Byte_Write

void Random_read(void)         // Randomread �Լ�
{
    IIC_START();               // start
    Process_write(Dev_Add_W);  // device address(0�� ��Ʈ 0)
    ACK_write();               // ack (slave -> master)
    
    Process_write(IIC_Add);    // address
    ACK_write();               // ack (slave -> master)
    
    IIC_START();               // start
    Process_write(Dev_Add_R);  // device address(0�� ��Ʈ 1)
    ACK_write();               // ack (slave -> master)
    
    Process_read();            // data read
    no_ACK();                  // nack (master -> slave)
    IIC_STOP();                // stop
} // end of Random_read 
