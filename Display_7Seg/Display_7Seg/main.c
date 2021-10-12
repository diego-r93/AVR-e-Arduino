/*
 * Display_7Seg.c
 *
 * Created: 16/08/2020 23:07:18
 * Author : Diego
 */ 

//==============================================================================================//
//						ESCREVENDO EM UM DISPLAY DE 7 SEGMENTOS ANODO COMUM						//
//==============================================================================================//

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

// Constante gravada na memória flash
const uint8_t Tabela[] PROGMEM = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78,
								  0x00, 0x18, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0E};
//------------------------------------------------------------------------------------------------


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
		if (!tst_bit(PINB, BOTAO))
		{
			if (valor == 0x0F)
				valor = 0;
			else
				valor++;
				
			DISPLAY = pgm_read_byte(&Tabela[valor]);
			
			_delay_ms(200);
		}
    }
}
//================================================================================================
