/*
 * ljh_1108_project1_array.c
 *
 * Created: 2023-11-08 ¿ÀÈÄ 2:43:50
 * Author: wjdgh
 */

/* 1Byte Write Mode_Array[] */

#include <mega128a.h>
#include <delay.h>

#define SCL_OUT DDRD |= 0x01 
#define SDA_OUT DDRD |= 0x02 
#define SDA_IN DDRD &= 0xFD 

#define CLK_HIGH PORTD |= 0x01 
#define CLK_LOW PORTD &= 0xFE 
#define DAT_HIGH PORTD |= 0x02 
#define DAT_LOW PORTD &= 0xFD 

/*#define Dev_Add 0xA3 // 0b 1010 0011
#define Add 0x71 // 0b 0111 0001
#define Data 0x51 // 0b 0101 0001*/

#define sw_4 PINE.4
/*#define sw_5 PINE.5
#define sw_6 PINE.6
#define sw_7 PINE.7*/

#define n 3

const unsigned char array[n] = {0xA0, 0x71, 0x51};

typedef unsigned char U8;

void IIC_START(void);
void IIC_STOP(void);
void Process(U8 value[]);
void ACK_write(void);
void Byte_Write(void);

void main(void)
{    
    DDRC = 0xFF;    
    PORTC = 0xFF; 
    /*DDRE = 0x00;*/        
                
    SCL_OUT;
    SDA_OUT;
    
    while(1)
    {
        Byte_Write(); 
          
        delay_ms(100);
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

void Process(U8 value[])
{
    U8 i_write, i_array;
    U8 value_buffer[];
     
    for(i_array=0;i_array<n;i_array++)
    {
        value_buffer[i_array] = value[i_array];
		for(i_write=0;i_write<8;i_write++)
        {
			if((value_buffer[i_array] & 0x80) == 0x80)
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
            value_buffer[i_array] = value_buffer[i_array] << 1;
        } // end of for i_write
        ACK_write();
		
    } // end of i_array    
    
    /*for(i_write=0;i_write<7;i_write++)
    {  
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
    delay_us(2); */
    
} // end of Byte_Write    

void ACK_write(void)
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
} // end of ACK

void Byte_Write(void)
{
	IIC_START();
	Process(array[]);
	IIC_STOP();
}