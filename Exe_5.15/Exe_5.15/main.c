/*
 * Exe_5.15.c
 *
 * Created: 22/08/2020 04:30:25
 * Author : Diego
 */ 

#include "def_principais.h"
#include "LCD.h"

typedef uint8_t byte;

int main(void)
{
    DDRD = 0xFF;
    DDRB = 0xFF;
    
    inic_LCD_4bits();
	escreve_LCD("*");
	
    while (1) 
    {		
		for (byte i = 0; i < 16; i++)
		{
			cmd_LCD(0x1C, 0);
			_delay_ms(200);
		}
			
		for (byte i = 0; i < 16; i++)
		{
			cmd_LCD(0x18, 0);
			_delay_ms(200);
		}			
    }
	
	return 0;
}

