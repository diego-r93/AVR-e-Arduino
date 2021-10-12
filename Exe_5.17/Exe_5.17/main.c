/*
 * Exe_5.17.c
 *
 * Created: 22/08/2020 05:48:53
 * Author : Diego
 */ 

#include "def_principais.h"
#include "LCD.h"

#define CIMA     PB2
#define ESQUERDA PB3
#define DIREITA  PB4
#define BAIXO    PB5


int main(void)
{
	DDRD = 0xFF;          // PORTD como saída
	DDRB =  0b11000011;   // PORTB como entrada para os pinos PB2, PB3, PB4 e PB5
	PORTB = 0b00111100;   // Habilita o pull-up nos pinos PB2, PB3, PB4 e PB5
	
	byte pos = 0x80;
	
	inic_LCD_4bits();
	
	cmd_LCD(0x0D, 0);     // Cursor piscante 
	
	while (1)
	{
		if (!tst_bit(PINB, CIMA))
		{
			while(!tst_bit(PINB, CIMA));
			_delay_ms(10);
			
			if (pos >= 0xC0 && pos <= 0xCF)
			{
				pos -= 0x40;
				cmd_LCD(pos, 0);
			}
		}
		
		if (!tst_bit(PINB, ESQUERDA))
		{
			while(!tst_bit(PINB, ESQUERDA));
			_delay_ms(10);
			
			if ((pos > 0x80 && pos <= 0x8F)  || (pos > 0xC0 && pos <= 0xCF))
			{	
				pos -= 1;			
				cmd_LCD(pos, 0);
			}			
		}
		
		if (!tst_bit(PINB, DIREITA))
		{
			while(!tst_bit(PINB, DIREITA));
			_delay_ms(10);
			
			if ( (pos >= 0x80 && pos < 0x8F) || (pos >= 0xC0 && pos < 0xCF))
			{
				pos += 1;
				cmd_LCD(pos, 0);
			}			
		}
		
		if (!tst_bit(PINB, BAIXO))
		{
			while(!tst_bit(PINB, BAIXO));
			_delay_ms(10);
			
			if (pos >= 0x80 && pos <= 0x8F)
			{
				pos += 0x40;
				cmd_LCD(pos, 0);
			}
		}
	}
		
	return 0;
}

