/*
 * Botao_LED.c
 *
 * Created: 17/08/2020 21:41:19
 * Author : diego
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
		if (!tst_bit(PIND, BOTAO))              // Se o botão for pressionado executa o if
		{
			while(!tst_bit(PIND, BOTAO));		// Fica preso até soltar o botão
			
			_delay_ms(10);                      // Atraso de 10ms para eliminar o ruído do botão
			
			if (tst_bit(PORTD, LED))			// Se o LED estiver apagado, liga o LED
			clr_bit(PORTD, LED);
			else                                // Se não apaga o LED
			set_bit(PORTD, LED);
		}
	}
}
