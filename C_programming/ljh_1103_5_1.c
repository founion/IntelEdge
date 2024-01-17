/*
 * ljh_1103_5_1.c
 *
 * Created: 2023-11-03 ¿ÀÈÄ 3:12:10
 * Author: wjdgh
 */

#include <mega128a.h>
#include <delay.h>

#define LED0 PORTC.0
#define LED7 PORTC.7
#define ON 0
#define OFF 1

void main(void)
{
    DDRC = 0xFF;
    PORTC = 0xFF;                            
    while (1)
    {
        LED0 = ON;
        LED7 = ON;
        delay_ms(500);
        
        LED0 = OFF; 
        LED7 = OFF;
        delay_ms(500);  
    }
}
