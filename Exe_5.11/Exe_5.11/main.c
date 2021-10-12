/*
 * Exe_5.11.c
 *
 * Created: 18/08/2020 15:36:59
 * Author : Diego
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define set_bit(Y, bit_x) (Y|=(1<<bit_x))

#define clr_bit(Y, bit_x) (Y&=~(1<<bit_x))

#define tst_bit(Y, bit_x) (Y&(1<<bit_x))

#define cpl_bit(Y, bit_x) (Y^=(1<<bit_x))

#define LED PD2
#define BOTAO PD7

void delay_ms(uint16_t);

int main(void)
{
	DDRD = 0b00000100;
	PORTD = 0b11111111;
	
	while(1)
	{
		uint16_t myDelay = 250;
		set_bit(PORTD, LED);
		
		if (!tst_bit(PIND, BOTAO))
		{
			_delay_ms(10);
			while(!tst_bit(PIND, BOTAO))
			{
				cpl_bit(PORTD, LED);
				delay_ms(myDelay);
				
				myDelay -= 10;				
				
				if (myDelay < 10 || myDelay > 250)
					myDelay = 10;								
			}
		}
	}
}

void delay_ms(uint16_t milliseconds)
{
	while(milliseconds > 0)
	{
		_delay_ms(1);
		milliseconds--;
	}
}
