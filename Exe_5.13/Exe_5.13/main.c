/*
 * Exe_5.13.c
 *
 * Created: 18/08/2020 23:50:48
 * Author : Diego
 */ 

//======================================================================================================//
//						ESCREVENDO EM UM DISPLAY DE 7 SEGMENTOS ANODO COMUM					        	//
//======================================================================================================//


#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdint.h>

#define set_bit(Y, bit_x) (Y|=(1<<bit_x))

#define clr_bit(Y, bit_x) (Y&=~(1<<bit_x))

#define tst_bit(Y, bit_x) (Y&(1<<bit_x))

#define cpl_bit(Y, bit_x) (Y^=(1<<bit_x))

#define DISPLAY PORTD
#define BOTAO PB0

const uint8_t Tabela[] PROGMEM = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78,
								  0x00, 0x18, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0E};
//------------------------------------------------------------------------------------------------------//


int main(void)
{
	uint8_t valor = 0;
	
	DDRB = 0b11111110;
	PORTB = 0x01;
	DDRD = 0xFF;
	PORTD = 0xFF;
	UCSR0B = 0x00;
	
	while (1)
	{
		while (tst_bit(PINB, BOTAO))
		{
			valor++;
						
			if (valor > 6)
				valor = 0;
		}
		if (!tst_bit(PINB, BOTAO))
		{
			_delay_ms(10);
			while(!tst_bit(PINB, BOTAO));			
					
			DISPLAY = pgm_read_byte(&Tabela[valor]);
		}
	}
}
//======================================================================================================//
