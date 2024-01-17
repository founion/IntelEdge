/*
 * ljh_1108_project1_read.c
 *
 * Created: 2023-11-08 ¿ÀÈÄ 3:31:47
 * Author: wjdgh
 */

/* 1Byte Read & Write Mode(use switch) */

#include <mega128a.h>
#include <delay.h>

#define SCL_OUT DDRD |= 0x01 
#define SDA_OUT DDRD |= 0x02  
#define SDA_IN DDRD &= 0xFD  

#define CLK_HIGH PORTD |= 0x01  
#define CLK_LOW PORTD &= 0xFE 
#define DAT_HIGH PORTD |= 0x02  
#define DAT_LOW PORTD &= 0xFD
#define n 3

typedef unsigned char U8;

U8 i;
U8 Dev_Add_W = 0xA0; /* 0b 1010 0000 */
U8 Dev_Add_R = 0xA1; /* 0b 1010 0001 */
U8 IIC_Add = 0xAA; /* 0b 1010 1010 */
U8 IIC_Data = 0x55; /* 0b 0101 0101 */
U8 Read_Data = 0;

const U8 IIC_Data_1[n] = {0x55, 0x2D, 0xF0}; // 0b 0101 0101, 0b 0010 1101, 0b 1111 0000

void IIC_START(void);
void IIC_STOP(void);
void Process_write(U8 value);
void Process_read(void);
void ACK_write(void);
/* void ACK_read(void); */
void no_ACK(void);
void Byte_Write(void);
void Random_read(void); 

void main(void)
{
    U8 key, old_sw, new_sw4, new_sw5;  
      
    DDRC = 0xFF; 
    DDRE = 0x00;   
    PORTC = 0xFF;
                
    SCL_OUT;
    SDA_OUT;
    
    
    old_sw = PINE & 0xF0;     
    
    while(1)
    {
        new_sw4 = PINE & 0x10;
        new_sw5 = PINE & 0x20;
        key = ((old_sw != 0) && (new_sw4 == 0))? 4:0;  
        if(key == 0)
        {
            key = ((old_sw != 0) && (new_sw5 == 0))? 5:0;
        } // end of if
                
        switch(key)
        {
            case 4: PORTC = 0xAA, Byte_Write(), delay_ms(10); break;   
            case 5: PORTC = 0x55, Random_read(), delay_ms(10); break;

            default: break;
        } // end of switch        
    } // end of while
} // end of main   

void IIC_START(void)
{
    DAT_HIGH;
    CLK_HIGH; 
    delay_us(6);
    DAT_LOW;
    CLK_LOW;
} // end of IIC_START
    
void IIC_STOP(void)
{
    DAT_LOW;
    CLK_HIGH; 
    delay_us(6);
    DAT_HIGH;
    CLK_LOW;
} // end of IIC_STOP

void Process_write(U8 value)
{
    U8 i_write;
    U8 value_buffer;
    
    value_buffer = value; 
        
    for(i_write=0;i_write<7;i_write++)
    {  
        CLK_LOW;
        delay_us(6);
        
        if((value_buffer & 0x80) == 0x80)
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
        value_buffer = value_buffer << 1;
    }
    
    if((value_buffer & 0x80) == 0x80)
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
    
    if(value_buffer == 0x80)
    {
        DAT_LOW;
    }
    delay_us(2);
} // end of Byte_Write   

void Process_read(void)
{
    U8 i, TEMP_READ_DATA = 0;
    SDA_IN;
    
    for(i=0;i<8;i++)
    {
        CLK_LOW;
        delay_us(6);
        CLK_HIGH;
        delay_us(6);
        CLK_LOW;
        
        TEMP_READ_DATA = ((PIND & 0x02) == 0x00) ? 0x00 : 0x80;
        TEMP_READ_DATA = TEMP_READ_DATA >> i;
        Read_Data |= TEMP_READ_DATA;
    } // end of for

    if(IIC_Data == Read_Data)
    {
        PORTC = 0xF0;
    }
} // end of Process_read 

void ACK_write(void) /* slave -> master */
{
    U8 i_ack;
    
    SDA_IN; 
    CLK_HIGH; 
    
    for(i_ack=0;i_ack<10;i_ack++)
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
    SDA_OUT;  
} // end of ACK_write

/*
void ACK_read(void)
{
    SDA_OUT;
    DAT_LOW;
    CLK_HIGH;
    delay_us(6);
    CLK_LOW;
} // end of ACK_read
*/

void no_ACK(void) /* master -> slave */
{
    SDA_OUT;
    DAT_HIGH;
    CLK_HIGH;
    delay_us(6);
    CLK_LOW;
} // end of no_ACK

void Byte_Write(void)
{
    IIC_START();
    Process_write(Dev_Add_W);
    ACK_write();
    
    Process_write(IIC_Add);
    ACK_write();
    
    for(i=0;i<n;i++)
    {
        Process_write(IIC_Data_1[i]);
        ACK_write();
    }
    IIC_STOP();
} // end of Byte_Write

void Random_read(void)
{
    IIC_START();
    Process_write(Dev_Add_W);
    ACK_write();
    
    Process_write(IIC_Add);
    ACK_write();
    
    IIC_START();
    Process_write(Dev_Add_R);
    ACK_write();
    
    Process_read();
    no_ACK();
    IIC_STOP();
} // end of Random_read 