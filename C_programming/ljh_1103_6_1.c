/*
 * ljh_1103_6_1.c
 *
 * Created: 2023-11-03 ¿ÀÈÄ 4:02:27
 * Author: wjdgh
 */

#include <mega128a.h>

void main(void)
{ 
    unsigned char key;   

    DDRC = 0xFF;
    DDRE &= 0x0F;
    
    PORTC = 0xFF;
while (1)
    {
        key = PINE & 0xF0; 
        switch(key)
        {
            case 0b11100000: PORTC = 0x00;                                                                  
            break;
            case 0b11010000: PORTC = 0xFF;
            break; 
            case 0b10110000: PORTC = 0x55;
            break;                        
            case 0b01110000: PORTC = 0xAA;
            break;  
            default:
            break;
        } //end of switch
    } // end of while
} // end of main
