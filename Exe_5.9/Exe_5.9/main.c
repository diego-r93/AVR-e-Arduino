/*
 * Exe_5.9.c
 *
 * Created: 18/08/2020 15:01:29
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
			clr_bit(PORTD, LED);			
		}
		else
		{
			set_bit(PORTD, LED);
		}
	}
}