/*
 * Exe_5.12.c
 *
 * Created: 18/08/2020 16:32:11
 * Author : Diego
 */ 

//====================================================================================================================//
//												ANIMAÇÃO DE LEDs COM SELEÇÃO										  //
//====================================================================================================================//


#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdint.h>

#define set_bit(Y, bit_x) (Y|=(1<<bit_x))

#define clr_bit(Y, bit_x) (Y&=~(1<<bit_x))

#define tst_bit(Y, bit_x) (Y&(1<<bit_x))

#define cpl_bit(Y, bit_x) (Y^=(1<<bit_x))

#define rot_right(Y, shift) ((Y>>shift)|(Y<<(8-shift)))

#define rot_left(Y, shift) ((Y<<shift)|(Y>>(8-shift)))

#define AJUSTE   PB0
#define SELECAO  PB1

void delay_ms(uint16_t);
void Display(uint8_t, uint16_t);

//--------------------------------------------------------------------------------------------------------------------//


int main(void)
{
	DDRB = 0b11111100;          // PB0 e PB1 como entradas, os demais como saída
	PORTB = 0b00000011;         // Habilita o pull-up dos pinos PB0 e PB1
    DDRD = 0xFF;                // PORTD como saída
    PORTD = 0xFF;               // Desliga os LEDs
    UCSR0B = 0x00;              // PD0 e PD1 como I/O genérico
	
	uint8_t sel = 0;

    while (1) 
    {
		if (!tst_bit(PINB, AJUSTE))
		{
			_delay_ms(10);
			
			if (sel)
				PORTD = 0xFF & ~(1<<(sel - 1));
									
			while(!tst_bit(PINB, AJUSTE))
			{
				if (!tst_bit(PINB, SELECAO))
				{
					_delay_ms(10);
					++sel;
					while(!tst_bit(PINB, SELECAO));
										
					PORTD = 0xFF & ~(1<<(sel - 1));					
					
					if (sel > 8)
						sel = 0;					
				}
			}
			PORTD = 0xFF;       // Desliga os LEDs
		}
		
		Display(sel, 100);		
    }
}

//--------------------------------------------------------------------------------------------------------------------//

void delay_ms(uint16_t milliseconds)
{
	while(milliseconds > 0)
	{
		_delay_ms(1);
		milliseconds--;
	}
}

void Display(uint8_t sel, uint16_t delay)
{	
	delay_ms(delay);
	
	if ((PORTD == 0x00) && (sel > 0 && sel < 4))
	{
		PORTD = 0xFF;
		delay_ms(delay);
	}
	
	if ((PORTD == 0xFF) && (sel == 3))
	{
		PORTD = 0b11111110;
		delay_ms(delay);
	}	
	
	if ((PORTD == 0xFF) && (sel == 4))
	{
		PORTD = 0b01111111;
		delay_ms(delay);
	}
	
	if ((PORTD == 0xFF) && (sel == 5 || sel == 8))
	{
		PORTD = 0x00;
		delay_ms(delay);
	}
			
	switch(sel)
	{
		case 1:	PORTD <<= 1;				
				break;
		
		case 2:	PORTD >>= 1;				
				break;
				
		case 3: PORTD = rot_left(PORTD, 1);
				break;
				
		case 4: PORTD = rot_right(PORTD, 1);
				break;
						
		case 5:	PORTD = ~(~PORTD << 1);
				break;
						
		case 6: PORTD -= 1;
				break;
				
		case 7: PORTD += 1;
				break;
				
		case 8:	PORTD = (~PORTD >> 1);
				break;
		
		default:	;
		
	}
}
//====================================================================================================================//
