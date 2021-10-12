/*
 * Exe_5.10.c
 *
 * Created: 18/08/2020 15:24:58
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

int main(void)
{
	DDRD = 0b00000100;
	PORTD = 0b11111111;
	
	while(1)
	{
		if (!tst_bit(PIND, BOTAO))
		{
			_delay_ms(10);
			while(!tst_bit(PIND, BOTAO))
			{
				cpl_bit(PORTD, LED);
				_delay_ms(100);
			}			
		}		
	}
}