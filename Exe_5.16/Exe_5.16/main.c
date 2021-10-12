/*
 * Exe_5.16.c
 *
 * Created: 22/08/2020 05:08:57
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
	
    while (1) 
    {
		cmd_LCD(0x01, 0);
		cmd_LCD('*', 1);
		_delay_ms(200);
		
		for (byte i = 0; i < 16; i++)
		{
			cmd_LCD(0x1C, 0);
			_delay_ms(200);
		}
		cmd_LCD(0x01, 0);   // Limpa o display e retorna o cursor para a primeira posição
		
		cmd_LCD(0xCF, 0);   // Desloca o cursor para o final da segunda linha
		cmd_LCD('*', 1);
		_delay_ms(200);
		
		for (byte i = 0; i < 16; i++)
		{
			cmd_LCD(0x18, 0);
			_delay_ms(200);
		}		
    }
	
	return 0;
}

