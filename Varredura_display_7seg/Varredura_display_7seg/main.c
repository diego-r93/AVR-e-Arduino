/*
 * Varredura_display_7seg.c
 *
 * Created: 08/07/2021 11:07:47
 * Author : diego
 */ 

//====================================================================================================================//
//											VARREDURA DE DISPLAYS DE 7 SEGMENTOS									  //
//====================================================================================================================//

#define F_CPU	16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

#define clr_bit(Y, bit_x) (Y &= ~(1<<bit_x))

unsigned char DISP[4];	// VAlores para os displays

ISR(TIMER0_OVF_vect)
{
	static unsigned char indice;
	
	PORTB |= 0x0F;			// Apaga todos os displays
	PORTD = DISP[indice];	// Coloca a informação dos display no port correspondente
	clr_bit(PORTB, indice);	// Habilita o display correspondente (Anodo Comum)
	indice++;
	
	if (indice == 4)
		indice = 0;		// Após 4 rotações inicializa para o primeiro display
}

int main(void)
{
    DDRD = 0xFF;
	DDRB = 0x0F;
	PORTB = 0xFF;
	
	UCSR0B = 0x00;
	
	TIMSK0 = 1<<TOIE0;	// Habilita a interrupção por estouro do timer 0
	TCCR0B = 1<<CS02;	// CLK/256 prescaler (CLK = 16 MHz), estouro a cada 4ms
	sei();
	
    while (1) 
    {
		DISP[0] = 0xC0;		// 0
		DISP[1] = 0xF9;		// 1
		DISP[2] = 0xA4;		// 2
		DISP[3] = 0xB0;		// 3
    }
}

